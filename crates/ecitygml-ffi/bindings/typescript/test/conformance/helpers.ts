// Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).
import assert from 'node:assert/strict';

import { AbstractFeatureKindRef, Building, CityModel } from '../../lib/index.mjs';
import { read as readFixture } from '../helpers.ts';

/** The tolerance of floating point comparisons in the case lists. */
const TOLERANCE = 1e-6;

/** Reads `tests/fixtures/<dataset>/<file>`. */
export function read(dataset: string, file: string): CityModel {
    return readFixture(`${dataset}/${file}`);
}

export function assertClose(actual: number, expected: number): void {
    assert.ok(Math.abs(actual - expected) <= TOLERANCE, `${actual} is not within ${TOLERANCE} of ${expected}`);
}

/** All items of a Diplomat iterator (they have `next()` but no `[Symbol.iterator]`). */
export function all<T>(iterator: { next(): IteratorResult<T> }): T[] {
    const items: T[] = [];
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        items.push(result.value);
    }
    return items;
}

/** The city model's first building. */
export function building(cityModel: CityModel): Building {
    const found = all(cityModel.iterFeatures()).map((f) => Building.tryFrom(f)).find((b) => b !== null);
    assert.ok(found);
    return found;
}

/** The building's boundaries, as features. */
export function boundaries(building: Building): AbstractFeatureKindRef[] {
    return all(building.boundaries()).map((p) => {
        const boundary = p.object();
        assert.ok(boundary);
        return AbstractFeatureKindRef.fromSpaceBoundary(boundary);
    });
}

export function firstName(feature: { names(): { next(): IteratorResult<{ value(): string }> } }): string {
    const name = feature.names().next();
    assert.ok(!name.done);
    return name.value.value();
}
