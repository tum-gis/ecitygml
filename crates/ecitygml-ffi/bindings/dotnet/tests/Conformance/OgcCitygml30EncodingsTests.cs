using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.</summary>
public class OgcCitygml30EncodingsTests
{
    private const string Dataset = "ogc-citygml-3.0-encodings";

    private const FeatureType Wall = FeatureType.WallSurface;
    private const FeatureType Roof = FeatureType.RoofSurface;
    private const FeatureType Ground = FeatureType.GroundSurface;

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    /// <summary>All features a class accepts, in document order.</summary>
    private static List<T> AllOf<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Items(cityModel.IterFeatures().Next).Select(tryFrom).OfType<T>().ToList();

    private static List<string> Names(CodeIterator names) => Items(names.Next).Select(n => Str(n.Value())).ToList();

    private static void AssertEnvelope(Envelope envelope, (double, double, double) lower, (double, double, double) upper)
    {
        foreach (var (position, expected) in new[] { (envelope.LowerCorner(), lower), (envelope.UpperCorner(), upper) })
        {
            AssertClose(expected.Item1, position.X());
            AssertClose(expected.Item2, position.Y());
            AssertClose(expected.Item3, position.Z());
        }
    }

    private static CityModel RoundTrip(CityModel cityModel)
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(cityModel);
        return GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
    }

    private record Surface(FeatureType Type, string Id, string? Name, MultiSurfaceProperty? MultiSurface);

    /// <summary>A space's boundaries; all inline wall, roof or ground surfaces.</summary>
    private static List<Surface> Surfaces(AbstractSpaceBoundaryPropertyIterator boundaries) =>
        Items(boundaries.Next).Select(property =>
        {
            Assert.Null(property.Href());
            var obj = property.Object()!;
            var id = Str(obj.FeatureId().AsStr());
            var feature = AbstractFeatureKindRef.FromSpaceBoundary(obj);
            string? First(CodeIterator names) => Names(names).FirstOrDefault();
            if (WallSurface.TryFrom(feature) is { } wall)
            {
                return new Surface(feature.FeatureType(), id, First(wall.Names()), wall.Lod2MultiSurface());
            }
            if (RoofSurface.TryFrom(feature) is { } roof)
            {
                return new Surface(feature.FeatureType(), id, First(roof.Names()), roof.Lod2MultiSurface());
            }
            var ground = GroundSurface.TryFrom(feature);
            Assert.NotNull(ground);
            return new Surface(feature.FeatureType(), id, First(ground.Names()), ground.Lod2MultiSurface());
        }).ToList();

    private static double Lod2Area(MultiSurfaceProperty? property) => property!.Object()!.Area3d();

    private static void AssertHeight(HeightIterator heights, double length)
    {
        var height = Assert.Single(Items(heights.Next));
        Assert.Equal("highestRoofEdge", Str(height.HighReference().Value()));
        Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
        Assert.Equal(HeightStatusValue.Measured, height.Status());
        AssertClose(length, height.Length().Value());
        Assert.Equal("#m", Str(height.Length().Uom()));
    }

    /// <summary>The hrefs of a storey's LoD2 surface members (null for inline members).</summary>
    private static List<string?> MemberHrefs(Storey storey)
    {
        var property = storey.Lod2MultiSurface()!;
        Assert.Null(property.Href());
        return Items(property.Object()!.SurfaceMember().Next).Select(member =>
        {
            Assert.Equal(member.Object() == null, member.Href() != null);
            return member.Href()?.ToString();
        }).ToList();
    }

    /// <summary>The relations of the roof surfaces and traffic areas, in document order: (city object, relation type,
    /// href).</summary>
    private static List<(string, string, string?)> Relations(CityModel cityModel)
    {
        var result = new List<(string, string, string?)>();
        foreach (var feature in Items(cityModel.IterFeatures().Next))
        {
            string id;
            CityObjectRelationPropertyIterator relatedTo;
            if (RoofSurface.TryFrom(feature) is { } roof)
            {
                (id, relatedTo) = (Str(roof.FeatureId().AsStr()), roof.RelatedTo());
            }
            else if (TrafficArea.TryFrom(feature) is { } area)
            {
                (id, relatedTo) = (Str(area.FeatureId().AsStr()), area.RelatedTo());
            }
            else
            {
                continue;
            }
            foreach (var property in Items(relatedTo.Next))
            {
                Assert.Null(property.Href());
                var relation = property.Object()!;
                Assert.Empty(Items(relation.GenericAttributes().Next));
                result.Add((id, Str(relation.RelationType().Value()), relation.RelationTo().Href()?.ToString()));
            }
        }
        return result;
    }

    /// <summary>(year, month, day) of a date time at 00:00 UTC.</summary>
    private static (int, uint, uint)? Date(DateTime? dateTime)
    {
        if (dateTime == null)
        {
            return null;
        }
        Assert.Equal((0u, 0u, 0), (dateTime.Hour(), dateTime.Minute(), dateTime.OffsetSeconds()));
        return (dateTime.Year(), dateTime.Month(), dateTime.Day());
    }

    public class Garage
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "Building_and_garage_LOD2-EPSG25832.gml");

        private static Building TheBuilding() => Assert.Single(AllOf(Model, Building.TryFrom));

        [Fact]
        public void GarageCityModel()
        {
            Assert.Equal(2u, (uint)Model.CityObjectsLen());
            AssertEnvelope(Model.BoundedBy()!.Envelope()!, (458868.0, 5438343.0, 112.0), (458892.0, 5438362.0, 117.0));
            Assert.Equal(
                [
                    FeatureType.CityModel, FeatureType.Building, Ground,
                    .. Enumerable.Repeat(Wall, 4),
                    Roof, Roof, FeatureType.BuildingPart,
                    .. Enumerable.Repeat(Wall, 4),
                    Ground, Roof, FeatureType.ReliefFeature, FeatureType.TinRelief,
                ],
                FeatureTypes(Model));
            Assert.Equal(17, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void GarageBuilding()
        {
            var building = TheBuilding();
            Assert.Equal("GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68", Str(building.FeatureId().AsStr()));
            Assert.Equal(["Example Building LOD2"], Names(building.Names()));
            Assert.Null(building.Class());
            Assert.Equal(["1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
            Assert.Empty(Items(building.Usages().Next));
            Assert.Equal("1030", Str(building.RoofType()!.Value()));
            Assert.Equal(1L, building.StoreysAboveGround());
            Assert.Null(building.StoreysBelowGround());
            var date = building.DateOfConstruction()!;
            Assert.Equal((1985, 1u, 1u), (date.Year(), date.Month(), date.Day()));
            AssertHeight(building.Heights(), 6.0);
            (FeatureType, string, double)[] expected =
            [
                (Ground, "Ground Slab", 50.0),
                (Wall, "Wall South", 30.0),
                (Wall, "Wall North", 30.0),
                (Wall, "Wall East", 20.0),
                (Wall, "Wall West", 20.0),
                (Roof, "Roof North", 32.01562118716424),
                (Roof, "Roof South", 32.01562118716424),
            ];
            var actual = Surfaces(building.Boundaries());
            Assert.Equal(expected.Select(e => (e.Item1, (string?)e.Item2)), actual.Select(a => (a.Type, a.Name)));
            foreach (var (surface, want) in actual.Zip(expected))
            {
                AssertClose(want.Item3, Lod2Area(surface.MultiSurface));
            }
        }

        [Fact]
        public void GarageBuildingPart()
        {
            var property = Assert.Single(Items(TheBuilding().BuildingParts().Next));
            Assert.Null(property.Href());
            var part = property.Object()!;
            Assert.Equal("GMLID_BUI379228_1244_301", Str(part.FeatureId().AsStr()));
            Assert.Equal(["Example BuildingPart LOD2"], Names(part.Names()));
            Assert.Null(part.Class());
            Assert.Equal(["1630"], Items(part.Functions().Next).Select(f => Str(f.Value())));
            Assert.Empty(Items(part.Usages().Next));
            Assert.Equal("1010", Str(part.RoofType()!.Value()));
            var date = part.DateOfConstruction()!;
            Assert.Equal((1985, 1u, 1u), (date.Year(), date.Month(), date.Day()));
            AssertHeight(part.Heights(), 2.5);
            // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
            (FeatureType, string, double?)[] expected =
            [
                (Wall, "Garage Wall East", 9.600000023841858),
                (Wall, "Garage Wall South", 6.25),
                (Wall, "Garage Wall West", null),
                (Wall, "Garage Wall North", 5.75),
                (Ground, "Garage Ground Slab", 10.0),
                (Roof, "Garage Roof", 10.012492197250394),
            ];
            var actual = Surfaces(part.Boundaries());
            Assert.Equal(expected.Select(e => (e.Item1, (string?)e.Item2)), actual.Select(a => (a.Type, a.Name)));
            foreach (var (surface, want) in actual.Zip(expected))
            {
                if (want.Item3 is { } area)
                {
                    AssertClose(area, Lod2Area(surface.MultiSurface));
                }
            }
        }

        [Fact]
        public void GarageRelief()
        {
            var relief = Assert.Single(AllOf(Model, ReliefFeature.TryFrom));
            Assert.Equal("GML_6bb30328-7599-4500-90ef-766fde6aa67b", Str(relief.FeatureId().AsStr()));
            Assert.Equal(["Example TIN LOD2"], Names(relief.Names()));
            Assert.Equal(LevelOfDetail.Two, relief.Lod());
            var component = Assert.Single(Items(relief.ReliefComponents().Next));
            Assert.Null(component.Href());
            Assert.Equal(FeatureType.TinRelief, component.Object()!.FeatureType());

            var tinRelief = Assert.Single(AllOf(Model, TinRelief.TryFrom));
            Assert.Equal("GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9", Str(tinRelief.FeatureId().AsStr()));
            Assert.Equal(["Ground"], Names(tinRelief.Names()));
            Assert.Equal(LevelOfDetail.Two, tinRelief.Lod());
            var tin = tinRelief.Tin()!;
            Assert.Null(tin.Href());
            var surface = tin.Object()!;
            Assert.Equal(12, Items(surface.Triangles().Next).Count());
            AssertClose(399.8446647372588, surface.Area3d());
        }

        [Fact]
        public void GarageRoundTrip()
        {
            var written = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            var ids = AllOf(written, Building.TryFrom).Select(b => Str(b.FeatureId().AsStr()))
                .Concat(AllOf(written, BuildingPart.TryFrom).Select(p => Str(p.FeatureId().AsStr())))
                .Concat(AllOf(written, ReliefFeature.TryFrom).Select(r => Str(r.FeatureId().AsStr())))
                .Concat(AllOf(written, TinRelief.TryFrom).Select(t => Str(t.FeatureId().AsStr())));
            Assert.Equal(
                [
                    "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68",
                    "GMLID_BUI379228_1244_301",
                    "GML_6bb30328-7599-4500-90ef-766fde6aa67b",
                    "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9",
                ],
                ids);
        }
    }

    public class Units
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "BuildingUnits_Storeys_xlink.gml");

        [Fact]
        public void UnitsCityModel()
        {
            Assert.Equal(1u, (uint)Model.CityObjectsLen());
            AssertEnvelope(Model.BoundedBy()!.Envelope()!, (457841.0, 5439082.0, 111.0), (457854.0, 5439093.0, 121.0));
            static IEnumerable<FeatureType> Room(int walls) =>
                [FeatureType.BuildingRoom, .. Enumerable.Repeat(FeatureType.InteriorWallSurface, walls), FeatureType.FloorSurface, FeatureType.CeilingSurface];
            Assert.Equal(
                [
                    FeatureType.CityModel, FeatureType.Building,
                    .. Enumerable.Repeat(Wall, 3),
                    Roof, Wall, Roof, Ground,
                    .. Room(8), .. Room(8), .. Room(4),
                    FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey,
                ],
                FeatureTypes(Model));
            Assert.Equal(41, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void UnitsBuilding()
        {
            var building = Assert.Single(AllOf(Model, Building.TryFrom));
            Assert.Equal("building_unit_example_1", Str(building.FeatureId().AsStr()));
            Assert.Empty(Items(building.Names().Next));
            Assert.Empty(Items(building.Functions().Next));
            Assert.Empty(Items(building.Usages().Next));
            Assert.Null(building.Class());
            Assert.Null(building.RoofType());
            (FeatureType, string, double)[] expected =
            [
                (Wall, "Outer Wall 1 (West)", 89.375),
                (Wall, "Outer Wall 2 (South)", 81.25),
                (Wall, "Outer Wall 3 (East)", 89.375),
                (Roof, "Roof 1 (North)", 86.53792521201326),
                (Wall, "Outer Wall 4 (North)", 81.25),
                (Roof, "Roof 2 (South)", 86.53792521201326),
                (Ground, "Base Surface", 143.0),
            ];
            var actual = Surfaces(building.Boundaries());
            Assert.Equal(expected.Select(e => (e.Item1, (string?)e.Item2)), actual.Select(a => (a.Type, a.Name)));
            foreach (var (surface, want) in actual.Zip(expected))
            {
                AssertClose(want.Item3, Lod2Area(surface.MultiSurface));
            }
        }

        [Fact]
        public void UnitsSubdivisions()
        {
            var building = Assert.Single(AllOf(Model, Building.TryFrom));
            var subdivisions = Items(building.BuildingSubdivisions().Next).ToList();
            Assert.All(subdivisions, s => Assert.Null(s.Href()));
            Assert.Equal(
                [FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey],
                subdivisions.Select(s => s.Object()!.FeatureType()));
            var units = AllOf(Model, BuildingUnit.TryFrom);
            Assert.Equal(["BuildingUnit_apartment1", "BuildingUnit_apartment2"], units.Select(u => Str(u.FeatureId().AsStr())));
            Assert.All(units, unit =>
            {
                Assert.Equal(["apartment"], Items(unit.Functions().Next).Select(f => Str(f.Value())));
                Assert.Null(unit.Class());
                Assert.Empty(Items(unit.Usages().Next));
                Assert.Empty(Items(unit.Boundaries().Next));
                Assert.Null(unit.Lod2MultiSurface());
            });
            var storeys = AllOf(Model, Storey.TryFrom);
            Assert.Equal(["storey1", "storey2"], storeys.Select(s => Str(s.FeatureId().AsStr())));
            Assert.All(storeys, storey =>
            {
                Assert.Empty(Items(storey.Names().Next));
                Assert.Null(storey.Class());
                Assert.Empty(Items(storey.Functions().Next));
                Assert.Empty(Items(storey.Usages().Next));
                Assert.Empty(Items(storey.Boundaries().Next));
            });
        }

        [Fact]
        public void UnitsStoreyGeometry()
        {
            (string[], (double, double, double), (double, double, double))[] expected =
            [
                (
                    [
                        "#Wall_1_PolyID82397_997_453711_16336011",
                        "#Wall_1_PolyID82397_997_453711_16336012",
                        "#Wall_1_PolyID82397_997_453711_163360136",
                    ],
                    (457841.1, 5439082.1, 111.1),
                    (457853.9, 5439092.9, 113.9)
                ),
                (
                    [
                        "#Wall_1_PolyID82397_997_453711_163360112",
                        "#Wall_1_PolyID82397_997_453711_163360122",
                        "#Wall_1_PolyID82397_997_453711_1633601362",
                    ],
                    (457841.1, 5439082.1, 114.1),
                    (457853.9, 5439092.9, 116.9)
                ),
            ];
            var storeys = AllOf(Model, Storey.TryFrom);
            Assert.Equal(expected.Length, storeys.Count);
            foreach (var (storey, (hrefs, lower, upper)) in storeys.Zip(expected))
            {
                Assert.Equal([null, .. hrefs, null, null], MemberHrefs(storey));
                var multiSurface = storey.Lod2MultiSurface()!.Object()!;
                Assert.Throws<ErrorException>(() => multiSurface.Area3d());
                AssertEnvelope(storey.BoundedBy()!.Envelope()!, lower, upper);
            }
        }

        [Fact]
        public void UnitsRoundTrip()
        {
            var written = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            Assert.Equal("building_unit_example_1", Str(Assert.Single(AllOf(written, Building.TryFrom)).FeatureId().AsStr()));
            Assert.Equal(AllOf(Model, Storey.TryFrom).Select(MemberHrefs), AllOf(written, Storey.TryFrom).Select(MemberHrefs));
        }
    }

    public class RoadBridge
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model =
            ReadFixture(Dataset, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");

        [Fact]
        public void RoadBridgeCityModel()
        {
            Assert.Equal(2u, (uint)Model.CityObjectsLen());
            Assert.Null(Model.BoundedBy());
            FeatureType[] section =
                [FeatureType.Section, FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea];
            Assert.Equal(
                [
                    FeatureType.CityModel, FeatureType.Bridge, Ground, Roof, Roof,
                    .. Enumerable.Repeat(Wall, 4),
                    FeatureType.Road, .. section, .. section, .. section,
                ],
                FeatureTypes(Model));
            Assert.Equal(24, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void RoadBridgeBridge()
        {
            var bridge = Assert.Single(AllOf(Model, Bridge.TryFrom));
            Assert.Equal("id_bridge1", Str(bridge.FeatureId().AsStr()));
            Assert.Empty(Items(bridge.Names().Next));
            Assert.Empty(Items(bridge.RelatedTo().Next));
            (string, double)[] expected =
            [
                ("id_groundsurface1", 77500.15996032),
                ("id_roofsurface1", 38750.07998016),
                ("id_roofsurface2", 38750.07998016),
                ("id_wallsurface4", 10075.02000744),
                ("id_wallsurface1", 20150.04001488),
                ("id_wallsurface2", 10075.02000744),
                ("id_wallsurface3", 20150.04001488),
            ];
            var actual = Surfaces(bridge.Boundaries());
            Assert.Equal(expected.Select(e => e.Item1), actual.Select(a => a.Id));
            foreach (var (surface, want) in actual.Zip(expected))
            {
                AssertClose(want.Item2, Lod2Area(surface.MultiSurface));
            }
        }

        [Fact]
        public void RoadBridgeRoad()
        {
            var road = Assert.Single(AllOf(Model, Road.TryFrom));
            Assert.Equal("id_road1", Str(road.FeatureId().AsStr()));
            Assert.Empty(Items(road.RelatedTo().Next));
            Assert.Empty(Items(road.TrafficSpaces().Next));
            Assert.Empty(Items(road.AuxiliaryTrafficSpaces().Next));
            var sections = Items(road.Sections().Next).Select(p =>
            {
                Assert.Null(p.Href());
                return p.Object()!;
            }).ToList();
            Assert.Equal(["id_section1", "id_section2", "id_section3"], sections.Select(s => Str(s.FeatureId().AsStr())));
            var spaces = sections.SelectMany(section => Items(section.TrafficSpaces().Next).Select(p =>
            {
                Assert.Null(p.Href());
                return p.Object()!;
            })).ToList();
            int[] numbers = [1, 2, 5, 6, 3, 4];
            Assert.Equal(numbers.Select(n => $"id_trafficspace{n}"), spaces.Select(s => Str(s.FeatureId().AsStr())));
            foreach (var (space, number) in spaces.Zip(numbers))
            {
                var boundary = Assert.Single(Items(space.Boundaries().Next));
                Assert.Null(boundary.Href());
                var area = boundary.Object()!;
                Assert.Equal(FeatureType.TrafficArea, area.FeatureType());
                Assert.Equal($"id_trafficarea{number}", Str(area.FeatureId().AsStr()));
            }
        }

        [Fact]
        public void RoadBridgeRelations()
        {
            Assert.Equal(
                [
                    ("id_roofsurface1", "equal", (string?)"id_trafficarea5"),
                    ("id_roofsurface2", "equal", "id_trafficarea6"),
                    ("id_trafficarea5", "equal", "id_roofSurface1"),
                    ("id_trafficarea6", "equal", "id_roofSurface2"),
                ],
                Relations(Model));
            Assert.All(AllOf(Model, WallSurface.TryFrom), w => Assert.Empty(Items(w.RelatedTo().Next)));
            Assert.All(AllOf(Model, GroundSurface.TryFrom), g => Assert.Empty(Items(g.RelatedTo().Next)));
        }

        [Fact]
        public void RoadBridgeRoundTrip()
        {
            var written = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            Assert.Equal(["id_bridge1"], AllOf(written, Bridge.TryFrom).Select(b => Str(b.FeatureId().AsStr())));
            Assert.Equal(["id_road1"], AllOf(written, Road.TryFrom).Select(r => Str(r.FeatureId().AsStr())));
            Assert.Equal(Relations(Model), Relations(written));
        }
    }

    public class Versioning
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture(Dataset, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml");

        [Fact]
        public void VersioningCityModel()
        {
            Assert.Equal(4u, (uint)Model.CityObjectsLen());
            Assert.Null(Model.BoundedBy());
            var types = FeatureTypes(Model);
            Assert.Equal(60, types.Count);
            Assert.Equal(FeatureType.CityModel, types[0]);
            Assert.Equal(
                new Dictionary<FeatureType, int>
                {
                    [FeatureType.CityModel] = 1,
                    [FeatureType.Building] = 4,
                    [FeatureType.BuildingPart] = 5,
                    [Roof] = 14,
                    [Wall] = 31,
                    [Ground] = 5,
                },
                types.GroupBy(t => t).ToDictionary(g => g.Key, g => g.Count()));
            Assert.Equal(59, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void VersioningBuildings()
        {
            (string, string, (int, uint, uint), (int, uint, uint)?, string[])[] expected =
            [
                ("BU_69381AL47_2000-01-01", "Building A", (2000, 1u, 1u), (2015, 1u, 1u), ["BU_69381AL47_1"]),
                ("BU_69381AL49_2000-01-01", "Building B", (2000, 1u, 1u), (2015, 1u, 1u), ["BU_69381AL49_1_2000-01-01"]),
                ("BU_69381AL49_2015-01-01", "Building B", (2015, 1u, 1u), null, ["BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01"]),
                ("BU_69381AL50_2015-01-01", "Building C", (2015, 1u, 1u), null, ["BU_69381AL50_1"]),
            ];
            var buildings = AllOf(Model, Building.TryFrom);
            Assert.Equal(expected.Length, buildings.Count);
            foreach (var (building, (id, name, created, terminated, parts)) in buildings.Zip(expected))
            {
                Assert.Equal(id, Str(building.FeatureId().AsStr()));
                Assert.Equal(name, Names(building.Names()).First());
                Assert.Equal(created, Date(building.CreationDate()));
                Assert.Equal(terminated, Date(building.TerminationDate()));
                var properties = Items(building.BuildingParts().Next).ToList();
                Assert.All(properties, p => Assert.Null(p.Href()));
                Assert.Equal(parts, properties.Select(p => Str(p.Object()!.FeatureId().AsStr())));
                Assert.Empty(Items(building.Heights().Next));
                Assert.Empty(Items(building.Boundaries().Next));
            }
        }

        [Fact]
        public void VersioningBuildingParts()
        {
            (string, double, int)[] expected =
            [
                ("BU_69381AL47_1", 13.015, 8),
                ("BU_69381AL49_1_2000-01-01", 10.63, 9),
                ("BU_69381AL49_1_2015-01-01", 10.63, 9),
                ("BU_69381AL49_2_2015-01-01", 8.743, 7),
                ("BU_69381AL50_1", 18.215, 17),
            ];
            var parts = AllOf(Model, BuildingPart.TryFrom);
            Assert.Equal(expected.Length, parts.Count);
            foreach (var (part, (id, height, boundaries)) in parts.Zip(expected))
            {
                Assert.Equal(id, Str(part.FeatureId().AsStr()));
                AssertHeight(part.Heights(), height);
                Assert.Equal(boundaries, Items(part.Boundaries().Next).Count());
                Assert.Null(part.CreationDate());
                Assert.Empty(Items(part.Names().Next));
            }
        }

        [Fact]
        public void VersioningRoundTrip()
        {
            var written = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            static List<string> Ids(CityModel cityModel) =>
                AllOf(cityModel, Building.TryFrom).Select(b => Str(b.FeatureId().AsStr()))
                    .Concat(AllOf(cityModel, BuildingPart.TryFrom).Select(p => Str(p.FeatureId().AsStr()))).ToList();
            static List<((int, uint, uint)?, (int, uint, uint)?)> Dates(CityModel cityModel) =>
                AllOf(cityModel, Building.TryFrom).Select(b => (Date(b.CreationDate()), Date(b.TerminationDate()))).ToList();
            Assert.Equal(Ids(Model), Ids(written));
            Assert.Equal(Dates(Model), Dates(written));
        }
    }
}
