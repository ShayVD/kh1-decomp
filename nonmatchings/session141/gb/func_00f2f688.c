/* gb.x func_00f2f688 near miss: 98 words differ, score 153 (ours 1372 bytes, original 1376). Mirror of the f2eee8 near miss: in each loop the f28090 rows come in the order 347 then 76, and the r = -r negate sits in the f12 slot. Logic is complete. What is left is FP allocation (original fi=f21, r=f20, t=f22; ours f22/f21/f20) and the scheduling that follows from it. Already tried: decl-order swaps, splitting r = fi*0.5; r /= 180 (saves 6 words), an explicit mid-loop i += 15 in loop 2 (no change), and asm-pinned registers (worse, 165). */
typedef struct { u8 pad[0x82]; s16 id; } World;
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern u8 D_00F614C0[];
extern u8 D_00F61510[];
extern f32 D_00F6156C;
void func_00f20248(s32);
void func_00f20290(s32);
void func_001c01b0(s32, void *, s32);
void func_00f2f440(s32);
s32 func_00f23ad8(s32);
s32 func_00f23d50(s32);
s32 func_00f23c70(s32);
void func_001bfac8(void);
f32 func_001befc8(s32, void *);
s32 func_00f28090(s32 id, void *pp, s32 x, s32 y, s32 a4, s32 size, f32 ry0, f32 ry1, f32 f);
s32 func_00f285e0(s32 id, void *pp, s32 x, s32 y, s32 a4, f32 *scl, s32 flag, f32 ry, f32 f1, f32 s, f32 f3);

void func_00f2f688(s32 arg) {
    s32 ids[3][4];
    f32 sc[3];
    s32 i, k, id, n;
    f32 fi, r, s, t;
    s32 j, m;
    ids[2][0] = 12;
    func_00f20248(11);
    func_001c01b0(-1, func_00f2f440, 12);
    n = func_00f23ad8(arg);
    ids[0][0] = func_00f23d50(D_00F56DC0->id);
    ids[1][0] = func_00f23d50(n);
    ids[0][1] = func_00f23c70(D_00F56DC0->id);
    ids[1][1] = func_00f23c70(n);
    ids[0][2] = D_00F56DC0->id;
    ids[1][2] = n;
    for (i = 0; i < 90; i += 15) {
        func_001bfac8();
        fi = i;
        r = fi * 0.017453292f;
        t = 180.0f - fi;
        id = func_00f28090(11200, D_00F56DC8, 41, 347, ids[1][1], 58, 0.0f, 0.0f, D_00F6156C);
        r = -r;
        id = func_00f28090(id, D_00F56DC8, 41, 347, ids[0][1], 58, r, 0.0f, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 76, ids[1][0], 58, 0.0f, 0.0f, D_00F6156C);
        func_00f28090(id, D_00F56DC8, 41, 76, ids[0][0], 58, r, 0.0f, D_00F6156C);
        k = i / 15 * 4;
        r = fi * 0.5f;
        r /= 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f285e0(10720, D_00F56DC8, 68 - (180 - i) / 2, 192, ids[1][2], sc, 0, 0.0f, fi / 180.0f, r + 0.5f, D_00F6156C);
        func_00f285e0(id, D_00F56DC8, i / 2 + 68, 192, ids[0][2], sc, 1, 0.0f, t / 180.0f, 1.0f - r, D_00F6156C);
    }
    for (i = 0; i < 90; i += 15) {
        func_001bfac8();
        j = 90 - i;
        r = (f32)j * 0.017453292f;
        fi = i;
        id = func_00f28090(11200, D_00F56DC8, 41, 347, ids[0][1], 58, 0.0f, 0.0f, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 347, ids[1][1], 58, 0.0f, r, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 76, ids[0][0], 58, 0.0f, 0.0f, D_00F6156C);
        func_00f28090(id, D_00F56DC8, 41, 76, ids[1][0], 58, 0.0f, r, D_00F6156C);
        k = i / 15 * 4 + 24;
        m = i + 90;
        r = fi * 0.5f;
        r /= 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f285e0(10720, D_00F56DC8, m / 2 + 68, 192, ids[0][2], sc, 1, 0.0f, (90.0f - fi) / 180.0f, 0.75f - r, D_00F6156C);
        fi += 90.0f;
        func_00f285e0(id, D_00F56DC8, 68 - j / 2, 192, ids[1][2], sc, 0, 0.0f, fi / 180.0f, r + 0.75f, D_00F6156C);
    }
    func_00f20290(11);
}
