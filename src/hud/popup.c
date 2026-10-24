/* The party popups (docs/modules.md "Session 46"), default flags part.
 * func_00243ef8 draws one popup: a title bar of six sprites with the title
 * w0 (font func_001f0868, colour D_00459D30), n - 1 middle lines of two
 * sprites with w1 and a bottom line of four with w1 or w2 (colour
 * D_00459D20), 22 pixels apart.  func_00243d18 steps and draws one sprite,
 * func_00243da0 / func_00243e58 draw a text with a colour and alpha.
 * func_002444a0 is the HUD's step for the popups (all off) and
 * func_002448d8 is 1 while one is on. */
#include "common.h"

typedef struct { u8 b[0xC0]; } Spr26;
typedef struct { s32 r, g, b; } C3;
typedef struct { s32 on; u8 pad4[0xA00 - 4]; } Cell;
typedef struct { Cell c[5]; } Row;
typedef struct {
    s32 n[4];   /* +0x0 */
    Row r[3];   /* +0x10 */
} Grid;

extern Grid D_00656510; /* src/data/bss_0065.c: Tbl D_00656510 */
extern s32 D_00656420;
extern C3 D_00459D30[], D_00459D20[];
void func_0024ae00(void *);
void func_0024af00(void *);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00243c10(void *, s32, s32, s32, f32, s32);
#else
void func_00243c10(void *, s32, s32, s32, s32, f32);
#define func_00243c10(a1, a2, a3, a4, a5, a6) (func_00243c10)(a1, a2, a3, a4, a6, a5)
#endif
void func_0024ac08(void *, s32 *);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);
s32 func_001f0868(s32, s32, s32, s32, s32, s32, s32, s32);

void func_00243d18(s32 f, void *p, s32 a, s32 b, s32 c, f32 x, s32 d) {
    if (f) func_0024ae00(p);
    func_0024af00(p);
    func_00243c10(p, a, b, c, x, d);
}

void func_00243da0(s32 x, s32 y, s32 a2, C3 *c, f32 f) {
    u8 col[4]; u8 *p;
    p = col; *p++ = c->r; *p++ = c->g; *p++ = c->b;
    *p = (u32)(f * 128.0f);
    D_00656420 = func_001f0638(D_00656420, 1, *(s32 *)col,
        (((x << 4) + 0x7000) >> 4) - 0x700,
        (((y << 4) + 0x7400) >> 4) - 0x740, a2);
}

void func_00243e58(s32 x, s32 y, s32 a2, C3 *c, f32 f) {
    u8 col[4]; u8 *p;
    p = col; *p++ = c->r; *p++ = c->g; *p++ = c->b;
    *p = (u32)(f * 128.0f);
    D_00656420 = func_001f0868(D_00656420, 1, 1, *(s32 *)col, x, y, a2, 12);
}

/* func_00243ef8 passed the alpha first: with the EABI's float registers the
 * order does not change the call, but it changes the order gcc evaluates the
 * arguments in, so the PS2 build calls through the old prototype. */
#ifdef KH1_PS2
#define DRAW_TEXT ((void (*)(f32, s32, s32, s32, C3 *))func_00243da0)
#else
#define DRAW_TEXT(f, x, y, w, c) func_00243da0(x, y, w, c, f)
#endif

void func_00243ef8(s32 flag, Spr26 *r, Spr26 *m, Spr26 *l, Spr26 *e, s32 a5, s32 b6, s32 x, s32 y, s32 n, s32 w0, s32 w1, s32 w2, s32 *c13, s32 *c14, f32 f) {
    s32 t[2];
    s32 i, j, k, cnt;
    Spr26 *p;
    for (i = 0, p = l; i < 6; i++, p++) func_00243d18(flag, p, a5, x, y, f, (s32)c13);
    func_00243d18(flag, e, b6, x, y, f, (s32)c14);
    func_0024ac08(l, t);
    func_00243e58(x + t[0] + 184, y + t[1] + 3, w0, D_00459D30, f);
    y += 20;
    cnt = n - 1;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            p = m;
            for (k = 0; k < 2; k++) {
                if (i == 0) {
                    if (flag) func_0024ae00(p);
                    func_0024af00(p);
                }
                func_00243c10(p, a5, x, y, f, (s32)c13);
                p++;
            }
            func_0024ac08(m, t);
            DRAW_TEXT(f, x + t[0] + 6, y + t[1] + 2, w1, D_00459D20);
            y += 22;
        }
    }
    p = r;
    for (i = 0; i < 4; i++) { func_00243d18(flag, p, a5, x, y, f, (s32)c13); p++; }
    func_0024ac08(r, t);
    if (n == 1) DRAW_TEXT(f, x + t[0] + 6, y + t[1] + 2, w1, D_00459D20);
    else DRAW_TEXT(f, x + t[0] + 6, y + t[1] + 2, w2, D_00459D20);
}

void func_002444a0(void) {
    s32 i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            D_00656510.r[i].c[j].on = 0;
}

s32 func_002448d8(void) {
    s32 i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < D_00656510.n[i]; j++)
            if ((&D_00656510.r[0])[i].c[j].on) return 1;
    return 0;
}
