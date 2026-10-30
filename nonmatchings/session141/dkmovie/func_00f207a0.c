/* dkmovie.x func_00f207a0: near miss (session 141), 7 words: the -1 constant is in a1 and D_00F28644's %hi in v0 in the original (ours the other way round); callee return types and store orders tried. */
#include "ovl.h"
typedef struct {
    u8 pad[0x3DEDC];
    s32 f3DEDC;
    s32 f3DEE0;
    s32 f3DEE4;
    u8 pad3DEE8[0x4C];
    s32 f3DF34;
    s32 f3DF38;
    s32 f3DF3C;
    s32 f3DF40;
    s32 f3DF44;
    s32 f3DF48;
    s32 f3DF4C;
    u8 pad3DF50[8];
    s8 f3DF58;
    s8 f3DF59;
    s8 f3DF5A;
    s8 f3DF5B;
    s8 f3DF5C;
    s8 f3DF5D;
    s8 f3DF5E;
    s8 f3DF5F;
    s8 f3DF60;
    s8 f3DF61;
    s8 f3DF62;
} MovieWork;
extern s16 D_00F28610;
extern s32 D_00F28644;
void func_001eda38(s32);
s32 func_001ed870(void);
void func_001eda90(s32, s32);
void func_001ed8c8(s32);
void func_00f207a0(MovieWork *m) {
    D_00F28610 = 0;
    D_00F28644 = 0;
    m->f3DF44 = 2;
    m->f3DF40 = -1;
    m->f3DEE4 = -1;
    m->f3DF38 = -1;
    m->f3DF3C = -1;
    m->f3DF58 = 0;
    m->f3DEDC = 0;
    m->f3DEE0 = 0;
    m->f3DF5D = 0;
    m->f3DF5E = 0;
    m->f3DF5B = 0;
    m->f3DF5C = 0;
    m->f3DF59 = 0;
    m->f3DF34 = 0;
    m->f3DF62 = 0;
    func_001eda38(0);
    m->f3DF4C = func_001ed870();
    func_001eda90(0, 1);
    func_001ed8c8(-1);
}
