/* The text functions, first part (docs/modules.md "Session 36"),
 * 0x001ef950-0x001f0000; the module goes on after 0x001f0000.
 *
 * A message block is a header (MsgHdr: +0x10 the offset of a u16 offset
 * table, +0x14 the offset of the strings); message n (from 1) starts at
 * strings + offsets[n - 1].  func_001efb18 / func_001efb30 make a block
 * current (D_0063F744 strings, D_0063F748 offsets) and func_001efbb8 reads
 * from it; func_001efaf0 makes the built-in system messages current
 * (D_003E5ED8 / D_003E8910), which text.nofill.c's func_001efc10 reads
 * directly.  In a string, codes below 0x15 are control codes whose length is
 * D_003E8D28[code] (0 = end, 0x10 = new line), 0x15-0x1f take two bytes and
 * the rest one: func_001efd20 skips n lines, func_001efee8 counts the lines
 * and func_001effc0 the characters (code 10 inserts the string at the next
 * D_003E8E08 slot).  D_003E8E28 is the glyph table (D_003E8E2C entries,
 * func_001eff50 finds a code), set by func_001efaa8 with the default
 * D_003E4658.  func_001ef950 sends three images of the resource
 * func_001559f0(52, 12) to the GS.
 *
 * From 0x001f00d0 (session 37): the width of a string in pixels at size sc
 * (18 is the glyph table's own size): func_001f0148 for message strings,
 * func_001f0340 for two-byte strings, func_001f0448 for a number, and the
 * GIF packet builders.  A builder writes a header and one sprite per glyph
 * after pk and returns the end; func_001f0868 (text.nostrict_nofill.c)
 * draws a message string, func_001f0ea8 a two-byte string, func_001f12c0 an
 * ASCII one (D_003E8D40 maps it to glyphs), func_001f15f0 one glyph and
 * func_001f18e8 a number (all in text.nofill.c).  Mode 0/1/2 aligns x
 * left / right / centre; the end position is left in D_0063F74C /
 * D_0063F750, and D_0063F740 is the line height.  func_001f1fc8 and
 * func_001f2630 (still assembly) draw at once; func_001f2a50 ... func_001f2d68
 * build a packet in a scratch buffer and send it through path 2.
 * func_001f2eb8 (text.nofill.c) uploads the font image D_003E9660 and its
 * CLUT D_003F1660 and sets up the packet headers of D_003F1A70, D_003F1E70,
 * D_003F2270 and D_003F27D0; the text windows follow (textwin.c). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F2270.h"
#include "data/pieces/D_003E9660.h"
#include "data/pieces/D_003F1660.h"
#include "data/types/nofill_text_001f0000_h69.h" /* Q, a GIF packet quadword */

typedef kh1_s128 u128;
typedef struct { u8 pad[0x10]; s32 o10; s32 o14; } MsgHdr;

extern u8 D_003E4658[];
extern u8 D_003E5ED8[];
extern u16 D_003E8910[];
extern u8 D_003E8D28[];
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003E8E2C;
extern s32 D_0063F740;
extern u8 *D_0063F744;
extern u16 *D_0063F748;
extern u8 D_00490940[];
extern s32 D_0063F74C;


void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
s32 func_001205f0(void *, void *);
u64 *func_00122048(u32, u32);
void func_001220b8(void *);
void *func_001559f0(s32, s32);

void func_001efaf0(void);
void func_001efb18(u8 *s, u16 *o);
void func_001efb58(s32);
void func_001efb78(s32);
void func_001efb98(s32);
u8 *func_001efbb8(s32);
u8 *func_001efc10(s32);
u8 *func_001efc68(u16 *o, u8 *s, s32 i);
u8 *func_001efd20(u8 *p, s32 n);
s32 func_001efdb8(u8 *p);
s32 func_001efee8(u8 *p);
s32 func_001effc0(u8 *s);
s32 func_001f0148(u8 *s, s32 sz);
s32 func_001f0340(u8 *p, s32 scale);
s32 func_001f0448(s32 n, s32 pad, s32 val, s32 w);
Q *func_001f07d8(Q *pk, s32 a1, s32 mode, s32 color, s32 x, s32 y, s32 id, s32 sc);
Q *func_001f0868(Q *pk, s32 a1, s32 mode, s32 color, s32 x, s32 y, u8 *str, s32 sc);
Q *func_001f0ea8(Q *pk, s32 a1, s32 mode, u32 color, s32 x, s32 y, u8 *str, s32 sc);
Q *func_001f12c0(Q *p, s32 a1, u32 color, s32 x, s32 y, u8 *str, s32 sc);
Q *func_001f15f0(Q *p, s32 a1, u32 color, s32 x, s32 y, s32 glyph, s32 sc);
Q *func_001f18e8(Q *p, s32 a1, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sc, u32 col);
s32 func_001f1f58(s32 mode, s32 color, s32 x, s32 y, s32 id, s32 sc);
s32 func_001f1fc8(s32 mode, s32 color, s32 x, s32 y, u8 *str, s32 sc);
s32 func_001f2630(s32 mode, u32 color, s32 x, s32 y, u8 *str, s32 sc);

void func_001ef950(void)
{
    u128 b[11];
    u128 a[11];
    u8 *p;

    p = func_001559f0(52, 12);
    func_001205f0(D_00490940, p);
    func_0011fbb0(16380, 1, 0, 0, 0, 16, 16, 64, p + 0x10000, a);
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), a);
    PlatGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 36, 0, 0, 256, 256, 2048, p, b);
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), b);
    PlatGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 44, 0, 0, 256, 256, 2048, p + 0x8000, b);
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), b);
    PlatGsSyncPath(0, 0);
}

void func_001efaa8(void) {
    D_003E8E28 = (Glyph_3e8e28 *)D_003E4658;
    D_003E8E2C = 0x310;
    func_001efb58(0x14);
    func_001efb78(0);
    func_001efb98(0);
    func_001efaf0();
}

void func_001efaf0(void) {
    func_001efb18(D_003E5ED8, D_003E8910);
}

void func_001efb18(u8 *s, u16 *o) {
    D_0063F744 = s;
    D_0063F748 = o;
}

void func_001efb30(MsgHdr *h) {
    D_0063F744 = (u8 *)h + h->o14;
    D_0063F748 = (u16 *)((u8 *)h + h->o10);
}

void func_001efb58(s32 arg0) {
    D_0063F740 = arg0 * 0x10;
}

s32 func_001efb68(void) {
    return (s32) D_0063F740 >> 4;
}

void func_001efb78(s32 arg0) {
    D_003E8E00 = arg0;
}

s32 func_001efb88(void) {
    return D_003E8E00;
}

void func_001efb98(s32 arg0) {
    D_003E8E04 = arg0;
}

s32 func_001efba8(void) {
    return D_003E8E04;
}

u8 *func_001efbb8(s32 a) {
    return D_0063F744 + D_0063F748[a - 1];
}

u8 *func_001efbe0(s32 id, s32 n) {
    return func_001efd20(func_001efbb8(id), n);
}

u8 *func_001efc38(s32 id, s32 n) {
    return func_001efd20(func_001efc10(id), n);
}

u8 *func_001efc68(u16 *o, u8 *s, s32 i) {
    return s + o[i - 1];
}

u8 *func_001efc80(u16 *o, u8 *s, s32 i, s32 n) {
    return func_001efd20(func_001efc68(o, s, i), n);
}

u8 *func_001efcb0(MsgHdr *h, s32 a) {
    u16 *o = (u16 *)((u8 *)h + h->o10);
    return (u8 *)h + h->o14 + o[a - 1];
}

u8 *func_001efcd8(MsgHdr *h, s32 a, s32 n) {
    u8 *t = (u8 *)h + h->o14;
    return func_001efd20(func_001efc68((u16 *)((u8 *)h + h->o10), t, a), n);
}

u8 *func_001efd20(u8 *p, s32 n) {
    if (n == 0) return p;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
            case 0:
                return p;
            case 16:
                p++;
                if (--n == 0) return p;
                break;
            default:
                p += D_003E8D28[*p];
                break;
            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001efd98(s32 id) {
    return func_001efdb8(func_001efbb8(id));
}

s32 func_001efdb8(u8 *p) {
    s32 n = 0;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
case 0:
 return n;
case 2:
 p++;
 n++;
 break;
case 16:
 return n;
case 3:
 p += 2;
 n++;
 break;
default:
 p += D_003E8D28[*p];
 break;

            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001efe68(s32 id) {
    return func_001efd98(id) + 1;
}

s32 func_001efe88(u8 *p) {
    return func_001efdb8(p) + 1;
}

s32 func_001efea8(s32 id) {
    return func_001efee8(func_001efbb8(id));
}

s32 func_001efec8(u16 *o, u8 *s, s32 i) {
    return func_001efee8(func_001efc68(o, s, i));
}

s32 func_001efee8(u8 *p) {
    s32 n = 1;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
            case 0:
                return n;
            case 16:
                p++;
                n++;
                break;
            default:
                p += D_003E8D28[*p];
                break;
            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001eff50(s32 a) {
    s32 i;
    Glyph_3e8e28 *e = D_003E8E28;
    for (i = 0; i < D_003E8E2C; i++, e++) {
        if (e->code == a) return i;
    }
    return 0;
}

s32 func_001effa0(s32 id) {
    return func_001effc0(func_001efbb8(id));
}

/* rodata: jump table at 0x490960 */
s32 func_001effc0(u8 *s) {
    s32 n = 0;
    u8 **tbl = ((u8 **)&D_003E8E08);
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                n++;
                s++;
                break;
            case 4:
                s++;
                break;
            case 5:
                s++;
                break;
            case 6:
                s++;
                break;
            case 9:
                s++;
                break;
            case 10:
                if (tbl[0]) n += func_001effc0(tbl[0]);
                tbl++;
                s++;
                break;
            case 11:
                tbl++;
                s += 4;
                break;
            case 8:
                s += 5;
                break;
            case 7:
                s += 2;
                break;
            case 12:
                s += 2;
                break;
            case 15:
                s += 2;
                break;
            case 13:
                s += 3;
                break;
            case 14:
                s += 3;
                break;
            case 17:
                s += 3;
                break;
            case 18:
                s += 3;
                break;
            case 19:
                s += 3;
                break;
            case 20:
                s += 3;
                break;
            case 0: case 2: case 3: case 16:
                return n;
            default:
                s++;
                break;
            }
        } else {
            if (*s == 24) s += 2;
            else s = (*s < 32) ? s + 2 : s + 1;
            n++;
        }
    }
}

s32 func_001f00d0(s32 id) {
    return func_001f0118(id, 18);
}

s32 func_001f00e8(u8 *s) {
    return func_001f0148(s, 18);
}

s32 func_001f0100(u8 *p) {
    return func_001f0340(p, 18);
}

s32 func_001f0118(s32 id, s32 sz) {
    return func_001f0148(func_001efbb8(id), sz);
}

/* rodata (jump table at 0x004909c0) */
s32 func_001f0148(u8 *s, s32 sz)
{
    s32 w = 0;
    u8 **a = ((u8 **)&D_003E8E08);
    s32 c;
    Glyph_3e8e28 *g;

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
                s += 2;
                break;
            case 15:
                s += 2;
                break;
            case 10:
                if (*a) w += func_001f0148(*a, sz) << 4;
                a++;
                s++;
                break;
            case 4:
                s++;
                break;
            case 5:
                s++;
                break;
            case 6:
                s++;
                break;
            case 9:
                s++;
                break;
            case 11:
                w += func_001f0448(s[2], s[3], (s32)*a, sz) << 4;
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
                s += 3;
                break;
            case 17:
                s += 3;
                break;
            case 18:
                s += 3;
                break;
            case 19:
                s += 3;
                break;
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

s32 func_001f0340(u8 *p, s32 scale) {
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
            Glyph_3e8e28 *g = &D_003E8E28[func_001eff50(k)];
            x += ((g->w << 4) + func_001efb88()) * scale / d;
        }
    }
}

/* The width of a number of n digits (0: as many as it has), zero-padded
 * when pad is set.  The q-loop divides by a local `ten` set before the pad
 * test. */
s32 func_001f0448(s32 n, s32 pad, s32 val, s32 w) {
    s32 buf[10];
    s32 neg = 0;
    s32 cnt;
    s32 i;
    s32 ws = w * 16;
    if (val == 0) {
        if (n == 0 || pad == 0) {
            buf[0] = 0;
            cnt = 1;
        } else {
            for (i = n - 1; i >= 0; i--) buf[i] = 0;
            cnt = n;
        }
    } else {
        if (val < 0) { val = -val; neg = 1; }
        if (n == 0) {
            cnt = 0;
            do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < 10);
        } else {
            s32 ten;
            cnt = 0;
            ten = 10;
            if (pad == 0) {
                do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < n);
            } else {
                s32 *q = buf; do { if (val == 0) { *q = 0; q++; cnt++; } else { cnt++; *q = val % ten; val /= ten; q++; } } while (cnt < n);
            }
        }
    }
    return (cnt + neg) * (ws + func_001efba8()) >> 4;
}

u8 func_001f05e8(s32 i) {
    return D_003E8E28[i].w;
}

s32 func_001f0600(s32 i, s32 b) {
    return ((D_003E8E28[i].w << 4) * b / 18) >> 4;
}

Q *func_001f0638(Q *pk, s32 a1, s32 color, s32 x, s32 y, u8 *str) {
    return func_001f0868(pk, a1, 0, color, x, y, str, 14);
}

Q *func_001f0670(Q *pk, s32 a1, s32 color, s32 x, s32 y, s32 id) {
    return func_001f07d8(pk, a1, 0, color, x, y, id, 18);
}

Q *func_001f06a8(Q *pk, s32 a1, s32 color, s32 x, s32 y, u8 *str) {
    return func_001f0868(pk, a1, 0, color, x, y, str, 18);
}

Q *func_001f06e0(Q *pk, s32 a1, s32 color, s32 x, s32 y, u8 *str) {
    return func_001f0ea8(pk, a1, 0, color, x, y, str, 18);
}

Q *func_001f0718(Q *pk, s32 a1, s32 color, s32 x, s32 y, s32 id, s32 sc) {
    return func_001f07d8(pk, a1, 0, color, x, y, id, sc);
}

Q *func_001f0758(Q *pk, s32 a1, s32 color, s32 x, s32 y, u8 *str, s32 sc) {
    return func_001f0868(pk, a1, 0, color, x, y, str, sc);
}

Q *func_001f0798(Q *pk, s32 a1, s32 color, s32 x, s32 y, u8 *str, s32 sc) {
    return func_001f0ea8(pk, a1, 0, color, x, y, str, sc);
}

Q *func_001f07d8(Q *pk, s32 a1, s32 mode, s32 color, s32 x, s32 y, s32 id, s32 sc) {
    return func_001f0868(pk, a1, mode, color, x, y, func_001efbb8(id), sc);
}

/* func_001f0868 is in text.nostrict_nofill.c; func_001f0ea8, func_001f12c0
 * and func_001f15f0 in text.nofill.c. */

Q *func_001f1868(Q *p, s32 a1, u32 color, s32 x, s32 y, s32 code, s32 sc) {
    return func_001f15f0(p, a1, color, x, y, func_001eff50(code), sc);
}

/* func_001f18e8 is in text.nofill.c. */

s32 func_001f1df0(s32 color, s32 x, s32 y, s32 id) {
    return func_001f1f58(0, color, x, y, id, 14);
}

s32 func_001f1e28(s32 color, s32 x, s32 y, u8 *str) {
    return func_001f1fc8(0, color, x, y, str, 14);
}

s32 func_001f1e60(u32 color, s32 x, s32 y, u8 *str) {
    return func_001f2630(0, color, x, y, str, 14);
}

s32 func_001f1e98(s32 color, s32 x, s32 y, s32 id, s32 sc) {
    return func_001f1f58(0, color, x, y, id, sc);
}

s32 func_001f1ed8(s32 color, s32 x, s32 y, u8 *str, s32 sc) {
    return func_001f1fc8(0, color, x, y, str, sc);
}

s32 func_001f1f18(u32 color, s32 x, s32 y, u8 *str, s32 sc) {
    return func_001f2630(0, color, x, y, str, sc);
}

s32 func_001f1f58(s32 mode, s32 color, s32 x, s32 y, s32 id, s32 sc) {
    return func_001f1fc8(mode, color, x, y, func_001efbb8(id), sc);
}

/* func_001f1fc8 and func_001f2630 are not matched (nonmatchings/session7,
 * session23-match). */

s32 func_001f2a50(u32 color, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *buf;
    void *u;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(0x1000, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f12c0((Q *)(buf + 2), 1, color, x, y, str, sc) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2b58(u32 color, s32 x, s32 y, s32 glyph, s32 sc) {
    u64 *buf;
    void *u;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(0x400, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f15f0((Q *)(buf + 2), 1, color, x, y, glyph, sc) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2c60(u32 color, s32 x, s32 y, s32 code, s32 sc) {
    u64 *buf;
    void *u;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(0x400, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f1868((Q *)(buf + 2), 1, color, x, y, code, sc) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2d68(s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sc, u32 col) {
    u64 *buf;
    void *u;
    u64 *p;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    p = func_00122048(0x400, 0x80);
    buf = p;
    p += 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f18e8((Q *)p, 1, mode, nd, pad, x, y, val, sc, col) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

void func_001f2e98(Q **img, Q **clut) {
    *img = D_003E9660;
    *clut = D_003F1660;
}

/* func_001f2eb8 is in text.nofill.c. */
