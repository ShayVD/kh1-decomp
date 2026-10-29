/* gb.x func_00f24240 near miss: 182 words differ, score 112 (ours 800 bytes, original 816). Clamps the GbPos cursor box inside the world dims and the current position, then stores h60/h62/flags. Logic is complete. Size comes back as GbPos from func_001bbdf0, and the f24160 argument is read raw from D->pos. Left: flags = 0 should be hoisted to s5 at the top; the pos copy should be spilled to 8(sp), with x read from the raw lhu and z from the spill; and register numbering. The original also has the xori v0,v0,0 / movn idiom on both call results. Already tried: != 0 / == 0 forms and moving the flags = 0 placement (no change). */
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
extern GbWorld *D_00F56DC0;
T14 *func_00f24160(u16, s32);
GbPos func_001bbdf0(T14 *);
s32 func_00f23f68(GbPos, GbPos, s32);
s32 func_00f23ec0(s32);

s32 func_00f24240(s32 id, T14 *loc) {
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
        loc = &D_00F56DC0->home;
    }
    pos = D_00F56DC0->pos;
    c = D_00F56DC0->cur;
    c.y = pos.y;
    hit = func_00f24160(*(u16 *)&D_00F56DC0->pos, id);
    s = func_001bbdf0(loc);
    t = c;
    if (t.x + s.x >= D_00F56DC0->w)
        t.x = D_00F56DC0->w - s.x;
    if (t.y + s.y >= D_00F56DC0->d)
        t.y = D_00F56DC0->d - s.y;
    if (t.z + s.z >= D_00F56DC0->h)
        t.z = D_00F56DC0->h - s.z;
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
        D_00F56DC0->cur = *(GbPos *)&hit->t.h0;
        flags = 3;
        D_00F56DC0->h62 = func_001bbdf0(hit);
    } else {
        ret = 0;
        if (func_00f23f68(t, s, id))
            flags = 5;
        D_00F56DC0->h62 = s;
        D_00F56DC0->cur = t;
    }
    if (!func_00f23ec0(loc->t.h4 - 1))
        flags |= 0x11;
    D_00F56DC0->flags = flags;
    return ret;
}
