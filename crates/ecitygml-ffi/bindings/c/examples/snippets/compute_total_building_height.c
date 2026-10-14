#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "AbstractCityObjectKind.h"
#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectProperty.h"
#include "AbstractCityObjectPropertyIterator.h"
#include "AbstractFeatureKindRef.h"
#include "Building.h"
#include "CityModel.h"
#include "ElevationReferenceValue.h"
#include "Error.h"
#include "GmlReader.h"
#include "Height.h"
#include "HeightIterator.h"
#include "HeightStatusValue.h"
#include "Length.h"

// Compares a string borrowed from the bindings with a C string
static bool equals(DiplomatStringView text, const char *expected) {
    return text.len == strlen(expected) &&
           memcmp(text.data, expected, text.len) == 0;
}

// Whether the height is measured from the lowest ground point to the top
// of construction and given in meters
static bool is_measured_total_height(const Height *height) {
    const ElevationReferenceValue *low =
        ecitygml_Height_low_reference(height);
    const ElevationReferenceValue *high =
        ecitygml_Height_high_reference(height);
    const Length *length = ecitygml_Height_length(height);
    return equals(ecitygml_ElevationReferenceValue_value(low),
                  "lowestGroundPoint") &&
           equals(ecitygml_ElevationReferenceValue_value(high),
                  "topOfConstruction") &&
           ecitygml_Height_status(height) == HeightStatusValue_Measured &&
           equals(ecitygml_Length_uom(length), "urn:adv:uom:m");
}

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

    // Sum up the measured heights of the top-level buildings
    double total_height = 0.0;
    AbstractCityObjectPropertyIterator *members =
        ecitygml_CityModel_city_object_members(city_model.ok);
    for (;;) {
        const AbstractCityObjectProperty *member =
            ecitygml_AbstractCityObjectPropertyIterator_next(members);
        if (!member) break;
        const AbstractCityObjectKind *city_object =
            ecitygml_AbstractCityObjectProperty_object(member);
        if (!city_object) continue;
        AbstractCityObjectKindRef *city_object_ref =
            ecitygml_AbstractCityObjectKindRef_from_city_object(city_object);
        AbstractFeatureKindRef *feature =
            ecitygml_AbstractFeatureKindRef_from_city_object(city_object_ref);
        const Building *building = ecitygml_Building_try_from(feature);
        if (building) {
            HeightIterator *heights = ecitygml_Building_heights(building);
            for (;;) {
                const Height *height = ecitygml_HeightIterator_next(heights);
                if (!height) break;
                if (is_measured_total_height(height)) {
                    const Length *length = ecitygml_Height_length(height);
                    total_height += ecitygml_Length_value(length);
                }
            }
            ecitygml_HeightIterator_destroy(heights);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
        ecitygml_AbstractCityObjectKindRef_destroy(city_object_ref);
    }
    ecitygml_AbstractCityObjectPropertyIterator_destroy(members);
    ecitygml_CityModel_destroy(city_model.ok);

    printf("Total measured height of buildings: %.3f m\n", total_height);
    return 0;
}
