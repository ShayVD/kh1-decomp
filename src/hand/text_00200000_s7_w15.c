#include "common.h"
#include "data/bss_0064.h"

typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x21]; u8 x26[0x4e]; } T74e;
typedef struct { T74e e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; u8 x499[256]; } G4BE8e;
extern G4BE8e *D_00304BE8;
typedef struct { u8 pad[8]; s32 flags; } G5bc8e;
extern G5bc8e *D_00425BC8;
typedef struct ObjE {
    u8 pad00[0x10];
    struct ObjE *x10;
    u8 pad14[0x24 - 0x14];
    s32 x24;
    s32 x28;
    s32 x2c;
    u8 pad30[0x40 - 0x30];
    s32 x40;
    u8 pad44[0x70 - 0x44];
    union { s32 i; u16 h[2]; } x70;
    u8 pad74[0x88 - 0x74];
    union { s32 i; u16 h[2]; } x88;
    u8 pad8c[0xb8 - 0x8c];
    s16 xb8;
    u8 padba[0xc2 - 0xba];
    s16 xc2;
    u8 padc4[2];
    s16 xc6;
    u8 padc8[0xcc - 0xc8];
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} ObjE;
extern s32 D_00641224, D_00641228, D_00641230, D_00641234, D_00641238, D_0064123C;
extern s32 D_00641240, D_00641254, D_00641274, D_00641790;
#include "data/pieces/D_003E3D68.h"
extern u8 D_003F38E0[], D_003F3910[];
extern s32 D_003F39A8[];
s32 func_001ee7f0(s32);
s32 func_001ee9e0(s32);
s32 func_001ee9b8(s32);
s32 func_001ee7c8(s32);
s32 func_001f42b8(ObjE *);
s32 func_001f3758(ObjE *);
void func_0011d768(s32);
void func_001fd858(ObjE *);
void func_0020bd18(ObjE *, s32);
u32 func_001fd518(ObjE *);
s32 func_001fe5a0(ObjE *);
ObjE *func_001f4468(ObjE *);
void func_001f3d58(ObjE *, s32);
s32 func_0020db00(ObjE *, s32, s32, s32);
ObjE *func_001f31a8(void *, s32);
ObjE *func_001f3520(void *, s32);
void func_001f3e48(ObjE *, ObjE *);
void func_0020da90(ObjE *, s32);
void func_001fd678(ObjE *, s32);
void func_00207830(ObjE *, s32, s32, s32, s32, s32, s32);

extern s32 D_00641244, D_00641248, D_00641258, D_0064125C;
extern s32 D_00641278[][16];
extern u8 D_003F39C0[], D_003F3980[];
void func_001fd5e0(ObjE *, s32);
void func_001fd610(ObjE *, s32);
void func_001fd688(ObjE *);
s32 func_001fd548(ObjE *);
s32 func_001ee6d0(s32);
s32 func_001efbb8(s32);
void func_001f3dc0(ObjE *);
void func_00202fc0(ObjE *);
s32 func_001fd618(ObjE *);
s32 func_001fd590(ObjE *);
void func_001f8ba8(ObjE *);
void func_001f8f30(void);
void func_0020dd38(ObjE *, s32, s32, s32, s32, s32);

extern s32 D_00641260, D_00641264, D_00641268, D_00641388, D_00641790;
extern s32 D_00641390[], D_00641798[];
void func_001fe158(ObjE *);
s32 func_001fd538(ObjE *);
void func_0020dfc8(ObjE *, s32, s32, s32, s32, s32, s32, s32);

s32 func_001ee5f0(s32);
void func_001f36b8(ObjE *);
void func_001f3708(ObjE *, s32);
void func_001f40a0(ObjE *, s32);
u32 func_002073f0(s32);
void func_00207428(ObjE *, s32, s32);
void func_00207870(ObjE *, s32, s32, s32, s32, s32, s32);
extern u8 D_003F39F0[];
extern ObjE *D_00641220; /* src/data/bss_0064.c: s32 D_00641220 */
extern s32 D_0064122C, D_0064126C, D_00641270, D_00641B98;
extern u32 D_00641250[];
extern s32 D_00641378[];

void func_0020f530(ObjE *o) {
    s32 w[2];
    s32 sel, n, lim;
    s32 *tbl;
    s32 fl, v, k, cnt, q;
    T74e *e;
    u8 *t;
    ObjE *p;
    s32 i, j, c, y, cur, a, s;

    if (o->x2c < 2) {
        lim = D_00641388;
        tbl = D_00641390;
        fl = 0;
        n = 8;
    } else {
        tbl = D_00641798;
        lim = D_00641790;
        fl = 1;
        n = 7;
    }
    if (!lim) return;
    func_001fd5e0(o, lim);
    func_001fd610(o, n);
    func_001fd688(o);
    if (func_001f42b8(o)) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3758(o);
            func_0011d768(3);
            if (!fl) D_00641224 = 0;
            else if (D_00641238 != 2) D_00641224 = 3;
            else D_00641224 = 2;
        } else {
            func_001fe158(o);
            func_0020bd18(o, 8);
            D_00641260 = (s16)o->xd0 >> 4;
            D_00641264 = (s16)o->xd2 >> 4;
            D_00641268 = (s16)o->xda >> 4;
            k = func_001fd548(o);
            p = o->x10;
            v = tbl[k];
            if (p) {
                if (v) p->x40 = func_001ee6d0(v);
                else p->x40 = func_001efbb8(152);
            }
            if (func_001fe5a0(o)) {
                p = func_001f4468(o);
                if (!fl) {
                    func_0011d768(2);
                    func_001f3d58(o, 5);
                    func_001f3758(o);
                    if ((w[0] = (s32)func_001f31a8(D_003F39C0, 6))) {
                        func_001f3e48((ObjE *)w[0], p);
                        ((ObjE *)w[0])->xd2 = *(u16 *)&D_00641274 << 4;
                        D_00641230 = v;
                        D_00641234 = v;
                        D_00641224 = 2;
                        if ((w[1] = (s32)func_001f31a8(D_003F3980, 6))) {
                            func_001f3e48((ObjE *)w[1], (ObjE *)w[0]);
                            ((ObjE *)w[1])->x24 = func_001fd518((ObjE *)w[0]);
                            func_001f3dc0((ObjE *)w[0]);
                        }
                    }
                } else if (D_00641228 != -1) {
                    if (D_00641238 == 1) {
                        if (func_001ee9e0(v)) {
                            if (D_00641234 && D_00304BE8->x499[D_00641234] >= 99) {
                                func_0011d768(4);
                                if ((w[0] = (s32)func_001f31a8(D_003F38E0, 6))) {
                                    func_001f3e48((ObjE *)w[0], p);
                                    func_0020da90((ObjE *)w[0], 161);
                                }
                            } else {
                                func_0011d768(2);
                                func_001f3d58(o, 5);
                                func_001f3758(o);
                                D_00641244 = v;
                                D_00641248 = v;
                                D_00304BE8->e[D_00304BE8->x48e[D_00641228]].x26[D_00641230] = v;
                                D_00304BE8->x499[v]--;
                                if (D_00641234) D_00304BE8->x499[D_00641234]++;
                                D_00641224 = 5;
                            }
                        } else {
                            func_0011d768(3);
                        }
                    } else if (func_001ee9e0(v)) {
                        func_0011d768(2);
                        func_001f3d58(o, 5);
                        func_001f3758(o);
                        D_00641244 = v;
                        D_00641248 = v;
                        e = &D_00304BE8->e[D_00304BE8->x48e[D_00641228]];
                        t = &e->x4;
                        e->x26[D_00641230] = v;
                        D_00304BE8->x499[v]--;
                        cnt = t[33];
                        q = 0;
                        if (cnt == 0) goto out;
                        if (t[q + 34] == 0) {
                            if (q < D_00641258) { D_00641258 = q; D_0064125C = 0; goto out; }
                            while (1) {
                                if (D_00641258 + q < cnt) {
                                    D_0064125C = q - D_00641258;
                                } else {
                                    D_00641258 = cnt - 8;
                                    D_0064125C = q - D_00641258;
                                }
                                goto out;
                            rest:;
                            }
                        }
                    inc:
                        q++;
                        if (q >= cnt) goto out;
                        if (((u8 *)(q + (u32)t))[34]) goto inc;
                        if (!(q < D_00641258)) goto rest;
                        D_00641258 = q;
                        D_0064125C = 0;
                    out:
                        D_00641224 = 5;
                    } else {
                        func_0011d768(3);
                    }
                }
            }
        }
    }
    func_00202fc0(o);
    i = 0;
    sel = func_001fd518(o);
    s = func_001fd538(o);
    j = func_001fd618(o) * 2;
    cur = func_001fd590(o);
    a = o->x28;
    n = o->xce + 1;
    func_001f8ba8(o);
    for (; i < n; i++) {
        y = 0;
        for (c = 0; c < 2 && j < lim; c++, j++) {
            s32 m, u;
            u = tbl[j];
            if (!a) m = 32;
            else if (i == sel && c == s) m = 31;
            else m = 30;
            func_0020dfc8(o, m, y, cur, 166, u, D_00304BE8->x499[u], 15);
            y += 166;
        }
        cur += 28;
    }
    func_001f8f30();
}

static inline void inl_fx(ObjE *o) {
    ObjE *p, *q;
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

void func_0020ff80(ObjE *o) {
    s32 fl, lim;
    u32 sel, i, n;
    u32 sel2;
    s32 y, a, m, go;
    s32 *f;
    ObjE *p;
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
                    u8 c = D_00304BE8->x48e[sel];
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
                        p->xd2 = *(u16 *)&D_0064125C << 4;
                        p->xd8 = 1;
                        p->xda = 0;
                        p->xb8 = 2656;
                        p->xc2 = 2656;
                        p->x88.i &= ~1;
                    } else if (sel == D_003E3D68) {
                        p->xd0 = *(u16 *)&D_00641260 << 4;
                        p->xd2 = *(u16 *)&D_00641264 << 4;
                        p->xda = *(u16 *)&D_00641268 << 4;
                        p->xd8 = 2;
                        p->xb8 = 5312;
                        p->xc2 = 2656;
                        p->x88.i |= 1;
                        p->xc6 = 0;
                        p->x70.i = 4;
                    } else {
                        p->xd0 = *(u16 *)&D_0064126C << 4;
                        p->xd2 = *(u16 *)&D_00641270 << 4;
                        p->xd8 = 1;
                        p->xda = 0;
                        p->xb8 = 2656;
                        p->xc2 = 2656;
                        p->x88.i &= ~1;
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
                            D_0064122C = func_001ee5f0(D_00304BE8->x48e[sel]);
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
                        if (!fl) {
                            D_00641224 = 1;
                            D_00641228 = -1;
                            D_0064122C = func_001efbb8(56);
                        } else {
                            D_00641240 = -1;
                            func_001f4468(o);
                            D_00641224 = 4;
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
    sel2 = func_001fd518(o);
    if (i < D_003E3D68) {
        f = D_00641378;
        do {
            if (*f++) m = i == sel2;
            else m = i == sel2 ? 3 : 2;
            func_00207870(o, m, a, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i++]));
            y += 28;
        } while (i < D_003E3D68);
    }
    n = o->xcc;
    if (D_003E3D68 < n) {
        if (lim) m = D_003E3D68 == sel2;
        else m = D_003E3D68 == sel2 ? 3 : 2;
        func_00207830(o, m, a, 0, y, 122, 56);
        if (D_003E3D68 + 1 < n && !fl) {
            func_00207830(o, D_003E3D68 + 1 == sel2, a, 0, y + 28, 122, 57);
            if (!func_002073f0(1)) func_00207428(o, 81, y + 40);
        }
    }
}
#include "data/data_003F.h"
