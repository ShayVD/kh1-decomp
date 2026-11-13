/* Round 48 wwm2: score 188 -> 186, statement order from tools/ovl/hill3.py (seed 3, --check ok, same built size). Earlier header below. */
/* Round 48 wwm2: the hill3o order from 4826d095 (wm func_00f22358 near miss, score 188 -> 123, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 123 was not valid. Restored the last valid statement order: score 188. Earlier header below. */
/* score 188 (1064 vs 1056 bytes); structure right, register allocation off: original hoists 71 into s8 alongside 68/66 (ours runs out of s-regs, so 71 is rematerialized), p shares s3 with &c->x8 and col shares s5 with &D_00F878F0, x/y negu regs swapped; tried statement orders, local pointer for D_00F878F0, s32 col, x/y order, c->x0 placement */
typedef struct { s32 x0; u8 *x4; s32 x8, xC, x10; } Ctx22;
extern Ctx22 *D_00F85160; /* one load in the original (lw s0, 0(&D_00F85160)), as func_00f2f3b8 declares it */
extern s32 D_00FBAA70;
extern s32 D_00FBAA74;
extern s32 D_00FBB330;
extern s32 D_00F878F0[4];
extern f32 D_00F85180[4][4];
extern f32 D_00F85200[4][4];
extern f32 D_00F87280[4][4];
s32 func_00f2ac10(s32);
void func_00f651c0(s32);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
u64 *func_00f66ac8(Ctx22 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b20(u64 *);
s32 func_00f66b38(u64 *);
s32 func_00f667b8(s32, u64 *, s32);
u8 *func_00f296d8(s32 *, u8 *, s32, s32);

void func_00f22358(s32 a0, s32 a1, s32 a2, u32 col, OvlMtx m, s32 tex) {
    OvlMtx b;
    OvlMtx r;
    Ctx22 *c;
    u64 *p;
    u64 *q;
    s32 x, y, k, s;
    s32 sv[3];

    y = -D_00FBAA74;
    x = -D_00FBAA70;
    if (D_00FBB330 == 13) {
        k = (func_00f2ac10(7) & 0x80) ? 3 : 1;
    } else {
        k = -1;
    }
    func_00f651c0(k);
    sceVu0UnitMatrix(r);
    sceVu0RotMatrixX(r, r, 3.1415926f); /* 0x40490FDA, the original's, from ee-gcc (it truncates) and from a port's compiler (it rounds): 3.1415927f gave the port 0x40490FDB (overlay-verify) */
    sceVu0MulMatrix(r, m, r);
    y = (y + 0x740) << 4;
    x = (x + 0x700) << 4;
    p = func_00f66b78(func_00f66ac8((Ctx22 *)D_00F85160->x0));
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = 0x131000070;
    p[1] = 78;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    p[1] = 24;
    p[0] = 0x0000740000007000;
    p += 2;
    p[1] = 0;
    p[0] = 70;
    p += 2;
    p[0] = (u64)col | 0x3F80000000000000;
    p[1] = 1;
    p += 2;
    p[1] = 5;
    p[0] = 0x174007000;
    p += 2;
    p[1] = 5;
    p[0] = 0x18C009000;
    p += 2;
    p[1] = 78;
    p[0] = 0x31000070;
    p += 2;
    func_00f66b90(p);
    D_00F878F0[0] = func_00f66ae0(p);
    if (tex == 0) return;
    q = p;
    p = func_00f66b78(func_00f66b20(q));
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = 0x5010D;
    p[1] = 71;
    p += 2;
    p[0] = (u64)x | ((u64)y << 32);
    p[1] = 24;
    p += 2;
    p[0] = 96;
    p[1] = 20;
    p += 2;
    p[0] = 0;
    p[1] = 8;
    p += 2;
    func_00f66b90(p);
    s = func_00f66b38(p);
    c = D_00F85160; /* overlay-verify: this was *D_00F85160, the struct's first word (a packet pointer), so c->x0 = p and the three
                       chains wrote into the packet and the DMA chain lost its ref tags (and the host faulted here once) */
    sv[2] = c->x10;
    sv[1] = c->xC;
    sv[0] = c->x8;
    c->x0 = (s32)p;
    b[3][3] = 1.0f;
    b[0][0] = 0.0f;
    b[0][1] = 0.0f;
    b[0][2] = 0.0f;
    b[0][3] = 0.0f;
    b[1][0] = 0.0f;
    b[1][1] = 0.0f;
    b[1][2] = 0.0f;
    b[1][3] = 0.0f;
    b[2][0] = 0.0f;
    b[2][1] = 0.0f;
    b[2][2] = 0.0f;
    b[2][3] = 0.0f;
    b[3][0] = 1.0f;
    b[3][1] = 1.0f;
    b[3][2] = 1.0f;
    c->x8 = func_00f667b8(c->x8, q, s);
    c->xC = func_00f667b8(c->xC, q, s);
    c->x10 = func_00f667b8(c->x10, q, s);
    sceVu0MulMatrix((void *)(c->x4 + 144), D_00F85200, r);
    sceVu0MulMatrix((void *)(c->x4 + 144), D_00F85180, (void *)(c->x4 + 144));
    sceVu0CopyMatrix((void *)(c->x4 + 16), b);
    sceVu0CopyMatrix((void *)(c->x4 + 80), D_00F87280);
    c->x4 = func_00f296d8(&c->x8, c->x4, tex, 0);
    c->x8 += 80;
    c->xC += 80;
    c->x10 += 80;
    D_00F878F0[3] = sv[2];
    D_00F878F0[1] = sv[0];
    D_00F878F0[2] = sv[1];
    func_00f651c0(-1);
}
