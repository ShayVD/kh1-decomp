/* wm.x func_00f56f30: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x82]; s16 id; s16 x84; } World;
extern World *D_00F9B540;
extern u8 D_00F9B548[];
extern f32 D_00FA5CE4;
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
s32 func_001c01b0(s32, void *, s32);
void func_001c0078(s32);
void func_00f56ce0();
void func_00f55bc0();
void func_00f55310();
void func_00f55d78();
void func_00f55d38();
s32 func_00f4ae48(s32);
s32 func_00f4ad68(s32);
s32 func_00f4aca8(s32);
void func_001bfac8(void);
void func_00f59820(s32, s32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f4ec30(s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, s32 a4, f32 f, s32 size);
#else
s32 func_00f4ec30(s32 id, void *pp, s32 x, s32 y, s32 a4, s32 size, f32 ry0, f32 ry1, f32 f);
static __inline__ s32 ee_00f4ec30(s32 x0, void * x1, s32 x2, s32 x3, f32 x4, f32 x5, s32 x6, f32 x7, s32 x8) { return func_00f4ec30(x0, x1, x2, x3, x6, x8, x4, x5, x7); }
#undef func_00f4ec30
#define func_00f4ec30 ee_00f4ec30
#endif
void func_00f56f30(void) {
    s32 ids[3][4];
    s32 h0;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 i;
    s32 k;
    s32 id;
    s32 n;
    f32 r;
    s32 a1;
    s32 a2;
    s32 a4;
    s32 a5;
    f32 c;
    f32 q;
    s32 ten;
    s32 ninety;
    h0 = func_001c00e8(-1, func_00f56ce0, KH1_Q(0));
    h1 = func_001c00e8(-1, func_00f55bc0, KH1_Q(0));
    h2 = func_001c00e8(-1, func_00f55310, KH1_Q(0));
    ids[0][0] = func_00f4ae48(D_00F9B540->id);
    ids[1][0] = D_00F9B540->id;
    n = func_00f4ad68(D_00F9B540->id);
    ids[1][1] = func_00f4ad68(n);
    ids[2][0] = 48;
    ids[0][1] = n;
    if (func_00f4aca8(n) != D_00F9B540->x84)
        h3 = func_001c01b0(-1, func_00f55d78, 48);
    else
        h3 = func_001c01b0(-1, func_00f55d38, 48);
    k = 2;
    ten = 10;
    a1 = 0;
    for (i = 0; i < 10; i++) {
        a4 = 58;
        func_001bfac8();
        r = (f32)(a1 / ten) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, a4);
        id = func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, r, ids[0][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a1 += 90;
    }
    ten = 10;
    a2 = 0;
    ninety = 90;
    i = 10;
    do {
        func_001bfac8();
        c = (f32)(ninety - a2 / ten);
        q = 0.017453292f;
        r = c * q;
        q = r;
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[0][0], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 76, -r, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a2 += 90;
    } while (--i != 0);
    for (i = 0; i < 8; i++) {
        func_001bfac8();
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
    }
    ten = 10;
    a4 = 0;
    for (i = 0; i < 10; i++) {
        func_001bfac8();
        r = (f32)(a4 / ten) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[1][1], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, r, ids[0][1], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a4 += 90;
    }
    ten = 10;
    a5 = 0;
    ninety = 90;
    i = 10;
    do {
        func_001bfac8();
        c = (f32)(ninety - a5 / ten);
        q = 0.017453292f;
        r = c * q;
        q = r;
        id = func_00f4ec30(11200, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 347, -r, 0.0f, ids[1][1], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a5 += 90;
    } while (--i != 0);
    func_00f59820(4, 0);
    func_001c0078(h0);
    func_001c0078(h1);
    func_001c0078(h3);
    func_001c0078(h2);
}
