// Helpers of the API suite (crates/ecitygml/tests/api/README.md).
import assert from 'node:assert/strict';

import { CityModel, ErrorKind } from '../../lib/index.mjs';
import { features } from '../helpers.ts';

export function featureTypes(cityModel: CityModel): unknown[] {
    return [...features(cityModel.iterFeatures())].map((feature) => feature.featureType());
}

/** Asserts that `run` throws an error of `kind` whose message contains `part`. */
export function assertError(run: () => unknown, kind: ErrorKind, part: string): void {
    assert.throws(run, (error: Error) => {
        assert.equal((error.cause as { kind(): ErrorKind }).kind(), kind);
        assert.ok(error.message.includes(part), error.message);
        return true;
    });
}
