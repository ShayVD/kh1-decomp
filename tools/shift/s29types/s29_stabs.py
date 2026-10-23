#!/usr/bin/env python3
"""Struct layouts of a file's types, read from gcc's stabs (session 29).

  python3 -I tools/shift/s29types/s29_stabs.py FILE.c TYPE [TYPE ...]
  python3 -I tools/shift/s29types/s29_stabs.py --flat FILE.c TYPE

Compiles FILE.c with its objects.mk recipe plus -gstabs (to a scratch .s) and
parses the `.stabs "Name:tN=..."` type entries.  Prints each type's members
(byte offset, bit offset/size for bit-fields, size, type) and with --flat the
leaves (scalars, arrays of scalars, pointers, bit-fields) by full path.
A struct/union/array/pointer type is printed as gcc knows it, so two files'
types can be compared leaf by leaf (`flat()`).
"""
import re, subprocess, sys, tempfile
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402

BASE = {  # stabs base type name -> our spelling
    "int": "s32", "char": "s8", "long int": "s64", "unsigned int": "u32", "long unsigned int": "u64",
    "long long int": "s64", "long long unsigned int": "u64", "short int": "s16",
    "short unsigned int": "u16", "signed char": "s8", "unsigned char": "u8", "float": "f32",
    "double": "f64", "long double": "f64", "void": "void",
}


def stabs_of(rel, text=None):
    cmd = L.recipes()[rel]
    with tempfile.TemporaryDirectory(dir=L.SCR) as td:
        src = L.ROOT / rel
        name = rel
        tmp = None
        if text is not None:
            tmp = src.with_name(".s29tmp_" + src.name)
            tmp.write_text(text)
            name = str(tmp.relative_to(L.ROOT))
        try:
            c = cmd.replace("$(TOOLCHAIN)", str(L.TOOLCHAIN)).replace("$(INCLUDES)", "-Iinclude -Isrc")
            c = c.replace("$(@:.o=.s)", f"{td}/o.s").replace(" " + rel, " " + name)
            c = c.replace(" -S ", " -S -gstabs ")
            r = subprocess.run(c, shell=True, cwd=L.ROOT, capture_output=True, text=True)
            if r.returncode:
                raise RuntimeError(r.stderr[-2000:])
            s = Path(td, "o.s").read_text()
        finally:
            if tmp:
                tmp.unlink()
    return re.findall(r'\.stabs\s+"((?:[^"\\]|\\.)*)"', s)


class T:
    """a stabs type: kind in base/struct/union/array/ptr/func/enum/alias"""

    def __init__(self, kind, **kw):
        self.kind = kind
        self.name = None
        self.__dict__.update(kw)


class Parser:
    def __init__(self, entries):
        self.types = {}  # number -> T
        self.named = {}  # typedef name -> number
        self.tags = {}
        for e in entries:
            m = re.match(r"^([^:]*):([a-zA-Z]{0,2})(\d.*)$", e)
            if not m:
                continue
            nm, k, rest = m.groups()
            self.s, self.i = rest, 0
            try:
                num = self.typeref()
            except Exception:
                continue
            if "t" not in k and "T" not in k:
                continue
            if "t" in k:
                self.named.setdefault(nm, num)
                t = self.types.get(num)
                if t is not None and t.name is None:
                    t.name = nm
            if "T" in k:
                self.tags.setdefault(nm, num)

    def num(self):
        m = re.match(r"-?\d+", self.s[self.i:])
        self.i += len(m.group(0))
        return int(m.group(0))

    def typeref(self):
        """N or N=def; returns N"""
        if self.s[self.i] == "(":
            raise ValueError("pair numbers")
        n = self.num()
        if self.i < len(self.s) and self.s[self.i] == "=":
            self.i += 1
            self.types[n] = self.typedef(n)
        return n

    def typedef(self, n):
        c = self.s[self.i]
        if c == "r":  # range: base type
            self.i += 1
            self.typeref()
            self.s_skip(";")
            lo = self.until(";")
            hi = self.until(";")
            return T("base", lo=lo, hi=hi)
        if c in "su":
            self.i += 1
            size = self.num()
            fields = []
            while self.s[self.i] != ";":
                fname = self.until(":")
                ft = self.typeref()
                self.s_skip(",")
                bo = self.num()
                self.s_skip(",")
                bs = self.num()
                self.s_skip(";")
                fields.append((fname, ft, bo, bs))
            self.i += 1
            return T("struct" if c == "s" else "union", size=size, fields=fields)
        if c == "a":
            self.i += 1
            self.s_skip("r")
            self.typeref()
            self.s_skip(";")
            lo = int(self.until(";"))
            hi = int(self.until(";"))
            el = self.typeref()
            return T("array", n=hi - lo + 1, el=el)
        if c == "*":
            self.i += 1
            return T("ptr", to=self.typeref())
        if c == "f":
            self.i += 1
            return T("func", ret=self.typeref())
        if c == "e":
            self.i += 1
            self.until(";;") if False else None
            while self.s[self.i] != ";":
                self.until(",")
            self.i += 1
            return T("enum")
        if c == "x":  # cross reference to an incomplete tag
            self.i += 1
            kind = self.s[self.i]
            self.i += 1
            tag = self.until(":")
            return T("xref", tag=tag, tkind=kind)
        if c == "k" or c == "B":
            self.i += 1
            return T("alias", to=self.typeref())
        # plain alias N=M
        return T("alias", to=self.typeref())

    def s_skip(self, ch):
        if self.s[self.i] != ch:
            raise ValueError(f"expected {ch} at {self.i}: {self.s[self.i:self.i + 20]}")
        self.i += 1

    def until(self, ch):
        j = self.s.index(ch, self.i)
        v = self.s[self.i:j]
        self.i = j + len(ch)
        return v

    # --- queries

    def resolve(self, n, depth=0):
        t = self.types.get(n)
        while t is not None and t.kind == "alias" and depth < 50:
            nn = t.to
            if nn == n:
                break
            n, t, depth = nn, self.types.get(nn), depth + 1
        return n, t

    def spell(self, n):
        """a C-ish spelling of type n (typedef names of base types normalised)"""
        t0 = self.types.get(n)
        name = t0.name if t0 else None
        n2, t = self.resolve(n)
        if t is None:
            return f"?{n}"
        if t.kind == "base":
            nm = t.name or name
            return BASE.get(nm, nm) if nm else self._base_guess(t)
        if t.kind == "ptr":
            return self.spell(t.to) + " *"
        if t.kind == "array":
            return f"{self.spell(t.el)} [{t.n}]"
        if t.kind in ("struct", "union"):
            return f"{t.kind}{{{self.size(n2)}}}"
        if t.kind == "func":
            return "func"
        if t.kind == "xref":
            return f"{t.tkind}tag {t.tag}"
        return t.kind

    def _base_guess(self, t):
        return f"base[{t.lo};{t.hi}]"

    def size(self, n):
        n, t = self.resolve(n)
        if t is None:
            return 0
        if t.kind in ("struct", "union"):
            return t.size
        if t.kind == "array":
            return t.n * self.size(t.el)
        if t.kind == "ptr":
            return 4
        if t.kind == "base":
            nm = t.name
            sp = BASE.get(nm, nm)
            return {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "s64": 8, "u64": 8,
                    "f32": 4, "f64": 8}.get(sp, 4)
        if t.kind == "enum":
            return 4
        return 0

    def leaves(self, n, path="", off=0):
        """[(bitoff, bitsize, spelling, path, kind)] leaves of type n"""
        n, t = self.resolve(n)
        out = []
        if t is not None and t.kind in ("struct", "union"):
            for fname, ft, bo, bs in t.fields:
                ft2, ftt = self.resolve(ft)
                p = f"{path}.{fname}" if path else fname
                if ftt is not None and ftt.kind in ("struct", "union"):
                    out.append((off + bo, bs, self.spell(ft), p, "agg:" + t.kind))
                    out += self.leaves(ft, p, off + bo)
                else:
                    isbits = ftt is not None and ftt.kind == "base" and bs != 8 * self.size(ft)
                    out.append((off + bo, bs, self.spell(ft), p, ("bits" if isbits else "leaf") + ":" + t.kind))
        return out


def parse(rel, text=None):
    return Parser(stabs_of(rel, text))


def main(argv):
    flat = "--flat" in argv
    argv = [a for a in argv if a != "--flat"]
    rel, names = argv[0], argv[1:]
    p = parse(rel)
    for nm in names:
        if nm not in p.named:
            print(f"{nm}: not found")
            continue
        n = p.named[nm]
        print(f"== {nm} size {p.size(n):#x}")
        for bo, bs, sp, path, k in p.leaves(n):
            if not flat and "." in path:
                continue
            b = f" bits@{bo % 32}:{bs}" if k.startswith("bits") else ""
            print(f"  {bo // 8:#06x} {bs // 8:#x}{b} {sp} {path} {k}")


if __name__ == "__main__":
    main(sys.argv[1:])
