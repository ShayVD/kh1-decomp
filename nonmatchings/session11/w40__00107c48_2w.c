/* 00107c48 2w LCS (2 positional), hand/nostrict, right size 232. s11w40: w34 3w draft + dead FP test `if ((f32)D_00351BD0 < 0.0f) j = 0;` right after `arg = (Ent16 *)i;`. The test is gone by local-alloc but leaves the lui/lw in bb0 with both hi and load global (they do not conflict, so global-alloc gives both v0: `lui v0; lw v0,7120(v0)`). Left: only the hi register, original lui v1. hi needs a conflict with v0 over its 1-insn life, or both local with load priority > hi. */
/* 00107c48: 3 LCS words (right size 232), hand/nostrict. s11w34: w20 3w with its dead TEST replaced by a flagged one-path dead SET `if (i != 0) { i = 0; n = 0; }` after `arg = (Ent16 *)i;` (also i <= 0, i & 1, etc.; one-set arms are if-converted to a cmov by jump1 and vanish before combine, a two-set arm survives to combine; the empty jump goes after combine). Same 3w as the dead test, so it is no longer a hack. Left: block-0 lui v0/lw v1 vs lui v1/lw v0. With the test at the top the D_00351BD0 lui/lw sit alone in bb2 during local-alloc (hi 95, load 96 both life 1, lower qty wins v0). With the test after the if (sched1 order lui, i=a0, lw, arg=i, beqz) both live 2: same tie. Needs the arg copy issued between lui and lw (or 3 refs on the load). */
#include "common.h"
typedef struct { s32 w0, w4, w8, w12; } Ent16;
typedef struct { s32 a, b; } P8;
extern s32 D_00351BD0;
extern Ent16 *D_00494BA8;
extern s32 D_00494BB0;
extern Ent16 D_00482290[];
extern Ent16 D_0047E250[];
extern P8 D_0047A1D0;

s32 func_00107c48(s32 i) {
    Ent16 *arg;
    Ent16 *base;
    Ent16 *dst;
    u32 tbl;
    Ent16 *q;
    s32 *p;
    s32 *r;
    s32 j;
    s32 n;
    u8 buf[64];

    arg = (Ent16 *)i;
    if ((f32)D_00351BD0 < 0.0f) j = 0; /* FLAGGED dead FP test (s11w40): moves the D_00351BD0 lui/lw into bb0 ahead of the dead-set test; both become global pseudos */
    if (i != 0) { i = 0; n = 0; } /* FLAGGED dead set: both sets die (i = 0 and n = 0 follow), life1 deletes them; the test keeps i live past the copy until combine */
    if (D_00351BD0 != 0) {
        base = D_00482290;
    } else {
        base = D_0047E250;
    }
    i = 0;
    tbl = arg->w4 + (s32)arg;
    n = 0;
    for (; i < D_00494BB0; ) {
        arg = (Ent16 *)(i << 4);
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)arg);
        i++;
        if (*p != 0) {
            q = (Ent16 *)((u32)(i * 16) + tbl);
            r = &q->w8;
            if (*r != 0) {
                *p = 3;
                base[n].w0 = *r; base[n].w4 = q->w12; n++;
            }
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
