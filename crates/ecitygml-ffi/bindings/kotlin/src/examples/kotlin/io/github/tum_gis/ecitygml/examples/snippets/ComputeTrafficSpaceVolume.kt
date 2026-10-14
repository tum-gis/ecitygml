package io.github.tum_gis.ecitygml.examples.snippets

import io.github.tum_gis.ecitygml.GmlReader
import io.github.tum_gis.ecitygml.TrafficSpace
import java.util.Locale

fun main(args: Array<String>) {
    val path = args.firstOrNull() ?: "model.gml"

    // Parse the CityGML document into the in-memory city model
    val cityModel = GmlReader.fromPath(path).getOrThrow()
        .finish().getOrThrow()

    // Traverse all features and keep only those that are traffic
    // spaces, using a type-safe conversion that skips all other
    // feature types
    val trafficSpaces = cityModel.iterFeatures()
        .asSequence()
        .mapNotNull { it?.let(TrafficSpace::tryFrom) }
        .toList()

    // Compute the volumes of the LOD2 solids and sum them up; spaces
    // without an LOD2 solid, or whose volume cannot be computed, count
    // as zero
    val total = trafficSpaces.sumOf { space ->
        space.lod2Solid()
            ?.object_()
            ?.volume3d()
            ?.getOrNull()
            ?: 0.0
    }

    val message = "Total volume of traffic spaces (LoD2): %.3f m^3"
    println(message.format(Locale.ROOT, total))
}
