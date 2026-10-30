/* Round 47 wwm2: score 58 -> 20, hill3o statement order. Earlier header below. */
/* 67 words (score 58, 288 vs 296). GS sprite packet, (x+1792)<<4 form; tried store permutations and permuter. */
void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5670[];

void *func_00f4d9c0(u8 *p, s32 a, s32 b, s32 c, s32 x, s32 y, s32 w, s32 h) {
    void *r;

    r = func_00f4d550(p, D_00FA5670, 0x130);
    *(u64 *)(p + 0x60) = ((u64)a << 32) | 100;
    *(u64 *)(p + 0x70) = ((u64)b << 1) | ((u64)c << 4) | 0x30001;
    w += x;
    h += y;
    *(u64 *)(p + 0xB0) = (x << 4) | ((u64)(y << 4) << 16);
    *(u64 *)(p + 0xD0) = (w << 4) | ((u64)(h << 4) << 16);
    *(u64 *)(p + 0xE0) = ((w + 1792) << 4) | ((u64)((h + 1856) << 4) << 16) | ((u64)1 << 32);
    *(u64 *)(p + 0xC0) = ((x + 1792) << 4) | ((u64)((y + 1856) << 4) << 16) | ((u64)1 << 32);
    return r;
}
