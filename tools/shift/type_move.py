#!/usr/bin/env python3
"""Move file-local C types into a header (phase 4, used by define_shared.py --mixed).

  python3 -I tools/shift/type_move.py SRC TYPE [TYPE ...] [--apply]

A shared bss name whose best declaration uses a struct (or typedef) that only
one source file defines needs that type in a header, so src/data/ can define
the name with it. For SRC (say src/hand/text_00110000_h29.c) this finds the
file-scope `typedef` / `struct X {...};` statements that define each TYPE and,
recursively, the file's own types they use, and moves them, in file order and
verbatim, to include/data/types/<name>.h (the path under src/ without hand/,
"/" -> "_", so variants differ). SRC includes that header where the
first moved statement was. Types emit no code, so the object is unchanged
(`make` checks it). The header copies SRC's own `#include` lines that live in
include/ (common.h, m2c.h, ...), so it compiles on its own.

Refused (printed, nothing written): a TYPE SRC does not define at file scope,
a header that already exists, a statement that is inside `#if` (it would lose
its condition), or a moved statement using a macro SRC #defines."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
KEYWORDS = {"typedef", "struct", "union", "enum", "const", "volatile", "unsigned", "signed",
            "char", "short", "int", "long", "float", "double", "void", "static", "extern",
            "__attribute__", "aligned", "packed", "sizeof", "inline", "register"}
IDENT = re.compile(r"[A-Za-z_]\w*")


def blank_comments(text: str) -> str:
    """Comments and string/char literals replaced by spaces (newlines kept)."""
    out, i, n = [], 0, len(text)
    while i < n:
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", text[i:j]))
            i = j
        elif text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif text[i] in "\"'":
            q, j = text[i], i + 1
            while j < n and text[j] != q:
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(text[i] + " " * (j - i - 2) + (text[j - 1] if j - i >= 2 else ""))
            i = j
        else:
            out.append(text[i])
            i += 1
    return "".join(out)


def statements(text: str):
    """File-scope statements: (start, end, kind, conditional) spans of text.
    kind: 'pp' (a preprocessor line), 'func' (a function body), 'decl'."""
    b = blank_comments(text)
    out, i, n, depth, cond = [], 0, len(b), 0, 0
    while i < n:
        while i < n and b[i] in " \t\r\n":
            i += 1
        if i >= n:
            break
        if b[i] == "#":
            j = i
            while True:
                k = b.find("\n", j)
                k = n if k < 0 else k
                if b[k - 1:k] == "\\" and k < n:
                    j = k + 1
                    continue
                break
            line = b[i:k]
            if re.match(r"#\s*if", line):
                cond += 1
            elif re.match(r"#\s*endif", line):
                cond -= 1
            out.append((i, k, "pp", cond > 0))
            i = k
            continue
        start, j, first_brace = i, i, None
        while j < n:
            c = b[j]
            if c in "{([":
                if c == "{" and depth == 0 and first_brace is None:
                    first_brace = j
                depth += 1
            elif c in "})]":
                depth -= 1
                if c == "}" and depth == 0:
                    head = b[start:first_brace]
                    if (")" in head and not re.match(r"\s*(typedef|struct|union|enum)\b", head)
                            and "=" not in head):
                        j += 1
                        out.append((start, j, "func", cond > 0))
                        break
            elif c == ";" and depth == 0:
                j += 1
                out.append((start, j, "decl", cond > 0))
                break
            elif c == "#" and depth == 0 and b[j - 1] == "\n":
                break  # a preprocessor line inside a declaration: stop here
            j += 1
        else:
            out.append((start, n, "decl", cond > 0))
        i = j if j > i else i + 1
    return out


def defines(stmt: str) -> tuple[set[str], set[str]]:
    """(typedef names, struct/union/enum tags with a body) a statement defines."""
    s = re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", stmt, flags=re.S)
    tags = set(re.findall(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{", s))
    names = set()
    if re.match(r"\s*typedef\b", s):
        # the declarators follow the last top-level '}' (struct/union) or the base type
        k = s.rfind("}")
        tail = s[k + 1:] if k >= 0 else re.sub(r"^\s*typedef\s+((?:(?:struct|union|enum|unsigned|signed|const|volatile)\s+)*[A-Za-z_]\w*)", "", s)
        tail = re.sub(r"\([^()]*\)\s*;", ";", tail)  # function typedef parameter list
        for m in IDENT.finditer(tail):
            if m.group(0) not in KEYWORDS:
                names.add(m.group(0))
    return names, tags


def uses(stmt: str) -> tuple[set[str], set[str]]:
    s = re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", stmt, flags=re.S)
    tags = set(re.findall(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)", s))
    return set(IDENT.findall(s)) - KEYWORDS, tags


def plan(src: Path, types: list[str]):
    text = src.read_text()
    b = blank_comments(text)
    sts = statements(text)
    info = []
    for st, en, kind, cond in sts:
        names, tags = defines(b[st:en]) if kind == "decl" else (set(), set())
        info.append((st, en, kind, cond, names, tags))
    by_name, by_tag = {}, {}
    for k, (_st, _en, _kind, _cond, names, tags) in enumerate(info):
        for nm in names:
            by_name.setdefault(nm, k)
        for t in tags:
            by_tag.setdefault(t, k)
    macros = set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", b, re.M))
    todo, take = [], set()
    for t in types:
        if t not in by_name:
            return None, f"{t}: no file-scope typedef in {src.relative_to(ROOT)}"
        todo.append(by_name[t])
    while todo:
        k = todo.pop()
        if k in take:
            continue
        take.add(k)
        st, en, _kind, cond, names, tags = info[k]
        if cond:
            return None, f"statement at offset {st} is inside #if"
        ids, utags = uses(b[st:en])
        if ids & macros:
            return None, f"uses macros {sorted(ids & macros)}"
        for nm in ids:
            if nm in by_name and by_name[nm] not in take and by_name[nm] != k:
                todo.append(by_name[nm])
        for t in utags:
            if t in by_tag and by_tag[t] not in take and by_tag[t] != k:
                todo.append(by_tag[t])
    return sorted(take), info


def header_types(hdr: Path) -> set[str]:
    """Typedef names a header written by apply() defines."""
    text = hdr.read_text()
    b = blank_comments(text)
    names = set()
    for st, en, kind, _c in statements(text):
        if kind == "decl":
            names |= defines(b[st:en])[0]
    return names


def header_name(src: Path) -> str:
    """src/hand/nostrict/text_X.c -> nostrict_text_X (variants of one file differ)."""
    rel = src.resolve().relative_to(ROOT / "src").with_suffix("")
    parts = [x for x in rel.parts if x != "hand"]
    return "_".join(parts)


def header_path(src: Path) -> Path:
    return ROOT / "include/data/types" / f"{header_name(src)}.h"


def apply(src: Path, take: list[int], info) -> Path:
    text = src.read_text()
    hdr = header_path(src)
    stem = header_name(src)
    guard = "KH1_DATA_TYPES_" + re.sub(r"\W", "_", stem).upper() + "_H"
    incs = []
    for ln in text.splitlines():
        m = re.match(r'\s*#\s*include\s+[<"]([^>"]+)[>"]', ln)
        if m and (ROOT / "include" / m.group(1)).exists() and not m.group(1).startswith("data/"):
            incs.append(f'#include "{m.group(1)}"')
    body = [text[info[k][0]:info[k][1]] for k in take]
    rel = src.relative_to(ROOT)
    h = [f"/* Types moved from {rel} (phase 4, tools/shift/type_move.py). */",
         f"#ifndef {guard}", f"#define {guard}", ""] + incs + [""] + body + ["", f"#endif /* {guard} */", ""]
    hdr.parent.mkdir(parents=True, exist_ok=True)
    hdr.write_text("\n".join(h))
    # cut the statements out of src, back to front; the include replaces the first
    out = text
    for k in reversed(take):
        st, en = info[k][0], info[k][1]
        # take the rest of the line too when it is blank, and the line's indentation
        ls = out.rfind("\n", 0, st) + 1
        le = out.find("\n", en)
        le = len(out) if le < 0 else le
        whole = out[ls:st].strip() == "" and out[en:le].strip() == ""
        rep = f'#include "data/types/{stem}.h"' if k == take[0] else ""
        if whole:
            out = out[:ls] + (rep + "\n" if rep else "") + out[le + 1:]
        else:
            out = out[:st] + rep + out[en:]
    src.write_text(out)
    return hdr


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("src")
    ap.add_argument("types", nargs="+")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    src = (ROOT / a.src).resolve()
    if header_path(src).exists():
        print(f"{header_path(src).relative_to(ROOT)} exists")
        return 1
    take, info = plan(src, a.types)
    if take is None:
        print(info)
        return 1
    text = src.read_text()
    for k in take:
        print(text[info[k][0]:info[k][1]])
    if a.apply:
        print(apply(src, take, info).relative_to(ROOT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
