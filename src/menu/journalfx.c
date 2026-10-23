/* Page 5 of the menu, part 2 (docs/modules.md "Session 41"),
 * 0x0021b860-0x0021cd68: frames built from the sprites of D_003F4CF0
 * (journalfx.nostrict.c's func_0021b860 draws one).  func_0021c450 a column
 * of three, func_0021c5e0 / func_0021c780 / func_0021c9a0 the list frames,
 * func_0021c4f8 the bobbing cursor (sinf of the window's timer +0x98),
 * func_0021cbc8 a labelled bar (text func_0021b800 from D_003F34E8),
 * func_0021ccd0 the page's title box (text func_001c2df0 of D_003F34F0).
 * Not proved by a boot. */
#include "common.h"
#include "vm/script_vm.h"
#include "data/bss_0064.h"
#include "data/data_003F.h"

typedef struct {
    u8 pad[0x98];
    f32 x98;
    u8 pad2[0xb0 - 0x9c];
    s32 xb0;
    s32 xb4;
    u8 pad3[0xbe - 0xb8];
    s16 xbe;
    s16 xc0;
    s16 pad4;
    s16 xc4;
    u8 pad5[0xd2 - 0xc6];
    s16 xd2;
} JFx;
typedef struct { u8 pad[0x90]; s32 x90; } JObj;

extern s32 D_003F34F0;

void func_0010eee0(s32, s32, s32, s32);
s32 func_0010ef90(s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
void func_00206130(void *, s32, s32, s32, s32, u32);
void func_0021b860(void *, s32, s32, s32, s32, s32);
s32 func_0021b800(s32);
s32 func_0021cbc8(void *, s32, s32, s32, s32, s32);
f32 sinf(f32);

void func_0021c450(void *a0, s32 a1, s32 a2, s32 a3) {
    s32 y = a1 + 25;
    s32 h;
    s32 z;
    if (a3 < 75) a3 = 75;
    h = a3 - 75;
    z = y + h;
    func_0021b860(a0, a1, a2, 0, 0, 24);
    func_0021b860(a0, y, a2, h, 0, 25);
    func_0021b860(a0, z, a2, 0, 0, 26);
}

void func_0021c4f8(JFx *o) {
    s32 a = (s32)(o->x98 * 256.0f);
    f32 s = sinf((a % 8192) * 0.0001220703125f * 6.2831855f);
    func_0021b860(o, ((o->xb0 + o->xbe - 0x7000) >> 4) + ((s32)(s * 262144.0f) >> 16) - 36,
                  (o->xb4 + (o->xd2 * o->xc4 >> 4) + o->xc0 - 0x7400) >> 4, 0, 0, 38);
}

void func_0021c5e0(void *a, s32 x, s32 y) {
    s32 i, yy, xb, xc;
    xb = x + 52;
    xc = x + 195;
    func_0021b860(a, x, y, 0, 0, 6);
    func_0021b860(a, xb, y, 143, 0, 7);
    func_0021b860(a, xc, y, 0, 0, 8);
    yy = y + 51;
    for (i = 0; i < 12; i++) {
        func_0021b860(a, x, yy, 0, 0, 9);
        func_0021b860(a, xb, yy, 143, 0, 10);
        func_0021b860(a, xc, yy, 0, 0, 11);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 12);
    func_0021b860(a, xb, yy, 143, 0, 13);
    func_0021b860(a, xc, yy, 0, 0, 14);
    xb = x - 16;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

void func_0021c780(void *a, s32 x, s32 y) {
    s32 i, yy, xb, xc, y20;
    xb = x + 52;
    yy = y + 20;
    y20 = yy;
    xc = x + 198;
    func_0021b860(a, x, y, 0, 0, 15);
    func_0021b860(a, xb, y, 146, 0, 16);
    func_0021b860(a, xc, y, 0, 0, 17);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, x, yy, 0, 0, 18);
        func_0021b860(a, xb, yy, 146, 0, 19);
        func_0021b860(a, xc, yy, 0, 0, 20);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 21);
    func_0021b860(a, xb, yy, 146, 0, 22);
    xb = x + 241;
    func_0021b860(a, xc, yy, 0, 0, 23);
    yy = y20;
    func_0021b860(a, xb, y, 0, 0, 0);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, xb, yy, 0, 0, 4);
        yy += 16;
    }
    func_0021b860(a, xb, yy, 0, 0, 2);
    xb = x + 225;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

void func_0021c9a0(void *a, s32 x, s32 y) {
    s32 i, yy, xb, y20;
    yy = y + 20;
    y20 = yy;
    func_0021b860(a, x, y, 0, 0, 1);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, x, yy, 0, 0, 5);
        yy += 16;
    }
    func_0021b860(a, x, yy, 0, 0, 3);
    yy = y20;
    xb = x + 241;
    func_0021b860(a, xb, y, 0, 0, 0);
    for (i = 0; i < 16; i++) {
        func_0021b860(a, xb, yy, 0, 0, 4);
        yy += 16;
    }
    func_0021b860(a, xb, yy, 0, 0, 2);
    xb = x + 225;
    yy = y + 7;
    for (i = 0; i < 18; i++) {
        func_0021b860(a, xb, yy, 0, 0, 31);
        yy += 16;
    }
}

void func_0021cb00(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg3;
    var_s1 = arg2;
    if (var_s0 > 0) {
        do {
            var_s0 -= 1;
            func_00206130(arg0, arg1, var_s1, 0xC8, 2, 0x40202020);
            var_s1 += arg4;
        } while (var_s0 > 0);
    }
}

void func_0021cb88(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_0021cbc8(arg0, arg1, arg2, arg3, arg4, 0x80461E00);
}

void func_0021cba8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_0021cbc8(arg0, arg1, arg2, arg3, arg4, 0x40461E00);
}

s32 func_0021cbc8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s2;

    func_0021b860(arg0, arg1 - 0x19, arg2 - 6, 0, 0, 0x22);
    temp_s2 = arg3 - 0x28;
    func_0021b860(arg0, arg1, arg2, 0, 0, 0x23);
    func_0021b860(arg0, arg1 + 0x14, arg2, temp_s2, 0, 0x25);
    func_0021b860(arg0, arg1 + temp_s2 + 0x14, arg2, 0, 0, 0x24);
    return func_001f94f0(arg0, 0, arg1 + 8, arg2 + 2, func_0021b800(arg4), 0xF, arg5);
}

void func_0021ccd0(JObj *arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_v0;
    u32 temp_a0;

    func_0021c450(arg0, 0x14, 0x59, 0xDC);
    temp_v0 = (s32) func_001c2df0((s8 *) D_003F34F0, arg1);
    temp_a0 = 0xDC - func_0010ef90(temp_v0, (s32) sp);
    func_0010eee0(((s32) (temp_a0 + (temp_a0 >> 0x1F)) >> 1) + 0x14, 0x7F - (sp[0] * 0xE), arg0->x90, temp_v0);
}

