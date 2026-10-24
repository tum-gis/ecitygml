"""Runs the scripts in examples/snippets/ (short programs giving a first impression of the bindings) and compares their output with the
expected output shared by all languages: for every `tests/expected/snippets/<snippet>/<dataset>/<fixture>.txt`,
the snippet runs on `tests/fixtures/<dataset>/<fixture>.gml` and must print that text."""

import subprocess
import sys
from pathlib import Path

import pytest

SNIPPETS = Path(__file__).parents[1] / "examples" / "snippets"
EXPECTED = Path(__file__).parents[5] / "tests" / "expected" / "snippets"
FIXTURES = Path(__file__).parents[5] / "tests" / "fixtures"

# Snippets that write a file, and its extension (the snippet's second argument).
OUTPUT_EXTENSIONS = {"translate_to_local_coordinates": ".gml"}

# The fixture of `<program>/<dataset>/<fixture>.txt` is `<dataset>/<fixture>`, as in `tests/fixtures`.
CASES = sorted(
    (path.parent.parent.name, f"{path.parent.name}/{path.stem}") for path in EXPECTED.glob("*/*/*.txt")
)


@pytest.mark.parametrize(("snippet", "fixture"), CASES, ids=[f"{s}-{f}" for s, f in CASES])
def test_expected_output(snippet: str, fixture: str, tmp_path: Path) -> None:
    args = [str(FIXTURES / f"{fixture}.gml")]
    extension = OUTPUT_EXTENSIONS.get(snippet)
    if extension is not None:
        args.append(str(tmp_path / f"output{extension}"))
    result = subprocess.run([sys.executable, str(SNIPPETS / f"{snippet}.py"), *args], capture_output=True, text=True)
    assert result.returncode == 0, result.stderr
    assert result.stdout == (EXPECTED / snippet / f"{fixture}.txt").read_text()
    expected_file = EXPECTED / snippet / f"{fixture}{extension}"
    if extension is not None and expected_file.exists():
        assert Path(args[1]).read_bytes() == expected_file.read_bytes()


def test_every_snippet_has_expected_output() -> None:
    assert sorted({s for s, _ in CASES}) == sorted(p.stem for p in SNIPPETS.glob("*.py"))
