@file:OptIn(ExperimentalUnsignedTypes::class)

package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import org.junit.jupiter.api.Nested
import kotlin.math.sqrt
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertIs
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/synthetic.md. `bridge_is_movable` is scoped out: `is_movable` isn't
// bound in Kotlin.

private const val DATASET = "synthetic"

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun featureTypes(cityModel: CityModel): List<FeatureType> = cityModel.iterFeatures().items().map { it.featureType() }

private fun <T : Any> allOf(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): List<T> =
    cityModel.iterFeatures().items().mapNotNull(tryFrom)

private fun <T : Any> only(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): T = allOf(cityModel, tryFrom).single()

private fun ymd(date: Date?): List<Int> = assertNotNull(date).let { listOf(it.year(), it.month().toInt(), it.day().toInt()) }

private fun roundTrip(cityModel: CityModel): Pair<CityModel, String> {
    val writer = GmlWriter.create(CitygmlFormat.Gml)
    writer.finish(cityModel).getOrThrow()
    val data = writer.data()
    return GmlReader.create(data, CitygmlFormat.Gml).finish().getOrThrow() to data.toByteArray().decodeToString()
}

private fun implicit(property: ImplicitGeometryProperty?): ImplicitGeometry {
    assertNotNull(property)
    assertNull(property.href())
    return assertNotNull(property.object_())
}

private fun roof(property: AbstractSpaceBoundaryProperty): RoofSurface {
    assertNull(property.href())
    return assertNotNull(RoofSurface.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(assertNotNull(property.object_()))))
}

private fun attributeSet(building: Building): GenericAttributeSet =
    assertNotNull(GenericAttributeSet.tryFrom(building.genericAttributes().items().single()))

class SyntheticTest {
    @Nested
    inner class BridgeFile {
        private val cityModel = read(DATASET, "bridge.gml")

        private fun part(bridge: Bridge): BridgePart {
            val property = bridge.bridgeParts().items().single()
            assertNull(property.href())
            return assertNotNull(property.object_())
        }

        @Test
        fun bridgeCityModel() {
            assertEquals(1uL, cityModel.cityObjectsLen())
            assertEquals(listOf(FeatureType.CityModel, FeatureType.Bridge, FeatureType.BridgePart), featureTypes(cityModel))
            assertEquals(listOf(FeatureType.Bridge, FeatureType.BridgePart), cityModel.iterCityObjects().items().map { it.featureType() })
        }

        @Test
        fun bridgeAttributes() {
            val bridge = only(cityModel, Bridge::tryFrom)
            assertEquals("bridge_1", bridge.featureId().asStr())
            assertEquals(listOf("Synthetic bridge"), bridge.names().items().map { it.value() })
            assertEquals("1000", bridge.class_()?.value())
            assertEquals(listOf("1010", "1020"), bridge.functions().items().map { it.value() })
            assertEquals(listOf("1000"), bridge.usages().items().map { it.value() })
            assertEquals(listOf(1990, 5, 1), ymd(bridge.dateOfConstruction()))
            assertTrue(bridge.heights().items().isEmpty())
            val bridgePart = part(bridge)
            assertEquals("bridge_part_1", bridgePart.featureId().asStr())
            assertNull(bridgePart.class_())
            assertTrue(bridgePart.functions().items().isEmpty())
            assertEquals("bridge_part_1", only(cityModel, BridgePart::tryFrom).featureId().asStr())
        }

        @Test
        fun bridgeCodeSpaces() {
            val bridge = only(cityModel, Bridge::tryFrom)
            assertEquals("https://example.org/bridge_class", bridge.class_()?.code()?.codeSpace())
            assertTrue(bridge.functions().items().all { it.code().codeSpace() == null })
        }

        @Test
        fun bridgeRoundTrip() {
            val (written, _) = roundTrip(cityModel)
            assertEquals(featureTypes(cityModel), featureTypes(written))
            val bridge = only(written, Bridge::tryFrom)
            assertEquals("1000", bridge.class_()?.value())
            assertEquals(listOf("1010", "1020"), bridge.functions().items().map { it.value() })
            assertEquals(listOf(1990, 5, 1), ymd(bridge.dateOfConstruction()))
            assertEquals("bridge_part_1", part(bridge).featureId().asStr())
        }
    }

    @Nested
    inner class TunnelFile {
        private val cityModel = read(DATASET, "tunnel.gml")

        private fun part(tunnel: Tunnel): TunnelPart {
            val property = tunnel.tunnelParts().items().single()
            assertNull(property.href())
            return assertNotNull(property.object_())
        }

        @Test
        fun tunnelCityModel() {
            assertEquals(1uL, cityModel.cityObjectsLen())
            assertEquals(listOf(FeatureType.CityModel, FeatureType.Tunnel, FeatureType.TunnelPart), featureTypes(cityModel))
            assertEquals(listOf(FeatureType.Tunnel, FeatureType.TunnelPart), cityModel.iterCityObjects().items().map { it.featureType() })
        }

        @Test
        fun tunnelAttributes() {
            val tunnel = only(cityModel, Tunnel::tryFrom)
            assertEquals("tunnel_1", tunnel.featureId().asStr())
            assertEquals(listOf("Synthetic tunnel"), tunnel.names().items().map { it.value() })
            assertEquals("1000", tunnel.class_()?.value())
            assertEquals(listOf("1010", "1020"), tunnel.functions().items().map { it.value() })
            assertEquals(listOf("1000"), tunnel.usages().items().map { it.value() })
            assertEquals(listOf(1990, 5, 1), ymd(tunnel.dateOfConstruction()))
            assertTrue(tunnel.heights().items().isEmpty())
            val tunnelPart = part(tunnel)
            assertEquals("tunnel_part_1", tunnelPart.featureId().asStr())
            assertNull(tunnelPart.class_())
            assertEquals(listOf("1030"), tunnelPart.functions().items().map { it.value() })
            assertEquals("tunnel_part_1", only(cityModel, TunnelPart::tryFrom).featureId().asStr())
        }

        @Test
        fun tunnelCodeSpaces() {
            val tunnel = only(cityModel, Tunnel::tryFrom)
            assertEquals("https://example.org/tunnel_class", tunnel.class_()?.code()?.codeSpace())
            assertTrue(tunnel.functions().items().all { it.code().codeSpace() == null })
        }

        @Test
        fun tunnelRoundTrip() {
            val (written, _) = roundTrip(cityModel)
            assertEquals(featureTypes(cityModel), featureTypes(written))
            val tunnel = only(written, Tunnel::tryFrom)
            assertEquals("1000", tunnel.class_()?.value())
            assertEquals(listOf("1010", "1020"), tunnel.functions().items().map { it.value() })
            assertEquals(listOf("1030"), part(tunnel).functions().items().map { it.value() })
        }
    }

    @Nested
    inner class VegetationFile {
        private val cityModel = read(DATASET, "vegetation.gml")

        private fun tree(model: CityModel, id: String): SolitaryVegetationObject =
            allOf(model, SolitaryVegetationObject::tryFrom).single { it.featureId().asStr() == id }

        @Test
        fun vegetationCityModel() {
            assertEquals(3uL, cityModel.cityObjectsLen())
            assertEquals(
                listOf(FeatureType.CityModel, FeatureType.SolitaryVegetationObject, FeatureType.SolitaryVegetationObject, FeatureType.PlantCover),
                featureTypes(cityModel),
            )
        }

        @Test
        fun vegetationTree() {
            val tree = tree(cityModel, "tree_1")
            assertEquals("1000", tree.class_()?.value())
            assertEquals(listOf("1010"), tree.functions().items().map { it.value() })
            assertEquals(listOf("1020"), tree.usages().items().map { it.value() })
            assertEquals("Quercus robur", tree.species()?.value())
            val height = assertNotNull(tree.height())
            assertClose(height.value(), 12.5)
            assertEquals("m", height.uom())
            assertClose(assertNotNull(tree.trunkDiameter()).value(), 0.4)
            assertClose(assertNotNull(tree.crownDiameter()).value(), 5.5)
            assertClose(assertNotNull(tree.rootBallDiameter()).value(), 1.2)
            assertClose(assertNotNull(tree.maxRootBallDepth()).value(), 0.8)
            assertNull(tree.lod2ImplicitRepresentation())
            assertNull(tree.lod3ImplicitRepresentation())
            assertNull(tree.lod1Solid())
            assertNull(tree.lod1TerrainIntersectionCurve())
        }

        @Test
        fun vegetationImplicitGeometry() {
            val geometry = implicit(tree(cityModel, "tree_1").lod1ImplicitRepresentation())
            assertEquals("tree_prototype", geometry.objectId().asStr())
            assertEquals("model/gltf+json", geometry.mimeType()?.value())
            val pos = assertNotNull(geometry.referencePoint().object_()).pos()
            assertEquals(listOf(457850.0, 5439090.0, 112.0), listOf(pos.x(), pos.y(), pos.z()))
            val matrix = geometry.transformationMatrix()
            val rows = (0uL..3uL).map { row -> (0uL..3uL).map { column -> matrix.get(row, column).getOrThrow() } }
            assertEquals(
                listOf(listOf(2.0, 0.0, 0.0, 10.0), listOf(0.0, 2.0, 0.0, 20.0), listOf(0.0, 0.0, 3.0, 30.0), listOf(0.0, 0.0, 0.0, 1.0)),
                rows,
            )
            val relative = assertNotNull(geometry.relativeGeometry()?.object_())
            assertEquals(GeometryType.MultiSurface, relative.geometryType())
            assertEquals(1, assertNotNull(MultiSurface.tryFrom(relative)).surfaceMember().items().size)
            assertNull(Point.tryFrom(relative))
            val triangulation = relative.triangulate().getOrThrow()
            assertFalse(triangulation.hasSkipped())
            assertEquals(1, triangulation.surface().triangles().items().size)
        }

        @Test
        fun vegetationPointRelativeGeometry() {
            val tree = tree(cityModel, "tree_2")
            assertNull(tree.lod1ImplicitRepresentation())
            val geometry = implicit(tree.lod2ImplicitRepresentation())
            assertEquals("point_prototype", geometry.objectId().asStr())
            assertNull(geometry.mimeType())
            val relative = assertNotNull(geometry.relativeGeometry()?.object_())
            assertEquals(GeometryType.Point, relative.geometryType())
            val pos = assertNotNull(Point.tryFrom(relative)).pos()
            assertEquals(listOf(0.0, 0.0, 0.0), listOf(pos.x(), pos.y(), pos.z()))
            assertNull(MultiSurface.tryFrom(relative))
        }

        @Test
        fun vegetationLibraryObject() {
            assertNull(implicit(tree(cityModel, "tree_1").lod1ImplicitRepresentation()).libraryObject())
            assertEquals(
                "https://example.org/trees/oak.gltf",
                implicit(tree(cityModel, "tree_2").lod2ImplicitRepresentation()).libraryObject(),
            )
        }

        @Test
        fun vegetationPlantCover() {
            val cover = only(cityModel, PlantCover::tryFrom)
            assertEquals("cover_1", cover.featureId().asStr())
            assertEquals("2000", cover.class_()?.value())
            assertTrue(cover.functions().items().isEmpty())
            assertTrue(cover.usages().items().isEmpty())
            assertClose(assertNotNull(cover.averageHeight()).value(), 2.5)
            assertClose(assertNotNull(cover.minHeight()).value(), 1.0)
            assertClose(assertNotNull(cover.maxHeight()).value(), 4.0)
            assertNull(cover.lod1ImplicitRepresentation())
            val feature = cityModel.iterFeatures().items().single { it.featureType() == FeatureType.PlantCover }
            assertNull(SolitaryVegetationObject.tryFrom(feature))
        }

        @Test
        fun vegetationCodeSpaces() {
            assertEquals("https://example.org/tree_class", tree(cityModel, "tree_1").class_()?.code()?.codeSpace())
            assertNull(only(cityModel, PlantCover::tryFrom).class_()?.code()?.codeSpace())
        }

        @Test
        fun vegetationRoundTrip() {
            val (written, text) = roundTrip(cityModel)
            assertEquals(featureTypes(cityModel), featureTypes(written))
            val tree = tree(written, "tree_1")
            assertEquals("Quercus robur", tree.species()?.value())
            assertClose(assertNotNull(tree.height()).value(), 12.5)
            val geometry = implicit(tree.lod1ImplicitRepresentation())
            assertEquals("tree_prototype", geometry.objectId().asStr())
            assertEquals("model/gltf+json", geometry.mimeType()?.value())
            assertClose(assertNotNull(only(written, PlantCover::tryFrom).averageHeight()).value(), 2.5)
            assertFalse(text.contains("objectId"))
        }
    }

    @Nested
    inner class CityFurnitureFile {
        private val cityModel = read(DATASET, "city-furniture.gml")

        @Test
        fun furnitureAttributes() {
            val furniture = only(cityModel, CityFurniture::tryFrom)
            assertEquals("sign_1", furniture.featureId().asStr())
            assertEquals(listOf("Vorschriftzeichen"), furniture.names().items().map { it.value() })
            assertEquals("1000", furniture.class_()?.value())
            assertEquals(listOf("1080"), furniture.functions().items().map { it.value() })
            assertEquals(listOf("1090"), furniture.usages().items().map { it.value() })
            val property = assertNotNull(furniture.lod2MultiSurface())
            assertNull(property.href())
            assertEquals(1, assertNotNull(property.object_()).surfaceMember().items().size)
            assertNull(furniture.lod1ImplicitRepresentation())
            assertNull(furniture.lod2TerrainIntersectionCurve())
        }

        @Test
        fun furnitureCodeSpaces() {
            assertEquals("https://example.org/furniture_class", only(cityModel, CityFurniture::tryFrom).class_()?.code()?.codeSpace())
        }
    }

    @Nested
    inner class BuildingFile {
        private val cityModel = read(DATASET, "building.gml")

        private fun building(model: CityModel): Building = allOf(model, Building::tryFrom).single { it.featureId().asStr() == "building_1" }

        @Test
        fun buildingCityModel() {
            assertEquals(2uL, cityModel.cityObjectsLen())
            assertEquals(
                listOf(FeatureType.CityModel, FeatureType.Building, FeatureType.RoofSurface, FeatureType.WindowSurface, FeatureType.Building),
                featureTypes(cityModel),
            )
            assertEquals(4, cityModel.iterCityObjects().items().size)
        }

        @Test
        fun buildingRelation() {
            val property = building(cityModel).relatedTo().items().single()
            assertNull(property.href())
            val relation = assertNotNull(property.object_())
            assertEquals("shared", relation.relationType().value())
            assertEquals("#building_2", relation.relationTo().href()?.toString_())
            val weight = relation.genericAttributes().items().single()
            assertEquals("weight", weight.name())
            assertEquals(3L, weight.asInt()?.value())
        }

        @Test
        fun buildingAttributeSet() {
            val set = attributeSet(building(cityModel))
            assertEquals("energy", set.name())
            val (demand, label) = set.genericAttributes().items()
            assertEquals("demand", demand.name())
            assertClose(assertNotNull(demand.asDouble()).value(), 12.5)
            assertEquals("label", label.name())
            assertEquals("A+", label.asString()?.value())
        }

        @Test
        fun buildingConstruction() {
            val building = building(cityModel)
            assertEquals(RelativeToWater.EntirelyAboveWaterSurface, building.relativeToWater())
            assertEquals(listOf(2020, 1, 1), ymd(building.dateOfConstruction()))
            assertEquals(listOf(2050, 12, 31), ymd(building.dateOfDemolition()))
            val occupancy = building.occupancies().items().single()
            assertEquals(4L, occupancy.numberOfOccupants().toLong())
            assertEquals("daytime", occupancy.interval()?.value())
            assertEquals("residents", occupancy.occupantType()?.value())
        }

        @Test
        fun buildingBoundaries() {
            val (first, second) = building(cityModel).boundaries().items()
            val roofSurface = roof(first)
            assertEquals("roof_1", roofSurface.featureId().asStr())
            val filling = roofSurface.fillingSurfaces().items().single()
            assertNull(filling.href())
            val window = assertNotNull(filling.object_())
            assertEquals(FeatureType.WindowSurface, window.featureType())
            assertEquals("roof_window_1", window.featureId().asStr())
            assertNull(second.object_())
            assertEquals("#missing_boundary", second.href()?.toString_())
        }

        @Test
        fun buildingTerrainIntersectionCurve() {
            val building = building(cityModel)
            val property = assertNotNull(building.lod2TerrainIntersectionCurve())
            assertNull(property.href())
            val multiCurve = assertNotNull(property.object_())
            val member = multiCurve.curveMember().items().single()
            assertEquals(2, assertNotNull(LineString.tryFrom(assertNotNull(member.object_()))).points().items().size)
            assertClose(multiCurve.length3d().getOrThrow(), 12.0)
            assertNull(building.lod1TerrainIntersectionCurve())
            assertNull(building.lod3TerrainIntersectionCurve())
        }

        @Test
        fun buildingRoundTrip() {
            val (written, text) = roundTrip(cityModel)
            assertEquals(featureTypes(cityModel), featureTypes(written))
            val building = building(written)
            val relation = assertNotNull(building.relatedTo().items().single().object_())
            assertEquals("#building_2", relation.relationTo().href()?.toString_())
            assertEquals("energy", attributeSet(building).name())
            assertEquals(listOf(2050, 12, 31), ymd(building.dateOfDemolition()))
            val occupancy = building.occupancies().items().single()
            assertEquals(4L, occupancy.numberOfOccupants().toLong())
            assertEquals("daytime", occupancy.interval()?.value())
            assertEquals("residents", occupancy.occupantType()?.value())
            val (first, second) = building.boundaries().items()
            assertEquals("roof_window_1", assertNotNull(roof(first).fillingSurfaces().items().single().object_()).featureId().asStr())
            assertEquals("#missing_boundary", second.href()?.toString_())
            assertClose(assertNotNull(building.lod2TerrainIntersectionCurve()?.object_()).length3d().getOrThrow(), 12.0)
            assertFalse(text.contains("TerrainIntersectionCurveProperty"))
        }
    }

    @Nested
    inner class TransportationFile {
        private val cityModel = read(DATASET, "transportation.gml")

        @Test
        fun transportationSection() {
            val section = only(cityModel, Section::tryFrom)
            assertEquals("section_1", section.featureId().asStr())
            assertEquals(TrafficDirectionValue.Both, section.trafficDirection())
            val occupancy = section.occupancies().items().single()
            assertEquals(120L, occupancy.numberOfOccupants().toLong())
            assertEquals("peakHour", occupancy.interval()?.value())
            val property = section.trafficSpaces().items().single()
            assertNull(property.href())
            val space = assertNotNull(property.object_())
            assertEquals("space_1", space.featureId().asStr())
            assertEquals(GranularityValue.Lane, space.granularity())
        }

        @Test
        fun transportationPoint() {
            val property = assertNotNull(only(cityModel, TrafficSpace::tryFrom).lod0Point())
            assertNull(property.href())
            val point = assertNotNull(property.object_())
            assertEquals("point_1", point.id()?.asStr())
            val pos = point.pos()
            assertEquals(listOf(1.5, -2.5, 3.25), listOf(pos.x(), pos.y(), pos.z()))
            val envelope = assertNotNull(point.computeEnvelope())
            for (corner in listOf(envelope.lowerCorner(), envelope.upperCorner())) {
                assertEquals(listOf(1.5, -2.5, 3.25), listOf(corner.x(), corner.y(), corner.z()))
            }
        }

        @Test
        fun transportationCurves() {
            val multiCurve = assertNotNull(only(cityModel, TrafficSpace::tryFrom).lod0MultiCurve()?.object_())
            val (line, ring, reference) = multiCurve.curveMember().items()
            val lineKind = assertNotNull(line.object_())
            assertEquals(GeometryType.LineString, lineKind.geometryType())
            assertNull(AbstractRingKind.tryFrom(lineKind))
            val lineString = assertNotNull(LineString.tryFrom(lineKind))
            assertEquals(2, lineString.points().items().size)
            assertClose(lineString.length3d(), 5.0)
            val ringKind = assertNotNull(ring.object_())
            assertEquals(GeometryType.LinearRing, ringKind.geometryType())
            val linearRing = assertNotNull(LinearRing.tryFrom(assertNotNull(AbstractRingKind.tryFrom(ringKind))))
            assertEquals(3, linearRing.points().items().size)
            assertClose(linearRing.length3d(), 2.0 + sqrt(2.0))
            assertNull(reference.object_())
            assertEquals("#missing_curve", reference.href()?.toString_())
            val error = assertIs<Error>(multiCurve.length3d().exceptionOrNull())
            assertEquals(ErrorKind.UnresolvedReference, error.kind())
            assertTrue(error.message().contains("#missing_curve"), error.message())
        }
    }

    @Nested
    inner class GeometryFile {
        private val cityModel = read(DATASET, "geometry.gml")

        @Test
        fun geometrySkippedMembers() {
            val building = allOf(cityModel, Building::tryFrom).single { it.featureId().asStr() == "geometry_1" }
            val multiSurface = assertNotNull(building.lod2MultiSurface()?.object_())
            val (square, collinear, tinKind) = multiSurface.surfaceMember().items().map { assertNotNull(it.object_()) }
            for ((kind, id) in listOf(square to "square", collinear to "collinear")) {
                assertEquals(GeometryType.Polygon, kind.geometryType())
                assertEquals(id, kind.id()?.asStr())
            }
            assertClose(collinear.area3d().getOrThrow(), 0.0)
            assertEquals(GeometryType.TriangulatedSurface, tinKind.geometryType())
            assertNull(Polygon.tryFrom(tinKind))
            val tin = assertNotNull(TriangulatedSurface.tryFrom(tinKind))
            assertEquals("tin", tin.id()?.asStr())
            assertEquals(2, tin.triangles().items().size)
            assertEquals(2, tin.surface().patches().items().size)
            assertClose(tin.area3d().getOrThrow(), 1.0)
            val triangulation = multiSurface.triangulate().getOrThrow()
            assertEquals(4, triangulation.surface().triangles().items().size)
            assertTrue(triangulation.hasSkipped())
            val error = triangulation.skipped().items().single()
            assertEquals(ErrorKind.InvalidArgument, error.kind())
            assertTrue(error.message().contains("earcut produced no triangles"), error.message())
        }
    }
}
