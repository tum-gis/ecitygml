using Xunit;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests;

public class BuildingTests
{
    private static (CityModel CityModel, Building Building) FirstBuilding(string fixture)
    {
        // Return the city model too: the building borrows from it, so callers keep both referenced.
        var cityModel = Read(fixture);
        var building = Items(cityModel.IterFeatures().Next).Select(Building.TryFrom).First(b => b != null)!;
        return (cityModel, building);
    }

    [Fact]
    public void OwnAndInheritedGetters()
    {
        var (_, building) = FirstBuilding("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
        Assert.Equal("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", Str(building.FeatureId().AsStr()));
        Assert.Equal("1000", Str(building.Class()!.Value()));
        Assert.Equal(["1000"], Items(building.Functions().Next).Select(f => Str(f.Value())));
        Assert.Equal("1030", Str(building.RoofType()!.Value()));
        Assert.Equal(2L, building.StoreysAboveGround());
        Assert.Equal(0L, building.StoreysBelowGround());
        Assert.Equal(2020, building.DateOfConstruction()!.Year());
        Assert.Null(building.DateOfDemolition());

        var height = Assert.Single(Items(building.Heights().Next));
        Assert.Equal(6.52, height.Length().Value());
        Assert.Equal("m", Str(height.Length().Uom()));
    }

    [Fact]
    public void Lod1SolidVolumeAndTriangulation()
    {
        var (_, building) = FirstBuilding("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
        var solid = building.Lod1Solid()?.Object();
        Assert.NotNull(solid);
        Assert.Equal(782.1228, solid.Volume3d(), 1e-6);
        var triangulation = solid.Triangulate();
        Assert.False(triangulation.HasSkipped());
        Assert.Equal(12, Items(triangulation.Surface().Triangles().Next).Count());
    }

    [Fact]
    public void WallSurfacesAsBoundaries()
    {
        var (_, building) = FirstBuilding("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
        var walls = Items(building.Boundaries().Next)
            .Select(property => property.Object())
            .OfType<AbstractSpaceBoundaryKind>()
            .Select(boundary => WallSurface.TryFrom(AbstractFeatureKindRef.FromSpaceBoundary(boundary)))
            .OfType<WallSurface>()
            .ToList();
        Assert.Equal(4, walls.Count);
        Assert.Equal(188.629, walls.Sum(wall => wall.Lod2MultiSurface()!.Object()!.Area3d()), 1e-3);
    }

    [Fact]
    public void LoD2SolidOfReferencesIsNotComputable()
    {
        // The FZK LoD2 solid only references its polygons by xlink:href, which stays unresolved.
        var (_, building) = FirstBuilding("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
        var solid = building.Lod2Solid()!.Object()!;
        var exception = Assert.Throws<ErrorException>(() => solid.Volume3d());
        Assert.Contains("xlink:href", exception.Inner.Message());
    }
}
