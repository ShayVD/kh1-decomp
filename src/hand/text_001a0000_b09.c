#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) GV4;
typedef struct { u128 a, b; } __attribute__((aligned(16))) GT32;
extern u128 D_00372770[2];
extern s8 D_00372790[];
s8 *func_001aa950(s32);
void func_001aa9d0(s32);
void func_00267530(GV4 *, GV4 *, GV4 *);
void func_002674b0(GV4 *, GV4 *, f32);
void func_00267518(GV4 *, GV4 *, GV4 *);

void func_001a9460(f32 t, u32 c0, u32 c1, u32 *dst) {
    GV4 a;
    GV4 b;
    s8 *tb;
    s32 n;
    s32 i;
    u32 *p;
    f32 f;

    tb = func_001aa950(32);
    n = t;
    ((u128 *)tb)[0] = D_00372770[0];
    ((u128 *)tb)[1] = D_00372770[1];
    if (n < 0) {
        if (n < -256)
            n = -256;
        n += 256;
        p = (u32 *)(((n & 0xe0) + D_00372790[n & 0x1f]) * 4 + (u32)dst);
        for (i = n; i < 256; i++) {
            *p = c0;
            p += tb[i & 0x1f];
        }
        p = dst;
        f = n;
        i = 0;
    } else {
        if (n >= 256)
            n = 255;
        p = dst;
        for (i = 0; i < n; i++) {
            *p = c1;
            p += tb[i & 0x1f];
        }
        f = 256.0f - n;
        n = 256;
    }
    b.x = ((u8 *)&c1)[0];
    b.y = ((u8 *)&c1)[1];
    b.z = ((u8 *)&c1)[2];
    b.w = ((u8 *)&c1)[3];
    a.x = ((u8 *)&c0)[0];
    a.y = ((u8 *)&c0)[1];
    a.z = ((u8 *)&c0)[2];
    a.w = ((u8 *)&c0)[3];
    func_00267530(&a, &a, &b);
    func_002674b0(&a, &a, f);
    for (; i < n; i++) {
        *p = (u32)b.w << 24 | (u32)b.z << 16 | (u32)b.y << 8 | (u32)b.x;
        func_00267518(&b, &b, &a);
        p += tb[i & 0x1f];
    }
    func_001aa9d0(32);
}

typedef struct { s32 x0; u16 x4; u8 pad6[6]; u8 xc; u8 padd[0xF70 - 0xD]; } BbEnt;
extern BbEnt *D_006257D0; /* src/data/bss_0062.c: u8 *D_006257D0 */
BbEnt *func_001ba9d8(s32);
s32 func_001baad0(void);
void func_001baaa8(s32);
void func_001be820(void *, u32);

s32 func_001bb880(s32 idx) {
    s32 map[16];
    s32 list[10];
    BbEnt *e;
    s32 i, n, j, k;

    e = func_001ba9d8(0);
    k = -1;
    n = 0;
    for (i = 0; i < 10; i++, e++) {
        if (e->x4 == 0)
            map[i] = k;
        else
            map[i] = n++;
    }
    i = func_001baad0();
    if (i >= 0) {
        if (map[i] >= 0)
            func_001baaa8(map[i]);
        else
            func_001baaa8(0);
    }
    e = func_001ba9d8(0);
    for (i = 0; i < 10; i++, e++) {
        if (e->x4 && e->xc)
            e->xc = map[e->xc - 1] + 1;
    }
    if (D_006257D0) {
        e = D_006257D0;
        if (e->x4 && e->xc)
            e->xc = map[e->xc - 1] + 1;
    }
    e = func_001ba9d8(0);
    n = 0;
    for (i = 0; i < 10; i++) {
        if (e[i].x4)
            list[n++] = i;
    }
    for (i = 0; i < 10 && i < n; i++) {
        if (i != list[i])
            e[i] = e[list[i]];
    }
    for (; i < 10; i++)
        func_001be820(&e[i], sizeof(BbEnt));
    e = func_001ba9d8(0);
    for (i = 0; i < 10; i++, e++) {
        if (e->xc) {
            j = e->xc - 1;
            if (j == i || func_001ba9d8(j)->xc - 1 != i)
                e->xc = 0;
        }
    }
    return map[idx];
}

typedef struct { u16 pos; u16 rot; u16 id; u16 x6; u8 pad8[4]; } CdPiece;
typedef struct { s32 x0; u16 n; u8 pad6[0x6A]; CdPiece p[(0xF70 - 0x70) / 12]; } CdEnt;
s32 func_001be6c8(void);
s32 func_001be710(void);
s32 func_001ba3f0(s32);
s32 func_001be680(void);

s32 func_001bcd10(CdEnt *dst, CdEnt *src) {
    s16 cnt[192];
    s32 i, ret, ok, t;
    s32 nc, nb, nd, f, e;

    for (i = 0; i < 192; i++)
        cnt[i] = 0;
    *dst = *src;
    nd = 0;
    dst->n = 0;
    nc = 0;
    nb = 0;
    ret = 0;
    for (i = 0; i < src->n; i++) {
        if (src->p[i].id == 0)
            continue;
        ok = 1;
        t = src->p[i].id - 1;
        e = 0;
        f = 0;
        switch (t) {
        case 4 ... 8:
            if (nb >= func_001be6c8()) {
                ok = 0;
                ret |= 4;
            }
            f = 1;
            break;
        case 58 ... 63:
            if (nc >= func_001be710()) {
                ok = 0;
                ret |= 8;
            }
            e = 1;
            break;
        }
        if (cnt[t] >= func_001ba3f0(t)) {
            ok = 0;
            ret |= 1;
        }
        if (nd >= func_001be680()) {
            ok = 0;
            ret |= 2;
        }
        if (ok) {
            nb += f;
            nc += e;
            cnt[t]++;
            nd++;
            dst->p[dst->n] = src->p[i];
            dst->n++;
        }
    }
    return ret;
}

typedef struct { s32 a, b, c, d, e, f; } C2Ent;
typedef struct {
    u64 pad0 : 32;
    u64 b32 : 1; u64 b33 : 1; u64 b34 : 1; u64 b35 : 2; u64 b37 : 1; u64 b38 : 1; u64 b39 : 1;
    u64 b40 : 1; u64 b41 : 2; u64 b43 : 1; u64 b44 : 2; u64 b46 : 1; u64 b47 : 1;
    u64 b48 : 1; u64 b49 : 1; u64 b50 : 1; u64 b51 : 1; u64 b52 : 1; u64 b53 : 1; u64 b54 : 1; u64 b55 : 1;
    u64 b56 : 1; u64 b57 : 1; u64 b58 : 1; u64 b59 : 1; u64 b60 : 1; u64 b61 : 1; u64 b62 : 1; u64 b63 : 1;
} C2W0;
typedef struct {
    u64 b0 : 1; u64 b1 : 1; u64 b2 : 1; u64 b3 : 1; u64 b4 : 1; u64 b5 : 1; u64 b6 : 1; u64 b7 : 1;
    u64 b8 : 2; u64 b10 : 1; u64 b11 : 1; u64 b12 : 1; u64 b13 : 1; u64 rest : 50;
} C2W1;
typedef struct {
    u8 pad0[0x3070];
    C2W0 w0;
    C2W1 w1;
    u8 pad3080[0xC0];
    s32 x3140;
    u8 pad3144[4];
    s32 x3148;
    u8 pad314c[0];
    f32 x314c;
    u8 pad3150[0x20];
    s32 x3170;
    s32 x3174;
    u8 pad3178[0x208];
    s32 x3380;
    C2Ent ent[8];
} C2Big;
#include "data/pieces/D_0037A378.h"
extern C2Big D_00389C90;

void func_001c29d8(void) {
    s32 i;

    D_00389C90.w0.b32 = 0;
    D_00389C90.w0.b33 = 0;
    D_00389C90.w0.b34 = 0;
    D_00389C90.w0.b37 = 0;
    D_00389C90.w0.b38 = 0;
    D_00389C90.w0.b39 = 0;
    D_00389C90.w0.b40 = 0;
    D_00389C90.w0.b43 = 0;
    D_00389C90.w0.b46 = 0;
    D_00389C90.w0.b47 = 0;
    D_00389C90.w0.b48 = 0;
    D_00389C90.w0.b49 = 0;
    D_00389C90.w0.b50 = 0;
    D_00389C90.w0.b51 = 0;
    D_00389C90.w0.b52 = 0;
    D_00389C90.w0.b53 = 0;
    D_00389C90.w0.b54 = 0;
    D_00389C90.w0.b55 = 0;
    D_00389C90.w0.b56 = 0;
    D_00389C90.w0.b57 = 0;
    D_00389C90.w0.b59 = 1;
    D_00389C90.w0.b60 = 0;
    D_00389C90.w0.b61 = 0;
    D_00389C90.w0.b63 = 0;
    D_00389C90.w1.b0 = 0;
    D_00389C90.w1.b1 = 0;
    D_00389C90.w1.b2 = 0;
    D_00389C90.w1.b3 = 0;
    D_00389C90.w1.b4 = 0;
    D_00389C90.w1.b6 = 0;
    D_00389C90.w1.b7 = 0;
    D_00389C90.w1.b10 = 0;
    D_00389C90.w1.b11 = 0;
    D_00389C90.w1.b12 = 0;
    D_00389C90.w1.b13 = 0;
    D_00389C90.x3148 = -1;
    D_00389C90.x314c = 1.0f;
    D_00389C90.x3170 = 0;
    D_00389C90.x3174 = 0;
    D_00389C90.x3380 = 0;
    D_00389C90.x3140 = 0;
    for (i = 0; i < 8; i++) {
        D_00389C90.ent[i].a = 0;
        D_00389C90.ent[i].b = -1;
        D_00389C90.ent[i].c = -1;
        D_00389C90.ent[i].e = 1;
        D_00389C90.ent[i].d = 0;
        D_00389C90.ent[i].f = -1;
    }
    (*(Bits_37a378 *)&D_0037A378).b1 = 0;
    (*(Bits_37a378 *)&D_0037A378).b5 = 0;
}
#include "data/data_0037.h"
