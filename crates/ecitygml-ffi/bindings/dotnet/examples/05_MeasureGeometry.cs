// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall, roof and ground
// surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `Area3d()` of a multi surface, `Volume3d()` of a solid,
// `Triangulate()` (a `Triangulation`, whose `Surface()` holds the triangles). They throw `ErrorException` when they
// can't compute a result. A common case: a solid whose surfaces only reference the boundary polygons by `xlink:href`
// (the reader doesn't resolve such references, as in Rust), shown here as "not computable" with the error message.
//
// Usage: dotnet run --project examples -- 05_measure_geometry path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       WallSurface: 4, area 188.629 m^2, 10 triangles
//       RoofSurface: 2, area 138.564 m^2, 4 triangles
//       GroundSurface: 1, area 120.000 m^2, 2 triangles
//       Doors and windows: 0, area 0.000 m^2
//       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

using static Ecitygml.Examples.Common;

namespace Ecitygml.Examples;

public static class MeasureGeometry
{
    private sealed class Measurement
    {
        public int Count;
        public double Area;
        public int Triangles;

        /// <summary>Adds a surface with its highest LoD multi surface; throws `ErrorException` if a calculation fails.</summary>
        public void Add(MultiSurface? multiSurface)
        {
            Count++;
            if (multiSurface == null) return;
            Area += multiSurface.Area3d();
            Triangles += Items(multiSurface.Triangulate().Surface().Triangles().Next).Count();
        }
    }

    /// <summary>Adds the doors and windows of a wall, roof or ground surface.</summary>
    private static void AddFillingSurfaces(AbstractFillingSurfacePropertyIterator fillings, Measurement measurement)
    {
        foreach (var filling in Items(fillings.Next).Select(property => property.Object()).OfType<AbstractFillingSurfaceKind>())
        {
            measurement.Add(HighestLod(filling.Lod3MultiSurface(), filling.Lod2MultiSurface(), filling.Lod1MultiSurface(), filling.Lod0MultiSurface()));
        }
    }

    private static void PrintBoundaries(Building building)
    {
        Measurement walls = new(), roofs = new(), grounds = new(), fillings = new();
        foreach (var boundary in Items(building.Boundaries().Next).Select(property => property.Object()).OfType<AbstractSpaceBoundaryKind>())
        {
            var feature = AbstractFeatureKindRef.FromSpaceBoundary(boundary);
            if (WallSurface.TryFrom(feature) is { } wall)
            {
                walls.Add(HighestLod(wall.Lod3MultiSurface(), wall.Lod2MultiSurface(), wall.Lod1MultiSurface(), wall.Lod0MultiSurface()));
                AddFillingSurfaces(wall.FillingSurfaces(), fillings);
            }
            else if (RoofSurface.TryFrom(feature) is { } roof)
            {
                roofs.Add(HighestLod(roof.Lod3MultiSurface(), roof.Lod2MultiSurface(), roof.Lod1MultiSurface(), roof.Lod0MultiSurface()));
                AddFillingSurfaces(roof.FillingSurfaces(), fillings);
            }
            else if (GroundSurface.TryFrom(feature) is { } ground)
            {
                grounds.Add(HighestLod(ground.Lod3MultiSurface(), ground.Lod2MultiSurface(), ground.Lod1MultiSurface(), ground.Lod0MultiSurface()));
                AddFillingSurfaces(ground.FillingSurfaces(), fillings);
            }
        }
        foreach (var (label, measurement) in new[] { ("WallSurface", walls), ("RoofSurface", roofs), ("GroundSurface", grounds) })
        {
            Console.WriteLine($"  {label}: {measurement.Count}, area {Fixed3(measurement.Area)} m^2, {measurement.Triangles} triangles");
        }
        Console.WriteLine($"  Doors and windows: {fillings.Count}, area {Fixed3(fillings.Area)} m^2");
    }

    private static void PrintSolids(Building building)
    {
        foreach (var (lod, property) in new[] { (1, building.Lod1Solid()), (2, building.Lod2Solid()), (3, building.Lod3Solid()) })
        {
            if (property?.Object() is not { } solid) continue;
            var members = solid.Exterior() is { } shell ? Items(shell.Members().Next).ToList() : [];
            var references = members.Count(member => member.Object() == null);
            Console.WriteLine($"  LoD{lod} solid: {members.Count} surfaces, {references} of them xlink:href references");
            string volume;
            try
            {
                volume = $"{Fixed3(solid.Volume3d())} m^3";
            }
            catch (ErrorException error)
            {
                volume = $"not computable ({ErrorText(error)})";
            }
            Console.WriteLine($"    Volume: {volume}");
        }
    }

    public static int Run(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("usage: 05_measure_geometry path/to/model.gml");
            return 2;
        }
        var cityModel = Common.ReadCityModel(args[0]);
        if (cityModel == null)
        {
            return 1;
        }

        var buildings = Items(cityModel.IterFeatures().Next).Select(Building.TryFrom).OfType<Building>().ToList();
        if (buildings.Count == 0)
        {
            Console.WriteLine("No buildings.");
        }
        for (var index = 0; index < buildings.Count; index++)
        {
            if (index > 0) Console.WriteLine();
            var building = buildings[index];
            Console.WriteLine($"Building {Str(building.FeatureId().AsStr())}");
            try
            {
                PrintBoundaries(building);
            }
            catch (ErrorException error) // e.g. a surface that can't be triangulated
            {
                Console.WriteLine($"  Boundaries: not computable ({ErrorText(error)})");
            }
            PrintSolids(building);
        }
        return 0;
    }
}
