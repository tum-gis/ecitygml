// The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.
#include "conformance/conformance.h"

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractSurfacePropertyIterator.h"
#include "BoundingShape.h"
#include "Bridge.h"
#include "BridgeFunctionValueIterator.h"
#include "BridgePartPropertyIterator.h"
#include "BridgeUsageValueIterator.h"
#include "CitygmlFormat.h"
#include "DirectPosition.h"
#include "Envelope.h"
#include "ExternalReferenceIterator.h"
#include "FeatureType.h"
#include "GenericAttributeKindIterator.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "HeightIterator.h"
#include "Id.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "OccupancyIterator.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"

#define BRIDGE FIXTURE("kit-bruecke/Modellbahnbruecke-LoD2-V03__v3.gml")
#define BRIDGE_ID "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"

/// The most features the fixture has.
#define MAX_FEATURES 32

void setUp(void) {}
void tearDown(void) {}

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    TEST_ASSERT_NOT_NULL(position);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
}

/// The feature types of `iter_features`, into `out`; returns their number.
static size_t feature_types(const CityModel *city_model, FeatureType *out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    return len;
}

/// The city model's bridge; it borrows from the model.
static const Bridge *bridge(const CityModel *city_model) {
    const Bridge *found = NULL;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while (found == NULL && (feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        found = ecitygml_Bridge_try_from(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    TEST_ASSERT_NOT_NULL(found);
    return found;
}

static void test_bridge_city_model(void) {
    CityModel *city_model = read(BRIDGE);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(457644.585, 5439126.455, 109.0, ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(457708.084, 5439157.169, 124.3, ecitygml_Envelope_upper_corner(envelope));
    FeatureType expected[19] = {FeatureType_CityModel, FeatureType_Bridge, FeatureType_Appearance};
    for (size_t i = 3; i < 6; i++) expected[i] = FeatureType_ParameterizedTexture;
    for (size_t i = 6; i < 8; i++) expected[i] = FeatureType_BridgeInstallation;
    for (size_t i = 8; i < 19; i++) expected[i] = FeatureType_BridgeConstructiveElement;
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(19, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, types, 19);
    size_t objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        objects++;
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    TEST_ASSERT_EQUAL_size_t(14, objects);
    ecitygml_CityModel_destroy(city_model);
}

static void test_bridge_attributes(void) {
    CityModel *city_model = read(BRIDGE);
    const Bridge *b = bridge(city_model);
    ASSERT_STR(BRIDGE_ID, ecitygml_Id_as_str(ecitygml_Bridge_feature_id(b)));
    CodeIterator *names = ecitygml_Bridge_names(b);
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    TEST_ASSERT_NULL(ecitygml_Bridge_class(b));
    BridgeFunctionValueIterator *functions = ecitygml_Bridge_functions(b);
    TEST_ASSERT_NULL(ecitygml_BridgeFunctionValueIterator_next(functions));
    ecitygml_BridgeFunctionValueIterator_destroy(functions);
    BridgeUsageValueIterator *usages = ecitygml_Bridge_usages(b);
    TEST_ASSERT_NULL(ecitygml_BridgeUsageValueIterator_next(usages));
    ecitygml_BridgeUsageValueIterator_destroy(usages);
    BridgePartPropertyIterator *parts = ecitygml_Bridge_bridge_parts(b);
    TEST_ASSERT_NULL(ecitygml_BridgePartPropertyIterator_next(parts));
    ecitygml_BridgePartPropertyIterator_destroy(parts);
    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Bridge_boundaries(b);
    TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
    TEST_ASSERT_NULL(ecitygml_Bridge_date_of_construction(b));
    TEST_ASSERT_NULL(ecitygml_Bridge_creation_date(b));
    HeightIterator *heights = ecitygml_Bridge_heights(b);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ecitygml_HeightIterator_destroy(heights);
    OccupancyIterator *occupancies = ecitygml_Bridge_occupancies(b);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    ecitygml_OccupancyIterator_destroy(occupancies);
    GenericAttributeKindIterator *attributes = ecitygml_Bridge_generic_attributes(b);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    ExternalReferenceIterator *references = ecitygml_Bridge_external_references(b);
    TEST_ASSERT_NULL(ecitygml_ExternalReferenceIterator_next(references));
    ecitygml_ExternalReferenceIterator_destroy(references);
    ecitygml_CityModel_destroy(city_model);
}

static void test_bridge_geometry(void) {
    CityModel *city_model = read(BRIDGE);
    const Bridge *b = bridge(city_model);
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_Bridge_bounded_by(b));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(457645.136, 5439126.692, 115.3, ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(457707.533, 5439156.931, 116.2, ecitygml_Envelope_upper_corner(envelope));
    const MultiSurfaceProperty *property = ecitygml_Bridge_lod2_multi_surface(b);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_MultiSurfaceProperty_href(property));
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(property);
    TEST_ASSERT_NOT_NULL(multi_surface);
    AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
    size_t count = 0;
    while (ecitygml_AbstractSurfacePropertyIterator_next(members) != NULL) count++;
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_EQUAL_size_t(18, count);
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(795.4201811265907, area.ok);
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TriangleIterator *triangles =
        ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok));
    count = 0;
    while (ecitygml_TriangleIterator_next(triangles) != NULL) count++;
    ecitygml_TriangleIterator_destroy(triangles);
    TEST_ASSERT_EQUAL_size_t(60, count);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    ecitygml_Triangulation_destroy(triangulation.ok);
    TEST_ASSERT_NULL(ecitygml_Bridge_lod1_solid(b));
    TEST_ASSERT_NULL(ecitygml_Bridge_lod2_solid(b));
    TEST_ASSERT_NULL(ecitygml_Bridge_lod3_multi_surface(b));
    ecitygml_CityModel_destroy(city_model);
}

static void test_bridge_round_trip(void) {
    CityModel *city_model = read(BRIDGE);
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    GmlReader *reader = ecitygml_GmlReader_new(ecitygml_GmlWriter_data(writer), CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result written = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    ecitygml_GmlWriter_destroy(writer);
    TEST_ASSERT_TRUE(written.is_ok);
    FeatureType original[MAX_FEATURES];
    FeatureType read_back[MAX_FEATURES];
    size_t len = feature_types(city_model, original);
    TEST_ASSERT_EQUAL_size_t(len, feature_types(written.ok, read_back));
    TEST_ASSERT_EQUAL_INT_ARRAY(original, read_back, len);
    ASSERT_STR(BRIDGE_ID, ecitygml_Id_as_str(ecitygml_Bridge_feature_id(bridge(written.ok))));
    ecitygml_CityModel_destroy(written.ok);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_bridge_city_model);
    RUN_TEST(test_bridge_attributes);
    RUN_TEST(test_bridge_geometry);
    RUN_TEST(test_bridge_round_trip);
    return UNITY_END();
}
