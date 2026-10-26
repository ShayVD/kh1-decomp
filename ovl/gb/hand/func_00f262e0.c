/* gb.x func_00f262e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 mode; } World;
typedef struct { u32 b0 : 1; u32 b1 : 1; } Flags;
s32 func_00f25ec0(s32);
void func_001ba708(s32);
void func_001bfac8(void);
void func_001c2ec8(s32, s32);
void func_00f26210(void);
extern s32 D_002BCDEC;
extern Flags D_0037A378;
extern s32 D_00F56D88;
extern World *D_00F56DC0;
extern s32 D_00F74490;
extern s32 D_00F7F4DC;
extern s32 D_00F7F4E0;

void func_00f262e0(s32 arg0) {
    s32 h;
    D_00F74490 = 0;
    D_00F7F4DC = 0;
    D_00F7F4E0 = 0;
    h = func_00f25ec0(arg0);
    if (h != 0) {
        func_001ba708(1);
        D_002BCDEC = 1;
        while (D_00F56D88 != 0) {
            func_001bfac8();
        }
        D_00F56D88 = 1;
        func_001c2ec8(h, 0);
        while (D_0037A378.b1 == 1) {
            if (D_00F56DC0->mode != 3) {
                func_00f26210();
            }
            D_00F74490++;
            func_001bfac8();
        }
        func_001ba708(0);
        D_00F56D88 = 0;
    }
}
