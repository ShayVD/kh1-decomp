#!/usr/bin/env python3
"""Match overlay functions from their twins (docs/overlays.md).

The summon overlays (xs_*.x) and the others share code: the same function, compiled
from the same source, at another address with other globals. For every function not
matched yet whose instructions equal a matched one's (call targets, %hi/%lo symbols and
branch labels masked), the matched C is copied with the names mapped instruction by
instruction, tried with autodecomp's compare, and kept as ovl/<name>/hand/func_X.c.

  python3 tools/ovl/twins.py [NAME...]          # targets (default: every overlay)

Sources: one-function files (ovl/*/hand/func_X.c, matched by the last `make ovl`) and
the functions of ovl/*/auto/ files. Writes only what matches.
"""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
SYM = re.compile(r"\b(?:func|D|jtbl)_[0-9A-Fa-f]{8}\b")
LABEL = re.compile(r"\.L([0-9A-F]{8})\b")
OP_COMMENT = re.compile(r"/\* [0-9A-F]{8} [0-9A-F]{8} \*/\s*")


def overlays() -> list[str]:
    return sorted(p.parent.name for p in (ROOT / "ovl").glob("*/layout.tsv"))


def dump_asm(name: str) -> dict[str, list[str]]:
    """{func: asm lines} for every function of one overlay (cached in out/ovl/<name>/asm.json)."""
    cache = ROOT / "out" / "ovl" / name / "asm.json"
    lay = ROOT / "ovl" / name / "layout.tsv"
    if cache.exists() and cache.stat().st_mtime > lay.stat().st_mtime:
        return json.loads(cache.read_text())
    code = ("import sys, json; sys.path.insert(0, 'tools'); import kh1tool as K\n"
            "cfg = K.load_config(); names = {a: s for s, a in K.load_registry().items()}\n"
            "out = {}\n"
            "for f in K.load_layout():\n"
            "    try: out[f'func_{f.addr:08x}'] = K.function_asm(cfg, f, names).splitlines()\n"
            "    except Exception as e: pass\n"
            "print(json.dumps(out))\n")
    r = subprocess.run([sys.executable, "-c", code], cwd=ROOT, capture_output=True, text=True,
                       env=dict(os.environ, KH1_OVL=name), check=True)
    cache.parent.mkdir(parents=True, exist_ok=True)
    cache.write_text(r.stdout)
    return json.loads(r.stdout)


def norm(lines: list[str], start: int) -> list[str]:
    out = []
    for ln in lines[1:]:
        ln = OP_COMMENT.sub("", ln).strip()
        ln = LABEL.sub(lambda m: f".L+{int(m.group(1), 16) - start:x}", ln)
        out.append(SYM.sub("SYM", ln))
    return out


def mapping(src: list[str], dst: list[str]) -> dict[str, str] | None:
    m: dict[str, str] = {}
    for a, b in zip(src[1:], dst[1:]):
        sa, sb = SYM.findall(a), SYM.findall(b)
        for x, y in zip(sa, sb):
            if m.setdefault(x, y) != y:
                return None
    return m


def matched(name: str) -> set[str]:
    pl = ROOT / "out" / "ovl" / name / "gen" / "placements.tsv"
    if not pl.exists():
        return set()
    return {f"func_{l.split()[0]}" for l in pl.read_text().splitlines()[1:]}


FUNC_DEF = re.compile(r"^[A-Za-z_][^;{}()]*\b(func_[0-9a-f]{8})\s*\([^;{]*\)\s*\{", re.M)


MODES: dict[tuple[str, str], str] = {}  # (overlay, func) -> flag mode of its file (func_X.nofill.c)


def sources(name: str) -> dict[str, str]:
    """{func: self-contained C} of the matched functions of one overlay."""
    out = {}
    for p in sorted((ROOT / "ovl" / name).rglob("*.c")):
        text = p.read_text()
        defs = list(FUNC_DEF.finditer(text))
        if p.parent.name == "hand" and len(defs) == 1:
            out[defs[0].group(1)] = text
            if len(p.suffixes) > 1:
                MODES[(name, defs[0].group(1))] = p.suffixes[-2][1:]
            continue
        # an auto/ file: every declaration line plus the one function body
        head = text[: defs[0].start()] if defs else text
        for k, d in enumerate(defs):
            end = defs[k + 1].start() if k + 1 < len(defs) else len(text)
            out[d.group(1)] = head + text[d.start(): end]
    return out


def try_file(name: str, func: str, code: str, mode: str = "") -> bool:
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as fh:
        fh.write(code)
        path = fh.name
    try:
        r = subprocess.run([sys.executable, "tools/autodecomp.py", "try", func, "--file", path], cwd=ROOT,
                           capture_output=True, text=True, env=dict(os.environ, KH1_OVL=name, KH1_MODE=mode))
    finally:
        os.unlink(path)
    return " MATCH " in r.stdout


def main() -> int:
    targets = sys.argv[1:] or overlays()
    asm = {n: dump_asm(n) for n in overlays()}
    shapes: dict[tuple, list[tuple[str, str]]] = {}
    for n in overlays():
        done = matched(n)
        for f in done:
            if f in asm[n]:
                start = int(f[5:], 16)
                shapes.setdefault(tuple(norm(asm[n][f], start)), []).append((n, f))
    srcs = {n: sources(n) for n in overlays()}
    found = 0
    for t in targets:
        done = matched(t)
        for g, lines in sorted(asm[t].items()):
            if g in done or list((ROOT / "ovl" / t / "hand").glob(f"{g}.*c")):
                continue
            key = tuple(norm(lines, int(g[5:], 16)))
            for n, f in shapes.get(key, []):
                code = srcs[n].get(f)
                if code is None:
                    continue
                mp = mapping(asm[n][f], lines)
                if mp is None:
                    continue
                mp[f] = g
                new = SYM.sub(lambda m: mp.get(m.group(0), m.group(0)), code)
                # names only the C has (declarations of unused externs) stay as they are
                new = re.sub(r"\A/\*[^\n]*\*/\n", "", new)
                mode = MODES.get((n, f), "")
                if try_file(t, g, new, mode):
                    out = ROOT / "ovl" / t / "hand" / (f"{g}.{mode}.c" if mode else f"{g}.c")
                    out.parent.mkdir(parents=True, exist_ok=True)
                    out.write_text(f"/* {t}.x {g}: the twin of {n}.x {f} (tools/ovl/twins.py). */\n" + new)
                    print(f"{t} {g} <- {n} {f}")
                    found += 1
                    break
    print(f"twins: {found} matched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
