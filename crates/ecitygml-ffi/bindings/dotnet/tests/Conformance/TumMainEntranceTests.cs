using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.</summary>
public class TumMainEntranceTests
{
    // The city model outlives every test: the features borrow from it.
    private static readonly CityModel Model = ReadFixture("tum-main-entrance", "TUM-Main-Entrance.gml");

    private static readonly FeatureType[] BoundaryTypes =
    [
        .. Enumerable.Repeat(FeatureType.WallSurface, 10),
        FeatureType.GroundSurface,
        .. Enumerable.Repeat(FeatureType.WallSurface, 3),
        FeatureType.RoofSurface,
        FeatureType.RoofSurface,
        FeatureType.WallSurface,
    ];

    private static void AssertPointClose(DirectPosition position, double x, double y, double z)
    {
        AssertClose(x, position.X());
        AssertClose(y, position.Y());
        AssertClose(z, position.Z());
    }

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    /// <summary>The area of an inline LoD2 multi surface.</summary>
    private static double Lod2Area(MultiSurfaceProperty? property)
    {
        Assert.NotNull(property);
        Assert.Null(property.Href());
        return property.Object()!.Area3d();
    }

    [Fact]
    public void EntranceCityModel()
    {
        Assert.Equal(1u, (uint)Model.CityObjectsLen());
        var envelope = Model.BoundedBy()!.Envelope()!;
        AssertPointClose(envelope.LowerCorner(), 689975.68, 5335962.63, 503.0);
        AssertPointClose(envelope.UpperCorner(), 692025.893, 5338012.713, 581.62);
        Assert.Equal([FeatureType.CityModel, FeatureType.Building, .. BoundaryTypes], FeatureTypes(Model));
        Assert.Equal(18, Items(Model.IterCityObjects().Next).Count());
    }

    [Fact]
    public void EntranceBuildingAttributes()
    {
        var building = FirstBuilding(Model);
        Assert.Equal("DEBY_LOD2_4959457", Str(building.FeatureId().AsStr()));
        Assert.Empty(Items(building.Names().Next));
        Assert.Null(building.Class());
        Assert.Equal(["31001_3020"], Items(building.Functions().Next).Select(f => Str(f.Value())));
        Assert.Empty(Items(building.Usages().Next));
        Assert.Equal("1000", Str(building.RoofType()!.Value()));
        Assert.Equal(4L, building.StoreysAboveGround());
        Assert.Null(building.StoreysBelowGround());

        var height = Assert.Single(Items(building.Heights().Next));
        Assert.Equal("topOfConstruction", Str(height.HighReference().Value()));
        Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
        Assert.Equal(HeightStatusValue.Measured, height.Status());
        AssertClose(19.408, height.Length().Value());
        Assert.Equal("urn:adv:uom:m", Str(height.Length().Uom()));

        var created = building.CreationDate()!;
        Assert.Equal((2025, 1u, 2u), (created.Year(), created.Month(), created.Day()));
        Assert.Equal((0u, 0u), (created.Hour(), created.Minute()));
        Assert.Equal(3600, created.OffsetSeconds());
        Assert.Null(building.BoundedBy());
        Assert.Empty(Items(building.Occupancies().Next));
        Assert.Empty(Items(building.BuildingSubdivisions().Next));
    }

    [Fact]
    public void EntranceExternalReference()
    {
        var reference = Assert.Single(Items(FirstBuilding(Model).ExternalReferences().Next));
        Assert.Equal("DEBYvAAAAABTMIyA", Str(reference.TargetResource()));
    }

    [Fact]
    public void EntranceGenericAttributes()
    {
        var attributes = Items(FirstBuilding(Model).GenericAttributes().Next)
            .Select(a => (Str(a.Name()), Str(a.AsString()!.Value())));
        Assert.Equal(
            [
                ("DatenquelleBodenhoehe", "1100"),
                ("DatenquelleDachhoehe", "1000"),
                ("DatenquelleLage", "1000"),
                ("Gemeindeschluessel", "09162000"),
                ("HoeheDach", "534.450"),
                ("HoeheGrund", "515.042"),
                ("Methode", "2000"),
                ("NiedrigsteTraufeDesGebaeudes", "527.312"),
                ("Grundrissaktualitaet", "2025-02-17"),
                ("Geometrietyp2DReferenz", "3000"),
            ],
            attributes);
    }

    [Fact]
    public void EntranceBoundaries()
    {
        var building = FirstBuilding(Model);
        Assert.All(Items(building.Boundaries().Next), p => Assert.Null(p.Href()));
        var features = Boundaries(building);
        Assert.Equal(BoundaryTypes, features.Select(f => f.FeatureType()));

        var walls = features.Select(WallSurface.TryFrom).OfType<WallSurface>().ToList();
        Assert.Equal("DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2", Str(walls[0].FeatureId().AsStr()));
        Assert.Empty(Items(walls[0].Names().Next));
        AssertClose(3783.3908922901974, walls.Sum(w => Lod2Area(w.Lod2MultiSurface())));

        var roofs = features.Select(RoofSurface.TryFrom).OfType<RoofSurface>().Select(r => Lod2Area(r.Lod2MultiSurface())).ToList();
        Assert.Equal(2, roofs.Count);
        AssertClose(250.233154296875, roofs[0]);
        AssertClose(979.3291015625, roofs[1]);
        AssertClose(1229.562255859375, roofs.Sum());

        var grounds = features.Select(GroundSurface.TryFrom).OfType<GroundSurface>().Select(g => Lod2Area(g.Lod2MultiSurface())).ToList();
        AssertClose(1229.562255859375, Assert.Single(grounds));
    }

    [Fact]
    public void EntranceWallTriangulation()
    {
        var wall = Items(Model.IterFeatures().Next).Select(WallSurface.TryFrom).First(w => w != null)!;
        var multiSurface = wall.Lod2MultiSurface()!.Object()!;
        Assert.Single(Items(multiSurface.SurfaceMember().Next));
        AssertClose(546.6949745937537, multiSurface.Area3d());
        var triangulation = multiSurface.Triangulate();
        Assert.Equal(4, Items(triangulation.Surface().Triangles().Next).Count());
        Assert.False(triangulation.HasSkipped());
        AssertClose(546.6949742237184, triangulation.Surface().Area3d());
    }

    [Fact]
    public void EntranceSolidUnresolved()
    {
        var property = FirstBuilding(Model).Lod2Solid()!;
        Assert.Null(property.Href());
        var solid = property.Object()!;
        var members = Items(solid.Exterior()!.Members().Next).ToList();
        Assert.Equal(17, members.Count);
        Assert.All(members, m => Assert.Null(m.Object()));
        Assert.Throws<ErrorException>(() => solid.Volume3d());
    }

    [Fact]
    public void EntranceRoundTrip()
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(Model);
        var written = GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
        Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
        Assert.Equal("DEBY_LOD2_4959457", Str(FirstBuilding(written).FeatureId().AsStr()));
        static List<string> BoundaryIds(CityModel cityModel) =>
            Items(FirstBuilding(cityModel).Boundaries().Next).Select(p => Str(p.Object()!.FeatureId().AsStr())).ToList();
        Assert.Equal(BoundaryIds(Model), BoundaryIds(written));
    }
}
