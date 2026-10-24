using Xunit;
using static Ecitygml.Tests.Api.ApiHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>The cases of crates/ecitygml/tests/api/geometry.md.</summary>
public class GeometryTests
{
    private const string FzkLod1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string FzkLod2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string Tum = "tum-main-entrance/TUM-Main-Entrance.gml";
    private const string AsamRoadShape = "asam-opendrive/ASAM-UC_RoadShape.gml";
    private const string Railway = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";
    private const string OgcGarage = "ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml";
    private const string OgcUnits = "ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml";
    private const string OgcRoadOverBridge =
        "ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml";

    private static List<T> AllOf<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Items(cityModel.IterFeatures().Next).Select(tryFrom).OfType<T>().ToList();

    private static void AssertClose(double expected, double actual) => Assert.Equal(expected, actual, 1e-6);

    private static void AssertPosition((double X, double Y, double Z) expected, DirectPosition actual)
    {
        AssertClose(expected.X, actual.X());
        AssertClose(expected.Y, actual.Y());
        AssertClose(expected.Z, actual.Z());
    }

    private static void AssertEnvelope(Envelope? envelope, (double, double, double) lower, (double, double, double) upper)
    {
        Assert.NotNull(envelope);
        AssertPosition(lower, envelope.LowerCorner());
        AssertPosition(upper, envelope.UpperCorner());
    }

    [Fact]
    public void ComputeEnvelope()
    {
        var lod1 = Read(FzkLod1);
        var solid = AllOf(lod1, Building.TryFrom)[0].Lod1Solid()!.Object()!;
        var lower = (457842.0, 5439083.0, 111.8);
        var upper = (457854.0, 5439093.0, 118.31769);
        AssertEnvelope(solid.ComputeEnvelope(), lower, upper);
        var shell = solid.Exterior()!;
        AssertEnvelope(shell.ComputeEnvelope(), lower, upper);
        AssertEnvelope(solid.Triangulate().Surface().ComputeEnvelope(), lower, upper);
        var first = Polygon.TryFrom(shell.Members().Next()!.Object()!)!;
        var ground = (457854.0, 5439093.0, 111.8);
        AssertEnvelope(first.ComputeEnvelope(), lower, ground);
        AssertEnvelope(first.Exterior()!.ComputeEnvelope(), lower, ground);

        var roadShape = Read(AsamRoadShape);
        var space = AllOf(roadShape, TrafficSpace.TryFrom)[0];
        var multiCurve = space.Lod2MultiCurve()!.Object()!;
        var curveLower = (-48.38872036507727, 2.3148451158285663, 0.25);
        var curveUpper = (-16.661414812688488, 26.674198193965925, 0.25);
        AssertEnvelope(multiCurve.ComputeEnvelope(), curveLower, curveUpper);
        var member = Assert.Single(Items(multiCurve.CurveMember().Next));
        AssertEnvelope(member.Object()!.ComputeEnvelope(), curveLower, curveUpper);
        var spaceSolid = space.Lod2Solid()!.Object()!;
        AssertEnvelope(
            spaceSolid.ComputeEnvelope(),
            (-49.60668801898414, 0.7284798382091271, 0.05),
            (-15.44344715878162, 28.260563471585364, 4.95));
        Assert.Equal(24, Items(spaceSolid.Points().Next).Count());

        var railway = Read(Railway);
        var tree = AllOf(railway, SolitaryVegetationObject.TryFrom)
            .First(t => Str(t.FeatureId().AsStr()) == "GMLID_SO092422_3593_9527");
        var point = tree.Lod3ImplicitRepresentation()!.Object()!.ReferencePoint().Object()!;
        var reference = (-568.8000793496976, 457.60044759869743, 105.00139681350242);
        AssertEnvelope(point.ComputeEnvelope(), reference, reference);

        var garage = Read(OgcGarage);
        var tin = AllOf(garage, TinRelief.TryFrom)[0].Tin()!.Object()!;
        AssertEnvelope(tin.ComputeEnvelope(), (458868.0, 5438343.0, 112.0), (458892.0, 5438362.0, 114.0));
    }

    [Fact]
    public void PolygonInteriorRings()
    {
        var cityModel = Read(Tum);
        var ground = Assert.Single(AllOf(cityModel, GroundSurface.TryFrom));
        var multiSurface = ground.Lod2MultiSurface()!.Object()!;
        var polygon = Polygon.TryFrom(Assert.Single(Items(multiSurface.SurfaceMember().Next)).Object()!)!;
        Assert.Equal("DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly", Str(polygon.Id()!.AsStr()));
        var exterior = LinearRing.TryFrom(polygon.Exterior()!)!;
        Assert.Equal(11, Items(exterior.Points().Next).Count());
        AssertClose(1371.825439453125, exterior.Area3d());
        AssertClose(150.78554397170106, exterior.Length3d());
        var interior = LinearRing.TryFrom(Assert.Single(Items(polygon.Interior().Next)))!;
        Assert.Equal(4, Items(interior.Points().Next).Count());
        AssertClose(142.26318359375, interior.Area3d());
        AssertClose(47.7096809282068, interior.Length3d());
        AssertClose(1229.562255859375, polygon.Area3d());
        Assert.Equal(15, Items(polygon.Points().Next).Count());
        AssertEnvelope(polygon.ComputeEnvelope(), (691009.16, 5335994.57, 515.042), (691054.07, 5336047.41, 515.042));
        var triangulation = multiSurface.Triangulate();
        Assert.False(triangulation.HasSkipped());
        Assert.Equal(15, Items(triangulation.Surface().Triangles().Next).Count());
        AssertClose(1229.5620994984272, triangulation.Surface().Area3d());
    }

    [Fact]
    public void CompositeSurfaceAndPatches()
    {
        var cityModel = Read(OgcRoadOverBridge);
        var ground = AllOf(cityModel, GroundSurface.TryFrom).First(g => Str(g.FeatureId().AsStr()) == "id_groundsurface1");
        var multiSurface = ground.Lod2MultiSurface()!.Object()!;
        Assert.Equal("id_groundsurface1-0", Str(multiSurface.Id()!.AsStr()));
        AssertClose(77500.15996032, multiSurface.Area3d());
        var kind = Assert.Single(Items(multiSurface.SurfaceMember().Next)).Object()!;
        Assert.Equal(GeometryType.CompositeSurface, kind.GeometryType());
        Assert.Null(Polygon.TryFrom(kind));
        var composite = CompositeSurface.TryFrom(kind)!;
        Assert.Equal("id_groundsurface1-1", Str(composite.Id()!.AsStr()));
        AssertClose(77500.15996032, composite.Area3d());
        Assert.Equal(6, Items(composite.Points().Next).Count());
        AssertEnvelope(composite.ComputeEnvelope(), (0.0, 0.0, 0.0), (393.7008, 196.8504, 0.0));
        var triangulation = composite.Triangulate();
        Assert.False(triangulation.HasSkipped());
        Assert.Equal(2, Items(triangulation.Surface().Triangles().Next).Count());

        string[] ids = ["fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447", "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163"];
        var members = Items(composite.SurfaceMember().Next).Select(m => m.Object()!).ToList();
        Assert.Equal(ids.Length, members.Count);
        foreach (var (surfaceKind, id) in members.Zip(ids))
        {
            Assert.Equal(GeometryType.Surface, surfaceKind.GeometryType());
            var surface = Surface.TryFrom(surfaceKind)!;
            Assert.Equal(id, Str(surface.Id()!.AsStr()));
            AssertClose(38750.07998016, surface.Area3d());
            Assert.Single(Items(surface.Triangulate().Surface().Triangles().Next));
            var patch = Assert.Single(Items(surface.Patches().Next));
            Assert.Null(Triangle.TryFrom(patch));
            var polygonPatch = PolygonPatch.TryFrom(patch)!;
            Assert.Empty(Items(polygonPatch.Interior().Next));
            Assert.Equal(3, Items(LinearRing.TryFrom(polygonPatch.Exterior()!)!.Points().Next).Count());
            AssertClose(38750.07998016, patch.Area3d());
            Assert.Single(Items(patch.Triangulate().Surface().Triangles().Next));
        }
    }

    [Fact]
    public void TrianglePatches()
    {
        var cityModel = Read(OgcGarage);
        var tin = AllOf(cityModel, TinRelief.TryFrom)[0].Tin()!.Object()!;
        Assert.Equal(12, Items(tin.Surface().Patches().Next).Count());
        var triangle = tin.Triangles().Next()!;
        AssertPosition((458883.0, 5438362.0, 114.0), triangle.A());
        AssertPosition((458868.0, 5438362.0, 112.0), triangle.B());
        AssertPosition((458875.0, 5438355.0, 112.0), triangle.C());
        AssertClose(53.42518132865812, triangle.Area());
        Assert.Equal(GeometryType.LinearRing, triangle.Exterior().GeometryType());
    }

    [Fact]
    public void UnresolvedSurfaceReference()
    {
        var cityModel = Read(OgcUnits);
        var storey = AllOf(cityModel, Storey.TryFrom).First(s => Str(s.FeatureId().AsStr()) == "storey1");
        var multiSurface = storey.Lod2MultiSurface()!.Object()!;
        Assert.Equal(6, Items(multiSurface.SurfaceMember().Next).Count());
        AssertError(() => multiSurface.Area3d(), ErrorKind.UnresolvedReference, "#Wall_1_PolyID82397_997_453711_16336011");
        Assert.Equal(12, Items(multiSurface.Points().Next).Count());
        AssertEnvelope(multiSurface.ComputeEnvelope(), (457841.1, 5439082.1, 111.1), (457853.9, 5439092.9, 113.9));
        var triangulation = multiSurface.Triangulate();
        Assert.False(triangulation.HasSkipped());
        Assert.Equal(6, Items(triangulation.Surface().Triangles().Next).Count());
    }

    [Fact]
    public void SolidUnresolvedReference()
    {
        var cityModel = Read(FzkLod2);
        var solid = AllOf(cityModel, Building.TryFrom)[0].Lod2Solid()!.Object()!;
        AssertError(() => solid.Volume3d(), ErrorKind.UnresolvedReference, "#PolyID7350_878_759628_120742");
    }

    [Fact]
    public void TriangulateWithoutMembers()
    {
        var cityModel = Read(FzkLod2);
        var solid = AllOf(cityModel, Building.TryFrom)[0].Lod2Solid()!.Object()!;
        Assert.Empty(Items(solid.Points().Next));
        Assert.Null(solid.ComputeEnvelope());
        AssertError(() => solid.Triangulate(), ErrorKind.InvalidArgument, "requires at least 1 element");
    }
}
