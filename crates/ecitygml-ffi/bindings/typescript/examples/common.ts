// Helpers shared by the examples.

import { readFileSync } from 'node:fs';

import { CityModel, CitygmlFormat, GmlReader } from '../lib/index.mjs';

/**
 * Reads a city model from a file, or prints the error and exits with code 1.
 *
 * WebAssembly has no file system: the file is read here and its bytes handed to the reader, with
 * the format picked from the extension (plain, `.gml.gz` or `.gml.zst`).
 */
export function readCityModel(path: string): CityModel {
    const format = path.endsWith('.gml.zst') ? CitygmlFormat.GmlZst
        : path.endsWith('.gml.gz') ? CitygmlFormat.GmlGz
        : CitygmlFormat.Gml;
    try {
        // The generated declaration says Array<number>; a Uint8Array works as well.
        return new GmlReader(readFileSync(path) as unknown as number[], format).finish();
    } catch (error) {
        // Errors of the bindings are thrown with the ecitygml Error as `cause`.
        console.error(`error: ${errorText(error)}`);
        process.exit(1);
    }
}

/** Diplomat's iterators have `next()` but no `[Symbol.iterator]`: this makes them iterable. */
export function* items<T>(iterator: { next(): IteratorResult<T> }): Generator<T> {
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        yield result.value;
    }
}

/** Exits with code 2 and a usage message unless exactly one argument was given. */
export function pathArgument(example: string): string {
    return pathArguments(example, 'path/to/model.gml')[0];
}

/** The command-line arguments; exits with code 2 and the usage message if their number differs. */
export function pathArguments(example: string, usage: string): string[] {
    const expected = usage.split(' ').length;
    if (process.argv.length !== 2 + expected) {
        console.error(`usage: ${example} ${usage}`);
        process.exit(2);
    }
    return process.argv.slice(2);
}

/**
 * The message of an error. The bindings throw a JavaScript `Error` whose `cause` is the ecitygml
 * `Error` (its `toString()` is the message); its own `message` starts with "Error: ".
 */
export function errorText(error: unknown): string {
    if (error instanceof Error) {
        return error.cause !== undefined ? String(error.cause) : error.message;
    }
    return String(error);
}

/** The multi surface of the highest level of detail among a thematic surface's properties (LoD3 first). */
export function highestLod<T>(...properties: ({ object(): T | null } | null)[]): T | null {
    for (const property of properties) {
        const object = property?.object();
        if (object) return object;
    }
    return null;
}
