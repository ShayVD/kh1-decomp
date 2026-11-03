/* gb.x func_00f35a80: matched by hand (session 141, wwm1 round 17): a CONTEXT_ONLY func_00f357b0 and func_00f358b8 above it. A call to a function defined earlier in the file is nothrow, which changes reorg's branch-likely choice (docs/overlays.md, "Branch-likely vs plain branch"). */
#include "ovl.h"
typedef struct { u8 pad0[6]; u16 w; u16 d; u16 h; } GbDims;
typedef struct {
    u8 pad0[0xA0];
    GbDims dims;
    u8 padac[0x1010 - 0xAC];
    u8 x1010[16];
} GbWorld;
typedef struct { s32 x0, x4, x8; } Pad;
typedef struct {
    u8 pad0[10];
    u8 b10;
    u8 pad11[5];
    OvlVec a;
    OvlVec b;
    u8 pad30[0x30];
} GbCamInfo;
typedef struct {
    OvlVec pos;
    u8 pad10[0x40 - 0x10];
    OvlVec trans;
    OvlVec rot;
} GbCam;
extern GbWorld *D_00F56DC0;
extern s32 D_00F616BC;
extern s32 D_00F616B8;
extern OvlVec D_00F80840;
extern OvlVec D_00F61630;
extern OvlVec D_00F80810;
extern OvlVec D_00F80820;
extern OvlVec D_00F80830;
extern GbCam D_00F80960;
extern s32 D_00F809C4;
extern s32 D_00F809C8;
extern s32 D_00F80850;
extern OvlMtx D_00F56E00;
extern OvlMtx D_00F56E80;
extern OvlMtx D_00F80860;
void func_001bc900(GbDims *, GbCamInfo *);
void func_001bd9e8(GbDims *);
void func_001bd470(void);
void sceVu0CopyVector(f32 *, f32 *);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, f32 *);
void sceVu0TransMatrix(OvlMtx, OvlMtx, f32 *);
void sceVu0ViewScreenMatrix(OvlMtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_00f35810(s32);
void func_001be9f0(f32 *);
void func_00f28c70(void);
s32 func_001c0310(s32, void *, ...);
void func_00f353b8();
void func_00f353e8();
void func_00f33968();
void func_001bfac8(void);
Pad *func_001ba488(s32);
s32 func_00f25418(Pad *);
CONTEXT_ONLY void func_00f357b0(void) {}
void func_00f25a18(void);
void func_00f219b0(s32);
s32 func_00f20060(void);
void func_00f20170(s32, s32);
CONTEXT_ONLY s32 func_00f358b8(s32 a0) { return 0; }
void func_001bebd0(OvlMtx, GbCam *, void *);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f28e10(s32, f32, s32);
#else
void func_00f28e10(s32, s32, f32);
static __inline__ void ee_00f28e10(s32 x0, f32 x1, s32 x2) { func_00f28e10(x0, x2, x1); }
#undef func_00f28e10
#define func_00f28e10 ee_00f28e10
#endif
void func_00f25a68(void);

void func_00f35a80(void) {
    OvlMtx vs;
    GbCamInfo info;
    Pad *p;
    s32 btn, b, i, n;
    f32 x, y, z, lo, hi, f;
    D_00F616BC = 0;
    func_001bc900(&D_00F56DC0->dims, &info);
    func_001bd9e8(&D_00F56DC0->dims);
    func_001bd470();
    D_00F616B8 = -1;
    x = -(D_00F56DC0->dims.w * 0.5f) * 200.0f;
    y = D_00F56DC0->dims.d * 0.5f * 200.0f;
    z = -(D_00F56DC0->dims.h * 0.5f) * 200.0f;
    D_00F80840[3] = 1.0f;
    D_00F61630[3] = 1.0f;
    D_00F80840[1] = y;
    D_00F80840[2] = z;
    D_00F80840[0] = x;
    D_00F61630[1] = -y;
    D_00F61630[2] = -z;
    D_00F61630[0] = -x;
    sceVu0CopyVector(D_00F80810, info.a);
    sceVu0CopyVector(D_00F80820, info.b);
    for (i = 0; i < 3; i++)
        D_00F80830[i] = D_00F80810[i] + (D_00F80820[i] - D_00F80810[i]) * 0.5f;
    D_00F80830[3] = 1.0f;
    func_00f35810(info.b10);
    sceVu0ViewScreenMatrix(vs, 512.0f, 1.0f, 1.0f, 2064.0f, 2080.0f, 1.0f, 16777000.0f, 1.0f, 65536.0f);
    f = D_00F56DC0->dims.w * 120;
    hi = D_00F80960.pos[2] + f;
    lo = D_00F80960.pos[2] - (f + f);
    func_001be9f0(D_00F80960.rot);
    func_00f28c70();
    func_001c0310(-1, func_00f353b8);
    D_00F809C4 = 0;
    D_00F80850 = 1;
    n = 0;
    while (1) {
        sceVu0CopyMatrix(D_00F56E00, vs);
        n++;
        sceVu0UnitMatrix(D_00F56E80);
        sceVu0TransMatrix(D_00F56E80, D_00F56E80, D_00F80960.trans);
        sceVu0RotMatrix(D_00F56E80, D_00F56E80, D_00F80960.rot);
        D_00F56E80[3][2] -= D_00F80960.pos[2];
        if (n < 5) {
            func_001bfac8();
            continue;
        }
        p = func_001ba488(0);
        btn = func_00f25418(p);
        b = p->x8;
        if (b & 0x4200) {
            D_00F80850 = 0;
            func_00f357b0();
            func_00f25a18();
            func_00f219b0(1);
            return;
        }
        if (b & 8) {
            if (!func_00f20060()) {
                D_00F80850 = 0;
                func_00f357b0();
                func_00f25a18();
                func_001c0310(-1, func_00f33968);
                func_00f219b0(3);
                return;
            }
            b = p->x8;
        }
        if (b & 1) {
            D_00F80850 = 0;
            n = 0;
            D_00F616BC = 1;
            func_00f357b0();
            func_00f20170(2, 0);
            func_001c0310(-1, func_00f353b8);
            D_00F616BC = 0;
            D_00F80850 = 1;
        } else if (b & 0x8000) {
            func_00f358b8(0);
        } else if (b & 0x1000) {
            func_00f358b8(1);
        } else if (D_00F809C4 == 0 && (b & 0x2000)) {
            D_00F809C8 = func_001c0310(-1, func_00f353e8);
        } else {
            if (btn & 0x1000)
                D_00F80960.rot[0] -= (3.141592503f / 90.0f);
            if (btn & 0x4000)
                D_00F80960.rot[0] += (3.141592503f / 90.0f);
            if (btn & 0x8000)
                D_00F80960.rot[1] += (3.141592503f / 90.0f);
            if (btn & 0x2000)
                D_00F80960.rot[1] -= (3.141592503f / 90.0f);
            if (p->x4 & 0x400)
                D_00F80960.pos[2] += 20.0f;
            if (p->x4 & 0x100)
                D_00F80960.pos[2] -= 20.0f;
            if (D_00F80960.pos[2] < lo)
                D_00F80960.pos[2] = lo;
            if (hi < D_00F80960.pos[2])
                D_00F80960.pos[2] = hi;
        }
        func_001be9f0(D_00F80960.rot);
        func_001bebd0(D_00F80860, &D_00F80960, D_00F56DC0->x1010);
        func_00f28e10(50, 0.5f, 1);
        func_00f28e10(51, 0.5f, 1);
        func_00f25a68();
        func_001bfac8();
    }
}
