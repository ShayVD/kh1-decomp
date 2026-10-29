/* Round 31 (wgb): 104 -> 89 words with func_00f4f6d8 declared and called in the order (s32 id, void *pp, f32 ry, f32 f1, f32 s, s32 x, s32 y, s32 a4, f32 f3, f32 *scl, s32 flag): same EE EABI registers, but the target sets the arguments up in this order (cf. wm func_00f3a860). score 165 (1372 vs 1376). Port of gb func_00f2f688's draft (gb score 153) via portmap3; mirror of f55fe0. Left: FP/s-reg numbering and one missing instruction, as in gb. Round 27 wwm2. */
typedef struct { u8 pad[0x82]; s16 id; } World;
extern World *D_00F9B540;
extern u8 D_00F9B548[];
extern u8 D_00F614C0[];
extern u8 D_00F61510[];
extern f32 D_00FA5CEC;
void func_00f47340(s32);
void func_00f47388(s32);
void func_001c01b0(s32, void *, s32);
void func_00f56538(s32);
s32 func_00f4abd0(s32);
s32 func_00f4ae48(s32);
s32 func_00f4ad68(s32);
void func_001bfac8(void);
f32 func_001befc8(s32, void *);
s32 func_00f4f188(s32 id, void *pp, s32 x, s32 y, s32 a4, s32 size, f32 ry0, f32 ry1, f32 f);
s32 func_00f4f6d8(s32 id, void *pp, f32 ry, f32 f1, f32 s, s32 x, s32 y, s32 a4, f32 f3, f32 *scl, s32 flag);
void func_00f56780(s32 arg) {
    s32 ids[3][4];
    f32 sc[3];
    s32 i, k, id, n;
    f32 fi, r, s, t;
    s32 j, m;
    ids[2][0] = 12;
    func_00f47340(11);
    func_001c01b0(-1, func_00f56538, 12);
    n = func_00f4abd0(arg);
    ids[0][0] = func_00f4ae48(D_00F9B540->id);
    ids[1][0] = func_00f4ae48(n);
    ids[0][1] = func_00f4ad68(D_00F9B540->id);
    ids[1][1] = func_00f4ad68(n);
    ids[0][2] = D_00F9B540->id;
    ids[1][2] = n;
    for (i = 0; i < 90; i += 15) {
        func_001bfac8();
        fi = i;
        r = fi * 0.017453292f;
        t = 180.0f - fi;
        id = func_00f4f188(11200, D_00F9B548, 41, 347, ids[1][1], 58, 0.0f, 0.0f, D_00FA5CEC);
        r = -r;
        id = func_00f4f188(id, D_00F9B548, 41, 347, ids[0][1], 58, r, 0.0f, D_00FA5CEC);
        id = func_00f4f188(id, D_00F9B548, 41, 76, ids[1][0], 58, 0.0f, 0.0f, D_00FA5CEC);
        func_00f4f188(id, D_00F9B548, 41, 76, ids[0][0], 58, r, 0.0f, D_00FA5CEC);
        k = i / 15 * 4;
        r = fi * 0.5f;
        r /= 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f4f6d8(10720, D_00F9B548, 0.0f, fi / 180.0f, r + 0.5f, 68 - (180 - i) / 2, 192, ids[1][2], D_00FA5CEC, sc, 0);
        func_00f4f6d8(id, D_00F9B548, 0.0f, t / 180.0f, 1.0f - r, i / 2 + 68, 192, ids[0][2], D_00FA5CEC, sc, 1);
    }
    for (i = 0; i < 90; i += 15) {
        func_001bfac8();
        j = 90 - i;
        r = (f32)j * 0.017453292f;
        fi = i;
        id = func_00f4f188(11200, D_00F9B548, 41, 347, ids[0][1], 58, 0.0f, 0.0f, D_00FA5CEC);
        id = func_00f4f188(id, D_00F9B548, 41, 347, ids[1][1], 58, 0.0f, r, D_00FA5CEC);
        id = func_00f4f188(id, D_00F9B548, 41, 76, ids[0][0], 58, 0.0f, 0.0f, D_00FA5CEC);
        func_00f4f188(id, D_00F9B548, 41, 76, ids[1][0], 58, 0.0f, r, D_00FA5CEC);
        k = i / 15 * 4 + 24;
        m = i + 90;
        r = fi * 0.5f;
        r /= 180.0f;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        id = func_00f4f6d8(10720, D_00F9B548, 0.0f, (90.0f - fi) / 180.0f, 0.75f - r, m / 2 + 68, 192, ids[0][2], D_00FA5CEC, sc, 1);
        fi += 90.0f;
        func_00f4f6d8(id, D_00F9B548, 0.0f, fi / 180.0f, r + 0.75f, 68 - j / 2, 192, ids[1][2], D_00FA5CEC, sc, 0);
    }
    func_00f47388(11);
}
