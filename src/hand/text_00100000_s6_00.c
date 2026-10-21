#include "common.h"

/* ---- 00100c30.c ---- */
#include "data/types/text_00100000_s6_00.h"
typedef struct { f32 f0, f4, f8, fc; s32 i10, i14, i18; s32 pad; f32 f20, f24; } Cam0;
extern V4f D_0029B310[16];
extern V4f D_002A4060[16];
extern f32 D_0029B270;
extern Cam0 D_002BC0F0;
void func_00100c30(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        D_002A4060[i].a = D_0029B310[i].a * 6.103515625e-05f;
        D_002A4060[i].b = D_0029B310[i].b * 6.103515625e-05f;
        D_002A4060[i].c = D_0029B310[i].c * 6.103515625e-05f;
        D_002A4060[i].d = D_0029B310[i].d * 6.103515625e-05f;
    }
/*P*/
    D_0029B270 = 0.0005454153478331864f;
    D_002BC0F0.f24 = 20000.0f;
    D_002BC0F0.f20 = 15000.0f;
    D_002BC0F0.f0 = 30000.0f;
    D_002BC0F0.f4 = 20000.0f;
    D_002BC0F0.f8 = 64.0f;
    D_002BC0F0.fc = 255.0f;
    D_002BC0F0.i10 = 0x10;
    D_002BC0F0.i14 = 0x70;
    D_002BC0F0.i18 = 0x80;
/*Q*/
}

/* ---- 001012e0.c ---- */
typedef struct { s32 off; s32 size; } Ent;
typedef struct { s32 ver; s32 pad[3]; Ent e[10]; } Hdr;
extern s32 D_002A3F38;
extern s32 D_002A3F30, D_002A3F34, D_002A3F2C, D_002A3F48, D_002A3F28, D_002A3F3C, D_002A3F40;
s32 D_00494418 ALIGNED(8);
s32 D_0049441C ALIGNED(4);
extern s32 D_0029B410, D_0029B414, D_0029B418, D_0029B41C;
extern s32 D_002BCDBC, D_002BCDF0;
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"

void func_00105288(s32, s32);
void func_00108cf8(s32, s32, s32);
void func_00100768(void);
void func_001007b0(void);
void func_001763f0(s32);
void func_00105d88(s32);
s32 func_001137c8(s32, s32);
void func_00120748(char *, s32, void *, s32);
void func_001012b8(s32, s32, s32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void func_001012e0(s32 arg) {
    char tmp[16];
    char buf[64];
    Hdr *h;
    Ent *e;
    s32 ver;
    h = (Hdr *)D_002A3F38;
    e = &h->e[1];
    ver = h->ver;
    D_002A3F2C = (s32)h + h->e[0].off;
    D_002A3F30 = (s32)h + e->off;
    D_002A3F34 = e->size;
    e = &h->e[5];
    D_00494418 = (s32)h + h->e[2].off;
    D_0049441C = (s32)h + h->e[3].off;
    D_002A3F48 = (s32)h + h->e[4].off;
    func_00106ed0(D_002A3F30, D_002A3F34);
    func_00105288(D_002A3F2C, 1);
    func_00108cf8(D_00494418, 0, 4);
    func_00100768();
    func_00108cf8(D_0049441C, 1, 4);
    func_001007b0();
    D_0029B414 = D_0029B410 = 0;
    D_0029B418 = 0;
    D_0029B41C = 0;
    if (ver >= 6) {
        if (e->size != 0) {
            D_0029B410 = D_002A3F38 + e->off;
            func_001763f0(D_0029B410);
        }
        e = &h->e[6];
        if (e->size != 0) {
            D_0029B414 = D_002A3F38 + e->off;
        }
        e = &h->e[7];
        if (ver >= 8) {
            if (e->size != 0) {
                D_0029B418 = D_002A3F38 + e->off;
                func_001763f0(D_0029B418);
            }
            e = &h->e[8];
            if (e->size != 0) {
                D_0029B41C = D_002A3F38 + e->off;
            }
            e = &h->e[9];
        }
        if (ver >= 10) {
            if (e->size != 0) {
                D_002A3F28 = D_002A3F38 + e->off;
                func_00105d88(D_002A3F28);
            }
        }
    }
    D_002BCDF0 = D_002A3F38 + arg;
    if (D_002BCDBC == 0) {
        strcpy(buf, D_002BCCE0);
        strcat(buf, D_0048CC30);
        D_002A3F3C = D_002A3F38 + arg;
        D_002A3F3C = func_001137c8(D_002A3F3C, 128);
        func_00120748(buf, D_002A3F3C, func_001012b8, 0);
    } else {
        func_001012b8(D_002A3F40, 0, D_002A3F3C);
    }
}

/* ---- 00101a18.c ---- */
typedef struct { u8 pad0[4]; s32 w4; u8 pad8[8]; u64 q10; u64 q18; s32 arr[8]; u8 pad40[0x60]; } Tex;
typedef struct { s32 lo; s32 hi; } W2;
typedef union { u64 d; W2 w; } Q;
void func_00101a18(Tex *t, u8 k, Q *q) {
/*P*/
    q[0].d = t->q10;
    q[1].d = 0x50;
    q[2].w.lo = t->arr[k];
    q[2].w.hi = t->w4;
    q[3].d = 0x51;
    q[4].d = t->q18;
    q[5].d = 0x52;
    q[6].d = 2;
    q[7].d = 0x53;
/*Q*/
}

/* ---- 00101fc8.c ---- */
static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
void func_00101fc8(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x200080;
    p[7] = xyz(x + 8, y + 2);
}

/* ---- 00102070.c ---- */
void func_00102070(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x1000100;
    p[7] = xyz(x + 16, y + 16);
}

/* ---- 00104f10.c ---- */
/* VU0 */
typedef struct { u8 pad[8]; s16 n; u8 pada[10]; } Face;
#include "data/types/text_00100000_s6_00_p.h"
extern Face *D_002A6238;
#include "data/pieces/D_002A6250.h"
static inline void scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
void func_00104f10(s32 i, f32 *o) {
    s16 *p = &D_002A6250[D_002A6238[i].n].x;
    o[3] = 1.0f;
    o[0] = *p++;
    o[1] = *p++;
    o[2] = *p;
    scale(o, o, 0.0001220703125f);
}

/* ---- 00106e18.c ---- */
extern s32 D_002A6C50, D_002A6C54, D_002A6B84;
extern u8 D_002BC270[];

void iFlushCache(s32);
void func_00266f38(s32, void *);
s32 func_00106e18(void) {
    func_0011fbb0(0x3600, 2, 0, 0, 0, 128, D_002A6C50 << 7, D_002A6C50 << 12, D_002A6C54, D_002BC270);
    iFlushCache(0);
    func_00266f38(D_002A6B84, D_002BC270);
    return 2;
}

/* ---- 00107120.c ---- */
#define SWK(a, b) { s32 t_ = *(a); *(a) = *(b); *(b) = t_; }
#define SWV(a, b) { u64 t_ = *(u64 *)(a); *(u64 *)(a) = *(u64 *)(b); *(u64 *)(b) = t_; }
void func_00107120(s32 *k, u32 *v, s32 n, s32 w) {
    s32 *lk;
    u32 *lv;
    s32 *pk;
    u32 *pv;
    s32 cnt, i, m;
    pk = k + 1;
    pv = v + w;
    cnt = 0;
    if (n < 2) return;
    if (n == 2) {
        if (k[0] < k[1]) {
            SWK(k, pk);
            SWV(v, pv);
        }
        return;
    }
    m = n >> 1;
    SWK(k, k + m);
    SWV(v, v + m * w);
    lk = k;
    lv = v;
    for (i = 1; i < n; i++) {
        if (k[0] < *pk) {
            lk++;
            lv += w;
            cnt++;
            if (pk != lk) {
                SWK(pk, lk);
                SWV(pv, lv);
            }
        }
        pk++;
        pv += w;
    }
    if (lk != k) {
        SWK(k, lk);
        SWV(v, lv);
    }
    func_00107120(k, v, cnt, w);
    func_00107120(lk + 1, lv + w, n - cnt - 1, w);
}
#include "data/data_0029.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/pieces/D_0029B310.h"
