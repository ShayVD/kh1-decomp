/* Round 34 wwm1 (2): score 348 -> 266, an unused `f32 xx[4];` declared after `OvlMtx m;` gives the target frame (288) and every stack offset of the target; it stands in for a 16-byte local of the original that is not identified. */
/* Round 34 wwm1: score 368 -> 348 (3832 -> 3824 vs 3816 bytes). The target has one jal func_00f31118 for both paths after func_00f3a860, with the f3d4d8 arm laid out first and `b` reloaded from the stack at the shared call: written as one call reached by falling out of `if (D_00F8C130 == 0) { ...f3d4d8...; b = 0; if (D_00F8C130 == 0) goto skip; }` (two calls let cse propagate b = 0 into a1). Left: frame 16 bytes smaller than the target (a/b at sp+176/180, target 192/196). Earlier header below. */
/* Round 64 wwm2: score 368 -> 366 with CONTEXT_ONLY definitions of func_00f2f400 (tools/ovl/nothrow.py: the call becomes nothrow, so reorg picks the original's plain/-likely branch next to it). Earlier header below. */
/* Round 47 wwm2: score 384 -> 368, hill3o statement order. Earlier header below. */
/* score 384 (3848 vs 3816). World-map player/camera update: early out on D_00F850F4, D_003F76BC init, then when D_00F8C220 == 0 && D_00F8C23C == 0 && D_00F9B1C0 >= 30: angle approach of D_00FBDA90 to D_00F8C210, D_00FBDA80 position update with clamps, pad actions (fa68/fcf8/fc50), D_00FBB808[3] item timers (func_00f2eb78/func_00f2d308), D_00FBB818/D_00FBB820 (func_00f2f400/func_00f2d2b0), D_00FBB824 shot + func_00f30568, D_00FBEBB8 offset from D_00F8C1E8, zoom D_00F8C144, func_00f324c0(held & 0x800); camera branches on D_00FBB5C4 with D_00FBB5C8 6-frame interpolation, Trans/Mul matrices, depth k clamped to +-256 (func_00f2d360/func_00f2d238/func_001ed410), D_00FBB828 and func_00f3a860/func_00f3d4d8/func_00f31118, then func_00f34998 and the tail calls. Left: the original frame is 16 bytes bigger (288 vs 272: one more 16-byte local vector), ours is 32 bytes long overall; not diffed further (time box). Round 28 wwm2. */
typedef struct { u8 pad[4]; u32 held; u32 press; u8 pad2[0x30]; f32 f3C; f32 f40; f32 f44; } Pad;
typedef struct { u8 pad[0x2C]; s8 b2C, b2D, b2E, b2F; } Cfg2;
typedef struct { u8 pad[0x3A]; s8 b3A, b3B, b3C, b3D, b3E, b3F; } Cfg;
extern s32 D_00F850F4;
extern s32 D_003F76BC;
extern s32 D_00F87350;
extern s32 D_00F9B2F0;
extern s32 D_00F8C23C;
extern s32 D_00F8C220;
extern s32 D_00F9B1C0;
extern f32 D_00F8C210[3];
extern f32 D_00FBDA90[3];
extern f32 D_00FBDA80[4];
extern f32 D_00FBDAA0[4];
extern f32 D_00FBDAB0[];
extern f32 D_002BBDEC;
extern f32 D_00F8C134;
extern s32 D_00F8C1FC;
extern f32 D_00FBBA64;
extern s32 D_00F8C284;
extern s32 D_00FBB5C0;
extern s32 D_00F8C1EC;
extern s32 D_00F8C1F0;
extern s32 D_00F8C1E8;
extern u32 D_00F8C154, D_00F8C158, D_00F8C15C, D_00F8C160, D_00F8C164, D_00F8C168;
extern s32 D_00FBB5B4;
extern s32 D_00FBB5B8;
extern s32 D_00FBB808[3];
extern s32 D_00FBB818[2];
extern s32 D_00FBB820;
extern s32 D_00FBB824;
extern s32 D_00FBB828;
extern Cfg D_00FBDAF8;
extern Cfg2 D_00F8DAF8;
extern s32 D_00FBBA58;
extern s32 D_00F8C12C;
extern s32 D_00F8C14C;
extern f32 D_00FBEBB8;
extern f32 D_00F8C144;
extern f32 D_00F8C140;
extern f32 D_00F8C13C;
extern f32 D_00F8C138;
extern s32 D_00FBB5C4;
extern s32 D_00FBB5C8;
extern OvlMtx D_00F8C240;
extern OvlMtx D_00F8C290;
extern OvlMtx D_00F85200;
extern OvlMtx D_00F85180;
extern s32 D_00F9B2EC;
extern s32 D_00F850A0;
extern s32 D_00F8C130;
void func_00f2f610(void);
void func_00f35800(void);
s32 func_00f41448(void);
void func_00114820(void);
s32 func_001c0310(s32, void (*)(void), ...);
void func_00f31000(void);
f32 *func_00f3f2c0(void);
Pad *func_001ba488(s32);
void func_00f2fa68(u32, s32 *, f32 *);
void func_00f2fcf8(u32, s32 *, f32 *);
void func_00f2fc50(u32, s32 *, f32 *);
void func_00f2eb78(s32);
void func_00f2d308(s32);
void func_00f2f400(s32); CONTEXT_ONLY void func_00f2f400(s32 a0) {}
void func_00f2d2b0(s32);
void func_00f2f7b0(void);
void func_00f30568(u32);
void func_00f324c0(s32);
void func_00f324d0(f32 *);
void func_001becb8(OvlMtx, f32 *, s32);
void func_00f2c8d8(f32 *);
s32 func_00f2d238(s32, s32);
s32 func_00f2d360(s32, s32);
void func_001ed410(s32, s32, s32, s32);
s32 func_00f40c98(void);
s32 func_00f3a860(s32 *, s32 *);
s32 func_00f3d4d8(s32 *, s32 *);
void func_00f31118(s32, s32, s32 *);
void func_00f34998(void);
void func_00f362f8(void);
void func_00f30628(void);
void func_00f2ee10(void);
void func_00f3e5d0(void);
void func_00f2c3f8(void);
void func_00f30178(void);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0RotMatrixY(OvlMtx, OvlMtx, f32);
void sceVu0RotMatrixZ(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, f32 *);
void sceVu0Normalize(f32 *, f32 *);
void sceVu0CopyVector(f32 *, f32 *);

void func_00f31430(void)
{
    f32 lim[4];
    s32 buf[4];
    OvlMtx m2;
    f32 *sz;
    OvlMtx m;
    f32 xx[4];
    Pad *pad;
    f32 v[4];
    s32 a, b;
    f32 f;
    s32 i;

    s32 snd, mask;
    s32 k, s;
    if (D_00F850F4 == 0) return;
    func_00f2f610();
    func_00f35800();
    if (D_003F76BC == 1 && D_00F87350 == 0 && func_00f41448() == 0 && D_00F9B2F0 == 0) {
        D_003F76BC = 0;
        D_00F8C23C = 1;
        func_00114820();
        func_001c0310(-1, func_00f31000);
    }
    if (D_00F8C220 == 0 && D_00F8C23C == 0 && D_00F9B1C0 >= 30) {
        sz = func_00f3f2c0();
        lim[0] = sz[0] * 0.5f;
        lim[1] = sz[1] * 0.5f;
        lim[2] = sz[1];
        pad = func_001ba488(0);
        D_00F8C210[0] = pad->f44 * 0.5235987f;
        D_00F8C210[2] = pad->f40 * 0.5235987f;
        D_00F8C210[1] = pad->f40 * 0.5235987f;
        for (i = 0; i < 3; i++) {
            if (D_00FBDA90[i] < D_00F8C210[i]) {
                D_00FBDA90[i] = D_00FBDA90[i] + D_002BBDEC * 0.069813165f;
                if (D_00F8C210[i] < D_00FBDA90[i]) D_00FBDA90[i] = D_00F8C210[i];
            }
            if (D_00F8C210[i] < D_00FBDA90[i]) {
                D_00FBDA90[i] = D_00FBDA90[i] - D_002BBDEC * 0.069813165f;
                if (D_00FBDA90[i] < D_00F8C210[i]) D_00FBDA90[i] = D_00F8C210[i];
            }
        }
        D_00FBDA80[2] = 0.0f;
        D_00FBDA80[0] = D_00FBDA80[0] + D_00FBDA90[1] * 80.0f * 1.9098597f * D_00F8C134 * D_002BBDEC;
        D_00FBDA80[1] = D_00FBDA80[1] - D_00FBDA90[0] * 80.0f * 1.9098597f * D_00F8C134 * D_002BBDEC;
        D_00FBDA80[3] = 1.0f;
        if (D_00FBDA80[0] < -lim[0]) D_00FBDA80[0] = -lim[0];
        if (lim[0] < D_00FBDA80[0]) D_00FBDA80[0] = lim[0];
        if (D_00FBDA80[1] < -lim[2]) D_00FBDA80[1] = -lim[2];
        if (lim[1] < D_00FBDA80[1]) D_00FBDA80[1] = lim[1];
        if (D_00F8C1FC == 0) {
            if (D_00FBBA64 >= 1.0f && D_00F8C284 != 0 && D_00FBB5C0 == 0 && D_00F8C1F0 == 0 && (pad->held & D_00F8C154)) {
                func_00f2fa68(D_00F8C154, &D_00F8C1EC, &D_002BBDEC);
            } else if (D_00F8C1EC == 0) {
                if (pad->held & D_00F8C158) {
                    D_00FBB5B4++;
                    func_00f2fcf8(D_00F8C158, &D_00F8C1EC, &D_002BBDEC);
                }
            } else if (D_00F8C1F0 != 0 && !(pad->held & D_00F8C158)) {
                func_00f2fc50(D_00F8C158, &D_00F8C1EC, &D_002BBDEC);
            }
            snd = -1;
            if (D_00FBB808[0] != 0) D_00FBB808[0]--;
            if (D_00FBB808[1] != 0) D_00FBB808[1]--;
            mask = 0;
            if (D_00FBB808[2] != 0) D_00FBB808[2]--;
            if (D_00FBDAF8.b3D != 0 && D_00FBBA58 > 0 && D_00FBB808[0] == 0 && (pad->press & D_00F8C160)) {
                D_00FBB808[0] = 25;
                if (D_00F8C12C == 0) D_00FBBA58--;
                snd = 0;
                mask = 1;
            }
            if (D_00FBDAF8.b3E != 0 && D_00FBBA58 > 0 && D_00FBB808[1] == 0 && (pad->press & D_00F8C160)) {
                D_00FBB808[1] = 6;
                if (D_00F8C12C == 0) D_00FBBA58--;
                if (snd < 1) snd = 1;
                mask |= 2;
            }
            if (D_00FBDAF8.b3F != 0 && D_00FBBA58 > 0 && D_00FBB808[2] == 0 && (pad->press & D_00F8C160)) {
                D_00FBB808[2] = 37;
                if (D_00F8C12C == 0) D_00FBBA58--;
                mask |= 4;
                if (snd < 2) snd = 2;
            }
            if (mask != 0) func_00f2eb78(mask);
            if (snd >= 0) func_00f2d308(snd);
            snd = -1;
            if (D_00FBB818[0] != 0) D_00FBB818[0]--;
            if (D_00FBB818[1] != 0) D_00FBB818[1]--;
            if (D_00FBB820 != 0) D_00FBB820--;
            if (pad->held & D_00F8C164) {
                if (D_00FBDAF8.b3A != 0 && D_00FBB818[0] == 0) {
                    func_00f2f400(0);
                    snd = 0;
                    D_00FBB818[0] = 3;
                }
                if (D_00FBDAF8.b3B != 0 && D_00FBB818[1] == 0) {
                    func_00f2f400(1);
                    D_00FBB818[1] = 6;
                    if (snd < 1) snd = 1;
                }
                if (D_00FBDAF8.b3C != 0 && D_00FBB820 == 0) {
                    func_00f2f400(2);
                    D_00FBB820 = 70;
                    if (snd < 2) snd = 2;
                }
            }
            if (snd >= 0) func_00f2d2b0(snd);
            if (D_00FBB824 != 0) D_00FBB824--;
            if (D_00FBBA58 >= 2 && D_00FBB824 == 0 &&
                (D_00F8DAF8.b2C != 0 || D_00F8DAF8.b2D != 0 || D_00F8DAF8.b2E != 0 || D_00F8DAF8.b2F != 0) &&
                (pad->f3C > 0.29999999f || (pad->held & D_00F8C168))) {
                D_00FBB5B8++;
                func_00f2f7b0();
                D_00FBB824 = 84;
                if (D_00F8C12C == 0) D_00FBBA58 -= 10;
            }
            if (D_00FBB824 == 0 && D_00F8C1F0 == 0 && D_00F8C1EC == 0 && (pad->held & D_00F8C15C) &&
                D_00FBBA58 >= 2 && D_00F8C14C != 0 && D_00F8C1FC == 0) {
                func_00f30568(D_00F8C15C);
                D_00FBBA58 -= 10;
            }
        }
        if (D_00F8C1E8 == 1) {
            if (-1000.0f < D_00FBEBB8) {
                D_00FBEBB8 -= 40.0f;
                if (D_00FBEBB8 < -1000.0f) D_00FBEBB8 = -1000.0f;
            }
        } else if (D_00F8C1E8 < 2 || D_00F8C1E8 >= 4) {
            if (D_00FBEBB8 != 0.0f) {
                if (D_00FBEBB8 < 0.0f) {
                    D_00FBEBB8 += 40.0f;
                    if (0.0f < D_00FBEBB8) D_00FBEBB8 = 0.0f;
                }
                if (0.0f < D_00FBEBB8) {
                    D_00FBEBB8 -= 40.0f;
                    if (D_00FBEBB8 < 0.0f) D_00FBEBB8 = 0.0f;
                }
            }
        } else {
            if (D_00FBEBB8 < 1000.0f) {
                D_00FBEBB8 += 40.0f;
                if (1000.0f < D_00FBEBB8) D_00FBEBB8 = 1000.0f;
            }
        }
        if (D_00F8C1EC == 0 && D_00F8C284 != 0 && D_00FBBA64 < 1.0f) {
            D_00FBBA64 += D_002BBDEC * 0.005f;
            if (1.0f <= D_00FBBA64) D_00FBBA64 = 1.0f;
        }
        if (D_00F8C1EC != 0) {
            D_00F8C144 *= 1.05f;
            if (D_00F8C138 < D_00F8C144) D_00F8C144 = D_00F8C138;
        } else if (D_00F8C1F0 != 0) {
            D_00F8C144 *= 0.95f;
            if (D_00F8C144 < D_00F8C13C) D_00F8C144 = D_00F8C13C;
        } else if (D_00F8C144 != D_00F8C140) {
            if (D_00F8C140 < D_00F8C144) {
                D_00F8C144 *= 0.98f;
                if (D_00F8C144 < D_00F8C140) D_00F8C144 = D_00F8C140;
            } else if (D_00F8C144 < D_00F8C140) {
                if (D_00F8C144 < 0.5f) {
                    D_00F8C144 += 0.049999998f;
                } else {
                    D_00F8C144 *= 1.02f;
                }
                if (D_00F8C140 < D_00F8C144) D_00F8C144 = D_00F8C140;
            }
        }
        if (D_00FBB5C0 != 0 && D_00F8C140 < D_00F8C144) D_00F8C144 = D_00F8C140;
        if (pad->held & 0x800) {
            func_00f324c0(1);
        } else {
            func_00f324c0(0);
        }
    }
    if (D_00F8C220 != 0) D_00FBB5C4 = 0;
    if (D_00FBB5C4 == 0) {
        sceVu0UnitMatrix(m);
        sceVu0RotMatrixY(m, m, D_00FBDA90[1]);
        sceVu0RotMatrixX(m, m, D_00FBDA90[0]);
        if (D_00FBB5C8 != 0 && --D_00FBB5C8 != 0) {
            f = (f32)D_00FBB5C8 / 6.0f;
            v[0] = (D_00FBDAA0[0] - m[2][0]) * f + m[2][0];
            v[1] = (D_00FBDAA0[1] - m[2][1]) * f + m[2][1];
            v[3] = 1.0f;
            v[2] = (D_00FBDAA0[2] - m[2][2]) * f + m[2][2];
            sceVu0Normalize(v, v);
            func_001becb8(m, v, 0);
        }
        sceVu0UnitMatrix(D_00F8C240);
        sceVu0RotMatrixZ(D_00F8C240, D_00F8C240, D_00FBDA90[2]);
        sceVu0MulMatrix(D_00F8C240, m, D_00F8C240);
    } else {
        func_00f324d0(v);
        v[0] -= D_00FBDA80[0];
        v[1] -= D_00FBDA80[1];
        v[2] -= D_00FBDA80[2];
        sceVu0Normalize(v, v);
        func_001becb8(m, v, 0);
        sceVu0UnitMatrix(D_00F8C240);
        sceVu0RotMatrixZ(D_00F8C240, D_00F8C240, D_00FBDA90[2]);
        sceVu0MulMatrix(D_00F8C240, m, D_00F8C240);
        sceVu0CopyVector(D_00FBDAA0, v);
        D_00FBB5C8 = 6;
    }
    sceVu0TransMatrix(D_00F8C240, D_00F8C240, D_00FBDA80);
    sceVu0MulMatrix(D_00F8C240, D_00F8C240, D_00F8C290);
    func_00f2c8d8(D_00FBDAB0);
    sceVu0MulMatrix(m2, D_00F85200, D_00F8C240);
    sceVu0MulMatrix(m2, D_00F85180, m2);
    k = (s32)-((m2[3][1] / m2[3][3] - 2048.0f) * 256.0f / 192.0f);
    if (k > 256) k = 256;
    if (k < -256) k = -256;
    s = func_00f2d360(D_00F8C1E8, func_00f2d238(256, -256));
    if (D_00F8C1E8 + 0x1000 >= 0) func_001ed410(-1, s, D_00F8C1E8 + 0x1000, k);
    if (D_00FBB828 != 0) D_00FBB828--;
    if (func_00f40c98() == 0 && D_00FBB828 == 0 && D_00F8C1FC == 0 && (D_00F9B2EC == 0 || D_00F850A0 != 0)) {
        D_00F8C130 = func_00f3a860(&a, &b);
        if (D_00F8C130 == 0) {
            D_00F8C130 = func_00f3d4d8(buf, &a);
            b = 0;
            if (D_00F8C130 == 0) goto skip;
        }
        func_00f31118(a, b, buf);
    skip:;
    }
    if (D_00F8C220 == 0 && D_00F8C23C == 0 && D_00F9B1C0 >= 30) func_00f34998();
    func_00f362f8();
    func_00f30628();
    func_00f2ee10();
    func_00f3e5d0();
    func_00f2c3f8();
    func_00f30178();
}
