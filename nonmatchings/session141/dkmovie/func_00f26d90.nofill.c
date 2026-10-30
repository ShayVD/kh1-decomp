/* Round 57 (wwm2): score 192 -> 103 (788 vs 824 bytes). valaudit flagged func_00f23598's a2 as a reload of D_00F28460 in the target, where ours reused the cached m. Every statement after the first func_00f234e8 now reads D_00F28460 directly, including the slot step written as `f3DD40++; f3DD40 = f3DD40 % f3DF50;`. Left: the target saves s2 for arg0, keeps &D_00F28460 in s0/s1, and reloads D_00F28460 and f3DD48 after the store `f3DD48 = n` (ours tests n). The nostrict modes are worse (151/156). Earlier header below. */
/* Round 25 (wwm1): score 193 -> 192 with tools/ovl/storeperm.py (store-order sweep). */
/* Round 45 wwm2: score 200 -> 193 under the nofill build mode (tools/ovl/modescan.py). Earlier header below. */
/* dkmovie.x func_00f26d90: draft (session 141, round 28), structurally complete, not polished, 788 vs 824 bytes, 188 words differ, score 211 (m2c draft did not compile). Opens the stream (from the disc table or by name), copies the two 64-byte tables out, then primes slot f3DD40 and starts reading slot f3DD44. Round 19 (wwm1): score 211 -> 206 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 22 (wwm1): the if/else at line(s) 22 with the arms swapped and the test negated (ifswap.py): score 206 -> 200. */
#include "../nonmatchings/session141/dkmovie/movie_work.h"

s32 func_00f22048(s32, s32, s32, s32);
s32 func_00f22118(MovieWork *);
s32 func_00f27de8(s32, s32);
s32 func_00f27eb0(s32, MovieWork *);
s32 func_00f275e0(s32);
void func_00f234e8(s32, s32, s32, s32 *, MovieWork *);
void func_00f23598(s32, s32, MovieWork *);
void func_00f23480(void);
void FlushCache(s32);
extern u8 D_00F28690[];
extern u8 D_00F286D0[];

void func_00f26d90(s32 arg0, s32 arg1) {
    s32 n;
    MovieWork *m;
    s32 i;

    if (D_00F28460->f3DF51 != 0) {
        if (!(D_00F28460->f3DF52 != 0)) {
            func_00f22048(D_00F28460->f3DF00, D_00F28460->f3DF04, (s32)D_00F28460->f80, (s32)D_00F28460);
        } else {
            D_00F28460->f3DD48 = -1;
        }
    } else {
        func_00f27de8(arg1, (s32)D_00F28460->f80);
    }
    FlushCache(0);
    for (i = 0; i < 0x40; i++) {
        D_00F28690[i] = D_00F28460->f80[i];
        D_00F286D0[i] = D_00F28460->fC0[i];
    }
    FlushCache(0);
    if (D_00F28460->f3DF51 != 0) {
        n = func_00f22118(D_00F28460);
    } else {
        n = func_00f27eb0(arg0, D_00F28460);
    }
    D_00F28460->f3DD48 = n;
    if (D_00F28460->f3DD48 < 0) {
        for (;;) {
            func_00f23480();
        }
    }
    func_00f234e8(D_00F28460->f3DD48, func_00f275e0(D_00F28460->f3DD40), D_00F28460->f3DD5C[D_00F28460->f3DD40], &D_00F28460->f3DD68[D_00F28460->f3DD40], D_00F28460);
    func_00f23598(D_00F28460->f3DD48, 0, D_00F28460);
    D_00F28460->f3DD74[D_00F28460->f3DD40] = 2;
    D_00F28460->f3DD90 = D_00F28460->f3DD5C[D_00F28460->f3DD40];
    D_00F28460->f3DD40++;
    D_00F28460->f3DD40 = D_00F28460->f3DD40 % D_00F28460->f3DF50;
    D_00F28460->f3DD74[D_00F28460->f3DD40] = 1;
    FlushCache(0);
    n = func_00f275e0(D_00F28460->f3DD40);
    if (D_00F28460->f3DD50[D_00F28460->f3DD40] != D_00F28460->f3DD4C) {
        func_00f234e8(D_00F28460->f3DD48, n, D_00F28460->f3DD5C[D_00F28460->f3DD40], &D_00F28460->f3DD68[D_00F28460->f3DD40], D_00F28460);
    }
    D_00F28460->f3DD44 = D_00F28460->f3DD40;
}
