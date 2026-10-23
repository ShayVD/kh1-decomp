#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

typedef W606Mem_304be8 S4BE8e;
void func_00207298(s32);
void func_002072e0(s32);

void func_0021b800(s32);
void func_002213a8(s32 a0) {
    if (a0 <= 0) func_0021b800(48);
    else if (a0 < 6) func_0021b800(49);
    else if (a0 < 10) func_0021b800(50);
    else if (a0 < 15) func_0021b800(a0 + 41);
    else func_0021b800(56);
}

extern s32 D_00643674;
extern u8 D_00643668[];
s32 func_00207250(s32);
void func_00222ab0(void) {
    s32 i;
    for (i = 0; i < D_00643674; i++) {
        if (!func_00207250(D_00643668[i])) {
            func_00207298(5);
            return;
        }
    }
    func_002072e0(5);
}

/* needs make: uses rodata */
#include "data/data_003F.h"
