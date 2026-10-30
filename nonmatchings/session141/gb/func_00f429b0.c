/* Round 37 (wgb): no change (3 words, score 5). The greg dump shows high(func_00f42928) is reloaded into v0 at insn 246 (after the .off load), so it cannot be scheduled before lw v1,0(v0); the target reloads it into v1. Tried: a static inline kick(cb) around func_001c01b0 (no change), an inline helper for the D_00F82AA4/AA8/AAC stores (31 words), hill3 --noalias (200 s, no gain), every build mode (norlo 48 words, nostrict 131). */
/* Round 36 (wgb): no change (3 words, score 5). Note: the round 35 order moves D_00F82AAC = 1 below D_00F82AA8 = m->bufs[buf], which is only safe while m does not point at D_00F82AAC; tools/ovl/hill3.py accepts it with --noalias but not under its default strict rules, and a strict score-ranked run from the pre-round-35 draft stops at 45 words, score 85. */
/* Round 35 (wgb): gb.x func_00f429b0 near miss: 50 -> 3 words, score 95 -> 5 (836 vs 840 bytes; the 4 bytes are the trailing nop). Statement order from a dependency-safe statement-order hill climb (round 35 hill3.py: only orders that keep every read/write conflict in place): rgba[3] = 0 after tbl, D_00F82AB4 = -1 last of the inits, D_00F82AAC = 1 after D_00F82AA8, and the x/addr clip loads after w/h. Left: the func_00f42928 address for func_001c01b0 (lui/addiu a1) is built in v0 after the tbl[cur].off load; the target builds it in v1 before that load. -dS: loop.c hoists high(func_00f42928) into the pre-header, the pseudo gets no register and reload rematerialises it at the a1 set, which sched1 issues last in its block (lowest priority, after insn 205, the .off load), so v0 is free. Tried: a cb variable at every position in the block, &func / cast / prototype forms, every buf toggle form, operand order of D_00F82AA4, for/while/goto loops (goto changes everything), ctx2, 3 more hill runs, a 10-minute permuter run (its best only moved buf &= 1 out of the block, which is not equivalent). Earlier header below. */
/* 50 words / score 95: control flow and calls match. buf++; buf &= 1 keeps buf in s8 (the & 1 form gives xori and spills it). Left: our temporaries land in t0 where the target uses a2 throughout, and the x/w/h loads of the clip are in a different order. Hill-climbed the prologue order. */
#include "ovl.h"

typedef struct { s32 off; s16 w; s16 h; s32 x; s32 data; } GbClip;
typedef struct { s32 idx; s32 cur; s32 base; s32 bufs[2]; s32 a14; s32 id; } GbMovie;
typedef struct { u8 pad0[8]; u32 press; } GbPadState;
extern GbPadState D_002C5AD0;
extern GbClip *D_00F707B0[];
extern s32 D_00F707C0[];
extern s32 D_00F82A88;
extern s32 D_00F82A9C;
extern s32 D_00F82AA4;
extern s32 D_00F82AA8;
extern s32 D_00F82AAC;
extern s32 D_00F82AB0;
extern s32 D_00F82AB4;
extern s32 D_00F82AB8;
void func_0011d768(s32);
void func_001bfac8(void);
s32 func_001c01b0(s32, void *);
s32 func_00f200a8(void);
void func_00f200b8(s32);
void func_00f3fe80(s32, s32);
void func_00f422e8(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_00f428e0(s32);
void func_00f42928(void);

void func_00f429b0(GbMovie *m) {
    u8 rgba[4];
    s32 max;
    GbClip *tbl;
    s32 fade = 0;
    s32 state = 0;
    s32 buf = 0;
    s32 addr, w, h, x, v;
    s32 gs;
    rgba[0] = 0;
    rgba[1] = 0;
    rgba[2] = 0;
    tbl = D_00F707B0[m->idx];
    rgba[3] = 0;
    max = D_00F707C0[m->idx];
    D_00F82AB8 = -1;
    D_00F82AB0 = 0;
    D_00F82AAC = 0;
    D_00F82AB4 = -1;
    do {
        if (D_00F82AAC == 0 && state != 2) {
            if (D_002C5AD0.press & 0x20) {
                m->cur++;
                if (m->cur >= max)
                    m->cur = max - 1;
            }
            if (D_002C5AD0.press & 0x80) {
                v = m->cur - 1;
                if (v < 0)
                    v = 0;
                m->cur = v;
            }
            if (m->cur != D_00F82AB8) {
                if (D_00F82AB8 == -1)
                    func_0011d768(2);
                else
                    func_0011d768(1);
                D_00F82AB8 = m->cur;
                D_00F82AA4 = m->base + tbl[m->cur].off;
                D_00F82AA8 = m->bufs[buf];
                D_00F82AAC = 1;
                buf++;
                buf &= 1;
                func_001c01b0(-1, func_00f42928);
            }
        }
        if (D_00F82AB0 != 0) {
            if (state == 0) {
                fade += 12;
                if (fade >= 128) {
                    fade = 128;
                    state = 1;
                }
            }
            if (state == 2) {
                fade -= 12;
                if (fade <= 0) {
                    state = 3;
                    fade = 0;
                }
            }
            rgba[0] = rgba[1] = rgba[2] = rgba[3] = fade;
            if (D_00F82AAC == 2)
                D_00F82AAC = 0;
            D_00F82A9C = m->a14;
            w = tbl[D_00F82AB4].w;
            h = tbl[D_00F82AB4].h;
            x = tbl[D_00F82AB4].x;
            addr = m->base + tbl[D_00F82AB4].data;
            gs = func_00f200a8();
            D_00F82A88 = gs;
            func_00f422e8(D_00F82AB0, addr, 0, 0, w, h, x, rgba, 0, 0x44, 0, 0x5001D);
            func_00f428e0(0);
            func_00f200b8(D_00F82A88);
            func_00f3fe80(m->id, gs);
        }
        func_001bfac8();
        if ((D_002C5AD0.press & 1) && state == 1) {
            func_0011d768(3);
            state = 2;
        }
    } while (state != 3);
}
