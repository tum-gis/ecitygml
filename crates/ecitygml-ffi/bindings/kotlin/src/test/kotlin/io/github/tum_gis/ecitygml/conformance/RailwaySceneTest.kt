package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/conformance/railway-scene.md.

private const val TEMPLATE_A = "#Mult_SO043561_5693_194007"
private const val TEMPLATE_B = "#Mult_SO045475_3243_790864"
private val INLINE_TEMPLATES = setOf("Forest tree 3", "Tree1", "Forest tree 1")
private val TEMPLATE_A_TREES = setOf("Forest tree 4", "Forest tree 9", "Forest tree 5")

private val WALL = FeatureType.WallSurface
private val ROOF = FeatureType.RoofSurface
private val GROUND = FeatureType.GroundSurface
private val CLOSURE = FeatureType.ClosureSurface

private val railway by lazy { read("railway-scene", "Railway_Scene_LoD3__v3-thinned.gml") }

private fun <T> Iterator<T?>.items(): List<T> = asSequence().map { assertNotNull(it) }.toList()

private fun featureTypes(cityModel: CityModel): List<FeatureType> = cityModel.iterFeatures().items().map { it.featureType() }

/** All features a class accepts, in document order. */
private fun <T> allOf(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): List<T> =
    cityModel.iterFeatures().items().mapNotNull(tryFrom)

/** A tree's inline LoD3 implicit geometry. */
private fun implicitGeometry(tree: SolitaryVegetationObject): ImplicitGeometry {
    val property = assertNotNull(tree.lod3ImplicitRepresentation())
    assertNull(property.href())
    return assertNotNull(property.object_())
}

private fun templateHref(tree: SolitaryVegetationObject): String? = implicitGeometry(tree).relativeGeometry()?.href()?.toString_()

private fun ImplicitGeometry.matrix(row: Int, column: Int): Double =
    transformationMatrix().get(row.toULong(), column.toULong()).getOrThrow()

class RailwaySceneTest {
    @Test
    fun railwayCityModel() {
        assertEquals(52uL, railway.cityObjectsLen())
        assertNull(railway.boundedBy())
        val types = featureTypes(railway)
        assertEquals(232, types.size)
        assertEquals(FeatureType.CityModel, types.first())
        assertEquals(
            mapOf(
                FeatureType.CityModel to 1,
                FeatureType.SolitaryVegetationObject to 15,
                FeatureType.Tunnel to 4,
                FeatureType.TunnelInstallation to 8,
                FeatureType.Railway to 10,
                FeatureType.Bridge to 4,
                FeatureType.BridgeConstructiveElement to 3,
                FeatureType.BridgeInstallation to 2,
                FeatureType.Building to 3,
                FeatureType.BuildingInstallation to 56,
                FeatureType.CityFurniture to 11,
                FeatureType.CityObjectGroup to 1,
                FeatureType.GenericOccupiedSpace to 2,
                FeatureType.WaterBody to 1,
                FeatureType.WaterSurface to 1,
                FeatureType.WaterGroundSurface to 1,
                FeatureType.ReliefFeature to 1,
                FeatureType.TinRelief to 1,
                WALL to 33,
                ROOF to 12,
                GROUND to 7,
                CLOSURE to 8,
                FeatureType.DoorSurface to 9,
                FeatureType.WindowSurface to 34,
                FeatureType.OuterCeilingSurface to 3,
                FeatureType.OuterFloorSurface to 1,
            ),
            types.groupingBy { it }.eachCount(),
        )
        assertEquals(231, railway.iterCityObjects().asSequence().count())
    }

    @Test
    fun railwayTunnels() {
        val expected = listOf(
            Triple("GMLID_BUI142242_863_347", "Tunnel KIT/KHH-3", listOf(GROUND, WALL, ROOF, WALL, CLOSURE, CLOSURE)),
            Triple("GMLID_BUI336993_213_9312", "Tunnel KIT/KHH-2", listOf(WALL, ROOF, WALL, CLOSURE, CLOSURE, GROUND)),
            Triple("GMLID_BUI289877_1911_4122", "Tunnel KIT/KHH-4", listOf(WALL, GROUND, CLOSURE, WALL, ROOF, CLOSURE)),
            Triple("GMLID_BUI180021_673_14143", "Tunnel KIT/KHH-1", listOf(GROUND, WALL, ROOF, CLOSURE, CLOSURE, WALL)),
        )
        val tunnels = allOf(railway, Tunnel::tryFrom)
        assertEquals(expected.size, tunnels.size)
        tunnels.zip(expected).forEach { (tunnel, want) ->
            assertEquals(want.first, tunnel.featureId().asStr())
            assertEquals(want.second, firstName(tunnel.names()))
            val properties = tunnel.boundaries().items()
            assertTrue(properties.all { it.href() == null })
            assertEquals(want.third, properties.map { assertNotNull(it.object_()).featureType() })
            assertNull(tunnel.class_())
            assertEquals(0, tunnel.functions().asSequence().count())
            assertEquals(0, tunnel.usages().asSequence().count())
            assertEquals(0, tunnel.tunnelParts().asSequence().count())
            val created = assertNotNull(tunnel.creationDate())
            assertEquals(Triple(2015, 3u, 6u), Triple(created.year(), created.month(), created.day()))
            assertEquals(0u to 0u, created.hour() to created.minute())
            assertEquals(3600, created.offsetSeconds())
            assertEquals(RelativeToTerrain.EntirelyAboveTerrain, tunnel.relativeToTerrain())
        }
    }

    @Test
    fun railwayTrees() {
        data class Expected(val id: String, val name: String, val class_: String?, val species: String, val functions: List<String>)
        val expected = listOf(
            Expected("GMLID_SO0158953_776_12462", "Forest tree 3", "1070", "1800", listOf()),
            Expected("GMLID_SO092422_3593_9527", "Tree1", null, "9999", listOf("LOD3")),
            Expected("GMLID_SO0200811_525_4986", "Forest tree 1", "1060", "1640", listOf()),
            Expected("GMLID_SO0321978_1466_7441", "Forest tree 4", "1070", "1800", listOf()),
            Expected("GMLID_SO0260143_1214_1315", "Forest tree 11", "1060", "1640", listOf()),
            Expected("GMLID_SO0400934_2926_3381", "Forest tree 12", "1060", "1640", listOf()),
            Expected("GMLID_SO0124800_3522_13577", "Forest tree 13", "1060", "1640", listOf()),
            Expected("GMLID_SO0443764_1492_9667", "Forest tree 14", "1060", "1640", listOf()),
            Expected("GMLID_SO015374_872_14131", "Forest tree 2", "1060", "1640", listOf()),
            Expected("GMLID_SO081792_2341_11961", "Forest tree 10", "1060", "1640", listOf()),
            Expected("GMLID_SO0283142_1335_8999", "Forest tree 7", "1060", "1640", listOf()),
            Expected("GMLID_SO0107241_3793_12555", "Forest tree 9", "1070", "1800", listOf()),
            Expected("GMLID_SO0286258_965_2893", "Forest tree 5", "1070", "1800", listOf()),
            Expected("GMLID_SO0410128_214_10515", "Forest tree 6", "1060", "1640", listOf()),
            Expected("GMLID_SO086970_1053_8814", "Forest tree 8", "1060", "1640", listOf()),
        )
        val trees = allOf(railway, SolitaryVegetationObject::tryFrom)
        assertEquals(expected.size, trees.size)
        trees.zip(expected).forEach { (tree, want) ->
            assertEquals(want.id, tree.featureId().asStr())
            assertEquals(want.name, firstName(tree.names()))
            assertEquals(want.class_, tree.class_()?.value())
            assertEquals(want.species, tree.species()?.value())
            assertEquals(want.functions, tree.functions().items().map { it.value() })
            assertEquals(0, tree.usages().asSequence().count())
            assertNull(tree.lod1ImplicitRepresentation())
            assertNull(tree.lod2ImplicitRepresentation())
        }
    }

    @Test
    fun railwayTreeTemplates() {
        for (tree in allOf(railway, SolitaryVegetationObject::tryFrom)) {
            val geometry = implicitGeometry(tree)
            assertNull(geometry.mimeType())
            listOf(30.0, 30.0, 30.0, 1.0).forEachIndexed { i, value -> assertClose(geometry.matrix(i, i), value) }
            val name = firstName(tree.names())
            val property = assertNotNull(geometry.relativeGeometry())
            if (name in INLINE_TEMPLATES) {
                assertNull(property.href())
                val multiSurface = assertNotNull(MultiSurface.tryFrom(assertNotNull(property.object_())), name)
                assertEquals(1, multiSurface.surfaceMember().asSequence().count())
            } else {
                assertNull(property.object_())
                assertEquals(if (name in TEMPLATE_A_TREES) TEMPLATE_A else TEMPLATE_B, templateHref(tree), name)
            }
        }
    }

    @Test
    fun railwayTreePlacement() {
        for (tree in allOf(railway, SolitaryVegetationObject::tryFrom)) {
            val geometry = implicitGeometry(tree)
            val pos = assertNotNull(geometry.referencePoint().object_()).pos()
            val translation = listOf(geometry.matrix(0, 3), geometry.matrix(1, 3), geometry.matrix(2, 3))
            val name = firstName(tree.names())
            val reference = if (name == "Tree1") {
                listOf(-568.8000793496976, 457.60044759869743, 105.00139681350242)
            } else {
                listOf(-600.0, 400.0, -150.0)
            }
            listOf(pos.x(), pos.y(), pos.z()).zip(reference).forEach { (actual, want) -> assertClose(actual, want) }
            val expected = when (name) {
                "Tree1" -> listOf(0.0, 0.0, 0.0)
                "Forest tree 3" -> listOf(39.4421005419207, 220.3838834926932, 268.5013679006178)
                else -> null
            }
            expected?.zip(translation)?.forEach { (want, actual) -> assertClose(actual, want) }
        }
    }

    @Test
    fun railwayFurniture() {
        val expected = listOf(
            "GMLID_7431654_78949_792" to "1090",
            "GMLID_0528986_170479_94" to "OTHERS",
            "GMLID_4323540_367099_910" to "1090",
            "GMLID_1381455_184173_656" to "OTHERS",
            "GMLID_1429491_351612_1485" to "1090",
            "GMLID_5361967_192822_672" to "1090",
            "GMLID_2108434_31807_876" to "1090",
            "GMLID_0373494_301709_129" to "1540",
            "GMLID_6162422_289094_1279" to "1090",
            "GMLID_3313190_307178_612" to "1090",
            "GMLID_855011_330784_753" to "1540",
        )
        val furniture = allOf(railway, CityFurniture::tryFrom)
        assertEquals(
            expected.map { it.first to listOf(it.second) },
            furniture.map { it.featureId().asStr() to it.functions().items().map { f -> f.value() } },
        )
        for (item in furniture) {
            assertNull(item.class_())
            assertEquals(0, item.usages().asSequence().count())
            assertNull(item.lod3ImplicitRepresentation())
            val property = assertNotNull(item.lod3MultiSurface())
            assertNull(property.href())
            assertEquals(1, assertNotNull(property.object_()).surfaceMember().asSequence().count())
        }
    }

    @Test
    fun railwayRelief() {
        val relief = allOf(railway, ReliefFeature::tryFrom).single()
        assertEquals("GMLID_TIN436865_187531_1154", relief.featureId().asStr())
        assertEquals(0, relief.names().asSequence().count())
        assertEquals(LevelOfDetail.Three, relief.lod())
        val component = relief.reliefComponents().items().single()
        assertNull(component.href())
        assertEquals(FeatureType.TinRelief, assertNotNull(component.object_()).featureType())

        val tinRelief = allOf(railway, TinRelief::tryFrom).single()
        assertEquals("UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9", tinRelief.featureId().asStr())
        assertEquals(LevelOfDetail.Three, tinRelief.lod())
        val tin = assertNotNull(tinRelief.tin())
        assertNull(tin.href())
        val surface = assertNotNull(tin.object_())
        assertEquals(1, surface.triangles().asSequence().count())
        assertClose(surface.area3d().getOrThrow(), 3.2750424144626247)
    }

    @Test
    fun railwayBuildingsAndBridges() {
        assertEquals(
            listOf(
                Triple("GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13),
                Triple("GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19),
                Triple("GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8),
            ),
            allOf(railway, Building::tryFrom).map {
                Triple(it.featureId().asStr(), firstName(it.names()), it.boundaries().asSequence().count())
            },
        )
        assertEquals(
            listOf(
                "GMLID_BUI205585_1385_1373" to "Bridge KIT 4",
                "GMLID_BUI51891_765_738" to "Bridge KIT 3",
                "GMLID_BUI100628_817_8083" to "Bridge KIT 2",
                "GMLID_BUI30683_572_6686" to "Bridge KIT 1",
            ),
            allOf(railway, Bridge::tryFrom).map { it.featureId().asStr() to firstName(it.names()) },
        )
    }

    @Test
    fun railwayRoundTrip() {
        val writer = GmlWriter.create(CitygmlFormat.Gml)
        writer.finish(railway).getOrThrow()
        val written = GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
        assertEquals(featureTypes(railway), featureTypes(written))
        fun ids(model: CityModel): List<String> =
            allOf(model, Tunnel::tryFrom).map { it.featureId().asStr() } +
                allOf(model, SolitaryVegetationObject::tryFrom).map { it.featureId().asStr() } +
                allOf(model, CityFurniture::tryFrom).map { it.featureId().asStr() } +
                allOf(model, Building::tryFrom).map { it.featureId().asStr() } +
                allOf(model, Bridge::tryFrom).map { it.featureId().asStr() }
        assertEquals(ids(railway), ids(written))
        fun hrefs(model: CityModel) = allOf(model, SolitaryVegetationObject::tryFrom).map(::templateHref)
        assertEquals(hrefs(railway), hrefs(written))
    }
}
