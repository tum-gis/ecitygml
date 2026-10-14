// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer:
// `triangulate()` turns a multi surface or solid into a `Triangulation`, whose `surface()` is a
// triangulated surface; each `Triangle` has its corners `a()`, `b()` and `c()`. Every wall, roof and
// ground surface, door and window becomes a named OBJ group, using its highest level of detail;
// buildings without such surfaces fall back to their highest LoD solid.
//
// Usage: gradle run06ExportObj --args="input.gml output.obj"
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

// The file name starts with its number in the learning order; the class keeps a readable name.
@file:JvmName("ExportObjKt")

package io.github.tum_gis.ecitygml.examples

import io.github.tum_gis.ecitygml.AbstractFeatureKindRef
import io.github.tum_gis.ecitygml.AbstractFillingSurfacePropertyIterator
import io.github.tum_gis.ecitygml.Building
import io.github.tum_gis.ecitygml.GroundSurface
import io.github.tum_gis.ecitygml.MultiSurface
import io.github.tum_gis.ecitygml.RoofSurface
import io.github.tum_gis.ecitygml.Triangulation
import io.github.tum_gis.ecitygml.WallSurface
import java.io.File
import java.io.Writer
import java.util.Locale
import kotlin.system.exitProcess

/**
 * Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the last
 * three vertices (OBJ indices are 1-based and count all vertices written so far).
 */
private class ObjWriter(private val file: Writer) {
    var vertices = 0
    var triangles = 0
    var groups = 0

    fun writeGroup(name: String, triangulation: Triangulation) {
        file.write("g $name\n")
        groups++
        for (triangle in triangulation.surface().triangles().asSequence().filterNotNull()) {
            for (corner in listOf(triangle.a(), triangle.b(), triangle.c())) {
                file.write(String.format(Locale.ROOT, "v %.6f %.6f %.6f\n", corner.x(), corner.y(), corner.z()))
            }
            file.write("f ${vertices + 1} ${vertices + 2} ${vertices + 3}\n")
            vertices += 3
            triangles++
        }
    }

    /** Writes a surface's multi surface (if any); throws the bindings' Error if triangulation fails. */
    fun writeSurface(name: String, multiSurface: MultiSurface?) {
        multiSurface?.let { writeGroup(name, it.triangulate().getOrThrow()) }
    }
}

/** Writes the doors and windows of a wall, roof or ground surface (`featureType()` names their type). */
private fun writeFillingSurfaces(obj: ObjWriter, prefix: String, fillings: AbstractFillingSurfacePropertyIterator) {
    for (filling in fillings.asSequence().mapNotNull { it?.object_() }) {
        obj.writeSurface("${prefix}_${filling.featureType().name}_${filling.featureId().asStr()}",
            highestLod(filling.lod3MultiSurface(), filling.lod2MultiSurface(), filling.lod1MultiSurface(), filling.lod0MultiSurface()))
    }
}

private fun exportBuilding(obj: ObjWriter, building: Building) {
    val prefix = building.featureId().asStr()
    var hasSurfaces = false
    for (boundary in building.boundaries().asSequence().mapNotNull { it?.object_() }) {
        val feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary)
        WallSurface.tryFrom(feature)?.let {
            obj.writeSurface("${prefix}_WallSurface_${it.featureId().asStr()}",
                highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            writeFillingSurfaces(obj, prefix, it.fillingSurfaces())
        } ?: RoofSurface.tryFrom(feature)?.let {
            obj.writeSurface("${prefix}_RoofSurface_${it.featureId().asStr()}",
                highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            writeFillingSurfaces(obj, prefix, it.fillingSurfaces())
        } ?: GroundSurface.tryFrom(feature)?.let {
            obj.writeSurface("${prefix}_GroundSurface_${it.featureId().asStr()}",
                highestLod(it.lod3MultiSurface(), it.lod2MultiSurface(), it.lod1MultiSurface(), it.lod0MultiSurface()))
            writeFillingSurfaces(obj, prefix, it.fillingSurfaces())
        } ?: continue
        hasSurfaces = true
    }
    if (hasSurfaces) return
    for ((lod, property) in listOf(3 to building.lod3Solid(), 2 to building.lod2Solid(), 1 to building.lod1Solid())) {
        val solid = property?.object_() ?: continue
        obj.writeGroup("${prefix}_LoD${lod}Solid", solid.triangulate().getOrThrow())
        return
    }
}

fun runExportObj(args: Array<String>): Int {
    if (args.size != 2) {
        System.err.println("usage: 06_export_obj input.gml output.obj")
        return 2
    }
    val cityModel = readCityModel(args[0]) ?: return 1
    val obj = try {
        File(args[1]).bufferedWriter().use { file ->
            ObjWriter(file).also { obj ->
                cityModel.iterFeatures().asSequence().mapNotNull { it?.let(Building::tryFrom) }.forEach { exportBuilding(obj, it) }
            }
        }
    } catch (error: Exception) {
        System.err.println("error: ${errorText(error)}")
        return 1
    }
    println("Wrote ${obj.vertices} vertices, ${obj.triangles} triangles, ${obj.groups} groups")
    return 0
}

fun main(args: Array<String>) {
    exitProcess(runExportObj(args))
}
