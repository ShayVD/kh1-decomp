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
    rgba[3] = 0;
    tbl = D_00F707B0[m->idx];
    max = D_00F707C0[m->idx];
    D_00F82AB8 = -1;
    D_00F82AB4 = -1;
    D_00F82AB0 = 0;
    D_00F82AAC = 0;
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
                D_00F82AAC = 1;
                D_00F82AA8 = m->bufs[buf];
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
            x = tbl[D_00F82AB4].x;
            addr = m->base + tbl[D_00F82AB4].data;
            w = tbl[D_00F82AB4].w;
            h = tbl[D_00F82AB4].h;
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
