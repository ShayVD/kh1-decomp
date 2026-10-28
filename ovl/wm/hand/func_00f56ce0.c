/* wm.x func_00f56ce0: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad0[0x48];
    u8 x48[0x82 - 0x48];
    s16 x82;
} World;

extern World *D_00F9B540;
extern u8 D_00F9B548[];
extern u8 D_00FA5BB0[];
extern u8 D_00FA5BD0[];
extern u8 D_00FA5C40[];
extern u8 D_00FA5C90[];
extern u8 D_00FA5BF8[];
extern u8 D_00FA5C18[];
extern f32 D_00FA5CE4;
void func_001bbbd0(OvlMtx *, void *);
f32 func_001befc8(s32, void *);
void func_00f4eaa0(s32, void *, s32, s32, s32, f32 *, OvlMtx *, f32, f32);
void func_001bfac8(void);
s32 func_00f4ad68(s32);

void func_00f56ce0(void) {
    f32 v[3];
    OvlMtx m;
    s32 t;
    s32 i;
    s32 x;
    s32 y;
    s32 id;
    f32 a;
    f32 b;
    f32 c;

    t = 0;
    func_001bbbd0(&m, D_00F9B540->x48);
    id = D_00F9B540->x82;
    for (i = 0; i < 20; i++) {
        a = func_001befc8(t, D_00FA5BB0);
        b = func_001befc8(t, D_00FA5BD0);
        x = (s32)(a * 16.0f) + 1088;
        y = 3072 - (s32)(b * 16.0f);
        c = func_001befc8(t, D_00FA5C40);
        v[2] = c;
        v[0] = c;
        v[1] = func_001befc8(t++, D_00FA5C90);
        func_00f4eaa0(10720, D_00F9B548, x, y, id, v, &m, 1.0f, D_00FA5CE4);
        func_001bfac8();
    }
    for (i = 0; i < 8; i++) {
        func_001bfac8();
        t++;
    }
    id = func_00f4ad68(D_00F9B540->x82);
    for (i = 0; i < 20; i++) {
        a = func_001befc8(t, D_00FA5BF8);
        b = func_001befc8(t, D_00FA5C18);
        x = (s32)(a * 16.0f) + 1088;
        y = 3072 - (s32)(b * 16.0f);
        c = func_001befc8(t, D_00FA5C40);
        v[2] = c;
        v[0] = c;
        v[1] = func_001befc8(t++, D_00FA5C90);
        func_00f4eaa0(10720, D_00F9B548, x, y, id, v, NULL, 1.0f, D_00FA5CE4);
        func_001bfac8();
    }
}
