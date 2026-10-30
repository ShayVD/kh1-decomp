/* gb.x func_00f299c8: matched by hand. */
#include "ovl.h"

/* gb.x func_00f299c8: matched by hand (session 141, from the wgb worker draft). The lock flag is a plain u16 read as (u16)(flags & 1), GbLoc is all u16 (2-byte aligned, so the copy uses ldl/lwl), and func_00f291f0 takes no argument. */
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u16 pos; u16 pad2; u16 id; u16 pad6; u16 pad8; u16 pad10; } GbLoc;
typedef struct { u8 pad0[6]; u16 w; u8 pad8[2]; u16 h; } GbDims;
typedef struct {
    u64 pad0[9];
    GbLoc loc;
    u8 pad54[0x5C - 0x54];
    GbPos prev;
    u16 pad5e;
    GbPos cur;
    u16 sx : 4;
    u16 q1 : 4;
    u16 sz : 4;
    u16 q2 : 4;
    u8 pad64[0x74 - 0x64];
    u16 flags;
    u8 pad76[0xA0 - 0x76];
    GbDims dims;
} GbWorld;
typedef struct { s32 pad0; s32 held; } GbPad;
extern GbWorld *D_00F56DC0;
extern s32 D_00F56DC4;
GbPad *func_001ba488(s32);
void func_00f2a470(s32 *, s32 *);
s32 func_00f291f0(void);
void func_0011d768(s32);
void func_00f24680(GbLoc *);
void func_00f291c0(s32);
void func_00f23e30(s32);
void func_00f24780(s32);
void func_00f24240(s32, s32);
void func_001bfac8(void);

s32 func_00f299c8(void) {
    GbDims *d = &D_00F56DC0->dims;
    GbPos pos;
    GbPad *pad;
    GbLoc loc;
    s32 dx, dz;
    s32 x = D_00F56DC0->cur.x;
    s32 y = D_00F56DC0->cur.y;
    s32 z = D_00F56DC0->cur.z;
    s32 sx = D_00F56DC0->sx;
    s32 sz = D_00F56DC0->sz;
    s32 ox, oz, r;
    s32 ret = 1;
    if (func_001ba488(0)->held & 0x2000) {
        do {
            pad = func_001ba488(0);
            func_00f2a470(&dx, &dz);
            if (dx | dz) {
                if (!(u16)(D_00F56DC0->flags & 1)) {
                    loc = D_00F56DC0->loc;
                    loc.pos = *(u16 *)&D_00F56DC0->cur;
                    r = func_00f291f0();
                    if (r == 0) {
                        func_0011d768(2);
                        func_00f24680(&loc);
                    } else {
                        func_00f291c0(r);
                        ret = 0;
                    }
                    func_00f23e30(loc.id - 1);
                    func_00f24780(D_00F56DC4);
                    if (ret == 0)
                        return 0;
                }
                ox = x;
                oz = z;
                x += dx * sx;
                if (x < 0)
                    x = 0;
                if (x > d->w - 1)
                    x = d->w - 1;
                z += dz * sz;
                if (z < 0)
                    z = 0;
                if (z > d->h - 1)
                    z = d->h - 1;
                if ((u16)(D_00F56DC0->flags & 1) && (ox != x || oz != z))
                    func_0011d768(20);
                pos.x = x;
                pos.y = y;
                pos.z = z;
                func_001bfac8();
                func_001bfac8();
                D_00F56DC0->prev = pos;
                D_00F56DC0->cur = pos;
                func_00f24240(D_00F56DC4, 0);
            }
            func_001bfac8();
        } while (pad->held & 0x2000);
    }
    return ret;
}
