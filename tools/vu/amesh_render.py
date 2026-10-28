#!/usr/bin/env python3
"""Draw a room's renderer A meshes (VU1 P0-P7) from the user's own map files,
textured, with nothing but the layouts in docs/renderer-spec.md section 2.2:
a reference picture for the port's renderer and a check of the spec.

  python3 -I tools/vu/amesh_render.py ROOM.bin ROOM.img --eye=X,Y,Z --at=X,Y,Z -o OUT.png
        [--layers AB] [--far 2,3] [--tint] [--fov 60] [--size 960x720]

ROOM.bin / ROOM.img are `<ww>00_<nn>.bin` and `.img` from tools/shift/extract_kingdom.py.
The .img is loaded into a model of GS memory the way func_00101048 uploads it
(CLUTs to blocks 0x3E00 + i, PSMT8 / PSMT4 pages to 0x2600 + 256 i, the PSMT8H
page at block 0). The grid's cells (section 1) are walked with
amesh_survey.py's VIF model; each strip is drawn with the TEX0_2 / CLAMP_2 its
mesh set last (CLUT CT32, CSM1), ST as 1.12 fixed point, vertex colour
x texel / 128, strip flag 0 = restart. Layer A is opaque (a texel with alpha 0
is not drawn, standing in for the alpha test), layer B is blended over it by
its alpha in the order of the cells (key 50000, no Z writes). --far draws the
far meshes of sections 2 / 3 (the sky, P4) instead, with the textures their
own packets upload. --tint colours layer B: blue = no P3 flag, green = UV
scroll slot, red = env map. Y is down in the game's space (the camera's up is
-Y). Not modelled: fog, the colour scale qw6, the clipper, mip levels,
filtering, the alpha test's exact reference.

Needs numpy and Pillow (not stdlib). The picture derives from the user's own
files: never commit it.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parent))
import amesh_survey as survey  # noqa: E402

CT32, T8, T4, T8H = 0x00, 0x13, 0x14, 0x1B


# GS memory: the address swizzles of host/null/gsmem.c (kh1_gsmem_addr), vectorised.
def _col32(x, y):
    return (x & 1) | (y & 1) << 1 | (x & 6) << 1 | (y & 6) << 3


def _blk32(x, y):
    return (x & 1) | (y & 1) << 1 | (x & 2) << 1 | (y & 2) << 2 | (x & 4) << 2


def _blk16(x, y):
    return (y & 1) | (x & 1) << 1 | (y & 2) << 1 | (x & 2) << 2 | (y & 4) << 2


def _col8w(x, by):
    swap = ((by >> 1) ^ (by >> 2)) & 1
    return _col32((x & 7) ^ (swap << 2), (by >> 2) * 2 + (by & 1))


def gs_addr(psm: int, bp: int, bw: int, x, y):
    """Word (CT32, T8H), byte (T8) or nibble (T4) address of pixel x, y."""
    x = np.asarray(x, np.int64) & 2047
    y = np.asarray(y, np.int64) & 2047
    if psm in (CT32, T8H):
        b = bp + (y >> 5) * bw * 32 + (x >> 6) * 32 + _blk32(x >> 3 & 7, y >> 3 & 3)
        return (b & 0x3FFF) * 64 + _col32(x & 7, y & 7)
    if psm == T8:
        b = bp + (y >> 6) * (bw >> 1) * 32 + (x >> 7) * 32 + _blk32(x >> 4 & 7, y >> 4 & 3)
        return (b & 0x3FFF) * 256 + _col8w(x, y & 15) * 4 + (x >> 3 & 1) * 2 + (y >> 1 & 1)
    if psm == T4:
        b = bp + (y >> 7) * (bw >> 1) * 32 + (x >> 7) * 32 + _blk16(x >> 5 & 3, y >> 4 & 7)
        return (b & 0x3FFF) * 512 + _col8w(x, y & 15) * 8 + (x >> 3 & 3) * 2 + (y >> 1 & 1)
    raise ValueError(f"PSM {psm:#x} not modelled")


class GsMem:
    def __init__(self) -> None:
        self.vm = np.zeros(4 << 20, np.uint8)
        self.cache: dict[int, np.ndarray] = {}

    def upload(self, psm: int, bp: int, bw: int, w: int, h: int, data: bytes) -> None:
        self.cache.clear()
        yy, xx = np.mgrid[0:h, 0:w]
        a = gs_addr(psm, bp, bw, xx.ravel(), yy.ravel())
        d = np.frombuffer(data, np.uint8)
        if psm == CT32:
            v = d[:w * h * 4].reshape(-1, 4)
            for k in range(4):
                self.vm[a * 4 + k] = v[:, k]
        elif psm == T8H:
            self.vm[a * 4 + 3] = d[:w * h]
        elif psm == T8:
            self.vm[a] = d[:w * h]
        elif psm == T4:
            n = np.empty(w * h, np.uint8)
            n[0::2] = d[:w * h // 2] & 15
            n[1::2] = d[:w * h // 2] >> 4
            byte = a >> 1
            for par in (0, 1):
                m = (a & 1) == par
                self.vm[byte[m]] = (self.vm[byte[m]] & (0xF0 >> (par * 4))) | (n[m] << (par * 4))

    def read(self, psm: int, bp: int, bw: int, x, y):
        a = gs_addr(psm, bp, bw, x, y)
        if psm == CT32:
            return self.vm[a[..., None] * 4 + np.arange(4)]
        if psm == T8H:
            return self.vm[a * 4 + 3]
        if psm == T8:
            return self.vm[a]
        return (self.vm[a >> 1] >> ((a & 1) * 4)) & 15

    def texture(self, tex0: int) -> np.ndarray:
        """The whole TW x TH RGBA picture TEX0 names (CT32 CLUT, CSM1)."""
        if tex0 not in self.cache:
            tbp, tbw, psm = tex0 & 0x3FFF, tex0 >> 14 & 0x3F, tex0 >> 20 & 0x3F
            tw, th, cbp = 1 << (tex0 >> 26 & 0xF), 1 << (tex0 >> 30 & 0xF), tex0 >> 37 & 0x3FFF
            yy, xx = np.mgrid[0:th, 0:tw]
            idx = self.read(psm, tbp, tbw, xx, yy).astype(np.int64)
            if psm in (T8, T8H):
                j = (idx & 0xE7) | ((idx & 8) << 1) | ((idx & 0x10) >> 1)
                clut = self.read(CT32, cbp, 1, j & 15, j >> 4)
            else:
                clut = self.read(CT32, cbp, 1, idx & 7, idx >> 3)
            self.cache[tex0] = clut.astype(np.float32)
        return self.cache[tex0]


def load_img(gs: GsMem, data: bytes) -> None:
    """func_00101048: the .img header {o0, n0, o8, -, o10, -, o18, -, o20, n20}."""
    h = struct.unpack_from("<10I", data, 0)
    so, tex, big = h[2], h[4], h[6]
    kinds = data[so:so + 16]
    n0, n1 = struct.unpack_from("<HH", data, so + 0x14)
    for i in range(n0):
        gs.upload(CT32, 0x3E00 + i, 1, 8, 2, data[tex + i * 256:tex + i * 256 + 64])
    for i in range(n0, n1, 4):
        gs.upload(CT32, 0x3E00 + i, 1, 16, 16, data[tex + i * 256:tex + i * 256 + 1024])
    for i in range(16):
        page = data[big + i * 0x10000:big + (i + 1) * 0x10000]
        if kinds[i] == 19:
            gs.upload(T8, 0x2600 + 256 * i, 4, 256, 256, page)
        elif kinds[i] == 20:
            gs.upload(T4, 0x2600 + 256 * i, 8, 512, 256, page)
    gs.upload(T8H, 0, 4, 256, 1024, data[big + 0x100000:big + 0x140000])


def f32(w: int) -> float:
    return struct.unpack("<f", struct.pack("<I", w))[0]


class Capture(survey.Vif):
    """The survey's VIF model, keeping each batch's strips and the GS state set before it."""

    def __init__(self, st, kind, where, tris, gs=None):
        super().__init__(st, kind, where)
        self.tris, self.gs = tris, gs
        self.tex0 = self.clamp = None
        self.bb = self.trx = 0

    def fields(self, reg: int, v: int) -> None:
        if reg in (6, 7):
            self.tex0 = v
        elif reg in (8, 9):
            self.clamp = v
        elif reg == 0x50:
            self.bb = v
        elif reg == 0x52:
            self.trx = v

    def direct(self, d: bytes, a: int, nq: int) -> None:
        if self.gs is None:
            return super().direct(d, a, nq)
        end = a + nq * 16
        while a < end:                     # A+D state and IMAGE uploads (the far meshes' textures)
            lo, hi = struct.unpack_from("<QQ", d, a)
            a += 16
            nloop, flg, nreg = lo & 0x7FFF, lo >> 58 & 3, (lo >> 60 & 0xF) or 16
            if flg == 0:
                for _ in range(nloop * nreg):
                    v, r = struct.unpack_from("<QB", d, a)
                    self.fields(r, v)
                    a += 16
            elif flg == 2:
                bb, trx = self.bb, self.trx
                self.gs.upload(bb >> 56 & 0x3F, bb >> 32 & 0x3FFF, bb >> 48 & 0x3F, trx & 0xFFF,
                               trx >> 32 & 0xFFF, d[a:a + nloop * 16])
                a += nloop * 16

    def mscnt(self) -> None:
        hdr = self.mem.get(0)
        if hdr is None or self.kind == "template":
            self.mem.clear()
            self.unpacks.clear()
            return
        n = hdr[0] & 0x7FFF
        prim = (hdr[0] | hdr[1] << 32) >> 47 & 0x7FF
        vs = []
        for v in range(n):
            q0, q1, q2 = self.mem[1 + 3 * v], self.mem[2 + 3 * v], self.mem[3 + 3 * v]
            vs.append(((f32(q0[0]), f32(q0[1]), f32(q0[2])), q0[3], tuple(q1),
                       (survey.s32(q2[0]) / 4096.0, survey.s32(q2[1]) / 4096.0), survey.s32(q2[3]) & 0xFFFF))
        for v in range(2, n):
            if vs[v][1] == 0:
                continue
            tri = vs[v - 2:v + 1]
            self.tris.append((self.kind, [t[0] for t in tri], [t[2] for t in tri], [t[3] for t in tri],
                              vs[v][4], self.tex0 if prim >> 4 & 1 else None, self.clamp or 0))
        self.mem.clear()
        self.unpacks.clear()


def load_cells(d: bytes, layers: str):
    u32 = lambda o: struct.unpack_from("<I", d, o)[0]  # noqa: E731
    s1 = u32(0x18)
    n, et = u32(s1), u32(s1 + 4)
    tris, st = [], survey.Stats()
    for i in range(n):
        a, aa, b, bb = struct.unpack_from("<4I", d, s1 + et + 16 * (i + 1))
        for kind, lo, ad in (("A", a, aa), ("B", b, bb)):
            if lo and kind in layers:
                Capture(st, kind, f"cell {i}", tris).run(d, s1 + ad, s1 + ad + (lo & 0xFFFF) * 16)
    return tris


def load_far(d: bytes, gs: GsMem, secs):
    u32 = lambda o: struct.unpack_from("<I", d, o)[0]  # noqa: E731
    tris, st = [], survey.Stats()
    for sec in secs:
        o = u32(0x10 + 8 * sec)
        lo, ad = u32(o + 0x90), u32(o + 0x94)
        Capture(st, "A", f"section {sec}", tris, gs).run(d, o + ad, o + ad + (lo & 0xFFFF) * 16)
    return tris


def _wrap(u, mode, mn, mx, size):
    u = np.floor(u).astype(np.int64)
    if mode == 0:
        u = u % size
    elif mode == 1:
        u = np.clip(u, 0, size - 1)
    elif mode == 2:
        u = np.clip(u, mn, mx)
    else:
        u = (u & mn) | mx
    return np.clip(u, 0, size - 1)


def render(tris, gs: GsMem, eye, at, w: int, h: int, fov: float, tint: bool) -> Image.Image:
    eye, at = np.array(eye, float), np.array(at, float)
    fwd = (at - eye) / np.linalg.norm(at - eye)
    right = np.cross(fwd, [0.0, -1.0, 0.0])
    right /= np.linalg.norm(right)
    up = np.cross(right, fwd)
    fl = (h / 2) / np.tan(np.radians(fov / 2))
    img = np.zeros((h, w, 3), np.float32)
    img[:] = (40, 40, 60)
    dep = np.full((h, w), np.inf, np.float32)
    for kind, pos, col, st, flag, tex0, clamp in sorted(tris, key=lambda t: t[0] != "A"):
        p = np.array(pos) - eye
        cz = p @ fwd
        if (cz < 10).any():
            continue                      # the VU clipper's job; dropped here
        sx, sy = w / 2 + fl * (p @ right) / cz, h / 2 - fl * (p @ up) / cz
        x0, x1 = max(int(sx.min()), 0), min(int(sx.max()) + 1, w - 1)
        y0, y1 = max(int(sy.min()), 0), min(int(sy.max()) + 1, h - 1)
        if x0 > x1 or y0 > y1:
            continue
        xx, yy = np.meshgrid(np.arange(x0, x1 + 1) + .5, np.arange(y0, y1 + 1) + .5)
        (ax, bx, cx), (ay, by, cy) = sx, sy
        den = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy)
        if abs(den) < 1e-9:
            continue
        l1 = ((by - cy) * (xx - cx) + (cx - bx) * (yy - cy)) / den
        l2 = ((cy - ay) * (xx - cx) + (ax - cx) * (yy - cy)) / den
        l3 = 1 - l1 - l2
        iz = l1 / cz[0] + l2 / cz[1] + l3 / cz[2]
        z = 1 / np.where(iz == 0, 1e-9, iz)
        sub, im = dep[y0:y1 + 1, x0:x1 + 1], img[y0:y1 + 1, x0:x1 + 1]
        m = (l1 >= 0) & (l2 >= 0) & (l3 >= 0) & (z < sub)
        if not m.any():
            continue
        w1, w2, w3 = l1 / cz[0] * z, l2 / cz[1] * z, l3 / cz[2] * z
        c = np.array(col, float)
        rgba = w1[..., None] * c[0] + w2[..., None] * c[1] + w3[..., None] * c[2]
        if tex0 is not None:
            tex = gs.texture(tex0)
            th, tw = tex.shape[:2]
            s = np.array(st)
            u = (w1 * s[0, 0] + w2 * s[1, 0] + w3 * s[2, 0]) * tw
            v = (w1 * s[0, 1] + w2 * s[1, 1] + w3 * s[2, 1]) * th
            ui = _wrap(u, clamp & 3, clamp >> 4 & 0x3FF, clamp >> 14 & 0x3FF, tw)
            vi = _wrap(v, clamp >> 2 & 3, clamp >> 24 & 0x3FF, clamp >> 34 & 0x3FF, th)
            texel = tex[vi, ui]
            rgb, a = texel[..., :3] * rgba[..., :3] / 128.0, texel[..., 3] * rgba[..., 3] / 128.0
        else:
            rgb, a = rgba[..., :3], rgba[..., 3]
        rgb = np.clip(rgb, 0, 255)
        if kind == "A":
            mm = m & (a > 0) if tex0 is not None else m
            sub[mm] = z[mm]
            im[mm] = rgb[mm]
        else:
            al = np.clip(a / 128.0, 0, 1)
            if tint:
                rgb = rgb * 0.5 + np.array([0, 80, 255] if flag == 0 else
                                           [255, 40, 40] if flag == 0x11 else [0, 255, 60]) * 0.5
            im[m] = im[m] * (1 - al[m, None]) + rgb[m] * al[m, None]
    return Image.fromarray(np.clip(img, 0, 255).astype(np.uint8))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("bin", type=Path)
    ap.add_argument("img", type=Path)
    ap.add_argument("--eye", required=True, help="camera position x,y,z (game units, y down)")
    ap.add_argument("--at", required=True, help="point looked at x,y,z")
    ap.add_argument("-o", "--out", required=True, type=Path)
    ap.add_argument("--layers", default="AB", help="grid layers to draw: A, B or AB")
    ap.add_argument("--far", help="draw the far meshes of these sections instead (2, 3 or 2,3)")
    ap.add_argument("--tint", action="store_true")
    ap.add_argument("--fov", type=float, default=60.0)
    ap.add_argument("--size", default="960x720")
    a = ap.parse_args()
    d = a.bin.read_bytes()
    gs = GsMem()
    load_img(gs, a.img.read_bytes())
    if a.far:
        tris = load_far(d, gs, [int(s) for s in a.far.split(",")])
    else:
        tris = load_cells(d, a.layers)
    pts = np.array([t[1] for t in tris]).reshape(-1, 3)
    print(f"{len(tris)} triangles; bounds {pts.min(0).round()} .. {pts.max(0).round()}")
    w, h = (int(x) for x in a.size.split("x"))
    eye = [float(x) for x in a.eye.split(",")]
    at = [float(x) for x in a.at.split(",")]
    render(tris, gs, eye, at, w, h, a.fov, a.tint).save(a.out)
    print(f"wrote {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
