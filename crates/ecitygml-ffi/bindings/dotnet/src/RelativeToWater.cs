namespace Envis.Ecitygml;

public enum RelativeToWater : int
{
    EntirelyAboveWaterSurface = 0,
    SubstantiallyAboveWaterSurface = 1,
    SubstantiallyAboveAndBelowWaterSurface = 2,
    SubstantiallyBelowWaterSurface = 3,
    EntirelyBelowWaterSurface = 4,
    TemporarilyAboveAndBelowWaterSurface = 5,
}