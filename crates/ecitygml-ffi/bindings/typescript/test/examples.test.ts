// Runs the scripts in examples/ and compares their output with the expected output shared by all
// languages: for every `tests/expected/examples/<example>/<dataset>/<fixture>.txt`, the example runs on
// `tests/fixtures/<dataset>/<fixture>.gml` and must print that text. Examples that write a file get a
// temporary output path; if `expected/<example>/<dataset>/<fixture><extension>` exists, the file must match it.
import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { existsSync, mkdtempSync, readdirSync, readFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { fileURLToPath } from 'node:url';
import { test } from 'node:test';

const examples = fileURLToPath(new URL('../examples/', import.meta.url));
const expected = fileURLToPath(new URL('../../../../../tests/expected/examples/', import.meta.url));
const fixtures = fileURLToPath(new URL('../../../../../tests/fixtures/', import.meta.url));
// Examples with an output file, and its extension.
const outputExtensions: Record<string, string> = { '06_export_obj': '.obj', '07_convert': '.gml.gz' };

function run(script: string, ...args: string[]) {
    return spawnSync(process.execPath, [join(examples, script), ...args], { encoding: 'utf8' });
}

for (const example of readdirSync(expected).sort()) {
    for (const file of readdirSync(join(expected, example), { recursive: true, encoding: 'utf8' }).filter((name) => name.endsWith('.txt')).sort()) {
        const fixture = file.slice(0, -'.txt'.length);
        test(`${example} ${fixture}`, () => {
            const extension = outputExtensions[example];
            const output = extension ? join(mkdtempSync(join(tmpdir(), 'ecitygml-example-')), `output${extension}`) : undefined;
            const result = run(`${example}.ts`, join(fixtures, `${fixture}.gml`), ...(output ? [output] : []));
            assert.equal(result.status, 0, result.stderr);
            assert.equal(result.stdout, readFileSync(join(expected, example, file), 'utf8'));
            const expectedFile = join(expected, example, `${fixture}${extension ?? ''}`);
            if (output && existsSync(expectedFile)) {
                assert.equal(readFileSync(output, 'utf8'), readFileSync(expectedFile, 'utf8'));
            }
        });
    }
}

test('every example has expected output', () => {
    const scripts = readdirSync(examples).filter((name) => /^\d\d_.*\.ts$/.test(name)).map((name) => name.slice(0, -3));
    assert.deepEqual(readdirSync(expected).sort(), scripts.sort());
});

test('missing file', () => {
    const result = run('01_read_city_model.ts', join(fixtures, 'does-not-exist.gml'));
    assert.equal(result.status, 1);
    assert.match(result.stderr, /no such file/i);
});
