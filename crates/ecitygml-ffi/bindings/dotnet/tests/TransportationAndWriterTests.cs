using Xunit;
using static Envis.Ecitygml.Tests.Helpers;

namespace Envis.Ecitygml.Tests;

public class TransportationAndWriterTests
{
    [Fact]
    public void TotalTrafficSpaceVolume()
    {
        var cityModel = Read("ASAM-UC_RoadShape.gml");
        var total = Items(cityModel.IterFeatures().Next)
            .Select(TrafficSpace.TryFrom)
            .OfType<TrafficSpace>()
            .Select(space => space.Lod2Solid()?.Object())
            .OfType<Solid>()
            .Sum(solid => solid.Volume3d());
        Assert.Equal(1260.0, total, 1e-9);
    }

    [Fact]
    public void RoadHierarchy()
    {
        var cityModel = Read("ASAM-Ex_Bidirectional_Junction.gml");
        var road = Items(cityModel.IterFeatures().Next).Select(Road.TryFrom).OfType<Road>().Single();
        Assert.Equal(3, Items(road.Sections().Next).Count());
        var intersection = Assert.Single(Items(road.Intersections().Next)).Object()!;
        Assert.Equal(3, Items(intersection.TrafficSpaces().Next).Count());
    }

    [Fact]
    public void GmlWriterRoundTripsInMemory()
    {
        var cityModel = Read("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
        var writer = GmlWriter.create(CitygmlFormat.GmlGz);
        writer.WithFormatting(Formatting.Indent((byte)' ', 2));
        writer.Finish(cityModel);
        var data = writer.Data().Clone();
        Assert.True(data.Length > 0);

        var written = GmlReader.create(data, CitygmlFormat.GmlGz).Finish();
        Assert.Equal(8, Items(written.IterCityObjects().Next).Count());
    }
}
