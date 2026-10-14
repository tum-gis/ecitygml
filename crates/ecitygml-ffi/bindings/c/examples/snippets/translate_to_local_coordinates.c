#include <stdio.h>
#include <string.h>

#include "BoundingShape.h"
#include "CityModel.h"
#include "DirectPosition.h"
#include "Envelope.h"
#include "Error.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "Vector3.h"

int main(int argc, char **argv) {
    const char *input_path = argc > 1 ? argv[1] : "model.gml";
    const char *output_path = argc > 2 ? argv[2] : "model_local.gml";

    // Parse the CityGML document, keeping the envelopes of the objects as
    // given in the file instead of recomputing them from their geometry
    DiplomatStringView input_view = {input_path, strlen(input_path)};
    ecitygml_GmlReader_from_path_result reader =
        ecitygml_GmlReader_from_path(input_view);
    if (!reader.is_ok) {
        ecitygml_Error_destroy(reader.err);
        return 1;
    }
    ecitygml_GmlReader_with_rebuild_object_bounds(reader.ok, false);
    ecitygml_GmlReader_finish_result city_model =
        ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!city_model.is_ok) {
        ecitygml_Error_destroy(city_model.err);
        return 1;
    }

    // Move the center of the city model's envelope to the origin
    const BoundingShape *bounding_shape =
        ecitygml_CityModel_bounded_by(city_model.ok);
    const Envelope *envelope =
        bounding_shape ? ecitygml_BoundingShape_envelope(bounding_shape) : NULL;
    if (!envelope) {
        ecitygml_CityModel_destroy(city_model.ok);
        return 1;
    }
    DirectPosition *center = ecitygml_Envelope_center(envelope);
    Vector3 offset = {
        -ecitygml_DirectPosition_x(center),
        -ecitygml_DirectPosition_y(center),
        -ecitygml_DirectPosition_z(center),
    };
    ecitygml_DirectPosition_destroy(center);
    ecitygml_CityModel_apply_translation(city_model.ok, offset);

    // Write the translated city model as a CityGML document
    DiplomatStringView output_view = {output_path, strlen(output_path)};
    ecitygml_GmlWriter_from_path_result writer =
        ecitygml_GmlWriter_from_path(output_view);
    if (!writer.is_ok) {
        ecitygml_Error_destroy(writer.err);
        ecitygml_CityModel_destroy(city_model.ok);
        return 1;
    }
    ecitygml_GmlWriter_finish_result written =
        ecitygml_GmlWriter_finish(writer.ok, city_model.ok);
    ecitygml_GmlWriter_destroy(writer.ok);
    ecitygml_CityModel_destroy(city_model.ok);
    if (!written.is_ok) {
        ecitygml_Error_destroy(written.err);
        return 1;
    }

    printf("Translated the city model by (%.3f, %.3f, %.3f) "
           "to local coordinates\n",
           offset.x, offset.y, offset.z);
    return 0;
}
