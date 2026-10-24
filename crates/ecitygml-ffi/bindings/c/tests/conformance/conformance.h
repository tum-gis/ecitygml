// Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).
#ifndef ECITYGML_C_CONFORMANCE_H
#define ECITYGML_C_CONFORMANCE_H

#include "test_helpers.h"

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "AbstractSpaceBoundaryProperty.h"
#include "AbstractSpaceBoundaryPropertyIterator.h"
#include "Building.h"
#include "Code.h"
#include "CodeIterator.h"

/// The tolerance of floating point comparisons in the case lists.
#define TOLERANCE 1e-6
#define ASSERT_CLOSE(expected, actual) TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, (expected), (actual))

/// The most boundaries a building of the fixtures has.
#define MAX_BOUNDARIES 17

/// The city model's first building; it borrows from the model.
static inline const Building *first_building(const CityModel *city_model) {
    const Building *building = NULL;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while (building == NULL && (feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        building = ecitygml_Building_try_from(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    TEST_ASSERT_NOT_NULL(building);
    return building;
}

/// The building's boundaries as features, into `out`; returns their number. Destroy them with
/// `destroy_features`.
static inline size_t boundaries(const Building *building, AbstractFeatureKindRef **out) {
    size_t len = 0;
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Building_boundaries(building);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_BOUNDARIES, len);
        out[len++] = ecitygml_AbstractFeatureKindRef_from_space_boundary(
            ecitygml_AbstractSpaceBoundaryProperty_object(property));
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);
    return len;
}

static inline void destroy_features(AbstractFeatureKindRef **features, size_t len) {
    for (size_t i = 0; i < len; i++) {
        ecitygml_AbstractFeatureKindRef_destroy(features[i]);
    }
}

/// The first of the names; takes the `names()` iterator and destroys it. The name borrows from the model.
static inline DiplomatStringView first_name(CodeIterator *names) {
    const Code *name = ecitygml_CodeIterator_next(names);
    TEST_ASSERT_NOT_NULL(name);
    DiplomatStringView value = ecitygml_Code_value(name);
    ecitygml_CodeIterator_destroy(names);
    return value;
}

#endif
