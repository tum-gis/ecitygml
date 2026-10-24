using Xunit;
using static Ecitygml.Tests.Api.ApiHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Api;

/// <summary>The cases of crates/ecitygml/tests/api/iteration.md. <c>native_iteration</c> is scoped out: the iterators
/// have <c>Next()</c>, but aren't <c>IEnumerator</c>s.</summary>
public class IterationTests
{
    private const string FzkLod3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
    private const string AsamRoadShape = "asam-opendrive/ASAM-UC_RoadShape.gml";

    [Fact]
    public void IteratorExhausted()
    {
        var iterator = Read(FzkLod3).IterFeatures();
        var count = 0;
        while (iterator.Next() != null)
        {
            count++;
        }
        Assert.Equal(22, count);
        Assert.Null(iterator.Next());
    }

    [Fact]
    public void IteratorStoppedEarly()
    {
        var cityModel = Read(AsamRoadShape);
        DropAfterFirst(cityModel);
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Assert.Equal(11, FeatureTypes(cityModel).Count);
        Assert.Equal(1u, cityModel.CityObjectsLen());
    }

    /// <summary>Takes the first feature of a fresh iterator, which is unreachable afterwards.</summary>
    private static void DropAfterFirst(CityModel cityModel)
    {
        var iterator = cityModel.IterFeatures();
        Assert.Equal(FeatureType.CityModel, iterator.Next()!.FeatureType());
    }

    [Fact]
    public void IteratorsIndependent()
    {
        var cityModel = Read(FzkLod3);
        var (first, second) = (cityModel.IterFeatures(), cityModel.IterFeatures());
        var (a, b) = (new List<FeatureType>(), new List<FeatureType>());
        while (true)
        {
            var (x, y) = (first.Next(), second.Next());
            Assert.Equal(x == null, y == null);
            if (x == null || y == null)
            {
                break;
            }
            a.Add(x.FeatureType());
            b.Add(y.FeatureType());
        }
        Assert.Equal(22, a.Count);
        Assert.Equal(a, b);
        Assert.Equal(a, FeatureTypes(cityModel));
    }

    [Fact]
    public void IteratorKeepsModelAlive()
    {
        var iterator = Read(FzkLod3).IterFeatures();
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Assert.Equal(4, Items(iterator.Next).Count(feature => WallSurface.TryFrom(feature) != null));
    }
}
