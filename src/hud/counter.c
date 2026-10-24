/* The counter (docs/modules.md "Session 46"), default flags part.
 * func_00244b10 splits a value into five digits and returns how many to draw
 * (no leading zeros, at least one); func_00244d00 steps the digit and frame
 * sprites (restarting them on a, starting their fades on b);
 * func_00244b00 is the HUD's step for the counter (off), func_00245228 is 1
 * while it is on, func_00244960 is an empty hook its draw hook calls. */
#include "common.h"
#include "data/types/text_00240000_s6_25.h"

extern s32 D_00662540; /* src/data/bss_0066.c: Hud D_00662540 */
extern Obj D_0065FD80[5][10];
extern Obj D_00662300[3]; /* src/data/bss_0066.c: u8 D_00662300[0x240] */
void func_0024a568(Obj *);
void func_0024a678(Obj *);
void func_0024a0c0(Obj *);
void func_0024a088(Obj *);
void func_0024a2e0(Obj *);
void func_0024a450(Obj *);
void func_0024af00(Obj *);

void func_00244960(void) {
}

void func_00244b00(void) {
    D_00662540 = 0;
}

s32 func_00244b10(s32 v, s32 *d) {
    s32 *p;
    s32 n = 5;
    s32 i = 0;
    d[0] = v / 10000;
    d[1] = v % 10000 / 1000;
    d[2] = v % 1000 / 100;
    d[3] = v % 100 / 10;
    d[4] = v % 10;
    if (d[0] == 0) {
        p = d;
        do {
            i++;
            p++;
            n--;
        } while (i < 4 && *p == 0);
    }
    return n;
}

void func_00244d00(s32 a, s32 b) {
    s32 i, j; Obj *o;
    if (a) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                func_0024a568(&D_0065FD80[i][j]);
                func_0024a678(&D_0065FD80[i][j]);
            }
        }
        o = D_00662300;
        for (i = 0; i < 3; i++, o++) {
            func_0024a568(o);
            func_0024a678(o);
        }
    }
    if (b) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                Obj *o = &D_0065FD80[i][j];
                if (o->fl & 2) { func_0024a0c0(o); func_0024a088(o); }
                if (o->fl & 0x40) { func_0024a2e0(o); func_0024a450(o); }
            }
        }
        o = D_00662300;
        for (i = 0; i < 3; i++, o++) {
            if (o->fl & 2) { func_0024a0c0(o); func_0024a088(o); }
            if (o->fl & 0x40) { func_0024a2e0(o); func_0024a450(o); }
        }
    }
    for (i = 0; i < 5; i++)
        for (j = 0; j < 10; j++)
            func_0024af00(&D_0065FD80[i][j]);
    o = D_00662300;
    for (i = 0; i < 3; i++, o++)
        func_0024af00(o);
}

s32 func_00245228(void) {
    return D_00662540 != 0;
}
