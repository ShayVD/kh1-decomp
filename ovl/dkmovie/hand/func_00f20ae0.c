/* dkmovie.x func_00f20ae0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DF44]; s32 df44; } MovieWork;
void func_00f20948(MovieWork *);
extern s16 D_00F28610;

void func_00f20ae0(MovieWork *w) {
    if (D_00F28610 == w->df44) {
        func_00f20948(w);
        D_00F28610 = w->df44 + 1;
    }
}
