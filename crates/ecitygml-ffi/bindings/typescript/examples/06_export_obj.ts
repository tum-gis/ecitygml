// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer:
// `triangulate()` turns a multi surface or solid into a `Triangulation`, whose `surface()` is a
// triangulated surface; each `Triangle` has its corners `a()`, `b()` and `c()`. Every wall, roof and
// ground surface, door and window becomes a named OBJ group, using its highest level of detail;
// buildings without such surfaces fall back to their highest LoD solid.
//
// Usage: node examples/06_export_obj.ts input.gml output.obj
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

import { writeFileSync } from 'node:fs';

import {
    AbstractFeatureKindRef,
    Building,
    GroundSurface,
    MultiSurface,
    RoofSurface,
    Triangulation,
    WallSurface,
} from '../lib/index.mjs';
import { errorText, highestLod, items, pathArguments, readCityModel } from './common.ts';

/**
 * Collects OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the
 * last three vertices (OBJ indices are 1-based and count all vertices written so far).
 */
class ObjWriter {
    lines: string[] = [];
    vertices = 0;
    triangles = 0;
    groups = 0;

    writeGroup(name: string, triangulation: Triangulation) {
        this.lines.push(`g ${name}`);
        this.groups++;
        for (const triangle of items(triangulation.surface().triangles())) {
            for (const corner of [triangle.a(), triangle.b(), triangle.c()]) {
                this.lines.push(`v ${corner.x().toFixed(6)} ${corner.y().toFixed(6)} ${corner.z().toFixed(6)}`);
            }
            this.lines.push(`f ${this.vertices + 1} ${this.vertices + 2} ${this.vertices + 3}`);
            this.vertices += 3;
            this.triangles++;
        }
    }

    /** Writes a surface's multi surface (if any); throws if triangulation fails. */
    writeSurface(name: string, multiSurface: MultiSurface | null) {
        if (multiSurface) this.writeGroup(name, multiSurface.triangulate());
    }
}

/** Writes a wall, roof or ground surface and its doors and windows (`featureType()` names their type). */
function writeSurfaceWithFillings(obj: ObjWriter, prefix: string, type: string, surface: WallSurface | RoofSurface | GroundSurface) {
    obj.writeSurface(`${prefix}_${type}_${surface.featureId().asStr()}`,
        highestLod(surface.lod3MultiSurface(), surface.lod2MultiSurface(), surface.lod1MultiSurface(), surface.lod0MultiSurface()));
    for (const property of items(surface.fillingSurfaces())) {
        const filling = property.object();
        if (filling) {
            obj.writeSurface(`${prefix}_${filling.featureType().toString()}_${filling.featureId().asStr()}`,
                highestLod(filling.lod3MultiSurface(), filling.lod2MultiSurface(), filling.lod1MultiSurface(), filling.lod0MultiSurface()));
        }
    }
}

function exportBuilding(obj: ObjWriter, building: Building) {
    const prefix = building.featureId().asStr();
    let hasSurfaces = false;
    for (const property of items(building.boundaries())) {
        const boundary = property.object();
        if (!boundary) continue;
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
        const wall = WallSurface.tryFrom(feature);
        const roof = RoofSurface.tryFrom(feature);
        const ground = GroundSurface.tryFrom(feature);
        if (wall) writeSurfaceWithFillings(obj, prefix, 'WallSurface', wall);
        else if (roof) writeSurfaceWithFillings(obj, prefix, 'RoofSurface', roof);
        else if (ground) writeSurfaceWithFillings(obj, prefix, 'GroundSurface', ground);
        else continue;
        hasSurfaces = true;
    }
    if (hasSurfaces) return;
    for (const [lod, property] of [[3, building.lod3Solid()], [2, building.lod2Solid()], [1, building.lod1Solid()]] as const) {
        const solid = property?.object();
        if (solid) {
            obj.writeGroup(`${prefix}_LoD${lod}Solid`, solid.triangulate());
            return;
        }
    }
}

const [inputPath, outputPath] = pathArguments('06_export_obj', 'input.gml output.obj');
const cityModel = readCityModel(inputPath);
const obj = new ObjWriter();
try {
    for (const feature of items(cityModel.iterFeatures())) {
        const building = Building.tryFrom(feature);
        if (building) exportBuilding(obj, building);
    }
    writeFileSync(outputPath, obj.lines.map((line) => `${line}\n`).join(''));
} catch (error) {
    console.error(`error: ${errorText(error)}`);
    process.exit(1);
}
console.log(`Wrote ${obj.vertices} vertices, ${obj.triangles} triangles, ${obj.groups} groups`);
