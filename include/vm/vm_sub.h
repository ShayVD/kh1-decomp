/* A script VM seen from +4 (docs/modules.md "Session 34" / "Session 35").
 *
 * Many VM library functions index the operand stack off vm + 4 (the `obj`
 * field) instead of off the record: `VmSub *s = (VmSub *)&vm->obj;` and
 * `s->stk[vm->sp]` read VmRec.stk[vm->sp].  On VmRec itself gcc indexes off
 * vm and the code differs, so those functions keep this view. */
#ifndef KH1_VM_VM_SUB_H
#define KH1_VM_VM_SUB_H

#include "common.h"
#include "data/types/vm_rec.h"

typedef struct {
    struct VmObj *obj;      /* VmRec.obj (0x004) */
    u8 pad4[0x17c];
    s32 stk[33];            /* VmRec.stk (0x184) */
} VmSub;

#endif /* KH1_VM_VM_SUB_H */
