using System.Text;
using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/fzk-haus.md.</summary>
public class FzkHausTests
{
    private const string Lod1File = "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string Lod2File = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string Lod3File = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";

    private static (double, double, double) Point(DirectPosition position) => (position.X(), position.Y(), position.Z());

    private static void AssertPointClose((double, double, double) expected, (double, double, double) actual)
    {
        AssertClose(expected.Item1, actual.Item1);
        AssertClose(expected.Item2, actual.Item2);
        AssertClose(expected.Item3, actual.Item3);
    }

    private static Polygon PolygonOf(AbstractSurfaceProperty property) => Polygon.TryFrom(property.Object()!)!;

    private static List<WallSurface> Walls(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(WallSurface.TryFrom).OfType<WallSurface>().ToList();

    public class Lod1
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture("fzk-haus", Lod1File);

        [Fact]
        public void Lod1CityModel()
        {
            Assert.Equal(1u, (uint)Model.CityObjectsLen());
            var envelope = Model.BoundedBy()!.Envelope()!;
            var (lower, upper) = (envelope.LowerCorner(), envelope.UpperCorner());
            AssertClose(457842.0, lower.X());
            AssertClose(5439083.0, lower.Y());
            AssertClose(111.8, lower.Z());
            AssertClose(457854.0, upper.X());
            AssertClose(5439093.0, upper.Y());
            AssertClose(118.317669, upper.Z());
        }

        [Fact]
        public void Lod1BuildingAttributes()
        {
            var building = FirstBuilding(Model);
            Assert.Equal("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", Str(building.FeatureId().AsStr()));
            Assert.Equal(["AC14-FZK-Haus"], Items(building.Names().Next).Select(n => Str(n.Value())));
            Assert.Equal("1000", Str(building.Class()!.Value()));
            Assert.Equal(["1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1000"], Items(building.Usages().Next).Select(u => Str(u.Value())));
            Assert.Equal("1030", Str(building.RoofType()!.Value()));
            Assert.Equal((2L, 0L), (building.StoreysAboveGround(), building.StoreysBelowGround()));

            var date = building.DateOfConstruction()!;
            Assert.Equal((2020, 1u, 1u), (date.Year(), date.Month(), date.Day()));
            Assert.Null(building.DateOfDemolition());
            var height = Assert.Single(Items(building.Heights().Next));
            Assert.Equal("topOfConstruction", Str(height.HighReference().Value()));
            Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
            Assert.Equal(HeightStatusValue.Measured, height.Status());
            AssertClose(6.52, height.Length().Value());
            Assert.Equal("m", Str(height.Length().Uom()));
            Assert.Empty(Items(building.Occupancies().Next));
            Assert.Empty(Items(building.BuildingParts().Next));
        }

        [Fact]
        public void Lod1Solid()
        {
            var building = FirstBuilding(Model);
            var solid = building.Lod1Solid()!.Object()!;
            AssertClose(782.1228, solid.Volume3d());
            var triangulation = solid.Triangulate();
            Assert.Equal(12, Items(triangulation.Surface().Triangles().Next).Count());
            Assert.False(triangulation.HasSkipped());
            Assert.Empty(Items(building.Boundaries().Next));
        }

        [Fact]
        public void Lod1EnvelopeMeasures()
        {
            var envelope = Model.BoundedBy()!.Envelope()!;
            AssertPointClose((12.0, 10.0, 6.517669), (envelope.SizeX(), envelope.SizeY(), envelope.SizeZ()));
            AssertPointClose((457848.0, 5439088.0, 115.0588345), Point(envelope.Center()));
            AssertClose(782.12028, envelope.Volume());
            Assert.True(envelope.Contains(envelope.LowerCorner()));
            Assert.True(envelope.Contains(envelope.UpperCorner()));
            Assert.True(envelope.Contains(DirectPosition.create(457848.0, 5439088.0, 115.0)));
            Assert.False(envelope.Contains(DirectPosition.create(457848.0, 5439088.0, 118.4)));
            Assert.False(envelope.Contains(DirectPosition.create(457841.9, 5439088.0, 115.0)));
            Assert.Null(Model.CreationDate());
        }

        [Fact]
        public void Lod1BuildingDetails()
        {
            Assert.Single(Items(Model.IterFeatures().Next), f => f.FeatureType() == FeatureType.Building);
            var building = FirstBuilding(Model);
            Assert.Equal("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", Str(building.Id()!.AsStr()));
            var envelope = building.BoundedBy()!.Envelope()!;
            AssertPointClose((457842.0, 5439083.0, 111.8), Point(envelope.LowerCorner()));
            AssertPointClose((457854.0, 5439093.0, 118.31769), Point(envelope.UpperCorner()));
            Assert.Null(building.Lod2Solid());
            Assert.Null(building.Lod0MultiSurface());
        }

        [Fact]
        public void Lod1SolidStructure()
        {
            var solid = FirstBuilding(Model).Lod1Solid()!.Object()!;
            Assert.Empty(Items(solid.Interior().Next));
            Assert.Equal(24, Items(solid.Points().Next).Count());
            var shell = solid.Exterior()!;
            AssertClose(782.1228, shell.Volume3d());
            var members = Items(shell.Members().Next).ToList();
            Assert.Equal(6, members.Count);
            Assert.All(members, m => Assert.Null(m.Href()));
            var polygons = members.Select(PolygonOf).ToList();
            Assert.All(polygons, p => Assert.Empty(Items(p.Interior().Next)));
            var rings = polygons.Select(p => LinearRing.TryFrom(p.Exterior()!)!).ToList();
            Assert.Equal(Enumerable.Repeat(4, 6), rings.Select(r => Items(r.Points().Next).Count()));
            Assert.All(rings, r => Assert.True(r.Area3d() > 0.0));
            AssertPointClose((457842.0, 5439083.0, 111.8), Point(Items(rings[0].Points().Next).First()));
            AssertClose(44.0, rings[0].Length3d());
            AssertClose(120.0, rings[0].Area3d());
        }

        [Fact]
        public void Lod1SolidTriangulation()
        {
            var solid = FirstBuilding(Model).Lod1Solid()!.Object()!;
            var triangulation = solid.Triangulate();
            Assert.Empty(Items(triangulation.Skipped().Next));
            var surface = triangulation.Surface();
            AssertClose(526.77836, surface.Area3d());
            Assert.Equal(36, Items(surface.Points().Next).Count());
            var triangle = Items(surface.Triangles().Next).First();
            AssertClose(111.8, triangle.A().Z());
            AssertClose(60.0, triangle.Area());
            var shell = solid.Exterior()!;
            Assert.Equal(12, Items(shell.Triangulate().Surface().Triangles().Next).Count());
            var first = PolygonOf(Items(shell.Members().Next).First());
            Assert.Equal(2, Items(first.Triangulate().Surface().Triangles().Next).Count());
        }

        [Fact]
        public void Lod1ApplyScale()
        {
            var cityModel = ReadFixture("fzk-haus", Lod1File);
            cityModel.ApplyScale(new Scale3 { X = 2.0, Y = 3.0, Z = 0.5 });
            var envelope = cityModel.BoundedBy()!.Envelope()!;
            AssertPointClose((24.0, 30.0, 3.2588345), (envelope.SizeX(), envelope.SizeY(), envelope.SizeZ()));
        }
    }

    public class Lod2
    {
        private static readonly CityModel Model = ReadFixture("fzk-haus", Lod2File);

        [Fact]
        public void Lod2BoundarySurfaces()
        {
            var features = Boundaries(FirstBuilding(Model));
            Assert.Equal(
                [
                    FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.RoofSurface,
                    FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ],
                features.Select(f => f.FeatureType()));
            Assert.Equal(
                ["Outer Wall 1 (West)", "Outer Wall 2 (South)", "Outer Wall 3 (East)", "Outer Wall 4 (North)"],
                features.Select(WallSurface.TryFrom).OfType<WallSurface>().Select(w => FirstName(w.Names())));
            Assert.Equal(
                ["Roof 1 (North)", "Roof 2 (South)"],
                features.Select(RoofSurface.TryFrom).OfType<RoofSurface>().Select(r => FirstName(r.Names())));
            Assert.Equal(
                ["Base Surface"],
                features.Select(GroundSurface.TryFrom).OfType<GroundSurface>().Select(g => FirstName(g.Names())));
        }

        [Fact]
        public void Lod2SurfaceAreas()
        {
            var features = Boundaries(FirstBuilding(Model));
            AssertClose(188.62887820601463, features.Select(WallSurface.TryFrom).OfType<WallSurface>()
                .Sum(s => s.Lod2MultiSurface()!.Object()!.Area3d()));
            AssertClose(138.56406460961398, features.Select(RoofSurface.TryFrom).OfType<RoofSurface>()
                .Sum(s => s.Lod2MultiSurface()!.Object()!.Area3d()));
            AssertClose(120.0, features.Select(GroundSurface.TryFrom).OfType<GroundSurface>()
                .Sum(s => s.Lod2MultiSurface()!.Object()!.Area3d()));
        }

        [Fact]
        public void Lod2GenericAttributes()
        {
            var building = FirstBuilding(Model);
            var attributes = Items(building.GenericAttributes().Next).ToList();
            Assert.Equal(3, attributes.Count);
            var measure = MeasureAttribute.TryFrom(attributes[0])!;
            Assert.Equal("GrossPlannedArea", Str(attributes[0].Name()));
            AssertClose(120.0, measure.Value().Value());
            Assert.Equal("m2", Str(measure.Value().Uom()));
            Assert.Equal(("ConstructionMethod", "New Building"), (Str(attributes[1].Name()), Str(attributes[1].AsString()!.Value())));
            Assert.Equal(("IsLandmarked", "NO"), (Str(attributes[2].Name()), Str(attributes[2].AsString()!.Value())));
            Assert.Empty(Items(building.ExternalReferences().Next));
        }

        [Fact]
        public void Lod2SolidUnresolved()
        {
            var solid = FirstBuilding(Model).Lod2Solid()!.Object()!;
            Assert.Throws<ErrorException>(() => solid.Volume3d());
        }

        [Fact]
        public void Lod2BuildingDetails()
        {
            var building = FirstBuilding(Model);
            Assert.Equal(RelativeToTerrain.EntirelyAboveTerrain, building.RelativeToTerrain());
            Assert.Null(building.RelativeToWater());
            var created = building.CreationDate()!;
            Assert.Equal((2017, 1u, 23u, 0u), (created.Year(), created.Month(), created.Day(), created.Hour()));
            Assert.Equal(3600, created.OffsetSeconds());
            Assert.Equal(1485126000L, created.Timestamp());
            Assert.Null(building.TerminationDate());
            Assert.Null(building.ValidFrom());
            Assert.Null(building.ValidTo());

            Assert.Equal("1000", Str(building.Class()!.Value()));
            Assert.Equal(["1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1000"], Items(building.Usages().Next).Select(u => Str(u.Value())));
            Assert.Equal("1030", Str(building.RoofType()!.Value()));
            Assert.Equal((2L, 0L), (building.StoreysAboveGround(), building.StoreysBelowGround()));
            var date = building.DateOfConstruction()!;
            Assert.Equal((2020, 1u, 1u), (date.Year(), date.Month(), date.Day()));
            Assert.Null(building.DateOfDemolition());
            var height = Assert.Single(Items(building.Heights().Next));
            Assert.Equal("topOfConstruction", Str(height.HighReference().Value()));
            Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
            Assert.Equal(HeightStatusValue.Measured, height.Status());
            AssertClose(6.52, height.Length().Value());
            Assert.Equal("m", Str(height.Length().Uom()));

            Assert.Empty(Items(building.Occupancies().Next));
            Assert.Empty(Items(building.RelatedTo().Next));
            Assert.Null(building.Lod1Solid());
            Assert.Null(building.BoundedBy());
            Assert.Null(building.Lod1TerrainIntersectionCurve());
            Assert.Null(building.Lod2TerrainIntersectionCurve());
            Assert.Null(building.Lod3TerrainIntersectionCurve());
            Assert.Null(building.Lod1ImplicitRepresentation());
            Assert.Null(building.Lod2ImplicitRepresentation());
            Assert.Null(building.Lod3ImplicitRepresentation());
        }

        [Fact]
        public void Lod2BoundaryIds()
        {
            var properties = Items(FirstBuilding(Model).Boundaries().Next).ToList();
            Assert.All(properties, p => Assert.Null(p.Href()));
            Assert.Equal(
                [
                    "GML_5856d7ad-5e34-498a-817b-9544bfbb1475",
                    "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
                    "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069",
                    "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
                    "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc",
                    "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
                    "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
                ],
                properties.Select(p => Str(p.Object()!.FeatureId().AsStr())));
        }

        [Fact]
        public void Lod2WallSurface()
        {
            var features = Boundaries(FirstBuilding(Model));
            var walls = features.Select(WallSurface.TryFrom).OfType<WallSurface>().ToList();
            var wall = walls[0];
            Assert.Equal("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", Str(wall.Id()!.AsStr()));
            Assert.Null(wall.Lod0MultiCurve());
            Assert.Null(wall.Lod0MultiSurface());
            Assert.Null(wall.Lod1MultiSurface());
            Assert.Null(wall.RelativeToTerrain());
            Assert.Null(wall.CreationDate());
            Assert.Empty(Items(wall.GenericAttributes().Next));
            Assert.NotNull(wall.BoundedBy());
            var multiSurface = wall.Lod2MultiSurface()!.Object()!;
            Assert.Single(Items(multiSurface.SurfaceMember().Next));
            Assert.Equal(3, Items(multiSurface.Triangulate().Surface().Triangles().Next).Count());
            Assert.All(walls, w => Assert.Empty(Items(w.FillingSurfaces().Next)));
            var ground = features.Select(GroundSurface.TryFrom).OfType<GroundSurface>().First();
            var member = Items(ground.Lod2MultiSurface()!.Object()!.SurfaceMember().Next).First();
            Assert.Equal(4, Items(PolygonOf(member).Exterior()!.Points().Next).Count());
        }

        [Fact]
        public void Lod2GenericAttributeKinds()
        {
            var attributes = Items(FirstBuilding(Model).GenericAttributes().Next).ToList();
            Assert.Null(attributes[0].AsString());
            Assert.Null(MeasureAttribute.TryFrom(attributes[1]));
            Assert.Null(MeasureAttribute.TryFrom(attributes[2]));
        }

        [Fact]
        public void Lod2CityObjects()
        {
            Assert.Equal(
                [
                    FeatureType.Building, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface,
                    FeatureType.RoofSurface, FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ],
                Items(Model.IterCityObjects().Next).Select(o => o.FeatureType()));
            var types = Items(Model.IterFeatures().Next).Select(f => f.FeatureType()).ToList();
            Assert.Equal(FeatureType.CityModel, types[0]);
            Assert.Single(types, t => t == FeatureType.CityModel);
        }

        [Fact]
        public void Lod2ObjectBounds()
        {
            var reader = GmlReader.FromPath(Encoding.UTF8.GetBytes(Fixture($"fzk-haus/{Lod2File}")));
            reader.WithRebuildObjectBounds(false);
            var cityModel = reader.Finish();
            Assert.Equal([false, false, false, false], Walls(cityModel).Select(w => w.BoundedBy() != null));
            cityModel.RecomputeChildBoundingShapes();
            Assert.Equal([true, true, true, true], Walls(cityModel).Select(w => w.BoundedBy() != null));
        }

        /// <summary>The lower corners of the city model's envelope and of the first wall surface's.</summary>
        private static List<(double, double, double)> LowerCorners(CityModel cityModel) =>
        [
            Point(cityModel.BoundedBy()!.Envelope()!.LowerCorner()),
            Point(Walls(cityModel)[0].BoundedBy()!.Envelope()!.LowerCorner()),
        ];

        [Fact]
        public void Lod2ApplyTranslation()
        {
            var cityModel = ReadFixture("fzk-haus", Lod2File);
            Assert.All(LowerCorners(cityModel), c => AssertPointClose((457842.0, 5439083.0, 111.8), c));
            cityModel.ApplyTranslation(new Vector3 { X = -100.0, Y = 200.0, Z = 10.0 });
            Assert.All(LowerCorners(cityModel), c => AssertPointClose((457742.0, 5439283.0, 121.8), c));
        }
    }

    public class Lod3
    {
        private static readonly CityModel Model = ReadFixture("fzk-haus", Lod3File);

        [Fact]
        public void Lod3DoorsAndWindows()
        {
            var features = Items(Model.IterFeatures().Next).ToList();
            var doors = features.Select(DoorSurface.TryFrom).OfType<DoorSurface>().ToList();
            Assert.Equal(["Door West", "Door South"], doors.Select(d => FirstName(d.Names())));
            AssertClose(6.803850099444389, doors.Sum(d => d.Lod3MultiSurface()!.Object()!.Area3d()));
            Assert.Equal(11, features.Select(WindowSurface.TryFrom).OfType<WindowSurface>().Count());
        }

        [Fact]
        public void Lod3WestWallFillings()
        {
            var wall = WallSurface.TryFrom(Boundaries(FirstBuilding(Model))[0])!;
            Assert.Equal("Outer Wall 1 (West)", FirstName(wall.Names()));
            var fillings = Items(wall.FillingSurfaces().Next).Select(p => p.Object()!).ToList();
            Assert.Equal(
                [
                    (FeatureType.WindowSurface, "Window Round"),
                    (FeatureType.WindowSurface, "Window North"),
                    (FeatureType.DoorSurface, "Door West"),
                    (FeatureType.WindowSurface, "Window South"),
                ],
                fillings.Select(f => (f.FeatureType(), FirstName(f.Names()))));
        }

        [Fact]
        public void Lod3BuildingDetails()
        {
            Assert.Equal(1u, (uint)Model.CityObjectsLen());
            var building = FirstBuilding(Model);
            Assert.Equal(RelativeToTerrain.EntirelyAboveTerrain, building.RelativeToTerrain());
            var features = Boundaries(building);
            Assert.Equal(
                [
                    FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.RoofSurface,
                    FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ],
                features.Select(f => f.FeatureType()));
            Assert.All(features.Select(WallSurface.TryFrom).OfType<WallSurface>(), w => Assert.NotNull(w.Lod3MultiSurface()));
        }

        [Fact]
        public void Lod3Fillings()
        {
            var features = Boundaries(FirstBuilding(Model));
            var perWall = features.Select(WallSurface.TryFrom).OfType<WallSurface>()
                .Select(w => Items(w.FillingSurfaces().Next).ToList()).ToList();
            Assert.Equal([4, 3, 3, 3], perWall.Select(p => p.Count));
            var properties = perWall.SelectMany(p => p).ToList();
            Assert.All(properties, p => Assert.Null(p.Href()));
            var fillings = properties.Select(p => p.Object()!).ToList();
            var types = fillings.Select(f => f.FeatureType()).ToList();
            Assert.Equal((2, 11), (types.Count(t => t == FeatureType.DoorSurface), types.Count(t => t == FeatureType.WindowSurface)));
            Assert.All(fillings, f => Assert.True(f.Lod3MultiSurface()!.Object()!.Area3d() > 0.0));
            Assert.All(features.Select(RoofSurface.TryFrom).OfType<RoofSurface>(), r => Assert.Empty(Items(r.FillingSurfaces().Next)));

            var all = Items(Model.IterFeatures().Next).ToList();
            var windows = all.Select(WindowSurface.TryFrom).OfType<WindowSurface>();
            AssertClose(23.168802611529827, windows.Sum(w => w.Lod3MultiSurface()!.Object()!.Area3d()));
            var doors = all.Select(DoorSurface.TryFrom).OfType<DoorSurface>().ToList();
            Assert.Equal(
                ["GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd", "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629"],
                doors.Select(d => Str(d.FeatureId().AsStr())));
            Assert.All(doors, d => Assert.Null(d.Lod2MultiSurface()));
        }

        [Fact]
        public void Lod3CityObjects()
        {
            var objects = Items(Model.IterCityObjects().Next).Select(o => o.FeatureType()).ToList();
            Assert.Equal(21, objects.Count);
            FeatureType[] kinds =
            [
                FeatureType.Building, FeatureType.WallSurface, FeatureType.RoofSurface,
                FeatureType.GroundSurface, FeatureType.DoorSurface, FeatureType.WindowSurface,
            ];
            Assert.Equal([1, 4, 2, 1, 2, 11], kinds.Select(k => objects.Count(t => t == k)));
            var types = Items(Model.IterFeatures().Next).Select(f => f.FeatureType()).ToList();
            Assert.Equal(22, types.Count);
            Assert.Equal(FeatureType.CityModel, types[0]);
        }

        [Fact]
        public void Lod3CompositeSurface()
        {
            var wall = WallSurface.TryFrom(Boundaries(FirstBuilding(Model))[0])!;
            var member = Items(wall.Lod3MultiSurface()!.Object()!.SurfaceMember().Next).First();
            var composite = CompositeSurface.TryFrom(member.Object()!)!;
            var members = Items(composite.SurfaceMember().Next).ToList();
            Assert.Equal(85, members.Count);
            var start = Items(PolygonOf(members[0]).Exterior()!.Points().Next).First();
            AssertPointClose((457842.0, 5439088.49240388, 115.913175911167), Point(start));
        }

        [Fact]
        public void Lod3RoundTrip()
        {
            var writer = GmlWriter.create(CitygmlFormat.Gml);
            writer.Finish(Model);
            var written = GmlReader.create(writer.Data().Clone(), CitygmlFormat.Gml).Finish();
            Assert.Equal(
                Items(Model.IterFeatures().Next).Select(f => f.FeatureType()),
                Items(written.IterFeatures().Next).Select(f => f.FeatureType()));
            Assert.Equal("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", Str(FirstBuilding(written).FeatureId().AsStr()));
            Assert.Equal(SurfaceIds(Model), SurfaceIds(written));
            var height = Assert.Single(Items(FirstBuilding(written).Heights().Next));
            Assert.Equal("topOfConstruction", Str(height.HighReference().Value()));
            Assert.Equal("lowestGroundPoint", Str(height.LowReference().Value()));
            Assert.Equal(HeightStatusValue.Measured, height.Status());
            AssertClose(6.52, height.Length().Value());
            Assert.Equal("m", Str(height.Length().Uom()));
        }

        /// <summary>The `feature_id`s of the building's boundaries, then of the wall surfaces' filling
        /// surfaces.</summary>
        private static List<string> SurfaceIds(CityModel cityModel)
        {
            var building = FirstBuilding(cityModel);
            var ids = Items(building.Boundaries().Next).Select(p => Str(p.Object()!.FeatureId().AsStr())).ToList();
            foreach (var wall in Boundaries(building).Select(WallSurface.TryFrom).Where(w => w != null))
            {
                ids.AddRange(Items(wall!.FillingSurfaces().Next).Select(p => Str(p.Object()!.FeatureId().AsStr())));
            }
            return ids;
        }
    }
}
