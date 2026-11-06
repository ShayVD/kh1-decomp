/* xs_mushu.x func_00f200e8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xCC]; f32 fCC; } Sub;
typedef struct { u8 pad[0x6C]; Sub *f6C; s32 f70; } Pl;
void func_0013aac0(Pl *);
s32 func_00130340(Pl *, s32, f32);
s32 func_00130578(Pl *, s32, f32);
void func_00f20098(s32);
void func_00157a30(Pl *, s32, s32);
#ifdef KH1_PS2
void func_0014cce0(Pl *, f32);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0014cce0(Pl *, f32);
#endif
extern Pl *D_00F21384;
extern s32 D_00F21394;
void func_00f200e8(void) {
    switch (D_00F21384->f70) {
    case 0:
        func_0013aac0(D_00F21384);
        func_00130340(D_00F21384, 0x010000C8, 0.0f);
        func_00130578(D_00F21384, 0x40100000, 0.0f);
        break;
    case 2:
        func_0013aac0(D_00F21384);
        func_0014cce0(D_00F21384, 20.0f);
        func_00130340(D_00F21384, 0x010000C9, 0.0f);
        func_00130578(D_00F21384, 0x40100006, 8.0f);
        break;
    case 8:
        func_0013aac0(D_00F21384);
        func_00130340(D_00F21384, 0x010000C9, 0.0f);
        func_00130578(D_00F21384, 0x40100075, 8.0f);
        D_00F21384->f6C->fCC = 0.196349550784f;
        break;
    default:
        return;
    }
    func_00f20098(1);
    func_00157a30(D_00F21384, 17, 0);
    D_00F21394 = 0;
}
