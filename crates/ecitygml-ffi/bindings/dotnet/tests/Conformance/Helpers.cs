using Xunit;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).</summary>
internal static class ConformanceHelpers
{
    /// <summary>The tolerance of floating point comparisons in the case lists.</summary>
    private const double Tolerance = 1e-6;

    /// <summary>Reads `tests/fixtures/&lt;dataset&gt;/&lt;file&gt;`.</summary>
    public static CityModel ReadFixture(string dataset, string file) => Read($"{dataset}/{file}");

    public static void AssertClose(double expected, double actual) =>
        Assert.True(Math.Abs(actual - expected) <= Tolerance, $"{actual} is not within {Tolerance} of {expected}");

    /// <summary>The city model's first building.</summary>
    public static Building FirstBuilding(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(Building.TryFrom).First(b => b != null)!;

    /// <summary>The building's boundaries, as features.</summary>
    public static List<AbstractFeatureKindRef> Boundaries(Building building) =>
        Items(building.Boundaries().Next).Select(p => AbstractFeatureKindRef.FromSpaceBoundary(p.Object()!)).ToList();

    /// <summary>The first of a feature's names (`Names()`).</summary>
    public static string FirstName(CodeIterator names) => Str(Items(names.Next).First().Value());
}
