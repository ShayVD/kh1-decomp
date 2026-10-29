/* wm.x func_00f51860: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u8 pad0[6]; u16 w; u8 pad8[2]; u16 h; } GbDims;
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 px : 4;
    u16 py : 4;
    u16 pz : 4;
    u16 pr : 4;
    u16 pad5e;
    GbPos cur;
    u8 pad62[0x74 - 0x62];
    u16 flags;
    u8 pad76[0x7E - 0x76];
    u8 b7e;
    u8 pad7f[0xA0 - 0x7F];
    GbDims dims;
} GbWorld;
typedef struct { u8 pad0[12]; GbPos step; } GbCell;
typedef struct { u8 pad0[4]; u16 id; u8 pad6[2]; u8 b8; } GbObj;
typedef struct { s32 pad0; s32 held; } GbPad;
extern GbWorld *D_00F9B540;
extern s32 D_00F9B544;
GbPad *func_001ba488(s32);
void func_00f51568(s32 *, s32 *);
GbCell *func_00f4b258(GbPos, s32);
void func_001c0688(s32);
void func_00f4b338(s32, s32);
GbObj *func_00f4b2e0(GbPos);
s32 func_00f4cad0(s32);
void func_00f4b878(s32);
void func_0011d768(s32);
void func_001bfac8(void);

void func_00f51860(void) {
    s32 dx, dz;
    GbDims *d = &D_00F9B540->dims;
    s32 x = D_00F9B540->px;
    s32 y = D_00F9B540->py;
    s32 z = D_00F9B540->pz;
    s32 sx, sz;
    s32 ox, oz;
    s32 moved, changed;
    GbPos pos;
    GbCell *c;
    GbObj *o;
    if (func_001ba488(0)->held & 0x1000) {
        do {
            func_00f51568(&dx, &dz);
            if (dx | dz) {
                sx = 1;
                sz = 1;
                if (D_00F9B540->flags & 2) {
                    c = func_00f4b258(D_00F9B540->cur, D_00F9B544);
                    if (c != NULL) {
                        sx = c->step.x;
                        sz = c->step.z;
                    }
                }
                if (dx != 0) {
                    if (dx < 0)
                        x = D_00F9B540->cur.x - 1;
                    else
                        x = D_00F9B540->cur.x + sx;
                }
                if (dz != 0) {
                    if (dz < 0)
                        z = D_00F9B540->cur.z - 1;
                    else
                        z = D_00F9B540->cur.z + sz;
                }
                if (x < 0)
                    x = 0;
                if (z < 0)
                    z = 0;
                if (x > d->w - 1)
                    x = d->w - 1;
                if (z > d->h - 1)
                    z = d->h - 1;
                moved = 0;
                changed = 0;
                pos.x = x;
                pos.y = y;
                pos.z = z;
                func_001c0688(2);
                if (pos.x != D_00F9B540->px || pos.z != D_00F9B540->pz)
                    moved = 1;
                ox = D_00F9B540->cur.x;
                oz = D_00F9B540->cur.z;
                *(GbPos *)((u8 *)D_00F9B540 + 0x5C) = pos;
                D_00F9B540->cur = pos;
                func_00f4b338(D_00F9B544, 0);
                if (ox != D_00F9B540->cur.x || oz != D_00F9B540->cur.z)
                    changed = 1;
                if (changed && (D_00F9B540->flags & 2)) {
                    o = func_00f4b2e0(D_00F9B540->cur);
                    if (o != NULL) {
                        if (func_00f4cad0(o->id - 1)) {
                            func_00f4b2e0(D_00F9B540->cur)->b8 = D_00F9B540->b7e;
                            func_00f4b878(D_00F9B544);
                            func_0011d768(2);
                        } else {
                            func_0011d768(4);
                        }
                    }
                } else if (moved) {
                    func_0011d768(20);
                }
            }
            func_001bfac8();
        } while (func_001ba488(0)->held & 0x1000);
    }
}
