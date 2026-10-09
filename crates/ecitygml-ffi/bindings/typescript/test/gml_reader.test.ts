import assert from 'node:assert/strict';
import { test } from 'node:test';
import { gzipSync, zstdCompressSync } from 'node:zlib';

import { CitygmlFormat, ErrorKind, Formatting, GmlReader, GmlWriter } from '../lib/index.mjs';
import { fixtureBytes, readBytes } from './helpers.ts';

const FZK_LOD1 = 'FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';

test('reads plain, gzip and zstd content from bytes', () => {
    const data = fixtureBytes(FZK_LOD1);
    assert.equal(readBytes(data, CitygmlFormat.Gml).cityObjectsLen(), 1);
    assert.equal(readBytes(gzipSync(data), CitygmlFormat.GmlGz).cityObjectsLen(), 1);
    // Compressed by Node's zstd, decoded by ruzstd (pure Rust) inside WebAssembly.
    assert.equal(readBytes(zstdCompressSync(data), CitygmlFormat.GmlZst).cityObjectsLen(), 1);
});

test('fromPath fails: WebAssembly has no file system', () => {
    assert.throws(() => GmlReader.fromPath(FZK_LOD1), (error: Error) =>
        (error.cause as { kind(): ErrorKind }).kind() == ErrorKind.Io);
});

test('parse errors carry kind and message', () => {
    assert.throws(() => readBytes(new TextEncoder().encode('<no-citygml')), (error: Error) =>
        (error.cause as { kind(): ErrorKind }).kind() == ErrorKind.Parse && error.message.includes('tag not closed'));
});

test('finish works only once', () => {
    const reader = new GmlReader(fixtureBytes(FZK_LOD1) as unknown as number[], CitygmlFormat.Gml);
    reader.withRebuildObjectBounds(false);
    assert.equal(reader.finish().cityObjectsLen(), 1);
    assert.throws(() => reader.finish(), (error: Error) => error.message.includes('already finished'));
});

test('GmlWriter writes to memory, plain, gzip and zstd', () => {
    const model = readBytes(fixtureBytes(FZK_LOD1));
    for (const format of [CitygmlFormat.Gml, CitygmlFormat.GmlGz, CitygmlFormat.GmlZst]) {
        const writer = new GmlWriter(format);
        writer.withFormatting(Formatting.indent(' '.charCodeAt(0), 2));
        writer.finish(model);
        assert.equal(readBytes(new Uint8Array(writer.data()), format).cityObjectsLen(), 1);
        assert.throws(() => writer.finish(model), (error: Error) => error.message.includes('already finished'));
    }
    const plain = new GmlWriter(CitygmlFormat.Gml);
    plain.finish(model);
    assert.ok(new TextDecoder().decode(new Uint8Array(plain.data())).includes('<bldg:Building'));
});

test('GmlWriter.fromPath fails: WebAssembly has no file system', () => {
    assert.throws(() => GmlWriter.fromPath('out.gml'), (error: Error) =>
        (error.cause as { kind(): ErrorKind }).kind() == ErrorKind.Io);
});
