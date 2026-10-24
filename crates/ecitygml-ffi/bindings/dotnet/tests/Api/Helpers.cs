using System.Text;
using Xunit;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>Helpers of the API suite (crates/ecitygml/tests/api/README.md).</summary>
internal static class ApiHelpers
{
    /// <summary>Paths are UTF-8 bytes in the bindings.</summary>
    public static byte[] Utf8(string path) => Encoding.UTF8.GetBytes(path);

    /// <summary>Reads the file at <paramref name="path"/>.</summary>
    public static CityModel ReadPath(string path) => GmlReader.FromPath(Utf8(path)).Finish();

    /// <summary>`GmlReader::new(data, format).finish()`.</summary>
    public static CityModel ReadData(byte[] data, CitygmlFormat format) => GmlReader.create(data, format).Finish();

    public static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(feature => feature.FeatureType()).ToList();

    /// <summary>Asserts that <paramref name="run"/> throws an error of <paramref name="kind"/> whose message contains
    /// <paramref name="part"/>.</summary>
    public static void AssertError(Action run, ErrorKind kind, string part)
    {
        var exception = Assert.Throws<ErrorException>(run);
        Assert.Equal(kind, exception.Inner.Kind());
        Assert.Contains(part, exception.Inner.Message());
    }

    /// <summary>A fresh temporary directory, removed on dispose.</summary>
    public sealed class TempDir : IDisposable
    {
        private readonly string _path = Directory.CreateTempSubdirectory("ecitygml-dotnet-api-").FullName;

        /// <summary>The path of <paramref name="name"/> in the directory.</summary>
        public string PathOf(string name) => Path.Combine(_path, name);

        public void Dispose() => Directory.Delete(_path, recursive: true);
    }
}
