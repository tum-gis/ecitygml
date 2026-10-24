// Runs the scripts in examples/snippets/ (short programs giving a first impression of the bindings) and compares their output with the
// expected output shared by all languages: for every `tests/expected/snippets/<snippet>/<dataset>/<fixture>.txt`,
// the snippet runs on `tests/fixtures/<dataset>/<fixture>.gml` and must print that text.
import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { existsSync, mkdtempSync, readdirSync, readFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { fileURLToPath } from 'node:url';
import { test } from 'node:test';

const snippets = fileURLToPath(new URL('../examples/snippets/', import.meta.url));
const expected = fileURLToPath(new URL('../../../../../tests/expected/snippets/', import.meta.url));
const fixtures = fileURLToPath(new URL('../../../../../tests/fixtures/', import.meta.url));
// Snippets that write a file, and its extension (the snippet's second argument).
const outputExtensions: Record<string, string> = { translate_to_local_coordinates: '.gml' };

for (const snippet of readdirSync(expected).sort()) {
    for (const file of readdirSync(join(expected, snippet), { recursive: true, encoding: 'utf8' }).filter((name) => name.endsWith('.txt')).sort()) {
        const fixture = file.slice(0, -'.txt'.length);
        test(`${snippet} ${fixture}`, () => {
            const extension = outputExtensions[snippet];
            const output = extension ? join(mkdtempSync(join(tmpdir(), 'ecitygml-snippet-')), `output${extension}`) : undefined;
            const result = spawnSync(process.execPath,
                [join(snippets, `${snippet}.ts`), join(fixtures, `${fixture}.gml`), ...(output ? [output] : [])], { encoding: 'utf8' });
            assert.equal(result.status, 0, result.stderr);
            assert.equal(result.stdout, readFileSync(join(expected, snippet, file), 'utf8'));
            const expectedFile = join(expected, snippet, `${fixture}${extension ?? ''}`);
            if (output && existsSync(expectedFile)) {
                assert.ok(readFileSync(output).equals(readFileSync(expectedFile)), `${output} differs from ${expectedFile}`);
            }
        });
    }
}

test('every snippet has expected output', () => {
    const scripts = readdirSync(snippets).filter((name) => name.endsWith('.ts')).map((name) => name.slice(0, -3));
    assert.deepEqual(readdirSync(expected).sort(), scripts.sort());
});
