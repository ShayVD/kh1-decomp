#include "common.h"
#include "data/bss_0064.h"

typedef struct { u8 pad0[0x24]; s32 x24; s32 x28; s32 x2c; u8 pad30[0x90 - 0x30]; s32 x90; u8 pad94[0xb0 - 0x94]; s32 xb0, xb4; u8 padb8[0xd8 - 0xb8]; s16 xd8, xda; } Obj;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad0[0x24]; f32 x24; s32 x28; s32 x2c; s32 x30; } Eff;
typedef struct { u8 pad0[0x10]; s32 x10; } S3110;
extern s32 D_00643250;
extern s32 D_00643274;
extern S3110 *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_00643114;
extern s32 D_00643118;
extern u8 D_003F5E30[];
extern f32 D_003F53C0[];
extern u16 D_003F56A0[];
extern s32 D_003F34F8;
#include "data/pieces/D_003E8E08.h"
s32 func_001f42b8(void);
void func_0021e538(void);
void func_0011d768(s32);
void func_0021b5c8(s32, s32, s32, s32, f32);
s32 func_001fd668(Obj *);
s32 func_0021e898(s32);
void func_0021b4c8(s32);
s32 func_0021b7f0(void);
Eff *func_001f31a8(void *, s32);
void func_001f3e48(Eff *, Obj *);
void func_001f3758(s32);
void func_0021b820(void);
void func_0021cba8(Obj *, s32, s32, s32, s32);
void func_0021cb88(Obj *, s32, s32, s32, s32);
s32 func_0021b170(s32);
void func_00203788(Obj *, s32, s32, s32, u32);
void func_0021c9a0(Obj *, s32, s32);
void func_0021cb00(Obj *, s32, s32, s32, s32);
s32 func_0021dc38(s32);
#include "vm/script_vm.h"
void func_0010edb0(s32, s32, s32, s32, s32, s32);
s32 func_0021b800(s32);
void func_001f94f0(Obj *, s32, s32, s32, s32, s32, u32);
void func_0021e120(Obj *, s32, s32, s32);

void func_0021e8d8(Obj *o) {
    s32 ch, n, k;
    Eff *p;
    s32 t;
    if (func_001f42b8()) {
        func_0021e538();
        if (o->x28 == 0) {
            if (D_00425BC8->x8 & 0x4000) {
                func_0011d768(3);
                func_0021b5c8(0xC009B, 0, 128, 128, 5.0f);
                o->x28 = 1;
            } else {
                switch (o->x2c) {
                case 0:
                    ch = 0;
                    n = o->xd8;
                    if (D_00425BC8->x10 & 0x80000480) {
                        if (o->xda > 0) {
                            o->xda -= 16;
                            ch = 1;
                        }
                    } else if (D_00425BC8->x10 & 0x20000820) {
                        if (o->xda < (n - 1) << 4) {
                            o->xda += 16;
                            ch = 1;
                        }
                    }
                    if (ch) func_0011d768(ch);
                    D_00643250 = func_001fd668(o);
                    if (D_00425BC8->x8 & 0x1000) {
                        if (func_0021e898(D_00643274)) {
                            func_0011d768(4);
                        } else {
                            func_0011d768(2);
                            func_0021b4c8(D_00643274);
                            o->x2c++;
                        }
                    }
                    break;
                case 1:
                    if (func_0021b7f0()) {
                        p = func_001f31a8(D_003F5E30, 50);
                        if (p) {
                            func_001f3e48(p, o);
                            k = D_00643274;
                            p->x24 = D_003F53C0[k];
                            p->x2c = 256;
                            p->x28 = 0;
                            p->x30 = D_003F56A0[k];
                        }
                        o->x2c++;
                    }
                    break;
                case 2:
                    o->x2c = 0;
                    break;
                }
            }
        } else {
            if (func_0021b7f0()) {
                func_001f3758(D_00643110->x10);
                D_00643114 = 1;
            }
        }
    }
    func_0021b820();
    if (func_0021e898(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 2);
    } else if (o->x2c != 2) {
        func_0021cb88(o, 176, 8, 320, 2);
    } else if (func_0021b170(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 3);
    } else {
        func_0021cb88(o, 176, 8, 320, 3);
    }
    func_00203788(o, 372, 40, 486, 0x80C8C8C8);
    func_0021c9a0(o, 16, 72);
    func_0021cb00(o, 32, 108, 9, 30);
    func_0021cb00(o, 280, 108, 9, 30);
    t = (s32)func_001c2df0((s8 *)D_003F34F8, func_0021dc38(D_00643274));
    func_0010edb0(((o->xb0 - 0x7000) >> 4) + 32, ((o->xb4 - 0x7400) >> 4) + 84, 256, D_00643250 * 2, o->x90, t);
    if (((*(s32 *)&D_003E8E08) = o->x24) && o->xd8 - 1 == func_001fd668(o)) {
        func_001f94f0(o, 0, 282, 328, func_0021b800(6), 15, 0x50461E00);
    }
    if (D_00643118 == 2) func_0021e120(o, 416, 88, D_00643274);
}
#include "data/data_003F.h"
