/* xs_genie.x func_00f21d58: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; f32 fC; } C;
typedef struct { u8 pad[0xC]; C *fC; } B;
typedef struct { u8 pad[0x20]; B *f20; } Obj;
#ifdef KH1_PS2
void func_00249950(f32 *, f32, f32);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_00249950(f32 *, f32, f32);
#endif
extern f32 D_002BBDFC;
s32 func_00f21d58(Obj *o) {
    o->f20->fC->fC -= D_002BBDFC * 0.0666666627f;
    func_00249950(&o->f20->fC->fC, 0.0f, 1.0f);
    if (o->f20->fC->fC == 0.0f) {
        return 1;
    }
    return 0;
}
