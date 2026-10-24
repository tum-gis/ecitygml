using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/railway-scene.md.</summary>
public class RailwaySceneTests
{
    private const string TemplateA = "#Mult_SO043561_5693_194007";
    private const string TemplateB = "#Mult_SO045475_3243_790864";
    private static readonly HashSet<string> InlineTemplates = ["Forest tree 3", "Tree1", "Forest tree 1"];
    private static readonly HashSet<string> TemplateATrees = ["Forest tree 4", "Forest tree 9", "Forest tree 5"];

    private const FeatureType Wall = FeatureType.WallSurface;
    private const FeatureType Roof = FeatureType.RoofSurface;
    private const FeatureType Ground = FeatureType.GroundSurface;
    private const FeatureType Closure = FeatureType.ClosureSurface;

    // The city model outlives every test: the features borrow from it.
    private static readonly CityModel Model = ReadFixture("railway-scene", "Railway_Scene_LoD3__v3-thinned.gml");

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    /// <summary>All features a class accepts, in document order.</summary>
    private static List<T> AllOf<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Items(cityModel.IterFeatures().Next).Select(tryFrom).OfType<T>().ToList();

    /// <summary>A tree's inline LoD3 implicit geometry.</summary>
    private static ImplicitGeometry Geometry(SolitaryVegetationObject tree)
    {
        var property = tree.Lod3ImplicitRepresentation()!;
        Assert.Null(property.Href());
        return property.Object()!;
    }

    private static string? TemplateHref(SolitaryVegetationObject tree) => Geometry(tree).RelativeGeometry()?.Href()?.ToString();

    private static double Matrix(ImplicitGeometry geometry, int row, int column) =>
        geometry.TransformationMatrix().Get((nuint)row, (nuint)column);

    [Fact]
    public void RailwayCityModel()
    {
        Assert.Equal(52u, (uint)Model.CityObjectsLen());
        Assert.Null(Model.BoundedBy());
        var types = FeatureTypes(Model);
        Assert.Equal(232, types.Count);
        Assert.Equal(FeatureType.CityModel, types[0]);
        Assert.Equal(
            new Dictionary<FeatureType, int>
            {
                [FeatureType.CityModel] = 1,
                [FeatureType.SolitaryVegetationObject] = 15,
                [FeatureType.Tunnel] = 4,
                [FeatureType.TunnelInstallation] = 8,
                [FeatureType.Railway] = 10,
                [FeatureType.Bridge] = 4,
                [FeatureType.BridgeConstructiveElement] = 3,
                [FeatureType.BridgeInstallation] = 2,
                [FeatureType.Building] = 3,
                [FeatureType.BuildingInstallation] = 56,
                [FeatureType.CityFurniture] = 11,
                [FeatureType.CityObjectGroup] = 1,
                [FeatureType.GenericOccupiedSpace] = 2,
                [FeatureType.WaterBody] = 1,
                [FeatureType.WaterSurface] = 1,
                [FeatureType.WaterGroundSurface] = 1,
                [FeatureType.ReliefFeature] = 1,
                [FeatureType.TinRelief] = 1,
                [Wall] = 33,
                [Roof] = 12,
                [Ground] = 7,
                [Closure] = 8,
                [FeatureType.DoorSurface] = 9,
                [FeatureType.WindowSurface] = 34,
                [FeatureType.OuterCeilingSurface] = 3,
                [FeatureType.OuterFloorSurface] = 1,
            },
            types.GroupBy(t => t).ToDictionary(g => g.Key, g => g.Count()));
        Assert.Equal(231, Items(Model.IterCityObjects().Next).Count());
    }

    [Fact]
    public void RailwayTunnels()
    {
        (string, string, FeatureType[])[] expected =
        [
            ("GMLID_BUI142242_863_347", "Tunnel KIT/KHH-3", [Ground, Wall, Roof, Wall, Closure, Closure]),
            ("GMLID_BUI336993_213_9312", "Tunnel KIT/KHH-2", [Wall, Roof, Wall, Closure, Closure, Ground]),
            ("GMLID_BUI289877_1911_4122", "Tunnel KIT/KHH-4", [Wall, Ground, Closure, Wall, Roof, Closure]),
            ("GMLID_BUI180021_673_14143", "Tunnel KIT/KHH-1", [Ground, Wall, Roof, Closure, Closure, Wall]),
        ];
        var tunnels = AllOf(Model, Tunnel.TryFrom);
        Assert.Equal(expected.Length, tunnels.Count);
        foreach (var (tunnel, (id, name, boundaries)) in tunnels.Zip(expected))
        {
            Assert.Equal(id, Str(tunnel.FeatureId().AsStr()));
            Assert.Equal(name, FirstName(tunnel.Names()));
            var properties = Items(tunnel.Boundaries().Next).ToList();
            Assert.All(properties, p => Assert.Null(p.Href()));
            Assert.Equal(boundaries, properties.Select(p => p.Object()!.FeatureType()));
            Assert.Null(tunnel.Class());
            Assert.Empty(Items(tunnel.Functions().Next));
            Assert.Empty(Items(tunnel.Usages().Next));
            Assert.Empty(Items(tunnel.TunnelParts().Next));
            var created = tunnel.CreationDate()!;
            Assert.Equal((2015, 3u, 6u), (created.Year(), created.Month(), created.Day()));
            Assert.Equal((0u, 0u), (created.Hour(), created.Minute()));
            Assert.Equal(3600, created.OffsetSeconds());
            Assert.Equal(RelativeToTerrain.EntirelyAboveTerrain, tunnel.RelativeToTerrain());
        }
    }

    [Fact]
    public void RailwayTrees()
    {
        (string, string, string?, string, string[])[] expected =
        [
            ("GMLID_SO0158953_776_12462", "Forest tree 3", "1070", "1800", []),
            ("GMLID_SO092422_3593_9527", "Tree1", null, "9999", ["LOD3"]),
            ("GMLID_SO0200811_525_4986", "Forest tree 1", "1060", "1640", []),
            ("GMLID_SO0321978_1466_7441", "Forest tree 4", "1070", "1800", []),
            ("GMLID_SO0260143_1214_1315", "Forest tree 11", "1060", "1640", []),
            ("GMLID_SO0400934_2926_3381", "Forest tree 12", "1060", "1640", []),
            ("GMLID_SO0124800_3522_13577", "Forest tree 13", "1060", "1640", []),
            ("GMLID_SO0443764_1492_9667", "Forest tree 14", "1060", "1640", []),
            ("GMLID_SO015374_872_14131", "Forest tree 2", "1060", "1640", []),
            ("GMLID_SO081792_2341_11961", "Forest tree 10", "1060", "1640", []),
            ("GMLID_SO0283142_1335_8999", "Forest tree 7", "1060", "1640", []),
            ("GMLID_SO0107241_3793_12555", "Forest tree 9", "1070", "1800", []),
            ("GMLID_SO0286258_965_2893", "Forest tree 5", "1070", "1800", []),
            ("GMLID_SO0410128_214_10515", "Forest tree 6", "1060", "1640", []),
            ("GMLID_SO086970_1053_8814", "Forest tree 8", "1060", "1640", []),
        ];
        var trees = AllOf(Model, SolitaryVegetationObject.TryFrom);
        Assert.Equal(expected.Length, trees.Count);
        foreach (var (tree, (id, name, @class, species, functions)) in trees.Zip(expected))
        {
            Assert.Equal(id, Str(tree.FeatureId().AsStr()));
            Assert.Equal(name, FirstName(tree.Names()));
            Assert.Equal(@class, tree.Class() is { } c ? Str(c.Value()) : null);
            Assert.Equal(species, Str(tree.Species()!.Value()));
            Assert.Equal(functions, Items(tree.Functions().Next).Select(f => Str(f.Value())));
            Assert.Empty(Items(tree.Usages().Next));
            Assert.Null(tree.Lod1ImplicitRepresentation());
            Assert.Null(tree.Lod2ImplicitRepresentation());
        }
    }

    [Fact]
    public void RailwayTreeTemplates()
    {
        foreach (var tree in AllOf(Model, SolitaryVegetationObject.TryFrom))
        {
            var geometry = Geometry(tree);
            Assert.Null(geometry.MimeType());
            foreach (var (i, value) in new[] { (0, 30.0), (1, 30.0), (2, 30.0), (3, 1.0) })
            {
                AssertClose(value, Matrix(geometry, i, i));
            }
            var name = FirstName(tree.Names());
            var property = geometry.RelativeGeometry()!;
            if (InlineTemplates.Contains(name))
            {
                Assert.Null(property.Href());
                var multiSurface = MultiSurface.TryFrom(property.Object()!);
                Assert.NotNull(multiSurface);
                Assert.Single(Items(multiSurface.SurfaceMember().Next));
            }
            else
            {
                Assert.Null(property.Object());
                Assert.Equal(TemplateATrees.Contains(name) ? TemplateA : TemplateB, TemplateHref(tree));
            }
        }
    }

    [Fact]
    public void RailwayTreePlacement()
    {
        foreach (var tree in AllOf(Model, SolitaryVegetationObject.TryFrom))
        {
            var geometry = Geometry(tree);
            var pos = geometry.ReferencePoint().Object()!.Pos();
            var name = FirstName(tree.Names());
            double[] reference = name == "Tree1"
                ? [-568.8000793496976, 457.60044759869743, 105.00139681350242]
                : [-600.0, 400.0, -150.0];
            AssertClose(reference[0], pos.X());
            AssertClose(reference[1], pos.Y());
            AssertClose(reference[2], pos.Z());
            double[]? translation = name switch
            {
                "Tree1" => [0.0, 0.0, 0.0],
                "Forest tree 3" => [39.4421005419207, 220.3838834926932, 268.5013679006178],
                _ => null,
            };
            if (translation != null)
            {
                for (var row = 0; row < 3; row++)
                {
                    AssertClose(translation[row], Matrix(geometry, row, 3));
                }
            }
        }
    }

    [Fact]
    public void RailwayFurniture()
    {
        (string, string)[] expected =
        [
            ("GMLID_7431654_78949_792", "1090"),
            ("GMLID_0528986_170479_94", "OTHERS"),
            ("GMLID_4323540_367099_910", "1090"),
            ("GMLID_1381455_184173_656", "OTHERS"),
            ("GMLID_1429491_351612_1485", "1090"),
            ("GMLID_5361967_192822_672", "1090"),
            ("GMLID_2108434_31807_876", "1090"),
            ("GMLID_0373494_301709_129", "1540"),
            ("GMLID_6162422_289094_1279", "1090"),
            ("GMLID_3313190_307178_612", "1090"),
            ("GMLID_855011_330784_753", "1540"),
        ];
        var furniture = AllOf(Model, CityFurniture.TryFrom);
        Assert.Equal(expected.Length, furniture.Count);
        foreach (var (item, (id, function)) in furniture.Zip(expected))
        {
            Assert.Equal(id, Str(item.FeatureId().AsStr()));
            Assert.Equal([function], Items(item.Functions().Next).Select(f => Str(f.Value())));
            Assert.Null(item.Class());
            Assert.Empty(Items(item.Usages().Next));
            Assert.Null(item.Lod3ImplicitRepresentation());
            var property = item.Lod3MultiSurface()!;
            Assert.Null(property.Href());
            Assert.Single(Items(property.Object()!.SurfaceMember().Next));
        }
    }

    [Fact]
    public void RailwayRelief()
    {
        var relief = Assert.Single(AllOf(Model, ReliefFeature.TryFrom));
        Assert.Equal("GMLID_TIN436865_187531_1154", Str(relief.FeatureId().AsStr()));
        Assert.Empty(Items(relief.Names().Next));
        Assert.Equal(LevelOfDetail.Three, relief.Lod());
        var component = Assert.Single(Items(relief.ReliefComponents().Next));
        Assert.Null(component.Href());
        Assert.Equal(FeatureType.TinRelief, component.Object()!.FeatureType());

        var tinRelief = Assert.Single(AllOf(Model, TinRelief.TryFrom));
        Assert.Equal("UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9", Str(tinRelief.FeatureId().AsStr()));
        Assert.Equal(LevelOfDetail.Three, tinRelief.Lod());
        var tin = tinRelief.Tin()!;
        Assert.Null(tin.Href());
        var surface = tin.Object()!;
        Assert.Single(Items(surface.Triangles().Next));
        AssertClose(3.2750424144626247, surface.Area3d());
    }

    [Fact]
    public void RailwayBuildingsAndBridges()
    {
        Assert.Equal(
            [
                ("GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13),
                ("GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19),
                ("GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8),
            ],
            AllOf(Model, Building.TryFrom).Select(b => (Str(b.FeatureId().AsStr()), FirstName(b.Names()), Items(b.Boundaries().Next).Count())));
        Assert.Equal(
            [
                ("GMLID_BUI205585_1385_1373", "Bridge KIT 4"),
                ("GMLID_BUI51891_765_738", "Bridge KIT 3"),
                ("GMLID_BUI100628_817_8083", "Bridge KIT 2"),
                ("GMLID_BUI30683_572_6686", "Bridge KIT 1"),
            ],
            AllOf(Model, Bridge.TryFrom).Select(b => (Str(b.FeatureId().AsStr()), FirstName(b.Names()))));
    }

    [Fact]
    public void RailwayRoundTrip()
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(Model);
        var written = GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
        Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
        static List<string> Ids(CityModel cityModel) =>
            AllOf(cityModel, Tunnel.TryFrom).Select(x => Str(x.FeatureId().AsStr()))
                .Concat(AllOf(cityModel, SolitaryVegetationObject.TryFrom).Select(x => Str(x.FeatureId().AsStr())))
                .Concat(AllOf(cityModel, CityFurniture.TryFrom).Select(x => Str(x.FeatureId().AsStr())))
                .Concat(AllOf(cityModel, Building.TryFrom).Select(x => Str(x.FeatureId().AsStr())))
                .Concat(AllOf(cityModel, Bridge.TryFrom).Select(x => Str(x.FeatureId().AsStr())))
                .ToList();
        static List<string?> Hrefs(CityModel cityModel) =>
            AllOf(cityModel, SolitaryVegetationObject.TryFrom).Select(TemplateHref).ToList();
        Assert.Equal(Ids(Model), Ids(written));
        Assert.Equal(Hrefs(Model), Hrefs(written));
    }
}
