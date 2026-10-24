/* A 1024-cell grid surface (grideff.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s11_w45.h"
#include "data/types/nostrict_text_00100000_s6_01_p2.h"
#include "data/types/nostrict_text_00100000_s6_01.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F30.h"
#include "data/types/nostrict_text_00100000_s6_01_p.h"

/* func_00107c48 (from hand/nostrict/text_00100000_s11_w45.c). */
typedef struct { s32 a, b; } P8;
extern s32 D_00351BD0;
extern Ent16 *D_00494BA8;
extern Ent16 D_00482290[];
extern Ent16 D_0047E250[];
extern s32 D_0047A1D0[2];
extern P8 D_0047A1D0_00107c48 __asm__("D_0047A1D0");
#define D_0047A1D0 D_0047A1D0_00107c48
s32 func_00107c48(s32 i) {
    Ent16 *arg;
    Ent16 *base;
    Ent16 *dst;
    u32 tbl;
    Ent16 *q;
    s32 *p;
    s32 *r;
    s32 n;
    u8 buf[64];

    arg = (Ent16 *)i;
    /* FLAGGED dead FP test (s11w45): `(f32)(s32)&D_00351BD0 < 0.0f` builds the address from the shared %hi
     * (lo_sum takes v0) while the hi stays live for the D_00351BD0 load in the next block, so global-alloc gives the hi v1; the then-arm before the else is the
     * explicit jump that keeps the test alive through both allocators (flow2 deletes it). i is reset to 0 below. */
    if ((f32)(s32)&D_00351BD0 < 0.0f) i = 0;
    /* FLAGGED dead set (s11w34): both sets die (i = 0 and n = 0 follow); the test keeps i live past the copy until combine */
    else if (i != 0) { i = 0; n = 0; }
    if (D_00351BD0 != 0) {
        base = D_00482290;
    } else {
        base = D_0047E250;
    }
    i = 0;
    tbl = arg->w4 + (s32)arg;
    n = 0;
    for (; i < D_00494BB0; ) {
        arg = (Ent16 *)(i << 4);
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)arg);
        i++;
        if (*p != 0) {
            q = (Ent16 *)((u32)(i * 16) + tbl);
            r = &q->w8;
            if (*r != 0) {
                *p = 3;
                base[n].w0 = *r; base[n].w4 = q->w12; n++;
            }
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
#undef D_0047A1D0

/* func_001081c8 (from hand/nostrict/text_00100000_s6_01.c). */
extern M144 D_002B5260[];
extern M144 D_002B2E60[];
extern s32 D_00482260[];
extern s32 D_0047E220[];
extern s32 D_0048BFD0[2];
extern s32 D_002BC170[4][4];
extern V3 D_00494C00[];
extern s32 D_004862D0[2];
s32 *func_001081c8(s32 *p, s32 k) {
    M144 *m;
    s32 *t;
    s32 i, j, c, mask;
    Ent16 *tbl;
    Ent16 *q;
    f32 f;
    s32 *r;
    Ent16 *e;
    if (D_00351BD0 != 0) {
        m = &D_002B5260[k];
        t = D_00482260;
    } else {
        m = &D_002B2E60[k];
        t = D_0047E220;
    }
    m->pad[0] = D_0048BFD0[0];
    m->pad[1] = D_0048BFD0[1];
    c = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m->a[c] = D_0029B280[i][j];
            m->b[c] = D_002BC170[i][j];
            c++;
        }
    }
    { f32 tmp[4]; tmp[3] = D_00494C00[k].y; m->b[11] = *(s32 *)&tmp[3]; }
    mask = 1;
    mask <<= k;
    *p++ = t[0];
    *p = (s32)m;
    p += 3;
    *p++ = t[4];
    *p = t[5];
    p += 3;
    *p++ = D_004862D0[0];
    *p = D_004862D0[1];
    r = p + 3;
    tbl = (Ent16 *)(((s32 *)D_002A3F30)[1] + (s32)D_002A3F30);
    for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        e = &D_00494BA8[i];
        if ((mask & e->w8) && (q = (Ent16 *)((u32)(j * 16) + (u32)tbl))->w8 != 0) {
            *r++ = q->w8;
            *r = q->w12;
            r += 3;
        }
    }
    *r++ = D_0047A1D0[0];
    *r = D_0047A1D0[1];
    r += 3;
    return r;

}

/* func_001083d8 (from hand/nostrict/text_00100000_s6_01.c). */
s32 *func_001083d8(s32 *p, s32 k) {
    M144 *m;
    s32 *t;
    s32 i, j, c, mask;
    Ent16 *tbl;
    Ent16 *q;
    f32 f;
    s32 *r;
    Ent16 *e;
    if (D_00351BD0 != 0) {
        m = &D_002B5260[k];
        t = D_00482260;
    } else {
        m = &D_002B2E60[k];
        t = D_0047E220;
    }
    m->pad[0] = D_0048BFD0[0];
    m->pad[1] = D_0048BFD0[1];
    c = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m->a[c] = D_0029B280[i][j];
            m->b[c] = D_002BC170[i][j];
            c++;
        }
    }
    { f32 tmp[4]; tmp[3] = D_00494C00[k].y; m->b[11] = *(s32 *)&tmp[3]; }
    mask = 1;
    mask <<= k;
    *p++ = t[0];
    *p = (s32)m;
    p += 3;
    *p++ = t[4];
    *p = t[5];
    p += 3;
    *p++ = D_004862D0[0];
    *p = D_004862D0[1];
    r = p + 3;
    tbl = (Ent16 *)(((s32 *)D_002A3F30)[1] + (s32)D_002A3F30);
    for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        e = &D_00494BA8[i];
        if ((mask & e->w8) && (q = (Ent16 *)((u32)(j * 16) + (u32)tbl))->w0 != 0) {
            *r++ = q->w0;
            *r = q->w4;
            r += 3;
        }
    }
    *r++ = D_0047A1D0[0];
    *r = D_0047A1D0[1];
    r += 3;
    return r;

}

/* func_00108708 (from hand/nostrict/text_00100000_s6_01.c). */
extern void func_00100670(u32, s32);
extern void func_001085e8(s32, s32);
extern void func_00108180(s32);
extern s32 D_0029B2F4;
extern s32 D_0029B2FC;
extern B64 D_0047A250[];
extern B64 D_004721D0[];
extern B64 D_00476210[];
extern B64 D_0046E190[];
extern f32 D_002BBDFC;
void func_00108708(void) {
    s32 *p;
    s32 *np;
    s32 i;

    if (D_00351BD0 != 0) {
        if (D_0029B2F4 > D_0029B2FC) {
            p = (s32 *)&D_0047A250[D_0029B2FC];
        } else {
            p = (s32 *)&D_004721D0[D_0029B2F4];
        }
    } else {
        if (D_0029B2F4 > D_0029B2FC) {
            p = (s32 *)&D_00476210[D_0029B2FC];
        } else {
            p = (s32 *)&D_0046E190[D_0029B2F4];
        }
    }
    for (i = 0; i < 32; i++) {
        if (D_00494C00[i].x != 0.0f) {
            np = func_001083d8(p, i);
            func_00100670(7, 50000);
            func_001085e8(50000, (s32)p);
            p = np;
            np = func_001081c8(p, i);
            func_00100670(3, 50000);
            func_001085e8(50000, (s32)p);
            p = np;
            D_00494C00[i].x -= D_002BBDFC;
            if (D_00494C00[i].z < 0.0f) {
                D_00494C00[i].y = fabsf(D_00494C00[i].x * D_00494C00[i].z);
            } else {
                D_00494C00[i].y = 1.0f - D_00494C00[i].x * D_00494C00[i].z;
            }
            if (D_00494C00[i].x <= 0.0f) {
                D_00494C00[i].x = 0.0f;
                if (!(D_00494C00[i].z < 0.0f)) {
                    func_00108180(i);
                }
            }
        }
    }
}

