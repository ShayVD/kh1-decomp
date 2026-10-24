/* The frame captured to D_00F20000 (capture.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s6_01_p2.h"
#include "data/types/nostrict_text_00100000_s6_01.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F30.h"
#include "data/types/nostrict_text_00100000_s6_01_p.h"
#include "data/pieces/D_002BBDE0.h"

/* func_0010a378 (from hand/nostrict/text_00100000_s6_01.c). */
extern void func_00109f88(void);
extern s32 func_00106b18(void *);
extern u64 D_002B6668;
extern u8 D_002B66B0[];
extern void func_00106b18_v(void *) __asm__("func_00106b18");
static inline void inl_a378(void *p, u64 c) {
    D_002B6668 = c;
    func_00106b18_v(p);
}
s32 func_0010a378(void) {
    func_00109f88();
    inl_a378(D_002B66B0, 0x180808080ULL);
    return 0;
}

