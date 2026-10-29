/* score 101 (356 vs 360). GS LoadImage packet: DMA cnt tag + A+D BITBLTBUF/TRXREG, cnt tag + TRXPOS/TRXDIR + image GIFtag, ref tag. The qwords are written as u32[4] with lo = v & 0xFFFFFFFF, hi = v >> 32 (the mask is needed for the TRXREG and/lui 0xffff). Left: scheduling order of the value builds/stores and one missing insn; precomputing all values first scored 131; a 6-minute permuter run found nothing. */
u64 *func_00f69278(u64 *p, u32 addr, s32 x, s32 y, s32 w, s32 h, s32 dbp, s32 psm, s32 dbw, s32 bpp)
{
    s32 qwc;
    u32 *q;
    s64 v;

    qwc = w * h * bpp / 128;
    q = (u32 *)(p + 2);
    q[0] = 2;
    q[1] = 0x10000000;
    q[2] = 14;
    q[3] = 0;
    q = (u32 *)(p + 4);
    v = ((s64)psm << 56) | ((s64)dbw << 48) | ((s64)dbp << 32);
    q[0] = v & 0xFFFFFFFF;
    q[1] = v >> 32;
    q[2] = 0x50;
    q[3] = 0;
    q = (u32 *)(p + 6);
    v = ((s64)h << 32) | (u32)w;
    q[0] = v & 0xFFFFFFFF;
    q[1] = v >> 32;
    q[2] = 0x52;
    q[3] = 0;
    q = (u32 *)(p + 10);
    q[0] = 2;
    q[1] = 0x10000000;
    q[2] = 14;
    q[3] = 0;
    q = (u32 *)(p + 12);
    v = ((s64)y << 48) | ((s64)x << 32);
    q[0] = v & 0xFFFFFFFF;
    q[1] = v >> 32;
    q[2] = 0x51;
    q[3] = 0;
    q = (u32 *)(p + 14);
    q[0] = 0;
    q[1] = 0;
    q[2] = 0x53;
    q[3] = 0;
    p[8] = 0x10000004;
    p[0] = 0x10000003;
    q = (u32 *)(p + 16);
    q[0] = qwc | 0x8000;
    q[1] = 0x08000000;
    q[2] = 0;
    q[3] = 0;
    p[18] = (u32)qwc | 0x30000000 | ((u64)(addr & ~0xF) << 32);
    return p + 20;
}
