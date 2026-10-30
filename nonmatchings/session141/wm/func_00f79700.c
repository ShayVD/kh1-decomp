/* Round 42 wwm2: score 41 -> 37. SETQ is expanded into plain statements, and r42/hill3o.py reordered the qword stores within each group. Left: sched2 order in the 3rd-5th qwords and the p[18] word. Writing it (u64)(u32)n | 0x30000000 | (addr & ~0xF) << 32 in any order or grouping is worse (117-142). */
/* Round 41 wwm2: score 84 -> 41, port.py of the gb twin func_00f42180 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* func_00f79700: score 84 (78 words; 344 vs 360 bytes), round 5. Same code as func_00f69278. PUT macro with one reassigned `Qw *q = &p[i]` per qword (the f7ef20/t7 trick) fixes the frame and the base register. Left: the original builds rg = (h<<32)|(u32)w, then `and` with 0xFFFFFFFF + dsll32/dsra32 for the TRXREG low word (ours stores w directly), and the instruction order of the bb/ps/n computations. `rg & 0xFFFFFFFF`, (u32)rg casts made it worse (127). */

#define SETQ(i, d, a) \
    q = (u32 *)&p[(i) * 2]; \
    q[0] = (d) & 0xFFFFFFFF; \
    q[1] = (u64)(d) >> 32; \
    q[2] = (a); \
    q[3] = 0;

u64 *func_00f79700(u64 *p, u32 addr, s32 x, s32 y, s32 w, s32 h, s32 dbp, s32 psm, s32 dbw, s32 bpp) {
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
