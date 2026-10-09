// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
// with their doors and windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are null when absent; lists are iterators (possibly empty).
// - Code-list values (class, function, ...) are wrappers with `value()` (and `code()`).
// - Properties referencing other objects (e.g. a building's boundaries) have `object()` and `href()`;
//   `object()` is null if the property only references an object elsewhere via `xlink:href`.
// - Abstract types are converted with `tryFrom`, e.g. a generic attribute to a `MeasureAttribute`,
//   or a boundary (via `AbstractFeatureKindRef.fromSpaceBoundary`) to a `WallSurface`.
//
// Usage: node examples/03_building_report.ts path/to/model.gml
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

import {
    AbstractFeatureKindRef,
    AbstractFillingSurfacePropertyIterator,
    Building,
    GenericAttributeKind,
    GroundSurface,
    MeasureAttribute,
    RoofSurface,
    WallSurface,
} from '../lib/index.mjs';
import { items, pathArgument, readCityModel } from './common.ts';

/** The `value()`s of code-list values (or codes), comma-separated; "-" if there are none. */
function joined(values: Iterable<{ value(): string }>): string {
    return [...values].map((value) => value.value()).join(', ') || '-';
}

/** The value of a generic attribute: string, integer, double or measure (value and unit). */
function genericAttributeValue(attribute: GenericAttributeKind): string {
    const string = attribute.asString();
    if (string) return string.value();
    const integer = attribute.asInt();
    if (integer) return String(integer.value());
    const double = attribute.asDouble();
    if (double) return double.value().toFixed(3);
    const measure = MeasureAttribute.tryFrom(attribute);
    if (measure) return `${measure.value().value().toFixed(3)} ${measure.value().uom()}`;
    return '(not shown)'; // e.g. a generic attribute set, which holds further attributes
}

/** Prints the doors and windows of a wall, roof or ground surface. */
function printFillingSurfaces(fillings: AbstractFillingSurfacePropertyIterator) {
    for (const property of items(fillings)) {
        const filling = property.object();
        if (filling) {
            console.log(`      ${filling.featureType().toString()} ${filling.featureId().asStr()}`);
        }
    }
}

function printBuilding(building: Building) {
    const date = building.dateOfConstruction();
    const pad = (value: number, width: number) => String(value).padStart(width, '0');
    console.log(`Building ${building.featureId().asStr()}`);
    console.log(`  Name: ${joined(items(building.names()))}`);
    console.log(`  Class: ${building.class_()?.value() ?? '-'}`);
    console.log(`  Functions: ${joined(items(building.functions()))}`);
    console.log(`  Usages: ${joined(items(building.usages()))}`);
    console.log(`  Roof type: ${building.roofType()?.value() ?? '-'}`);
    // 64-bit integers are BigInts in JavaScript.
    console.log(`  Storeys above ground: ${building.storeysAboveGround() ?? '-'}`);
    console.log(`  Storeys below ground: ${building.storeysBelowGround() ?? '-'}`);
    console.log(`  Date of construction: ${date ? `${pad(date.year(), 4)}-${pad(date.month(), 2)}-${pad(date.day(), 2)}` : '-'}`);

    console.log('  Heights:');
    for (const height of items(building.heights())) {
        const length = height.length();
        console.log(`    ${length.value().toFixed(3)} ${length.uom()} (${height.highReference().value()} to ${height.lowReference().value()})`);
    }

    console.log('  Generic attributes:');
    for (const attribute of items(building.genericAttributes())) {
        console.log(`    ${attribute.name()}: ${genericAttributeValue(attribute)}`);
    }

    // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    // and ground surfaces can have filling surfaces: doors and windows.
    console.log('  Boundaries:');
    for (const property of items(building.boundaries())) {
        const boundary = property.object();
        if (!boundary) {
            console.log(`    (reference to ${property.href()?.toString()})`);
            continue;
        }
        console.log(`    ${boundary.featureType().toString()} ${boundary.featureId().asStr()}`);
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
        const surface = WallSurface.tryFrom(feature) ?? RoofSurface.tryFrom(feature) ?? GroundSurface.tryFrom(feature);
        if (surface) {
            printFillingSurfaces(surface.fillingSurfaces());
        }
    }
}

const cityModel = readCityModel(pathArgument('03_building_report'));
const buildings = [...items(cityModel.iterFeatures())]
    .map((feature) => Building.tryFrom(feature))
    .filter((building) => building !== null);
if (buildings.length === 0) {
    console.log('No buildings.');
}
buildings.forEach((building, index) => {
    if (index > 0) console.log();
    printBuilding(building);
});
