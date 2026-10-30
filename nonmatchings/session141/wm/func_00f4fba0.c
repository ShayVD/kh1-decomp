/* Round 35 (wgb): wm.x func_00f4fba0 near miss: 62 -> 26 words, score 51 -> 25 (452 vs 456 bytes). port.py of gb func_00f28aa8's round 35 draft (y + 1952 and << 4 split around the first call, XYZ words built with separate |=); see that file for what is left and what was tried. Earlier header below. */
/* 62 words (452 vs 456). Packet and loop structure are right; left: target keeps ((sel-top)*26 + 1952) and the final <<4 separate (sll 1 / addiu / sll 4), ours folds to sll 5 + 31232, and the x constants 0x73C0/0x8680 are or-ed separately from a shared z = 1<<32 register. Tried z variable, *16, split statements, all modes. */
extern char D_00FB77D8[];
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, char *, s32);
char *func_00f632d0(s32);

void func_00f4fba0(u64 **pp, s32 sel, s32 top) {
    u64 *p;
    s32 y, i, ty, k;
    u64 v;
    y = (sel - top) * 26 + 1952;
    p = func_00f66ac8(*pp);
    y <<= 4;
    p = func_00f66b78(p);
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
    func_00f66b90(p);
    p = func_001f0798(p, 1, 0x80808080, 64, 60, D_00FB77D8, 24);
    k = top + 64;
    ty = 98;
    for (i = 0; i < 10; i++) {
        p = func_001f0798(p, 1, 0x80808080, 64, ty, func_00f632d0(k++), 16);
        ty += 26;
    }
    func_00f66f78(0x9C40, func_00f66ae0(p));
    *pp = p;
}
