/* Round 46 wwm2: score 77 -> 71, func_001f9438 and func_001fbcd8 declared s32. Earlier header below. */
/* Round 41 wwm2: score 81 -> 77, port.py of the wm twin func_00f6dfd8 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 132 words / score 81 (676 vs 672). The call/argument structure is right, and declaring sum first gives the original's stack slots. Left: colour global address scheduling. The original emits a separate lui for each of D_00F7056C/68/70/64; ours shares one hi through a move. Tried six RGBA macro orders and every order of the x/y/w/col statements. */
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

    n = func_001bc500();
    lst = func_001bc4d0();
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += lst[i * 16];
    }
    col = RGBA(D_00F70564, D_00F70568, D_00F7056C, D_00F70570);
    x = D_00F70558;
    y = D_00F7055C;
    w = D_00F70560;
    func_001fc308(ctx, x, y + D_00F70578, 0, D_00F70574, 17, 0, col, col);
    func_001fc308(ctx, x + w, y + D_00F70578, 0, D_00F70574, 18, 0, col, col);
    func_001f9438(ctx, 2, x + (w + 8) / 2, y, D_00F71198[lst[D_00F82AC8 * 16 + 5]], o->x5,
                  RGBA(D_00F70564, D_00F70568, D_00F7056C, D_00F70570));
    func_001f9438(ctx, o->x3, D_00F7057C, D_00F70584, 114, o->x5, RGBA(o->r, o->g, o->b, o->a));
    func_001fbcd8(ctx, 1, 4, 0, D_00F70580, D_00F70588, sum, 0, RGBA(o->r, o->g, o->b, o->a));
}
