// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
// roof and ground surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `area3d()` of a multi surface,
// `volume3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the triangles).
// They return a Kotlin `Result`, failed when they can't compute a result. A common case: a solid whose
// surfaces only reference the boundary polygons by `xlink:href` (the reader doesn't resolve such
// references, as in Rust), shown here as "not computable" with the error message.
//
// Usage: gradle run05MeasureGeometry --args="path/to/model.gml"
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       WallSurface: 4, area 188.629 m^2, 10 triangles
//       RoofSurface: 2, area 138.564 m^2, 4 triangles
//       GroundSurface: 1, area 120.000 m^2, 2 triangles
//       Doors and windows: 0, area 0.000 m^2
//       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("MeasureGeometryKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.AbstractFeatureKindRef
import io.github.tum_gis.ecitygml.AbstractFillingSurfacePropertyIterator
import io.github.tum_gis.ecitygml.Building
import io.github.tum_gis.ecitygml.GroundSurface
import io.github.tum_gis.ecitygml.MultiSurface
import io.github.tum_gis.ecitygml.MultiSurfaceProperty
import io.github.tum_gis.ecitygml.RoofSurface
import io.github.tum_gis.ecitygml.WallSurface
import kotlin.system.exitProcess

/** The multi surface of the highest level of detail among a thematic surface's properties (LoD3 first). */
internal fun highestLod(vararg properties: MultiSurfaceProperty?): MultiSurface? =
    properties.firstNotNullOfOrNull { it?.object_() }

private class Measurement {
    var count = 0
    var area = 0.0
    var triangles = 0

    /** Adds a surface with its highest LoD multi surface; throws the bindings' Error if it fails. */
    fun add(multiSurface: MultiSurface?) {
        count++
        multiSurface ?: return
        area += multiSurface.area3d().getOrThrow()
        triangles += multiSurface.triangulate().getOrThrow().surface().triangles().asSequence().count()
    }
}

/** Adds the doors and windows of a wall, roof or ground surface. */
private fun addFillingSurfaces(fillings: AbstractFillingSurfacePropertyIterator, measurement: Measurement) {
    for (filling in fillings.asSequence().mapNotNull { it?.object_() }) {
        measurement.add(highestLod(filling.lod3MultiSurface(), filling.lod2MultiSurface(), filling.lod1MultiSurface(), filling.lod0MultiSurface()))
    }
}

private fun printBoundaries(building: Building) {
    val (walls, roofs, grounds, fillings) = List(4) { Measurement() }
    for (boundary in building.boundaries().asSequence().mapNotNull { it?.object_() }) {
        val feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary)
        WallSurface.tryFrom(feature)?.let {
            walls.add(highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            addFillingSurfaces(it.fillingSurfaces(), fillings)
        } ?: RoofSurface.tryFrom(feature)?.let {
            roofs.add(highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            addFillingSurfaces(it.fillingSurfaces(), fillings)
        } ?: GroundSurface.tryFrom(feature)?.let {
            grounds.add(highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            addFillingSurfaces(it.fillingSurfaces(), fillings)
        }
    }
    for ((label, measurement) in listOf("WallSurface" to walls, "RoofSurface" to roofs, "GroundSurface" to grounds)) {
        println("  $label: ${measurement.count}, area ${fixed3(measurement.area)} m^2, ${measurement.triangles} triangles")
    }
    println("  Doors and windows: ${fillings.count}, area ${fixed3(fillings.area)} m^2")
}

private fun printSolids(building: Building) {
    for ((lod, property) in listOf(1 to building.lod1Solid(), 2 to building.lod2Solid(), 3 to building.lod3Solid())) {
        val solid = property?.object_() ?: continue
        val members = solid.exterior()?.members()?.asSequence()?.toList() ?: emptyList()
        val references = members.count { it?.object_() == null }
        println("  LoD$lod solid: ${members.size} surfaces, $references of them xlink:href references")
        val volume = solid.volume3d().fold({ "${fixed3(it)} m^3" }, { "not computable (${errorText(it)})" })
        println("    Volume: $volume")
    }
}

fun runMeasureGeometry(args: Array<String>): Int {
    if (args.size != 1) {
        System.err.println("usage: 05_measure_geometry path/to/model.gml")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1

    val buildings = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(Building::tryFrom) }.toList()
    if (buildings.isEmpty()) {
        println("No buildings.")
    }
    buildings.forEachIndexed { index, building ->
        if (index > 0) println()
        println("Building ${building.featureId().asStr()}")
        try {
            printBoundaries(building)
        } catch (error: Exception) { // e.g. a surface that can't be triangulated
            println("  Boundaries: not computable (${errorText(error)})")
        }
        printSolids(building)
    }
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runMeasureGeometry(args))
}
