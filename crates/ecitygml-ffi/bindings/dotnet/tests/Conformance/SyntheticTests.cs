using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/synthetic.md. The cases of code spaces and
/// <c>vegetation_library_object</c> are scoped out: <c>Code::code_space</c> and
/// <c>ImplicitGeometry::library_object</c> aren't bound in .NET.</summary>
public class SyntheticTests
{
    private const string Dataset = "synthetic";

    private static List<FeatureType> FeatureTypes(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(f => f.FeatureType()).ToList();

    private static List<T> AllOf<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Items(cityModel.IterFeatures().Next).Select(tryFrom).OfType<T>().ToList();

    private static T Only<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Assert.Single(AllOf(cityModel, tryFrom));

    private static (int, uint, uint) Ymd(Date? date)
    {
        Assert.NotNull(date);
        return (date.Year(), date.Month(), date.Day());
    }

    private static (CityModel Written, string Text) RoundTrip(CityModel cityModel)
    {
        var writer = GmlWriter.create(CitygmlFormat.Gml);
        writer.Finish(cityModel);
        var data = writer.Data().Clone();
        return (GmlReader.create(data, CitygmlFormat.Gml).Finish(), System.Text.Encoding.UTF8.GetString(data));
    }

    private static ImplicitGeometry Implicit(ImplicitGeometryProperty? property)
    {
        Assert.NotNull(property);
        Assert.Null(property.Href());
        return property.Object()!;
    }

    public class BridgeFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "bridge.gml");

        private static BridgePart Part(Bridge bridge)
        {
            var property = Assert.Single(Items(bridge.BridgeParts().Next));
            Assert.Null(property.Href());
            return property.Object()!;
        }

        [Fact]
        public void BridgeCityModel()
        {
            Assert.Equal(1u, Model.CityObjectsLen());
            Assert.Equal([FeatureType.CityModel, FeatureType.Bridge, FeatureType.BridgePart], FeatureTypes(Model));
            Assert.Equal(
                [FeatureType.Bridge, FeatureType.BridgePart],
                Items(Model.IterCityObjects().Next).Select(o => o.FeatureType()));
        }

        [Fact]
        public void BridgeAttributes()
        {
            var bridge = Only(Model, Bridge.TryFrom);
            Assert.Equal("bridge_1", Str(bridge.FeatureId().AsStr()));
            Assert.Equal(["Synthetic bridge"], Items(bridge.Names().Next).Select(n => Str(n.Value())));
            Assert.Equal("1000", Str(bridge.Class()!.Value()));
            Assert.Equal(["1010", "1020"], Items(bridge.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1000"], Items(bridge.Usages().Next).Select(u => Str(u.Value())));
            Assert.Equal((1990, 5u, 1u), Ymd(bridge.DateOfConstruction()));
            Assert.Empty(Items(bridge.Heights().Next));
            var part = Part(bridge);
            Assert.Equal("bridge_part_1", Str(part.FeatureId().AsStr()));
            Assert.Null(part.Class());
            Assert.Empty(Items(part.Functions().Next));
            Assert.Equal("bridge_part_1", Str(Only(Model, BridgePart.TryFrom).FeatureId().AsStr()));
        }

        [Fact]
        public void BridgeIsMovable()
        {
            var bridge = Only(Model, Bridge.TryFrom);
            Assert.True(bridge.IsMovable());
            Assert.False(Part(bridge).IsMovable());
        }

        [Fact]
        public void BridgeRoundTrip()
        {
            var (written, _) = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            var bridge = Only(written, Bridge.TryFrom);
            Assert.Equal("1000", Str(bridge.Class()!.Value()));
            Assert.Equal(["1010", "1020"], Items(bridge.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal((1990, 5u, 1u), Ymd(bridge.DateOfConstruction()));
            Assert.Equal("bridge_part_1", Str(Part(bridge).FeatureId().AsStr()));
        }
    }

    public class TunnelFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "tunnel.gml");

        private static TunnelPart Part(Tunnel tunnel)
        {
            var property = Assert.Single(Items(tunnel.TunnelParts().Next));
            Assert.Null(property.Href());
            return property.Object()!;
        }

        [Fact]
        public void TunnelCityModel()
        {
            Assert.Equal(1u, Model.CityObjectsLen());
            Assert.Equal([FeatureType.CityModel, FeatureType.Tunnel, FeatureType.TunnelPart], FeatureTypes(Model));
            Assert.Equal(
                [FeatureType.Tunnel, FeatureType.TunnelPart],
                Items(Model.IterCityObjects().Next).Select(o => o.FeatureType()));
        }

        [Fact]
        public void TunnelAttributes()
        {
            var tunnel = Only(Model, Tunnel.TryFrom);
            Assert.Equal("tunnel_1", Str(tunnel.FeatureId().AsStr()));
            Assert.Equal(["Synthetic tunnel"], Items(tunnel.Names().Next).Select(n => Str(n.Value())));
            Assert.Equal("1000", Str(tunnel.Class()!.Value()));
            Assert.Equal(["1010", "1020"], Items(tunnel.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1000"], Items(tunnel.Usages().Next).Select(u => Str(u.Value())));
            Assert.Equal((1990, 5u, 1u), Ymd(tunnel.DateOfConstruction()));
            Assert.Empty(Items(tunnel.Heights().Next));
            var part = Part(tunnel);
            Assert.Equal("tunnel_part_1", Str(part.FeatureId().AsStr()));
            Assert.Null(part.Class());
            Assert.Equal(["1030"], Items(part.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal("tunnel_part_1", Str(Only(Model, TunnelPart.TryFrom).FeatureId().AsStr()));
        }

        [Fact]
        public void TunnelRoundTrip()
        {
            var (written, _) = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            var tunnel = Only(written, Tunnel.TryFrom);
            Assert.Equal("1000", Str(tunnel.Class()!.Value()));
            Assert.Equal(["1010", "1020"], Items(tunnel.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1030"], Items(Part(tunnel).Functions().Next).Select(f => Str(f.Value())));
        }
    }

    public class VegetationFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "vegetation.gml");

        private static SolitaryVegetationObject Tree(CityModel cityModel, string id) =>
            AllOf(cityModel, SolitaryVegetationObject.TryFrom).Single(t => Str(t.FeatureId().AsStr()) == id);

        [Fact]
        public void VegetationCityModel()
        {
            Assert.Equal(3u, Model.CityObjectsLen());
            Assert.Equal(
                [FeatureType.CityModel, FeatureType.SolitaryVegetationObject, FeatureType.SolitaryVegetationObject, FeatureType.PlantCover],
                FeatureTypes(Model));
        }

        [Fact]
        public void VegetationTree()
        {
            var tree = Tree(Model, "tree_1");
            Assert.Equal("1000", Str(tree.Class()!.Value()));
            Assert.Equal(["1010"], Items(tree.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1020"], Items(tree.Usages().Next).Select(u => Str(u.Value())));
            Assert.Equal("Quercus robur", Str(tree.Species()!.Value()));
            var height = tree.Height()!;
            AssertClose(12.5, height.Value());
            Assert.Equal("m", Str(height.Uom()));
            AssertClose(0.4, tree.TrunkDiameter()!.Value());
            AssertClose(5.5, tree.CrownDiameter()!.Value());
            AssertClose(1.2, tree.RootBallDiameter()!.Value());
            AssertClose(0.8, tree.MaxRootBallDepth()!.Value());
            Assert.Null(tree.Lod2ImplicitRepresentation());
            Assert.Null(tree.Lod3ImplicitRepresentation());
            Assert.Null(tree.Lod1Solid());
            Assert.Null(tree.Lod1TerrainIntersectionCurve());
        }

        [Fact]
        public void VegetationImplicitGeometry()
        {
            var geometry = Implicit(Tree(Model, "tree_1").Lod1ImplicitRepresentation());
            Assert.Equal("tree_prototype", Str(geometry.ObjectId().AsStr()));
            Assert.Equal("model/gltf+json", Str(geometry.MimeType()!.Value()));
            var pos = geometry.ReferencePoint().Object()!.Pos();
            Assert.Equal((457850.0, 5439090.0, 112.0), (pos.X(), pos.Y(), pos.Z()));
            var matrix = geometry.TransformationMatrix();
            double[][] rows = [[2, 0, 0, 10], [0, 2, 0, 20], [0, 0, 3, 30], [0, 0, 0, 1]];
            for (nuint row = 0; row < 4; row++)
            {
                for (nuint column = 0; column < 4; column++)
                {
                    AssertClose(rows[row][column], matrix.Get(row, column));
                }
            }
            var relative = geometry.RelativeGeometry()!.Object()!;
            Assert.Equal(GeometryType.MultiSurface, relative.GeometryType());
            Assert.Single(Items(MultiSurface.TryFrom(relative)!.SurfaceMember().Next));
            Assert.Null(Point.TryFrom(relative));
            var triangulation = relative.Triangulate();
            Assert.False(triangulation.HasSkipped());
            Assert.Single(Items(triangulation.Surface().Triangles().Next));
        }

        [Fact]
        public void VegetationPointRelativeGeometry()
        {
            var tree = Tree(Model, "tree_2");
            Assert.Null(tree.Lod1ImplicitRepresentation());
            var geometry = Implicit(tree.Lod2ImplicitRepresentation());
            Assert.Equal("point_prototype", Str(geometry.ObjectId().AsStr()));
            Assert.Null(geometry.MimeType());
            var relative = geometry.RelativeGeometry()!.Object()!;
            Assert.Equal(GeometryType.Point, relative.GeometryType());
            var pos = Point.TryFrom(relative)!.Pos();
            Assert.Equal((0.0, 0.0, 0.0), (pos.X(), pos.Y(), pos.Z()));
            Assert.Null(MultiSurface.TryFrom(relative));
        }

        [Fact]
        public void VegetationPlantCover()
        {
            var cover = Only(Model, PlantCover.TryFrom);
            Assert.Equal("cover_1", Str(cover.FeatureId().AsStr()));
            Assert.Equal("2000", Str(cover.Class()!.Value()));
            Assert.Empty(Items(cover.Functions().Next));
            Assert.Empty(Items(cover.Usages().Next));
            AssertClose(2.5, cover.AverageHeight()!.Value());
            AssertClose(1.0, cover.MinHeight()!.Value());
            AssertClose(4.0, cover.MaxHeight()!.Value());
            Assert.Null(cover.Lod1ImplicitRepresentation());
            var feature = Items(Model.IterFeatures().Next).Single(f => f.FeatureType() == FeatureType.PlantCover);
            Assert.Null(SolitaryVegetationObject.TryFrom(feature));
        }

        [Fact]
        public void VegetationRoundTrip()
        {
            var (written, text) = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            var tree = Tree(written, "tree_1");
            Assert.Equal("Quercus robur", Str(tree.Species()!.Value()));
            AssertClose(12.5, tree.Height()!.Value());
            var geometry = Implicit(tree.Lod1ImplicitRepresentation());
            Assert.Equal("tree_prototype", Str(geometry.ObjectId().AsStr()));
            Assert.Equal("model/gltf+json", Str(geometry.MimeType()!.Value()));
            AssertClose(2.5, Only(written, PlantCover.TryFrom).AverageHeight()!.Value());
            Assert.DoesNotContain("objectId", text);
        }
    }

    public class CityFurnitureFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "city-furniture.gml");

        [Fact]
        public void FurnitureAttributes()
        {
            var furniture = Only(Model, CityFurniture.TryFrom);
            Assert.Equal("sign_1", Str(furniture.FeatureId().AsStr()));
            Assert.Equal(["Vorschriftzeichen"], Items(furniture.Names().Next).Select(n => Str(n.Value())));
            Assert.Equal("1000", Str(furniture.Class()!.Value()));
            Assert.Equal(["1080"], Items(furniture.Functions().Next).Select(f => Str(f.Value())));
            Assert.Equal(["1090"], Items(furniture.Usages().Next).Select(u => Str(u.Value())));
            var property = furniture.Lod2MultiSurface()!;
            Assert.Null(property.Href());
            Assert.Single(Items(property.Object()!.SurfaceMember().Next));
            Assert.Null(furniture.Lod1ImplicitRepresentation());
            Assert.Null(furniture.Lod2TerrainIntersectionCurve());
        }
    }

    private static RoofSurface Roof(AbstractSpaceBoundaryProperty property)
    {
        Assert.Null(property.Href());
        return RoofSurface.TryFrom(AbstractFeatureKindRef.FromSpaceBoundary(property.Object()!))!;
    }

    private static GenericAttributeSet AttributeSet(Building building) =>
        GenericAttributeSet.TryFrom(Assert.Single(Items(building.GenericAttributes().Next)))!;

    public class BuildingFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "building.gml");

        private static Building Building1(CityModel cityModel) =>
            AllOf(cityModel, Building.TryFrom).Single(b => Str(b.FeatureId().AsStr()) == "building_1");

        [Fact]
        public void BuildingCityModel()
        {
            Assert.Equal(2u, Model.CityObjectsLen());
            Assert.Equal(
                [FeatureType.CityModel, FeatureType.Building, FeatureType.RoofSurface, FeatureType.WindowSurface, FeatureType.Building],
                FeatureTypes(Model));
            Assert.Equal(4, Items(Model.IterCityObjects().Next).Count());
        }

        [Fact]
        public void BuildingRelation()
        {
            var property = Assert.Single(Items(Building1(Model).RelatedTo().Next));
            Assert.Null(property.Href());
            var relation = property.Object()!;
            Assert.Equal("shared", Str(relation.RelationType().Value()));
            Assert.Equal("#building_2", relation.RelationTo().Href()!.ToString());
            var weight = Assert.Single(Items(relation.GenericAttributes().Next));
            Assert.Equal("weight", Str(weight.Name()));
            Assert.Equal(3L, weight.AsInt()!.Value());
        }

        [Fact]
        public void BuildingAttributeSet()
        {
            var set = AttributeSet(Building1(Model));
            Assert.Equal("energy", Str(set.Name()));
            var attributes = Items(set.GenericAttributes().Next).ToList();
            Assert.Equal(2, attributes.Count);
            Assert.Equal("demand", Str(attributes[0].Name()));
            AssertClose(12.5, attributes[0].AsDouble()!.Value());
            Assert.Equal("label", Str(attributes[1].Name()));
            Assert.Equal("A+", Str(attributes[1].AsString()!.Value()));
        }

        [Fact]
        public void BuildingConstruction()
        {
            var building = Building1(Model);
            Assert.Equal(RelativeToWater.EntirelyAboveWaterSurface, building.RelativeToWater());
            Assert.Equal((2020, 1u, 1u), Ymd(building.DateOfConstruction()));
            Assert.Equal((2050, 12u, 31u), Ymd(building.DateOfDemolition()));
            var occupancy = Assert.Single(Items(building.Occupancies().Next));
            Assert.Equal(4L, occupancy.NumberOfOccupants());
            Assert.Equal("daytime", Str(occupancy.Interval()!.Value()));
            Assert.Equal("residents", Str(occupancy.OccupantType()!.Value()));
        }

        [Fact]
        public void BuildingBoundaries()
        {
            var boundaries = Items(Building1(Model).Boundaries().Next).ToList();
            Assert.Equal(2, boundaries.Count);
            var roof = Roof(boundaries[0]);
            Assert.Equal("roof_1", Str(roof.FeatureId().AsStr()));
            var filling = Assert.Single(Items(roof.FillingSurfaces().Next));
            Assert.Null(filling.Href());
            var window = filling.Object()!;
            Assert.Equal(FeatureType.WindowSurface, window.FeatureType());
            Assert.Equal("roof_window_1", Str(window.FeatureId().AsStr()));
            Assert.Null(boundaries[1].Object());
            Assert.Equal("#missing_boundary", boundaries[1].Href()!.ToString());
        }

        [Fact]
        public void BuildingTerrainIntersectionCurve()
        {
            var building = Building1(Model);
            var property = building.Lod2TerrainIntersectionCurve()!;
            Assert.Null(property.Href());
            var multiCurve = property.Object()!;
            var member = Assert.Single(Items(multiCurve.CurveMember().Next));
            Assert.Equal(2, Items(LineString.TryFrom(member.Object()!)!.Points().Next).Count());
            AssertClose(12.0, multiCurve.Length3d());
            Assert.Null(building.Lod1TerrainIntersectionCurve());
            Assert.Null(building.Lod3TerrainIntersectionCurve());
        }

        [Fact]
        public void BuildingRoundTrip()
        {
            var (written, text) = RoundTrip(Model);
            Assert.Equal(FeatureTypes(Model), FeatureTypes(written));
            var building = Building1(written);
            var relation = Assert.Single(Items(building.RelatedTo().Next)).Object()!;
            Assert.Equal("#building_2", relation.RelationTo().Href()!.ToString());
            Assert.Equal("energy", Str(AttributeSet(building).Name()));
            Assert.Equal((2050, 12u, 31u), Ymd(building.DateOfDemolition()));
            var occupancy = Assert.Single(Items(building.Occupancies().Next));
            Assert.Equal(4L, occupancy.NumberOfOccupants());
            Assert.Equal("daytime", Str(occupancy.Interval()!.Value()));
            Assert.Equal("residents", Str(occupancy.OccupantType()!.Value()));
            var boundaries = Items(building.Boundaries().Next).ToList();
            var window = Assert.Single(Items(Roof(boundaries[0]).FillingSurfaces().Next)).Object()!;
            Assert.Equal("roof_window_1", Str(window.FeatureId().AsStr()));
            Assert.Equal("#missing_boundary", boundaries[1].Href()!.ToString());
            AssertClose(12.0, building.Lod2TerrainIntersectionCurve()!.Object()!.Length3d());
            Assert.DoesNotContain("TerrainIntersectionCurveProperty", text);
        }
    }

    public class TransportationFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "transportation.gml");

        [Fact]
        public void TransportationSection()
        {
            var section = Only(Model, Section.TryFrom);
            Assert.Equal("section_1", Str(section.FeatureId().AsStr()));
            Assert.Equal(TrafficDirectionValue.Both, section.TrafficDirection());
            var occupancy = Assert.Single(Items(section.Occupancies().Next));
            Assert.Equal(120L, occupancy.NumberOfOccupants());
            Assert.Equal("peakHour", Str(occupancy.Interval()!.Value()));
            var property = Assert.Single(Items(section.TrafficSpaces().Next));
            Assert.Null(property.Href());
            var space = property.Object()!;
            Assert.Equal("space_1", Str(space.FeatureId().AsStr()));
            Assert.Equal(GranularityValue.Lane, space.Granularity());
        }

        [Fact]
        public void TransportationPoint()
        {
            var property = Only(Model, TrafficSpace.TryFrom).Lod0Point()!;
            Assert.Null(property.Href());
            var point = property.Object()!;
            Assert.Equal("point_1", Str(point.Id()!.AsStr()));
            var pos = point.Pos();
            Assert.Equal((1.5, -2.5, 3.25), (pos.X(), pos.Y(), pos.Z()));
            var envelope = point.ComputeEnvelope()!;
            foreach (var corner in new[] { envelope.LowerCorner(), envelope.UpperCorner() })
            {
                Assert.Equal((1.5, -2.5, 3.25), (corner.X(), corner.Y(), corner.Z()));
            }
        }

        [Fact]
        public void TransportationCurves()
        {
            var multiCurve = Only(Model, TrafficSpace.TryFrom).Lod0MultiCurve()!.Object()!;
            var members = Items(multiCurve.CurveMember().Next).ToList();
            Assert.Equal(3, members.Count);
            var line = members[0].Object()!;
            Assert.Equal(GeometryType.LineString, line.GeometryType());
            Assert.Null(AbstractRingKind.TryFrom(line));
            var lineString = LineString.TryFrom(line)!;
            Assert.Equal(2, Items(lineString.Points().Next).Count());
            AssertClose(5.0, lineString.Length3d());
            var ring = members[1].Object()!;
            Assert.Equal(GeometryType.LinearRing, ring.GeometryType());
            var linearRing = LinearRing.TryFrom(AbstractRingKind.TryFrom(ring)!)!;
            Assert.Equal(3, Items(linearRing.Points().Next).Count());
            AssertClose(2.0 + Math.Sqrt(2.0), linearRing.Length3d());
            Assert.Null(members[2].Object());
            Assert.Equal("#missing_curve", members[2].Href()!.ToString());
            var exception = Assert.Throws<ErrorException>(() => multiCurve.Length3d());
            Assert.Equal(ErrorKind.UnresolvedReference, exception.Inner.Kind());
            Assert.Contains("#missing_curve", exception.Inner.Message());
        }
    }

    public class GeometryFile
    {
        private static readonly CityModel Model = ReadFixture(Dataset, "geometry.gml");

        [Fact]
        public void GeometrySkippedMembers()
        {
            var building = AllOf(Model, Building.TryFrom).Single(b => Str(b.FeatureId().AsStr()) == "geometry_1");
            var multiSurface = building.Lod2MultiSurface()!.Object()!;
            var members = Items(multiSurface.SurfaceMember().Next).Select(m => m.Object()!).ToList();
            Assert.Equal(3, members.Count);
            foreach (var (kind, id) in members.Take(2).Zip(["square", "collinear"]))
            {
                Assert.Equal(GeometryType.Polygon, kind.GeometryType());
                Assert.Equal(id, Str(kind.Id()!.AsStr()));
            }
            AssertClose(0.0, members[1].Area3d());
            Assert.Equal(GeometryType.TriangulatedSurface, members[2].GeometryType());
            Assert.Null(Polygon.TryFrom(members[2]));
            var tin = TriangulatedSurface.TryFrom(members[2])!;
            Assert.Equal("tin", Str(tin.Id()!.AsStr()));
            Assert.Equal(2, Items(tin.Triangles().Next).Count());
            Assert.Equal(2, Items(tin.Surface().Patches().Next).Count());
            AssertClose(1.0, tin.Area3d());
            var triangulation = multiSurface.Triangulate();
            Assert.Equal(4, Items(triangulation.Surface().Triangles().Next).Count());
            Assert.True(triangulation.HasSkipped());
            var error = Assert.Single(Items(triangulation.Skipped().Next));
            Assert.Equal(ErrorKind.InvalidArgument, error.Kind());
            Assert.Contains("earcut produced no triangles", error.Message());
        }
    }
}
