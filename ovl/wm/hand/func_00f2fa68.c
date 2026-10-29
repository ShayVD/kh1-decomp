/* wm.x func_00f2fa68: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[6]; u16 lo : 8; u16 kind : 4; u16 hi : 4; u16 h; u16 pad; } N2fa68;
typedef struct { s32 n; u8 pad[0x2C]; N2fa68 ent[1]; } D2fa68;
extern D2fa68 D_00F85240;
extern s32 D_00F8C1EC;
extern s32 D_00FBB5AC;
extern s32 D_00FBB5B0;
void func_00f2cfd8(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_00f2f8e0();
void func_00f2d590(void);
void func_00f2d3d8(s32);

void func_00f2fa68(void) {
    s32 i;
    s32 found;
    s32 r;
    s32 h, t;
    if (D_00F8C1EC != 0) {
        return;
    }
    found = 0;
    for (i = 0; i < D_00F85240.n; i++) {
        t = D_00F85240.ent[i].h - 1;
        if (t == 53) {
            found = 1;
        }
    }
    if (!found) {
        D_00FBB5AC++;
    } else {
        D_00FBB5B0++;
    }
    for (i = 0; i < D_00F85240.n; i++) {
        h = D_00F85240.ent[i].h;
        t = h - 1;
        if (D_00F85240.ent[i].kind == 4) {
            r = -1;
            switch (h) {
            case 5:
                r = !found ? 2 : 3;
                break;
            case 6:
                r = !found ? 6 : 7;
                break;
            case 7:
                r = !found ? 10 : 11;
                break;
            case 8:
                r = !found ? 14 : 15;
                break;
            case 9:
                r = !found ? 18 : 19;
                break;
            }
            if (r >= 0) {
                func_00f2cfd8(0, i, t, r, 2, r, 0, func_00f2f8e0, 0, -1);
            }
        }
    }
    D_00F8C1EC = 1;
    func_00f2d590();
    func_00f2d3d8(found + 2);
}
