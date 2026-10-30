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

u32 kh1_nat_tris(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, KH1GpuVert *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2], par = data[3];
        const u32 *v = data + 4;
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
