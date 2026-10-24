using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.</summary>
public class FzkHausCitygml30Tests
{
    private const string Dataset = "fzk-haus-citygml-3.0";
    private const string ConstructionId = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86";
    private const string TestBuildingId = "KIT-Test-Building-01";
    private const string WindowId = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz";

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    /// <summary>The number of features per feature type, over `IterFeatures`.</summary>
    private static Dictionary<FeatureType, int> FeatureTypeCounts(CityModel cityModel) =>
        FeatureTypes(cityModel).GroupBy(t => t).ToDictionary(g => g.Key, g => g.Count());

    private static List<Storey> Storeys(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(Storey.TryFrom).OfType<Storey>().ToList();

    private static void AssertCityModel(CityModel cityModel, (double, double, double) lower, (double, double, double) upper)
    {
        Assert.Equal(1u, (uint)cityModel.CityObjectsLen());
        var envelope = cityModel.BoundedBy()!.Envelope()!;
        foreach (var (position, expected) in new[] { (envelope.LowerCorner(), lower), (envelope.UpperCorner(), upper) })
        {
            AssertClose(expected.Item1, position.X());
            AssertClose(expected.Item2, position.Y());
            AssertClose(expected.Item3, position.Z());
        }
    }

    /// <summary>The one height and occupancy of the storey examples' buildings.</summary>
    private static void AssertHeightAndOccupancy(Building building)
    {
        var height = Assert.Single(Items(building.Heights().Next));
        Assert.Equal("highestRoofEdge", Str(height.HighReference().Value()));
        Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
        Assert.Equal(HeightStatusValue.Measured, height.Status());
        AssertClose(6.52, height.Length().Value());
        Assert.Equal("urn:adv:uom:m", Str(height.Length().Uom()));
        Assert.Equal(2L, Assert.Single(Items(building.Occupancies().Next)).NumberOfOccupants());
    }

    /// <summary>The storeys' first names and classes.</summary>
    private static void AssertStoreys(CityModel cityModel, string?[] classes)
    {
        var storeys = Storeys(cityModel);
        Assert.Equal(["Ground Floor", "Second Floor"], storeys.Select(s => FirstName(s.Names())));
        Assert.Equal(classes, storeys.Select(s => s.Class() is { } c ? Str(c.Value()) : null));
    }

    /// <summary>A storey's boundaries as (feature type, first name, LoD2 multi surface); all inline wall, roof or
    /// ground surfaces.</summary>
    private static List<(FeatureType Type, string Name, MultiSurfaceProperty? MultiSurface)> BoundarySurfaces(Storey storey) =>
        Items(storey.Boundaries().Next).Select(property =>
        {
            Assert.Null(property.Href());
            var feature = AbstractFeatureKindRef.FromSpaceBoundary(property.Object()!);
            if (WallSurface.TryFrom(feature) is { } wall)
            {
                return (feature.FeatureType(), FirstName(wall.Names()), wall.Lod2MultiSurface());
            }
            if (RoofSurface.TryFrom(feature) is { } roof)
            {
                return (feature.FeatureType(), FirstName(roof.Names()), roof.Lod2MultiSurface());
            }
            var ground = GroundSurface.TryFrom(feature);
            Assert.NotNull(ground);
            return (feature.FeatureType(), FirstName(ground.Names()), ground.Lod2MultiSurface());
        }).ToList();

    /// <summary>Writes the city model and reads it back: the same feature types in the same order and the building's
    /// id.</summary>
    private static void AssertRoundTrip(CityModel cityModel, string buildingId)
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(cityModel);
        var written = GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
        Assert.Equal(FeatureTypes(cityModel), FeatureTypes(written));
        Assert.Equal(buildingId, Str(FirstBuilding(written).FeatureId().AsStr()));
    }

    public class Construction
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml");

        [Fact]
        public void ConstructionCityModel()
        {
            AssertCityModel(Model, (458899.5, 5438784.5, 113.5), (458912.5, 5438795.5, 120.017691));
            Assert.Equal(
                [
                    FeatureType.CityModel,
                    FeatureType.Building,
                    FeatureType.Storey,
                    .. Enumerable.Repeat(FeatureType.BuildingConstructiveElement, 5),
                    FeatureType.Storey,
                    .. Enumerable.Repeat(FeatureType.BuildingConstructiveElement, 6),
                    FeatureType.Appearance,
                    .. Enumerable.Repeat(FeatureType.ParameterizedTexture, 5),
                    .. Enumerable.Repeat(FeatureType.X3dMaterial, 5),
                ],
                FeatureTypes(Model));
            Assert.Equal(14, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void ConstructionBuilding()
        {
            var building = FirstBuilding(Model);
            Assert.Equal(ConstructionId, Str(building.FeatureId().AsStr()));
            Assert.Equal(["KIT FZK-Haus"], Items(building.Names().Next).Select(n => Str(n.Value())));
            Assert.Null(building.Class());
            Assert.Equal(["31001_1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
            Assert.Empty(Items(building.Usages().Next));
            Assert.Equal("3100", Str(building.RoofType()!.Value()));
            Assert.Null(building.StoreysAboveGround());
            Assert.Null(building.StoreysBelowGround());
            AssertHeightAndOccupancy(building);
            Assert.Empty(Items(building.Boundaries().Next));
            Assert.Empty(Items(building.GenericAttributes().Next));
            Assert.Null(building.Lod2Solid());
            Assert.Null(building.Lod2MultiSurface());
        }

        [Fact]
        public void ConstructionStoreys()
        {
            var subdivisions = Items(FirstBuilding(Model).BuildingSubdivisions().Next).ToList();
            Assert.Equal(2, subdivisions.Count);
            Assert.All(subdivisions, s =>
            {
                Assert.Null(s.Href());
                Assert.Equal(FeatureType.Storey, s.Object()!.FeatureType());
            });
            AssertStoreys(Model, ["Entrance Floor", "non Entrance Floor"]);
            Assert.All(Storeys(Model), storey =>
            {
                Assert.Empty(Items(storey.Functions().Next));
                Assert.Empty(Items(storey.Usages().Next));
                Assert.Empty(Items(storey.Boundaries().Next));
                Assert.Null(storey.Lod2Solid());
            });
        }

        [Fact]
        public void ConstructionRoundTrip() => AssertRoundTrip(Model, ConstructionId);
    }

    public class Interior
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml");

        [Fact]
        public void InteriorCityModel()
        {
            AssertCityModel(Model, (458900.0, 5438785.0, 113.5), (458912.0, 5438795.0, 120.017691));
            Assert.Equal(77, FeatureTypes(Model).Count);
            Assert.Equal(
                new Dictionary<FeatureType, int>
                {
                    [FeatureType.CityModel] = 1,
                    [FeatureType.Building] = 1,
                    [FeatureType.Storey] = 2,
                    [FeatureType.GroundSurface] = 1,
                    [FeatureType.WallSurface] = 8,
                    [FeatureType.RoofSurface] = 2,
                    [FeatureType.BuildingRoom] = 7,
                    [FeatureType.InteriorWallSurface] = 27,
                    [FeatureType.CeilingSurface] = 8,
                    [FeatureType.FloorSurface] = 7,
                    [FeatureType.ClosureSurface] = 6,
                    [FeatureType.Appearance] = 1,
                    [FeatureType.ParameterizedTexture] = 5,
                    [FeatureType.X3dMaterial] = 1,
                },
                FeatureTypeCounts(Model));
            Assert.Equal(69, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void InteriorBuilding()
        {
            var building = FirstBuilding(Model);
            Assert.Equal(TestBuildingId, Str(building.FeatureId().AsStr()));
            Assert.Equal(["KIT Test Building FZK-Haus for CityGML 3.0"], Items(building.Names().Next).Select(n => Str(n.Value())));
            Assert.Null(building.Class());
            Assert.Null(building.RoofType());
            Assert.Empty(Items(building.Functions().Next));
            Assert.Empty(Items(building.Usages().Next));
            AssertHeightAndOccupancy(building);
            var attribute = Assert.Single(Items(building.GenericAttributes().Next));
            Assert.Equal(("@cityeditor:layer", "LoD2-Ausgeblendet"), (Str(attribute.Name()), Str(attribute.AsString()!.Value())));
            Assert.Empty(Items(building.Boundaries().Next));
        }

        [Fact]
        public void InteriorSolidUnresolved()
        {
            var property = FirstBuilding(Model).Lod2Solid()!;
            Assert.Null(property.Href());
            var solid = property.Object()!;
            var members = Items(solid.Exterior()!.Members().Next).ToList();
            Assert.Equal(11, members.Count);
            Assert.All(members, m => Assert.Null(m.Object()));
            Assert.Throws<ErrorException>(() => solid.Volume3d());
        }

        [Fact]
        public void InteriorStoreyBoundaries()
        {
            (FeatureType, string, double)[][] expected =
            [
                [
                    (FeatureType.GroundSurface, "Ground", 120.0),
                    (FeatureType.WallSurface, "Ground Floor / Wall East", 29.0),
                    (FeatureType.WallSurface, "Ground Floor / Wall South", 34.80000000447035),
                    (FeatureType.WallSurface, "Ground Floor / Wall West", 29.0),
                    (FeatureType.WallSurface, "Ground Floor / Wall North", 34.80000000447035),
                ],
                [
                    (FeatureType.RoofSurface, "Second Floor / Roof South", 69.28203022609509),
                    (FeatureType.RoofSurface, "Second Floor / Roof North", 69.28203022609509),
                    (FeatureType.WallSurface, "Second Floor / Wall South", 8.771279998123646),
                    (FeatureType.WallSurface, "Second Floor / Wall West", 21.743155002593994),
                    (FeatureType.WallSurface, "Second Floor / Wall East", 21.743155002593994),
                    (FeatureType.WallSurface, "Second Floor / Wall North", 8.771279998123646),
                ],
            ];
            var storeys = Storeys(Model);
            Assert.Equal(expected.Length, storeys.Count);
            foreach (var (storey, surfaces) in storeys.Zip(expected))
            {
                var actual = BoundarySurfaces(storey);
                Assert.Equal(surfaces.Select(s => (s.Item1, s.Item2)), actual.Select(a => (a.Type, a.Name)));
                foreach (var (surface, want) in actual.Zip(surfaces))
                {
                    AssertClose(want.Item3, surface.MultiSurface!.Object()!.Area3d());
                }
            }
            AssertStoreys(Model, [null, null]);
        }

        [Fact]
        public void InteriorRoundTrip() => AssertRoundTrip(Model, TestBuildingId);
    }

    public class Window
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model =
            ReadFixture(Dataset, "04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml");

        [Fact]
        public void WindowCityModel()
        {
            AssertCityModel(Model, (458899.5, 5438784.5, 113.5), (458912.5, 5438795.5, 120.017691));
            Assert.Equal(54, FeatureTypes(Model).Count);
            Assert.Equal(
                new Dictionary<FeatureType, int>
                {
                    [FeatureType.CityModel] = 1,
                    [FeatureType.Building] = 1,
                    [FeatureType.Storey] = 2,
                    [FeatureType.BuildingConstructiveElement] = 18,
                    [FeatureType.Door] = 5,
                    [FeatureType.Window] = 11,
                    [FeatureType.Appearance] = 2,
                    [FeatureType.ParameterizedTexture] = 5,
                    [FeatureType.X3dMaterial] = 9,
                },
                FeatureTypeCounts(Model));
            Assert.Equal(37, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void WindowBuilding()
        {
            var building = FirstBuilding(Model);
            Assert.Equal(WindowId, Str(building.FeatureId().AsStr()));
            Assert.Equal(["KIT FZK-Haus"], Items(building.Names().Next).Select(n => Str(n.Value())));
            Assert.Equal(["31001_1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal("3100", Str(building.RoofType()!.Value()));
            Assert.Empty(Items(building.Boundaries().Next));
            AssertStoreys(Model, ["Entrance Floor", "non Entrance Floor"]);
        }

        [Fact]
        public void WindowRoundTrip() => AssertRoundTrip(Model, WindowId);
    }

    public class PointCloud
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml");

        [Fact]
        public void PointCloudCityModel()
        {
            AssertCityModel(Model, (458900.0, 5438785.0, 113.5), (458912.0, 5438795.0, 120.017691));
            Assert.Equal(
                [
                    FeatureType.CityModel,
                    FeatureType.Building,
                    FeatureType.Storey,
                    FeatureType.GroundSurface,
                    .. Enumerable.Repeat(FeatureType.WallSurface, 4),
                    FeatureType.Storey,
                    FeatureType.RoofSurface,
                    FeatureType.RoofSurface,
                    .. Enumerable.Repeat(FeatureType.WallSurface, 4),
                ],
                FeatureTypes(Model));
        }

        [Fact]
        public void PointCloudStoreyBoundaries()
        {
            var building = FirstBuilding(Model);
            Assert.Equal(TestBuildingId, Str(building.FeatureId().AsStr()));
            Assert.Empty(Items(building.Boundaries().Next));
            (FeatureType, string)[][] expected =
            [
                [
                    (FeatureType.GroundSurface, " Ground Floor / GroundSurface"),
                    (FeatureType.WallSurface, "Ground Floor / Wall East"),
                    (FeatureType.WallSurface, "Ground Floor / Wall South"),
                    (FeatureType.WallSurface, "Ground Floor / Wall West"),
                    (FeatureType.WallSurface, "Ground Floor / Wall North"),
                ],
                [
                    (FeatureType.RoofSurface, "Second Floor / Roof North"),
                    (FeatureType.RoofSurface, "Second Floor / Roof South"),
                    (FeatureType.WallSurface, "Second Floor / Wall South"),
                    (FeatureType.WallSurface, "Second Floor / Wall West"),
                    (FeatureType.WallSurface, "Second Floor / Wall East"),
                    (FeatureType.WallSurface, "Second Floor / Wall North"),
                ],
            ];
            var storeys = Storeys(Model);
            Assert.Equal(expected.Length, storeys.Count);
            foreach (var (storey, surfaces) in storeys.Zip(expected))
            {
                var actual = BoundarySurfaces(storey);
                Assert.Equal(surfaces, actual.Select(a => (a.Type, a.Name)));
                Assert.All(actual, a => Assert.Null(a.MultiSurface));
            }
        }

        [Fact]
        public void PointCloudRoundTrip() => AssertRoundTrip(Model, TestBuildingId);
    }
}
