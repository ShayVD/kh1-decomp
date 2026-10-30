/* Round 57 (wwm2): 224 -> 112. The motion vectors are read as the target builds them: mx = IPU_CMD << 4; my = IPU_CMD << 4; mx += IPU_CMD; my += IPU_CMD; on s16 mx/my (sll 20 / sra 16, then sll 16 / sra 16). The extra refs give mx/my the target's s3/s2 and n s5. Round 56 (wwm2): score 256 -> 226 -> 224 (1568 vs 1576 bytes; 224 from hill3, 360 s, which moved the qs/fcode/first/n set-up and the type 2 command build; valaudit's callee sequence now matches). After func_00f26848 in the type 1 and type 2 paths, the target tests IPU_CTRL bit 14 and on a clear bit reads IPU_CTRL once more, discarding the value. With that test in both cases they cross-jump into one func_00f26848 call, as in the target (the old draft had one call too many). Left: register choice (s2-s6 for n, mx, my and the IPU pointers) and the prologue schedule. Earlier header below. */
/* dkmovie.x func_00f25978: draft (session 141, round 28), structurally complete, not polished, 1552 vs 1576 bytes, 323 words differ, score 262 (m2c draft scored 549). IPU decode task for MPEG-style packets (the func_00f25658 sibling): per picture it reads the picture type from the IPU, for P/B pictures the motion vector pair, then runs the intra (type 2), predicted (type 1) or skipped (type 3) path through func_00f26540 / func_00f26848; type 4 ends the packet. Round 19 (wwm1): score 262 -> 256 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
#include "../nonmatchings/session141/dkmovie/movie_work.h"

typedef struct { s32 f0; u8 pad4[5]; u8 b9; u8 bA; u8 padB[3]; u8 bE; u8 bF; } MvPkt;
void func_00f269c0(s32, s32);
void func_00f26a20(s32, s32);
void func_00f26540(s32, s32, s32);
void func_00f26848(s32, s32, s32, s32);
#define D4b_CHCR (*(volatile u32 *)0x1000D400)

void func_00f25978(void) {
    s32 base;
    s32 type;
    MvPkt *h;
    s32 qs;
    s32 n;
    s16 mx, my;
    u8 fcode;
    s32 size;
    s32 first;
    s32 a, b, c;

    h = (MvPkt *)D_00F28460->f3DD90;
    qs = h->b9;
    base = (h->bE << 20) + (((h->bF & 1) << 22) + ((h->bF >> 1) << 16));
    size = h->f0;
    fcode = h->bA;
    first = 1;
    IPU_CTRL = base + 0x1200000;
    IPU_CTRL = (IPU_CTRL | 0x40000000) + base;
    while (IPU_CTRL < 0) {
    }
    my = 0;
    D_00F28460->f3DD90 += 0x10;
    n = -1;
    mx = 0;
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
            mx = IPU_CMD << 4;
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            my = IPU_CMD << 4;
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            mx += IPU_CMD;
            IPU_CMD = 0x38000000;
            while (IPU_CTRL < 0) {
            }
            my += IPU_CMD;
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
            if (!((IPU_CTRL >> 14) & 1)) {
                (void)IPU_CTRL;
            }
            break;
        case 2:
            func_00f26a20((s32)D_00F28464 + 0x70, 0x300);
            IPU_CTRL = base + 0x1200000;
            a = first << 26;
            first = 0;
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
            if (!((IPU_CTRL >> 14) & 1)) {
                (void)IPU_CTRL;
            }
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
