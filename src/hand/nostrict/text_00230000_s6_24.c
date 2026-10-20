#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0065.h"

/* ---- h_ok.c */
typedef int u128 __attribute__((mode(TI)));
void func_00237018(u128 *, s32, s32);

void func_00238768(u128 *src, s32 n, u128 *buf) {
    s32 k = 2;
    u64 *e;
    s32 i;
    u64 t;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 24;
        ((u64 *)d)[0] = 0;
        ((u64 *)d)[1] = 63;
        d[1] = src[i * 14 + 0];
        d[2] = src[i * 14 + 1];
        d[3] = src[i * 14 + 2];
        d[4] = src[i * 14 + 6];
        d[5] = src[i * 14 + 10];
        d[6] = src[i * 14 + 3];
        d[7] = src[i * 14 + 7];
        d[8] = src[i * 14 + 11];
        d[9] = src[i * 14 + 4];
        d[10] = src[i * 14 + 8];
        d[11] = src[i * 14 + 12];
        e = (u64 *)&d[12];
        e[0] = 0;
        e[1] = 63;
        d[13] = src[i * 14 + 0];
        d[14] = src[i * 14 + 1];
        d[15] = src[i * 14 + 4];
        d[16] = src[i * 14 + 8];
        d[17] = src[i * 14 + 12];
        d[18] = src[i * 14 + 3];
        d[19] = src[i * 14 + 7];
        d[20] = src[i * 14 + 11];
        d[21] = src[i * 14 + 5];
        d[22] = src[i * 14 + 9];
        d[23] = src[i * 14 + 13];
    }
    buf[1] = 0;
    t = (n * 2) | 0x8000;
    t |= (u64)0xC0ADC000 << 32;
    ((u64 *)&buf[1])[0] = t;
    ((u64 *)&buf[1])[1] = 0x413413413EEE;
    func_00237018(buf, k, 1);
}

/* ---- f399.c */
void func_0024ae00(void *);
void func_0024af00(void *);
void func_00239860(void *, void *, s32, s32, f32, s32, void *, s32);
void func_002399f0(s32 a0, void *a1, void *a2, s32 dx, s32 dy, s32 *src, f32 s) {
    if (a0) func_0024ae00(a1);
    func_0024af00(a1);
    func_00239860(a1, a2, dx, dy, s, 1, src, 1);
}

/* ---- q7.c */
typedef struct { u64 b[24]; } Spr570;
typedef struct { u8 pad[0x40]; Spr570 s0; Spr570 s1; s32 x1c0; u8 pad1c4[0x1d0 - 0x1c4]; } Ob570;
typedef struct { s32 cur; s32 t[6]; u8 rest[132 - 28]; } St570;
extern Ob570 D_00650120[];
extern Ob570 D_00650C00;
extern St570 D_00449908;
extern u8 D_004409A0[], D_00443180[], D_004419B0[], D_00444A70[], D_00446240[], D_004478F0[], D_00448FA0[], D_00449530[];
extern u8 D_004497A0[], D_004497D0[], D_00449818[], D_00449860[], D_004498A8[], D_004498E8[];
extern u8 D_00426790[], D_004267C0[], D_004267F0[];
/* Sprite and packet work buffers of the six menu objects func_0023b570 builds (phase 4:
 * defined here because nothing else uses them; sizes are the distance to the next known
 * object, docs/shiftable-plan.md "Phase 4"). Qword-aligned: they hold DMA/GIF packets. */
u8 D_006489E0[0x240] ALIGNED(16);
u8 D_00648C20[0xc0] ALIGNED(16);
u8 D_00648CE0[0xc0] ALIGNED(16);
u8 D_00648DA0[0xc0] ALIGNED(16);
u8 D_00648E60[0xc0] ALIGNED(16);
u8 D_00648F20[0x300] ALIGNED(16);
u8 D_00649220[0x240] ALIGNED(16);
u8 D_00649460[0x540] ALIGNED(16);
u8 D_006499A0[0x540] ALIGNED(16);
u8 D_00649EE0[0xc0] ALIGNED(16);
u8 D_00649FA0[0xc0] ALIGNED(16);
u8 D_0064A060[0xc0] ALIGNED(16);
u8 D_0064A120[0xc0] ALIGNED(16);
u8 D_0064A1E0[0xc0] ALIGNED(16);
u8 D_0064A2A0[0xc0] ALIGNED(16);
u8 D_0064A360[0x300] ALIGNED(16);
u8 D_0064A660[0x300] ALIGNED(16);
u8 D_0064A960[0x180] ALIGNED(16);
u8 D_0064AAE0[0x540] ALIGNED(16);
u8 D_0064B020[0x540] ALIGNED(16);
u8 D_0064B560[0xc0] ALIGNED(16);
u8 D_0064B620[0xc0] ALIGNED(16);
u8 D_0064B6E0[0xc0] ALIGNED(16);
u8 D_0064B7A0[0xc0] ALIGNED(16);
u8 D_0064B860[0xc0] ALIGNED(16);
u8 D_0064B920[0xc0] ALIGNED(16);
u8 D_0064B9E0[0x300] ALIGNED(16);
u8 D_0064BCE0[0x300] ALIGNED(16);
u8 D_0064BFE0[0xc0] ALIGNED(16);
u8 D_0064C0A0[0x480] ALIGNED(16);
u8 D_0064C520[0x480] ALIGNED(16);
u8 D_0064C9A0[0xc0] ALIGNED(16);
u8 D_0064CA60[0xc0] ALIGNED(16);
u8 D_0064CB20[0xc0] ALIGNED(16);
u8 D_0064CBE0[0xc0] ALIGNED(16);
u8 D_0064CCA0[0xc0] ALIGNED(16);
u8 D_0064CD60[0xc0] ALIGNED(16);
u8 D_0064CE20[0x300] ALIGNED(16);
u8 D_0064D120[0x300] ALIGNED(16);
u8 D_0064D420[0xc0] ALIGNED(16);
u8 D_0064D4E0[0x480] ALIGNED(16);
u8 D_0064D960[0x480] ALIGNED(16);
u8 D_0064DDE0[0xc0] ALIGNED(16);
u8 D_0064DEA0[0xc0] ALIGNED(16);
u8 D_0064DF60[0xc0] ALIGNED(16);
u8 D_0064E020[0xc0] ALIGNED(16);
u8 D_0064E0E0[0xc0] ALIGNED(16);
u8 D_0064E1A0[0xc0] ALIGNED(16);
u8 D_0064E260[0x300] ALIGNED(16);
u8 D_0064E560[0x300] ALIGNED(16);
u8 D_0064E860[0xc0] ALIGNED(16);
u8 D_0064E920[0x480] ALIGNED(16);
u8 D_0064EDA0[0x480] ALIGNED(16);
u8 D_0064F220[0xc0] ALIGNED(16);
u8 D_0064F2E0[0xc0] ALIGNED(16);
u8 D_0064F3A0[0xc0] ALIGNED(16);
u8 D_0064F460[0xc0] ALIGNED(16);
u8 D_0064F520[0xc0] ALIGNED(16);
u8 D_0064F5E0[0xc0] ALIGNED(16);
u8 D_0064F6A0[0x300] ALIGNED(16);
u8 D_0064F9A0[0x300] ALIGNED(16);
u8 D_0064FCA0[0xc0] ALIGNED(16);
extern u8 D_0064FD60[];
void *memset(void *, s32, u32);
void func_0023b4b8(s32);
void func_0024aac8(void *);
void func_0023aed0(s32, Ob570 *, void *, void *, void *, void *, void *, void *, s32, void *, void *, void *, void *, void *, void *, void *, void *, void *);
void func_0024af40(void *, void *, void *);
s32 func_0023a968(void);
s32 func_0011ef38(s32 (*)(void));
void func_0011ef10(s32, s32 (*)(void));

typedef struct { s32 a, b, off; } Hdr570;
#define RES(d) ((u8 *)(d) + ((Hdr570 *)(d))->off)

void func_0023b570(void) {
    s32 i;
    Spr570 *sp;
    Hdr570 *h;
    u8 *p;
    memset(D_00650120, 0, 2784);
    memset(&D_00449908, 0, 132);
    D_00449908.cur = -1;
    for (i = 0; i < 6; i++) D_00449908.t[i] = -1;
    func_0023b4b8(3);
    func_0024aac8(D_004409A0);
    func_0024aac8(D_00443180);
    func_0024aac8(D_004419B0);
    func_0024aac8(D_00444A70);
    func_0024aac8(D_00446240);
    func_0024aac8(D_004478F0);
    func_0024aac8(D_00448FA0);
    func_0024aac8(D_00449530);
    h = (Hdr570 *)D_004409A0; p = (u8 *)h + h->off;
    func_0023aed0(0, &D_00650120[0], D_004497A0, p, D_00426790, D_004267F0, D_00648CE0, D_00648DA0, 3,
                  D_006489E0, D_00648C20, D_00648E60, D_00648F20, D_00649220, 0, 0, 0, 0);
    sp = (Spr570 *)RES(D_00449530);
    D_00650120[0].s0 = sp[0];
    D_00650120[0].s1 = sp[1];
    D_00650120[0].x1c0 = 0;
    h = (Hdr570 *)D_00443180; p = (u8 *)h + h->off;
    func_0023aed0(1, &D_00650120[1], D_004497D0, p, D_004267C0, D_004267F0, D_0064A060, D_0064A1E0, 7,
                  D_00649460, D_00649EE0, D_0064A2A0, D_0064A360, D_0064A960, D_0064A120, D_006499A0, D_00649FA0, D_0064A660);
    h = (Hdr570 *)D_004419B0; p = (u8 *)h + h->off;
    func_0023aed0(2, &D_00650120[2], D_00449818, p, D_004267C0, D_004267F0, D_0064B6E0, D_0064B860, 7,
                  D_0064AAE0, D_0064B560, D_0064B920, D_0064B9E0, D_0064BFE0, D_0064B7A0, D_0064B020, D_0064B620, D_0064BCE0);
    h = (Hdr570 *)D_00444A70; p = (u8 *)h + h->off;
    func_0023aed0(3, &D_00650120[3], D_00449860, p, D_004267C0, D_004267F0, D_0064CB20, D_0064CCA0, 6,
                  D_0064C0A0, D_0064C9A0, D_0064CD60, D_0064CE20, D_0064D420, D_0064CBE0, D_0064C520, D_0064CA60, D_0064D120);
    h = (Hdr570 *)D_00446240; p = (u8 *)h + h->off;
    func_0023aed0(4, &D_00650120[4], D_004498A8, p, D_004267C0, D_004267F0, D_0064DF60, D_0064E0E0, 6,
                  D_0064D4E0, D_0064DDE0, D_0064E1A0, D_0064E260, D_0064E860, D_0064E020, D_0064D960, D_0064DEA0, D_0064E560);
    h = (Hdr570 *)D_004478F0; p = (u8 *)h + h->off;
    func_0023aed0(4, &D_00650C00, D_004498A8, p, D_004267C0, D_004267F0, D_0064F3A0, D_0064F520, 6,
                  D_0064E920, D_0064F220, D_0064F5E0, D_0064F6A0, D_0064FCA0, D_0064F460, D_0064EDA0, D_0064F2E0, D_0064F9A0);
    func_0024af40(D_004498E8, D_0064FD60, D_00448FA0);
    if (func_0011ef38(func_0023a968) == 0) func_0011ef10(0x29811, func_0023a968);
}

/* ---- p_ok2.c */

typedef struct { u8 b[192]; } Spr17;
typedef struct {
    void *x0; void *x4; u8 pad8[4]; void *xc; void *x10;
    Spr17 *x14; void *x18; void *x1c; Spr17 *x20; Spr17 *x24;
    Spr17 *x28; Spr17 *x2c; void *x30; Spr17 *x34;
    u8 pad38[0x1c0 - 0x38]; void *x1c0;
} Ob17;
typedef struct { s32 x0; s32 x4; s32 x8; s32 cur; s32 n; u8 id[16]; u8 col[16]; } Mn17;
typedef struct { s32 c[4]; } __attribute__((aligned(16))) Col;
typedef struct { s32 c[4][4]; } __attribute__((aligned(16))) Col4;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
extern s32 D_00449900;
/* D_00449908: St570 above */
extern Col D_004914C0;
extern Col D_004914D0;
extern Col4 D_004914E0;
void func_00239778(s32 a, void *b, void *c, void *d, s32 e, s32 g, f32 h);
void func_00239a80(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h);
void func_00239d20(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h);
void func_002399f0(s32, void *, void *, s32, s32, s32 *, f32);
void func_0024ac08(void *, s32 *);
void func_0024ac68(void *, s32 *);
void func_00239558(s32, s32, s32, s32);

void func_0024ae00(void *);
void func_0024af00(void *);
void func_00239860(void *, void *, s32, s32, f32, s32, void *, s32);
CONTEXT_ONLY void func_00239a80(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h) {
    if (a) {
        func_0024ae00(b);
        if (c) func_0024ae00(c);
    }
    func_0024af00(b);
    if (c) func_0024af00(c);
    func_00239860(b, d, e, g, h, 0, col, 0);
    if (c) func_00239860(b, d, e, g, h, 0, col, 0);
}
void func_0023bb98(s32 mode, Mn17 *m, s32 big, s32 on, Ob17 *o, s32 x, s32 y, f32 f) {
    s32 pos[4];
    Col c0 = D_004914C0;
    Col c1 = D_004914D0;
    Col4 c2 = D_004914E0;
    s32 buf[16];
    f32 s;
    s32 i, yy, xx, on2;
    Spr17 *sel;
    xx = x;
    yy = y;
    D_00650DD4 = f;
    D_00650DD0 = f;
    s = 1.0f;
    if (big == 0) s = 0.5f;
    func_00239a80(on, o->xc, o->x28, o->x0, xx, yy, &c0, s);
    if (mode == 0) {
        func_0024ac68(o->x1c0, buf);
        func_002399f0(on, o->x10, o->x4, xx, yy, buf, s);
    } else {
        func_00239a80(on, o->x10, 0, o->x4, xx, yy, &c0, s);
    }
    yy = y + 20;
    for (i = 0; i < m->n - 1; yy += 22, i++) {
        if (m->cur == i) continue;
        if (o->x2c) func_00239a80(on, &o->x14[i], &o->x2c[i], o->x0, x, yy, &c0, s);
        else func_00239a80(on, &o->x14[i], 0, o->x0, x, yy, &c0, s);
        func_0024ac08(&o->x14[i], pos);
        func_00239558(m->id[i], x + pos[0], yy + pos[1], m->col[i]);
        if (D_00449900 && i == m->cur + 1)
            func_00239a80(on, o->x1c, 0, o->x0, x + pos[0], yy + pos[1] - 22, &c0, s);
    }
    if (m->cur != m->n - 1) {
        func_00239a80(on, o->x18, o->x30, o->x0, x, yy, &c0, s);
        func_0024ac08(o->x18, pos);
        func_00239558(m->id[i], x + pos[0], yy + pos[1], m->col[i]);
        if (D_00449900 && i == m->cur + 1)
            func_00239a80(on, o->x1c, 0, o->x0, x + pos[0], yy + pos[1] - 22, &c0, s);
    }
    if (big) {
        xx = x + 11;
        on2 = m->cur != D_00449908.t[mode];
        yy = y + m->cur * 22;
        yy += 18;
        sel = 0;
        for (i = 0; i < 4; i++) {
            if (i == 2) func_00239d20(on2, &o->x20[2], 0, o->x0, xx, yy, &c2, s);
            else if (i == 1) func_00239a80(on2, &o->x20[1], 0, o->x0, xx, yy, &c1, s);
            else if (o->x34) func_00239778(on2, &o->x20[i], &o->x34[i], o->x0, xx, yy, s);
            else func_00239778(on2, &o->x20[i], 0, o->x0, xx, yy, s);
        }
        switch (mode) {
        case 0:
            if (m->id[m->cur] == 1) sel = &o->x24[0];
            else if (m->id[m->cur] == 2) sel = &o->x24[1];
            else if (m->id[m->cur] == 3) sel = &o->x24[2];
            break;
        case 1:
            if (m->id[m->cur] == 6) sel = &o->x24[1];
            else sel = &o->x24[0];
            break;
        case 2:
        case 3:
            sel = &o->x24[0];
            break;
        }
        if (sel) func_00239778(on2, sel, 0, o->x4, xx, yy, s);
        func_0024ac08(&o->x20[1], pos);
        func_00239558(m->id[m->cur], xx + pos[0], yy + pos[1] + 2, m->col[m->cur]);
        D_00449908.t[mode] = m->cur;
    }
}

/* ---- hc4.c */
typedef struct { u64 d[24]; } B192;
typedef struct { s32 a, b; } P8;
typedef struct { s32 used, x4, x8, pad; B192 blk; s32 xd0, xd4; P8 xd8; } Slot;
extern Slot D_00651310[10];
extern B192 *D_00651300;
Slot *func_0023c228(void);

/* ---- c3.c */
s32 func_0023c4d8(P8 *a0, s32 a1, s32 a2, s32 a3) {
    Slot *e = func_0023c228();
    if (e == 0) return -1; { B192 *s = D_00651300; e->x8 = a1; e->blk = *s; } e->xd0 = a2; e->xd4 = a3; e->xd8 = *a0;
    return e - D_00651310;
}

/* ---- e4_3.c */
typedef struct { s32 x, y, z, w; } I4b;
I4b *func_0023d208(s32 *, s32 *, f32, I4b *);
#define D208(a,b,c,f) func_0023d208(a,b,f,c)
s32 func_0023d1e0(f32);

I4b *func_0023e160(s32 *c, s32 *r, s32 *col, I4b *d, f32 a0, f32 a1, f32 al) {
    I4b *h;
    I4b *e;
    s32 i, n, m;
    ((u64 *)d)[0] = 0x1000000000008001ULL;
    ((u64 *)d)[1] = 1;
    d++;
    d->x = col[0];
    d->y = col[1];
    d->z = col[2];
    d->w = (u32)(col[3] * al);
    d++;
    h = d;
    d++;
    d->x = r[0];
    d->y = r[1];
    d->z = 0;
    d->w = 0;
    d = h + 2;
    d->x = c[0];
    d->y = c[1];
    d->z = 0;
    d->w = 0;
    d = D208(c, r, h + 3, a0);
    i = func_0023d1e0(a0) + 1;
    m = func_0023d1e0(a1);
    for (; i <= m; i++) {
        d = D208(c, r, d, i * 0.785398081f);
    }
    d = D208(c, r, d, a1);
    n = (d - h) - 1;
    ((u64 *)h)[0] = (n / 2) | 0x8000 | (0x82BBULL << 46);
    ((u64 *)h)[1] = 0x53;
    return d;
}

/* ---- k6.c */
typedef struct { u64 lo, hi; } QW;
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
typedef struct { u8 pad[0x18]; u64 unk18; } Tex;
typedef struct {
    s32 unk0;
    s32 unk4;
    Spr *unk8[7];
    s32 unk24;
    Spr *unk28[4];
    s32 unk38;
    u8 pad3c[0x6C - 0x3C];
    Tex *unk6C;
    u8 pad70[0xA18 - 0x70];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA94 - 0xA20];
    s32 unkA94;
} Obj;
extern Tex D_004268B0;
void func_0023d528(Obj *, s32 *, s32 *);
QW *func_0023d700(Spr *, Tex *, s32, s32, QW *, f32);
QW *func_0023e5b0(Obj *, QW *);
QW *func_0023e330(Obj *, QW *);
QW *func_0023e8f0(Obj *, QW *);
QW *func_0023ec88(Obj *, QW *);

typedef union {
    u64 v;
    struct { u64 tbp0:14, tbw:6, psm:6, tw:4, th:4, tcc:1, tfx:2, cbp:14, cpsm:4, csm:1, csa:5, cld:3; } b;
} Tex0;

CONTEXT_ONLY QW *func_0023e330(Obj *o, QW *r) { return r; }
CONTEXT_ONLY QW *func_0023e8f0(Obj *o, QW *r) { return r; }
QW *func_0023ee80(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    s32 i, x, y;
    u64 t;
    Tex0 tx;
    func_0023d528(o, a, b);
    x = b[0];
    y = b[1];
    for (i = 0; i < o->unk38; i++) {
        r = func_0023d700(o->unk28[i], &D_004268B0, x, y, r, o->unkA1C);
    }
    for (i = 0; i < o->unk24; i++) {
        if (((o->unkA18 == 0 && o->unk0 == 0) || (o->unk0 == 3 && o->unkA94 == 0)) && i == 5) continue;
        r = func_0023d700(o->unk8[i], o->unk6C, x, y, r, o->unkA1C);
    }
    r->lo = 0x2000000000008001;
    r->hi = 0xEE;
    r++;
    t = o->unk6C->unk18;
    tx.v = t;
    tx.b.csa = 0;
    tx.b.cld = 1;
    tx.b.psm = 0x13;
    r->lo = tx.v;
    r->hi = 6;
    r++;
    r->lo = t;
    r->hi = 6;
    r++;
    switch (o->unk0) {
    case 3:
        r = func_0023e5b0(o, r);
        if (o->unkA94) r = func_0023e330(o, r);
        break;
    case 0:
    case 1:
    case 2:
    case 4:
        r = func_0023ec88(o, func_0023e8f0(o, r));
        break;
    }
    return r;
}

/* ---- ih.c */
typedef struct { s32 x0, x4, x8, xc; } S4A20;
extern S4A20 D_00454A20;
typedef struct { u8 pad[0x3C]; s32 x3c; s32 x40; } St6C;
typedef struct { u8 pad[0x6C]; St6C *x6c; } Ow4;
typedef struct { s32 x0; Ow4 *x4; } Ob810;

/* ---- i_ok.c */
s32 func_00240810(Ob810 *o) {
    s32 r;
    St6C *p;
    if (o->x0 == 4) {
        r = 0;
        if (D_00454A20.x4 != 0) {
            if ((f32)D_00454A20.x4 < (f32)D_00454A20.xc * 0.3f) r = 1;
        }
    } else {
        r = 0;
        if (o->x0 != 3) {
            p = o->x4->x6c;
            if (p->x3c > 0) {
                r = p->x3c < 9;
                if (p->x40 >= 45) {
                    if ((f32)p->x3c / (f32)p->x40 < 0.199999988079071044921875f) r = 1;
                    else r = 0;
                }
            }
        }
    }
    return r;
}
