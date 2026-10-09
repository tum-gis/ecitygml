// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
// areas and the volumes of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
// (like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
// Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
// are reached through properties (`object()`), the areas through the space's `boundaries()`,
// converted with `tryFrom`. Geometry calculations (`length3d`, `area3d`, `volume3d`) can fail, e.g.
// for degenerate geometry, and then throw.
//
// Usage: node examples/04_road_network.ts path/to/model.gml
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

import {
    AbstractFeatureKindRef,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    AuxiliaryTrafficSpacePropertyIterator,
    Road,
    TrafficArea,
    TrafficSpace,
    TrafficSpacePropertyIterator,
} from '../lib/index.mjs';
import { errorText, items, pathArgument, readCityModel } from './common.ts';

/** Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces). */
class Totals {
    spaces = 0;
    length = 0;
    volume = 0;
    areas = 0;
    area = 0;
}

/**
 * A measurement as text (e.g. "40.000 m"), passed to `add`; "-" without geometry, and a note if the
 * calculation fails.
 */
function measured<G>(geometry: G | null | undefined, measure: (geometry: G) => number, unit: string, add: (value: number) => void): string {
    if (!geometry) return '-';
    try {
        const value = measure(geometry);
        add(value);
        return `${value.toFixed(3)} ${unit}`;
    } catch (error) {
        return `not computable (${errorText(error)})`;
    }
}

function printSpace(space: TrafficSpace | AuxiliaryTrafficSpace, totals: Totals, indent: string) {
    const isTrafficSpace = space instanceof TrafficSpace;
    console.log(`${indent}${isTrafficSpace ? 'TrafficSpace' : 'AuxiliaryTrafficSpace'} ${space.featureId().asStr()}`);
    const length = measured(space.lod2MultiCurve()?.object(), (curve) => curve.length3d(), 'm', (v) => (totals.length += v));
    const volume = measured(space.lod2Solid()?.object(), (solid) => solid.volume3d(), 'm^3', (v) => (totals.volume += v));
    console.log(`${indent}  Centre line (LoD2): ${length}`);
    console.log(`${indent}  Volume (LoD2 solid): ${volume}`);
    totals.spaces++;

    // The areas are the space's boundaries of the matching type.
    for (const property of items(space.boundaries())) {
        const boundary = property.object();
        if (!boundary) continue;
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
        const area = isTrafficSpace ? TrafficArea.tryFrom(feature) : AuxiliaryTrafficArea.tryFrom(feature);
        if (!area) continue;
        const text = measured(area.lod2MultiSurface()?.object(), (surface) => surface.area3d(), 'm^2', (v) => (totals.area += v));
        console.log(`${indent}  ${isTrafficSpace ? 'TrafficArea' : 'AuxiliaryTrafficArea'} ${area.featureId().asStr()}: ${text}`);
        totals.areas++;
    }
}

/** The traffic and auxiliary traffic spaces of a road, section or intersection. */
function printSpaces(spaces: TrafficSpacePropertyIterator, auxiliarySpaces: AuxiliaryTrafficSpacePropertyIterator,
    traffic: Totals, auxiliary: Totals, indent: string) {
    for (const property of items(spaces)) {
        const space = property.object();
        if (space) printSpace(space, traffic, indent);
    }
    for (const property of items(auxiliarySpaces)) {
        const space = property.object();
        if (space) printSpace(space, auxiliary, indent);
    }
}

const cityModel = readCityModel(pathArgument('04_road_network'));
const traffic = new Totals();
const auxiliary = new Totals();
const roads = [...items(cityModel.iterFeatures())].map((feature) => Road.tryFrom(feature)).filter((road) => road !== null);
for (const road of roads) {
    console.log(`Road ${road.featureId().asStr()}`);
    printSpaces(road.trafficSpaces(), road.auxiliaryTrafficSpaces(), traffic, auxiliary, '  '); // a road can hold spaces directly, too
    for (const property of items(road.sections())) {
        const section = property.object();
        if (!section) continue;
        console.log(`  Section ${section.featureId().asStr()}`);
        printSpaces(section.trafficSpaces(), section.auxiliaryTrafficSpaces(), traffic, auxiliary, '    ');
    }
    for (const property of items(road.intersections())) {
        const intersection = property.object();
        if (!intersection) continue;
        console.log(`  Intersection ${intersection.featureId().asStr()}`);
        printSpaces(intersection.trafficSpaces(), intersection.auxiliaryTrafficSpaces(), traffic, auxiliary, '    ');
    }
}

console.log();
console.log(`Roads: ${roads.length}`);
for (const [label, totals] of [['Traffic spaces', traffic], ['Auxiliary traffic spaces', auxiliary]] as const) {
    console.log(`${label}: ${totals.spaces}, centre lines ${totals.length.toFixed(3)} m, ${totals.areas} areas ${totals.area.toFixed(3)} m^2, volume ${totals.volume.toFixed(3)} m^3`);
}
console.log(`Total volume of traffic spaces (LoD2): ${traffic.volume.toFixed(3)} m^3`);
