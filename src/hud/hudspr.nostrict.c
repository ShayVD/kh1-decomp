/* The HUD's drawing helpers (docs/modules.md "Session 46"), nostrict part:
 * func_002399f0 steps a sprite and draws it with one caller colour for all
 * four corners (func_00239860). */
#include "common.h"

void func_0024ae00(void *);
void func_0024af00(void *);
void func_00239860(void *, void *, s32, s32, f32, s32, void *, s32);

void func_002399f0(s32 a0, void *a1, void *a2, s32 dx, s32 dy, s32 *src, f32 s) {
    if (a0) func_0024ae00(a1);
    func_0024af00(a1);
    func_00239860(a1, a2, dx, dy, s, 1, src, 1);
}
