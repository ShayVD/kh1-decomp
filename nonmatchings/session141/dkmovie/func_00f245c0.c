/* dkmovie.x func_00f245c0: draft (session 141, round 28), structurally complete, not polished, 2568 vs 2592 bytes, 632 words differ, score 608 (m2c output unusable). The demux task for MPEG-style movies: opens the stream (func_00f26d90), counts the frames, sets the picture size from the first header, then per packet decodes (func_00f25180 / func_00f260c0), keeps the three stream slots reading (f3DD44 read slot, f3DD40 decode slot), and stops on flag 8; flag 0x80 restarts the movie. Ends by setting 0x8000 and idling forever. */
#include "ovl.h"
#include "../nonmatchings/session141/dkmovie/movie_work.h"

void sceIpuInit(void);
void FlushCache(s32);
void func_001eda90(s32, s32);
void func_0024b1e8(void *, void *, s32);
void func_0024e468(s32);
void func_00f208b8(MovieWork *);
void func_00f20ae0(MovieWork *);
void func_00f23480(void);
void func_00f23498(void);
void func_00f234e8(s32, s32, s32, s32 *, MovieWork *);
void func_00f23598(s32, s32, MovieWork *);
s32 func_00f23620(MovieWork *);
void func_00f23650(void);
void func_00f25010(MovieWork *, s32);
void func_00f25180(void);
void func_00f255f0(void);
void func_00f260c0(void);
void func_00f26be0(void);
void func_00f26d90(s8 *, s8 *);
s32 func_00f270c8(MovieWork *, s32, s32, s32);
s32 func_00f275e0(s32);
void func_00f279f8(s32);
extern u8 D_00F28568[];
extern u8 D_00F28580[];

void func_00f245c0(void) {
    MovieWork *m;
    u8 *h;
    s32 w, ht;
    s32 r;
    s32 n;
    s32 k;
    s32 f;

    D_00F28460->f3DF52 = 0;
    sceIpuInit();
    m = D_00F28460;
    for (;;) {
        func_00f26d90(m->f3DDD4, m->f3DE54);
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
        D_00F28460->f3DD24 = ht * 16;
        D_00F28460->f3DD28 = h[13];
        D_00F28460->f3DD20 = w;
        func_00f279f8(w);
        f = D_00F28460->f3DDD0 | 0x200;
        D_00F28460->f3DDD0 = f;
        if (f & 0x100) {
            while (!(D_00F28460->f3DDD0 & 8)) {
                func_00f23480();
                if (!(D_00F28460->f3DDD0 & 0x100)) {
                    goto play;
                }
            }
        } else {
        play:
            func_00f23650();
            func_00f26be0();
            do {
                func_00f25180();
                func_00f260c0();
                m = D_00F28460;
                if (m->f3DF67 == 0 && m->f3DD2C == m->f3DF1C - 30) {
                    func_001eda90(0, 0xEF);
                    D_00F28460->f3DF67 = 1;
                }
                func_00f255f0();
                m = D_00F28460;
                m->f3DD90 += ((s32 *)m->f3DD90)[2] + 0x10;
                func_00f23498();
                m = D_00F28460;
                r = -1;
                if (m->f3DD74[m->f3DD44] == 1) {
                    r = func_00f23620(m);
                    if (r == 0) {
                        m = D_00F28460;
                        m->f3DD74[m->f3DD44] = 2;
                        n = m->f3DD44 + 1;
                        m->f3DD44 = n;
                        m->f3DD44 = n % m->f3DF50;
                    }
                }
                m = D_00F28460;
                if (m->f3DD74[m->f3DD44] == 0) {
                    if (r == -1) {
                        r = func_00f23620(m);
                    }
                    if (r == 0) {
                        n = func_00f275e0(D_00F28460->f3DD44);
                        if (n != 0) {
                            m = D_00F28460;
                            func_00f234e8(m->f3DD48, n, m->f3DD5C[m->f3DD44], &m->f3DD68[m->f3DD44], m);
                            D_00F28460->f3DD74[D_00F28460->f3DD44] = 1;
                        }
                    }
                }
                m = D_00F28460;
                n = ++m->f3DD2C;
                if (m->f3DD50[m->f3DD40] == n) {
                    if (n == m->f3DD4C) {
                        f = m->f3DDD0 | 0x1000;
                        m->f3DDD0 = f;
                        if (f & 0x2000) {
                            func_00f208b8(m);
                            func_00f23480();
                            while (!(D_00F28460->f3DDD0 & 8)) {
                                func_00f255f0();
                                func_00f23480();
                            }
                        }
                    } else {
                        m = D_00F28460;
                        switch (m->f3DD74[m->f3DD40]) {
                        case 0:
                            n = func_00f275e0(m->f3DD40);
                            if (n != 0) {
                                if (func_00f23620(D_00F28460) != 0) {
                                    func_00f23598(D_00F28460->f3DD48, 1, D_00F28460);
                                }
                                m = D_00F28460;
                                func_00f234e8(m->f3DD48, n, m->f3DD5C[m->f3DD40], &m->f3DD68[m->f3DD40], m);
                                func_00f23598(D_00F28460->f3DD48, 1, D_00F28460);
                                D_00F28460->f3DD74[D_00F28460->f3DD40] = 2;
                            }
                            break;
                        case 1:
                            func_00f23598(m->f3DD48, 1, D_00F28460);
                            D_00F28460->f3DD74[D_00F28460->f3DD40] = 2;
                            break;
                        }
                        m = D_00F28460;
                        if (m->f3DD44 == m->f3DD40) {
                            m->f3DD44 = (m->f3DD44 + 1) % m->f3DF50;
                        }
                        FlushCache(0);
                        m = D_00F28460;
                        n = m->f3DD40 - 1;
                        m->f3DD90 = m->f3DD5C[m->f3DD40] + m->f3DD68[m->f3DD40];
                        if (n < 0) {
                            n = m->f3DF50 - 1;
                        }
                        m->f3DD74[n] = 0;
                        k = m->f3DD40 + 1;
                        m->f3DD40 = k;
                        m->f3DD40 = k % m->f3DF50;
                        if (m->f3DD74[m->f3DD44] == 0 && func_00f23620(m) == 0) {
                            n = func_00f275e0(D_00F28460->f3DD44);
                            if (n != 0) {
                                m = D_00F28460;
                                func_00f234e8(m->f3DD48, n, m->f3DD5C[m->f3DD44], &m->f3DD68[m->f3DD44], m);
                                D_00F28460->f3DD74[D_00F28460->f3DD44] = 1;
                            }
                        }
                    }
                }
                m = D_00F28460;
                n = m->f3DD40 - 1;
                if (n < 0) {
                    n = m->f3DF50 - 1;
                }
                if (m->f3DD74[n] != 2) {
                    __asm__ volatile("break");
                }
                k = m->f3DDD0;
                m->f3DDD0 = k | 4;
                if ((k | 4) & 0x4040) {
                    m->f3DDD0 = (k | 0x44) & ~0x4000;
                    func_00f208b8(m);
                    func_00f23480();
                    if (D_00F28460->f3DDD0 & 0x40) {
                        while (!(D_00F28460->f3DDD0 & 8)) {
                            func_00f255f0();
                            func_00f23480();
                            if (!(D_00F28460->f3DDD0 & 0x40)) {
                                break;
                            }
                        }
                    }
                } else {
                    func_00f20ae0(D_00F28460);
                    func_00f23480();
                }
                if (*(s32 *)D_00F28460->f3DD14 != 0x12345678) {
                    func_0024b1e8(D_00F28568, D_00F28580, 0x4B0);
                }
            } while (!(D_00F28460->f3DDD0 & 8));
        }
        func_00f25010(D_00F28460, 1);
        f = D_00F28460->f3DDD0;
        if ((f & 8) || !(f & 0x80)) {
            break;
        }
        func_00f270c8(D_00F28460, 0, 0, D_00F28460->f3DF48);
        m = D_00F28460;
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
