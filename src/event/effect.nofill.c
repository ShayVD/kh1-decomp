/* func_001ddbf8 of src/event/effect.c: needs nofill (s6_15b). */
#include "common.h"
#include "event/effect.h"
#include "vm/vm_mgr.h"

extern VmMgr D_00389C90;
void func_001763f0(void *);

/* The .dpx is loaded: set up the effects, clear bit 44 of f3070. */
void func_001ddbf8(void)
{
    func_001763f0(D_0062A220);
    D_00389C90.f3070.x &= ~(1ULL << 44);
}
