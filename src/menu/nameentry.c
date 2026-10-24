/* The name-entry screen (docs/modules.md "Session 47"),
 * 0x0024bc68-0x0024d4a0 except nameentry.nofill.c's func_0024c950 (the name
 * line and the two buttons).  A five-page character grid (D_0046A540 the
 * page, the L1/R1 bits 0x400/0x800 turn it; D_0046A568 each page's cells,
 * ended by -10, with -1 an empty one) and a cursor (D_0046A544,
 * D_0046A548; func_0024bce8 snaps it to the nearest cell); up to eight
 * characters in D_00669A40 (-1 empty, D_00669A58 the next).  Column 0 holds
 * "end" (D_0046A560) and, in the full-screen mode (D_00669A5C == 0), a
 * second button (D_0046A558).  func_0024d1c8 starts it (a starting name,
 * the save slot D_00669A60, a mode); func_0024cfa0 runs a frame;
 * func_0024cf00 writes the name into the slot (func_001bc4e0) through
 * func_0024ce80 (characters to the game's text code, func_0024cde8 the
 * reverse); func_0024d418 starts it from the current name (func_001eafd8)
 * with func_0024d138 its close.  Read from the code and the layout; not
 * proved by a boot. */
#include "common.h"
#include "data/bss_0066.h"
#include "data/bss_0066_mixed.h"
#include "data/data_0046.h"
#include "data/pieces/D_0046A568.h"

typedef union { u32 w; struct { s16 a; s16 b; } h; } E;
typedef struct { s32 dx:4; u32 col:4; u32 row:4; u32 pad:4; s32 id:16; } BF;
typedef struct { s32 a; s8 s[92]; } Slot;
typedef struct { u8 pad[0x60]; Slot slot[1]; } SaveHdr;

extern u32 D_002C5AD8;
extern u32 D_002C5AE0;

void func_0011d768(s32);
void func_0011ef10(s32, void *);
void func_00114820(void);
void func_00114830(void);
void func_001ba2a8(s32, s32);
SaveHdr *func_001bc4e0(void);
s32 func_001be010(s32);
void func_001be3c0(s32);
u8 *func_001eafd8(void);
void func_001efaf0(void);
void func_001efb18(void *, void *);
s32 func_001f0600(s32, s32);
s32 func_001f31a8(void *, s32); /* s32, not void, for func_0024d1c8 */
s32 func_001f3840(void *);
s32 func_001f40c8(void);
void func_001f82b0(void);
void func_001f8f30(void);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fade0(void *, s32, s32, s32, s32, u32);
void func_001fefc8(void *, s32, s32, s32, s32);
void func_002014a0(void *, s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_0024c8b8(void *, s16 *, s32, s32, s32, s32);
/* nameentry.nofill.c */
void func_0024c950(void *);

s32 func_0024bc68(u32 a0, u32 a1) {
    u32 *p = D_0046A568[D_0046A540];
    while (((s16 *)p)[1] != -10) {
        if (((s16 *)p)[1] == -1 && a0 == ((*p >> 4) & 0xf) && a1 == ((*p >> 8) & 0xf)) return 1;
        p++;
    }
    return 0;
}

/* *px / *py are re-read at the end (gcse copies of the first loads,
 * numbered after the -10 pseudo, so -10 wins the global-alloc tie). */
void func_0024bce8(s32 *px, s32 *py) {
    s32 x = *px;
    s32 y = *py;
    s32 dx, dy = 0;
    s32 i;
    E *e;
    if (x == D_0046A54C) {
        dx = (y == D_0046A550) ? -1 : 0;
    } else {
        dx = 1; if (x < D_0046A54C) dx = -1;
    }
    if (y != D_0046A550) {
        dy = 1; if (y < D_0046A550) dy = -1;
    }
    for (i = 0; i < 12; i++) {
        for (e = ((E **)&D_0046A568)[D_0046A540]; e->h.b != -10; e++) {
            if (e->h.b != -1 && x == ((e->w >> 4) & 15) && y == ((e->w >> 8) & 15)) {
                *px = x;
                *py = y;
                return;
            }
        }
        x += dx;
        y += dy;
    }
    if (*px == 0) {
        if (D_00669A5C == 0) {
            if ((u32)*py < 3) {
                *px = 0;
                *py = 3;
                return;
            }
        } else if ((u32)*py < 4) {
            *px = 0;
            *py = 4;
            return;
        }
    }
    *px = D_0046A54C;
    *py = D_0046A550;
}

s32 func_0024be58(void) {
    return D_002C5AD8 | (((u32) D_002C5AD8 >> 0x18) & 0xF0);
}

s32 func_0024be70(void) {
    return D_002C5AE0 | (((u32) D_002C5AE0 >> 0x18) & 0xF0);
}

/* The cells are bitfield structs (BF: a signed 4-bit dx, col, row, an s16
 * id); the empty do-while stands for a compiled-out assert at the start of
 * the D_0046A54C != 0 branch (it stops cse following the jump). */
void func_0024be88(void *a0)
{
    s32 old;
    s32 snd;
    s32 max;
    s32 n;
    BF *p;
    s16 id;
    s32 col, row, off, x;
    u32 color;

    old = D_0046A540;
    D_0046A560 = 0;
    max = old == 4 ? 11 : 10;
    snd = 0;
    D_0046A558 = 0;
    if (D_0046A55C == 0) {
        if (func_0024be58() & 0x800) {
            if (++D_0046A540 >= 5) D_0046A540 = 0;
        }
        if (func_0024be58() & 0x400) {
            if (--D_0046A540 < 0) D_0046A540 = 4;
        }
        if (D_0046A540 != old) func_0011d768(1);
    }
    if (D_0046A544 > max) D_0046A544 = max;
    if (D_0046A544 < 0) D_0046A544 = 0;
    if (func_0024bc68(D_0046A544, D_0046A548)) func_0024bce8(&D_0046A544, &D_0046A548);
    if (D_0046A55C == 0) {
        while (!(func_0024be70() & 0x20)) {
            if (func_0024be70() & 0x80) {
                if (--D_0046A544 < 0) D_0046A544 = 0;
            } else if (func_0024be70() & 0x40) {
                if (++D_0046A548 >= 5) D_0046A548 = 4;
            } else if (func_0024be70() & 0x10) {
                if (--D_0046A548 < 0) D_0046A548 = 0;
            }
            goto done;
        }
        if (++D_0046A544 > max) D_0046A544 = max;
    done:
        if (func_0024be58() & 8) {
            D_0046A544 = 0;
            D_0046A548 = 4;
            D_0046A554 = 4;
        }
    }
    func_0024bce8(&D_0046A544, &D_0046A548);
    if ((func_0024be58() & 0x4000) && D_0046A55C == 0) {
        if (D_00669A58 == 7 && D_00669A40[D_00669A58] != -1) {
            D_00669A40[D_00669A58] = -1;
        } else {
            n = D_00669A58 - 1;
            if (n < 0) n = 0;
            D_00669A58 = n;
            D_00669A40[n] = -1;
        }
        snd = 2;
    }
    if (D_0046A54C != D_0046A544 || D_0046A550 != D_0046A548) {
        if (D_0046A54C == 0) {
            if (D_0046A550 != D_0046A548) D_0046A554 = D_0046A548;
            if (D_0046A544 == 1 && (u32)(D_0046A550 - 3) < 2) D_0046A548 = D_0046A554;
        } else {
            do { } while (0);
            if (D_0046A544 == 1) D_0046A554 = D_0046A548;
        }
        snd = 1;
        D_0046A54C = D_0046A544;
        D_0046A550 = D_0046A548;
    }
    if (D_0046A544 == 0) {
        if (D_0046A548 == 3) D_0046A558 = 1;
        if (D_0046A548 == 4) D_0046A560 = 1;
    }
    p = (BF *)D_0046A568[D_0046A540];
    while (p->id != -10) {
        id = p->id;
        col = p->col;
        row = p->row;
        color = 0x80808080;
        if (D_0046A544 == col && D_0046A548 == row) {
            color = 0x8036F040;
            if ((func_0024be58() & 0x2000) && D_0046A55C == 0 && id >= 0 && D_0046A544 != 0) {
                if (D_00669A58 < 8) {
                    D_00669A40[D_00669A58] = id;
                    if (++D_00669A58 >= 8) D_00669A58 = 7;
                    snd = 3;
                }
            }
        }
        if (id > 0) {
            off = func_001f0600(id, 15);
            if (off < 7) off = 7 - off / 2;
            else off = 0;
        } else off = 0;
        x = (col * 2 + p->dx) * 16;
        row = row * 32 + 156;
        col = x + 127;
        if (id > 0) func_001fade0(a0, col + off, row + D_00669A70, id, 15, color);
        if (color == 0x8036F040 && D_0046A544 != 0)
            func_001fefc8(a0, x + 123, row + D_00669A70 - 4, 26, 26);
        p++;
    }
    if (snd == 1) func_0011d768(1);
    if (snd == 2) func_0011d768(3);
    if (snd == 3) func_0011d768(2);
}

void func_0024c460(void *a) {
    s32 c[2];
    s32 w[2] = { 17, 15 };
    s32 col[5] = { 0x0CFB8D2A, 0x0CF29829, 0x0CDFB128, 0x0CCBCB27, 0x0CC2D726 };
    s32 x, i, k;
    x = 156 - w[0];
    func_00206130(a, 0, x + D_00669A70, 512, 173, 0x59191202);
    if (D_00669A5C)
        func_00206130(a, 0, x + 173, 512, 211 - x, 0x59191202);
    c[0] = 0x4C00509A;
    c[1] = 0x4C2998FF;
    func_00206130(a, 187, D_00669A78 + 325, 47, 17, c[D_0046A540 == 0]);
    func_00206130(a, 239, D_00669A78 + 325, 47, 17, c[D_0046A540 == 1]);
    func_00206130(a, 291, D_00669A78 + 325, 47, 17, c[D_0046A540 == 2]);
    func_00206130(a, 343, D_00669A78 + 325, 47, 17, c[D_0046A540 == 3]);
    func_00206130(a, 395, D_00669A78 + 325, 47, 17, c[D_0046A540 == 4]);
    func_0024c8b8(a, D_0046A580, 189, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A588, 241, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A590, 293, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A598, 345, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A5A0, 397, D_00669A78 + 326, 14, 0x4F000000);
    func_001efb18(D_0046A080, D_0046A0C0);
    func_001f9438(a, 0, 147, D_00669A78 + 352, 2, 14, 0x4CFFFFFF);
    for (i = 0; i < 11; i++) {
        if (i & 1)
            func_00206130(a, 0, x + D_00669A70, 512, w[i & 1], col[i / 2]);
        x += w[i & 1];
    }
    func_00206130(a, 0, D_00669A70 - w[0] + 156, 512, 2, 0x80784040);
    func_001efb18(D_0046A080, D_0046A0C0);
    k = D_00669A5C ? 3 : 1;
    func_002014a0(a, 2, 2, 12, D_00669A70 + 127, 120, 70, D_0046A5A8, k, 16);
    func_00206130(a, 0, D_00669A70 - w[0] + 329, 512, 2, 0x80784040);
}

void func_0024c8b8(void *a0, s16 *p, s32 x, s32 y, s32 dx, s32 a5) {
    s32 i;
    for (i = 0; p[i] >= 0; i++) {
        func_001fade0(a0, x, y, p[i], dx, a5);
        x += dx;
    }
}

void func_0024cde8(u16 *d, u8 *s) {
    s32 i = 0;
    while (s[i] != 0) {
        u32 c = s[i];
        if (c == 1) {
            c = 0;
        } else if (c - 32 < 224) {
            c = c - 32;
        } else {
            if (c == 24) { c = s[i + 1]; c -= 25; c <<= 8; }
            else { c -= 25; c <<= 8; c += s[i + 1]; }
            c += 224;
            i++;
        }
        *d++ = c;
        i++;
    }
}

void func_0024ce80(u8 *d, s16 *s) {
    s32 i, n = 0;
    s32 c;
    for (i = 0; i < 8 && (c = *s) >= 0; i++) {
        if (c == 0) c = 1;
        else { c += 32; if (c >= 256) { c += 0x1800; d[n++] = c >> 8; } }
        s++;
        d[n++] = c;
    }
    d[n] = 0;
}

void func_0024cf00(void) {
    Slot *p = &func_001bc4e0()->slot[D_00669A60];
    s32 i;
    for (i = 0; p->s[i + 48] != 0; i++) p->s[i + 48] = 0;
    func_0024ce80((u8 *)p + 52, D_00669A40);
}

s32 func_0024cf80(void) {
    return D_0046A5D8;
}

s32 func_0024cf90(void) {
    return D_00669A7C;
}

void func_0024cfa0(void *a) {
    s32 i;
    func_0024c460(a);
    func_0024be88(a);
    func_0024c950(a);
    func_001f8f30();
    if (D_0046A558 != 0 && (func_0024be58() & 0x2000)) {
        s32 *p = &D_0046A55C;
        if (*p == 0) {
            *p = 1;
            func_0011d768(2);
            func_001f3840(a);
            D_0046A5D8 = 0;
            return;
        }
    }
    if (!(func_0024be58() & 0x2000)) return;
    if (D_0046A55C != 0) return;
    if (D_0046A560 == 0) return;
    for (i = 0; i < 8; i++) {
        if (D_00669A40[i] == -1) continue;
        if (D_00669A40[i] != 0) break;
    }
    if (i == 8) {
        func_0011d768(4);
        return;
    }
    D_0046A5D8 = 1;
    D_0046A55C = 1;
    func_0011d768(2);
    func_001f3840(a);
    if (D_00669A60 < 0) return;
    func_0024cf00();
    if (D_00669A64 != 0) {
        D_00669A7C = func_001be010(D_00669A60);
        return;
    }
    func_001be3c0(D_00669A60);
}

s32 func_0024d138(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        return 0;
    }
    func_0024ce80(func_001eafd8(), D_00669A40);
    if (D_00669A5C != 0) {
        func_001ba2a8(0, (s32)func_001eafd8());
    }
    D_0046A53C = 1;
    func_00114830();
    func_001efaf0();
    return 4;
}

void func_0024d1c8(s16 *src, s32 a, s32 b, s32 c) {
    s32 i;
    s32 *pp = &c;
    func_00114820();
    D_00669A7C = -1;
    D_0046A55C = 0;
    D_00669A68 = 0;
    D_00669A6C = 0;
    D_00669A60 = a;
    D_00669A64 = b;
    D_00669A5C = c;
    if (c == 0) {
        D_00669A70 = -28;
        D_00669A74 = -16;
        D_00669A78 = -3;
        D_0046A112 = 0;
        D_0046A1F2 = 0;
        D_0046A2D2 = 0;
        D_0046A3B2 = 0;
        D_0046A4DA = 0;
    } else {
        D_00669A70 = 0;
        D_00669A74 = 0;
        D_00669A78 = 0;
        D_0046A112 = -1;
        D_0046A1F2 = -1;
        D_0046A2D2 = -1;
        D_0046A3B2 = -1;
        D_0046A4DA = -1;
    }
    D_00669A58 = 0;
    for (i = 0; i < 8; i++) D_00669A40[i] = -1;
    if (src != NULL) {
        for (i = 0; i < 8; i++) {
            D_00669A40[i] = src[i];
            if (src[i] < 0) break;
            D_00669A58++;
        }
    }
    if (D_00669A58 == 8) D_00669A58 = 7;
    D_0046A540 = 0;
    D_0046A544 = 1;
    D_0046A548 = 0;
    D_0046A54C = 1;
    D_0046A554 = D_0046A550 = 0;
    D_0046A560 = 0;
    D_0046A558 = 0;
    D_0046A5BC = 20;
    D_0046A53C = 0;
    func_001f31a8(D_0046A5E0, 1);
}

s32 func_0024d408(void) {
    return D_0046A55C;
}

void func_0024d418(void) {
    s16 buf[16];
    s32 i;
    func_0011ef10(0x2BFE8, func_0024d138);
    for (i = 0; i < 9; i++) buf[i] = -1;
    func_0024cde8((u16 *)buf, func_001eafd8());
    func_0024d1c8(buf, -1, 0, 1);
}

s32 func_0024d490(void) {
    return D_0046A53C;
}
