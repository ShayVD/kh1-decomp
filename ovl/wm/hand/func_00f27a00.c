/* wm.x func_00f27a00: matched by hand. */
#include "ovl.h"

typedef struct { u64 a; u32 trig; } WmPad8;
extern s32 D_00F873F4;
extern s32 D_00F878E4;
extern s32 D_00F878E8;
extern s32 D_00FBAA68;
extern s32 D_00FBB550;
s32 func_00f26e48(s32);
void func_00f258c8(s32);
void func_00f29500(s32, s32, s32);
void func_00f28448(s32, s32, s32, s32);
void func_00f26e80(s32, s32, s32, s32, f32);
WmPad8 *func_001ba488(s32);
void func_001bfac8(void);

s32 func_00f27a00(s32 a0) {
    s32 n;
    WmPad8 *p;
    s32 t;
    s32 i;
    f32 f;

    n = func_00f26e48(a0);
    while (p = func_001ba488(0), D_00F878E8 == 0) {
        if (p->trig & 1) return 4;
        if (p->a & 0x2000002000000000) return 3;
        if (p->a & 0x8000008000000000) return 1;
        if (((u32 *)p)[1] & 0x2000) t = 0; else t = 1;
        if (n >= 2) {
            if (p->a & 0x4000004000000000) {
                D_00F873F4 = 1;
                func_00f258c8(2);
                D_00F878E4 = 0;
                for (i = 0; i < 8; i++) {
                    f = i * 100.0f * 0.125f + 0.0f;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, a0);
                    func_00f26e80(0, 0, a0, t, f);
                    func_001bfac8();
                }
                D_00F878E4 = 1;
                D_00FBB550 = (D_00FBB550 + n - 1) % n;
                D_00F873F4 = 0;
                continue;
            }
            if (p->a & 0x1000001000000000) {
                D_00F873F4 = 1;
                func_00f258c8(2);
                D_00F878E4 = 0;
                for (i = 0; i < 8; i++) {
                    f = i * -100.0f * 0.125f + 0.0f;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, a0);
                    func_00f26e80(0, 0, a0, t, f);
                    func_001bfac8();
                }
                D_00F878E4 = 1;
                D_00FBB550 = (D_00FBB550 + n + 1) % n;
                D_00F873F4 = 0;
                continue;
            }
        }
        func_00f29500(0, 0x3600, D_00FBAA68);
        func_00f28448(0, 0, 0, a0);
        func_00f26e80(0, 0, a0, t, 0.0f);
        func_001bfac8();
    }
    return 0;
}
