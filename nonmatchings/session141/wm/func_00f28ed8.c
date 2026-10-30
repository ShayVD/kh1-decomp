/* Round 48 wwm2: the hill3o order from bab769da (wm func_00f28ed8 near miss, score 67 -> 65, hill3o statement order (wwm2 round 4) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 65 was not valid. Restored the last valid statement order: score 67. Earlier header below. */
/* Round 46 wwm2: score 75 -> 67, func_00f29500 declared s32 (v0 stays busy after the call). Earlier header below. */
/* score 75 (1340 vs 1344, trailing nop only). Title/logo panel: switches D_00FBAA60/64 to the 877F8/87A68 texture tables, fade-in alpha from t (t*128/30), func_002193f0 picks the button sprite (switch with default: case 0: gives the slti tree), colour ramp between t 20..60 written as u/v halves joined by one col = u | v, slide-in offsets t*-128/60+128 and t*-256/60+256, then three func_001f0758 text rows. Keys: col = 0 inside the t < 20 branch, separate k = hi | 0xFFFFFF for the text colour, alpha float first in the fade product. Left: float register numbering in the fade/ramp maths and the (0x700 - x) << 4 header word (orig computes it into the x register). Round 27 wwm2. */
extern u64 **D_00F85160;
extern void *D_00FBAA60;
extern void *D_00FBAA64;
extern s32 D_00FBAA6C;
extern s32 D_00F874F8[];
extern s32 D_00F877F8[];
extern s32 D_00F87950[];
extern s32 D_00F87A68[];
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fe8(s32, s32);
s32 func_00f29500(s32, s32, s32);
s32 func_002193f0(void);
s32 func_00f2b8f0(s32);
u64 *func_00f24738(s32, s32, s32, u32, u64 *);
u64 *func_00f24900(s32, s32, s32, s32, u64 *);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, s32, s32);

void func_00f28ed8(s32 x, s32 y, s32 alpha, f32 t)
{
    u64 *p;
    s32 a;
    s32 idx;
    s32 n;
    u32 col;
    s32 hi;
    s32 c;
    s32 off;
    s32 u, v, k;

    D_00FBAA60 = D_00F877F8;
    D_00FBAA64 = D_00F87A68;
    func_00f29500(0, 0x2600, D_00FBAA6C);
    p = func_00f66b78(func_00f66ac8(*D_00F85160));
    p[0] = 0x30003;
    p[1] = 71;
    p += 2;
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = (s64)(((0x700 - x) << 4) | ((s64)((0x740 - y) << 4) << 32));
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    if (t < 30.0f) {
        a = (s32)((f32)alpha * (t * 128.0f / 30.0f + 0.0f) * 0.0078125f);
    } else {
        a = alpha;
    }
    p = func_00f23a58(0x70, 0x60, 0, a, p);
    n = func_002193f0();
    switch (n) {
    case 1:
        idx = 2;
        break;
    case 2:
        idx = 5;
        break;
    default:
    case 0:
        idx = 1;
        break;
    }
    if (t < 20.0f) {
        col = 0;
        hi = alpha << 24;
    } else {
        if (t < 60.0f) {
            hi = alpha << 24;
            c = (s32)((t - 20.0f) * 255.0f / 40.0f + 0.0f);
            u = (c << 8) | (c << 16);
            v = c | ((s32)(((f32)alpha - 0.0f) * (t - 20.0f) / 40.0f + 0.0f) << 24);
        } else {
            hi = alpha << 24;
            c = (s32)((t - 60.0f) * -127.0f / 40.0f + 255.0f);
            u = c | hi;
            v = (c << 16) | (c << 8);
        }
        col = u | v;
    }
    p = func_00f24738(0xC0, 0x80, idx, col, p);
    p = func_00f24738(0x10, 0x30, 6, col, p);
    if (t < 60.0f) {
        off = (s32)(t * -128.0f / 60.0f + 128.0f);
    } else {
        off = 0;
    }
    p = func_00f23a58(off + 0x16C, 0x80, 4, alpha, p);
    p = func_00f23a58(0x10 - off, 0x80, 3, alpha, p);
    if (t < 60.0f) {
        off = (s32)(t * -256.0f / 60.0f + 256.0f);
    } else {
        off = 0;
    }
    p = func_00f23a58(-off, 0xF8, 7, alpha, p);
    p = func_00f24900(off + 0x100, 0xF8, 7, alpha, p);
    k = hi | 0xFFFFFF;
    p = func_001f0758(p, 1, k, 0xA - off, 0x102, func_00f2b8f0(0x18), 0x10);
    p = func_001f0758(p, 1, k, off + 0x10A, 0x102, func_00f2b8f0(func_002193f0() + 0x1A), 0x10);
    p = func_00f23a58(off + 0x1AA, 0x15E, 8, alpha, p);
    p = func_001f0758(p, 1, k, off + 0x1B4, 0x166, func_00f2b8f0(0x14), 0x10);
    p = func_00f66b78(p);
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    func_00f66fe8(3, func_00f66ae0(p));
    *D_00F85160 = p;
    D_00FBAA60 = D_00F874F8;
    D_00FBAA64 = D_00F87950;
}
