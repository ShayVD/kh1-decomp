/* 0010d470 near miss (natural): 170 words off by true DP LCS (orig unmatched; was 179 in s12w6), size 4120 vs 3968, hand strict, rodata RO=48cdf0.
   Only change vs s12w6__0010d470_179w_tlcs.c: both case-24 byte reads split as `c = str[pos]; c -= 25;` (main switch) and
   `c = sub[k]; c -= 25;` (copy loop): the original loads the byte straight into c (lbu t0). Everything else as s12w6
   (its header: c2 in a1 instead of a3, case 24/25 cross-jump, case 9 form, copy-loop registers).
   The unnatural 129w probe is s14m__0010d470_129w_finding.c. */
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

#define PUT_TAIL b->g[n].y = y; b->g[n].col = col; b->g[n].a = alpha; b->g[n].sc = scale; w += scale; n++;
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
    PUT_TAIL

void func_0010d470(TObj *o, TBuf *b) {
    char buf[64];
    s32 pos;
    s32 nl, cont, align, alpha;
    s32 x, y, n, k, m;
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
    if (fl & 4) alpha = 0; else alpha = 0x80;
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
                switch (c2 = str[pos]) {
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
                switch (c2 = str[pos]) {
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
                    {
                        s32 i = c2 - 32;
                        sub = func_00132f60(D_002BBAD0[i], D_002BBAE0[i]);
                    }
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
                m = n;
                while (c) {
                    if (c >= 0x20) {
                        code = c - 0x20;
                    } else {
                        switch (c) {
                        case 1:
                            break;
                        case 24:
                            k++;
                            c = sub[k];
                            c -= 25;
                            code = (c << 8) + 0xE0;
                            break;
                        case 25: case 26: case 27: case 28: case 29: case 30: case 31:
                            k++;
                            c -= 25;
                            code = (c << 8) + sub[k] + 0xE0;
                            break;
                        }
                    }
                    if (c == 1) {
                        b->g[m].code = 9999;
                        if (D_004D59E4 == 0) {
                            b->g[m].x = x;
                            x += fs * 12.0f + 0.0f;
                        } else {
                            b->g[m].x = x + (24.0f - WD(code) * fs) * 0.5f;
                            x += D_004D59E8;
                        }
                        b->g[m].w = x - o->x8; n++; b->g[n - 1].sc = scale; b->g[m].y = y; b->g[m].col = col; w += scale;
                    } else {
                        b->g[m].code = code;
                        if (D_004D59E4 == 0) {
                            b->g[m].x = x;
                            if (c == 0x20) x += WD(code) * fs;
                            else x += WD(code) * fs + 0.0f;
                            b->g[m].w = x - o->x8;
                        } else {
                            b->g[m].x = x + (24.0f - WD(code) * fs) * 0.5f;
                            x += D_004D59E8;
                        }
                        b->g[m].y = y;
                        w += scale;
                        b->g[m].col = col;
                        n++;
                        b->g[n - 1].sc = scale;
                    }
                    b->g[m].a = alpha;
                    m++;
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
                switch (c2 = str[pos]) {
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
                if (str[pos] == 0) {
                    s32 d;
                    pos++;
                    c2 = str[pos];
                    d = c2 / 10;
                    pos++;
                    scale = str[pos] + (f32)d;
                    if (scale == 0.0f) scale = 1e-6f;
                } else {
                    scale = o->x14;
                }
                break;
            case 24:
                pos++;
                c = str[pos];
                c -= 25;
                code = (c << 8) + 0xE0;
                PUT
                break;
            case 25: case 26: case 27: case 28: case 29: case 30: case 31:
                c -= 25;
                pos++;
                c2 = str[pos];
                code = (c << 8) + c2 + 0xE0;
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
    b->nl = nl;
    b->w = w;
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
