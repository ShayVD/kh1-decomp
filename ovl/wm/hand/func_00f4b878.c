/* wm.x func_00f4b878: matched by hand (session 141, wwm1 round 19): CONTEXT_ONLY func_001bb740 above (nothrow call), the min/max updates and else-branch stores reordered (sclimb.py), the grid index as yy * (h->w * h->h) + zz * h->w + xx, and the zero initializers as assignments after the declarations in the order x0, y0, z0, first, x1, y1, z1 (that order sets the stack slots 32/20/24/28). */
#include "ovl.h"
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 w : 4; } Cell;
typedef struct { Cell pos; u16 f2; u16 f4; u16 f6; u16 f8; u16 f10; } Ent;
typedef struct { Ent e; Cell size; u16 idx; } Slot;
typedef struct { u8 pad0[4]; u16 count; u16 w; u8 pad8[2]; u16 h; u8 pad12[100]; Ent ents[1]; } Hdr;
typedef struct { u32 x0 : 4; u32 y0 : 4; u32 z0 : 4; u32 pad : 4; u32 x1 : 4; u32 y1 : 4; u32 z1 : 4; } Box;
typedef struct { s32 f0; Box box; Slot grid[1]; } Grid;
typedef struct { u8 pad0[160]; Hdr hdr; u8 pad[4332 - 160 - sizeof(Hdr)]; u8 tab[1]; } World;
extern World *D_00F9B540;
s32 func_001bb740(void); CONTEXT_ONLY s32 func_001bb740() { return 0; }
u8 func_001ba3f0(s32);
void func_00f4af28(s32);
u16 func_001bbdf0(Ent *);
void func_00f4b878(Grid *g) {
    Hdr *h = &D_00F9B540->hdr;
    Slot *grid;
    Ent *e;
    Slot s;
    s32 x0, y0, z0, x1, y1, z1;
    s32 first;
    u8 *p;
    s32 i, x, y, z;
    x0 = 0;
    y0 = 0;
    z0 = 0;
    first = 0;
    x1 = 0;
    y1 = 0;
    z1 = 0;
    for (i = 0; i < func_001bb740(); i++) {
        D_00F9B540->tab[i] = func_001ba3f0(i);
    }
    for (i = 0; i < h->count; i++) {
        func_00f4af28(D_00F9B540->hdr.ents[i].f4 - 1);
    }
    grid = g->grid;
    for (i = 0, p = (u8 *)grid; i < sizeof(Slot) * 4096; i++) {
        *p++ = 0;
    }
    for (i = 0, e = h->ents; i < h->count; i++, e++) {
        e->f6 = 33;
        y = e->pos.y;
        z = e->pos.z;
        x = e->pos.x;
        s.e = *e;
        *(u16 *)&s.size = func_001bbdf0(e);
        s.idx = i;
        {
            s32 yy, zz, xx;
            for (yy = y; yy < y + s.size.y; yy++) {
                for (zz = z; zz < z + s.size.z; zz++) {
                    for (xx = x; xx < x + s.size.x; xx++) {
                        grid[yy * (h->w * h->h) + zz * h->w + xx] = s;
                    }
                }
            }
        }
        if (first) {
            if (x < x0) x0 = x;
            if (y < y0) y0 = y;
            if (z < z0) z0 = z;
            if (x1 < x + s.size.x - 1) x1 = x + s.size.x - 1;
            if (y1 < y + s.size.y - 1) y1 = y + s.size.y - 1;
            if (z1 < z + s.size.z - 1) z1 = z + s.size.z - 1;
        } else {
            x0 = x;
            y0 = y;
            z0 = z;
            x1 = x + s.size.x - 1;
            y1 = y + s.size.y - 1;
            first = 1;
            z1 = z + s.size.z - 1;
        }
    }
    g->box.x0 = x0;
    g->box.y0 = y0;
    g->box.z0 = z0;
    g->box.x1 = x1;
    g->box.y1 = y1;
    g->box.z1 = z1;
}
