/* A worker thread and its semaphores, 0x0010c0c8-0x0010c3c0:
 * func_0010c278 creates and starts the thread (CreateThread, CreateSema)
 * and func_0010c348 / func_0010c378 signal it (platform code: the kernel's
 * threads). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "m2c.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"

/* func_0010c0c8 (from hand/text_00100000_h2.c). */
s32 WaitSema(s32);
/* Callbacks run by the semaphore-driven thread func_0010c0c8. */
void func_0010c0c8(void) {
    s32 i;
    for (;;) {
        WaitSema(D_00495260);
        for (i = 0; i < 2; i++) {
            if (D_002B75A0[i].fn) {
                D_002B75A0[i].fn(D_002B75A0[i].arg);
                D_002B75A0[i].done = 1;
            }
        }
    }
}

/* func_0010c150 (from auto/text_00100000.c). */
M2C_UNK func_002581a0(s32);
void func_0010c150(void) {
    func_002581a0(D_00495260);
}

/* func_0010c170 (from hand/text_00100000_h2.c). */
void func_0010c170(void (*fn)(s32), s32 arg) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (!D_002B75A0[i].fn) {
            D_002B75A0[i].fn = fn;
            D_002B75A0[i].arg = arg;
            D_002B75A0[i].done = 0;
            return;
        }
    }
}

/* func_0010c1b8 (from hand/text_00100000_h2.c). */
void func_0010c1b8(void (*fn)(s32)) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (fn == D_002B75A0[i].fn) {
            D_002B75A0[i].fn = 0;
            D_002B75A0[i].arg = 0;
            D_002B75A0[i].done = 0;
            return;
        }
    }
}

/* func_0010c200 (from auto/text_00100000_13.c). */
s32 func_0010c200(void) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    var_a0 = ((s32 *)&D_002B75A0);
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 3;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

/* func_0010c240 (from auto/text_00100000_3.c). */
void func_0010c240(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 1;
    var_v0 = &D_002B75A0;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s32 *, 8) = 0;
        var_v0 += 0xC;
    } while (var_v1 >= 0);
}

/* func_0010c278 (from hand/text_00100000_h28.c). */
typedef struct { s32 currentCount; s32 maxCount; s32 initCount; s32 numWaitThreads; u32 attr; u32 option; } SemaParam;
typedef struct { s32 status; void (*entry)(void); void *stack; s32 stackSize; void *gpReg; s32 initPriority; s32 currentPriority; u32 attr; u32 option; s32 waitType; s32 waitId; s32 wakeupCount; } ThreadParam;
extern s32 ChangeThreadPriority(s32, s32);
extern s32 CreateSema(SemaParam *);
extern s32 CreateThread(ThreadParam *);
s32 D_0049525C ALIGNED(4);
extern s32 GetThreadId(void);
extern s32 StartThread(s32, void *);
extern u8 D_002B75C0[];
extern u8 D_00494050[];
extern volatile s32 D_00495258;
void func_0010c278(void) {
    ThreadParam tp;
    u8 pad[32];
    SemaParam sp;

    func_0010c240();
    ChangeThreadPriority(GetThreadId(), 30);
    sp.maxCount = 1;
    sp.currentCount = 0;
    sp.initCount = 0;
    sp.option = 0;
    D_00495258 = CreateSema(&sp);
    D_00495260 = CreateSema(&sp);
    tp.entry = func_0010c0c8;
    tp.stack = D_002B75C0;
    tp.stackSize = 0x4000;
    tp.initPriority = 40;
    tp.gpReg = D_00494050;
    D_0049525C = CreateThread(&tp);
    if (D_0049525C != -1) {
        StartThread(D_0049525C, 0);
    }
}

/* func_0010c348 (from auto/text_00100000_3.c). */
M2C_UNK SignalSema(s32);
#define WaitSema ((M2C_UNK (*)(s32)) WaitSema)
void func_0010c348(void) {
    SignalSema(D_00495260);
    WaitSema(D_00495258);
}
#undef WaitSema

/* func_0010c378 (from auto/text_00100000_9.c). */
M2C_UNK iReferSemaStatus(s32, void *);
M2C_UNK iSignalSema(s32);
void func_0010c378(void) {
    s32 sp[8];
    iReferSemaStatus(D_00495258, sp);
    if (M2C_FIELD(sp, M2C_UNK *, 0xC) != 0) {
        iSignalSema(D_00495258);
    }
}

