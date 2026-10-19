#include "common.h"
/* func_001c99a8 (s11w1, hand strict, CONTEXT_ONLY func_001c6890 above): from s10 w6 (10w). The camera flags word is u64 bitfields directly in Cam (`D_003C5510.b5 = 1`) instead of the punning union u { u64 flags; struct { s32 lo; f32 f4, f8, ... } s; } (alias set 0); f8 is a plain field. Union-free stores fix the sched1 load order and FP registers. */
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4a;
typedef struct {
    u64 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, rest:58;
    f32 f8, fc, f10, f14;
    f32 t0;
    f32 t1;
    f32 t2;
    u8 pad24[4];
    s32 x28;
    s32 x2c;
    s32 x30;
    u8 pad34[0xc];
    V4a p40;
    V4a p50;
    V4a p60;
    V4a p70;
    V4a p80;
    V4a p90;
    f32 r[3];
    s32 xac;
    f32 fb0;
    s32 xb4;
    u8 padb8[8];
    V4a v0;
    V4a a, b, c, d, e;
    f32 f120, f124, f128, f12c;
} Cam;
extern Cam D_003C5510;
void func_002675a8(void *, void *);
CONTEXT_ONLY void func_001c6890(void) { V4a a; func_002675a8(&a, &D_003C5510.p40); }
void func_001e9fe8(V4a *d, V4a *s);
s32 func_001c99a8(VM *vm) {
    s32 m;
    f32 d;
    func_001c6890();
    D_003C5510.b5 = 1;
    m = vm->stk[vm->sp - 3];
    d = (f32)vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.x30 = m;
    D_003C5510.p80.x = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
    D_003C5510.p80.y = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f;
    D_003C5510.p80.z = vm->stk[vm->sp] * 3.1415928f / 180.0f;
    D_003C5510.f8 = d;
    func_001e9fe8(&D_003C5510.p80, &D_003C5510.p80);
    D_003C5510.p50.x = D_003C5510.b.x;
    D_003C5510.p50.y = D_003C5510.b.y;
    D_003C5510.p50.z = D_003C5510.b.z;
    vm->sp -= 5;
    return 2;
}
