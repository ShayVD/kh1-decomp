/* The KeMdlTfd model draw, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a9790 fills a draw block for model id of the resource (colour from
 * col >> 7, position x, y, the flags fl) and hands it to opdma.c's
 * func_001aaf88.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"

typedef f32 Mtx4[4][4];
typedef struct { u32 flags; u8 pad04[0x12]; u16 h16; } DMdl;
typedef struct { u8 pad[0x14]; void *x14; u8 pad18[4]; DMdl *mdl; s32 x20; } Ent24;
typedef struct { u8 pad[0x10]; Mtx4 m; Mtx4 m2; u8 *x90; s32 x94; } PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
typedef struct { u8 pad0[0x10]; Ent24 *x10; void *anims; void *grps; } PppRes;
extern PppRes *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern Mtx4 D_00615FC0;

typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s16 h0C;
    s16 h0E;
    s32 w10;
    s32 w14;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    u8 *w38;
    s32 w3C;
    s32 w40;
    void *p44;
    u8 pad48[0x18];
} DParam;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;
s32 func_001aaf88(DMdl *, DParam *, s32);

void func_001a9790(s32 id, u16 *col, s32 h, s32 x, s32 y, u8 fl, void *p) {
    Mtx4 m;
    DParam c;
    Ent24 *s;
    DMdl *md;

    if (id == 0xffff)
        return;
    s = &D_00615E64->x10[id];
    md = s->mdl;
    c.flags = 0;
    if (fl & 2) {
        c.flags = 4;
        if (!(md->flags & 1))
            c.flags |= 8;
    } else {
        if (fl & 1)
            c.flags = 128;
        if (!(md->flags & 1))
            c.flags |= 8;
    }
    if (!(md->flags & 2))
        c.flags |= 16;
    if (fl & 4)
        c.flags |= 0x200;
    if (fl & 8)
        c.flags |= 0x100;
    if (fl & 0x10) {
        c.flags |= 0x2000;
        c.p30 = m;
        PlatVu0MulMatrix(m, D_00615FC0, D_00615E68->m);
    }
    c.p44 = (fl & 0x20) ? p : 0;
    c.h08 = md->h16;
    c.w1C = 0;
    c.w38 = D_00615E68->x90;
    c.w3C = D_00615E68->x94;
    c.h0C = 0;
    c.p04 = D_00616240;
    c.h0E = h;
    c.w10 = x << 16;
    c.w14 = y << 16;
    c.w40 = 0;
    c.b0A = 0;
    c.r = col[0] >> 7;
    c.g = col[1] >> 7;
    c.b = col[2] >> 7;
    c.a = col[3] >> 7;
    c.p20 = D_00615E68->m2;
    c.p24 = D_00616140;
    c.p28 = D_00616100;
    c.p2C = D_00615E68->m;
    c.w34 = D_00616224;
    D_00616224 = func_001aaf88(md, &c, s->x20);
}
