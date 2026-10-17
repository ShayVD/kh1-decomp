#include "common.h"

typedef struct { f32 x, y, z; } V12;
typedef struct { f32 u, v; } UV;

void func_00106b18(void *);
void *func_00121e28(s32, void *);
void func_00121ee0(void *);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_002678b8(void *, void *, void *);
void func_00267578(void *, void *, void *);
void func_00103b68(void *, void *, void *, void *, void *);
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void sceVu0MulMatrix(void *, void *, void *);
void func_00103a70(void);
s32 FlushCache(s32);
s32 sceGsSyncPath(s32, s32);

extern u8 D_002A5FD0[], D_002A6110[];
extern f32 D_003732D0[];
extern volatile f32 D_00494A70;
extern f32 D_004948A0[4], D_002A60C0[4];
extern f32 D_004948B0[4][4], D_004948F0[4][4], D_004949B0[4][4], D_004949F0[4][4];
extern f32 D_002A6080[4], D_002A6090[4], D_002A60A0[4], D_002A60B0[4];
extern u8 D_0048C770[];
extern u32 *D_0048CAD4;

s32 func_00103c48(void) {
    f32 mt[4][4] __attribute__((aligned(16)));
    V12 *vtx;
    UV *uv;
    u32 *pkt;
    u32 *p;
    s32 w, h, i, j, k;
    s32 dx, dy;
    u32 n;
    s32 a;
    u64 tag;
    f32 x, y, u, v;
    f32 *c;
    f32 sc;

    h = 25;
    func_00106b18(D_002A5FD0);
    w = 25;
    func_00106b18(D_002A6110);
    vtx = func_00121e28(7500, &vtx);
    uv = func_00121e28(5000, &uv);
    y = -192.0f;
    v = 0.0f;
    for (j = 0; j < h; j++) {
        x = -192.0f;
        u = 0.125f;
        for (i = 0; i < w; i++) {
            vtx[j * w + i].x = x;
            x += 16.0f;
            vtx[j * w + i].y = y;
            vtx[j * w + i].z = 0;
            uv[j * w + i].u = u;
            u += 0.03125f;
            uv[j * w + i].v = v;
        }
        y += 16.0f;
        v += 0.03125f;
    }
    dy = 2048 / h;
    dx = 2048 / w;
    c = &D_003732D0[2048];
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            sc = D_00494A70;
            vtx[j * w + i].z = c[j * dy] * sc + c[i * dx] * sc;
        }
    }
    pkt = func_00121e28(0xe114, &pkt);
    p = pkt;
    *p++ = 0x10000e40;
    *p++ = 0;
    *p++ = 0x13000000;
    *p++ = 0;
    n = w * 2;
    tag = 0x300e400000008032;
    for (k = 0; k < h - 1; k++) {
        *p++ = 0;
        *p++ = 0x6c978000;
        *p++ = (u32)tag;
        *p++ = tag >> 32;
        *p++ = 0x412;
        *p++ = 0;
        for (i = 0; i < n / 2; i++) {
            a = i * w + k;
            *(f32 *)p++ = vtx[a].x;
            *(f32 *)p++ = vtx[a].y;
            *(f32 *)p++ = vtx[a].z;
            *(f32 *)p++ = 1.0f;
            a++;
            *(f32 *)p++ = vtx[a].x;
            *(f32 *)p++ = vtx[a].y;
            *(f32 *)p++ = vtx[a].z;
            *(f32 *)p++ = 1.0f;
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < 4; j++) {
                *(f32 *)p++ = 128.0f;
            }
        }
        for (i = 0; i < n / 2; i++) {
            a = i * w + k;
            *(f32 *)p++ = uv[a].u;
            *(f32 *)p++ = uv[a].v;
            *(f32 *)p++ = 1.0f;
            *p++ = 0;
            a++;
            *(f32 *)p++ = uv[a].u;
            *(f32 *)p++ = uv[a].v;
            *(f32 *)p++ = 1.0f;
            *p++ = 0;
        }
        *p++ = 0x17000000;
        *p++ = 0;
    }
    *p++ = 0x70000000;
    *p++ = 0;
    p[1] = 0;
    p[0] = 0;
    sceVu0UnitMatrix(mt);
    func_002678b8(D_004948B0, mt, D_002A60C0);
    func_00267578(D_004948B0, D_004948B0, D_004948A0);
    func_00103b68(D_004949B0, D_002A6080, D_002A6090, D_002A60A0, D_002A60B0);
    func_00267b08(D_004949F0, 512.0f, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 16777215.0f, 1.0f, 65536.0f);
    sceVu0MulMatrix(D_004948F0, D_004949F0, D_004949B0);
    func_00103a70();
    D_0048CAD4 = pkt;
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = (u32)D_0048C770 & 0x0fffffff;
    *(volatile u32 *)0x1000e010 = 2;
    FlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    func_00121ee0(vtx);
    func_00121ee0(uv);
    sceGsSyncPath(0, 0);
    func_00121ee0(pkt);
    return 4;
}
