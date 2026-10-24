/* The timer and score display (docs/modules.md "Session 46"),
 * 0x002474e8-0x00248628, default flags part.  D_00669350 (MgSlot) points at a
 * caller's MgHud: a score "a" or "a/b" (x4, the digits by mode 1-4), a
 * distance in metres (x18, x1c), and a time (x20; hours only with x2c)
 * drawn with sprites at (x, y), the record time in red under it
 * (func_00247930) and the timer's icon (func_00248238).  func_00248380 is the
 * draw hook (registered by func_00248400, the set up): its drawing
 * environment D_00669070, then func_00248140 (sprites and texts in one GIF
 * send).  func_002485b8 shows a MgHud and func_002485d0 / func_002485e0 hide
 * it; func_002485f0 returns 1 when its time shows and 2 when its score does
 * (the markers of src/hud/marker.c move down for them).  Most likely the
 * minigames' display; not proved by a boot. */
#include "common.h"
#include "data/types/text_00240000_h50.h"
#include "data/pieces/D_00467408.h"
#include "data/pieces/D_00431F30.h"

typedef struct {
    s32 x0;
    s32 x4;    /* +0x4: the score is shown */
    s32 on;    /* +0x8: with its maximum */
    s32 mode;  /* +0xC: digits 1-4 */
    s32 a;     /* +0x10 */
    s32 b;     /* +0x14 */
    s32 x18;   /* +0x18: the distance is shown */
    s32 x1c;   /* +0x1C: the distance */
    s32 x20;   /* +0x20: the time is shown */
    s32 x;     /* +0x24 */
    s32 y;     /* +0x28 */
    s32 x2c;   /* +0x2C: with hours */
    s32 x30;
    s32 v34, v38, v3C, v40;  /* +0x34: the time, from hundredths to hours */
    s32 v44, v48, v4C, v50;  /* +0x44: the record */
} MgHud;
typedef struct { s32 on; MgHud *c; } MgSlot;
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 r, g, b, a; } RGBA;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;

Q D_00669070 ALIGNED(16);
Panel D_006691E0 ALIGNED(32);
u8 D_006692C0[0x18] ALIGNED(16);
u8 D_006692F0[0x18] ALIGNED(16);
u8 D_00669320[0x18] ALIGNED(16);
extern MgSlot D_00669350; /* src/data/bss_0066.c: u8 D_00669350[0x8] */
extern void *D_00669358[]; /* src/data/bss_0066.c: u8 D_00669358[0x30] */
extern void *D_00669388[2];
extern void *D_00669390[8];
extern void *D_006693B0[8];
extern void *D_006693D0[7]; /* src/data/bss_0066.c: u8 D_006693D0[0x20] */
extern Q4 D_00351E10[];
extern Q4 *D_006691D0;
extern Q4 *D_006691D4;
extern s32 D_0046740C;
extern char D_004917D8[];
s32 sprintf(char *, const char *, ...);
u32 strlen(const char *);
Q4 *func_001f12c0(Q4 *, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_002393d8(void);
void func_0024aa48(void *, void *, void *);
void func_00247930(MgHud *);
void func_00248238(MgSlot *);
void func_00249a48(void *, s32);

/* func_00247cf8 passed the alpha fourth: with the EABI's float registers the
 * order does not change the call, but it changes the order gcc evaluates the
 * arguments in, so the PS2 build calls through the old prototype. */
#ifdef KH1_PS2
#define DRAW_TEXT ((void (*)(s32, s32, u8 *, f32, char *, s32))func_002475d0)
#else
#define DRAW_TEXT(x, y, c, f, s, fnt) func_002475d0(x, y, c, s, fnt, f)
#endif

void func_002474e8(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_006691E0;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_006691E0.q[i].d = D_006691E0.q[i].d * s;
    }
    D_006691D0 = func_002388b8(&D_006691E0, 1, D_006691D0);
}

void func_002475d0(s32 a0, s32 a1, u8 *c, char *a3, s32 a4, f32 f) {
    RGBA col;
    col.r = *c++;
    col.g = *c++;
    col.b = *c++;
    col.a = (u32)(f * 128.0f);
    D_006691D0 = func_001f12c0(D_006691D0, 1, *(s32 *)&col, a0, a1, (s32)a3, a4);
}

void func_00247678(s32 v, s32 *tens, s32 *ones) {
    *tens = v / 10;
    *ones = v % 10;
}

void func_002476a0(MgHud *o) {
    s32 a, b;
    s32 x, y;
    x = o->x; x += 73; y = o->y;
    if (o->x2c) {
        func_00247678(o->v40, &a, &b);
        func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
        x += 15;
        func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
        x += 16;
        func_002474e8(D_00669358[10], D_006692F0, x, y, 1.0f);
        x += 13;
    }
    func_00247678(o->v3C, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 9;
    func_00247678(o->v38, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 5;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 4;
    func_00247678(o->v34, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    func_002474e8(D_00669358[b], D_006692F0, x + 15, y, 1.0f);
}

void func_00247b50(MgHud *m) {
    s32 i;
    for (i = 0; i < 8; i++)
        func_002474e8(D_006693B0[i], D_006692C0, m->x, m->y, 1.0f);
    func_002476a0(m);
    func_00247930(m);
}

void func_00247bd0(MgHud *m) {
    s32 i;
    for (i = 0; i < 8; i++)
        func_002474e8(D_00669390[i], D_006692C0, m->x, m->y, 1.0f);
    func_002476a0(m);
    func_00247930(m);
}

void func_00247c50(MgHud *m) {
    s32 i;
    for (i = 0; i < 7; i++)
        func_002474e8(D_006693D0[i], D_006692C0, m->x, m->y, 1.0f);
    func_002476a0(m);
}

void func_00247cc8(s32 n) {
    func_00249a48(&D_00431F30[n], 1);
}

void func_00247cf8(MgHud *p) {
    char buf[16];
    u8 col[3];
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    switch (p->mode) {
    case 1:
        sprintf(buf, "%01d", p->a);
        DRAW_TEXT(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            DRAW_TEXT(84, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%01d", p->b);
            DRAW_TEXT(97, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 2:
        sprintf(buf, D_004917D8, p->a);
        DRAW_TEXT(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            DRAW_TEXT(97, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, D_004917D8, p->b);
            DRAW_TEXT(110, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 3:
        sprintf(buf, "%03d", p->a);
        DRAW_TEXT(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            DRAW_TEXT(110, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%03d", p->b);
            DRAW_TEXT(123, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 4:
        sprintf(buf, "%04d", p->a);
        DRAW_TEXT(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            DRAW_TEXT(123, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%04d", p->b);
            DRAW_TEXT(136, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    }
}

void func_00248010(MgHud *p) {
    char buf[16];
    u8 col[3];
    s32 x;
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    sprintf(buf, "%d", p->x1c);
    x = 69;
    func_002475d0(x, 22, col, buf, D_00467408, 1.0f);
    x += strlen(buf) * 13;
    sprintf(buf, "m");
    func_002475d0(x + 2, 24, col, buf, D_0046740C, 1.0f);
}

/* func_00248140 passes its MgHud; nothing reads it. */
void func_002480d8(MgHud *c) {
    s32 i;
    for (i = 0; i < 2; i++)
        func_002474e8(D_00669388[i], D_00669320, 0, 0, 1.0f);
}

void func_00248140(MgSlot *a) {
    MgHud *c;
    D_006691D4 = D_00351E10;
    D_006691D0 = D_00351E10 + 1;
    c = a->c;
    func_002393d8();
    if (c->x20) {
        if (c->x30 == 0) func_00247c50(c);
        else if (c->x2c == 0) func_00247bd0(c);
        else func_00247b50(c);
    }
    if (c->x4 || c->x18) func_002480d8(c);
    if (c->x4) func_00247cf8(c);
    if (c->x18) func_00248010(c);
    func_00237018(D_006691D4, D_006691D0 - D_006691D4, 1);
}

s32 func_00248380(void) {
    if (D_00669350.on == 0) {
        return 0;
    }
    func_002370c8(&D_00669070);
    D_00669070.unkE0 = 5;
    D_00669070.unk60 = 0x30003;
    func_00237018(&D_00669070, 0x16, 1);
    func_00248140(&D_00669350);
    func_00248238(&D_00669350);
    return 0;
}

void func_002485b8(MgHud *c) {
    D_00669350.on = 1;
    D_00669350.c = c;
}

void func_002485d0(void) {
    D_00669350.on = 0;
}

void func_002485e0(void) {
    D_00669350.on = 0;
}

s32 func_002485f0(void) {
    s32 r = 0;
    if (D_00669350.on == 1) {
        r = D_00669350.c->x20 != 0;
        if (D_00669350.c->x4 != 0) r |= 2;
    }
    return r;
}
