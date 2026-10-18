/* func_0024be88: 167 words off (right size) in hand; 130 with -fno-cse-follow-jumps -freduce-all-givs. Off: lui-hoisted global address regs s5/s6/s7 permuted (A560/A548/A544), loop hoists constant 7 into s8 where orig rematerializes li 7; the else-if (D_0046A544 == 1) reuses the earlier A544 load (orig reloads; -fno-cse-follow-jumps fixes that part). */
#include "common.h"
typedef struct { u32 w; } BEnt;
typedef struct { s16 lo; s16 id; } BEntH;
extern s32 D_0046A540;
extern s32 D_0046A544;
extern s32 D_0046A548;
extern s32 D_0046A54C;
extern s32 D_0046A550;
extern s32 D_0046A554;
extern s32 D_0046A558;
extern s32 D_0046A55C;
extern s32 D_0046A560;
extern u32 *D_0046A568[];
extern s16 D_00669A40[8];
extern s32 D_00669A58;
extern s32 D_00669A70;
s32 func_0024be58(void);
s32 func_0024be70(void);
s32 func_0024bc68(s32, s32);
void func_0024bce8(s32 *, s32 *);
void func_0011d768(s32);
s32 func_001f0600(s32, s32);
void func_001fade0(void *, s32, s32, s32, s32, u32);
void func_001fefc8(void *, s32, s32, s32, s32);

void func_0024be88(void *a0)
{
    s32 old;
    s32 snd;
    s32 max;
    s32 n;
    u32 *p;
    s16 id;
    u32 w;
    s32 col, row, off, x, y, x2;
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
            D_0046A554 = 4;
            D_0046A544 = 0;
            D_0046A548 = 4;
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
        }
        if (D_0046A54C != 0 && D_0046A544 == 1) {
            D_0046A554 = D_0046A548;
        }
        snd = 1;
        D_0046A54C = D_0046A544;
        D_0046A550 = D_0046A548;
    }
    if (D_0046A544 == 0) {
        if (D_0046A548 == 3) D_0046A558 = 1;
        if (D_0046A548 == 4) D_0046A560 = 1;
    }
    p = D_0046A568[D_0046A540];
    while (((BEntH *)p)->id != -10) {
        id = ((BEntH *)p)->id;
        w = *p;
        col = (w >> 4) & 0xf;
        row = (w >> 8) & 0xf;
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
        x = (col * 2 + ((s32)(*p << 28) >> 28)) * 16;
        y = row * 32 + 156;
        x2 = x + 127;
        if (id > 0) func_001fade0(a0, x2 + off, y + D_00669A70, id, 15, color);
        if (color == 0x8036F040 && D_0046A544 != 0)
            func_001fefc8(a0, x + 123, y + D_00669A70 - 4, 26, 26);
        p++;
    }
    if (snd == 1) func_0011d768(1);
    if (snd == 2) func_0011d768(3);
    if (snd == 3) func_0011d768(2);
}
