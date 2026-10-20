#include "common.h"
#include "data/bss_0065.h"

extern s32 D_00648038[];

s32 func_002366d8(s32 i, s32 n) {
    s32 v = ((s64)D_00648038[i] * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    D_00648038[i] = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}

s32 func_002367f8(s32 *p, s32 n) {
    s32 v = ((s64)*p * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    *p = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}

typedef int u128 __attribute__((mode(TI)));
s32 func_00266c08(s32);
void func_00266f38(s32, u32);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);

void func_00237018(u128 *p, s32 n, s32 wait) {
    s32 ch;
    u32 hi = 0x80000000;
    n--;
    if (n > 0) {
        *p = 0;
        *(s32 *)p = n | 0x70000000;
        if ((u32)p < 0x70000000) {
            hi = 0;
        }
        ch = func_00266c08(2);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        func_00266f38(ch, (u32)p | hi);
        if (wait) {
            do {
                sceGsSyncPath(0, 0);
            } while (0);
        }
    }
}


typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
void func_002672f8(V4 *, void *, V4 *);
void func_002674d0(V4 *, V4 *, f32);
s32 func_00267ef0(V4 *, V4 *, V4 *);

void func_00237548(V4 *a, V4 *b, V4 *c, void *m) {
    V4 v[3];
    func_002672f8(&v[0], m, a);
    func_002672f8(&v[1], m, b);
    func_002672f8(&v[2], m, c);
    func_002674d0(&v[0], &v[0], v[0].w);
    func_002674d0(&v[1], &v[1], v[1].w);
    func_002674d0(&v[2], &v[2], v[2].w);
    func_00267ef0(&v[0], &v[1], &v[2]);
}


typedef struct { s32 x, y, z, w; } I4;

f32 func_00237a48(I4 *out, void *m, V4 *in, s32 raw) {
    V4 v;
    f32 r;
    func_002672f8(&v, m, in);
    r = 1.0f / v.w;
    v.x *= r;
    v.y *= r;
    v.z *= r;
    if (raw == 0) {
        out->x = v.x * 16.0f;
        out->y = v.y * 16.0f;
        out->z = v.z * 16.0f;
        out->w = v.w * 16.0f;
    } else {
        out->z = v.z;
        out->x = v.x * 16.0f;
        out->y = v.y * 16.0f;
        out->w = v.w;
    }
    return r;
}

typedef struct { u128 q[5]; } Item;
void func_00267da0(u128 *, void *, u128 *, s32, s32);

u128 *func_00237790(Item *src, u128 *dst, void *m) {
    u128 out[2];
    V4 a, b;
    u128 *h;
    func_002672f8(&a, m, (V4 *)&src->q[1]);
    func_002672f8(&b, m, (V4 *)&src->q[2]);
    func_002674d0(&a, &a, a.w);
    func_002674d0(&b, &b, b.w);
    if (func_00267ef0(&a, &b, &b)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0x4004C00000008001;
    ((u64 *)h)[1] = 0x5151;
    func_00267da0(out, m, &src->q[1], 2, 1);
    dst[2] = src->q[3];
    dst[3] = out[0];
    dst[4] = src->q[4];
    dst[0] = 0;
    dst[5] = out[1];
    *(s32 *)dst = 0x10000005;
    return dst + 6;
}

void func_002386c0(u128 *src, s32 n, u128 *buf) {
    s32 k = 2;
    s32 i;
    u64 t;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 6;
        d[0] = src[i * 6 + 0];
        d[1] = src[i * 6 + 1];
        d[2] = src[i * 6 + 2];
        d[3] = src[i * 6 + 3];
        d[4] = src[i * 6 + 4];
        d[5] = src[i * 6 + 5];
    }
    buf[1] = 0;
    ((u64 *)&buf[1])[1] = 0x43413E;
    t = n | 0x8000;
    t |= (u64)0x60AB4000 << 32;
    ((u64 *)&buf[1])[0] = t;
    func_00237018(buf, k, 1);
}

u128 *func_002388b8(u128 *src, s32 n, u128 *buf) {
    s32 k = 1;
    u64 *e;
    s32 i;
    u64 t;
    buf[0] = 0;
    t = (n * 2) | 0x8000;
    t |= (u64)0xC0ADC000 << 32;
    ((u64 *)buf)[0] = t;
    ((u64 *)buf)[1] = 0x413413413EEE;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 24;
        ((u64 *)d)[0] = 0;
        ((u64 *)d)[1] = 63;
        d[1] = src[i * 14 + 0];
        d[2] = src[i * 14 + 1];
        d[3] = src[i * 14 + 2];
        d[4] = src[i * 14 + 6];
        d[5] = src[i * 14 + 10];
        d[6] = src[i * 14 + 3];
        d[7] = src[i * 14 + 7];
        d[8] = src[i * 14 + 11];
        d[9] = src[i * 14 + 4];
        d[10] = src[i * 14 + 8];
        d[11] = src[i * 14 + 12];
        e = (u64 *)&d[12];
        e[0] = 0;
        e[1] = 63;
        d[13] = src[i * 14 + 0];
        d[14] = src[i * 14 + 1];
        d[15] = src[i * 14 + 4];
        d[16] = src[i * 14 + 8];
        d[17] = src[i * 14 + 12];
        d[18] = src[i * 14 + 3];
        d[19] = src[i * 14 + 7];
        d[20] = src[i * 14 + 11];
        d[21] = src[i * 14 + 5];
        d[22] = src[i * 14 + 9];
        d[23] = src[i * 14 + 13];
    }
    return buf + k;
}

typedef struct { u8 r, g, b, a; } Rgba;
typedef struct { u8 pad[4]; u16 x4; } Res;
extern f32 D_00650DD0;
extern s32 D_006488F0;
Res *func_001478c8(s32);
s32 func_00147808(s32);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);

void func_00239558(s32 id, s32 x, s32 y, s32 c) {
    Rgba col;
    u8 v = c;
    col.r = v;
    col.g = v;
    col.b = v;
    col.a = D_00650DD0 * 128.0f;
    D_006488F0 = func_001f0638(D_006488F0, 1, *(s32 *)&col, ((x * 16 + 0x7100) >> 4) - 0x700,
                               ((y * 16 + 0x7420) >> 4) - 0x740, func_00147808(func_001478c8(id)->x4));
}

typedef struct Pk74 { struct Pk74 *next; s32 type; } Pk74;
typedef struct { Pk74 *head; s32 pad; } Bk74;
typedef struct { s32 bits; Bk74 *tbl; } Ht74;
s32 *func_002378c8(Pk74 *, s32 *, s32);
s32 *func_00237d48(Pk74 *, s32 *, s32);
s32 *func_00237ec0(Pk74 *, s32 *, s32);

void func_002380c0(Ht74 *h, s32 *b0, s32 *b1, s32 a3, s32 a4) {
    s32 *buf = b0;
    s32 n = 1 << h->bits;
    Bk74 *bk = h->tbl;
    s32 *r, *q, *prev, *last;
    Pk74 *p;
    s32 i;
    for (i = 0; i < n; i++, bk++) {
        last = 0;
        if (bk->head != 0) {
            p = bk->head;
            r = buf;
            do {
                prev = r;
                if (p->type == 2) r = func_002378c8(p, r, a4);
                else if (p->type == 1) r = (s32 *)func_00237790((Item *)p, (u128 *)r, (void *)a4);
                else if (p->type == 3) r = func_00237d48(p, r, a4);
                else if (p->type == 4) r = func_00237ec0(p, r, 0);
                if (prev != r) last = prev;
                if (p->next == 0) break;
                p = p->next;
            } while (1);
            if (r != buf) {
                *last |= 0x70000000;
                q = (s32 *)func_00266c08(2);
                *q |= 0x40;
                FlushCache(0);
                sceGsSyncPath(0, 0);
                func_00266f38((s32)q, (u32)buf);
                buf = (buf == b0) ? b1 : b0;
            }
        }
    }
    sceGsSyncPath(0, 0);
}
#include "data/bss_0064_mixed.h"
