/* 0010d470: 338 words off by LCS in mode hand (strict) with the session-6 draft unchanged (430 in hand/nostrict, the mode the draft was saved for; 3840 vs 3968 bytes in hand, 4088 in nostrict). rodata 0x48cdf0 via rr.py. In hand the loop-top pos reload (lw 64(sp)) and the prologue match; left: the original duplicates the glyph-PUT tail (move v0,v1 pointer copies, b 0x10e348/0x10e354 partial-reload entry points) where ours cross-jumps, and the second PUT copy at 0x10e1d8 is missing. */
/* func_0010d470: far (946 words differ by position; LCS sequence diff 180 of 992 insns, size 1022 vs 992), mode hand/nostrict (strict is far worse), rodata 0x48cdf0 ("%d" + jtbl_0048CE00/CE80, via rr.py). Full structure is in place: all 32 main cases + 36-entry case-14 sub-switch and copy loop. Remaining: (1) pos (sp+64) handling. The orig reloads pos at each case start and has a partial reload at the loop end (E348/E34C/E350/E354 entry points). Ours keeps the loop-top pos load in a register, gcse-style. (2) Crossjump differences: the orig does not merge the c==0x20/else tails in the main PUT or the case-2 y+=fs*37/28 copies, but merges case 25-31 into case 24 midway. Ours merges differently. (3) Glyph field store scheduling (orig uses two pointer copies, move v0,v1). Table D_004D5300 == D_00495280.w (+0x40080). */
#include "common.h"
typedef struct { u8 pad0[4]; u8 *x4; u16 x8; u16 xa; u8 padc[4]; u8 x10; u8 pad11[2]; u8 x13; f32 x14; f32 x18; f32 x1c; } TObj;
typedef struct { u16 code; u16 col; u16 x; u16 y; s16 w; s16 a; f32 sc; } TGl;
typedef struct { u16 n; s16 nl; f32 w; s32 x8; u8 pad[1]; u8 xd; u8 pade[2]; TGl g[384]; f32 lw[16]; f32 lk[16]; } TBuf;
typedef struct { u8 pad[0x40080]; s8 w[1]; } WTab;
extern WTab D_00495280;
extern s32 D_004D5AF0;
extern s32 D_004D59E4;
extern s32 D_004D59E8;
extern s32 D_004D59F0[];
extern s32 D_002BBAB0, D_002BBAB4, D_002BBAB8, D_002BBABC, D_002BBAC0, D_002BBAC4, D_002BBAC8;
extern s32 D_002BBAD0[], D_002BBAE0[];
extern s32 D_003C5830[];
extern s8 D_002BB610[];
void func_0010d138(TObj *, TBuf *);
void func_0010d230(TObj *, TBuf *);
s32 func_0010d350(u8 *);
void func_0010d388(char *, const char *, ...);
s16 func_0010d438(s32 *, u8 *);
u8 *func_00132f48(s32);
u8 *func_00132f60(s32, s32);
u8 *func_00147760(s32);
u8 *func_00147808(u16);
u16 *func_00147840(s32);
struct S4 { s32 x0; u8 *x4; };
struct S4 *func_001478a0(s32);
u8 *func_001ba228(s32);
u8 *func_001eafd8(void);
s32 func_001ef7a0(void);

#define WD(c) D_00495280.w[c]

#define PUT \
    b->g[n].code = code; \
    if (D_004D59E4 == 0) { \
        b->g[n].x = x; \
        if (c == 0x20) x += WD(code) * fs; \
        else x += WD(code) * fs + 0.0f; \
        b->g[n].w = x - o->x8; \
    } else { \
        b->g[n].x = x + (24.0f - WD(code) * fs) * 0.5f; \
        x += D_004D59E8; \
    } \
    g = &b->g[n++]; \
    w += scale; \
    g->a = alpha; \
    g->sc = scale; \
    g->y = y; \
    g->col = col;

void func_0010d470(TObj *o, TBuf *b) {
    char buf[64];
    s32 pos;
    s32 nl, cont, align, alpha;
    s32 x, y, n, k;
    u8 *str;
    u8 *sub;
    u16 code;
    u8 c;
    u8 c2;
    s32 col;
    u8 fl;
    f32 w, scale, fs, v;
    TGl *g;

    code = 0;
    sub = 0;
    n = 0;
    D_004D5AF0 = 0;
    fl = o->x13;
    nl = 0;
    alpha = (fl & 4) ? 0 : 0x80;
    x = o->x8;
    y = o->xa;
    str = o->x4;
    col = o->x10;
    if (fl & 2) {
        b->xd = 20;
        fs = 0.8333330154f;
        D_004D59E8 = 18;
    } else {
        b->xd = 24;
        fs = 1.0f;
        D_004D59E8 = 20;
    }
    if (o->x14 == 0.0f) o->x14 = 1e-6f;
    D_004D59E4 = 0;
    w = 0.0f;
    align = 0;
    cont = 1;
    pos = 0;
    scale = o->x14;
    do {
        c = str[pos];
        if (c >= 0x20) {
            code = c - 0x20;
            PUT
        } else {
            switch (c) {
            case 4:
                D_004D59F0[D_004D5AF0++] = x - o->x8;
                b->lk[nl] = 123456.0f;
                b->lw[nl] = w;
                nl++;
                cont = 0;
                break;
            case 0:
                cont = 0;
                D_004D59F0[D_004D5AF0++] = x - o->x8;
                break;
            case 1:
                b->g[n].code = 9999;
                if (D_004D59E4 == 0) {
                    b->g[n].x = x;
                    x += fs * 12.0f + 0.0f;
                } else {
                    b->g[n].x = x + (24.0f - WD(code) * fs) * 0.5f;
                    x += D_004D59E8;
                }
                g = &b->g[n];
                g->a = alpha;
                w += scale;
                g->w = x - o->x8;
                n++;
                g->sc = scale;
                g->y = y;
                g->col = col;
                break;
            case 2:
                D_004D59F0[D_004D5AF0++] = x - o->x8;
                x = o->x8;
                if (o->x13 & 8) y += fs * 37.0f;
                else y += fs * 28.0f;
                break;
            case 3:
                b->lk[nl] = 123456.0f;
                b->lw[nl] = w;
                nl++;
                break;
            case 5:
                b->lk[nl] = (f32)func_0010d438(&pos, str) + 1000000.0f;
                b->lw[nl] = w;
                nl++;
                break;
            case 6:
                b->lk[nl] = func_0010d438(&pos, str);
                b->lw[nl] = w;
                nl++;
                break;
            case 7:
                y += func_0010d438(&pos, str);
                break;
            case 11:
                pos++;
                switch (str[pos]) {
                case 0:
                    x += func_0010d438(&pos, str);
                    break;
                case 1:
                    x = o->x8 + func_0010d438(&pos, str);
                    break;
                }
                break;
            case 13:
                pos++;
                switch (str[pos]) {
                case 0:
                    alpha = o->x18 = 128 / func_0010d438(&pos, str);
                    break;
                case 1:
                    v = func_0010d438(&pos, str);
                    o->x1c = -128.0f / v;
                    b->lk[nl] = v + 2000000.0f;
                    b->lw[nl] = w;
                    nl++;
                    break;
                }
                break;
            case 14:
                pos++;
                switch (c2 = str[pos]) {
                case 0:
                    func_0010d388(buf, "%d", func_001ef7a0());
                    sub = buf;
                    break;
                case 1:
                    sub = func_00147808(*func_00147840(D_002BBAB0));
                    func_0010d350(sub);
                    break;
                case 2:
                    sub = func_001ba228(D_002BBAB4);
                    func_0010d350(sub);
                    break;
                case 3:
                    sub = func_001eafd8();
                    func_0010d350(sub);
                    break;
                case 4:
                    sub = func_001478a0(D_002BBAB8)->x4;
                    func_0010d350(sub);
                    break;
                case 5:
                    sub = func_00132f60(D_002BBABC, D_002BBAC0);
                    func_0010d350(sub);
                    break;
                case 32: case 33: case 34: case 35:
                    sub = func_00132f60(D_002BBAD0[c2 - 32], D_002BBAE0[c2 - 32]);
                    func_0010d350(sub);
                    break;
                case 6:
                    sub = func_00132f48(D_002BBAC4);
                    func_0010d350(sub);
                    break;
                case 7:
                    sub = func_00147760(D_002BBAC8);
                    func_0010d350(sub);
                    break;
                case 16: case 17: case 18: case 19:
                case 20: case 21: case 22: case 23:
                    func_0010d388(buf, "%d", D_003C5830[c2]);
                    sub = buf;
                    break;
                }
                k = 0;
                c = *sub;
                g = &b->g[n];
                while (c) {
                    if (c >= 0x20) {
                        code = c - 0x20;
                    } else if (c == 0x18) {
                        k++;
                        c = sub[k] - 25;
                        code = (c << 8) + 0xE0;
                    } else if (c >= 25) {
                        if (c < 32) {
                            k++;
                            c -= 25;
                            code = (c << 8) + sub[k] + 0xE0;
                        }
                    }
                    if (c == 1) {
                        b->g[n].code = 9999;
                        if (D_004D59E4 == 0) {
                            b->g[n].x = x;
                            x += fs * 12.0f + 0.0f;
                        } else {
                            b->g[n].x = x + (24.0f - WD(code) * fs) * 0.5f;
                            x += D_004D59E8;
                        }
                        b->g[n].y = y;
                        w += scale;
                        b->g[n].col = col;
                        b->g[n].w = x - o->x8;
                        b->g[n].sc = scale;
                        n++;
                    } else {
                        b->g[n].code = code;
                        if (D_004D59E4 == 0) {
                            b->g[n].x = x;
                            if (c == 0x20) x += WD(code) * fs;
                            else x += WD(code) * fs + 0.0f;
                            b->g[n].w = x - o->x8;
                        } else {
                            b->g[n].x = x + (24.0f - WD(code) * fs) * 0.5f;
                            x += D_004D59E8;
                        }
                        b->g[n].y = y;
                        w += scale;
                        b->g[n].col = col;
                        b->g[n].sc = scale;
                        n++;
                    }
                    b->g[n - 1].a = alpha;
                    k++;
                    c = sub[k];
                }
                break;
            case 12:
                pos++;
                col = str[pos];
                if (col == 255) col = o->x10;
                break;
            case 8:
                align = 1;
                break;
            case 15:
                pos++;
                switch (str[pos]) {
                case 1:
                    break;
                case 0:
                    align = 2;
                    break;
                case 2:
                    D_004D59E4 = 1;
                    break;
                case 3:
                    D_004D59E4 = 0;
                    break;
                }
                break;
            case 9:
                w += scale;
                pos++;
                c2 = str[pos];
                g = &b->g[n];
                n++;
                g->x = x;
                code = c2 + 10000;
                g->code = code;
                g->sc = scale;
                x += D_002BB610[c2];
                g->y = y;
                g->a = alpha;
                g->w = x - o->x8;
                g->col = col;
                break;
            case 10:
                pos++;
                if (str[pos]) {
                    scale = o->x14;
                } else {
                    s32 d;
                    pos++;
                    d = str[pos] / 10;
                    pos++;
                    scale = str[pos] + (f32)d;
                    if (scale == 0.0f) scale = 1e-6f;
                }
                break;
            case 24:
                pos++;
                c = str[pos] - 25;
                code = (c << 8) + 0xE0;
                PUT
                break;
            case 25: case 26: case 27: case 28: case 29: case 30: case 31:
                c -= 25;
                pos++;
                code = (c << 8) + str[pos] + 0xE0;
                PUT
                break;
            case 16: case 17: case 18: case 19:
            case 20: case 21: case 22: case 23:
                break;
            }
        }
        pos++;
    } while (cont);
    b->n = n;
    b->w = w;
    b->nl = nl;
    b->x8 = 0;
    switch (align) {
    case 1:
        func_0010d138(o, b);
        break;
    case 2:
        func_0010d230(o, b);
        break;
    }
}
