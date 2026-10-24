package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import org.junit.jupiter.api.Nested
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.

private const val DATASET = "ogc-citygml-3.0-encodings"

private val garage by lazy { read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml") }
private val units by lazy { read(DATASET, "BuildingUnits_Storeys_xlink.gml") }
private val roadBridge by lazy { read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml") }
private val versioning by lazy { read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml") }

private val WALL = FeatureType.WallSurface
private val ROOF = FeatureType.RoofSurface
private val GROUND = FeatureType.GroundSurface

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun featureTypes(cityModel: CityModel): List<FeatureType> = cityModel.iterFeatures().items().map { it.featureType() }

/** All features a class accepts, in document order. */
private fun <T> allOf(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): List<T> =
    cityModel.iterFeatures().items().mapNotNull(tryFrom)

private fun names(names: Iterator<Code?>): List<String> = names.items().map { it.value() }

private fun assertEnvelope(envelope: Envelope?, lower: Triple<Double, Double, Double>, upper: Triple<Double, Double, Double>) {
    assertNotNull(envelope)
    for ((position, expected) in listOf(envelope.lowerCorner() to lower, envelope.upperCorner() to upper)) {
        assertClose(position.x(), expected.first)
        assertClose(position.y(), expected.second)
        assertClose(position.z(), expected.third)
    }
}

private fun roundTrip(cityModel: CityModel): CityModel {
    val writer = GmlWriter.create(CitygmlFormat.Gml)
    writer.finish(cityModel).getOrThrow()
    return GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
}

private data class Surface(val type: FeatureType, val id: String, val name: String?, val multiSurface: MultiSurfaceProperty?)

/** A space's boundaries; all inline wall, roof or ground surfaces. */
private fun surfaces(boundaries: Iterator<AbstractSpaceBoundaryProperty?>): List<Surface> =
    boundaries.items().map { property ->
        assertNull(property.href())
        val obj = assertNotNull(property.object_())
        val feature = AbstractFeatureKindRef.fromSpaceBoundary(obj)
        val id = obj.featureId().asStr()
        val wall = WallSurface.tryFrom(feature)
        val roof = RoofSurface.tryFrom(feature)
        val ground = GroundSurface.tryFrom(feature)
        when {
            wall != null -> Surface(feature.featureType(), id, wall.names().items().firstOrNull()?.value(), wall.lod2MultiSurface())
            roof != null -> Surface(feature.featureType(), id, roof.names().items().firstOrNull()?.value(), roof.lod2MultiSurface())
            ground != null -> Surface(feature.featureType(), id, ground.names().items().firstOrNull()?.value(), ground.lod2MultiSurface())
            else -> error("unexpected boundary ${feature.featureType()}")
        }
    }

private fun lod2Area(property: MultiSurfaceProperty?): Double = assertNotNull(property?.object_()).area3d().getOrThrow()

private fun assertHeight(heights: Iterator<Height?>, length: Double) {
    val height = heights.items().single()
    assertEquals("highestRoofEdge", height.highReference().value())
    assertEquals("lowestGroundPoint", height.lowReference().value())
    assertEquals(HeightStatusValue.Measured, height.status())
    assertClose(height.length().value(), length)
    assertEquals("#m", height.length().uom())
}

/** The hrefs of a storey's LoD2 surface members (null for inline members). */
private fun memberHrefs(storey: Storey): List<String?> {
    val property = assertNotNull(storey.lod2MultiSurface())
    assertNull(property.href())
    return assertNotNull(property.object_()).surfaceMember().items().map { member ->
        assertEquals(member.object_() == null, member.href() != null)
        member.href()?.toString_()
    }
}

/** The relations of the roof surfaces and traffic areas, in document order: (city object, relation type, href). */
private fun relations(cityModel: CityModel): List<Triple<String, String, String?>> =
    cityModel.iterFeatures().items().flatMap { feature ->
        val roof = RoofSurface.tryFrom(feature)
        val area = TrafficArea.tryFrom(feature)
        val (id, relatedTo) = when {
            roof != null -> roof.featureId().asStr() to roof.relatedTo()
            area != null -> area.featureId().asStr() to area.relatedTo()
            else -> return@flatMap emptyList()
        }
        relatedTo.items().map { property ->
            assertNull(property.href())
            val relation = assertNotNull(property.object_())
            assertEquals(0, relation.genericAttributes().asSequence().count())
            Triple(id, relation.relationType().value(), relation.relationTo().href()?.toString_())
        }
    }

/** (year, month, day) of a date time at 00:00 UTC. */
private fun date(dateTime: DateTime?): Triple<Int, UInt, UInt>? = dateTime?.let {
    assertEquals(Triple(0u, 0u, 0), Triple(it.hour(), it.minute(), it.offsetSeconds()))
    Triple(it.year(), it.month(), it.day())
}

class OgcCitygml30EncodingsTest {
    @Nested
    inner class Garage {
        private fun building(): Building = allOf(garage, Building::tryFrom).single()

        @Test
        fun garageCityModel() {
            assertEquals(2uL, garage.cityObjectsLen())
            assertEnvelope(garage.boundedBy()?.envelope(), Triple(458868.0, 5438343.0, 112.0), Triple(458892.0, 5438362.0, 117.0))
            val expected = listOf(FeatureType.CityModel, FeatureType.Building, GROUND) + List(4) { WALL } +
                listOf(ROOF, ROOF, FeatureType.BuildingPart) + List(4) { WALL } +
                listOf(GROUND, ROOF, FeatureType.ReliefFeature, FeatureType.TinRelief)
            assertEquals(expected, featureTypes(garage))
            assertEquals(17, garage.iterCityObjects().asSequence().count())
        }

        @Test
        fun garageBuilding() {
            val b = building()
            assertEquals("GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68", b.featureId().asStr())
            assertEquals(listOf("Example Building LOD2"), names(b.names()))
            assertNull(b.class_())
            assertEquals(listOf("1000"), b.functions().items().map { it.value() })
            assertEquals(0, b.usages().asSequence().count())
            assertEquals("1030", b.roofType()?.value())
            assertEquals(1L, b.storeysAboveGround())
            assertNull(b.storeysBelowGround())
            val date = assertNotNull(b.dateOfConstruction())
            assertEquals(Triple(1985, 1u, 1u), Triple(date.year(), date.month(), date.day()))
            assertHeight(b.heights(), 6.0)
            val expected = listOf(
                Triple(GROUND, "Ground Slab", 50.0),
                Triple(WALL, "Wall South", 30.0),
                Triple(WALL, "Wall North", 30.0),
                Triple(WALL, "Wall East", 20.0),
                Triple(WALL, "Wall West", 20.0),
                Triple(ROOF, "Roof North", 32.01562118716424),
                Triple(ROOF, "Roof South", 32.01562118716424),
            )
            val actual = surfaces(b.boundaries())
            assertEquals(expected.map { it.first to it.second }, actual.map { it.type to it.name })
            actual.zip(expected).forEach { (surface, want) -> assertClose(lod2Area(surface.multiSurface), want.third) }
        }

        @Test
        fun garageBuildingPart() {
            val property = building().buildingParts().items().single()
            assertNull(property.href())
            val part = assertNotNull(property.object_())
            assertEquals("GMLID_BUI379228_1244_301", part.featureId().asStr())
            assertEquals(listOf("Example BuildingPart LOD2"), names(part.names()))
            assertNull(part.class_())
            assertEquals(listOf("1630"), part.functions().items().map { it.value() })
            assertEquals(0, part.usages().asSequence().count())
            assertEquals("1010", part.roofType()?.value())
            val date = assertNotNull(part.dateOfConstruction())
            assertEquals(Triple(1985, 1u, 1u), Triple(date.year(), date.month(), date.day()))
            assertHeight(part.heights(), 2.5)
            // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
            val expected = listOf(
                Triple(WALL, "Garage Wall East", 9.600000023841858),
                Triple(WALL, "Garage Wall South", 6.25),
                Triple(WALL, "Garage Wall West", null),
                Triple(WALL, "Garage Wall North", 5.75),
                Triple(GROUND, "Garage Ground Slab", 10.0),
                Triple(ROOF, "Garage Roof", 10.012492197250394),
            )
            val actual = surfaces(part.boundaries())
            assertEquals(expected.map { it.first to it.second }, actual.map { it.type to it.name })
            actual.zip(expected).forEach { (surface, want) -> want.third?.let { assertClose(lod2Area(surface.multiSurface), it) } }
        }

        @Test
        fun garageRelief() {
            val relief = allOf(garage, ReliefFeature::tryFrom).single()
            assertEquals("GML_6bb30328-7599-4500-90ef-766fde6aa67b", relief.featureId().asStr())
            assertEquals(listOf("Example TIN LOD2"), names(relief.names()))
            assertEquals(LevelOfDetail.Two, relief.lod())
            val component = relief.reliefComponents().items().single()
            assertNull(component.href())
            assertEquals(FeatureType.TinRelief, assertNotNull(component.object_()).featureType())

            val tinRelief = allOf(garage, TinRelief::tryFrom).single()
            assertEquals("GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9", tinRelief.featureId().asStr())
            assertEquals(listOf("Ground"), names(tinRelief.names()))
            assertEquals(LevelOfDetail.Two, tinRelief.lod())
            val tin = assertNotNull(tinRelief.tin())
            assertNull(tin.href())
            val surface = assertNotNull(tin.object_())
            assertEquals(12, surface.triangles().asSequence().count())
            assertClose(surface.area3d().getOrThrow(), 399.8446647372588)
        }

        @Test
        fun garageRoundTrip() {
            val written = roundTrip(garage)
            assertEquals(featureTypes(garage), featureTypes(written))
            val ids = allOf(written, Building::tryFrom).map { it.featureId().asStr() } +
                allOf(written, BuildingPart::tryFrom).map { it.featureId().asStr() } +
                allOf(written, ReliefFeature::tryFrom).map { it.featureId().asStr() } +
                allOf(written, TinRelief::tryFrom).map { it.featureId().asStr() }
            assertEquals(
                listOf(
                    "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68",
                    "GMLID_BUI379228_1244_301",
                    "GML_6bb30328-7599-4500-90ef-766fde6aa67b",
                    "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9",
                ),
                ids,
            )
        }
    }

    @Nested
    inner class Units {
        @Test
        fun unitsCityModel() {
            assertEquals(1uL, units.cityObjectsLen())
            assertEnvelope(units.boundedBy()?.envelope(), Triple(457841.0, 5439082.0, 111.0), Triple(457854.0, 5439093.0, 121.0))
            fun room(walls: Int) = listOf(FeatureType.BuildingRoom) + List(walls) { FeatureType.InteriorWallSurface } +
                listOf(FeatureType.FloorSurface, FeatureType.CeilingSurface)
            val expected = listOf(FeatureType.CityModel, FeatureType.Building) + List(3) { WALL } +
                listOf(ROOF, WALL, ROOF, GROUND) + room(8) + room(8) + room(4) +
                listOf(FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey)
            assertEquals(expected, featureTypes(units))
            assertEquals(41, units.iterCityObjects().asSequence().count())
        }

        @Test
        fun unitsBuilding() {
            val b = allOf(units, Building::tryFrom).single()
            assertEquals("building_unit_example_1", b.featureId().asStr())
            assertEquals(0, b.names().asSequence().count())
            assertEquals(0, b.functions().asSequence().count())
            assertEquals(0, b.usages().asSequence().count())
            assertNull(b.class_())
            assertNull(b.roofType())
            val expected = listOf(
                Triple(WALL, "Outer Wall 1 (West)", 89.375),
                Triple(WALL, "Outer Wall 2 (South)", 81.25),
                Triple(WALL, "Outer Wall 3 (East)", 89.375),
                Triple(ROOF, "Roof 1 (North)", 86.53792521201326),
                Triple(WALL, "Outer Wall 4 (North)", 81.25),
                Triple(ROOF, "Roof 2 (South)", 86.53792521201326),
                Triple(GROUND, "Base Surface", 143.0),
            )
            val actual = surfaces(b.boundaries())
            assertEquals(expected.map { it.first to it.second }, actual.map { it.type to it.name })
            actual.zip(expected).forEach { (surface, want) -> assertClose(lod2Area(surface.multiSurface), want.third) }
        }

        @Test
        fun unitsSubdivisions() {
            val b = allOf(units, Building::tryFrom).single()
            val subdivisions = b.buildingSubdivisions().items()
            assertTrue(subdivisions.all { it.href() == null })
            assertEquals(
                listOf(FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey),
                subdivisions.map { assertNotNull(it.object_()).featureType() },
            )
            val found = allOf(units, BuildingUnit::tryFrom)
            assertEquals(listOf("BuildingUnit_apartment1", "BuildingUnit_apartment2"), found.map { it.featureId().asStr() })
            for (unit in found) {
                assertEquals(listOf("apartment"), unit.functions().items().map { it.value() })
                assertNull(unit.class_())
                assertEquals(0, unit.usages().asSequence().count())
                assertEquals(0, unit.boundaries().asSequence().count())
                assertNull(unit.lod2MultiSurface())
            }
            val storeys = allOf(units, Storey::tryFrom)
            assertEquals(listOf("storey1", "storey2"), storeys.map { it.featureId().asStr() })
            for (storey in storeys) {
                assertEquals(0, storey.names().asSequence().count())
                assertNull(storey.class_())
                assertEquals(0, storey.functions().asSequence().count())
                assertEquals(0, storey.usages().asSequence().count())
                assertEquals(0, storey.boundaries().asSequence().count())
            }
        }

        @Test
        fun unitsStoreyGeometry() {
            val expected = listOf(
                Triple(
                    listOf(
                        "#Wall_1_PolyID82397_997_453711_16336011",
                        "#Wall_1_PolyID82397_997_453711_16336012",
                        "#Wall_1_PolyID82397_997_453711_163360136",
                    ),
                    Triple(457841.1, 5439082.1, 111.1),
                    Triple(457853.9, 5439092.9, 113.9),
                ),
                Triple(
                    listOf(
                        "#Wall_1_PolyID82397_997_453711_163360112",
                        "#Wall_1_PolyID82397_997_453711_163360122",
                        "#Wall_1_PolyID82397_997_453711_1633601362",
                    ),
                    Triple(457841.1, 5439082.1, 114.1),
                    Triple(457853.9, 5439092.9, 116.9),
                ),
            )
            val storeys = allOf(units, Storey::tryFrom)
            assertEquals(expected.size, storeys.size)
            storeys.zip(expected).forEach { (storey, want) ->
                val (hrefs, lower, upper) = want
                assertEquals(listOf<String?>(null) + hrefs + listOf(null, null), memberHrefs(storey))
                assertTrue(assertNotNull(storey.lod2MultiSurface()?.object_()).area3d().isFailure)
                assertEnvelope(storey.boundedBy()?.envelope(), lower, upper)
            }
        }

        @Test
        fun unitsRoundTrip() {
            val written = roundTrip(units)
            assertEquals(featureTypes(units), featureTypes(written))
            assertEquals("building_unit_example_1", allOf(written, Building::tryFrom).single().featureId().asStr())
            assertEquals(allOf(units, Storey::tryFrom).map(::memberHrefs), allOf(written, Storey::tryFrom).map(::memberHrefs))
        }
    }

    @Nested
    inner class RoadBridge {
        @Test
        fun roadBridgeCityModel() {
            assertEquals(2uL, roadBridge.cityObjectsLen())
            assertNull(roadBridge.boundedBy())
            val section = listOf(FeatureType.Section, FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea)
            val expected = listOf(FeatureType.CityModel, FeatureType.Bridge, GROUND, ROOF, ROOF) + List(4) { WALL } +
                listOf(FeatureType.Road) + section + section + section
            assertEquals(expected, featureTypes(roadBridge))
            assertEquals(24, roadBridge.iterCityObjects().asSequence().count())
        }

        @Test
        fun roadBridgeBridge() {
            val bridge = allOf(roadBridge, Bridge::tryFrom).single()
            assertEquals("id_bridge1", bridge.featureId().asStr())
            assertEquals(0, bridge.names().asSequence().count())
            assertEquals(0, bridge.relatedTo().asSequence().count())
            val expected = listOf(
                "id_groundsurface1" to 77500.15996032,
                "id_roofsurface1" to 38750.07998016,
                "id_roofsurface2" to 38750.07998016,
                "id_wallsurface4" to 10075.02000744,
                "id_wallsurface1" to 20150.04001488,
                "id_wallsurface2" to 10075.02000744,
                "id_wallsurface3" to 20150.04001488,
            )
            val actual = surfaces(bridge.boundaries())
            assertEquals(expected.map { it.first }, actual.map { it.id })
            actual.zip(expected).forEach { (surface, want) -> assertClose(lod2Area(surface.multiSurface), want.second) }
        }

        @Test
        fun roadBridgeRoad() {
            val road = allOf(roadBridge, Road::tryFrom).single()
            assertEquals("id_road1", road.featureId().asStr())
            assertEquals(0, road.relatedTo().asSequence().count())
            assertEquals(0, road.trafficSpaces().asSequence().count())
            assertEquals(0, road.auxiliaryTrafficSpaces().asSequence().count())
            val sections = road.sections().items().map { assertNull(it.href()); assertNotNull(it.object_()) }
            assertEquals(listOf("id_section1", "id_section2", "id_section3"), sections.map { it.featureId().asStr() })
            val spaces = sections.flatMap { section ->
                section.trafficSpaces().items().map { assertNull(it.href()); assertNotNull(it.object_()) }
            }
            val numbers = listOf(1, 2, 5, 6, 3, 4)
            assertEquals(numbers.map { "id_trafficspace$it" }, spaces.map { it.featureId().asStr() })
            spaces.zip(numbers).forEach { (space, number) ->
                val boundary = space.boundaries().items().single()
                assertNull(boundary.href())
                val area = assertNotNull(boundary.object_())
                assertEquals(FeatureType.TrafficArea, area.featureType())
                assertEquals("id_trafficarea$number", area.featureId().asStr())
            }
        }

        @Test
        fun roadBridgeRelations() {
            assertEquals(
                listOf(
                    Triple("id_roofsurface1", "equal", "id_trafficarea5"),
                    Triple("id_roofsurface2", "equal", "id_trafficarea6"),
                    Triple("id_trafficarea5", "equal", "id_roofSurface1"),
                    Triple("id_trafficarea6", "equal", "id_roofSurface2"),
                ),
                relations(roadBridge),
            )
            assertTrue(allOf(roadBridge, WallSurface::tryFrom).all { it.relatedTo().asSequence().count() == 0 })
            assertTrue(allOf(roadBridge, GroundSurface::tryFrom).all { it.relatedTo().asSequence().count() == 0 })
        }

        @Test
        fun roadBridgeRoundTrip() {
            val written = roundTrip(roadBridge)
            assertEquals(featureTypes(roadBridge), featureTypes(written))
            assertEquals(listOf("id_bridge1"), allOf(written, Bridge::tryFrom).map { it.featureId().asStr() })
            assertEquals(listOf("id_road1"), allOf(written, Road::tryFrom).map { it.featureId().asStr() })
            assertEquals(relations(roadBridge), relations(written))
        }
    }

    @Nested
    inner class Versioning {
        @Test
        fun versioningCityModel() {
            assertEquals(4uL, versioning.cityObjectsLen())
            assertNull(versioning.boundedBy())
            val types = featureTypes(versioning)
            assertEquals(60, types.size)
            assertEquals(FeatureType.CityModel, types.first())
            assertEquals(
                mapOf(
                    FeatureType.CityModel to 1,
                    FeatureType.Building to 4,
                    FeatureType.BuildingPart to 5,
                    ROOF to 14,
                    WALL to 31,
                    GROUND to 5,
                ),
                types.groupingBy { it }.eachCount(),
            )
            assertEquals(59, versioning.iterCityObjects().asSequence().count())
        }

        @Test
        fun versioningBuildings() {
            data class Expected(val id: String, val name: String, val created: Triple<Int, UInt, UInt>, val terminated: Triple<Int, UInt, UInt>?, val parts: List<String>)
            val expected = listOf(
                Expected("BU_69381AL47_2000-01-01", "Building A", Triple(2000, 1u, 1u), Triple(2015, 1u, 1u), listOf("BU_69381AL47_1")),
                Expected("BU_69381AL49_2000-01-01", "Building B", Triple(2000, 1u, 1u), Triple(2015, 1u, 1u), listOf("BU_69381AL49_1_2000-01-01")),
                Expected("BU_69381AL49_2015-01-01", "Building B", Triple(2015, 1u, 1u), null, listOf("BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01")),
                Expected("BU_69381AL50_2015-01-01", "Building C", Triple(2015, 1u, 1u), null, listOf("BU_69381AL50_1")),
            )
            val buildings = allOf(versioning, Building::tryFrom)
            assertEquals(expected.size, buildings.size)
            buildings.zip(expected).forEach { (b, want) ->
                assertEquals(want.id, b.featureId().asStr())
                assertEquals(want.name, names(b.names()).first())
                assertEquals(want.created, date(b.creationDate()))
                assertEquals(want.terminated, date(b.terminationDate()))
                val parts = b.buildingParts().items()
                assertTrue(parts.all { it.href() == null })
                assertEquals(want.parts, parts.map { assertNotNull(it.object_()).featureId().asStr() })
                assertEquals(0, b.heights().asSequence().count())
                assertEquals(0, b.boundaries().asSequence().count())
            }
        }

        @Test
        fun versioningBuildingParts() {
            val expected = listOf(
                Triple("BU_69381AL47_1", 13.015, 8),
                Triple("BU_69381AL49_1_2000-01-01", 10.63, 9),
                Triple("BU_69381AL49_1_2015-01-01", 10.63, 9),
                Triple("BU_69381AL49_2_2015-01-01", 8.743, 7),
                Triple("BU_69381AL50_1", 18.215, 17),
            )
            val parts = allOf(versioning, BuildingPart::tryFrom)
            assertEquals(expected.size, parts.size)
            parts.zip(expected).forEach { (part, want) ->
                assertEquals(want.first, part.featureId().asStr())
                assertHeight(part.heights(), want.second)
                assertEquals(want.third, part.boundaries().asSequence().count())
                assertNull(part.creationDate())
                assertEquals(0, part.names().asSequence().count())
            }
        }

        @Test
        fun versioningRoundTrip() {
            val written = roundTrip(versioning)
            assertEquals(featureTypes(versioning), featureTypes(written))
            fun ids(model: CityModel) = allOf(model, Building::tryFrom).map { it.featureId().asStr() } +
                allOf(model, BuildingPart::tryFrom).map { it.featureId().asStr() }
            fun dates(model: CityModel) = allOf(model, Building::tryFrom).map { date(it.creationDate()) to date(it.terminationDate()) }
            assertEquals(ids(versioning), ids(written))
            assertEquals(dates(versioning), dates(written))
        }
    }
}
