#include "common.h"
typedef struct { s32 w0, w4, w8, w12; } Ent16;
typedef struct { s32 pad[2]; s32 a[16]; s32 b[16]; s32 pad2[2]; } M144;
typedef struct { f32 x, y, z; } V3;
extern s32 D_00351BD0;
extern M144 D_002B5260[];
extern M144 D_002B2E60[];
extern s32 D_00482260[];
extern s32 D_0047E220[];
extern s32 D_0048BFD0[2];
extern s32 D_0029B280[4][4];
extern s32 D_002BC170[4][4];
extern V3 D_00494C00[];
extern s32 D_004862D0[2];
extern s32 *D_002A3F30;
extern s32 D_00494BB0;
extern Ent16 *D_00494BA8;
extern s32 D_0047A1D0[2];

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
    tbl = (Ent16 *)(D_002A3F30[1] + (s32)D_002A3F30);
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
    tbl = (Ent16 *)(D_002A3F30[1] + (s32)D_002A3F30);
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

extern void func_00100670(u32, s32);
extern void func_001085e8(s32, s32);
extern void func_00108180(s32);
extern s32 D_0029B2F4;
extern s32 D_0029B2FC;
typedef struct { u8 b[64]; } B64;
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

extern s32 FlushCache(s32);
extern s32 sceGsExecLoadImage(void *, void *);
extern s32 sceGsSyncPath(s32, s32);
extern void sceGsSetDefLoadImage(void *, s16, s16, s16, s16, s16, s16, s16);
extern u8 D_002BC1B0[];

s32 func_001090e8(void *src, s32 w, s32 h, s32 dbp) {
    sceGsSetDefLoadImage(D_002BC1B0, dbp, w / 64, 20, 0, 0, w, h);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    return sceGsExecLoadImage(D_002BC1B0, src);
}

extern volatile s32 D_002BBE08;
extern s32 D_002BBD40;
extern volatile s32 D_002BBDE0;
extern volatile s32 D_00495164;
extern volatile s32 D_00495160;
extern f32 D_002BBE00;
extern s32 D_002BC128, D_002BC12C, D_002BC130, D_002BC134;
extern s32 D_003F34A4;
extern u8 D_009A0000[];
extern void func_00111000(void);
extern void func_0010fe80(void);
extern void func_00109268(void);
extern void func_0010c240(void);
extern void func_00120aa0(void);
extern void func_0011edc8(void);
extern void func_0011c9c0(void);
extern void func_00110458(void);
extern void func_001103a0(void);
extern void func_00100278(void);
extern void func_001117e0(void);
extern void func_001759a8(void);
extern void func_001ee520(void);
extern void func_001c0750(void);
extern void func_001ba798(void);
extern void func_00236f00(void);
extern void func_0010fc38(void);
extern void func_0010c3c0(void);
extern void func_0011cb80(void *);
extern void func_0011cd20(s32, void *, s32);
extern void func_0010fc98(void);
extern void func_001ef950(void);
extern void func_001559f0(s32, s32);
extern void func_001104e0(void);
extern void func_00105f28(void);
extern void func_0010ff60(s32);

void func_00109388(void) {
    D_002BBE08 = 1;
    D_002BBD40 = 0;
    func_00111000();
    func_0010fe80();
    func_00109268();
    func_0010c240();
    func_00120aa0();
    func_0011edc8();
    D_00495164 = D_002BBDE0 = 0;
    D_00495160 = 0;
    D_002BBE00 = 1.0f;
    D_002BC128 = 0;
    D_002BC12C = 0;
    D_002BC130 = 0;
    D_002BC134 = 0;
    func_0011c9c0();
    func_00110458();
    func_001103a0();
    func_00100278();
    func_001117e0();
    func_001759a8();
    func_001ee520();
    D_003F34A4 = 0;
    func_001c0750();
    func_001ba798();
    func_00236f00();
    func_0010fc38();
    func_0010c3c0();
    func_0011cb80(D_009A0000);
    func_0011cd20(2, D_009A0000, 0);
    func_0010fc98();
    func_001ef950();
    func_001559f0(0, 64);
    func_001104e0();
    func_00105f28();
    func_0010ff60(0);
}

extern void func_00109f88(void);
extern s32 func_00106b18(void *);
extern u64 D_002B6668;
extern u8 D_002B66B0[];
extern void func_00106b18_v(void *) __asm__("func_00106b18");
static inline void inl_a378(void *p, u64 c) {
    D_002B6668 = c;
    func_00106b18_v(p);
}
s32 func_0010a378(void) {
    func_00109f88();
    inl_a378(D_002B66B0, 0x180808080ULL);
    return 0;
}

/* func_0010b6c0 needs func_0010a5d0 and func_0010b2d0 defined above (CONTEXT_ONLY copies). */
typedef struct {
    s32 id;
    s16 pad4;
    u16 f6;
    u16 anim;
    u16 kind;
    u8 padc[0x10];
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[8];
    f32 f50, f54;
} Win;
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef struct { u8 pad[0x1c]; f32 ry; } Rot;
extern Mtx D_00495190, D_00495210;
extern u8 D_004951D0[];
extern s32 D_002BBE18;
extern u8 D_002B73B0[], D_002B73E0[], D_002B7490[], D_002B7450[], D_002B74C0[];
extern u8 D_002B67D0[], D_002B67E0[];
extern void *D_00495250;
extern void func_0010b208(void *, void *, void *);
extern s32 func_00121e28(s32, s32 *);
extern void func_0010b190(Win *);
extern void func_0010b270(void *, Win *);
extern void func_0010a780(Win *, void *, s32, s32, s32);
extern void func_00121eb0(s32);
extern void func_0010b390(Win *, f32 *);
extern s32 func_00122048(s32, s32);
extern void func_00106b58(s32);
extern void func_001220b8(s32);

typedef int u128 __attribute__((mode(TI)));
extern u64 D_002B70B0[];
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6);
extern u8 D_002B71D0[], D_002B7210[], D_002B7250[], D_002B7290[], D_002B72D0[], D_002B7310[], D_002B7350[];
CONTEXT_ONLY void func_0010a5d0(s32 a0, u8 *p, s32 n, s32 mode, s32 sub) {
    s32 loc[2];
    u64 *q;
    *(u128 *)p = 0;
    *(s32 *)p = 0x7000000e;
    q = (u64 *)(p + 16);
    q[0] = ((u64)n << 47) | 0xd000400000008001ULL;
    q[1] = 0x4124124124128ULL;
    loc[0] = 0;
    loc[1] = 0;
    switch (mode) {
    case 0:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7210, 23, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B72D0, 26, (s32)D_002B71D0); break;
        }
        break;
    case 1:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7250, 22, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7310, 25, (s32)D_002B71D0); break;
        }
        break;
    case 2:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7290, 24, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7350, 27, (s32)D_002B71D0); break;
        }
        break;
    }
}


extern u8 D_002BCAF0[];
extern void func_00267578(Mtx, Mtx, void *);
extern void func_002676c0(Mtx, void *, f32);
extern void sceVu0MulMatrix(Mtx, Mtx, Mtx);
CONTEXT_ONLY void func_0010b2d0(Mtx out, Rot *r, void *t) {
    Mtx m;
    f32 a = r->ry;
    if (a > 180.0f) {
        a -= 180.0f;
    } else {
        a += -180.0f;
    }
    func_002676c0(m, D_002BCAF0, a / 180.0f * 3.1415928f);
    func_00267578(m, m, t);
    sceVu0MulMatrix(m, D_00495190, m);
    sceVu0MulMatrix(out, D_00495210, m);
}
void func_0010b6c0(Win *w) {
    u8 m[64] __attribute__((aligned(16)));
    f32 v[4];
    s32 p;
    s32 h = 0;
    f32 k;

    func_0010b208(D_00495190, D_004951D0, &w->f50);
    if (D_002BBE18 == 0) {
        func_00106b18(D_002B73B0);
    } else {
        func_00106b18(D_002B73E0);
    }
    switch (w->kind) {
    case 0:
        break;
    case 1:
        func_00106b18(D_002B7490);
        p = func_00121e28((s32)((w->w + 2.0f) * (w->h + 2.0f) * 13.0f + 2.0f) << 4, &p);
        D_00495250 = D_002B67D0;
        func_0010b190(w);
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 1);
        func_00106b18((void *)p);
        func_00121eb0(p);
        break;
    default:
        k = 3.0f;
        func_00106b18(D_002B7450);
        w->x += w->f50 * k;
        w->y += w->f54 * k;
        D_00495250 = D_002B67E0;
        func_0010b190(w);
        func_0010b390(w, v);
        if (w->f6) {
            h = func_00122048(240, 128);
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 0, w->f6);
            func_00106b58(h);
        }
        p = func_00121e28((s32)((w->w + 2.0f) * (w->h + 2.0f) * 13.0f + 2.0f) << 4, &p);
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 0);
        func_00106b18((void *)p);
        func_00106b18(D_002B7490);
        w->x -= w->f50 * k;
        w->y -= w->f54 * k;
        D_00495250 = D_002B67D0;
        func_0010b190(w);
        if (w->f6 && (u16)(w->anim - 5) < 10) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 0, w->f6);
            func_00106b58(h);
        }
        if (w->f6 && !((u16)(w->anim - 5) < 10)) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 1, w->f6);
            func_00106b58(h);
        }
        func_0010b270(m, w);
        func_0010a780(w, m, p, 84, 1);
        func_00106b18((void *)p);
        if (w->f6) {
            func_0010b2d0((void *)m, (Rot *)w, v);
            func_0010a5d0((s32)m, (u8 *)h, 84, 2, w->f6);
            func_00106b58(h);
        }
        func_00121eb0(p);
        if (w->f6) {
            func_001220b8(h);
        }
        break;
    }
    func_00106b18(D_002B74C0);
}

