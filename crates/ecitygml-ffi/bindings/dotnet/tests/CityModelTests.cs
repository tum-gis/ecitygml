using System.Text;
using Xunit;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests;

public class CityModelTests
{
    private const string FzkLod1 = "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string FzkLod2 = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

    [Fact]
    public void ReadsCityObjects()
    {
        Assert.Equal(1u, (uint)Read(FzkLod1).CityObjectsLen());
    }

    [Fact]
    public void MissingFileThrowsIoError()
    {
        var exception = Assert.Throws<ErrorException>(() => Read("does-not-exist.gml"));
        Assert.Equal(ErrorKind.Io, exception.Inner.Kind());
        Assert.Contains("No such file", exception.Inner.Message());
    }

    [Fact]
    public void UnsupportedExtensionThrowsInvalidArgument()
    {
        var exception = Assert.Throws<ErrorException>(() => Read("README.md"));
        Assert.Equal(ErrorKind.InvalidArgument, exception.Inner.Kind());
    }

    [Fact]
    public void GmlReaderFinishesOnce()
    {
        var reader = GmlReader.FromPath(Encoding.UTF8.GetBytes(Fixture(FzkLod1)));
        reader.WithRebuildObjectBounds(false);
        reader.Finish();
        var exception = Assert.Throws<ErrorException>(() => reader.Finish());
        Assert.Equal(ErrorKind.InvalidArgument, exception.Inner.Kind());
    }

    [Fact]
    public void BoundedByEnvelope()
    {
        var envelope = Read(FzkLod1).BoundedBy()?.Envelope();
        Assert.NotNull(envelope);
        Assert.Equal(12.0, envelope.SizeX());
        Assert.Equal(10.0, envelope.SizeY());
        Assert.Equal(6.517669, envelope.SizeZ(), 1e-9);
        Assert.Equal(457842.0, envelope.LowerCorner().X());
        Assert.True(envelope.Contains(envelope.UpperCorner()));
    }

    [Fact]
    public void ApplyTranslationAndScale()
    {
        var cityModel = Read(FzkLod1);
        Envelope Envelope() => cityModel.BoundedBy()!.Envelope()!;
        var lower = Envelope().LowerCorner();
        var (x, y, z) = (lower.X(), lower.Y(), lower.Z());

        cityModel.ApplyTranslation(new Vector3 { X = -100.0, Y = 200.0, Z = 10.0 });
        var moved = Envelope().LowerCorner();
        Assert.Equal(x - 100.0, moved.X(), 1e-6);
        Assert.Equal(y + 200.0, moved.Y(), 1e-6);
        Assert.Equal(z + 10.0, moved.Z(), 1e-6);

        cityModel.ApplyScale(new Scale3 { X = 2.0, Y = 3.0, Z = 0.5 });
        Assert.Equal(24.0, Envelope().SizeX(), 1e-6);
        Assert.Equal(30.0, Envelope().SizeY(), 1e-6);
        Assert.Equal(6.517669 / 2, Envelope().SizeZ(), 1e-6);
    }

    [Fact]
    public void IterFeaturesYieldsTheCityModelFirst()
    {
        var cityModel = Read(FzkLod2);
        var types = Items(cityModel.IterFeatures().Next).Select(feature => feature.FeatureType()).ToList();
        Assert.Equal(FeatureType.CityModel, types[0]);
        Assert.Equal(1, types.Count(type => type == FeatureType.Building));
        Assert.Equal(4, types.Count(type => type == FeatureType.WallSurface));
    }

    [Fact]
    public void IterCityObjectsAtAllDepths()
    {
        var cityModel = Read(FzkLod2);
        Assert.Equal(8, Items(cityModel.IterCityObjects().Next).Count());
    }

    [Fact]
    public void TryFromConvertsOnlyMatchingFeatures()
    {
        var cityModel = Read(FzkLod1);
        var features = Items(cityModel.IterFeatures().Next).ToList();
        Assert.Single(features, feature => Building.TryFrom(feature) != null);
        Assert.All(features, feature => Assert.Null(TrafficSpace.TryFrom(feature)));
    }
}
