/* dktitle.x func_00f21068: matched (session 141): session 132's draft plus a CONTEXT_ONLY func_00f209b0 above it (bc1fl -> bc1f). */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
extern Fade D_00F2C738, D_00F2C748, D_00F2C758, D_00F2C768;
extern u8 D_009A0000[];
extern u8 *D_00F26E1C;
void func_00f20a98(u8 *);
CONTEXT_ONLY void func_00f209b0(u8 *a0) {}
void func_00f203a8(u64, s32, s32, s32, s32, s32, s32);
void func_00f20540(s32, s32, s32, s32, s32);
static inline void fadeB(Fade *f) {
    switch (f->st) {
    case 0:
        f->v += 0.01f;
        if (0.6f <= f->v) { f->v = 0.0f; f->st = 1; }
        break;
    case 1:
        f->v += 2.1333334f;
        if (128.0f <= f->v) f->v = 128.0f;
        break;
    }
}
static inline void fadeC(Fade *f) {
    switch (f->st) {
    case 0:
        f->v += 0.01f;
        if (0.6f <= f->v) { f->v = 0.0f; f->st = 1; }
        break;
    case 1:
        f->v += 0.7111111f;
        if (128.0f <= f->v) f->v = 128.0f;
        break;
    }
}
static inline void fadeD(Fade *f) {
    f->v += 2.1333334f;
    if (128.0f <= f->v) f->v = 128.0f;
}
static inline void fadeA(Fade *f) {
    switch (f->st) {
    case 0:
        f->v += 0.8f;
        if (96.0f <= f->v) { f->v = 96.0f; f->st = 1; }
        break;
    case 1:
        f->v -= 0.8f;
        if (f->v <= 0.0f) f->v = 0.0f;
        break;
    }
}
void func_00f21068(void) {
    func_00f20a98(D_009A0000);
    func_00f203a8(0x200F1E8665423200ULL, 68, (s32)D_00F2C768.v, 0, 0, 512, 384);
    func_00f203a8(0x2008000664022600ULL, 68, (s32)D_00F2C748.v, 0, 0, 512, 384);
    if (D_00F2C738.v == 0.0f && D_00F2C768.v == 128.0f) {
        func_00f209b0(D_00F26E1C);
        func_00f203a8(0x2008000664120E00ULL, 68, (s32)D_00F2C758.v, 0, 0, 512, 384);
        fadeC(&D_00F2C758);
    }
    func_00f20540((s32)D_00F2C738.v, 0, 0, 512, 384);
    fadeB(&D_00F2C748);
    fadeD(&D_00F2C768);
    fadeA(&D_00F2C738);
}
