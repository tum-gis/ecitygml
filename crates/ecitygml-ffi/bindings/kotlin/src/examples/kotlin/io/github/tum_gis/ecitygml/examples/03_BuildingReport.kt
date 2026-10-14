// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
// with their doors and windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are null when absent; lists are iterators (possibly empty), here turned into
//   sequences.
// - Code-list values (class, function, ...) are wrappers with `value()` (and `code()`).
// - Properties referencing other objects (e.g. a building's boundaries) have `object_()` and
//   `href()`; `object_()` is null if the property only references an object elsewhere via
//   `xlink:href`.
// - Abstract types are converted with `tryFrom`, e.g. a generic attribute to a `MeasureAttribute`,
//   or a boundary (via `AbstractFeatureKindRef.fromSpaceBoundary`) to a `WallSurface`.
//
// Usage: gradle run03BuildingReport --args="path/to/model.gml"
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       Name: AC14-FZK-Haus
//       Class: 1000
//       ...
//       Boundaries:
//         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//         ...

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("BuildingReportKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.AbstractFeatureKindRef
import io.github.tum_gis.ecitygml.AbstractFillingSurfacePropertyIterator
import io.github.tum_gis.ecitygml.Building
import io.github.tum_gis.ecitygml.GenericAttributeKind
import io.github.tum_gis.ecitygml.GroundSurface
import io.github.tum_gis.ecitygml.MeasureAttribute
import io.github.tum_gis.ecitygml.RoofSurface
import io.github.tum_gis.ecitygml.WallSurface
import kotlin.system.exitProcess

/** Values comma-separated, "-" if there are none. */
private fun joined(values: Sequence<String>): String = values.joinToString(", ").ifEmpty { "-" }

/** The value of a generic attribute: string, integer, double or measure (value and unit). */
private fun genericAttributeValue(attribute: GenericAttributeKind): String {
    attribute.asString()?.let { return it.value() }
    attribute.asInt()?.let { return it.value().toString() }
    attribute.asDouble()?.let { return fixed3(it.value()) }
    MeasureAttribute.tryFrom(attribute)?.let { return "${fixed3(it.value().value())} ${it.value().uom()}" }
    return "(not shown)" // e.g. a generic attribute set, which holds further attributes
}

/** Prints the doors and windows of a wall, roof or ground surface. */
private fun printFillingSurfaces(fillings: AbstractFillingSurfacePropertyIterator) {
    for (filling in fillings.asSequence().mapNotNull { it?.object_() }) {
        println("      ${filling.featureType().name} ${filling.featureId().asStr()}")
    }
}

private fun printBuilding(building: Building) {
    println("Building ${building.featureId().asStr()}")
    println("  Name: ${joined(building.names().asSequence().map { it!!.value() })}")
    println("  Class: ${building.class_()?.value() ?: "-"}")
    println("  Functions: ${joined(building.functions().asSequence().map { it!!.value() })}")
    println("  Usages: ${joined(building.usages().asSequence().map { it!!.value() })}")
    println("  Roof type: ${building.roofType()?.value() ?: "-"}")
    println("  Storeys above ground: ${building.storeysAboveGround() ?: "-"}")
    println("  Storeys below ground: ${building.storeysBelowGround() ?: "-"}")
    val date = building.dateOfConstruction()
    println("  Date of construction: ${date?.let { "%04d-%02d-%02d".format(it.year(), it.month().toInt(), it.day().toInt()) } ?: "-"}")

    println("  Heights:")
    for (height in building.heights().asSequence().filterNotNull()) {
        val length = height.length()
        println("    ${fixed3(length.value())} ${length.uom()} (${height.highReference().value()} to ${height.lowReference().value()})")
    }

    println("  Generic attributes:")
    for (attribute in building.genericAttributes().asSequence().filterNotNull()) {
        println("    ${attribute.name()}: ${genericAttributeValue(attribute)}")
    }

    // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    // and ground surfaces can have filling surfaces: doors and windows.
    println("  Boundaries:")
    for (property in building.boundaries().asSequence().filterNotNull()) {
        val boundary = property.object_()
        if (boundary == null) {
            println("    (reference to ${property.href()?.toString_()})")
            continue
        }
        println("    ${boundary.featureType().name} ${boundary.featureId().asStr()}")
        val feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary)
        WallSurface.tryFrom(feature)?.let { printFillingSurfaces(it.fillingSurfaces()) }
            ?: RoofSurface.tryFrom(feature)?.let { printFillingSurfaces(it.fillingSurfaces()) }
            ?: GroundSurface.tryFrom(feature)?.let { printFillingSurfaces(it.fillingSurfaces()) }
    }
}

fun runBuildingReport(args: Array<String>): Int {
    if (args.size != 1) {
        System.err.println("usage: 03_building_report path/to/model.gml")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1

    val buildings = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(Building::tryFrom) }.toList()
    if (buildings.isEmpty()) {
        println("No buildings.")
    }
    buildings.forEachIndexed { index, building ->
        if (index > 0) println()
        printBuilding(building)
    }
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runBuildingReport(args))
}
