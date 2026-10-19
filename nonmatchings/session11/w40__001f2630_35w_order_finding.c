/* 001f2630 35w LCS, hand/nofill, session9/w2 context. FINDING (s11w40): plain constants, store source order x30(f2+w) x34(f4+288) x44 x10 x14 x2c (computes f2+w/f4+288 before the x10/x14 stores so f2/f4 die there: all six in the weight -1 group in LUID order) gives the EXACT original store order and loop-block registers, but sched1 now issues the a0=2 arg insn before the cy+h insn, so reload picks v1 (not a0) for the spilled h and the first spill choice changes reloads function-wide (size 1064). Needs cy+h issued after the d[0] `or` frees a0 and before li a0,2. */
/* 001f2630 3w LCS, hand/nofill, session9/w2 context. Plain constant (no k8, no dead set): g->x2c = 0x8000 after g->x14 in source (both FIX-pinned in an hc climb). Every register in the block matches the original; only store order is off: x10/x14 have weight 0 here (f2/f4 still used later by x30/x34), so x2c (weight -1) still issues 3rd. Pinning x30/x34 before x10/x14 with the plain constant breaks global allocation (23w+). */
/* 001f2630 1w LCS (5 positional), hand/nofill, same context as session9/w2__001f2630_3w.c. Fresh hc climb from struct-offset order (seed 2). Left: the x2c sw a1,44(s4) issues right after sd d[1] instead of after sw t0,20(s4) (x14). Moving x2c later in source changes allocation (32-180w). k8 = 0x8000 inside the block plus a dead 'k8 = 0x8000' in the '\\n' branch (stops loop.c hoisting) gives the exact store order but 0x8000/f4/f4+288 take t0/a2/a1 instead of a1/t0/a2 (7w, see 001f2630_7w_order.c): the li is issued early in sched1 so k8 lives 28 insns and drops in local-alloc priority. */
/* 001f2630 3w, hand/nofill (unchanged w13 draft; new finding). The natural offset-order store block (x10,x14,x20,...,x4c with loads f7,d0,f4,d1,f2 first) is 6w with the same allocation. Final store order = sched1 order (sched2 ties fall back to it); sched1 ranks ready stores by reg weight (value dies: first), then forward-dep count (x20=cx has 3, the rest 2), then LUID. Moving x2c after x44 in the source changes local-alloc in the loop block, so the first "Spilling for insn" in greg (the cy+h insn, h spilled at 20(sp)) picks v1/v0 instead of a0 and every spilled-param reload in the function changes (180+ words). A u16-union alias on x2c changes nothing. */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef struct {
    u64 d[2];
    s32 x10, x14, x18, x1c;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
} Pg;
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;

#define SETX() \
    switch (mode) { \
    case 0: \
    default: \
        cx = x * 16 + 0x7000; \
        break; \
    case 1: \
        cx = (x - func_001f0340(str, sc)) * 16 + 0x7000; \
        break; \
    case 2: \
        cx = (x - func_001f0340(str, sc) / 2) * 16 + 0x7000; \
        break; \
    }

extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003E8E2C;
CONTEXT_ONLY void func_001efb78(s32 arg0) { D_003E8E00 = arg0; }
CONTEXT_ONLY s32 func_001efb88(void) { return D_003E8E00; }
CONTEXT_ONLY void func_001efb98(s32 arg0) { D_003E8E04 = arg0; }
CONTEXT_ONLY s32 func_001efba8(void) { return D_003E8E04; }
CONTEXT_ONLY s32 func_001eff50(s32 a) {
    s32 i;
    Glyph *e = D_003E8E28;
    for (i = 0; i < D_003E8E2C; i++, e++) {
        if (e->code == a) return i;
    }
    return 0;
}
CONTEXT_ONLY s32 func_001f0340(u8 *p, s32 scale) {
    s32 d = 18;
    s32 x = 0;
    for (;;) {
        s32 c = *p;
        s32 k;
        if (c == 0 || c == 10) return x >> 4;
        k = c | (p[1] << 8);
        p += 2;
        if (k == 0x4081) {
            x += (scale << 8) / d;
        } else {
            Glyph *g = &D_003E8E28[func_001eff50(k)];
            x += ((g->w << 4) + func_001efb88()) * scale / d;
        }
    }
}

s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);
extern u8 D_003F2270[];

void func_001f2630(s32 mode, u32 a1, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *buf;
    void *dma;
    Pg *g;
    Glyph *gl;
    s32 cx, cy, c, w, s, h;
    u8 f7;
    s32 f2, f4, t, a;

    func_001efb78(0);
    func_001efb98(0);
    h = sc * 16;
    func_00266f38(func_00266c08(2), D_003F2270);
    buf = func_00122048(1024, 128);
    dma = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    g = (Pg *)(buf + 1);
    d = (u64 *)g;
    d[0] = 0x4000000000000001;
    d[1] = 0xeeee;
    d[2] = 0;
    d[3] = 0x3f;
    d[4] = 0x4007ff8001300000;
    d[5] = 22;
    d[6] = 68;
    d[7] = 66;
    d[8] = a1;
    d[9] = 1;
    d[10] = 0x50ab400000008001;
    d[11] = 0x4343e;
    *(u64 *)buf = 0x7000000b;
    g = (Pg *)(buf + 7);
    cy = y * 16 + 0x7400;
    SETX();
    for (;;) {
        c = *str;
        if (c == 0) goto done;
        if (c == '\n') {
            str++;
            cy += D_0063F740;
            SETX();
            continue;
        }
        c |= str[1] << 8;
        str += 2;
        if (c == 0x4081) {
            cx += (sc << 8) / 18;
            continue;
        }
        gl = &D_003E8E28[func_001eff50(c)];
        w = gl->w << 4;
        s = w * sc / 18;
        a = (w + func_001efb88()) * sc / 18;
/*P*/
        f7 = gl->f7;
        f4 = gl->f4;
        f2 = gl->f2;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->d[1] = 22;
        g->x30 = f2 + w;
        g->x34 = f4 + 288;
        g->x44 = cy + h;
        g->x10 = f2;
        g->x14 = f4;
        g->x2c = 0x8000;
        g->x20 = cx;
        g->x24 = cy;
        g->x28 = 0x100000;
        g->x48 = 0x100000;
        g->x4c = 0;
        g->x40 = cx + s;
/*Q*/
        t = func_00266c08(2);
        cx += a;
        func_00266f38(t, dma);
        sceGsSyncPath(0, 0);
    }
done:
    func_001220b8(buf);
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
}
