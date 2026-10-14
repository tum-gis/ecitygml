#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/Vector3.hpp>

#include <cstdio>

int main(int argc, char** argv) {
    const char* input_path = argc > 1 ? argv[1] : "model.gml";
    const char* output_path = argc > 2 ? argv[2] : "model_local.gml";

    // Parse the CityGML document, keeping the envelopes of the objects as
    // given in the file instead of recomputing them from their geometry
    auto reader = ecitygml::GmlReader::from_path(input_path);
    if (!reader.is_ok()) return 1;
    auto reader_ok = std::move(reader).ok().value();
    reader_ok->with_rebuild_object_bounds(false);
    auto city_model = reader_ok->finish();
    if (!city_model.is_ok()) return 1;
    auto model = std::move(city_model).ok().value();

    // Move the center of the city model's envelope to the origin
    const auto* bounding_shape = model->bounded_by();
    if (!bounding_shape) return 1;
    const auto* envelope = bounding_shape->envelope();
    if (!envelope) return 1;
    auto center = envelope->center();
    const ecitygml::Vector3 offset{-center->x(), -center->y(), -center->z()};
    model->apply_translation(offset);

    // Write the translated city model as a CityGML document
    auto writer = ecitygml::GmlWriter::from_path(output_path);
    if (!writer.is_ok()) return 1;
    auto written = std::move(writer).ok().value()->finish(*model);
    if (!written.is_ok()) return 1;

    std::printf(
        "Translated the city model by (%.3f, %.3f, %.3f) "
        "to local coordinates\n",
        offset.x, offset.y, offset.z);
}
