/* wm.x func_00f48f98: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 state; } W48f98;
void func_00106780(s32);
s32 func_001ba9d8(s32);
void func_001bab80(s32, s32);
void func_001bb428(s32);
void func_001be1e8(s32, s32);
void func_001bfac8(void);
s32 func_001c01b0(s32, void *, s32);
void func_00f47b60(void);
void func_00f48870(s32, s32);
void func_00f48cd0(void);
void func_00f48d30(void);
void func_00f48dd8(void);
void func_00f48f70(void);
s32 func_00f4b338(s32, s32);
void func_00f4b878(s32);
void func_00f4e3f8(s32);
void func_00f504f8(s32);
void func_00f51d18(void);
void func_00f58f98(s32);
void func_00f59820(s32, s32);
void func_00f5cb78(void);
void func_00f60448(s32);
void func_00f4d3d8();
extern W48f98 *D_00F9B540;
extern s32 D_00F9B544;
extern s32 D_00F9B644;
extern s32 D_01080A24;
extern s32 D_01080A20;
extern s32 D_010809B8;
extern s32 D_00F9B640;
extern s32 D_00F9B50C;
extern s32 D_00F9B518;

void func_00f48f98(void) {
    s32 i;

    D_01080A24 = 0;
    while (1) {
        switch (D_00F9B540->state) {
        case 2:
            func_00f5cb78();
            break;
        case 1:
            func_00f51d18();
            break;
        case 0:
            func_00f58f98(0);
            break;
        case 3:
            D_01080A20 = 0;
            for (i = 0; i < 60; i++) {
                func_001bfac8();
            }
            func_00f48d30();
            func_00106780(30);
            if (D_00F9B644 != 0) {
                func_001c01b0(12, func_00f4d3d8, D_00F9B644 - 1);
                D_00F9B644 = 0;
            }
            func_001bfac8();
            func_001bfac8();
            func_001bb428(0);
            func_00f60448(D_01080A24);
            func_001bb428(1);
            while (D_010809B8 != 0) {
                func_001bfac8();
            }
            if (D_00F9B640 != 0) {
                func_001bab80(10, func_001ba9d8(0));
                func_001be1e8(0, 0);
                func_00f47b60();
            }
            func_00f4b878(D_00F9B544);
            func_00f4b338(D_00F9B544, 0);
            func_00f4e3f8(0);
            D_00F9B540->state = 0;
            func_00f59820(7, 0);
            func_00f59820(5, 0);
            func_00f48870(0, 0);
            D_00F9B50C = 1;
            D_00F9B518 = 0;
            func_00f504f8(1);
            func_00f48cd0();
            func_00106780(30);
            if (D_00F9B640 == 0) {
                func_00f48f70();
                func_00f48dd8();
            }
            D_01080A24 = 1;
            break;
        }
    }
}
