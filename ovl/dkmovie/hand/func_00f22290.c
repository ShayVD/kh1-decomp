/* dkmovie.x func_00f22290: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad[0x3DD48];
    s32 f3DD48;
    u8 pad3DD4C[0x3DF52 - 0x3DD4C];
    s8 f3DF52;
} MovieWork;
extern s32 D_00F283C8;
extern s8 D_00F28680;
extern s32 D_00F28670;
extern s32 D_00F28678;
extern s32 D_00F28684;
extern u8 D_00F283D8[];
s32 sceIoctl(s32, s32, void *);
void func_00f23480(void);
void func_00f208b8(MovieWork *);
void func_00f255f0(void);
s32 func_00f220d0(void);
void func_00f21b98(void);
void func_00f21bd8(MovieWork *);
void func_00f21da0(s32, s32, s32, void *, MovieWork *);
void func_00f27678(void);

s32 func_00f22290(s32 arg0, MovieWork *m) {
    s32 st;
    s32 started = 0;
    s32 once;
    s32 cnt;
    s32 r;
    D_00F283C8 = 0;
    if (m->f3DF52) {
        once = 0;
        for (;;) {
            sceIoctl(m->f3DD48, 1, &st);
            if (st == 0) {
                D_00F28680 = 0;
                return 1;
            }
            func_00f23480();
            if (arg0) {
                if (!once) {
                    once = 1;
                    func_00f208b8(m);
                }
                func_00f255f0();
            }
        }
    }
    once = 0;
    for (;;) {
        for (cnt = 0; cnt < 150; cnt++) {
            r = func_00f220d0();
            if (r == 0) {
                D_00F28680 = 0;
                D_00F283C8 = 0;
                return 1;
            }
            if (r != -1) {
                cnt = 0;
                func_00f21b98();
                D_00F28680 = 1;
                func_00f21bd8(m);
                func_00f21da0(D_00F28670, D_00F28678, D_00F28684, D_00F283D8, m);
            }
            if (!started) {
                started = 1;
                D_00F283C8 = started;
            }
            func_00f23480();
            if (arg0) {
                if (!once) {
                    once = 1;
                    func_00f208b8(m);
                }
                func_00f255f0();
                func_00f27678();
            }
        }
        func_00f21da0(D_00F28670, D_00F28678, D_00F28684, D_00F283D8, m);
    }
}
