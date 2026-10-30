/* Round 34 wwm1: score 722 -> 393 (2872 -> 2924 vs 2944 bytes). The target recomputes x + 0x60 and y + (off + C) on both sides of each `if (gl != 0) func_00f24548(...)` with a `b` over the else copy (gcse PRE of expressions written in the call arguments): x + 0x60 inline in every call, `yy = off + C;` before the test and `y + yy` in both calls. Left (control flow): the func_00f24fe0 row loop tail (target beqz, beqz, b). Earlier header below. */
/* Round 48 wwm2: the hill3o order from 47650907 (wm func_00f26e80 near miss, score 722 -> 472, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 472 was not valid. Restored the last valid statement order: score 722. Earlier header below. */
/* score 722 (2872 vs 2944). Item carousel (x, y, list, flag, t): off = t*96/100, centre icon with glow (func_00f24548) and func_00f23df0, size/alpha/glow from double maths on |t| written as a = d; if (d < 0) a = 0.0 - d; (gives the __cmpdf2/__subdf3(0,d) calls without code duplication); with cnt >= 2 the neighbours at off+0x60/0x120, the fading extras at off/off+0x180 and the up/down arrows (func_00f23a58/func_00f24380) at x + 0x60 - w/2; then func_00f23a58(x+0x90, y+0x2A), 3 func_00f24fe0 rows with ys = D_00FB6778 (aggregate initializer in the original, struct copy here), footer and func_00f66fe8(1). Call sequence lines up. Left: the original spills x, list and flag to the stack and recomputes |t| differently in places; 72 bytes short. Round 28 wwm2. */
typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } Tex;
typedef struct { s32 v[3]; } Y3;
extern Tex D_00F874F8[];
extern Y3 D_00FB6778;
extern s32 D_00FBB550;
extern s32 D_00FBB340;
extern u64 **D_00F85160;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fe8(s32, s32);
s32 func_00f24f50(s32);
s32 func_00f26e48(s32 *);
s32 func_001bb2e0(s32);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
u64 *func_00f24380(s32, s32, s32, s32, u64 *);
u64 *func_00f23df0(s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f24548(s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f24fe0(s32, s32, s32, s32, s32, u64 *);

void func_00f26e80(s32 x, s32 y, s32 *list, s32 flag, f32 t)
{
    Y3 ys;
    u64 *p;
    s32 cnt;
    s32 off;
    s32 icon;
    s32 sz, al, gl;
    s32 k;
    s32 yy;
    s32 id;
    s32 n;
    s32 i;
    double d, a;

    p = func_00f66b78(func_00f66ac8(*D_00F85160));
    p[0] = 0x131000070LL;
    p[1] = 78;
    p += 2;
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = 0x50003;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    off = (s32)(t * 96.0f / 100.0f);
    cnt = func_00f26e48(list);
    icon = func_00f24f50(list[D_00FBB550 % cnt]);
    d = t;
    a = d;
    if (d < 0) a = 0.0 - d;
    sz = (s32)(((100.0 - a) * 0.5 + 50.0) / 100.0 * 128.0);
    a = d;
    if (d < 0) a = 0.0 - d;
    al = (s32)(((100.0 - a) * 0.75 + 25.0) / 100.0 * 128.0);
    a = d;
    if (d < 0) a = 0.0 - d;
    gl = (s32)((100.0 - a) / 100.0 * 128.0);
    yy = off + 0xC0;
    if (gl != 0) {
        p = func_00f24548((x + 0x60), y + yy, sz, sz, 32, (gl << 24) | 0x800000, p);
    }
    p = func_00f23df0((x + 0x60), y + yy, sz, sz, icon, al, p);
    if (cnt >= 2) {
        sz = 64;
        if (off > 0) {
            a = d;
            if (d < 0) a = 0.0 - d;
            sz = (s32)((a * 0.5 + 50.0) / 100.0 * 128.0);
            a = d;
            if (d < 0) a = 0.0 - d;
            al = (s32)((a * 0.5 + 50.0) / 100.0 * 128.0);
            a = d;
            if (d < 0) a = 0.0 - d;
            gl = (s32)(a / 100.0 * 128.0);
        } else {
            al = 64;
            gl = 0;
        }
        k = cnt * 2;
        icon = func_00f24f50(list[(D_00FBB550 + k - 1) % cnt]);
        yy = off + 0x60;
        if (gl != 0) {
            p = func_00f24548((x + 0x60), y + yy, sz, sz, 32, (gl << 24) | 0x800000, p);
        }
        p = func_00f23df0((x + 0x60), y + yy, sz, sz, icon, al, p);
        if (off > 0) {
            d = t;
            if (d < 0) d = 0.0 - d;
            al = (s32)(d * 0.5 / 100.0 * 128.0);
            p = func_00f23df0((x + 0x60), y + off, 64, 64, func_00f24f50(list[(D_00FBB550 + k - 2) % cnt]), al, p);
        }
        p = func_00f23a58(x + (0x60 - D_00F874F8[15].w / 2), y + 0x70, 15, 0xE0 - D_00FBB340, p);
        if (off < 0) {
            d = t;
            a = d;
            if (d < 0) a = 0.0 - d;
            sz = (s32)((a * 0.5 + 50.0) / 100.0 * 128.0);
            a = d;
            if (d < 0) a = 0.0 - d;
            al = (s32)((a * 0.5 + 50.0) / 100.0 * 128.0);
            if (d < 0) d = 0.0 - d;
            gl = (s32)(d / 100.0 * 128.0);
        } else {
            sz = 64;
            al = 64;
            gl = 0;
        }
        icon = func_00f24f50(list[(D_00FBB550 + k + 1) % cnt]);
        yy = off + 0x120;
        if (gl != 0) {
            p = func_00f24548((x + 0x60), y + yy, sz, sz, 32, (gl << 24) | 0x800000, p);
        }
        p = func_00f23df0((x + 0x60), y + yy, sz, sz, icon, al, p);
        if (off < 0) {
            d = t;
            if (d < 0) d = 0.0 - d;
            al = (s32)(d * 0.5 / 100.0 * 128.0);
            p = func_00f23df0((x + 0x60), y + (off + 0x180), 64, 64, func_00f24f50(list[(D_00FBB550 + k + 2) % cnt]), al, p);
        }
        p = func_00f24380(x + (0x60 - D_00F874F8[15].w / 2), y + 0xF8, 15, 0xE0 - D_00FBB340, p);
    }
    p = func_00f23a58(x + 0x90, y + 0x2A, 0, 0x80, p);
    ys = D_00FB6778;
    id = list[D_00FBB550 % cnt];
    n = func_001bb2e0(id);
    for (i = 0; i < n && i < 3; i++) {
        p = func_00f24fe0(x + 0xD8, y + ys.v[i], id, i + 1, (flag != 0 && i + 1 < n) ? 1 : 0, p);
    }
    for (; i < 3; i++) {
        p = func_00f24fe0(x + 0xD8, y + ys.v[i], id, 0, 0, p);
    }
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
    func_00f66fe8(1, func_00f66ae0(p));
    *D_00F85160 = p;
}
