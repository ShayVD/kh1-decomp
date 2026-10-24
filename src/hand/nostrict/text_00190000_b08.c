/* ppp draw/frame callbacks around 0x197000-0x1a1000 (worker b08). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
extern s32 D_00616224;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
void func_001a9098(void *, void *);
extern PppMtx D_00616180, D_00616080;
extern PppMtx D_00616180;
#define D_00616224 (*(volatile s32 *) &D_00616224)
#undef D_00616224
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0, D_00616180;

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
#define D_00616224 (*(volatile s32 *) &D_00616224)
#undef D_00616224

/* needs make: uses rodata */

void *func_0017f958(void *, s32);

void *func_0017f958(void *, s32);
#include "data/data_0037.h"
