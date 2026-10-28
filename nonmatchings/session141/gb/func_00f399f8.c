/* 104 words / score 110 (472 vs 512 bytes): the call sequence and nibble-bitfield entity loop are right. Left: the original keeps n (func_001bb678) as an int and recomputes (u16)n for each of the three x88 nibble fields separately (+0xffff for -1, one with a 64-bit dsrl), plus the n*420-2520 float; my u16 temporaries get CSE'd. Wanted for the f22d00 table (wm twin func_00f60af0). */
typedef struct { u16 x : 4, y : 4, z : 4, w : 4; u16 b, c, flags, d, e; } GbEnt2;
typedef struct { u64 lo : 32; u64 f0 : 4; u64 f1 : 4; u64 f2 : 4; u64 hi : 20; } GbBits;
typedef struct {
    u8 pad0[88];
    GbBits x88;
    u8 pad60[136 - 96];
    f32 x136;
    u8 pad8c[164 - 140];
    u16 count;
    u16 w;
    u16 x168;
    u16 h;
    u8 padac[272 - 172];
    GbEnt2 ents[1];
} GbMap;
extern GbMap *D_00F56DC0;
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001be1e8(s32, s32);
void func_001bd470(void);
s32 func_001bb678(void);

void func_00f399f8(s32 idx) {
    s32 m, i, d, n;
    u16 h;
    GbEnt2 *e;
    if (idx >= func_001bc4a8())
        m = idx - func_001bc4a8();
    else
        m = func_001bc4b8(idx) | 0x80;
    func_001be1e8(0, m);
    func_001bd470();
    n = func_001bb678();
    d = (n - D_00F56DC0->w) / 2;
    for (i = 0; i < D_00F56DC0->count; i++) {
        e = &D_00F56DC0->ents[i];
        if (e->c) {
            e->x += d;
            e->y += d;
            e->z += d;
        }
    }
    h = n >> 1;
    D_00F56DC0->x88.f0 = h - 1;
    D_00F56DC0->x88.f1 = h;
    D_00F56DC0->x88.f2 = h - 1;
    D_00F56DC0->w = n;
    D_00F56DC0->h = n;
    D_00F56DC0->x168 = n;
    D_00F56DC0->x136 = -2944.0f - (n * 420 - 2520);
}
