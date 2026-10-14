// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain,
// `.gml.gz` or `.gml.zst`) into a `CityModel`, which owns all features. Fallible calls return a
// Kotlin `Result`, whose failure is the ecitygml `Error` (an exception). Objects borrowed from the
// city model keep it alive; the garbage collector frees the native memory.
//
// Usage: gradle run01ReadCityModel --args="path/to/model.gml"
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     City object members: 1
//     City objects (at all depths): 8
//     Envelope:
//       lower corner: 457842.000, 5439083.000, 111.800
//       upper corner: 457854.000, 5439093.000, 118.318
//       size: 12.000 x 10.000 x 6.518

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("ReadCityModelKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.CityModel
import io.github.tum_gis.ecitygml.Error
import io.github.tum_gis.ecitygml.GmlReader
import java.util.Locale
import kotlin.system.exitProcess

/** Reads a city model, or prints the error and returns null. Shared by the examples. */
internal fun readCityModel(path: String): CityModel? =
    // `fromPath` opens the file and picks the format from its extension; `finish` parses it.
    GmlReader.fromPath(path).mapCatching { it.finish().getOrThrow() }.getOrElse { error ->
        // The bindings' Error is the exception; its text comes from `message()`.
        System.err.println("error: ${if (error is Error) error.message() else error.message}")
        null
    }

/** `%.3f`, independent of the default locale's decimal separator. */
internal fun fixed3(value: Double): String = String.format(Locale.ROOT, "%.3f", value)

/** Returns the exit code (separate from `main`, so tests can run it in the same JVM). */
fun runReadCityModel(args: Array<String>): Int {
    if (args.size != 1) {
        System.err.println("usage: 01_read_city_model path/to/model.gml")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1

    // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
    // doors and windows are city objects too, which `iterCityObjects()` visits as well.
    println("City object members: ${cityModel.cityObjectsLen()}")
    println("City objects (at all depths): ${cityModel.iterCityObjects().asSequence().count()}")

    // `boundedBy()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both
    // are optional (null when absent), as in the file.
    val envelope = cityModel.boundedBy()?.envelope()
    if (envelope == null) {
        println("Envelope: none")
        return 0
    }
    val (lower, upper) = envelope.lowerCorner() to envelope.upperCorner()
    println("Envelope:")
    println("  lower corner: ${fixed3(lower.x())}, ${fixed3(lower.y())}, ${fixed3(lower.z())}")
    println("  upper corner: ${fixed3(upper.x())}, ${fixed3(upper.y())}, ${fixed3(upper.z())}")
    println("  size: ${fixed3(envelope.sizeX())} x ${fixed3(envelope.sizeY())} x ${fixed3(envelope.sizeZ())}")
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runReadCityModel(args))
}
