/* wm.x func_00f3bde8: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 a0;
    s32 a4;
    s32 a8;
    s32 ac;
    s32 b0;
} Sub;
typedef struct {
    u8 pad[0xa0];
    Sub s;
    u8 pad2[0xc];
} E;
extern E D_01067FE0[];
void func_00f3bde8(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        s32 f = D_01067FE0[i].s.a0;
        if (f & 2) {
            D_01067FE0[i].s.a0 = 1;
        } else if (f & 1) {
            D_01067FE0[i].s.a0 = 0;
            D_01067FE0[i].s.b0 = 0;
            D_01067FE0[i].s.a8 = 0;
            D_01067FE0[i].s.ac = 0;
        }
    }
}
