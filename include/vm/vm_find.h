/* Finding a script VM in its tables (src/vm/vm_find.nofill.c;
 * docs/modules.md).  Not in script_vm.h: many callers still declare
 * func_001e98d0 with their own VM view as the return type. */
#ifndef KH1_VM_VM_FIND_H
#define KH1_VM_VM_FIND_H

#include "common.h"
#include "data/types/vm_rec.h"

/* The VM with index `b` in the current table of `kind` (0 or 1), or 0. */
VmRec *func_001e98d0(s32 kind, s32 b);
/* The index of `p` in the current table of `kind`, or -1. */
s32 func_001e99e8(s32 kind, VmRec *p);
/* The VM of `kind` whose func_00123618(x0) is `id`, or 0. */
VmRec *func_001e9b98(s32 kind, s32 id);

#endif /* KH1_VM_VM_FIND_H */
