#include "common.h"

typedef struct { u8 lo:3; u8 mode:2; u8 hi:3; } Sema5968;
#include "data/pieces/D_002C5968.h"
s32 func_0024d4a0(void);
void iSignalSema(s32);

void func_0024d7b0(s32 sema) {
    (*(volatile Sema5968 *)&D_002C5968).mode = 1;
    if (func_0024d4a0()) iSignalSema(sema);
}
