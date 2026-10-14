using System.Globalization;
using System.Text;
using Ecitygml.Diplomat;

namespace Ecitygml.Examples;

/// <summary>Helpers shared by the examples.</summary>
internal static class Common
{
    /// <summary>
    /// Reads a city model, or prints the error and returns null. `FromPath` opens the file and picks the format from
    /// its extension; paths are UTF-8 bytes in the bindings.
    /// </summary>
    public static CityModel? ReadCityModel(string path)
    {
        try
        {
            return GmlReader.FromPath(Encoding.UTF8.GetBytes(path)).Finish();
        }
        catch (ErrorException error)
        {
            Console.Error.WriteLine($"error: {error.Inner.Message()}");
            return null;
        }
    }

    /// <summary>The text of an error: the bindings throw `ErrorException`, whose `Inner` is the ecitygml Error.</summary>
    public static string ErrorText(Exception error) => error is ErrorException e ? e.Inner.Message() : error.Message;

    /// <summary>
    /// A borrowed string: UTF-8 bytes that Rust still owns (`DiplomatBorrowedSpan`), copied into a .NET string.
    /// </summary>
    public static string Str(DiplomatBorrowedSpan<byte> text) => Encoding.UTF8.GetString(text.Clone());

    /// <summary>Diplomat's .NET iterators have `Next()` (null at the end) but are not `IEnumerable`.</summary>
    public static IEnumerable<T> Items<T>(Func<T?> next) where T : class
    {
        for (var item = next(); item != null; item = next())
        {
            yield return item;
        }
    }

    /// <summary>`%.3f`, independent of the current culture's decimal separator.</summary>
    public static string Fixed3(double value) => value.ToString("F3", CultureInfo.InvariantCulture);

    /// <summary>The multi surface of the highest level of detail among a thematic surface's properties (LoD3 first).</summary>
    public static MultiSurface? HighestLod(params MultiSurfaceProperty?[] properties) =>
        properties.Select(property => property?.Object()).FirstOrDefault(multiSurface => multiSurface != null);
}
