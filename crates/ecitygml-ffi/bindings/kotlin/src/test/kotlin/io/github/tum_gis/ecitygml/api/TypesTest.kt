package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/api/types.md.

private const val FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
private const val FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
private const val FZK_LOD3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"
private const val TUM = "tum-main-entrance/TUM-Main-Entrance.gml"
private const val ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml"
private const val ASAM_JUNCTION = "asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml"
private const val RAILWAY = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml"
private const val SIG3D = "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_"

/** The first feature that `tryFrom` accepts. */
private fun <T : Any> first(cityModel: CityModel, tryFrom: (AbstractFeatureKindRef) -> T?): T =
    assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { tryFrom(it!!) })

/** `tryFrom` accepts exactly the features of its feature type. */
private fun assertTryFromMatches(cityModel: CityModel, types: List<Pair<(AbstractFeatureKindRef) -> Any?, FeatureType>>) {
    for (feature in cityModel.iterFeatures().asSequence().map { it!! }) {
        for ((tryFrom, featureType) in types) {
            assertEquals(feature.featureType() == featureType, tryFrom(feature) != null, "$featureType as ${feature.featureType()}")
        }
    }
}

class TypesTest {
    @Test
    fun directPositionNew() {
        val position = DirectPosition.create(1.0, 2.0, 3.0).getOrThrow()
        assertEquals(listOf(1.0, 2.0, 3.0), listOf(position.x(), position.y(), position.z()))
        assertError(DirectPosition.create(Double.NaN, 0.0, 0.0), ErrorKind.InvalidArgument, "non-finite")
    }

    @Test
    fun levelOfDetailIndex() {
        listOf(LevelOfDetail.Zero, LevelOfDetail.One, LevelOfDetail.Two, LevelOfDetail.Three).forEachIndexed { index, lod ->
            assertEquals(index.toULong(), lod.asIndex())
            assertEquals(lod, LevelOfDetail.tryFrom(index.toUByte()).getOrThrow())
        }
        assertError(LevelOfDetail.tryFrom(4u.toUByte()), ErrorKind.InvalidArgument, "4")
    }

    @Test
    fun featureTypeName() {
        assertEquals("Building", FeatureType.Building.name)
        assertEquals("TinRelief", FeatureType.TinRelief.name)
    }

    @Test
    fun dateFromParts() {
        val date = Date.fromParts(2020, 1u, 2u, 3600).getOrThrow()
        assertEquals(listOf(2020, 1, 2, 3600), listOf(date.year(), date.month().toInt(), date.day().toInt(), date.offsetSeconds()))
        val start = date.startOfDay()
        assertEquals(listOf(0u, 0u, 0u), listOf(start.hour(), start.minute(), start.second()))
        assertEquals("2020-01-02T00:00:00+01:00", start.toRfc3339())

        assertError(Date.fromParts(2021, 2u, 30u, 0), ErrorKind.InvalidArgument, "do not form a valid date")
    }

    @Test
    fun dateTimeFromParts() {
        val dateTime = DateTime.fromParts(2017, 1u, 23u, 13u, 14u, 15u, 500_000_000u, -7200).getOrThrow()
        assertEquals(listOf(2017, 1, 23), listOf(dateTime.year(), dateTime.month().toInt(), dateTime.day().toInt()))
        assertEquals(listOf(13u, 14u, 15u), listOf(dateTime.hour(), dateTime.minute(), dateTime.second()))
        assertEquals(500_000_000u, dateTime.nanosecond())
        assertEquals(-7200, dateTime.offsetSeconds())
        assertEquals(1485184455L, dateTime.timestamp())
        assertEquals(500_000_000u, dateTime.timestampSubsecNanos())
        assertEquals("2017-01-23T13:14:15.500-02:00", dateTime.toRfc3339())

        assertError(
            DateTime.fromParts(2020, 1u, 1u, 0u, 0u, 0u, 0u, 30),
            ErrorKind.InvalidArgument,
            "timezone offset of 30 s is invalid",
        )
    }

    @Test
    fun dateTimeRead() {
        val created = assertNotNull(first(read(fixture(FZK_LOD2)), Building::tryFrom).creationDate())
        assertEquals("2017-01-23T00:00:00+01:00", created.toRfc3339())
    }

    @Test
    fun tryFromMatchesFeatureType() {
        assertTryFromMatches(
            read(fixture(FZK_LOD3)),
            listOf(
                Building::tryFrom to FeatureType.Building,
                WallSurface::tryFrom to FeatureType.WallSurface,
                RoofSurface::tryFrom to FeatureType.RoofSurface,
                GroundSurface::tryFrom to FeatureType.GroundSurface,
                DoorSurface::tryFrom to FeatureType.DoorSurface,
                WindowSurface::tryFrom to FeatureType.WindowSurface,
            ),
        )
        assertTryFromMatches(
            read(fixture(ASAM_ROAD_SHAPE)),
            listOf(
                Road::tryFrom to FeatureType.Road,
                Section::tryFrom to FeatureType.Section,
                TrafficSpace::tryFrom to FeatureType.TrafficSpace,
                TrafficArea::tryFrom to FeatureType.TrafficArea,
                AuxiliaryTrafficSpace::tryFrom to FeatureType.AuxiliaryTrafficSpace,
                AuxiliaryTrafficArea::tryFrom to FeatureType.AuxiliaryTrafficArea,
            ),
        )
    }

    @Test
    fun featureFromCityObject() {
        val cityObject = assertNotNull(read(fixture(ASAM_JUNCTION)).iterCityObjects().next())
        assertEquals(FeatureType.Road, cityObject.featureType())
        val feature = AbstractFeatureKindRef.fromCityObject(cityObject)
        assertEquals(FeatureType.Road, feature.featureType())
        assertEquals("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", Road.tryFrom(feature)?.featureId()?.asStr())
        assertNull(Building.tryFrom(feature))
    }

    @Test
    fun matrixIndexOutOfRange() {
        val tree = assertNotNull(
            read(fixture(RAILWAY)).iterFeatures().asSequence()
                .mapNotNull { SolitaryVegetationObject.tryFrom(it!!) }
                .find { it.featureId().asStr() == "GMLID_SO092422_3593_9527" },
        )
        val matrix = assertNotNull(tree.lod3ImplicitRepresentation()?.object_()).transformationMatrix()
        assertEquals(1.0, matrix.get(3uL, 3uL).getOrThrow())
        for ((row, column) in listOf(4uL to 0uL, 0uL to 4uL)) {
            assertError(matrix.get(row, column), ErrorKind.InvalidArgument, "out of range")
        }
    }

    @Test
    fun gmlId() {
        val cityModel = read(fixture(FZK_LOD1))
        val generated = cityModel.featureId().asStr()
        assertTrue(generated.startsWith("ecitygml-gen-feature-"), generated)
        assertEquals(generated, cityModel.id()?.asStr())

        val wall = first(read(fixture(FZK_LOD2)), WallSurface::tryFrom)
        assertEquals("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", wall.id()?.asStr())
        assertEquals("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", wall.featureId().asStr())

        assertEquals("DEBY_LOD2_4959457", first(read(fixture(TUM)), Building::tryFrom).id()?.asStr())
    }

    @Test
    fun codeSpace() {
        val building = first(read(fixture(FZK_LOD2)), Building::tryFrom)
        val code = assertNotNull(building.class_()).code()
        assertEquals("1000" to "${SIG3D}class.xml", code.value() to code.codeSpace())
        assertEquals(listOf("${SIG3D}function.xml"), building.functions().asSequence().map { it!!.code().codeSpace() }.toList())
        assertEquals(listOf("${SIG3D}usage.xml"), building.usages().asSequence().map { it!!.code().codeSpace() }.toList())

        val functions = first(read(fixture(TUM)), Building::tryFrom).functions().asSequence().map { it!!.value() to it.code().codeSpace() }
        assertEquals(listOf("31001_3020" to null), functions.toList())

        val names = read(fixture(FZK_LOD1)).names().asSequence().map { it!!.value() to it.codeSpace() }
        assertEquals(listOf("AC14-FZK-Haus" to null), names.toList())
    }
}
