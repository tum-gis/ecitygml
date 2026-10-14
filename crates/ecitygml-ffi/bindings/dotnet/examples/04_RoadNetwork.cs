// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area areas and the volumes
// of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which (like the road
// itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks). Each space is bounded by
// traffic areas or auxiliary traffic areas, its ground surfaces. The spaces are reached through properties
// (`Object()`), the areas through the space's `Boundaries()`, converted with `TryFrom`. Geometry calculations
// (`Length3d`, `Area3d`, `Volume3d`) can fail, e.g. for degenerate geometry, and then throw `ErrorException`.
//
// Usage: dotnet run --project examples -- 04_road_network path/to/model.gml
//
// Output for ASAM-UC_RoadShape.gml (shortened):
//
//     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//           Centre line (LoD2): 40.000 m
//           Volume (LoD2 solid): 720.000 m^3
//           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//         ...
//
//     Total volume of traffic spaces (LoD2): 1260.000 m^3

using static Ecitygml.Examples.Common;

namespace Ecitygml.Examples;

public static class RoadNetwork
{
    /// <summary>Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces).</summary>
    private sealed class Totals
    {
        public int Spaces;
        public double Length;
        public double Volume;
        public int Areas;
        public double Area;
    }

    /// <summary>
    /// A measurement as text (e.g. "40.000 m"), passed to <paramref name="add"/>; "-" without geometry, and a note if
    /// the calculation fails.
    /// </summary>
    private static string Measured<T>(T? geometry, Func<T, double> measure, string unit, Action<double> add) where T : class
    {
        if (geometry == null) return "-";
        try
        {
            var value = measure(geometry);
            add(value);
            return $"{Fixed3(value)} {unit}";
        }
        catch (ErrorException error)
        {
            return $"not computable ({ErrorText(error)})";
        }
    }

    /// <summary>
    /// Prints a traffic or auxiliary traffic space, given its parts (the two are separate classes with the same
    /// getters).
    /// </summary>
    private static void PrintSpace(string kind, Id id, MultiCurve? curve, Solid? solid,
        AbstractSpaceBoundaryPropertyIterator boundaries, Func<AbstractFeatureKindRef, (string Label, MultiSurface? Surface)?> area,
        Totals totals, string indent)
    {
        Console.WriteLine($"{indent}{kind} {Str(id.AsStr())}");
        Console.WriteLine($"{indent}  Centre line (LoD2): {Measured(curve, c => c.Length3d(), "m", v => totals.Length += v)}");
        Console.WriteLine($"{indent}  Volume (LoD2 solid): {Measured(solid, s => s.Volume3d(), "m^3", v => totals.Volume += v)}");
        totals.Spaces++;

        // The areas are the space's boundaries of the matching type.
        foreach (var boundary in Items(boundaries.Next).Select(property => property.Object()).OfType<AbstractSpaceBoundaryKind>())
        {
            if (area(AbstractFeatureKindRef.FromSpaceBoundary(boundary)) is not { } found) continue;
            Console.WriteLine($"{indent}  {found.Label}: {Measured(found.Surface, s => s.Area3d(), "m^2", v => totals.Area += v)}");
            totals.Areas++;
        }
    }

    /// <summary>The traffic and auxiliary traffic spaces of a road, section or intersection.</summary>
    private static void PrintSpaces(TrafficSpacePropertyIterator spaces, AuxiliaryTrafficSpacePropertyIterator auxiliarySpaces,
        Totals traffic, Totals auxiliary, string indent)
    {
        foreach (var space in Items(spaces.Next).Select(property => property.Object()).OfType<TrafficSpace>())
        {
            PrintSpace("TrafficSpace", space.FeatureId(), space.Lod2MultiCurve()?.Object(), space.Lod2Solid()?.Object(),
                space.Boundaries(),
                feature => TrafficArea.TryFrom(feature) is { } a
                    ? ($"TrafficArea {Str(a.FeatureId().AsStr())}", a.Lod2MultiSurface()?.Object())
                    : null,
                traffic, indent);
        }
        foreach (var space in Items(auxiliarySpaces.Next).Select(property => property.Object()).OfType<AuxiliaryTrafficSpace>())
        {
            PrintSpace("AuxiliaryTrafficSpace", space.FeatureId(), space.Lod2MultiCurve()?.Object(), space.Lod2Solid()?.Object(),
                space.Boundaries(),
                feature => AuxiliaryTrafficArea.TryFrom(feature) is { } a
                    ? ($"AuxiliaryTrafficArea {Str(a.FeatureId().AsStr())}", a.Lod2MultiSurface()?.Object())
                    : null,
                auxiliary, indent);
        }
    }

    public static int Run(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("usage: 04_road_network path/to/model.gml");
            return 2;
        }
        var cityModel = Common.ReadCityModel(args[0]);
        if (cityModel == null)
        {
            return 1;
        }

        var traffic = new Totals();
        var auxiliary = new Totals();
        var roads = Items(cityModel.IterFeatures().Next).Select(Road.TryFrom).OfType<Road>().ToList();
        foreach (var road in roads)
        {
            Console.WriteLine($"Road {Str(road.FeatureId().AsStr())}");
            PrintSpaces(road.TrafficSpaces(), road.AuxiliaryTrafficSpaces(), traffic, auxiliary, "  "); // a road can hold spaces directly, too
            foreach (var section in Items(road.Sections().Next).Select(property => property.Object()).OfType<Section>())
            {
                Console.WriteLine($"  Section {Str(section.FeatureId().AsStr())}");
                PrintSpaces(section.TrafficSpaces(), section.AuxiliaryTrafficSpaces(), traffic, auxiliary, "    ");
            }
            foreach (var intersection in Items(road.Intersections().Next).Select(property => property.Object()).OfType<Intersection>())
            {
                Console.WriteLine($"  Intersection {Str(intersection.FeatureId().AsStr())}");
                PrintSpaces(intersection.TrafficSpaces(), intersection.AuxiliaryTrafficSpaces(), traffic, auxiliary, "    ");
            }
        }

        Console.WriteLine();
        Console.WriteLine($"Roads: {roads.Count}");
        foreach (var (label, totals) in new[] { ("Traffic spaces", traffic), ("Auxiliary traffic spaces", auxiliary) })
        {
            Console.WriteLine($"{label}: {totals.Spaces}, centre lines {Fixed3(totals.Length)} m, {totals.Areas} areas {Fixed3(totals.Area)} m^2, volume {Fixed3(totals.Volume)} m^3");
        }
        Console.WriteLine($"Total volume of traffic spaces (LoD2): {Fixed3(traffic.Volume)} m^3");
        return 0;
    }
}
