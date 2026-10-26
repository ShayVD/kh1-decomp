/* xl_limit.x func_00f21cb8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fn; } Res;
s32 func_00130340(s32, s32, f32);
Res *func_00130578(s32, s32, f32);
void func_001315c0(s32, s32, f32 *, f32);
void func_00147ed8(s32, s32, s32, f32 *);
void func_00f21ad8(void);
void func_00f21af8(void);
extern s32 D_002E26A0;
extern s32 D_00F23208;
extern s32 D_00F23E14;

void func_00f21cb8(void) {
    f32 pos[4];
    s32 o = D_002E26A0;
    if (D_00F23E14 < 5) {
        func_001315c0(o, 0x30, pos, 0.0f);
        func_00147ed8(D_00F23208, 5, 20000, pos);
    }
    func_00130340(o, 0x010000ED, 0.0f);
    func_00130578(o, 0xEE, 0.0f)->fn = func_00f21ad8;
    func_00130578(o, 0x40100000, 0.0f)->fn = func_00f21af8;
}
