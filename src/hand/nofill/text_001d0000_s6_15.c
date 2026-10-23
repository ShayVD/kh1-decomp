#include "common.h"

typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
    f32 f330;
} VM;
typedef struct { u8 pad0[0x1f]; u8 n; u8 items[0x74 - 0x20]; } Chr;
typedef struct { u8 pad0[6]; Chr ch[10]; u8 a48e[11]; u8 a499[1]; } Save;
#include "data/pieces/D_00304BE8.h"

extern f32 D_002BBDFC;
/* rodata */
typedef struct { u8 pad0[0x3070]; u64 f3070; } Big02;
extern Big02 D_00389C90;
#include "data/pieces/D_0037A378.h"
extern char D_003DAC40[][6];
#include "data/pieces/D_003DACA0.h"
typedef Tbl_3daca0 Tbl;
s32 func_0011e340(void *);
s32 func_001559f0(s32, s32);
void func_001e01f0(void);

s32 sprintf(char *, const char *, ...);
s32 func_001e0220(VM *vm) {
    char buf[512];
    s32 *pp;
    if (!(D_0037A378 & 1)) {
        if (func_0011e340(0) == 0) {
            sprintf(buf, "voice/event/%s_%03d.vset", D_003DAC40[vm->stk[vm->sp - 1]], vm->stk[vm->sp]);
            pp = (s32 *)&D_003DACA0;
            *pp = func_001559f0(60, 4); func_00120748(buf, *pp, func_001e01f0, 0);
            D_00389C90.f3070 |= 0x8000ULL << 37;
        } else {
            return 4;
        }
    }
    vm->sp -= 2;
    return 2;
}
double ceil(double);
void func_0011e220(void *, s32, s32, s32);
s32 func_001e0338(VM *vm) {
    Tbl *t = D_003DACA0;
    s32 k = vm->stk[vm->sp - 2];
    s32 s; void *p;
    f32 a, b;
    s = *(t->tbl + k); p = (u8 *)t + *(t->tbl + k + t->n); a = vm->stk[vm->sp - 1] / 100.0f; b = vm->stk[vm->sp] / 100.0f;
    if (!(D_0037A378 & 1)) {
        func_0011e220(p, s, ceil(a * 16383.0f), ceil(b * 16383.0f));
    }
    vm->flags.x |= 4; vm->f2f4 = 4.0f; vm->sp -= 3;
    return 6;
}
void func_001ed6b0(void *);
s32 func_001e0498(VM *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) {
        func_001ed6b0((void *)-1);
        vm->sp--;
        return 2;
    }
    {
        Tbl *t = D_003DACA0;
        func_001ed6b0((u8 *)t + *(t->tbl + k + t->n));
    }
    vm->sp--;
    return 2;
}
s32 func_001e0528(VM *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) { if (func_0011e340(0)) return 4; }
    else { Tbl *t = D_003DACA0; if (func_0011e340((u8 *)t + *(t->tbl + k + t->n))) return 4; }
    vm->sp--;
    return 2;
}
#include "data/data_003D.h"
#include "data/pieces/D_002BBDFC.h"
