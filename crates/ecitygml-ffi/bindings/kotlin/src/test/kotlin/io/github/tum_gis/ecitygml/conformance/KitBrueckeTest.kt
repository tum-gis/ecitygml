package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertNull

// The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.

private const val BRIDGE_ID = "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"

private val model by lazy { read("kit-bruecke", "Modellbahnbruecke-LoD2-V03__v3.gml") }

private fun bridge(cityModel: CityModel): Bridge =
    assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Bridge::tryFrom) })

private fun featureTypes(cityModel: CityModel): List<FeatureType> =
    cityModel.iterFeatures().asSequence().map { assertNotNull(it).featureType() }.toList()

private fun assertEnvelope(envelope: Envelope?, lower: Triple<Double, Double, Double>, upper: Triple<Double, Double, Double>) {
    assertNotNull(envelope)
    for ((position, expected) in listOf(envelope.lowerCorner() to lower, envelope.upperCorner() to upper)) {
        assertClose(position.x(), expected.first)
        assertClose(position.y(), expected.second)
        assertClose(position.z(), expected.third)
    }
}

class KitBrueckeTest {
    @Test
    fun bridgeCityModel() {
        assertEquals(1uL, model.cityObjectsLen())
        assertEnvelope(model.boundedBy()?.envelope(), Triple(457644.585, 5439126.455, 109.0), Triple(457708.084, 5439157.169, 124.3))
        val expected = listOf(FeatureType.CityModel, FeatureType.Bridge, FeatureType.Appearance) +
            List(3) { FeatureType.ParameterizedTexture } +
            List(2) { FeatureType.BridgeInstallation } +
            List(11) { FeatureType.BridgeConstructiveElement }
        assertEquals(expected, featureTypes(model))
        assertEquals(14, model.iterCityObjects().asSequence().count())
    }

    @Test
    fun bridgeAttributes() {
        val b = bridge(model)
        assertEquals(BRIDGE_ID, b.featureId().asStr())
        assertEquals(0, b.names().asSequence().count())
        assertNull(b.class_())
        assertEquals(0, b.functions().asSequence().count())
        assertEquals(0, b.usages().asSequence().count())
        assertEquals(0, b.bridgeParts().asSequence().count())
        assertEquals(0, b.boundaries().asSequence().count())
        assertNull(b.dateOfConstruction())
        assertNull(b.creationDate())
        assertEquals(0, b.heights().asSequence().count())
        assertEquals(0, b.occupancies().asSequence().count())
        assertEquals(0, b.genericAttributes().asSequence().count())
        assertEquals(0, b.externalReferences().asSequence().count())
    }

    @Test
    fun bridgeGeometry() {
        val b = bridge(model)
        assertEnvelope(b.boundedBy()?.envelope(), Triple(457645.136, 5439126.692, 115.3), Triple(457707.533, 5439156.931, 116.2))
        val property = assertNotNull(b.lod2MultiSurface())
        assertNull(property.href())
        val multiSurface = assertNotNull(property.object_())
        assertEquals(18, multiSurface.surfaceMember().asSequence().count())
        assertClose(multiSurface.area3d().getOrThrow(), 795.4201811265907)
        val triangulation = multiSurface.triangulate().getOrThrow()
        assertEquals(60, triangulation.surface().triangles().asSequence().count())
        assertFalse(triangulation.hasSkipped())
        assertNull(b.lod1Solid())
        assertNull(b.lod2Solid())
        assertNull(b.lod3MultiSurface())
    }

    @Test
    fun bridgeRoundTrip() {
        val writer = GmlWriter.create(CitygmlFormat.Gml)
        writer.finish(model).getOrThrow()
        val written = GmlReader.create(writer.data(), CitygmlFormat.Gml).finish().getOrThrow()
        assertEquals(featureTypes(model), featureTypes(written))
        assertEquals(BRIDGE_ID, bridge(written).featureId().asStr())
    }
}
