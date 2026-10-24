/* Object class 0x19, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015ea40 registers in the class table D_00350D88
 * (func_0014f830(0x19, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class19.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"

/* func_0015e8d8 (from hand/nostrict/text_00150000_h36.c). */
void func_0014f658(void *, s32);
typedef struct { u8 b0; u8 type; u16 bone; f32 off; f32 dy; f32 r; f32 h; } CylSrc;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; CylSrc *cyl2; } CylHdr;
typedef struct { u8 pad[0xD0]; f32 m[4][4]; } Mtx0D0;
typedef struct { u8 pad[0x60]; f32 v60[4]; f32 v70[4]; f32 v80[4]; s32 x90; Mtx0D0 *mtx; u8 pad98[0x78]; f32 x110[4]; s32 x120; } Sub148;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4]; f32 vel[4]; f32 sx, sy; u8 pad48[0x24]; struct { u8 pad[4]; f32 f4, f8; } *p6C; s32 x70; u8 pad74[0xC0];
    CylHdr *hdr; u8 pad138[0x10]; Sub148 *p148; u8 pad14c[4]; f32 rot; u8 pad154[0xC]; union { u64 d; u32 w; } x160; u8 pad168[0x1A6];
    u16 h30E; u8 pad310[0x60]; u64 flags; u8 pad378[0x2C]; u32 mask; u32 mask2;
    u8 pad3ac[0x14]; f32 x3C0[4];
} CylObj;
void func_00137688(void *, f32);
void func_00130398(void *, s32, f32);
f32 func_00120c88(f32);
extern f32 D_002BBDFC;
f32 atan2f(f32, f32);
s32 func_001375d8(void *);
void func_0015e8d8(CylObj *o, f32 *v) {
    f32 a;
    if (0.0f < v[3]) {
        a = func_00120c88(atan2f(v[0], v[2]) - o->vel[3]);
    } else a = 0.0f;
    if (0.008726646f < a) a = 0.008726646f;
    else if (a < -0.008726646f) a = -0.008726646f;
    a = func_00120c88(a * D_002BBDFC + o->vel[3]);
    func_00137688(o, a);
    o->rot = a;
    if (func_001375d8(o)) {
        func_0014f658(o, 24);
        return;
    }
    func_00130398(o, 126, 16.0f);
}

