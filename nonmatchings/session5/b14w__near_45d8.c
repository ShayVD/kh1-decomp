#include "common.h"
typedef struct Obj { u8 pad[0x10]; struct Obj *x10; u8 p14[0x10]; s32 x24; } Obj;
typedef struct { u8 pad[4]; u32 x4; s32 x8; } Cfg;
extern Cfg *D_00425BC8;
extern u32 D_00642C3C;
extern s32 D_00642C24;
extern s32 D_00642C28;
extern u8 *D_00642C30;
extern s32 D_00642C34;
extern s32 D_00642C40;
extern s32 D_00642C44;
extern s32 D_00642C6C;
extern s32 D_003F3EB8[];
extern u8 D_003F3DF0[];
extern u8 *D_00304BE8;
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd518(void *);
s32 func_001fe5a0(void *);
void func_001f3d58(void *, s32);
Obj *func_001f4468(void *);
Obj *func_001f31a8(u8 *, s32);
void func_001f3e90(Obj *, Obj *);
void func_001f3e20(Obj *, Obj *);
void func_002140c0(Obj *, s32);
void func_00209340(void *, s32, s32 *);

void func_002145d8(Obj *a) {
    s32 buf[3];
    s32 f, v;
    Obj *o, *p;
    f = D_00642C3C & 0x80;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a);
            func_0011d768(3);
            D_00642C24 = 1;
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            v = func_001fd518(a);
            D_00642C6C = v;
            if ((p = a->x10)) {
                if (v == 0) p->x24 = f ? 181 : 184;
                else p->x24 = D_003F3EB8[v];
            }
            if (func_001fe5a0(a)) {
                func_001f3d58(a, 5);
                p = func_001f4468(a);
                D_00642C44 = D_00642C6C;
                switch (D_00642C6C) {
                case 0:
                    func_001f3758(a);
                    if (D_00642C28 != -1) {
                        if (!f) {
                            func_0011d768(75);
                            D_00642C30[D_00642C34 + 64] |= 0x80;
                            D_00642C24 = 5;
                        } else if (D_00642C40 == 0) {
                            func_0011d768(5);
                            D_00642C30[D_00642C34 + 64] &= 0x7f;
                            D_00642C24 = 5;
                        } else {
                            func_0011d768(4);
                            if ((o = func_001f31a8(D_003F3DF0, 6))) {
                                func_001f3e90(p, o);
                                func_001f3e20(o, p);
                                func_002140c0(o, 202);
                            }
                        }
                    } else {
                        if (!f) func_0011d768(75);
                        else func_0011d768(5);
                        (D_00642C34 + D_00304BE8)[1433] ^= 0x80;
                        D_00642C24 = 5;
                    }
                    break;
                case 1:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 4;
                    break;
                case 2:
                    func_001f3758(a);
                    func_0011d768(2);
                    D_00642C24 = 3;
                    break;
                }
            }
        }
    }
    buf[0] = f ? 185 : 186;
    buf[1] = 187;
    buf[2] = 188;
    func_00209340(a, 2, buf);
}
