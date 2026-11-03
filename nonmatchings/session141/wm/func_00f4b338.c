/* Round 48 wwm2: the hill3o order from a672e810 (wm func_00f4b338 near miss, score 112 -> 84, hill3o statement order (wwm2 round ) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 84 was not valid. Restored the last valid statement order: score 112. Earlier header below. */
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
#ifdef KH1_PS2
GbPos func_001bbdf0(T14 *);
#else /* a port: the definition returns s32 (src/gummi/ship.c); an i386 struct return is a hidden pointer */
s32 func_001bbdf0(T14 *);
static __inline__ GbPos ee_001bbdf0(T14 *p) {
    union { s32 i; GbPos s; } u;
    u.i = func_001bbdf0(p);
    return u.s;
}
#define func_001bbdf0 ee_001bbdf0
#endif
s32 func_00f4b060(GbPos, GbPos, s32);
s32 func_00f4afb8(s32);

s32 func_00f4b338(s32 id, T14 *loc) {
    s32 own = 0;
    GbPos pos;
    GbPos c;
    GbPos t;
    T14 *hit;
    GbPos s;
    s32 flags = 0;
    s32 ret;
    if (loc == NULL) {
        own = 1;
        loc = &D_00F9B540->home;
    }
    pos = D_00F9B540->pos;
    c = D_00F9B540->cur;
    c.y = pos.y;
    hit = func_00f4b258(*(u16 *)&D_00F9B540->pos, id);
    s = func_001bbdf0(loc);
    t = c;
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
        ret = 1;
        D_00F9B540->cur = *(GbPos *)&hit->t.h0;
        flags = 3;
        D_00F9B540->h62 = func_001bbdf0(hit);
    } else {
        ret = 0;
        if (func_00f4b060(t, s, id))
            flags = 5;
        D_00F9B540->h62 = s;
        D_00F9B540->cur = t;
    }
    if (!func_00f4afb8(loc->t.h4 - 1))
        flags |= 0x11;
    D_00F9B540->flags = flags;
    return ret;
}
