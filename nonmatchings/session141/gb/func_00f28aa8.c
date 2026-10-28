/* 62 words / score 51: packets and the text loop are right. The original computes ((sel-top)*26 + 1952) << 4 without folding the 1952 into the shift, and keeps the XYZ constant parts in separate ors; gcc here folds to *416+31232. Tried s16/u16 y, split statements, (y+20)<<4. */
extern char D_00F71728[];
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, char *, s32);
char *func_00f3c1d8(s32);

void func_00f28aa8(u64 **pp, s32 sel, s32 top) {
    u64 *p;
    s32 y, i, ty, k;
    y = (sel - top) * 26;
    y += 1952;
    y *= 16;
    p = func_00f3fa80(func_00f3f9d0(*pp));
    p[0] = 0x0000740000007000ULL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    p[0] = 70;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F800000802020FFULL;
    p[1] = 1;
    p += 2;
    p[0] = (u64)29632 | ((u64)y << 16) | ((u64)1 << 32);
    p[1] = 5;
    p += 2;
    p[0] = (u64)0x8680 | ((u64)(y + 320) << 16) | ((u64)1 << 32);
    p[1] = 5;
    p += 2;
    func_00f3fa98(p);
    p = func_001f0798(p, 1, 0x80808080, 64, 60, D_00F71728, 24);
    k = top + 64;
    ty = 98;
    for (i = 0; i < 10; i++) {
        p = func_001f0798(p, 1, 0x80808080, 64, ty, func_00f3c1d8(k++), 16);
        ty += 26;
    }
    func_00f3fe80(0x9C40, func_00f3f9e8(p));
    *pp = p;
}
