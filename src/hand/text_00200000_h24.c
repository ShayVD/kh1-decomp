#include "common.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; } S2C40;
extern S2C40 D_003F2C40[];
void func_00201440(s32, s32, s32, s32, s32, s32, s32, void *, s32);
void func_00201460(s32, s32, s32, s32, s32, s32, s32, void *, s32);
void func_00201480(s32, s32, s32, s32, s32, s32, s32, void *, s32);

void func_002078f0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201440(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40[a1], s0);
}

void func_00207938(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201460(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40[a1], s0);
}

void func_00207980(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201480(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40[a1], s0);
}

void func_00207830(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_002078f0(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

void func_00207870(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_00207938(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

void func_002078b0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_00207980(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

typedef struct { u8 pad[0xbe]; s16 lo0:4; s16 x:12; s16 lo1:4; s16 y:12; s16 lo2:4; s16 z:12; } S79c8;

void func_002079c8(S79c8 *a0) {
    s16 z = a0->z;
    func_002078f0((s32)a0, 1, 2, 2, a0->x, a0->y, z, a0->x + z / 2, 43);
}

void func_002016b0(s32, s32, s32, s32);
void func_00201988(s32, s32, s32, s32);
void func_00201c60(s32, s32, s32, s32);
void func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00207cc0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40[a1];
    func_002016b0(a0, a2, a3 + 2, e->a);
    func_001fb428(a0, 1, 2, 0, a2 + 37, a3 + 7, t0, 12, e->e);
}

void func_00207e20(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40[a1];
    func_00201988(a0, a2, a3 + 3, e->a);
    func_001fb428(a0, 1, 4, 0, a2 + 51, a3 + 7, t0, 12, e->e);
}

void func_00207f80(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40[a1];
    func_00201c60(a0, a2, a3 + 2, e->a);
    func_001fb428(a0, 1, 2, 0, a2 + 29, a3 + 7, t0, 12, e->e);
}

typedef struct { u8 pad0[0x24]; s32 f24; u8 pad[0xb0 - 0x28]; s32 b0; s32 b4; s16 b8; s16 ba; s16 bc; s16 be; s16 c0; s16 c2; s16 c4; s16 c6; u8 pad3[10]; s16 d2; u8 pad4[6]; s16 da; } Sbbc0;
void func_0020bb90(s32, s32);
void func_0020bc48(s32, s32, s32);

void func_0020bbc0(Sbbc0 *a0) {
    func_0020bb90((a0->b0 + a0->c2 * (a0->da + 16) / 16 + a0->be - a0->c6 - 0x7000) >> 4,
                  (a0->b4 + a0->c4 * a0->d2 / 16 + a0->c0 - 0x7400) >> 4);
}

void func_0020bd18(Sbbc0 *a0, s32 a1) {
    func_0020bc48(a1, (a0->b0 + a0->c2 * (a0->da + 16) / 16 + a0->be - a0->c6 - 0x7000) >> 4,
                  (a0->b4 + a0->c4 * a0->d2 / 16 + a0->c0 - 0x7400) >> 4);
}

extern s32 D_006411FC;
extern f32 D_00641200;
extern s32 D_00641204;
extern f32 D_00641208;
extern s32 D_0064120C;
extern f32 D_00641218;

void func_0020be10(s32 a0) {
    D_006411FC = 2;
    D_00641200 = a0;
    D_00641204 = 0;
    D_00641208 = D_00641218;
    D_0064120C = 0;
}

extern u32 D_003E3D68;
void func_00208458(s32, s32, s32, u32, u32);
void func_0020be68(s32, s32, u32);

void func_0020c070(s32 a0) {
    u32 i;
    s32 x = 105;
    func_00208458(a0, 0, 0, 0x80602020, D_003E3D68);
    for (i = 0; i < D_003E3D68; i++) {
        func_0020be68(a0, x, i);
        x += 79;
    }
}

void func_001fc308(s32, s32, s32, s32, s32, s32, s32, s32, s32);


void func_0020ca30(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_001fc308(a0, 12, 11, 0, 0, 3, a1, a2, a3);
}


extern u8 D_003F33A8[];
void func_00205e30(s32, void *);
void func_00206130(s32, s32, s32, s32, s32, s32);
void func_0020ccb0(s32);
void func_0020ce78(s32 a0) {
    func_00205e30(a0, D_003F33A8);
    func_00206130(a0, 0, 0, 512, 2, 0x80f04646);
    func_0020ccb0(a0);
    func_001fc308(a0, 160, 12, 0, 63, 20, 0, 0x40c87878, 0x40c87878);
}

typedef struct { s32 f0; s32 f4; s32 f8; } S5bc8;
extern S5bc8 *D_00425BC8;
extern s32 D_003F34C0;
s32 func_001f4390(s32);
void func_001f3840(s32);
void func_0011d768(s32);
void func_00207618(void);
void func_0020cf90(s32 a0) {
    if (func_001f4390(a0) && (D_00425BC8->f8 & 8)) {
        if (!(D_003F34C0 & 3)) {
            func_001f3840(a0);
            func_0011d768(3);
            func_00207618();
            D_003F34C0 |= 1;
        } else {
            func_0011d768(4);
        }
    }
}

extern s32 D_003F34A4, D_003F34A8, D_003F34C4;
void func_001f3110(void);
s32 func_0020d6c0(s32);
void func_0020d530(void);
s32 func_0020d030(void);
void func_0020d050(s32);
void func_0020d2f8(void);
typedef struct { s16 f0; s16 f2; } Task;
Task *func_0011ef10(s32, void (*)(void));

void func_0020d6c8(s32 a0) {
    s32 v;
    D_003F34A4 = 0;
    func_001f3110();
    if (func_0020d6c0(a0)) return;
    D_003F34A8 = 0;
    func_0020d530();
    v = func_0020d030();
    D_003F34C4 = v;
    if (v) func_0020d050(v);
    func_0011ef10(0x270ff, func_0020d2f8)->f2 = a0;
}

s32 func_001efd98(s32);

void func_0020d890(Sbbc0 *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->b4 -= v;
    a0->ba += v;
    a0->c0 += v;
    a0->f24 = a1;
}

s32 func_001f42b8(Sbbc0 *);
void func_001f3708(Sbbc0 *, s32);
s32 func_001fe570(Sbbc0 *);
void func_00207b38(Sbbc0 *, s32);
void func_00207bb0(Sbbc0 *, s32);

void func_0020d900(Sbbc0 *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->f8 & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207b38(a0, a0->f24);
}

void func_0020d990(Sbbc0 *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->b4 -= v;
    a0->ba += v;
    a0->c0 += v;
    a0->f24 = a1;
}

void func_0020da00(Sbbc0 *a0) {
    if (func_001f42b8(a0)) {
        if (D_00425BC8->f8 & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0)) func_001f3708(a0, 6);
        }
    }
    func_00207bb0(a0, a0->f24);
}

void func_0020da90(Sbbc0 *a0, s32 a1) {
    s32 v = func_001efd98(a1) * 368;
    a0->b4 -= v;
    a0->ba += v;
    a0->c0 += v;
    a0->f24 = a1;
}
