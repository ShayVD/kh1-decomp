#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec4[4] __attribute__((aligned(16)));
typedef s32 IVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615FC0;
extern PppMtx D_00616040;
typedef struct { u8 pad[48]; u128 q; } KekoG;
extern KekoG D_0061E800;
extern s8 D_00372EA0;
extern s32 D_00372EA8[];

typedef struct {
    u8 pad0[4];
    s32 w4;
    s32 w8;
    s32 wC;
} KekoHdr;
typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0xE];
    u8 b16, b17;
} KekoMdl;
typedef struct {
    u8 pad0[0x1C];
    KekoMdl *mdl;
    u8 pad20[4];
} KekoSlot;
typedef struct {
    u8 pad0[0x10];
    KekoSlot *slot;
} KekoRes;
extern KekoRes *D_00615E64;

typedef struct {
    u8 pad0[4];
    s32 id;
    f32 len;
    f32 off;
    f32 col[2][4];
    u8 b30;
} KekoKey;
typedef struct {
    u8 pad0[0xC];
    s32 *offs;
} KekoEnv;

void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002673b8(f32 *, f32 *);
void func_002675e0(s32 *, f32 *);
s32 func_00267ea8(f32 *);
void FlushCache(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, s32);
void sceGsSyncPath(s32, s32);
static inline f32 keko_sqrtf(f32 x) {
    f32 r;
    __asm__ volatile(".set noreorder\n\tsqrt.s %0, %1\n\t.set reorder" : "=f"(r) : "f"(x));
    return r;
}

static inline s32 keko_alloc(s32 n) {
    s8 *sp = &D_00372EA0;
    s32 *st = D_00372EA8;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v + n;
    return v;
}

void pppRyjDrawKekotoDraw(u8 *obj, KekoKey *k, KekoEnv *e) {
    Vec4 v[2];
    Vec4 V[8];
    IVec4 cv[8];
    s32 ca[4];
    s32 cb[4];
    f32 sc[2];
    Vec4 d;
    Vec4 n;
    Vec4 tmp;
    Vec4 *w2;
    u8 *w0;
    f32 r0, r1;
    s32 i, j;
    u64 *pkt;
    s32 phys;
    u64 *tag;
    s32 cnt;
    s32 *p;
    KekoMdl *mdl;
    KekoHdr *hdr;
    f32 c8, c9, cA, cB;
    s32 *c0, *c1;
    Vec4 *q;
    IVec4 *c;

    w2 = (Vec4 *)(obj + e->offs[2] + 0xA0);
    w0 = obj + e->offs[0] + 0xA0;
    if (k->id == 0xFFFF) return;
    v[0][0] = -k->len;
    v[0][1] = 0;
    v[0][2] = 0;
    v[0][3] = 1.0f;
    v[1][0] = k->len;
    v[1][1] = 0;
    v[1][2] = 0;
    v[1][3] = 1.0f;
    if (k->b30) {
        Vec4 t0, t1;
        PppMtx M;
        sceVu0MulMatrix(M, D_00615FC0, D_00615E68->m);
        func_002672f8(t0, M, v[0]);
        func_002675a8(t1, t0);
        t1[0] += k->off;
        func_002672f8(t0, D_00616040, t0);
        func_002672f8(t1, D_00616040, t1);
        if (t0[3] > 0.0f && t1[3] > 0.0f) {
            t0[3] = 1.0f / t0[3];
            func_00267e90(t0, t0, t0[3]);
            t1[3] = 1.0f / t1[3];
            func_00267e90(t1, t1, t1[3]);
            func_00267530(t0, t0, t1);
            r0 = keko_sqrtf(t0[0] * t0[0] + t0[1] * t0[1]);
        } else {
            r0 = 0.0f;
        }
        func_002672f8(t0, M, v[1]);
        func_002675a8(t1, t0);
        t1[0] += k->off;
        func_002672f8(t0, D_00616040, t0);
        func_002672f8(t1, D_00616040, t1);
        if (t0[3] > 0.0f && t1[3] > 0.0f) {
            t0[3] = 1.0f / t0[3];
            func_00267e90(t0, t0, t0[3]);
            t1[3] = 1.0f / t1[3];
            func_00267e90(t1, t1, t1[3]);
            func_00267530(t0, t0, t1);
            r1 = keko_sqrtf(t0[0] * t0[0] + t0[1] * t0[1]);
        } else {
            r1 = 0.0f;
        }
        if (r0 == 0.0f && r1 == 0.0f) return;
    } else {
        Vec4 u0, u1;
        PppMtx M;
        sceVu0MulMatrix(M, D_00615FC0, D_00615E68->m);
        u0[0] = u0[1] = u0[2] = 0.0f;
        u0[3] = 1.0f;
        func_002672f8(u0, M, u0);
        func_002675a8(u1, u0);
        u1[0] += k->off;
        func_002672f8(u0, D_00616040, u0);
        func_002672f8(u1, D_00616040, u1);
        if (u0[3] > 0.0f && u1[3] > 0.0f) {
            u0[3] = 1.0f / u0[3];
            func_00267e90(u0, u0, u0[3]);
            u1[3] = 1.0f / u1[3];
            func_00267e90(u1, u1, u1[3]);
            func_00267530(u0, u0, u1);
            r0 = r1 = keko_sqrtf(u0[0] * u0[0] + u0[1] * u0[1]);
        } else {
            r0 = r1 = 0.0f;
        }

    }
    func_002672f8(V[2], D_00615E68->m2, v[0]);
    func_002672f8(V[4], D_00615E68->m2, v[1]);
    if (V[2][3] <= 0.0f && V[4][3] <= 0.0f) return;
    if (V[2][3] > 0.0f) {
        sc[0] = V[2][3] = 1.0f / V[2][3];
        func_00267e90(V[2], V[2], V[2][3]);
    }
    if (V[4][3] > 0.0f) {
        sc[1] = V[4][3] = 1.0f / V[4][3];
        func_00267e90(V[4], V[4], V[4][3]);
    }
    d[2] = 0.0f;
    d[3] = 0.0f;
    d[0] = V[4][0] - V[2][0];
    d[1] = V[4][1] - V[2][1];
    func_002673b8(d, d);
    n[1] = d[0];
    n[2] = 0.0f;
    n[0] = -d[1];
    n[3] = 0.0f;
    func_00267560(tmp, n, r0);
    func_00267518(V[3], V[2], tmp);
    func_00267560(tmp, n, r1);
    func_00267518(V[5], V[4], tmp);
    n[0] = -n[0];
    n[1] = -n[1];
    func_00267560(tmp, n, r0);
    func_00267518(V[2], V[2], tmp);
    func_00267560(tmp, n, r1);
    func_00267518(V[4], V[4], tmp);
    func_00267560(tmp, d, r0);
    func_00267530(V[0], V[2], tmp);
    func_00267530(V[1], V[3], tmp);
    func_00267560(tmp, d, r1);
    func_00267518(V[6], V[4], tmp);
    func_00267518(V[7], V[5], tmp);
    for (i = 0; i < 8; i++) func_002675e0(cv[i], V[i]);
    c8 = w0[8];
    c9 = w0[9];
    cA = w0[10];
    cB = w0[11];
    ca[0] = c8 * k->col[0][0];
    ca[1] = c9 * k->col[0][1];
    ca[2] = cA * k->col[0][2];
    ca[3] = cB * k->col[0][3];
    cb[0] = c8 * k->col[1][0];
    cb[1] = c9 * k->col[1][1];
    cb[2] = cA * k->col[1][2];
    cb[3] = cB * k->col[1][3];
    c0 = ca;
    c1 = cb;
    for (i = 0; i < 4; i++) {
        if (ca[i] < 0) ca[i] = 0;
        else if (ca[i] >= 256) ca[i] = 255;
        if (cb[i] < 0) cb[i] = 0;
        else if (cb[i] >= 256) cb[i] = 255;
    }
    mdl = D_00615E64->slot[k->id].mdl;
    hdr = (KekoHdr *)((u8 *)mdl + mdl->w4);
    pkt = (u64 *)keko_alloc(2048);

    pkt[2] = 0x3000000000000001ULL;
    pkt[3] = 0xEEE;
    cnt = 0;
    tag = pkt + 10;
    ((s32 *)pkt)[8] = hdr->w8;
    c = cv;
    p = (s32 *)(pkt + 12);
    ((s32 *)pkt)[9] = hdr->wC;
    pkt[5] = 6;
    q = w2;
    ((s32 *)pkt)[12] = mdl->b16;
    ((s32 *)pkt)[13] = mdl->b17;
    phys = ((s32)pkt & 0x0FFFFFFF) | 0x80000000;
    pkt[7] = 0x42;
    ((u128 *)pkt)[4] = D_0061E800.q;

    for (i = 0; i < 8; i++, c++, q++) {

        if (func_00267ea8(V[i])) continue;

        if (k->b30) {
            if (i < 4) func_00267560(tmp, w2[i], sc[0]);
            else func_00267560(tmp, w2[i], sc[1]);
            *(f32 *)p = tmp[0]; p++;
            *(f32 *)p = tmp[1]; p++;
            *(f32 *)p = tmp[2]; p++;
        } else {
            *(f32 *)p = (*q)[0]; p++;
            *(f32 *)p = (*q)[1]; p++;
            *(f32 *)p = (*q)[2]; p++;
        }
        *p++ = 0;
        if (i < 4) {
            for (j = 0; j < 4; j++) *p++ = c0[j];
        } else {
            for (j = 0; j < 4; j++) *p++ = c1[j];
        }
        cnt++;
        *p++ = (*c)[0];
        *p++ = (*c)[1];
        *p++ = (*c)[2];
        *p++ = 0;
    }
    tag[0] = (cnt | 0x8000) | (0xC0B9ULL << 46);
    tag[1] = 0x412;
    __asm__ volatile("sync");
    *(u128 *)pkt = 0;
    *(s32 *)pkt = ((((s32)p - (s32)pkt) >> 4) - 1) | 0x70000000;
    FlushCache(0);
    func_00266f38(func_00266c08(2), phys);
    sceGsSyncPath(0, 0);
    { s8 *sp_ = &D_00372EA0; s32 i_ = *sp_; i_--; *sp_ = i_; }
}
