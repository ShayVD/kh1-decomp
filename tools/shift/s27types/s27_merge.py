"""Merge the used fields of several files' struct views into one set of types (session 27).

Every view node (a local struct type of one file) is attached to a class; a class becomes
one struct type.  The used fields of the attached nodes are placed into slots by offset:
struct members first (largest first), then leaf arrays, scalars, bit-fields, and byte
blobs last.  A field that matches a slot exactly maps to it; a field inside one element
of a struct-array slot is placed in that slot's class (path `m[i].x`); a scalar inside a
leaf array of its element type maps to the element (`a[i]`).  Anything else that
overlaps is a conflict, and the file whose field it is stays unfolded.
"""
import re
from collections import Counter, defaultdict

KORDER = {"struct": 0, "array": 1, "leaf": 2, "bits": 3, "blob": 4}
PADNAME = re.compile(r"^(pad|_pad|unk|_|x?pad|padding|rsv|reserved|dummy)", re.I)


def tmpname(x, nid):
    return f"{x}__q{nid}"


def compatible(a, b):
    if a == b:
        return True
    ints = r"\b(s8|u8|char|s16|u16|s32|u32|s64|u64)\b"
    w = {"s8": 8, "u8": 8, "char": 8, "s16": 16, "u16": 16, "s32": 32, "u32": 32, "s64": 64, "u64": 64}
    ra = re.sub(ints, lambda m: f"I{w[m.group(1)]}", a)
    rb = re.sub(ints, lambda m: f"I{w[m.group(1)]}", b)
    return ra == rb and "*" not in a and "*" not in b


def elem_key(tkey):
    """the element type key of a leaf array key `T [n]...` (first dimension dropped)"""
    m = re.match(r"^(.*?)\s*\[[^\]]*\](.*)$", tkey)
    return (m.group(1) + " " + m.group(2)).strip() if m else None


def needed(ft, used, nid, memo):
    if nid in memo:
        return memo[nid]
    memo[nid] = []
    out = []
    for f in ft.nodes[nid].fields:
        u = tmpname(f.name, nid) in used
        if f.kind == "struct":
            sub = needed(ft, used, f.sub, memo)
            if u or sub:
                out.append(f)
        elif u:
            out.append(f)
    memo[nid] = out
    return out


class Cand:
    def __init__(self, f, rel, nid, off, bitoff, prefix):
        self.f, self.rel, self.nid, self.off, self.bitoff, self.prefix = f, rel, nid, off, bitoff, prefix

    @property
    def kind(self):
        f = self.f
        if f.kind == "leaf" and f.n > 1:
            base = f.tkey.split("[")[0].strip()
            return "blob" if base in ("u8", "s8", "char") and f.size > 16 else "array"
        return f.kind

    def rng(self):
        if self.f.kind == "bits":
            return (self.bitoff, self.bitoff + self.f.width)
        return (self.off * 8, (self.off + self.f.size) * 8)


class Slot:
    def __init__(self, c, sid):
        self.sid, self.kind, self.f = sid, c.f.kind, c.f
        self.lo, self.hi = c.rng()
        self.off, self.size, self.n, self.elem = c.off, c.f.size, c.f.n, c.f.elem
        self.bitoff, self.width = c.bitoff, c.f.width
        self.cands = [c]
        self.sub = None


class Cls:
    def __init__(self, cid, parent=None):
        self.cid, self.parent = cid, parent
        self.slots, self.cands, self.nodes = [], [], []
        self.size = 0


class Merge:
    def __init__(self, files, prio):
        self.files, self.prio = files, prio
        self.fail = {}

    def run(self):
        self.classes = [Cls(0)]
        self.attached = {}  # (rel, nid) -> cid
        self.fmap = {}  # (rel, tmpname) -> [(slot, idx)]
        self.need = {}
        self.slots = []
        for rel, (ft, used, roots) in self.files.items():
            memo = {}
            for r in roots:
                needed(ft, used, ft.byname[r], memo)
            self.need[rel] = memo
            for r in roots:
                self.attach(0, rel, ft.byname[r])
        i = 0
        while i < len(self.classes):
            self.process(self.classes[i])
            i += 1
        return not self.fail

    def attach(self, cid, rel, nid):
        k = (rel, nid)
        if k in self.attached:
            if self.attached[k] != cid:
                self.fail.setdefault(rel, f"type {self.files[rel][0].nodes[nid].name or 'anon'} "
                                          "sits in two different places")
            return
        self.attached[k] = cid
        cl = self.classes[cid]
        cl.nodes.append(k)
        node = self.files[rel][0].nodes[nid]
        cl.size = max(cl.size, node.size)
        for f in self.need[rel].get(nid, []):
            cl.cands.append(Cand(f, rel, nid, f.off, f.bitoff, []))

    def newslot(self, cl, c):
        s = Slot(c, len(self.slots))
        self.slots.append(s)
        cl.slots.append(s)
        if c.f.kind == "struct":
            sub = Cls(len(self.classes), cl.cid)
            sub.size = c.f.elem
            self.classes.append(sub)
            s.sub = sub.cid
            self.attach(sub.cid, c.rel, c.f.sub)
        return s

    def same(self, s, c):
        f = c.f
        if s.kind != f.kind or (s.lo, s.hi) != c.rng():
            return False
        if f.kind == "struct":
            return (s.n, s.elem) == (f.n, f.elem)
        if f.kind == "bits":
            return compatible(s.f.tkey, f.tkey)
        if f.localref or s.f.localref:
            return False
        return (s.n, s.elem) == (f.n, f.elem) and compatible(s.f.tkey, f.tkey)

    def process(self, cl):
        cands = sorted(cl.cands, key=lambda c: (0 if c.rel.startswith("include/") else 1, KORDER[c.kind], -(c.f.size if c.f.kind != "bits" else 0),
                                               self.prio[c.rel], c.off))
        for c in cands:
            if c.rel in self.fail:
                continue
            lo, hi = c.rng()
            hits = [s for s in cl.slots if s.lo < hi and lo < s.hi]
            key = (c.rel, tmpname(c.f.name, c.nid))
            if c.f.localref:
                self.fail.setdefault(c.rel, f"field {c.f.name} has the file's own type {c.f.localref}")
                continue
            if not hits:
                s = self.newslot(cl, c)
                self.fmap[key] = c.prefix + [(s, None)]
                continue
            if len(hits) == 1:
                s = hits[0]
                if self.same(s, c):
                    s.cands.append(c)
                    self.fmap[key] = c.prefix + [(s, None)]
                    if c.f.kind == "struct":
                        self.attach(s.sub, c.rel, c.f.sub)
                    continue
                if s.kind == "struct" and s.elem:
                    rel0 = s.off * 8
                    i = (lo - rel0) // (s.elem * 8)
                    e0, e1 = rel0 + i * s.elem * 8, rel0 + (i + 1) * s.elem * 8
                    if e0 <= lo and hi <= e1:
                        idx = i if s.n > 1 or s.f.mem.dims else None
                        if c.f.kind == "struct" and lo == e0 and hi == e1 and c.f.n == 1:
                            # one whole element: the view's type is the element type
                            self.fmap[key] = c.prefix + [(s, idx)]
                            self.attach(s.sub, c.rel, c.f.sub)
                            continue
                        sub = self.classes[s.sub]
                        d = s.off + i * s.elem
                        sub.cands.append(Cand(c.f, c.rel, c.nid, c.off - d,
                                              None if c.bitoff is None else c.bitoff - d * 8,
                                              c.prefix + [(s, idx)]))
                        continue
                if (s.kind == "leaf" and s.n > 1 and c.f.kind == "leaf" and c.f.n == 1 and not c.f.mem.dims
                        and c.f.size == s.elem and (c.off - s.off) % s.elem == 0
                        and elem_key(s.f.tkey) and compatible(elem_key(s.f.tkey), c.f.tkey.strip())
                        and len(s.f.mem.dims) == 1):
                    self.fmap[key] = c.prefix + [(s, (c.off - s.off) // s.elem)]
                    continue
            h = hits[0]
            self.fail.setdefault(c.rel, f"field {c.f.name} at {c.off:#x} overlaps {h.f.name} "
                                        f"({h.cands[0].rel})")


def is_hand(rel):
    return rel.startswith("src/hand/")


def weight(rel):
    """naming weight: an earlier fold's header first, then hand files"""
    return 100 if rel.startswith("include/") else 3 if is_hand(rel) else 1


def emit(N, mg, sname):
    """(type definitions in dependency order, header deps, aliases {(rel, nid): type},
    fmap {(rel, tmpname): path})"""
    addr = N[2:].lstrip("0").lower() or "0"
    cname = {0: sname}
    taken_t = {sname}
    snames = {}
    # slot names, class by class
    for cl in mg.classes:
        taken = set()
        for s in sorted(cl.slots, key=lambda s: (s.lo, s.hi)):
            cn = Counter()
            for c in s.cands:
                w = weight(c.rel) * (0.1 if PADNAME.match(c.f.name) else 1)
                cn[c.f.name] += w
            nm = cn.most_common(1)[0][0] if cn else s.f.name
            if nm in taken:
                nm = f"{nm}_{s.off:x}"
            taken.add(nm)
            snames[s.sid] = nm
    for cl in mg.classes[1:]:
        names = Counter()
        for rel, nid in cl.nodes:
            nm = mg.files[rel][0].nodes[nid].name
            if nm:
                names[nm] += weight(rel)
        parent_slot = next(s for s in mg.slots if s.sub == cl.cid)
        base = names.most_common(1)[0][0] if names else f"{cname.get(cl.parent, sname)}_{snames[parent_slot.sid]}"
        nm = base if base.endswith("_" + addr) else f"{base}_{addr}"
        k = 2
        while nm in taken_t:
            nm = f"{base}{k}_{addr}"; k += 1
        taken_t.add(nm)
        cname[cl.cid] = nm
    deps = set()
    defs = {}
    order = []

    def visit(cid):
        if cid in order:
            return
        for s in mg.classes[cid].slots:
            if s.sub is not None:
                visit(s.sub)
        order.append(cid)
    visit(0)
    for cl in mg.classes:
        visit(cl.cid)
    for cid in order:
        cl = mg.classes[cid]
        lines, cur, unit = [], 0, None
        for s in sorted(cl.slots, key=lambda s: (s.lo, s.hi)):
            nm = snames[s.sid]
            if s.kind == "bits":
                ub, ue = s.off * 8, (s.off + s.size) * 8
                if unit and ub >= unit[1]:
                    if cur < unit[1]:
                        lines.append(f"    {unit[2]} :{unit[1] - cur};")
                    cur, unit = unit[1], None
                if unit is None:
                    if cur < ub:
                        lines.append(f"    u8 pad_{cur // 8:x}[{(ub - cur) // 8:#x}];")
                        cur = ub
                    unit = (ub, ue, s.f.tkey)
                if s.bitoff > cur:
                    lines.append(f"    {s.f.tkey} :{s.bitoff - cur};")
                lines.append(f"    {s.f.tkey} {nm}:{s.width};")
                cur = s.bitoff + s.width
                continue
            if unit:
                if cur < unit[1]:
                    lines.append(f"    {unit[2]} :{unit[1] - cur};")
                cur, unit = unit[1], None
            if cur < s.off * 8:
                lines.append(f"    u8 pad_{cur // 8:x}[{(s.off * 8 - cur) // 8:#x}];")
            cur = (s.off + s.size) * 8
            if s.kind == "struct":
                dims = "".join(f"[{d}]" for d in s.f.mem.dims)
                lines.append(f"    {cname[s.sub]} {nm}{dims};")
            else:
                deps |= s.f.deps
                lines.append("    " + s.f.tmpl.replace("{}", nm) + ";")
        if unit and cur < unit[1]:
            lines.append(f"    {unit[2]} :{unit[1] - cur};")
            cur = unit[1]
        if cur < cl.size * 8:
            lines.append(f"    u8 pad_{cur // 8:x}[{(cl.size * 8 - cur) // 8:#x}];")
        defs[cid] = "typedef struct {\n" + "\n".join(lines) + f"\n}} {cname[cid]};"
    aliases = {}
    for cl in mg.classes:
        for rel, nid in cl.nodes:
            if mg.files[rel][0].nodes[nid].name:
                aliases[(rel, nid)] = cname[cl.cid]
    fmap = {}
    for k, path in mg.fmap.items():
        fmap[k] = ".".join(snames[s.sid] + (f"[{i}]" if i is not None else "") for s, i in path)
    return [defs[c] for c in order], deps, aliases, fmap
