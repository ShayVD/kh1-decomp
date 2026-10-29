/* score 5 (5 words; 852 vs 856 bytes). Menu text builder; same type table as func_00f67928. Permuter found `r = 100 + i * 24;` (reusing dead r as the y argument) which fixed the loop giv. Left: in the second sprite qword the original schedules `addiu a0,a0,2072` before the two dsll; and `move s4,s6` / `lui s5,0xfa` swap before the inner loop. Tried x/y temporaries, x1/y1 locals, an s64 temp, operand orders, do-while, y forms. */
extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
u64 *func_001f0798(u64 *, s32, s32, s32, s32, char *, s32);
char *func_00f632d0(s32);

void func_00f639c0(char *str, s32 type, s32 val)
{
    u64 *p = *D_00FA66D8;
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
    p = func_00f66b78(func_00f66ac8(p));
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    func_00f66b90(p);
    p = func_001f0798(p, 1, 0x80808080, 256, 54, str, 20);
    p = func_00f66b78(p);
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
    func_00f66b90(p);
    for (i = 0; i < lim; i++) {
        s = func_00f632d0(base + i);
        for (j = 0; s[j]; j += 2) {
            buf[0] = s[j];
            buf[1] = s[j + 1];
            buf[2] = 0;
            r = 100 + i * 24;
            p = func_001f0798(p, 1, 0x80808080, 260 + j * 12, r, buf, D_00FA66DC);
        }
    }
    func_00f66f78(40000, func_00f66ae0(p));
    *D_00FA66D8 = p;
}
