#include "common.h"

typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x21]; u8 x26[0x4e]; } T74e;
typedef struct { T74e e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; u8 x499[256]; } G4BE8e;
extern G4BE8e *D_00304BE8;
typedef struct { u8 pad[8]; s32 flags; } G5bc8e;
extern G5bc8e *D_00425BC8;
typedef struct ObjE { u8 pad[0x10]; struct ObjE *x10; u8 p14[0x10]; s32 x24; } ObjE;
extern s32 D_00641224, D_00641228, D_00641230, D_00641234, D_00641238, D_0064123C;
extern s32 D_00641240, D_00641254, D_00641274, D_00641790;
extern u32 D_003E3D68;
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
s32 func_001fd518(ObjE *);
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

void func_0020e588(ObjE *o) {
    s32 fl[4];
    s32 id[4];
    s32 c0, c1, c2, c3;
    ObjE *p, *q;
    s32 i, y;

    if (D_00641234) {
        c0 = func_001ee7f0(D_00641234);
        c1 = func_001ee9e0(D_00641234);
        c2 = D_00641228 != -1;
        c3 = func_001ee9b8(D_00641234);
    } else {
        c0 = 0;
        c1 = 1;
        c2 = 1;
        c3 = 0;
    }
    if (func_001f42b8(o)) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3758(o);
            func_0011d768(3);
            D_00641224 = 1;
        } else {
            func_001fd858(o);
            func_0020bd18(o, 8);
            D_00641274 = func_001fd518(o);
            if ((p = o->x10)) p->x24 = D_00641274;
            if (func_001fe5a0(o)) {
                p = func_001f4468(o);
                D_00641238 = D_00641274;
                switch (D_00641274) {
                case 0:
                    if (D_00641234 && c0) {
                        if (func_001ee7c8(D_00641234)) {
                            func_001f3d58(o, 5);
                            func_001f3758(o);
                            D_0064123C = 0;
                            if (func_0020db00(o, D_00641228, D_00641230, 0)) D_00641224 = 5;
                        } else {
                            func_001f3d58(o, 5);
                            func_001f3758(o);
                            func_0011d768(2);
                            D_00641224 = 3;
                            D_0064123C = 1;
                        }
                    } else {
                        func_0011d768(4);
                    }
                    break;
                case 1:
                    if (c1 && (D_00641234 || D_00641228 != -1)) {
                        func_001f3d58(o, 5);
                        func_001f3758(o);
                        func_0011d768(2);
                        D_00641224 = 3;
                    } else {
                        func_0011d768(4);
                    }
                    break;
                case 2:
                    if (c2) {
                        if (D_00641234) {
                            if (D_00304BE8->x499[D_00641234] >= 99) {
                                func_0011d768(4);
                                if ((q = func_001f31a8(D_003F38E0, 6))) {
                                    func_001f3e48(q, p);
                                    func_0020da90(q, 161);
                                }
                            } else {
                                func_0011d768(2);
                                func_001f3d58(o, 5);
                                func_001f3758(o);
                                D_00304BE8->x499[D_00641234]++;
                                D_00304BE8->e[D_00304BE8->x48e[D_00641228]].x26[D_00641230] = 0;
                                D_00641224 = 5;
                            }
                        } else if (D_00641790) {
                            func_001f3d58(o, 5);
                            func_001f3758(o);
                            func_0011d768(2);
                            D_00641240 = -1;
                            D_00641254 = D_003E3D68;
                            D_00641224 = 4;
                        } else {
                            func_0011d768(4);
                            if ((q = func_001f31a8(D_003F38E0, 6))) {
                                func_001f3e48(q, p);
                                func_0020da90(q, 162);
                            }
                        }
                    } else {
                        func_0011d768(4);
                    }
                    break;
                case 3:
                    if (D_00641234 && c3) {
                        func_001f3d58(o, 5);
                        func_001f3758(o);
                        func_0011d768(2);
                        if ((q = func_001f3520(D_003F3910, 6))) {
                            func_001f3e48(q, p);
                            func_001fd678(q, 0);
                        }
                    } else {
                        func_0011d768(4);
                    }
                    break;
                }
            }
        }
    }
    fl[0] = 0;
    fl[1] = 0;
    fl[2] = 0;
    fl[3] = 0;
    fl[func_001fd518(o)] |= 1;
    if (!c0) fl[0] |= 2;
    if (!c1) fl[1] |= 2;
    if (!c2) fl[2] |= 2;
    if (!c3) fl[3] |= 2;
    id[0] = 145;
    id[1] = 148;
    id[2] = D_00641234 ? 146 : 149;
    id[3] = 147;
    y = 0;
    for (i = 0; i < 4; i++) {
        func_00207830(o, D_003F39A8[fl[i]], 2, 0, y, 122, id[i]);
        y += 28;
    }
}
