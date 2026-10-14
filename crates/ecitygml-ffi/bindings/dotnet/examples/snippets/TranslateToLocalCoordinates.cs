#:project ../../Ecitygml.csproj
using System.Globalization;
using System.Text;
using Ecitygml;

var inputPath = args.Length > 0 ? args[0] : "model.gml";
var outputPath = args.Length > 1 ? args[1] : "model_local.gml";

// Parse the CityGML document, keeping the envelopes of the objects as given
// in the file instead of recomputing them from their geometry
var reader = GmlReader.FromPath(Encoding.UTF8.GetBytes(inputPath));
reader.WithRebuildObjectBounds(false);
var cityModel = reader.Finish();

// Move the center of the city model's envelope to the origin
var envelope = cityModel.BoundedBy()?.Envelope()
    ?? throw new InvalidOperationException("the city model has no envelope");
var center = envelope.Center();
var offset = new Vector3 { X = -center.X(), Y = -center.Y(), Z = -center.Z() };
cityModel.ApplyTranslation(offset);

// Write the translated city model as a CityGML document
var outputBytes = Encoding.UTF8.GetBytes(outputPath);
GmlWriter.FromPath(outputBytes).Finish(cityModel);

Console.WriteLine(string.Format(
    CultureInfo.InvariantCulture,
    "Translated the city model by ({0:F3}, {1:F3}, {2:F3}) "
        + "to local coordinates",
    offset.X, offset.Y, offset.Z));
