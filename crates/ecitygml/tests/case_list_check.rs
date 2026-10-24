//! Checks that every suite implements exactly the cases of the case lists, for both kinds of suite: the conformance
//! suite (case lists per fixture dataset in `crates/ecitygml/tests/conformance`) and the API suite (case lists per API
//! area in `crates/ecitygml/tests/api`); see the README.md in each folder.
//!
//! For each case list `<name>.md` (its case ids are the ``## `<id>` `` headings), each suite that runs at least one of
//! its cases must have the list's test file, and its tests must be exactly the cases scoped to that suite: none
//! missing, none extra. A case runs in every suite unless its first line is `Suites: <suites>` or
//! `Suites: all except <suites>`. Names are compared normalized (lower case, letters and digits only, without a
//! leading `test`), so `building_count`, `test_building_count`, `"Building count"` and `BuildingCount` match. Files
//! in a suite's folder that belong to no case list are reported too.

use regex::Regex;
use std::collections::{BTreeMap, BTreeSet};
use std::path::{Path, PathBuf};

const BINDINGS: &str = "crates/ecitygml-ffi/bindings";
const RUST_TEST: &str = r"#\[test\]\s*(?:#\[[^\]]*\]\s*)*fn\s+(\w+)";

/// A kind of suite: the folder name in each suite (`{kind}`, .NET `{Kind}`) and whether each case list belongs to a
/// fixture dataset of the same name.
struct Kind {
    folder: &'static str,
    dotnet_folder: &'static str,
    per_dataset: bool,
}

const KINDS: [Kind; 2] = [
    Kind {
        folder: "conformance",
        dotnet_folder: "Conformance",
        per_dataset: true,
    },
    Kind {
        folder: "api",
        dotnet_folder: "Api",
        per_dataset: false,
    },
];

/// A suite: its folder (with `{kind}`), the test file name of a case list (`{snake}` or `{pascal}`), the pattern of a
/// test's name, and the helper files allowed next to the test files (with `{kind}`).
struct Suite {
    name: &'static str,
    folder: &'static str,
    file_pattern: &'static str,
    test_pattern: &'static str,
    helpers: &'static [&'static str],
}

const SUITES: [Suite; 9] = [
    Suite {
        name: "Rust",
        folder: "crates/ecitygml/tests/{kind}",
        file_pattern: "{snake}.rs",
        test_pattern: RUST_TEST,
        helpers: &["main.rs", "README.md"],
    },
    Suite {
        name: "Rust FFI",
        folder: "crates/ecitygml-ffi/tests/{kind}",
        file_pattern: "{snake}.rs",
        test_pattern: RUST_TEST,
        helpers: &["main.rs"],
    },
    Suite {
        name: "C",
        folder: "{bindings}/c/tests/{kind}",
        file_pattern: "test_{snake}.c",
        test_pattern: r"RUN_TEST\(\s*(\w+)\s*\)",
        helpers: &["{kind}.h"],
    },
    Suite {
        name: "C++",
        folder: "{bindings}/cpp/tests/{kind}",
        file_pattern: "test_{snake}.cpp",
        test_pattern: r#"TEST_CASE\(\s*"([^"]+)""#,
        helpers: &["{kind}.hpp"],
    },
    Suite {
        name: "Python",
        folder: "{bindings}/python/tests/{kind}",
        file_pattern: "test_{snake}.py",
        test_pattern: r"(?m)^\s*def\s+(test_\w+)",
        helpers: &["__init__.py", "helpers.py"],
    },
    Suite {
        name: "TypeScript",
        folder: "{bindings}/typescript/test/{kind}",
        file_pattern: "{snake}.test.ts",
        test_pattern: r"\btest\(\s*'([^']+)'",
        helpers: &["helpers.ts"],
    },
    Suite {
        name: "Kotlin",
        folder: "{bindings}/kotlin/src/test/kotlin/io/github/tum_gis/ecitygml/{kind}",
        file_pattern: "{pascal}Test.kt",
        test_pattern: r"@Test\s+fun\s+(\w+)",
        helpers: &["Helpers.kt"],
    },
    Suite {
        name: ".NET",
        folder: "{bindings}/dotnet/tests/{Kind}",
        file_pattern: "{pascal}Tests.cs",
        test_pattern: r"\[Fact\]\s*public\s+void\s+(\w+)",
        helpers: &["Helpers.cs"],
    },
    Suite {
        name: "Dart",
        folder: "{bindings}/dart/test/{kind}",
        file_pattern: "{snake}_test.dart",
        test_pattern: r"\btest\(\s*'([^']+)'",
        helpers: &["helpers.dart"],
    },
];

impl Suite {
    fn folder(&self, kind: &Kind) -> String {
        self.folder
            .replace("{bindings}", BINDINGS)
            .replace("{kind}", kind.folder)
            .replace("{Kind}", kind.dotnet_folder)
    }

    fn is_helper(&self, kind: &Kind, file: &str) -> bool {
        self.helpers
            .iter()
            .any(|helper| helper.replace("{kind}", kind.folder) == file)
    }
}

/// The folder of a kind's case lists, next to the Rust suite (the reference the bindings follow).
fn case_list_folder(kind: &Kind) -> String {
    SUITES[0].folder(kind)
}

fn repository_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR")).join("../..")
}

/// `test_building_count`, `"Building count"` and `BuildingCount` all become `buildingcount`.
fn normalize(name: &str) -> String {
    let normalized: String = name
        .to_lowercase()
        .chars()
        .filter(char::is_ascii_alphanumeric)
        .collect();
    normalized
        .strip_prefix("test")
        .map_or(normalized.clone(), str::to_string)
}

/// The test file name of a case list: `{snake}` → `fzk_haus_citygml_3_0`, `{pascal}` → `FzkHausCitygml30`.
fn file_name(pattern: &str, list: &str) -> String {
    let parts: Vec<&str> = list
        .split(|c: char| !c.is_ascii_alphanumeric())
        .filter(|part| !part.is_empty())
        .collect();
    let snake = parts
        .iter()
        .map(|part| part.to_lowercase())
        .collect::<Vec<_>>()
        .join("_");
    let pascal: String = parts
        .iter()
        .map(|part| {
            let mut chars = part.chars();
            chars.next().map_or(String::new(), |first| {
                first
                    .to_uppercase()
                    .chain(chars.flat_map(char::to_lowercase))
                    .collect()
            })
        })
        .collect();
    pattern
        .replace("{snake}", &snake)
        .replace("{pascal}", &pascal)
}

/// A case: its id and the suites that run it.
struct Case {
    id: String,
    suites: BTreeSet<&'static str>,
}

/// The cases of a case list, or the problems of its `Suites:` lines.
fn cases(case_list: &str) -> Result<Vec<Case>, Vec<String>> {
    let heading = Regex::new(r"(?m)^## `([a-z0-9_]+)`[ \t]*$").expect("valid pattern");
    let headings: Vec<_> = heading.captures_iter(case_list).collect();
    let mut cases = Vec::new();
    let mut problems = Vec::new();
    for (i, captures) in headings.iter().enumerate() {
        let id = captures[1].to_string();
        let start = captures.get(0).unwrap().end();
        let end = headings
            .get(i + 1)
            .map_or(case_list.len(), |next| next.get(0).unwrap().start());
        let first_line = case_list[start..end]
            .lines()
            .map(str::trim)
            .find(|line| !line.is_empty())
            .unwrap_or_default();
        match scope(first_line) {
            Ok(suites) => cases.push(Case { id, suites }),
            Err(problem) => problems.push(format!("`{id}`: {problem}")),
        }
    }
    if problems.is_empty() {
        Ok(cases)
    } else {
        Err(problems)
    }
}

/// The suites of a case's first line: all, unless it is `Suites: <suites>` or `Suites: all except <suites>`, each
/// optionally followed by ` (<reason>)` and a period.
fn scope(first_line: &str) -> Result<BTreeSet<&'static str>, String> {
    let all: BTreeSet<&'static str> = SUITES.iter().map(|suite| suite.name).collect();
    let Some(listed) = first_line.strip_prefix("Suites:") else {
        return Ok(all);
    };
    let listed = listed.split(" (").next().unwrap_or_default();
    let listed = listed.trim().trim_end_matches('.');
    let (except, listed) = match listed.strip_prefix("all except ") {
        Some(rest) => (true, rest),
        None => (false, listed),
    };
    let mut named = BTreeSet::new();
    for name in listed.split(',').map(str::trim) {
        let suite = all
            .iter()
            .find(|suite| **suite == name)
            .ok_or_else(|| format!("unknown suite `{name}` in `Suites:`"))?;
        named.insert(*suite);
    }
    Ok(if except {
        all.difference(&named).copied().collect()
    } else {
        named
    })
}

fn read(path: &Path) -> String {
    std::fs::read_to_string(path).unwrap_or_else(|error| panic!("{}: {error}", path.display()))
}

/// The problems of all suites of a kind, as messages; empty if every suite matches the case lists.
fn problems(root: &Path, kind: &Kind) -> Vec<String> {
    let mut found = Vec::new();
    let mut expected_files: BTreeMap<&str, BTreeSet<String>> = BTreeMap::new();
    let lists_folder = case_list_folder(kind);

    let mut case_lists: Vec<PathBuf> = std::fs::read_dir(root.join(&lists_folder))
        .expect("the case list folder should exist")
        .flatten()
        .map(|entry| entry.path())
        .filter(|path| {
            path.extension().is_some_and(|extension| extension == "md")
                && path.file_name().is_some_and(|name| name != "README.md")
        })
        .collect();
    case_lists.sort();

    for case_list in &case_lists {
        let list_file = case_list
            .file_name()
            .unwrap()
            .to_string_lossy()
            .into_owned();
        let list = case_list
            .file_stem()
            .unwrap()
            .to_string_lossy()
            .into_owned();
        if kind.per_dataset && !root.join("tests/fixtures").join(&list).is_dir() {
            found.push(format!(
                "{list_file}: no fixture folder tests/fixtures/{list}"
            ));
        }
        let cases = match cases(&read(case_list)) {
            Ok(cases) => cases,
            Err(problems) => {
                found.extend(problems.iter().map(|p| format!("{list_file}: {p}")));
                continue;
            }
        };
        if cases.is_empty() {
            found.push(format!("{list_file}: no cases (headings ``## `<id>` ``)"));
        }
        let ids: BTreeSet<String> = cases.iter().map(|case| normalize(&case.id)).collect();
        if ids.len() != cases.len() {
            found.push(format!("{list_file}: duplicate case ids"));
        }

        expected_files
            .entry("Rust")
            .or_default()
            .insert(list_file.clone());
        for suite in &SUITES {
            let scoped: BTreeMap<String, &str> = cases
                .iter()
                .filter(|case| case.suites.contains(suite.name))
                .map(|case| (normalize(&case.id), case.id.as_str()))
                .collect();
            if scoped.is_empty() {
                continue;
            }
            let folder = suite.folder(kind);
            let name = file_name(suite.file_pattern, &list);
            expected_files
                .entry(suite.name)
                .or_default()
                .insert(name.clone());
            let path = root.join(&folder).join(&name);
            if !path.is_file() {
                found.push(format!(
                    "{}: {folder}/{name} is missing ({} cases of {list_file})",
                    suite.name,
                    scoped.len()
                ));
                continue;
            }
            let tests: BTreeSet<String> = Regex::new(suite.test_pattern)
                .expect("valid pattern")
                .captures_iter(&read(&path))
                .map(|captures| normalize(&captures[1]))
                .collect();
            for (normalized, id) in &scoped {
                if !tests.contains(normalized) {
                    found.push(format!("{}: {folder}/{name} lacks case `{id}`", suite.name));
                }
            }
            for test in tests.iter().filter(|test| !scoped.contains_key(*test)) {
                found.push(format!(
                    "{}: {folder}/{name} has a test not scoped to it in {list_file}: {test}",
                    suite.name
                ));
            }
        }
    }

    for suite in &SUITES {
        let folder = suite.folder(kind);
        let Ok(entries) = std::fs::read_dir(root.join(&folder)) else {
            continue;
        };
        let expected = expected_files.get(suite.name);
        let mut stray: Vec<String> = entries
            .flatten()
            .filter(|entry| entry.path().is_file())
            .map(|entry| entry.file_name().to_string_lossy().into_owned())
            .filter(|name| {
                !suite.is_helper(kind, name) && !expected.is_some_and(|files| files.contains(name))
            })
            .collect();
        stray.sort();
        for name in stray {
            found.push(format!(
                "{}: {folder}/{name} belongs to no case list",
                suite.name
            ));
        }
    }
    found
}

#[test]
fn suites_match_case_lists() {
    let root = repository_root();
    let found: Vec<String> = KINDS
        .iter()
        .flat_map(|kind| {
            problems(&root, kind)
                .into_iter()
                .map(move |problem| format!("[{}] {problem}", kind.folder))
        })
        .collect();
    assert!(
        found.is_empty(),
        "{} case list problem(s), see the README.md next to the case lists:\n{}",
        found.len(),
        found.join("\n")
    );
}

#[test]
fn names_match_across_naming_styles() {
    for name in [
        "building_count",
        "test_building_count",
        "Building count",
        "building count",
        "buildingCount",
        "BuildingCount",
    ] {
        assert_eq!(normalize(name), "buildingcount", "{name}");
    }
}

#[test]
fn file_names_of_a_case_list() {
    assert_eq!(
        file_name("{snake}.rs", "fzk-haus-citygml-3.0"),
        "fzk_haus_citygml_3_0.rs"
    );
    assert_eq!(file_name("test_{snake}.c", "fzk-haus"), "test_fzk_haus.c");
    assert_eq!(
        file_name("{pascal}Test.kt", "fzk-haus-citygml-3.0"),
        "FzkHausCitygml30Test.kt"
    );
    assert_eq!(
        file_name("{pascal}Tests.cs", "kit-bruecke"),
        "KitBrueckeTests.cs"
    );
    assert_eq!(file_name("{pascal}Tests.cs", "reader"), "ReaderTests.cs");
}

#[test]
fn case_ids_are_the_backticked_headings() {
    let case_list = "# Title\n\n## `building_count`\n\ntext\n\n## Not a case\n\n## `wall_area`\n";
    let ids: Vec<String> = cases(case_list)
        .unwrap()
        .into_iter()
        .map(|case| case.id)
        .collect();
    assert_eq!(ids, ["building_count", "wall_area"]);
}

#[test]
fn suites_of_a_case() {
    let suites = |first_line| scope(first_line).unwrap().into_iter().collect::<Vec<_>>();
    assert_eq!(suites("Some text.").len(), SUITES.len());
    assert_eq!(
        suites("Suites: Rust FFI, C, .NET (paths are bytes)."),
        [".NET", "C", "Rust FFI"]
    );
    assert_eq!(
        suites("Suites: all except Rust, TypeScript (no reason).").len(),
        SUITES.len() - 2
    );
    assert_eq!(suites("Suites: Python."), ["Python"]);
    assert!(scope("Suites: Ruby").is_err());
}
