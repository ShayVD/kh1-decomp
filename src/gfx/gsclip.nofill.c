/* Screen-range checks of GS vertices (docs/modules.md "Session 45"),
 * 0x00236e40-0x00236f00.  func_00236e40(v) is 1 when the vertex's x or y
 * (12.4 fixed point) is above 0xFFFF or its z above 0xFFFF28;
 * func_00236e80(a, b, c, d) is 1 when any of a quad's four is.  No C caller
 * in the main ELF. */
#include "common.h"

s32 func_00236e40(u32 *p) {
    if (p[2] > 0xFFFF28) return 1;
    if (p[0] > 0xFFFF) return 1;
    return p[1] > 0xFFFF;
}

s32 func_00236e80(u32 *a, u32 *b, u32 *c, u32 *d) {
    if (func_00236e40(a)) return 1;
    if (func_00236e40(b)) return 1;
    if (func_00236e40(c)) return 1;
    return func_00236e40(d) != 0;
}
