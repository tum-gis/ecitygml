@file:OptIn(ExperimentalUnsignedTypes::class)

package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import java.io.File
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertTrue

// The cases of crates/ecitygml/tests/api/writer.md.

private val model by lazy { read(fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")) }

private fun assertReadsBack(file: File) = assertEquals(featureTypes(model), featureTypes(read(file.path)), file.path)

/** The model written as `Gml` text. */
private fun text(formatting: Formatting? = null): String {
    val writer = GmlWriter.create(CitygmlFormat.Gml)
    formatting?.let(writer::withFormatting)
    writer.finish(model).getOrThrow()
    return writer.data().toByteArray().decodeToString()
}

private const val FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"

/** A city model written as `Gml` text. */
private fun textOf(cityModel: CityModel): String {
    val writer = GmlWriter.create(CitygmlFormat.Gml)
    writer.finish(cityModel).getOrThrow()
    return writer.data().toByteArray().decodeToString()
}

/** The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order. */
private fun wallCoordinates(cityModel: CityModel): List<Triple<Double, Double, Double>> =
    cityModel.iterFeatures().asSequence()
        .mapNotNull { WallSurface.tryFrom(it!!)?.lod2MultiSurface()?.object_() }
        .flatMap { it.surfaceMember().asSequence() }
        .mapNotNull { member -> member?.object_()?.let(Polygon::tryFrom) }
        .flatMap { polygon -> LinearRing.tryFrom(polygon.exterior()!!)!!.points().asSequence() }
        .map { Triple(it!!.x(), it.y(), it.z()) }
        .toList()

private fun indent(char: Char, size: Int) = Formatting.indent(char.code.toUByte(), size.toULong())

class WriterTest {
    @Test
    fun writerInMemory() {
        for (format in listOf(CitygmlFormat.Gml, CitygmlFormat.GmlGz, CitygmlFormat.GmlZst)) {
            val writer = GmlWriter.create(format)
            assertTrue(writer.data().isEmpty())
            writer.finish(model).getOrThrow()
            assertEquals(featureTypes(model), featureTypes(readData(writer.data(), format)), "$format")
        }
        assertTrue(text().contains("<bldg:Building"))
    }

    @Test
    fun writerFiles() = withTempDir { dir ->
        for (name in listOf("out.gml", "out.gml.gz", "out.gml.zst")) {
            val file = dir.resolve(name)
            GmlWriter.fromPath(file.path).getOrThrow().finish(model).getOrThrow()
            assertReadsBack(file)
        }
    }

    @Test
    fun writerOverwritesFile() = withTempDir { dir ->
        val file = dir.resolve("out.gml")
        file.writeText("x".repeat(100_000))
        GmlWriter.fromPath(file.path).getOrThrow().finish(model).getOrThrow()
        assertReadsBack(file)
    }

    @Test
    fun writerBasePathWithFormat() = withTempDir { dir ->
        dir.resolve("out.gml.gz").writeText("x".repeat(100_000))
        GmlWriter.fromBasePathWithFormat(dir.resolve("out").path, CitygmlFormat.GmlGz).getOrThrow().finish(model).getOrThrow()
        assertReadsBack(dir.resolve("out.gml.gz"))
    }

    @Test
    fun writerFormatting() {
        val default = text()
        assertTrue(default.lines().size > 1)
        assertFalse(default.lines().any { it.startsWith(' ') || it.startsWith('\t') })
        assertEquals(default, text(Formatting.newLine()))
        assertEquals(default, text(indent(' ', 0)))

        assertTrue(text(Formatting.compact()).lines().size < default.lines().size)

        val spaces = text(indent(' ', 2)).lines()
        assertTrue(spaces.any { it.startsWith("  <") })
        assertFalse(spaces.any { it.startsWith('\t') })

        val tabs = text(indent('\t', 1))
        assertTrue(tabs.lines().any { it.startsWith("\t<") })
        assertEquals(featureTypes(model), featureTypes(readData(tabs.encodeToByteArray().toUByteArray(), CitygmlFormat.Gml)))
    }

    @Test
    fun writerFinishOnce() {
        val writer = GmlWriter.create(CitygmlFormat.Gml)
        writer.finish(model).getOrThrow()
        assertError(writer.finish(model), ErrorKind.InvalidArgument, "already finished")
    }

    @Test
    fun writerUnsupportedExtension() = withTempDir { dir ->
        assertError(GmlWriter.fromPath(dir.resolve("out.txt").path), ErrorKind.InvalidArgument, "txt")
    }

    @Test
    fun writerMissingDirectory() = withTempDir { dir ->
        assertError(GmlWriter.fromPath(dir.resolve("missing/out.gml").path), ErrorKind.Io, "")
    }

    @Test
    fun writerKeepsReferences() {
        val text = textOf(read(fixture(FZK_LOD2)))
        assertEquals(1, text.split("xlink:href=\"#PolyID7350_878_759628_120742\"").size - 1)
        assertEquals(1, text.split("gml:id=\"PolyID7350_878_759628_120742\"").size - 1)
    }

    @Test
    fun writerPreservesCoordinates() {
        val cityModel = read(fixture(FZK_LOD2))
        val written = readData(textOf(cityModel).toByteArray().toUByteArray(), CitygmlFormat.Gml)
        val coordinates = wallCoordinates(cityModel)
        assertTrue(coordinates.isNotEmpty())
        assertEquals(coordinates, wallCoordinates(written))
    }
}
