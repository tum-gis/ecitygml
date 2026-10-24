import { readFileSync } from 'node:fs';

import { AbstractFeatureKindRefIterator, CityModel, CitygmlFormat, GmlReader } from '../lib/index.mjs';

const fixtures = new URL('../../../../../tests/fixtures/', import.meta.url);

export function fixtureBytes(name: string): Uint8Array {
    return readFileSync(new URL(name, fixtures));
}

/** `GmlReader::new(data, format).finish()`, as in Rust. */
export function readBytes(data: Uint8Array, format = CitygmlFormat.Gml): CityModel {
    // The generated declaration says Array<number>; a Uint8Array works as well.
    return new GmlReader(data as unknown as number[], format).finish();
}

export function read(name: string): CityModel {
    return readBytes(fixtureBytes(name));
}

/** Diplomat's iterators have `next()` but no `[Symbol.iterator]`. */
export function* features(iterator: AbstractFeatureKindRefIterator) {
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        yield result.value;
    }
}

/** A model with the FZK LoD2 header and `member` as its only city object (no fixture has one). */
export function readMember(member: string): CityModel {
    const text = new TextDecoder().decode(fixtureBytes('fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml'));
    return readBytes(new TextEncoder().encode(text.slice(0, text.indexOf('<cityObjectMember>')) + member));
}
