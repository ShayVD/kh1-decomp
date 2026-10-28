/* register allocation: the original computes x*16, y*16, (x+w)*16, (y+h)*16 twice each (once for the +0x7000/0x7400 XYZ values); ours CSEs them. */
void func_00f26458(void *, void *, s32);
extern u8 D_00F60EF0[];

void func_00f268c8(u64 *p, s32 a, s32 b, s32 c, s32 x, s32 y, s32 w, s32 h) {
    h += y;
    w += x;
    func_00f26458(p, D_00F60EF0, 0x130);
    p[12] = ((u64)a << 32) | 100;
    p[14] = ((u64)b << 1) | ((u64)c << 4) | 0x30001;
    p[22] = (x * 16) | ((u64)(y * 16) << 16);
    p[26] = (w * 16) | ((u64)(h * 16) << 16);
    p[28] = ((w + 0x700) * 16) | ((u64)((h + 0x740) * 16) << 16) | 0x100000000;
    p[24] = ((x + 0x700) * 16) | ((u64)((y + 0x740) * 16) << 16) | 0x100000000;
}
