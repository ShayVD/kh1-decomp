#!/usr/bin/env python3
"""Host build census (phase 5, docs/vita-port-plan.md section 5 step 1).

Compiles every game C file (src/ minus src/sdk/, which the port replaces) with
a host compiler as a 32-bit x86 object under -DKH1_HOST, the null-platform
side of include/platform/, and counts what fails by cause. Nothing here
touches the PS2 build: objects go to out/host/.

    python3 -I tools/host/census.py                 # summary by cause
    python3 -I tools/host/census.py --files CAUSE   # the files failing with CAUSE
    python3 -I tools/host/census.py --cc clang

A file is counted under the cause of its first error; --all-errors counts
every error line instead. The summary is also written to out/host/census.tsv.

--link also assembles src/data/*.s for x86 (`.word` read as `.long`; needs
the pieces a PS2 `make` cuts into out/data/pieces/), compiles the null
platform host/null/*.c and the shared port code host/port/*.c, generates
out/host/defs_host.c (the bss and data D_ names only symbols.ld knows, sized
to the next known address, with the ELF's bytes where they lie below .bss)
and counts the symbols the compiled objects still leave undefined, by kind
(out/host/undefined.txt lists them). The near-miss C drafts of the unmatched
functions (shift/drafts.tsv, the func_ rows) are compiled with the game files
for the link: the port runs them (vita-port-plan section 3).

--exe (implies --link) then links out/host/kh1-host with the host compiler
(-m32 -no-pie, the host libc and libm) and host/null/main.c's main(), which
calls the game's main; `out/host/kh1-host` runs it to the first PlatCdRead.
"""
import argparse
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "out", "host")

# -malign-double: long long / double align to 8 inside structs, as on the EE
# and the Vita's EABI (i386's default is 4, which moves fields).
# Builtins stay on as for the EE game code (implicit fabsf is the builtin).
# gnu89 + the -Wno-error list: gcc 2.96 C (implicit declarations, int <->
# pointer conversions) that gcc 14 refuses by default.
CFLAGS = [
    "-m32", "-malign-double", "-std=gnu89", "-O1", "-g", "-w",
    "-fno-strict-aliasing", "-fno-pic", "-fno-stack-protector", "-DKH1_HOST", "-Iinclude", "-Isrc",
    "-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion",
    "-Wno-error=incompatible-pointer-types", "-Wno-error=implicit-int",
]

# (cause, regex on the error text). First match wins.
CAUSES = [
    ("asm: MIPS instruction", r"Error: (no such instruction|invalid instruction suffix|bad register name|unknown pseudo-op|invalid char)"),
    ("asm: register variable", r"invalid register name for"),
    ("asm: constraint", r"impossible constraint|must specify a single register|invalid 'asm'|unknown register name|matching constraint|asm operand"),
    ("asm: other", r"\bError: "),
    ("u128 arithmetic", r"(incompatible types when assigning to type '\w+' \{aka '(kh1_[su]128|struct <anonymous>)'\}|invalid operands to binary .*kh1_[su]128|kh1_[su]128.*(used struct type value where scalar|incompatible type)|aggregate value used where an integer|used struct type value where scalar is required|conversion to non-scalar type|wrong type argument to (unary|increment|decrement))"),
    ("bitfield wider than type", r"width of '.*' exceeds its type"),
    ("struct size check", r"size of array '.*_check_.*' is negative|size of array '.*' is negative"),
    ("cast as lvalue", r"lvalue required as"),
    ("builtin / libc clash", r"conflicting types for '(fabsf|sqrtf|memcpy|memset|strlen|strcpy|abs|sinf|cosf|atan2f|printf|sprintf|memcmp|strcmp)'"),
    ("conflicting types", r"conflicting types for"),
    ("unknown type", r"unknown type name|storage size of .* isn't known|has incomplete type|invalid use of undefined type"),
    ("undeclared", r"undeclared"),
]


def game_files():
    out = []
    for d, dirs, files in os.walk(os.path.join(ROOT, "src")):
        rel = os.path.relpath(d, ROOT)
        if rel == "src/sdk" or rel.startswith("src/sdk/"):
            continue
        for f in files:
            if f.endswith(".c") and not f.startswith("."):
                out.append(os.path.join(rel, f))
    return sorted(out)


def draft_files():
    """The C drafts of shift/drafts.tsv's game functions (not the SDK's)."""
    out = []
    for l in open(os.path.join(ROOT, "shift", "drafts.tsv")):
        f = l.rstrip("\n").split("\t")
        if len(f) >= 2 and f[0].startswith("func_"):
            out.append(f[1])
    return out


def classify(text):
    for name, rx in CAUSES:
        if re.search(rx, text):
            return name
    return "other"


def first_error(stderr):
    lines = [l for l in stderr.splitlines() if re.search(r"\berror: |\bError: ", l)]
    return lines


def compile_one(cc, path):
    obj = os.path.join(OUT, path + ".o")
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    p = subprocess.run([cc] + CFLAGS + ["-c", "-o", obj, path], cwd=ROOT,
                       capture_output=True, text=True, env=dict(os.environ, LC_ALL="C"))
    errs = first_error(p.stderr)
    if p.returncode == 0:
        return path, True, []
    if not errs:
        errs = [p.stderr.strip().splitlines()[-1] if p.stderr.strip() else "unknown failure"]
    return path, False, errs


def assemble_data():
    objs = []
    d = os.path.join(OUT, "data")
    os.makedirs(d, exist_ok=True)
    for f in sorted(os.listdir(os.path.join(ROOT, "src", "data"))):
        if not f.endswith(".s"):
            continue
        src = open(os.path.join(ROOT, "src", "data", f)).read()
        src = re.sub(r"^(\s*)\.word\b", r"\1.long", src, flags=re.M)
        tmp = os.path.join(d, f)
        open(tmp, "w").write(src)
        obj = tmp[:-2] + ".o"
        p = subprocess.run(["as", "--32", "-o", obj, tmp], cwd=ROOT, capture_output=True, text=True)
        if p.returncode:
            print("data: %s does not assemble: %s" % (f, p.stderr.strip().splitlines()[0]))
        else:
            objs.append(obj)
    return objs


def nm(objs, defined):
    args = ["nm", "--defined-only" if defined else "--undefined-only"] + objs
    out = subprocess.run(args, capture_output=True, text=True).stdout
    syms = set()
    for l in out.splitlines():
        parts = l.split()
        if defined and len(parts) == 3 and parts[1] not in "Nn":
            syms.add(parts[2])
        elif not defined and len(parts) == 2 and parts[0] == "U":
            syms.add(parts[1])
    return syms


def sym_kind(s, failing_defs, asm_defs):
    if s in failing_defs:
        return "defined in a game file that does not compile yet"
    if s in asm_defs:
        return "defined in src/asm/ (hand asm: needs C)"
    if s.startswith("sce"):
        return "SDK call outside include/platform/ (" + s[:6] + "*)"
    if s.startswith("D_"):
        a = int(s[2:10], 16)
        if a < 0x100000:
            return "D_ below 0x100000 (kernel / scratchpad offsets)"
        if a >= 0x6A0000:
            return "D_ in the fixed memory map (vita-port-plan section 4)"
        return "D_ data / bss only the PS2 linker script defines"
    if s.startswith("func_"):
        a = int(s[5:13], 16)
        if a >= 0x0024F2E0:
            return "func_ in the SDK segment (libc / libgraph ...: the port's own)"
        return "func_ game code in no host object (the 9 unmatched; ppp functions a macro defines in a failing file)"
    return "libc / libm / compiler (" + s + ")" if len(s) < 24 else "other"


def host_defs(undefined, cc):
    """Define the D_ variables only the PS2 linker script places (bss with no
    C definition, and data the data pieces do not cover) in
    out/host/defs_host.c: each a byte array up to the next known address
    (out/gen/symbols.ld, out/gen/data.tsv), aligned as its address is; inside
    the ELF's loaded section it takes the user's ELF bytes (build output only,
    never committed), in .bss zeros."""
    import bisect
    import tomllib
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    from elf32 import Elf
    from pathlib import Path
    want = sorted(s for s in undefined if re.fullmatch(r"D_[0-9A-F]{8}", s)
                  and 0x100000 <= int(s[2:], 16) < 0x6A0000)
    if not want:
        return None
    known = set()
    for l in open(os.path.join(ROOT, "out", "gen", "symbols.ld")):
        m = re.search(r"PROVIDE\(\w+ = 0x([0-9a-f]+)\)", l)
        if m:
            known.add(int(m.group(1), 16))
    for l in open(os.path.join(ROOT, "out", "gen", "data.tsv")):
        f = l.split("\t")
        if re.fullmatch(r"[0-9a-f]{8}", f[0]):
            known.add(int(f[0], 16))
    ks = sorted(known)
    cfg = tomllib.load(open(os.path.join(ROOT, "kh1.toml"), "rb"))
    elf = Elf.load(Path(ROOT) / cfg["target"]["elf"])
    bss = elf.section(".bss")
    out = ["/* Generated by tools/host/census.py --link: the D_ variables only the PS2",
           " * linker script defines, sized to the next known address. Build output. */"]
    for s in want:
        a = int(s[2:], 16)
        j = bisect.bisect_right(ks, a)
        size = (ks[j] if j < len(ks) else 0x6A0000) - a
        al = min(16, a & -a)
        data = None
        if a < bss.addr:
            data = elf.read(a, size)
        if data:
            body = ", ".join("0x%02x" % b for b in data)
            out.append("unsigned char %s[0x%x] __attribute__((aligned(%d))) = {%s};" % (s, size, al, body))
        else:
            out.append("unsigned char %s[0x%x] __attribute__((aligned(%d)));" % (s, size, al))
    src = os.path.join(OUT, "defs_host.c")
    open(src, "w").write("\n".join(out) + "\n")
    obj = src + ".o"
    p = subprocess.run([cc] + CFLAGS + ["-c", "-o", obj, src], cwd=ROOT, capture_output=True, text=True)
    if p.returncode:
        print("host definitions: out/host/defs_host.c does not compile:\n%s" % p.stderr[:2000])
        return None
    print("host definitions: %d D_ variables in out/host/defs_host.c (%d with the ELF's bytes)"
          % (len(want), sum(1 for l in out if "= {" in l)))
    return obj


def link_census(results, cc):
    ok_objs = [os.path.join(OUT, p + ".o") for p, ok, _ in results if ok]
    data_objs = assemble_data()
    null_objs = []
    # host/null: the null platform; host/port: what every port platform shares
    for d in ("null", "port"):
        nd = os.path.join(ROOT, "host", d)
        for f in sorted(os.listdir(nd)):
            if f.endswith(".c"):
                obj = os.path.join(OUT, d, f + ".o")
                os.makedirs(os.path.dirname(obj), exist_ok=True)
                p = subprocess.run([cc] + CFLAGS + ["-c", "-o", obj, os.path.join("host", d, f)], cwd=ROOT,
                                   capture_output=True, text=True)
                if p.returncode:
                    print("null platform: host/%s/%s does not compile:\n%s" % (d, f, p.stderr))
                else:
                    null_objs.append(obj)
    objs = ok_objs + data_objs + null_objs
    defined = nm(objs, True)
    # functions.tsv names: C defines the name, the data blob's .word uses func_<addr>
    alias = {}
    for l in open(os.path.join(ROOT, "functions.tsv")):
        parts = l.split("\t")
        if len(parts) >= 2 and not l.startswith("#") and parts[1].split():
            alias[parts[0]] = "func_" + parts[1].split()[0].lower()[-8:]
    # the func_<addr> spelling the data blob and the drafts use for a functions.tsv name: an
    # alias symbol, so the real link (--exe) resolves it too
    refs = nm(objs, False)
    pairs = sorted((alias[n], n) for n in defined if n in alias
                   and alias[n] in refs and alias[n] not in defined)
    # (a linker script assignment: an assembler .set to another object's symbol stays undefined)
    link_census.script = None
    if pairs:
        src = os.path.join(OUT, "aliases.ld")
        open(src, "w").write("".join("PROVIDE(%s = %s);\n" % (f, n) for f, n in pairs))
        link_census.script = src
    defined |= set(alias[n] for n in defined if n in alias)
    undefined = refs - defined
    hobj = host_defs(undefined, cc)
    if hobj:
        objs.append(hobj)
        null_objs.append(hobj)
        undefined -= nm([hobj], True)
    # where the missing names are defined on the PS2 side
    failing_defs, asm_defs = set(), set()
    for p, ok, _ in results:
        if not ok:
            src = open(os.path.join(ROOT, p), errors="replace").read()
            # definitions: a function head (no `;` on its line) or a variable
            names = set(re.findall(r"^(?!extern|typedef)[A-Za-z_][\w \t\*]*?\b(\w+)[ \t]*\([^;\n]*$", src, re.M))
            names |= set(re.findall(r"^(?!extern|typedef)[A-Za-z_][\w \t\*]*?\b((?:D|func)_[0-9A-Fa-f]{8}\w*)[ \t]*[\[=;]", src, re.M))
            failing_defs |= names | set(alias[n] for n in names if n in alias)
    for f in os.listdir(os.path.join(ROOT, "src", "asm")):
        src = open(os.path.join(ROOT, "src", "asm", f), errors="replace").read()
        asm_defs |= set(re.findall(r"^\s*(?:glabel\s+|\.globl\s+)?(func_[0-9a-f]{8})\s*:?", src, re.M))
    kinds = {}
    for s in undefined:
        kinds.setdefault(sym_kind(s, failing_defs, asm_defs), []).append(s)
    with open(os.path.join(OUT, "undefined.txt"), "w") as f:
        for k in sorted(kinds):
            for s in sorted(kinds[k]):
                f.write("%s\t%s\n" % (k, s))
    print("link: %d objects (%d game, %d data, %d null platform / port), %d symbols undefined"
          % (len(objs), len(ok_objs), len(data_objs), len(null_objs), len(undefined)))
    link_census.objs = objs
    link_census.undefined = undefined
    small = []
    for k, v in sorted(kinds.items(), key=lambda kv: -len(kv[1])):
        if k.startswith("libc"):
            small.extend(v)
        else:
            print("  %5d  %s" % (len(v), k))
    if small:
        print("  %5d  libc / libm / compiler: %s" % (len(small), " ".join(sorted(small))))


def link_exe(objs, cc):
    """Link out/host/kh1-host from the census objects against the host libc."""
    exe = os.path.join(OUT, "kh1-host")
    extra = [link_census.script] if link_census.script else []
    p = subprocess.run([cc, "-m32", "-no-pie", "-o", exe] + objs + extra + ["-lm"], cwd=ROOT,
                       capture_output=True, text=True, env=dict(os.environ, LC_ALL="C"))
    if p.returncode:
        errs = [l for l in p.stderr.splitlines() if "undefined reference" in l or "multiple definition" in l]
        print("exe: the link fails (%d lines; first: %s)" % (len(p.stderr.splitlines()),
              (errs or p.stderr.strip().splitlines() or ["?"])[0]))
        open(os.path.join(OUT, "link.log"), "w").write(p.stderr)
        return 1
    if os.path.exists(os.path.join(OUT, "link.log")):
        os.remove(os.path.join(OUT, "link.log"))
    print("exe: out/host/kh1-host linked (%d objects)" % len(objs))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cc", default=os.environ.get("HOST_CC", "gcc"))
    ap.add_argument("--files", metavar="CAUSE", help="list the files whose first error is CAUSE (a prefix)")
    ap.add_argument("--all-errors", action="store_true", help="count every error line, not one per file")
    ap.add_argument("--show", metavar="FILE", help="print one file's errors")
    ap.add_argument("--link", action="store_true", help="also count the symbols left undefined (see above)")
    ap.add_argument("--exe", action="store_true", help="also link out/host/kh1-host (see above)")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()

    files = [a.show] if a.show else game_files() + draft_files()
    with ThreadPoolExecutor(a.j) as ex:
        results = list(ex.map(lambda f: compile_one(a.cc, f), files))

    if a.show:
        print("\n".join(results[0][2]) or "compiles")
        return 0

    by_cause = {}
    for path, ok, errs in results:
        if ok:
            continue
        if a.all_errors:
            for e in errs:
                by_cause.setdefault(classify(e), []).append(path)
        else:
            by_cause.setdefault(classify(errs[0]), []).append(path)

    if a.files:
        for cause, paths in sorted(by_cause.items()):
            if cause.startswith(a.files):
                print("\n".join(sorted(set(paths))))
        return 0

    nok = sum(1 for r in results if r[1])
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, "census.tsv"), "w") as f:
        f.write("path\tok\tcause\tfirst_error\n")
        for path, ok, errs in results:
            f.write("%s\t%d\t%s\t%s\n" % (path, ok, "" if ok else classify(errs[0]),
                                          "" if ok else errs[0].replace("\t", " ")))
    nd = sum(1 for r in results if r[0].startswith("nonmatchings/"))
    print("%s: %d / %d game files compile (%d fail; %d of them drafts of unmatched functions)"
          % (a.cc, nok, len(results), len(results) - nok, nd))
    for cause, paths in sorted(by_cause.items(), key=lambda kv: -len(kv[1])):
        print("  %5d  %s" % (len(paths), cause))
    if a.link or a.exe:
        link_census(results, a.cc)
    if a.exe:
        return link_exe(link_census.objs, a.cc)
    return 0


if __name__ == "__main__":
    sys.exit(main())
