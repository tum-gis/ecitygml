package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import org.junit.jupiter.api.Nested
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.

private const val DATASET = "fzk-haus-citygml-3.0"
private const val CONSTRUCTION_ID = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86"
private const val TEST_BUILDING_ID = "KIT-Test-Building-01"
private const val WINDOW_ID = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz"

private val construction by lazy { read(DATASET, "01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml") }
private val interior by lazy { read(DATASET, "04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml") }
private val window by lazy { read(DATASET, "04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml") }
private val pointCloud by lazy { read(DATASET, "06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml") }

private typealias Point = Triple<Double, Double, Double>

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun featureTypes(cityModel: CityModel): List<FeatureType> = cityModel.iterFeatures().items().map { it.featureType() }

private fun storeys(cityModel: CityModel): List<Storey> = cityModel.iterFeatures().items().mapNotNull(Storey::tryFrom)

private fun assertCityModel(cityModel: CityModel, lower: Point, upper: Point) {
    assertEquals(1uL, cityModel.cityObjectsLen())
    val envelope = assertNotNull(cityModel.boundedBy()?.envelope())
    for ((position, expected) in listOf(envelope.lowerCorner() to lower, envelope.upperCorner() to upper)) {
        assertClose(position.x(), expected.first)
        assertClose(position.y(), expected.second)
        assertClose(position.z(), expected.third)
    }
}

/** The one height and occupancy of the storey examples' buildings. */
private fun assertHeightAndOccupancy(b: Building) {
    val height = b.heights().items().single()
    assertEquals("highestRoofEdge", height.highReference().value())
    assertEquals("lowestGroundPoint", height.lowReference().value())
    assertEquals(HeightStatusValue.Measured, height.status())
    assertClose(height.length().value(), 6.52)
    assertEquals("urn:adv:uom:m", height.length().uom())
    assertEquals(2L, b.occupancies().items().single().numberOfOccupants())
}

/** The storeys' first names and classes. */
private fun assertStoreys(cityModel: CityModel, classes: List<String?>) {
    val found = storeys(cityModel)
    assertEquals(listOf("Ground Floor", "Second Floor"), found.map { firstName(it.names()) })
    assertEquals(classes, found.map { it.class_()?.value() })
}

/** A storey's boundaries as (feature type, first name, LoD2 multi surface); all inline wall, roof or ground surfaces. */
private fun boundarySurfaces(storey: Storey): List<Triple<FeatureType, String, MultiSurfaceProperty?>> =
    storey.boundaries().items().map { property ->
        assertNull(property.href())
        val feature = AbstractFeatureKindRef.fromSpaceBoundary(assertNotNull(property.object_()))
        val wall = WallSurface.tryFrom(feature)
        val roof = RoofSurface.tryFrom(feature)
        val ground = GroundSurface.tryFrom(feature)
        when {
            wall != null -> Triple(feature.featureType(), firstName(wall.names()), wall.lod2MultiSurface())
            roof != null -> Triple(feature.featureType(), firstName(roof.names()), roof.lod2MultiSurface())
            ground != null -> Triple(feature.featureType(), firstName(ground.names()), ground.lod2MultiSurface())
            else -> error("unexpected boundary ${feature.featureType()}")
        }
    }

/** Writes the city model and reads it back: the same feature types in the same order and the building's id. */
private fun assertRoundTrip(cityModel: CityModel, buildingId: String) {
    val writer = GmlWriter.create(CitygmlFormat.Gml)
    writer.finish(cityModel).getOrThrow()
    val written = GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
    assertEquals(featureTypes(cityModel), featureTypes(written))
    assertEquals(buildingId, building(written).featureId().asStr())
}

class FzkHausCitygml30Test {
    @Nested
    inner class Construction {
        @Test
        fun constructionCityModel() {
            assertCityModel(construction, Triple(458899.5, 5438784.5, 113.5), Triple(458912.5, 5438795.5, 120.017691))
            val expected = listOf(FeatureType.CityModel, FeatureType.Building, FeatureType.Storey) +
                List(5) { FeatureType.BuildingConstructiveElement } +
                FeatureType.Storey +
                List(6) { FeatureType.BuildingConstructiveElement } +
                FeatureType.Appearance +
                List(5) { FeatureType.ParameterizedTexture } +
                List(5) { FeatureType.X3DMaterial }
            assertEquals(expected, featureTypes(construction))
            assertEquals(14, construction.iterCityObjects().asSequence().count())
        }

        @Test
        fun constructionBuilding() {
            val b = building(construction)
            assertEquals(CONSTRUCTION_ID, b.featureId().asStr())
            assertEquals(listOf("KIT FZK-Haus"), b.names().items().map { it.value() })
            assertNull(b.class_())
            assertEquals(listOf("31001_1000"), b.functions().items().map { it.value() })
            assertEquals(0, b.usages().asSequence().count())
            assertEquals("3100", b.roofType()?.value())
            assertNull(b.storeysAboveGround())
            assertNull(b.storeysBelowGround())
            assertHeightAndOccupancy(b)
            assertEquals(0, b.boundaries().asSequence().count())
            assertEquals(0, b.genericAttributes().asSequence().count())
            assertNull(b.lod2Solid())
            assertNull(b.lod2MultiSurface())
        }

        @Test
        fun constructionStoreys() {
            val subdivisions = building(construction).buildingSubdivisions().items()
            assertEquals(2, subdivisions.size)
            for (subdivision in subdivisions) {
                assertNull(subdivision.href())
                assertEquals(FeatureType.Storey, assertNotNull(subdivision.object_()).featureType())
            }
            assertStoreys(construction, listOf("Entrance Floor", "non Entrance Floor"))
            for (storey in storeys(construction)) {
                assertEquals(0, storey.functions().asSequence().count())
                assertEquals(0, storey.usages().asSequence().count())
                assertEquals(0, storey.boundaries().asSequence().count())
                assertNull(storey.lod2Solid())
            }
        }

        @Test
        fun constructionRoundTrip() = assertRoundTrip(construction, CONSTRUCTION_ID)
    }

    @Nested
    inner class Interior {
        @Test
        fun interiorCityModel() {
            assertCityModel(interior, Triple(458900.0, 5438785.0, 113.5), Triple(458912.0, 5438795.0, 120.017691))
            val types = featureTypes(interior)
            assertEquals(77, types.size)
            assertEquals(
                mapOf(
                    FeatureType.CityModel to 1,
                    FeatureType.Building to 1,
                    FeatureType.Storey to 2,
                    FeatureType.GroundSurface to 1,
                    FeatureType.WallSurface to 8,
                    FeatureType.RoofSurface to 2,
                    FeatureType.BuildingRoom to 7,
                    FeatureType.InteriorWallSurface to 27,
                    FeatureType.CeilingSurface to 8,
                    FeatureType.FloorSurface to 7,
                    FeatureType.ClosureSurface to 6,
                    FeatureType.Appearance to 1,
                    FeatureType.ParameterizedTexture to 5,
                    FeatureType.X3DMaterial to 1,
                ),
                types.groupingBy { it }.eachCount(),
            )
            assertEquals(69, interior.iterCityObjects().asSequence().count())
        }

        @Test
        fun interiorBuilding() {
            val b = building(interior)
            assertEquals(TEST_BUILDING_ID, b.featureId().asStr())
            assertEquals(listOf("KIT Test Building FZK-Haus for CityGML 3.0"), b.names().items().map { it.value() })
            assertNull(b.class_())
            assertNull(b.roofType())
            assertEquals(0, b.functions().asSequence().count())
            assertEquals(0, b.usages().asSequence().count())
            assertHeightAndOccupancy(b)
            val attribute = b.genericAttributes().items().single()
            assertEquals("@cityeditor:layer" to "LoD2-Ausgeblendet", attribute.name() to attribute.asString()?.value())
            assertEquals(0, b.boundaries().asSequence().count())
        }

        @Test
        fun interiorSolidUnresolved() {
            val property = assertNotNull(building(interior).lod2Solid())
            assertNull(property.href())
            val solid = assertNotNull(property.object_())
            val members = assertNotNull(solid.exterior()).members().items()
            assertEquals(11, members.size)
            assertTrue(members.all { it.object_() == null })
            assertTrue(solid.volume3d().isFailure)
        }

        @Test
        fun interiorStoreyBoundaries() {
            val expected = listOf(
                listOf(
                    Triple(FeatureType.GroundSurface, "Ground", 120.0),
                    Triple(FeatureType.WallSurface, "Ground Floor / Wall East", 29.0),
                    Triple(FeatureType.WallSurface, "Ground Floor / Wall South", 34.80000000447035),
                    Triple(FeatureType.WallSurface, "Ground Floor / Wall West", 29.0),
                    Triple(FeatureType.WallSurface, "Ground Floor / Wall North", 34.80000000447035),
                ),
                listOf(
                    Triple(FeatureType.RoofSurface, "Second Floor / Roof South", 69.28203022609509),
                    Triple(FeatureType.RoofSurface, "Second Floor / Roof North", 69.28203022609509),
                    Triple(FeatureType.WallSurface, "Second Floor / Wall South", 8.771279998123646),
                    Triple(FeatureType.WallSurface, "Second Floor / Wall West", 21.743155002593994),
                    Triple(FeatureType.WallSurface, "Second Floor / Wall East", 21.743155002593994),
                    Triple(FeatureType.WallSurface, "Second Floor / Wall North", 8.771279998123646),
                ),
            )
            val found = storeys(interior)
            assertEquals(expected.size, found.size)
            found.zip(expected).forEach { (storey, surfaces) ->
                val actual = boundarySurfaces(storey)
                assertEquals(surfaces.map { it.first to it.second }, actual.map { it.first to it.second })
                actual.zip(surfaces).forEach { (surface, want) ->
                    assertClose(assertNotNull(surface.third?.object_()).area3d().getOrThrow(), want.third)
                }
            }
            assertStoreys(interior, listOf(null, null))
        }

        @Test
        fun interiorRoundTrip() = assertRoundTrip(interior, TEST_BUILDING_ID)
    }

    @Nested
    inner class Window {
        @Test
        fun windowCityModel() {
            assertCityModel(window, Triple(458899.5, 5438784.5, 113.5), Triple(458912.5, 5438795.5, 120.017691))
            val types = featureTypes(window)
            assertEquals(54, types.size)
            assertEquals(
                mapOf(
                    FeatureType.CityModel to 1,
                    FeatureType.Building to 1,
                    FeatureType.Storey to 2,
                    FeatureType.BuildingConstructiveElement to 18,
                    FeatureType.Door to 5,
                    FeatureType.Window to 11,
                    FeatureType.Appearance to 2,
                    FeatureType.ParameterizedTexture to 5,
                    FeatureType.X3DMaterial to 9,
                ),
                types.groupingBy { it }.eachCount(),
            )
            assertEquals(37, window.iterCityObjects().asSequence().count())
        }

        @Test
        fun windowBuilding() {
            val b = building(window)
            assertEquals(WINDOW_ID, b.featureId().asStr())
            assertEquals(listOf("KIT FZK-Haus"), b.names().items().map { it.value() })
            assertEquals(listOf("31001_1000"), b.functions().items().map { it.value() })
            assertEquals("3100", b.roofType()?.value())
            assertEquals(0, b.boundaries().asSequence().count())
            assertStoreys(window, listOf("Entrance Floor", "non Entrance Floor"))
        }

        @Test
        fun windowRoundTrip() = assertRoundTrip(window, WINDOW_ID)
    }

    @Nested
    inner class PointCloud {
        @Test
        fun pointCloudCityModel() {
            assertCityModel(pointCloud, Triple(458900.0, 5438785.0, 113.5), Triple(458912.0, 5438795.0, 120.017691))
            val expected = listOf(FeatureType.CityModel, FeatureType.Building, FeatureType.Storey, FeatureType.GroundSurface) +
                List(4) { FeatureType.WallSurface } +
                listOf(FeatureType.Storey, FeatureType.RoofSurface, FeatureType.RoofSurface) +
                List(4) { FeatureType.WallSurface }
            assertEquals(expected, featureTypes(pointCloud))
        }

        @Test
        fun pointCloudStoreyBoundaries() {
            val b = building(pointCloud)
            assertEquals(TEST_BUILDING_ID, b.featureId().asStr())
            assertEquals(0, b.boundaries().asSequence().count())
            val expected = listOf(
                listOf(
                    FeatureType.GroundSurface to " Ground Floor / GroundSurface",
                    FeatureType.WallSurface to "Ground Floor / Wall East",
                    FeatureType.WallSurface to "Ground Floor / Wall South",
                    FeatureType.WallSurface to "Ground Floor / Wall West",
                    FeatureType.WallSurface to "Ground Floor / Wall North",
                ),
                listOf(
                    FeatureType.RoofSurface to "Second Floor / Roof North",
                    FeatureType.RoofSurface to "Second Floor / Roof South",
                    FeatureType.WallSurface to "Second Floor / Wall South",
                    FeatureType.WallSurface to "Second Floor / Wall West",
                    FeatureType.WallSurface to "Second Floor / Wall East",
                    FeatureType.WallSurface to "Second Floor / Wall North",
                ),
            )
            val found = storeys(pointCloud)
            assertEquals(expected.size, found.size)
            found.zip(expected).forEach { (storey, surfaces) ->
                val actual = boundarySurfaces(storey)
                assertEquals(surfaces, actual.map { it.first to it.second })
                assertTrue(actual.all { it.third == null })
            }
        }

        @Test
        fun pointCloudRoundTrip() = assertRoundTrip(pointCloud, TEST_BUILDING_ID)
    }
}
