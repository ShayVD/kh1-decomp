/* dkmovie.x func_00f26d90: draft (session 141, round 28), structurally complete, not polished, 788 vs 824 bytes, 188 words differ, score 211 (m2c draft did not compile). Opens the stream (from the disc table or by name), copies the two 64-byte tables out, then primes slot f3DD40 and starts reading slot f3DD44. */
#include "ovl.h"
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
    MovieWork *m;
    s32 i;
    s32 n;

    if (D_00F28460->f3DF51 != 0) {
        if (D_00F28460->f3DF52 != 0) {
            D_00F28460->f3DD48 = -1;
        } else {
            func_00f22048(D_00F28460->f3DF00, D_00F28460->f3DF04, (s32)D_00F28460->f80, (s32)D_00F28460);
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
    m = D_00F28460;
    func_00f234e8(m->f3DD48, func_00f275e0(D_00F28460->f3DD40), m->f3DD5C[m->f3DD40], &m->f3DD68[m->f3DD40], m);
    m = D_00F28460;
    func_00f23598(m->f3DD48, 0, m);
    m = D_00F28460;
    m->f3DD74[m->f3DD40] = 2;
    n = m->f3DD40;
    m->f3DD40 = n + 1;
    m->f3DD90 = m->f3DD5C[n];
    m->f3DD40 = (n + 1) % m->f3DF50;
    m->f3DD74[m->f3DD40] = 1;
    FlushCache(0);
    m = D_00F28460;
    n = func_00f275e0(D_00F28460->f3DD40);
    if (m->f3DD50[m->f3DD40] != m->f3DD4C) {
        func_00f234e8(m->f3DD48, n, m->f3DD5C[m->f3DD40], &m->f3DD68[m->f3DD40], m);
    }
    D_00F28460->f3DD44 = D_00F28460->f3DD40;
}
