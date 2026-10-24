// The cases of crates/ecitygml/tests/conformance/railway-scene.md.
#include "conformance/conformance.h"

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractGeometryKind.h"
#include "AbstractGeometryProperty.h"
#include "AbstractReliefComponentKind.h"
#include "AbstractReliefComponentProperty.h"
#include "AbstractReliefComponentPropertyIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSurfacePropertyIterator.h"
#include "Bridge.h"
#include "CityFurniture.h"
#include "CityFurnitureFunctionValue.h"
#include "CityFurnitureFunctionValueIterator.h"
#include "CityFurnitureUsageValueIterator.h"
#include "CitygmlFormat.h"
#include "DateTime.h"
#include "DirectPosition.h"
#include "Error.h"
#include "FeatureType.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "HRef.h"
#include "Id.h"
#include "ImplicitGeometry.h"
#include "ImplicitGeometryProperty.h"
#include "LevelOfDetail.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Point.h"
#include "PointProperty.h"
#include "RelativeToTerrain.h"
#include "ReliefFeature.h"
#include "SolitaryVegetationObject.h"
#include "SolitaryVegetationObjectClassValue.h"
#include "SolitaryVegetationObjectFunctionValue.h"
#include "SolitaryVegetationObjectFunctionValueIterator.h"
#include "SolitaryVegetationObjectUsageValueIterator.h"
#include "SpeciesValue.h"
#include "TinProperty.h"
#include "TinRelief.h"
#include "TransformationMatrix4x4.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Tunnel.h"
#include "TunnelFunctionValueIterator.h"
#include "TunnelPartPropertyIterator.h"
#include "TunnelUsageValueIterator.h"

#define RAILWAY FIXTURE("railway-scene/Railway_Scene_LoD3__v3-thinned.gml")
#define TEMPLATE_A "#Mult_SO043561_5693_194007"
#define TEMPLATE_B "#Mult_SO045475_3243_790864"

/// The features of the fixture.
#define MAX_FEATURES 256
/// The longest id or href of the fixture, plus the terminating zero.
#define MAX_STRING 96

#define WALL FeatureType_WallSurface
#define ROOF FeatureType_RoofSurface
#define GROUND FeatureType_GroundSurface
#define CLOSURE FeatureType_ClosureSurface

#define LEN(array) (sizeof(array) / sizeof((array)[0]))

void setUp(void) {}
void tearDown(void) {}

/// An href as written, into `out`.
static void href_string(const HRef *href, char out[MAX_STRING]) {
    DiplomatWrite *write = diplomat_buffer_write_create(64);
    ecitygml_HRef_to_string(href, write);
    size_t len = diplomat_buffer_write_len(write);
    TEST_ASSERT_LESS_THAN_size_t(MAX_STRING, len);
    memcpy(out, diplomat_buffer_write_get_bytes(write), len);
    out[len] = '\0';
    diplomat_buffer_write_destroy(write);
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

/// Declares `all_<T>`: the features `T::try_from` accepts, into `out` (borrowed from the model); returns their number.
#define DEFINE_ALL_OF(T)                                                                         \
    static size_t all_##T(const CityModel *city_model, const T **out, size_t max) {              \
        size_t len = 0;                                                                          \
        AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model); \
        AbstractFeatureKindRef *feature;                                                         \
        while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {     \
            const T *x = ecitygml_##T##_try_from(feature);                                       \
            if (x != NULL) {                                                                     \
                TEST_ASSERT_LESS_THAN_size_t(max, len);                                          \
                out[len++] = x;                                                                  \
            }                                                                                    \
            ecitygml_AbstractFeatureKindRef_destroy(feature);                                    \
        }                                                                                        \
        ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);                               \
        return len;                                                                              \
    }

DEFINE_ALL_OF(Tunnel)
DEFINE_ALL_OF(SolitaryVegetationObject)
DEFINE_ALL_OF(CityFurniture)
DEFINE_ALL_OF(Building)
DEFINE_ALL_OF(Bridge)
DEFINE_ALL_OF(ReliefFeature)
DEFINE_ALL_OF(TinRelief)

/// A tree's inline LoD3 implicit geometry.
static const ImplicitGeometry *implicit_geometry(const SolitaryVegetationObject *tree) {
    const ImplicitGeometryProperty *property = ecitygml_SolitaryVegetationObject_lod3_implicit_representation(tree);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_ImplicitGeometryProperty_href(property));
    const ImplicitGeometry *geometry = ecitygml_ImplicitGeometryProperty_object(property);
    TEST_ASSERT_NOT_NULL(geometry);
    return geometry;
}

/// The href of a tree's relative geometry into `out` ("" if it is inline).
static void template_href(const SolitaryVegetationObject *tree, char out[MAX_STRING]) {
    const AbstractGeometryProperty *property = ecitygml_ImplicitGeometry_relative_geometry(implicit_geometry(tree));
    TEST_ASSERT_NOT_NULL(property);
    const HRef *href = ecitygml_AbstractGeometryProperty_href(property);
    if (href != NULL) {
        href_string(href, out);
    } else {
        out[0] = '\0';
    }
}

static double matrix(const ImplicitGeometry *geometry, size_t row, size_t column) {
    ecitygml_TransformationMatrix4x4_get_result value =
        ecitygml_TransformationMatrix4x4_get(ecitygml_ImplicitGeometry_transformation_matrix(geometry), row, column);
    TEST_ASSERT_TRUE(value.is_ok);
    return value.ok;
}

/// Whether the borrowed string equals `expected`.
static bool equals(DiplomatStringView view, const char *expected) {
    return view.len == strlen(expected) && memcmp(view.data, expected, view.len) == 0;
}

static void test_railway_city_model(void) {
    static const struct {
        FeatureType type;
        size_t count;
    } expected[] = {
        {FeatureType_CityModel, 1},
        {FeatureType_SolitaryVegetationObject, 15},
        {FeatureType_Tunnel, 4},
        {FeatureType_TunnelInstallation, 8},
        {FeatureType_Railway, 10},
        {FeatureType_Bridge, 4},
        {FeatureType_BridgeConstructiveElement, 3},
        {FeatureType_BridgeInstallation, 2},
        {FeatureType_Building, 3},
        {FeatureType_BuildingInstallation, 56},
        {FeatureType_CityFurniture, 11},
        {FeatureType_CityObjectGroup, 1},
        {FeatureType_GenericOccupiedSpace, 2},
        {FeatureType_WaterBody, 1},
        {FeatureType_WaterSurface, 1},
        {FeatureType_WaterGroundSurface, 1},
        {FeatureType_ReliefFeature, 1},
        {FeatureType_TinRelief, 1},
        {WALL, 33},
        {ROOF, 12},
        {GROUND, 7},
        {CLOSURE, 8},
        {FeatureType_DoorSurface, 9},
        {FeatureType_WindowSurface, 34},
        {FeatureType_OuterCeilingSurface, 3},
        {FeatureType_OuterFloorSurface, 1},
    };
    CityModel *city_model = read(RAILWAY);
    TEST_ASSERT_EQUAL_size_t(52, ecitygml_CityModel_city_objects_len(city_model));
    TEST_ASSERT_NULL(ecitygml_CityModel_bounded_by(city_model));
    FeatureType types[MAX_FEATURES];
    size_t len = feature_types(city_model, types);
    TEST_ASSERT_EQUAL_size_t(232, len);
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, types[0]);
    size_t total = 0;
    for (size_t i = 0; i < LEN(expected); i++) {
        size_t count = 0;
        for (size_t j = 0; j < len; j++) {
            if (types[j] == expected[i].type) count++;
        }
        TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].count, count, "feature type");
        total += expected[i].count;
    }
    TEST_ASSERT_EQUAL_size_t(len, total);
    size_t objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        objects++;
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    TEST_ASSERT_EQUAL_size_t(231, objects);
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_tunnels(void) {
    static const struct {
        const char *id;
        const char *name;
        FeatureType boundaries[6];
    } expected[] = {
        {"GMLID_BUI142242_863_347", "Tunnel KIT/KHH-3", {GROUND, WALL, ROOF, WALL, CLOSURE, CLOSURE}},
        {"GMLID_BUI336993_213_9312", "Tunnel KIT/KHH-2", {WALL, ROOF, WALL, CLOSURE, CLOSURE, GROUND}},
        {"GMLID_BUI289877_1911_4122", "Tunnel KIT/KHH-4", {WALL, GROUND, CLOSURE, WALL, ROOF, CLOSURE}},
        {"GMLID_BUI180021_673_14143", "Tunnel KIT/KHH-1", {GROUND, WALL, ROOF, CLOSURE, CLOSURE, WALL}},
    };
    CityModel *city_model = read(RAILWAY);
    const Tunnel *tunnels[5];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), all_Tunnel(city_model, tunnels, 5));
    for (size_t i = 0; i < LEN(expected); i++) {
        const Tunnel *tunnel = tunnels[i];
        ASSERT_STR(expected[i].id, ecitygml_Id_as_str(ecitygml_Tunnel_feature_id(tunnel)));
        ASSERT_STR(expected[i].name, first_name(ecitygml_Tunnel_names(tunnel)));
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Tunnel_boundaries(tunnel);
        const AbstractSpaceBoundaryProperty *property;
        size_t len = 0;
        while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries)) != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(6, len);
            TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(property));
            const AbstractSpaceBoundaryKind *object = ecitygml_AbstractSpaceBoundaryProperty_object(property);
            TEST_ASSERT_NOT_NULL(object);
            TEST_ASSERT_EQUAL_INT(expected[i].boundaries[len++], ecitygml_AbstractSpaceBoundaryKind_feature_type(object));
        }
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
        TEST_ASSERT_EQUAL_size_t(6, len);
        TEST_ASSERT_NULL(ecitygml_Tunnel_class(tunnel));
        TunnelFunctionValueIterator *functions = ecitygml_Tunnel_functions(tunnel);
        TEST_ASSERT_NULL(ecitygml_TunnelFunctionValueIterator_next(functions));
        ecitygml_TunnelFunctionValueIterator_destroy(functions);
        TunnelUsageValueIterator *usages = ecitygml_Tunnel_usages(tunnel);
        TEST_ASSERT_NULL(ecitygml_TunnelUsageValueIterator_next(usages));
        ecitygml_TunnelUsageValueIterator_destroy(usages);
        TunnelPartPropertyIterator *parts = ecitygml_Tunnel_tunnel_parts(tunnel);
        TEST_ASSERT_NULL(ecitygml_TunnelPartPropertyIterator_next(parts));
        ecitygml_TunnelPartPropertyIterator_destroy(parts);
        const DateTime *created = ecitygml_Tunnel_creation_date(tunnel);
        TEST_ASSERT_NOT_NULL(created);
        TEST_ASSERT_EQUAL_INT32(2015, ecitygml_DateTime_year(created));
        TEST_ASSERT_EQUAL_UINT32(3, ecitygml_DateTime_month(created));
        TEST_ASSERT_EQUAL_UINT32(6, ecitygml_DateTime_day(created));
        TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_hour(created));
        TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_minute(created));
        TEST_ASSERT_EQUAL_INT32(3600, ecitygml_DateTime_offset_seconds(created));
        ecitygml_Tunnel_relative_to_terrain_result terrain = ecitygml_Tunnel_relative_to_terrain(tunnel);
        TEST_ASSERT_TRUE(terrain.is_ok);
        TEST_ASSERT_EQUAL_INT(RelativeToTerrain_EntirelyAboveTerrain, terrain.ok);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_trees(void) {
    static const struct {
        const char *id;
        const char *name;
        const char *class_value;
        const char *species;
        const char *function;
    } expected[] = {
        {"GMLID_SO0158953_776_12462", "Forest tree 3", "1070", "1800", NULL},
        {"GMLID_SO092422_3593_9527", "Tree1", NULL, "9999", "LOD3"},
        {"GMLID_SO0200811_525_4986", "Forest tree 1", "1060", "1640", NULL},
        {"GMLID_SO0321978_1466_7441", "Forest tree 4", "1070", "1800", NULL},
        {"GMLID_SO0260143_1214_1315", "Forest tree 11", "1060", "1640", NULL},
        {"GMLID_SO0400934_2926_3381", "Forest tree 12", "1060", "1640", NULL},
        {"GMLID_SO0124800_3522_13577", "Forest tree 13", "1060", "1640", NULL},
        {"GMLID_SO0443764_1492_9667", "Forest tree 14", "1060", "1640", NULL},
        {"GMLID_SO015374_872_14131", "Forest tree 2", "1060", "1640", NULL},
        {"GMLID_SO081792_2341_11961", "Forest tree 10", "1060", "1640", NULL},
        {"GMLID_SO0283142_1335_8999", "Forest tree 7", "1060", "1640", NULL},
        {"GMLID_SO0107241_3793_12555", "Forest tree 9", "1070", "1800", NULL},
        {"GMLID_SO0286258_965_2893", "Forest tree 5", "1070", "1800", NULL},
        {"GMLID_SO0410128_214_10515", "Forest tree 6", "1060", "1640", NULL},
        {"GMLID_SO086970_1053_8814", "Forest tree 8", "1060", "1640", NULL},
    };
    CityModel *city_model = read(RAILWAY);
    const SolitaryVegetationObject *trees[16];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), all_SolitaryVegetationObject(city_model, trees, 16));
    for (size_t i = 0; i < LEN(expected); i++) {
        const SolitaryVegetationObject *tree = trees[i];
        ASSERT_STR(expected[i].id, ecitygml_Id_as_str(ecitygml_SolitaryVegetationObject_feature_id(tree)));
        ASSERT_STR(expected[i].name, first_name(ecitygml_SolitaryVegetationObject_names(tree)));
        const SolitaryVegetationObjectClassValue *class_value = ecitygml_SolitaryVegetationObject_class(tree);
        if (expected[i].class_value == NULL) {
            TEST_ASSERT_NULL(class_value);
        } else {
            TEST_ASSERT_NOT_NULL(class_value);
            ASSERT_STR(expected[i].class_value, ecitygml_SolitaryVegetationObjectClassValue_value(class_value));
        }
        const SpeciesValue *species = ecitygml_SolitaryVegetationObject_species(tree);
        TEST_ASSERT_NOT_NULL(species);
        ASSERT_STR(expected[i].species, ecitygml_SpeciesValue_value(species));
        SolitaryVegetationObjectFunctionValueIterator *functions = ecitygml_SolitaryVegetationObject_functions(tree);
        if (expected[i].function != NULL) {
            ASSERT_STR(expected[i].function, ecitygml_SolitaryVegetationObjectFunctionValue_value(
                                                 ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(functions)));
        }
        TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(functions));
        ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(functions);
        SolitaryVegetationObjectUsageValueIterator *usages = ecitygml_SolitaryVegetationObject_usages(tree);
        TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObjectUsageValueIterator_next(usages));
        ecitygml_SolitaryVegetationObjectUsageValueIterator_destroy(usages);
        TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod1_implicit_representation(tree));
        TEST_ASSERT_NULL(ecitygml_SolitaryVegetationObject_lod2_implicit_representation(tree));
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_tree_templates(void) {
    CityModel *city_model = read(RAILWAY);
    const SolitaryVegetationObject *trees[16];
    size_t len = all_SolitaryVegetationObject(city_model, trees, 16);
    for (size_t i = 0; i < len; i++) {
        const ImplicitGeometry *geometry = implicit_geometry(trees[i]);
        TEST_ASSERT_NULL(ecitygml_ImplicitGeometry_mime_type(geometry));
        static const double diagonal[] = {30.0, 30.0, 30.0, 1.0};
        for (size_t j = 0; j < 4; j++) {
            ASSERT_CLOSE(diagonal[j], matrix(geometry, j, j));
        }
        DiplomatStringView name = first_name(ecitygml_SolitaryVegetationObject_names(trees[i]));
        const AbstractGeometryProperty *property = ecitygml_ImplicitGeometry_relative_geometry(geometry);
        TEST_ASSERT_NOT_NULL(property);
        if (equals(name, "Forest tree 3") || equals(name, "Tree1") || equals(name, "Forest tree 1")) {
            TEST_ASSERT_NULL(ecitygml_AbstractGeometryProperty_href(property));
            const AbstractGeometryKind *object = ecitygml_AbstractGeometryProperty_object(property);
            TEST_ASSERT_NOT_NULL(object);
            const MultiSurface *multi_surface = ecitygml_MultiSurface_try_from(object);
            TEST_ASSERT_NOT_NULL(multi_surface);
            AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
            TEST_ASSERT_NOT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
            TEST_ASSERT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
            ecitygml_AbstractSurfacePropertyIterator_destroy(members);
        } else {
            TEST_ASSERT_NULL(ecitygml_AbstractGeometryProperty_object(property));
            bool template_a =
                equals(name, "Forest tree 4") || equals(name, "Forest tree 9") || equals(name, "Forest tree 5");
            char href[MAX_STRING];
            template_href(trees[i], href);
            TEST_ASSERT_EQUAL_STRING(template_a ? TEMPLATE_A : TEMPLATE_B, href);
        }
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_tree_placement(void) {
    CityModel *city_model = read(RAILWAY);
    const SolitaryVegetationObject *trees[16];
    size_t len = all_SolitaryVegetationObject(city_model, trees, 16);
    for (size_t i = 0; i < len; i++) {
        const ImplicitGeometry *geometry = implicit_geometry(trees[i]);
        const Point *point = ecitygml_PointProperty_object(ecitygml_ImplicitGeometry_reference_point(geometry));
        TEST_ASSERT_NOT_NULL(point);
        const DirectPosition *pos = ecitygml_Point_pos(point);
        DiplomatStringView name = first_name(ecitygml_SolitaryVegetationObject_names(trees[i]));
        bool tree1 = equals(name, "Tree1");
        ASSERT_CLOSE(tree1 ? -568.8000793496976 : -600.0, ecitygml_DirectPosition_x(pos));
        ASSERT_CLOSE(tree1 ? 457.60044759869743 : 400.0, ecitygml_DirectPosition_y(pos));
        ASSERT_CLOSE(tree1 ? 105.00139681350242 : -150.0, ecitygml_DirectPosition_z(pos));
        if (tree1) {
            for (size_t row = 0; row < 3; row++) ASSERT_CLOSE(0.0, matrix(geometry, row, 3));
        } else if (equals(name, "Forest tree 3")) {
            ASSERT_CLOSE(39.4421005419207, matrix(geometry, 0, 3));
            ASSERT_CLOSE(220.3838834926932, matrix(geometry, 1, 3));
            ASSERT_CLOSE(268.5013679006178, matrix(geometry, 2, 3));
        }
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_furniture(void) {
    static const char *const expected[][2] = {
        {"GMLID_7431654_78949_792", "1090"},   {"GMLID_0528986_170479_94", "OTHERS"},
        {"GMLID_4323540_367099_910", "1090"},  {"GMLID_1381455_184173_656", "OTHERS"},
        {"GMLID_1429491_351612_1485", "1090"}, {"GMLID_5361967_192822_672", "1090"},
        {"GMLID_2108434_31807_876", "1090"},   {"GMLID_0373494_301709_129", "1540"},
        {"GMLID_6162422_289094_1279", "1090"}, {"GMLID_3313190_307178_612", "1090"},
        {"GMLID_855011_330784_753", "1540"},
    };
    CityModel *city_model = read(RAILWAY);
    const CityFurniture *furniture[12];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), all_CityFurniture(city_model, furniture, 12));
    for (size_t i = 0; i < LEN(expected); i++) {
        const CityFurniture *item = furniture[i];
        ASSERT_STR(expected[i][0], ecitygml_Id_as_str(ecitygml_CityFurniture_feature_id(item)));
        CityFurnitureFunctionValueIterator *functions = ecitygml_CityFurniture_functions(item);
        ASSERT_STR(expected[i][1],
                   ecitygml_CityFurnitureFunctionValue_value(ecitygml_CityFurnitureFunctionValueIterator_next(functions)));
        TEST_ASSERT_NULL(ecitygml_CityFurnitureFunctionValueIterator_next(functions));
        ecitygml_CityFurnitureFunctionValueIterator_destroy(functions);
        TEST_ASSERT_NULL(ecitygml_CityFurniture_class(item));
        CityFurnitureUsageValueIterator *usages = ecitygml_CityFurniture_usages(item);
        TEST_ASSERT_NULL(ecitygml_CityFurnitureUsageValueIterator_next(usages));
        ecitygml_CityFurnitureUsageValueIterator_destroy(usages);
        TEST_ASSERT_NULL(ecitygml_CityFurniture_lod3_implicit_representation(item));
        const MultiSurfaceProperty *property = ecitygml_CityFurniture_lod3_multi_surface(item);
        TEST_ASSERT_NOT_NULL(property);
        TEST_ASSERT_NULL(ecitygml_MultiSurfaceProperty_href(property));
        AbstractSurfacePropertyIterator *members =
            ecitygml_MultiSurface_surface_member(ecitygml_MultiSurfaceProperty_object(property));
        TEST_ASSERT_NOT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
        TEST_ASSERT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
        ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_relief(void) {
    CityModel *city_model = read(RAILWAY);
    const ReliefFeature *reliefs[2];
    TEST_ASSERT_EQUAL_size_t(1, all_ReliefFeature(city_model, reliefs, 2));
    ASSERT_STR("GMLID_TIN436865_187531_1154", ecitygml_Id_as_str(ecitygml_ReliefFeature_feature_id(reliefs[0])));
    CodeIterator *names = ecitygml_ReliefFeature_names(reliefs[0]);
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    TEST_ASSERT_EQUAL_INT(LevelOfDetail_Three, ecitygml_ReliefFeature_lod(reliefs[0]));
    AbstractReliefComponentPropertyIterator *components = ecitygml_ReliefFeature_relief_components(reliefs[0]);
    const AbstractReliefComponentProperty *component = ecitygml_AbstractReliefComponentPropertyIterator_next(components);
    TEST_ASSERT_NOT_NULL(component);
    TEST_ASSERT_NULL(ecitygml_AbstractReliefComponentPropertyIterator_next(components));
    TEST_ASSERT_NULL(ecitygml_AbstractReliefComponentProperty_href(component));
    TEST_ASSERT_EQUAL_INT(FeatureType_TinRelief, ecitygml_AbstractReliefComponentKind_feature_type(
                                                     ecitygml_AbstractReliefComponentProperty_object(component)));
    ecitygml_AbstractReliefComponentPropertyIterator_destroy(components);

    const TinRelief *tin_reliefs[2];
    TEST_ASSERT_EQUAL_size_t(1, all_TinRelief(city_model, tin_reliefs, 2));
    ASSERT_STR("UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9", ecitygml_Id_as_str(ecitygml_TinRelief_feature_id(tin_reliefs[0])));
    TEST_ASSERT_EQUAL_INT(LevelOfDetail_Three, ecitygml_TinRelief_lod(tin_reliefs[0]));
    const TinProperty *tin = ecitygml_TinRelief_tin(tin_reliefs[0]);
    TEST_ASSERT_NOT_NULL(tin);
    TEST_ASSERT_NULL(ecitygml_TinProperty_href(tin));
    const TriangulatedSurface *surface = ecitygml_TinProperty_object(tin);
    TEST_ASSERT_NOT_NULL(surface);
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(surface);
    TEST_ASSERT_NOT_NULL(ecitygml_TriangleIterator_next(triangles));
    TEST_ASSERT_NULL(ecitygml_TriangleIterator_next(triangles));
    ecitygml_TriangleIterator_destroy(triangles);
    ecitygml_TriangulatedSurface_area_3d_result area = ecitygml_TriangulatedSurface_area_3d(surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(3.2750424144626247, area.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void test_railway_buildings_and_bridges(void) {
    static const struct {
        const char *id;
        const char *name;
        size_t boundaries;
    } buildings_expected[] = {
        {"GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13},
        {"GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19},
        {"GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8},
    };
    static const char *const bridges_expected[][2] = {
        {"GMLID_BUI205585_1385_1373", "Bridge KIT 4"},
        {"GMLID_BUI51891_765_738", "Bridge KIT 3"},
        {"GMLID_BUI100628_817_8083", "Bridge KIT 2"},
        {"GMLID_BUI30683_572_6686", "Bridge KIT 1"},
    };
    CityModel *city_model = read(RAILWAY);
    const Building *buildings[4];
    TEST_ASSERT_EQUAL_size_t(LEN(buildings_expected), all_Building(city_model, buildings, 4));
    for (size_t i = 0; i < LEN(buildings_expected); i++) {
        ASSERT_STR(buildings_expected[i].id, ecitygml_Id_as_str(ecitygml_Building_feature_id(buildings[i])));
        ASSERT_STR(buildings_expected[i].name, first_name(ecitygml_Building_names(buildings[i])));
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Building_boundaries(buildings[i]);
        size_t count = 0;
        while (ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries) != NULL) count++;
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
        TEST_ASSERT_EQUAL_size_t(buildings_expected[i].boundaries, count);
    }
    const Bridge *bridges[5];
    TEST_ASSERT_EQUAL_size_t(LEN(bridges_expected), all_Bridge(city_model, bridges, 5));
    for (size_t i = 0; i < LEN(bridges_expected); i++) {
        ASSERT_STR(bridges_expected[i][0], ecitygml_Id_as_str(ecitygml_Bridge_feature_id(bridges[i])));
        ASSERT_STR(bridges_expected[i][1], first_name(ecitygml_Bridge_names(bridges[i])));
    }
    ecitygml_CityModel_destroy(city_model);
}

/// A borrowed string view, copied into `out`.
static void copy_view(DiplomatStringView view, char out[MAX_STRING]) {
    TEST_ASSERT_LESS_THAN_size_t(MAX_STRING, view.len);
    memcpy(out, view.data, view.len);
    out[view.len] = '\0';
}

/// The most ids `railway_ids` collects.
#define MAX_IDS 40

/// Declares `ids_<T>`: the `feature_id`s of the features `T::try_from` accepts, appended to `out` from `len`;
/// returns the new number.
#define DEFINE_IDS_OF(T, max)                                                              \
    static size_t ids_##T(const CityModel *city_model, char out[][MAX_STRING], size_t len) { \
        const T *features[max];                                                            \
        size_t n = all_##T(city_model, features, max);                                     \
        for (size_t i = 0; i < n; i++) {                                                   \
            TEST_ASSERT_LESS_THAN_size_t(MAX_IDS, len);                                    \
            copy_view(ecitygml_Id_as_str(ecitygml_##T##_feature_id(features[i])), out[len++]); \
        }                                                                                  \
        return len;                                                                        \
    }

DEFINE_IDS_OF(Tunnel, 5)
DEFINE_IDS_OF(SolitaryVegetationObject, 16)
DEFINE_IDS_OF(CityFurniture, 12)
DEFINE_IDS_OF(Building, 4)
DEFINE_IDS_OF(Bridge, 5)

/// The `feature_id`s of the tunnels, trees, city furniture, buildings and bridges, into `out`; returns their number.
static size_t railway_ids(const CityModel *city_model, char out[][MAX_STRING]) {
    size_t len = ids_Tunnel(city_model, out, 0);
    len = ids_SolitaryVegetationObject(city_model, out, len);
    len = ids_CityFurniture(city_model, out, len);
    len = ids_Building(city_model, out, len);
    return ids_Bridge(city_model, out, len);
}

static void test_railway_round_trip(void) {
    CityModel *city_model = read(RAILWAY);
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

    static char original_ids[MAX_IDS][MAX_STRING];
    static char written_ids[MAX_IDS][MAX_STRING];
    size_t ids = railway_ids(city_model, original_ids);
    TEST_ASSERT_EQUAL_size_t(ids, railway_ids(written.ok, written_ids));
    for (size_t i = 0; i < ids; i++) TEST_ASSERT_EQUAL_STRING(original_ids[i], written_ids[i]);

    const SolitaryVegetationObject *a[16];
    const SolitaryVegetationObject *b[16];
    size_t trees = all_SolitaryVegetationObject(city_model, a, 16);
    TEST_ASSERT_EQUAL_size_t(trees, all_SolitaryVegetationObject(written.ok, b, 16));
    for (size_t i = 0; i < trees; i++) {
        char href_a[MAX_STRING];
        char href_b[MAX_STRING];
        template_href(a[i], href_a);
        template_href(b[i], href_b);
        TEST_ASSERT_EQUAL_STRING(href_a, href_b);
    }
    ecitygml_CityModel_destroy(written.ok);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_railway_city_model);
    RUN_TEST(test_railway_tunnels);
    RUN_TEST(test_railway_trees);
    RUN_TEST(test_railway_tree_templates);
    RUN_TEST(test_railway_tree_placement);
    RUN_TEST(test_railway_furniture);
    RUN_TEST(test_railway_relief);
    RUN_TEST(test_railway_buildings_and_bridges);
    RUN_TEST(test_railway_round_trip);
    return UNITY_END();
}
