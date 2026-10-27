#!/usr/bin/env python3
"""Find locals handed to a callee that reads past them (phase 5, portability.md rule 15).

On the EE a frame's locals sit at fixed offsets, so matched C can pass a callee
one 16-byte local while the callee reads the 48 bytes after it (the next
locals), or an `s32 [2]` it fills with four words: the original frame happens
to have the room. On the host and the Vita the compiler places locals as it
likes, and the callee writes over other locals or saved registers (session 136:
the camera's ray casts, func_0024ac08's four-word position).

    python3 -I tools/host/localcheck.py [--tsv out/host/localcheck.tsv] [-v]

reads both sides:
- the EE side: for each function of the original ELF and each argument
  register a0-a7, how far the callee reads or writes through that pointer
  (the largest `offset + width` of a load or store based on it, following
  copies, `addiu` offsets and calls that pass it on, linearly, without the
  control flow);
- the C side: each call in src/ (the host's view, `gcc -E -DKH1_HOST`) that
  passes a local's address (`&x`, `&x[k]`, an array `x`, through casts) and
  that local's size on the host (`sizeof` compiled with the file's own
  text, gcc -m32).
A call is listed when the callee reaches past the local. Float parameters (by
the callee's prototype) do not take an integer register, as on the EE.
A heuristic: check each hit by hand (a callee may read past the local only on
a path the caller never takes).
"""
import argparse
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import argcheck  # noqa: E402

ROOT = argcheck.ROOT
BINUTILS = os.environ.get("KH1_BINUTILS_PREFIX", "mips-linux-gnu-")
ELF = os.path.join(ROOT, "SLPS_251.98")
TMP = os.path.join(ROOT, "out", "host", "localcheck")

WIDTH = {"lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2, "sh": 2,
         "lw": 4, "lwu": 4, "sw": 4, "lwc1": 4, "swc1": 4, "lwl": 4, "lwr": 4, "swl": 4, "swr": 4,
         "ld": 8, "sd": 8, "ldc1": 8, "sdc1": 8, "ldl": 8, "ldr": 8, "sdl": 8, "sdr": 8,
         "lq": 16, "sq": 16, "lqc2": 16, "sqc2": 16}
STORES = {m for m in WIDTH if m.startswith("s")}
EABI = {"t0": "a4", "t1": "a5", "t2": "a6", "t3": "a7"}
ARGREGS = ["a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"]
CALLEE_SAVED = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "fp", "sp", "gp"}
LINE = re.compile(r"^\s*([0-9a-f]+):\s+[0-9a-f]{8}\s+(\S+)\s*(.*)$")
MEM = re.compile(r"^(-?(?:0x)?[0-9a-f]+)\((\w+)\)$")


def ee_functions():
    """layout.tsv's functions: address -> end; and every name (functions.tsv too) -> address."""
    ends, names = {}, {}
    for l in open(os.path.join(ROOT, "layout.tsv")):
        f = l.rstrip("\n").split("\t")
        if len(f) >= 4 and re.fullmatch(r"[0-9a-f]{8}", f[0]):
            a = int(f[0], 16)
            ends[a] = int(f[1], 16)
            names["func_%08x" % a] = a
    for l in open(os.path.join(ROOT, "functions.tsv")):
        f = l.rstrip("\n").split("\t")
        if len(f) >= 2 and not l.startswith("#") and f[1].split():
            try:
                names[f[0]] = int(f[1].split()[0], 16)
            except ValueError:
                pass
    return ends, names


def disassemble(ends):
    lo, hi = min(ends), max(ends.values())
    out = subprocess.run([BINUTILS + "objdump", "-d", "-z", "-m", "mips:5900", "-EL",
                          "--start-address=0x%x" % lo, "--stop-address=0x%x" % hi, ELF],
                         check=True, capture_output=True, text=True).stdout
    insns = {}
    for line in out.splitlines():
        m = LINE.match(line)
        if m:
            ops = [EABI.get(o.strip(), o.strip()) for o in m.group(3).split(",")] if m.group(3) else []
            insns[int(m.group(1), 16)] = (m.group(2), ops)
    return insns


class Extents:
    """How far function F reaches through its argument register R: (reads or writes, writes),
    None where it does not."""

    def __init__(self, ends, insns, opaque=()):
        # opaque: functions whose reach depends on a length argument (memcpy ...): not followed
        self.ends, self.insns, self.memo, self.opaque = ends, insns, {}, set(opaque)

    def get(self, f, reg, depth=0):
        key = (f, reg)
        if key in self.memo:
            return self.memo[key]
        if f not in self.ends or depth > 6 or (depth and f in self.opaque):
            return (None, None)
        self.memo[key] = (None, None)  # recursion guard
        live = {reg: 0}  # register -> offset from the pointer
        best = [None, None]  # reads or writes, writes
        # session 139: a loop's index (`sll t, i, S` added to the pointer, `slti _, i, N` its bound) reaches
        # ((N - 1) << S) past it (func_00121a78 normalizes three 16-byte rows through `addu a1, s2, a0`)
        bound, shl = {}, {}
        a = f
        while a < self.ends[f]:
            mn, ops = self.insns.get(a, ("?", []))
            a += 4
            if mn in ("slti", "sltiu") and len(ops) == 3:
                try:
                    bound[ops[1]] = max(bound.get(ops[1], 0), int(ops[2], 0))
                except ValueError:
                    pass

        def reach(n, write):
            best[0] = max(best[0] or 0, n)
            if write:
                best[1] = max(best[1] or 0, n)

        def step(mn, ops):
            """One non-call instruction's effect on the live pointer copies."""
            if mn in WIDTH and len(ops) == 2:
                m = MEM.match(ops[1])
                if m and m.group(2) in live:
                    off = int(m.group(1), 0) + live[m.group(2)]
                    # the unaligned pairs: lwl / ldl name the last byte, lwr / ldr the first
                    reach(off + (1 if mn in ("lwl", "swl", "ldl", "sdl") else WIDTH[mn]), mn in STORES)
                if mn not in STORES and ops[0] in live:
                    del live[ops[0]]
                return
            if mn == "move" and len(ops) == 2:
                if ops[1] in live:
                    live[ops[0]] = live[ops[1]]
                else:
                    live.pop(ops[0], None)
                return
            if mn == "sll" and len(ops) == 3:
                shl[ops[0]] = (ops[1], int(ops[2], 0))
                live.pop(ops[0], None)
                return
            if mn in ("addu", "daddu") and len(ops) == 3 and "zero" not in ops[1:] and (ops[1] in live) != (ops[2] in live):
                p, q = (ops[1], ops[2]) if ops[1] in live else (ops[2], ops[1])
                if q in shl and shl[q][0] in bound and bound[shl[q][0]] > 0:
                    live[ops[0]] = live[p] + ((bound[shl[q][0]] - 1) << shl[q][1])
                else:
                    live.pop(ops[0], None)
                return
            if mn in ("addu", "daddu", "or") and len(ops) == 3 and "zero" in ops[1:]:
                src = ops[1] if ops[2] == "zero" else ops[2]
                if src in live:
                    live[ops[0]] = live[src]
                else:
                    live.pop(ops[0], None)
                return
            if mn in ("addiu", "daddiu") and len(ops) == 3 and ops[1] in live:
                live[ops[0]] = live[ops[1]] + int(ops[2], 0)
                return
            if mn.startswith("b") or mn.startswith("j") or mn in STORES:
                return
            if ops:
                shl.pop(ops[0], None)
            if ops and ops[0] in live:
                del live[ops[0]]

        a = f
        while a < self.ends[f]:
            mn, ops = self.insns.get(a, ("?", []))
            a += 4
            if mn in ("jal", "jalr"):
                step(*self.insns.get(a, ("?", [])))  # the delay slot runs first
                a += 4
                if mn == "jal":
                    t = int(ops[0], 16)
                    for r in ARGREGS:
                        if r in live:
                            e = self.get(t, r, depth + 1)
                            if e[0] is not None:
                                reach(live[r] + e[0], False)
                            if e[1] is not None:
                                reach(live[r] + e[1], True)
                for r in list(live):
                    if r not in CALLEE_SAVED:
                        del live[r]
                continue
            step(mn, ops)
        best = tuple(best)
        self.memo[key] = best
        return best


# ---- the C side ----

DECL = re.compile(r"^\s*(?:(?:volatile|register|const|struct|union|unsigned|signed)\s+)*([A-Za-z_]\w*)\s+(.*?);\s*$")
FUNC_HEAD = re.compile(r"(?<![\w.])([A-Za-z_]\w*)\s*\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*\{")
PROTO = re.compile(r"(?<![\w.])([A-Za-z_]\w*)\s*\(([^;{}()]*)\)\s*;")
FLOAT_T = re.compile(r"^\s*(?:const\s+)?(f32|float|f64|double)\s*\w*\s*$")
# libc: the reach of a loop over a length or a terminator is not a fixed size
LIBC = {"memset", "memcpy", "memmove", "memcmp", "strlen", "strcat", "strcpy", "strncpy", "strcmp", "strncmp",
        "sprintf", "printf", "strchr"}
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "goto"}


def preprocess(path):
    p = subprocess.run(["gcc", "-m32", "-E", "-P", "-DKH1_HOST", "-Iinclude", "-Isrc", path],
                       cwd=ROOT, capture_output=True, text=True)
    return path, p.stdout if p.returncode == 0 else ""


def split_top(s, sep=","):
    out, depth, cur = [], 0, ""
    for c in s:
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == sep and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += c
    out.append(cur)
    return out


def match_paren(s, i, o="(", c=")"):
    depth = 0
    for j in range(i, len(s)):
        if s[j] == o:
            depth += 1
        elif s[j] == c:
            depth -= 1
            if depth == 0:
                return j
    return -1


def float_params(params):
    """Per parameter: True if it is a float (no integer register on the EE)."""
    ps = [p for p in split_top(params) if p.strip() and p.strip() not in ("void", "...")]
    return [bool(FLOAT_T.match(p)) for p in ps]


def locals_of(body):
    """name -> (type name, dims list, pointer?) for the declarations in a function body."""
    out = {}
    for stmt in re.split(r"[;{}]", body):
        stmt = re.sub(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", "", stmt).strip() + ";"
        m = DECL.match(stmt)
        if not m or m.group(1) in KEYWORDS or m.group(1) == "return":
            continue
        t = m.group(1)
        for d in split_top(m.group(2)):
            d = d.split("=")[0].strip()
            dm = re.fullmatch(r"(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)", d)
            if not dm:
                continue
            dims = re.findall(r"\[([^\]]*)\]", dm.group(3))
            out[dm.group(2)] = (t, dims, bool(dm.group(1)))
    return out


def eval_int(s):
    try:
        return int(eval(s.replace("U", "").replace("u", ""), {"__builtins__": {}}))
    except Exception:
        return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    ap.add_argument("-v", action="store_true", help="also list calls whose local's size is unknown")
    a = ap.parse_args()

    ends, names = ee_functions()
    ext = Extents(ends, disassemble(ends), [names[n] for n in LIBC if n in names])

    with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        texts = list(ex.map(preprocess, argcheck.files()))

    floats = {}  # callee name -> [is float per parameter]
    for _, s in texts:
        for m in PROTO.finditer(s):
            floats.setdefault(m.group(1), float_params(m.group(2)))
    calls = []  # (file, caller, callee, arg index, reg, local, type, dims, element offset)
    for path, s in texts:
        for m in FUNC_HEAD.finditer(s):
            if m.group(1) in KEYWORDS:
                continue
            ob = m.end() - 1
            cb = match_paren(s, ob, "{", "}")
            if cb < 0:
                continue
            body = s[ob:cb]
            floats[m.group(1)] = float_params(m.group(2))
            locs = locals_of(body)
            for cm in re.finditer(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(", body):
                callee = cm.group(1)
                if callee not in names or callee in KEYWORDS or callee in LIBC:
                    continue
                cp = match_paren(body, cm.end() - 1)
                if cp < 0:
                    continue
                args = split_top(body[cm.end():cp])
                fl = floats.get(callee, [])
                ireg = 0
                for k, arg in enumerate(args):
                    isf = fl[k] if k < len(fl) else False
                    if isf:
                        continue
                    reg = ARGREGS[ireg] if ireg < 8 else None
                    ireg += 1
                    e = arg.strip()
                    while True:  # strip casts and parentheses
                        cm2 = re.match(r"^\(\s*[A-Za-z_][\w\s\*]*(?:\(\s*\*\s*\)\s*(?:\[[^\]]*\]\s*)+)?\)\s*(.*)$", e, re.S)
                        if cm2 and not re.match(r"^\(\s*[A-Za-z_]\w*\s*\)$", e):
                            e = cm2.group(1).strip()
                            continue
                        if e.startswith("(") and match_paren(e, 0) == len(e) - 1:
                            e = e[1:-1].strip()
                            continue
                        break
                    am = re.fullmatch(r"(&?)\s*([A-Za-z_]\w*)\s*(?:\[\s*([^\]]+)\s*\])?", e)
                    if not am or am.group(2) not in locs or reg is None:
                        continue
                    t, dims, ptr = locs[am.group(2)]
                    amp, idx = am.group(1), am.group(3)
                    if ptr:
                        continue
                    if not amp and not dims:
                        continue  # passed by value
                    if not amp and idx is not None:
                        continue
                    calls.append((path, m.group(1), callee, k, reg, am.group(2), t, dims, idx))

    # each local's host size, from the compiler on the file's own text (type names repeat across files)
    text_of = dict(texts)
    by_file = {}
    for c in calls:
        by_file.setdefault(c[0], set()).add((c[6], tuple(c[7])))

    def probe(path):
        keys = sorted(by_file[path])
        out = {}
        while keys:
            src = text_of[path] + "\n" + "\n".join(
                "char __lc_%d[sizeof(%s%s)];" % (i, t, "".join("[%s]" % d for d in dims))
                for i, (t, dims) in enumerate(keys)) + "\n"
            obj = os.path.join(TMP, path.replace("/", "_") + ".o")
            p = subprocess.run(["gcc", "-m32", "-malign-double", "-std=gnu89", "-w", "-fno-common", "-c", "-x", "c",
                                "-", "-o", obj], input=src, capture_output=True, text=True)
            if p.returncode == 0:
                nm = subprocess.run(["nm", "-S", obj], capture_output=True, text=True).stdout
                for l in nm.splitlines():
                    f = l.split()
                    if len(f) == 4 and f[3].startswith("__lc_"):
                        out[keys[int(f[3][5:])]] = int(f[1], 16)
                os.remove(obj)
                return path, out
            # drop the probes the compiler refused and try again
            bad = {int(m.group(1)) for m in re.finditer(r"__lc_(\d+)", p.stderr)}
            lines = {int(m.group(1)) for m in re.finditer(r"<stdin>:(\d+):", p.stderr)}
            base = text_of[path].count("\n") + 2
            bad |= {n - base for n in lines if 0 <= n - base < len(keys)}
            if not bad:
                return path, out
            keys = [k for i, k in enumerate(keys) if i not in bad]
        return path, out

    os.makedirs(TMP, exist_ok=True)
    with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        sizes = dict(ex.map(probe, by_file))

    hits, unsized = [], []
    for path, caller, callee, k, reg, var, t, dims, idx in calls:
        e, w = ext.get(names[callee], reg)
        if not e:
            continue
        total = sizes[path].get((t, tuple(dims)))
        if total is None:
            unsized.append((path, caller, callee, var, t, dims, e))
            continue
        start = 0
        if idx is not None:
            iv = eval_int(idx)
            n = 1
            for d in dims:
                n = None if n is None or eval_int(d) is None else n * eval_int(d)
            if iv is None or not n:
                continue
            start = iv * (total // n) * (n // (eval_int(dims[0]) or 1))
        room = total - start
        if e > room:
            hits.append((path, caller, callee, k, reg, var, "%s%s" % (t, "".join("[%s]" % d for d in dims)), room, e,
                         "writes %d" % w if w and w > room else "reads only"))

    hits.sort()
    for h in hits:
        print("%s\t%s -> %s arg %d (%s): %s %s, %d bytes; the callee reaches %d (%s)" % h)
    if a.v:
        for u in sorted(unsized):
            print("unsized\t%s\t%s -> %s: %s (%s%s), callee reaches %d" % (u[0], u[1], u[2], u[3], u[4], u[5], u[6]))
    print("localcheck: %d calls pass a local's address, %d reach past it%s"
          % (len(calls), len(hits), ", %d of unknown size" % len(unsized) if unsized else ""), file=sys.stderr)
    if a.tsv:
        with open(a.tsv, "w") as f:
            f.write("file\tcaller\tcallee\targ\treg\tlocal\ttype\troom\treach\twrites\n")
            for h in hits:
                f.write("\t".join(str(x) for x in h) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
