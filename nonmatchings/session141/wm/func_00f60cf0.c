/* Round 41 wwm2: score 95 -> 42, port.py of the gb twin func_00f39bf8 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* Round 41 wwm2: score 136 -> 95. Three packed GS words are reordered: the XYZ word (x << 4) | 0x100000000 | (y1 << 4) << 16, and the two UV words with the v (<< 16) half first. Found by three greedy passes of r41/orsweep.py, which tries every order of the | terms in each packed word line. */
/* 53 words / score 52: the prologue and the non-flip branch match. Index D_00FA6000[idx] directly per field (no pointer). Writing q[1] before q[0] in the last flip store stops cross-jumping. Left: the flip branch is scheduled differently, starting with v<<4 where we load sp0 first. */

typedef struct { s32 pad0; s32 u; s32 v; s32 w; s32 h; } GbSprite;
typedef struct { u8 pad0[0x2200]; u64 tex0[1]; } GbTexState;
extern GbSprite D_00FA6000[];
extern GbTexState *D_00F9B540;
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);

u64 *func_00f60cf0(u64 *p, s32 x, s32 y, s32 idx, u64 rgba, s32 flip) {
    s32 x1 = x + D_00FA6000[idx].w;
    s32 y1 = y + D_00FA6000[idx].h;
    s32 u = D_00FA6000[idx].u;
    s32 u1 = u + D_00FA6000[idx].w;
    s32 v = D_00FA6000[idx].v;
    s32 v1 = v + D_00FA6000[idx].h;
    u64 *q = func_00f66b78(p);
    q[0] = 0x156;
    q[1] = 0;
    q += 2;
    q[0] = D_00F9B540->tex0[idx];
    q[1] = 6;
    q += 2;
    q[0] = rgba;
    q[1] = 1;
    q += 2;
    if (flip == 0) {
        q[0] = (u << 4) | ((u64)(v << 4) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        q[1] = 5;
        q += 2;
        q[0] = ((u1 << 4) + 16) | ((u64)((v1 << 4) + 16) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x1 << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
        q[1] = 5;
    } else {
        q[0] = (u << 4) | ((u64)(v << 4) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x1 << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        q[1] = 5;
        q += 2;
        q[0] = ((u64)((v1 << 4) + 16) << 16) | ((u1 << 4) + 16);
        q[1] = 3;
        q += 2;
        q[1] = 5;
        q[0] = (x << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
    }
    q += 2;
    func_00f66b90(q);
    return q;
}
