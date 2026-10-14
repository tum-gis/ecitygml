"""Runs the scripts in examples/ and compares their output with the expected output shared by all
languages: for every `tests/expected/examples/<example>/<fixture>.txt`, the example runs on
`tests/fixtures/<fixture>.gml` and must print that text. Examples that write a file get a temporary
output path; if `expected/<example>/<fixture><extension>` exists, the file must match it too."""

import subprocess
import sys
from pathlib import Path

import pytest

EXAMPLES = Path(__file__).parents[1] / "examples"
EXPECTED = Path(__file__).parents[5] / "tests" / "expected" / "examples"
FIXTURES = Path(__file__).parents[5] / "tests" / "fixtures"
# Examples with an output file, and its extension.
OUTPUT_EXTENSIONS = {"06_export_obj": ".obj", "07_convert": ".gml.gz"}

CASES = sorted((path.parent.name, path.stem) for path in EXPECTED.glob("*/*.txt"))


def run(script: str, *args: str) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [sys.executable, str(EXAMPLES / script), *args], capture_output=True, text=True
    )


@pytest.mark.parametrize(("example", "fixture"), CASES, ids=[f"{e}-{f}" for e, f in CASES])
def test_expected_output(example: str, fixture: str, tmp_path: Path) -> None:
    args = [str(FIXTURES / f"{fixture}.gml")]
    extension = OUTPUT_EXTENSIONS.get(example)
    if extension is not None:
        args.append(str(tmp_path / f"output{extension}"))
    result = run(f"{example}.py", *args)
    assert result.returncode == 0, result.stderr
    assert result.stdout == (EXPECTED / example / f"{fixture}.txt").read_text()
    expected_file = EXPECTED / example / f"{fixture}{extension}"
    if extension is not None and expected_file.exists():
        assert Path(args[1]).read_text() == expected_file.read_text()


def test_every_example_has_expected_output() -> None:
    assert sorted({e for e, _ in CASES}) == sorted(p.stem for p in EXAMPLES.glob("[0-9][0-9]_*.py"))


def test_missing_file() -> None:
    result = run("01_read_city_model.py", str(FIXTURES / "does-not-exist.gml"))
    assert result.returncode == 1
    assert "No such file" in result.stderr


def test_usage() -> None:
    assert run("01_read_city_model.py").returncode == 2
    assert run("07_convert.py", "only-one-argument.gml").returncode == 2
