/* gb.x func_00f3c8c8 near miss: 5 words differ, score 5 (ours 852 bytes, original 856). This is wm func_00f639c0's near miss ported with tools/ovl/port.py; the same 5 words are left. One: the second sprite qword's addiu a0,a0,2072 should be scheduled before the two dsll. Two: move s4,s6 / lui s5,0xf6 swap before the inner loop. Already tried: incrementing x and y, separate x+2072 / y+1976 terms, a pre-shifted y, and swapping the x/y order (all 5 or worse). */
extern u64 **D_00F61F58;
extern s32 D_00F61F5C;
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_001f0798(u64 *, s32, s32, s32, s32, char *, s32);
char *func_00f3c1d8(s32);

void func_00f3c8c8(char *str, s32 type, s32 val)
{
    u64 *p = *D_00F61F58;
    s32 base, lim, i, j, q, r, x, y;
    char *s;
    char buf[4];

    switch (type) {
    case 0:
        base = 15;
        lim = 10;
        break;
    case 1:
        base = 25;
        lim = 7;
        break;
    case 2:
        base = 32;
        lim = 10;
        break;
    case 3:
        base = 42;
        lim = 7;
        break;
    case 4:
        base = 49;
        lim = 8;
        break;
    case 5:
        base = 57;
        lim = 7;
        break;
    }
    p = func_00f3fa80(func_00f3f9d0(p));
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    func_00f3fa98(p);
    p = func_001f0798(p, 1, 0x80808080, 256, 54, str, 20);
    p = func_00f3fa80(p);
    p[0] = 70;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F80000080202020LL;
    p[1] = 1;
    p += 2;
    p[0] = 0x179807F80LL;
    p[1] = 5;
    p += 2;
    p[0] = 0x189808C00LL;
    p[1] = 5;
    p += 2;
    q = val / 5;
    r = val % 5;
    p[0] = 70;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F800000802020FFLL;
    p[1] = 1;
    p += 2;
    x = r * 24 + 2048;
    y = q * 24 + 1952;
    p[0] = ((s64)x << 4) | ((s64)(y << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = ((s64)(x + 24) << 4) | ((s64)((y + 24) << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    func_00f3fa98(p);
    for (i = 0; i < lim; i++) {
        s = func_00f3c1d8(base + i);
        for (j = 0; s[j]; j += 2) {
            buf[0] = s[j];
            buf[1] = s[j + 1];
            buf[2] = 0;
            r = 100 + i * 24;
            p = func_001f0798(p, 1, 0x80808080, 260 + j * 12, r, buf, D_00F61F5C);
        }
    }
    func_00f3fe80(40000, func_00f3f9e8(p));
    *D_00F61F58 = p;
}
