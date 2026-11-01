/* The native renderer's CPU side (include/platform/natdraw.h, docs/native-renderer.md): a run's strips as GPU
 * triangles, and the run's matrices folded with the screen mapping.  Plain C with no libc but memcpy (the Vita
 * build compiles host/port/).  Not part of the PS2 build. */
#include "common.h"
#include "platform/natdraw.h"
#include "platform/depth.h"

void *memcpy(void *, const void *, __SIZE_TYPE__);

static f32 nf(u32 v) {
    union { u32 u; f32 f; } x;
    x.u = v;
    return x.f;
}

static void put(KH1GpuVert *o, const u32 *v, u32 rgba, u32 f) {
    o->x = nf(v[0]);
    o->y = nf(v[1]);
    o->z = nf(v[2]);
    o->s = nf(v[4]);
    o->t = nf(v[5]);
    o->q = nf(v[6]);
    o->rgba[0] = (u8)rgba;
    o->rgba[1] = (u8)(rgba >> 8);
    o->rgba[2] = (u8)(rgba >> 16);
    o->rgba[3] = (u8)(rgba >> 24);
    o->f = (u8)f;
    o->pad[0] = (u8)v[3];
    o->pad[1] = o->pad[2] = 0;
}

/* 2026-11-01 (native-plan.md stage 1, the GPU thread's recording): each strip vertex goes to the GPU's form once
 * (put / put0 into sv) and its triangles are copies of those (32 bytes each), where it was converted again for each of
 * the up to 3 triangles it is in.  The same vertices out, in the same order.  kh1_nat_once 0 (config.txt recfast=0,
 * host KH1_HOST_RECFAST=0) converts per triangle as before */
int kh1_nat_once = 1;
#define SV_MAX 512
static KH1GpuVert sv[SV_MAX];

u32 kh1_nat_tris(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, KH1GpuVert *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2], par = data[3];
        const u32 *v = data + 4;
        if (kh1_nat_once && nv <= SV_MAX) {
            u32 bad = 0; /* bit k of the last 3: vertex j - 2 + k's matrix index past the run's */
            for (j = 0; j < nv; j++) put(&sv[j], v + j * 8, rgba, f);
            for (j = 0; j < nv; j++) {
                bad = (bad >> 1) | (v[j * 8 + 3] >= nmat) << 2;
                if (j < 2 || bad) continue;
                if (n + 3 > max) { (*lost)++; continue; }
                if ((par + j) & 1) {
                    out[n] = sv[j - 2];
                    out[n + 1] = sv[j - 1];
                } else {
                    out[n] = sv[j - 1];
                    out[n + 1] = sv[j - 2];
                }
                out[n + 2] = sv[j];
                n += 3;
            }
            data += 4 + nv * 8;
            continue;
        }
        for (j = 2; j < nv; j++) {
            const u32 *a = v + (j - 2) * 8, *b = v + (j - 1) * 8, *c = v + j * 8;
            if (a[3] >= nmat || b[3] >= nmat || c[3] >= nmat) continue;
            if (n + 3 > max) { (*lost)++; continue; }
            if ((par + j) & 1) { /* odd: kept as it is when its area >= 0 */
                put(&out[n], a, rgba, f);
                put(&out[n + 1], b, rgba, f);
            } else { /* even: P18's operands swapped, so its mirror */
                put(&out[n], b, rgba, f);
                put(&out[n + 1], a, rgba, f);
            }
            put(&out[n + 2], c, rgba, f);
            n += 3;
        }
        data += 4 + nv * 8;
    }
    return n;
}

/* P0's vertex: (x, y, z, flags), (s, t, 1, rgba) */
static void put0(KH1GpuVert *o, const u32 *v, u32 f) {
    o->x = nf(v[0]);
    o->y = nf(v[1]);
    o->z = nf(v[2]);
    o->s = nf(v[4]);
    o->t = nf(v[5]);
    o->q = nf(v[6]);
    o->rgba[0] = (u8)v[7];
    o->rgba[1] = (u8)(v[7] >> 8);
    o->rgba[2] = (u8)(v[7] >> 16);
    o->rgba[3] = (u8)(v[7] >> 24);
    o->f = (u8)f;
    o->pad[0] = 0x80; /* matrix 0, z not clamped (shadergen.c: the GPU clips it at P0's near and far planes) */
    o->pad[1] = o->pad[2] = 0;
}
/* 2026-10-31: P0's records (natdraw.h): the triangle ending at vertex j is drawn when its flag word's low half is
 * not 0; with bit 0x20 (the Z sign flag of P0's cross product times the flag as a float) it is dropped when the
 * product is negative.  P0's product is -cross(p1 - p0, p2 - p0) in screen space (y down), so with a positive flag
 * the triangle is kept when that cross is <= 0 (listed with its first two vertices swapped, to the one winding rule
 * the cull mode keeps), with a negative flag when >= 0 (as it is).  Without 0x20 (0x02: only a zero product, a
 * triangle with no area, which draws nothing anyway) it is not culled.  culled 1 lists the first kind, 0 the
 * second */
u32 kh1_nat_tris0(const u32 *data, u32 nrec, u32 f, int culled, KH1GpuVert *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2];
        const u32 *v = data + 4;
        if (kh1_nat_once && nv <= SV_MAX) { /* each vertex converted once (kh1_nat_tris), only those a triangle uses */
            u32 done = 0; /* sv holds vertices 0 .. done - 1 */
            for (j = 2; j < nv; j++) {
                u32 fl = v[j * 8 + 3] & 0xFFFF;
                if (!fl || ((fl & 0x20) != 0) != (culled != 0)) continue;
                if (n + 3 > max) { (*lost)++; continue; }
                if (done < j - 2) done = j - 2;
                for (; done <= j; done++) put0(&sv[done], v + done * 8, f);
                if (culled && !(v[j * 8 + 3] >> 31)) {
                    out[n] = sv[j - 1];
                    out[n + 1] = sv[j - 2];
                } else {
                    out[n] = sv[j - 2];
                    out[n + 1] = sv[j - 1];
                }
                out[n + 2] = sv[j];
                n += 3;
            }
            data += 4 + nv * 8;
            continue;
        }
        for (j = 2; j < nv; j++) {
            const u32 *a = v + (j - 2) * 8, *b = v + (j - 1) * 8, *c = v + j * 8;
            u32 fl = c[3] & 0xFFFF;
            if (!fl || ((fl & 0x20) != 0) != (culled != 0)) continue;
            if (n + 3 > max) { (*lost)++; continue; }
            if (culled && !(c[3] >> 31)) {
                put0(&out[n], b, f);
                put0(&out[n + 1], a, f);
            } else {
                put0(&out[n], a, f);
                put0(&out[n + 1], b, f);
            }
            put0(&out[n + 2], c, f);
            n += 3;
        }
        data += 4 + nv * 8;
    }
    return n;
}

void kh1_nat_fold(const KH1RenderPass *p, u32 zbuf_lo, s32 xshift16, const u32 *mats, u32 nmat, f32 *out) {
    /* vertex.h's x: ((X - OFX + 8) / 16 + ox) x scale with X = 16 x gx (+ the shift), then x 2 / w - 1 */
    f32 ax = p->w ? 2.0f * p->scale / (f32)p->w : 0.0f, ay = p->h ? 2.0f * p->scale / (f32)p->h : 0.0f;
    f32 bx = ax * (((f32)(8 + xshift16 - p->ofx)) / 16.0f + p->ox) - 1.0f;
    f32 by = ay * (((f32)(8 - p->ofy)) / 16.0f + p->oy) - 1.0f;
    f32 kz = kh1_depth_f32(1, 0x30 | (zbuf_lo >> 24 & 15)); /* Z x 2^-bits */
    u32 i, k;
    for (i = 0; i < nmat; i++, mats += 16, out += 16) {
        f32 row[4][4];
        for (k = 0; k < 4; k++) { /* M's rows from its columns */
            row[0][k] = nf(mats[k * 4]);
            row[1][k] = nf(mats[k * 4 + 1]);
            row[2][k] = nf(mats[k * 4 + 2]);
            row[3][k] = nf(mats[k * 4 + 3]);
        }
        for (k = 0; k < 4; k++) {
            out[k] = ax * row[0][k] + bx * row[3][k];
            out[4 + k] = ay * row[1][k] + by * row[3][k];
            out[8 + k] = kz * row[2][k];
            out[12 + k] = row[3][k];
        }
    }
}

void kh1_nat_ref_xyz(const u32 *m, const f32 *pos, f32 out[3]) {
    f32 c[4];
    u32 k;
    for (k = 0; k < 4; k++) c[k] = nf(m[k]) * pos[0] + nf(m[4 + k]) * pos[1] + nf(m[8 + k]) * pos[2] + nf(m[12 + k]);
    out[0] = c[0] / c[3];
    out[1] = c[1] / c[3];
    out[2] = c[2] / c[3];
}
