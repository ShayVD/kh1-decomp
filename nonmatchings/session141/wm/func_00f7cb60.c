/* 3 words left (score 4): the &2 arm jumps to the shared `p[0] = 0` tail and fills its slot with the D_00FB5EC0 store; the original duplicates the tail into each arm (steals it into the b slot). Tried per-arm duplicates (crossjumped worse), volatile D_00FB5EC0, swapped arms, all modes, ctx.py. */
#include "ovl.h"

extern s32 D_0108F730[2];
extern s32 D_00FB6108;
extern s8 D_0108F738[];
extern u8 D_00FB64AC[];
extern s32 D_00FB5EC0;
extern s32 D_0108F6E8;
extern s32 D_0108F6EC;
void func_00f7bfb8(void);

void func_00f7cb60(void) {
    s32 *p = D_0108F730;
    p[0] = 0;
    p[1] = 0;
    func_00f7bfb8();
    if ((u32)(D_00FB6108 - 2) < 26) {
        p[0] = 1;
        p[1] = 1;
        if (D_0108F738[D_00FB6108] == 0) {
            if (D_00FB64AC[D_00FB6108] & 2) {
                p[1] = 0;
                D_00FB5EC0 = 0;
            } else {
                D_00FB5EC0 = 1;
            }
            p[0] = 0;
        } else if (D_0108F6E8 != 0) {
            p[0] = 1;
            D_00FB5EC0 = 0;
            p[1] = 0;
        } else if (D_00FB64AC[D_00FB6108] & 2) {
            p[1] = 0;
            D_00FB5EC0 = 0;
        }
        if (D_0108F6EC == 0) {
            D_00FB5EC0 = 0;
            D_0108F730[1] = 0;
        }
        if (D_00FB6108 < 27) {
            if (D_00FB6108 >= 21 && D_0108F730[1] != 0) {
                D_0108F730[1] = 0;
                D_00FB5EC0 = 0;
            }
        }
    }
}
