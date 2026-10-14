#include <stdio.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "WallSurface.h"

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

    // Sum up the areas of the LOD2 multi-surfaces of all wall surfaces;
    // other feature types, walls without an LOD2 multi-surface, and areas
    // that cannot be computed are skipped
    double total_area = 0.0;
    AbstractFeatureKindRefIterator *features =
        ecitygml_CityModel_iter_features(city_model.ok);
    for (;;) {
        AbstractFeatureKindRef *feature =
            ecitygml_AbstractFeatureKindRefIterator_next(features);
        if (!feature) break;
        // The wall borrows from the city model, so it stays valid after
        // its feature is destroyed
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
        if (!wall) continue;
        const MultiSurfaceProperty *surface_property =
            ecitygml_WallSurface_lod2_multi_surface(wall);
        if (!surface_property) continue;
        const MultiSurface *surface =
            ecitygml_MultiSurfaceProperty_object(surface_property);
        if (!surface) continue;
        ecitygml_MultiSurface_area_3d_result area =
            ecitygml_MultiSurface_area_3d(surface);
        if (area.is_ok) {
            total_area += area.ok;
        } else {
            ecitygml_Error_destroy(area.err);
        }
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    ecitygml_CityModel_destroy(city_model.ok);

    printf("Total area of wall surfaces (LoD2): %.3f m^2\n", total_area);
    return 0;
}
