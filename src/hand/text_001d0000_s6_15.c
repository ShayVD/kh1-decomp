#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0062.h"

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(Msg *m);
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
typedef W606Mem_304be8 Chr;
typedef Save_304be8 Save;

s32 func_001d3610(VM *vm) {
    s32 n = 0;
    s32 i, j, c;
    s32 k = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c < 20) {
            for (j = 0; j < ((u8 *)D_00304BE8)[c * 0x74 + 0x25]; j++) { if (D_00304BE8->m[c].sub.x22[j] == k) n++; }
            
        }
    }
    n += D_00304BE8->items[k];
    vm->stk[vm->sp] = n;
    return 2;
}
s32 func_001d3710(VM *vm) {
    s32 n = 0;
    s32 i, j, c;
    s32 k = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) { if (i == 3) break;
        c = D_00304BE8->x48e[i];
        if (c < 20) {
            for (j = 0; j < ((u8 *)D_00304BE8)[c * 0x74 + 0x25]; j++) { if (D_00304BE8->m[c].sub.x22[j] == k) n++; }
        }
    }
    n += D_00304BE8->items[k];
    vm->stk[vm->sp] = n;
    return 2;
}
s32 func_001d8680(VM *vm) {
    Msg m;
    m.type = 40;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    return 2;
}
s32 func_001d86e0(void) {
    Msg m;
    m.type = 40;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    return 2;
}
typedef struct { u8 pad0[0x10]; void *f10; VM *f14; s32 f18; u8 pad1c[0xc]; s32 f28; s32 f2c; } Tsk;
typedef struct { u8 pad0[0x68]; void *f68; } O68;
extern u8 D_0062A630[];
extern s32 D_0062A628;
extern s32 D_0062A608[];
s32 func_001dd5c0();
Tsk *func_0011f090(void *, s32, s32 (*)());
s32 func_001df7e0(VM *vm) {
    Tsk *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    s32 n, v; void *o;
    t->f2c = 7;
    n = D_0062A628;
    v = vm->stk[vm->sp];
    o = ((O68 *)vm->obj)->f68;
    t->f28 = v; t->f10 = o; t->f14 = vm; t->f18 = n; D_0062A608[n] = v;
    D_0062A628 = n + 1;
    if (D_0062A628 >= 8) D_0062A628 = 0;
    vm->sp--;
    return 2;
}
s32 func_001df890(VM *vm) {
    Tsk *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    s32 n, v; void *o;
    t->f2c = 8;
    n = D_0062A628;
    v = vm->stk[vm->sp];
    o = ((O68 *)vm->obj)->f68;
    t->f28 = v; t->f10 = o; t->f14 = vm; t->f18 = n; D_0062A608[n] = v;
    D_0062A628 = n + 1;
    if (D_0062A628 >= 8) D_0062A628 = 0;
    vm->sp--;
    return 2;
}
#include "data/bss_0062_mixed.h"
