/* dkmovie.x func_00f25978: draft (session 141, round 28), structurally complete, not polished, 1552 vs 1576 bytes, 323 words differ, score 262 (m2c draft scored 549). IPU decode task for MPEG-style packets (the func_00f25658 sibling): per picture it reads the picture type from the IPU, for P/B pictures the motion vector pair, then runs the intra (type 2), predicted (type 1) or skipped (type 3) path through func_00f26540 / func_00f26848; type 4 ends the packet. */
#include "ovl.h"
#include "../nonmatchings/session141/dkmovie/movie_work.h"

typedef struct { s32 f0; u8 pad4[5]; u8 b9; u8 bA; u8 padB[3]; u8 bE; u8 bF; } MvPkt;
void func_00f269c0(s32, s32);
void func_00f26a20(s32, s32);
void func_00f26540(s32, s32, s32);
void func_00f26848(s32, s32, s32, s32);
#define D4b_CHCR (*(volatile u32 *)0x1000D400)

void func_00f25978(void) {
    MvPkt *h;
    s32 base;
    s32 size;
    s32 qs;
    s32 first;
    u8 fcode;
    s32 n;
    s32 type;
    s16 mx, my;
    s32 a, b, c;

    h = (MvPkt *)D_00F28460->f3DD90;
    first = 1;
    base = (h->bE << 20) + (((h->bF & 1) << 22) + ((h->bF >> 1) << 16));
    size = h->f0;
    qs = h->b9;
    fcode = h->bA;
    IPU_CTRL = base + 0x1200000;
    IPU_CTRL = (IPU_CTRL | 0x40000000) + base;
    while (IPU_CTRL < 0) {
    }
    n = -1;
    mx = 0;
    my = 0;
    D_00F28460->f3DD90 += 0x10;
    func_00f269c0(D_00F28460->f3DD90, size);
    for (;;) {
        n++;
        IPU_CMD = 0x30000000;
        while (IPU_CTRL < 0) {
        }
        type = IPU_CMD & 0xFFFF;
        if (type == 4) {
            break;
        }
        do {
            IPU_CMD = 0x30000000;
            while (IPU_CTRL < 0) {
            }
        } while ((IPU_CMD & 0xFFFF) == 0x23);
        if (type & 1) {
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            a = IPU_CMD;
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            b = IPU_CMD;
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            c = IPU_CMD;
            IPU_CMD = 0x38000000;
            mx = a * 16 + c;
            while (IPU_CTRL < 0) {
            }
            my = b * 16 + IPU_CMD;
        }
        switch (type) {
        case 1:
            func_00f26a20((s32)D_00F28464 + 0x70, 0x300);
            IPU_CTRL = base + 0x1000000;
            IPU_CMD = (fcode << 16) | 0x20000000;
            func_00f26540(n, mx, my);
            while (IPU_CTRL < 0) {
            }
            while ((D3_CHCR >> 8) & 1) {
            }
            while ((D4b_CHCR >> 8) & 1) {
            }
            while ((D1_CHCR >> 8) & 1) {
            }
            func_00f26848(n, mx, my, type);
            break;
        case 2:
            func_00f26a20((s32)D_00F28464 + 0x70, 0x300);
            a = first << 26;
            first = 0;
            IPU_CTRL = base + 0x1200000;
            IPU_CMD = a | (qs << 16) | 0x28000000;
            while (IPU_CTRL < 0) {
            }
            while ((D3_CHCR >> 8) & 1) {
            }
            while ((D4b_CHCR >> 8) & 1) {
            }
            while ((D1_CHCR >> 8) & 1) {
            }
            func_00f26848(n, 0, 0, type);
            break;
        case 3:
            func_00f26540(n, mx, my);
            while ((D4b_CHCR >> 8) & 1) {
            }
            func_00f26848(n, mx, my, type);
            while ((D1_CHCR >> 8) & 1) {
            }
            break;
        }
    }
    D4_CHCR = 0;
    IPU_CTRL = (IPU_CTRL | 0x40000000) + base;
    while (IPU_CTRL < 0) {
    }
    while ((D4_CHCR >> 8) & 1) {
    }
    while ((D1_CHCR >> 8) & 1) {
    }
    D_00F28460->f3DD90 += size;
}
