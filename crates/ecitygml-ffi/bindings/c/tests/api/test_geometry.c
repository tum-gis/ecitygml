// The cases of crates/ecitygml/tests/api/geometry.md.
#include "api.h"

#include "AbstractCurveKind.h"
#include "AbstractCurveProperty.h"
#include "AbstractCurvePropertyIterator.h"
#include "AbstractRingKind.h"
#include "AbstractRingKindIterator.h"
#include "AbstractSurfaceKind.h"
#include "AbstractSurfacePatchKind.h"
#include "AbstractSurfacePatchKindIterator.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "Building.h"
#include "CompositeSurface.h"
#include "DirectPosition.h"
#include "DirectPositionIterator.h"
#include "Envelope.h"
#include "GeometryType.h"
#include "GroundSurface.h"
#include "Id.h"
#include "ImplicitGeometry.h"
#include "ImplicitGeometryProperty.h"
#include "LinearRing.h"
#include "MultiCurve.h"
#include "MultiCurveProperty.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Point.h"
#include "PointProperty.h"
#include "Polygon.h"
#include "PolygonPatch.h"
#include "Shell.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "SolitaryVegetationObject.h"
#include "Storey.h"
#include "Surface.h"
#include "TinProperty.h"
#include "TinRelief.h"
#include "TrafficSpace.h"
#include "Triangle.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"

#define FZK_LOD1 FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
#define FZK_LOD2 FIXTURE("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
#define TUM FIXTURE("tum-main-entrance/TUM-Main-Entrance.gml")
#define ASAM_ROAD_SHAPE FIXTURE("asam-opendrive/ASAM-UC_RoadShape.gml")
#define RAILWAY FIXTURE("railway-scene/Railway_Scene_LoD3__v3-thinned.gml")
#define OGC_GARAGE FIXTURE("ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml")
#define OGC_UNITS FIXTURE("ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml")
#define OGC_ROAD_OVER_BRIDGE \
    FIXTURE("ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml")

#define TOLERANCE 1e-6
#define ASSERT_CLOSE(expected, actual) TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, (expected), (actual))

void setUp(void) {}
void tearDown(void) {}

/// Declares `count_<T>`: the number of items of a `<T>Iterator`, which it destroys.
#define DEFINE_COUNT(T)                                                 \
    static size_t count_##T(T##Iterator *iterator) {                    \
        size_t n = 0;                                                   \
        while (ecitygml_##T##Iterator_next(iterator) != NULL) n++;      \
        ecitygml_##T##Iterator_destroy(iterator);                       \
        return n;                                                       \
    }

DEFINE_COUNT(DirectPosition)
DEFINE_COUNT(AbstractSurfaceProperty)
DEFINE_COUNT(AbstractCurveProperty)
DEFINE_COUNT(AbstractRingKind)
DEFINE_COUNT(AbstractSurfacePatchKind)
DEFINE_COUNT(Triangle)

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

/// Declares `with_id_<T>`: the feature of type `T` with that `feature_id`.
#define DEFINE_WITH_ID(T, MAX)                                                       \
    static const T *with_id_##T(const CityModel *city_model, const char *id) {       \
        const T *features[MAX];                                                      \
        size_t len = all_##T(city_model, features, MAX);                             \
        for (size_t i = 0; i < len; i++) {                                           \
            DiplomatStringView found = ecitygml_Id_as_str(ecitygml_##T##_feature_id(features[i])); \
            if (found.len == strlen(id) && memcmp(found.data, id, found.len) == 0) { \
                return features[i];                                                  \
            }                                                                        \
        }                                                                            \
        TEST_FAIL_MESSAGE(id);                                                       \
        return NULL;                                                                 \
    }

DEFINE_ALL_OF(Building)
DEFINE_ALL_OF(GroundSurface)
DEFINE_ALL_OF(TrafficSpace)
DEFINE_ALL_OF(TinRelief)
DEFINE_ALL_OF(Storey)
DEFINE_ALL_OF(SolitaryVegetationObject)
DEFINE_WITH_ID(GroundSurface, 8)
DEFINE_WITH_ID(Storey, 4)
DEFINE_WITH_ID(SolitaryVegetationObject, 16)

static void assert_position(const DirectPosition *actual, double x, double y, double z) {
    TEST_ASSERT_NOT_NULL(actual);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(actual));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(actual));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(actual));
}

/// Asserts the corners of the envelope (`lower` and `upper` are x, y, z), then destroys it.
static void assert_envelope(Envelope *envelope, const double lower[3], const double upper[3]) {
    TEST_ASSERT_NOT_NULL(envelope);
    assert_position(ecitygml_Envelope_lower_corner(envelope), lower[0], lower[1], lower[2]);
    assert_position(ecitygml_Envelope_upper_corner(envelope), upper[0], upper[1], upper[2]);
    ecitygml_Envelope_destroy(envelope);
}

static void assert_id(const char *expected, const Id *id) {
    TEST_ASSERT_NOT_NULL(id);
    ASSERT_STR(expected, ecitygml_Id_as_str(id));
}

static void compute_envelope(void) {
    CityModel *lod1 = read(FZK_LOD1);
    const Building *buildings[1];
    TEST_ASSERT_EQUAL_size_t(1, all_Building(lod1, buildings, 1));
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod1_solid(buildings[0]));
    const double lower[] = {457842.0, 5439083.0, 111.8};
    const double upper[] = {457854.0, 5439093.0, 118.31769};
    assert_envelope(ecitygml_Solid_compute_envelope(solid), lower, upper);
    const Shell *shell = ecitygml_Solid_exterior(solid);
    TEST_ASSERT_NOT_NULL(shell);
    assert_envelope(ecitygml_Shell_compute_envelope(shell), lower, upper);
    ecitygml_Solid_triangulate_result triangulation = ecitygml_Solid_triangulate(solid);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    assert_envelope(ecitygml_TriangulatedSurface_compute_envelope(ecitygml_Triangulation_surface(triangulation.ok)), lower,
                    upper);
    ecitygml_Triangulation_destroy(triangulation.ok);
    AbstractSurfacePropertyIterator *members = ecitygml_Shell_members(shell);
    const Polygon *first =
        ecitygml_Polygon_try_from(ecitygml_AbstractSurfaceProperty_object(ecitygml_AbstractSurfacePropertyIterator_next(members)));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_NOT_NULL(first);
    const double ground[] = {457854.0, 5439093.0, 111.8};
    assert_envelope(ecitygml_Polygon_compute_envelope(first), lower, ground);
    assert_envelope(ecitygml_AbstractRingKind_compute_envelope(ecitygml_Polygon_exterior(first)), lower, ground);
    ecitygml_CityModel_destroy(lod1);

    CityModel *road_shape = read(ASAM_ROAD_SHAPE);
    const TrafficSpace *spaces[2];
    TEST_ASSERT_EQUAL_size_t(2, all_TrafficSpace(road_shape, spaces, 2));
    const MultiCurve *multi_curve = ecitygml_MultiCurveProperty_object(ecitygml_TrafficSpace_lod2_multi_curve(spaces[0]));
    const double curve_lower[] = {-48.38872036507727, 2.3148451158285663, 0.25};
    const double curve_upper[] = {-16.661414812688488, 26.674198193965925, 0.25};
    assert_envelope(ecitygml_MultiCurve_compute_envelope(multi_curve), curve_lower, curve_upper);
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractCurveProperty(ecitygml_MultiCurve_curve_member(multi_curve)));
    AbstractCurvePropertyIterator *curves = ecitygml_MultiCurve_curve_member(multi_curve);
    const AbstractCurveKind *curve =
        ecitygml_AbstractCurveProperty_object(ecitygml_AbstractCurvePropertyIterator_next(curves));
    ecitygml_AbstractCurvePropertyIterator_destroy(curves);
    assert_envelope(ecitygml_AbstractCurveKind_compute_envelope(curve), curve_lower, curve_upper);
    const Solid *space_solid = ecitygml_SolidProperty_object(ecitygml_TrafficSpace_lod2_solid(spaces[0]));
    const double solid_lower[] = {-49.60668801898414, 0.7284798382091271, 0.05};
    const double solid_upper[] = {-15.44344715878162, 28.260563471585364, 4.95};
    assert_envelope(ecitygml_Solid_compute_envelope(space_solid), solid_lower, solid_upper);
    TEST_ASSERT_EQUAL_size_t(24, count_DirectPosition(ecitygml_Solid_points(space_solid)));
    ecitygml_CityModel_destroy(road_shape);

    CityModel *railway = read(RAILWAY);
    const SolitaryVegetationObject *tree = with_id_SolitaryVegetationObject(railway, "GMLID_SO092422_3593_9527");
    const Point *point = ecitygml_PointProperty_object(ecitygml_ImplicitGeometry_reference_point(
        ecitygml_ImplicitGeometryProperty_object(ecitygml_SolitaryVegetationObject_lod3_implicit_representation(tree))));
    TEST_ASSERT_NOT_NULL(point);
    const double reference[] = {-568.8000793496976, 457.60044759869743, 105.00139681350242};
    assert_envelope(ecitygml_Point_compute_envelope(point), reference, reference);
    ecitygml_CityModel_destroy(railway);

    CityModel *garage = read(OGC_GARAGE);
    const TinRelief *reliefs[1];
    TEST_ASSERT_EQUAL_size_t(1, all_TinRelief(garage, reliefs, 1));
    const TriangulatedSurface *tin = ecitygml_TinProperty_object(ecitygml_TinRelief_tin(reliefs[0]));
    const double tin_lower[] = {458868.0, 5438343.0, 112.0};
    const double tin_upper[] = {458892.0, 5438362.0, 114.0};
    assert_envelope(ecitygml_TriangulatedSurface_compute_envelope(tin), tin_lower, tin_upper);
    ecitygml_CityModel_destroy(garage);
}

static void polygon_interior_rings(void) {
    CityModel *city_model = read(TUM);
    const GroundSurface *grounds[2];
    TEST_ASSERT_EQUAL_size_t(1, all_GroundSurface(city_model, grounds, 2));
    const MultiSurface *multi_surface =
        ecitygml_MultiSurfaceProperty_object(ecitygml_GroundSurface_lod2_multi_surface(grounds[0]));
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfaceProperty(ecitygml_MultiSurface_surface_member(multi_surface)));
    AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
    const Polygon *polygon =
        ecitygml_Polygon_try_from(ecitygml_AbstractSurfaceProperty_object(ecitygml_AbstractSurfacePropertyIterator_next(members)));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_NOT_NULL(polygon);
    assert_id("DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly", ecitygml_Polygon_id(polygon));
    const LinearRing *exterior = ecitygml_LinearRing_try_from(ecitygml_Polygon_exterior(polygon));
    TEST_ASSERT_NOT_NULL(exterior);
    TEST_ASSERT_EQUAL_size_t(11, count_DirectPosition(ecitygml_LinearRing_points(exterior)));
    ASSERT_CLOSE(1371.825439453125, ecitygml_LinearRing_area_3d(exterior));
    ASSERT_CLOSE(150.78554397170106, ecitygml_LinearRing_length_3d(exterior));
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractRingKind(ecitygml_Polygon_interior(polygon)));
    AbstractRingKindIterator *interiors = ecitygml_Polygon_interior(polygon);
    const LinearRing *interior = ecitygml_LinearRing_try_from(ecitygml_AbstractRingKindIterator_next(interiors));
    ecitygml_AbstractRingKindIterator_destroy(interiors);
    TEST_ASSERT_NOT_NULL(interior);
    TEST_ASSERT_EQUAL_size_t(4, count_DirectPosition(ecitygml_LinearRing_points(interior)));
    ASSERT_CLOSE(142.26318359375, ecitygml_LinearRing_area_3d(interior));
    ASSERT_CLOSE(47.7096809282068, ecitygml_LinearRing_length_3d(interior));
    ecitygml_Polygon_area_3d_result area = ecitygml_Polygon_area_3d(polygon);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(1229.562255859375, area.ok);
    TEST_ASSERT_EQUAL_size_t(15, count_DirectPosition(ecitygml_Polygon_points(polygon)));
    const double lower[] = {691009.16, 5335994.57, 515.042};
    const double upper[] = {691054.07, 5336047.41, 515.042};
    assert_envelope(ecitygml_Polygon_compute_envelope(polygon), lower, upper);
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    const TriangulatedSurface *surface = ecitygml_Triangulation_surface(triangulation.ok);
    TEST_ASSERT_EQUAL_size_t(15, count_Triangle(ecitygml_TriangulatedSurface_triangles(surface)));
    ecitygml_TriangulatedSurface_area_3d_result surface_area = ecitygml_TriangulatedSurface_area_3d(surface);
    TEST_ASSERT_TRUE(surface_area.is_ok);
    ASSERT_CLOSE(1229.5620994984272, surface_area.ok);
    ecitygml_Triangulation_destroy(triangulation.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void composite_surface_and_patches(void) {
    CityModel *city_model = read(OGC_ROAD_OVER_BRIDGE);
    const GroundSurface *ground = with_id_GroundSurface(city_model, "id_groundsurface1");
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(ecitygml_GroundSurface_lod2_multi_surface(ground));
    assert_id("id_groundsurface1-0", ecitygml_MultiSurface_id(multi_surface));
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(77500.15996032, area.ok);
    TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfaceProperty(ecitygml_MultiSurface_surface_member(multi_surface)));
    AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
    const AbstractSurfaceKind *kind = ecitygml_AbstractSurfaceProperty_object(ecitygml_AbstractSurfacePropertyIterator_next(members));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_EQUAL_INT(GeometryType_CompositeSurface, ecitygml_AbstractSurfaceKind_geometry_type(kind));
    TEST_ASSERT_NULL(ecitygml_Polygon_try_from(kind));
    const CompositeSurface *composite = ecitygml_CompositeSurface_try_from(kind);
    TEST_ASSERT_NOT_NULL(composite);
    assert_id("id_groundsurface1-1", ecitygml_CompositeSurface_id(composite));
    ecitygml_CompositeSurface_area_3d_result composite_area = ecitygml_CompositeSurface_area_3d(composite);
    TEST_ASSERT_TRUE(composite_area.is_ok);
    ASSERT_CLOSE(77500.15996032, composite_area.ok);
    TEST_ASSERT_EQUAL_size_t(6, count_DirectPosition(ecitygml_CompositeSurface_points(composite)));
    const double lower[] = {0.0, 0.0, 0.0};
    const double upper[] = {393.7008, 196.8504, 0.0};
    assert_envelope(ecitygml_CompositeSurface_compute_envelope(composite), lower, upper);
    ecitygml_CompositeSurface_triangulate_result triangulation = ecitygml_CompositeSurface_triangulate(composite);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    TEST_ASSERT_EQUAL_size_t(2, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok))));
    ecitygml_Triangulation_destroy(triangulation.ok);

    const char *ids[] = {"fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447", "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163"};
    TEST_ASSERT_EQUAL_size_t(2, count_AbstractSurfaceProperty(ecitygml_CompositeSurface_surface_member(composite)));
    AbstractSurfacePropertyIterator *surfaces = ecitygml_CompositeSurface_surface_member(composite);
    for (size_t i = 0; i < 2; i++) {
        const AbstractSurfaceKind *surface_kind =
            ecitygml_AbstractSurfaceProperty_object(ecitygml_AbstractSurfacePropertyIterator_next(surfaces));
        TEST_ASSERT_EQUAL_INT(GeometryType_Surface, ecitygml_AbstractSurfaceKind_geometry_type(surface_kind));
        const Surface *surface = ecitygml_Surface_try_from(surface_kind);
        TEST_ASSERT_NOT_NULL(surface);
        assert_id(ids[i], ecitygml_Surface_id(surface));
        ecitygml_Surface_area_3d_result surface_area = ecitygml_Surface_area_3d(surface);
        TEST_ASSERT_TRUE(surface_area.is_ok);
        ASSERT_CLOSE(38750.07998016, surface_area.ok);
        ecitygml_Surface_triangulate_result surface_triangulation = ecitygml_Surface_triangulate(surface);
        TEST_ASSERT_TRUE(surface_triangulation.is_ok);
        TEST_ASSERT_EQUAL_size_t(
            1, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(surface_triangulation.ok))));
        ecitygml_Triangulation_destroy(surface_triangulation.ok);
        TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfacePatchKind(ecitygml_Surface_patches(surface)));
        AbstractSurfacePatchKindIterator *patches = ecitygml_Surface_patches(surface);
        const AbstractSurfacePatchKind *patch = ecitygml_AbstractSurfacePatchKindIterator_next(patches);
        ecitygml_AbstractSurfacePatchKindIterator_destroy(patches);
        TEST_ASSERT_NULL(ecitygml_Triangle_try_from(patch));
        const PolygonPatch *polygon_patch = ecitygml_PolygonPatch_try_from(patch);
        TEST_ASSERT_NOT_NULL(polygon_patch);
        TEST_ASSERT_EQUAL_size_t(0, count_AbstractRingKind(ecitygml_PolygonPatch_interior(polygon_patch)));
        const LinearRing *exterior = ecitygml_LinearRing_try_from(ecitygml_PolygonPatch_exterior(polygon_patch));
        TEST_ASSERT_NOT_NULL(exterior);
        TEST_ASSERT_EQUAL_size_t(3, count_DirectPosition(ecitygml_LinearRing_points(exterior)));
        ecitygml_AbstractSurfacePatchKind_area_3d_result patch_area = ecitygml_AbstractSurfacePatchKind_area_3d(patch);
        TEST_ASSERT_TRUE(patch_area.is_ok);
        ASSERT_CLOSE(38750.07998016, patch_area.ok);
        ecitygml_AbstractSurfacePatchKind_triangulate_result patch_triangulation =
            ecitygml_AbstractSurfacePatchKind_triangulate(patch);
        TEST_ASSERT_TRUE(patch_triangulation.is_ok);
        TEST_ASSERT_EQUAL_size_t(
            1, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(patch_triangulation.ok))));
        ecitygml_Triangulation_destroy(patch_triangulation.ok);
    }
    ecitygml_AbstractSurfacePropertyIterator_destroy(surfaces);
    ecitygml_CityModel_destroy(city_model);
}

static void triangle_patches(void) {
    CityModel *city_model = read(OGC_GARAGE);
    const TinRelief *reliefs[1];
    TEST_ASSERT_EQUAL_size_t(1, all_TinRelief(city_model, reliefs, 1));
    const TriangulatedSurface *tin = ecitygml_TinProperty_object(ecitygml_TinRelief_tin(reliefs[0]));
    TEST_ASSERT_EQUAL_size_t(12, count_AbstractSurfacePatchKind(ecitygml_Surface_patches(ecitygml_TriangulatedSurface_surface(tin))));
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(tin);
    const Triangle *triangle = ecitygml_TriangleIterator_next(triangles);
    ecitygml_TriangleIterator_destroy(triangles);
    TEST_ASSERT_NOT_NULL(triangle);
    assert_position(ecitygml_Triangle_a(triangle), 458883.0, 5438362.0, 114.0);
    assert_position(ecitygml_Triangle_b(triangle), 458868.0, 5438362.0, 112.0);
    assert_position(ecitygml_Triangle_c(triangle), 458875.0, 5438355.0, 112.0);
    ASSERT_CLOSE(53.42518132865812, ecitygml_Triangle_area(triangle));
    TEST_ASSERT_EQUAL_INT(GeometryType_LinearRing, ecitygml_AbstractRingKind_geometry_type(ecitygml_Triangle_exterior(triangle)));
    ecitygml_CityModel_destroy(city_model);
}

static void unresolved_surface_reference(void) {
    CityModel *city_model = read(OGC_UNITS);
    const Storey *storey = with_id_Storey(city_model, "storey1");
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(ecitygml_Storey_lod2_multi_surface(storey));
    TEST_ASSERT_EQUAL_size_t(6, count_AbstractSurfaceProperty(ecitygml_MultiSurface_surface_member(multi_surface)));
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    TEST_ASSERT_FALSE(area.is_ok);
    assert_error(area.err, ErrorKind_UnresolvedReference, "#Wall_1_PolyID82397_997_453711_16336011");
    TEST_ASSERT_EQUAL_size_t(12, count_DirectPosition(ecitygml_MultiSurface_points(multi_surface)));
    const double lower[] = {457841.1, 5439082.1, 111.1};
    const double upper[] = {457853.9, 5439092.9, 113.9};
    assert_envelope(ecitygml_MultiSurface_compute_envelope(multi_surface), lower, upper);
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    TEST_ASSERT_EQUAL_size_t(6, count_Triangle(ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok))));
    ecitygml_Triangulation_destroy(triangulation.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void solid_unresolved_reference(void) {
    CityModel *city_model = read(FZK_LOD2);
    const Building *buildings[1];
    TEST_ASSERT_EQUAL_size_t(1, all_Building(city_model, buildings, 1));
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod2_solid(buildings[0]));
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
    TEST_ASSERT_FALSE(volume.is_ok);
    assert_error(volume.err, ErrorKind_UnresolvedReference, "#PolyID7350_878_759628_120742");
    ecitygml_CityModel_destroy(city_model);
}

static void triangulate_without_members(void) {
    CityModel *city_model = read(FZK_LOD2);
    const Building *buildings[1];
    TEST_ASSERT_EQUAL_size_t(1, all_Building(city_model, buildings, 1));
    const Solid *solid = ecitygml_SolidProperty_object(ecitygml_Building_lod2_solid(buildings[0]));
    TEST_ASSERT_EQUAL_size_t(0, count_DirectPosition(ecitygml_Solid_points(solid)));
    TEST_ASSERT_NULL(ecitygml_Solid_compute_envelope(solid));
    ecitygml_Solid_triangulate_result triangulation = ecitygml_Solid_triangulate(solid);
    TEST_ASSERT_FALSE(triangulation.is_ok);
    assert_error(triangulation.err, ErrorKind_InvalidArgument, "requires at least 1 element");
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(compute_envelope);
    RUN_TEST(polygon_interior_rings);
    RUN_TEST(composite_surface_and_patches);
    RUN_TEST(triangle_patches);
    RUN_TEST(unresolved_surface_reference);
    RUN_TEST(solid_unresolved_reference);
    RUN_TEST(triangulate_without_members);
    return UNITY_END();
}
