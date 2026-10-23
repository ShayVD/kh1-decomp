#include "common.h"
#include "data/pieces/D_002C5968.h"

s32 func_0024d4a0(void);
void iSignalSema(s32);

void func_0024d7b0(s32 sema) {
    (*(volatile Sema_2c5968 *)&D_002C5968).mode = 1;
    if (func_0024d4a0()) iSignalSema(sema);
}
