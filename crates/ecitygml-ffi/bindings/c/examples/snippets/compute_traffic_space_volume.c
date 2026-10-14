#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "TrafficSpace.h"

int main(int argc, char **argv) {
    const char *path = argc > 1 ? argv[1] : "model.gml";

    // Parse the CityGML document into the in-memory city model
    DiplomatStringView path_view = {path, strlen(path)};
    ecitygml_GmlReader_from_path_result reader =
        ecitygml_GmlReader_from_path(path_view);
    if (!reader.is_ok) {
        ecitygml_Error_destroy(reader.err);
        return 1;
    }
    ecitygml_GmlReader_finish_result city_model =
        ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!city_model.is_ok) {
        ecitygml_Error_destroy(city_model.err);
        return 1;
    }

    // Traverse all features and keep only those that are traffic
    // spaces; they borrow from the city model, so they stay valid
    // after their features are destroyed
    const TrafficSpace **traffic_spaces = NULL;
    size_t traffic_spaces_len = 0;
    AbstractFeatureKindRefIterator *features =
        ecitygml_CityModel_iter_features(city_model.ok);
    for (;;) {
        AbstractFeatureKindRef *feature =
            ecitygml_AbstractFeatureKindRefIterator_next(features);
        if (!feature) break;
        const TrafficSpace *space =
            ecitygml_TrafficSpace_try_from(feature);
        if (space) {
            size_t len = traffic_spaces_len + 1;
            const TrafficSpace **grown =
                realloc(traffic_spaces, len * sizeof *traffic_spaces);
            if (!grown) return 1;
            traffic_spaces = grown;
            traffic_spaces[traffic_spaces_len++] = space;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);

    // Compute the volumes of the LOD2 solids and sum them up; spaces
    // without an LOD2 solid, or whose volume cannot be computed, are
    // skipped
    double total = 0.0;
    for (size_t i = 0; i < traffic_spaces_len; i++) {
        const SolidProperty *solid_property =
            ecitygml_TrafficSpace_lod2_solid(traffic_spaces[i]);
        if (!solid_property) continue;
        const Solid *solid = ecitygml_SolidProperty_object(solid_property);
        if (!solid) continue;
        ecitygml_Solid_volume_3d_result volume =
            ecitygml_Solid_volume_3d(solid);
        if (volume.is_ok) {
            total += volume.ok;
        } else {
            ecitygml_Error_destroy(volume.err);
        }
    }
    free(traffic_spaces);
    ecitygml_CityModel_destroy(city_model.ok);

    printf("Total volume of traffic spaces (LoD2): %.3f m^3\n", total);
    return 0;
}
