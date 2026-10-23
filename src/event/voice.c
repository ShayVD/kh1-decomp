/* Event voices (docs/modules.md "Session 34"), 0x001e01b8-0x001e05a8.
 *
 * The script functions that load "voice/event/<name>_<n>.vset" into
 * D_003DACA0 (func_001e0220) and play / wait for its clips.  Their data
 * (the name table D_003DAC40 and D_003DACA0) follows the effects'
 * D_003DABD8 and is used by nothing else; they share no state with
 * src/event/effect.c, so they are their own file.  func_001e0220,
 * func_001e0338, func_001e0498 and func_001e0528 are in voice.nofill.c. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "data/pieces/D_003DACA0.h"

extern VmMgr D_00389C90;
extern u64 D_0038CD00;
u32 func_001559f0(s32, s32);

/* Allocate the voice set's buffer (60 blocks; script_vm's loader). */
void func_001e01b8(void) {
    D_003DACA0 = (Tbl_3daca0 *)(func_001559f0(0x3C, 4));
}

/* The voice set is loaded: clear bit 52 of f3070. */
void func_001e01f0(void) {
    D_00389C90.f3070.x = D_00389C90.f3070.x & ~(1ULL << 52);
}

/* func_001e0220 is in voice.nofill.c. */

/* Wait until the voice set is loaded (bit 52 of D_0038CD00). */
s32 func_001e0318(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 52) & 1) return 4;
    return 2;
}

/* func_001e0338, func_001e0498 and func_001e0528 are in voice.nofill.c. */
