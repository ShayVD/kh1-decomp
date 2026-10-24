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
    "-m32", "-malign-double", "-std=gnu89", "-O1", "-w",
    "-fno-strict-aliasing", "-DKH1_HOST", "-Iinclude", "-Isrc",
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


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cc", default=os.environ.get("HOST_CC", "gcc"))
    ap.add_argument("--files", metavar="CAUSE", help="list the files whose first error is CAUSE (a prefix)")
    ap.add_argument("--all-errors", action="store_true", help="count every error line, not one per file")
    ap.add_argument("--show", metavar="FILE", help="print one file's errors")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()

    files = [a.show] if a.show else game_files()
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
    print("%s: %d / %d game files compile (%d fail)" % (a.cc, nok, len(results), len(results) - nok))
    for cause, paths in sorted(by_cause.items(), key=lambda kv: -len(kv[1])):
        print("  %5d  %s" % (len(paths), cause))
    return 0


if __name__ == "__main__":
    sys.exit(main())
