// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`: `fromPath` creates the output file and picks the format from its
// extension (`.gml`, `.gml.gz` or `.gml.zst`), `withFormatting` sets the layout (here indented by two
// spaces; `Formatting.compact()` writes no line breaks at all), and `finish` writes the city model.
// Reading the written file back verifies the result.
//
// Usage: gradle run07Convert --args="input.gml output.gml.gz"
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("ConvertKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.CityModel
import io.github.tum_gis.ecitygml.Formatting
import io.github.tum_gis.ecitygml.GmlWriter
import kotlin.system.exitProcess

private const val INDENT_SIZE = 2

private fun summary(cityModel: CityModel) =
    "${cityModel.cityObjectsLen()} city object members, ${cityModel.iterCityObjects().asSequence().count()} city objects"

/** What `GmlWriter.fromPath` writes for this path (it fails for other extensions). */
private fun formatName(path: String) = when {
    path.endsWith(".gml.gz") -> "gzip-compressed CityGML"
    path.endsWith(".gml.zst") -> "zstd-compressed CityGML"
    else -> "CityGML"
}

fun runConvert(args: Array<String>): Int {
    if (args.size != 2) {
        System.err.println("usage: 07_convert input.gml output.gml[.gz|.zst]")
        return 2
    }
    val (inputPath, outputPath) = args
    val cityModel = readCityModel(inputPath) ?: return 1
    println("Read: ${summary(cityModel)}")

    val written = GmlWriter.fromPath(outputPath).mapCatching { writer ->
        writer.withFormatting(Formatting.indent(' '.code.toUByte(), INDENT_SIZE.toULong()))
        writer.finish(cityModel).getOrThrow()
    }
    written.onFailure {
        System.err.println("error: ${errorText(it)}")
        return 1
    }
    println("Wrote: ${formatName(outputPath)}, indented by $INDENT_SIZE spaces")

    val readBack = readCityModel(outputPath) ?: return 1
    println("Read back: ${summary(readBack)}")
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runConvert(args))
}
