/* score 179 (1084 vs 1088). Port of gb func_00f24d00 (wgb near miss, same score) via portmap2. See the gb header for what is left. Round 26 wwm2. */
typedef struct {
    u16 x : 4;
    u16 y : 4;
    u16 z : 4;
    u16 r : 4;
} GbPos;
typedef struct {
    GbPos p;
    u8 pad2[10];
} GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 d;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
extern GbMap *D_00F9B540;
u16 func_001bbdf0(GbEnt *);
void func_001bbf88(GbEnt *, s32, s32);

void func_00f4bdf8(s32 axis, s32 dir) {
    GbHdr *h = &D_00F9B540->hdr;
    GbEnt *e;
    s32 i, t, w, d, hh;
    u16 sz;
    GbPos o, n;
    if (dir == 0)
        return;
    e = h->ents;
    d = h->d;
    w = h->w;
    hh = h->h;
    switch (axis) {
    case 0:
        t = d;
        d = hh;
        hh = t;
        if (dir != -1) {
            if (dir == 1) {
                for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.y = d - o.z - ((sz >> 8) & 0xF);
                    e->p.z = o.y;
                    func_001bbf88(e, axis, dir);
                    e++;
                }
            }
        } else {
            for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.x = o.x;
                    e->p.y = o.z;
                    e->p.z = hh - o.y - ((sz >> 4) & 0xF);
                    func_001bbf88(e, axis, dir);
                    e++;
                }
        }
        break;
    case 1:
        t = hh;
        hh = w;
        w = t;
        if (dir != -1) {
            if (dir == 1) {
                for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.z = o.x;
                    e->p.y = o.y;
                    e->p.x = w - o.z - ((sz >> 8) & 0xF);
                    func_001bbf88(e, axis, dir);
                    e++;
                }
            }
        } else {
            for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.x = o.z;
                    e->p.y = o.y;
                    e->p.z = hh - o.x - (sz & 0xF);
                    func_001bbf88(e, axis, dir);
                    e++;
                }
        }
        break;
    case 2:
        t = d;
        d = w;
        w = t;
        if (dir != -1) {
            if (dir == 1) {
                for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.x = w - o.y - ((sz >> 4) & 0xF);
                    e->p.y = o.x;
                    e->p.z = o.z;
                    func_001bbf88(e, axis, dir);
                    e++;
                }
            }
        } else {
            for (i = 0; i < h->count; i++) {
                    sz = func_001bbdf0(e);
                    o = e->p;
                    e->p.x = o.y;
                    e->p.z = o.z;
                    e->p.y = d - o.x - (sz & 0xF);
                    func_001bbf88(e, axis, dir);
                    e++;
                }
        }
        break;
    }
}
