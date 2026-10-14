#:project ../../Ecitygml.csproj
using System.Text;
using Ecitygml;

var path = args.Length > 0 ? args[0] : "model.gml";

// Parse the CityGML document into the in-memory city model
var pathBytes = Encoding.UTF8.GetBytes(path);
var cityModel = GmlReader.FromPath(pathBytes).Finish();

// Sum up the areas of the LOD2 multi-surfaces of all wall surfaces; other
// feature types and walls without an LOD2 multi-surface are skipped
var totalArea = 0.0;
var features = cityModel.IterFeatures();
while (features.Next() is { } feature)
{
    var wall = WallSurface.TryFrom(feature);
    var surface = wall?.Lod2MultiSurface()?.Object();
    if (surface != null)
    {
        totalArea += surface.Area3d();
    }
}

Console.WriteLine(FormattableString.Invariant(
    $"Total area of wall surfaces (LoD2): {totalArea:F3} m^2"));
