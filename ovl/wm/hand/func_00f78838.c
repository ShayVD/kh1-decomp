/* wm.x func_00f78838: the twin of dktitle.x func_00f26648 (tools/ovl/twins.py). */
#include "ovl.h"

s32 func_00120748(s32, s32, void *, s32);
void func_0024e468(s32);
extern s32 D_0108F6B0;
extern void func_00f78828(void);
s32 func_00f78838(s32 a0, s32 a1, s32 align, s32 *out) {
    D_0108F6B0 = -1;
    func_00120748(a0, a1, func_00f78828, 0);
    while (D_0108F6B0 == -1) {
        func_0024e468(1);
    }
    if (out != 0) *out = D_0108F6B0;
    if (align == 0) return a1 + D_0108F6B0;
    { s32 m = align - 1; return (a1 + D_0108F6B0 + m) & ~m; }
}
