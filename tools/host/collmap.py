#!/usr/bin/env python3
"""The field's collision at one frame of a host run, for planning pad-script gotos (session 140).

    python3 -I tools/host/collmap.py dump FRAME DIR [--pad FILE] [--iso DISC]
    python3 -I tools/host/collmap.py at DIR X:Z ...            # the floors under each point (y, group, tri)
    python3 -I tools/host/collmap.py near DIR X Z R            # every triangle with a vertex within R
    python3 -I tools/host/collmap.py path DIR X Z Y  X Z Y [--rise R] [--rock]
    python3 -I tools/host/collmap.py map DIR OUT.png X0 Z0 X1 Z1 [name:X:Z ...]
    python3 -I tools/host/collmap.py slice DIR OUT.png X0 Z0 X1 Z1 YLO YHI [name:X:Z ...]

`dump` runs out/host/kh1-host under gdb to FRAME and saves the room's triangles (D_002A6238, count
D_002A6258, 20 bytes: s16 v[4] vertex indices (v[3] -1 for a triangle), s16 n, u8 act, u8 group, the
plane's d, the attribute word) and vertices (D_002A624C, 12-byte Vtx) to DIR, with the player's
position (D_002E26A0[0] + 0x10).  y grows downwards: a floor's y is negative above the sea.

A floor is a triangle whose normal's y is over 0.6 (its winding gives +y for floors, -y for ceilings).
`path` searches floor to floor: triangles sharing a vertex are a walk, vertices of two floors within
60 apart with a rise of at most R (110: a jump's height) are a jump; drops of any height are allowed.
Without --rock it leaves out the rock faces (attribute & 0x1b0 == 0x1b0: Sora slides off them).
It knows nothing of walls, ladders or exits: use `slice` (the walls crossing one height band) to check
a leg, and confirm every leg with a run (KH1_HOST_POS=N prints the player's position every N frames).
Seen in Destiny Islands' first room: a ladder is a thin wall with attribute 0x000d0120 (walk into it
to climb); the room's exits are floors with bit 0x1000 (t1293 at (-836, 1506), the west bridge t1282).
`map` draws the floors lowest first, a hue per 100 units of height, with their y; `slice` draws the
floors of one height band and the walls crossing it.  Pictures go to out/ or a scratch directory (they
show the user's own disc's level data: never commit them).
"""
import heapq
import math
import os
import struct
import subprocess
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
EXE = os.path.join(ROOT, "out", "host", "kh1-host")


def dump(a):
    frame, out = int(a[0]), os.path.abspath(a[1])
    pad = a[a.index("--pad") + 1] if "--pad" in a else os.environ.get("KH1_HOST_PAD")
    iso = a[a.index("--iso") + 1] if "--iso" in a else os.environ.get("KH1_HOST_ISO")
    os.makedirs(out, exist_ok=True)
    p = "((float*)((char*)D_002E26A0[0]+0x10))"
    g = ["handle SIGSEGV nostop noprint pass", "set pagination off",
         "break kh1_host_vblank if frames == %d" % frame, "run",
         'printf "tris %d\\n", D_002A6258',
         'printf "player %%f %%f %%f\\n", %s[0], %s[1], %s[2]' % (p, p, p),
         "dump binary memory %s/tris.bin (char*)D_002A6238 (char*)D_002A6238+20*D_002A6258" % out]
    open(os.path.join(out, "dump.gdb"), "w").write("\n".join(g) + "\n")
    env = dict(os.environ, KH1_HOST_CD="go", KH1_HOST_FRAMES=str(frame + 1), KH1_HOST_QUIET="1")
    if pad:
        env["KH1_HOST_PAD"] = pad
    if iso:
        env["KH1_HOST_ISO"] = iso
    r = subprocess.run(["gdb", "-batch", "-x", os.path.join(out, "dump.gdb"), EXE], env=env, cwd=ROOT,
                       capture_output=True, text=True).stdout
    lines = [l for l in r.splitlines() if l.startswith(("tris", "player"))]
    print("\n".join(lines))
    if not os.path.exists(os.path.join(out, "tris.bin")):
        print("collmap: no dump (gdb said: %s)" % r.strip().splitlines()[-1:], file=sys.stderr)
        return 1
    t = open(os.path.join(out, "tris.bin"), "rb").read()
    nv = max(max(struct.unpack_from("<4h", t, k * 20)) for k in range(len(t) // 20)) + 1
    g = g[:4] + ["dump binary memory %s/verts.bin (char*)D_002A624C (char*)D_002A624C+%d" % (out, 12 * nv)]
    open(os.path.join(out, "dump.gdb"), "w").write("\n".join(g) + "\n")
    subprocess.run(["gdb", "-batch", "-x", os.path.join(out, "dump.gdb"), EXE], env=env, cwd=ROOT,
                   capture_output=True, text=True)
    print("vertices %d" % nv)
    return 0


class Coll:
    def __init__(self, d):
        t = open(os.path.join(d, "tris.bin"), "rb").read()
        vb = open(os.path.join(d, "verts.bin"), "rb").read()
        self.tri = []          # (k, points, group, attr, normal, is_floor)
        for k in range(len(t) // 20):
            tr = struct.unpack_from("<4hhBBiI", t, k * 20)
            idx = [i for i in tr[:4] if i >= 0]
            if len(idx) < 3 or (max(idx) + 1) * 12 > len(vb):
                continue
            p = [struct.unpack_from("<3f", vb, i * 12) for i in idx]
            u = [p[1][j] - p[0][j] for j in range(3)]
            w = [p[2][j] - p[0][j] for j in range(3)]
            n = (u[1] * w[2] - u[2] * w[1], u[2] * w[0] - u[0] * w[2], u[0] * w[1] - u[1] * w[0])
            L = math.sqrt(sum(c * c for c in n)) or 1.0
            n = tuple(c / L for c in n)
            self.tri.append((k, p, tr[6], tr[8], n, idx, L / 2))

    @staticmethod
    def inside(x, z, p):
        c = False
        for i in range(len(p)):
            a, b = p[i], p[i - 1]
            if (a[2] > z) != (b[2] > z) and x < (b[0] - a[0]) * (z - a[2]) / (b[2] - a[2]) + a[0]:
                c = not c
        return c

    def floors(self, rock=True, sea=False):
        return [t for t in self.tri if t[4][1] > 0.6 and (rock or (t[3] & 0x1B0) != 0x1B0)
                and (sea or abs(t[4][1]) * t[6] < 4e6)]

    @staticmethod
    def y_at(t, x, z):
        p, n = t[1], t[4]
        return p[0][1] - (n[0] * (x - p[0][0]) + n[2] * (z - p[0][2])) / n[1]


def describe(t):
    k, p, g, fl, n = t[:5]
    return "t%d %s y %.0f..%.0f x %.0f..%.0f z %.0f..%.0f g%d attr %08x n %.2f %.2f %.2f" % (
        k, "floor" if n[1] > 0.6 else "ceil " if n[1] < -0.6 else "wall ",
        min(q[1] for q in p), max(q[1] for q in p), min(q[0] for q in p), max(q[0] for q in p),
        min(q[2] for q in p), max(q[2] for q in p), g, fl, n[0], n[1], n[2])


def at(a):
    c = Coll(a[0])
    fl = c.floors()
    for s in a[1:]:
        x, z = map(float, s.split(":"))
        hits = sorted((c.y_at(t, x, z), t[2], t[0]) for t in fl if c.inside(x, z, t[1]))
        print(s, " ".join("%.0f(g%d,t%d)" % h for h in hits))
    return 0


def near(a):
    c = Coll(a[0])
    x, z, r = map(float, a[1:4])
    for t in sorted(c.tri, key=lambda t: min(q[1] for q in t[1])):
        if min(math.hypot(q[0] - x, q[2] - z) for q in t[1]) <= r:
            print(describe(t))
    return 0


def path(a):
    rise = float(a[a.index("--rise") + 1]) if "--rise" in a else 110.0
    rock = "--rock" in a
    a = [s for i, s in enumerate(a) if s != "--rock" and s != "--rise" and (i == 0 or a[i - 1] != "--rise")]
    c = Coll(a[0])
    S, G = tuple(map(float, a[1:4])), tuple(map(float, a[4:7]))
    F = {t[0]: t for t in c.floors(rock)}
    cen = {k: tuple(sum(q[j] for q in t[1]) / len(t[1]) for j in range(3)) for k, t in F.items()}
    byv, grid = defaultdict(list), defaultdict(list)
    for k, t in F.items():
        for i in t[5]:
            byv[i].append(k)
        for q in t[1]:
            grid[(int(q[0] // 80), int(q[2] // 80))].append((k, q))
    adj = defaultdict(dict)
    for k, t in F.items():
        for i in t[5]:
            for m in byv[i]:
                if m != k:
                    adj[k][m] = "walk"
        for q in t[1]:
            gx, gz = int(q[0] // 80), int(q[2] // 80)
            for dx in (-1, 0, 1):
                for dz in (-1, 0, 1):
                    for m, r in grid[(gx + dx, gz + dz)]:
                        if m != k and m not in adj[k] and math.hypot(r[0] - q[0], r[2] - q[2]) < 60 \
                                and q[1] - r[1] <= rise:
                            adj[k][m] = "jump"

    def find(P):
        hits = [(abs(c.y_at(t, P[0], P[1]) - P[2]), k) for k, t in F.items() if c.inside(P[0], P[1], t[1])]
        return min(hits)[1] if hits else None
    s, g = find((S[0], S[1], S[2])), find((G[0], G[1], G[2]))
    if s is None or g is None:
        print("no floor under the %s" % ("start" if s is None else "goal"))
        return 1
    dist, prev, pq = {s: 0.0}, {}, [(0.0, s)]
    while pq:
        dd, k = heapq.heappop(pq)
        if k == g:
            break
        if dd > dist[k]:
            continue
        for m, kind in adj[k].items():
            nd = dd + math.hypot(cen[m][0] - cen[k][0], cen[m][2] - cen[k][2]) + (300 if kind == "jump" else 0)
            if nd < dist.get(m, 1e18):
                dist[m], prev[m] = nd, (k, kind)
                heapq.heappush(pq, (nd, m))
    if g not in prev and g != s:
        print("no path")
        return 1
    steps, k = [(g, "")], g
    while k != s:
        k, kind = prev[k]
        steps.append((k, kind))
    steps.reverse()
    for i, (k, _) in enumerate(steps):
        nxt = steps[i + 1][1] if i + 1 < len(steps) else ""
        print("%7.0f %7.0f %6.0f t%d %s" % (cen[k][0], cen[k][2], cen[k][1], k, ("-> " + nxt) if nxt else ""))
    return 0


def picture(a, band):
    from PIL import Image, ImageDraw
    import colorsys
    c = Coll(a[0])
    x0, z0, x1, z1 = map(float, a[2:6])
    if band:
        ylo, yhi = map(float, a[6:8])
    marks = [m.split(":") for m in a[(8 if band else 6):]]
    S = 1600 / max(x1 - x0, z1 - z0)
    W, H = int((x1 - x0) * S) + 1, int((z1 - z0) * S) + 1
    img = Image.new("RGB", (W, H), (255, 255, 255))
    dr = ImageDraw.Draw(img)
    P = lambda q: ((q[0] - x0) * S, (q[2] - z0) * S)
    fl = sorted(c.floors(), key=lambda t: -sum(q[1] for q in t[1]) / len(t[1]))
    for t in fl:
        y = sum(q[1] for q in t[1]) / len(t[1])
        if band and not ylo - 30 <= y <= yhi:
            continue
        r, g, b = colorsys.hsv_to_rgb(((int(-y) // 100) % 12) / 12, 0.45, 0.95)
        dr.polygon([P(q) for q in t[1]], fill=(int(r * 255), int(g * 255), int(b * 255)), outline=(150, 150, 150))
    for t in c.tri:
        ys = [q[1] for q in t[1]]
        if abs(t[4][1]) <= 0.6 and (not band or (min(ys) < ylo and max(ys) > ylo - 40)):
            dr.line([P(q) for q in t[1]] + [P(t[1][0])], fill=(0, 0, 0), width=2 if band else 1)
    if not band:
        for t in fl:
            if abs(t[4][1]) * t[6] * S * S > 2500:
                cx = sum(P(q)[0] for q in t[1]) / len(t[1])
                cz = sum(P(q)[1] for q in t[1]) / len(t[1])
                dr.text((cx - 10, cz - 5), "%d" % (sum(q[1] for q in t[1]) / len(t[1])), fill=(0, 0, 0))
    step = 100 if band else 500
    for gx in range(int(x0 // step) * step, int(x1) + 1, step):
        dr.line([((gx - x0) * S, 0), ((gx - x0) * S, H)], fill=(160, 160, 255))
        dr.text(((gx - x0) * S + 2, 2), str(gx), fill=(0, 0, 255))
    for gz in range(int(z0 // step) * step, int(z1) + 1, step):
        dr.line([(0, (gz - z0) * S), (W, (gz - z0) * S)], fill=(160, 160, 255))
        dr.text((2, (gz - z0) * S + 2), str(gz), fill=(0, 0, 255))
    for m in marks:
        px, pz = (float(m[1]) - x0) * S, (float(m[2]) - z0) * S
        dr.ellipse([px - 5, pz - 5, px + 5, pz + 5], fill=(255, 0, 0))
        dr.text((px + 7, pz - 6), m[0], fill=(200, 0, 0))
    img.save(a[1])
    return 0


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    cmd, a = sys.argv[1], sys.argv[2:]
    return {"dump": dump, "at": at, "near": near, "path": path,
            "map": lambda a: picture(a, False), "slice": lambda a: picture(a, True)}[cmd](a)


if __name__ == "__main__":
    sys.exit(main())
