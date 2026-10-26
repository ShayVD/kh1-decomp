/* wm.x func_00f4d3d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 h76; } WmObj76;
s32 func_00f4cfb8(s32);
void func_001ba708(s32);
void func_001bfac8(void);
void func_001c2ec8(s32, s32);
void func_00f4d308(void);
extern s32 D_002BCDEC;
typedef struct { u32 b0 : 1; u32 b1 : 1; } WmFlags;
extern WmFlags D_0037A378;
extern s32 D_00F9B508;
extern WmObj76 *D_00F9B540;
extern s32 D_01080C50;
extern s32 D_0108BC9C;
extern s32 D_0108BCA0;

void func_00f4d3d8(s32 arg0) {
    s32 h;

    D_01080C50 = 0;
    D_0108BC9C = 0;
    D_0108BCA0 = 0;
    h = func_00f4cfb8(arg0);
    if (h != 0) {
        func_001ba708(1);
        D_002BCDEC = 1;
        while (D_00F9B508 != 0) {
            func_001bfac8();
        }
        D_00F9B508 = 1;
        func_001c2ec8(h, 0);
        while (D_0037A378.b1 == 1) {
            if (D_00F9B540->h76 != 3) {
                func_00f4d308();
            }
            D_01080C50++;
            func_001bfac8();
        }
        func_001ba708(0);
        D_00F9B508 = 0;
    }
}
