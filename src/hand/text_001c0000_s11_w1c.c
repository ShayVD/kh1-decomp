#include "common.h"
/* func_001cf960 (s11w1, hand strict): from s8 w4 (7w, 3 LCS). The VM flags at 0x328 are u64 bitfields directly in the VM struct, which also has an f32 (x2f4): the bitfield store `vm->b1 = 1` gets the VM struct alias set, so sd flags still conflicts with the f32 pos loads (stays after them) but ld flags no longer conflicts with the Msg stores in sched2. */
typedef struct { u8 pad[16]; f32 pos[3]; } Act;
typedef struct {
    s32 x0;
    Act *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 x2f4;
    u8 pad2f8[0x30];
    u64 b0:1, b1:1, rest:62;
    u8 pad330[0x20];
} __attribute__((aligned(8))) VMc;
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
    vm->b1 = 1;
    func_001c4640(&m);
    vm->sp -= 4;
    return 2;
}
