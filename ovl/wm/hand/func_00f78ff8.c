/* wm.x func_00f78ff8: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 pad14[23];
} __attribute__((aligned(8))) PadState;

typedef struct {
    void (*f0)(void);
    void (*f4)(void);
} Mode;

typedef struct {
    u8 pad0[0x98];
    s32 x98;
    s32 x9C;
    s32 xA0;
} Ev;

extern s32 D_00FB5BB0;
extern PadState D_0108F980[2];
extern PadState D_002C5AD0[2];
extern Mode *D_00FB5EA8;
extern s32 D_0108FA60[2];
extern s32 D_0108FA70;
extern s32 D_0108FA74;
extern s32 D_00FB5EC4;
extern s32 D_00FB5EC8;
extern s32 D_00FB6164;
extern s32 D_00FB610C;
extern s32 D_0108F730[2];
extern s32 D_0108F6C4;
extern s32 D_00FB5EAC;
extern s32 D_00FB5EC0;
extern Ev D_00FB6498;
void func_00f7b9a0(void);
void func_0011d768(s32);
void func_001fd708(void);

void func_00f78ff8(s32 *arg) {
    s32 i;
    s32 k;

    if (D_00FB5BB0 == 0) {
        for (i = 0; i < 2; i++) {
            D_0108F980[i].x8 = 0;
            D_0108F980[i].x10 = 0;
            D_0108F980[i].x4 = 0;
        }
    } else {
        for (i = 0; i < 2; i++) {
            D_0108F980[i] = D_002C5AD0[i];
        }
    }
    if (D_00FB5EA8) {
        for (i = 0; i < 2; i++) {
            D_0108FA60[i] = arg[i];
        }
        D_00FB5EC4 = D_00FB5EC8;
        D_0108FA74 = D_0108FA70;
        D_00FB5EA8->f0();
        if (D_0108FA60[0] != arg[0]) {
            func_00f7b9a0();
        }
        for (i = 0; i < 2; i++) {
            arg[i] = D_0108FA60[i];
        }
    }
    k = -1;
    if (D_00FB5EC4 == 0 && D_00FB6164 && D_0108FA70 == 66) {
        if (D_0108F980[0].x8 & 0x2000) {
            k = 0;
        }
        if (D_0108F980[0].x8 & 0x8000) {
            k = 1;
        }
    }
    if (k >= 0 && D_00FB5EA8 && D_00FB610C != -1) {
        if (D_0108F730[0] == 0 && D_0108F730[1] == 0 && k == 0) {
            func_0011d768(4);
            return;
        }
        D_00FB5EA8->f4();
        D_00FB5EA8 = NULL;
        D_0108F6C4 = 0;
        D_00FB5EAC = 1;
        func_001fd708();
        D_00FB6498.x98 = D_00FB610C;
        D_00FB6498.x9C = D_00FB5EC0;
        D_00FB6498.xA0 = k;
        if (k == 0) {
            func_0011d768(11);
        } else {
            func_0011d768(2);
        }
    }
}
