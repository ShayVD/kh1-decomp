/* gb.x func_00f4a410: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; s8 b4; u8 pad5[59]; void (*fn)(void); } Obj;
Obj *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f49dd8(void);
void func_00f4a2c8(void);
extern s32 D_00F82BF0, D_00F702F0, D_00F70648;
extern s32 D_00F82C08[];
extern Obj *D_00F82C30[];
void func_00f4a410(void) {
    s32 i;
    s32 q = D_00F702F0;
    for (i = 0; i < D_00F82BF0; i++) {
        D_00F82C30[i] = func_00f445a8(11, 13, 2, 1, 0, 15, D_00F82C08[i] + 52, 1, 0, 0, 0, D_00F70648, 0, 0, 0, 0, 0, 256, q);
        D_00F82C30[i]->b4 = 6;
        D_00F82C30[i]->fn = func_00f49dd8;
    }
    func_00f445a8(11, 7, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 256, q)->fn = func_00f4a2c8;
}
