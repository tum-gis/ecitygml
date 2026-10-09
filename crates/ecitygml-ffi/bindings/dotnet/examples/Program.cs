namespace Envis.Ecitygml.Examples;

/// <summary>
/// Runs an example by name: <c>dotnet run --project examples -- 01_read_city_model model.gml</c>. Each example is a
/// class with <c>Run(string[] args)</c>, which returns the exit code (separate from <c>Main</c>, so the tests can run it
/// in the same process).
/// </summary>
public static class Program
{
    /// <summary>The examples, in the order to learn them.</summary>
    public static readonly IReadOnlyDictionary<string, Func<string[], int>> Examples =
        new Dictionary<string, Func<string[], int>>
        {
            ["01_read_city_model"] = ReadCityModel.Run,
            ["02_list_features"] = ListFeatures.Run,
            ["03_building_report"] = BuildingReport.Run,
            ["04_road_network"] = RoadNetwork.Run,
            ["05_measure_geometry"] = MeasureGeometry.Run,
            ["06_export_obj"] = ExportObj.Run,
            ["07_convert"] = Convert.Run,
        };

    public static int Main(string[] args)
    {
        if (args.Length == 0 || !Examples.TryGetValue(args[0], out var run))
        {
            Console.Error.WriteLine($"usage: dotnet run --project examples -- <{string.Join("|", Examples.Keys)}> <arguments>");
            return 2;
        }
        return run(args[1..]);
    }
}
