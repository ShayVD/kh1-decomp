/* 6 words left; tried 7 variants (a-g) */
typedef struct { OvlMtx m; u8 pad[0xE4 - 0x40]; u16 xe4; u8 pad2[0x108 - 0xE6]; s32 x108; } E3a0f0;
extern OvlMtx D_00F85200;
extern OvlMtx D_00F85180;
s32 func_00f39ef0(s32);
void func_001ed410(s32, s32, s32, s32);

void func_00f3a0f0(E3a0f0 *arg0) {
    OvlMtx m;
    s32 id;
    s32 h;
    s32 v;
    if (arg0->x108 < 0) {
        return;
    }
    h = arg0->xe4 + 0x2000;
    id = func_00f39ef0(arg0->x108);
    sceVu0MulMatrix(m, D_00F85200, arg0->m);
    sceVu0MulMatrix(m, D_00F85180, m);
    v = -(((m[3][1] / m[3][3]) - 2048.0f) * 256.0f / 192.0f);
    if (v > 256) {
        v = 256;
    }
    if (v < -256) {
        v = -256;
    }
    func_001ed410(-1, id, h, v);
}
