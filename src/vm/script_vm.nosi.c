/* src/vm/script_vm.c's func_001c1718, which needs -fno-sched-interblock
 * (flag mode nosi; docs/modules.md "Flags").  It was below func_001c0bf0 in
 * the original file: the CONTEXT_ONLY stub stands in for that definition. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "data/data_0038.h"

void *func_00232cc0(s32);

CONTEXT_ONLY s64 func_001c0bf0(s64 x, u32 type) { return x; }

/* op 17: pop into s32 variable `a` */
s32 func_001c1718(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    if (a < 2048) {
        *(s32 *)(p1 + a) = func_001c0bf0(v->stk[v->sp], 4);
        v->sp--;
    } else if (a < 2304) {
        a -= 2048;
        *(s32 *)(p1 + a + 2048) = func_001c0bf0(v->stk[v->sp], 4);
        v->sp--;
    } else if (a < 2816) {
        a -= 2304;
        if ((s32)(v->fl.x >> 5) & 1) {
            D_0038B4C4[a] = v->stk[v->sp];
            v->sp--;
        } else {
            D_0038ACC4[a] = v->stk[v->sp];
            v->sp--;
        }
    } else {
        a -= 3392;
        *(s32 *)(p2 + a) = func_001c0bf0(v->stk[v->sp], 4);
        v->sp--;
    }
    return 2;
}
