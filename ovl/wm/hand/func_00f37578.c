/* wm.x func_00f37578: matched by hand. */
#include "ovl.h"

typedef struct { u8 id; u8 pad[15]; u8 kind; u8 k; } Z;
typedef struct { u8 pad[0xEC]; Z *z; s32 h; } A;
typedef struct { u8 pad[0x14]; s32 type; s32 k; } B;
typedef struct { u8 pad[0x540]; s32 b; } W;
Z *func_00f62c78(s32, s32);
s32 func_00f62c90(s32);
s32 func_00f64c38(s32, s32);
extern W *D_00F864C0;
extern s32 D_00F87020;

void func_00f37578(A *a, B *b) {
    s32 k, i, n;
    Z *z;
    switch (b->type) {
    case 2:
    default:
        k = a->z->k;
        break;
    case 4:
        k = b->k;
        break;
    }
    i = 0;
    n = func_00f62c90(D_00F864C0->b);
    while (i < n) {
        z = func_00f62c78(i++, D_00F864C0->b);
        if (z->kind == k) break;
        z = 0;
    }
    if (z != 0) {
        a->z = z;
        a->h = func_00f64c38(z->id, D_00F87020);
    }
}
