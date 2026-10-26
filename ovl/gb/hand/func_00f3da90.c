/* gb.x func_00f3da90: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; u32 off; } A64;
typedef struct { u32 off; u32 x; } B64;
typedef struct { u8 pad[8]; u32 na; A64 *a; u32 nb; B64 *b; } H64;

s32 func_00f3da90(H64 *h) {
    u32 i;
    A64 *a;
    B64 *b;
    h->a = a = (A64 *)((u8 *)h->a + (u32)h);
    h->b = b = (B64 *)((u8 *)h->b + (u32)h);
    for (i = 0; i < h->na; i++) {
        a[i].off += (u32)h;
    }
    for (i = 0; i < h->nb; i++) {
        b[i].off += (u32)h;
    }
    return 1;
}
