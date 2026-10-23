#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x20];
    f32 f3c;
    u8 pad40[0x330];
    u64 f370;
} Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    s32 f6c;
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    u64 flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(void *m);
double sin(double);
double cos(double);
typedef struct {
    s32 x0;
    void *ent;
    f32 cur[3];
    f32 tgt[3];
    f32 spd;
    u8 pad24[0x304];
    u64 flags;
} VM2;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
    f32 d[3];
} Msg2;
double sqrt(double);


#include "data/pieces/D_0037A378.h"
void func_001d3e30(VM2 *vm) {
    Msg2 m;
    f32 dx, dy, dz, dist, spd;
    dx = vm->tgt[0] - vm->cur[0];
    dy = vm->tgt[1] - vm->cur[1];
    dz = vm->tgt[2] - vm->cur[2];
    dist = sqrt(dx * dx + dy * dy + dz * dz);
    spd = vm->spd;
    if (dist < spd || (D_0037A378 & 1)) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = vm->tgt[0];
        m.v[1] = vm->tgt[1];
        m.v[2] = vm->tgt[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
        vm->flags &= ~0x200ULL;
    } else {
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[3] = 1.0f;
    m.d[0] = (vm->tgt[0] - vm->cur[0]) / dist * spd;
    m.d[1] = (vm->tgt[1] - vm->cur[1]) / dist * spd;
    m.d[2] = (vm->tgt[2] - vm->cur[2]) / dist * spd;
    vm->cur[0] += m.d[0];
    vm->cur[1] += m.d[1];
    vm->cur[2] += m.d[2];
    m.v[0] = vm->cur[0];
    m.v[1] = vm->cur[1];
    m.v[2] = vm->cur[2];
    func_001c4640(&m);
    }
}
