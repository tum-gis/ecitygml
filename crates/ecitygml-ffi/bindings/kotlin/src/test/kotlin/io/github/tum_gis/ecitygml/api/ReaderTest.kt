@file:OptIn(ExperimentalUnsignedTypes::class)

package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import kotlin.test.Test
import kotlin.test.assertEquals

// The cases of crates/ecitygml/tests/api/reader.md.

private const val FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
private const val FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"

class ReaderTest {
    @Test
    fun readerFromBytes() {
        assertEquals(1uL, readData(bytes(fixture(FZK_LOD1)), CitygmlFormat.Gml).cityObjectsLen())
    }

    @Test
    fun readerCompressed() {
        for ((extension, format) in listOf("gz" to CitygmlFormat.GmlGz, "zst" to CitygmlFormat.GmlZst)) {
            val path = fixture("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.$extension")
            assertEquals(1uL, read(path).cityObjectsLen(), path)
            assertEquals(1uL, readData(bytes(path), format).cityObjectsLen(), path)
        }
    }

    @Test
    fun readerDefaultRebuildsObjectBounds() {
        val cityModel = read(fixture(FZK_LOD2))
        val walls = cityModel.iterFeatures().asSequence().mapNotNull { WallSurface.tryFrom(it!!) }.toList()
        assertEquals(List(4) { true }, walls.map { it.boundedBy() != null })
    }

    @Test
    fun readerFinishOnce() {
        val reader = GmlReader.fromPath(fixture(FZK_LOD1)).getOrThrow()
        reader.withRebuildObjectBounds(false)
        assertEquals(1uL, reader.finish().getOrThrow().cityObjectsLen())
        assertError(reader.finish(), ErrorKind.InvalidArgument, "already finished")
    }

    @Test
    fun readerMissingFile() {
        assertError(GmlReader.fromPath(fixture("does-not-exist.gml")), ErrorKind.Io, "No such file")
    }

    @Test
    fun readerUnsupportedExtension() {
        assertError(GmlReader.fromPath(fixture("README.md")), ErrorKind.InvalidArgument, "md")
    }

    @Test
    fun readerInvalidContent() {
        val reader = GmlReader.fromPath(fixture("invalid/unclosed-tag.gml")).getOrThrow()
        assertError(reader.finish(), ErrorKind.Parse, "tag not closed")
    }
}
