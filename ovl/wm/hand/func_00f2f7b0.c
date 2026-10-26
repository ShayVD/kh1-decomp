/* wm.x func_00f2f7b0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 pad[4]; u16 k; u8 pad2[6]; } It;
typedef struct { s32 n; u8 pad[0xC]; OvlVec org; u8 pad2[0xC]; f32 h; u8 pad3[4]; It items[1]; } L;
void func_001c0310(s32, void (*)(void));
void func_00f2c910(OvlMtx, s32);
void func_00f2cfd8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f3e778(s32, f32 *);
void func_00f2f678(void);
extern s32 D_00F850F4;
extern L D_00F85240;

void func_00f2f7b0(void) {
    OvlMtx m;
    s32 i, id, k;
    if (D_00F850F4 == 0) return;
    for (i = 0; i < D_00F85240.n; i++) {
        k = D_00F85240.items[i].k - 1;
        id = -1;
        if (k == 44 || k == 45) {
            func_00f2c910(m, i);
            id = 56;
            func_00f3e778(0, m[3]);
        } else if (k == 46 || k == 47) {
            func_00f2c910(m, i);
            id = 57;
            func_00f3e778(1, m[3]);
        }
        if (id >= 0) {
            func_00f2cfd8(0, i, k, id, 2, id, 0, 0, 0, -1);
        }
    }
    func_001c0310(9, func_00f2f678);
}
