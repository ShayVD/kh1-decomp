/* xs_simba.x func_00f21768: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; OvlVec pos; u8 pad2[0x370 - 0x20]; u64 f370; } Act;
s32 func_00148968(Act *, void *, s32);
void func_00f21020(void);
void func_00f21490(void);
extern void *D_00304B6C;
extern Act *D_00F21C34;
extern volatile Act *D_00F21C38;
extern void *D_00F21C44;
extern s32 D_00FA7750;
extern s32 D_00FA7754;
extern s32 D_00FA7758;
void func_00f21768(void) {
    s32 *p;
    
    func_00f21020();
    
    PlatVu0CopyVector(D_00F21C38->pos, D_00F21C34->pos);
    D_00304B6C = func_00f21490;
    D_00FA7750 = 0;
    D_00FA7758 = 0;
    p = &D_00FA7754;
    *p = func_00148968((Act *)D_00F21C38, D_00F21C44, 0);
    D_00F21C38->f370 &= ~0x0010000000000000;
}
