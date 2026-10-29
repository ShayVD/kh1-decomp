/* func_00f79700: near miss (session 141 round 4), score 187: GS upload packet (BITBLTBUF/TRXREG/TRXPOS/TRXDIR + image GIF tag + DMA ref); same code as func_00f69278. Ours spills to a 64/80-byte frame because every 64-bit value is computed up front; the original writes each qword through one base register (addiu t7,a0,N per qword), with the two DMA tags written after p[7]. Probably needs the right inline-helper shape (see func_00f7ef20). */
typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;

static inline void put(Qw *q, u64 a, u64 b) {
    q->w[0] = a;
    q->w[1] = a >> 32;
    q->w[2] = b;
    q->w[3] = b >> 32;
}

Qw *func_00f79700(Qw *p, s32 addr, s32 dx, s32 dy, s32 w, s32 h, s32 dbp, s32 dpsm, s32 dbw, s32 bpp) {
    s32 n = w * h * bpp / 128;

    put(&p[1], 0x1000000000000002, 14);
    put(&p[2], ((s64)dbp << 32) | ((s64)dbw << 48) | ((s64)dpsm << 56), 0x50);
    put(&p[3], ((s64)h << 32) | (u32)w, 0x52);
    put(&p[5], 0x1000000000000002, 14);
    put(&p[6], ((s64)dx << 32) | ((s64)dy << 48), 0x51);
    put(&p[7], 0, 0x53);
    p[4].d[0] = 0x10000004;
    p[0].d[0] = 0x10000003;
    put(&p[8], (n | 0x8000) | 0x0800000000000000, 0);
    p[9].d[0] = (u32)n | 0x30000000 | ((s64)(addr & ~0xF) << 32);
    return p + 10;
}
