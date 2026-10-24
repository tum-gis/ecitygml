package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/api/geometry.md.

private const val FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
private const val FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
private const val TUM = "tum-main-entrance/TUM-Main-Entrance.gml"
private const val ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml"
private const val RAILWAY = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml"
private const val OGC_GARAGE = "ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml"
private const val OGC_UNITS = "ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml"
private const val OGC_ROAD_OVER_BRIDGE = "ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml"

private fun <T : Any> allOf(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): List<T> =
    cityModel.iterFeatures().asSequence().mapNotNull { tryFrom(it!!) }.toList()

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun assertClose(expected: Double, actual: Double) = assertEquals(expected, actual, 1e-6)

private fun assertPosition(expected: Triple<Double, Double, Double>, actual: DirectPosition) {
    assertClose(expected.first, actual.x())
    assertClose(expected.second, actual.y())
    assertClose(expected.third, actual.z())
}

private fun assertEnvelope(envelope: Envelope?, lower: Triple<Double, Double, Double>, upper: Triple<Double, Double, Double>) {
    assertNotNull(envelope)
    assertPosition(lower, envelope.lowerCorner())
    assertPosition(upper, envelope.upperCorner())
}

class GeometryTest {
    @Test
    fun computeEnvelope() {
        val solid = assertNotNull(allOf(read(fixture(FZK_LOD1)), Building::tryFrom)[0].lod1Solid()?.object_())
        val lower = Triple(457842.0, 5439083.0, 111.8)
        val upper = Triple(457854.0, 5439093.0, 118.31769)
        assertEnvelope(solid.computeEnvelope(), lower, upper)
        val shell = assertNotNull(solid.exterior())
        assertEnvelope(shell.computeEnvelope(), lower, upper)
        assertEnvelope(solid.triangulate().getOrThrow().surface().computeEnvelope(), lower, upper)
        val first = assertNotNull(Polygon.tryFrom(assertNotNull(shell.members().next()?.object_())))
        val ground = Triple(457854.0, 5439093.0, 111.8)
        assertEnvelope(first.computeEnvelope(), lower, ground)
        assertEnvelope(assertNotNull(first.exterior()).computeEnvelope(), lower, ground)

        val space = allOf(read(fixture(ASAM_ROAD_SHAPE)), TrafficSpace::tryFrom)[0]
        val multiCurve = assertNotNull(space.lod2MultiCurve()?.object_())
        val curveLower = Triple(-48.38872036507727, 2.3148451158285663, 0.25)
        val curveUpper = Triple(-16.661414812688488, 26.674198193965925, 0.25)
        assertEnvelope(multiCurve.computeEnvelope(), curveLower, curveUpper)
        val member = multiCurve.curveMember().items().single()
        assertEnvelope(assertNotNull(member.object_()).computeEnvelope(), curveLower, curveUpper)
        val spaceSolid = assertNotNull(space.lod2Solid()?.object_())
        assertEnvelope(
            spaceSolid.computeEnvelope(),
            Triple(-49.60668801898414, 0.7284798382091271, 0.05),
            Triple(-15.44344715878162, 28.260563471585364, 4.95),
        )
        assertEquals(24, spaceSolid.points().items().size)

        val tree = allOf(read(fixture(RAILWAY)), SolitaryVegetationObject::tryFrom)
            .first { it.featureId().asStr() == "GMLID_SO092422_3593_9527" }
        val point = assertNotNull(tree.lod3ImplicitRepresentation()?.object_()?.referencePoint()?.object_())
        val reference = Triple(-568.8000793496976, 457.60044759869743, 105.00139681350242)
        assertEnvelope(point.computeEnvelope(), reference, reference)

        val tin = assertNotNull(allOf(read(fixture(OGC_GARAGE)), TinRelief::tryFrom)[0].tin()?.object_())
        assertEnvelope(tin.computeEnvelope(), Triple(458868.0, 5438343.0, 112.0), Triple(458892.0, 5438362.0, 114.0))
    }

    @Test
    fun polygonInteriorRings() {
        val ground = allOf(read(fixture(TUM)), GroundSurface::tryFrom).single()
        val multiSurface = assertNotNull(ground.lod2MultiSurface()?.object_())
        val polygon = assertNotNull(Polygon.tryFrom(assertNotNull(multiSurface.surfaceMember().items().single().object_())))
        assertEquals("DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly", polygon.id()?.asStr())
        val exterior = assertNotNull(LinearRing.tryFrom(assertNotNull(polygon.exterior())))
        assertEquals(11, exterior.points().items().size)
        assertClose(1371.825439453125, exterior.area3d())
        assertClose(150.78554397170106, exterior.length3d())
        val interior = assertNotNull(LinearRing.tryFrom(polygon.interior().items().single()))
        assertEquals(4, interior.points().items().size)
        assertClose(142.26318359375, interior.area3d())
        assertClose(47.7096809282068, interior.length3d())
        assertClose(1229.562255859375, polygon.area3d().getOrThrow())
        assertEquals(15, polygon.points().items().size)
        assertEnvelope(polygon.computeEnvelope(), Triple(691009.16, 5335994.57, 515.042), Triple(691054.07, 5336047.41, 515.042))
        val triangulation = multiSurface.triangulate().getOrThrow()
        assertFalse(triangulation.hasSkipped())
        assertEquals(15, triangulation.surface().triangles().items().size)
        assertClose(1229.5620994984272, triangulation.surface().area3d().getOrThrow())
    }

    @Test
    fun compositeSurfaceAndPatches() {
        val ground = allOf(read(fixture(OGC_ROAD_OVER_BRIDGE)), GroundSurface::tryFrom)
            .first { it.featureId().asStr() == "id_groundsurface1" }
        val multiSurface = assertNotNull(ground.lod2MultiSurface()?.object_())
        assertEquals("id_groundsurface1-0", multiSurface.id()?.asStr())
        assertClose(77500.15996032, multiSurface.area3d().getOrThrow())
        val kind = assertNotNull(multiSurface.surfaceMember().items().single().object_())
        assertEquals(GeometryType.CompositeSurface, kind.geometryType())
        assertNull(Polygon.tryFrom(kind))
        val composite = assertNotNull(CompositeSurface.tryFrom(kind))
        assertEquals("id_groundsurface1-1", composite.id()?.asStr())
        assertClose(77500.15996032, composite.area3d().getOrThrow())
        assertEquals(6, composite.points().items().size)
        assertEnvelope(composite.computeEnvelope(), Triple(0.0, 0.0, 0.0), Triple(393.7008, 196.8504, 0.0))
        val triangulation = composite.triangulate().getOrThrow()
        assertFalse(triangulation.hasSkipped())
        assertEquals(2, triangulation.surface().triangles().items().size)

        val ids = listOf("fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447", "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163")
        val members = composite.surfaceMember().items().map { assertNotNull(it.object_()) }
        assertEquals(ids.size, members.size)
        for ((surfaceKind, id) in members.zip(ids)) {
            assertEquals(GeometryType.Surface, surfaceKind.geometryType())
            val surface = assertNotNull(Surface.tryFrom(surfaceKind))
            assertEquals(id, surface.id()?.asStr())
            assertClose(38750.07998016, surface.area3d().getOrThrow())
            assertEquals(1, surface.triangulate().getOrThrow().surface().triangles().items().size)
            val patch = surface.patches().items().single()
            assertNull(Triangle.tryFrom(patch))
            val polygonPatch = assertNotNull(PolygonPatch.tryFrom(patch))
            assertTrue(polygonPatch.interior().items().isEmpty())
            assertEquals(3, assertNotNull(LinearRing.tryFrom(assertNotNull(polygonPatch.exterior()))).points().items().size)
            assertClose(38750.07998016, patch.area3d().getOrThrow())
            assertEquals(1, patch.triangulate().getOrThrow().surface().triangles().items().size)
        }
    }

    @Test
    fun trianglePatches() {
        val tin = assertNotNull(allOf(read(fixture(OGC_GARAGE)), TinRelief::tryFrom)[0].tin()?.object_())
        assertEquals(12, tin.surface().patches().items().size)
        val triangle = assertNotNull(tin.triangles().next())
        assertPosition(Triple(458883.0, 5438362.0, 114.0), triangle.a())
        assertPosition(Triple(458868.0, 5438362.0, 112.0), triangle.b())
        assertPosition(Triple(458875.0, 5438355.0, 112.0), triangle.c())
        assertClose(53.42518132865812, triangle.area())
        assertEquals(GeometryType.LinearRing, triangle.exterior().geometryType())
    }

    @Test
    fun unresolvedSurfaceReference() {
        val storey = allOf(read(fixture(OGC_UNITS)), Storey::tryFrom).first { it.featureId().asStr() == "storey1" }
        val multiSurface = assertNotNull(storey.lod2MultiSurface()?.object_())
        assertEquals(6, multiSurface.surfaceMember().items().size)
        assertError(multiSurface.area3d(), ErrorKind.UnresolvedReference, "#Wall_1_PolyID82397_997_453711_16336011")
        assertEquals(12, multiSurface.points().items().size)
        assertEnvelope(multiSurface.computeEnvelope(), Triple(457841.1, 5439082.1, 111.1), Triple(457853.9, 5439092.9, 113.9))
        val triangulation = multiSurface.triangulate().getOrThrow()
        assertFalse(triangulation.hasSkipped())
        assertEquals(6, triangulation.surface().triangles().items().size)
    }

    @Test
    fun solidUnresolvedReference() {
        val solid = assertNotNull(allOf(read(fixture(FZK_LOD2)), Building::tryFrom)[0].lod2Solid()?.object_())
        assertError(solid.volume3d(), ErrorKind.UnresolvedReference, "#PolyID7350_878_759628_120742")
    }

    @Test
    fun triangulateWithoutMembers() {
        val solid = assertNotNull(allOf(read(fixture(FZK_LOD2)), Building::tryFrom)[0].lod2Solid()?.object_())
        assertTrue(solid.points().items().isEmpty())
        assertNull(solid.computeEnvelope())
        assertError(solid.triangulate(), ErrorKind.InvalidArgument, "requires at least 1 element")
    }
}
