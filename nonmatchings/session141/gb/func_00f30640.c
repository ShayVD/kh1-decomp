/* Round 31 (wgb): 193 -> 172 words with func_00f27b38 declared and called in the order (s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, s32 a4, f32 f, s32 size): same EE EABI registers, but the target sets the arguments up in this order (cf. wm func_00f3a860). gb.x func_00f30640 near miss: 193 words differ, score 199 (ours 1460 bytes, original 1464). Mirror of func_00f2fe38 (k counts down from 48, func_00f303f0 / func_00f2f440 handlers, id roles swapped). Loops 2 and 5 use the same do { a += 90; ... } while (--i != 0) form as f2fe38 (was 225). The remaining issue is the same: the original reloads the 0.017453292f constant every iteration and divides a before the increment. See func_00f2fe38 for what was tried. */
typedef struct { u8 pad[0x82]; s16 id; s16 x84; } World;
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern f32 D_00F61564;
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
s32 func_001c01b0(s32, void *, s32);
void func_001c0078(s32);
void func_00f303f0();
void func_00f2eac8();
void func_00f2e218();
void func_00f2f440();
void func_00f2ec40();
s32 func_00f23d50(s32);
s32 func_00f23c70(s32);
s32 func_00f23bb0(s32);
void func_001bfac8(void);
void func_00f32728(s32, s32);
s32 func_00f27b38(s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, s32 a4, f32 f, s32 size);
void func_00f30640(void) {
    s32 ids[3][4];
    s32 h0;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 i;
    s32 k;
    s32 id;
    s32 n;
    s32 a;
    f32 r;
    h0 = func_001c00e8(-1, func_00f303f0, 0);
    h1 = func_001c00e8(-1, func_00f2eac8, 0);
    h2 = func_001c00e8(-1, func_00f2e218, 0);
    ids[0][1] = func_00f23c70(D_00F56DC0->id);
    ids[1][1] = D_00F56DC0->id;
    n = func_00f23d50(D_00F56DC0->id);
    ids[1][0] = func_00f23d50(n);
    ids[2][0] = 48;
    ids[0][0] = n;
    if (func_00f23bb0(n) != D_00F56DC0->x84)
        h3 = func_001c01b0(-1, func_00f2f440, 48);
    else
        h3 = func_001c01b0(-1, func_00f2ec40, 48);
    k = 48;
    a = 0;
    for (i = 0; i < 10; i++) {
        func_001bfac8();
        r = (f32)(a / 10) * 0.017453292f;
        id = func_00f27b38(11200, D_00F56DC8, 41, 347, 0.0f, 0.0f, ids[1][1], D_00F61564, 58);
        id = func_00f27b38(id, D_00F56DC8, 41, 347, -r, 0.0f, ids[0][1], D_00F61564, 58);
        func_00f27b38(id, D_00F56DC8, 41, 76, 0.0f, 0.0f, ids[0][0], D_00F61564, 58);
        func_00f32728(4, k / 2);
        k--;
        a += 90;
    }
    a = 0;
    i = 10;
    do {
        func_001bfac8();
        a += 90;
        r = (f32)(90 - (a - 90) / 10) * 0.017453292f;
        id = func_00f27b38(11200, D_00F56DC8, 41, 347, 0.0f, 0.0f, ids[0][1], D_00F61564, 58);
        id = func_00f27b38(id, D_00F56DC8, 41, 347, 0.0f, r, ids[1][1], D_00F61564, 58);
        func_00f27b38(id, D_00F56DC8, 41, 76, 0.0f, 0.0f, ids[0][0], D_00F61564, 58);
        func_00f32728(4, k / 2);
        k--;
    } while (--i != 0);
    for (i = 0; i < 8; i++) {
        func_001bfac8();
        id = func_00f27b38(11200, D_00F56DC8, 41, 76, 0.0f, 0.0f, ids[0][0], D_00F61564, 58);
        func_00f27b38(id, D_00F56DC8, 41, 347, 0.0f, 0.0f, ids[1][1], D_00F61564, 58);
        func_00f32728(4, k / 2);
        k--;
    }
    a = 0;
    for (i = 0; i < 10; i++) {
        func_001bfac8();
        r = (f32)(a / 10) * 0.017453292f;
        id = func_00f27b38(11200, D_00F56DC8, 41, 76, 0.0f, 0.0f, ids[1][0], D_00F61564, 58);
        id = func_00f27b38(id, D_00F56DC8, 41, 76, -r, 0.0f, ids[0][0], D_00F61564, 58);
        func_00f27b38(id, D_00F56DC8, 41, 347, 0.0f, 0.0f, ids[1][1], D_00F61564, 58);
        func_00f32728(4, k / 2);
        k--;
        a += 90;
    }
    a = 0;
    i = 10;
    do {
        func_001bfac8();
        a += 90;
        r = (f32)(90 - (a - 90) / 10) * 0.017453292f;
        id = func_00f27b38(11200, D_00F56DC8, 41, 76, 0.0f, 0.0f, ids[0][0], D_00F61564, 58);
        id = func_00f27b38(id, D_00F56DC8, 41, 76, 0.0f, r, ids[1][0], D_00F61564, 58);
        func_00f27b38(id, D_00F56DC8, 41, 347, 0.0f, 0.0f, ids[1][1], D_00F61564, 58);
        func_00f32728(4, k / 2);
        k--;
    } while (--i != 0);
    func_00f32728(4, 0);
    func_001c0078(h0);
    func_001c0078(h1);
    func_001c0078(h3);
    func_001c0078(h2);
}
