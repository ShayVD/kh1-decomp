/* Round 31 (wgb): 195 -> 172 words with func_00f4ec30 declared and called in the order (s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, s32 a4, f32 f, s32 size): same EE EABI registers, but the target sets the arguments up in this order (cf. wm func_00f3a860). wm f56f30 near miss (port of the gb twin f2fe38 near miss): 195 words differ, score 199 (1460 vs 1464 bytes). Same leftovers as gb: the original divides a before the a += 90 and reloads the deg-to-rad constant each iteration. See the gb file for what was tried. */
typedef struct { u8 pad[0x82]; s16 id; s16 x84; } World;
extern World *D_00F9B540;
extern u8 D_00F9B548[];
extern f32 D_00FA5CE4;
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
s32 func_001c01b0(s32, void *, s32);
void func_001c0078(s32);
void func_00f56ce0();
void func_00f55bc0();
void func_00f55310();
void func_00f55d78();
void func_00f55d38();
s32 func_00f4ae48(s32);
s32 func_00f4ad68(s32);
s32 func_00f4aca8(s32);
void func_001bfac8(void);
void func_00f59820(s32, s32);
s32 func_00f4ec30(s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, s32 a4, f32 f, s32 size);
void func_00f56f30(void) {
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
    h0 = func_001c00e8(-1, func_00f56ce0, 0);
    h1 = func_001c00e8(-1, func_00f55bc0, 0);
    h2 = func_001c00e8(-1, func_00f55310, 0);
    ids[0][0] = func_00f4ae48(D_00F9B540->id);
    ids[1][0] = D_00F9B540->id;
    n = func_00f4ad68(D_00F9B540->id);
    ids[1][1] = func_00f4ad68(n);
    ids[2][0] = 48;
    ids[0][1] = n;
    if (func_00f4aca8(n) != D_00F9B540->x84)
        h3 = func_001c01b0(-1, func_00f55d78, 48);
    else
        h3 = func_001c01b0(-1, func_00f55d38, 48);
    k = 2;
    a = 0;
    for (i = 0; i < 10; i++) {
        func_001bfac8();
        r = (f32)(a / 10) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, r, ids[0][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a += 90;
    }
    a = 0;
    i = 10;
    do {
        func_001bfac8();
        a += 90;
        r = (f32)(90 - (a - 90) / 10) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[0][0], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 76, -r, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
    } while (--i != 0);
    for (i = 0; i < 8; i++) {
        func_001bfac8();
        id = func_00f4ec30(11200, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
    }
    a = 0;
    for (i = 0; i < 10; i++) {
        func_001bfac8();
        r = (f32)(a / 10) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[1][1], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 347, 0.0f, r, ids[0][1], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
        a += 90;
    }
    a = 0;
    i = 10;
    do {
        func_001bfac8();
        a += 90;
        r = (f32)(90 - (a - 90) / 10) * 0.017453292f;
        id = func_00f4ec30(11200, D_00F9B548, 41, 347, 0.0f, 0.0f, ids[0][1], D_00FA5CE4, 58);
        id = func_00f4ec30(id, D_00F9B548, 41, 347, -r, 0.0f, ids[1][1], D_00FA5CE4, 58);
        func_00f4ec30(id, D_00F9B548, 41, 76, 0.0f, 0.0f, ids[1][0], D_00FA5CE4, 58);
        func_00f59820(4, k / 2);
        k++;
    } while (--i != 0);
    func_00f59820(4, 0);
    func_001c0078(h0);
    func_001c0078(h1);
    func_001c0078(h3);
    func_001c0078(h2);
}
