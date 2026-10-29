/* 132 words / score 81 (676 vs 672). The call/argument structure is right, and declaring sum first gives the original's stack slots. Left: colour global address scheduling. The original emits a separate lui for each of D_00F7056C/68/70/64; ours shares one hi through a move. Tried six RGBA macro orders and every order of the x/y/w/col statements. */
#include "ovl.h"

typedef struct { u8 n; u8 pad1[4]; u8 kind; u8 pad6[10]; } GbItem;
typedef struct { u8 pad0[3]; s8 font; u8 pad4; s8 size; u8 pad6[0x32]; u8 r, g, b, a; } GbText;
GbItem *func_001bc4d0(void);
s32 func_001bc500(void);
void func_001f9438(s32, s32, s32, s32, s32, s32, u32);
void func_001fbcd8(s32, s32, s32, s32, s32, s32, s32, s32, u32);
void func_001fc308(s32, s32, s32, s32, s32, s32, s32, u32, u32);
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
extern s16 D_00F71198[];
extern s32 D_00F82AC8;

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

void func_00f46ee0(GbText *t, s32 id) {
    s32 sum;
    GbItem *items;
    s32 n;
    s32 i;
    s32 x, y, w;
    u32 col;
    n = func_001bc500();
    items = func_001bc4d0();
    sum = 0;
    for (i = 0; i < n; i++)
        sum += items[i].n;
    y = D_00F7055C;
    x = D_00F70558;
    col = RGBA(D_00F70564, D_00F70568, D_00F7056C, D_00F70570);
    w = D_00F70560;
    func_001fc308(id, x, y + D_00F70578, 0, D_00F70574, 17, 0, col, col);
    func_001fc308(id, x + w, y + D_00F70578, 0, D_00F70574, 18, 0, col, col);
    func_001f9438(id, 2, x + (w + 8) / 2, y, D_00F71198[items[D_00F82AC8].kind], t->size,
                  RGBA(D_00F70564, D_00F70568, D_00F7056C, D_00F70570));
    func_001f9438(id, t->font, D_00F7057C, D_00F70584, 114, t->size, RGBA(t->r, t->g, t->b, t->a));
    func_001fbcd8(id, 1, 4, 0, D_00F70580, D_00F70588, sum, 0, RGBA(t->r, t->g, t->b, t->a));
}
