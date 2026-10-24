package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull

// The cases of crates/ecitygml/tests/api/iteration.md.

private const val FZK_LOD3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"
private const val ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml"

class IterationTest {
    @Test
    fun iteratorExhausted() {
        val iterator = read(fixture(FZK_LOD3)).iterFeatures()
        var count = 0
        while (iterator.hasNext()) {
            assertNotNull(iterator.next())
            count++
        }
        assertEquals(22, count)
        assertFalse(iterator.hasNext())
        assertFalse(iterator.hasNext())
    }

    @Test
    fun iteratorStoppedEarly() {
        val cityModel = read(fixture(ASAM_ROAD_SHAPE))
        var iterator: AbstractFeatureKindRefIterator? = cityModel.iterFeatures()
        assertEquals(FeatureType.CityModel, assertNotNull(iterator?.next()).featureType())
        @Suppress("UNUSED_VALUE")
        iterator = null
        System.gc()
        assertEquals(11, featureTypes(cityModel).size)
        assertEquals(1uL, cityModel.cityObjectsLen())
    }

    @Test
    fun iteratorsIndependent() {
        val cityModel = read(fixture(FZK_LOD3))
        val (first, second) = cityModel.iterFeatures() to cityModel.iterFeatures()
        val (a, b) = mutableListOf<FeatureType>() to mutableListOf<FeatureType>()
        while (first.hasNext() || second.hasNext()) {
            assertEquals(first.hasNext(), second.hasNext())
            a.add(assertNotNull(first.next()).featureType())
            b.add(assertNotNull(second.next()).featureType())
        }
        assertEquals(22, a.size)
        assertEquals(a, b)
        assertEquals(a, featureTypes(cityModel))
    }

    @Test
    fun iteratorKeepsModelAlive() {
        val iterator = read(fixture(FZK_LOD3)).iterFeatures()
        System.gc()
        assertEquals(4, iterator.asSequence().count { WallSurface.tryFrom(it!!) != null })
    }

    @Test
    fun nativeIteration() {
        val types = mutableListOf<FeatureType>()
        for (feature in read(fixture(FZK_LOD3)).iterFeatures()) {
            types.add(assertNotNull(feature).featureType())
        }
        assertEquals(22, types.size)
        assertEquals(FeatureType.CityModel, types[0])
    }
}
