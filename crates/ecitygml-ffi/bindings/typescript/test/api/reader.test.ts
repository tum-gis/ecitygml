// The cases of crates/ecitygml/tests/api/reader.md. WebAssembly has no file system: where a case reads a file, the
// test reads its bytes and passes them to `GmlReader::new`.
import assert from 'node:assert/strict';
import { test } from 'node:test';

import { CitygmlFormat, ErrorKind, GmlReader, WallSurface } from '../../lib/index.mjs';
import { features, fixtureBytes, readBytes } from '../helpers.ts';
import { assertError } from './helpers.ts';

const FZK_LOD1 = 'fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const FZK_LOD2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';

test('reader from bytes', () => {
    assert.equal(readBytes(fixtureBytes(FZK_LOD1), CitygmlFormat.Gml).cityObjectsLen(), 1);
});

test('reader compressed', () => {
    for (const [extension, format] of [['gz', CitygmlFormat.GmlGz], ['zst', CitygmlFormat.GmlZst]] as const) {
        const data = fixtureBytes(`fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.${extension}`);
        assert.equal(readBytes(data, format).cityObjectsLen(), 1, extension);
    }
});

test('reader default rebuilds object bounds', () => {
    const cityModel = readBytes(fixtureBytes(FZK_LOD2));
    const walls = [...features(cityModel.iterFeatures())].map((f) => WallSurface.tryFrom(f)).filter((w) => w != null);
    assert.deepEqual(walls.map((wall) => wall.boundedBy() != null), [true, true, true, true]);
});

test('reader finish once', () => {
    const reader = new GmlReader(fixtureBytes(FZK_LOD1) as unknown as number[], CitygmlFormat.Gml);
    reader.withRebuildObjectBounds(false);
    assert.equal(reader.finish().cityObjectsLen(), 1);
    assertError(() => reader.finish(), ErrorKind.InvalidArgument, 'already finished');
});

test('reader unsupported extension', () => {
    assertError(() => GmlReader.fromPath('../../../../../tests/fixtures/README.md'), ErrorKind.InvalidArgument, 'md');
});

test('reader invalid content', () => {
    const reader = new GmlReader(fixtureBytes('invalid/unclosed-tag.gml') as unknown as number[], CitygmlFormat.Gml);
    assertError(() => reader.finish(), ErrorKind.Parse, 'tag not closed');
});

test('reader without file system', () => {
    assertError(() => GmlReader.fromPath(FZK_LOD1), ErrorKind.Io, 'operation not supported on this platform');
});
