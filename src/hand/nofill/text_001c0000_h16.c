#include "common.h"

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;

typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;

void func_00122f58(Actor *, f32, f32, f32);

