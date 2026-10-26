/* wm.x func_00f28e58: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 btn; } Pad;
Pad *func_001ba488(s32);
void func_001bfac8(void);
void func_00f22ac8(void);
void func_00f28230(s32, s32);
void func_00f28448(s32, s32, s32, s32);
void func_00f28a68(s32, s32, s32);
void func_00f29500(s32, s32, s32);
extern s32 D_00FBAA68;

void func_00f28e58(void) {
    while (!(func_001ba488(0)->btn & 0x4000)) {
        func_00f29500(0, 0x3600, D_00FBAA68);
        func_00f28448(0, 0, 0x80, 0);
        func_00f28a68(0, 0, 0x80);
        func_00f22ac8();
        func_001bfac8();
    }
    func_00f28230(0, 0x3600);
}
