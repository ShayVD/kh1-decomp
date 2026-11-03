"""The native overlays for the host and Vita builds (docs/native-overlays.md,
include/platform/ovl.h, host/port/ovl.c). Imported by tools/host/census.py's link step, so
`make host-census` and tools/vita/build.py both take them.

For each overlay in ovl/overlays.tsv with sources: its C (ovl/NAME/**/*.c, as the PS2 overlay
build compiles them, plus the drafts ovl/NAME/drafts.tsv lists for the functions not matched yet)
is compiled with the target's compiler and out/.../ovl/NAME/names.h forced in front, which
renames the overlay's names (func_00f2xxxx, D_00F2xxxx: the same addresses mean other code in
each overlay) to NAME_00f2xxxx / NAME_D_00F2xxxx. Its data names are set to their place in the
memory map's overlay area, where the game's loader puts the file. The overlay is linked only when
every function of its layout is defined; otherwise it is left out (and its calls answered as
before: host/null/main.c's KH1_HOST_OVL=stub) and the missing functions are printed.

An overlay with ovl/NAME/platform.tsv (`func<TAB>replacement` rows) has parts a port replaces
with its own code (dkmovie.x's player: include/platform/movie.h): those functions' data pointers
(relocs.tsv) are pointed at the replacement, and only the functions the entry and the remaining
pointers reach through the C are compiled (the files that define them); the rest of the layout
is not needed.

out/.../ovl/modules.c holds kh1_ovl_modules: each linked overlay's file name, pin (size, SHA-256),
entry and the data pointers to fix up after a load (ovl/NAME/relocs.tsv).
"""
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BASE = 0x00F20000
MEM_BASE = 0x6A0000
# the overlay area's names: its functions, and data anywhere up to 0x00FE0000 (session 136:
# xs_dh_break.x's buffers past its file, D_00F317F0 ... D_00FA2400). Functions too: wm.x's code
# runs to 0x00F87E60 (it was func_00f2xxxx only, which covered the first 64 KiB), and its buffers
# to 0x0109xxxx (D_01067FE0 ... D_0108FAA0)
NAME_RX = re.compile(r"\b(func_00f[2-9a-d][0-9a-f]{4}|D_00F[2-9A-F][0-9A-F]{4}|D_010[0-9A-F]{5})\b")
# a function definition: the name, its parameters and `{` (a prototype has its `;` first)
HEAD_RX = re.compile(r"\b(func_00f[2-9a-d][0-9a-f]{4})\s*\([^;{]*?\)\s*\{")


def read_c(path):
    """a C file without its comments: a header comment naming another function with a `(`
    (wm.x's "the twin of gb.x func_00f26458 (tools/ovl/twins.py)") read as that one's definition
    and hid the real one"""
    text = open(os.path.join(ROOT, path), errors="replace").read()
    return re.sub(r"/\*.*?\*/|//[^\n]*", lambda m: "\n" * m.group(0).count("\n") or " ", text, flags=re.S)


def pins():
    out = {}
    for line in open(os.path.join(ROOT, "ovl", "overlays.tsv")):
        if line.strip() and not line.startswith(("#", "name")):
            name, size, sha = line.rstrip("\n").split("\t")[:3]
            out[name] = (int(size), sha)
    return out


def extra_pins(name):
    """ovl/NAME/pins.tsv (session 142): other files of the same name the native C also runs, as
    `size<TAB>sha256<TAB>what` rows: only files whose code is byte-identical to the pinned one's
    and whose data differs only in ways the C reads from the loaded file (the English patch's wm.x:
    its world names and their offset tables)"""
    path = os.path.join(ROOT, "ovl", name, "pins.tsv")
    out = []
    if os.path.exists(path):
        for line in open(path):
            if line.strip() and not line.startswith(("#", "size")):
                size, sha = line.rstrip("\n").split("\t")[:2]
                out.append((int(size), sha))
    return out


def layout(name):
    funcs = []
    for line in open(os.path.join(ROOT, "ovl", name, "layout.tsv")):
        if line.strip() and not line.startswith(("#", "addr")):
            funcs.append(line.split("\t")[3].strip())
    return funcs


def sources(name):
    d = os.path.join(ROOT, "ovl", name)
    out = []
    for dirpath, _dirs, files in os.walk(d):
        for f in files:
            if f.endswith(".c") and not f.startswith("."):
                out.append(os.path.relpath(os.path.join(dirpath, f), ROOT))
    drafts = os.path.join(d, "drafts.tsv")
    if os.path.exists(drafts):
        for line in open(drafts):
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 2 and parts[0].startswith("func_"):
                out.append(parts[1])
    return sorted(out)


def platform(name):
    """ovl/NAME/platform.tsv: {func: the port's replacement}"""
    path = os.path.join(ROOT, "ovl", name, "platform.tsv")
    out = {}
    if os.path.exists(path):
        for line in open(path):
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 2 and parts[0].startswith("func_"):
                out[parts[0]] = parts[1]
    return out


def bodies(srcs):
    """{func: (source, the names its body uses)}, a body running to the next definition"""
    out = {}
    for s in srcs:
        text = read_c(s)
        heads = list(HEAD_RX.finditer(text))
        for i, m in enumerate(heads):
            end = heads[i + 1].start() if i + 1 < len(heads) else len(text)
            out[m.group(1)] = (s, set(NAME_RX.findall(text[m.end():end])))
    return out


def reached(roots, body, stop):
    """the functions the roots reach through the C, not following the replaced ones"""
    seen, todo = set(), list(roots)
    while todo:
        f = todo.pop()
        if f in seen or f in stop:
            continue
        seen.add(f)
        todo += [n for n in body.get(f, ("", ()))[1] if n.startswith("func_")]
    return seen


def relocs(name):
    path = os.path.join(ROOT, "ovl", name, "relocs.tsv")
    rows = []
    if os.path.exists(path):
        for line in open(path):
            if line.strip() and not line.startswith(("#", "addr")):
                a, t, k = line.split()[:3]
                rows.append((int(a, 16), int(t, 16), k))
    return rows


def build(cc, cflags, out, nm):
    """Compile every overlay with sources; returns (objects, linked overlay names)."""
    objs, linked = [], []
    gen = []
    p = pins()
    for name in sorted(p):
        if not os.path.exists(os.path.join(ROOT, "ovl", name, "layout.tsv")):
            continue
        srcs = sources(name)
        # relocs.tsv (tools/ovl/relocs.py) marks an overlay as prepared for a native run
        if not srcs or not os.path.exists(os.path.join(ROOT, "ovl", name, "relocs.tsv")):
            continue
        funcs = layout(name)
        plat = platform(name)
        if plat:  # the port's own code replaces part of the overlay: only what the rest reaches
            body = bodies(srcs)
            keep = reached([funcs[0]] + ["func_%08x" % t for _a, t, k in relocs(name) if k == "func"], body, plat)
            funcs = [f for f in funcs if f in keep]
            srcs = sorted(set(body[f][0] for f in funcs if f in body))
        names = set(funcs)
        heads = set()
        for s in srcs:
            text = read_c(s)
            names |= set(NAME_RX.findall(text))
            heads |= set(HEAD_RX.findall(text))
        missing = [f for f in funcs if f not in heads]
        if missing:  # not every function has C yet: not worth compiling
            print("ovl: %s.x left out (C for %d / %d functions)" % (name, len(funcs) - len(missing), len(funcs)))
            continue
        names.discard("D_00F20000")
        od = os.path.join(out, "ovl", name)
        os.makedirs(od, exist_ok=True)
        hdr = os.path.join(od, "names.h")
        with open(hdr, "w") as f:
            f.write("/* generated by tools/host/ovlnative.py: %s.x's names, one module per overlay */\n" % name)
            for n in sorted(names):
                new = name + "_" + (n[5:] if n.startswith("func_") else n)
                f.write("#define %s %s\n" % (n, new))
        mine, bad = [], []
        for s in srcs:
            obj = os.path.join(od, s.replace("/", "__") + ".o")
            # a near-miss draft is plain C with no includes (tools/ovl/hand.py puts ovl.h in front)
            pre = ["-include", "ovl.h"] if s.startswith("nonmatchings/") else []
            r = subprocess.run([cc] + cflags + ["-Iovl/" + name, "-include", "platform/ovlsdk.h"] + pre + ["-include", hdr, "-c", "-o", obj, s], cwd=ROOT,
                               capture_output=True, text=True, env=dict(os.environ, LC_ALL="C"))
            if r.returncode:
                errs = [ln for ln in r.stderr.splitlines() if "error:" in ln] or r.stderr.strip().splitlines() or ["?"]
                bad.append((s, errs[0]))
            else:
                mine.append(obj)
        defined = nm(mine, True) if mine else set()
        missing = [f for f in funcs if name + "_" + f[5:] not in defined]
        if bad or missing:
            print("ovl: %s.x left out (native C for %d / %d functions%s)" % (
                name, len(funcs) - len(missing), len(funcs),
                "; %d files do not compile, first %s: %s" % (len(bad), bad[0][0], bad[0][1]) if bad else ""))
            if missing:
                print("  missing: " + " ".join(missing[:40]) + (" ..." if len(missing) > 40 else ""))
            for b in bad[:None if os.environ.get("KH1_OVL_ERRORS") else 0]:
                print("  %s: %s" % b)
            continue
        # the overlay's data names: their place in the memory map's overlay area
        data = sorted(n for n in names if n.startswith("D_"))
        rows = relocs(name)
        fix = []
        for a, t, k in rows:
            fn = "func_%08x" % t
            if k == "func" and fn in plat:
                fix.append((a, t, plat[fn]))
                continue
            if k == "func" and fn not in funcs:
                continue
            fix.append((a, t, name + "_" + fn[5:] if k == "func" else None))
        gen.append((name, p[name], name + "_" + funcs[0][5:], fix, data))
        gen += [(name, pin, name + "_" + funcs[0][5:], fix, None) for pin in extra_pins(name)]
        objs += mine
        linked.append(name)
    src = os.path.join(out, "ovl", "modules.c")
    os.makedirs(os.path.dirname(src), exist_ok=True)
    with open(src, "w") as f:
        f.write("/* generated by tools/host/ovlnative.py: the native overlays (include/platform/ovl.h) */\n")
        f.write('#include "common.h"\n#include "platform/ovl.h"\n')
        for name, (size, sha), entry, fix, data in gen:
            if data is None:  # another pin of the overlay before: its tables are written
                continue
            for fn in sorted(set(x[2] for x in fix if x[2])):
                f.write("void %s(void);\n" % fn)
            f.write("int %s();\n" % entry)
            f.write("static const KH1OvlFix %s_fix[] = {\n" % name)
            for a, t, fn in fix:
                f.write("    {0x%08X, 0x%08X, %s},\n" % (a, t, "(void *)" + fn if fn else "0"))
            f.write("    {0, 0, 0}\n};\n")
        f.write("const KH1OvlModule kh1_ovl_modules[] = {\n")
        for name, (size, sha), entry, fix, data in gen:
            f.write('    {"%s.x", %d, "%s", (int (*)(int, int))%s, %s_fix, %d},\n' % (name, size, sha, entry, name, len(fix)))
        f.write("    {0, 0, 0, 0, 0, 0}\n};\nconst int kh1_ovl_module_count = %d;\n" % len(gen))
    obj = os.path.join(out, "ovl", "modules.o")
    r = subprocess.run([cc] + cflags + ["-c", "-o", obj, src], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        print("ovl: %s does not compile:\n%s" % (os.path.relpath(src, ROOT), r.stderr))
    else:
        objs.append(obj)
    # the data names as linker-script symbols (an assembler .set to another object's symbol
    # stays undefined): census.py appends build.script to its aliases.ld. An assignment, not
    # PROVIDE (session 145): a CONTEXT_ONLY copy of an overlay variable (wm.x's
    # `CONTEXT_ONLY W58 D_00F87E98[1]`) is a weak definition off the EE, which a PROVIDE yields
    # to, so the C read a one-element array instead of the loaded file; a script assignment wins
    build.script = "".join("%s_%s = kh1_memmap + 0x%X;\n" % (name, d, int(d[2:], 16) - MEM_BASE)
                           for name, _p, _e, _f, data in gen for d in data or ())
    print("ovl: native overlays linked: %s" % (" ".join(n + ".x" + ("" if not extra_pins(n) else " (+%d pin%s)" % (
        len(extra_pins(n)), "s" if len(extra_pins(n)) > 1 else "")) for n in linked) or "none"))
    return objs, linked
