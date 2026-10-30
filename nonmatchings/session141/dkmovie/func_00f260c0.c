/* Round 56 (wwm2): score 360 -> 207 (1108 vs 1152 bytes). The target is one switch over every type with case 0 in it, and the case bodies laid out 0x40, 0x50/0x51 (sltiu 82 / 80 in the decision tree), 0x1C30, 0x3860, 0x6400, 0xC800, 0x8000/0x8700, 0x3830/0x3F30. After the switch, `if (t == 0) { present } else f3DF34++`, so an unknown type also advances the clock (the old draft returned early). Left: the 0x40/0x50 bodies reload D_00F28460 and f3DD90 after computing p, and test f3DED8 as == 0 and then != 1 (ours folds that to one bne). Hoisting `p = 0` above the switch scores 193 but is 16 bytes further from the target's size. Earlier header below. */
/* dkmovie.x func_00f260c0: draft (session 141, round 28), structurally complete, not polished, 1104 vs 1152 bytes, 262 words differ, score 360 (m2c draft did not compile). Packet dispatcher: by the packet type word, hands audio blocks to the ADPCM/PCM converters, a type-0 packet presents the due picture (func_00f209d0), every other packet advances the clock f3DF34. */
#include "ovl.h"
#include "../nonmatchings/session141/dkmovie/movie_work.h"

s32 func_001ed920(void);
void func_00f209d0(s32, s32, s32, s32, MovieWork *, s32);
void func_00f20aa8(MovieWork *);
void func_00f211c8(u8 *, u8 *, s32, MovieWork *);
void func_00f213f0(u8 *, s32, MovieWork *);
void func_00f21478(u8 *, u8 *, s32, u8 *, MovieWork *);
void func_00f21500(u8 *, u8 *, s32, u8 *, MovieWork *);
void func_00f25fa0(void);
void func_00f26040(void);

void func_00f260c0(void) {
    s32 *h = (s32 *)D_00F28460->f3DD90;
    u32 t = h[0];
    u8 *p;
    s32 n;
    s32 sync;
    s32 i;
    s32 aux;

    switch (t) {
    case 0:
        break;
    case 0x40:
        p = 0;
        if (D_00F28460->f3DED8 != 0 && D_00F28460->f3DED8 == 1) {
            p = (u8 *)h + (h[1] + 15) / 16 * 16 + 0x10;
        }
        func_00f21478((u8 *)D_00F28460->f3DD90 + 0x10, D_00F28460->f1E900, h[1], p, D_00F28460);
        break;
    case 0x50:
    case 0x51:
        p = 0;
        if (D_00F28460->f3DED8 != 0 && D_00F28460->f3DED8 == 1) {
            p = (u8 *)h + h[2] - h[3] + 0x10;
        }
        func_00f21500((u8 *)D_00F28460->f3DD90 + 0x10, D_00F28460->f1E900, h[1], p, D_00F28460);
        break;
    case 0x1C30:
        func_00f211c8((u8 *)h + 0x10, D_00F28460->f1E900, 0, D_00F28460);
        break;
    case 0x3860:
        func_00f211c8((u8 *)h + D_00F28460->f3DED8 * 0x1C30 + 0x10, D_00F28460->f1E900, 0, D_00F28460);
        break;
    case 0x6400:
        func_00f213f0((u8 *)h + 0x10, 0, D_00F28460);
        break;
    case 0xC800:
        func_00f213f0((u8 *)h + D_00F28460->f3DED8 * 0x6400 + 0x10, 0, D_00F28460);
        break;
    case 0x8000:
    case 0x8700:
        func_00f26040();
        break;
    case 0x3830:
    case 0x3F30:
        func_00f25fa0();
        break;
    }
    if (t == 0) {
        if (D_00F28460->f3DF59 == 0 && (*(u64 *)&D_00F28460->f3DF58 & ((u64)0xFFFF << 40))) {
            n = D_00F28460->f3DF34;
            sync = n & 1;
            if (n >= 2) {
                sync = func_001ed920();
            }
            if (sync != -1) {
                i = 0;
                func_00f20aa8(D_00F28460);
                if (D_00F28460->f3DF38[0] == -1) {
                    i = 1;
                } else if (D_00F28460->f3DF38[1] < D_00F28460->f3DF38[0]) {
                    i = D_00F28460->f3DF38[1] >= 0;
                }
                if (D_00F28460->f3DF28 != 0 && D_00F28460->f3DF5B[i] != 0) {
                    aux = (s32)D_00F28460->aux[i];
                } else {
                    aux = 0;
                }
                func_00f209d0((s32)D_00F28460->pic[i], aux, 0, D_00F28460->f3DF38[i], D_00F28460, sync);
                D_00F28460->f3DF5D[i] = 0;
                D_00F28460->f3DF5B[i] = 0;
                D_00F28460->f3DF38[i] = -1;
            }
        }
    } else {
        D_00F28460->f3DF34++;
    }
}
