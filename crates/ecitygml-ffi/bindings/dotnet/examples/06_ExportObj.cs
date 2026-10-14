// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer: `Triangulate()` turns a
// multi surface or solid into a `Triangulation`, whose `Surface()` is a triangulated surface; each `Triangle` has its
// corners `A()`, `B()` and `C()`. Every wall, roof and ground surface, door and window becomes a named OBJ group,
// using its highest level of detail; buildings without such surfaces fall back to their highest LoD solid.
//
// Usage: dotnet run --project examples -- 06_export_obj input.gml output.obj
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

using System.Globalization;
using static Ecitygml.Examples.Common;

namespace Ecitygml.Examples;

public static class ExportObj
{
    /// <summary>
    /// Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the last three vertices
    /// (OBJ indices are 1-based and count all vertices written so far).
    /// </summary>
    private sealed class ObjWriter(TextWriter file)
    {
        public int Vertices;
        public int Triangles;
        public int Groups;

        public void WriteGroup(string name, Triangulation triangulation)
        {
            file.Write($"g {name}\n");
            Groups++;
            foreach (var triangle in Items(triangulation.Surface().Triangles().Next))
            {
                foreach (var corner in new[] { triangle.A(), triangle.B(), triangle.C() })
                {
                    file.Write(string.Format(CultureInfo.InvariantCulture, "v {0:F6} {1:F6} {2:F6}\n", corner.X(), corner.Y(), corner.Z()));
                }
                file.Write($"f {Vertices + 1} {Vertices + 2} {Vertices + 3}\n");
                Vertices += 3;
                Triangles++;
            }
        }

        /// <summary>Writes a surface's multi surface (if any); throws `ErrorException` if triangulation fails.</summary>
        public void WriteSurface(string name, MultiSurface? multiSurface)
        {
            if (multiSurface != null) WriteGroup(name, multiSurface.Triangulate());
        }
    }

    /// <summary>Writes the doors and windows of a wall, roof or ground surface (`FeatureType()` names their type).</summary>
    private static void WriteFillingSurfaces(ObjWriter obj, string prefix, AbstractFillingSurfacePropertyIterator fillings)
    {
        foreach (var filling in Items(fillings.Next).Select(property => property.Object()).OfType<AbstractFillingSurfaceKind>())
        {
            obj.WriteSurface($"{prefix}_{filling.FeatureType()}_{Str(filling.FeatureId().AsStr())}",
                HighestLod(filling.Lod3MultiSurface(), filling.Lod2MultiSurface(), filling.Lod1MultiSurface(), filling.Lod0MultiSurface()));
        }
    }

    private static void ExportBuilding(ObjWriter obj, Building building)
    {
        var prefix = Str(building.FeatureId().AsStr());
        var hasSurfaces = false;
        foreach (var boundary in Items(building.Boundaries().Next).Select(property => property.Object()).OfType<AbstractSpaceBoundaryKind>())
        {
            var feature = AbstractFeatureKindRef.FromSpaceBoundary(boundary);
            if (WallSurface.TryFrom(feature) is { } wall)
            {
                obj.WriteSurface($"{prefix}_WallSurface_{Str(wall.FeatureId().AsStr())}",
                    HighestLod(wall.Lod3MultiSurface(), wall.Lod2MultiSurface(), wall.Lod1MultiSurface(), wall.Lod0MultiSurface()));
                WriteFillingSurfaces(obj, prefix, wall.FillingSurfaces());
            }
            else if (RoofSurface.TryFrom(feature) is { } roof)
            {
                obj.WriteSurface($"{prefix}_RoofSurface_{Str(roof.FeatureId().AsStr())}",
                    HighestLod(roof.Lod3MultiSurface(), roof.Lod2MultiSurface(), roof.Lod1MultiSurface(), roof.Lod0MultiSurface()));
                WriteFillingSurfaces(obj, prefix, roof.FillingSurfaces());
            }
            else if (GroundSurface.TryFrom(feature) is { } ground)
            {
                obj.WriteSurface($"{prefix}_GroundSurface_{Str(ground.FeatureId().AsStr())}",
                    HighestLod(ground.Lod3MultiSurface(), ground.Lod2MultiSurface(), ground.Lod1MultiSurface(), ground.Lod0MultiSurface()));
                WriteFillingSurfaces(obj, prefix, ground.FillingSurfaces());
            }
            else
            {
                continue;
            }
            hasSurfaces = true;
        }
        if (hasSurfaces) return;
        foreach (var (lod, property) in new[] { (3, building.Lod3Solid()), (2, building.Lod2Solid()), (1, building.Lod1Solid()) })
        {
            if (property?.Object() is not { } solid) continue;
            obj.WriteGroup($"{prefix}_LoD{lod}Solid", solid.Triangulate());
            return;
        }
    }

    public static int Run(string[] args)
    {
        if (args.Length != 2)
        {
            Console.Error.WriteLine("usage: 06_export_obj input.gml output.obj");
            return 2;
        }
        var cityModel = Common.ReadCityModel(args[0]);
        if (cityModel == null)
        {
            return 1;
        }
        ObjWriter obj;
        try
        {
            using var file = new StreamWriter(args[1]);
            obj = new ObjWriter(file);
            foreach (var building in Items(cityModel.IterFeatures().Next).Select(Building.TryFrom).OfType<Building>())
            {
                ExportBuilding(obj, building);
            }
        }
        catch (Exception error) when (error is ErrorException or IOException or UnauthorizedAccessException)
        {
            Console.Error.WriteLine($"error: {ErrorText(error)}");
            return 1;
        }
        Console.WriteLine($"Wrote {obj.Vertices} vertices, {obj.Triangles} triangles, {obj.Groups} groups");
        return 0;
    }
}
