//! Thins the point clouds of a CityGML file by keeping every n-th `gml:Point` of each `gml:pointMembers`.
//!
//! Used to derive a small fixture from a point cloud example (see ../fzk-haus-citygml-3.0/README.md). The file is
//! processed line by line on raw bytes: only whole `<gml:Point>` ... `</gml:Point>` blocks are removed, every other
//! byte (including line endings) is kept. Expects each `gml:Point` to start and end on lines of its own, as in the FZK
//! Haus examples.
//!
//! Dependency-free, so it builds with `rustc` alone:
//!
//! ```bash
//! rustc --edition 2024 -O thin_point_clouds.rs -o /tmp/thin_point_clouds
//! /tmp/thin_point_clouds INPUT OUTPUT [STRIDE]   # STRIDE defaults to 1000
//! ```

use std::process::ExitCode;
use std::{env, fs};

const USAGE: &str = "Usage: thin_point_clouds INPUT OUTPUT [STRIDE]   (STRIDE defaults to 1000)";
const DEFAULT_STRIDE: usize = 1000;

const POINT_MEMBERS_START: &[u8] = b"<gml:pointMembers>";
const POINT_MEMBERS_END: &[u8] = b"</gml:pointMembers>";
const POINT_START: &[u8] = b"<gml:Point>";
const POINT_END: &[u8] = b"</gml:Point>";

/// The thinned lines and the number of points before and after.
struct Thinned<'a> {
    lines: Vec<&'a [u8]>,
    before: usize,
    after: usize,
}

fn contains(line: &[u8], pattern: &[u8]) -> bool {
    line.windows(pattern.len()).any(|window| window == pattern)
}

/// The lines of `data` with their line endings (`\n`, `\r\n` or `\r`), as Python's `bytes.splitlines(keepends=True)`.
fn split_lines(data: &[u8]) -> Vec<&[u8]> {
    let mut lines = Vec::new();
    let mut start = 0;
    let mut i = 0;
    while i < data.len() {
        let end = match data[i] {
            b'\n' => Some(i + 1),
            b'\r' if data.get(i + 1) == Some(&b'\n') => Some(i + 2),
            b'\r' => Some(i + 1),
            _ => None,
        };
        match end {
            Some(end) => {
                lines.push(&data[start..end]);
                start = end;
                i = end;
            }
            None => i += 1,
        }
    }
    if start < data.len() {
        lines.push(&data[start..]);
    }
    lines
}

/// The lines with every `stride`-th point of each point list kept (the first, then every stride-th after it).
fn thin<'a>(lines: &[&'a [u8]], stride: usize) -> Result<Thinned<'a>, String> {
    let mut output = Vec::new();
    let mut in_point_members = false;
    let mut point: Option<Vec<&[u8]>> = None;
    let mut index = 0;
    let (mut before, mut after) = (0, 0);
    for &line in lines {
        if in_point_members && point.is_none() && contains(line, POINT_START) {
            point = Some(Vec::new());
        }
        if let Some(point_lines) = point.as_mut() {
            point_lines.push(line);
            if contains(line, POINT_END) {
                before += 1;
                if index % stride == 0 {
                    output.extend_from_slice(point_lines);
                    after += 1;
                }
                index += 1;
                point = None;
            }
            continue;
        }
        if contains(line, POINT_MEMBERS_START) {
            in_point_members = true;
            index = 0;
        } else if contains(line, POINT_MEMBERS_END) {
            in_point_members = false;
        }
        output.push(line);
    }
    if point.is_some() {
        return Err("unterminated <gml:Point>".to_owned());
    }
    Ok(Thinned {
        lines: output,
        before,
        after,
    })
}

/// Thins `input` into `output`; the number of points before and after.
fn run(input: &str, output: &str, stride: usize) -> Result<(usize, usize), String> {
    let data = fs::read(input).map_err(|error| format!("cannot read {input}: {error}"))?;
    let thinned = thin(&split_lines(&data), stride)?;
    fs::write(output, thinned.lines.concat()).map_err(|error| format!("cannot write {output}: {error}"))?;
    Ok((thinned.before, thinned.after))
}

fn main() -> ExitCode {
    let args: Vec<String> = env::args().skip(1).collect();
    if !(2..=3).contains(&args.len()) {
        eprintln!("{USAGE}");
        return ExitCode::from(2);
    }
    let stride = match args.get(2).map(|stride| stride.parse::<usize>()) {
        None => DEFAULT_STRIDE,
        Some(Ok(stride)) if stride >= 1 => stride,
        Some(_) => {
            eprintln!("STRIDE must be an integer of at least 1");
            return ExitCode::from(2);
        }
    };
    match run(&args[0], &args[1], stride) {
        Ok((before, after)) => {
            println!("kept {after} of {before} points (every {stride}th)");
            ExitCode::SUCCESS
        }
        Err(error) => {
            eprintln!("error: {error}");
            ExitCode::FAILURE
        }
    }
}
