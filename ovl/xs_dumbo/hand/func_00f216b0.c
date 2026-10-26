/* xs_dumbo.x func_00f216b0: matched by hand. */
#include "ovl.h"

typedef struct { OvlVec start; OvlVec dir; s32 pad[4]; s16 f30; s16 pad2; s32 pad3[3]; } Hit;
typedef struct { s32 n; f32 t; s32 pad[2]; Hit hit; } Res;
typedef struct { u8 pad[0x30]; OvlVec p; } Node;
void func_00118608(Hit *);
void func_00f216b0(Res *r, Node *arg1, s32 cnt) {
    OvlVec d;
    Hit h;
    s32 i;
    s32 n = cnt - 1;
    for (i = 0; i < n; i++) {
        PlatVu0SubVector(d, arg1[i + 1].p, arg1[i].p);
        PlatVu0CopyVector(h.start, arg1[i].p);
        PlatVu0CopyVector(h.dir, d);
        func_00118608(&h);
        if (h.f30 >= 0) {
            r->hit = h;
            break;
        }
    }
    if (i == n) {
        r->n = n;
        r->t = 1.0f;
    } else {
        r->n = i;
        r->t = (f32)i / (f32)n;
    }
}
