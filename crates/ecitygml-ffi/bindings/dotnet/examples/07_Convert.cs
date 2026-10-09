// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`: `FromPath` creates the output file and picks the format from its extension
// (`.gml`, `.gml.gz` or `.gml.zst`), `WithFormatting` sets the layout (here indented by two spaces;
// `Formatting.Compact()` writes no line breaks at all), and `Finish` writes the city model. Reading the written file
// back verifies the result.
//
// Usage: dotnet run --project examples -- 07_convert input.gml output.gml.gz
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

using System.Text;
using static Envis.Ecitygml.Examples.Common;

namespace Envis.Ecitygml.Examples;

public static class Convert
{
    private const int IndentSize = 2;

    private static string Summary(CityModel cityModel) =>
        $"{cityModel.CityObjectsLen()} city object members, {Items(cityModel.IterCityObjects().Next).Count()} city objects";

    /// <summary>What `GmlWriter.FromPath` writes for this path (it fails for other extensions).</summary>
    private static string FormatName(string path) =>
        path.EndsWith(".gml.gz") ? "gzip-compressed CityGML"
        : path.EndsWith(".gml.zst") ? "zstd-compressed CityGML"
        : "CityGML";

    public static int Run(string[] args)
    {
        if (args.Length != 2)
        {
            Console.Error.WriteLine("usage: 07_convert input.gml output.gml[.gz|.zst]");
            return 2;
        }
        var (inputPath, outputPath) = (args[0], args[1]);
        var cityModel = Common.ReadCityModel(inputPath);
        if (cityModel == null)
        {
            return 1;
        }
        Console.WriteLine($"Read: {Summary(cityModel)}");

        try
        {
            var writer = GmlWriter.FromPath(Encoding.UTF8.GetBytes(outputPath));
            writer.WithFormatting(Formatting.Indent((byte)' ', IndentSize));
            writer.Finish(cityModel);
        }
        catch (ErrorException error)
        {
            Console.Error.WriteLine($"error: {ErrorText(error)}");
            return 1;
        }
        Console.WriteLine($"Wrote: {FormatName(outputPath)}, indented by {IndentSize} spaces");

        var written = Common.ReadCityModel(outputPath);
        if (written == null)
        {
            return 1;
        }
        Console.WriteLine($"Read back: {Summary(written)}");
        return 0;
    }
}
