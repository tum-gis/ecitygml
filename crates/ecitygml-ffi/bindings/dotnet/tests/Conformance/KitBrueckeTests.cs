using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.</summary>
public class KitBrueckeTests
{
    private const string BridgeId = "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7";

    // The city model outlives every test: the features borrow from it.
    private static readonly CityModel Model = ReadFixture("kit-bruecke", "Modellbahnbruecke-LoD2-V03__v3.gml");

    private static Bridge FirstBridge(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(Bridge.TryFrom).First(b => b != null)!;

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    private static void AssertEnvelope(Envelope envelope, (double, double, double) lower, (double, double, double) upper)
    {
        foreach (var (position, expected) in new[] { (envelope.LowerCorner(), lower), (envelope.UpperCorner(), upper) })
        {
            AssertClose(expected.Item1, position.X());
            AssertClose(expected.Item2, position.Y());
            AssertClose(expected.Item3, position.Z());
        }
    }

    [Fact]
    public void BridgeCityModel()
    {
        Assert.Equal(1u, (uint)Model.CityObjectsLen());
        AssertEnvelope(Model.BoundedBy()!.Envelope()!, (457644.585, 5439126.455, 109.0), (457708.084, 5439157.169, 124.3));
        Assert.Equal(
            [
                FeatureType.CityModel,
                FeatureType.Bridge,
                FeatureType.Appearance,
                .. Enumerable.Repeat(FeatureType.ParameterizedTexture, 3),
                .. Enumerable.Repeat(FeatureType.BridgeInstallation, 2),
                .. Enumerable.Repeat(FeatureType.BridgeConstructiveElement, 11),
            ],
            FeatureTypes(Model));
        Assert.Equal(14, Items(Model.IterCityObjects().Next).Count());
    }

    [Fact]
    public void BridgeAttributes()
    {
        var bridge = FirstBridge(Model);
        Assert.Equal(BridgeId, Str(bridge.FeatureId().AsStr()));
        Assert.Empty(Items(bridge.Names().Next));
        Assert.Null(bridge.Class());
        Assert.Empty(Items(bridge.Functions().Next));
        Assert.Empty(Items(bridge.Usages().Next));
        Assert.Empty(Items(bridge.BridgeParts().Next));
        Assert.Empty(Items(bridge.Boundaries().Next));
        Assert.Null(bridge.DateOfConstruction());
        Assert.Null(bridge.CreationDate());
        Assert.Empty(Items(bridge.Heights().Next));
        Assert.Empty(Items(bridge.Occupancies().Next));
        Assert.Empty(Items(bridge.GenericAttributes().Next));
        Assert.Empty(Items(bridge.ExternalReferences().Next));
    }

    [Fact]
    public void BridgeGeometry()
    {
        var bridge = FirstBridge(Model);
        AssertEnvelope(bridge.BoundedBy()!.Envelope()!, (457645.136, 5439126.692, 115.3), (457707.533, 5439156.931, 116.2));
        var property = bridge.Lod2MultiSurface()!;
        Assert.Null(property.Href());
        var multiSurface = property.Object()!;
        Assert.Equal(18, Items(multiSurface.SurfaceMember().Next).Count());
        AssertClose(795.4201811265907, multiSurface.Area3d());
        var triangulation = multiSurface.Triangulate();
        Assert.Equal(60, Items(triangulation.Surface().Triangles().Next).Count());
        Assert.False(triangulation.HasSkipped());
        Assert.Null(bridge.Lod1Solid());
        Assert.Null(bridge.Lod2Solid());
        Assert.Null(bridge.Lod3MultiSurface());
    }

    [Fact]
    public void BridgeRoundTrip()
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(Model);
        var written = GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
        Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
        Assert.Equal(BridgeId, Str(FirstBridge(written).FeatureId().AsStr()));
    }
}
