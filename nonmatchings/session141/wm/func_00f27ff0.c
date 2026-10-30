/* Round 47 wwm2: score 102 -> 90, hill3o statement order. Earlier header below. */
/* 71 words (352 vs 360). Row layout loop; target uses 9 s-regs and spills per with sq. Tried ternary/if row count, gx local. */
s32 func_00f26e48(s32 *);
void func_00f27d18(s32, s32, s32);

void func_00f27ff0(s32 x, s32 y, s32 *items) {
    s32 *p;
    s32 ystep;
    s32 gx;
    s32 step;
    s32 rows;
    s32 cnt;
    s32 cy;
    s32 cx;
    s32 i;
    s32 n;
    s32 r;
    s32 gap;
    s32 per;
    n = func_00f26e48(items);
    p = items;
    rows = 2;

    if (n < 4) {
        rows = 1;
    }
    per = n / rows + (n % rows != 0);
    gap = (298 - rows * 144) / (rows + 1);
    cy = gap + 46;
    ystep = gap + 144;
    for (r = 0; r < rows; r++) {
        cnt = (n < per) ? n : per;
        gx = (512 - cnt * 96) / (cnt + 1);
        cx = gx;
        step = gx + 96;
        for (i = 0; i < cnt; i++) {
            func_00f27d18(x + cx, y + cy, *p++);
            cx += step;
        }
        n -= cnt;
        cy += ystep;
    }
}
