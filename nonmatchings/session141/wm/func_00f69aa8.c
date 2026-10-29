/* Round 35 (wgb): wm.x func_00f69aa8 near miss: 4 -> 3 words, score 7 -> 5 (836 vs 840 bytes). port.py of gb func_00f429b0's round 35 draft; the prologue move now matches. Left: the func_00f69a20 address (lui/addiu a1) in v0 after the lw instead of v1 before it, the same as gb (see func_00f429b0 there for the -dS analysis and what was tried). Earlier header below. */
/* score 7 (4 words) after a permuter run on the score-43 draft (session 141). Left: `move s8,zero` vs `move s8,s7` in the prologue, and the D_00F69A20 address (lui/addiu) scheduled before the lw instead of after. Earlier header: */
/* score 43 (21 words; 836 vs 840 bytes). Modal picture viewer loop. Fixes so far: load w/h/bpp/addr into locals before func_00f471a0 (order addr, h, bpp, w), `nb++; nb &= 1;` (not (nb+1)&1, which combine turns into xori), D_0108F264 uses entry field +0, global init order brute-forced. Left: registers only - the hoisted %hi(0x109) pseudo for D_0108F26C lands in v1 instead of a0, which ripples to the 2 constant (a2) and &D_002C5AD0 (v1), a bnezl vs bnez at the loop top, and the func_00f69a20 address load order. */
typedef struct { s32 off; s16 w; s16 h; s32 x; s32 data; } GbClip;
typedef struct { s32 idx; s32 cur; s32 base; s32 bufs[2]; s32 a14; s32 id; } GbMovie;
typedef struct { u8 pad0[8]; u32 press; } GbPadState;
extern GbPadState D_002C5AD0;
extern GbClip *D_00FB4F30[];
extern s32 D_00FB4F40[];
extern s32 D_0108F248;
extern s32 D_0108F25C;
extern s32 D_0108F264;
extern s32 D_0108F268;
extern s32 D_0108F26C;
extern s32 D_0108F270;
extern s32 D_0108F274;
extern s32 D_0108F278;
void func_0011d768(s32);
void func_001bfac8(void);
s32 func_001c01b0(s32, void *);
s32 func_00f471a0(void);
void func_00f471b0(s32);
void func_00f66f78(s32, s32);
void func_00f693e0(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_00f699d8(s32);
void func_00f69a20(void);

void func_00f69aa8(GbMovie *m) {
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
    tbl = D_00FB4F30[m->idx];
    rgba[3] = 0;
    max = D_00FB4F40[m->idx];
    D_0108F278 = -1;
    D_0108F270 = 0;
    D_0108F26C = 0;
    D_0108F274 = -1;
    do {
        if (D_0108F26C == 0 && state != 2) {
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
            if (m->cur != D_0108F278) {
                if (D_0108F278 == -1)
                    func_0011d768(2);
                else
                    func_0011d768(1);
                D_0108F278 = m->cur;
                D_0108F264 = m->base + tbl[m->cur].off;
                D_0108F268 = m->bufs[buf];
                D_0108F26C = 1;
                buf++;
                buf &= 1;
                func_001c01b0(-1, func_00f69a20);
            }
        }
        if (D_0108F270 != 0) {
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
            if (D_0108F26C == 2)
                D_0108F26C = 0;
            D_0108F25C = m->a14;
            w = tbl[D_0108F274].w;
            h = tbl[D_0108F274].h;
            x = tbl[D_0108F274].x;
            addr = m->base + tbl[D_0108F274].data;
            gs = func_00f471a0();
            D_0108F248 = gs;
            func_00f693e0(D_0108F270, addr, 0, 0, w, h, x, rgba, 0, 0x44, 0, 0x5001D);
            func_00f699d8(0);
            func_00f471b0(D_0108F248);
            func_00f66f78(m->id, gs);
        }
        func_001bfac8();
        if ((D_002C5AD0.press & 1) && state == 1) {
            func_0011d768(3);
            state = 2;
        }
    } while (state != 3);
}
