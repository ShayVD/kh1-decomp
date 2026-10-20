#include "common.h"


typedef struct {
    u8 pad0[0x14];
    f32 x14;
    u8 pad18[0x3b0 - 0x18];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 v3c0[4];
} Pc;
f32 sinf(f32);
void func_0014cd38(Pc *);
extern f32 D_002BBDFC;

static inline f32 mn(f32 x, f32 l) { return x < l ? x : l; }
void func_0014cdc8(Pc *o, f32 *v) {
    f32 a;
    f32 b;
    f32 y;

    a = o->x3b0;
    b = o->x3b8;
    if (a < b) {
        a = sinf(a / b * 3.1415928f * 0.5f);
        a = sinf(a * 3.1415928f * 0.5f);
        y = o->x3b4 + a * o->x3bc; v[1] = y - o->x14;
        func_0014cd38(o);
    } else {
        a -= b;
        y = o->x3b4 + o->x3bc + 0.4846938625f * a * a * 0.5f;
        v[1] = mn(y - o->x14, D_002BBDFC * 20.0f);
    }
    o->v3c0[1] = v[1];
}

/* func_001cb738 (session 7, w3): written like its matched sibling func_001cb7d0 (text_001c0000_h67.c). */
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
    f32 f330;
    u8 pad334[0xc];
    f32 f340[3];
} VM;
typedef struct { f32 a[4]; s32 b[3]; s32 pad; u64 d[2]; } CamS;
typedef struct { u8 st[4]; u8 x4[12]; u16 tbl[8][256]; s32 cnt[8]; s8 ids[4]; u8 pad1034[0x3034 - 0x1034]; s32 f3034; s32 f3038; u8 pad303c[0x3070 - 0x303c]; union { u64 x; s32 i[2]; } f3070; union { u64 x; s32 i[2]; } f3078; u8 pad3080[0x14]; s32 f3094; u8 pad3098[0x316c - 0x3098]; s32 f316c; u8 pad3170[0x3460 - 0x3170]; f32 dur; f32 t; u8 pad3468[8]; CamS start; CamS tgt; } Str;
extern Str D_00389C90;
extern s32 D_00389C80;
extern char *D_00388480[];
extern u8 D_003C5640[];
extern s32 D_002BBAB0;
s32 func_001cb738(VM *vm) {
    s32 idx = vm->stk[vm->sp - 1];
    s32 val = vm->stk[vm->sp];
    vm->sp -= 2;
    D_002BBAB0 = val;
    D_00388480[D_00389C80] = D_003C5640;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = *(u16 *)&D_00389C80;
    D_00389C80++;
    return 2;
}

/* func_001d0380 (session 7, w3): the flag test + return tail is written in both branches (jump2 cross-jumps them back); with one shared tail it needs -fno-sched-interblock (hand/nosi). */
typedef struct { u8 pad0[0x10]; f32 pos[3]; u8 pad1c[0x20]; f32 f3c; u8 pad40[0x330]; u64 f370; } Ent2;
typedef struct {
    s32 x0;
    Ent2 *ent;
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
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, brest:26;
    u32 hi;
    f32 f330;
    u32 pad334;
    u64 q338;
} VM2;
extern s32 D_002BCDE4, D_002BCC90;
void func_001c2ec8(s32 a, s32 b);
void func_001c3770(s32 a, s32 b);
s32 func_001d0380(VM2 *vm) {
    s32 a, b, n;
    b = D_00389C90.f3038;
    a = D_00389C90.f3034;
    n = vm->stk[vm->sp];
    if (n < 100) {
        func_001c2ec8(D_002BCDE4, n);
        if ((vm->b5 == 1 && b) || (vm->b5 != 1 && a)) goto r8;
        vm->sp--;
        return 10;
    } else {
        n -= 100;
        func_001c3770(D_002BCC90, n);
        if ((vm->b5 == 1 && b) || (vm->b5 != 1 && a)) goto r8;
        vm->sp--;
        return 10;
    }
r8:
    return 8;
}
#include "data/data_002B.h"
#include "data/data_003C.h"
