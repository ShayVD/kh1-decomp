#!/usr/bin/env python3
"""Write docs/progress.svg, the README's progress bars, from committed files only.

  python3 tools/progress_badge.py           # or `make progress-badge`

No game data and no compiler, so it runs in CI without KH1_ELF_URL (.github/workflows/
progress.yml, on pushes to main). It reads the same facts `make progress` and
`make ovl-progress` measure against the ELF, under the rule that nothing non-matching is
ever built (a non-matching function fails `make verify` and lives in nonmatchings/):

  main ELF   every function in layout.tsv, less the ones in shift/unmatched/ (the asm
             exports of what src/ does not place yet)
  overlays   every function in ovl/NAME/layout.tsv that ovl/NAME's sources define;
             CONTEXT_ONLY stubs and `#if 0` blocks define nothing

Numbers are code bytes (function sizes from the layouts), as in docs/progress.md.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SVG = ROOT / "docs" / "progress.svg"

COMMENT_OR_LITERAL = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
FUNC_NAME = re.compile(r"\b(func_[0-9a-f]{8})\s*\(")
ASM_LABEL = re.compile(r"^(func_[0-9a-f]{8}):", re.M)


def live_code(text: str) -> str:
    """C source without comments, literals, preprocessor lines and `#if 0` branches."""
    out, stack = [], []
    for line in COMMENT_OR_LITERAL.sub(" ", text).replace("\\\n", " ").split("\n"):
        d = line.strip()
        if not d.startswith("#"):
            if all(stack):
                out.append(line)
            continue
        d = d[1:].strip()
        if d.startswith("if"):
            stack.append(not re.match(r"if\s+0\b", d))
        elif d.startswith(("else", "elif")) and stack:
            stack[-1] = not stack[-1]
        elif d.startswith("endif") and stack:
            stack.pop()
    return "\n".join(out)


def c_definitions(text: str) -> set[str]:
    """func_XXXXXXXX names given a body at file scope (not CONTEXT_ONLY) in C source."""
    found, depth, decl = set(), 0, ""
    for c in live_code(text):
        if c == "{":
            if depth == 0 and "CONTEXT_ONLY" not in decl:
                m = FUNC_NAME.search(decl)
                if m and "=" not in decl[:m.start()]:
                    found.add(m.group(1))
            depth, decl = depth + 1, ""
        elif c == "}":
            depth, decl = depth - 1, ""
        elif depth == 0:
            decl = "" if c == ";" else decl + c
    return found


def source_definitions(root: Path) -> set[str]:
    found = set()
    for f in root.rglob("*"):
        if f.suffix == ".c":
            found |= c_definitions(f.read_text(errors="replace"))
        elif f.suffix == ".s":
            found |= set(ASM_LABEL.findall(f.read_text(errors="replace")))
    return found


def load_layout(path: Path) -> list[tuple[str, int]]:
    """(name, size) of each function; addr / end / size / name columns."""
    rows = [l.split("\t") for l in path.read_text().splitlines() if l and not l.startswith(("#", "addr"))]
    return [(r[3], int(r[2])) for r in rows]


def tally(funcs: list[tuple[str, int]], matched) -> dict:
    done = [size for name, size in funcs if matched(name)]
    return {"matched": len(done), "funcs": len(funcs), "matched_bytes": sum(done),
            "bytes": sum(size for _, size in funcs)}


def main_elf() -> dict:
    layout = load_layout(ROOT / "layout.tsv")
    unmatched = {p.stem for p in (ROOT / "shift" / "unmatched").glob("func_*.s")}
    if not unmatched <= {name for name, _ in layout}:
        sys.exit(f"error: shift/unmatched/ has functions not in layout.tsv: {sorted(unmatched - {n for n, _ in layout})}")
    placed = unmatched & source_definitions(ROOT / "src")
    if placed:
        sys.exit(f"error: matched in src/ but still in shift/unmatched/: {sorted(placed)}")
    return tally(layout, lambda name: name not in unmatched)


def overlays() -> dict:
    total = {"matched": 0, "funcs": 0, "matched_bytes": 0, "bytes": 0}
    for layout in sorted((ROOT / "ovl").glob("*/layout.tsv")):
        defined = source_definitions(layout.parent)
        funcs = load_layout(layout)
        unknown = defined - {name for name, _ in funcs}
        if unknown:
            sys.exit(f"error: {layout.parent.name} defines functions not in its layout: {sorted(unknown)}")
        t = tally(funcs, lambda name: name in defined)
        for k in total:
            total[k] += t[k]
    return total


def percent(a: int, b: int) -> float:
    """Rounded down, so 99.996% never reads as 100.00% with work left."""
    return a * 10000 // b / 100


def render(rows: list[tuple[str, dict]]) -> str:
    # Inline attributes only: GitHub sanitizes the SVG and its <img> gets no page CSS. The
    # dark card keeps its own contrast on both of GitHub's themes.
    width, row_h, top = 720, 44, 74
    bar_x, bar_w, bar_h = 132, 372, 10
    height = top + row_h * len(rows) + 8
    font = "-apple-system,BlinkMacSystemFont,'Segoe UI',Helvetica,Arial,sans-serif"
    head = rows[0][1]
    summary = (f"{percent(head['matched_bytes'], head['bytes']):.2f}% of code bytes matched, "
               f"{head['matched']:,} of {head['funcs']:,} functions; work in progress")
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
           f'viewBox="0 0 {width} {height}" role="img" aria-label="Decompilation progress: {summary}">',
           f"<title>Decompilation progress: {summary}</title>",
           f'<rect x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="8" fill="#161b22" stroke="#30363d"/>',
           f'<g font-family="{font}" fill="#e6edf3">',
           '<text x="20" y="31" font-size="17" font-weight="600">Decompilation progress</text>',
           '<text x="20" y="52" font-size="13" fill="#9198a1">'
           "Work in progress. Bars show code bytes identical to the original.</text>"]
    for i, (label, t) in enumerate(rows):
        y = top + row_h * i
        share = t["matched_bytes"] / t["bytes"]
        fill = max(round(bar_w * share), bar_h) if t["matched_bytes"] else 0
        weight = ' font-weight="600"' if i == 0 else ""
        out += [f'<text x="20" y="{y + 15}" font-size="14"{weight}>{label}</text>',
                f'<rect x="{bar_x}" y="{y + 5}" width="{bar_w}" height="{bar_h}" rx="4" fill="#30363d"/>',
                f'<rect x="{bar_x}" y="{y + 5}" width="{fill}" height="{bar_h}" rx="4" fill="#4493f8"/>',
                f'<text x="{bar_x + bar_w + 62}" y="{y + 15}" font-size="14" text-anchor="end"{weight}>'
                f"{percent(t['matched_bytes'], t['bytes']):.2f}%</text>",
                f'<text x="{width - 20}" y="{y + 15}" font-size="12" text-anchor="end" fill="#9198a1">'
                f"{t['matched']:,} / {t['funcs']:,} funcs</text>"]
    return "\n".join(out + ["</g>", "</svg>", ""])


def main() -> int:
    elf, ovl = main_elf(), overlays()
    rows = [("All code", {k: elf[k] + ovl[k] for k in elf}), ("Main ELF", elf), ("Overlays", ovl)]
    for label, t in rows:
        print(f"{label:<9} {t['matched']:>5} / {t['funcs']:<5} functions  "
              f"{t['matched_bytes']:>8} / {t['bytes']:<8} bytes  {percent(t['matched_bytes'], t['bytes']):.2f}%")
    SVG.write_text(render(rows))
    print(f"wrote {SVG.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
