/* The script manager's resets (docs/modules.md "Session 48"),
 * 0x001c06f8-0x001c08e8, directly before the VM runtime (script_vm.c):
 * func_001c06f8 clears the manager's VM table choice (D_00389C90.x3034 /
 * x3038) and flag bit 58, then sets the event queue up (func_001c07f0) and
 * the effects (func_001dd170); func_001c0750 resets the VM state
 * (func_001c0830: the three 64-byte tables at D_003C39B0 and flag bit 42),
 * the library (src/vm/vm_lib.c), the voices, vm_util and the lists, and
 * clears D_0037A178 as func_001c07a8 does.  func_001c07f0 gives the queue
 * D_006297F8 (which script_vm.c posts to) a pool of 8 entries of 0x1c bytes
 * (D_00629808) and registers func_001c07c8, which empties it, as handler
 * 0xC352.  Read from the code, not proved by a boot. */
#include "common.h"
#include "vm/vm_mgr.h"
#include "data/data_003C.h"
#include "data/pieces/D_0037A178.h"

extern VmMgr D_00389C90;
extern u8 D_006297F8[];
void func_001c07f0(void);
void func_001c0830(void);
void func_001cd238(void);
void func_001dd170(void);
void func_001e01b8(void);
void func_001e4918(void);
void func_001ea430(void);
s32 func_0011f130(void *, s32);
s32 func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef10(s32, s32 (*)(void));

void func_001c06f8(void) {
    VmMgr **pb;
    VmMgr *b = &D_00389C90;
    pb = &b;
    (*pb)->x3034 = 0;
    b->x3038 = 0;
    b->f3070.x &= ~(1ULL << 58);
    func_001c07f0();
    func_001dd170();
}

void func_001c0750(void) {
    func_001c0830();
    func_001cd238();
    func_001e01b8();
    func_001ea430();
    func_001e4918();
    D_0037A178[0] = 0;
    D_0037A178[1] = 0;
    D_0037A178[2] = 0;
    D_0037A178[3] = 0;
}

void func_001c07a8(void) {
    D_0037A178[0] = 0;
    D_0037A178[1] = 0;
    D_0037A178[2] = 0;
    D_0037A178[3] = 0;
}

s32 func_001c07c8(void) {
    func_0011f130(D_006297F8, 0);
    return 0;
}

/* The queue's pool: 8 entries of 0x1c bytes. */
s32 D_00629808[0x3a] ALIGNED(8);

void func_001c07f0(void) {
    func_0011efa8(D_006297F8, D_00629808, 0x1C, 8);
    func_0011ef10(0xC352, func_001c07c8);
}

void func_001c0830(void) {
    s32 i;
    for (i = 0; i < 64; i++) D_003C39B0[i] = 0;
    for (i = 0; i < 64; i++) D_003C39F0[i] = 0;
    for (i = 0; i < 64; i++) D_003C3A30[i] = 0;
    D_00389C90.f3070.x &= ~(1ULL << 42);
}
