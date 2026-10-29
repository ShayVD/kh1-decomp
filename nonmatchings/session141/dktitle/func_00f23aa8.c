/* dktitle.x func_00f23aa8: near-miss draft (session 132), not byte-identical; the port runs it (ovl/dktitle/drafts.tsv). Session 141 round 21 (wwm1): score 144 -> 138 with sclimb.py. */

void func_00206370(void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern u32 D_00F26E38;
extern u32 D_00F26E3C;
extern u8 D_00F26E70[];
extern u8 D_00F26E88[];
typedef s32 IV[4] __attribute__((aligned(16)));

s32 func_00f23aa8(void *o, s32 x, s32 a) {
    IV c[7];
    s32 p, i, f, top, bot, j;

    p = (s64)((u64)D_00F26E3C * 100) / D_00F26E38;
    if (p > 100) p = 100;
    c[6][0] = a / 2 << 24;
    i = p / 20;
    f = p % 20;
    j = i + 1;
    c[0][0] = D_00F26E70[i * 3 + 0]; c[0][1] = D_00F26E70[j * 3 + 0];
    c[1][0] = D_00F26E70[i * 3 + 1]; c[1][1] = D_00F26E70[j * 3 + 1];
    c[2][0] = D_00F26E70[i * 3 + 2]; c[2][1] = D_00F26E70[j * 3 + 2];
    c[3][0] = D_00F26E88[i * 3 + 0]; c[3][1] = D_00F26E88[j * 3 + 0];
    c[4][0] = D_00F26E88[i * 3 + 1]; c[4][1] = D_00F26E88[j * 3 + 1];
    c[5][0] = D_00F26E88[i * 3 + 2]; c[5][1] = D_00F26E88[j * 3 + 2];
    top = (c[0][0] * (20 - f) + c[0][1] * f) / 20 | c[6][0] | ((c[2][0] * (20 - f) + c[2][1] * f) / 20 << 16 | (c[1][0] * (20 - f) + c[1][1] * f) / 20 << 8);
    bot = (c[3][0] * (20 - f) + c[3][1] * f) / 20 | c[6][0] | ((c[5][0] * (20 - f) + c[5][1] * f) / 20 << 16 | (c[4][0] * (20 - f) + c[4][1] * f) / 20 << 8);
    func_00206370(o, 0, 0, 512, 319, top, top, bot, bot);
    return bot;
}
