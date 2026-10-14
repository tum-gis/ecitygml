//! Runs the examples and snippets (`examples/`) and compares their output with the expected output shared by all
//! languages: for every `tests/expected/{examples,snippets}/<name>/<fixture>.txt` at the repository root, the program
//! runs on `tests/fixtures/<fixture>.gml` and must print that text. Examples that write a file get a temporary output
//! path; if `<fixture><extension>` exists next to the expected text, the file must match it.
//!
//! `cargo test` builds the examples before running the tests; a test selection that skips them (e.g.
//! `cargo test --test examples`) needs `cargo build --examples` first.

use std::path::{Path, PathBuf};
use std::process::{Command, Output};

/// Examples and snippets that write a file, and its extension (the program's second argument).
const OUTPUT_EXTENSIONS: [(&str, &str); 3] = [
    ("06_export_obj", ".obj"),
    ("07_convert", ".gml.gz"),
    ("translate_to_local_coordinates", ".gml"),
];

fn repository_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR")).join("../..")
}

/// The compiled example: `target/<profile>/examples/<name>`, next to this test's `deps` directory.
fn executable(name: &str) -> PathBuf {
    let test = std::env::current_exe().expect("the test executable should have a path");
    let profile_dir = test
        .parent()
        .and_then(Path::parent)
        .expect("the test should run from target/<profile>/deps");
    profile_dir
        .join("examples")
        .join(format!("{name}{}", std::env::consts::EXE_SUFFIX))
}

fn run(name: &str, args: &[&Path]) -> Output {
    let executable = executable(name);
    assert!(
        executable.exists(),
        "{} is missing: build the examples (`cargo build --examples`)",
        executable.display()
    );
    Command::new(&executable)
        .args(args)
        .output()
        .expect("the example should start")
}

/// The test cases: (program, fixture, expected output) for every `<kind>/<program>/<fixture>.txt`.
fn cases(kind: &str) -> Vec<(String, String, PathBuf)> {
    let directory = repository_root().join("tests/expected").join(kind);
    let mut cases = Vec::new();
    for program in std::fs::read_dir(&directory)
        .expect("the expected outputs should exist")
        .flatten()
    {
        for file in std::fs::read_dir(program.path())
            .expect("should be a directory")
            .flatten()
        {
            let path = file.path();
            if path.extension().is_some_and(|extension| extension == "txt") {
                let program = program.file_name().to_string_lossy().into_owned();
                let fixture = path
                    .file_stem()
                    .expect("should have a name")
                    .to_string_lossy()
                    .into_owned();
                cases.push((program, fixture, path));
            }
        }
    }
    cases.sort();
    cases
}

/// Runs every case of a kind and returns a description of each one that failed.
fn failures(kind: &str) -> Vec<String> {
    let mut failures = Vec::new();
    for (program, fixture, expected) in cases(kind) {
        let input = repository_root()
            .join("tests/fixtures")
            .join(format!("{fixture}.gml"));
        let extension = OUTPUT_EXTENSIONS
            .iter()
            .find(|(name, _)| *name == program)
            .map(|(_, extension)| *extension);
        let output_file = extension.map(|extension| {
            std::env::temp_dir().join(format!(
                "ecitygml-example-{}-{program}-{fixture}{extension}",
                std::process::id()
            ))
        });
        let args: Vec<&Path> = std::iter::once(input.as_path())
            .chain(output_file.as_deref())
            .collect();

        let output = run(&program, &args);
        let stdout = String::from_utf8_lossy(&output.stdout);
        let expected_text =
            std::fs::read_to_string(&expected).expect("the expected output should be readable");
        if !output.status.success() {
            failures.push(format!(
                "{program} {fixture}: {}\n{}",
                output.status,
                String::from_utf8_lossy(&output.stderr)
            ));
        } else if stdout != expected_text {
            failures.push(format!(
                "{program} {fixture}: output differs from {}:\n{stdout}",
                expected.display()
            ));
        } else if let (Some(output_file), Some(extension)) = (&output_file, extension) {
            let expected_file = expected.with_file_name(format!("{fixture}{extension}"));
            if expected_file.exists()
                && std::fs::read(output_file).ok() != std::fs::read(&expected_file).ok()
            {
                failures.push(format!(
                    "{program} {fixture}: the written file differs from {}",
                    expected_file.display()
                ));
            }
        }
        if let Some(output_file) = output_file {
            let _ = std::fs::remove_file(output_file);
        }
    }
    failures
}

#[test]
fn examples_print_expected_output() {
    let failures = failures("examples");
    assert!(failures.is_empty(), "{}", failures.join("\n\n"));
}

#[test]
fn snippets_print_expected_output() {
    let failures = failures("snippets");
    assert!(failures.is_empty(), "{}", failures.join("\n\n"));
}

#[test]
fn every_example_and_snippet_has_expected_output() {
    let mut examples: Vec<String> =
        std::fs::read_dir(Path::new(env!("CARGO_MANIFEST_DIR")).join("examples"))
            .expect("the examples should exist")
            .flatten()
            .filter_map(|entry| {
                entry
                    .path()
                    .file_stem()
                    .map(|stem| stem.to_string_lossy().into_owned())
            })
            .filter(|name| name.starts_with(|c: char| c.is_ascii_digit()))
            .collect();
    examples.sort();
    let mut snippets: Vec<String> =
        std::fs::read_dir(Path::new(env!("CARGO_MANIFEST_DIR")).join("examples/snippets"))
            .expect("the snippets should exist")
            .flatten()
            .filter_map(|entry| {
                entry
                    .path()
                    .file_stem()
                    .map(|stem| stem.to_string_lossy().into_owned())
            })
            .collect();
    snippets.sort();
    let programs = |kind: &str| {
        let mut programs: Vec<String> = cases(kind)
            .into_iter()
            .map(|(program, _, _)| program)
            .collect();
        programs.dedup();
        programs
    };
    assert_eq!(programs("examples"), examples);
    assert_eq!(programs("snippets"), snippets);
}

#[test]
fn missing_file() {
    let output = run(
        "01_read_city_model",
        &[&repository_root().join("tests/fixtures/does-not-exist.gml")],
    );
    assert_eq!(output.status.code(), Some(1));
    assert!(String::from_utf8_lossy(&output.stderr).contains("No such file"));
}

#[test]
fn usage() {
    assert_eq!(run("01_read_city_model", &[]).status.code(), Some(2));
    assert_eq!(
        run("07_convert", &[Path::new("only-one-argument.gml")])
            .status
            .code(),
        Some(2)
    );
}
