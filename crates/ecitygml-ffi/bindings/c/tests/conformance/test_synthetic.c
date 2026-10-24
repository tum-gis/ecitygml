// The cases of crates/ecitygml/tests/conformance/synthetic.md.
#include "conformance/conformance.h"

#include <math.h>
#include <stdlib.h>

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractCurveKind.h"
#include "AbstractCurveProperty.h"
#include "AbstractCurvePropertyIterator.h"
#include "AbstractFillingSurfaceKind.h"
#include "AbstractFillingSurfaceProperty.h"
#include "AbstractFillingSurfacePropertyIterator.h"
#include "AbstractGeometryKind.h"
#include "AbstractGeometryProperty.h"
#include "AbstractRingKind.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSurfaceKind.h"
#include "AbstractSurfacePatchKindIterator.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "Bridge.h"
#include "BridgeClassValue.h"
#include "BridgeFunctionValue.h"
#include "BridgeFunctionValueIterator.h"
#include "BridgePart.h"
#include "BridgePartProperty.h"
#include "BridgePartPropertyIterator.h"
#include "BridgeUsageValue.h"
#include "BridgeUsageValueIterator.h"
#include "CityFurniture.h"
#include "CityFurnitureClassValue.h"
#include "CityFurnitureFunctionValue.h"
#include "CityFurnitureFunctionValueIterator.h"
#include "CityFurnitureUsageValue.h"
#include "CityFurnitureUsageValueIterator.h"
#include "CityObjectRelation.h"
#include "CityObjectRelationProperty.h"
#include "CityObjectRelationPropertyIterator.h"
#include "CitygmlFormat.h"
#include "Date.h"
#include "DirectPosition.h"
#include "DirectPositionIterator.h"
#include "DoubleAttribute.h"
#include "Envelope.h"
#include "Error.h"
#include "ErrorKind.h"
#include "FeatureType.h"
#include "GenericAttributeKind.h"
#include "GenericAttributeKindIterator.h"
#include "GenericAttributeSet.h"
#include "GeometryType.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "GranularityValue.h"
#include "HRef.h"
#include "HeightIterator.h"
#include "Id.h"
#include "ImplicitGeometry.h"
#include "ImplicitGeometryProperty.h"
#include "IntAttribute.h"
#include "IntervalValue.h"
#include "LineString.h"
#include "LinearRing.h"
#include "Measure.h"
#include "MimeTypeValue.h"
#include "MultiCurve.h"
#include "MultiCurveProperty.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Occupancy.h"
#include "OccupancyIterator.h"
#include "OccupantTypeValue.h"
#include "PlantCover.h"
#include "PlantCoverClassValue.h"
#include "PlantCoverFunctionValueIterator.h"
#include "PlantCoverUsageValueIterator.h"
#include "Point.h"
#include "PointProperty.h"
#include "Polygon.h"
#include "Reference.h"
#include "RelationTypeValue.h"
#include "RelativeToWater.h"
#include "RoofSurface.h"
#include "Section.h"
#include "SolitaryVegetationObject.h"
#include "SolitaryVegetationObjectClassValue.h"
#include "SolitaryVegetationObjectFunctionValue.h"
#include "SolitaryVegetationObjectFunctionValueIterator.h"
#include "SolitaryVegetationObjectUsageValue.h"
#include "SolitaryVegetationObjectUsageValueIterator.h"
#include "SpeciesValue.h"
#include "StringAttribute.h"
#include "Surface.h"
#include "TrafficDirectionValue.h"
#include "TrafficSpace.h"
#include "TrafficSpaceProperty.h"
#include "TrafficSpacePropertyIterator.h"
#include "TransformationMatrix4x4.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"
#include "TriangulationSkippedIterator.h"
#include "Tunnel.h"
#include "TunnelClassValue.h"
#include "TunnelFunctionValue.h"
#include "TunnelFunctionValueIterator.h"
#include "TunnelPart.h"
#include "TunnelPartProperty.h"
#include "TunnelPartPropertyIterator.h"
#include "TunnelUsageValue.h"
#include "TunnelUsageValueIterator.h"

#define SYNTHETIC(file) FIXTURE("synthetic/" file)
/// The longest href or id of the files, plus the terminating zero.
#define MAX_STRING 64
#define MAX_FEATURES 8

void setUp(void) {}
void tearDown(void) {}

/// Declares `count_<T>`: the number of items of a `<T>Iterator`, which it destroys.
#define DEFINE_COUNT(T)                                                       \
    static size_t count_##T(T##Iterator *iterator) {                          \
        size_t n = 0;                                                         \
        while (ecitygml_##T##Iterator_next(iterator) != NULL) n++;            \
        ecitygml_##T##Iterator_destroy(iterator);                             \
        return n;                                                             \
    }

DEFINE_COUNT(Height)
DEFINE_COUNT(BridgeFunctionValue)
DEFINE_COUNT(PlantCoverFunctionValue)
DEFINE_COUNT(PlantCoverUsageValue)
DEFINE_COUNT(AbstractSurfaceProperty)
DEFINE_COUNT(AbstractSurfacePatchKind)
DEFINE_COUNT(DirectPosition)
DEFINE_COUNT(Triangle)

/// Asserts the `value`s of a `<T>Iterator` (which it destroys): the strings that follow, in order.
#define ASSERT_VALUES(T, iterator, ...)                                                    \
    do {                                                                                   \
        const char *values_[] = {__VA_ARGS__};                                           \
        T##Iterator *iterator_ = (iterator);                                               \
        for (size_t i_ = 0; i_ < sizeof(values_) / sizeof(values_[0]); i_++) {        \
            const T *value_ = ecitygml_##T##Iterator_next(iterator_);                      \
            TEST_ASSERT_NOT_NULL(value_);                                                  \
            ASSERT_STR(values_[i_], ecitygml_##T##_value(value_));                       \
        }                                                                                  \
        TEST_ASSERT_NULL(ecitygml_##T##Iterator_next(iterator_));                          \
        ecitygml_##T##Iterator_destroy(iterator_);                                         \
    } while (0)

static bool equals(DiplomatStringView view, const char *expected) {
    return view.len == strlen(expected) && memcmp(view.data, expected, view.len) == 0;
}

/// Declares `all_<T>`: the features `T::try_from` accepts, into `out` (borrowed from the model); returns their number.
#define DEFINE_ALL(T)                                                                            \
    static size_t all_##T(const CityModel *city_model, const T **out) {                          \
        size_t len = 0;                                                                          \
        AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model); \
        AbstractFeatureKindRef *feature;                                                         \
        while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {     \
            const T *x = ecitygml_##T##_try_from(feature);                                       \
            if (x != NULL) {                                                                     \
                TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);                                 \
                out[len++] = x;                                                                  \
            }                                                                                    \
            ecitygml_AbstractFeatureKindRef_destroy(feature);                                    \
        }                                                                                        \
        ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);                               \
        return len;                                                                              \
    }

/// Declares `only_<T>`: the only feature `T::try_from` accepts.
#define DEFINE_ONLY(T)                                                \
    DEFINE_ALL(T)                                                     \
    static const T *only_##T(const CityModel *city_model) {           \
        const T *found[MAX_FEATURES];                                 \
        TEST_ASSERT_EQUAL_size_t(1, all_##T(city_model, found));      \
        return found[0];                                              \
    }

/// Declares `with_id_<T>`: the feature `T::try_from` accepts with that `feature_id`.
#define DEFINE_WITH_ID(T)                                                                                \
    DEFINE_ALL(T)                                                                                        \
    static const T *with_id_##T(const CityModel *city_model, const char *id) {                           \
        const T *found[MAX_FEATURES];                                                                    \
        size_t len = all_##T(city_model, found);                                                         \
        for (size_t i = 0; i < len; i++) {                                                               \
            if (equals(ecitygml_Id_as_str(ecitygml_##T##_feature_id(found[i])), id)) return found[i];    \
        }                                                                                                \
        TEST_FAIL_MESSAGE(id);                                                                           \
        return NULL;                                                                                     \
    }

DEFINE_ONLY(Bridge)
DEFINE_ONLY(BridgePart)
DEFINE_ONLY(Tunnel)
DEFINE_ONLY(TunnelPart)
DEFINE_ONLY(PlantCover)
DEFINE_ONLY(CityFurniture)
DEFINE_ONLY(Section)
DEFINE_ONLY(TrafficSpace)
DEFINE_WITH_ID(SolitaryVegetationObject)
DEFINE_WITH_ID(Building)

/// Asserts how an href is written.
static void assert_href(const char *expected, const HRef *href) {
    TEST_ASSERT_NOT_NULL(href);
    DiplomatWrite *write = diplomat_buffer_write_create(MAX_STRING);
    ecitygml_HRef_to_string(href, write);
    ASSERT_STR(expected, ((DiplomatStringView){diplomat_buffer_write_get_bytes(write), diplomat_buffer_write_len(write)}));
    diplomat_buffer_write_destroy(write);
}

static void assert_ymd(const Date *date, int32_t year, uint32_t month, uint32_t day) {
    TEST_ASSERT_NOT_NULL(date);
    TEST_ASSERT_EQUAL_INT32(year, ecitygml_Date_year(date));
    TEST_ASSERT_EQUAL_UINT32(month, ecitygml_Date_month(date));
    TEST_ASSERT_EQUAL_UINT32(day, ecitygml_Date_day(date));
}

static void assert_feature_types(const CityModel *city_model, const FeatureType *expected, size_t len) {
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    for (size_t i = 0; i < len; i++) {
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator);
        TEST_ASSERT_NOT_NULL(feature);
        TEST_ASSERT_EQUAL_INT(expected[i], ecitygml_AbstractFeatureKindRef_feature_type(feature));
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    TEST_ASSERT_NULL(ecitygml_AbstractFeatureKindRefIterator_next(iterator));
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
}

static size_t city_object_types(const CityModel *city_model, FeatureType *out) {
    size_t len = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = ecitygml_AbstractCityObjectKindRef_feature_type(object);
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    return len;
}

/// Writes and reads back the city model; `*text` is the written CityGML (free it).
static CityModel *round_trip(const CityModel *city_model, char **text) {
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    DiplomatU8View data = ecitygml_GmlWriter_data(writer);
    *text = malloc(data.len + 1);
    memcpy(*text, data.data, data.len);
    (*text)[data.len] = '\0';
    GmlReader *reader = ecitygml_GmlReader_new(data, CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result written = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    ecitygml_GmlWriter_destroy(writer);
    TEST_ASSERT_TRUE(written.is_ok);
    return written.ok;
}

static void assert_feature_types_equal(const CityModel *a, const CityModel *b) {
    FeatureType expected[MAX_FEATURES];
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(a);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        expected[len++] = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    assert_feature_types(b, expected, len);
}

// bridge.gml

static const BridgePart *bridge_part(const Bridge *bridge) {
    BridgePartPropertyIterator *parts = ecitygml_Bridge_bridge_parts(bridge);
    const BridgePartProperty *property = ecitygml_BridgePartPropertyIterator_next(parts);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_BridgePartPropertyIterator_next(parts));
    ecitygml_BridgePartPropertyIterator_destroy(parts);
    TEST_ASSERT_NULL(ecitygml_BridgePartProperty_href(property));
    const BridgePart *part = ecitygml_BridgePartProperty_object(property);
    TEST_ASSERT_NOT_NULL(part);
    return part;
}

static void bridge_city_model(void) {
    CityModel *city_model = read(SYNTHETIC("bridge.gml"));
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {FeatureType_CityModel, FeatureType_Bridge, FeatureType_BridgePart};
    assert_feature_types(city_model, types, 3);
    FeatureType objects[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, city_object_types(city_model, objects));
    TEST_ASSERT_EQUAL_INT_ARRAY(types + 1, objects, 2);
    ecitygml_CityModel_destroy(city_model);
}

static void bridge_attributes(void) {
    CityModel *city_model = read(SYNTHETIC("bridge.gml"));
    const Bridge *bridge = only_Bridge(city_model);
    ASSERT_STR("bridge_1", ecitygml_Id_as_str(ecitygml_Bridge_feature_id(bridge)));
    ASSERT_VALUES(Code, ecitygml_Bridge_names(bridge), "Synthetic bridge");
    ASSERT_STR("1000", ecitygml_BridgeClassValue_value(ecitygml_Bridge_class(bridge)));
    ASSERT_VALUES(BridgeFunctionValue, ecitygml_Bridge_functions(bridge), "1010", "1020");
    ASSERT_VALUES(BridgeUsageValue, ecitygml_Bridge_usages(bridge), "1000");
    assert_ymd(ecitygml_Bridge_date_of_construction(bridge), 1990, 5, 1);
    TEST_ASSERT_EQUAL_size_t(0, count_Height(ecitygml_Bridge_heights(bridge)));
    const BridgePart *part = bridge_part(bridge);
    ASSERT_STR("bridge_part_1", ecitygml_Id_as_str(ecitygml_BridgePart_feature_id(part)));
    TEST_ASSERT_NULL(ecitygml_BridgePart_class(part));
    TEST_ASSERT_EQUAL_size_t(0, count_BridgeFunctionValue(ecitygml_BridgePart_functions(part)));
    ASSERT_STR("bridge_part_1", ecitygml_Id_as_str(ecitygml_BridgePart_feature_id(only_BridgePart(city_model))));
    ecitygml_CityModel_destroy(city_model);
}

static void bridge_is_movable(void) {
    CityModel *city_model = read(SYNTHETIC("bridge.gml"));
    const Bridge *bridge = only_Bridge(city_model);
    ecitygml_Bridge_is_movable_result movable = ecitygml_Bridge_is_movable(bridge);
    TEST_ASSERT_TRUE(movable.is_ok);
    TEST_ASSERT_TRUE(movable.ok);
    ecitygml_BridgePart_is_movable_result part_movable = ecitygml_BridgePart_is_movable(bridge_part(bridge));
    TEST_ASSERT_TRUE(part_movable.is_ok);
    TEST_ASSERT_FALSE(part_movable.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void assert_code_space(const char *expected, const Code *code) {
    ecitygml_Code_code_space_result code_space = ecitygml_Code_code_space(code);
    if (expected == NULL) {
        TEST_ASSERT_FALSE(code_space.is_ok);
    } else {
        TEST_ASSERT_TRUE(code_space.is_ok);
        ASSERT_STR(expected, code_space.ok);
    }
}

static void bridge_code_spaces(void) {
    CityModel *city_model = read(SYNTHETIC("bridge.gml"));
    const Bridge *bridge = only_Bridge(city_model);
    assert_code_space("https://example.org/bridge_class", ecitygml_BridgeClassValue_code(ecitygml_Bridge_class(bridge)));
    BridgeFunctionValueIterator *functions = ecitygml_Bridge_functions(bridge);
    const BridgeFunctionValue *function;
    while ((function = ecitygml_BridgeFunctionValueIterator_next(functions)) != NULL) {
        assert_code_space(NULL, ecitygml_BridgeFunctionValue_code(function));
    }
    ecitygml_BridgeFunctionValueIterator_destroy(functions);
    ecitygml_CityModel_destroy(city_model);
}

static void bridge_round_trip(void) {
    CityModel *city_model = read(SYNTHETIC("bridge.gml"));
    char *text;
    CityModel *written = round_trip(city_model, &text);
    assert_feature_types_equal(city_model, written);
    const Bridge *bridge = only_Bridge(written);
    ASSERT_STR("1000", ecitygml_BridgeClassValue_value(ecitygml_Bridge_class(bridge)));
    ASSERT_VALUES(BridgeFunctionValue, ecitygml_Bridge_functions(bridge), "1010", "1020");
    assert_ymd(ecitygml_Bridge_date_of_construction(bridge), 1990, 5, 1);
    ASSERT_STR("bridge_part_1", ecitygml_Id_as_str(ecitygml_BridgePart_feature_id(bridge_part(bridge))));
    free(text);
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// tunnel.gml

static const TunnelPart *tunnel_part(const Tunnel *tunnel) {
    TunnelPartPropertyIterator *parts = ecitygml_Tunnel_tunnel_parts(tunnel);
    const TunnelPartProperty *property = ecitygml_TunnelPartPropertyIterator_next(parts);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_TunnelPartPropertyIterator_next(parts));
    ecitygml_TunnelPartPropertyIterator_destroy(parts);
    TEST_ASSERT_NULL(ecitygml_TunnelPartProperty_href(property));
    const TunnelPart *part = ecitygml_TunnelPartProperty_object(property);
    TEST_ASSERT_NOT_NULL(part);
    return part;
}

static void tunnel_city_model(void) {
    CityModel *city_model = read(SYNTHETIC("tunnel.gml"));
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {FeatureType_CityModel, FeatureType_Tunnel, FeatureType_TunnelPart};
    assert_feature_types(city_model, types, 3);
    FeatureType objects[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, city_object_types(city_model, objects));
    TEST_ASSERT_EQUAL_INT_ARRAY(types + 1, objects, 2);
    ecitygml_CityModel_destroy(city_model);
}

static void tunnel_attributes(void) {
    CityModel *city_model = read(SYNTHETIC("tunnel.gml"));
    const Tunnel *tunnel = only_Tunnel(city_model);
    ASSERT_STR("tunnel_1", ecitygml_Id_as_str(ecitygml_Tunnel_feature_id(tunnel)));
    ASSERT_VALUES(Code, ecitygml_Tunnel_names(tunnel), "Synthetic tunnel");
    ASSERT_STR("1000", ecitygml_TunnelClassValue_value(ecitygml_Tunnel_class(tunnel)));
    ASSERT_VALUES(TunnelFunctionValue, ecitygml_Tunnel_functions(tunnel), "1010", "1020");
    ASSERT_VALUES(TunnelUsageValue, ecitygml_Tunnel_usages(tunnel), "1000");
    assert_ymd(ecitygml_Tunnel_date_of_construction(tunnel), 1990, 5, 1);
    TEST_ASSERT_EQUAL_size_t(0, count_Height(ecitygml_Tunnel_heights(tunnel)));
    const TunnelPart *part = tunnel_part(tunnel);
    ASSERT_STR("tunnel_part_1", ecitygml_Id_as_str(ecitygml_TunnelPart_feature_id(part)));
    TEST_ASSERT_NULL(ecitygml_TunnelPart_class(part));
    ASSERT_VALUES(TunnelFunctionValue, ecitygml_TunnelPart_functions(part), "1030");
    ASSERT_STR("tunnel_part_1", ecitygml_Id_as_str(ecitygml_TunnelPart_feature_id(only_TunnelPart(city_model))));
    ecitygml_CityModel_destroy(city_model);
}

static void tunnel_code_spaces(void) {
    CityModel *city_model = read(SYNTHETIC("tunnel.gml"));
    const Tunnel *tunnel = only_Tunnel(city_model);
    assert_code_space("https://example.org/tunnel_class", ecitygml_TunnelClassValue_code(ecitygml_Tunnel_class(tunnel)));
    TunnelFunctionValueIterator *functions = ecitygml_Tunnel_functions(tunnel);
    const TunnelFunctionValue *function;
    while ((function = ecitygml_TunnelFunctionValueIterator_next(functions)) != NULL) {
        assert_code_space(NULL, ecitygml_TunnelFunctionValue_code(function));
    }
    ecitygml_TunnelFunctionValueIterator_destroy(functions);
    ecitygml_CityModel_destroy(city_model);
}

static void tunnel_round_trip(void) {
    CityModel *city_model = read(SYNTHETIC("tunnel.gml"));
    char *text;
    CityModel *written = round_trip(city_model, &text);
    assert_feature_types_equal(city_model, written);
    const Tunnel *tunnel = only_Tunnel(written);
    ASSERT_STR("1000", ecitygml_TunnelClassValue_value(ecitygml_Tunnel_class(tunnel)));
    ASSERT_VALUES(TunnelFunctionValue, ecitygml_Tunnel_functions(tunnel), "1010", "1020");
    ASSERT_VALUES(TunnelFunctionValue, ecitygml_TunnelPart_functions(tunnel_part(tunnel)), "1030");
    free(text);
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// vegetation.gml

static const ImplicitGeometry *implicit(const ImplicitGeometryProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_ImplicitGeometryProperty_href(property));
    const ImplicitGeometry *geometry = ecitygml_ImplicitGeometryProperty_object(property);
    TEST_ASSERT_NOT_NULL(geometry);
    return geometry;
}

static void vegetation_city_model(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    TEST_ASSERT_EQUAL_size_t(3, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {FeatureType_CityModel, FeatureType_SolitaryVegetationObject,
                                 FeatureType_SolitaryVegetationObject, FeatureType_PlantCover};
    assert_feature_types(city_model, types, 4);
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_tree(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const SolitaryVegetationObject *tree = with_id_SolitaryVegetationObject(city_model, "tree_1");
    ASSERT_STR("1000", ecitygml_SolitaryVegetationObjectClassValue_value(ecitygml_SolitaryVegetationObject_class(tree)));
    ASSERT_VALUES(SolitaryVegetationObjectFunctionValue, ecitygml_SolitaryVegetationObject_functions(tree), "1010");
    ASSERT_VALUES(SolitaryVegetationObjectUsageValue, ecitygml_SolitaryVegetationObject_usages(tree), "1020");
    ASSERT_STR("Quercus robur", ecitygml_SpeciesValue_value(ecitygml_SolitaryVegetationObject_species(tree)));
    const Measure *height = ecitygml_SolitaryVegetationObject_height(tree);
    ASSERT_CLOSE(12.5, ecitygml_Measure_value(height));
    ASSERT_STR("m", ecitygml_Measure_uom(height));
    ASSERT_CLOSE(0.4, ecitygml_Measure_value(ecitygml_SolitaryVegetationObject_trunk_diameter(tree)));
    ASSERT_CLOSE(5.5, ecitygml_Measure_value(ecitygml_SolitaryVegetationObject_crown_diameter(tree)));
    ASSERT_CLOSE(1.2, ecitygml_Measure_value(ecitygml_SolitaryVegetationObject_root_ball_diameter(tree)));
    ASSERT_CLOSE(0.8, ecitygml_Measure_value(ecitygml_SolitaryVegetationObject_max_root_ball_depth(tree)));
    TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod2_implicit_representation(tree));
    TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod3_implicit_representation(tree));
    TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod1_solid(tree));
    TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(tree));
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_implicit_geometry(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const ImplicitGeometry *geometry = implicit(
        ecitygml_SolitaryVegetationObject_lod1_implicit_representation(with_id_SolitaryVegetationObject(city_model, "tree_1")));
    ASSERT_STR("tree_prototype", ecitygml_Id_as_str(ecitygml_ImplicitGeometry_object_id(geometry)));
    ASSERT_STR("model/gltf+json", ecitygml_MimeTypeValue_value(ecitygml_ImplicitGeometry_mime_type(geometry)));
    const DirectPosition *pos = ecitygml_Point_pos(ecitygml_PointProperty_object(ecitygml_ImplicitGeometry_reference_point(geometry)));
    TEST_ASSERT_EQUAL_DOUBLE(457850.0, ecitygml_DirectPosition_x(pos));
    TEST_ASSERT_EQUAL_DOUBLE(5439090.0, ecitygml_DirectPosition_y(pos));
    TEST_ASSERT_EQUAL_DOUBLE(112.0, ecitygml_DirectPosition_z(pos));
    const double rows[4][4] = {{2, 0, 0, 10}, {0, 2, 0, 20}, {0, 0, 3, 30}, {0, 0, 0, 1}};
    const TransformationMatrix4x4 *matrix = ecitygml_ImplicitGeometry_transformation_matrix(geometry);
    for (size_t row = 0; row < 4; row++) {
        for (size_t column = 0; column < 4; column++) {
            ecitygml_TransformationMatrix4x4_get_result value = ecitygml_TransformationMatrix4x4_get(matrix, row, column);
            TEST_ASSERT_TRUE(value.is_ok);
            ASSERT_CLOSE(rows[row][column], value.ok);
        }
    }
    const AbstractGeometryKind *relative = ecitygml_AbstractGeometryProperty_object(ecitygml_ImplicitGeometry_relative_geometry(geometry));
    TEST_ASSERT_EQUAL_INT(GeometryType_MultiSurface, ecitygml_AbstractGeometryKind_geometry_type(relative));
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfaceProperty(ecitygml_MultiSurface_surface_member(ecitygml_MultiSurface_try_from(relative))));
    TEST_ASSERT_NULL(ecitygml_Point_try_from(relative));
    ecitygml_AbstractGeometryKind_triangulate_result triangulation = ecitygml_AbstractGeometryKind_triangulate(relative);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    TEST_ASSERT_EQUAL_size_t(1, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok))));
    ecitygml_Triangulation_destroy(triangulation.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_point_relative_geometry(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const SolitaryVegetationObject *tree = with_id_SolitaryVegetationObject(city_model, "tree_2");
    TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod1_implicit_representation(tree));
    const ImplicitGeometry *geometry = implicit(ecitygml_SolitaryVegetationObject_lod2_implicit_representation(tree));
    ASSERT_STR("point_prototype", ecitygml_Id_as_str(ecitygml_ImplicitGeometry_object_id(geometry)));
    TEST_ASSERT_NULL(ecitygml_ImplicitGeometry_mime_type(geometry));
    const AbstractGeometryKind *relative = ecitygml_AbstractGeometryProperty_object(ecitygml_ImplicitGeometry_relative_geometry(geometry));
    TEST_ASSERT_EQUAL_INT(GeometryType_Point, ecitygml_AbstractGeometryKind_geometry_type(relative));
    const DirectPosition *pos = ecitygml_Point_pos(ecitygml_Point_try_from(relative));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, ecitygml_DirectPosition_x(pos));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, ecitygml_DirectPosition_y(pos));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, ecitygml_DirectPosition_z(pos));
    TEST_ASSERT_NULL(ecitygml_MultiSurface_try_from(relative));
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_library_object(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const ImplicitGeometry *first = implicit(
        ecitygml_SolitaryVegetationObject_lod1_implicit_representation(with_id_SolitaryVegetationObject(city_model, "tree_1")));
    TEST_ASSERT_FALSE(ecitygml_ImplicitGeometry_library_object(first).is_ok);
    const ImplicitGeometry *second = implicit(
        ecitygml_SolitaryVegetationObject_lod2_implicit_representation(with_id_SolitaryVegetationObject(city_model, "tree_2")));
    ecitygml_ImplicitGeometry_library_object_result library_object = ecitygml_ImplicitGeometry_library_object(second);
    TEST_ASSERT_TRUE(library_object.is_ok);
    ASSERT_STR("https://example.org/trees/oak.gltf", library_object.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_plant_cover(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const PlantCover *cover = only_PlantCover(city_model);
    ASSERT_STR("cover_1", ecitygml_Id_as_str(ecitygml_PlantCover_feature_id(cover)));
    ASSERT_STR("2000", ecitygml_PlantCoverClassValue_value(ecitygml_PlantCover_class(cover)));
    TEST_ASSERT_EQUAL_size_t(0, count_PlantCoverFunctionValue(ecitygml_PlantCover_functions(cover)));
    TEST_ASSERT_EQUAL_size_t(0, count_PlantCoverUsageValue(ecitygml_PlantCover_usages(cover)));
    ASSERT_CLOSE(2.5, ecitygml_Measure_value(ecitygml_PlantCover_average_height(cover)));
    ASSERT_CLOSE(1.0, ecitygml_Measure_value(ecitygml_PlantCover_min_height(cover)));
    ASSERT_CLOSE(4.0, ecitygml_Measure_value(ecitygml_PlantCover_max_height(cover)));
    TEST_ASSERT_NULL(ecitygml_PlantCover_lod1_implicit_representation(cover));
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        if (ecitygml_AbstractFeatureKindRef_feature_type(feature) == FeatureType_PlantCover) {
            TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_try_from(feature));
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_code_spaces(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    const SolitaryVegetationObject *tree = with_id_SolitaryVegetationObject(city_model, "tree_1");
    assert_code_space("https://example.org/tree_class",
                      ecitygml_SolitaryVegetationObjectClassValue_code(ecitygml_SolitaryVegetationObject_class(tree)));
    assert_code_space(NULL, ecitygml_PlantCoverClassValue_code(ecitygml_PlantCover_class(only_PlantCover(city_model))));
    ecitygml_CityModel_destroy(city_model);
}

static void vegetation_round_trip(void) {
    CityModel *city_model = read(SYNTHETIC("vegetation.gml"));
    char *text;
    CityModel *written = round_trip(city_model, &text);
    assert_feature_types_equal(city_model, written);
    const SolitaryVegetationObject *tree = with_id_SolitaryVegetationObject(written, "tree_1");
    ASSERT_STR("Quercus robur", ecitygml_SpeciesValue_value(ecitygml_SolitaryVegetationObject_species(tree)));
    ASSERT_CLOSE(12.5, ecitygml_Measure_value(ecitygml_SolitaryVegetationObject_height(tree)));
    const ImplicitGeometry *geometry = implicit(ecitygml_SolitaryVegetationObject_lod1_implicit_representation(tree));
    ASSERT_STR("tree_prototype", ecitygml_Id_as_str(ecitygml_ImplicitGeometry_object_id(geometry)));
    ASSERT_STR("model/gltf+json", ecitygml_MimeTypeValue_value(ecitygml_ImplicitGeometry_mime_type(geometry)));
    ASSERT_CLOSE(2.5, ecitygml_Measure_value(ecitygml_PlantCover_average_height(only_PlantCover(written))));
    TEST_ASSERT_NULL(strstr(text, "objectId"));
    free(text);
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// city-furniture.gml

static void furniture_attributes(void) {
    CityModel *city_model = read(SYNTHETIC("city-furniture.gml"));
    const CityFurniture *furniture = only_CityFurniture(city_model);
    ASSERT_STR("sign_1", ecitygml_Id_as_str(ecitygml_CityFurniture_feature_id(furniture)));
    ASSERT_VALUES(Code, ecitygml_CityFurniture_names(furniture), "Vorschriftzeichen");
    ASSERT_STR("1000", ecitygml_CityFurnitureClassValue_value(ecitygml_CityFurniture_class(furniture)));
    ASSERT_VALUES(CityFurnitureFunctionValue, ecitygml_CityFurniture_functions(furniture), "1080");
    ASSERT_VALUES(CityFurnitureUsageValue, ecitygml_CityFurniture_usages(furniture), "1090");
    const MultiSurfaceProperty *property = ecitygml_CityFurniture_lod2_multi_surface(furniture);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_MultiSurfaceProperty_href(property));
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfaceProperty(ecitygml_MultiSurface_surface_member(ecitygml_MultiSurfaceProperty_object(property))));
    TEST_ASSERT_NULL(ecitygml_CityFurniture_lod1_implicit_representation(furniture));
    TEST_ASSERT_NULL(ecitygml_CityFurniture_lod2_terrain_intersection_curve(furniture));
    ecitygml_CityModel_destroy(city_model);
}

static void furniture_code_spaces(void) {
    CityModel *city_model = read(SYNTHETIC("city-furniture.gml"));
    assert_code_space("https://example.org/furniture_class",
                      ecitygml_CityFurnitureClassValue_code(ecitygml_CityFurniture_class(only_CityFurniture(city_model))));
    ecitygml_CityModel_destroy(city_model);
}

// building.gml

static const CityObjectRelation *relation_of(const Building *building) {
    CityObjectRelationPropertyIterator *relations = ecitygml_Building_related_to(building);
    const CityObjectRelationProperty *property = ecitygml_CityObjectRelationPropertyIterator_next(relations);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(relations));
    ecitygml_CityObjectRelationPropertyIterator_destroy(relations);
    TEST_ASSERT_NULL(ecitygml_CityObjectRelationProperty_href(property));
    const CityObjectRelation *relation = ecitygml_CityObjectRelationProperty_object(property);
    TEST_ASSERT_NOT_NULL(relation);
    return relation;
}

static const GenericAttributeSet *attribute_set(const Building *building) {
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(building);
    const GenericAttributeKind *attribute = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_NOT_NULL(attribute);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    const GenericAttributeSet *set = ecitygml_GenericAttributeSet_try_from(attribute);
    TEST_ASSERT_NOT_NULL(set);
    return set;
}

/// The building's two boundaries, into `out`; the first one's roof surface.
static const RoofSurface *boundaries_of(const Building *building, const AbstractSpaceBoundaryProperty *out[2]) {
    AbstractSpaceBoundaryPropertyIterator *iterator = ecitygml_Building_boundaries(building);
    out[0] = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(iterator);
    out[1] = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(iterator);
    TEST_ASSERT_NOT_NULL(out[0]);
    TEST_ASSERT_NOT_NULL(out[1]);
    TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(iterator));
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(iterator);
    TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(out[0]));
    AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(ecitygml_AbstractSpaceBoundaryProperty_object(out[0]));
    const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
    ecitygml_AbstractFeatureKindRef_destroy(feature);
    TEST_ASSERT_NOT_NULL(roof);
    return roof;
}

static const AbstractFillingSurfaceKind *only_filling(const RoofSurface *roof) {
    AbstractFillingSurfacePropertyIterator *fillings = ecitygml_RoofSurface_filling_surfaces(roof);
    const AbstractFillingSurfaceProperty *property = ecitygml_AbstractFillingSurfacePropertyIterator_next(fillings);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_AbstractFillingSurfacePropertyIterator_next(fillings));
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(fillings);
    TEST_ASSERT_NULL(ecitygml_AbstractFillingSurfaceProperty_href(property));
    const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
    TEST_ASSERT_NOT_NULL(filling);
    return filling;
}

static void building_city_model(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    TEST_ASSERT_EQUAL_size_t(2, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {FeatureType_CityModel, FeatureType_Building, FeatureType_RoofSurface,
                                 FeatureType_WindowSurface, FeatureType_Building};
    assert_feature_types(city_model, types, 5);
    FeatureType objects[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(4, city_object_types(city_model, objects));
    ecitygml_CityModel_destroy(city_model);
}

static void building_relation(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    const CityObjectRelation *relation = relation_of(with_id_Building(city_model, "building_1"));
    ASSERT_STR("shared", ecitygml_RelationTypeValue_value(ecitygml_CityObjectRelation_relation_type(relation)));
    assert_href("#building_2", ecitygml_Reference_href(ecitygml_CityObjectRelation_relation_to(relation)));
    GenericAttributeKindIterator *attributes = ecitygml_CityObjectRelation_generic_attributes(relation);
    const GenericAttributeKind *weight = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_NOT_NULL(weight);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ASSERT_STR("weight", ecitygml_GenericAttributeKind_name(weight));
    TEST_ASSERT_EQUAL_INT64(3, ecitygml_IntAttribute_value(ecitygml_GenericAttributeKind_as_int(weight)));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    ecitygml_CityModel_destroy(city_model);
}

static void building_attribute_set(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    const GenericAttributeSet *set = attribute_set(with_id_Building(city_model, "building_1"));
    ASSERT_STR("energy", ecitygml_GenericAttributeSet_name(set));
    GenericAttributeKindIterator *attributes = ecitygml_GenericAttributeSet_generic_attributes(set);
    const GenericAttributeKind *demand = ecitygml_GenericAttributeKindIterator_next(attributes);
    const GenericAttributeKind *label = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_NOT_NULL(demand);
    TEST_ASSERT_NOT_NULL(label);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ASSERT_STR("demand", ecitygml_GenericAttributeKind_name(demand));
    ASSERT_CLOSE(12.5, ecitygml_DoubleAttribute_value(ecitygml_GenericAttributeKind_as_double(demand)));
    ASSERT_STR("label", ecitygml_GenericAttributeKind_name(label));
    ASSERT_STR("A+", ecitygml_StringAttribute_value(ecitygml_GenericAttributeKind_as_string(label)));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    ecitygml_CityModel_destroy(city_model);
}

static void building_construction(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    const Building *building = with_id_Building(city_model, "building_1");
    ecitygml_Building_relative_to_water_result water = ecitygml_Building_relative_to_water(building);
    TEST_ASSERT_TRUE(water.is_ok);
    TEST_ASSERT_EQUAL_INT(RelativeToWater_EntirelyAboveWaterSurface, water.ok);
    assert_ymd(ecitygml_Building_date_of_construction(building), 2020, 1, 1);
    assert_ymd(ecitygml_Building_date_of_demolition(building), 2050, 12, 31);
    OccupancyIterator *occupancies = ecitygml_Building_occupancies(building);
    const Occupancy *occupancy = ecitygml_OccupancyIterator_next(occupancies);
    TEST_ASSERT_NOT_NULL(occupancy);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    TEST_ASSERT_EQUAL_INT64(4, ecitygml_Occupancy_number_of_occupants(occupancy));
    ASSERT_STR("daytime", ecitygml_IntervalValue_value(ecitygml_Occupancy_interval(occupancy)));
    ASSERT_STR("residents", ecitygml_OccupantTypeValue_value(ecitygml_Occupancy_occupant_type(occupancy)));
    ecitygml_OccupancyIterator_destroy(occupancies);
    ecitygml_CityModel_destroy(city_model);
}

static void building_boundaries(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    const AbstractSpaceBoundaryProperty *boundaries[2];
    const RoofSurface *roof = boundaries_of(with_id_Building(city_model, "building_1"), boundaries);
    ASSERT_STR("roof_1", ecitygml_Id_as_str(ecitygml_RoofSurface_feature_id(roof)));
    const AbstractFillingSurfaceKind *window = only_filling(roof);
    TEST_ASSERT_EQUAL_INT(FeatureType_WindowSurface, ecitygml_AbstractFillingSurfaceKind_feature_type(window));
    ASSERT_STR("roof_window_1", ecitygml_Id_as_str(ecitygml_AbstractFillingSurfaceKind_feature_id(window)));
    TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_object(boundaries[1]));
    assert_href("#missing_boundary", ecitygml_AbstractSpaceBoundaryProperty_href(boundaries[1]));
    ecitygml_CityModel_destroy(city_model);
}

static void building_terrain_intersection_curve(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    const Building *building = with_id_Building(city_model, "building_1");
    const MultiCurveProperty *property = ecitygml_Building_lod2_terrain_intersection_curve(building);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_MultiCurveProperty_href(property));
    const MultiCurve *multi_curve = ecitygml_MultiCurveProperty_object(property);
    AbstractCurvePropertyIterator *members = ecitygml_MultiCurve_curve_member(multi_curve);
    const AbstractCurveProperty *member = ecitygml_AbstractCurvePropertyIterator_next(members);
    TEST_ASSERT_NOT_NULL(member);
    TEST_ASSERT_NULL(ecitygml_AbstractCurvePropertyIterator_next(members));
    ecitygml_AbstractCurvePropertyIterator_destroy(members);
    const LineString *line = ecitygml_LineString_try_from(ecitygml_AbstractCurveProperty_object(member));
    TEST_ASSERT_EQUAL_size_t(2, count_DirectPosition(ecitygml_LineString_points(line)));
    ecitygml_MultiCurve_length_3d_result length = ecitygml_MultiCurve_length_3d(multi_curve);
    TEST_ASSERT_TRUE(length.is_ok);
    ASSERT_CLOSE(12.0, length.ok);
    TEST_ASSERT_NULL(ecitygml_Building_lod1_terrain_intersection_curve(building));
    TEST_ASSERT_NULL(ecitygml_Building_lod3_terrain_intersection_curve(building));
    ecitygml_CityModel_destroy(city_model);
}

static void building_round_trip(void) {
    CityModel *city_model = read(SYNTHETIC("building.gml"));
    char *text;
    CityModel *written = round_trip(city_model, &text);
    assert_feature_types_equal(city_model, written);
    const Building *building = with_id_Building(written, "building_1");
    assert_href("#building_2", ecitygml_Reference_href(ecitygml_CityObjectRelation_relation_to(relation_of(building))));
    ASSERT_STR("energy", ecitygml_GenericAttributeSet_name(attribute_set(building)));
    assert_ymd(ecitygml_Building_date_of_demolition(building), 2050, 12, 31);
    OccupancyIterator *occupancies = ecitygml_Building_occupancies(building);
    const Occupancy *occupancy = ecitygml_OccupancyIterator_next(occupancies);
    TEST_ASSERT_NOT_NULL(occupancy);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    TEST_ASSERT_EQUAL_INT64(4, ecitygml_Occupancy_number_of_occupants(occupancy));
    ASSERT_STR("daytime", ecitygml_IntervalValue_value(ecitygml_Occupancy_interval(occupancy)));
    ASSERT_STR("residents", ecitygml_OccupantTypeValue_value(ecitygml_Occupancy_occupant_type(occupancy)));
    ecitygml_OccupancyIterator_destroy(occupancies);
    const AbstractSpaceBoundaryProperty *boundaries[2];
    const RoofSurface *roof = boundaries_of(building, boundaries);
    ASSERT_STR("roof_window_1", ecitygml_Id_as_str(ecitygml_AbstractFillingSurfaceKind_feature_id(only_filling(roof))));
    assert_href("#missing_boundary", ecitygml_AbstractSpaceBoundaryProperty_href(boundaries[1]));
    ecitygml_MultiCurve_length_3d_result length = ecitygml_MultiCurve_length_3d(
        ecitygml_MultiCurveProperty_object(ecitygml_Building_lod2_terrain_intersection_curve(building)));
    TEST_ASSERT_TRUE(length.is_ok);
    ASSERT_CLOSE(12.0, length.ok);
    TEST_ASSERT_NULL(strstr(text, "TerrainIntersectionCurveProperty"));
    free(text);
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// transportation.gml

static void transportation_section(void) {
    CityModel *city_model = read(SYNTHETIC("transportation.gml"));
    const Section *section = only_Section(city_model);
    ASSERT_STR("section_1", ecitygml_Id_as_str(ecitygml_Section_feature_id(section)));
    ecitygml_Section_traffic_direction_result direction = ecitygml_Section_traffic_direction(section);
    TEST_ASSERT_TRUE(direction.is_ok);
    TEST_ASSERT_EQUAL_INT(TrafficDirectionValue_Both, direction.ok);
    OccupancyIterator *occupancies = ecitygml_Section_occupancies(section);
    const Occupancy *occupancy = ecitygml_OccupancyIterator_next(occupancies);
    TEST_ASSERT_NOT_NULL(occupancy);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    TEST_ASSERT_EQUAL_INT64(120, ecitygml_Occupancy_number_of_occupants(occupancy));
    ASSERT_STR("peakHour", ecitygml_IntervalValue_value(ecitygml_Occupancy_interval(occupancy)));
    ecitygml_OccupancyIterator_destroy(occupancies);
    TrafficSpacePropertyIterator *spaces = ecitygml_Section_traffic_spaces(section);
    const TrafficSpaceProperty *property = ecitygml_TrafficSpacePropertyIterator_next(spaces);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_TrafficSpacePropertyIterator_next(spaces));
    ecitygml_TrafficSpacePropertyIterator_destroy(spaces);
    TEST_ASSERT_NULL(ecitygml_TrafficSpaceProperty_href(property));
    const TrafficSpace *space = ecitygml_TrafficSpaceProperty_object(property);
    ASSERT_STR("space_1", ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(space)));
    TEST_ASSERT_EQUAL_INT(GranularityValue_Lane, ecitygml_TrafficSpace_granularity(space));
    ecitygml_CityModel_destroy(city_model);
}

static void transportation_point(void) {
    CityModel *city_model = read(SYNTHETIC("transportation.gml"));
    const PointProperty *property = ecitygml_TrafficSpace_lod0_point(only_TrafficSpace(city_model));
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_PointProperty_href(property));
    const Point *point = ecitygml_PointProperty_object(property);
    ASSERT_STR("point_1", ecitygml_Id_as_str(ecitygml_Point_id(point)));
    const DirectPosition *pos = ecitygml_Point_pos(point);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, ecitygml_DirectPosition_x(pos));
    TEST_ASSERT_EQUAL_DOUBLE(-2.5, ecitygml_DirectPosition_y(pos));
    TEST_ASSERT_EQUAL_DOUBLE(3.25, ecitygml_DirectPosition_z(pos));
    Envelope *envelope = ecitygml_Point_compute_envelope(point);
    TEST_ASSERT_NOT_NULL(envelope);
    const DirectPosition *corners[] = {ecitygml_Envelope_lower_corner(envelope), ecitygml_Envelope_upper_corner(envelope)};
    for (size_t i = 0; i < 2; i++) {
        TEST_ASSERT_EQUAL_DOUBLE(1.5, ecitygml_DirectPosition_x(corners[i]));
        TEST_ASSERT_EQUAL_DOUBLE(-2.5, ecitygml_DirectPosition_y(corners[i]));
        TEST_ASSERT_EQUAL_DOUBLE(3.25, ecitygml_DirectPosition_z(corners[i]));
    }
    ecitygml_Envelope_destroy(envelope);
    ecitygml_CityModel_destroy(city_model);
}

static void transportation_curves(void) {
    CityModel *city_model = read(SYNTHETIC("transportation.gml"));
    const MultiCurve *multi_curve = ecitygml_MultiCurveProperty_object(ecitygml_TrafficSpace_lod0_multi_curve(only_TrafficSpace(city_model)));
    AbstractCurvePropertyIterator *iterator = ecitygml_MultiCurve_curve_member(multi_curve);
    const AbstractCurveProperty *members[3];
    for (size_t i = 0; i < 3; i++) {
        members[i] = ecitygml_AbstractCurvePropertyIterator_next(iterator);
        TEST_ASSERT_NOT_NULL(members[i]);
    }
    TEST_ASSERT_NULL(ecitygml_AbstractCurvePropertyIterator_next(iterator));
    ecitygml_AbstractCurvePropertyIterator_destroy(iterator);

    const AbstractCurveKind *line = ecitygml_AbstractCurveProperty_object(members[0]);
    TEST_ASSERT_EQUAL_INT(GeometryType_LineString, ecitygml_AbstractCurveKind_geometry_type(line));
    TEST_ASSERT_NULL(ecitygml_AbstractRingKind_try_from(line));
    const LineString *line_string = ecitygml_LineString_try_from(line);
    TEST_ASSERT_EQUAL_size_t(2, count_DirectPosition(ecitygml_LineString_points(line_string)));
    ASSERT_CLOSE(5.0, ecitygml_LineString_length_3d(line_string));

    const AbstractCurveKind *ring = ecitygml_AbstractCurveProperty_object(members[1]);
    TEST_ASSERT_EQUAL_INT(GeometryType_LinearRing, ecitygml_AbstractCurveKind_geometry_type(ring));
    const LinearRing *linear_ring = ecitygml_LinearRing_try_from(ecitygml_AbstractRingKind_try_from(ring));
    TEST_ASSERT_NOT_NULL(linear_ring);
    TEST_ASSERT_EQUAL_size_t(3, count_DirectPosition(ecitygml_LinearRing_points(linear_ring)));
    ASSERT_CLOSE(2.0 + sqrt(2.0), ecitygml_LinearRing_length_3d(linear_ring));

    TEST_ASSERT_NULL(ecitygml_AbstractCurveProperty_object(members[2]));
    assert_href("#missing_curve", ecitygml_AbstractCurveProperty_href(members[2]));
    ecitygml_MultiCurve_length_3d_result length = ecitygml_MultiCurve_length_3d(multi_curve);
    TEST_ASSERT_FALSE(length.is_ok);
    TEST_ASSERT_EQUAL_INT(ErrorKind_UnresolvedReference, ecitygml_Error_kind(length.err));
    TEST_ASSERT_TRUE(message_contains(length.err, "#missing_curve"));
    ecitygml_Error_destroy(length.err);
    ecitygml_CityModel_destroy(city_model);
}

// geometry.gml

static void geometry_skipped_members(void) {
    CityModel *city_model = read(SYNTHETIC("geometry.gml"));
    const MultiSurface *multi_surface =
        ecitygml_MultiSurfaceProperty_object(ecitygml_Building_lod2_multi_surface(with_id_Building(city_model, "geometry_1")));
    AbstractSurfacePropertyIterator *iterator = ecitygml_MultiSurface_surface_member(multi_surface);
    const AbstractSurfaceKind *members[3];
    for (size_t i = 0; i < 3; i++) {
        const AbstractSurfaceProperty *member = ecitygml_AbstractSurfacePropertyIterator_next(iterator);
        TEST_ASSERT_NOT_NULL(member);
        members[i] = ecitygml_AbstractSurfaceProperty_object(member);
    }
    TEST_ASSERT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(iterator));
    ecitygml_AbstractSurfacePropertyIterator_destroy(iterator);
    const char *ids[] = {"square", "collinear"};
    for (size_t i = 0; i < 2; i++) {
        TEST_ASSERT_EQUAL_INT(GeometryType_Polygon, ecitygml_AbstractSurfaceKind_geometry_type(members[i]));
        ASSERT_STR(ids[i], ecitygml_Id_as_str(ecitygml_AbstractSurfaceKind_id(members[i])));
    }
    ecitygml_AbstractSurfaceKind_area_3d_result area = ecitygml_AbstractSurfaceKind_area_3d(members[1]);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(0.0, area.ok);
    TEST_ASSERT_EQUAL_INT(GeometryType_TriangulatedSurface, ecitygml_AbstractSurfaceKind_geometry_type(members[2]));
    TEST_ASSERT_NULL(ecitygml_Polygon_try_from(members[2]));
    const TriangulatedSurface *tin = ecitygml_TriangulatedSurface_try_from(members[2]);
    TEST_ASSERT_NOT_NULL(tin);
    ASSERT_STR("tin", ecitygml_Id_as_str(ecitygml_TriangulatedSurface_id(tin)));
    TEST_ASSERT_EQUAL_size_t(2, count_Triangle(ecitygml_TriangulatedSurface_triangles(tin)));
    TEST_ASSERT_EQUAL_size_t(2, count_AbstractSurfacePatchKind(ecitygml_Surface_patches(ecitygml_TriangulatedSurface_surface(tin))));
    ecitygml_TriangulatedSurface_area_3d_result tin_area = ecitygml_TriangulatedSurface_area_3d(tin);
    TEST_ASSERT_TRUE(tin_area.is_ok);
    ASSERT_CLOSE(1.0, tin_area.ok);
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_EQUAL_size_t(4, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok))));
    TEST_ASSERT_TRUE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    TriangulationSkippedIterator *skipped = ecitygml_Triangulation_skipped(triangulation.ok);
    Error *error = ecitygml_TriangulationSkippedIterator_next(skipped);
    TEST_ASSERT_NOT_NULL(error);
    TEST_ASSERT_EQUAL_INT(ErrorKind_InvalidArgument, ecitygml_Error_kind(error));
    TEST_ASSERT_TRUE(message_contains(error, "earcut produced no triangles"));
    ecitygml_Error_destroy(error);
    Error *more = ecitygml_TriangulationSkippedIterator_next(skipped);
    TEST_ASSERT_NULL(more);
    ecitygml_TriangulationSkippedIterator_destroy(skipped);
    ecitygml_Triangulation_destroy(triangulation.ok);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(bridge_city_model);
    RUN_TEST(bridge_attributes);
    RUN_TEST(bridge_is_movable);
    RUN_TEST(bridge_code_spaces);
    RUN_TEST(bridge_round_trip);
    RUN_TEST(tunnel_city_model);
    RUN_TEST(tunnel_attributes);
    RUN_TEST(tunnel_code_spaces);
    RUN_TEST(tunnel_round_trip);
    RUN_TEST(vegetation_city_model);
    RUN_TEST(vegetation_tree);
    RUN_TEST(vegetation_implicit_geometry);
    RUN_TEST(vegetation_point_relative_geometry);
    RUN_TEST(vegetation_library_object);
    RUN_TEST(vegetation_plant_cover);
    RUN_TEST(vegetation_code_spaces);
    RUN_TEST(vegetation_round_trip);
    RUN_TEST(furniture_attributes);
    RUN_TEST(furniture_code_spaces);
    RUN_TEST(building_city_model);
    RUN_TEST(building_relation);
    RUN_TEST(building_attribute_set);
    RUN_TEST(building_construction);
    RUN_TEST(building_boundaries);
    RUN_TEST(building_terrain_intersection_curve);
    RUN_TEST(building_round_trip);
    RUN_TEST(transportation_section);
    RUN_TEST(transportation_point);
    RUN_TEST(transportation_curves);
    RUN_TEST(geometry_skipped_members);
    return UNITY_END();
}
