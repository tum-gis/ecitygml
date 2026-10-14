// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
// areas and the volumes of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
// (like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
// Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
// are reached through properties (`object_()`), the areas through the space's `boundaries()`,
// converted with `tryFrom`. Geometry calculations (`length3d`, `area3d`, `volume3d`) can fail, e.g.
// for degenerate geometry, and return a Kotlin `Result`.
//
// Usage: gradle run04RoadNetwork --args="path/to/model.gml"
//
// Output for ASAM-UC_RoadShape.gml (shortened):
//
//     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//           Centre line (LoD2): 40.000 m
//           Volume (LoD2 solid): 720.000 m^3
//           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//         ...
//
//     Total volume of traffic spaces (LoD2): 1260.000 m^3

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("RoadNetworkKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.AbstractFeatureKindRef
import io.github.tum_gis.ecitygml.AbstractSpaceBoundaryPropertyIterator
import io.github.tum_gis.ecitygml.AuxiliaryTrafficArea
import io.github.tum_gis.ecitygml.AuxiliaryTrafficSpacePropertyIterator
import io.github.tum_gis.ecitygml.Error
import io.github.tum_gis.ecitygml.MultiCurve
import io.github.tum_gis.ecitygml.MultiSurface
import io.github.tum_gis.ecitygml.Road
import io.github.tum_gis.ecitygml.Solid
import io.github.tum_gis.ecitygml.TrafficArea
import io.github.tum_gis.ecitygml.TrafficSpacePropertyIterator
import kotlin.system.exitProcess

/** Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces). */
private class Totals {
    var spaces = 0
    var length = 0.0
    var volume = 0.0
    var areas = 0
    var area = 0.0
}

/** The text of a calculation's error (the bindings' Error has its text in `message()`). */
internal fun errorText(error: Throwable): String = if (error is Error) error.message() else error.message ?: "$error"

/**
 * A measurement as text (e.g. "40.000 m"), passed to `add`; "-" without geometry, and a note if the
 * calculation fails.
 */
private fun <G> measured(geometry: G?, measure: (G) -> Result<Double>, unit: String, add: (Double) -> Unit): String {
    geometry ?: return "-"
    return measure(geometry).fold(
        onSuccess = { add(it); "${fixed3(it)} $unit" },
        onFailure = { "not computable (${errorText(it)})" },
    )
}

/** Prints a traffic or auxiliary traffic space, given its parts (the two are separate classes). */
private fun printSpace(
    kind: String, id: String, curve: MultiCurve?, solid: Solid?, boundaries: AbstractSpaceBoundaryPropertyIterator,
    area: (AbstractFeatureKindRef) -> Pair<String, MultiSurface?>?, totals: Totals, indent: String,
) {
    println("$indent$kind $id")
    println("$indent  Centre line (LoD2): ${measured(curve, MultiCurve::length3d, "m") { totals.length += it }}")
    println("$indent  Volume (LoD2 solid): ${measured(solid, Solid::volume3d, "m^3") { totals.volume += it }}")
    totals.spaces++

    // The areas are the space's boundaries of the matching type.
    for (boundary in boundaries.asSequence().mapNotNull { it?.object_() }) {
        val (label, surface) = area(AbstractFeatureKindRef.fromSpaceBoundary(boundary)) ?: continue
        println("$indent  $label: ${measured(surface, MultiSurface::area3d, "m^2") { totals.area += it }}")
        totals.areas++
    }
}

/** The traffic and auxiliary traffic spaces of a road, section or intersection. */
private fun printSpaces(
    spaces: TrafficSpacePropertyIterator, auxiliarySpaces: AuxiliaryTrafficSpacePropertyIterator,
    traffic: Totals, auxiliary: Totals, indent: String,
) {
    for (space in spaces.asSequence().mapNotNull { it?.object_() }) {
        printSpace("TrafficSpace", space.featureId().asStr(), space.lod2MultiCurve()?.object_(),
            space.lod2Solid()?.object_(), space.boundaries(), { feature ->
                TrafficArea.tryFrom(feature)?.let { "TrafficArea ${it.featureId().asStr()}" to it.lod2MultiSurface()?.object_() }
            }, traffic, indent)
    }
    for (space in auxiliarySpaces.asSequence().mapNotNull { it?.object_() }) {
        printSpace("AuxiliaryTrafficSpace", space.featureId().asStr(), space.lod2MultiCurve()?.object_(),
            space.lod2Solid()?.object_(), space.boundaries(), { feature ->
                AuxiliaryTrafficArea.tryFrom(feature)?.let {
                    "AuxiliaryTrafficArea ${it.featureId().asStr()}" to it.lod2MultiSurface()?.object_()
                }
            }, auxiliary, indent)
    }
}

fun runRoadNetwork(args: Array<String>): Int {
    if (args.size != 1) {
        System.err.println("usage: 04_road_network path/to/model.gml")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1

    val traffic = Totals()
    val auxiliary = Totals()
    val roads = cityModel.iterFeatures().asSequence().mapNotNull { it?.let(Road::tryFrom) }.toList()
    for (road in roads) {
        println("Road ${road.featureId().asStr()}")
        printSpaces(road.trafficSpaces(), road.auxiliaryTrafficSpaces(), traffic, auxiliary, "  ") // a road can hold spaces directly, too
        for (section in road.sections().asSequence().mapNotNull { it?.object_() }) {
            println("  Section ${section.featureId().asStr()}")
            printSpaces(section.trafficSpaces(), section.auxiliaryTrafficSpaces(), traffic, auxiliary, "    ")
        }
        for (intersection in road.intersections().asSequence().mapNotNull { it?.object_() }) {
            println("  Intersection ${intersection.featureId().asStr()}")
            printSpaces(intersection.trafficSpaces(), intersection.auxiliaryTrafficSpaces(), traffic, auxiliary, "    ")
        }
    }

    println()
    println("Roads: ${roads.size}")
    for ((label, totals) in listOf("Traffic spaces" to traffic, "Auxiliary traffic spaces" to auxiliary)) {
        println("$label: ${totals.spaces}, centre lines ${fixed3(totals.length)} m, ${totals.areas} areas ${fixed3(totals.area)} m^2, volume ${fixed3(totals.volume)} m^3")
    }
    println("Total volume of traffic spaces (LoD2): ${fixed3(traffic.volume)} m^3")
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runRoadNetwork(args))
}
