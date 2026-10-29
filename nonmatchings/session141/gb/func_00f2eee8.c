/* 110 words / score 168 (1368 = 1368). Logic complete; f2f688 is its mirror (same calls, rows swapped, func_00f2f440 instead of f2ec80). Keys: func_001c01b0 takes 3 args; one f32 reused for the angle and the scale (r = fi*k ... r = -r ... r = fi*0.5/180) and fi += 90 reuse cut a float reg; sc[2] = sc[0] = ... gives the store order. Left: FP/s-reg numbering only (orig fi=f21, r=f20, t=f22; loop 2 ints s1=90-i, s0=i+90 with D_00F56DC8 moved to s5). Reusing n/arg for those ints made it worse (206/220). Decl-order sweep: no change. Permuter running at hand-off. */
typedef struct { u8 pad[0x82]; s16 id; } World;
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern u8 D_00F614C0[];
extern u8 D_00F61510[];
extern f32 D_00F6156C;
void func_00f20248(s32);
void func_00f20290(s32);
void func_001c01b0(s32, void *, s32);
void func_00f2ec80(s32);
s32 func_00f23ad8(s32);
s32 func_00f23d50(s32);
s32 func_00f23c70(s32);
void func_001bfac8(void);
f32 func_001befc8(s32, void *);
s32 func_00f28090(s32 id, void *pp, s32 x, s32 y, s32 a4, s32 size, f32 ry0, f32 ry1, f32 f);
s32 func_00f285e0(s32 id, void *pp, s32 x, s32 y, s32 a4, f32 *scl, s32 flag, f32 ry, f32 f1, f32 s, f32 f3);

void func_00f2eee8(s32 arg) {
    s32 ids[3][4];
    f32 sc[3];
    s32 i, k, id, n;
    f32 fi, r, s, t;
    s32 j, m;
    ids[2][0] = 12;
    func_00f20248(11);
    func_001c01b0(-1, func_00f2ec80, 12);
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
        id = func_00f28090(11200, D_00F56DC8, 41, 76, ids[1][0], 58, 0.0f, 0.0f, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 76, ids[0][0], 58, 0.0f, r, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 347, ids[1][1], 58, 0.0f, 0.0f, D_00F6156C);
        func_00f28090(id, D_00F56DC8, 41, 347, ids[0][1], 58, 0.0f, r, D_00F6156C);
        k = i / 15 * 4;
        r = fi * 0.5f / 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f285e0(10720, D_00F56DC8, (180 - i) / 2 + 68, 192, ids[1][2], sc, 0, 0.0f, fi / 180.0f, r + 0.5f, D_00F6156C);
        func_00f285e0(id, D_00F56DC8, 68 - i / 2, 192, ids[0][2], sc, 1, 0.0f, t / 180.0f, 1.0f - r, D_00F6156C);
    }
    for (i = 0; i < 90; i += 15) {
        func_001bfac8();
        j = 90 - i;
        r = (f32)j * 0.017453292f;
        fi = i;
        m = i + 90;
        id = func_00f28090(11200, D_00F56DC8, 41, 76, ids[0][0], 58, 0.0f, 0.0f, D_00F6156C);
        r = -r;
        id = func_00f28090(id, D_00F56DC8, 41, 76, ids[1][0], 58, r, 0.0f, D_00F6156C);
        id = func_00f28090(id, D_00F56DC8, 41, 347, ids[0][1], 58, 0.0f, 0.0f, D_00F6156C);
        func_00f28090(id, D_00F56DC8, 41, 347, ids[1][1], 58, r, 0.0f, D_00F6156C);
        k = i / 15 * 4 + 24;
        r = fi * 0.5f / 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f285e0(10720, D_00F56DC8, 68 - m / 2, 192, ids[0][2], sc, 1, 0.0f, (90.0f - fi) / 180.0f, 0.75f - r, D_00F6156C);
        fi += 90.0f;
        func_00f285e0(id, D_00F56DC8, j / 2 + 68, 192, ids[1][2], sc, 0, 0.0f, fi / 180.0f, r + 0.75f, D_00F6156C);
    }
    func_00f20290(11);
}
