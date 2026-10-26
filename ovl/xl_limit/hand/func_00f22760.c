/* xl_limit.x func_00f22760: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x44]; s32 f44; u8 pad2[0xBE - 0x48]; u16 fBE; } Info;
typedef struct { u8 pad[0x6C]; Info *f6C; } Act;
typedef struct { u8 pad[0x10]; s32 f10; s32 f14[3]; u8 f20[2][16]; } Ctl;
Ctl *func_0011f090(void *, s32, void *);
s32 func_00122ff8(Act *);
void func_001315c0(Act *, s32, void *, f32);
void func_00141540(Act *, s32);
s32 func_00141608(Act *, s32);
void func_00f225b0(void);
extern Act *D_002E26A0[];
extern u8 D_00F23F80[];
s32 func_00f22760(void) {
    s32 i;
    Act *a;
    Ctl *c;
    for (i = 0; i < 3; i++) {
        a = D_002E26A0[i];
        if (func_00122ff8(a) != 0) {
            func_00141608(a, -a->f6C->fBE);
            func_00141540(a, -a->f6C->f44);
        }
    }
    c = func_0011f090(D_00F23F80, 0, func_00f225b0);
    c->f10 = 0;
    for (i = 0; i < 2; i++) {
        a = D_002E26A0[i + 1];
        if (func_00122ff8(a) == 0) {
            a = D_002E26A0[0];
        }
        func_001315c0(a, 0x8003, c->f20[i], 0.0f);
        c->f14[i] = 0;
    }
    return 1;
}
