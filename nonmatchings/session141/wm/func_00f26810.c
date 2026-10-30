/* score 196 (1344 bytes, same size). Status page: header packet, item icon via func_00f23df0, name built in a local buffer as 0x77 + string (lb test / lbu copy), level icon centred with (0x94 - D_00F874F8[k].w) / 2, 8 stat rows (func_00f23c20 + func_001f0758 + func_00f24e38), then two totals. Rotated while (1) loop with py = y + yy at the bottom fixes the size. Left: register allocation (orig p = s2, x+229 = s1 reused for i and x+152, t/v in s3; ours swaps s1/s2 and keeps t in s0); cx reuse for x+152 was worse. Round 27 wwm2. */
typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } Tex;
extern Tex D_00F874F8[];
extern u64 **D_00F85160;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fe8(s32, s32);
s32 func_00f24f50(s32);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
u64 *func_00f23c20(s32, s32, s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f23df0(s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f24e38(s32, s32, s32, s32, u64 *);
u64 *func_00f24fe0(s32, s32, s32, s32, s32, u64 *);
s32 *func_001bb198(s32);
s32 *func_001bb1d8(s32);
s32 func_001bb2e0(s32);
s32 func_001baf08(s32 *);
s8 *func_00f2b6f0(s32);
s8 *func_00f2b8f0(s32);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, s8 *, s32);
u64 *func_001f0868(u64 *, s32, s32, s32, s32, s32, s8 *, s32);

void func_00f26810(s32 x, s32 y, s32 id, s32 flag)
{
    s8 buf[64];
    u64 *p;
    s32 *t;
    s8 *s;
    s8 *d;
    s32 cx, cy;
    s32 i;
    s32 yy;
    s32 py;
    s32 v;
    s32 k;
    s32 n;

    p = func_00f66b78(func_00f66ac8(*D_00F85160));
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = 0x50003;
    p[1] = 71;
    p += 2;
    p[0] = 0x131000070LL;
    p[1] = 78;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    p = func_00f23a58(x, y + 41, 6, 128, p);
    if (flag != 0) {
        p = func_00f23a58(x, y + 96, 17, 128, p);
    }
    cx = x + 229;
    cy = y + 253;
    p = func_00f23a58(cx, cy, 1, 128, p);
    if (flag == 0) {
        t = func_001bb198(id);
    } else {
        t = func_001bb1d8(id);
    }
    if (t[8] != 0) {
        p = func_00f23df0(x + 200, y + 72, 48, 48, func_00f24f50(t[8]), 128, p);
        s = func_00f2b6f0(t[8]);
        if (s != 0) {
            buf[0] = 0x77;
            d = buf + 1;
            while (*s != 0) {
                *d++ = *s++;
            }
            *d = 0;
            p = func_001f0868(p, 1, 1, -128, x + 210, y + 71, buf, 16);
        }
    }
    s = func_00f2b6f0(id);
    if (s != 0) {
        p = func_001f0758(p, 1, 0x8000D000, x + 26, y + 53, s, 16);
    }
    k = flag == 0 ? 13 : 12;
    p = func_00f23a58(x + (0x94 - D_00F874F8[k].w) / 2 + 35, y + 101, k, 128, p);
    p = func_00f24fe0(cx, cy, id, func_001bb2e0(id), 0, p);
    if (flag == 0) {
        t = func_001bb198(id);
    } else {
        t = func_001bb1d8(id);
    }
    yy = 126;
    i = 0;
    py = y + yy;
    while (1) {
        yy += 19;
        p = func_00f23c20(x + 24, py, i * 16, 0, 16, 16, 31, 128, p);
        n = i + 3;
        i++;
        p = func_001f0758(p, 1, -128, x + 40, py, func_00f2b8f0(n), 16);
        p = func_00f24e38(x + 168, py, *t++, 3, p);
        if (i >= 8) break;
        py = y + yy;
    }
    if (flag == 0) {
        v = func_001baf08(func_001bb198(id));
    } else {
        v = func_001baf08(func_001bb1d8(id));
    }
    yy += 4;
    if (flag == 0) {
        py = y + yy;
        p = func_00f23a58(x + 24, py, 10, 128, p);
    } else {
        py = y + yy;
        p = func_00f23a58(x + 24, py, 14, 128, p);
    }
    p = func_00f24e38(x + 152, py, v, 4, p);
    v = func_001baf08(func_001bb1d8(id));
    yy += 36;
    py = y + yy;
    p = func_00f23a58(x + 24, py, 14, 128, p);
    p = func_00f24e38(x + 152, py, v, 4, p);
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
