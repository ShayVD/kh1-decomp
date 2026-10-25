#!/usr/bin/env python3
"""Walk the static DMA chains offline, over the PS2 ELF's bytes (phase 5, docs/vita-port-plan.md 5.1p).

  python3 -I tools/host/dmawalk.py [--elf SLPS_251.98] [--float ELF] [--regs] [-v] [--state] [--no-seeds] [--tsv out/host/dmawalk.tsv]

The Python twin of host/null/dmawalk.c (KH1_HOST_TRACE=2, docs/renderer-spec.md
4.4-4.6) for the sends whose chain is a name: dmacheck.py --list's "static data"
and "static bss" rows.  The host run reads only the chains the fake disc reaches;
this reads every one the ELF holds.  Per send: the channel (from the source:
PlatDmaGetChan(n), or the variable it was stored in), the chain walked tag by tag
the way the DMAC's source chain mode does, then its data read as the receiver
would: GIF packets on channel 2 (the tags dropped), VIF codes on VIF0 / VIF1 (each
tag's upper words first when the send sets TTE), and the data of a VIF1 DIRECT
read again as GIF packets (PATH2).  A chain that leaves the ELF's bytes, ends
inside a GIF packet or a VIF code's data, or holds a word that is no VIF code is a
row (exit 1).

SEEDS (session 78): the chains an init function builds from constants (the text
windows' headers, the menus' image uploads, the wave, texspot's tags) are written over
the ELF's bytes first, so they walk too ("seeded from" in the note); --no-seeds walks
the ELF alone.

Not rows: a chain in bss, or a data chain whose first tag is zero in the ELF
(built at run time: walk them on the host), and data the chain sends from bss, the
scratchpad or a code-range placeholder (filled at run time) when the receiver is
inside a packet that covers it (an IMAGE's pixels).  Data the receiver would parse
there stops the read ("run-time data").

--float ELF (the m12 float build, e.g. out/s37check/... or out/shift's linked ELF with
symbols): walks the same chain in that ELF from where its first name floated and
checks every tag sits at the same name + offset, every ADDR word points at the
same name + offset (relocated), and every data block holds the same bytes.  A
difference is a row: the shiftable build would send another chain.

--regs: the GS registers each send's PACKED / REGLIST / A+D writes touch (the
renderer's state census, renderer-spec 3.2 / 4.6); -v adds each value decoded
(tools/vu/gs_packets.py's fields).  --state (session 77): the renderer's state list instead
of the sends: each register's distinct values, decoded, and the functions that send each
(tools/host/gsstate.py makes the same list from a KH1_HOST_TRACE=4 run).  Prints names, counts and decoded fields, never
raw bytes; the output is derived from the user's ELF at run time: do not commit it.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import hashlib
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "host"))
sys.path.insert(0, str(ROOT / "tools" / "vu"))
import dmacheck  # noqa: E402
from elf32 import Elf  # noqa: E402

CODE = (0x00100000, 0x00272C70)
TAGS = ["refe", "cnt", "next", "ref", "refs", "call", "ret", "end"]
# PACKED register descriptors (REGLIST the same; 0xE A+D only in PACKED)
DESC = {0: "PRIM", 1: "RGBAQ", 2: "ST", 3: "UV", 4: "XYZF2", 5: "XYZ2", 6: "TEX0_1", 7: "TEX0_2",
        8: "CLAMP_1", 9: "CLAMP_2", 0xA: "FOG", 0xC: "XYZF3", 0xD: "XYZ3", 0xE: "A+D", 0xF: "NOP"}
VERTEX = {"RGBAQ", "ST", "UV", "XYZF2", "XYZ2", "XYZF3", "XYZ3", "FOG", "NOP"}


class Image:
    """an ELF's loaded bytes; bss and everything else unreadable"""

    def __init__(self, path: Path):
        self.elf = Elf.load(path)
        self.segs = [(s.vaddr, s.offset, s.filesz, s.memsz) for s in self.elf.segments if s.type == 1]
        self.seeds = []        # (address, bytes, builder): what the C writes at run time (SEEDS)

    def seed(self, a: int, data: bytes, src: str):
        self.seeds.append((a, data, src))

    def seeded(self, a: int, n: int = 16):
        """the seed holding [a, a + n) whole, or None"""
        for s in self.seeds:
            if s[0] <= a and a + n <= s[0] + len(s[1]):
                return s
        return None

    def kind(self, a: int, n: int = 16) -> str:
        """'elf' (bytes), 'bss', 'code' (a placeholder the game patches), 'spr' or 'outside'"""
        if self.seeded(a, n):
            return "elf"
        if RUNTIME[0] <= a < RUNTIME[1]:
            return "bss"
        if a & 0x80000000 or 0x70000000 <= a < 0x70004000:
            return "spr"
        if CODE[0] <= a < CODE[1]:
            return "code"
        for va, _off, fs, ms in self.segs:
            if va <= a and a + n <= va + fs:
                return "elf"
            if va <= a < va + ms and a + n <= va + ms:
                return "bss"
        return "outside"

    def read(self, a: int, n: int) -> bytes:
        s = self.seeded(a, n)
        if s:
            return s[1][a - s[0]:a - s[0] + n]
        return self.elf.read(a, n)

    def words(self, a: int) -> tuple[int, int, int, int]:
        return struct.unpack("<4I", self.read(a, 16))


class Names:
    """address -> (name, offset) from a sorted (addr, size, name) list"""

    def __init__(self, rows):
        self.rows = sorted(rows)
        self.keys = [r[0] for r in self.rows]
        self.by_name = {r[2]: r for r in self.rows}

    def at(self, a: int):
        i = bisect.bisect_right(self.keys, a) - 1
        if i >= 0:
            s, n, name = self.rows[i]
            if a < s + max(n, 1):
                return name, a - s
        return None

    def add(self, a: int, n: int, name: str):
        """a name data.tsv lacks (a bss name the linker script places)"""
        r = self.by_name.get(name)
        if r is None or (r[0] == a and r[1] < n):   # or a size-0 alias the float ELF lists
            self.__init__([x for x in self.rows if x[2] != name] + [(a, n, name)])

    @classmethod
    def ps2(cls):
        rows = []
        for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
            f = ln.split("\t")
            rows.append((int(f[0], 16), int(f[3], 16), f[1]))
        return cls(rows)

    @classmethod
    def from_elf(cls, elf: Elf):
        rows = [(s.value, s.size, s.name) for s in elf.symbols()
                if s.type in (0, 1) and s.shndx and re.match(r"D_[0-9A-F]{8}$", s.name)]
        return cls(rows)


# --- chains the C builds at run time from constants (session 78) ---------------------------
#
# 61 sends start at a chain that is zero in the ELF.  Most are not drawn at run time from
# data: an init function writes the whole packet from constants once and the senders send it
# as it is (the text windows' headers, the menus' image uploads, the wave), or writes only the
# tag over a packet the ELF holds (texspot).  Each seed below writes, over the ELF's bytes,
# what that C writes, so the walk reads those chains too (status "whole", note "seeded").
# An upload's source is the image a file load left in memory: RUNTIME stands for it (read as
# bss: the IMAGE packet covers it).  Not seeded: chains the C fills per frame from the model
# data (mdlgs's D_00351C40 / D_00573AC0 / D_00573E40) and grideff's D_002BC270, whose
# transfer size comes from the run (func_00106e18).  --no-seeds walks the ELF's bytes alone.
# The values were checked against the host build (gdb: the init functions' bytes, session 78).

RUNTIME = (0x01F00000, 0x02000000)   # a file's image in memory (an address no ELF byte has)
MASK = (1 << 64) - 1


def _q(a: int, b: int = 0) -> bytes:
    return struct.pack("<QQ", a & MASK, b & MASK)


def _end(qwc: int) -> int:
    """func_0011fb78(p, 7, end): an end tag"""
    return 0x70000000 | qwc


def _gif(nloop: int, eop: int) -> int:
    """func_0011fb48(t, eop, end): a PACKED GIF tag, one A+D register"""
    return nloop | eop << 15 | 1 << 60


def upload(a0, a1, a2, a3, a4, a5, a6, a7, a8) -> bytes:
    """func_0011fbb0(a0 ... a8, buf) (src/gfx/gifpkt.c): an image upload, 11 qwords.  BITBLTBUF
    DBP a0 DBW a1 DPSM a2, TRXPOS a3 / a4, TRXREG a5 x a6, TRXDIR 0, an IMAGE tag of a7 qwords
    whose pixels a ref tag sends from a8, then TEXFLUSH; the upper words it leaves are 0"""
    return b"".join([
        _q(0x10000006), _q(_gif(4, 0), 0xE),
        _q(a0 << 32 | a1 << 48 | a2 << 56, 0x50), _q(a3 << 32 | a4 << 48, 0x51),
        _q(a5 | a6 << 32, 0x52), _q(0, 0x53),
        _q(a7 | 1 << 59), _q(a7 | 0x30000000 | a8 << 32),
        _q(_end(2)), _q(_gif(1, 1), 0xE), _q(0, 0x3F)])


def _text_head(regs) -> bytes:
    """func_001f2eb8's packet headers: an end tag, a GIF tag (EOP), one A+D qword per register"""
    return _q(_end(len(regs) + 1)) + _q(0x1000000000008000 | len(regs), 0xE) + \
        b"".join(_q(v, r) for r, v in regs)


def _wave() -> bytes:
    """func_001e9670 (src/screen/wave.c): a cnt tag of 404 qwords (TEST_1, ALPHA_1, then a
    200-loop GIF tag over 100 strips of four qwords) and an end tag"""
    v = []
    for i in range(100):
        v += [struct.pack("<4i", i + 32, i + 96, i + 16, 96), struct.pack("<4i", 0x7880, (i + 2098) << 4, 0xFFFFFF, 0),
              struct.pack("<4i", i + 32, i + 96, i + 16, 96), struct.pack("<4i", 0x8780, (i + 2098) << 4, 0xFFFFFF, 0)]
    return _q(0x10000194) + _q(0x1000000000000002, 14) + _q(0x4000D, 71) + _q(68, 66) + \
        _q(0x2024C000000080C8, 65) + b"".join(v) + _q(0x70000000)


def _tag_over(img, a: int, qwc: int) -> bytes:
    """a builder that writes only the tag's first words (QWC, the id byte, ADDR 0) over the ELF's packet"""
    return struct.pack("<HBBI", qwc, img.read(a + 2, 1)[0], 0x70, 0) + img.read(a + 8, 8)


TEX0_FONT = 0x2007BF8621413D7C
TEX0_FONT2 = 0x2007FF8622411000
# (chain, builder, bytes(img, at)): at(name) is the name's address in that image
SEEDS = [
    ("D_003F1A70", "func_001f2eb8", lambda img, at: _text_head([(0x47, 0x4000D)])),
    ("D_003F1E70", "func_001f2eb8", lambda img, at: _text_head(
        [(0x47, 0x4000D), (0x3F, 0), (0x06, TEX0_FONT), (0x14, 0x61)])),
    ("D_003F2270", "func_001f2eb8", lambda img, at: _text_head(
        [(0x47, 0x4000D), (0x3F, 0), (0x06, TEX0_FONT2), (0x14, 0x61)])),
    ("D_003F27D0", "func_001f2eb8", lambda img, at: _text_head([(0x47, 0x5000D)])),
    ("D_003F2670", "func_001f2eb8", lambda img, at: upload(0x3D7C, 4, 20, 0, 0, 256, 256, 2048, at("D_003E9660"))),
    ("D_003F2720", "func_001f2eb8", lambda img, at: upload(0x3DFC, 1, 0, 0, 0, 16, 16, 64, at("D_003F1660"))),
    ("D_0035C4A0", "func_00175708", lambda img, at: _tag_over(img, at("D_0035C4A0"), 10)),
    ("D_0035C550", "func_00175708", lambda img, at: _tag_over(img, at("D_0035C550"), 16)),
    ("D_00631620", "func_001e9670", lambda img, at: _wave()),
    ("D_00641080", "func_0020b338", lambda img, at: upload(0x3600, 2, 0x13, 0, 0, 0x68, 0x38, 0x16C, RUNTIME[0])),
    ("D_00641130", "func_0020b338", lambda img, at: upload(0x3640, 1, 0, 0, 0, 0x10, 0x10, 0x40, RUNTIME[0])),
    ("D_00642D30", "func_00219500", lambda img, at: upload(0x3600, 4, 0x13, 0, 0, 0x8A, 0x58, 0x2F7, RUNTIME[0])),
    ("D_00642DE0", "func_00219500", lambda img, at: upload(0x3680, 1, 0, 0, 0, 0x10, 0x10, 0x40, RUNTIME[0])),
    ("D_00642EB0", "func_0021d188", lambda img, at: upload(0x3600, 4, 0x13, 0, 0, 0x100, 0x100, 0x1000, RUNTIME[0])),
    ("D_00642F60", "func_0021d188", lambda img, at: upload(0x3700, 1, 0, 0, 0, 0x10, 0x10, 0x40, RUNTIME[0])),
    ("D_00643290", "func_0021e120", lambda img, at: upload(0x3600, 2, 19, 0, 0, 64, 64, 256, RUNTIME[0])),
    ("D_00643340", "func_0021e120", lambda img, at: upload(0x3680, 1, 0, 0, 0, 16, 16, 64, RUNTIME[0])),
]


def apply_seeds(img: Image, at, names: Names | None = None) -> None:
    for name, src, build in SEEDS:
        data = build(img, at)
        img.seed(at(name), data, src)
        if names is not None:
            names.add(at(name), len(data), name)


# --- the receivers -------------------------------------------------------------------------

class Gif:
    """one stream of GIF packets, fed a qword at a time (None: bytes unknown here)"""

    def __init__(self):
        self.left = 0          # qwords (64-bit words for REGLIST) of the current packet to come
        self.mode = None       # 'packed' / 'reglist' / 'image'
        self.regs = []
        self.k = 0
        self.packets = self.eop = self.image = 0
        self.unknown = False   # a GIFtag in bytes not in the ELF
        self.writes = collections.Counter()
        self.values = []       # (register, 64-bit value) for -v

    def qword(self, q: bytes | None):
        if self.unknown:
            return
        if self.left:
            if q is not None and self.mode == "packed":
                self._packed(q)
            elif self.mode == "reglist":
                for h in (0, 8):
                    if self.left:
                        d = self.regs[self.k % len(self.regs)]
                        if q is not None and d != 0xE:
                            self._write(DESC.get(d), q[h:h + 8])
                        self.k += 1
                        self.left -= 1
                return
            self.left -= 1
            return
        if q is None:
            self.unknown = True
            return
        lo, hi = struct.unpack_from("<QQ", q)
        nloop, eop, pre, prim = lo & 0x7FFF, lo >> 15 & 1, lo >> 46 & 1, lo >> 47 & 0x7FF
        flg, nreg = lo >> 58 & 3, lo >> 60 & 15 or 16
        self.regs = [hi >> (4 * i) & 15 for i in range(nreg)]
        self.k = 0
        self.packets += 1
        self.eop += eop
        if pre and flg == 0:
            self._write("PRIM", struct.pack("<Q", prim))
        if flg == 0:
            self.mode, self.left = "packed", nloop * nreg
        elif flg == 1:
            self.mode, self.left = "reglist", nloop * nreg   # counted in 64-bit words
            if self.left & 1:
                self.left += 1                               # the last qword's upper half is padding
        else:
            self.mode, self.left = "image", nloop
            self.image += 1
            if nloop:
                self.writes["IMAGE"] += 1

    def _packed(self, q: bytes):
        d = self.regs[self.k % len(self.regs)]
        self.k += 1
        if d == 0xE:
            self._write("A+D", q[0:8], q[8] & 0x7F)
        else:
            self._write(DESC.get(d), q[0:8])

    def _write(self, name, v: bytes, reg: int | None = None):
        if name is None:
            return
        if name == "A+D":
            import gs_packets
            name = gs_packets.GSREG.get(reg, "reg%#x" % reg)
        self.writes[name] += 1
        if name not in VERTEX:
            self.values.append((name, struct.unpack("<Q", v)[0]))

    def short(self) -> bool:
        return bool(self.left) and not self.unknown

    def note(self) -> str:
        return "gif %d packets (%d eop, %d image)%s" % (self.packets, self.eop, self.image,
                                                        ": ENDS INSIDE A PACKET" if self.short() else "")


class Vif:
    """one stream of VIF codes and their data, fed 32-bit words (None: unknown)"""

    def __init__(self, vif0: bool):
        self.vif0 = vif0
        self.need = self.pad = self.pos = 0
        self.cl = self.wl = 0
        self.codes = self.unpacks = self.direct = self.mpg = 0
        self.bad = []
        self.unknown = False
        self.in_direct = False
        self.qw = []
        self.gif = Gif()       # PATH2: every DIRECT's data, one stream

    def word(self, w: int | None, at: int, pos: int | None = None):
        if pos is not None:
            self.pos = pos
        p, self.pos = self.pos, (self.pos + 1) & 3
        if self.unknown:
            return
        if self.pad:
            self.pad -= 1
            return
        if self.need:
            self.need -= 1
            if self.in_direct:
                self.qw.append(w)
                if len(self.qw) == 4:
                    self.gif.qword(None if None in self.qw else struct.pack("<4I", *self.qw))
                    self.qw = []
                if not self.need:
                    self.in_direct = False
            return
        if w is None:
            self.unknown = True
            return
        cmd, imm, num = w >> 24 & 0x7F, w & 0xFFFF, w >> 16 & 0xFF
        self.codes += 1
        if self.vif0 and cmd in (0x02, 0x03, 0x06, 0x50, 0x51):
            cmd = 0x7F
        if cmd in (0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x10, 0x11, 0x13, 0x14, 0x15, 0x17):
            return
        if cmd == 0x01:
            self.cl, self.wl = imm & 0xFF, imm >> 8 & 0xFF
            return
        if cmd == 0x20:
            self.need = 1
            return
        if cmd in (0x30, 0x31):
            self.need = 4
            return
        if cmd == 0x4A:
            self.mpg += 1
            self.pad = (p + 1) & 1
            self.need = (num or 256) * 2
            return
        if cmd in (0x50, 0x51):
            self.direct += 1
            self.pad = (4 - (p + 1)) & 3
            self.need = (imm or 0x10000) * 4
            self.in_direct = True
            return
        if cmd & 0x60 == 0x60:
            vn, vl, n = cmd >> 2 & 3, cmd & 3, num or 256
            if not (vl == 3 and vn != 3):
                bits = 16 if vl == 3 else (32 >> vl) * (vn + 1)
                if self.wl > self.cl and self.wl:
                    n = n // self.wl * self.cl + min(n % self.wl, self.cl)
                self.unpacks += 1
                self.need = (n * bits + 31) // 32
                return
        self.bad.append(at)

    def short(self) -> bool:
        return bool(self.need or self.pad) and not self.unknown

    def note(self, ch: int) -> str:
        s = "vif%d %d codes (%d unpack, %d mpg, %d direct)" % (ch, self.codes, self.unpacks, self.mpg, self.direct)
        if self.short():
            s += ": ENDS INSIDE A CODE"
        if self.bad:
            s += ": %d NOT A VIF CODE" % len(self.bad)
        if self.direct:
            s += "; path2 " + self.gif.note()
        return s


# --- the walk --------------------------------------------------------------------------------

def walk(img: Image, tadr: int, ch: int, tte: bool):
    """(tags, problems, receiver, notes): tags as (at, id, qwc, addr, data address, data kind)"""
    tags, probs, asr, tag = [], [], [], tadr
    done = False
    while not done and len(tags) < 4096:
        k = img.kind(tag)
        if k != "elf":
            probs.append("TAG %s at %08x" % (k.upper(), tag))
            break
        w0, addr, _u2, _u3 = img.words(tag)
        qwc, tid, nxt = w0 & 0xFFFF, w0 >> 28 & 7, tag + 16
        data = addr if tid in (0, 3, 4) else tag + 16
        if tid == 1:
            nxt = tag + 16 + qwc * 16
        elif tid == 2:
            nxt = addr
        elif tid == 5:
            if len(asr) == 2:
                probs.append("CALL TOO DEEP")
                break
            asr.append(tag + 16 + qwc * 16)
            nxt = addr
        elif tid == 6:
            if asr:
                nxt = asr.pop()
            else:
                done = True
        elif tid in (0, 7):
            done = True
        dk = img.kind(data, qwc * 16) if qwc else "elf"
        if dk == "outside":
            probs.append("DATA OUTSIDE at %08x" % data)
        tags.append((tag, tid, qwc, addr, data, dk))
        if probs:
            break
        tag = nxt
    if not done and not probs:
        probs.append("NO END")
    if probs:
        return tags, probs, None, []
    if ch == 2:
        rx = Gif()
        for _at, _tid, qwc, _addr, data, dk in tags:
            for i in range(qwc):
                rx.qword(img.read(data + i * 16, 16) if dk == "elf" else None)
        if rx.short():
            probs.append("ENDS INSIDE A GIF PACKET")
        notes = [rx.note()] + (["run-time data"] if rx.unknown else [])
    else:
        rx = Vif(ch == 0)
        for at, _tid, qwc, _addr, data, dk in tags:
            if tte:
                _w0, _a, u2, u3 = img.words(at)
                rx.word(u2, at + 8, 2)
                rx.word(u3, at + 12)
            rx.pos = 0
            for i in range(qwc * 4):
                rx.word(struct.unpack_from("<I", img.read(data + i * 4, 4))[0] if dk == "elf" else None,
                        data + i * 4)
        if rx.short():
            probs.append("ENDS INSIDE A VIF CODE")
        if rx.bad:
            probs.append("%d WORDS NOT A VIF CODE (first at %08x)" % (len(rx.bad), rx.bad[0]))
        if rx.gif.short():
            probs.append("PATH2 ENDS INSIDE A GIF PACKET")
        notes = [rx.note(ch)] + (["run-time data"] if rx.unknown or rx.gif.unknown else [])
    return tags, probs, rx, notes


# --- the sends -------------------------------------------------------------------------------

CHAN_RX = r"PlatDmaGetChan(?:As)?\s*\(\s*(?:[^(),]*,\s*)?(\d)\s*\)"


def channels():
    """global variables that hold a channel: name -> n"""
    out = {}
    for _rel, t in dmacheck.sources():
        for m in re.finditer(r"\b(D_[0-9A-F]{8})\s*=\s*" + CHAN_RX, t):
            out[m.group(1)] = int(m.group(2))
    return out


def channel_of(expr, before, gl):
    e = re.sub(r"\([^()]*\*\s*\)", "", expr).strip()
    m = re.fullmatch(CHAN_RX, e)
    if m:
        return int(m.group(1))
    if e in gl:
        return gl[e]
    ms = re.findall(r"\b%s\s*=\s*%s" % (re.escape(e), CHAN_RX), before)
    return int(ms[-1]) if ms else None


def tte_of(expr, before):
    """the send sets TTE: `c->tte = 1` (DmaChcr bit fields) or `|= 0x40` on the channel before it"""
    e = re.sub(r"\([^()]*\*\s*\)", "", expr).strip()
    tail = before[-1500:]
    sets = [m.group(1) for m in re.finditer(r"\b%s->tte\s*=\s*(\d)" % re.escape(e), tail)]
    return bool(sets) and sets[-1] == "1"


# dmapool's GIF send wrappers (channel 2, D_002A6B84): func_00106b18 sends its argument,
# func_00106bd8 queues it for func_00106b98's interrupt-time send
WRAPPERS = ("func_00106b18", "func_00106bd8")
FN_RX = re.compile(r"^(?!\s)[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{", re.M)


def wrapper_sends():
    """(rel, line, function, wrapper, D_ name) for each wrapper call handed a name"""
    out = []
    rx = re.compile(r"\b(%s)\s*\(\s*(?:\([^()]*\)\s*)?&?\s*(D_[0-9A-F]{8})\b" % "|".join(WRAPPERS))
    for rel, t in dmacheck.sources():
        fns = [(m.start(), m.group(1)) for m in FN_RX.finditer(t)]
        for m in rx.finditer(t):
            fn = [f for f in fns if f[0] < m.start()]
            out.append((rel, t.count("\n", 0, m.start()) + 1, fn[-1][1] if fn else "?", m.group(1), m.group(2)))
    return out


def static_sends(img: Image, names: Names):
    """(call, function, channel, tte, [(start name, start address)], kind)"""
    gl = channels()
    texts = dict(dmacheck.sources())
    out = []
    for rel, line, fn, ch, src, kind in dmacheck.sends():
        if not kind.startswith("static"):
            continue
        t = texts[rel]
        pos = sum(len(x) + 1 for x in t.split("\n")[:line - 1])
        before = t[max(0, t.rfind("\n}", 0, pos)):pos]
        n = channel_of(ch, before, gl)
        name = re.search(r"D_[0-9A-F]{8}", src).group(0)
        base = names.by_name.get(name) or (int(name[2:], 16), 0, name)
        starts = []
        if re.search(r"\[\s*[A-Za-z_]\w*\s*\]", src):
            # a table of chain pointers indexed at run time: every entry
            for i in range(0, base[1], 4):
                a = struct.unpack("<I", img.read(base[0] + i, 4))[0]
                if a:
                    starts.append(("%s[v=%d]" % (name, i // 4), a))
            seen = set()
            starts = [s for s in starts if not (s[1] in seen or seen.add(s[1]))]
        else:
            m = re.search(r"%s\s*\[\s*(\d+)\s*\]" % name, src)
            starts.append((name + ("[%s]" % m.group(1) if m else ""), base[0] + (int(m.group(1)) * 16 if m else 0)))
        out.append(("%s:%d" % (rel, line), fn, n, tte_of(ch, before), starts, kind.split()[1]))
    for rel, line, fn, w, name in wrapper_sends():
        out.append(("%s:%d" % (rel, line), "%s via %s" % (fn, w), 2, False, [(name, int(name[2:], 16))], "data"))
    return out


def ps2_of(nm):
    """(D_ name, offset) as the PS2 address it stands for: two names of one place (an alias) agree"""
    return int(nm[0][2:], 16) + nm[1] if nm else None


def same_chain(a_img, a_names, a_tags, b_img, b_names, b_start):
    """the float ELF's chain from b_start against the original's tags: [] or the differences"""
    diffs, tag, asr = [], b_start, []
    for at, tid, qwc, addr, data, dk in a_tags:
        if b_img.kind(tag) != "elf":
            return ["float tag at %08x not in the ELF" % tag]
        w0, baddr, _u2, _u3 = b_img.words(tag)
        bq, bid = w0 & 0xFFFF, w0 >> 28 & 7
        if (bq, bid) != (qwc, tid):
            return ["tag %s+%#x: %s %d, float %s %d" % (*a_names.at(at), TAGS[tid], qwc, TAGS[bid], bq)]
        if ps2_of(a_names.at(at)) != ps2_of(b_names.at(tag)):
            diffs.append("tag %s+%#x at float %s" % (*a_names.at(at), b_names.at(tag)))
        if tid in (0, 2, 3, 4, 5):
            na, nb = a_names.at(addr), b_names.at(baddr)
            if (ps2_of(na) if na else addr) != (ps2_of(nb) if nb else baddr):
                diffs.append("tag %s+%#x ADDR -> %s, float -> %s" % (
                    *a_names.at(at), "%s+%#x" % na if na else "%08x" % addr, "%s+%#x" % nb if nb else "%08x" % baddr))
        bdata = baddr if tid in (0, 3, 4) else tag + 16
        if qwc and dk == "elf":
            if b_img.kind(bdata, qwc * 16) != "elf" or \
                    hashlib.sha1(a_img.read(data, qwc * 16)).digest() != hashlib.sha1(b_img.read(bdata, qwc * 16)).digest():
                diffs.append("tag %s+%#x: data differs" % a_names.at(at))
        if tid == 1:
            tag = tag + 16 + qwc * 16
        elif tid == 2:
            tag = baddr
        elif tid == 5:
            asr.append(tag + 16 + qwc * 16)
            tag = baddr
        elif tid == 6 and asr:
            tag = asr.pop()
        else:
            tag += 16
    return diffs


def print_state(state):
    """state: register name -> value -> {sender: None}; one block per register (GS address order),
    each distinct value decoded with its sender count and senders (most senders first)"""
    import gs_packets
    num = {nm: r for r, nm in gs_packets.GSREG.items()}
    for n in sorted(state, key=lambda n: (num.get(n, 0x100), n)):
        print("%s: %d values" % (n, len(state[n])))
        for v, fns in sorted(state[n].items(), key=lambda kv: (-len(kv[1]), kv[0])):
            dec = gs_packets.decode(num[n], v) if n in num else "%#x" % v
            print("\t%-60s %2d  %s" % (dec, len(fns), " ".join(sorted(fns))))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--elf", type=Path, default=ROOT / "SLPS_251.98")
    ap.add_argument("--float", type=Path, help="a float ELF with symbols: check each chain moved whole")
    ap.add_argument("--regs", action="store_true", help="the GS registers each send writes")
    ap.add_argument("-v", action="store_true", help="with --regs: each value decoded")
    ap.add_argument("--state", action="store_true",
                    help="the renderer's state list: each distinct GS state value and the functions that send it")
    ap.add_argument("--no-seeds", action="store_true",
                    help="walk the ELF's bytes alone (no SEEDS: the chains init code builds are run time)")
    ap.add_argument("--tsv", type=Path)
    a = ap.parse_args()
    if a.state:
        a.regs = True
    if not (ROOT / "out/gen/data.tsv").exists():
        sys.exit("dmawalk: out/gen/data.tsv is missing: run make first")
    img, names = Image(a.elf), Names.ps2()
    fl = Image(a.float) if a.float else None
    fnames = Names.from_elf(fl.elf) if fl else None
    if not a.no_seeds:
        apply_seeds(img, lambda n: names.by_name[n][0] if n in names.by_name else int(n[2:], 16), names)
        if fl:
            def fat(n):
                if n in fnames.by_name:
                    return fnames.by_name[n][0]
                base, off = names.at(int(n[2:], 16))   # a name inside a bigger definition
                return fnames.by_name[base][0] + off
            apply_seeds(fl, fat, fnames)
    rows, tsv, total = [], [], collections.Counter()
    walked = {}
    counts = collections.Counter()
    state = collections.defaultdict(dict)   # register -> value -> {function: None}
    for call, fn, ch, tte, starts, kind in static_sends(img, names):
        if ch is None:
            rows.append((call, fn, "?", "channel not found"))
            continue
        for sname, start in starts:
            k = img.kind(start)
            if k != "elf":
                status, note = "run time", "in %s" % k
                counts["run time (%s)" % k] += 1
            elif img.read(start, 16) == bytes(16):
                status, note = "run time", "zero in the ELF"
                counts["run time (zero in the ELF)"] += 1
            else:
                key = (start, ch, tte)
                if key not in walked:
                    walked[key] = walk(img, start, ch, tte)
                tags, probs, rx, notes = walked[key]
                status = "PROBLEM" if probs else "whole"
                sd = img.seeded(start)
                counts[status + (" (seeded)" if sd else "")] += 1
                note = ("seeded from %s; " % sd[2] if sd else "") + "%d tags, %d qwords, ends with %s; %s" % (
                    len(tags), sum(t[2] for t in tags), TAGS[tags[-1][1]] if tags else "?", "; ".join(probs + notes))
                if probs:
                    rows.append((call, fn, sname, "; ".join(probs)))
                if fl and not probs:
                    base = sname.split("[")[0]
                    if base not in fnames.by_name and names.at(int(base[2:], 16)):
                        base = names.at(int(base[2:], 16))[0]   # a name inside a bigger definition
                    fs = fnames.by_name.get(base)
                    if fs is None:
                        d = ["%s not in the float ELF's symbols" % base]
                    else:
                        m = re.search(r"\[v=(\d+)\]$", sname)
                        if m:   # a table entry: the chain the float table's word names
                            fstart = struct.unpack("<I", fl.read(fs[0] + int(m.group(1)) * 4, 4))[0]
                        else:
                            # a D_ name is its PS2 address (an alias the float ELF keeps need not be in data.tsv)
                            fstart = fs[0] + start - int(base[2:], 16)
                        d = same_chain(img, names, tags, fl, fnames, fstart)
                    note += "; float: " + ("same chain" if not d else "; ".join(d[:3]))
                    counts["float same" if not d else "float DIFF"] += 1
                    if d:
                        rows.append((call, fn, sname, "float: " + "; ".join(d[:3])))
                if a.regs and rx is not None:
                    g = rx if isinstance(rx, Gif) else rx.gif
                    total.update(g.writes)
                    if g.writes:
                        st = sorted(n for n in g.writes if n not in VERTEX)
                        note += "; regs " + " ".join("%s%s" % (n, "x%d" % g.writes[n] if g.writes[n] > 1 else "")
                                                     for n in st)
                        vx = sum(g.writes[n] for n in g.writes if n in VERTEX)
                        if vx:
                            note += " + %d vertex words" % vx
            if a.state and status == "whole":
                rx = walked[(start, ch, tte)][2]
                g = rx if isinstance(rx, Gif) else rx.gif
                for n, v in g.values:
                    state[n].setdefault(v, {})[fn] = None
            if a.state:
                continue
            print("%s\t%s\tch %d%s\t%s\t%s\t%s" % (call, fn, ch, " tte" if tte else "", sname, status, note))
            tsv.append((call, fn, str(ch), "tte" if tte else "", sname, status, note))
            if a.regs and a.v and status == "whole":
                import gs_packets
                rx = walked[(start, ch, tte)][2]
                g = rx if isinstance(rx, Gif) else rx.gif
                for n, v in dict.fromkeys(g.values):
                    try:
                        dec = gs_packets.decode(next(r for r, nm in gs_packets.GSREG.items() if nm == n), v)
                    except StopIteration:
                        dec = ""
                    print("\t\t%-10s %s" % (n, dec))
    if a.state:
        print_state(state)
    elif a.regs:
        print("# registers written, all sends: " + ", ".join("%s %d" % kv for kv in sorted(total.items())))
    for r in rows:
        print("ROW\t" + "\t".join(r))
    print("# %d static sends walked: %s; %d rows" % (sum(counts[k] for k in counts if not k.startswith("float")),
          ", ".join("%s %d" % kv for kv in sorted(counts.items())), len(rows)), file=sys.stderr)
    if a.tsv:
        a.tsv.parent.mkdir(parents=True, exist_ok=True)
        a.tsv.write_text("call\tfunction\tchannel\ttte\tchain\tstatus\tnote\n" +
                         "".join("\t".join(r) + "\n" for r in tsv))
    return 1 if rows else 0


if __name__ == "__main__":
    sys.exit(main())
