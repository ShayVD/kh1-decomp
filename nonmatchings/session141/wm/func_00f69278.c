/* score 41 (356 vs 360 is only the trailing alignment nop). Separate s64 locals bb/tr/tp (one shared `v` made gcc copy into t8: 101 -> 41), lo = v & 0xFFFFFFFF, and p[0] = 0x10000003 before p[8] = 0x10000004. Left: the DMA ref tag; the original zero-extends qwc first (dsll32/dsrl32), ORs 0x30000000 as a 64-bit op, then ORs addr<<32; every spelling tried (u64 casts, a tag variable at every position, operand orders) either narrows the OR to 32 bits or ORs addr first. A 20-minute permuter run found nothing better. */
u64 *func_00f69278(u64 *p, u32 addr, s32 x, s32 y, s32 w, s32 h, s32 dbp, s32 psm, s32 dbw, s32 bpp)
{
    s32 qwc;
    u32 *q;
    s64 bb, tr, tp;
    u64 tag;

    qwc = w * h * bpp / 128;
    q = (u32 *)(p + 2);
    q[0] = 2;
    q[1] = 0x10000000;
    q[2] = 14;
    q[3] = 0;
    q = (u32 *)(p + 4);
    bb = ((s64)psm << 56) | ((s64)dbw << 48) | ((s64)dbp << 32);
    q[0] = bb & 0xFFFFFFFF;
    q[1] = bb >> 32;
    q[2] = 0x50;
    q[3] = 0;
    q = (u32 *)(p + 6);
    tr = ((s64)h << 32) | (u32)w;
    q[0] = tr & 0xFFFFFFFF;
    q[1] = tr >> 32;
    q[2] = 0x52;
    q[3] = 0;
    q = (u32 *)(p + 10);
    q[0] = 2;
    q[1] = 0x10000000;
    q[2] = 14;
    q[3] = 0;
    q = (u32 *)(p + 12);
    tp = ((s64)y << 48) | ((s64)x << 32);
    q[0] = tp & 0xFFFFFFFF;
    q[1] = tp >> 32;
    q[2] = 0x51;
    q[3] = 0;
    q = (u32 *)(p + 14);
    q[0] = 0;
    q[1] = 0;
    q[2] = 0x53;
    q[3] = 0;
    p[0] = 0x10000003;
    p[8] = 0x10000004;
    q = (u32 *)(p + 16);
    q[0] = qwc | 0x8000;
    q[1] = 0x08000000;
    q[2] = 0;
    q[3] = 0;
    p[18] = ((u64)(addr & ~0xF) << 32) | 0x30000000 | (u32)qwc;
    return p + 20;
}
