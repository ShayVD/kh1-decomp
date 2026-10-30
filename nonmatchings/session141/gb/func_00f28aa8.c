/* Round 35 (wgb): gb.x func_00f28aa8 near miss: 62 -> 26 words, score 51 -> 25 (452 vs 456 bytes). y = (sel - top) * 26 + 1952 before the first call and y <<= 4 after func_00f3f9d0 keeps the add and the shift apart (combine folded them to *416 + 31232 before); each XYZ word is built in a u64 v with separate |= statements, so the 1 << 32 constant is not folded into the low part. Left: the target keeps y + 320 in y's own register (s0) and builds both XYZ words around one shared 1 << 32 in a2; ours builds both in a1. Tried: v = y; v <<= 16 forms, a second u64 for the second word, y += 320 in place, p[1] before p[0], hill2 over statement order and over choice slots for the three expressions (126 combinations). Earlier header below. */
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
    u64 v;
    y = (sel - top) * 26 + 1952;
    p = func_00f3f9d0(*pp);
    y <<= 4;
    p = func_00f3fa80(p);
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
    v = (u64)y << 16;
    v |= 29632;
    v |= (u64)1 << 32;
    p[0] = v;
    p[1] = 5;
    p += 2;
    v = (u64)(y + 320) << 16;
    v |= 0x8680;
    v |= (u64)1 << 32;
    p[0] = v;
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
