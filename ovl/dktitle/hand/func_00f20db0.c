/* dktitle.x func_00f20db0: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
void func_00f20db0(Fade *f) {
    switch (f->st) {
    case 0:
        f->v += 2.1333334f;
        if (128.0f <= f->v) { f->t = 180; f->v = 128.0f; f->st = 1; }
        break;
    case 1:
        if (--f->t == 0) f->st = 2;
        break;
    case 2:
        f->v -= 2.1333334f;
        if (f->v <= 0.0f) f->v = 0.0f;
        break;
    }
}
