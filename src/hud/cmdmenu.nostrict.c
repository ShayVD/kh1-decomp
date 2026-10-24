/* The command menu (docs/modules.md "Session 46"), nostrict part.
 * func_0023b570 is its set up (called from the HUD's func_00236f18): clears
 * the six menus D_00650120 and the state D_00449908, loads the eight sprite
 * files (func_0024aac8), builds each menu's sprites from its index list with
 * func_0023aed0 (D_00650C00 is a second menu of kind 4), the frame of
 * D_0064FD60, and registers the draw hook func_0023a968 (func_0011ef10,
 * priority 0x29811).  func_0023bb98 draws the top list (mode 0) with its
 * colours D_004914C0 / D_004914D0 / D_004914E0 like hudspr.c's
 * func_00239e30. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0065.h"
#include "data/types/nostrict_text_00230000_s6_24_p.h"
#include "data/pieces/D_00449908.h"
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_004267C0.h"
#include "data/pieces/D_00426790.h"
#include "data/data_0044.h"
#include "data/pieces/D_004914C0.h"
#include "data/pieces/D_004914D0.h"
#include "data/pieces/D_004914E0.h"

/* A sprite (192 bytes). */
typedef struct { u64 d[24]; } HudSpr;
/* One menu (0x1d0 bytes): what func_0023aed0 builds from the sprite files,
 * the two sprite sets func_0023a8d0 picks from and the one in use (x1c0). */
typedef struct {
    void *x0; void *x4; s32 n; HudSpr *xc; HudSpr *x10;
    HudSpr *x14; HudSpr *x18; HudSpr *x1c; HudSpr *x20; HudSpr *x24;
    HudSpr *x28; HudSpr *x2c; HudSpr *x30; HudSpr *x34;
    u8 pad38[0x40 - 0x38]; HudSpr s0; HudSpr s1; void *x1c0; u8 pad1c4[0x1d0 - 0x1c4];
} CmdMenu;
typedef struct { s32 x0; s32 x4; s32 x8; s32 cur; s32 n; u8 id[16]; u8 col[16]; } Mn17;
typedef struct { s32 a, b, off; } Hdr570;
#define RES(d) ((u8 *)(d) + ((Hdr570 *)(d))->off)

/* Sprite and packet work buffers of the six menus func_0023b570 builds (phase 4:
 * defined here because nothing else uses them; sizes are the distance to the next known
 * object, docs/shiftable-plan.md "Phase 4"). HudSpr arrays (session 46; they were u8 arrays of the same sizes).  Qword-aligned: they hold DMA/GIF packets. */
HudSpr D_006489E0[3] ALIGNED(16);
HudSpr D_00648C20[1] ALIGNED(16);
HudSpr D_00648CE0[1] ALIGNED(16);
HudSpr D_00648DA0[1] ALIGNED(16);
HudSpr D_00648E60[1] ALIGNED(16);
HudSpr D_00648F20[4] ALIGNED(16);
HudSpr D_00649220[3] ALIGNED(16);
HudSpr D_00649460[7] ALIGNED(16);
HudSpr D_006499A0[7] ALIGNED(16);
HudSpr D_00649EE0[1] ALIGNED(16);
HudSpr D_00649FA0[1] ALIGNED(16);
HudSpr D_0064A060[1] ALIGNED(16);
HudSpr D_0064A120[1] ALIGNED(16);
HudSpr D_0064A1E0[1] ALIGNED(16);
HudSpr D_0064A2A0[1] ALIGNED(16);
HudSpr D_0064A360[4] ALIGNED(16);
HudSpr D_0064A660[4] ALIGNED(16);
HudSpr D_0064A960[2] ALIGNED(16);
HudSpr D_0064AAE0[7] ALIGNED(16);
HudSpr D_0064B020[7] ALIGNED(16);
HudSpr D_0064B560[1] ALIGNED(16);
HudSpr D_0064B620[1] ALIGNED(16);
HudSpr D_0064B6E0[1] ALIGNED(16);
HudSpr D_0064B7A0[1] ALIGNED(16);
HudSpr D_0064B860[1] ALIGNED(16);
HudSpr D_0064B920[1] ALIGNED(16);
HudSpr D_0064B9E0[4] ALIGNED(16);
HudSpr D_0064BCE0[4] ALIGNED(16);
HudSpr D_0064BFE0[1] ALIGNED(16);
HudSpr D_0064C0A0[6] ALIGNED(16);
HudSpr D_0064C520[6] ALIGNED(16);
HudSpr D_0064C9A0[1] ALIGNED(16);
HudSpr D_0064CA60[1] ALIGNED(16);
HudSpr D_0064CB20[1] ALIGNED(16);
HudSpr D_0064CBE0[1] ALIGNED(16);
HudSpr D_0064CCA0[1] ALIGNED(16);
HudSpr D_0064CD60[1] ALIGNED(16);
HudSpr D_0064CE20[4] ALIGNED(16);
HudSpr D_0064D120[4] ALIGNED(16);
HudSpr D_0064D420[1] ALIGNED(16);
HudSpr D_0064D4E0[6] ALIGNED(16);
HudSpr D_0064D960[6] ALIGNED(16);
HudSpr D_0064DDE0[1] ALIGNED(16);
HudSpr D_0064DEA0[1] ALIGNED(16);
HudSpr D_0064DF60[1] ALIGNED(16);
HudSpr D_0064E020[1] ALIGNED(16);
HudSpr D_0064E0E0[1] ALIGNED(16);
HudSpr D_0064E1A0[1] ALIGNED(16);
HudSpr D_0064E260[4] ALIGNED(16);
HudSpr D_0064E560[4] ALIGNED(16);
HudSpr D_0064E860[1] ALIGNED(16);
HudSpr D_0064E920[6] ALIGNED(16);
HudSpr D_0064EDA0[6] ALIGNED(16);
HudSpr D_0064F220[1] ALIGNED(16);
HudSpr D_0064F2E0[1] ALIGNED(16);
HudSpr D_0064F3A0[1] ALIGNED(16);
HudSpr D_0064F460[1] ALIGNED(16);
HudSpr D_0064F520[1] ALIGNED(16);
HudSpr D_0064F5E0[1] ALIGNED(16);
HudSpr D_0064F6A0[4] ALIGNED(16);
HudSpr D_0064F9A0[4] ALIGNED(16);
HudSpr D_0064FCA0[1] ALIGNED(16);
extern CmdMenu D_00650120[]; /* src/data/bss_0065.c: Ob17 D_00650120[0x6] */
extern CmdMenu D_00650C00;
extern u8 D_004409A0[], D_00443180[], D_004419B0[], D_00444A70[], D_00446240[], D_004478F0[], D_00448FA0[], D_00449530[];
extern u8 D_004497A0[], D_004497D0[], D_00449818[], D_00449860[], D_004498A8[], D_004498E8[];
extern u8 D_0064FD60[];
extern f32 D_00650DD0;
extern f32 D_00650DD4;
extern s32 D_00449900;
extern Col D_004914C0;
extern Col D_004914D0;
extern Col4 D_004914E0;
void *memset(void *, s32, u32);
void func_0023b4b8(s32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
s32 func_0023a968(void);
s32 func_0011ef38(s32 (*)(void));
void func_0011ef10(s32, s32 (*)(void));
void func_00239778(s32 a, void *b, void *c, void *d, s32 e, s32 g, f32 h);
void func_00239d20(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h);
void func_002399f0(s32, void *, void *, s32, s32, s32 *, f32);
void func_0024ac08(void *, s32 *);
void func_0024ac68(void *, s32 *);
void func_00239558(s32, s32, s32, s32);

void func_0023aed0(s32 mode, CmdMenu *o, s32 *idx, HudSpr *tbl, void *a, void *b, HudSpr *p6, HudSpr *p7,
                   s32 n, HudSpr *p9, HudSpr *p10, HudSpr *p11, HudSpr *p12, HudSpr *p13, HudSpr *p14,
                   HudSpr *p15, HudSpr *p16, HudSpr *p17)
{
    s32 i;
    *p10 = tbl[*idx++];
    *p11 = tbl[*idx++];
    for (i = 0; i < n; i++) p9[i] = tbl[*idx];
    idx++;
    *p6 = tbl[*idx++];
    for (i = 0; i < 4; i++) p12[i] = tbl[*idx++];
    *p7 = tbl[*idx++];
    switch (mode) {
    case 0:
        for (i = 0; i < 3; i++) p13[i] = tbl[*idx++];
        break;
    case 1: case 2: case 3: case 4:
        if (mode == 1) {
            for (i = 0; i < 2; i++) p13[i] = tbl[*idx++];
        } else if (mode != 4) {
            *p13 = tbl[*idx++];
        }
        *p16 = tbl[*idx++];
        for (i = 0; i < n; i++) p15[i] = tbl[*idx];
        idx++;
        *p14 = tbl[*idx++];
        for (i = 0; i < 4; i++) p17[i] = tbl[*idx++];
        break;
    }
    o->x0 = a;
    o->x4 = b;
    o->xc = p6;
    o->x10 = p7;
    o->n = n;
    o->x14 = p9;
    o->x18 = p10;
    o->x1c = p11;
    o->x20 = p12;
    o->x24 = p13;
    o->x28 = p14;
    o->x2c = p15;
    o->x30 = p16;
    o->x34 = p17;
}

void func_0023b570(void) {
    s32 i;
    HudSpr *sp;
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
    func_0023aed0(0, &D_00650120[0], (s32 *)D_004497A0, (HudSpr *)p, D_00426790, D_004267F0, D_00648CE0, D_00648DA0, 3,
                  D_006489E0, D_00648C20, D_00648E60, D_00648F20, D_00649220, 0, 0, 0, 0);
    sp = (HudSpr *)RES(D_00449530);
    D_00650120[0].s0 = sp[0];
    D_00650120[0].s1 = sp[1];
    D_00650120[0].x1c0 = 0;
    h = (Hdr570 *)D_00443180; p = (u8 *)h + h->off;
    func_0023aed0(1, &D_00650120[1], (s32 *)D_004497D0, (HudSpr *)p, D_004267C0, D_004267F0, D_0064A060, D_0064A1E0, 7,
                  D_00649460, D_00649EE0, D_0064A2A0, D_0064A360, D_0064A960, D_0064A120, D_006499A0, D_00649FA0, D_0064A660);
    h = (Hdr570 *)D_004419B0; p = (u8 *)h + h->off;
    func_0023aed0(2, &D_00650120[2], (s32 *)D_00449818, (HudSpr *)p, D_004267C0, D_004267F0, D_0064B6E0, D_0064B860, 7,
                  D_0064AAE0, D_0064B560, D_0064B920, D_0064B9E0, D_0064BFE0, D_0064B7A0, D_0064B020, D_0064B620, D_0064BCE0);
    h = (Hdr570 *)D_00444A70; p = (u8 *)h + h->off;
    func_0023aed0(3, &D_00650120[3], (s32 *)D_00449860, (HudSpr *)p, D_004267C0, D_004267F0, D_0064CB20, D_0064CCA0, 6,
                  D_0064C0A0, D_0064C9A0, D_0064CD60, D_0064CE20, D_0064D420, D_0064CBE0, D_0064C520, D_0064CA60, D_0064D120);
    h = (Hdr570 *)D_00446240; p = (u8 *)h + h->off;
    func_0023aed0(4, &D_00650120[4], (s32 *)D_004498A8, (HudSpr *)p, D_004267C0, D_004267F0, D_0064DF60, D_0064E0E0, 6,
                  D_0064D4E0, D_0064DDE0, D_0064E1A0, D_0064E260, D_0064E860, D_0064E020, D_0064D960, D_0064DEA0, D_0064E560);
    h = (Hdr570 *)D_004478F0; p = (u8 *)h + h->off;
    func_0023aed0(4, &D_00650C00, (s32 *)D_004498A8, (HudSpr *)p, D_004267C0, D_004267F0, D_0064F3A0, D_0064F520, 6,
                  D_0064E920, D_0064F220, D_0064F5E0, D_0064F6A0, D_0064FCA0, D_0064F460, D_0064EDA0, D_0064F2E0, D_0064F9A0);
    func_0024af40(D_004498E8, D_0064FD60, D_00448FA0);
    if (func_0011ef38(func_0023a968) == 0) func_0011ef10(0x29811, func_0023a968);
}

/* func_0023bb98 matches only with a copy of func_00239a80 (hudspr.nofill.c)
 * above it. */
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

void func_0023bb98(s32 mode, Mn17 *m, s32 big, s32 on, CmdMenu *o, s32 x, s32 y, f32 f) {
    s32 pos[4];
    Col c0 = D_004914C0;
    Col c1 = D_004914D0;
    Col4 c2 = D_004914E0;
    s32 buf[16];
    f32 s;
    s32 i, yy, xx, on2;
    HudSpr *sel;
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
