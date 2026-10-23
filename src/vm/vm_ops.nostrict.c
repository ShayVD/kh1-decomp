/* src/vm/vm_ops.c's func_001c1980, which needs -fno-strict-aliasing
 * (flag mode nostrict; docs/modules.md "Flags"). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"

/* Jump VM `v` to `pc` at return level `lvl`: a lower level saves the current
 * pc on the return stack first. */
s32 func_001c1980(VmRec *v, s32 lvl, s32 pc) {
    if (lvl < v->rsp) {
        v->x2f4 = 0;
        v->ret[v->rsp] = v->pc;
        v->rsp = lvl;
        v->pc = pc;
        v->fl.x &= ~4;
    } else if (lvl == v->rsp) {
        v->pc = pc;
        v->x2f4 = 0;
        v->fl.x &= ~4;
    }
    v->ret[lvl] = pc;
    return 1;
}
