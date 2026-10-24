package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import org.junit.jupiter.api.Nested
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.

private val roadShape by lazy { read("asam-opendrive", "ASAM-UC_RoadShape.gml") }
private val junction by lazy { read("asam-opendrive", "ASAM-Ex_Bidirectional_Junction.gml") }

private val SPACES = listOf(
    "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
    "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
    "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c",
    "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
    "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13",
    "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
    "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
)

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun road(cityModel: CityModel): Road =
    assertNotNull(cityModel.iterFeatures().items().firstNotNullOfOrNull(Road::tryFrom))

/** The objects of inline properties; fails on a reference-only property. */
private fun <P, T> objects(properties: Iterator<P?>, href: (P) -> HRef?, obj: (P) -> T?): List<T> =
    properties.items().map {
        assertNull(href(it))
        assertNotNull(obj(it))
    }

private fun sections(road: Road) = objects(road.sections(), { it.href() }, { it.object_() })
private fun trafficSpaces(space: Iterator<TrafficSpaceProperty?>) = objects(space, { it.href() }, { it.object_() })
private fun auxiliarySpaces(space: Iterator<AuxiliaryTrafficSpaceProperty?>) = objects(space, { it.href() }, { it.object_() })
private fun surfaceMembers(members: Iterator<AbstractSurfaceProperty?>) = objects(members, { it.href() }, { it.object_() })

private fun assertPointClose(position: DirectPosition, expected: Triple<Double, Double, Double>) {
    assertClose(position.x(), expected.first)
    assertClose(position.y(), expected.second)
    assertClose(position.z(), expected.third)
}

private fun assertEnvelope(cityModel: CityModel, lower: Triple<Double, Double, Double>, upper: Triple<Double, Double, Double>) {
    val envelope = assertNotNull(cityModel.boundedBy()?.envelope())
    assertPointClose(envelope.lowerCorner(), lower)
    assertPointClose(envelope.upperCorner(), upper)
}

/** The single boundary of a space, inline, as a feature. */
private fun onlyBoundary(boundaries: Iterator<AbstractSpaceBoundaryProperty?>): AbstractFeatureKindRef {
    val all = objects(boundaries, { it.href() }, { it.object_() })
    assertEquals(1, all.size)
    return AbstractFeatureKindRef.fromSpaceBoundary(all.single())
}

/** The single curve member of an inline multi curve, as a line string: (point count, length). */
private fun lineString(multiCurve: MultiCurve): Pair<Int, Double> {
    val members = objects(multiCurve.curveMember(), { it.href() }, { it.object_() })
    assertEquals(1, members.size)
    val curve = assertNotNull(LineString.tryFrom(members.single()))
    return curve.points().asSequence().count() to curve.length3d()
}

private fun localIds(references: Iterator<TrafficSpaceReference?>): List<String> =
    references.items().map { assertNotNull(Reference.fromTrafficSpaceReference(it).href()?.localId()) }

class AsamOpendriveTest {
    @Nested
    inner class RoadShape {
        private fun section(): Section = sections(road(roadShape)).single()
        private fun spaces(): List<TrafficSpace> = trafficSpaces(section().trafficSpaces())

        @Test
        fun roadShapeCityModel() {
            assertEquals(1uL, roadShape.cityObjectsLen())
            val types = listOf(
                FeatureType.CityModel, FeatureType.Road, FeatureType.Section,
                FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                FeatureType.AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficArea,
                FeatureType.AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficArea,
            )
            assertEquals(types, roadShape.iterFeatures().items().map { it.featureType() })
            assertEquals(types.drop(1), roadShape.iterCityObjects().items().map { it.featureType() })
            assertEnvelope(
                roadShape,
                Triple(-50.21567184593757, -2.4442507170297514, 0.0),
                Triple(-13.007511850967884, 29.053746110395082, 4.95),
            )
        }

        @Test
        fun roadShapeRoad() {
            val road = road(roadShape)
            assertEquals("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", road.featureId().asStr())
            assertNull(road.class_())
            assertNull(road.trafficDirection())
            listOf(
                road.functions(), road.usages(), road.intersections(), road.occupancies(), road.trafficSpaces(),
                road.auxiliaryTrafficSpaces(), road.markings(), road.holes(),
            ).forEach { assertTrue(!it.hasNext()) }
            assertEquals("UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29", section().featureId().asStr())
        }

        @Test
        fun roadShapeSection() {
            val section = section()
            assertNull(section.class_())
            assertNull(section.trafficDirection())
            assertNull(section.lod0MultiCurve())
            assertNull(section.lod1Solid())
            assertTrue(!section.markings().hasNext())
            assertTrue(!section.holes().hasNext())
            assertEquals(
                listOf("UUID_ae81947d-a661-3678-a5ee-eed58b68694f", "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421"),
                trafficSpaces(section.trafficSpaces()).map { it.featureId().asStr() },
            )
            assertEquals(
                listOf("UUID_12298df9-4982-33a8-ab4a-9953410bbff7", "UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578"),
                auxiliarySpaces(section.auxiliaryTrafficSpaces()).map { it.featureId().asStr() },
            )
        }

        @Test
        fun roadShapeTrafficSpaces() {
            val spaces = spaces()
            assertEquals(
                listOf(TrafficDirectionValue.Backwards, TrafficDirectionValue.Forwards),
                spaces.map { it.trafficDirection() },
            )
            for (space in spaces) {
                assertEquals(GranularityValue.Lane, space.granularity())
                assertNull(space.class_())
                assertEquals(listOf("1"), space.functions().items().map { it.value() })
                assertEquals(listOf("2"), space.usages().items().map { it.value() })
                assertTrue(!space.occupancies().hasNext())
                assertEquals(SpaceType.Open, space.spaceType())
                assertNull(space.relativeToTerrain())
                assertNull(space.creationDate())
                assertTrue(!space.predecessors().hasNext())
                assertTrue(!space.successors().hasNext())
                assertNotNull(TrafficArea.tryFrom(onlyBoundary(space.boundaries())))
            }
        }

        @Test
        fun roadShapeGenericAttributes() {
            val attributes = spaces()[0].genericAttributes().items().map { a ->
                val int = a.asInt()
                val double = a.asDouble()
                when {
                    int != null -> Triple(a.name(), "int", int.value())
                    double != null -> Triple(a.name(), "double", double.value())
                    else -> Triple(a.name(), "string", a.asString()?.value())
                }
            }
            assertEquals(
                listOf(
                    Triple("identifier_laneId", "int", 1L),
                    Triple("identifier_laneSectionId", "int", 0L),
                    Triple("identifier_roadId", "string", "1"),
                    Triple("opendrive_road_length", "double", 40.0),
                    Triple("opendrive_road_rule", "string", "RIGHT_HAND_TRAFFIC"),
                    Triple("opendrive_laneSection_curvePositionStart", "double", 0.0),
                    Triple("opendrive_lane_type", "string", "DRIVING"),
                    Triple("opendrive_lane_level", "string", "false"),
                ),
                attributes,
            )
        }

        @Test
        fun roadShapeTrafficSpaceGeometry() {
            val spaces = spaces()
            val volumes = spaces.map { assertNotNull(it.lod2Solid()?.object_()).volume3d().getOrThrow() }
            assertClose(volumes[0], 720.0)
            assertClose(volumes[1], 540.0)
            for (space in spaces) {
                val property = assertNotNull(space.lod2MultiCurve())
                assertNull(property.href())
                val multiCurve = assertNotNull(property.object_())
                assertClose(multiCurve.length3d().getOrThrow(), 40.0)
                val (points, length) = lineString(multiCurve)
                assertEquals(2, points)
                assertClose(length, 40.0)
                assertNull(space.lod0MultiCurve())
                assertNull(space.lod3MultiCurve())
                assertNull(space.lod1Solid())
                assertNull(space.lod3Solid())
                assertNull(space.lod2MultiSurface())
            }
        }

        @Test
        fun roadShapeTrafficAreas() {
            val areas = spaces().map { assertNotNull(TrafficArea.tryFrom(onlyBoundary(it.boundaries()))) }
            assertEquals(
                listOf("UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2", "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a"),
                areas.map { it.featureId().asStr() },
            )
            val area3d = areas.map { area ->
                assertEquals("Lane", firstName(area.names()))
                assertNull(area.class_())
                assertEquals(listOf("1"), area.functions().items().map { it.value() })
                assertEquals(listOf("2"), area.usages().items().map { it.value() })
                assertNull(area.surfaceMaterial())
                assertNull(area.lod0MultiCurve())
                assertNull(area.lod0MultiSurface())
                assertNull(area.lod1MultiSurface())
                assertNull(area.lod3MultiSurface())
                assertNull(area.relativeToTerrain())
                val multiSurface = assertNotNull(area.lod2MultiSurface()?.object_())
                assertEquals(1, surfaceMembers(multiSurface.surfaceMember()).size)
                multiSurface.area3d().getOrThrow()
            }
            assertClose(area3d[0], 160.79800993793438)
            assertClose(area3d[1], 121.34249049694012)
        }

        @Test
        fun roadShapeAuxiliaryTraffic() {
            val spaces = auxiliarySpaces(section().auxiliaryTrafficSpaces())
            for (space in spaces) {
                assertEquals(GranularityValue.Lane, space.granularity())
                assertNull(space.class_())
                assertTrue(!space.functions().hasNext())
                assertTrue(!space.usages().hasNext())
                assertEquals(SpaceType.Open, space.spaceType())
                assertClose(assertNotNull(space.lod2Solid()?.object_()).volume3d().getOrThrow(), 100.0)
                assertClose(assertNotNull(space.lod2MultiCurve()?.object_()).length3d().getOrThrow(), 40.0)
            }
            val areas = spaces.map { assertNotNull(AuxiliaryTrafficArea.tryFrom(onlyBoundary(it.boundaries()))) }
            assertEquals(
                listOf("UUID_4890681a-e9fa-365e-a676-f89afb453f9b", "UUID_d3c71d48-5222-355e-8037-9677aee30d7e"),
                areas.map { it.featureId().asStr() },
            )
            for (area in areas) {
                assertEquals("Lane", firstName(area.names()))
                assertNull(area.class_())
                assertTrue(!area.functions().hasNext())
                assertTrue(!area.usages().hasNext())
                assertNull(area.surfaceMaterial())
                assertClose(assertNotNull(area.lod2MultiSurface()?.object_()).area3d().getOrThrow(), 40.0)
            }
        }
    }

    @Nested
    inner class Junction {
        private fun spaces(): List<TrafficSpace> = junction.iterFeatures().items().mapNotNull(TrafficSpace::tryFrom)

        @Test
        fun junctionCityModel() {
            assertEquals(1uL, junction.cityObjectsLen())
            assertEquals(
                listOf(
                    FeatureType.CityModel, FeatureType.Road, FeatureType.Section, FeatureType.TrafficSpace,
                    FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.Marking,
                    FeatureType.Marking, FeatureType.Marking, FeatureType.Marking, FeatureType.Section,
                    FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.Section, FeatureType.TrafficSpace,
                    FeatureType.TrafficArea, FeatureType.Intersection, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                    FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                ),
                junction.iterFeatures().items().map { it.featureType() },
            )
            assertEquals(23, junction.iterCityObjects().items().size)
            assertEnvelope(
                junction,
                Triple(-52.66282419815818, -37.4146115571896, 0.0),
                Triple(34.10760429351533, 6.338805461729647, 0.0),
            )
        }

        @Test
        fun junctionRoad() {
            val road = road(junction)
            assertEquals("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", road.featureId().asStr())
            val sections = sections(road)
            assertEquals(
                listOf(
                    "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
                    "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                    "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d",
                ),
                sections.map { it.featureId().asStr() },
            )
            assertEquals(listOf(2, 1, 1), sections.map { it.trafficSpaces().asSequence().count() })
            assertEquals(listOf(4, 0, 0), sections.map { it.markings().asSequence().count() })
            assertTrue(sections.all { !it.auxiliaryTrafficSpaces().hasNext() })
            val intersection = objects(road.intersections(), { it.href() }, { it.object_() }).single()
            assertEquals("UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571", intersection.featureId().asStr())
            assertNull(intersection.class_())
            assertEquals(SPACES.drop(4), trafficSpaces(intersection.trafficSpaces()).map { it.featureId().asStr() })
        }

        @Test
        fun junctionTrafficSpaces() {
            val spaces = spaces()
            assertEquals(SPACES, spaces.map { it.featureId().asStr() })
            assertEquals(
                listOf(TrafficDirectionValue.Backwards) + List(6) { TrafficDirectionValue.Forwards },
                spaces.map { it.trafficDirection() },
            )
            assertTrue(spaces.all { it.lod2Solid() == null })
            val curves = spaces.map { lineString(assertNotNull(it.lod2MultiCurve()?.object_())) }
            assertEquals(listOf(9, 9, 5, 6, 7, 8, 7), curves.map { it.first })
            listOf(
                36.74683751297985, 36.74683751297985, 20.0, 21.746217945006258, 26.761532846607814,
                30.210435770102656, 30.0,
            ).zip(curves).forEach { (expected, curve) -> assertClose(curve.second, expected) }
        }

        @Test
        fun junctionTrafficAreas() {
            val surfaces = junction.iterFeatures().items().mapNotNull(TrafficArea::tryFrom)
                .map { assertNotNull(it.lod2MultiSurface()?.object_()) }
            assertEquals(listOf(8, 8, 4, 5, 6, 7, 6), surfaces.map { surfaceMembers(it.surfaceMember()).size })
            listOf(
                112.81279116484816, 112.81279116484816, 61.4, 66.76088909116919, 81.22157625123039,
                92.69041581703632, 92.1,
            ).zip(surfaces).forEach { (expected, surface) -> assertClose(surface.area3d().getOrThrow(), expected) }
        }

        @Test
        fun junctionTrafficSpaceLinks() {
            val (s0, s1, s2, s3, s4) = SPACES
            val (s5, s6) = SPACES.drop(5)
            assertEquals(
                listOf(
                    listOf<String>() to listOf<String>(),
                    listOf<String>() to listOf(s6),
                    listOf(s4, s5) to listOf(),
                    listOf<String>() to listOf(s4),
                    listOf(s3) to listOf(s2),
                    listOf("UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f") to listOf(s0),
                    listOf(s1) to listOf(s2),
                ),
                spaces().map { localIds(it.predecessors()) to localIds(it.successors()) },
            )
        }

        @Test
        fun junctionMarkings() {
            val section = sections(road(junction)).first()
            val markings = objects(section.markings(), { it.href() }, { it.object_() })
            val areas = markings.map { marking ->
                assertEquals("RoadMarking", firstName(marking.names()))
                assertNull(marking.class_())
                assertNull(marking.lod0MultiSurface())
                assertNull(marking.lod3MultiSurface())
                val multiSurface = assertNotNull(marking.lod2MultiSurface()?.object_())
                assertEquals(1, surfaceMembers(multiSurface.surfaceMember()).size)
                multiSurface.area3d().getOrThrow()
            }
            assertEquals(4, areas.size)
            listOf(0.48, 0.48, 0.48, 0.08962050155758661).zip(areas)
                .forEach { (expected, actual) -> assertClose(actual, expected) }
        }
    }
}
