#include "common.h"

typedef struct { s32 a, b, c, d; } Q4;
typedef struct { u8 pad0[0xA0]; f32 xa0; u8 pad[0x10]; s32 xb4; u8 pad2[2]; u16 xba; u8 pad3[4]; u16 xc0; u8 pad4[0x10]; s16 xd2; } Obj;

void func_00109278(void);
void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001efd98(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f4040(void *, s32);
void func_001f4058(void *, s32);
void func_001f40a0(void *, s32);
s32 func_001f42b8(void);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
s32 func_0020d030(void);
void func_0020d2f8(void);
void func_0020d530(void);
void func_00228e70(void *);
void func_00229490(s32);
void func_00233ef8(s32);

extern s32 D_003F3468[];
extern s32 D_003F3488[];
extern s32 D_003F34A8;
extern s32 D_003F34C4;
extern u8 D_003F6D10[];
extern void *D_003F6E18[];
extern s32 D_003F6E24;
extern s32 D_003F6E2C;
extern u8 D_003F6FD0[];
extern s32 D_003F6FF8[];
extern Q4 D_00643720;
extern s32 D_00643730;
extern s32 D_006437C4;

void func_002295a0(s32 arg0, s32 arg1) {
    s32 r;
    func_001f3110();
    D_003F34A8 = 1;
    func_0020d530();
    D_003F6E24 = 1;
    D_003F6E2C = arg1;
    if (arg1 != 1) {
        D_00643720.a = 0;
        D_00643720.b = 1;
        D_00643720.c = 2;
        D_00643720.d = 3;
        D_00643730 = 4;
    } else {
        D_00643730 = 3;
        D_00643720.b = arg1;
        D_00643720.c = 3;
        D_00643720.a = 0;
    }
    func_0011d768(6);
    r = func_0020d030();
    D_003F34C4 = r;
    if (r != 0) {
        func_00229490(r);
    }
    func_0011ef10(0x270FF, func_0020d2f8)[1] = arg0;
}

void func_00229690(void *arg0) {
    void *objs[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        objs[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F3488[i]);
            arg0 = objs[i];
        }
    }
    objs[0] = func_001f31a8(D_003F6D10, 4);
    if (objs[0] != 0) {
        func_001f3e48(objs[0], arg0);
        func_00228e70(objs[0]);
    }
    func_0020bb90(0x85, 0);
    func_0020bd18(objs[0], 8);
    func_0020bda8(0x10);
}

void func_0022b2e0(void *arg0) {
    Obj *o;
    s32 d;
    func_0011d768(4);
    o = func_001f31a8(D_003F6FD0, 6);
    if (o != NULL) {
        func_001f3e48(o, arg0);
        func_001f4058(o, 2);
        func_001f3d58(o, 6);
        d = func_001efd98(D_003F6FF8[D_006437C4]) * 0x170;
        o->xb4 -= d;
        o->xba += d;
        o->xc0 += d;
        func_0020bda8(0x10);
    }
}

extern u8 D_003F7000[];
extern u8 D_003F7030[];
extern u8 D_003F7060[];
extern s32 D_00425C28[];
extern s32 D_006437E4;
extern s32 D_006469A4;

void func_0022b8a0(void *arg0) {
    Obj *o[3];
    if (func_001f42b8() != 0) {
        func_00109278();
        func_00233ef8(0);
        D_006469A4 = 0;
        D_006437E4 = 0;
        D_00425C28[0] = 3;
        D_00425C28[4] = 3;
        o[0] = func_001f31a8(D_003F7060, 6);
        if (o[0] != NULL) {
            func_001f3e48(o[0], arg0);
            func_001f4040(o[0], 4);
            func_001f40a0(o[0], 0x5A000000);
            o[1] = func_001f31a8(D_003F7030, 6);
            if (o[1] != NULL) {
                func_001f3e48(o[1], o[0]);
                o[1]->xd2 = *(u16 *)&D_006437C4 << 4;
                o[2] = func_001f31a8(D_003F7000, 6);
                if (o[2] != NULL) {
                    func_001f3e48(o[2], o[1]);
                    func_001f3dc0(o[1]);
                }
            }
        }
    }
}

extern void *D_003F71C8[];
extern s32 D_003F71E0[];
extern s32 D_003F71F8[];

void func_0022bb48(void *arg0) {
    void *objs[5];
    s32 i;
    for (i = 0; i < 5; i++) {
        objs[i] = func_001f31a8(D_003F71C8[i], D_003F71E0[i]);
        if (objs[i] != 0) {
            func_001f3e48(objs[i], arg0);
            func_001f3d58(objs[i], D_003F71F8[i]);
            arg0 = objs[i];
        }
    }
    func_001f3dc0(objs[4]);
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
}

extern s32 D_003F34A4;
extern u8 D_003F7380[];
extern s32 D_003F73A4;
extern s32 D_006469B0;
extern s32 D_006469B4;
s32 func_00219428(void);
void func_0022d038(void);

void func_0022d080(s32 arg0) {
    void *objs[4];
    s32 v;
    s32 *p = &D_006469B4, *q = &D_006469B0;
    func_001f3110();
    objs[0] = func_001f31a8(D_003F7380, 12);
    v = func_00219428() != 0 ? 1 : 2;
    *q = v;
    *p = v;
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
    D_003F34A4 = 1;
    D_003F73A4 = 0;
    func_0011ef10(0x2BFE7, func_0022d038)[1] = arg0;
}

extern u8 D_003F7510[];
extern u8 D_003F7540[];
extern u8 D_003F7570[];
extern s32 D_003F76B4;
void func_0020bbc0(void *);
void func_0022da58(void);

void func_0022daa0(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76B4 = 0;
    o[0] = func_001f31a8(D_003F7570, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7540, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7510, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022da58)[1] = arg0;
}

extern u8 D_003F75A0[];
extern u8 D_003F75D0[];
extern u8 D_003F7600[];
extern s32 D_003F76B8;
void func_0022de98(void);

void func_0022dee0(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76B8 = 0;
    o[0] = func_001f31a8(D_003F7600, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F75D0, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F75A0, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022de98)[1] = arg0;
}

extern u8 D_003F7630[];
extern u8 D_003F7660[];
extern u8 D_003F7690[];
extern s32 D_003F76BC;
void func_0022e320(void);

void func_0022e368(s32 arg0) {
    Obj *o[3];
    func_001f3110();
    D_003F76BC = 0;
    o[0] = func_001f31a8(D_003F7690, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7660, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7630, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022e320)[1] = arg0;
}

extern u8 D_003F7720[];
extern u8 D_003F7750[];
extern s32 D_003F7774;
extern s32 D_006469D0;
extern s32 D_006469D4;
extern s32 D_006469DC;
extern s32 D_006469E4;
extern s32 D_006469EC;
extern s32 D_006469F4;
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
void func_0020b968(void);
void func_0022eab8(void);

void func_0022eb00(s32 arg0) {
    Obj *o[2];
    func_001f3110();
    o[0] = func_001f31a8(D_003F7750, 44);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7720, 45);
        if (o[1] != NULL) {
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            o[1]->xa0 = 0;
        }
    }
    D_006469DC = 0;
    D_006469E4 = 0;
    D_006469EC = 0;
    D_006469F4 = 0;
    D_003F7774 = 1;
    D_006469D0 = 0;
    D_006469D4 = 0;
    func_0020b968();
    func_0020bb90(0x153, 0xA4);
    func_0020bda8(0x28);
    func_0011ef10(0x2BFE9, func_0022eab8)[1] = arg0;
}

typedef struct { u8 pad[0x499]; u8 a[1]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern u32 D_003E3D6C;
extern s32 D_00646A14;
extern s32 D_00646A18;
extern u32 D_00646A20;
extern s32 D_00646A28;
extern s32 D_00647634;
extern u8 *D_00647638;
extern s32 D_0064763C;
void func_001ef7f0(s32);
void func_0022ebf8(s32);

s32 func_0022ee08(void) {
    s32 *p = &D_00646A18;
    func_0022ebf8(D_00646A14);
    if (*p > 0) {
        func_0011d768(8);
        func_001ef7f0(D_0064763C);
        if (D_00646A20 < D_003E3D6C) {
            { s32 o = D_00647634; D_00647638[o + 0x22] = *p; }
        } else {
            D_00304BE8->a[*p] += D_00646A28;
        }
    } else {
        func_0011d768(4);
    }
    D_00646A28 = 1;
    return D_00646A18;
}
