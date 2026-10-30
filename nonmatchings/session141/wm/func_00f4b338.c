/* Round 47 wwm2: score 112 -> 84, hill3o statement order. Earlier header below. */
/* wm f4b338 near miss (port of gb twin f24240 near miss): 182 words differ, score 112 (800 vs 816 bytes). Same shape and leftovers as the gb twin: id and own live in 0/4(sp) and the pos copy in 8(sp) in the original, flags=0 hoisted to s5, register numbering. Tried flags/own init placement and pos/cur load order (no change). */
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; u8 b8; u8 b9; u16 h10; } T12;
typedef struct { T12 t; u16 h12; } T14;
typedef struct {
    u16 x : 4;
    u16 y : 4;
    u16 z : 4;
    u16 r : 4;
} GbPos;
typedef struct {
    u8 pad0[0x48];
    T14 home;
    u8 pad56[0x5C - 0x56];
    GbPos pos;
    u16 pad5e;
    GbPos cur;
    GbPos h62;
    u8 pad64[0x74 - 0x64];
    u16 flags;
    u8 pad76[0xA6 - 0x76];
    u16 w;
    u16 d;
    u16 h;
} GbWorld;
extern GbWorld *D_00F9B540;
T14 *func_00f4b258(u16, s32);
GbPos func_001bbdf0(T14 *);
s32 func_00f4b060(GbPos, GbPos, s32);
s32 func_00f4afb8(s32);

s32 func_00f4b338(s32 id, T14 *loc) {
    GbPos c;
    GbPos pos;
    s32 own = 0;
    s32 ret;
    GbPos s;
    s32 flags = 0;
    T14 *hit;
    GbPos t;
    if (loc == NULL) {
        loc = &D_00F9B540->home;
        own = 1;
    }
    pos = D_00F9B540->pos;
    c = D_00F9B540->cur;
    hit = func_00f4b258(*(u16 *)&D_00F9B540->pos, id);
    c.y = pos.y;
    t = c;
    s = func_001bbdf0(loc);
    if (t.x + s.x >= D_00F9B540->w)
        t.x = D_00F9B540->w - s.x;
    if (t.y + s.y >= D_00F9B540->d)
        t.y = D_00F9B540->d - s.y;
    if (t.z + s.z >= D_00F9B540->h)
        t.z = D_00F9B540->h - s.z;
    if (pos.x < t.x)
        t.x = pos.x;
    if (pos.y < t.y)
        t.y = pos.y;
    if (pos.z < t.z)
        t.z = pos.z;
    if (pos.x >= t.x + s.x)
        t.x = pos.x - s.x + 1;
    if (pos.y >= t.y + s.y)
        t.y = pos.y - s.y + 1;
    if (pos.z >= t.z + s.z)
        t.z = pos.z - s.z + 1;
    if (own && hit != NULL) {
        flags = 3;
        D_00F9B540->cur = *(GbPos *)&hit->t.h0;
        D_00F9B540->h62 = func_001bbdf0(hit);
        ret = 1;
    } else {
        ret = 0;
        if (func_00f4b060(t, s, id))
            flags = 5;
        D_00F9B540->h62 = s;
        D_00F9B540->cur = t;
    }
    if (!func_00f4afb8(loc->t.h4 - 1))
        flags |= 0x11;
    return ret;
    D_00F9B540->flags = flags;
}
