#!/usr/bin/env python3
"""Layouts of a file's local struct types, measured by a probe compile (session 27).

  python3 -I tools/shift/s27types/s27_layout.py FILE.c TYPE [TYPE ...]

Prints each node (named local struct typedef, or anonymous member struct) with its
fields: offset, size, element count, kind (leaf / struct / bits) and type.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402

BSIZE = {"s8": 1, "u8": 1, "char": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "s64": 8, "u64": 8}

_hdr_index = None


def header_types():
    """typedef name -> header (path relative to include/) for every include/ header"""
    global _hdr_index
    if _hdr_index is None:
        _hdr_index = {}
        for p in sorted((L.ROOT / "include").rglob("*.h")):
            t = C.strip_comments(p.read_text(errors="replace"))
            rel = str(p.relative_to(L.ROOT / "include"))
            for m in re.finditer(r"\}\s*([\w\s,*]+);", t):
                for n in m.group(1).split(","):
                    n = n.strip()
                    if re.fullmatch(r"\w+", n):
                        _hdr_index.setdefault(n, rel)
            for m in re.finditer(r"\btypedef\b[^;{}]*?\b(\w+)\s*(?:\[[^\]]*\]\s*)*;", t):
                _hdr_index.setdefault(m.group(1), rel)
    return _hdr_index


class Field:
    def __init__(self, **kw):
        self.name = None; self.off = 0; self.size = 0; self.n = 1; self.kind = "leaf"
        self.sub = None; self.tkey = None; self.tmpl = None; self.bitoff = None; self.width = None
        self.deps = set(); self.localref = None; self.elem = 0; self.ptrnode = None; self.tdef = None
        self.__dict__.update(kw)

    def __repr__(self):
        k = self.tkey if self.kind != "struct" else f"struct<{self.sub}>"
        b = f" bits@{self.bitoff}:{self.width}" if self.kind == "bits" else ""
        return f"{self.off:#06x} {self.size:#x} n={self.n} {self.kind} {k} {self.name}{b}"


class Node:
    def __init__(self, nid, name, kind, parent=None):
        self.nid, self.name, self.kind, self.parent = nid, name, kind, parent
        self.size = 0; self.fields = []; self.members = []; self.path = None
        self.defn = None  # Def for named nodes
        self.inline_children = []  # anonymous nodes, in member order


class FileTypes:
    """the local struct nodes reachable from `roots` in one file text"""

    def __init__(self, rel, text, roots):
        self.rel, self.text = rel, text
        self.ct = C.strip_comments(text)
        self.nodes = {}  # nid -> Node
        self.byname = {}
        self.err = None
        for r in roots:
            self.named(r)

    def local_struct(self, name):
        return C.find_def(self.text, name, self.ct)

    def local_typedef(self, name):
        """the whole `typedef ... name ...;` statement of a non-struct local typedef, or None"""
        for m in re.finditer(r"\btypedef\b[^;{}]*;", self.ct):
            st = m.group(0)
            if re.search(r"\b" + name + r"\b", st) and not re.match(r"typedef\s+(struct|union)\s+\w+\s+" + name + r"\s*;", st):
                # the name must be the declared one, not the base type
                body = re.sub(r"__attribute__\s*\(\(.*?\)\)", "", st)
                if re.search(r"\b" + name + r"\b\s*(\[|;|\))", body):
                    return re.sub(r"\s+", " ", st)
        return None

    def resolve(self, ts):
        """normalized base type, following the file's simple typedefs"""
        b = C.norm_base(ts)
        seen = 0
        while seen < 8:
            p = C.plain(b)
            if p in C.BASIC or self.local_struct(p):
                break
            st = C.simple_typedef(self.ct, p)
            if not st:
                break
            b = (b.replace(p, C.norm_base(st)) if p in b else C.norm_base(st))
            seen += 1
        return b

    def named(self, name):
        if name in self.byname:
            return self.byname[name]
        d = self.local_struct(name)
        if d is None:
            raise ValueError(f"{name}: not a local struct typedef")
        n = Node(f"{len(self.nodes)}", name, d.kind)
        n.defn = d
        self.nodes[n.nid] = n
        self.byname[name] = n.nid
        n.path = f"(({name} *)0)->"
        self.build(n, self.ct[d.b0:d.b1])
        return n.nid

    def build(self, node, body):
        node.members = C.parse_members(body)
        for m in node.members:
            if m.name is None:
                continue
            f = Field(name=m.name)
            idx = "".join("[0]" for _ in m.dims)
            f.probe = node.path + m.name
            f.probe0 = f.probe + idx
            if m.inline:
                ch = Node(f"{len(self.nodes)}", None, m.inline[0], parent=node.nid)
                self.nodes[ch.nid] = ch
                ch.path = f.probe0 + "."
                node.inline_children.append(ch.nid)
                self.build(ch, m.inline[1])
                f.kind, f.sub = "struct", ch.nid
            elif m.bits is not None:
                f.kind, f.width = "bits", m.bits
                f.tkey = self.resolve(m.base)
            elif m.fnptr:
                f.tkey = re.sub(r"\s+", " ", m.tmpl.replace("{}", ""))
                f.tmpl = m.tmpl
            else:
                b = self.resolve(m.base)
                p = C.plain(b)
                if m.stars == 0 and self.local_struct(p):
                    f.kind, f.sub = "struct", self.named(p)
                    f.tkey = None
                else:
                    lt = None if self.local_struct(p) or p in C.BASIC else self.local_typedef(p)
                    if self.local_struct(p) and m.stars > 0:
                        f.ptrnode = self.named(p)  # a pointer to a local struct: its class decides
                    elif self.local_struct(p):
                        f.localref = p
                    elif lt:
                        # a local typedef of another kind (array, attribute, function): copied
                        f.tdef = (p, lt)
                    elif p not in C.BASIC:
                        h = header_types().get(p)
                        if h and not h.startswith("data/"):
                            f.deps.add(h)
                        else:
                            f.localref = p
                    dims = "".join(f"[{d}]" for d in m.dims)
                    f.tkey = b + " " + "*" * m.stars + dims
                    f.tmpl = b + " " + "*" * m.stars + "{}" + dims
                    if f.ptrnode is not None:
                        vol = "volatile " if "volatile" in b.split() else ""
                        f.tkey = f"{vol}@ptr " + "*" * m.stars + dims
                        f.tmpl = f"{vol}@P " + "*" * m.stars + "{}" + dims
                    elif f.tdef:
                        stmt = re.sub(r"\b" + p + r"\b", "@", f.tdef[1])
                        f.tkey = f"tdef<{stmt}> " + b.replace(p, "@") + " " + "*" * m.stars + dims
                        f.tmpl = b.replace(p, "@T") + " " + "*" * m.stars + "{}" + dims
            f.mem = m
            node.fields.append(f)

    def probe(self):
        exprs = []
        for n in self.nodes.values():
            if n.name:
                exprs.append(("size", n.nid, None, f"sizeof({n.name})"))
            for f in n.fields:
                if f.kind == "bits":
                    continue
                exprs.append(("off", n.nid, f, f"(unsigned int)&({f.probe})"))
                exprs.append(("size", n.nid, f, f"sizeof({f.probe})"))
                exprs.append(("esize", n.nid, f, f"sizeof({f.probe0})"))
        body = ",\n".join(f"  1 + ({e})" for *_, e in exprs)
        text = self.text + "\nunsigned int __s27_probe[] = {\n" + body + "\n};\n"
        asm, diags = L.compile_s(self.rel, text)
        if asm is None:
            raise ValueError("probe does not compile: " + "; ".join(m for _, m in diags)[:500])
        m = re.search(r"^__s27_probe:\n((?:\s*\.word\s+\S+\n)+)", asm, re.M)
        vals = [int(x, 0) - 1 for x in re.findall(r"\.word\s+(\S+)", m.group(1))]
        if len(vals) != len(exprs):
            raise ValueError("probe: word count")
        for (what, nid, f, _), v in zip(exprs, vals):
            node = self.nodes[nid]
            if f is None:
                node.size = v
            elif what == "off":
                f.off = v
            elif what == "size":
                f.size = v
            else:
                f.elem = v
        # anonymous nodes: offsets relative to their own start, size from the parent field
        for n in self.nodes.values():
            for f in n.fields:
                if f.kind != "bits":
                    f.n = f.size // f.elem if f.elem else 1
        for n in self.nodes.values():
            if n.parent is not None:
                base = next(f for f in self.nodes[n.parent].fields if f.sub == n.nid)
                n.size = base.elem
                n.absbase = base
        for n in self.nodes.values():
            if n.parent is None:
                continue
        # relative offsets: the probe gave offsets from the named root of each path
        for n in self.nodes.values():
            if n.parent is not None:
                start = self.abs_off(n)
                for f in n.fields:
                    if f.kind != "bits":
                        f.off -= start
        for n in self.nodes.values():
            self.bits(n)

    def abs_off(self, n):
        if n.parent is None:
            return 0
        return n.absbase.off

    def bits(self, n):
        cur = 0
        for m, f in self.member_fields(n):
            if m.bits is None:
                if f is not None:
                    cur = (f.off + f.size) * 8
                continue
            t = self.resolve(m.base)
            st = BSIZE.get(C.plain(t), 4) * 8
            w = m.bits
            if w == 0:
                cur = -(-cur // st) * st
                continue
            if cur // st != (cur + w - 1) // st:
                cur = -(-cur // st) * st
            if f is not None:
                f.bitoff, f.off, f.size = cur, (cur // st) * (st // 8), st // 8
                f.tkey = t
            cur += w

    def member_fields(self, n):
        it = iter(n.fields)
        out = []
        for m in n.members:
            out.append((m, next(it) if m.name is not None else None))
        return out


def main(argv):
    rel, types = argv[0], argv[1:]
    ft = FileTypes(rel, (L.ROOT / rel).read_text(), types)
    ft.probe()
    for n in ft.nodes.values():
        print(f"node {n.nid} {n.name or '(anon in ' + str(n.parent) + ')'} {n.kind} size {n.size:#x}")
        for f in n.fields:
            print("   ", f, f"-> node {f.sub}" if f.sub else "", f"localref={f.localref}" if f.localref else "",
                  " ".join(sorted(f.deps)))


if __name__ == "__main__":
    main(sys.argv[1:])
