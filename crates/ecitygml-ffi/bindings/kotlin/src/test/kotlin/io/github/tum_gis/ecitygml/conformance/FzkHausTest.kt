package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import org.junit.jupiter.api.Nested
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/fzk-haus.md.

private const val LOD1 = "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
private const val LOD2 = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
private const val LOD3 = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"

private val lod1 by lazy { read("fzk-haus", LOD1) }
private val lod2 by lazy { read("fzk-haus", LOD2) }
private val lod3 by lazy { read("fzk-haus", LOD3) }

private fun point(position: DirectPosition) = Triple(position.x(), position.y(), position.z())

private fun assertPointClose(actual: Triple<Double, Double, Double>, expected: Triple<Double, Double, Double>) {
    assertClose(actual.first, expected.first)
    assertClose(actual.second, expected.second)
    assertClose(actual.third, expected.third)
}

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun features(cityModel: CityModel): List<AbstractFeatureKindRef> = cityModel.iterFeatures().items()

private fun polygon(property: AbstractSurfaceProperty?): Polygon =
    assertNotNull(Polygon.tryFrom(assertNotNull(property?.object_())))

private fun walls(cityModel: CityModel): List<WallSurface> = features(cityModel).mapNotNull(WallSurface::tryFrom)

/** The lower corners of the city model's envelope and of the first wall surface's. */
private fun lowerCorners(cityModel: CityModel) = listOf(
    point(assertNotNull(cityModel.boundedBy()?.envelope()).lowerCorner()),
    point(assertNotNull(walls(cityModel).first().boundedBy()?.envelope()).lowerCorner()),
)

class FzkHausTest {
    @Nested
    inner class Lod1 {
        @Test
        fun lod1CityModel() {
            assertEquals(1uL, lod1.cityObjectsLen())
            val envelope = assertNotNull(lod1.boundedBy()?.envelope())
            val (lower, upper) = envelope.lowerCorner() to envelope.upperCorner()
            listOf(
                lower.x() to 457842.0, lower.y() to 5439083.0, lower.z() to 111.8,
                upper.x() to 457854.0, upper.y() to 5439093.0, upper.z() to 118.317669,
            ).forEach { (actual, expected) -> assertClose(actual, expected) }
        }

        @Test
        fun lod1BuildingAttributes() {
            val b = building(lod1)
            assertEquals("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", b.featureId().asStr())
            assertEquals(listOf("AC14-FZK-Haus"), b.names().asSequence().map { it!!.value() }.toList())
            assertEquals("1000", b.class_()?.value())
            assertEquals(listOf("1000"), b.functions().asSequence().map { it!!.value() }.toList())
            assertEquals(listOf("1000"), b.usages().asSequence().map { it!!.value() }.toList())
            assertEquals("1030", b.roofType()?.value())
            assertEquals(2L to 0L, b.storeysAboveGround() to b.storeysBelowGround())

            val date = assertNotNull(b.dateOfConstruction())
            assertEquals(Triple(2020, 1u, 1u), Triple(date.year(), date.month(), date.day()))
            assertNull(b.dateOfDemolition())
            val height = assertNotNull(b.heights().asSequence().single())
            assertEquals("topOfConstruction", height.highReference().value())
            assertEquals("lowestGroundPoint", height.lowReference().value())
            assertEquals(HeightStatusValue.Measured, height.status())
            assertClose(height.length().value(), 6.52)
            assertEquals("m", height.length().uom())
            assertEquals(0, b.occupancies().asSequence().count())
            assertEquals(0, b.buildingParts().asSequence().count())
        }

        @Test
        fun lod1Solid() {
            val b = building(lod1)
            val solid = assertNotNull(b.lod1Solid()?.object_())
            assertClose(solid.volume3d().getOrThrow(), 782.1228)
            val triangulation = solid.triangulate().getOrThrow()
            assertEquals(12, triangulation.surface().triangles().asSequence().count())
            assertFalse(triangulation.hasSkipped())
            assertEquals(0, b.boundaries().asSequence().count())
        }

        @Test
        fun lod1EnvelopeMeasures() {
            val envelope = assertNotNull(lod1.boundedBy()?.envelope())
            assertPointClose(Triple(envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()), Triple(12.0, 10.0, 6.517669))
            assertPointClose(point(envelope.center()), Triple(457848.0, 5439088.0, 115.0588345))
            assertClose(envelope.volume(), 782.12028)
            assertTrue(envelope.contains(envelope.lowerCorner()))
            assertTrue(envelope.contains(envelope.upperCorner()))
            fun at(x: Double, y: Double, z: Double) = DirectPosition.create(x, y, z).getOrThrow()
            assertTrue(envelope.contains(at(457848.0, 5439088.0, 115.0)))
            assertFalse(envelope.contains(at(457848.0, 5439088.0, 118.4)))
            assertFalse(envelope.contains(at(457841.9, 5439088.0, 115.0)))
            assertNull(lod1.creationDate())
        }

        @Test
        fun lod1BuildingDetails() {
            assertEquals(1, features(lod1).count { it.featureType() == FeatureType.Building })
            val b = building(lod1)
            assertEquals("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", b.id()?.asStr())
            val envelope = assertNotNull(b.boundedBy()?.envelope())
            assertPointClose(point(envelope.lowerCorner()), Triple(457842.0, 5439083.0, 111.8))
            assertPointClose(point(envelope.upperCorner()), Triple(457854.0, 5439093.0, 118.31769))
            assertNull(b.lod2Solid())
            assertNull(b.lod0MultiSurface())
        }

        @Test
        fun lod1SolidStructure() {
            val solid = assertNotNull(building(lod1).lod1Solid()?.object_())
            assertEquals(0, solid.interior().asSequence().count())
            assertEquals(24, solid.points().asSequence().count())
            val shell = assertNotNull(solid.exterior())
            assertClose(shell.volume3d().getOrThrow(), 782.1228)
            val members = shell.members().items()
            assertEquals(6, members.size)
            assertTrue(members.all { it.href() == null })
            val polygons = members.map(::polygon)
            assertTrue(polygons.all { it.interior().asSequence().none() })
            val rings = polygons.map { assertNotNull(LinearRing.tryFrom(assertNotNull(it.exterior()))) }
            assertEquals(List(6) { 4 }, rings.map { it.points().asSequence().count() })
            assertTrue(rings.all { it.area3d() > 0.0 })
            assertPointClose(point(rings[0].points().items().first()), Triple(457842.0, 5439083.0, 111.8))
            assertClose(rings[0].length3d(), 44.0)
            assertClose(rings[0].area3d(), 120.0)
        }

        @Test
        fun lod1SolidTriangulation() {
            val solid = assertNotNull(building(lod1).lod1Solid()?.object_())
            val triangulation = solid.triangulate().getOrThrow()
            assertEquals(0, triangulation.skipped().asSequence().count())
            val surface = triangulation.surface()
            assertClose(surface.area3d().getOrThrow(), 526.77836)
            assertEquals(36, surface.points().asSequence().count())
            val triangle = surface.triangles().items().first()
            assertClose(triangle.a().z(), 111.8)
            assertClose(triangle.area(), 60.0)
            val shell = assertNotNull(solid.exterior())
            assertEquals(12, shell.triangulate().getOrThrow().surface().triangles().asSequence().count())
            val first = polygon(shell.members().items().first())
            assertEquals(2, first.triangulate().getOrThrow().surface().triangles().asSequence().count())
        }

        @Test
        fun lod1ApplyScale() {
            val cityModel = read("fzk-haus", LOD1)
            cityModel.applyScale(Scale3(2.0, 3.0, 0.5))
            val envelope = assertNotNull(cityModel.boundedBy()?.envelope())
            assertPointClose(Triple(envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()), Triple(24.0, 30.0, 3.2588345))
        }
    }

    @Nested
    inner class Lod2 {
        @Test
        fun lod2BoundarySurfaces() {
            val features = boundaries(building(lod2))
            assertEquals(
                listOf(
                    FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.RoofSurface,
                    FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ),
                features.map { it.featureType() },
            )
            assertEquals(
                listOf("Outer Wall 1 (West)", "Outer Wall 2 (South)", "Outer Wall 3 (East)", "Outer Wall 4 (North)"),
                features.mapNotNull(WallSurface::tryFrom).map { firstName(it.names()) },
            )
            assertEquals(
                listOf("Roof 1 (North)", "Roof 2 (South)"),
                features.mapNotNull(RoofSurface::tryFrom).map { firstName(it.names()) },
            )
            assertEquals(listOf("Base Surface"), features.mapNotNull(GroundSurface::tryFrom).map { firstName(it.names()) })
        }

        @Test
        fun lod2SurfaceAreas() {
            val features = boundaries(building(lod2))
            fun area(multiSurfaces: List<MultiSurfaceProperty?>): Double =
                multiSurfaces.sumOf { assertNotNull(it?.object_()).area3d().getOrThrow() }
            assertClose(area(features.mapNotNull(WallSurface::tryFrom).map { it.lod2MultiSurface() }), 188.62887820601463)
            assertClose(area(features.mapNotNull(RoofSurface::tryFrom).map { it.lod2MultiSurface() }), 138.56406460961398)
            assertClose(area(features.mapNotNull(GroundSurface::tryFrom).map { it.lod2MultiSurface() }), 120.0)
        }

        @Test
        fun lod2GenericAttributes() {
            val b = building(lod2)
            val attributes = b.genericAttributes().asSequence().map { it!! }.toList()
            assertEquals(3, attributes.size)
            val (area, method, landmarked) = attributes
            val measure = assertNotNull(MeasureAttribute.tryFrom(area))
            assertEquals("GrossPlannedArea", area.name())
            assertClose(measure.value().value(), 120.0)
            assertEquals("m2", measure.value().uom())
            assertEquals("ConstructionMethod" to "New Building", method.name() to method.asString()?.value())
            assertEquals("IsLandmarked" to "NO", landmarked.name() to landmarked.asString()?.value())
            assertEquals(0, b.externalReferences().asSequence().count())
        }

        @Test
        fun lod2SolidUnresolved() {
            val solid = assertNotNull(building(lod2).lod2Solid()?.object_())
            assertTrue(solid.volume3d().isFailure)
        }

        @Test
        fun lod2BuildingDetails() {
            val b = building(lod2)
            assertEquals(RelativeToTerrain.EntirelyAboveTerrain, b.relativeToTerrain())
            assertNull(b.relativeToWater())
            val created = assertNotNull(b.creationDate())
            assertEquals(listOf(2017, 1, 23, 0), listOf(created.year(), created.month().toInt(), created.day().toInt(), created.hour().toInt()))
            assertEquals(3600, created.offsetSeconds())
            assertEquals(1485126000L, created.timestamp())
            assertNull(b.terminationDate())
            assertNull(b.validFrom())
            assertNull(b.validTo())

            assertEquals("1000", b.class_()?.value())
            assertEquals(listOf("1000"), b.functions().items().map { it.value() })
            assertEquals(listOf("1000"), b.usages().items().map { it.value() })
            assertEquals("1030", b.roofType()?.value())
            assertEquals(2L to 0L, b.storeysAboveGround() to b.storeysBelowGround())
            val date = assertNotNull(b.dateOfConstruction())
            assertEquals(Triple(2020, 1u, 1u), Triple(date.year(), date.month(), date.day()))
            assertNull(b.dateOfDemolition())
            val height = b.heights().items().single()
            assertEquals("topOfConstruction", height.highReference().value())
            assertEquals("lowestGroundPoint", height.lowReference().value())
            assertEquals(HeightStatusValue.Measured, height.status())
            assertClose(height.length().value(), 6.52)
            assertEquals("m", height.length().uom())

            assertEquals(0, b.occupancies().asSequence().count())
            assertEquals(0, b.relatedTo().asSequence().count())
            assertNull(b.lod1Solid())
            assertNull(b.boundedBy())
            assertNull(b.lod1TerrainIntersectionCurve())
            assertNull(b.lod2TerrainIntersectionCurve())
            assertNull(b.lod3TerrainIntersectionCurve())
            assertNull(b.lod1ImplicitRepresentation())
            assertNull(b.lod2ImplicitRepresentation())
            assertNull(b.lod3ImplicitRepresentation())
        }

        @Test
        fun lod2BoundaryIds() {
            val properties = building(lod2).boundaries().items()
            assertTrue(properties.all { it.href() == null })
            assertEquals(
                listOf(
                    "GML_5856d7ad-5e34-498a-817b-9544bfbb1475",
                    "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
                    "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069",
                    "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
                    "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc",
                    "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
                    "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
                ),
                properties.map { assertNotNull(it.object_()).featureId().asStr() },
            )
        }

        @Test
        fun lod2WallSurface() {
            val features = boundaries(building(lod2))
            val wallSurfaces = features.mapNotNull(WallSurface::tryFrom)
            val wall = wallSurfaces.first()
            assertEquals("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", wall.id()?.asStr())
            assertNull(wall.lod0MultiCurve())
            assertNull(wall.lod0MultiSurface())
            assertNull(wall.lod1MultiSurface())
            assertNull(wall.relativeToTerrain())
            assertNull(wall.creationDate())
            assertEquals(0, wall.genericAttributes().asSequence().count())
            assertNotNull(wall.boundedBy())
            val multiSurface = assertNotNull(wall.lod2MultiSurface()?.object_())
            assertEquals(1, multiSurface.surfaceMember().asSequence().count())
            assertEquals(3, multiSurface.triangulate().getOrThrow().surface().triangles().asSequence().count())
            assertTrue(wallSurfaces.all { it.fillingSurfaces().asSequence().none() })
            val ground = features.firstNotNullOf(GroundSurface::tryFrom)
            val member = assertNotNull(ground.lod2MultiSurface()?.object_()).surfaceMember().items().first()
            assertEquals(4, assertNotNull(polygon(member).exterior()).points().asSequence().count())
        }

        @Test
        fun lod2GenericAttributeKinds() {
            val (area, method, landmarked) = building(lod2).genericAttributes().items()
            assertNull(area.asString())
            assertNull(MeasureAttribute.tryFrom(method))
            assertNull(MeasureAttribute.tryFrom(landmarked))
        }

        @Test
        fun lod2CityObjects() {
            assertEquals(
                listOf(
                    FeatureType.Building, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface,
                    FeatureType.RoofSurface, FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ),
                lod2.iterCityObjects().items().map { it.featureType() },
            )
            val types = features(lod2).map { it.featureType() }
            assertEquals(FeatureType.CityModel, types.first())
            assertEquals(1, types.count { it == FeatureType.CityModel })
        }

        @Test
        fun lod2ObjectBounds() {
            val reader = GmlReader.fromPath("${System.getProperty("ecitygml.fixtures")}/fzk-haus/$LOD2").getOrThrow()
            reader.withRebuildObjectBounds(false)
            val cityModel = reader.finish().getOrThrow()
            assertEquals(List(4) { false }, walls(cityModel).map { it.boundedBy() != null })
            cityModel.recomputeChildBoundingShapes()
            assertEquals(List(4) { true }, walls(cityModel).map { it.boundedBy() != null })
        }

        @Test
        fun lod2ApplyTranslation() {
            val cityModel = read("fzk-haus", LOD2)
            lowerCorners(cityModel).forEach { assertPointClose(it, Triple(457842.0, 5439083.0, 111.8)) }
            cityModel.applyTranslation(Vector3(-100.0, 200.0, 10.0))
            lowerCorners(cityModel).forEach { assertPointClose(it, Triple(457742.0, 5439283.0, 121.8)) }
        }
    }

    @Nested
    inner class Lod3 {
        @Test
        fun lod3DoorsAndWindows() {
            val features = lod3.iterFeatures().asSequence().filterNotNull().toList()
            val doors = features.mapNotNull(DoorSurface::tryFrom)
            assertEquals(listOf("Door West", "Door South"), doors.map { firstName(it.names()) })
            assertClose(doors.sumOf { assertNotNull(it.lod3MultiSurface()?.object_()).area3d().getOrThrow() }, 6.803850099444389)
            assertEquals(11, features.mapNotNull(WindowSurface::tryFrom).size)
        }

        @Test
        fun lod3WestWallFillings() {
            val wall = assertNotNull(WallSurface.tryFrom(boundaries(building(lod3)).first()))
            assertEquals("Outer Wall 1 (West)", firstName(wall.names()))
            val fillings = wall.fillingSurfaces().asSequence().map { assertNotNull(it?.object_()) }.toList()
            assertEquals(
                listOf(
                    FeatureType.WindowSurface to "Window Round",
                    FeatureType.WindowSurface to "Window North",
                    FeatureType.DoorSurface to "Door West",
                    FeatureType.WindowSurface to "Window South",
                ),
                fillings.map { it.featureType() to firstName(it.names()) },
            )
        }

        @Test
        fun lod3BuildingDetails() {
            assertEquals(1uL, lod3.cityObjectsLen())
            val b = building(lod3)
            assertEquals(RelativeToTerrain.EntirelyAboveTerrain, b.relativeToTerrain())
            val features = boundaries(b)
            assertEquals(
                listOf(
                    FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.WallSurface, FeatureType.RoofSurface,
                    FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface,
                ),
                features.map { it.featureType() },
            )
            assertTrue(features.mapNotNull(WallSurface::tryFrom).all { it.lod3MultiSurface() != null })
        }

        @Test
        fun lod3Fillings() {
            val features = boundaries(building(lod3))
            val perWall = features.mapNotNull(WallSurface::tryFrom).map { it.fillingSurfaces().items() }
            assertEquals(listOf(4, 3, 3, 3), perWall.map { it.size })
            val properties = perWall.flatten()
            assertTrue(properties.all { it.href() == null })
            val fillings = properties.map { assertNotNull(it.object_()) }
            val types = fillings.map { it.featureType() }
            assertEquals(2 to 11, types.count { it == FeatureType.DoorSurface } to types.count { it == FeatureType.WindowSurface })
            assertTrue(fillings.all { assertNotNull(it.lod3MultiSurface()?.object_()).area3d().getOrThrow() > 0.0 })
            assertTrue(features.mapNotNull(RoofSurface::tryFrom).all { it.fillingSurfaces().asSequence().none() })

            val all = features(lod3)
            val windows = all.mapNotNull(WindowSurface::tryFrom)
            assertClose(windows.sumOf { assertNotNull(it.lod3MultiSurface()?.object_()).area3d().getOrThrow() }, 23.168802611529827)
            val doors = all.mapNotNull(DoorSurface::tryFrom)
            assertEquals(
                listOf("GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd", "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629"),
                doors.map { it.featureId().asStr() },
            )
            assertTrue(doors.all { it.lod2MultiSurface() == null })
        }

        @Test
        fun lod3CityObjects() {
            val objects = lod3.iterCityObjects().items().map { it.featureType() }
            assertEquals(21, objects.size)
            assertEquals(
                listOf(1, 4, 2, 1, 2, 11),
                listOf(
                    FeatureType.Building, FeatureType.WallSurface, FeatureType.RoofSurface,
                    FeatureType.GroundSurface, FeatureType.DoorSurface, FeatureType.WindowSurface,
                ).map { type -> objects.count { it == type } },
            )
            val types = features(lod3).map { it.featureType() }
            assertEquals(22, types.size)
            assertEquals(FeatureType.CityModel, types.first())
        }

        @Test
        fun lod3CompositeSurface() {
            val wall = assertNotNull(WallSurface.tryFrom(boundaries(building(lod3)).first()))
            val member = assertNotNull(wall.lod3MultiSurface()?.object_()).surfaceMember().items().first()
            val composite = assertNotNull(CompositeSurface.tryFrom(assertNotNull(member.object_())))
            val members = composite.surfaceMember().items()
            assertEquals(85, members.size)
            val start = assertNotNull(polygon(members.first()).exterior()).points().items().first()
            assertPointClose(point(start), Triple(457842.0, 5439088.49240388, 115.913175911167))
        }

        @Test
        fun lod3RoundTrip() {
            val writer = GmlWriter.create(CitygmlFormat.Gml)
            writer.finish(lod3).getOrThrow()
            val written = GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
            assertEquals(features(lod3).map { it.featureType() }, features(written).map { it.featureType() })
            assertEquals("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82", building(written).featureId().asStr())
            // The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
            fun surfaceIds(model: CityModel): List<String> =
                building(model).boundaries().items().map { assertNotNull(it.object_()).featureId().asStr() } +
                    boundaries(building(model)).mapNotNull(WallSurface::tryFrom)
                        .flatMap { wall -> wall.fillingSurfaces().items().map { assertNotNull(it.object_()).featureId().asStr() } }
            assertEquals(surfaceIds(lod3), surfaceIds(written))
            val height = building(written).heights().items().single()
            assertEquals("topOfConstruction", height.highReference().value())
            assertEquals("lowestGroundPoint", height.lowReference().value())
            assertEquals(HeightStatusValue.Measured, height.status())
            assertClose(height.length().value(), 6.52)
            assertEquals("m", height.length().uom())
        }
    }
}
