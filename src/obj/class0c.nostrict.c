/* Object class 0x0C, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015e128 registers in the class table D_00350D88
 * (func_0014f830(0x0C, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class0c.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"

/* func_0015dc50 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { u8 pad[8]; f32 f8; } EntDC;
typedef struct { u8 pad[0x10]; union { EntDC *p; f32 f; } p10; } HdrDC;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x114]; HdrDC *h; } ObjDC;
typedef struct { f32 a[4]; f32 b[4]; u8 pad[0x10]; s16 r; u8 pad2[0xE]; } Ray;
void func_00118548(Ray *);
s32 func_0015dc50(void *vo) {
    ObjDC *o = vo;
    Ray r;
    HdrDC *h;
    PlatVu0CopyVector(r.a, o->pos);
    h = o->h;
    r.a[1] -= h->p10.p->f8;
    r.b[0] = r.b[2] = 0.0f;
    r.b[1] = h->p10.p->f8;
    r.b[3] = 1.0f;
    func_00118548(&r);
    return r.r;
}

/* func_0015dd50 (from hand/nostrict/text_00150000_h36.c). */
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
extern s32 D_002C5C54;
s32 func_001375f0(void *);
void func_0015dcc8(void *, f32 *);
s32 func_0015dd50(void *vo, f32 *v) {
    CylObj *o = vo;
    s32 r;
    f32 z, d[4], dd;
    if (D_002C5C54 == 0) {
        if ((func_001375f0(o) || !((s32)(o->x160.d >> 2) & 1)) && !(o->x160.w & 1)) {
            r = func_0015dc50(o);
            o->p148->x120 = r;
            if (r >= 0) {
                PlatVu0CopyVector(o->p148->x110, (*(f32 (*)[0x4])&D_002C58A0));
                z = 0.0f;
                if (z < v[3]) {
                    func_0015dcc8(o, d);
                    dd = PlatVu0InnerProduct(d, v);
                    if (z < dd) {
                        f32 f;
                        if (0.7999999523162842f < v[3]) f = o->p6C->f8; else f = o->p6C->f4;
                        PlatVu0ScaleVectorXYZ(o->p148->x110, d, f * dd);
                    }
                }
                func_0014f658(o, 12);
                return 1;
            }
        }
    }
    return 0;
}

/* func_0015dff8 (from hand/nostrict/text_00150000_h36.c). */
void func_0014cc88(void *, f32);
void func_00121fc4(f32 *, f32 *);
void func_00156260(void *, f32 *);
s32 func_0015dff8(CylObj *o, s32 flag) {
    s32 r;
    f32 d[4];
    if (flag) {
        func_0014cc88(o, 0.0f);
        PlatVu0CopyVector(o->x3C0, o->p148->x110);
        return 2;
    }
    r = func_0015dc50(o);
    o->p148->x120 = r;
    if (r < 0) {
        PlatVu0CopyVector(d, o->p148->x110);
        d[1] = 0;
        func_00121fc4(d, d);
        d[3] *= 5.0f;
        func_0014f658(o, 0);
        func_00156260(o, d);
    }
    return o->x70;
}

