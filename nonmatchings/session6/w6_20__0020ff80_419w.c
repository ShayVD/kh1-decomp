/* func_0020ff80 partial draft, ~419 words (size 1812 vs 1844), mode hand (strict; gcse needed: HIGH(D_00641224) kept in s4). Off: sel/HIGH(D_003E3D68) in s1/s2 swapped, x88/xd8 store scheduling in the p->x10->x10 setup (orig cross-jumps cases sel<cnt and sel>cnt), several delay-slot fills. Calls func_0020db00 (matched in out/hand/text_00200000_s6_20.c) — try it defined above. */
#include "common.h"
typedef struct ObjF {
    u8 pad00[0x10];
    struct ObjF *x10;
    u8 pad14[0x24 - 0x14];
    s32 x24;
    s32 x28;
    u8 pad2c[0x70 - 0x2c];
    s32 x70;
    u8 pad74[0x88 - 0x74];
    s32 x88;
    u8 pad8c[0xb8 - 0x8c];
    s16 xb8;
    u8 padba[0xc2 - 0xba];
    s16 xc2;
    u8 padc4[2];
    s16 xc6;
    u8 padc8[0xcc - 0xc8];
    s16 xcc;
    u8 padce[0xd0 - 0xce];
    s16 xd0;
    s16 xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} ObjF;
typedef struct {
    u8 pad000[0x48e];
    u8 party[4];
} FSave;
typedef struct { u8 pad[8]; s32 flags; } FPad;
extern FSave *D_00304BE8;
extern FPad *D_00425BC8;
extern u32 D_003E3D68;
extern u8 D_003F39F0[];
extern ObjF *D_00641220;
extern s32 D_00641224, D_00641228, D_0064122C, D_00641230, D_00641238, D_00641240;
extern u32 D_00641250[];
extern s32 D_00641258, D_0064125C, D_00641260, D_00641264, D_00641268, D_0064126C, D_00641270;
extern s32 D_00641378[];
extern s32 D_00641388, D_00641790, D_00641B98;
void func_0011d768(s32);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);
ObjF *func_001f31a8(void *, s32);
void func_001f36b8(ObjF *);
void func_001f3708(ObjF *, s32);
void func_001f3758(ObjF *);
void func_001f3d58(ObjF *, s32);
void func_001f3dc0(ObjF *);
void func_001f3e48(ObjF *, ObjF *);
void func_001f40a0(ObjF *, s32);
s32 func_001f42b8(ObjF *);
ObjF *func_001f4468(ObjF *);
u32 func_001fd518(ObjF *);
void func_001fd858(ObjF *);
s32 func_001fe5a0(ObjF *);
u32 func_002073f0(s32);
void func_00207428(ObjF *, s32, s32);
void func_00207830(ObjF *, s32, s32, s32, s32, s32, s32);
void func_00207870(ObjF *, s32, s32, s32, s32, s32, s32);
void func_0020bd18(ObjF *, s32);
s32 func_0020db00(ObjF *, s32, s32, s32);

static inline void inl_fx(ObjF *o) {
    ObjF *p, *q;
    func_001f3708(o, 5);
    func_0011d768(2);
    p = o->x10;
    if (p) {
        func_001f36b8(p);
        p = p->x10;
        if (p) {
            p->x28 = 1;
            func_001f40a0(p, 0x60000000);
            q = func_001f31a8(D_003F39F0, 6);
            if (q) func_001f3e48(q, p);
            func_001f3dc0(p);
        }
    }
}

void func_0020ff80(ObjF *o) {
    s32 fl, lim;
    u32 sel, i, n;
    s32 y, a, m, go;
    s32 *f;
    ObjF *p;
    if (D_00641224 < 2) {
        fl = 0;
        lim = D_00641388;
    } else {
        lim = D_00641790;
        fl = 1;
    }
    if (func_001f42b8(o)) {
        if (D_00425BC8->flags & 0x4000) {
            if (!fl) {
                func_001f3758(D_00641220);
            } else {
                func_001f3758(o);
                D_00641224 = 2;
            }
            func_0011d768(3);
        } else {
            func_001fd858(o);
            func_0020bd18(o, 8);
            sel = func_001fd518(o);
            p = o->x10;
            D_00641250[fl] = sel;
            if (p) {
                if (sel < D_003E3D68) {
                    u8 c = D_00304BE8->party[sel];
                    if (!fl || D_00641238 == 1) {
                        if (!c) p->x24 = 122;
                        else p->x24 = 123;
                    } else {
                        if (!c) p->x24 = 126;
                        else p->x24 = 127;
                    }
                    p->x28 = func_001ee5f0(c);
                } else {
                    if (sel == D_003E3D68) p->x24 = 124;
                    else p->x24 = 125;
                }
                p = p->x10;
                if (p) {
                    p->x24 = sel;
                    if (sel < D_003E3D68) {
                        p->xd0 = *(u16 *)&D_00641258 << 4;
                        p->x88 &= ~1;
                        p->xd8 = 1;
                        p->xd2 = *(u16 *)&D_0064125C << 4;
                        p->xc2 = 2656;
                        p->xda = 0;
                        p->xb8 = 2656;
                    } else if (sel == D_003E3D68) {
                        p->xd0 = *(u16 *)&D_00641260 << 4;
                        p->xd2 = *(u16 *)&D_00641264 << 4;
                        p->x70 = 4;
                        p->xd8 = 2;
                        p->xda = *(u16 *)&D_00641268 << 4;
                        p->xb8 = 5312;
                        p->xc2 = 2656;
                        p->x88 |= 1;
                        p->xc6 = 0;
                    } else {
                        p->xd0 = *(u16 *)&D_0064126C << 4;
                        p->x88 &= ~1;
                        p->xd8 = 1;
                        p->xd2 = *(u16 *)&D_00641270 << 4;
                        p->xc2 = 2656;
                        p->xda = 0;
                        p->xb8 = 2656;
                    }
                }
            }
            if (func_001fe5a0(o)) {
                if (sel < D_003E3D68) {
                    if (D_00641378[sel]) {
                        go = 1;
                        if (!fl) {
                            D_00641224 = 1;
                            D_00641228 = sel;
                            D_0064122C = func_001ee5f0(D_00304BE8->party[sel]);
                        } else {
                            D_00641240 = sel;
                            if (D_00641238 == 0) {
                                func_001f3d58(o, 5);
                                func_001f3758(o);
                                go = 0;
                                if (func_0020db00(o, D_00641228, D_00641230, D_00641240)) D_00641224 = 5;
                            } else {
                                D_00641224 = 4;
                            }
                        }
                        if (go) inl_fx(o);
                    } else {
                        func_0011d768(4);
                    }
                } else if (sel == D_003E3D68) {
                    if (lim) {
                        inl_fx(o);
                        if (fl) {
                            D_00641240 = -1;
                            func_001f4468(o);
                            D_00641224 = 4;
                        } else {
                            D_00641224 = 1;
                            D_00641228 = -1;
                            D_0064122C = func_001efbb8(56);
                        }
                    } else {
                        func_0011d768(4);
                    }
                } else if (D_00641B98) {
                    inl_fx(o);
                    D_00641224 = 1;
                    D_00641228 = -2;
                    D_0064122C = func_001efbb8(57);
                } else {
                    func_0011d768(4);
                }
            }
        }
    }
    a = fl != 0;
    i = 0;
    y = 0;
    sel = func_001fd518(o);
    if (D_003E3D68) {
        f = D_00641378;
        do {
            if (*f++) m = i == sel;
            else {
                m = 3;
                if (i != sel) m = 2;
            }
            func_00207870(o, m, a, 0, y, 122, func_001ee5f0(D_00304BE8->party[i++]));
            y += 28;
        } while (i < D_003E3D68);
    }
    n = o->xcc;
    if (D_003E3D68 < n) {
        if (lim) m = D_003E3D68 == sel;
        else {
            m = 3;
            if (D_003E3D68 != sel) m = 2;
        }
        func_00207830(o, m, a, 0, y, 122, 56);
        if (D_003E3D68 + 1 < n && !fl) {
            func_00207830(o, D_003E3D68 + 1 == sel, a, 0, y + 28, 122, 57);
            if (!func_002073f0(1)) func_00207428(o, 81, y + 40);
        }
    }
}
