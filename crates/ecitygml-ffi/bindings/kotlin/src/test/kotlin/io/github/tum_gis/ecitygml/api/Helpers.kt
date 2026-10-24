@file:OptIn(ExperimentalUnsignedTypes::class)

package io.github.tum_gis.ecitygml.api

import io.github.tum_gis.ecitygml.*
import java.io.File
import kotlin.test.assertEquals
import kotlin.test.assertIs
import kotlin.test.assertTrue

// Helpers of the API suite (crates/ecitygml/tests/api/README.md).

private val fixtures = System.getProperty("ecitygml.fixtures")

/** `tests/fixtures/<path>`. */
internal fun fixture(path: String) = "$fixtures/$path"

/** Reads the file at `path`. */
internal fun read(path: String): CityModel = GmlReader.fromPath(path).mapCatching { it.finish().getOrThrow() }.getOrThrow()

/** `GmlReader::new(data, format).finish()`. */
internal fun readData(data: UByteArray, format: CitygmlFormat): CityModel = GmlReader.create(data, format).finish().getOrThrow()

internal fun bytes(path: String): UByteArray = File(path).readBytes().toUByteArray()

internal fun featureTypes(cityModel: CityModel): List<FeatureType> =
    cityModel.iterFeatures().asSequence().map { it!!.featureType() }.toList()

/** Asserts that the result failed with an error of `kind` whose message contains `part`. */
internal fun assertError(result: Result<*>, kind: ErrorKind, part: String) {
    // The Rust `Error` is the exception; its text comes from `message()`.
    val error = assertIs<Error>(result.exceptionOrNull())
    assertEquals(kind, error.kind())
    assertTrue(error.message().contains(part), error.message())
}

/** A fresh temporary directory for `block`, removed afterwards. */
internal fun <T> withTempDir(block: (File) -> T): T {
    val dir = kotlin.io.path.createTempDirectory("ecitygml-kotlin-api-").toFile()
    try {
        return block(dir)
    } finally {
        dir.deleteRecursively()
    }
}
