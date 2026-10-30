/* Round 46 wwm2: score 16 -> 14, hill3o statement order. Earlier header below. */
/* 15 words left (576 vs 576): scheduling only - f42860 arg move order (move a3,s2 first) and loop preheader init order. Tried if/ternary shapes, color inline (gives the move s2,s0 copy), init/body line perms, permuter (-j1, 8 min). */
typedef struct { u64 d; u64 r; } GP42ce0;
s32 func_001baf08(s32 *);
GP42ce0 *func_00f42860(s32, s32, s32, s32, GP42ce0 *);
GP42ce0 *func_00f42a38(s32, s32, s32, s32, s32, s32, s32, s32, GP42ce0 *);
GP42ce0 *func_00f42c08(s32, s32, s32, s32, s32, GP42ce0 *);
s32 func_00f66ac8(GP42ce0 *);
s32 func_00f66ae0(GP42ce0 *);
GP42ce0 *func_00f66b78(s32);
void func_00f66b90(GP42ce0 *);
void func_00f66fb0(s32, s32);
GP42ce0 *func_00f674a8(s32, s32, s32, s32);
extern s32 D_00F85034;
extern s32 *D_00F85160;
extern s32 D_00F8702C;
extern s32 D_00F87310[8];
extern f32 D_00F9B1DC;

void func_00f42ce0(s32 arg0) {
    s32 cnt;
    GP42ce0 *p;
    s32 a;

    s32 color;
    s32 i;
    s32 alpha;
    s32 x, y, v;
    s32 n;
    s32 *q;
    s32 c;
    alpha = D_00F9B1DC * 128.0f;
    if (alpha != 0) {
        p = func_00f674a8(32, 0x3600, D_00F8702C, *D_00F85160);
        if (arg0 != 0) {
            p = func_00f66b78(func_00f66ac8(p));
            p->r = 0x14;
            p->d = 0;
            p++;
            p->d = 0x30000;
            p->r = 0x47;
            p++;
            p->d = 0x740000007000;
            p->r = 0x18;
            p++;
            p->d = 0x44;
            p->r = 0x42;
            p++;
            func_00f66b90(p);
            cnt = func_001baf08(D_00F87310);
            p = func_00f42860(374, 16, 2, alpha, p);
            a = alpha << 24;
            p = func_00f42c08(D_00F85034 + 374, 16, a | 0x808080, cnt, 4, p);
            if (arg0 == 1) {
                x = 0;
                q = D_00F87310;
                y = 36;
                for (i = 0; i < 8; i++) {
                    p = func_00f42a38(434, y, x, 0, 16, 16, 4, (a | 0x808080), p);
                    n = *q++;
                    c = a | 0x323280;
                    v = n;
                    if (n >= 1000) {
                        v = 999;
                    } else {
                        c = (a | 0x808080);
                    }
                    p = func_00f42c08(450, y, c, v, 3, p);
                    x += 16;
                    y += 16;
                }
            }
            func_00f66fb0(33, func_00f66ae0(p));
        }
        *D_00F85160 = (s32)p;
    }
}
