// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces with their doors and
// windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are null when absent; lists are iterators (possibly empty).
// - Code-list values (class, function, ...) are wrappers with `Value()` (and `Code()`).
// - Properties referencing other objects (e.g. a building's boundaries) have `Object()` and `Href()`; `Object()` is
//   null if the property only references an object elsewhere via `xlink:href`.
// - Abstract types are converted with `TryFrom`, e.g. a generic attribute to a `MeasureAttribute`, or a boundary (via
//   `AbstractFeatureKindRef.FromSpaceBoundary`) to a `WallSurface`.
//
// Usage: dotnet run --project examples -- 03_building_report path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       Name: AC14-FZK-Haus
//       Class: 1000
//       ...
//       Boundaries:
//         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//         ...

using Envis.Ecitygml.Diplomat;
using static Envis.Ecitygml.Examples.Common;

namespace Envis.Ecitygml.Examples;

public static class BuildingReport
{
    /// <summary>Values comma-separated, "-" if there are none.</summary>
    private static string Joined(IEnumerable<DiplomatBorrowedSpan<byte>> values)
    {
        var text = string.Join(", ", values.Select(Str));
        return text.Length > 0 ? text : "-";
    }

    /// <summary>The value of a generic attribute: string, integer, double or measure (value and unit).</summary>
    private static string GenericAttributeValue(GenericAttributeKind attribute)
    {
        if (attribute.AsString() is { } text) return Str(text.Value());
        if (attribute.AsInt() is { } integer) return integer.Value().ToString();
        if (attribute.AsDouble() is { } real) return Fixed3(real.Value());
        if (MeasureAttribute.TryFrom(attribute) is { } measure) return $"{Fixed3(measure.Value().Value())} {Str(measure.Value().Uom())}";
        return "(not shown)"; // e.g. a generic attribute set, which holds further attributes
    }

    /// <summary>Prints the doors and windows of a wall, roof or ground surface.</summary>
    private static void PrintFillingSurfaces(AbstractFillingSurfacePropertyIterator fillings)
    {
        foreach (var filling in Items(fillings.Next).Select(property => property.Object()).OfType<AbstractFillingSurfaceKind>())
        {
            Console.WriteLine($"      {filling.FeatureType()} {Str(filling.FeatureId().AsStr())}");
        }
    }

    private static void PrintBuilding(Building building)
    {
        Console.WriteLine($"Building {Str(building.FeatureId().AsStr())}");
        Console.WriteLine($"  Name: {Joined(Items(building.Names().Next).Select(name => name.Value()))}");
        Console.WriteLine($"  Class: {(building.Class() is { } c ? Str(c.Value()) : "-")}");
        Console.WriteLine($"  Functions: {Joined(Items(building.Functions().Next).Select(function => function.Value()))}");
        Console.WriteLine($"  Usages: {Joined(Items(building.Usages().Next).Select(usage => usage.Value()))}");
        Console.WriteLine($"  Roof type: {(building.RoofType() is { } roofType ? Str(roofType.Value()) : "-")}");
        Console.WriteLine($"  Storeys above ground: {building.StoreysAboveGround()?.ToString() ?? "-"}");
        Console.WriteLine($"  Storeys below ground: {building.StoreysBelowGround()?.ToString() ?? "-"}");
        var date = building.DateOfConstruction();
        Console.WriteLine($"  Date of construction: {(date == null ? "-" : $"{date.Year():D4}-{date.Month():D2}-{date.Day():D2}")}");

        Console.WriteLine("  Heights:");
        foreach (var height in Items(building.Heights().Next))
        {
            var length = height.Length();
            Console.WriteLine($"    {Fixed3(length.Value())} {Str(length.Uom())} ({Str(height.HighReference().Value())} to {Str(height.LowReference().Value())})");
        }

        Console.WriteLine("  Generic attributes:");
        foreach (var attribute in Items(building.GenericAttributes().Next))
        {
            Console.WriteLine($"    {Str(attribute.Name())}: {GenericAttributeValue(attribute)}");
        }

        // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof and ground surfaces
        // can have filling surfaces: doors and windows.
        Console.WriteLine("  Boundaries:");
        foreach (var property in Items(building.Boundaries().Next))
        {
            var boundary = property.Object();
            if (boundary == null)
            {
                Console.WriteLine($"    (reference to {property.Href()})");
                continue;
            }
            Console.WriteLine($"    {boundary.FeatureType()} {Str(boundary.FeatureId().AsStr())}");
            var feature = AbstractFeatureKindRef.FromSpaceBoundary(boundary);
            if (WallSurface.TryFrom(feature) is { } wall) PrintFillingSurfaces(wall.FillingSurfaces());
            else if (RoofSurface.TryFrom(feature) is { } roof) PrintFillingSurfaces(roof.FillingSurfaces());
            else if (GroundSurface.TryFrom(feature) is { } ground) PrintFillingSurfaces(ground.FillingSurfaces());
        }
    }

    public static int Run(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("usage: 03_building_report path/to/model.gml");
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
            PrintBuilding(buildings[index]);
        }
        return 0;
    }
}
