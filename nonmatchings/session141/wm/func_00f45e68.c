/* Round 36 (wgb): wm.x func_00f45e68 near miss: 27 -> 28 words, score 44 -> 36 (aligned diff 27 -> 24). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 27 words (520 bytes). Flip/non-flip sprite (no 1792 offset). Mixed access forms (e = &D[idx] for u/v, D[idx].w/.h) plus hill-climbed statement order took it from 54 to 27. Left: the target makes two element addresses (D+idx*20 copied twice, and idx*20+D) and loads w,h,u,v in that order; x0/x1 spill to the stack. */
/* 54 words (520 bytes). Flip/non-flip sprite (no 1792 offset); structure right; left: element-address copies (t1/a2/v1 plus a separate t0) and branch scheduling. Tried ~1100 random orders of the field loads and both branch bodies. */
typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } T45e68;
extern T45e68 D_00F9B330[];
extern u64 D_00F87070[];
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f45e68(s32 pk, s32 flip, s32 idx, u32 rgba) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    s32 u, v, w, h;
    u64 *p;

    T45e68 *e = &D_00F9B330[idx];
    h = D_00F9B330[idx].h;
    w = D_00F9B330[idx].w;
    x1 = w + 6;
    u = e->u;
    v = e->v;
    if (flip == 0) {
        v0 = v + 1;
        x0 = 9;
        v1 = v + h - 2;
        y0 = 57;
        y1 = y0 + h - 3;
        u0 = u + 1;
        u1 = u + w - 2;
    } else {
        u1 = u + 1;
        x1 = 503;
        v0 = v + 1;
        y0 = 56;
        x0 = 505 - w;
        v1 = v + h - 2;
        u0 = u + w - 2;
        y1 = y0 + h;
    }
    p = func_00f66b78(pk);
    p[0] = 0x0000008000000048LL;
    p[1] = 66;
    p += 2;
    p[0] = 342;
    p[1] = 0;
    p += 2;
    p[0] = (u64)rgba | 0x3F80000000000000LL;
    p[1] = 1;
    p += 2;
    p[0] = D_00F87070[idx];
    p[1] = 6;
    p += 2;
    p[0] = (s64)(u0 << 4) | ((s64)(v0 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x0 << 4) | ((s64)(y0 << 4) << 16);
    p[1] = 5;
    p += 2;
    p[0] = (s64)(u1 << 4) | ((s64)(v1 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x1 << 4) | ((s64)(y1 << 4) << 16);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
