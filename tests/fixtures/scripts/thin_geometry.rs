//! Thins the geometry and drops the global appearances of a CityGML file, keeping its features, attributes and
//! references.
//!
//! Used to derive a small fixture from a large example. Three kinds of elements are removed, matched by local name:
//!
//! - every `appearanceMember` of the root `CityModel` (the global appearances, e.g. texture coordinates);
//! - every `surfaceMember` of a `MultiSurface` or `CompositeSurface` but the first;
//! - every `Triangle` of a `patches` or `trianglePatches` (a TIN) but the first.
//!
//! The file is processed as raw bytes, tag by tag: a removed element goes with the whitespace before it (its
//! indentation and preceding line ending), every other byte is kept. Comments, processing instructions and CDATA
//! sections are copied as they are.
//!
//! Dependency-free, so it builds with `rustc` alone:
//!
//! ```bash
//! rustc --edition 2024 -O thin_geometry.rs -o /tmp/thin_geometry
//! /tmp/thin_geometry INPUT OUTPUT
//! ```

use std::process::ExitCode;
use std::{env, fs};

const USAGE: &str = "Usage: thin_geometry INPUT OUTPUT";

/// The aggregates whose `surfaceMember`s are thinned to the first.
const SURFACE_AGGREGATES: [&[u8]; 2] = [b"MultiSurface", b"CompositeSurface"];
/// The patch lists whose `Triangle`s are thinned to the first.
const TRIANGLE_LISTS: [&[u8]; 2] = [b"patches", b"trianglePatches"];

/// An open element: its local name and the number of children it kept so far that are thinned to the first.
struct Frame<'a> {
    local_name: &'a [u8],
    kept: usize,
}

/// What was removed and kept.
#[derive(Default)]
struct Counts {
    appearance_members: usize,
    surface_members_kept: usize,
    surface_members_removed: usize,
    triangles_kept: usize,
    triangles_removed: usize,
}

/// The part of a qualified name after the prefix (`gml:Triangle` → `Triangle`).
fn local_name(name: &[u8]) -> &[u8] {
    match name.iter().position(|&byte| byte == b':') {
        Some(colon) => &name[colon + 1..],
        None => name,
    }
}

fn find(data: &[u8], from: usize, pattern: &[u8]) -> Option<usize> {
    data[from..]
        .windows(pattern.len())
        .position(|window| window == pattern)
        .map(|position| from + position)
}

/// The end (exclusive) of the tag starting at `start`, skipping `>` inside quoted attribute values.
fn tag_end(data: &[u8], start: usize) -> Option<usize> {
    let mut quote = None;
    for (offset, &byte) in data[start..].iter().enumerate() {
        match (quote, byte) {
            (None, b'"' | b'\'') => quote = Some(byte),
            (Some(open), _) if byte == open => quote = None,
            (None, b'>') => return Some(start + offset + 1),
            _ => {}
        }
    }
    None
}

/// The name of the element tag `tag` (`<name ...>`, `</name>` or `<name/>`).
fn tag_name(tag: &[u8]) -> &[u8] {
    let name = tag.strip_prefix(b"</").or_else(|| tag.strip_prefix(b"<")).unwrap_or(tag);
    let end = name
        .iter()
        .position(|&byte| byte.is_ascii_whitespace() || byte == b'>' || byte == b'/')
        .unwrap_or(name.len());
    &name[..end]
}

/// The end (exclusive) of the markup that is not an element tag at `start` (comment, CDATA, processing instruction
/// or declaration), or `None` if `start` begins an element tag.
fn other_markup_end(data: &[u8], start: usize) -> Option<Result<usize, String>> {
    let rest = &data[start..];
    let (terminator, what): (&[u8], &str) = if rest.starts_with(b"<!--") {
        (b"-->", "comment")
    } else if rest.starts_with(b"<![CDATA[") {
        (b"]]>", "CDATA section")
    } else if rest.starts_with(b"<?") {
        (b"?>", "processing instruction")
    } else if rest.starts_with(b"<!") {
        (b">", "declaration")
    } else {
        return None;
    };
    Some(
        find(data, start + 2, terminator)
            .map(|end| end + terminator.len())
            .ok_or_else(|| format!("unterminated {what} at byte {start}")),
    )
}

/// Whether the child `local_name` of the open elements `stack` is removed; counts what is kept and removed.
fn removes(stack: &mut [Frame], local_name: &[u8], counts: &mut Counts) -> bool {
    let depth = stack.len();
    let Some(parent) = stack.last_mut() else {
        return false;
    };
    if depth == 1 && parent.local_name == b"CityModel" && local_name == b"appearanceMember" {
        counts.appearance_members += 1;
        return true;
    }
    let (kept, removed) = if SURFACE_AGGREGATES.contains(&parent.local_name) && local_name == b"surfaceMember" {
        (&mut counts.surface_members_kept, &mut counts.surface_members_removed)
    } else if TRIANGLE_LISTS.contains(&parent.local_name) && local_name == b"Triangle" {
        (&mut counts.triangles_kept, &mut counts.triangles_removed)
    } else {
        return false;
    };
    if parent.kept == 0 {
        parent.kept = 1;
        *kept += 1;
        false
    } else {
        *removed += 1;
        true
    }
}

/// `data` with the elements described in the module documentation removed.
fn thin(data: &[u8]) -> Result<(Vec<u8>, Counts), String> {
    let mut output = Vec::with_capacity(data.len());
    let mut counts = Counts::default();
    let mut stack: Vec<Frame> = Vec::new();
    // The depth of the stack at which the element being removed was opened.
    let mut removing: Option<usize> = None;
    // The start of the input not yet copied to the output.
    let mut copied_to = 0;
    let mut position = 0;

    while let Some(start) = find(data, position, b"<") {
        if let Some(end) = other_markup_end(data, start) {
            position = end?;
            continue;
        }
        let end = tag_end(data, start).ok_or_else(|| format!("unterminated tag at byte {start}"))?;
        let tag = &data[start..end];
        let closing = tag.starts_with(b"</");
        let self_closing = tag.ends_with(b"/>");
        let name = local_name(tag_name(tag));
        position = end;

        if closing {
            let frame = stack
                .pop()
                .ok_or_else(|| format!("unexpected closing tag at byte {start}"))?;
            if frame.local_name != name {
                return Err(format!("mismatched closing tag at byte {start}"));
            }
            if removing == Some(stack.len()) {
                removing = None;
                copied_to = end;
            }
            continue;
        }
        if removing.is_none() && removes(&mut stack, name, &mut counts) {
            // Copy what precedes the element, without the whitespace right before it.
            let preceding = &data[copied_to..start];
            let kept = preceding
                .iter()
                .rposition(|byte| !byte.is_ascii_whitespace())
                .map_or(0, |last| last + 1);
            output.extend_from_slice(&preceding[..kept]);
            if self_closing {
                copied_to = end;
            } else {
                removing = Some(stack.len());
            }
        }
        if !self_closing {
            stack.push(Frame {
                local_name: name,
                kept: 0,
            });
        }
    }
    if !stack.is_empty() {
        return Err("unclosed elements at the end of the input".to_owned());
    }
    output.extend_from_slice(&data[copied_to..]);
    Ok((output, counts))
}

fn run(input: &str, output: &str) -> Result<Counts, String> {
    let data = fs::read(input).map_err(|error| format!("cannot read {input}: {error}"))?;
    let (thinned, counts) = thin(&data)?;
    fs::write(output, thinned).map_err(|error| format!("cannot write {output}: {error}"))?;
    Ok(counts)
}

fn main() -> ExitCode {
    let args: Vec<String> = env::args().skip(1).collect();
    if args.len() != 2 {
        eprintln!("{USAGE}");
        return ExitCode::from(2);
    }
    match run(&args[0], &args[1]) {
        Ok(counts) => {
            println!("removed {} global appearance members", counts.appearance_members);
            println!(
                "kept {} of {} surface members, {} of {} triangles",
                counts.surface_members_kept,
                counts.surface_members_kept + counts.surface_members_removed,
                counts.triangles_kept,
                counts.triangles_kept + counts.triangles_removed,
            );
            ExitCode::SUCCESS
        }
        Err(error) => {
            eprintln!("error: {error}");
            ExitCode::FAILURE
        }
    }
}
