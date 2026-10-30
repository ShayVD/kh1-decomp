/* gb.x func_00f46ee0: matched by hand. */
#include "ovl.h"

/* gb.x func_00f46ee0: matched. Each colour read is a block of s32 locals (r, a, b, g), and w + 8 goes into its own local before the func_001fc308 calls (found by decomp-permuter, wgb round 54). */
#include "ovl.h"

typedef struct {
    u8 pad0[3];
    s8 x3;
    u8 pad4;
    s8 x5;
    u8 pad6[0x32];
    u8 r, g, b, a;
} Obj;

extern s32 D_00F70558;
extern s32 D_00F7055C;
extern s32 D_00F70560;
extern s32 D_00F70564;
extern s32 D_00F70568;
extern s32 D_00F7056C;
extern s32 D_00F70570;
extern s32 D_00F70574;
extern s32 D_00F70578;
extern s32 D_00F7057C;
extern s32 D_00F70580;
extern s32 D_00F70584;
extern s32 D_00F70588;
extern s32 D_00F82AC8;
extern s16 D_00F71198[];
s32 func_001bc500(void);
u8 *func_001bc4d0(void);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, u32);
s32 func_001fbcd8(void *, s32, s32, s32, s32, s32, s32, s32, u32);

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

void func_00f46ee0(Obj *o, void *ctx) {
    s32 n;
    s32 sum;
    u8 *lst;
    s32 i;
    u32 col;
    s32 x;
    s32 y;
    s32 w;
    s32 w8;

    n = func_001bc500();
    lst = func_001bc4d0();
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += lst[i * 16];
    }
    { s32 r = D_00F70564, a = D_00F70570, b = D_00F7056C, g = D_00F70568; col = RGBA(r, g, b, a); }
    x = D_00F70558;
    y = D_00F7055C;
    w = D_00F70560;
    w8 = w + 8;
    func_001fc308(ctx, x, y + D_00F70578, 0, D_00F70574, 17, 0, col, col);
    func_001fc308(ctx, x + w, y + D_00F70578, 0, D_00F70574, 18, 0, col, col);
    {
        s32 r = D_00F70564, a = D_00F70570, b = D_00F7056C, g = D_00F70568;
        func_001f9438(ctx, 2, x + w8 / 2, y, D_00F71198[lst[D_00F82AC8 * 16 + 5]], o->x5, RGBA(r, g, b, a));
    }
    func_001f9438(ctx, o->x3, D_00F7057C, D_00F70584, 114, o->x5, RGBA(o->r, o->g, o->b, o->a));
    func_001fbcd8(ctx, 1, 4, 0, D_00F70580, D_00F70588, sum, 0, RGBA(o->r, o->g, o->b, o->a));
}
