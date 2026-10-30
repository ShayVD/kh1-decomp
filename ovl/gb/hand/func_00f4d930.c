/* gb.x func_00f4d930: matched by hand. Round 47 (wgb). The a8 field of Ent is s8. Four reads are (u8)p->a8 and one is (p->a8 & 0xFF). Any mix of the two forms matches; one form throughout does not. As a plain u8, loop.c hoisted the 9, 21 and 1 colour constants, and reload gave 21 and 1 each other's registers. */
#include "ovl.h"

typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; } Obj;
typedef struct { u8 a0; u8 pad1[7]; s8 a8; u8 pad9; u8 aA; u8 padb[41]; u8 s34[44]; } Ent;
extern s32 D_002C5AD8;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F703C8;
extern s32 D_00F705B0;
extern s8 D_00F7114B;
extern s32 D_00F829CC;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F82A34;
extern s32 D_00F82D74;
extern s32 D_00F82D78;
extern s32 D_00F82D7C;
extern s32 D_00F82D80;
extern s32 D_00F82D84;
extern s32 D_00F82D88;
void func_0011d768(s32);
Ent *func_001bc4e0(void);
s32 func_001bc510(void);
void func_001efb18(s32, s32);
void func_001f3840(Obj *);
void func_001f3dc0(s32);
s32 func_001f42b8(Obj *);
s32 func_001f4390(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
s32 func_001fd638(Obj *);
void func_001fd858(Obj *);
s32 func_001fe5a0(Obj *);
void func_00202fc0(Obj *);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(Obj *, s32, s32, s32, s32, s32, s32, s32, u8 *);
void func_00208280(Obj *, s32, s32, s32, s32, s32);
s32 func_00f39330(void);
s32 func_00f39340(void);

void func_00f4d930(Obj *o)
{
    s32 c[2];
    s32 n;
    s32 selx, sely;
    s32 sel;
    Ent *e;
    Ent *p;
    s32 num, i, y, k, s3, col;

    e = func_001bc4e0();
    n = func_001bc510() - 1;
    if (func_001f42b8(o)) func_001fd858(o);
    num = 0;
    func_00202fc0(o);
    func_001f8ee0(o);
    i = func_001fd618(o);
    y = func_001fd590(o);
    sel = func_001fd548(o);
    for (k = 0; k < i; k++) {
        p = &e[k + 1];
        if (p->a0 == 0 && (u8)p->a8 == 0) num++;
    }
    o->hc2 = 2240;
    selx = 0;
    o->hbe = 0;
    sely = 0;
    for (k = n + 1; k >= 0; k--) {
        if (i < n) {
            p = &e[i + 1];
            s3 = sel == i;
            if (!s3) {
                if ((u8)p->a8 == 0) {
                    c[0] = 9;
                    c[1] = 9;
                } else {
                    c[0] = 21;
                    c[1] = 21;
                }
            } else {
                c[0] = 0;
                c[1] = 1;
            }
            if (p->a0 == 0 && (u8)p->a8 == 0) {
                func_001efb18(func_00f39330(), func_00f39340());
                func_002078f0(o, c[s3], 2, 0, 0, y, D_00F705B0, D_00F703C8, num + 196);
                num++;
            } else {
                func_00207938(o, c[s3], 2, 0, 0, y, D_00F705B0, D_00F703C8, p->s34);
            }
            if (s3) {
                col = 128;
                selx = (o->x >> 4) + D_00F705B0 - 1792;
                sely = (o->y >> 4) + y - 1856;
                if (D_00F82D78) { if ((u8)p->a8 == 0) D_00F82A34 = 0; else D_00F82A34 = 1; }
            } else {
                col = 64;
            }
            if ((p->a8 & 0xFF) == 0)
                func_00208280(o, 10, y + 4, 18, 46, col);
            else
                func_00208280(o, 10, y + 4, 18, 47, col);
            y += 28;
        }
        i++;
    }
    func_001f8f30();
    if (func_001f4390(o)) {
        if (D_00F82D80) {
            D_00F829D4 = selx;
            D_00F829D8 = sely;
        }
        D_00F702D8 = D_00F702DC = sel + 1;
        if (D_00F82D7C < 0) {
            D_00F82D84 = func_001fd618(o) << 4;
            D_00F82D88 = func_001fd638(o) << 4;
            func_001f3840(o);
        } else if (D_00F82D78) {
            if (func_001fe5a0(o)) {
                func_001f3dc0(D_00F829CC);
                D_00F82D84 = func_001fd618(o) << 4;
                D_00F82D88 = func_001fd638(o) << 4;
                p = &e[sel + 1];
                if (D_00F7114B & p->aA) {
                    func_0011d768(4);
                    D_00F82D7C = 1;
                } else if (p->aA & 0xF0) {
                    func_0011d768(4);
                    if (p->aA & 0x10) D_00F82D7C = 2; else D_00F82D7C = 3;
                    D_00F82D78 = 0;
                    D_00F82D74 = sel;
                } else {
                    D_00F82D74 = sel;
                    func_0011d768(2);
                    func_001f3840(o);
                    D_00F82D78 = 0;
                }
            } else if (D_002C5AD8 & 0x4000) {
                D_00F82D84 = func_001fd618(o) << 4;
                D_00F82D88 = func_001fd638(o) << 4;
                D_00F82D74 = -1;
                func_0011d768(3);
                func_001f3840(o);
                D_00F82D78 = 0;
            }
        }
    }
}
