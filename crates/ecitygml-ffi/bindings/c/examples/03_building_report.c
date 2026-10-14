// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
// with their doors and windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are NULL pointers (or `..._result` structs with `is_ok` false) when absent;
//   lists are iterators whose `next` returns NULL at the end and which must be destroyed.
// - Code-list values (class, function, ...) are wrappers with `value` (and `code`).
// - Properties referencing other objects (e.g. a building's boundaries) have `object` and `href`;
//   `object` is NULL if the property only references an object elsewhere via `xlink:href`.
// - Abstract types are converted with `try_from`, e.g. a generic attribute to a `MeasureAttribute`,
//   or a boundary (via `ecitygml_AbstractFeatureKindRef_from_space_boundary`) to a `WallSurface`.
//
// Built by bindings/c/CMakeLists.txt (`mise run build:bindings:c`), which also runs it as a test.
//
// Usage: 03_building_report path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       Name: AC14-FZK-Haus
//       Class: 1000
//       ...
//       Boundaries:
//         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//         ...

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "AbstractFillingSurfaceKind.h"
#include "AbstractFillingSurfaceProperty.h"
#include "AbstractFillingSurfacePropertyIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSpaceBoundaryProperty.h"
#include "AbstractSpaceBoundaryPropertyIterator.h"
#include "Building.h"
#include "BuildingClassValue.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingUsageValue.h"
#include "BuildingUsageValueIterator.h"
#include "CityModel.h"
#include "Code.h"
#include "CodeIterator.h"
#include "Date.h"
#include "DoubleAttribute.h"
#include "ElevationReferenceValue.h"
#include "Error.h"
#include "FeatureType.h"
#include "GenericAttributeKind.h"
#include "GenericAttributeKindIterator.h"
#include "GmlReader.h"
#include "GroundSurface.h"
#include "HRef.h"
#include "Height.h"
#include "HeightIterator.h"
#include "Id.h"
#include "IntAttribute.h"
#include "Length.h"
#include "Measure.h"
#include "MeasureAttribute.h"
#include "RoofSurface.h"
#include "RoofTypeValue.h"
#include "StringAttribute.h"
#include "WallSurface.h"

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

static void print_view(DiplomatStringView text) {
    printf("%.*s", (int)text.len, text.data);
}

// Prints ", " before every list value except the first.
static void print_separator(size_t index) {
    if (index > 0) {
        printf(", ");
    }
}

// Ends a list's line, with "-" if it had no values.
static void print_dash_if_none(size_t count) {
    printf(count == 0 ? "-\n" : "\n");
}

// Prints a feature type's name and an id, e.g. "WallSurface GML_...".
static void print_type_and_id(FeatureType type, const Id *id) {
    DiplomatWrite *name = diplomat_buffer_write_create(32);
    ecitygml_FeatureType_to_string(type, name);
    printf("%.*s ", (int)diplomat_buffer_write_len(name), diplomat_buffer_write_get_bytes(name));
    diplomat_buffer_write_destroy(name);
    print_view(ecitygml_Id_as_str(id));
    printf("\n");
}

// Prints the doors and windows of a wall, roof or ground surface, then destroys the iterator.
static void print_filling_surfaces(AbstractFillingSurfacePropertyIterator *fillings) {
    const AbstractFillingSurfaceProperty *property;
    while ((property = ecitygml_AbstractFillingSurfacePropertyIterator_next(fillings)) != NULL) {
        const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
        if (filling) {
            printf("      ");
            print_type_and_id(ecitygml_AbstractFillingSurfaceKind_feature_type(filling),
                              ecitygml_AbstractFillingSurfaceKind_feature_id(filling));
        }
    }
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(fillings);
}

// Prints the value of a generic attribute: string, integer, double or measure (value and unit).
static void print_generic_attribute_value(const GenericAttributeKind *attribute) {
    const StringAttribute *string = ecitygml_GenericAttributeKind_as_string(attribute);
    const IntAttribute *integer = ecitygml_GenericAttributeKind_as_int(attribute);
    const DoubleAttribute *real = ecitygml_GenericAttributeKind_as_double(attribute);
    const MeasureAttribute *measure = ecitygml_MeasureAttribute_try_from(attribute);
    if (string) {
        print_view(ecitygml_StringAttribute_value(string));
    } else if (integer) {
        printf("%" PRId64, ecitygml_IntAttribute_value(integer));
    } else if (real) {
        printf("%.3f", ecitygml_DoubleAttribute_value(real));
    } else if (measure) {
        const Measure *value = ecitygml_MeasureAttribute_value(measure);
        printf("%.3f ", ecitygml_Measure_value(value));
        print_view(ecitygml_Measure_uom(value));
    } else {
        printf("(not shown)");  // e.g. a generic attribute set, which holds further attributes
    }
}

static void print_building(const Building *building) {
    printf("Building ");
    print_view(ecitygml_Id_as_str(ecitygml_Building_feature_id(building)));

    printf("\n");

    // Lists are iterators: print the values comma-separated ("-" if there are none), then destroy
    // the iterator.
    printf("  Name: ");
    CodeIterator *names = ecitygml_Building_names(building);
    const Code *name;
    size_t name_count = 0;
    while ((name = ecitygml_CodeIterator_next(names)) != NULL) {
        print_separator(name_count++);
        print_view(ecitygml_Code_value(name));
    }
    ecitygml_CodeIterator_destroy(names);
    print_dash_if_none(name_count);

    // Optional single values are pointers, NULL when absent.
    printf("  Class: ");
    const BuildingClassValue *class_value = ecitygml_Building_class(building);
    if (class_value) {
        print_view(ecitygml_BuildingClassValue_value(class_value));
        printf("\n");
    } else {
        printf("-\n");
    }

    printf("  Functions: ");
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(building);
    const BuildingFunctionValue *function;
    size_t function_count = 0;
    while ((function = ecitygml_BuildingFunctionValueIterator_next(functions)) != NULL) {
        print_separator(function_count++);
        print_view(ecitygml_BuildingFunctionValue_value(function));
    }
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    print_dash_if_none(function_count);

    printf("  Usages: ");
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(building);
    const BuildingUsageValue *usage;
    size_t usage_count = 0;
    while ((usage = ecitygml_BuildingUsageValueIterator_next(usages)) != NULL) {
        print_separator(usage_count++);
        print_view(ecitygml_BuildingUsageValue_value(usage));
    }
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    print_dash_if_none(usage_count);

    printf("  Roof type: ");
    const RoofTypeValue *roof_type = ecitygml_Building_roof_type(building);
    if (roof_type) {
        print_view(ecitygml_RoofTypeValue_value(roof_type));
        printf("\n");
    } else {
        printf("-\n");
    }

    // Optional numbers come as `..._result` structs: `ok` is only set if `is_ok`.
    ecitygml_Building_storeys_above_ground_result above = ecitygml_Building_storeys_above_ground(building);
    if (above.is_ok) {
        printf("  Storeys above ground: %" PRId64 "\n", above.ok);
    } else {
        printf("  Storeys above ground: -\n");
    }
    ecitygml_Building_storeys_below_ground_result below = ecitygml_Building_storeys_below_ground(building);
    if (below.is_ok) {
        printf("  Storeys below ground: %" PRId64 "\n", below.ok);
    } else {
        printf("  Storeys below ground: -\n");
    }

    const Date *date = ecitygml_Building_date_of_construction(building);
    if (date) {
        printf("  Date of construction: %04d-%02u-%02u\n", ecitygml_Date_year(date), ecitygml_Date_month(date),
               ecitygml_Date_day(date));
    } else {
        printf("  Date of construction: -\n");
    }

    printf("  Heights:\n");
    HeightIterator *heights = ecitygml_Building_heights(building);
    const Height *height;
    while ((height = ecitygml_HeightIterator_next(heights)) != NULL) {
        const Length *length = ecitygml_Height_length(height);
        printf("    %.3f ", ecitygml_Length_value(length));
        print_view(ecitygml_Length_uom(length));
        printf(" (");
        print_view(ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
        printf(" to ");
        print_view(ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
        printf(")\n");
    }
    ecitygml_HeightIterator_destroy(heights);

    printf("  Generic attributes:\n");
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(building);
    const GenericAttributeKind *attribute;
    while ((attribute = ecitygml_GenericAttributeKindIterator_next(attributes)) != NULL) {
        printf("    ");
        print_view(ecitygml_GenericAttributeKind_name(attribute));
        printf(": ");
        print_generic_attribute_value(attribute);
        printf("\n");
    }
    ecitygml_GenericAttributeKindIterator_destroy(attributes);

    // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    // and ground surfaces can have filling surfaces: doors and windows.
    printf("  Boundaries:\n");
    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Building_boundaries(building);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries)) != NULL) {
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        if (boundary == NULL) {
            DiplomatWrite *href = diplomat_buffer_write_create(64);
            ecitygml_HRef_to_string(ecitygml_AbstractSpaceBoundaryProperty_href(property), href);
            printf("    (reference to %.*s)\n", (int)diplomat_buffer_write_len(href), diplomat_buffer_write_get_bytes(href));
            diplomat_buffer_write_destroy(href);
            continue;
        }
        printf("    ");
        print_type_and_id(ecitygml_AbstractSpaceBoundaryKind_feature_type(boundary),
                          ecitygml_AbstractSpaceBoundaryKind_feature_id(boundary));
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary);
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(feature);
        if (wall) {
            print_filling_surfaces(ecitygml_WallSurface_filling_surfaces(wall));
        } else if (roof) {
            print_filling_surfaces(ecitygml_RoofSurface_filling_surfaces(roof));
        } else if (ground) {
            print_filling_surfaces(ecitygml_GroundSurface_filling_surfaces(ground));
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: 03_building_report path/to/model.gml\n");
        return 2;
    }
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){argv[1], strlen(argv[1])});
    if (!reader.is_ok) {
        return print_error(reader.err);
    }
    ecitygml_GmlReader_finish_result result = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!result.is_ok) {
        return print_error(result.err);
    }
    CityModel *city_model = result.ok;

    // The buildings borrow from the city model, so they stay valid after their feature is destroyed.
    size_t building_count = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const Building *building = ecitygml_Building_try_from(feature);
        if (building) {
            if (building_count++ > 0) {
                printf("\n");
            }
            print_building(building);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    if (building_count == 0) {
        printf("No buildings.\n");
    }

    ecitygml_CityModel_destroy(city_model);
    return 0;
}
