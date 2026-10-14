#:project ../../Ecitygml.csproj
using System.Text;
using Ecitygml;

var path = args.Length > 0 ? args[0] : "model.gml";

// Parse the CityGML document into the in-memory city model
var pathBytes = Encoding.UTF8.GetBytes(path);
var cityModel = GmlReader.FromPath(pathBytes).Finish();

// Traverse all features and keep only those that are traffic spaces,
// using a type-safe conversion that skips all other feature types
var trafficSpaces = new List<TrafficSpace>();
var features = cityModel.IterFeatures();
while (features.Next() is { } feature)
{
    if (TrafficSpace.TryFrom(feature) is { } space)
    {
        trafficSpaces.Add(space);
    }
}

// Compute the volumes of the LOD2 solids and sum them up; spaces
// without an LOD2 solid are skipped
var total = trafficSpaces
    .Select(space => space.Lod2Solid()?.Object())
    .OfType<Solid>()
    .Sum(solid => solid.Volume3d());

Console.WriteLine(FormattableString.Invariant(
    $"Total volume of traffic spaces (LoD2): {total:F3} m^3"));
