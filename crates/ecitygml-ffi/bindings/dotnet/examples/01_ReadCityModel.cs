// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain, `.gml.gz` or
// `.gml.zst`) into a `CityModel`, which owns all features (see `Common.ReadCityModel`). Errors, e.g. a missing file
// or invalid XML, are thrown as `ErrorException`, whose `Inner` is the ecitygml `Error`. Absent values are C#
// nullable types; objects borrowed from the city model keep it alive, and the garbage collector frees the native
// memory.
//
// Usage: dotnet run --project examples -- 01_read_city_model path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     City object members: 1
//     City objects (at all depths): 8
//     Envelope:
//       lower corner: 457842.000, 5439083.000, 111.800
//       upper corner: 457854.000, 5439093.000, 118.318
//       size: 12.000 x 10.000 x 6.518

using static Ecitygml.Examples.Common;

namespace Ecitygml.Examples;

public static class ReadCityModel
{
    public static int Run(string[] args)
    {
        if (args.Length != 1)
        {
            Console.Error.WriteLine("usage: 01_read_city_model path/to/model.gml");
            return 2;
        }
        var cityModel = Common.ReadCityModel(args[0]);
        if (cityModel == null)
        {
            return 1;
        }

        // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces, doors and
        // windows are city objects too, which `IterCityObjects()` visits as well.
        Console.WriteLine($"City object members: {cityModel.CityObjectsLen()}");
        Console.WriteLine($"City objects (at all depths): {Items(cityModel.IterCityObjects().Next).Count()}");

        // `BoundedBy()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both are optional (null
        // when absent), as in the file.
        var envelope = cityModel.BoundedBy()?.Envelope();
        if (envelope == null)
        {
            Console.WriteLine("Envelope: none");
            return 0;
        }
        var (lower, upper) = (envelope.LowerCorner(), envelope.UpperCorner());
        Console.WriteLine("Envelope:");
        Console.WriteLine($"  lower corner: {Fixed3(lower.X())}, {Fixed3(lower.Y())}, {Fixed3(lower.Z())}");
        Console.WriteLine($"  upper corner: {Fixed3(upper.X())}, {Fixed3(upper.Y())}, {Fixed3(upper.Z())}");
        Console.WriteLine($"  size: {Fixed3(envelope.SizeX())} x {Fixed3(envelope.SizeY())} x {Fixed3(envelope.SizeZ())}");
        return 0;
    }
}
