// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
// those walls, and so on. `iterFeatures()` visits all of them, depth first in document order, as
// `AbstractFeatureKindRef`s. Each tells its `featureType()`; to use the getters of its concrete
// type, convert it with that type's `tryFrom`, which returns null for other types.
//
// Usage: gradle run02ListFeatures --args="path/to/model.gml"
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Feature type              Count
//     CityModel                     1
//     Building                      1
//     WallSurface                   4
//     ...
//     Total                        22
//
//     Buildings:
//       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("ListFeaturesKt")

package space.envis.ecitygml.examples

import space.envis.ecitygml.Building
import kotlin.system.exitProcess

private fun row(name: String, count: Any) = println(String.format("%-24s %6s", name, count))

fun runListFeatures(args: Array<String>): Int {
    if (args.size != 1) {
        System.err.println("usage: 02_list_features path/to/model.gml")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1

    // Count the features per type, in the order the types first appear (`groupingBy` keeps the
    // order); a Kotlin enum's `name` is the type's name.
    val counts = cityModel.iterFeatures().asSequence().filterNotNull()
        .groupingBy { it.featureType().name }
        .eachCount()

    row("Feature type", "Count")
    for ((name, count) in counts) {
        row(name, count)
    }
    row("Total", counts.values.sum())

    // `Building.tryFrom` turns a feature into a `Building` (or null).
    println()
    println("Buildings:")
    for (building in cityModel.iterFeatures().asSequence().mapNotNull { it?.let(Building::tryFrom) }) {
        println("  ${building.featureId().asStr()}")
    }
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runListFeatures(args))
}
