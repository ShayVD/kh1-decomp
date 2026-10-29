/* 62 words (452 vs 456). Packet and loop structure are right; left: target keeps ((sel-top)*26 + 1952) and the final <<4 separate (sll 1 / addiu / sll 4), ours folds to sll 5 + 31232, and the x constants 0x73C0/0x8680 are or-ed separately from a shared z = 1<<32 register. Tried z variable, *16, split statements, all modes. */
s32 func_00f66ac8(s32);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, void *, s32);
void *func_00f632d0(s32);
s32 func_00f66ae0(u64 *);
void func_00f66f78(s32, s32);
extern u8 D_00FB77D8[];

void func_00f4fba0(s32 *pk, s32 sel, s32 top) {
    u64 *p;
    s32 y;
    s32 i;
    s32 n;
    s32 ty;

    y = ((sel - top) * 26 + 1952) << 4;
    p = func_00f66b78(func_00f66ac8(*pk));
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    p[0] = 70;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F800000802020FFLL;
    p[1] = 1;
    p += 2;
    p[0] = (s64)((60 + 1792) << 4) | ((s64)y << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = (s64)((360 + 1792) << 4) | ((s64)(y + 320) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    p = func_001f0798(p, 1, 0x80808080, 64, 60, D_00FB77D8, 24);
    n = top + 64;
    ty = 98;
    for (i = 9; i >= 0; i--) {
        p = func_001f0798(p, 1, 0x80808080, 64, ty, func_00f632d0(n++), 16);
        ty += 26;
    }
    func_00f66f78(0x9C40, func_00f66ae0(p));
    *pk = (s32)p;
}
