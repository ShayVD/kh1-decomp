/* An overlay run in place (docs/modules.md "Session 44"), 0x002335d8-0x00233610.
 * func_002335d8(i) loads the file D_00425BC0[i] ("xs_dh_break.x") to
 * 0x00F20000 with func_001205f0 and calls its entry there.  No C caller:
 * most likely a table entry.  An overlay the Vita build has to load another
 * way (docs/portability.md). */
#include "common.h"

/* D_00425BC0 stays extern: func_002335d8 indexes it with i, and D_00425BC4 (named by
 * text_001d0000.c) is its next entry, so the table is longer than its extent; floating
 * it alone hung the SHIFT_FLOAT build at boot (session 17). */
extern s32 D_00425BC0[];
void D_00F20000(s32, s32);
void func_001205f0(s32, void *);

void func_002335d8(s32 i) {
    func_001205f0(D_00425BC0[i], D_00F20000);
    D_00F20000(0, 0);
}
