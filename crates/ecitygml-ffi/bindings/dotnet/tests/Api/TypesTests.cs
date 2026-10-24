using Xunit;
using static Ecitygml.Tests.Api.ApiHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>The cases of crates/ecitygml/tests/api/types.md. <c>level_of_detail_index</c> and <c>code_space</c> are
/// scoped out (C# enums have no methods; <c>Code::code_space</c> isn't bound).</summary>
public class TypesTests
{
    private const string FzkLod1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string FzkLod2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string FzkLod3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string Tum = "tum-main-entrance/TUM-Main-Entrance.gml";
    private const string AsamRoadShape = "asam-opendrive/ASAM-UC_RoadShape.gml";
    private const string AsamJunction = "asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml";
    private const string Railway = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";

    /// <summary>The first feature that <paramref name="tryFrom"/> accepts.</summary>
    private static T First<T>(CityModel cityModel, Func<AbstractFeatureKindRef, T?> tryFrom) where T : class =>
        Items(cityModel.IterFeatures().Next).Select(tryFrom).First(x => x != null)!;

    /// <summary><c>tryFrom</c> accepts exactly the features of its feature type.</summary>
    private static void AssertTryFromMatches(
        CityModel cityModel, (Func<AbstractFeatureKindRef, object?> TryFrom, FeatureType FeatureType)[] types)
    {
        foreach (var feature in Items(cityModel.IterFeatures().Next))
        {
            foreach (var (tryFrom, featureType) in types)
            {
                Assert.True(
                    (tryFrom(feature) != null) == (feature.FeatureType() == featureType),
                    $"{featureType} as {feature.FeatureType()}");
            }
        }
    }

    [Fact]
    public void DirectPositionNew()
    {
        var position = DirectPosition.create(1.0, 2.0, 3.0);
        Assert.Equal([1.0, 2.0, 3.0], new[] { position.X(), position.Y(), position.Z() });
        AssertError(() => DirectPosition.create(double.NaN, 0.0, 0.0), ErrorKind.InvalidArgument, "non-finite");
    }

    [Fact]
    public void FeatureTypeName()
    {
        Assert.Equal("Building", FeatureType.Building.ToString());
        Assert.Equal("TinRelief", FeatureType.TinRelief.ToString());
    }

    [Fact]
    public void DateFromParts()
    {
        var date = Date.FromParts(2020, 1, 2, 3600);
        Assert.Equal((2020, 1u, 2u, 3600), (date.Year(), date.Month(), date.Day(), date.OffsetSeconds()));
        var start = date.StartOfDay();
        Assert.Equal((0u, 0u, 0u), (start.Hour(), start.Minute(), start.Second()));
        Assert.Equal("2020-01-02T00:00:00+01:00", start.ToRfc3339());

        AssertError(() => Date.FromParts(2021, 2, 30, 0), ErrorKind.InvalidArgument, "do not form a valid date");
    }

    [Fact]
    public void DateTimeFromParts()
    {
        var dateTime = DateTime.FromParts(2017, 1, 23, 13, 14, 15, 500_000_000, -7200);
        Assert.Equal((2017, 1u, 23u), (dateTime.Year(), dateTime.Month(), dateTime.Day()));
        Assert.Equal((13u, 14u, 15u), (dateTime.Hour(), dateTime.Minute(), dateTime.Second()));
        Assert.Equal(500_000_000u, dateTime.Nanosecond());
        Assert.Equal(-7200, dateTime.OffsetSeconds());
        Assert.Equal(1485184455L, dateTime.Timestamp());
        Assert.Equal(500_000_000u, dateTime.TimestampSubsecNanos());
        Assert.Equal("2017-01-23T13:14:15.500-02:00", dateTime.ToRfc3339());

        AssertError(
            () => DateTime.FromParts(2020, 1, 1, 0, 0, 0, 0, 30),
            ErrorKind.InvalidArgument,
            "timezone offset of 30 s is invalid");
    }

    [Fact]
    public void DateTimeRead()
    {
        var created = First(Read(FzkLod2), Building.TryFrom).CreationDate();
        Assert.Equal("2017-01-23T00:00:00+01:00", created!.ToRfc3339());
    }

    [Fact]
    public void TryFromMatchesFeatureType()
    {
        AssertTryFromMatches(Read(FzkLod3),
        [
            (Building.TryFrom, FeatureType.Building),
            (WallSurface.TryFrom, FeatureType.WallSurface),
            (RoofSurface.TryFrom, FeatureType.RoofSurface),
            (GroundSurface.TryFrom, FeatureType.GroundSurface),
            (DoorSurface.TryFrom, FeatureType.DoorSurface),
            (WindowSurface.TryFrom, FeatureType.WindowSurface),
        ]);
        AssertTryFromMatches(Read(AsamRoadShape),
        [
            (Road.TryFrom, FeatureType.Road),
            (Section.TryFrom, FeatureType.Section),
            (TrafficSpace.TryFrom, FeatureType.TrafficSpace),
            (TrafficArea.TryFrom, FeatureType.TrafficArea),
            (AuxiliaryTrafficSpace.TryFrom, FeatureType.AuxiliaryTrafficSpace),
            (AuxiliaryTrafficArea.TryFrom, FeatureType.AuxiliaryTrafficArea),
        ]);
    }

    [Fact]
    public void FeatureFromCityObject()
    {
        var cityObject = Read(AsamJunction).IterCityObjects().Next()!;
        Assert.Equal(FeatureType.Road, cityObject.FeatureType());
        var feature = AbstractFeatureKindRef.FromCityObject(cityObject);
        Assert.Equal(FeatureType.Road, feature.FeatureType());
        Assert.Equal("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", Str(Road.TryFrom(feature)!.FeatureId().AsStr()));
        Assert.Null(Building.TryFrom(feature));
    }

    [Fact]
    public void MatrixIndexOutOfRange()
    {
        var tree = Items(Read(Railway).IterFeatures().Next)
            .Select(SolitaryVegetationObject.TryFrom)
            .First(t => t != null && Str(t.FeatureId().AsStr()) == "GMLID_SO092422_3593_9527")!;
        var matrix = tree.Lod3ImplicitRepresentation()!.Object()!.TransformationMatrix();
        Assert.Equal(1.0, matrix.Get(3, 3));
        foreach (var (row, column) in new (nuint, nuint)[] { (4, 0), (0, 4) })
        {
            AssertError(() => matrix.Get(row, column), ErrorKind.InvalidArgument, "out of range");
        }
    }

    [Fact]
    public void GmlId()
    {
        var cityModel = Read(FzkLod1);
        var generated = Str(cityModel.FeatureId().AsStr());
        Assert.StartsWith("ecitygml-gen-feature-", generated);
        Assert.Equal(generated, Str(cityModel.Id()!.AsStr()));

        var wall = First(Read(FzkLod2), WallSurface.TryFrom);
        Assert.Equal("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", Str(wall.Id()!.AsStr()));
        Assert.Equal("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", Str(wall.FeatureId().AsStr()));

        Assert.Equal("DEBY_LOD2_4959457", Str(First(Read(Tum), Building.TryFrom).Id()!.AsStr()));
    }
}
