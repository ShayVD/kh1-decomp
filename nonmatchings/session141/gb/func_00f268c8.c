/* Round 41 wwm2: score 84 -> 58, port.py of the wm twin func_00f4d9c0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* Round 35 (wgb): gb.x func_00f268c8 near miss: 67 -> 56 words, score 88 -> 84. Store order inside the //{ //} block from a dependency-safe statement-order hill climb (round 35 hill3.py: only orders that keep every read/write conflict in place). The wm twin func_00f4d9c0 gets 56 words but a worse score (84 vs 58), so it is not ported. Earlier header below. */
void *func_00f26458(void *, void *, s32);
extern u8 D_00F60EF0[];

void *func_00f268c8(u8 *p, s32 a, s32 b, s32 c, s32 x, s32 y, s32 w, s32 h) {
    void *r;

    h += y;
    w += x;
    r = func_00f26458(p, D_00F60EF0, 0x130);
    *(u64 *)(p + 0x60) = ((u64)a << 32) | 100;
    *(u64 *)(p + 0x70) = ((u64)b << 1) | ((u64)c << 4) | 0x30001;
    *(u64 *)(p + 0xB0) = (x << 4) | ((u64)(y << 4) << 16);
    *(u64 *)(p + 0xD0) = (w << 4) | ((u64)(h << 4) << 16);
    *(u64 *)(p + 0xE0) = ((w + 1792) << 4) | ((u64)((h + 1856) << 4) << 16) | ((u64)1 << 32);
    *(u64 *)(p + 0xC0) = ((x + 1792) << 4) | ((u64)((y + 1856) << 4) << 16) | ((u64)1 << 32);
    return r;
}
