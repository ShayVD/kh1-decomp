/* xs_simba.x func_00f21490: matched by hand. */
#include "ovl.h"

typedef struct { s32 flags; u8 pad4[0xC]; OvlVec pos; OvlVec v20; OvlVec v30; u8 pad40[0x30]; s32 f70; u8 pad74[0xDC]; f32 f150; u8 pad154[0x224]; s32 f378; } Act;
typedef struct { u8 pad[0x10]; u8 *p10; } Eff;
void func_00f218d0(void *, f32 *, f32);
s32 func_00130340(Act *, s32, f32);
void func_00130398(Act *, s32, f32);
void func_00130578(Act *, s32, f32);
s32 func_00137618(Act *);
void func_00f21148(Act *);
s32 func_00122ff8(s32);
void func_00f200a0(Act *);
s32 func_00148968(Act *, void *, s32);
void func_00135800(Act *, f32, f32);
void func_00137688(Act *, f32);
f32 func_001216d8(f32, f32, f32);
extern f32 D_002BBDFC;
extern s32 D_002E31B0;
extern void *D_00304B6C;
extern Act *D_00F21C34;
extern Act *D_00F21C38;
extern void *D_00F21C44;
extern s32 D_00FA6A10;
extern u8 D_00FA6F38[];
extern s32 D_00FA6F30;
extern s32 D_00FA7750;
extern Eff *D_00FA7754;
extern s32 D_00FA7758;
void func_00f21490(Act *a) {
    OvlVec v;

    PlatVu0CopyVector(v, D_00F21C34->pos);
    func_00f218d0(D_00FA6F38, v, 30.0f);
    if (a->flags & 0x400) {
        switch (a->f70) {
        case 0:
            if (a->f378 == 2 && D_00FA6A10 != 1) {
                func_00130398(a, 0x01000007, 0.0f);
                func_00130578(a, 0x40000000, 8.0f);
            }
            break;
        case 2:
            func_00130340(a, 6, 8.0f);
            break;
        }
    }
    if (func_00137618(a)) {
        switch (D_00FA6A10) {
        case 0:
            func_00f21148(a);
            break;
        case 1:
            if (func_00122ff8(D_002E31B0)) {
                func_00f200a0(a);
                break;
            }
            D_00F21C38->f150 = D_00F21C34->f150;
            PlatVu0CopyVector(a->v20, a->v30);
            a->v20[3] = 0.0f;
            break;
        case 100:
            D_00FA6F30 = (f32)D_00FA6F30 - D_002BBDFC;
            switch (D_00FA7758) {
            case 0:
                func_00130340(a, 204, 8.0f);
                func_00148968(a, D_00F21C44, 10);
                *D_00FA7754->p10 = 1;
                D_00FA7758 = 1;
                D_00FA6F30 = 12;
                break;
            case 1:
                if ((f32)D_00FA6F30 <= 0.0f) {
                    func_00135800(a, 0.0f, 20.0f);
                    D_00FA7758 = 2;
                    D_00FA6F30 = 20;
                }
                break;
            case 2:
                if ((f32)D_00FA6F30 <= 0.0f)
                    D_00304B6C = 0;
                break;
            }
            break;
        }
    } else {
        D_00FA7750 = 0;
    }
    func_00137688(a, func_001216d8(a->v30[3], a->f150, 0.06981317f));
}
