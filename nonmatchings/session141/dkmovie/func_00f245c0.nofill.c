/* Round 59 (wwm2): score 182 -> 118, building 2584 vs 2592 bytes. The 8-byte gap is not missing code. n is dropped around ++f3DD2C: f3DD50[f3DD40] is tested twice, as the target compares the loaded a1 both times. An empty case 2 gives the target's switch tree (== 1, then < 2, then != 0). Every remaining instruction matches except one copy of &D_00F28460, which lands in s1 where the target has s0, at the bnel after the f3DD2C compare. Because of that copy, reorg fills the branch-likely delay slot with the target label's lw a2,0(s1) and branches past it, which removes one instruction and one nop. The size-exact version (182) is func_00f245c0.exact.nofill.c. The last-frame break is the target's control flow: its 0x2000 test, its wait loop and its fall-through all branch to 0xf24f0c (jal func_00f25010) and skip the f3DD74[n] != 2 check and the flag-4 block. */
/* Round 58 (wwm2): score 380 -> 309 -> 252 -> 224 -> 182 (2592 vs 2592 bytes). The packet advance goes through n (n = size; n += 0x10; f3DD90 += n gives the target's s0), and the read slot is advanced with f3DD44++. The header fields are stored in the target's order (h is a u8 pointer, so each h[] load stays after the stores before it), and the 0x200 flag is set with |= and tested by re-reading f3DDD0. The 0x100 wait before playing is a do-while whose first test is flag 8 (to the end of the pass, so a goto) and whose loop test is 0x100, as the target lays it out (no copied exit test), and func_00f279f8 takes the height * 16 as a second argument (func_00f23750 passes two as well). The last-frame case (f3DD50[f3DD40] == f3DD4C) leaves the decode loop with a break: in the target its 0x2000 test and its wait loop both branch straight to the func_00f25010 call. The 0x40 wait loop after flag 4 tests 0x40 then 8 each pass, the restart test is two ifs (the target tests 8 and 0x80 separately instead of folding them to & 0x88), and f3DD74[n] = 0 is stored before f3DD40 is re-read. valaudit's call 15 flag is not a value difference: the target's a0 is D_00F28460 already, and the lw 0(s6) it reads is a nullified beqzl delay slot. Not taken: dropping n around ++f3DD2C (testing f3DD50[f3DD40] twice) scores 259 but builds 2572 bytes, because reorg then fills the branch-likely slots differently. Left: the gcse copies of &D_00F28460 (s0/s1/s8 placement) and the register choice. */
/* Round 57 wwm2: score 524 -> 380 at the same size. The cached `m = D_00F28460` copies are gone and every access reads D_00F28460 directly: the target reloads the pointer for each statement and passes the loaded value straight to func_00f23620 (valaudit's call 11/12 a0 flags). Left: call 15 (func_00f208b8) still takes a copy where the target loads, plus the register choice. Earlier header below. */
/* Round 45 wwm2: score 538 -> 524 under the nofill build mode (tools/ovl/modescan.py). Earlier header below. */
/* dkmovie.x func_00f245c0: draft (session 141, round 28), structurally complete, not polished, 2568 vs 2592 bytes, 632 words differ, score 608 (m2c output unusable). The demux task for MPEG-style movies: opens the stream (func_00f26d90), counts the frames, sets the picture size from the first header, then per packet decodes (func_00f25180 / func_00f260c0), keeps the three stream slots reading (f3DD44 read slot, f3DD40 decode slot), and stops on flag 8; flag 0x80 restarts the movie. Ends by setting 0x8000 and idling forever. Round 19 (wwm1): score 608 -> 538 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
#include "../nonmatchings/session141/dkmovie/movie_work.h"

void sceIpuInit(void); CONTEXT_ONLY void sceIpuInit() {}
void FlushCache(s32);
void func_001eda90(s32, s32);
void func_0024b1e8(void *, void *, s32);
void func_0024e468(s32);
void func_00f208b8(MovieWork *);
void func_00f20ae0(MovieWork *);
void func_00f23480(void); CONTEXT_ONLY void func_00f23480() {}
void func_00f23498(void); CONTEXT_ONLY void func_00f23498() {}
void func_00f234e8(s32, s32, s32, s32 *, MovieWork *);
void func_00f23598(s32, s32, MovieWork *);
s32 func_00f23620(MovieWork *);
void func_00f23650(void);
void func_00f25010(MovieWork *, s32);
void func_00f25180(void); CONTEXT_ONLY void func_00f25180() {}
void func_00f255f0(void);
void func_00f260c0(void); CONTEXT_ONLY void func_00f260c0() {}
void func_00f26be0(void); CONTEXT_ONLY void func_00f26be0() {}
void func_00f26d90(s8 *, s8 *);
s32 func_00f270c8(MovieWork *, s32, s32, s32);
s32 func_00f275e0(s32);
void func_00f279f8(s32, s32);
extern u8 D_00F28568[];
extern u8 D_00F28580[];

void func_00f245c0(void) {
    u8 *h;
    s32 n;
    s32 k;
    s32 r;
    s32 w, ht;
    s32 f;

    D_00F28460->f3DF52 = 0;
    sceIpuInit();
    for (;;) {
        func_00f26d90(D_00F28460->f3DDD4, D_00F28460->f3DE54);
        D_00F28460->f3DF67 = 0;
        D_00F28460->f3DF1C = 0;
        while (D_00F28460->size[D_00F28460->f3DF1C] != 0) {
            D_00F28460->f3DF1C++;
        }
        h = (u8 *)D_00F28460->f3DD90;
        w = h[11];
        D_00F28460->f3DD18 = w;
        w *= 16;
        ht = h[12];
        D_00F28460->f3DD1C = ht;
        D_00F28460->f3DD28 = h[13];
        D_00F28460->f3DD20 = w;
        D_00F28460->f3DD24 = ht * 16;
        func_00f279f8(w, ht * 16);
        D_00F28460->f3DDD0 |= 0x200;
        if (D_00F28460->f3DDD0 & 0x100) {
            do {
                if (D_00F28460->f3DDD0 & 8) {
                    goto stop;
                }
                func_00f23480();
            } while (D_00F28460->f3DDD0 & 0x100);
        }
        func_00f23650();
        func_00f26be0();
        do {
            func_00f25180();
            func_00f260c0();
            if (D_00F28460->f3DF67 == 0 && D_00F28460->f3DD2C == D_00F28460->f3DF1C - 30) {
                func_001eda90(0, 0xEF);
                D_00F28460->f3DF67 = 1;
            }
            func_00f255f0();
            n = ((s32 *)D_00F28460->f3DD90)[2];
            n += 0x10;
            D_00F28460->f3DD90 += n;
            func_00f23498();
            r = -1;
            if (D_00F28460->f3DD74[D_00F28460->f3DD44] == 1) {
                r = func_00f23620(D_00F28460);
                if (r == 0) {
                    D_00F28460->f3DD74[D_00F28460->f3DD44] = 2;
                    D_00F28460->f3DD44++;
                    D_00F28460->f3DD44 = D_00F28460->f3DD44 % D_00F28460->f3DF50;
                }
            }
            if (D_00F28460->f3DD74[D_00F28460->f3DD44] == 0) {
                if (r == -1) {
                    r = func_00f23620(D_00F28460);
                }
                if (r == 0) {
                    n = func_00f275e0(D_00F28460->f3DD44);
                    if (n != 0) {
                        func_00f234e8(D_00F28460->f3DD48, n, D_00F28460->f3DD5C[D_00F28460->f3DD44], &D_00F28460->f3DD68[D_00F28460->f3DD44], D_00F28460);
                        D_00F28460->f3DD74[D_00F28460->f3DD44] = 1;
                    }
                }
            }
            D_00F28460->f3DD2C++;
            if (D_00F28460->f3DD50[D_00F28460->f3DD40] == D_00F28460->f3DD2C) {
                if (D_00F28460->f3DD50[D_00F28460->f3DD40] == D_00F28460->f3DD4C) {
                    f = D_00F28460->f3DDD0 | 0x1000;
                    D_00F28460->f3DDD0 = f;
                    if (f & 0x2000) {
                        func_00f208b8(D_00F28460);
                        func_00f23480();
                        while (!(D_00F28460->f3DDD0 & 8)) {
                            func_00f255f0();
                            func_00f23480();
                        }
                    }
                    break;
                } else {
                    switch (D_00F28460->f3DD74[D_00F28460->f3DD40]) {
                    case 0:
                        n = func_00f275e0(D_00F28460->f3DD40);
                        if (n != 0) {
                            if (func_00f23620(D_00F28460) != 0) {
                                func_00f23598(D_00F28460->f3DD48, 1, D_00F28460);
                            }
                            func_00f234e8(D_00F28460->f3DD48, n, D_00F28460->f3DD5C[D_00F28460->f3DD40], &D_00F28460->f3DD68[D_00F28460->f3DD40], D_00F28460);
                            func_00f23598(D_00F28460->f3DD48, 1, D_00F28460);
                            D_00F28460->f3DD74[D_00F28460->f3DD40] = 2;
                        }
                        break;
                    case 1:
                        func_00f23598(D_00F28460->f3DD48, 1, D_00F28460);
                        D_00F28460->f3DD74[D_00F28460->f3DD40] = 2;
                        break;
                    case 2:
                        break;
                    }
                    if (D_00F28460->f3DD44 == D_00F28460->f3DD40) {
                        D_00F28460->f3DD44 = (D_00F28460->f3DD44 + 1) % D_00F28460->f3DF50;
                    }
                    FlushCache(0);
                    n = D_00F28460->f3DD40 - 1;
                    D_00F28460->f3DD90 = D_00F28460->f3DD5C[D_00F28460->f3DD40] + D_00F28460->f3DD68[D_00F28460->f3DD40];
                    if (n < 0) {
                        n = D_00F28460->f3DF50 - 1;
                    }
                    D_00F28460->f3DD74[n] = 0;
                    k = D_00F28460->f3DD40 + 1;
                    D_00F28460->f3DD40 = k;
                    D_00F28460->f3DD40 = k % D_00F28460->f3DF50;
                    if (D_00F28460->f3DD74[D_00F28460->f3DD44] == 0 && func_00f23620(D_00F28460) == 0) {
                        n = func_00f275e0(D_00F28460->f3DD44);
                        if (n != 0) {
                            func_00f234e8(D_00F28460->f3DD48, n, D_00F28460->f3DD5C[D_00F28460->f3DD44], &D_00F28460->f3DD68[D_00F28460->f3DD44], D_00F28460);
                            D_00F28460->f3DD74[D_00F28460->f3DD44] = 1;
                        }
                    }
                }
            }
            n = D_00F28460->f3DD40 - 1;
            if (n < 0) {
                n = D_00F28460->f3DF50 - 1;
            }
            if (D_00F28460->f3DD74[n] != 2) {
                __asm__ volatile("break");
            }
            k = D_00F28460->f3DDD0;
            D_00F28460->f3DDD0 = k | 4;
            if ((k | 4) & 0x4040) {
                D_00F28460->f3DDD0 = (k | 0x44) & ~0x4000;
                func_00f208b8(D_00F28460);
                func_00f23480();
                while (D_00F28460->f3DDD0 & 0x40) {
                    if (D_00F28460->f3DDD0 & 8) {
                        break;
                    }
                    func_00f255f0();
                    func_00f23480();
                }
            } else {
                func_00f20ae0(D_00F28460);
                func_00f23480();
            }
            if (*(s32 *)D_00F28460->f3DD14 != 0x12345678) {
                func_0024b1e8(D_00F28568, D_00F28580, 0x4B0);
            }
        } while (!(D_00F28460->f3DDD0 & 8));
stop:
        func_00f25010(D_00F28460, 1);
        f = D_00F28460->f3DDD0;
        if (f & 8) {
            break;
        }
        if (!(f & 0x80)) {
            break;
        }
        func_00f270c8(D_00F28460, 0, 0, D_00F28460->f3DF48);
    }
    D_00F28460->f3DEEC = 0;
    if (*(s32 *)D_00F28460->f3DD14 != 0x12345678) {
        func_0024b1e8(D_00F28568, D_00F28580, 0x4CA);
    }
    D_00F28460->f3DDD0 |= 0x8000;
    for (;;) {
        func_0024e468(1);
        D_00F28460->f3DDD0 |= 0x40000;
    }
}
