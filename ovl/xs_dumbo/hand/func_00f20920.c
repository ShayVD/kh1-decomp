/* xs_dumbo.x func_00f20920: matched by hand. */
#include "ovl.h"

typedef struct DumboObj {
    u8 pad0[0x10];
    OvlVec pos;
    u8 pad20[0x1C];
    f32 r3c;
    u8 pad40[0x58];
    struct DumboObj *parent;
    u8 pad9c[0x370 - 0x9C];
    u8 b[4];
    u8 pad374[0x4A0 - 0x374];
    void *fn;
} DumboObj;
void func_00137308(DumboObj *, s32);
void func_00137688(DumboObj *, f32);
void func_00f20900();
extern s32 D_00F23200;

void func_00f20920(DumboObj *arg0) {
    s32 i;

    if (arg0->fn == NULL) {
        func_00137308(arg0, D_00F23200);
        arg0->fn = func_00f20900;
    }
    if (arg0->parent != NULL) {
        PlatVu0CopyVector(arg0->pos, arg0->parent->pos);
        func_00137688(arg0, arg0->parent->r3c);
        for (i = 0; i < 4; i++) {
            arg0->b[i] = arg0->parent->b[i];
        }
    }
}
