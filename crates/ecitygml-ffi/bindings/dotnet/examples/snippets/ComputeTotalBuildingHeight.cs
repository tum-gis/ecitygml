#:project ../../Ecitygml.csproj
using System.Text;
using Ecitygml;
using Ecitygml.Diplomat;

// Decodes a UTF-8 string borrowed from the bindings
static string Text(DiplomatBorrowedSpan<byte> text) =>
    Encoding.UTF8.GetString(text.Clone());

var path = args.Length > 0 ? args[0] : "model.gml";

// Parse the CityGML document into the in-memory city model
var pathBytes = Encoding.UTF8.GetBytes(path);
var cityModel = GmlReader.FromPath(pathBytes).Finish();

// Sum up the measured heights of the top-level buildings; only heights from
// the lowest ground point to the top of construction given in meters are
// taken into account
var totalHeight = 0.0;
var members = cityModel.CityObjectMembers();
while (members.Next() is { } member)
{
    if (member.Object() is not { } cityObject) continue;
    var cityObjectRef = AbstractCityObjectKindRef.FromCityObject(cityObject);
    var feature = AbstractFeatureKindRef.FromCityObject(cityObjectRef);
    if (Building.TryFrom(feature) is not { } building) continue;
    var heights = building.Heights();
    while (heights.Next() is { } height)
    {
        if (Text(height.LowReference().Value()) == "lowestGroundPoint"
            && Text(height.HighReference().Value()) == "topOfConstruction"
            && height.Status() == HeightStatusValue.Measured
            && Text(height.Length().Uom()) == "urn:adv:uom:m")
        {
            totalHeight += height.Length().Value();
        }
    }
}

Console.WriteLine(FormattableString.Invariant(
    $"Total measured height of buildings: {totalHeight:F3} m"));
