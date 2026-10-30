/* Round 36 (wgb): gb.x func_00f3b348 near miss: 94 -> 94 words, score 98 -> 92 (aligned diff 68 -> 62). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 94 words / score 98 (408 vs 432 bytes). The original copies the colour and position source pointers through extra registers (t0->a2->a0, t2->a3->a1) and reads each element from a different copy. It also keeps hi(D_00F82640) in s8 across the loop. Tried inline get/put helpers, a loop copy, and the nogcse and nostrict_nogcse modes. */
#include "ovl.h"

typedef struct { s32 v[3]; s32 pad; } GbRec;
extern GbRec D_00F82640[];
extern u8 D_00379F28[];
extern u8 *D_00F56DC0;
s32 func_00f39e90(void);
void func_001c01b0(s32, void *, ...);
void func_001bfac8(void);
void func_00f3b0b8();
void func_00f3b250();

void func_00f3b348(s32 id) {
    s32 pos[4];
    s32 col[4];
    s32 i;
    s32 c = func_00f39e90();
    u8 *src = &D_00379F28[c * 4];
    GbRec *r = &D_00F82640[id];
    col[0] = src[0] >> 1;
    pos[1] = r->v[1];
    col[2] = src[2] >> 1;
    col[1] = src[1] >> 1;
    pos[0] = r->v[0];
    pos[2] = r->v[2];
    D_00F56DC0[id] = c;
    for (i = 0; i < 30; i++) {
        switch (i) {
        case 0:
            func_001c01b0(-1, func_00f3b0b8, 0, col);
            break;
        case 6:
            func_001c01b0(-1, func_00f3b0b8, 1, col);
            break;
        case 12:
            func_001c01b0(-1, func_00f3b0b8, 2, col);
            break;
        case 18:
            func_001c01b0(-1, func_00f3b250, id, pos, col);
            break;
        }
        func_001bfac8();
    }
    r = &D_00F82640[id];
    r->v[1] = col[1];
    r->v[0] = col[0];
    r->v[2] = col[2];
}
