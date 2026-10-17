#include "common.h"
typedef struct { u64 rgba; u64 st; s32 x, y, z, w; } V;
typedef struct { u64 tag[2]; u64 a; u64 b; V v[4]; } G;
extern u32 D_003F34B0[];
extern u8 D_003F1A70[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
u32 func_001edd88(u32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
void func_0020a9b0(s32 a) {
    u64 *p;
    G *g;
    u64 *q;
    void *u;
    func_00266f38(func_00266c08(2), D_003F1A70);
    q = func_00122048(1024, 128);
    p = q++;
    q++;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    g = (G *)q;
    g->tag[0] = 0x9026400000008001;
    g->tag[1] = 0x4e4e4e4ee;
    g->a = 0x44;
    g->b = 0x42;
    g->v[1].rgba = g->v[0].rgba = func_001edd88(D_003F34B0[0] | (a << 24), 64);
    g->v[0].st = 1;
    g->v[0].x = 0x7000;
    g->v[0].y = 0x7400;
    g->v[0].z = 0x100000;
    g->v[0].w = 0;
    g->v[1].st = 1;
    g->v[1].x = 0x9000;
    g->v[1].y = 0x7400;
    g->v[1].z = 0x100000;
    g->v[1].w = 0;
    g->v[3].rgba = g->v[2].rgba = func_001edd88(D_003F34B0[1] | (a << 24), 64);
    g->v[2].st = 1;
    g->v[2].x = 0x7000;
    g->v[2].y = 0x8c00;
    g->v[2].z = 0x100000;
    g->v[2].w = 0;
    g->v[3].st = 1;
    g->v[3].x = 0x9000;
    g->v[3].y = 0x8c00;
    g->v[3].z = 0x100000;
    g->v[3].w = 0;
    q += 20;
    p[0] = (((s32)q - (s32)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}

extern s32 D_003F31F0[];

void func_0020b120(s32 prim, s32 al, u32 c0, u32 c1, u32 c2, u32 c3) {
    u64 *p;
    u64 *q;
    G *g;
    void *u;
    func_00266f38(func_00266c08(2), D_003F1A70);
    q = func_00122048(1024, 128);
    p = q++;
    q++;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    c0 = func_001edd88(c0, al);
    c1 = func_001edd88(c1, al);
    c2 = func_001edd88(c2, al);
    c3 = func_001edd88(c3, al);
    g = (G *)q;
    g->tag[0] = 0x9026400000008001;
    g->tag[1] = 0x4e4e4e4ee;
    g->a = D_003F31F0[prim];
    g->b = 0x42;
    g->v[0].rgba = c0;
    g->v[0].st = 1;
    g->v[0].x = 0x7000;
    g->v[0].y = 0x7400;
    g->v[0].z = 0x100000;
    g->v[0].w = 0;
    g->v[1].rgba = c1;
    g->v[1].st = 1;
    g->v[1].x = 0x9000;
    g->v[1].y = 0x7400;
    g->v[1].z = 0x100000;
    g->v[1].w = 0;
    g->v[2].rgba = c2;
    g->v[2].st = 1;
    g->v[2].x = 0x7000;
    g->v[2].y = 0x8c00;
    g->v[2].z = 0x100000;
    g->v[2].w = 0;
    g->v[3].rgba = c3;
    g->v[3].st = 1;
    g->v[3].x = 0x9000;
    g->v[3].y = 0x8c00;
    g->v[3].z = 0x100000;
    g->v[3].w = 0;
    q += 20;
    p[0] = (((s32)q - (s32)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}

extern s32 D_00640E00[8];
extern s32 D_00640E20;
extern s32 D_003F34A8, D_003F34A4, D_003F34C0, D_003F34C8;
extern s32 D_00640E2C, D_00640E30, D_002BC140, D_002BC144;
s32 func_001ec510(void);
void func_00207598(void);
void func_0020d360(void);
void func_001ef830(void);
void func_00209f70(void);
void func_0020b338(void);
void func_0020a8f0(void);
void func_0020b968(void);
void func_00211358(void);
void func_00213d00(void);
void func_00216118(void);
void func_00217fb0(void);
void func_002190e8(void);
void func_0021adb0(void);
void func_0021dad8(void);
void func_00229820(void);
void func_0020d530(void) {
    s32 n;
    D_00640E00[2] = 2;
    D_00640E00[3] = 3;
    D_00640E00[4] = 4;
    D_00640E00[0] = 0;
    D_00640E00[1] = 1;
    D_00640E20 = 5;
    if (func_001ec510()) {
        D_00640E00[D_00640E20++] = 5;
    }
    D_00640E00[D_00640E20++] = 6;
    if (D_003F34A8 == 1) {
        D_00640E00[D_00640E20++] = 7;
    } 
    func_00207598();
    D_003F34A4 = 1;
    D_00640E2C = D_002BC144;
    D_00640E30 = D_002BC140;
    D_003F34C0 &= ~1;
    D_003F34C0 &= ~2;
    D_003F34C8 = 0;
    func_0020d360();
    func_001ef830();
    func_00209f70();
    func_0020b338();
    func_0020a8f0();
    func_0020b968();
    func_00211358();
    func_00213d00();
    func_00216118();
    func_00217fb0();
    func_002190e8();
    func_0021adb0();
    func_0021dad8();
    func_00229820();
}

typedef struct { u8 pad[4]; u8 x4; u8 pad5[0x17]; u8 x1c; u8 pad1d[0x74 - 0x1d]; } T74;
typedef struct { T74 e[10]; u8 pad[0x48e - 0x488]; u8 x48e[11]; u8 x499[256]; } G4BE8;
extern G4BE8 *D_00304BE8;
typedef struct N { u8 pad[0x10]; struct N *x10; u8 pad14[0x14]; s32 x28; u8 pad2c[0xba - 0x2c]; s16 xba; u8 padbc[0x10]; s16 xcc; s16 xce; } N;
typedef struct { u8 pad[8]; s32 x8; } P5BC8;
extern P5BC8 *D_00425BC8;
extern void *D_00641BA0;
extern s32 D_00641BA4, D_00641BA8, D_00641BAC, D_00641BC4;
extern u8 *D_00641BB0;
extern u32 D_003E3D68;
extern u8 D_003F3CC0[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(N *);
void func_0020bd18(N *, s32);
s32 func_001fd518(N *);
s32 func_001fe5a0(N *);
void func_001f3708(N *, s32);
void func_001f36b8(N *);
N *func_001f31a8(void *, s32);
void func_001f3e90(N *, N *);
void func_001f3e20(N *, N *);
void func_001f3dc0(N *);
s32 func_001ee5f0(s32);
void func_00207870(N *, s32, s32, s32, s32, s32, s32);
void func_00213258(N *a0) {
    N *o, *c;
    u32 i;
    s32 sel, k;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00641BA0);
            func_0011d768(3);
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00641BC4 = func_001fd518(a0);
            o = a0->x10;
            if (o != 0 && (o = o->x10) != 0) {
                s32 v = D_00304BE8->e[D_00304BE8->x48e[D_00641BC4]].x1c + 1;
                o->xcc = v;
                if (v < 9) {
                    o->xce = v;
                    o->xba = v * 448 - 32;
                } else {
                    o->xce = 8;
                    o->xba = 3552;
                }
            }
            if (func_001fe5a0(a0)) {
                func_0011d768(2);
                D_00641BA4 = 1;
                D_00641BA8 = D_00641BC4;
                D_00641BAC = D_00304BE8->x48e[D_00641BC4];
                D_00641BB0 = &D_00304BE8->e[D_00641BAC].x4;
                func_001f3708(a0, 5);
                o = a0->x10;
                if (o != 0) {
                    func_001f36b8(o);
                    o = o->x10;
                    if (o != 0) {
                        o->x28 = 1;
                        c = func_001f31a8(D_003F3CC0, 6);
                        if (c != 0) {
                            func_001f3e90(o, c);
                            func_001f3e20(c, o);
                        }
                        func_001f3dc0(o);
                    }
                }
            }
        }
    }
    sel = func_001fd518(a0);
    for (i = 0, k = 0; i < D_003E3D68; k += 28) {
        s32 eq = i == sel;
        s32 v = func_001ee5f0(D_00304BE8->x48e[i++]);
        func_00207870(a0, eq, 0, 0, k, 122, v);
    }
}
