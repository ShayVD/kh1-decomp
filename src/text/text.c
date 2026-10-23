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
 * func_001559f0(52, 12) to the GS. */
#include "common.h"
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003E8E08.h"

typedef int u128 __attribute__((mode(TI)));
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

void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
s32 func_001205f0(void *, void *);
void *func_001559f0(s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);

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

void func_001ef950(void)
{
    u128 b[11];
    u128 a[11];
    u8 *p;

    p = func_001559f0(52, 12);
    func_001205f0(D_00490940, p);
    func_0011fbb0(16380, 1, 0, 0, 0, 16, 16, 64, p + 0x10000, a);
    FlushCache(0);
    func_00266f38(func_00266c08(2), a);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 36, 0, 0, 256, 256, 2048, p, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 44, 0, 0, 256, 256, 2048, p + 0x8000, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
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
