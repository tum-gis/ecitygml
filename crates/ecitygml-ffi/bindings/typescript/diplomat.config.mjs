// Configuration read by the generated loader (lib/diplomat-wasm.mjs).
// The debug or release build of crates/ecitygml-ffi for wasm32-unknown-unknown
// (`mise run build:bindings:typescript [--release]`), chosen with ECITYGML_FFI_PROFILE (default: debug).
const profile = globalThis.process?.env?.ECITYGML_FFI_PROFILE ?? 'debug';
if (profile !== 'debug' && profile !== 'release') {
    throw new Error(`ECITYGML_FFI_PROFILE must be debug or release, not ${profile}`);
}

export default {
    wasm_path: new URL(`../../../../target/wasm32-unknown-unknown/${profile}/ecitygml_ffi.wasm`, import.meta.url),
};
