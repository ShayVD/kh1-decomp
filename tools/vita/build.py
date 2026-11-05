#!/usr/bin/env python3
"""The first Vita build (phase 5, docs/vita-build.md): the game's C, the data pieces and the
platform code (host/null's GS model and DMA walk, host/port, host/vita) compiled for the Vita's
Cortex-A9 with vitasdk, linked, and packed as out/vita/kh1-decomp.vpk.

    python3 -I tools/vita/build.py               # needs $VITASDK (or /usr/local/vitasdk) and a
                                                  # PS2 `make` first (the data pieces, symbols.ld)
    python3 -I tools/vita/build.py --linux-arm   # the same code for 32-bit ARM Linux (the host's
                                                  # null runner, host/null/main.c): out/armlinux/kh1-arm,
                                                  # run under qemu-arm (gcc-arm-linux-gnueabihf,
                                                  # qemu-user), to check the ARM build without a Vita

It reuses tools/host/census.py's compile and link steps with the Vita's compiler: the game files
and the drafts of the unmatched functions as census --exe takes them, the D_ names only the PS2
linker script places (defs_host.c) and the functions.tsv aliases (aliases.ld).

**The VPK holds bytes from your own ELF** (the data pieces and defs_host.c's initial values, as
the host build does): it is build output for your own Vita, never to be shared or committed.
The game's disc image is not in it; the Vita reads it from ux0:data/kh1/ (host/vita/main.c).

What runs and what does not: docs/vita-build.md.
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import zlib
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "host"))
import census  # noqa: E402

TITLE = "Kingdom Hearts (kh1-decomp)"
TITLE_ID = "KHDC00001"
VERSION = "00.01"

# census.py's host flags for ARM: gnu89 and the gcc 2.96 leniencies, char signed as on the EE
# (ARM's is unsigned), no fused multiply-add (portability rule 7)
CFLAGS = [
    "-std=gnu89", "-g", "-w", "-fsigned-char", "-fno-strict-aliasing", "-ffp-contract=off",
    "-Iinclude", "-Isrc", "-I" + census.KIT + "ucontext/std", "-Ihost/null", "-Ihost/vita",
    "-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion",
    "-Wno-error=incompatible-pointer-types", "-Wno-error=implicit-int",
]
# The optimisation (`--opt`, or KH1_VITA_OPT): the game's flags, the platform's (host/null, host/port, host/vita:
# the VU1 programs, the GS worker, the GPU thread) and the link's.  vitasdk's gcc already targets the Vita's A9
# by default (armv7-a, -mtune=cortex-a9, -mfpu=neon, hard float, Thumb-2: `arm-vita-eabi-gcc -v`), so -mcpu /
# -mfpu add nothing.  None changes a float result: -ffp-contract=off stays, no -ffast-math.  LTO is for the
# platform only: the game's files declare a function as a variable where they take its address (`extern u8
# func_x[]`, legal one file at a time), which LTO's merge refuses.  Fat objects: census.py's nm reads them.
LTO = ["-flto=auto", "-ffat-lto-objects"]
OPTS = {
    "o2": (["-O2"], [], []),
    "o3": (["-O3"], [], []),
    "lto": (["-O2"], LTO, ["-O2", "-flto=auto"]),
    "o3lto": (["-O3"], LTO, ["-O3", "-flto=auto"]),
}
DEFAULT_OPT = "o2"  # o3lto measured no faster on a Vita (docs/vita-build.md "Clocks and compiler flags")

# gcc 14 and later refuse these by default (vitasdk's gcc is 15; the Linux cross gcc may be older)
CFLAGS_GCC14 = ["-Wno-error=return-mismatch", "-Wno-error=declaration-missing-parameter-type"]

# vitasdk's gcc (arm-vita-eabi, a bare-metal EABI) makes an enum as small as its values, one byte for most;
# the EE's gcc and every host's make it an int.  The game's structs have enum fields (EN, a one-value enum the
# matching code uses for its alias set: grideff.c's EntLb), so on the Vita their layout was not the EE's: the
# grid effect's DMA tags came out wrong and the Dive's floor vanished every other frame (docs/vita-build.md
# "The flashing floor").  The game's files take int enums (-fno-short-enums); host/vita's own files keep
# the SDK's one-byte enums, which its structs (SceGxm's, vita2d's) are laid out for.
census_platform_flags = census.platform_flags
PLATFORM_OPT = []
# memmap.c defines its names in top-level asm (`.set`), which LTO's symbol table does not see
NO_LTO = {("port", "memmap.c")}
def platform_opt(d, f):
    return [x for x in PLATFORM_OPT if x not in LTO] if (d, f) in NO_LTO else PLATFORM_OPT
def vita_platform_flags(d, f):
    # the kit's modules (third_party/vita-port-kit) are vitasdk code like host/vita's: the SDK's enums
    sdk = d == "vita" or d.startswith("third_party/")
    return census_platform_flags(d, f) + platform_opt(d, f) + (["-fshort-enums"] if sdk else [])
def armlinux_platform_flags(d, f):
    return census_platform_flags(d, f) + platform_opt(d, f)

# --gxm's flags for host/vita/gxm.c and its stand-in (as tools/vita/gxmcheck.sh's, for ARM)
CFLAGS_GXM = ["-std=gnu99", "-w", "-DKH1_HOST", "-fno-pic", "-fno-stack-protector", "-mfpu=neon", "-Iinclude", "-Isrc",
              "-Ihost/null", "-Ihost/vita"]

# the two targets: the Vita, and 32-bit ARM Linux for qemu-arm (the host's null runner as it is,
# with the kit's context switch and host/armlinux's overlay answer)
TARGETS = {
    "vita": dict(
        out="out/vita", prefix="arm-vita-eabi-", defines=["-DKH1_VITA", "-fno-short-enums"],
        dirs=[("null", ("main.c",)), ("port", ()), ("vita", ()), (census.KIT_COSTACK, ()), (census.KIT_RING, ()), (census.KIT + "ucontext", ())]
        + [(census.KIT + m, ()) for m in ("config", "log", "clocks", "watchdog", "procparam")],
        link=["-Wl,-q", "-Wl,--no-warn-rwx-segments", "-Wl,--no-enum-size-warning"],
        libs=["-lvita2d", "-lvitashark", "-lSceShaccCgExt", "-lSceShaccCg_stub", "-ltaihen_stub", "-lSceKernelDmacMgr_stub", "-lSceDisplay_stub", "-lSceGxm_stub", "-lSceSysmodule_stub", "-lSceCommonDialog_stub",
              "-lSceAppMgr_stub", "-lScePgf_stub", "-lSceAudio_stub", "-lSceCtrl_stub", "-lSceTouch_stub", "-lSceSysmem_stub", "-lSceKernelModulemgr_stub", "-lScePower_stub", "-lm"]),
    "linux-arm": dict(
        out="out/armlinux", prefix="arm-linux-gnueabihf-", defines=["-DKH1_HOST", "-fno-pic", "-fno-stack-protector", "-mfpu=neon"],
        dirs=[("null", ()), ("port", ()), ("vita", ("main.c", "pad.c", "display.c", "menu.c")), ("armlinux", ()),
              (census.KIT_COSTACK, ()), (census.KIT_RING, ()), (census.KIT + "ucontext", ())],
        link=["-no-pie", "-Wl,--no-warn-execstack"], libs=["-lm"]),
}

# The overlay entry D_00F20000: the game loads an overlay's MIPS code there and calls its first byte,
# and the same name is the load's destination (and a sound bank's or a capture's buffer).  In the
# files that name it, the preprocessed text's calls (`D_00F20000(` outside a declaration, or a cast
# of it called at once, `...) D_00F20000)(`) go to kh1_ovl_entry (host/vita/main.c); every other use
# stays the buffer.  gumisave.c's func_001b9c60 keeps a cast pointer and calls it later: on the Vita
# that call jumps into data (the Gummi overlays are not decompiled either).
OVL_CALL = re.compile(r"(?<![\w\s])(\s*)D_00F20000(\s*\(|\s*\)\s*\()|(\b(?:return|else|do)\s+)D_00F20000(\s*\()")


def ovl_callers(files):
    return set(f for f in files if "D_00F20000" in open(os.path.join(ROOT, f), errors="replace").read())


def ovl_rewrite(text):
    """The calls of the overlay entry in a preprocessed file to kh1_ovl_entry; the count."""
    n = [0]

    def sub(m):
        n[0] += 1
        if m.group(3) is not None:
            return m.group(3) + "kh1_ovl_entry" + m.group(4)
        return m.group(1) + "kh1_ovl_entry" + m.group(2)
    text = OVL_CALL.sub(sub, text)
    return "int kh1_ovl_entry();\n" + text, n[0]


def assemble_data(asm, out):
    """src/data/*.s for ARM: `.word` is 4 bytes as on MIPS; `@progbits` / `@object` are `%` (`@` starts
    an ARM comment).  census.HOST_TAIL's zeros after a piece as on the host."""
    objs = []
    d = os.path.join(out, "data")
    os.makedirs(d, exist_ok=True)
    inc = open(os.path.join(ROOT, "include", "data", "piece.inc")).read().replace("@progbits", "%progbits") \
        .replace("@object", "%object")
    open(os.path.join(d, "piece.inc"), "w").write(inc)
    for f in sorted(os.listdir(os.path.join(ROOT, "src", "data"))):
        if not f.endswith(".s"):
            continue
        src = open(os.path.join(ROOT, "src", "data", f)).read()
        src = src.replace('"include/data/piece.inc"', '"%s"' % os.path.join(d, "piece.inc"))
        src = src.replace("@progbits", "%progbits").replace("@object", "%object")
        for name, n in census.HOST_TAIL.items():
            src = re.sub(r"^(\s*PIECE_END %s,.*)$" % name, r"\1\n\t.space 0x%x" % n, src, flags=re.M)
        tmp = os.path.join(d, f)
        open(tmp, "w").write(src)
        obj = tmp[:-2] + ".o"
        p = subprocess.run([asm, "-o", obj, tmp], cwd=ROOT, capture_output=True, text=True)
        if p.returncode:
            print("data: %s does not assemble: %s" % (f, p.stderr.strip().splitlines()[0]))
        else:
            objs.append(obj)
    return objs


def compile_game(cc, files, ovl, out):
    calls = {}

    def one(path):
        obj = os.path.join(out, path + ".o")
        os.makedirs(os.path.dirname(obj), exist_ok=True)
        src = path
        if path in ovl:
            p = subprocess.run([cc] + census.CFLAGS + ["-E", path], cwd=ROOT, capture_output=True, text=True)
            if p.returncode:
                return path, False, census.first_error(p.stderr) or [p.stderr.strip()[-300:]]
            text, calls[path] = ovl_rewrite(p.stdout)
            src = os.path.join(out, path + ".i")
            open(src, "w").write(text)
        p = subprocess.run([cc] + census.CFLAGS + ["-c", "-o", obj, src], cwd=ROOT, capture_output=True, text=True,
                           env=dict(os.environ, LC_ALL="C"))
        errs = census.first_error(p.stderr)
        return path, p.returncode == 0, errs or ([p.stderr.strip()[-300:]] if p.returncode else [])
    with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        res = list(ex.map(one, files))
    compile_game.calls = calls
    return res


def png_icon(path, w, h, rgb):
    """A plain one-colour 8-bit paletted PNG (the LiveArea wants indexed colour), made here: no
    image is committed."""
    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    raw = b"".join(b"\0" + bytes(w) for _ in range(h))
    data = b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 3, 0, 0, 0)) \
        + chunk(b"PLTE", bytes(rgb)) + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b"")
    open(path, "wb").write(data)


def run(args, what):
    p = subprocess.run(args, cwd=ROOT, capture_output=True, text=True)
    if p.returncode:
        print("vita: %s failed:\n%s%s" % (what, p.stdout[-3000:], p.stderr[-3000:]))
        sys.exit(1)
    return p


def tool_prefix(name):
    """The compiler prefix's directory: vitasdk's bin, or PATH for the Linux cross compiler."""
    if name == "vita":
        sdk = os.environ.get("VITASDK", "/usr/local/vitasdk")
        b = os.path.join(sdk, "bin")
        if not os.path.exists(os.path.join(b, "arm-vita-eabi-gcc")):
            sys.exit("vita: no vitasdk at %s (set VITASDK; docs/vita-build.md says how to get it)" % sdk)
        return b + os.sep
    p = subprocess.run(["sh", "-c", "command -v arm-linux-gnueabihf-gcc"], capture_output=True, text=True)
    if p.returncode:
        sys.exit("vita: --linux-arm needs arm-linux-gnueabihf-gcc (apt install gcc-arm-linux-gnueabihf qemu-user)")
    return os.path.dirname(p.stdout.strip()) + os.sep


def gcc_major(cc):
    v = subprocess.run([cc, "-dumpversion"], capture_output=True, text=True).stdout.strip()
    return int(v.split(".")[0]) if v[:1].isdigit() else 0


def code_gap(b, elf):
    """Bytes between the end of the executable LOAD segment and the next LOAD segment's start."""
    out = subprocess.run([b + "arm-vita-eabi-readelf", "-lW", elf], capture_output=True, text=True).stdout
    loads = [l.split() for l in out.splitlines() if l.strip().startswith("LOAD")]
    loads = sorted((int(x[2], 16), int(x[5], 16), "E" in x[6:-1]) for x in loads)
    for i, (va, memsz, ex) in enumerate(loads[:-1]):
        if ex:
            return loads[i + 1][0] - (va + memsz)
    return None


def package(b, out, elf):
    velf = os.path.join(out, "kh1.velf")
    run([b + "vita-elf-create", elf, velf], "vita-elf-create")
    eboot = os.path.join(out, "eboot.bin")
    run([b + "vita-make-fself", "-s", "-c", velf, eboot], "vita-make-fself")
    sfo = os.path.join(out, "param.sfo")
    run([b + "vita-mksfoex", "-s", "APP_VER=" + VERSION, "-s", "TITLE_ID=" + TITLE_ID,
         "-d", "ATTRIBUTE2=12", TITLE, sfo], "vita-mksfoex")
    sysdir = os.path.join(out, "sce_sys")
    os.makedirs(os.path.join(sysdir, "livearea", "contents"), exist_ok=True)
    png_icon(os.path.join(sysdir, "icon0.png"), 128, 128, (0x20, 0x30, 0x80))
    png_icon(os.path.join(sysdir, "livearea", "contents", "bg.png"), 840, 500, (0x10, 0x18, 0x40))
    png_icon(os.path.join(sysdir, "livearea", "contents", "startup.png"), 280, 158, (0x20, 0x30, 0x80))
    open(os.path.join(sysdir, "livearea", "contents", "template.xml"), "w").write(
        '<?xml version="1.0" encoding="utf-8"?>\n<livearea style="a1" format-ver="01.00" content-rev="1">\n'
        '  <livearea-background><image>bg.png</image></livearea-background>\n'
        '  <gate><startup-image>startup.png</startup-image></gate>\n</livearea>\n')
    vpk = os.path.join(out, "kh1-decomp.vpk")
    if os.path.exists(vpk):
        os.remove(vpk)
    pack = [b + "vita-pack-vpk", "-s", sfo, "-b", eboot]
    for f in ("icon0.png", "livearea/contents/bg.png", "livearea/contents/startup.png",
              "livearea/contents/template.xml"):
        pack += ["-a", "%s=sce_sys/%s" % (os.path.join(sysdir, f), f)]
    run(pack + [vpk], "vita-pack-vpk")
    return vpk


def translations_missing():
    """What census.platform_flags would fall back to the interpreter for (an empty list: both translations on):
    the sound driver (LIBSSL.IRX -> out/gen/iop_rec.c) and the VU1 programs (SLPS_251.98 -> out/gen/vu1_tr.c)."""
    out = []
    if not census.iop_flags():
        out.append("LIBSSL.IRX (from your own disc's root) is missing from the repo root or does not translate: "
                   "the sound driver would run on the interpreter")
    if not census_platform_flags("port", "vu1.c"):
        out.append("SLPS_251.98 is missing from the repo root or does not translate: the VU1 programs would run on "
                   "the interpreter")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--linux-arm", action="store_true", help="build out/armlinux/kh1-arm for qemu-arm instead")
    ap.add_argument("--gxm", action="store_true",
                    help="with --linux-arm: also out/armlinux/kh1-arm-gxm, the Vita's GPU renderer on the sceGxm "
                         "stand-in (tools/vita/gxmcheck.sh's, compiled for ARM)")
    ap.add_argument("--opt", choices=sorted(OPTS), default=os.environ.get("KH1_VITA_OPT", DEFAULT_OPT),
                    help="the optimisation (default %s; KH1_VITA_OPT sets it too)" % DEFAULT_OPT)
    ap.add_argument("--allow-interpreter", action="store_true",
                    help="build even without LIBSSL.IRX / SLPS_251.98 in the repo root: the sound driver (or the VU1 "
                         "programs) then run on the interpreter, much slower (KH1_VITA_ALLOW_INTERP=1 sets it too)")
    a = ap.parse_args()
    global PLATFORM_OPT
    opt_c, PLATFORM_OPT, opt_link = OPTS[a.opt]
    name = "linux-arm" if a.linux_arm else "vita"
    t = TARGETS[name]
    b = tool_prefix(name)
    cc = b + t["prefix"] + "gcc"
    out = os.path.join(ROOT, t["out"])
    if not os.path.exists(os.path.join(ROOT, "out", "gen", "symbols.ld")):
        sys.exit("vita: run the PS2 `make` first (out/gen/symbols.ld, out/data/pieces/)")

    # 2026-11-01: three VPKs in a row (natchain, pendgpu, main 9a95cf9) were built without LIBSSL.IRX in the repo
    # root, so their sound driver ran on the MIPS interpreter (~0.8 s of a core more per 2 s window) and nobody
    # noticed until a Vita log was read.  The translations are now required unless asked for otherwise.
    missing = translations_missing() if name == "vita" else []
    if missing:
        for m in missing:
            print("vita: " + m)
        if not (a.allow_interpreter or os.environ.get("KH1_VITA_ALLOW_INTERP") == "1"):
            sys.exit("vita: refusing to build a slow VPK; copy the file(s) above into the repo root, or pass "
                     "--allow-interpreter (docs/vita-build.md \"The sound's driver as C\")")
        print("vita: " + "!" * 60 + "\nvita: building WITHOUT the translation(s) above (--allow-interpreter)\n"
              "vita: " + "!" * 60)

    census.OUT = out
    census.CFLAGS = CFLAGS + opt_c + t["defines"] + (CFLAGS_GCC14 if gcc_major(cc) >= 14 else [])
    census.NM = b + t["prefix"] + "nm"
    census.TYPE_PREFIX = "%"
    census.PLATFORM_DIRS = t["dirs"]
    census.platform_flags = vita_platform_flags if name == "vita" else armlinux_platform_flags
    census.assemble_data = lambda: assemble_data(b + t["prefix"] + "as", out)
    os.makedirs(out, exist_ok=True)

    files = census.game_files() + census.draft_files()
    results = compile_game(cc, files, ovl_callers(files), out)
    bad = [r for r in results if not r[1]]
    calls = compile_game.calls
    print("%s: %d / %d game files compile (%d calls of the overlay entry in %d files)" %
          (name, len(results) - len(bad), len(results), sum(calls.values()), sum(1 for v in calls.values() if v)))
    for path, _ok, errs in bad[:20]:
        print("  %s: %s" % (path, (errs or ["?"])[0]))
    if bad:
        return 1

    census.link_census(results, cc)
    objs = census.link_census.objs
    extra = [census.link_census.script] if census.link_census.script else []
    elf = os.path.join(out, "kh1.elf" if name == "vita" else "kh1-arm")
    t["link"] = opt_link + t["link"]
    p = subprocess.run([cc] + t["link"] + ["-o", elf] + objs + extra + t["libs"], cwd=ROOT,
                       capture_output=True, text=True)
    if p.returncode:
        open(os.path.join(out, "link.log"), "w").write(p.stderr)
        syms = sorted(set(re.findall(r"undefined reference to `([^']+)'", p.stderr)))
        lines = [l for l in p.stderr.splitlines() if "undefined reference" in l or "multiple definition" in l]
        print("%s: the link fails (%d undefined: %s; %s/link.log)" % (name, len(syms), " ".join(syms[:30]), t["out"]))
        print("\n".join((lines or p.stderr.splitlines())[:10]))
        return 1
    if name == "vita":
        # vita-elf-create puts its import / export tables (~3 KiB) after the code segment, before the
        # data segment's page: when the code ends just short of a page (session 140: 1,168 bytes
        # left) it fails with "segment 1 overlaps".  Pad the code segment onto the next page then.
        gap = code_gap(b, elf)
        if gap is not None and gap < 0x1000:
            pad = os.path.join(out, "segpad.o")
            asm = os.path.join(out, "segpad.s")
            open(asm, "w").write('.section .rodata.kh1_segpad,"a"\n.space %d\n' % (gap + 512))
            run([b + "arm-vita-eabi-as", "-o", pad, asm], "the segment pad")
            run([cc] + t["link"] + ["-o", elf] + objs + [pad] + extra + t["libs"], "the padded link")
            print("vita: the code segment padded by %d bytes (%d were left before the data's page)" % (gap + 512, gap))
    if name == "vita":
        # the SDK reads these by name (the process parameters, newlib's heap); LTO drops a variable
        # nothing references, and the app then starts with the default 256 KiB stack and stops at once
        syms = subprocess.run([census.NM, elf], capture_output=True, text=True).stdout.split()
        lost = [s for s in ("sceUserMainThreadStackSize", "_newlib_heap_size_user") if s not in syms]
        if lost:
            print("vita: %s missing from the link (dropped by LTO?)" % " ".join(lost))
            return 1
    # 2026-11-02: a CONTEXT_ONLY copy (common.h: weak off the EE, "the real definition wins at link") wins when the
    # real one is in a library: an archive member is not pulled for a symbol already defined.  wm.x's draft
    # func_00f7ad38's sinf / cosf returning 0 replaced libm's for the whole game, and the 3D went black on the Vita.
    # Weak code left in the link is such a copy (the toolchain's own __aeabi_*div0 aside)
    nms = subprocess.run([census.NM, elf], capture_output=True, text=True).stdout.splitlines()
    weak = sorted(set(f[2] for f in (l.split() for l in nms) if len(f) == 3 and f[1] == "W" and not f[2].startswith("__aeabi_")))
    if weak:
        print("%s: weak code in the link, a CONTEXT_ONLY copy in place of the real definition: %s" % (name, " ".join(weak[:20])))
        print("  (guard the copy with #ifdef KH1_PS2 in its source)")
        return 1
    print("%s: %s linked (%d objects, --opt %s)" % (name, os.path.relpath(elf, ROOT), len(objs), a.opt))
    if name == "linux-arm" and a.gxm:
        # 2026-10-31: tools/vita/gxmcheck.sh's run on ARM (NEON, the Vita's float and struct layout), so the
        # native renderer's pictures can be compared with the x86 stand-in's (vita-build.md)
        sdk = os.environ.get("VITASDK", "/usr/local/vitasdk")
        cf = CFLAGS_GXM + opt_c + ["-I" + os.path.join(sdk, "arm-vita-eabi", "include")]
        gobjs = []
        for src in ("host/vita/gxm.c", "tests/host/gxm_mock.c"):
            o = os.path.join(out, os.path.basename(src) + ".gxm.o")
            run([cc] + cf + ["-c", src, "-o", o], src)
            gobjs.append(o)
        gelf = elf + "-gxm"
        run([cc] + t["link"] + ["-o", gelf] + objs + gobjs + extra + t["libs"], "the gxm link")
        print("linux-arm: %s linked (the GPU renderer on its stand-in)" % os.path.relpath(gelf, ROOT))
    if name == "linux-arm":
        print("linux-arm: run it as the host runner: KH1_HOST_ISO=... QEMU_LD_PREFIX=/usr/arm-linux-gnueabihf "
              "qemu-arm %s" % os.path.relpath(elf, ROOT))
        return 0
    vpk = package(b, out, elf)
    print("vita: %s (%d KiB): your own build, never share it (docs/vita-build.md)"
          % (os.path.relpath(vpk, ROOT), os.path.getsize(vpk) // 1024))
    return 0


if __name__ == "__main__":
    sys.exit(main())
