using System.Text;
using Xunit;
using static Ecitygml.Tests.Api.ApiHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>The cases of crates/ecitygml/tests/api/writer.md.</summary>
public class WriterTests
{
    private readonly CityModel _model = Read("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml");

    private void AssertReadsBack(string path) => Assert.Equal(FeatureTypes(_model), FeatureTypes(ReadPath(path)));

    /// <summary>The model written as `Gml` text.</summary>
    private string Text(Formatting? formatting = null)
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        if (formatting != null)
        {
            writer.WithFormatting(formatting);
        }
        writer.Finish(_model);
        return Encoding.UTF8.GetString(writer.Data().Clone());
    }

    private static string[] Lines(string text) => text.TrimEnd('\n').Split('\n');

    [Fact]
    public void WriterInMemory()
    {
        foreach (var format in new[] { CitygmlFormat.Gml, CitygmlFormat.GmlGz, CitygmlFormat.GmlZst })
        {
            var writer = GmlWriter.create(format);
            Assert.Empty(writer.Data().Clone());
            writer.Finish(_model);
            Assert.Equal(FeatureTypes(_model), FeatureTypes(ReadData(writer.Data().Clone(), format)));
        }
        Assert.Contains("<bldg:Building", Text());
    }

    [Fact]
    public void WriterFiles()
    {
        using var dir = new TempDir();
        foreach (var name in new[] { "out.gml", "out.gml.gz", "out.gml.zst" })
        {
            GmlWriter.FromPath(Utf8(dir.PathOf(name))).Finish(_model);
            AssertReadsBack(dir.PathOf(name));
        }
    }

    [Fact]
    public void WriterOverwritesFile()
    {
        using var dir = new TempDir();
        var path = dir.PathOf("out.gml");
        File.WriteAllText(path, new string('x', 100_000));
        GmlWriter.FromPath(Utf8(path)).Finish(_model);
        AssertReadsBack(path);
    }

    [Fact]
    public void WriterBasePathWithFormat()
    {
        using var dir = new TempDir();
        File.WriteAllText(dir.PathOf("out.gml.gz"), new string('x', 100_000));
        GmlWriter.FromBasePathWithFormat(Utf8(dir.PathOf("out")), CitygmlFormat.GmlGz).Finish(_model);
        AssertReadsBack(dir.PathOf("out.gml.gz"));
    }

    [Fact]
    public void WriterFormatting()
    {
        var defaultText = Text();
        Assert.True(Lines(defaultText).Length > 1);
        Assert.DoesNotContain(Lines(defaultText), line => line.StartsWith(' ') || line.StartsWith('\t'));
        Assert.Equal(defaultText, Text(Formatting.NewLine()));
        Assert.Equal(defaultText, Text(Formatting.Indent((byte)' ', 0)));

        Assert.True(Lines(Text(Formatting.Compact())).Length < Lines(defaultText).Length);

        var spaces = Lines(Text(Formatting.Indent((byte)' ', 2)));
        Assert.Contains(spaces, line => line.StartsWith("  <"));
        Assert.DoesNotContain(spaces, line => line.StartsWith('\t'));

        var tabs = Text(Formatting.Indent((byte)'\t', 1));
        Assert.Contains(Lines(tabs), line => line.StartsWith("\t<"));
        Assert.Equal(FeatureTypes(_model), FeatureTypes(ReadData(Encoding.UTF8.GetBytes(tabs), CitygmlFormat.Gml)));
    }

    [Fact]
    public void WriterFinishOnce()
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(_model);
        AssertError(() => writer.Finish(_model), ErrorKind.InvalidArgument, "already finished");
    }

    [Fact]
    public void WriterUnsupportedExtension()
    {
        using var dir = new TempDir();
        AssertError(() => GmlWriter.FromPath(Utf8(dir.PathOf("out.txt"))), ErrorKind.InvalidArgument, "txt");
    }

    [Fact]
    public void WriterMissingDirectory()
    {
        using var dir = new TempDir();
        AssertError(() => GmlWriter.FromPath(Utf8(dir.PathOf("missing/out.gml"))), ErrorKind.Io, "");
    }

    private const string FzkLod2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

    /// <summary>A city model written as `Gml` text.</summary>
    private static string TextOf(CityModel cityModel)
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(cityModel);
        return Encoding.UTF8.GetString(writer.Data().Clone());
    }

    private static int Occurrences(string text, string part) => text.Split(part).Length - 1;

    [Fact]
    public void WriterKeepsReferences()
    {
        var text = TextOf(Read(FzkLod2));
        Assert.Equal(1, Occurrences(text, "xlink:href=\"#PolyID7350_878_759628_120742\""));
        Assert.Equal(1, Occurrences(text, "gml:id=\"PolyID7350_878_759628_120742\""));
    }

    /// <summary>The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document
    /// order.</summary>
    private static List<(double, double, double)> WallCoordinates(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next)
            .Select(f => WallSurface.TryFrom(f)?.Lod2MultiSurface()?.Object())
            .OfType<MultiSurface>()
            .SelectMany(ms => Items(ms.SurfaceMember().Next))
            .Select(member => Polygon.TryFrom(member.Object()!))
            .OfType<Polygon>()
            .SelectMany(polygon => Items(LinearRing.TryFrom(polygon.Exterior()!)!.Points().Next))
            .Select(p => (p.X(), p.Y(), p.Z()))
            .ToList();

    [Fact]
    public void WriterPreservesCoordinates()
    {
        var cityModel = Read(FzkLod2);
        var written = ReadData(Encoding.UTF8.GetBytes(TextOf(cityModel)), CitygmlFormat.Gml);
        var coordinates = WallCoordinates(cityModel);
        Assert.NotEmpty(coordinates);
        Assert.Equal(coordinates, WallCoordinates(written));
    }
}
