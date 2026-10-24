package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.

private val entrance by lazy { read("tum-main-entrance", "TUM-Main-Entrance.gml") }

private val boundaryTypes = List(10) { FeatureType.WallSurface } + FeatureType.GroundSurface +
    List(3) { FeatureType.WallSurface } + listOf(FeatureType.RoofSurface, FeatureType.RoofSurface, FeatureType.WallSurface)

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun featureTypes(cityModel: CityModel): List<FeatureType> = cityModel.iterFeatures().items().map { it.featureType() }

private fun assertPointClose(position: DirectPosition, x: Double, y: Double, z: Double) {
    assertClose(position.x(), x)
    assertClose(position.y(), y)
    assertClose(position.z(), z)
}

/** The area of an inline LoD2 multi surface. */
private fun lod2Area(property: MultiSurfaceProperty?): Double {
    assertNotNull(property)
    assertNull(property.href())
    return assertNotNull(property.object_()).area3d().getOrThrow()
}

class TumMainEntranceTest {
    @Test
    fun entranceCityModel() {
        assertEquals(1uL, entrance.cityObjectsLen())
        val envelope = assertNotNull(entrance.boundedBy()?.envelope())
        assertPointClose(envelope.lowerCorner(), 689975.68, 5335962.63, 503.0)
        assertPointClose(envelope.upperCorner(), 692025.893, 5338012.713, 581.62)
        assertEquals(listOf(FeatureType.CityModel, FeatureType.Building) + boundaryTypes, featureTypes(entrance))
        assertEquals(18, entrance.iterCityObjects().asSequence().count())
    }

    @Test
    fun entranceBuildingAttributes() {
        val b = building(entrance)
        assertEquals("DEBY_LOD2_4959457", b.featureId().asStr())
        assertEquals(0, b.names().asSequence().count())
        assertNull(b.class_())
        val function = b.functions().items().single()
        assertEquals("31001_3020", function.value())
        assertEquals(0, b.usages().asSequence().count())
        assertEquals("1000", b.roofType()?.value())
        assertEquals(4L, b.storeysAboveGround())
        assertNull(b.storeysBelowGround())

        val height = b.heights().items().single()
        assertEquals("topOfConstruction", height.highReference().value())
        assertEquals("lowestGroundPoint", height.lowReference().value())
        assertEquals(HeightStatusValue.Measured, height.status())
        assertClose(height.length().value(), 19.408)
        assertEquals("urn:adv:uom:m", height.length().uom())

        val created = assertNotNull(b.creationDate())
        assertEquals(Triple(2025, 1u, 2u), Triple(created.year(), created.month(), created.day()))
        assertEquals(0u to 0u, created.hour() to created.minute())
        assertEquals(3600, created.offsetSeconds())
        assertNull(b.boundedBy())
        assertEquals(0, b.occupancies().asSequence().count())
        assertEquals(0, b.buildingSubdivisions().asSequence().count())
    }

    @Test
    fun entranceExternalReference() {
        val reference = building(entrance).externalReferences().items().single()
        assertEquals("DEBYvAAAAABTMIyA", reference.targetResource())
    }

    @Test
    fun entranceExternalReferenceDetails() {
        val reference = building(entrance).externalReferences().items().single()
        assertEquals("http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100", reference.informationSystem())
        assertNull(reference.relationType())
    }

    @Test
    fun entranceGenericAttributes() {
        val attributes = building(entrance).genericAttributes().items().map { it.name() to assertNotNull(it.asString()).value() }
        assertEquals(
            listOf(
                "DatenquelleBodenhoehe" to "1100",
                "DatenquelleDachhoehe" to "1000",
                "DatenquelleLage" to "1000",
                "Gemeindeschluessel" to "09162000",
                "HoeheDach" to "534.450",
                "HoeheGrund" to "515.042",
                "Methode" to "2000",
                "NiedrigsteTraufeDesGebaeudes" to "527.312",
                "Grundrissaktualitaet" to "2025-02-17",
                "Geometrietyp2DReferenz" to "3000",
            ),
            attributes,
        )
    }

    @Test
    fun entranceBoundaries() {
        val b = building(entrance)
        assertTrue(b.boundaries().items().all { it.href() == null })
        val features = boundaries(b)
        assertEquals(boundaryTypes, features.map { it.featureType() })

        val walls = features.mapNotNull(WallSurface::tryFrom)
        assertEquals("DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2", walls.first().featureId().asStr())
        assertEquals(0, walls.first().names().asSequence().count())
        assertClose(walls.sumOf { lod2Area(it.lod2MultiSurface()) }, 3783.3908922901974)

        val roofs = features.mapNotNull(RoofSurface::tryFrom).map { lod2Area(it.lod2MultiSurface()) }
        assertEquals(2, roofs.size)
        assertClose(roofs[0], 250.233154296875)
        assertClose(roofs[1], 979.3291015625)
        assertClose(roofs.sum(), 1229.562255859375)

        val grounds = features.mapNotNull(GroundSurface::tryFrom).map { lod2Area(it.lod2MultiSurface()) }
        assertEquals(1, grounds.size)
        assertClose(grounds.single(), 1229.562255859375)
    }

    @Test
    fun entranceWallTriangulation() {
        val wall = assertNotNull(entrance.iterFeatures().items().firstNotNullOfOrNull(WallSurface::tryFrom))
        val multiSurface = assertNotNull(wall.lod2MultiSurface()?.object_())
        assertEquals(1, multiSurface.surfaceMember().asSequence().count())
        assertClose(multiSurface.area3d().getOrThrow(), 546.6949745937537)
        val triangulation = multiSurface.triangulate().getOrThrow()
        assertEquals(4, triangulation.surface().triangles().asSequence().count())
        assertFalse(triangulation.hasSkipped())
        assertClose(triangulation.surface().area3d().getOrThrow(), 546.6949742237184)
    }

    @Test
    fun entranceSolidUnresolved() {
        val property = assertNotNull(building(entrance).lod2Solid())
        assertNull(property.href())
        val solid = assertNotNull(property.object_())
        val members = assertNotNull(solid.exterior()).members().items()
        assertEquals(17, members.size)
        assertTrue(members.all { it.object_() == null })
        assertTrue(solid.volume3d().isFailure)
    }

    @Test
    fun entranceRoundTrip() {
        val writer = GmlWriter.create(CitygmlFormat.Gml)
        writer.finish(entrance).getOrThrow()
        val written = GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
        assertEquals(featureTypes(entrance), featureTypes(written))
        assertEquals("DEBY_LOD2_4959457", building(written).featureId().asStr())
        fun boundaryIds(model: CityModel): List<String> =
            building(model).boundaries().items().map { assertNotNull(it.object_()).featureId().asStr() }
        assertEquals(boundaryIds(entrance), boundaryIds(written))
    }
}
