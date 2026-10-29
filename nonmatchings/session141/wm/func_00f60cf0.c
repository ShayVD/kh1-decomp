/* Round 41 wwm2: score 136 -> 95. Three packed GS words are reordered: the XYZ word (x << 4) | 0x100000000 | (y1 << 4) << 16, and the two UV words with the v (<< 16) half first. Found by three greedy passes of r41/orsweep.py, which tries every order of the | terms in each packed word line. */
/* Round 36 (wwm2): wm.x func_00f60cf0 near miss: score 138 -> 136 (141 -> 139 words, 568 vs 600); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* score 138. Sprite packet; the original reaches the D_00FA6000 entry through several register copies (nested inline helpers?). Parked early. */
#include "ovl.h"

typedef struct {
    s32 x0;
    s32 u;
    s32 v;
    s32 w;
    s32 h;
} Spr;

extern Spr D_00FA6000[];
extern u8 *D_00F9B540;
u64 *func_00f66b78(void *);
void func_00f66b90(u64 *);

u64 *func_00f60cf0(void *buf, s32 x, s32 y, s32 idx, u64 col, s32 flip) {
    Spr *e = &D_00FA6000[idx];
    s32 x1 = x + e->w;
    s32 y1 = y + e->h;
    s32 u = e->u;
    s32 v = e->v;
    s32 u1 = u + e->w;
    s32 v1 = v + e->h;
    u64 *p;

    p = func_00f66b78(buf);
    p[1] = 0;
    p[0] = 342;
    p += 2;
    p[0] = *(u64 *)(D_00F9B540 + idx * 8 + 0x2200);
    p[1] = 6;
    p += 2;
    p[0] = col;
    p[1] = 1;
    p += 2;
    if (flip == 0) {
        p[0] = (u << 4) | ((u64)(v << 4) << 16);
        p[1] = 3;
        p += 2;
        p[0] = (x << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        p[1] = 5;
        p += 2;
        p[0] = ((u1 << 4) + 16) | ((u64)((v1 << 4) + 16) << 16);
        p[1] = 3;
        p += 2;
        p[1] = 5;
        p[0] = (x1 << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
    } else {
        p[1] = 3;
        p[0] = ((u64)(v << 4) << 16) | (u << 4);
        p += 2;
        p[1] = 5;
        p[0] = (x1 << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        p += 2;
        p[1] = 3;
        p[0] = ((u64)((v1 << 4) + 16) << 16) | (u1 << 4);
        p += 2;
        p[1] = 5;
        p[0] = (x << 4) | 0x100000000 | ((u64)(y1 << 4) << 16);
    }
    p += 2;
    func_00f66b90(p);
    return p;
}
