package io.github.tum_gis.ecitygml.examples.snippets

import io.github.tum_gis.ecitygml.GmlReader
import io.github.tum_gis.ecitygml.GmlWriter
import io.github.tum_gis.ecitygml.Vector3
import java.util.Locale

fun main(args: Array<String>) {
    val inputPath = args.getOrElse(0) { "model.gml" }
    val outputPath = args.getOrElse(1) { "model_local.gml" }

    // Parse the CityGML document, keeping the envelopes of the objects as
    // given in the file instead of recomputing them from their geometry
    val reader = GmlReader.fromPath(inputPath).getOrThrow()
    reader.withRebuildObjectBounds(false)
    val cityModel = reader.finish().getOrThrow()

    // Move the center of the city model's envelope to the origin
    val envelope = checkNotNull(cityModel.boundedBy()?.envelope()) {
        "the city model has no envelope"
    }
    val center = envelope.center()
    val offset = Vector3(-center.x(), -center.y(), -center.z())
    cityModel.applyTranslation(offset)

    // Write the translated city model as a CityGML document
    GmlWriter.fromPath(outputPath).getOrThrow()
        .finish(cityModel).getOrThrow()

    val message = "Translated the city model by (%.3f, %.3f, %.3f) " +
        "to local coordinates"
    println(message.format(Locale.ROOT, offset.x, offset.y, offset.z))
}
