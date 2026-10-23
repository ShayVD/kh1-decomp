#include "common.h"
#include "data/bss_0063.h"
/* Script VM handlers: obj at +4, top index at +0x180, value stack at +0x184.
 * The stack is indexed off &vm->u.s (vm+4) with a local copy of sp. */
typedef struct {
    void *obj;
    u8 pad4[0x17c];
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    union {
        Sub s;
        struct { void *obj; u8 pad[0x178]; s32 sp; } h;
    } u;
} VM;
extern u64 D_0038CD00;
#include "data/pieces/D_003DACA0.h"
s32 func_0011e340(void *);
#include "data/pieces/D_003DAD3C.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_001e0000_h20.h"
#include "data/pieces/D_003DC390.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_006314D0;
extern s32 D_006314D8;
#include "data/pieces/D_003DABD4.h"
void func_001e7fe0();
void func_0011ec08(s32, s32, s32, void (*)());
extern s32 D_006314CC;
extern s32 D_006314DC;
void func_001e8308();
void func_0011eb88(s32, s32, s32, void (*)());
extern volatile s32 D_002C58C0;
s32 func_0011c808(s32);
#include "data/pieces/D_0037A378.h"
void func_0011d080(s32, s32);
void func_0011d0d8(s32, s32);
void func_0011d108(s32, s32, s32);
s32 func_0011e368(s32, s32);
void func_0011d350(s32, s32);


/* func_001ddfb8, func_001de030, func_001de0b0, func_001de290, func_001df170, func_001df1d8, func_001df310, func_001df698, func_001df940, func_001dfb20 are in src/event/effect.c. */









/* func_001e16b0, func_001e1748, func_001e17e0, func_001e25c8, func_001e26b8 are in src/screen/screen.c. */





/* func_001e2778, func_001e2a40, func_001e30f8, func_001e3aa8, func_001e3ed0, func_001e3fc8, func_001e42b0 are in src/shop/shop.c. */







/* func_001e4a68, func_001e5788, func_001e63a8, func_001e6450, func_001e6580, func_001e6e20, func_001e7930, func_001e79a0, func_001e7a68, func_001e7ad8, func_001e7d90, func_001e7e00 are in src/list/list.c. */












s32 func_001e8178(void) {
    if (func_0011e340(0)) return 0;
    func_0011ec08(D_006314D0, ((s32)D_003DABD4), D_006314D8, func_001e7fe0);
    return 4;
}

s32 func_001e82e0(VM *vm) {
    if ((s32)(D_0038CD00 >> 56) & 1) return 4;
    return 2;
}

s32 func_001e84a0(void) {
    if (func_0011e340(0)) return 0;
    func_0011eb88(D_006314CC, ((s32)D_003DABD4), D_006314DC, func_001e8308);
    return 4;
}

s32 func_001e8608(VM *vm) {
    if ((s32)(D_0038CD00 >> 51) & 1) return 4;
    return 2;
}

s32 func_001e89c0(VM *vm) {
    if ((s32)(D_0038CD00 >> 57) & 1) return 4;
    return 2;
}

s32 func_001e8b50(VM *vm) {
    D_002C58C0 |= 0x8000;
    if (!func_0011c808(vm->u.s.stk[vm->u.h.sp] - 1)) return 4;
    vm->u.h.sp -= 1;
    return 2;
}

s32 func_001e8c88(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 1], b = s->stk[i];
    if (!(D_0037A378 & 1)) {
        func_0011d080(a, b);
        i = vm->u.h.sp;
    }
    vm->u.h.sp = i - 2;
    return 2;
}

s32 func_001e8cf0(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d0d8(s->stk[i - 1], s->stk[i]);
    vm->u.h.sp -= 2;
    return 2;
}

s32 func_001e8d40(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d108(s->stk[i - 2], s->stk[i - 1], s->stk[i] * 8);
    vm->u.h.sp -= 3;
    return 2;
}

s32 func_001e8de8(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    func_0011d350(s->stk[i - 1], s->stk[i]);
    vm->u.h.sp -= 2;
    return 2;
}
#include "data/bss_0062_typed.h"
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_003D.h"
#include "data/data_002C.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
