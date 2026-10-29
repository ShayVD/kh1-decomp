/* 16 words (660 bytes + pad). Four fade loops into func_00f41830. Divisors must be int locals ((f32)n) so x/4 is not turned into x*0.25; t = -(f32)i / (f32)n fixes loops 2 and 4. Left: loop 1 schedules t/n before the -192*t multiply (target does the multiply first); tried xx/c statement orders, t pre-divided, several x expression forms. */
void func_001c0688(s32);
void func_0011d768(s32);
void func_00f41830(s32, s32, s32, s32, s32, s32);
void func_001bfac8(void);

void func_00f41990(s32 x, s32 y, s32 a2, s32 a3, s32 a4, s32 a5) {
    s32 i;
    s32 c;
    s32 xx;
    s32 n;
    f32 t;

    func_001c0688(a3);
    func_0011d768(a5);
    n = 4;
    for (i = 0; i < 4; i++) {
        t = i;
        xx = (s32)(-192.0f * t / (f32)n + 192.0f) + x;
        c = (s32)((t / (f32)n + 0.0f) * 127.0f) + 128;
        func_00f41830(xx, y, a2, c | ((c << 8) | (c << 16)) | 0x80000000, 128, a4);
        func_001bfac8();
    }
    n = 10;
    for (i = 0; i < 10; i++) {
        t = -(f32)i / (f32)n;
        c = (s32)((t + 1.0f) * 127.0f) + 128;
        func_00f41830(x, y, a2, c | ((c << 16) | (c << 8)) | 0x80000000, 128, a4);
        func_001bfac8();
    }
    for (i = 29; i >= 0; i--) {
        func_00f41830(x, y, a2, 0x80808080, 128, a4);
        func_001bfac8();
    }
    n = 8;
    for (i = 0; i < 8; i++) {
        t = -(f32)i / (f32)n;
        c = (s32)((t + 1.0f) * 128.0f);
        func_00f41830(x, y, a2, (c << 24) | 0x808080, c, a4);
        func_001bfac8();
    }
}
