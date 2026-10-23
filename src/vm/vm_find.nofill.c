/* Finding a script VM (0x001e98d0-0x001e9d00; docs/modules.md
 * "src/vm/vm_find.nofill.c").
 *
 * The VMs live in five tables of VmRec: D_0038D170 / D_0039A580 (kind 0,
 * which one by VmMgr.x3034), D_003A7990 / D_003B4DA0 (kind 1, by x3038)
 * and D_003C3A70 (all kinds while VmMgr.x316c is set); each has its count
 * just before it.  These three walk them; the handlers and the script
 * functions call them, far from src/vm/script_vm.c, so they are their own
 * file.  func_001e98d0 matches only without gas's delay slot filling (the
 * nofill mode, docs/modules.md "Flags"); the other two match either way. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"
#include "vm/vm_find.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003C3A70.h"

extern VmMgr D_00389C90;
extern s32 D_0039A570, D_003A7980, D_003B4D90, D_003C21A0, D_003C54F0;
s32 func_00123618(s32);

/* The VM with index `b` in the current table of `kind`, or 0. */
VmRec *func_001e98d0(s32 kind, s32 b) {
    if (D_00389C90.x316c) return &D_003C3A70[b];
    if (kind == 1) {
        if (!D_00389C90.x3038) {
            if (b < D_003B4D90) return &D_003A7990[b];
        } else {
            if (b < D_003C21A0) return &D_003B4DA0[b];
        }
    } else {
        if (!D_00389C90.x3034) {
            if (b < D_0039A570) return &D_0038D170[b];
        } else {
            if (b < D_003A7980) return &D_0039A580[b];
        }
    }
    return 0;
}

/* The index of `p` in the current table of `kind`, or -1. */
s32 func_001e99e8(s32 kind, VmRec *p) {
    s32 i;
    if (D_00389C90.x316c) {
        for (i = 0; i < D_003C54F0; i++) if (&D_003C3A70[i] == p) return i;
    } else if (kind == 1) {
        if (D_00389C90.x3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) if (&D_003A7990[i] == p) return i;
        } else {
            for (i = 0; i < D_003C21A0; i++) if (&D_003B4DA0[i] == p) return i;
        }
    } else {
        if (D_00389C90.x3034 == 0) {
            for (i = 0; i < D_0039A570; i++) if (&D_0038D170[i] == p) return i;
        } else {
            for (i = 0; i < D_003A7980; i++) if (&D_0039A580[i] == p) return i;
        }
    }
    return -1;
}

/* The VM of `kind` whose id (func_00123618 of VmRec.x0) is `id`, or 0.
 * (The second kind-1 table walks D_0039A580 with D_003A7980's count: as in
 * the original.) */
VmRec *func_001e9b98(s32 kind, s32 id) {
    s32 i;
    if (kind == 1) {
        if (!D_00389C90.x3038) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123618(D_003A7990[i].x0) == id) return &D_003A7990[i];
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123618(D_0039A580[i].x0) == id) return &D_0039A580[i];
            }
        }
    } else {
        if (!D_00389C90.x3034) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123618(D_0038D170[i].x0) == id) return &D_0038D170[i];
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123618(D_0039A580[i].x0) == id) return &D_0039A580[i];
            }
        }
    }
    return 0;
}
