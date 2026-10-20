#include "common.h"
#include "data/bss_0064.h"
/* func_00219f98 (rodata jtbl 0x490f20, verify with wqb03_rr.py 00490f20). CONTEXT_ONLY func_00219380 above. Key: D_003F4C68/78 as flat s32 arrays read [k*2] then [k*2+1] (base + (k*8+4) gives the addu/move copy pair). */
typedef struct ObjT {
    u8 pad[0xD2];
    s16 xd2;
    u8 padd4[0xDA - 0xD4];
    s16 xda;
} Obj;
typedef struct { u8 pad[4]; u32 x4; s32 x8; u8 padc[4]; u32 x10; } Cfg;
typedef struct { s32 x0; s32 x4; s32 x8; u8 padc[4]; s32 x10; s32 x14; s32 x18; u8 pad1c[0x2C - 0x1C]; s32 x2c; } S34B8;
typedef struct { s32 p0; s32 p1; } P2;
extern Cfg *D_00425BC8;
extern S34B8 *D_003F34B8;
extern s32 D_00642D20;
extern s32 D_00642D24;
extern s32 D_003F34C8;
extern s32 D_003F34CC;
extern s32 D_003F34D0;
extern char D_00490F10[];
extern u8 D_003F4B40[];
extern u8 D_003F4B70[];
extern u8 D_003F4BA0[];
extern u8 D_003F4B10[];
extern u8 D_003F47F0[];
extern s32 D_003F4C18[];
extern s32 D_003F4C38[];
extern s32 D_003F4C58[];
extern s32 D_003F4C68[];
extern s32 D_003F4C78[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd518(void *);
void func_001f3d58(void *, s32);
Obj *func_001f4468(void *);
Obj *func_001f31a8(u8 *, s32);
Obj *func_001f3520(u8 *, s32);
void func_001f3e90(void *, Obj *);
void func_001f3e20(Obj *, void *);
void func_001f3dc0(Obj *);
s32 func_00120748(char *, s32, void (*)(void), s32);
void func_002194d0(void);
s32 func_00219158(u32);
void func_002191f0(u32, s32);
s32 func_00219380(void);
s32 func_00219428(void);
void func_001edaf0(s32);
void func_00206690(void *, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, u32, u32);

#define ROW(n) if (D_00642D24 == n) { t.p0 = D_003F4C68[k * 2]; t.p1 = D_003F4C68[k * 2 + 1]; } else { t.p0 = D_003F4C78[k * 2]; t.p1 = D_003F4C78[k * 2 + 1]; }


CONTEXT_ONLY s32 func_00219380(void) { return D_00642D20; }
/* rodata 0x490f20 */
void func_00219f98(void *a) {
    P2 t;
    Obj *o[3];
    Obj *p;
    s32 v, k, i, y, ch;

    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758((void *)D_00642D20);
            func_0011d768(3);
        } else if (D_00425BC8->x8 & 0x2000) {
            switch (D_00642D24) {
            case 0:
                p = func_001f4468(a);
                func_001f3d58(a, 5);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4B40, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->x0 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 96;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 1:
                p = func_001f4468(a);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4B70, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->x4 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 96;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 2:
                p = func_001f4468(a);
                func_001f3758(a);
                func_0011d768(2);
                if (D_003F34CC == 0) {
                    D_003F34CC = 1;
                    D_003F34C8++;
                    func_00120748(D_00490F10, D_003F34D0, func_002194d0, 0);
                }
                if ((o[0] = func_001f3520(D_003F4BA0, 6))) {
                    func_001f3e90(p, o[0]);
                    func_001f3e20(o[0], p);
                    o[0]->xda = (u16)D_003F34B8->x8 * 16;
                    if ((o[1] = func_001f31a8(D_003F4B10, 6))) {
                        func_001f3e90(o[0], o[1]);
                        func_001f3e20(o[1], o[0]);
                        o[1]->xd2 = 0;
                        if ((o[2] = func_001f31a8(D_003F47F0, 6))) {
                            func_001f3e90(o[1], o[2]);
                            func_001f3e20(o[2], o[1]);
                            func_001f3dc0(o[0]);
                        }
                    }
                }
                break;
            case 3:
            case 4:
                if (func_00219158(D_00642D24) < D_003F4C18[D_00642D24])
                    func_002191f0(D_00642D24, func_00219158(D_00642D24) + 1);
                else
                    func_002191f0(D_00642D24, 0);
                func_0011d768(1);
                if (D_00642D24 == 4)
                    func_001edaf0(func_00219380() == 0);
                break;
            case 5:
                if (func_00219428()) {
                    if (func_00219158(5) <= 0)
                        func_002191f0(5, func_00219158(5) + 1);
                    else
                        func_002191f0(5, 0);
                    func_0011d768(1);
                    break;
                }
            case 6:
                func_0011d768(4);
                break;
            case 7:
                func_0011d768(2);
                D_003F34B8->x0 = 0;
                D_003F34B8->x4 = 0;
                D_003F34B8->x8 = 0;
                D_003F34B8->x10 = 0;
                D_003F34B8->x14 = 0;
                D_003F34B8->x18 = 0;
                func_001edaf0(1);
                break;
            }
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642D24 = v;
            ch = 0;
            if ((u32)(v - 6) >= 2 && (v != 5 || func_00219428())) {
                if (D_00425BC8->x10 & 0x80000080) {
                    if (func_00219158(D_00642D24) > 0) {
                        ch = 1;
                        func_002191f0(D_00642D24, func_00219158(D_00642D24) - 1);
                    } else if (D_00425BC8->x8 & 0x80000080) {
                        ch = 1;
                        func_002191f0(D_00642D24, D_003F4C18[D_00642D24]);
                    }
                } else if (D_00425BC8->x10 & 0x20000020) {
                    if (func_00219158(D_00642D24) < D_003F4C18[D_00642D24]) {
                        ch = 1;
                        func_002191f0(D_00642D24, func_00219158(D_00642D24) + 1);
                    } else if (D_00425BC8->x8 & 0x20000020) {
                        func_002191f0(D_00642D24, 0);
                        ch = 1;
                    }
                }
                if (ch) {
                    func_0011d768(1);
                    if (D_00642D24 == 4)
                        func_001edaf0(func_00219380() == 0);
                }
            }
        }
    }
    y = 71;
    for (i = 0; i < 8; i++) {
        k = 0;
        if (i == D_00642D24) {
            if (i < 7) {
                s32 yy = y + 12;
                k = 11;
                func_00206690(a, -64, yy, 75);
                func_00206690(a, 153, yy, 6);
                if (D_00642D24 != 6) {
                    func_00206690(a, 321, yy, 6);
                    func_00206690(a, 489, yy, 23);
                } else {
                    func_00206690(a, 489, yy, 23);
                }
            } else {
                k = 1;
            }
        }
        func_002078f0(a, k, 2, 0, 11, y, 142, 27, D_003F4C38[i]);
        y += 28;
    }
    k = D_003F34B8->x0;
    ROW(0);
    func_002078f0(a, t.p0, 2, 2, 159, 71, 162, 240, 295);
    func_002078f0(a, t.p1, 2, 2, 327, 71, 162, 408, 296);
    k = D_003F34B8->x4;
    ROW(1);
    func_002078f0(a, t.p0, 2, 2, 159, 99, 162, 240, 300);
    func_002078f0(a, t.p1, 2, 2, 327, 99, 162, 408, 301);
    k = D_003F34B8->x8;
    ROW(2);
    func_002078f0(a, t.p0, 2, 2, 159, 127, 162, 240, 304);
    func_002078f0(a, t.p1, 2, 2, 327, 127, 162, 408, 305);
    k = D_003F34B8->x10;
    ROW(3);
    func_002078f0(a, t.p0, 2, 2, 159, 155, 162, 240, 312);
    func_002078f0(a, t.p1, 2, 2, 327, 155, 162, 408, 313);
    k = D_003F34B8->x14;
    ROW(4);
    func_002078f0(a, t.p0, 2, 2, 159, 183, 162, 240, 316);
    func_002078f0(a, t.p1, 2, 2, 327, 183, 162, 408, 317);
    k = D_003F34B8->x18;
    ROW(5);
    func_002078f0(a, t.p0, 2, 2, 159, 211, 162, 240, 452);
    func_002078f0(a, t.p1, 2, 2, 327, 211, 162, 408, 453);
    k = D_003F34B8->x2c;
    if (D_00642D24 == 6) t.p0 = D_003F4C68[0]; else t.p0 = D_003F4C78[0];
    func_002078f0(a, t.p0, 2, 2, 159, 239, 330, 324, D_003F4C58[k]);
    v = D_00642D24;
    if (v < 5) {
        y = v * 28 + 78;
        if (func_00219158(v) == 0)
            func_001fc308(a, 304, y, 0, 0, 16, 0, 0x80808080, 0x80808080);
        else
            func_001fc308(a, 335, y, 0, 0, 15, 0, 0x80808080, 0x80808080);
    }
}
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
