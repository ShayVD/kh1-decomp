/* xs_tink.x func_00f20818: near miss (session 141), score 35. The original threads the jump after
   func_00147ed8 succeeds past the tail null check (the tail reloads D_00F20E90 through &D_00F20E90),
   and leaves the blez delay slot empty; no C ordering tried (48 variants) reproduces that. */
#include "ovl.h"
typedef struct { f32 *pos; u8 pad[0x10]; s32 state; } TinkObj;
extern s32 D_00F20D88;
extern s32 D_00F20ECC;
extern void *D_00F20D80;
extern OvlVec D_00F20EA0;
extern TinkObj *D_00F20E90;
extern char D_00F20E00[];
extern char D_00F20E10[];
TinkObj *func_00147ed8(void *, s32, s32, f32 *);
void __assert(const char *, s32, const char *);
void func_00f20338(void);
void func_00f201e0(void);
void func_00f20690(void);
s32 func_00f20818(void) {
    switch (D_00F20D88) {
    case 0:
        if (D_00F20ECC > 0) {
            if (--D_00F20ECC == 0) {
                TinkObj **pp = &D_00F20E90;
                *pp = func_00147ed8(D_00F20D80, 6, 20000, D_00F20EA0);
                if (*pp == NULL) {
                    __assert(D_00F20E00, 176, D_00F20E10);
                }
            }
        } else {
            func_00f20338();
            func_00f201e0();
        }
        break;
    case 100:
        func_00f20690();
        break;
    case 101:
        return 4;
    }
    if (D_00F20E90 != NULL) {
        TinkObj **pp = &D_00F20E90;
        if (((*pp)->state & 3) != 1) {
            *pp = NULL;
        } else {
            sceVu0CopyVector((*pp)->pos, D_00F20EA0);
        }
    }
    return 0;
}
