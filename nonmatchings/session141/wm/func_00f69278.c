/* drafttwins.py: score 41 -> 37, port.py of the gb twin func_00f42180 draft. Earlier header below. */
/* score 41 (356 vs 360 is only the trailing alignment nop). Separate s64 locals bb/tr/tp (one shared `v` made gcc copy into t8: 101 -> 41), lo = v & 0xFFFFFFFF, and p[0] = 0x10000003 before p[8] = 0x10000004. Left: the DMA ref tag; the original zero-extends qwc first (dsll32/dsrl32), ORs 0x30000000 as a 64-bit op, then ORs addr<<32; every spelling tried (u64 casts, a tag variable at every position, operand orders) either narrows the OR to 32 bits or ORs addr first. A 20-minute permuter run found nothing better. */
#define SETQ(i, d, a) \
    q = (u32 *)&p[(i) * 2]; \
    q[0] = (d) & 0xFFFFFFFF; \
    q[1] = (u64)(d) >> 32; \
    q[2] = (a); \
    q[3] = 0;

u64 *func_00f69278(u64 *p, u32 addr, s32 x, s32 y, s32 w, s32 h, s32 dbp, s32 psm, s32 dbw, s32 bpp) {
    u32 *q;
    s32 n = w * h * bpp / 128;
    p[0] = 0x10000003;
    q = (u32 *)&p[(1) * 2];
    q[0] = (0x1000000000000002) & 0xFFFFFFFF;
    q[1] = (u64)(0x1000000000000002) >> 32;
    q[2] = (0xE);
    q[3] = 0;
    q = (u32 *)&p[(2) * 2];
    q[0] = (((u64)psm << 56) | ((u64)dbw << 48) | ((u64)dbp << 32)) & 0xFFFFFFFF;
    q[2] = (0x50);
    q[1] = (u64)(((u64)psm << 56) | ((u64)dbw << 48) | ((u64)dbp << 32)) >> 32;
    q[3] = 0;
    q = (u32 *)&p[(3) * 2];
    q[0] = (((u64)h << 32) | (u64)(u32)w) & 0xFFFFFFFF;
    p[8] = 0x10000004;
    q[2] = (0x52);
    q[1] = (u64)(((u64)h << 32) | (u64)(u32)w) >> 32;
    q[3] = 0;
    q = (u32 *)&p[(5) * 2];
    q[0] = (0x1000000000000002) & 0xFFFFFFFF;
    q[1] = (u64)(0x1000000000000002) >> 32;
    q[2] = (0xE);
    q[3] = 0;
    q = (u32 *)&p[(6) * 2];
    q[0] = (((u64)y << 48) | ((u64)x << 32)) & 0xFFFFFFFF;
    q[1] = (u64)(((u64)y << 48) | ((u64)x << 32)) >> 32;
    q[2] = (0x51);
    q[3] = 0;
    q = (u32 *)&p[(7) * 2];
    q[0] = (0) & 0xFFFFFFFF;
    q[1] = (u64)(0) >> 32;
    q[2] = (0x53);
    q[3] = 0;
    q = (u32 *)&p[16];
    q[0] = n | 0x8000;
    q[1] = 0x08000000;
    q[2] = 0;
    q[3] = 0;
    p[18] = ((u64)(addr & ~0xF) << 32) | 0x30000000 | (u64)(u32)n;
    return p + 20;
}
