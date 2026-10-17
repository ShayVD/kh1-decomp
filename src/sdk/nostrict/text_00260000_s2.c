/* libgcc frame.c: __register_frame_info / __register_frame_info_table
 * shapes. Match with ee-gcc 2.96 -O2 -G0 -fno-strict-aliasing (filled or
 * no_fill); fail under strict aliasing (store order). */
#include "common.h"
s32 WaitSema(s32);
s32 SignalSema(s32);
typedef struct Obj { void *pc_begin, *pc_end; void *fde_begin; void **fde_array; u32 count; struct Obj *next; } Obj;
extern s32 D_0046AF14;   /* object mutex (semaphore id) */
extern Obj *D_0066FAD0;  /* object list */

void func_00263db8(void *begin, Obj *ob) {
    s32 *m = &D_0046AF14;
    Obj **op;
    s32 s;
    ob->fde_begin = begin;
    ob->pc_begin = ob->pc_end = 0;
    ob->fde_array = 0;
    ob->count = 0;
    WaitSema(*m);
    op = &D_0066FAD0;
    s = *m;
    ob->next = *op;
    *op = ob;
    do { SignalSema(s); } while (0);
}

void func_00263e50(void *begin, Obj *ob) {
    s32 *m = &D_0046AF14;
    Obj **op;
    s32 s;
    ob->fde_begin = begin;
    ob->fde_array = begin;
    ob->pc_begin = ob->pc_end = 0;
    ob->count = 0;
    WaitSema(*m);
    op = &D_0066FAD0;
    s = *m;
    ob->next = *op;
    *op = ob;
    do { SignalSema(s); } while (0);
}
