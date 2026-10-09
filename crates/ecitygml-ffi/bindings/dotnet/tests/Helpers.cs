using System.Reflection;
using System.Text;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Tests;

/// <summary>Conveniences shared by the tests.</summary>
internal static class Helpers
{
    /// <summary>The directory of the CityGML fixtures (tests/fixtures at the repository root).</summary>
    public static readonly string Fixtures = typeof(Helpers).Assembly
        .GetCustomAttributes<AssemblyMetadataAttribute>()
        .Single(attribute => attribute.Key == "Fixtures").Value!;

    public static string Fixture(string name) => Path.Combine(Fixtures, name);

    /// <summary>`GmlReader::from_path(path)?.finish()`, as in Rust. Paths are UTF-8 bytes in the bindings.</summary>
    public static CityModel Read(string name) => GmlReader.FromPath(Encoding.UTF8.GetBytes(Fixture(name))).Finish();

    /// <summary>A borrowed string (UTF-8 bytes still owned by Rust), copied into a .NET string.</summary>
    public static string Str(DiplomatBorrowedSpan<byte> text) => Encoding.UTF8.GetString(text.Clone());

    /// <summary>Diplomat's .NET iterators have `Next()` (null at the end) but are not `IEnumerable`.</summary>
    public static IEnumerable<T> Items<T>(Func<T?> next) where T : class
    {
        for (var item = next(); item != null; item = next())
        {
            yield return item;
        }
    }
}
