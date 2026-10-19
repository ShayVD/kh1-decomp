/* 001f1fc8 13w LCS, hand/nofill, RO=00490a80, context as session11/w32__001f1fc8_2w.c (2w best stays s11w32). FINDING (s11w65): plain constants, source order d0 d1 col x3c x40(f2+w) x44(f4+288) x50 x54 x58 x20 x24 x38 one x30 x34 x5c: f2/f4 die at x20/x24 and 0x100000 at x38, so all of them sit in sched1's weight -1 group and 'one' issues right after x38 and before x30, as in the original (no hoisted k1 needed). Left: x58 (weight 0 now) issues after x30, plus the li/local-alloc register permutation. sched2 keeps sched1 order for every store of tier A (d0 col one x3c x44 x54 x58 x30 x20 x24 x38 share one dependent count with the original registers), so the original sched1 order must be d0 col x3c x44 x54 x58 x20 x24 x38 one x30: that needs both 0x100000 stores (x58 and x38) in the weight -1 group, impossible with one pseudo, or x30 (5 dependents: anti dep on cx += adv) ranked below one/x38. */
/* 001f1fc8 2w LCS (9 positional), hand/nofill, rodata 00490a80 (RO=00490a80 lc_s11.py), context as session7/w32__001f1fc8_5w.c. Glyph store block in plain struct-offset order (d0,d1,col,one,x20..x5c); hc climbs from it find nothing better. Left: sd a1,24 (one=1) issues 3rd (orig after x38) and sw s6,48 (x30) after x58 instead of after one. Hoisting the 1 (u64 k1 = 1 before the loop; loop.c moves it, reload rematerialises li a1,1) puts one after x38 exactly as orig, and 22 hoisted puts d1 late like orig, so the original probably had these constants loop-invariant; but climbs of that shape stop at 11 (block regs). */
/* rodata */ /* func_001f1fc8: 5 words off in hand/nostrict_nofill (rr.py 00490a80; was 10w in hand/nofill). Header order hill-climbed in nostrict_nofill fixes the a3/t0 constant regs. Left: glyph store order, sd one(24) issued too early (orig after x38), col(16)/x54(84) later than orig. */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef struct {
    u64 d[2];
    u64 col, one;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
    s32 x50, x54, x58, x5c;
} Gl;
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_003E8E08[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;
extern u8 D_003F2270[];

extern s32 D_003E8E00;
extern s32 D_003E8E04;
CONTEXT_ONLY void func_001efb78(s32 arg0) { D_003E8E00 = arg0; }
CONTEXT_ONLY s32 func_001efb88(void) { return D_003E8E00; }
CONTEXT_ONLY void func_001efb98(s32 arg0) { D_003E8E04 = arg0; }
s32 func_001f0448(s32, s32, u8 *, s32);
CONTEXT_ONLY s32 func_001f0148(u8 *s, s32 sz)
{
    s32 w = 0;
    u8 **a = (u8 **)D_003E8E08;
    s32 c;
    Glyph *g;

    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                w += (sz << 8) / 18;
                s++;
                break;
            case 12:
                sz = s[1];
                s += 2;
                break;
            case 7:
            case 15:
                s += 2;
                break;
            case 10:
                if (*a) w += func_001f0148(*a, sz) << 4;
                a++;
                s++;
                break;
            case 4:
            case 5:
            case 6:
            case 9:
                s++;
                break;
            case 11:
                w += func_001f0448(s[2], s[3], *a, sz) << 4;
                a++;
                s += 4;
                break;
            case 13:
                w += (s16)(s[1] | (s[2] << 8)) * sz * 16 / 18;
                s += 3;
                break;
            case 8:
                s += 5;
                break;
            case 14:
            case 17:
            case 18:
            case 19:
            case 20:
                s += 3;
                break;
            case 0:
            case 2:
            case 3:
            case 16:
                return w >> 4;
            default:
                s++;
                break;
            }
        } else {
            if (*s == 24) {
                c = (s[1] << 8) - 0x1820;
                s += 2;
            } else if (*s < 32) {
                c = ((s[0] << 8) | s[1]) - 0x1820;
                s += 2;
            } else {
                c = *s - 32;
                s++;
            }
            g = &D_003E8E28[c];
            w += ((g->w << 4) + func_001efb88()) * sz / 18;
        }
    }
}

s32 func_00266c08(s32);
void func_00266f38(s32, u32);
s32 sceGsSyncPath(s32, s32);
u8 *func_00122048(s32, s32);
void func_001220b8(u8 *);
s32 func_001f2d68(s32, s32, s32, s32, s32, s32, s32, s32);

#define SETX() \
    switch (mode) { \
    case 0: \
    default: \
        cx = x * 16 + 0x7000; \
        break; \
    case 1: \
        cx = (x - func_001f0148(str, sc)) * 16 + 0x7000; \
        break; \
    case 2: \
        cx = (x - func_001f0148(str, sc) / 2) * 16 + 0x7000; \
        break; \
    }

s32 func_001f1fc8(s32 mode, s32 color, s32 x, s32 y, u8 *str, s32 sc) {
/*D*/
    u8 *buf;
    u32 ua;
    u64 *d;
    Q *p;
    Gl *g;
    Glyph *gl;
    s32 cx, cy, k, w, s, h, adv;
    s32 *argp;
    s32 defcol;
    s32 f2, f4;
    u8 f7;
/*E*/

    func_001efb78(0); /*FIX*/
    h = sc << 4;
    func_001efb98(0); /*FIX*/
    func_00266f38(func_00266c08(2), (u32)D_003F2270); /*FIX*/
    buf = func_00122048(1024, 128); /*FIX*/
    ua = ((u32)buf & 0x0fffffff) | 0x80000000;
    p = (Q *)(buf + 16);
    d = (u64 *)p;
    d[0] = 0x1000000000000003;
    d[1] = 14;
    d[3] = 63;
    d[4] = 0x4007ff8001300000;
    cy = y * 16 + 0x7400;
    defcol = color;
    d[2] = 0;
    d[5] = 22;
    d[6] = 68;
    d[7] = 66;
    d[8] = 0x60ab400000008001;
    d[9] = 0x4343ee;
    p = (Q *)(buf + 96);
    *(u64 *)buf = 0x7000000b;
    argp = D_003E8E08;
    SETX();
    for (;;) {
        if (*str < 21) {
            switch (*str) {
            case 0:
            case 16:
                goto done;
            case 1:
                str++;
                cx += (sc << 8) / 18;
                break;
            case 3:
                str++;
                D_0063F740 = *str << 4;
            case 2:
                str++;
                cy += D_0063F740;
                SETX();
                break;
            case 4: str++; mode = 0; break;
            case 5: str++; mode = 1; break;
            case 6: str++; mode = 2; break;
            case 7:
                if (str[1]) color = D_003E8D00[str[1] + 1];
                else color = defcol;
                str += 2;
                break;
            case 8:
                color = str[1] | (str[2] << 8) | (str[3] << 16) | (str[4] << 24);
                str += 5;
                break;
            case 9:
                str++;
                color = *argp++;
                break;
            case 10:
                if (*argp) {
                    cx = func_001f1fc8(0, color, cx >> 4, cy >> 4, (u8 *)*argp, sc) << 4;
                    cy = D_0063F750 << 4;
                }
                str++;
                argp++;
                break;
            case 11:
                cx = func_001f2d68(str[1], str[2], str[3], cx >> 4, cy >> 4, *argp, sc, color) << 4;
                argp++;
                str += 4;
                cy = D_0063F750 << 4;
                break;
            case 12:
                sc = str[1];
                str += 2;
                h = sc << 4;
                break;
            case 13:
                cx += (s16)(str[1] | (str[2] << 8)) << 4;
                str += 3;
                break;
            case 14:
                cy += (s16)(str[1] | (str[2] << 8)) << 4;
                str += 3;
                break;
            case 15: str += 2; break;
            case 17:
            case 19:
                x = (s16)(str[1] | (str[2] << 8));
                str += 3;
                cx = x * 16 + 0x7000;
                break;
            case 18:
            case 20:
                cy = ((s16)(str[1] | (str[2] << 8)) << 4) + 0x7400;
                str += 3;
                break;
            default:
                str++;
                break;
            }
        } else {
            if (*str == 24) {
                k = (str[1] << 8) - 0x1820;
                str += 2;
            } else if (*str < 32) {
                k = ((str[0] << 8) | str[1]) - 0x1820;
                str += 2;
            } else {
                k = *str - 32;
                str++;
            }
            gl = &D_003E8E28[k];
            w = gl->w << 4;
            s = w * sc / 18;
            adv = (w + func_001efb88()) * sc / 18;
/*P*/
            f2 = gl->f2;
            f4 = gl->f4;
            g = (Gl *)p;
            f7 = gl->f7;
            g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
            g->d[1] = 22;
            g->col = (u32)color;
            g->x3c = 0x8000;
            g->x40 = f2 + w;
            g->x44 = f4 + 288;
            g->x50 = cx + s;
            g->x54 = cy + h;
            g->x58 = 0x100000;
            g->x20 = f2;
            g->x24 = f4;
            g->x30 = cx;
            g->x34 = cy;
            g->x38 = 0x100000;
            g->one = 1;
            g->x5c = 0;
/*Q*/
            func_00266f38(func_00266c08(2), ua);
            cx += adv;
            sceGsSyncPath(0, 0);
        }
    }
done:
    func_001220b8(buf);
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return D_0063F74C;
}
