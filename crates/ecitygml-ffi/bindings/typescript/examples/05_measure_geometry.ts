// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
// roof and ground surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `area3d()` of a multi surface,
// `volume3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the triangles).
// They throw when they can't compute a result. A common case: a solid whose surfaces only reference
// the boundary polygons by `xlink:href` (the reader doesn't resolve such references, as in Rust),
// shown here as "not computable" with the error message.
//
// Usage: node examples/05_measure_geometry.ts path/to/model.gml
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

import {
    AbstractFeatureKindRef,
    AbstractFillingSurfacePropertyIterator,
    Building,
    GroundSurface,
    MultiSurface,
    RoofSurface,
    WallSurface,
} from '../lib/index.mjs';
import { errorText, highestLod, items, pathArgument, readCityModel } from './common.ts';

class Measurement {
    count = 0;
    area = 0;
    triangles = 0;

    /** Adds a surface with its highest LoD multi surface; throws if a calculation fails. */
    add(multiSurface: MultiSurface | null) {
        this.count++;
        if (!multiSurface) return;
        this.area += multiSurface.area3d();
        this.triangles += [...items(multiSurface.triangulate().surface().triangles())].length;
    }
}

type ThematicSurface = WallSurface | RoofSurface | GroundSurface;

/** Adds a wall, roof or ground surface, and its doors and windows to `fillings`. */
function addSurface(surface: ThematicSurface, measurement: Measurement, fillings: Measurement) {
    measurement.add(highestLod(surface.lod3MultiSurface(), surface.lod2MultiSurface(), surface.lod1MultiSurface(), surface.lod0MultiSurface()));
    addFillingSurfaces(surface.fillingSurfaces(), fillings);
}

function addFillingSurfaces(fillings: AbstractFillingSurfacePropertyIterator, measurement: Measurement) {
    for (const property of items(fillings)) {
        const filling = property.object();
        if (filling) {
            measurement.add(highestLod(filling.lod3MultiSurface(), filling.lod2MultiSurface(), filling.lod1MultiSurface(), filling.lod0MultiSurface()));
        }
    }
}

function printBoundaries(building: Building) {
    const [walls, roofs, grounds, fillings] = [new Measurement(), new Measurement(), new Measurement(), new Measurement()];
    for (const property of items(building.boundaries())) {
        const boundary = property.object();
        if (!boundary) continue;
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
        const wall = WallSurface.tryFrom(feature);
        const roof = RoofSurface.tryFrom(feature);
        const ground = GroundSurface.tryFrom(feature);
        if (wall) addSurface(wall, walls, fillings);
        else if (roof) addSurface(roof, roofs, fillings);
        else if (ground) addSurface(ground, grounds, fillings);
    }
    for (const [label, measurement] of [['WallSurface', walls], ['RoofSurface', roofs], ['GroundSurface', grounds]] as const) {
        console.log(`  ${label}: ${measurement.count}, area ${measurement.area.toFixed(3)} m^2, ${measurement.triangles} triangles`);
    }
    console.log(`  Doors and windows: ${fillings.count}, area ${fillings.area.toFixed(3)} m^2`);
}

function printSolids(building: Building) {
    for (const [lod, property] of [[1, building.lod1Solid()], [2, building.lod2Solid()], [3, building.lod3Solid()]] as const) {
        const solid = property?.object();
        if (!solid) continue;
        const shell = solid.exterior();
        const members = shell ? [...items(shell.members())] : [];
        const references = members.filter((member) => member.object() === null).length;
        console.log(`  LoD${lod} solid: ${members.length} surfaces, ${references} of them xlink:href references`);
        let volume: string;
        try {
            volume = `${solid.volume3d().toFixed(3)} m^3`;
        } catch (error) {
            volume = `not computable (${errorText(error)})`;
        }
        console.log(`    Volume: ${volume}`);
    }
}

const cityModel = readCityModel(pathArgument('05_measure_geometry'));
const buildings = [...items(cityModel.iterFeatures())].map((feature) => Building.tryFrom(feature)).filter((b) => b !== null);
if (buildings.length === 0) {
    console.log('No buildings.');
}
buildings.forEach((building, index) => {
    if (index > 0) console.log();
    console.log(`Building ${building.featureId().asStr()}`);
    try {
        printBoundaries(building);
    } catch (error) { // e.g. a surface that can't be triangulated
        console.log(`  Boundaries: not computable (${errorText(error)})`);
    }
    printSolids(building);
});
