/* gb.x func_00f303f0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 pad[0x48]; f32 rot[4]; u8 pad58[0x2A]; s16 cur; } World;
void func_001bbbd0(OvlMtx, void *);
void func_001bfac8(void);
f32 func_001befc8(s32, void *);
s32 func_00f23d50(s32);
void func_00f279a8(s32, void *, s32, s32, s32, OvlVec, OvlMtx *, f32, f32);
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern u8 D_00F61430[];
extern u8 D_00F61450[];
extern u8 D_00F61478[];
extern u8 D_00F61498[];
extern u8 D_00F614C0[];
extern u8 D_00F61510[];
extern f32 D_00F61564;

void func_00f303f0(void) {
    OvlVec v;
    OvlMtx m;
    s32 i, j, x, y, cur;
    f32 fx, fy;
    func_001bbbd0(m, D_00F56DC0->rot);
    cur = D_00F56DC0->cur;
    i = 48;
    for (j = 0; j < 20; j++) {
        fx = func_001befc8(i, D_00F61478);
        fy = func_001befc8(i, D_00F61498);
        x = (s32)(fx * 16.0f) + 0x440;
        y = 0xC00 - (s32)(fy * 16.0f);
        v[0] = v[2] = func_001befc8(i, D_00F614C0);
        v[1] = func_001befc8(i, D_00F61510);
        func_00f279a8(0x29E0, D_00F56DC8, x, y, cur, v, &m, 1.0f, D_00F61564);
        func_001bfac8();
        i--;
    }
    for (j = 0; j < 8; j++) {
        func_001bfac8();
        i--;
    }
    cur = func_00f23d50(D_00F56DC0->cur);
    for (j = 0; j < 20; j++) {
        fx = func_001befc8(i, D_00F61430);
        fy = func_001befc8(i, D_00F61450);
        x = (s32)(fx * 16.0f) + 0x440;
        y = 0xC00 - (s32)(fy * 16.0f);
        v[0] = v[2] = func_001befc8(i, D_00F614C0);
        v[1] = func_001befc8(i, D_00F61510);
        func_00f279a8(0x29E0, D_00F56DC8, x, y, cur, v, NULL, 1.0f, D_00F61564);
        func_001bfac8();
        i--;
    }
}
