/* 9 words / score 19: the original copies e->w into another register for the first log2 loop (move a0,t2) and uses t1 for e->h. */
typedef struct {
    s32 addr;
    s32 pad4;
    s32 bpp;
    s32 padc;
    u32 w;
    u32 h;
    s32 pad18;
} GbImg;
typedef struct {
    u8 pad0[0xC];
    GbImg *imgs;
} GbTex;

static inline s32 log2u(u32 x) {
    s32 r = 0;
    u32 n = 1;
    while (n < x) {
        n <<= 1;
        r++;
    }
    return r;
}
u64 func_00f3eac0(s32 base, GbTex *t, s32 idx, s32 coff) {
    GbImg *e = &t->imgs[idx];
    s32 tbp = base + e->addr / 256;
    s32 cbp = 0;
    s32 tcc = 0;
    s32 psm;
    s32 tw, th;
    u32 n;
    switch (e->bpp) {
    case 4:
        cbp = tbp + coff;
        psm = 20;
        tcc = 1;
        break;
    case 8:
        cbp = tbp + coff * 4;
        psm = 19;
        tcc = 1;
        break;
    case 16:
        psm = 2;
        break;
    case 24:
        psm = 1;
        break;
    case 32:
        psm = 0;
        tcc = 1;
        break;
    default:
        return 0;
    }
    tw = log2u(e->w);
    th = log2u(e->h);
    return base | ((u64)(e->w >> 6) << 14) | ((u64)psm << 20) | ((u64)tw << 26) | ((u64)th << 30) | ((u64)tcc << 34) | ((u64)cbp << 37) | ((u64)1 << 61);
}
