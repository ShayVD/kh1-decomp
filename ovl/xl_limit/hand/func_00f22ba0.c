/* xl_limit.x func_00f22ba0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; s32 f14; } Obj;
typedef struct { s32 f0; s32 f4; Obj *f8; s32 pad[5]; } Ent;
void func_00106a58(s32);
void func_001625c8(void *, void *);
void func_0013bde8(void *, void *, s32);
void func_0011efa8(void *, void *, s32, s32);
void func_0011ef10(s32, void *);
s32 func_0011f130(void *, s32);
void func_00f22870(s32);
s32 func_0013be00(void *);
void func_00f21e60(void);
extern u32 D_002C5958;
extern u8 *D_00F23F90;
extern u8 D_00F23FA0[];
extern u8 D_00F23EA0[];
extern u8 D_00F233C0[];
extern u8 D_00F23F80[];
extern u8 D_00F23F00[];
extern Ent D_00F23290[];
s32 func_00f22ba0(u16 *pad) {
    s32 i;
    Ent *e;
    if ((D_002C5958 & 0x810000) != 0x10000) {
        if ((D_002C5958 >> 26) & 1) {
            D_002C5958 &= ~0x04000000;
            func_00106a58(61);
        }
        return 4;
    }
    func_001625c8(D_00F23F90 + 0xD0, D_00F23FA0);
    if (*pad & 0x10) {
        func_0013bde8(D_00F23EA0, D_00F233C0, 6);
        func_0011efa8(D_00F23F80, D_00F23F00, 0x40, 2);
        func_0011ef10(100000, func_00f21e60);
    }
    func_0011f130(D_00F23F80, 0);
    e = D_00F23290;
    for (i = 0; i < 6; i++, e++) {
        if (e->f8 != 0) {
            if ((e->f8->f14 & 3) != 1) {
                e->f8 = 0;
            } else {
                func_00f22870(i);
            }
        }
    }
    return func_0013be00(D_00F23EA0) ? 0 : 4;
}
