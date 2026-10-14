package io.github.tum_gis.ecitygml.examples.snippets

import io.github.tum_gis.ecitygml.AbstractCityObjectKindRef
import io.github.tum_gis.ecitygml.AbstractFeatureKindRef
import io.github.tum_gis.ecitygml.Building
import io.github.tum_gis.ecitygml.GmlReader
import io.github.tum_gis.ecitygml.HeightStatusValue
import java.util.Locale

fun main(args: Array<String>) {
    val path = args.firstOrNull() ?: "model.gml"

    // Parse the CityGML document into the in-memory city model
    val cityModel = GmlReader.fromPath(path).getOrThrow()
        .finish().getOrThrow()

    // Sum up the measured heights of the top-level buildings; only heights
    // from the lowest ground point to the top of construction given in
    // meters are taken into account
    val totalHeight = cityModel.cityObjectMembers().asSequence()
        .mapNotNull { it?.object_() }
        .map { AbstractCityObjectKindRef.fromCityObject(it) }
        .map { AbstractFeatureKindRef.fromCityObject(it) }
        .mapNotNull { Building.tryFrom(it) }
        .flatMap { it.heights().asSequence().filterNotNull() }
        .filter {
            it.lowReference().value() == "lowestGroundPoint" &&
                it.highReference().value() == "topOfConstruction" &&
                it.status() == HeightStatusValue.Measured &&
                it.length().uom() == "urn:adv:uom:m"
        }
        .sumOf { it.length().value() }

    val message = "Total measured height of buildings: %.3f m"
    println(message.format(Locale.ROOT, totalHeight))
}
