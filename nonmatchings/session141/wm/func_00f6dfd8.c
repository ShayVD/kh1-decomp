/* score 77 (132 words; 676 vs 672 bytes). UI draw. One extra `move a1,v1` (shared %hi for D_00FB4CEC/CE8) and scheduling around the first func_001fc308; dropping the w local gives score 50 but loads D_00FB4CE0 twice (680 bytes). The RGBA tree in the original is (r | a<<24) | (b<<16 | g<<8). Tried RGBA operand orders, statement orders, decl orders/types, all modes. */
#include "ovl.h"

typedef struct {
    u8 pad0[3];
    s8 x3;
    u8 pad4;
    s8 x5;
    u8 pad6[0x32];
    u8 r, g, b, a;
} Obj;

extern s32 D_00FB4CD8;
extern s32 D_00FB4CDC;
extern s32 D_00FB4CE0;
extern s32 D_00FB4CE4;
extern s32 D_00FB4CE8;
extern s32 D_00FB4CEC;
extern s32 D_00FB4CF0;
extern s32 D_00FB4CF4;
extern s32 D_00FB4CF8;
extern s32 D_00FB4CFC;
extern s32 D_00FB4D00;
extern s32 D_00FB4D04;
extern s32 D_00FB4D08;
extern s32 D_0108F288;
extern s16 D_00FB5918[];
s32 func_001bc500(void);
u8 *func_001bc4d0(void);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);
void func_001f9438(void *, s32, s32, s32, s32, s32, u32);
void func_001fbcd8(void *, s32, s32, s32, s32, s32, s32, s32, u32);

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

void func_00f6dfd8(Obj *o, void *ctx) {
    s32 n;
    s32 sum;
    u8 *lst;
    s32 i;
    u32 col;
    s32 x;
    s32 y;
    s32 w;

    n = func_001bc500();
    lst = func_001bc4d0();
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += lst[i * 16];
    }
    col = RGBA(D_00FB4CE4, D_00FB4CE8, D_00FB4CEC, D_00FB4CF0);
    x = D_00FB4CD8;
    y = D_00FB4CDC;
    w = D_00FB4CE0;
    func_001fc308(ctx, x, y + D_00FB4CF8, 0, D_00FB4CF4, 17, 0, col, col);
    func_001fc308(ctx, x + w, y + D_00FB4CF8, 0, D_00FB4CF4, 18, 0, col, col);
    func_001f9438(ctx, 2, x + (w + 8) / 2, y, D_00FB5918[lst[D_0108F288 * 16 + 5]], o->x5,
                  RGBA(D_00FB4CE4, D_00FB4CE8, D_00FB4CEC, D_00FB4CF0));
    func_001f9438(ctx, o->x3, D_00FB4CFC, D_00FB4D04, 114, o->x5, RGBA(o->r, o->g, o->b, o->a));
    func_001fbcd8(ctx, 1, 4, 0, D_00FB4D00, D_00FB4D08, sum, 0, RGBA(o->r, o->g, o->b, o->a));
}
