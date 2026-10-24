// The cases of crates/ecitygml/tests/conformance/fzk-haus.md.
#include "conformance/conformance.h"

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractFillingSurfaceKind.h"
#include "AbstractFillingSurfaceProperty.h"
#include "AbstractFillingSurfacePropertyIterator.h"
#include "AbstractRingKind.h"
#include "AbstractRingKindIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSurfaceKind.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "BoundingShape.h"
#include "BuildingClassValue.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingPartPropertyIterator.h"
#include "BuildingUsageValue.h"
#include "BuildingUsageValueIterator.h"
#include "CityObjectRelationPropertyIterator.h"
#include "CitygmlFormat.h"
#include "CompositeSurface.h"
#include "Date.h"
#include "DateTime.h"
#include "DirectPosition.h"
#include "DirectPositionIterator.h"
#include "DoorSurface.h"
#include "ElevationReferenceValue.h"
#include "Envelope.h"
#include "Error.h"
#include "ExternalReferenceIterator.h"
#include "FeatureType.h"
#include "GenericAttributeKind.h"
#include "GenericAttributeKindIterator.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "GroundSurface.h"
#include "Height.h"
#include "HeightIterator.h"
#include "HeightStatusValue.h"
#include "Id.h"
#include "Length.h"
#include "LinearRing.h"
#include "Measure.h"
#include "MeasureAttribute.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "OccupancyIterator.h"
#include "Polygon.h"
#include "RelativeToTerrain.h"
#include "RelativeToWater.h"
#include "RoofSurface.h"
#include "RoofTypeValue.h"
#include "Scale3.h"
#include "Shell.h"
#include "ShellIterator.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "StringAttribute.h"
#include "Triangle.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"
#include "TriangulationSkippedIterator.h"
#include "Vector3.h"
#include "WallSurface.h"
#include "WindowSurface.h"

#define LOD1 FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
#define LOD2 FIXTURE("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
#define LOD3 FIXTURE("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")

void setUp(void) {}
void tearDown(void) {}

/// The LoD2 area of a multi surface property.
static double lod2_area(const MultiSurfaceProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    ecitygml_MultiSurface_area_3d_result area =
        ecitygml_MultiSurface_area_3d(ecitygml_MultiSurfaceProperty_object(property));
    TEST_ASSERT_TRUE(area.is_ok);
    return area.ok;
}

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    TEST_ASSERT_NOT_NULL(position);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
}

// Each count_* takes the iterator, counts its items and destroys it.

static size_t count_positions(DirectPositionIterator *iterator) {
    size_t count = 0;
    while (ecitygml_DirectPositionIterator_next(iterator) != NULL) count++;
    ecitygml_DirectPositionIterator_destroy(iterator);
    return count;
}

static size_t count_triangles(TriangleIterator *iterator) {
    size_t count = 0;
    while (ecitygml_TriangleIterator_next(iterator) != NULL) count++;
    ecitygml_TriangleIterator_destroy(iterator);
    return count;
}

static size_t count_surface_members(AbstractSurfacePropertyIterator *iterator) {
    size_t count = 0;
    while (ecitygml_AbstractSurfacePropertyIterator_next(iterator) != NULL) count++;
    ecitygml_AbstractSurfacePropertyIterator_destroy(iterator);
    return count;
}

static size_t count_fillings(AbstractFillingSurfacePropertyIterator *iterator) {
    size_t count = 0;
    while (ecitygml_AbstractFillingSurfacePropertyIterator_next(iterator) != NULL) count++;
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(iterator);
    return count;
}

/// The number of triangles of a triangulation; destroys it.
static size_t triangulation_triangles(Triangulation *triangulation) {
    size_t count = count_triangles(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation)));
    ecitygml_Triangulation_destroy(triangulation);
    return count;
}

/// The polygon of a surface property; it borrows from the model.
static const Polygon *polygon_of(const AbstractSurfaceProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    const AbstractSurfaceKind *surface = ecitygml_AbstractSurfaceProperty_object(property);
    TEST_ASSERT_NOT_NULL(surface);
    const Polygon *polygon = ecitygml_Polygon_try_from(surface);
    TEST_ASSERT_NOT_NULL(polygon);
    return polygon;
}

/// The first polygon of a surface property iterator; destroys the iterator. It borrows from the model.
static const Polygon *first_polygon(AbstractSurfacePropertyIterator *members) {
    const Polygon *polygon = polygon_of(ecitygml_AbstractSurfacePropertyIterator_next(members));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    return polygon;
}

/// Asserts the first point of the iterator; destroys the iterator.
static void assert_first_point(double x, double y, double z, DirectPositionIterator *points) {
    assert_point_close(x, y, z, ecitygml_DirectPositionIterator_next(points));
    ecitygml_DirectPositionIterator_destroy(points);
}

/// The most features a fixture of this file has.
#define MAX_FEATURES 32

/// All features of the city model, into `out`; returns their number. Destroy them with `destroy_features`.
static size_t all_features(const CityModel *city_model, AbstractFeatureKindRef **out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = feature;
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    return len;
}

/// The feature types of `iter_city_objects`, into `out`; returns their number.
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

/// Whether each wall surface has a `bounded_by`, into `out`; returns the number of wall surfaces.
static size_t walls_bounded(const CityModel *city_model, bool *out) {
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    size_t walls = 0;
    for (size_t i = 0; i < len; i++) {
        const WallSurface *wall = ecitygml_WallSurface_try_from(features[i]);
        if (wall != NULL) out[walls++] = ecitygml_WallSurface_bounded_by(wall) != NULL;
    }
    destroy_features(features, len);
    return walls;
}

/// Asserts the lower corners of the city model's envelope and of the first wall surface's.
static void assert_lower_corners(double x, double y, double z, const CityModel *city_model) {
    assert_point_close(x, y, z,
                       ecitygml_Envelope_lower_corner(ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model))));
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    const WallSurface *wall = NULL;
    for (size_t i = 0; wall == NULL && i < len; i++) wall = ecitygml_WallSurface_try_from(features[i]);
    TEST_ASSERT_NOT_NULL(wall);
    assert_point_close(x, y, z,
                       ecitygml_Envelope_lower_corner(ecitygml_BoundingShape_envelope(ecitygml_WallSurface_bounded_by(wall))));
    destroy_features(features, len);
}

// FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml

static void test_lod1_city_model(void) {
    CityModel *city_model = read(LOD1);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    const DirectPosition *lower = ecitygml_Envelope_lower_corner(envelope);
    const DirectPosition *upper = ecitygml_Envelope_upper_corner(envelope);
    ASSERT_CLOSE(457842.0, ecitygml_DirectPosition_x(lower));
    ASSERT_CLOSE(5439083.0, ecitygml_DirectPosition_y(lower));
    ASSERT_CLOSE(111.8, ecitygml_DirectPosition_z(lower));
    ASSERT_CLOSE(457854.0, ecitygml_DirectPosition_x(upper));
    ASSERT_CLOSE(5439093.0, ecitygml_DirectPosition_y(upper));
    ASSERT_CLOSE(118.317669, ecitygml_DirectPosition_z(upper));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_building_attributes(void) {
    CityModel *city_model = read(LOD1);
    const Building *b = first_building(city_model);
    ASSERT_STR("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    CodeIterator *names = ecitygml_Building_names(b);
    ASSERT_STR("AC14-FZK-Haus", ecitygml_Code_value(ecitygml_CodeIterator_next(names)));
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    ASSERT_STR("1000", ecitygml_BuildingClassValue_value(ecitygml_Building_class(b)));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    ASSERT_STR("1000", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    ASSERT_STR("1000", ecitygml_BuildingUsageValue_value(ecitygml_BuildingUsageValueIterator_next(usages)));
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("1030", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    ecitygml_Building_storeys_above_ground_result above = ecitygml_Building_storeys_above_ground(b);
    ecitygml_Building_storeys_below_ground_result below = ecitygml_Building_storeys_below_ground(b);
    TEST_ASSERT_TRUE(above.is_ok && below.is_ok);
    TEST_ASSERT_EQUAL_INT64(2, above.ok);
    TEST_ASSERT_EQUAL_INT64(0, below.ok);

    const Date *date = ecitygml_Building_date_of_construction(b);
    TEST_ASSERT_NOT_NULL(date);
    TEST_ASSERT_EQUAL_INT32(2020, ecitygml_Date_year(date));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_month(date));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_day(date));
    TEST_ASSERT_NULL(ecitygml_Building_date_of_demolition(b));
    HeightIterator *heights = ecitygml_Building_heights(b);
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("topOfConstruction", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(6.52, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);
    OccupancyIterator *occupancies = ecitygml_Building_occupancies(b);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    ecitygml_OccupancyIterator_destroy(occupancies);
    BuildingPartPropertyIterator *parts = ecitygml_Building_building_parts(b);
    TEST_ASSERT_NULL(ecitygml_BuildingPartPropertyIterator_next(parts));
    ecitygml_BuildingPartPropertyIterator_destroy(parts);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_solid(void) {
    CityModel *city_model = read(LOD1);
    const Building *b = first_building(city_model);
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod1_solid(b));
    TEST_ASSERT_NOT_NULL(solid);
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
    TEST_ASSERT_TRUE(volume.is_ok);
    ASSERT_CLOSE(782.1228, volume.ok);
    ecitygml_Solid_triangulate_result triangulation = ecitygml_Solid_triangulate(solid);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TriangleIterator *triangles =
        ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok));
    size_t count = 0;
    while (ecitygml_TriangleIterator_next(triangles) != NULL) count++;
    ecitygml_TriangleIterator_destroy(triangles);
    TEST_ASSERT_EQUAL_size_t(12, count);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    ecitygml_Triangulation_destroy(triangulation.ok);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    TEST_ASSERT_EQUAL_size_t(0, boundaries(b, features));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_envelope_measures(void) {
    CityModel *city_model = read(LOD1);
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    ASSERT_CLOSE(12.0, ecitygml_Envelope_size_x(envelope));
    ASSERT_CLOSE(10.0, ecitygml_Envelope_size_y(envelope));
    ASSERT_CLOSE(6.517669, ecitygml_Envelope_size_z(envelope));
    DirectPosition *center = ecitygml_Envelope_center(envelope);
    assert_point_close(457848.0, 5439088.0, 115.0588345, center);
    ecitygml_DirectPosition_destroy(center);
    ASSERT_CLOSE(782.12028, ecitygml_Envelope_volume(envelope));
    TEST_ASSERT_TRUE(ecitygml_Envelope_contains(envelope, ecitygml_Envelope_lower_corner(envelope)));
    TEST_ASSERT_TRUE(ecitygml_Envelope_contains(envelope, ecitygml_Envelope_upper_corner(envelope)));
    const double points[3][3] = {{457848.0, 5439088.0, 115.0}, {457848.0, 5439088.0, 118.4}, {457841.9, 5439088.0, 115.0}};
    const bool contained[3] = {true, false, false};
    for (size_t i = 0; i < 3; i++) {
        ecitygml_DirectPosition_new_result position = ecitygml_DirectPosition_new(points[i][0], points[i][1], points[i][2]);
        TEST_ASSERT_TRUE(position.is_ok);
        TEST_ASSERT_EQUAL(contained[i], ecitygml_Envelope_contains(envelope, position.ok));
        ecitygml_DirectPosition_destroy(position.ok);
    }
    TEST_ASSERT_NULL(ecitygml_CityModel_creation_date(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_building_details(void) {
    CityModel *city_model = read(LOD1);
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    size_t buildings = 0;
    for (size_t i = 0; i < len; i++) {
        buildings += ecitygml_AbstractFeatureKindRef_feature_type(features[i]) == FeatureType_Building;
    }
    destroy_features(features, len);
    TEST_ASSERT_EQUAL_size_t(1, buildings);
    const Building *b = first_building(city_model);
    const Id *id = ecitygml_Building_id(b);
    TEST_ASSERT_NOT_NULL(id);
    ASSERT_STR("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", ecitygml_Id_as_str(id));
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_Building_bounded_by(b));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(457842.0, 5439083.0, 111.8, ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(457854.0, 5439093.0, 118.31769, ecitygml_Envelope_upper_corner(envelope));
    TEST_ASSERT_NULL(ecitygml_Building_lod2_solid(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod0_multi_surface(b));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_solid_structure(void) {
    CityModel *city_model = read(LOD1);
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod1_solid(first_building(city_model)));
    TEST_ASSERT_NOT_NULL(solid);
    ShellIterator *interior = ecitygml_Solid_interior(solid);
    TEST_ASSERT_NULL(ecitygml_ShellIterator_next(interior));
    ecitygml_ShellIterator_destroy(interior);
    TEST_ASSERT_EQUAL_size_t(24, count_positions(ecitygml_Solid_points(solid)));
    const Shell *shell = ecitygml_Solid_exterior(solid);
    TEST_ASSERT_NOT_NULL(shell);
    ecitygml_Shell_volume_3d_result volume = ecitygml_Shell_volume_3d(shell);
    TEST_ASSERT_TRUE(volume.is_ok);
    ASSERT_CLOSE(782.1228, volume.ok);
    const LinearRing *rings[6];
    size_t len = 0;
    AbstractSurfacePropertyIterator *members = ecitygml_Shell_members(shell);
    const AbstractSurfaceProperty *member;
    while ((member = ecitygml_AbstractSurfacePropertyIterator_next(members)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(6, len);
        TEST_ASSERT_NULL(ecitygml_AbstractSurfaceProperty_href(member));
        const Polygon *polygon = polygon_of(member);
        AbstractRingKindIterator *holes = ecitygml_Polygon_interior(polygon);
        TEST_ASSERT_NULL(ecitygml_AbstractRingKindIterator_next(holes));
        ecitygml_AbstractRingKindIterator_destroy(holes);
        const AbstractRingKind *exterior = ecitygml_Polygon_exterior(polygon);
        TEST_ASSERT_NOT_NULL(exterior);
        rings[len] = ecitygml_LinearRing_try_from(exterior);
        TEST_ASSERT_NOT_NULL(rings[len]);
        len++;
    }
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_EQUAL_size_t(6, len);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_size_t(4, count_positions(ecitygml_LinearRing_points(rings[i])));
        TEST_ASSERT_TRUE(ecitygml_LinearRing_area_3d(rings[i]) > 0.0);
    }
    assert_first_point(457842.0, 5439083.0, 111.8, ecitygml_LinearRing_points(rings[0]));
    ASSERT_CLOSE(44.0, ecitygml_LinearRing_length_3d(rings[0]));
    ASSERT_CLOSE(120.0, ecitygml_LinearRing_area_3d(rings[0]));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_solid_triangulation(void) {
    CityModel *city_model = read(LOD1);
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod1_solid(first_building(city_model)));
    TEST_ASSERT_NOT_NULL(solid);
    ecitygml_Solid_triangulate_result triangulation = ecitygml_Solid_triangulate(solid);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TriangulationSkippedIterator *skipped = ecitygml_Triangulation_skipped(triangulation.ok);
    TEST_ASSERT_NULL(ecitygml_TriangulationSkippedIterator_next(skipped));
    ecitygml_TriangulationSkippedIterator_destroy(skipped);
    const TriangulatedSurface *surface = ecitygml_Triangulation_surface(triangulation.ok);
    ecitygml_TriangulatedSurface_area_3d_result area = ecitygml_TriangulatedSurface_area_3d(surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(526.77836, area.ok);
    TEST_ASSERT_EQUAL_size_t(36, count_positions(ecitygml_TriangulatedSurface_points(surface)));
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(surface);
    const Triangle *triangle = ecitygml_TriangleIterator_next(triangles);
    TEST_ASSERT_NOT_NULL(triangle);
    ASSERT_CLOSE(111.8, ecitygml_DirectPosition_z(ecitygml_Triangle_a(triangle)));
    ASSERT_CLOSE(60.0, ecitygml_Triangle_area(triangle));
    ecitygml_TriangleIterator_destroy(triangles);
    ecitygml_Triangulation_destroy(triangulation.ok);

    const Shell *shell = ecitygml_Solid_exterior(solid);
    ecitygml_Shell_triangulate_result shell_triangulation = ecitygml_Shell_triangulate(shell);
    TEST_ASSERT_TRUE(shell_triangulation.is_ok);
    TEST_ASSERT_EQUAL_size_t(12, triangulation_triangles(shell_triangulation.ok));
    ecitygml_Polygon_triangulate_result first = ecitygml_Polygon_triangulate(first_polygon(ecitygml_Shell_members(shell)));
    TEST_ASSERT_TRUE(first.is_ok);
    TEST_ASSERT_EQUAL_size_t(2, triangulation_triangles(first.ok));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod1_apply_scale(void) {
    CityModel *city_model = read(LOD1);
    ecitygml_CityModel_apply_scale(city_model, (Scale3){.x = 2.0, .y = 3.0, .z = 0.5});
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    ASSERT_CLOSE(24.0, ecitygml_Envelope_size_x(envelope));
    ASSERT_CLOSE(30.0, ecitygml_Envelope_size_y(envelope));
    ASSERT_CLOSE(3.2588345, ecitygml_Envelope_size_z(envelope));
    ecitygml_CityModel_destroy(city_model);
}

// FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml

static void test_lod2_boundary_surfaces(void) {
    CityModel *city_model = read(LOD2);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    const FeatureType types[] = {FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
                                 FeatureType_RoofSurface, FeatureType_WallSurface, FeatureType_RoofSurface,
                                 FeatureType_GroundSurface};
    TEST_ASSERT_EQUAL_size_t(7, len);
    const char *walls[] = {"Outer Wall 1 (West)", "Outer Wall 2 (South)", "Outer Wall 3 (East)", "Outer Wall 4 (North)"};
    const char *roofs[] = {"Roof 1 (North)", "Roof 2 (South)"};
    size_t wall = 0, roof = 0, ground = 0;
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(types[i], ecitygml_AbstractFeatureKindRef_feature_type(features[i]));
        const WallSurface *w = ecitygml_WallSurface_try_from(features[i]);
        const RoofSurface *r = ecitygml_RoofSurface_try_from(features[i]);
        const GroundSurface *g = ecitygml_GroundSurface_try_from(features[i]);
        if (w != NULL) ASSERT_STR(walls[wall++], first_name(ecitygml_WallSurface_names(w)));
        if (r != NULL) ASSERT_STR(roofs[roof++], first_name(ecitygml_RoofSurface_names(r)));
        if (g != NULL) {
            ASSERT_STR("Base Surface", first_name(ecitygml_GroundSurface_names(g)));
            ground++;
        }
    }
    TEST_ASSERT_EQUAL_size_t(4, wall);
    TEST_ASSERT_EQUAL_size_t(2, roof);
    TEST_ASSERT_EQUAL_size_t(1, ground);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_surface_areas(void) {
    CityModel *city_model = read(LOD2);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    double walls = 0.0, roofs = 0.0, grounds = 0.0;
    for (size_t i = 0; i < len; i++) {
        const WallSurface *w = ecitygml_WallSurface_try_from(features[i]);
        const RoofSurface *r = ecitygml_RoofSurface_try_from(features[i]);
        const GroundSurface *g = ecitygml_GroundSurface_try_from(features[i]);
        if (w != NULL) walls += lod2_area(ecitygml_WallSurface_lod2_multi_surface(w));
        if (r != NULL) roofs += lod2_area(ecitygml_RoofSurface_lod2_multi_surface(r));
        if (g != NULL) grounds += lod2_area(ecitygml_GroundSurface_lod2_multi_surface(g));
    }
    ASSERT_CLOSE(188.62887820601463, walls);
    ASSERT_CLOSE(138.56406460961398, roofs);
    ASSERT_CLOSE(120.0, grounds);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_generic_attributes(void) {
    CityModel *city_model = read(LOD2);
    const Building *b = first_building(city_model);
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(b);
    const GenericAttributeKind *area = ecitygml_GenericAttributeKindIterator_next(attributes);
    const GenericAttributeKind *method = ecitygml_GenericAttributeKindIterator_next(attributes);
    const GenericAttributeKind *landmarked = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_TRUE(area != NULL && method != NULL && landmarked != NULL);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    const MeasureAttribute *measure = ecitygml_MeasureAttribute_try_from(area);
    TEST_ASSERT_NOT_NULL(measure);
    ASSERT_STR("GrossPlannedArea", ecitygml_GenericAttributeKind_name(area));
    ASSERT_CLOSE(120.0, ecitygml_Measure_value(ecitygml_MeasureAttribute_value(measure)));
    ASSERT_STR("m2", ecitygml_Measure_uom(ecitygml_MeasureAttribute_value(measure)));
    ASSERT_STR("ConstructionMethod", ecitygml_GenericAttributeKind_name(method));
    ASSERT_STR("New Building", ecitygml_StringAttribute_value(ecitygml_GenericAttributeKind_as_string(method)));
    ASSERT_STR("IsLandmarked", ecitygml_GenericAttributeKind_name(landmarked));
    ASSERT_STR("NO", ecitygml_StringAttribute_value(ecitygml_GenericAttributeKind_as_string(landmarked)));
    ExternalReferenceIterator *references = ecitygml_Building_external_references(b);
    TEST_ASSERT_NULL(ecitygml_ExternalReferenceIterator_next(references));
    ecitygml_ExternalReferenceIterator_destroy(references);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_solid_unresolved(void) {
    CityModel *city_model = read(LOD2);
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod2_solid(first_building(city_model)));
    TEST_ASSERT_NOT_NULL(solid);
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
    TEST_ASSERT_FALSE(volume.is_ok);
    ecitygml_Error_destroy(volume.err);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_building_details(void) {
    CityModel *city_model = read(LOD2);
    const Building *b = first_building(city_model);
    ecitygml_Building_relative_to_terrain_result terrain = ecitygml_Building_relative_to_terrain(b);
    TEST_ASSERT_TRUE(terrain.is_ok);
    TEST_ASSERT_EQUAL_INT(RelativeToTerrain_EntirelyAboveTerrain, terrain.ok);
    TEST_ASSERT_FALSE(ecitygml_Building_relative_to_water(b).is_ok);
    const DateTime *created = ecitygml_Building_creation_date(b);
    TEST_ASSERT_NOT_NULL(created);
    TEST_ASSERT_EQUAL_INT32(2017, ecitygml_DateTime_year(created));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_DateTime_month(created));
    TEST_ASSERT_EQUAL_UINT32(23, ecitygml_DateTime_day(created));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_hour(created));
    TEST_ASSERT_EQUAL_INT32(3600, ecitygml_DateTime_offset_seconds(created));
    TEST_ASSERT_EQUAL_INT64(1485126000, ecitygml_DateTime_timestamp(created));
    TEST_ASSERT_NULL(ecitygml_Building_termination_date(b));
    TEST_ASSERT_NULL(ecitygml_Building_valid_from(b));
    TEST_ASSERT_NULL(ecitygml_Building_valid_to(b));

    ASSERT_STR("1000", ecitygml_BuildingClassValue_value(ecitygml_Building_class(b)));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    ASSERT_STR("1000", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    ASSERT_STR("1000", ecitygml_BuildingUsageValue_value(ecitygml_BuildingUsageValueIterator_next(usages)));
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("1030", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    ecitygml_Building_storeys_above_ground_result above = ecitygml_Building_storeys_above_ground(b);
    ecitygml_Building_storeys_below_ground_result below = ecitygml_Building_storeys_below_ground(b);
    TEST_ASSERT_TRUE(above.is_ok && below.is_ok);
    TEST_ASSERT_EQUAL_INT64(2, above.ok);
    TEST_ASSERT_EQUAL_INT64(0, below.ok);
    const Date *date = ecitygml_Building_date_of_construction(b);
    TEST_ASSERT_NOT_NULL(date);
    TEST_ASSERT_EQUAL_INT32(2020, ecitygml_Date_year(date));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_month(date));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_day(date));
    TEST_ASSERT_NULL(ecitygml_Building_date_of_demolition(b));
    HeightIterator *heights = ecitygml_Building_heights(b);
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("topOfConstruction", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(6.52, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);

    OccupancyIterator *occupancies = ecitygml_Building_occupancies(b);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    ecitygml_OccupancyIterator_destroy(occupancies);
    CityObjectRelationPropertyIterator *related = ecitygml_Building_related_to(b);
    TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(related));
    ecitygml_CityObjectRelationPropertyIterator_destroy(related);
    TEST_ASSERT_NULL(ecitygml_Building_lod1_solid(b));
    TEST_ASSERT_NULL(ecitygml_Building_bounded_by(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod1_terrain_intersection_curve(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod2_terrain_intersection_curve(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod3_terrain_intersection_curve(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod1_implicit_representation(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod2_implicit_representation(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod3_implicit_representation(b));
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_boundary_ids(void) {
    CityModel *city_model = read(LOD2);
    const char *ids[] = {
        "GML_5856d7ad-5e34-498a-817b-9544bfbb1475", "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
        "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069", "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
        "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc", "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
        "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
    };
    size_t i = 0;
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Building_boundaries(first_building(city_model));
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(7, i);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(property));
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        TEST_ASSERT_NOT_NULL(boundary);
        ASSERT_STR(ids[i], ecitygml_Id_as_str(ecitygml_AbstractSpaceBoundaryKind_feature_id(boundary)));
        i++;
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);
    TEST_ASSERT_EQUAL_size_t(7, i);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_wall_surface(void) {
    CityModel *city_model = read(LOD2);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    const WallSurface *wall = ecitygml_WallSurface_try_from(features[0]);
    TEST_ASSERT_NOT_NULL(wall);
    const Id *id = ecitygml_WallSurface_id(wall);
    TEST_ASSERT_NOT_NULL(id);
    ASSERT_STR("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", ecitygml_Id_as_str(id));
    TEST_ASSERT_NULL(ecitygml_WallSurface_lod0_multi_curve(wall));
    TEST_ASSERT_NULL(ecitygml_WallSurface_lod0_multi_surface(wall));
    TEST_ASSERT_NULL(ecitygml_WallSurface_lod1_multi_surface(wall));
    TEST_ASSERT_FALSE(ecitygml_WallSurface_relative_to_terrain(wall).is_ok);
    TEST_ASSERT_NULL(ecitygml_WallSurface_creation_date(wall));
    GenericAttributeKindIterator *attributes = ecitygml_WallSurface_generic_attributes(wall);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    TEST_ASSERT_NOT_NULL(ecitygml_WallSurface_bounded_by(wall));
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(ecitygml_WallSurface_lod2_multi_surface(wall));
    TEST_ASSERT_NOT_NULL(multi_surface);
    TEST_ASSERT_EQUAL_size_t(1, count_surface_members(ecitygml_MultiSurface_surface_member(multi_surface)));
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_EQUAL_size_t(3, triangulation_triangles(triangulation.ok));
    const GroundSurface *ground = NULL;
    for (size_t i = 0; i < len; i++) {
        const WallSurface *w = ecitygml_WallSurface_try_from(features[i]);
        if (w != NULL) TEST_ASSERT_EQUAL_size_t(0, count_fillings(ecitygml_WallSurface_filling_surfaces(w)));
        if (ground == NULL) ground = ecitygml_GroundSurface_try_from(features[i]);
    }
    TEST_ASSERT_NOT_NULL(ground);
    const MultiSurface *ground_surface = ecitygml_MultiSurfaceProperty_object(ecitygml_GroundSurface_lod2_multi_surface(ground));
    TEST_ASSERT_NOT_NULL(ground_surface);
    const Polygon *polygon = first_polygon(ecitygml_MultiSurface_surface_member(ground_surface));
    TEST_ASSERT_EQUAL_size_t(4, count_positions(ecitygml_AbstractRingKind_points(ecitygml_Polygon_exterior(polygon))));
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_generic_attribute_kinds(void) {
    CityModel *city_model = read(LOD2);
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(first_building(city_model));
    const GenericAttributeKind *area = ecitygml_GenericAttributeKindIterator_next(attributes);
    const GenericAttributeKind *method = ecitygml_GenericAttributeKindIterator_next(attributes);
    const GenericAttributeKind *landmarked = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_TRUE(area != NULL && method != NULL && landmarked != NULL);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKind_as_string(area));
    TEST_ASSERT_NULL(ecitygml_MeasureAttribute_try_from(method));
    TEST_ASSERT_NULL(ecitygml_MeasureAttribute_try_from(landmarked));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_city_objects(void) {
    CityModel *city_model = read(LOD2);
    FeatureType objects[MAX_FEATURES];
    const FeatureType expected[] = {FeatureType_Building,    FeatureType_WallSurface, FeatureType_WallSurface,
                                    FeatureType_WallSurface, FeatureType_RoofSurface, FeatureType_WallSurface,
                                    FeatureType_RoofSurface, FeatureType_GroundSurface};
    TEST_ASSERT_EQUAL_size_t(8, city_object_types(city_model, objects));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, objects, 8);
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, ecitygml_AbstractFeatureKindRef_feature_type(features[0]));
    size_t city_models = 0;
    for (size_t i = 0; i < len; i++) {
        city_models += ecitygml_AbstractFeatureKindRef_feature_type(features[i]) == FeatureType_CityModel;
    }
    TEST_ASSERT_EQUAL_size_t(1, city_models);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod2_object_bounds(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(LOD2));
    TEST_ASSERT_TRUE(reader.is_ok);
    ecitygml_GmlReader_with_rebuild_object_bounds(reader.ok, false);
    ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    TEST_ASSERT_TRUE(city_model.is_ok);
    bool bounded[MAX_FEATURES];
    const bool none[] = {false, false, false, false};
    const bool all[] = {true, true, true, true};
    TEST_ASSERT_EQUAL_size_t(4, walls_bounded(city_model.ok, bounded));
    TEST_ASSERT_EQUAL_MEMORY(none, bounded, sizeof none);
    ecitygml_CityModel_recompute_child_bounding_shapes(city_model.ok);
    TEST_ASSERT_EQUAL_size_t(4, walls_bounded(city_model.ok, bounded));
    TEST_ASSERT_EQUAL_MEMORY(all, bounded, sizeof all);
    ecitygml_CityModel_destroy(city_model.ok);
}

static void test_lod2_apply_translation(void) {
    CityModel *city_model = read(LOD2);
    assert_lower_corners(457842.0, 5439083.0, 111.8, city_model);
    ecitygml_CityModel_apply_translation(city_model, (Vector3){.x = -100.0, .y = 200.0, .z = 10.0});
    assert_lower_corners(457742.0, 5439283.0, 121.8, city_model);
    ecitygml_CityModel_destroy(city_model);
}

// FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml

static void test_lod3_doors_and_windows(void) {
    CityModel *city_model = read(LOD3);
    const char *doors[] = {"Door West", "Door South"};
    size_t door = 0, windows = 0;
    double area = 0.0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const DoorSurface *d = ecitygml_DoorSurface_try_from(feature);
        if (d != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(2, door);
            ASSERT_STR(doors[door++], first_name(ecitygml_DoorSurface_names(d)));
            area += lod2_area(ecitygml_DoorSurface_lod3_multi_surface(d));
        }
        windows += ecitygml_WindowSurface_try_from(feature) != NULL;
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    TEST_ASSERT_EQUAL_size_t(2, door);
    ASSERT_CLOSE(6.803850099444389, area);
    TEST_ASSERT_EQUAL_size_t(11, windows);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod3_west_wall_fillings(void) {
    CityModel *city_model = read(LOD3);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    TEST_ASSERT_GREATER_THAN_size_t(0, len);
    const WallSurface *wall = ecitygml_WallSurface_try_from(features[0]);
    TEST_ASSERT_NOT_NULL(wall);
    ASSERT_STR("Outer Wall 1 (West)", first_name(ecitygml_WallSurface_names(wall)));
    const FeatureType types[] = {FeatureType_WindowSurface, FeatureType_WindowSurface, FeatureType_DoorSurface,
                                 FeatureType_WindowSurface};
    const char *names[] = {"Window Round", "Window North", "Door West", "Window South"};
    size_t i = 0;
    AbstractFillingSurfacePropertyIterator *fillings = ecitygml_WallSurface_filling_surfaces(wall);
    const AbstractFillingSurfaceProperty *property;
    while ((property = ecitygml_AbstractFillingSurfacePropertyIterator_next(fillings)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(4, i);
        const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
        TEST_ASSERT_EQUAL_INT(types[i], ecitygml_AbstractFillingSurfaceKind_feature_type(filling));
        ASSERT_STR(names[i], first_name(ecitygml_AbstractFillingSurfaceKind_names(filling)));
        i++;
    }
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(fillings);
    TEST_ASSERT_EQUAL_size_t(4, i);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod3_building_details(void) {
    CityModel *city_model = read(LOD3);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const Building *b = first_building(city_model);
    ecitygml_Building_relative_to_terrain_result terrain = ecitygml_Building_relative_to_terrain(b);
    TEST_ASSERT_TRUE(terrain.is_ok);
    TEST_ASSERT_EQUAL_INT(RelativeToTerrain_EntirelyAboveTerrain, terrain.ok);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(b, features);
    const FeatureType types[] = {FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
                                 FeatureType_RoofSurface, FeatureType_WallSurface, FeatureType_RoofSurface,
                                 FeatureType_GroundSurface};
    TEST_ASSERT_EQUAL_size_t(7, len);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(types[i], ecitygml_AbstractFeatureKindRef_feature_type(features[i]));
        const WallSurface *wall = ecitygml_WallSurface_try_from(features[i]);
        if (wall != NULL) TEST_ASSERT_NOT_NULL(ecitygml_WallSurface_lod3_multi_surface(wall));
    }
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod3_fillings(void) {
    CityModel *city_model = read(LOD3);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    const size_t expected[] = {4, 3, 3, 3};
    size_t walls = 0, doors = 0, windows = 0;
    for (size_t i = 0; i < len; i++) {
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(features[i]);
        if (roof != NULL) TEST_ASSERT_EQUAL_size_t(0, count_fillings(ecitygml_RoofSurface_filling_surfaces(roof)));
        const WallSurface *wall = ecitygml_WallSurface_try_from(features[i]);
        if (wall == NULL) continue;
        TEST_ASSERT_LESS_THAN_size_t(4, walls);
        TEST_ASSERT_EQUAL_size_t(expected[walls++], count_fillings(ecitygml_WallSurface_filling_surfaces(wall)));
        AbstractFillingSurfacePropertyIterator *properties = ecitygml_WallSurface_filling_surfaces(wall);
        const AbstractFillingSurfaceProperty *property;
        while ((property = ecitygml_AbstractFillingSurfacePropertyIterator_next(properties)) != NULL) {
            TEST_ASSERT_NULL(ecitygml_AbstractFillingSurfaceProperty_href(property));
            const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
            TEST_ASSERT_NOT_NULL(filling);
            doors += ecitygml_AbstractFillingSurfaceKind_feature_type(filling) == FeatureType_DoorSurface;
            windows += ecitygml_AbstractFillingSurfaceKind_feature_type(filling) == FeatureType_WindowSurface;
            TEST_ASSERT_TRUE(lod2_area(ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(filling)) > 0.0);
        }
        ecitygml_AbstractFillingSurfacePropertyIterator_destroy(properties);
    }
    TEST_ASSERT_EQUAL_size_t(4, walls);
    TEST_ASSERT_EQUAL_size_t(2, doors);
    TEST_ASSERT_EQUAL_size_t(11, windows);
    destroy_features(features, len);

    AbstractFeatureKindRef *all[MAX_FEATURES];
    size_t all_len = all_features(city_model, all);
    const char *door_ids[] = {"GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd", "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629"};
    size_t door = 0;
    double window_area = 0.0;
    for (size_t i = 0; i < all_len; i++) {
        const WindowSurface *window = ecitygml_WindowSurface_try_from(all[i]);
        if (window != NULL) window_area += lod2_area(ecitygml_WindowSurface_lod3_multi_surface(window));
        const DoorSurface *d = ecitygml_DoorSurface_try_from(all[i]);
        if (d != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(2, door);
            ASSERT_STR(door_ids[door++], ecitygml_Id_as_str(ecitygml_DoorSurface_feature_id(d)));
            TEST_ASSERT_NULL(ecitygml_DoorSurface_lod2_multi_surface(d));
        }
    }
    TEST_ASSERT_EQUAL_size_t(2, door);
    ASSERT_CLOSE(23.168802611529827, window_area);
    destroy_features(all, all_len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod3_city_objects(void) {
    CityModel *city_model = read(LOD3);
    FeatureType objects[MAX_FEATURES];
    size_t len = city_object_types(city_model, objects);
    TEST_ASSERT_EQUAL_size_t(21, len);
    const FeatureType kinds[] = {FeatureType_Building,      FeatureType_WallSurface, FeatureType_RoofSurface,
                                 FeatureType_GroundSurface, FeatureType_DoorSurface, FeatureType_WindowSurface};
    const size_t expected[] = {1, 4, 2, 1, 2, 11};
    for (size_t k = 0; k < 6; k++) {
        size_t count = 0;
        for (size_t i = 0; i < len; i++) count += objects[i] == kinds[k];
        TEST_ASSERT_EQUAL_size_t(expected[k], count);
    }
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t features_len = all_features(city_model, features);
    TEST_ASSERT_EQUAL_size_t(22, features_len);
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, ecitygml_AbstractFeatureKindRef_feature_type(features[0]));
    destroy_features(features, features_len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_lod3_composite_surface(void) {
    CityModel *city_model = read(LOD3);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    const WallSurface *wall = ecitygml_WallSurface_try_from(features[0]);
    TEST_ASSERT_NOT_NULL(wall);
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(ecitygml_WallSurface_lod3_multi_surface(wall));
    TEST_ASSERT_NOT_NULL(multi_surface);
    AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
    const AbstractSurfaceProperty *member = ecitygml_AbstractSurfacePropertyIterator_next(members);
    TEST_ASSERT_NOT_NULL(member);
    const CompositeSurface *composite = ecitygml_CompositeSurface_try_from(ecitygml_AbstractSurfaceProperty_object(member));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_NOT_NULL(composite);
    TEST_ASSERT_EQUAL_size_t(85, count_surface_members(ecitygml_CompositeSurface_surface_member(composite)));
    const Polygon *first = first_polygon(ecitygml_CompositeSurface_surface_member(composite));
    assert_first_point(457842.0, 5439088.49240388, 115.913175911167,
                       ecitygml_AbstractRingKind_points(ecitygml_Polygon_exterior(first)));
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

/// The most surface ids `surface_ids` collects.
#define MAX_SURFACE_IDS 32

/// Copies a borrowed id into `out` (64 bytes).
static void copy_id(char *out, DiplomatStringView id) {
    TEST_ASSERT_LESS_THAN_size_t(64, id.len);
    memcpy(out, id.data, id.len);
    out[id.len] = '\0';
}

/// The `feature_id`s of the first building's boundaries, then of the wall surfaces' filling surfaces, into `out`;
/// returns their number.
static size_t surface_ids(const CityModel *city_model, char out[][64]) {
    size_t len = 0;
    const Building *building = first_building(city_model);
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Building_boundaries(building);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_SURFACE_IDS, len);
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        copy_id(out[len++], ecitygml_Id_as_str(ecitygml_AbstractSpaceBoundaryKind_feature_id(boundary)));
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);

    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t count = boundaries(building, features);
    for (size_t i = 0; i < count; i++) {
        const WallSurface *wall = ecitygml_WallSurface_try_from(features[i]);
        if (wall == NULL) continue;
        AbstractFillingSurfacePropertyIterator *fillings = ecitygml_WallSurface_filling_surfaces(wall);
        const AbstractFillingSurfaceProperty *filling;
        while ((filling = ecitygml_AbstractFillingSurfacePropertyIterator_next(fillings)) != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(MAX_SURFACE_IDS, len);
            const AbstractFillingSurfaceKind *kind = ecitygml_AbstractFillingSurfaceProperty_object(filling);
            copy_id(out[len++], ecitygml_Id_as_str(ecitygml_AbstractFillingSurfaceKind_feature_id(kind)));
        }
        ecitygml_AbstractFillingSurfacePropertyIterator_destroy(fillings);
    }
    destroy_features(features, count);
    return len;
}

static void test_lod3_round_trip(void) {
    CityModel *city_model = read(LOD3);
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    GmlReader *reader = ecitygml_GmlReader_new(ecitygml_GmlWriter_data(writer), CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result written = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    ecitygml_GmlWriter_destroy(writer);
    TEST_ASSERT_TRUE(written.is_ok);
    AbstractFeatureKindRef *original[MAX_FEATURES];
    AbstractFeatureKindRef *read_back[MAX_FEATURES];
    size_t len = all_features(city_model, original);
    TEST_ASSERT_EQUAL_size_t(len, all_features(written.ok, read_back));
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(ecitygml_AbstractFeatureKindRef_feature_type(original[i]),
                              ecitygml_AbstractFeatureKindRef_feature_type(read_back[i]));
    }
    destroy_features(original, len);
    destroy_features(read_back, len);
    ASSERT_STR("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82",
               ecitygml_Id_as_str(ecitygml_Building_feature_id(first_building(written.ok))));
    char original_ids[MAX_SURFACE_IDS][64], written_ids[MAX_SURFACE_IDS][64];
    size_t ids = surface_ids(city_model, original_ids);
    TEST_ASSERT_EQUAL_size_t(ids, surface_ids(written.ok, written_ids));
    for (size_t i = 0; i < ids; i++) {
        TEST_ASSERT_EQUAL_STRING(original_ids[i], written_ids[i]);
    }
    HeightIterator *heights = ecitygml_Building_heights(first_building(written.ok));
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("topOfConstruction", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(6.52, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);
    ecitygml_CityModel_destroy(written.ok);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_lod1_city_model);
    RUN_TEST(test_lod1_building_attributes);
    RUN_TEST(test_lod1_solid);
    RUN_TEST(test_lod1_envelope_measures);
    RUN_TEST(test_lod1_building_details);
    RUN_TEST(test_lod1_solid_structure);
    RUN_TEST(test_lod1_solid_triangulation);
    RUN_TEST(test_lod1_apply_scale);
    RUN_TEST(test_lod2_boundary_surfaces);
    RUN_TEST(test_lod2_surface_areas);
    RUN_TEST(test_lod2_generic_attributes);
    RUN_TEST(test_lod2_solid_unresolved);
    RUN_TEST(test_lod2_building_details);
    RUN_TEST(test_lod2_boundary_ids);
    RUN_TEST(test_lod2_wall_surface);
    RUN_TEST(test_lod2_generic_attribute_kinds);
    RUN_TEST(test_lod2_city_objects);
    RUN_TEST(test_lod2_object_bounds);
    RUN_TEST(test_lod2_apply_translation);
    RUN_TEST(test_lod3_doors_and_windows);
    RUN_TEST(test_lod3_west_wall_fillings);
    RUN_TEST(test_lod3_building_details);
    RUN_TEST(test_lod3_fillings);
    RUN_TEST(test_lod3_city_objects);
    RUN_TEST(test_lod3_composite_surface);
    RUN_TEST(test_lod3_round_trip);
    return UNITY_END();
}
