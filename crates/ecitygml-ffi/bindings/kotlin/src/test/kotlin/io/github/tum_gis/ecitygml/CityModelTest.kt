package io.github.tum_gis.ecitygml

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertIs
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

private val fixtures = System.getProperty("ecitygml.fixtures")

/** `GmlReader::from_path(path)?.finish()`, as in Rust. */
private fun read(path: String): Result<CityModel> = GmlReader.fromPath(path).mapCatching { it.finish().getOrThrow() }

class CityModelTest {
    @Test
    fun readsCityObjects() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        assertEquals(1uL, cityModel.cityObjectsLen())
    }

    @Test
    fun missingFileFails() {
        // The Rust `Error` is the exception; its text comes from `message()`.
        val error = assertIs<Error>(read("$fixtures/does-not-exist.gml").exceptionOrNull())
        assertEquals(ErrorKind.Io, error.kind())
        assertTrue(error.message().contains("No such file"), error.message())
    }

    @Test
    fun unsupportedExtensionFails() {
        val error = assertIs<Error>(read("$fixtures/../../README.md").exceptionOrNull())
        assertEquals(ErrorKind.InvalidArgument, error.kind())
    }

    @Test
    fun boundedBy() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val envelope = assertNotNull(assertNotNull(cityModel.boundedBy()).envelope())
        assertEquals(12.0, envelope.sizeX())
        assertEquals(10.0, envelope.sizeY())
        assertEquals(6.517669, envelope.sizeZ(), 1e-9)
    }

    @Test
    fun envelopeCorners() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val lower = assertNotNull(assertNotNull(cityModel.boundedBy()).envelope()).lowerCorner()
        assertEquals(457842.0, lower.x())
        assertEquals(5439083.0, lower.y())
        assertEquals(111.8, lower.z())
    }

    @Test
    fun createsDirectPosition() {
        val position = DirectPosition.create(1.0, 2.0, 3.0).getOrThrow()
        assertEquals(3.0, position.z())

        val error = assertIs<Error>(DirectPosition.create(Double.NaN, 0.0, 0.0).exceptionOrNull())
        assertEquals(ErrorKind.InvalidArgument, error.kind())
    }

    @Test
    fun lifespan() {
        // The fixtures only have lifespan dates on buildings; add one to the city model itself.
        val original = java.io.File("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").readText()
        val file = kotlin.io.path.createTempFile(suffix = ".gml").toFile()
        file.writeText(original.replaceFirst(
            "</gml:boundedBy>",
            "</gml:boundedBy>\n  <creationDate>2017-01-23T00:00:00+01:00</creationDate>",
        ))
        val cityModel = read(file.path).getOrThrow()
        file.delete()

        val creationDate = assertNotNull(cityModel.creationDate())
        assertEquals("2017-01-23T00:00:00+01:00", creationDate.toRfc3339())
        assertEquals(1485126000L, creationDate.timestamp())
        assertEquals(null, cityModel.validTo())
    }

    @Test
    fun featureId() {
        val original = java.io.File("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").readText()
        val file = kotlin.io.path.createTempFile(suffix = ".gml").toFile()
        file.writeText(original.replaceFirst("<CityModel ", "<CityModel gml:id=\"CM_1\" "))
        val cityModel = read(file.path).getOrThrow()
        file.delete()
        assertEquals("CM_1", cityModel.featureId().asStr())
    }

    @Test
    fun gmlIdAndNames() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val names = cityModel.names().asSequence().map { it!!.value() to it.codeSpace() }.toList()
        assertEquals(listOf("AC14-FZK-Haus" to null), names)

        val original = java.io.File("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").readText()
        val file = kotlin.io.path.createTempFile(suffix = ".gml").toFile()
        file.writeText(original.replaceFirst("<CityModel ", "<CityModel gml:id=\"CM_gml\" "))
        val withId = read(file.path).getOrThrow()
        file.delete()
        assertEquals("CM_gml", withId.id()?.asStr())
    }

    @Test
    fun gmlReaderFinishesOnce() {
        val reader = GmlReader.fromPath("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        reader.withRebuildObjectBounds(false)
        assertEquals(1uL, reader.finish().getOrThrow().cityObjectsLen())
        assertEquals(ErrorKind.InvalidArgument, assertIs<Error>(reader.finish().exceptionOrNull()).kind())
    }

    @Test
    fun trafficSpaceMultiCurves() {
        val cityModel = read("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow()
        val spaces = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(TrafficSpace::tryFrom) }.toList()
        assertEquals(2, spaces.size)
        for (space in spaces) {
            assertEquals(null, space.lod0MultiCurve())
            assertEquals(null, space.lod3MultiCurve())
            val multiCurve = assertNotNull(space.lod2MultiCurve()?.object_())
            assertEquals(40.0, multiCurve.length3d().getOrThrow(), 1e-9)
            assertNotNull(multiCurve.computeEnvelope())

            val members = multiCurve.curveMember().asSequence().toList()
            assertEquals(1, members.size)
            val curve = assertNotNull(members.single()?.object_())
            assertEquals(GeometryType.LineString, curve.geometryType())
            val lineString = assertNotNull(LineString.tryFrom(curve))
            assertEquals(40.0, lineString.length3d(), 1e-9)
            assertEquals(2, lineString.points().asSequence().count())
        }
    }

    @Test
    fun trafficSpaceMultiSurface() {
        // A 10 m x 4 m rectangle with a 1 m x 1 m hole (39 m^2), inserted after the first lod2Solid.
        val multiSurfaceXml = "</lod2Solid><lod2MultiSurface><gml:MultiSurface><gml:surfaceMember><gml:Polygon gml:id=\"PolyID_space\"><gml:exterior><gml:LinearRing><gml:posList srsDimension=\"3\">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior><gml:interior><gml:LinearRing><gml:posList srsDimension=\"3\">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList></gml:LinearRing></gml:interior></gml:Polygon></gml:surfaceMember></gml:MultiSurface></lod2MultiSurface>"
        val original = java.io.File("$fixtures/ASAM-UC_RoadShape.gml").readText()
        val file = kotlin.io.path.createTempFile(suffix = ".gml").toFile()
        file.writeText(original.replaceFirst("</lod2Solid>", multiSurfaceXml))
        val cityModel = read(file.path).getOrThrow()
        file.delete()
        val spaces = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(TrafficSpace::tryFrom) }.toList()
        assertEquals(2, spaces.size)
        assertEquals(null, spaces[1].lod2MultiSurface())

        val space = spaces[0]
        assertEquals(null, space.lod0MultiSurface())
        assertEquals(null, space.lod3MultiSurface())
        val multiSurface = assertNotNull(space.lod2MultiSurface()?.object_())
        assertEquals(39.0, multiSurface.area3d().getOrThrow(), 1e-9)
        assertNotNull(multiSurface.computeEnvelope())
        assertEquals(8, multiSurface.points().asSequence().count())

        val members = multiSurface.surfaceMember().asSequence().toList()
        assertEquals(1, members.size)
        val surface = assertNotNull(members.single()?.object_())
        assertEquals(GeometryType.Polygon, surface.geometryType())
        assertEquals("PolyID_space", surface.id()?.asStr())
        val polygon = assertNotNull(Polygon.tryFrom(surface))
        assertEquals(39.0, polygon.area3d().getOrThrow(), 1e-9)
        assertEquals(8, polygon.points().asSequence().count())
    }

    @Test
    fun trafficSpaceLod0Point() {
        val original = java.io.File("$fixtures/ASAM-UC_RoadShape.gml").readText()
        val file = kotlin.io.path.createTempFile(suffix = ".gml").toFile()
        file.writeText(original.replaceFirst("</lod2Solid>", "</lod2Solid><lod0Point><gml:Point gml:id=\"PointID_space\"><gml:pos srsDimension=\"3\">1.5 -2.5 3.25</gml:pos></gml:Point></lod0Point>"))
        val cityModel = read(file.path).getOrThrow()
        file.delete()
        val spaces = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(TrafficSpace::tryFrom) }.toList()
        assertEquals(2, spaces.size)
        assertEquals(null, spaces[1].lod0Point())

        val point = assertNotNull(spaces[0].lod0Point()?.object_())
        assertEquals("PointID_space", point.id()?.asStr())
        val pos = point.pos()
        assertEquals(listOf(1.5, -2.5, 3.25), listOf(pos.x(), pos.y(), pos.z()))
        assertEquals(1.5, assertNotNull(point.computeEnvelope()).lowerCorner().x())
    }

    @Test
    fun trafficAreas() {
        val cityModel = read("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow()
        val areas = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(TrafficArea::tryFrom) }.toList()
        assertEquals(2, areas.size)

        val area = areas.first()
        assertEquals(null, area.class_())
        assertEquals(listOf("1"), area.functions().asSequence().map { it!!.value() }.toList())
        assertEquals(listOf("2"), area.usages().asSequence().map { it!!.code().value() }.toList())
        assertEquals(null, area.surfaceMaterial())
        assertEquals(null, area.lod0MultiCurve())
        assertTrue(area.featureId().asStr().startsWith("UUID_8625bf6f"))
        assertEquals(listOf("Lane"), area.names().asSequence().map { it!!.value() }.toList())

        val totalArea = areas.sumOf { assertNotNull(it.lod2MultiSurface()?.object_()).area3d().getOrThrow() }
        assertEquals(282.1405004348745, totalArea, 1e-6)
    }

    @Test
    fun auxiliaryTrafficSpacesAndAreas() {
        val cityModel = read("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow()
        val features = cityModel.iterFeatures().asSequence().filterNotNull().toList()

        val spaces = features.mapNotNull(AuxiliaryTrafficSpace::tryFrom)
        assertEquals(2, spaces.size)
        for (space in spaces) {
            assertEquals(null, space.class_())
            assertEquals(0, space.functions().asSequence().count())
            assertEquals(GranularityValue.Lane, space.granularity())
            assertEquals(100.0, assertNotNull(space.lod2Solid()?.object_()).volume3d().getOrThrow(), 1e-6)
            assertEquals(40.0, assertNotNull(space.lod2MultiCurve()?.object_()).length3d().getOrThrow(), 1e-9)
        }

        val areas = features.mapNotNull(AuxiliaryTrafficArea::tryFrom)
        assertEquals(2, areas.size)
        for (area in areas) {
            assertEquals(null, area.class_())
            assertEquals(0, area.functions().asSequence().count())
            assertEquals(null, area.surfaceMaterial())
            assertEquals(listOf("Lane"), area.names().asSequence().map { it!!.value() }.toList())
            assertEquals(40.0, assertNotNull(area.lod2MultiSurface()?.object_()).area3d().getOrThrow(), 1e-6)
        }
    }

    @Test
    fun roadWithSection() {
        val cityModel = read("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow()
        val road = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Road::tryFrom) })
        assertEquals(null, road.class_())
        assertEquals(0, road.intersections().asSequence().count())
        assertEquals(0, road.trafficSpaces().asSequence().count())

        val sections = road.sections().asSequence().toList()
        assertEquals(1, sections.size)
        val section = assertNotNull(sections.single()?.object_())
        assertEquals(2, section.trafficSpaces().asSequence().count())
        val volume = section.auxiliaryTrafficSpaces().asSequence().sumOf {
            assertNotNull(it?.object_()?.lod2Solid()?.object_()).volume3d().getOrThrow()
        }
        assertEquals(200.0, volume, 1e-6)
    }

    @Test
    fun roadWithSectionsIntersectionAndMarkings() {
        val cityModel = read("$fixtures/ASAM-Ex_Bidirectional_Junction.gml").getOrThrow()
        val road = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Road::tryFrom) })
        val sections = road.sections().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(listOf(2, 1, 1), sections.map { it.trafficSpaces().asSequence().count() })
        val markings = sections.first().markings().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(4, markings.size)
        assertTrue(markings.all { it.class_() == null })

        val intersections = road.intersections().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(1, intersections.size)
        assertEquals(3, intersections.single().trafficSpaces().asSequence().count())
    }

    @Test
    fun building() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        assertEquals("1000", building.class_()?.value())
        assertEquals(listOf("1000"), building.functions().asSequence().map { it!!.value() }.toList())
        assertEquals("1030", building.roofType()?.value())
        assertEquals(2L, building.storeysAboveGround())
        assertEquals(0L, building.storeysBelowGround())

        assertEquals(2020, building.dateOfConstruction()?.year())
        assertEquals(null, building.dateOfDemolition())
        val height = assertNotNull(building.heights().asSequence().single())
        assertEquals("topOfConstruction", height.highReference().value())
        assertEquals(HeightStatusValue.Measured, height.status())
        assertEquals(6.52, height.length().value())
        assertEquals("m", height.length().uom())

        assertEquals(782.1228, assertNotNull(building.lod1Solid()?.object_()).volume3d().getOrThrow(), 1e-6)
        assertEquals(0, building.buildingParts().asSequence().count())
    }

    @Test
    fun wallRoofAndGroundSurfaces() {
        val cityModel = read("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val features = cityModel.iterFeatures().asSequence().filterNotNull().toList()

        val walls = features.mapNotNull(WallSurface::tryFrom)
        assertEquals(
            listOf("Outer Wall 1 (West)", "Outer Wall 2 (South)", "Outer Wall 3 (East)", "Outer Wall 4 (North)"),
            walls.map { it.names().asSequence().first()!!.value() },
        )
        val wallArea = walls.sumOf { assertNotNull(it.lod2MultiSurface()?.object_()).area3d().getOrThrow() }
        assertEquals(188.62887820601463, wallArea, 1e-6)

        val roofs = features.mapNotNull(RoofSurface::tryFrom)
        assertEquals(2, roofs.size)
        val roofArea = roofs.sumOf { assertNotNull(it.lod2MultiSurface()?.object_()).area3d().getOrThrow() }
        assertEquals(138.56406460961398, roofArea, 1e-6)

        val ground = features.mapNotNull(GroundSurface::tryFrom).single()
        assertEquals("Base Surface", ground.names().asSequence().first()!!.value())
        assertEquals(120.0, assertNotNull(ground.lod2MultiSurface()?.object_()).area3d().getOrThrow(), 1e-6)
    }

    @Test
    fun doorAndWindowSurfaces() {
        val cityModel = read("$fixtures/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val features = cityModel.iterFeatures().asSequence().filterNotNull().toList()

        val doors = features.mapNotNull(DoorSurface::tryFrom)
        assertEquals(listOf("Door West", "Door South"), doors.map { it.names().asSequence().first()!!.value() })
        val doorArea = doors.sumOf { assertNotNull(it.lod3MultiSurface()?.object_()).area3d().getOrThrow() }
        assertEquals(6.803850099444389, doorArea, 1e-6)
        assertEquals(11, features.mapNotNull(WindowSurface::tryFrom).size)

        val west = features.mapNotNull(WallSurface::tryFrom)
            .first { it.names().asSequence().first()!!.value() == "Outer Wall 1 (West)" }
        val fillings = west.fillingSurfaces().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(
            listOf(
                FeatureType.WindowSurface to "Window Round",
                FeatureType.WindowSurface to "Window North",
                FeatureType.DoorSurface to "Door West",
                FeatureType.WindowSurface to "Window South",
            ),
            fillings.map { it.featureType() to it.names().asSequence().first()!!.value() },
        )
    }

    @Test
    fun spaceBoundaries() {
        val cityModel = read("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        val boundaries = building.boundaries().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(7, boundaries.size)
        assertEquals(2, boundaries.count { it.featureType() == FeatureType.RoofSurface })
        val walls = boundaries.mapNotNull { WallSurface.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(it)) }
        assertEquals(4, walls.size)
        val wallArea = walls.sumOf { assertNotNull(it.lod2MultiSurface()?.object_()).area3d().getOrThrow() }
        assertEquals(188.62887820601463, wallArea, 1e-6)
    }

    @Test
    fun envelopeVolumeAndContains() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val envelope = assertNotNull(cityModel.boundedBy()?.envelope())
        assertEquals(782.12028, envelope.volume(), 1e-6)
        assertTrue(envelope.contains(envelope.lowerCorner()))
        assertTrue(envelope.contains(envelope.upperCorner()))
        assertTrue(!envelope.contains(DirectPosition.create(457848.0, 5439088.0, 118.4).getOrThrow()))
    }

    @Test
    fun levelOfDetail() {
        assertEquals(2uL, LevelOfDetail.Two.asIndex())
        assertEquals(LevelOfDetail.Three, LevelOfDetail.tryFrom(3u.toUByte()).getOrThrow())
        assertEquals(ErrorKind.InvalidArgument, assertIs<Error>(LevelOfDetail.tryFrom(4u.toUByte()).exceptionOrNull()).kind())
    }

    @Test
    fun solidShellPolygonsAndLinearRings() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        val solid = assertNotNull(building.lod1Solid()?.object_())
        assertEquals(0, solid.interior().asSequence().count())
        val shell = assertNotNull(solid.exterior())
        val polygons = shell.members().asSequence().map { assertNotNull(Polygon.tryFrom(assertNotNull(it?.object_()))) }.toList()
        assertEquals(6, polygons.size)
        for (polygon in polygons) {
            assertEquals(0, polygon.interior().asSequence().count())
            val ring = assertNotNull(LinearRing.tryFrom(assertNotNull(polygon.exterior())))
            assertEquals(4, ring.points().asSequence().count())
        }
        assertEquals(782.1228, shell.volume3d().getOrThrow(), 1e-6)
    }

    @Test
    fun gmlWriterRoundTrips() {
        val model = read("$fixtures/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val features = model.iterFeatures().asSequence().count()
        for (format in listOf(CitygmlFormat.Gml, CitygmlFormat.GmlGz, CitygmlFormat.GmlZst)) {
            val writer = GmlWriter.create(format)
            writer.withFormatting(Formatting.indent(' '.code.toUByte(), 2uL))
            writer.finish(model).getOrThrow()
            val written = GmlReader.create(writer.data(), format).finish().getOrThrow()
            assertEquals(features, written.iterFeatures().asSequence().count())
            assertTrue(writer.finish(model).isFailure)
        }

        val file = kotlin.io.path.createTempFile(suffix = ".gml.zst").toFile()
        GmlWriter.fromPath(file.path).getOrThrow().finish(model).getOrThrow()
        assertEquals(features, read(file.path).getOrThrow().iterFeatures().asSequence().count())
        file.delete()
    }

    @Test
    fun solidTriangulation() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        val triangulation = assertNotNull(building.lod1Solid()?.object_()).triangulate().getOrThrow()
        assertTrue(!triangulation.hasSkipped())
        assertEquals(12, triangulation.surface().triangles().asSequence().count())
        assertEquals(526.77836, triangulation.surface().area3d().getOrThrow(), 1e-3)
    }

    /** A model with the FZK LoD2 header and `member` as its only city object (no fixture has one). */
    private fun readMember(member: String): CityModel {
        val text = java.io.File("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").readText()
        val content = text.substring(0, text.indexOf("<cityObjectMember>")) + member
        return GmlReader.create(content.toByteArray().toUByteArray(), CitygmlFormat.Gml).finish().getOrThrow()
    }

    @Test
    fun bridgeAndTunnel() {
        val bridges = readMember(
            """<cityObjectMember><brid:Bridge gml:id="bridge_1"><brid:class>1000</brid:class>""" +
                """<brid:isMovable>true</brid:isMovable><brid:bridgePart><brid:BridgePart gml:id="bridge_part_1">""" +
                """<brid:isMovable>false</brid:isMovable></brid:BridgePart></brid:bridgePart></brid:Bridge>""" +
                """</cityObjectMember></CityModel>""",
        )
        // No isMovable() in Kotlin: diplomat-tool 0.16 generates invalid Kotlin for an Option<bool> return.
        val bridge = assertNotNull(bridges.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Bridge::tryFrom) })
        assertEquals("1000", bridge.class_()?.value())
        val part = assertNotNull(bridge.bridgeParts().asSequence().single()?.object_())
        assertEquals("bridge_part_1", part.featureId().asStr())

        val tunnels = readMember(
            """<cityObjectMember><tun:Tunnel gml:id="tunnel_1"><tun:function>1010</tun:function><tun:tunnelPart>""" +
                """<tun:TunnelPart gml:id="tunnel_part_1"><tun:function>1030</tun:function></tun:TunnelPart>""" +
                """</tun:tunnelPart></tun:Tunnel></cityObjectMember></CityModel>""",
        )
        val tunnel = assertNotNull(tunnels.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Tunnel::tryFrom) })
        assertEquals(listOf("1010"), tunnel.functions().asSequence().map { it!!.value() }.toList())
        val tunnelPart = assertNotNull(tunnel.tunnelParts().asSequence().single()?.object_())
        assertEquals(listOf("1030"), tunnelPart.functions().asSequence().map { it!!.value() }.toList())
    }

    /** Reads FZK LoD2 with `from` replaced by `to` (no fixture has subdivisions or implicit geometry). */
    private fun readLod2Modified(from: String, to: String): CityModel {
        val text = java.io.File("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").readText()
        val content = text.replaceFirst(from, to)
        return GmlReader.create(content.toByteArray().toUByteArray(), CitygmlFormat.Gml).finish().getOrThrow()
    }

    @Test
    fun buildingSubdivisions() {
        val anchor = "<bldg:storeysBelowGround>0</bldg:storeysBelowGround>"
        val cityModel = readLod2Modified(
            anchor,
            anchor + """<bldg:buildingSubdivision><bldg:Storey gml:id="storey_ground"><bldg:class>ground</bldg:class>""" +
                """<bldg:function>living</bldg:function></bldg:Storey></bldg:buildingSubdivision>""" +
                """<bldg:buildingSubdivision><bldg:BuildingUnit gml:id="unit_1"><bldg:usage>residential</bldg:usage>""" +
                """</bldg:BuildingUnit></bldg:buildingSubdivision>""",
        )
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        val subdivisions = building.buildingSubdivisions().asSequence().map { assertNotNull(it?.object_()) }.toList()
        assertEquals(listOf(FeatureType.Storey, FeatureType.BuildingUnit), subdivisions.map { it.featureType() })
        assertEquals("ground", subdivisions[0].class_()?.value())
        assertEquals(listOf("living"), subdivisions[0].functions().asSequence().map { it!!.value() }.toList())
        assertEquals(listOf("residential"), subdivisions[1].usages().asSequence().map { it!!.value() }.toList())
        val storey = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Storey::tryFrom) })
        assertEquals("storey_ground", storey.featureId().asStr())
        val unit = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(BuildingUnit::tryFrom) })
        assertEquals("unit_1", unit.featureId().asStr())
    }

    @Test
    fun terrainIntersectionCurveAndImplicitRepresentation() {
        val cityModel = readLod2Modified(
            "</lod2Solid>",
            "</lod2Solid>" +
                "<lod2TerrainIntersectionCurve><gml:MultiCurve><gml:curveMember><gml:LineString>" +
                "<gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>" +
                "</gml:LineString></gml:curveMember></gml:MultiCurve></lod2TerrainIntersectionCurve>" +
                """<lod1ImplicitRepresentation><ImplicitGeometry gml:id="tree_prototype">""" +
                "<transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>" +
                "<mimeType>model/gltf+json</mimeType>" +
                "<referencePoint><gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point></referencePoint>" +
                "<relativeGeometry><gml:Point><gml:pos>0 0 0</gml:pos></gml:Point></relativeGeometry>" +
                "</ImplicitGeometry></lod1ImplicitRepresentation>",
        )
        val building = assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        assertEquals(null, building.lod1TerrainIntersectionCurve())
        val curve = assertNotNull(building.lod2TerrainIntersectionCurve()?.object_())
        assertEquals(12.0, curve.length3d().getOrThrow(), 1e-9)

        val implicit = assertNotNull(building.lod1ImplicitRepresentation()?.object_())
        assertEquals("tree_prototype", implicit.objectId().asStr())
        assertEquals("model/gltf+json", implicit.mimeType()?.value())
        assertEquals(null, implicit.libraryObject())
        assertEquals(112.0, assertNotNull(implicit.referencePoint().object_()).pos().z())
        val matrix = implicit.transformationMatrix()
        assertEquals(10.0, matrix.get(0uL, 3uL).getOrThrow())
        assertEquals(3.0, matrix.get(2uL, 2uL).getOrThrow())
        assertTrue(matrix.get(4uL, 0uL).isFailure)

        val geometry = assertNotNull(implicit.relativeGeometry()?.object_())
        assertEquals(GeometryType.Point, geometry.geometryType())
        assertEquals(0.0, assertNotNull(Point.tryFrom(geometry)).pos().x())
        assertEquals(null, MultiSurface.tryFrom(geometry))
    }

    @Test
    fun iterCityObjects() {
        val cityModel = read("$fixtures/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val types = cityModel.iterCityObjects().asSequence().map { it!!.featureType() }.toList()
        assertTrue(FeatureType.CityModel !in types)
        assertEquals(1, types.count { it == FeatureType.Building })
        assertEquals(4, types.count { it == FeatureType.WallSurface })

        val junction = read("$fixtures/ASAM-Ex_Bidirectional_Junction.gml").getOrThrow()
        val first = assertNotNull(junction.iterCityObjects().next())
        val road = assertNotNull(Road.tryFrom(AbstractFeatureKindRef.fromCityObject(first)))
        assertEquals("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", road.featureId().asStr())
    }

    @Test
    fun recomputeChildBoundingShapes() {
        val reader = GmlReader.fromPath("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        reader.withRebuildObjectBounds(false)
        val cityModel = reader.finish().getOrThrow()
        fun wallBounded() = cityModel.iterFeatures().asSequence()
            .firstNotNullOf { it?.let(WallSurface::tryFrom) }.boundedBy() != null
        assertTrue(!wallBounded())
        cityModel.recomputeChildBoundingShapes()
        assertTrue(wallBounded())
    }

    @Test
    fun applyTranslationAndScale() {
        val cityModel = read("$fixtures/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        fun envelope() = assertNotNull(assertNotNull(cityModel.boundedBy()).envelope())
        val lower = envelope().lowerCorner()
        val (x, y, z) = Triple(lower.x(), lower.y(), lower.z())

        cityModel.applyTranslation(Vector3(-100.0, 200.0, 10.0))
        val moved = envelope().lowerCorner()
        assertEquals(x - 100.0, moved.x(), 1e-6)
        assertEquals(y + 200.0, moved.y(), 1e-6)
        assertEquals(z + 10.0, moved.z(), 1e-6)

        cityModel.applyScale(Scale3(2.0, 3.0, 0.5))
        assertEquals(24.0, envelope().sizeX(), 1e-6)
        assertEquals(30.0, envelope().sizeY(), 1e-6)
        assertEquals(6.517669 / 2, envelope().sizeZ(), 1e-6)
    }

    @Test
    fun vegetationCityFurnitureAndRelief() {
        val vegetation = readMember(
            """<cityObjectMember><veg:SolitaryVegetationObject gml:id="tree_1"><veg:class>1000</veg:class>""" +
                """<veg:species>Quercus robur</veg:species><veg:height uom="m">12.5</veg:height>""" +
                """</veg:SolitaryVegetationObject></cityObjectMember><cityObjectMember><veg:PlantCover gml:id="cover_1">""" +
                """<veg:averageHeight uom="m">2.5</veg:averageHeight></veg:PlantCover></cityObjectMember>""" +
                """<cityObjectMember><frn:CityFurniture gml:id="sign_1"><frn:function>1080</frn:function>""" +
                """</frn:CityFurniture></cityObjectMember></CityModel>""",
        )
        val tree = assertNotNull(vegetation.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(SolitaryVegetationObject::tryFrom) })
        assertEquals("1000", tree.class_()?.value())
        assertEquals("Quercus robur", tree.species()?.value())
        assertEquals(12.5, tree.height()?.value())
        val cover = assertNotNull(vegetation.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(PlantCover::tryFrom) })
        assertEquals(2.5, cover.averageHeight()?.value())
        val furniture = assertNotNull(vegetation.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(CityFurniture::tryFrom) })
        assertEquals(listOf("1080"), furniture.functions().asSequence().map { it!!.value() }.toList())

        val relief = readMember(
            """<cityObjectMember><dem:ReliefFeature gml:id="relief_1"><dem:lod>2</dem:lod><dem:reliefComponent>""" +
                """<dem:TINRelief gml:id="tin_1"><dem:lod>1</dem:lod><dem:tin><gml:TriangulatedSurface><gml:patches>""" +
                """<gml:Triangle><gml:exterior><gml:LinearRing><gml:posList>0 0 0 1 0 0 0 1 0 0 0 0</gml:posList>""" +
                """</gml:LinearRing></gml:exterior></gml:Triangle></gml:patches></gml:TriangulatedSurface></dem:tin>""" +
                """</dem:TINRelief></dem:reliefComponent></dem:ReliefFeature></cityObjectMember></CityModel>""",
        )
        val reliefFeature = assertNotNull(relief.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(ReliefFeature::tryFrom) })
        assertEquals(LevelOfDetail.Two, reliefFeature.lod())
        val component = assertNotNull(reliefFeature.reliefComponents().asSequence().single()?.object_())
        assertEquals(FeatureType.TinRelief, component.featureType())
        assertEquals(LevelOfDetail.One, component.lod())
        val tin = assertNotNull(relief.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(TinRelief::tryFrom) })
        assertEquals(1, assertNotNull(tin.tin()?.object_()).triangles().asSequence().count())
    }

    @Test
    fun genericAttributesAndExternalReferences() {
        val fzk = read("$fixtures/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml").getOrThrow()
        val building = assertNotNull(fzk.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        val attributes = building.genericAttributes().asSequence().map { it!! }.toList()
        assertEquals(listOf("GrossPlannedArea", "ConstructionMethod", "IsLandmarked"), attributes.map { it.name() })
        val measure = assertNotNull(MeasureAttribute.tryFrom(attributes[0]))
        assertEquals(120.0, measure.value().value())
        assertEquals("m2", measure.value().uom())
        assertEquals("New Building", attributes[1].asString()?.value())
        assertEquals(0, building.externalReferences().asSequence().count())

        val tum = read("$fixtures/TUM-Main-Entrance.gml").getOrThrow()
        val tumBuilding = assertNotNull(tum.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })
        assertEquals("DEBYvAAAAABTMIyA", tumBuilding.externalReferences().asSequence().single()?.targetResource())
    }

    @Test
    fun trafficSpaces() {
        val cityModel = read("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow()
        val spaces = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(TrafficSpace::tryFrom) }.toList()
        assertEquals(2, spaces.size)
        assertEquals(
            setOf(TrafficDirectionValue.Forwards, TrafficDirectionValue.Backwards),
            spaces.map { it.trafficDirection() }.toSet(),
        )

        val space = spaces.first()
        assertEquals(GranularityValue.Lane, space.granularity())
        assertEquals(listOf("1"), space.functions().asSequence().map { it!!.value() }.toList())
        assertEquals(listOf("2"), space.usages().asSequence().map { it!!.code().value() }.toList())
        assertEquals(SpaceType.Open, space.spaceType())
        assertEquals(null, space.class_())
    }

    @Test
    fun totalTrafficSpaceVolume() {
        // The traffic-space analysis of the original Python example, with the generated API.
        val cityModel = GmlReader.fromPath("$fixtures/ASAM-UC_RoadShape.gml").getOrThrow().finish().getOrThrow()
        var totalVolume = 0.0
        for (feature in cityModel.iterFeatures()) {
            val solid = feature?.let(TrafficSpace::tryFrom)?.lod2Solid()?.object_() ?: continue
            totalVolume += solid.volume3d().getOrThrow()
        }
        assertEquals(1260.0, totalVolume, 1e-6)
    }

    @Test
    fun dateAndDateTimeFromParts() {
        val dateTime = DateTime.fromParts(2017, 1u, 23u, 13u, 14u, 15u, 0u, -7200).getOrThrow()
        assertEquals(13u, dateTime.hour())
        assertEquals(-7200, dateTime.offsetSeconds())
        assertEquals("2017-01-23T13:14:15-02:00", dateTime.toRfc3339())

        val date = Date.fromParts(2020, 1u, 2u, 3600).getOrThrow()
        assertEquals("2020-01-02T00:00:00+01:00", date.startOfDay().toRfc3339())
        assertEquals(ErrorKind.InvalidArgument, assertIs<Error>(Date.fromParts(2021, 2u, 30u, 0).exceptionOrNull()).kind())
    }
}
