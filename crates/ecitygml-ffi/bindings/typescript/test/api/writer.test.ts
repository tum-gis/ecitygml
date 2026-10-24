// The cases of crates/ecitygml/tests/api/writer.md. WebAssembly has no file system: the cases writing files aren't
// scoped to TypeScript.
import assert from 'node:assert/strict';
import { test } from 'node:test';

import {
    CityModel,
    CitygmlFormat,
    ErrorKind,
    Formatting,
    GmlWriter,
    LinearRing,
    Polygon,
    WallSurface,
} from '../../lib/index.mjs';
import { features, read, readBytes } from '../helpers.ts';
import { assertError, featureTypes } from './helpers.ts';

const model = read('fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml');

/** The model written as `Gml` text. */
function text(cityModel: CityModel, formatting?: Formatting): string {
    const writer = new GmlWriter(CitygmlFormat.Gml);
    if (formatting !== undefined) {
        writer.withFormatting(formatting);
    }
    writer.finish(cityModel);
    return new TextDecoder().decode(new Uint8Array(writer.data()));
}

test('writer in memory', () => {
    for (const format of [CitygmlFormat.Gml, CitygmlFormat.GmlGz, CitygmlFormat.GmlZst]) {
        const writer = new GmlWriter(format);
        assert.equal(writer.data().length, 0);
        writer.finish(model);
        assert.deepEqual(featureTypes(readBytes(new Uint8Array(writer.data()), format)), featureTypes(model));
    }
    assert.ok(text(model).includes('<bldg:Building'));
});

test('writer formatting', () => {
    const lines = (text: string) => text.split('\n').filter((line, i, all) => i < all.length - 1 || line !== '');
    const defaultText = text(model);
    assert.ok(lines(defaultText).length > 1);
    assert.ok(!lines(defaultText).some((line) => line.startsWith(' ') || line.startsWith('\t')));
    assert.equal(text(model, Formatting.newLine()), defaultText);
    assert.equal(text(model, Formatting.indent(' '.charCodeAt(0), 0)), defaultText);

    assert.ok(lines(text(model, Formatting.compact())).length < lines(defaultText).length);

    const spaces = lines(text(model, Formatting.indent(' '.charCodeAt(0), 2)));
    assert.ok(spaces.some((line) => line.startsWith('  <')));
    assert.ok(!spaces.some((line) => line.startsWith('\t')));

    const tabs = text(model, Formatting.indent('\t'.charCodeAt(0), 1));
    assert.ok(lines(tabs).some((line) => line.startsWith('\t<')));
    assert.deepEqual(featureTypes(readBytes(new TextEncoder().encode(tabs))), featureTypes(model));
});

test('writer finish once', () => {
    const writer = new GmlWriter(CitygmlFormat.Gml);
    writer.finish(model);
    assertError(() => writer.finish(model), ErrorKind.InvalidArgument, 'already finished');
});

test('writer unsupported extension', () => {
    assertError(() => GmlWriter.fromPath('out.txt'), ErrorKind.InvalidArgument, 'txt');
});

test('writer without file system', () => {
    assertError(() => GmlWriter.fromPath('out.gml'), ErrorKind.Io, 'operation not supported on this platform');
});

const FZK_LOD2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';

/** The number of times `part` occurs in `text`. */
function occurrences(text: string, part: string): number {
    return text.split(part).length - 1;
}

test('writer keeps references', () => {
    const written = text(read(FZK_LOD2));
    assert.equal(occurrences(written, 'xlink:href="#PolyID7350_878_759628_120742"'), 1);
    assert.equal(occurrences(written, 'gml:id="PolyID7350_878_759628_120742"'), 1);
});

/** The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order. */
function wallCoordinates(cityModel: CityModel): number[][] {
    const result: number[][] = [];
    for (const feature of features(cityModel.iterFeatures())) {
        const multiSurface = WallSurface.tryFrom(feature)?.lod2MultiSurface()?.object();
        if (multiSurface == null) continue;
        const members = multiSurface.surfaceMember();
        for (let member = members.next(); !member.done; member = members.next()) {
            const polygon = Polygon.tryFrom(member.value.object()!);
            if (polygon == null) continue;
            const points = LinearRing.tryFrom(polygon.exterior()!)!.points();
            for (let p = points.next(); !p.done; p = points.next()) {
                result.push([p.value.x(), p.value.y(), p.value.z()]);
            }
        }
    }
    return result;
}

test('writer preserves coordinates', () => {
    const cityModel = read(FZK_LOD2);
    const written = readBytes(new TextEncoder().encode(text(cityModel)));
    const coordinates = wallCoordinates(cityModel);
    assert.ok(coordinates.length > 0);
    assert.deepEqual(wallCoordinates(written), coordinates);
});
