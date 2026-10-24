using Xunit;
using static Ecitygml.Tests.Api.ApiHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>The cases of crates/ecitygml/tests/api/reader.md.</summary>
public class ReaderTests
{
    private const string FzkLod1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string FzkLod2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

    [Fact]
    public void ReaderFromBytes()
    {
        Assert.Equal(1u, ReadData(File.ReadAllBytes(Fixture(FzkLod1)), CitygmlFormat.Gml).CityObjectsLen());
    }

    [Fact]
    public void ReaderCompressed()
    {
        foreach (var (extension, format) in new[] { ("gz", CitygmlFormat.GmlGz), ("zst", CitygmlFormat.GmlZst) })
        {
            var path = Fixture($"fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.{extension}");
            Assert.Equal(1u, ReadPath(path).CityObjectsLen());
            Assert.Equal(1u, ReadData(File.ReadAllBytes(path), format).CityObjectsLen());
        }
    }

    [Fact]
    public void ReaderDefaultRebuildsObjectBounds()
    {
        var cityModel = Read(FzkLod2);
        var walls = Items(cityModel.IterFeatures().Next).Select(WallSurface.TryFrom).Where(w => w != null).ToList();
        Assert.Equal(Enumerable.Repeat(true, 4), walls.Select(wall => wall!.BoundedBy() != null));
    }

    [Fact]
    public void ReaderFinishOnce()
    {
        var reader = GmlReader.FromPath(Utf8(Fixture(FzkLod1)));
        reader.WithRebuildObjectBounds(false);
        Assert.Equal(1u, reader.Finish().CityObjectsLen());
        AssertError(() => reader.Finish(), ErrorKind.InvalidArgument, "already finished");
    }

    [Fact]
    public void ReaderMissingFile()
    {
        AssertError(() => GmlReader.FromPath(Utf8(Fixture("does-not-exist.gml"))), ErrorKind.Io, "No such file");
    }

    [Fact]
    public void ReaderUnsupportedExtension()
    {
        AssertError(() => GmlReader.FromPath(Utf8(Fixture("README.md"))), ErrorKind.InvalidArgument, "md");
    }

    [Fact]
    public void ReaderNonUtf8Path()
    {
        AssertError(() => GmlReader.FromPath(new byte[] { 0xff, (byte)'.', (byte)'g', (byte)'m', (byte)'l' }),
            ErrorKind.InvalidArgument, "`path`");
    }

    [Fact]
    public void ReaderInvalidContent()
    {
        var reader = GmlReader.FromPath(Utf8(Fixture("invalid/unclosed-tag.gml")));
        AssertError(() => reader.Finish(), ErrorKind.Parse, "tag not closed");
    }
}
