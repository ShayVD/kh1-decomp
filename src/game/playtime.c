/* The play timer (docs/modules.md "Session 36"), 0x001ee118-0x001ee388:
 * func_001ee118 is the play time in 1/60 s (the frame counter D_002BBDF4
 * times the scale D_002BBDEC); the others split it into hours (216000),
 * minutes and seconds.  playtime.nofill.c holds the hundredths. */
#include "common.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDEC.h"

u32 func_001ee118(void);

u32 func_001ee118(void) {
    return *(volatile u32 *)&D_002BBDF4 * D_002BBDEC;
}

u32 func_001ee198(void) {
    return func_001ee118() / 216000U;
}

u32 func_001ee1d0(void) {
    return func_001ee118() / 3600U;
}

u32 func_001ee200(void) {
    return func_001ee118() / 60U;
}

void func_001ee230(u32 *a, u32 *b, u32 *c, u32 *d) {
    u32 t = func_001ee118();
    *a = t / 216000U;
    t = t % 216000U;
    *b = t / 3600U;
    t = t % 3600U;
    *c = t / 60U;
    *d = t % 60U;
}

u32 func_001ee2d0(void) {
    return func_001ee118() / 216000U;
}

u32 func_001ee308(void) {
    return (u32) (func_001ee118() / 3600U) % 60U;
}

u32 func_001ee348(void) {
    return (u32) (func_001ee118() / 60U) % 60U;
}
