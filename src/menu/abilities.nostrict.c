/* The abilities page's sort window (src/menu/abilities.c; docs/modules.md
 * "Session 40"; was in src/hand/nostrict/text_00200000_h70.c): func_002143e0
 * picks a sort key (D_00642C70, three entries; the second is not offered for
 * the shared list) into D_00642C48 and sorts (func_00213fb0).  It needs
 * -fno-strict-aliasing. */
#include "common.h"
#include "text/textwin.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"

extern s32 D_00642C24, D_00642C28, D_00642C70;
void func_0011d768(s32);
s32 func_001f3758(void *);
void func_001f3d58(void *, s32);
s32 func_001f42b8(void *);
s32 func_001fd518(void *);
void func_001fd858(void *);
s32 func_001fe5a0(void *);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_0020bd18(void *, s32);
void func_00213fb0(void);

void func_002143e0(TextWin *a0) {
    s32 sel;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a0);
            func_0011d768(3);
            D_00642C24 = 2;
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00642C70 = func_001fd518(a0);
            if (func_001fe5a0(a0)) {
                if (D_00642C70 == 1 && D_00642C28 == -1) {
                    func_0011d768(4);
                } else {
                    func_0011d768(74);
                    func_001f3d58(a0, 5);
                    func_001f3758(a0);
                    D_00642C48 = D_00642C70;
                    D_00642C24 = 5;
                    func_00213fb0();
                }
            }
        }
    }
    sel = func_001fd518(a0);
    func_00207830(a0, sel == 0, 2, 0, 0, 122, 193);
    { s32 k; if (D_00642C28 != -1) k = sel == 1; else k = sel == 1 ? 3 : 2; func_00207830(a0, k, 2, 0, 28, 122, 194); }
    func_00207830(a0, sel == 2, 2, 0, 56, 122, 195);
}
