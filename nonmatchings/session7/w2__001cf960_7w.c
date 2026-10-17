/* 7w: hand (strict): flags as union {u64 x; s32 i[2];} (like func_001d14f0 in text_001d0000_h43.c), flags |= 2 last before the call; only the flags ld is scheduled after the Msg sd instead of before */
#include "common.h"
typedef struct { u8 pad[16]; f32 pos[3]; } Act;
typedef struct {
    s32 x0;
    Act *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VMc;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
s32 func_001cf960(VMc *vm) {
    Msg m;
    m.type = 4;
    m.val = (u32)vm->stk[vm->sp] * 2;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 3] - vm->obj->pos[0];
    m.v[1] = vm->stk[vm->sp - 2] - vm->obj->pos[1];
    m.v[2] = vm->stk[vm->sp - 1] - vm->obj->pos[2];
    m.v[3] = 1.0f;
    vm->flags.x |= 2;
    func_001c4640(&m);
    vm->sp -= 4;
    return 2;
}
