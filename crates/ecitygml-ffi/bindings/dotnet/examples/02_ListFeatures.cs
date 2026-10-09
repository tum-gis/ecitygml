// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in those walls, and
// so on. `IterFeatures()` visits all of them, depth first in document order, as `AbstractFeatureKindRef`s. Each tells
// its `FeatureType()`; to use the getters of its concrete type, convert it with that type's `TryFrom`, which returns
// null for other types.
//
// Usage: dotnet run --project examples -- 02_list_features path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Feature type              Count
//     CityModel                     1
//     Building                      1
//     WallSurface                   4
//     ...
//     Total                        22
//
//     Buildings:
//       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

using static Envis.Ecitygml.Examples.Common;

namespace Envis.Ecitygml.Examples;

public static class ListFeatures
{
    private static void Row(string name, object count) => Console.WriteLine($"{name,-24} {count,6}");

    public static int Run(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("usage: 02_list_features path/to/model.gml");
            return 2;
        }
        var cityModel = Common.ReadCityModel(args[0]);
        if (cityModel == null)
        {
            return 1;
        }

        // Count the features per type, in the order the types first appear (an OrderedDictionary keeps it). The
        // feature type is a C# enum, whose name is the type's name.
        var counts = new OrderedDictionary<string, int>();
        foreach (var feature in Items(cityModel.IterFeatures().Next))
        {
            var name = feature.FeatureType().ToString();
            counts[name] = counts.GetValueOrDefault(name) + 1;
        }

        Row("Feature type", "Count");
        foreach (var (name, count) in counts)
        {
            Row(name, count);
        }
        Row("Total", counts.Values.Sum());

        // `Building.TryFrom` turns a feature into a `Building` (or null).
        Console.WriteLine();
        Console.WriteLine("Buildings:");
        foreach (var building in Items(cityModel.IterFeatures().Next).Select(Building.TryFrom).OfType<Building>())
        {
            Console.WriteLine($"  {Str(building.FeatureId().AsStr())}");
        }
        return 0;
    }
}
