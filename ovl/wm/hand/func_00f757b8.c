/* wm.x func_00f757b8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; } Obj;
typedef struct { u8 a0; u8 pad1[7]; u8 a8; u8 pad9[43]; s8 s34[44]; } Ent;
extern s32 D_002C5AD8;
extern s8 *D_003E8E08;
extern s32 D_00FB4A54;
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s32 D_00FB4B48;
extern s32 D_00FB4D30;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F550;
extern s32 D_0108F554;
extern s32 D_0108F558;
extern s32 D_0108F55C;
extern s32 D_0108F560;
extern s32 D_0108F564;
void func_0011d768(s32);
s32 func_001ba3f0(s32);
Ent *func_001bc4e0(void);
s32 func_001bc510(void);
s32 func_001be278(void);
void func_001efb18(s32, s32);
void func_001f3840(Obj *);
s32 func_001f42b8(Obj *);
s32 func_001f4390(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
s32 func_001fd638(Obj *);
void func_001fd858(Obj *);
void func_00202fc0(Obj *);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(Obj *, s32, s32, s32, s32, s32, s32, s32, s8 *);
void func_00208280(Obj *, s32, s32, s32, s32, s32);
s32 func_00f60428(void);
s32 func_00f60438(void);

void func_00f757b8(Obj *o)
{
    s32 c[2];
    s32 n;
    s32 selx, sely;
    s32 sel;
    Ent *e;
    s32 skip;
    s32 cur;
    Ent *p;
    s32 num, i, y, k, s3, hl;

    e = func_001bc4e0() + 1;
    n = func_001bc510() - 1;
    cur = func_001be278();
    if (func_001f42b8(o) && D_0108F558) func_001fd858(o);
    skip = 0;
    for (k = 0; k < n; k++) {
        if (e[k].a8 == 0) break;
        skip++;
    }
    n -= skip;
    cur -= skip;
    e += skip;
    func_00202fc0(o);
    func_001f8ee0(o);
    i = func_001fd618(o);
    y = func_001fd590(o);
    sel = func_001fd548(o);
    num = 1 - n;
    if (func_001ba3f0(69)) num = 5 - n;
    if (func_001ba3f0(70)) num = 10 - n;
    for (k = 0; k < i; k++) {
        p = &e[k];
        if (p->a0 == 0 && p->a8 == 0) num++;
    }
    o->hc2 = 2240;
    selx = 0;
    o->hbe = 0;
    sely = 0;
    for (k = n + 1; k >= 0; k--) {
        if (i < n) {
            p = &e[i];
            hl = 0;
            s3 = sel == i;
            if (D_0108F558 > 0) {
                if (!s3) {
                    c[0] = 6;
                    c[1] = 6;
                    if (cur == i) {
                        hl = 1;
                        c[0] = 7;
                        c[1] = 7;
                    }
                } else {
                    c[0] = 0;
                    c[1] = 1;
                    hl = 1;
                }
            } else if (cur == i) {
                hl = 1;
                c[0] = 7;
                c[1] = 7;
            } else {
                c[0] = 0;
                c[1] = 0;
            }
            if (p->a0 == 0 && p->a8 == 0) {
                func_001efb18(func_00f60428(), func_00f60438());
                func_002078f0(o, c[s3], 2, 0, 0, y, D_00FB4D30, D_00FB4B48, num + 196);
                num++;
            } else {
                func_00207938(o, c[s3], 2, 0, 0, y, D_00FB4D30, D_00FB4B48, p->s34);
            }
            if (s3) {
                selx = (o->x >> 4) + D_00FB4D30 - 1792;
                sely = (o->y >> 4) + y - 1856;
            }
            func_00208280(o, 10, y + 4, 18, 46, hl ? 128 : 64);
            y += 28;
        }
        i++;
    }
    func_001f8f30();
    if (func_001f4390(o)) {
        if (D_0108F558 < 0) {
            func_001f3840(o);
        } else if (D_0108F558 > 0) {
            D_0108F194 = selx;
            D_0108F198 = sely;
            if (D_00FB4A54 == 0) {
                D_00FB4A58 = D_00FB4A5C = sel + skip + 1;
            }
            if (D_002C5AD8 & 0x2000) {
                D_0108F560 = func_001fd618(o) << 4;
                D_0108F564 = func_001fd638(o) << 4;
                D_0108F554 = sel + skip;
                if (D_0108F55C == 1) {
                    if (e[sel].s34[0] == 0) {
                        func_0011d768(4);
                        D_0108F550 = 2;
                        return;
                    }
                    if (func_001be278() == D_0108F554) func_0011d768(4);
                    else func_0011d768(2);
                } else {
                    func_0011d768(2);
                }
                if (e[sel].s34[0]) {
                    D_0108F550 = 1;
                    D_003E8E08 = e[sel].s34;
                } else {
                    D_0108F558 = 0;
                }
            } else if (D_002C5AD8 & 0x4000) {
                D_0108F560 = func_001fd618(o) << 4;
                D_0108F564 = func_001fd638(o) << 4;
                D_0108F554 = -1;
                func_0011d768(3);
                D_0108F558 = 0;
            }
        }
    }
}
