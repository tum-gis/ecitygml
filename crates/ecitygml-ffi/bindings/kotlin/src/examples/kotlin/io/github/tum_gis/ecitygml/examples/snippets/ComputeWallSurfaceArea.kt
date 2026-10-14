package io.github.tum_gis.ecitygml.examples.snippets

import io.github.tum_gis.ecitygml.GmlReader
import io.github.tum_gis.ecitygml.WallSurface
import java.util.Locale

fun main(args: Array<String>) {
    val path = args.firstOrNull() ?: "model.gml"

    // Parse the CityGML document into the in-memory city model
    val cityModel = GmlReader.fromPath(path).getOrThrow()
        .finish().getOrThrow()

    // Sum up the areas of the LOD2 multi-surfaces of all wall surfaces;
    // other feature types and walls without an LOD2 multi-surface are
    // skipped
    var totalArea = 0.0
    for (feature in cityModel.iterFeatures()) {
        val wall = feature?.let(WallSurface::tryFrom) ?: continue
        val surface = wall.lod2MultiSurface()?.object_() ?: continue
        totalArea += surface.area3d().getOrThrow()
    }

    val message = "Total area of wall surfaces (LoD2): %.3f m^2"
    println(message.format(Locale.ROOT, totalArea))
}
