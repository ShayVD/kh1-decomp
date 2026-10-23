/* The event voice functions of src/event/voice.c that need nofill (s6_15). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_003DACA0.h"

extern VmMgr D_00389C90;
extern char D_003DAC40[][6];
typedef Tbl_3daca0 Tbl;
s32 func_0011e340(void *);
s32 func_001559f0(s32, s32);
s32 func_00120748();
void func_001e01f0(void);
s32 sprintf(char *, const char *, ...);

/* Load voice/event/<D_003DAC40[stk[sp-1]]>_<stk[sp]>.vset (bit 52 of
 * f3070 until it is in); wait while a voice plays. */
s32 func_001e0220(VmRec *vm) {
    char buf[512];
    s32 *pp;
    if (!(D_0037A378 & 1)) {
        if (func_0011e340(0) == 0) {
            sprintf(buf, "voice/event/%s_%03d.vset", D_003DAC40[vm->stk[vm->sp - 1]], vm->stk[vm->sp]);
            pp = (s32 *)&D_003DACA0;
            *pp = func_001559f0(60, 4); func_00120748(buf, *pp, func_001e01f0, 0);
            D_00389C90.f3070.x |= 0x8000ULL << 37;
        } else {
            return 4;
        }
    }
    vm->sp -= 2;
    return 2;
}

double ceil(double);
void func_0011e220(void *, s32, s32, s32);

/* Play clip stk[sp-2] of the set at volumes stk[sp-1], stk[sp] percent;
 * wait 4 frames. */
s32 func_001e0338(VmRec *vm) {
    Tbl *t = D_003DACA0;
    s32 k = vm->stk[vm->sp - 2];
    s32 s; void *p;
    f32 a, b;
    s = *(t->tbl + k); p = (u8 *)t + *(t->tbl + k + t->n); a = vm->stk[vm->sp - 1] / 100.0f; b = vm->stk[vm->sp] / 100.0f;
    if (!(D_0037A378 & 1)) {
        func_0011e220(p, s, ceil(a * 16383.0f), ceil(b * 16383.0f));
    }
    vm->fl.x |= 4; vm->x2f4 = 4.0f; vm->sp -= 3;
    return 6;
}

void func_001ed6b0(void *);

/* Stop clip stk[sp] (-1: all). */
s32 func_001e0498(VmRec *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) {
        func_001ed6b0((void *)-1);
        vm->sp--;
        return 2;
    }
    {
        Tbl *t = D_003DACA0;
        func_001ed6b0((u8 *)t + *(t->tbl + k + t->n));
    }
    vm->sp--;
    return 2;
}

/* Wait while clip stk[sp] (-1: any) plays. */
s32 func_001e0528(VmRec *vm) {
    s32 k = vm->stk[vm->sp];
    if (k == -1) { if (func_0011e340(0)) return 4; }
    else { Tbl *t = D_003DACA0; if (func_0011e340((u8 *)t + *(t->tbl + k + t->n))) return 4; }
    vm->sp--;
    return 2;
}
