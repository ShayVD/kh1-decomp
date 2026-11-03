/* Round 33 (wgb): gb.x func_00f2f688 near miss: 34 -> 25 words, score 31 (ours 1372 bytes, original 1376; the last word is the alignment nop). FP allocation is now the original's (r=f20, fi=f21, t=f22 in loop 1): -fdump-rtl (ee-gcc -dl -dg) showed local-alloc only takes pseudos that live in one block and die once, so the original's fi, r and t must all be global. Changes: loop 2 reuses fi and r (no fi2/r2/q2); loop 2 sets t = 0.0f at its top and passes t for every 0.0f; loop 1 does fi = t; between the two func_00f285e0-type calls and passes fi / 180.0f to the second (replaces round 32's r2 = t copy); n90 = 90.0f from round 32 is kept. Left: scheduling only. Around the first func_00f285e0-type call of loop 1 the original issues div.s $f13 (fi / 180) right after the two nops, ours issues li a2,180 / lwc1 / sub.s first. In every func_00f285e0-type call the original sets li a3,192 before mov.s $f12. Tried without gain: every int/float interleaving of the func_00f285e0 parameters, unused labels as block boundaries, zero held in s for loop 1, the loop-2 m statement at every position, and a 10-minute permuter run (26 words). The inline-helper idea for the calls grew the frame (272 bytes). Mirror: func_00f2eee8; wm twin func_00f56780. */
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
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f28090(s32 id, void *pp, s32 x, s32 y, f32 ry0, f32 ry1, f32 f, s32 a4, s32 size);
#else
s32 func_00f28090(s32, void *, s32, s32, s32, s32, f32, f32, f32);
static __inline__ s32 ee_00f28090(s32 x0, void * x1, s32 x2, s32 x3, f32 x4, f32 x5, f32 x6, s32 x7, s32 x8) { return func_00f28090(x0, x1, x2, x3, x7, x8, x4, x5, x6); }
#undef func_00f28090
#define func_00f28090 ee_00f28090
#endif
#ifdef KH1_PS2
s32 func_00f285e0(s32 id, void *pp, f32 ry, f32 f1, f32 s, s32 x, s32 y, s32 a4, f32 f3, f32 *scl, s32 flag);
#else /* the definition's order (portability rule 11: the EE passes the floats in $f12-$f15 apart) */
s32 func_00f285e0(s32 id, void *pp, s32 x, s32 y, s32 a4, f32 *scl, s32 flag, f32 ry, f32 f1, f32 s, f32 f3);
static __inline__ s32 ee_00f285e0(s32 id, void *pp, f32 ry, f32 f1, f32 s, s32 x, s32 y, s32 a4, f32 f3, f32 *scl, s32 flag) {
    return func_00f285e0(id, pp, x, y, a4, scl, flag, ry, f1, s, f3);
}
#undef func_00f285e0
#define func_00f285e0 ee_00f285e0
#endif
void func_00f2f688(s32 arg) {
    s32 ids[3][4];
    f32 sc[3];
    s32 i, k, id, n;
    f32 fi, r, s, t;
    f32 n90;
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
        id = func_00f28090(11200, D_00F56DC8, 41, 347, 0.0f, 0.0f, D_00F6156C, ids[1][1], 58);
        r = -r;
        id = func_00f28090(id, D_00F56DC8, 41, 347, r, 0.0f, D_00F6156C, ids[0][1], 58);
        id = func_00f28090(id, D_00F56DC8, 41, 76, 0.0f, 0.0f, D_00F6156C, ids[1][0], 58);
        func_00f28090(id, D_00F56DC8, 41, 76, r, 0.0f, D_00F6156C, ids[0][0], 58);
        k = i / 15 * 4;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        r = fi * 0.5f;
        r /= 180.0f;
        id = func_00f285e0(10720, D_00F56DC8, 0.0f, fi / 180.0f, r + 0.5f, 68 - (180 - i) / 2, 192, ids[1][2], D_00F6156C, sc, 0);
        fi = t;
        func_00f285e0(id, D_00F56DC8, 0.0f, fi / 180.0f, 1.0f - r, i / 2 + 68, 192, ids[0][2], D_00F6156C, sc, 1);
    }
    for (i = 0; i < 90; i += 15) {
        t = 0.0f;
        func_001bfac8();
        j = 90 - i;
        r = (f32)j * 0.017453292f;
        fi = i;
        id = func_00f28090(11200, D_00F56DC8, 41, 347, t, t, D_00F6156C, ids[0][1], 58);
        id = func_00f28090(id, D_00F56DC8, 41, 347, t, r, D_00F6156C, ids[1][1], 58);
        id = func_00f28090(id, D_00F56DC8, 41, 76, t, t, D_00F6156C, ids[0][0], 58);
        func_00f28090(id, D_00F56DC8, 41, 76, t, r, D_00F6156C, ids[1][0], 58);
        k = i / 15 * 4 + 24;
        m = i + 90;
        sc[1] = func_001befc8(k, D_00F614C0);
        sc[0] = sc[2] = func_001befc8(k, D_00F61510);
        sc[2] = sc[0] = (sc[0] - 1.0f) * 0.5f + 1.0f;
        sc[1] = (sc[1] - 1.0f) * 0.5f + 1.0f;
        n90 = 90.0f;
        r = fi * 0.5f;
        r /= 180.0f;
        id = func_00f285e0(10720, D_00F56DC8, t, (n90 - fi) / 180.0f, 0.75f - r, m / 2 + 68, 192, ids[0][2], D_00F6156C, sc, 1);
        fi = fi + n90;
        func_00f285e0(id, D_00F56DC8, t, fi / 180.0f, r + 0.75f, 68 - j / 2, 192, ids[1][2], D_00F6156C, sc, 0);
    }
    func_00f20290(11);
}
