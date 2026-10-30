/* wm.x func_00f7cd68: matched by hand. */
#include "ovl.h"

typedef struct {
    u16 x0;
    u16 x2;
    u16 x4;
    u16 x6;
    u32 x8;
} Pad;

typedef struct {
    u8 pad0[0xA4];
    s32 xA4;
    u8 xA8;
    u8 xA9;
    u8 xAA;
} Ev;

extern s32 D_00FB5EC8;
extern s32 D_00FB5ECC;
extern s32 D_00FB6108;
extern Ev D_00FB6498;
extern f32 D_00FB5BD4;
extern f32 D_00FB5BE0;
extern Pad D_0108F980;
void func_0011d768(s32);
void func_0024e468(s32);
void func_00f229d8(s32);
void func_00f25660(void);
s32 func_00f25650(void);
void func_00f25640(void);
void func_00f7cae0(OvlMtx *, f32, f32, f32, f32);
void func_00f22a78(s32, s32, OvlMtx *);

void func_00f7cd68(void) {
    OvlMtx m;
    f32 ry;
    f32 rx;
    f32 dist;
    s32 i;

    func_0011d768(2);
    D_00FB5EC8 = 1;
    D_00FB5ECC = 0;
    func_0024e468(1);
    D_00FB6498.xA4 = 0;
    func_00f229d8(D_00FB6108);
    while (D_00FB6498.xA4 == 0) {
        func_0024e468(1);
    }
    if (D_00FB6498.xA4 > 0) {
        rx = 0.0f;
        func_0024e468(1);
        func_00f25660();
        ry = 0.0f;
        if (D_00FB6108 == 16) {
            ry = D_00FB5BD4;
        }
        D_00FB6498.xAA = 0;
        D_00FB6498.xA9 = 0;
        D_00FB6498.xA8 = 0;
        dist = 26000.0f;
        for (i = 0; i < 10; i++) {
            dist -= 2000.0f;
            D_00FB5ECC = i * 8;
            func_00f7cae0(&m, 0.0f, ry, rx, dist);
            func_00f22a78(0, 0, &m);
            func_0024e468(1);
        }
        for (;;) {
            if (D_0108F980.x6 & 0x20) {
                ry -= D_00FB5BE0;
            }
            if (D_0108F980.x6 & 0x80) {
                ry += D_00FB5BE0;
            }
            if ((D_0108F980.x8 & 0x4000) && func_00f25650()) {
                func_00f25640();
                func_0011d768(3);
                break;
            }
            if (ry >= 3.14f) {
                ry -= 6.28f;
            }
            if (ry <= -3.14f) {
                ry += 6.28f;
            }
            if (rx >= 3.14f) {
                rx -= 6.28f;
            }
            if (rx <= -3.14f) {
                rx += 6.28f;
            }
            func_00f7cae0(&m, 0.0f, ry, rx, dist);
            func_00f22a78(0, 0, &m);
            func_0024e468(1);
        }
        for (i = 0; i < 10; i++) {
            dist += 2000.0f;
            D_00FB5ECC = 72 - i * 8;
            func_00f7cae0(&m, 0.0f, ry, rx, dist);
            func_00f22a78(0, 0, &m);
            func_0024e468(1);
        }
        D_00FB5ECC = 0;
        func_0024e468(1);
    }
    D_00FB5EC8 = 0;
    func_0024e468(1);
}
