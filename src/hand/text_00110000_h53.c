#include "common.h"
#include "data/bss_004F.h"

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V53;

static inline f32 w53_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void w53_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w53_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

void func_0011a978(s32, s32, V53 *);
void func_0011a9c8(s32, s32, V53 *);

s32 func_0011bfc8(s32 a0, s32 a1, void *p0, void *dir, void *out) {
    V53 n, p;
    f32 den, t;
    func_0011a978(a0, a1, &n);
    den = w53_dot(&n, dir);
    if (den >= 0.0f) return 0;
    func_0011a9c8(a0, a1, &p);
    t = (w53_dot(&n, &p) - w53_dot(&n, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w53_scale(out, dir, t);
    w53_add(out, out, p0);
    return 1;
}

extern f32 D_002C5980[4];
extern f32 D_002C5C20;
f32 func_00120bf8(void *);
void func_002673b8(void *, void *);
void func_00267560(void *, void *, f32);

s32 func_0011f370(V53 *st, u8 *pad) {
    s32 bits = 0;
    s32 s, j;
    f32 v, len;
    V53 *d = st;
    for (s = 0; s < 2; s++) {
        for (j = 0; j < 2; j++) {
            v = (f32)pad[s * 2 + 2 + j] - 127.5f;
            D_002C5980[j] = v;
            if (v > 0.0f) {
                D_002C5980[j] = v - D_002C5C20;
                if (D_002C5980[j] < 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 1) << (s * 8 + 21 - j);
                }
            } else {
                D_002C5980[j] = v + D_002C5C20;
                if (D_002C5980[j] > 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 4) << (s * 8 + 21 - j);
                }
            }
            D_002C5980[j] = D_002C5980[j] / (127.5f - D_002C5C20);
        }
        len = func_00120bf8(D_002C5980);
        if (len > 1.0f) len = 1.0f;
        func_002673b8(&d[5], D_002C5980);
        d[5].w = 1.0f;
        func_00267560(&d[3], &d[5], len);
        d++;
    }
    return bits;
}

typedef struct { u64 a, b; } Q53;
Q53 *func_0011fb38(s32, u64, Q53 *);
void func_0011fb48(Q53 *, s32, Q53 *);
void func_0011fb78(Q53 *, s32, Q53 *);

Q53 *func_0011fbb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7, s32 a8, Q53 *buf) {
    Q53 *p, *r, *t;
    t = buf + 1;
    p = func_0011fb38(0x50, (u64)a0 << 32 | (u64)a1 << 48 | (u64)a2 << 56, buf + 2);
    p = func_0011fb38(0x51, (u64)a3 << 32 | (u64)a4 << 48, p);
    p = func_0011fb38(0x52, (u64)a5 | (u64)a6 << 32, p);
    p = func_0011fb38(0x53, 0, p);
    func_0011fb48(t, 0, p);
    t = p;
    p++;
    t->a = (u64)a7 | 0x8000ULL << 44;
    func_0011fb78(buf, 1, p);
    r = p;
    p++;
    r->a = (u64)(a7 | 0x30000000) | (u64)a8 << 32;
    r = p++;
    t = p++;
    p = func_0011fb38(63, 0, p);
    func_0011fb48(t, 1, p);
    func_0011fb78(r, 7, p);
    return r;
}

typedef struct {
    u32 b0 : 1;
    u32 comp : 1;
    u32 r : 30;
    u8 pad4[32];
    u32 lsn;
    u32 size;
    u8 *buf;
    u32 result;
} CdReq53;
typedef struct { u32 b0 : 1; u32 b1 : 1; u32 b2 : 1; u32 r : 29; } F5968;
extern volatile F5968 D_002C5968;
extern char D_0048D260[];
extern u32 D_002C5B44;
extern void (*D_0046A6A8)(s32);
extern u32 D_004F3200;
s32 func_0025b588(char *, s32);
s32 func_0025b990(s32, s32, s32);
s32 func_0025bbc8(s32, u8 *, s32);
s32 func_0025b810(s32);
void FlushCache(s32);
u32 func_00120040(u8 *, u32);
void func_0010c150(void);
void func_002193e0(s32);
void func_001201d0(CdReq53 *);
void func_0010c170(void (*)(CdReq53 *), CdReq53 *);
void func_0010c1b8(void (*)(CdReq53 *));

void func_001202c0(CdReq53 *r) {
    s32 err = 0;
    s32 fd, left, n;
    fd = func_0025b588(D_0048D260, 1);
    if (fd >= 0) {
        if (!(D_002C5B44 & 0x2000)) {
            func_0025b990(fd, r->lsn << 11, 0);
            goto rd;
        }
        err = 1;
        goto out;
    }
    err = 1;
    goto out;
rd:
    n = 0;
    left = r->size;
    while (left > 0) {
        n = func_0025bbc8(fd, r->buf, left);
        if (n < 0) {
            err = 1;
            break;
        }
        left -= n;
    }
    func_0025b810(fd);
    if (err == 0) {
        if (r->comp) {
            FlushCache(0);
            n = func_00120040(r->buf, r->size);
        }
        r->result = n;
    }
out:
    if (err) {
        D_0046A6A8(4);
        D_002C5968.b2 = 1;
        do func_0010c150(); while (D_002C5968.b2);
        func_002193e0(0);
        r->lsn += D_004F3200;
        func_0010c170(func_001201d0, r);
    }
    func_0010c1b8(func_001202c0);
}

void func_00267530(V53 *, V53 *, V53 *);
void func_00267518(V53 *, V53 *, V53 *);
void func_002674f0(V53 *, V53 *, V53 *, f32);
void func_00121fc4(V53 *, V53 *);

s32 func_00121168(V53 *out, V53 *a, V53 *b, f32 t) {
    V53 q, d1, d2, x, y;
    func_00267530(&d1, &a[1], &a[0]);
    func_00267530(&d2, &b[1], &b[0]);
    func_00267560(&x, &d1, ((b->y - a->y) + d2.y * (b->x - a->x)) / (d2.x * d1.y - d2.y * d1.x));
    func_00267518(&x, &x, a);
    func_00267530(&d1, a, &x);
    func_00121fc4(&d1, &d1);
    func_00267530(&d2, b, &x);
    func_00121fc4(&d2, &d2);
    func_002674f0(&q, &d2, &d1, t);
    func_002673b8(&q, &q);
    func_00267560(&y, &q, d1.w + (d2.w - d1.w) * t);
    func_00267518(&out[0], &x, &y);
    out[0].w = 1.0f;
    func_00267530(&d1, &a[1], &x);
    func_00121fc4(&d1, &d1);
    func_00267530(&d2, &b[1], &x);
    func_00121fc4(&d2, &d2);
    func_002674f0(&q, &d2, &d1, t);
    func_002673b8(&q, &q);
    func_00267560(&y, &q, d1.w + (d2.w - d1.w) * t);
    func_00267518(&out[1], &x, &y);
    out[1].w = 1.0f;
    return 1;
}

extern s32 D_002BC128, D_002BC130, D_002BC134;
extern u32 D_002C5958;
extern s32 D_002C5C4C, D_002C5C50, D_002C5C54;
void func_0012b738(void);
void func_00124b90(void);
void func_00142030(void);
void func_001561b0(void);
void func_00132c70(s32, s32);
void func_00133520(void);
void func_00146590(void);
void func_00151808(void);
void func_001356a8(void);
void func_0014c378(void);
void func_0012ff80(void);
void func_00122cf0(void);
void func_00134718(void);
void func_0013bd08(void);
void func_0012ea38(void);

void func_00122198(s32 a0, s32 a1) {
    D_002C5958 = 0;
    if (D_002BC128 == 16 && (D_002BC130 == 26 || D_002BC130 == 33 || D_002BC130 == 34)) {
        *(volatile u32 *)&D_002C5958 |= 0x20;
    }
    D_002C5C4C = D_002BC128 == 9 || (D_002BC128 == 16 && D_002BC130 == 21);
    D_002C5C50 = D_002BC128 == 10 || (D_002BC128 == 16 && D_002BC130 == 22);
    D_002C5C54 = D_002BC128 == 15 && D_002BC134 == 10;
    func_0012b738();
    func_00124b90();
    func_00142030();
    func_001561b0();
    func_00132c70(a0, a1);
    func_00133520();
    func_00146590();
    func_00151808();
    func_001356a8();
    func_0014c378();
    func_0012ff80();
    func_00122cf0();
    func_00134718();
    func_0013bd08();
    func_0012ea38();
}

typedef struct { s32 type; u32 flags; u8 pad8[4]; f32 radius; V53 pos; f32 dir[4]; V53 col; } Light53;
extern Light53 D_002C5C80[];
extern f32 D_002C5910[4][4];
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
f32 func_00267390(f32 *, V53 *);
float cosf(float);

void func_00122770(u8 *o, V53 *pos, f32 m[4][4]) {
    V53 d;
    Light53 *l;
    s32 i, j, n;
    f32 dot, r;
    n = 0;
    sceVu0CopyMatrix(m, D_002C5910);
    l = D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (!(*(u32 *)(o + 0x420) & (1 << i))) continue;
        switch (l->type) {
        case 2:
            for (j = 0; j < 3; j++) m[j][n] = -l->dir[j];
            n++;
            break;
        case 3:
            func_00267530(&d, &l->pos, pos);
            func_00121fc4(&d, &d);
            if (d.w < l->radius) {
                func_00267560(&d, &d, cosf(d.w / l->radius * 3.1415928f * 0.5f));
                for (j = 0; j < 3; j++) m[j][n] = ((f32 *)&d)[j];
            }
            n++;
            break;
        case 4:
            func_00267530(&d, &l->pos, pos);
            func_00121fc4(&d, &d);
            dot = -func_00267390(l->dir, &d);
            r = l->radius;
            if (r < dot) {
                func_00267560(&d, &d, (dot - r) / (1.0f - r));
                for (j = 0; j < 3; j++) m[j][n] = ((f32 *)&d)[j];
            }
            n++;
            break;
        }
    }
    m[3][3] = 1.0f;
}

typedef struct { u8 pad[0x130]; u8 *name; } Obj53;
extern s32 D_002C648C;
char D_004F7150[0x4][32] ALIGNED(16);
extern char *D_002C6460[];
extern char D_0048D320[], D_0048D328[], D_0048D330[];
extern u8 D_00491A18[];
Obj53 *func_00123488(u32);
u8 *func_001320a8(u32);
int sprintf(char *, const char *, ...);
u32 strlen(const char *);

static inline s32 w53_toupper(s32 c) {
    return ((D_00491A18 + 1)[c] & 2) ? c - 32 : c;
}

char *func_00122dc8(u32 id, char *buf) {
    Obj53 *o = func_00123488(id);
    u8 *p;
    s32 n, i;
    char c;
    if (o) {
        p = o->name;
    } else {
        p = func_001320a8(id);
    }
    if (!buf) {
        buf = D_004F7150[D_002C648C];
        D_002C648C = (D_002C648C + 1) % 4;
    }
    if (p) {
        sprintf(buf, D_0048D320, D_002C6460[(id >> 16) & 0xff], p + 104);
    } else if (((id >> 16) & 0xff) < 11) {
        sprintf(buf, D_0048D328, D_002C6460[(id >> 16) & 0xff], id);
    } else {
        sprintf(buf, D_0048D330, (id >> 16) & 0xff, id);
    }
    n = strlen(buf);
    for (i = 0; i < n; i++) {
        buf[i] = w53_toupper(buf[i]);
    }
    return buf;
}

typedef struct { u8 pad[4]; u32 flags; } Info8;
typedef struct {
    u64 lo : 44;
    u64 b44 : 1;
    u64 b45 : 1;
    u64 b46 : 1;
    u64 hi : 17;
} F370;
typedef struct Act53 {
    u8 pad0[0x10];
    V53 pos;
    V53 rot;
    f32 x30, x34, x38, x3c;
    u8 pad40[0x10];
    V53 prev;
    u8 pad60[0x60];
    f32 xc0;
    f32 xc4;
    f32 xc8;
    f32 xcc;
    u8 padd0[0x50];
    V53 x120;
    Info8 *info;
    u8 pad134[0x1c];
    f32 x150;
    u8 pad154[0x14c];
    V53 x2a0;
    u8 pad2b0[0xa0];
    s32 col[4];
    u8 pad360[0x10];
    F370 f;
    u8 pad378[0x26];
    u8 x39e;
    u8 pad39f[0x11];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
} Act53;
typedef struct {
    union { u32 w; u64 d; struct { u64 lo : 16; u64 b16 : 1; u64 hi : 47; } b; } u;
    u8 pad8[0x88];
    Act53 *owner;
} Ent53;
extern V53 D_002C58A0;
void func_002675a8(V53 *, V53 *);
f32 func_00120c88(f32);
float sinf(float);
float cosf(float);
void func_00136d38(Act53 *);
void func_00116660(V53 *);
Ent53 *func_0014a398(Ent53 *);

void func_001238d0(Act53 *o, V53 *p) {
    Ent53 *e;
    f32 a;
    func_002675a8(&o->pos, p);
    o->pos.w = 1.0f;
    func_002675a8(&o->prev, &o->pos);
    if (!((*(u64 *)&o->f >> 44) & 1)) {
        a = func_00120c88(p->w);
        o->x30 = sinf(a);
        o->x34 = 0.0f;
        o->x38 = cosf(a);
        o->x150 = a;
        o->x3c = a;
        func_002675a8(&o->rot, (V53 *)&o->x30);
    }
    o->rot.w = 0.0f;
    o->x3b4 = p->y;
    o->x3b0 = 0.0f;
    o->x3b8 = 0.0f;
    o->x3bc = 0.0f;
    o->xc0 = 0.0f;
    o->xc4 = 1.0f;
    o->xcc = 1.0f;
    o->xc8 = 0.0f;
    func_00136d38(o);
    func_002675a8(&o->x2a0, &o->pos);
    func_00116660(&o->x2a0);
    if (!(o->info->flags & 0x40000)) {
        o->col[3] = 128;
        o->col[2] = 128;
        o->col[1] = 128;
        o->col[0] = 128;
    }
    o->x39e = 0;
    o->f.b46 = 0;
    func_002675a8(&o->x120, &D_002C58A0);
    for (e = 0; (e = func_0014a398(e)) != 0;) {
        if (e->owner == o && (e->u.w & 3) == 1) e->u.b.b16 = 0;
    }
}

typedef f32 M53[4][4] __attribute__((aligned(16)));
extern f32 D_004F7650, D_002E27A4, D_004F77E0;
extern V53 D_002E2780, D_002E2790, D_002E26B0;
extern s32 D_002C5950;
extern M53 D_004F76E0[], D_004F7760[], D_004F7660[];
extern M53 D_002E2700, D_002E2740, D_002E26C0, D_002BBE20;
extern f32 (*D_002E27AC)[4];
void func_00110a48(f32);
void func_00120cf8(V53 *, f32 (*)[4], f32);
void func_002672f8(V53 *, f32 (*)[4], V53 *);
void func_00267930(f32 (*)[4], V53 *, V53 *, V53 *);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_00110ba8(void);
f32 func_00124d28(V53 *, V53 *);

s32 func_00125000(void) {
    V53 d, r;
    M53 m;
    func_00110a48(D_004F7650);
    func_00267530(&d, &D_002E2790, &D_002E2780);
    func_002673b8(&d, &d);
    func_00120cf8(&d, m, func_00120c88(D_002E27A4));
    func_002672f8(&r, m, &D_002E26B0);
    func_00267930(D_004F76E0[D_002C5950], &D_002E2780, &d, &r);
    sceVu0CopyMatrix(D_002E2700, D_004F76E0[D_002C5950]);
    sceVu0CopyMatrix(D_004F7760[D_002C5950], D_002BBE20);
    sceVu0CopyMatrix(D_002E2740, D_004F7760[D_002C5950]);
    sceVu0MulMatrix(D_004F7660[D_002C5950], D_002E2740, D_002E2700);
    sceVu0CopyMatrix(D_002E26C0, D_004F7660[D_002C5950]);
    D_002E27AC = D_004F7660[D_002C5950];
    func_00110ba8();
    D_004F77E0 = func_00124d28(&D_002E2780, &D_002E2790);
    return 0;
}

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
typedef struct { s16 id; u8 pad[18]; } E7810;
extern E7810 *D_004F7810;
typedef struct { u32 lo : 25; u32 b25 : 1; u32 hi : 6; } F27c8;
extern F27c8 D_002E27C8;
void func_0012ec60(s32, s32, V53 *);

s32 func_00126838(u8 *o, s32 *a, V53 *v) {
    s32 t[68];
    s32 i;
    for (i = 15; i < 19; i++) t[i] = 0;
    if (!(FLD(u8, FLD(u8 *, o, 0x14c), 0x29) < FLD(u8, FLD(u8 *, o, 0x6c), 0xd1))) t[16] = 1;
    if (a[0]) {
        func_0012ec60(a[0], a[1], v);
        func_00267530(v, v, (V53 *)(o + 0x10));
        if (v->y < -100.0f) {
            t[17] = 1;
        } else {
            t[18] = 1;
            if (FLD(s32, o, 0x70) == 2 && D_002E27C8.b25) t[15] = t[16];
        }
        v->y = 0.0f;
    } else {
        t[18] = 1;
    }

    for (i = 15; i < 19; i++) {
        if (t[i] > 0 && D_004F7810[i].id != FLD(s32, o, 0x164)
) return i;
    }
    for (i = 18; i >= 15; i--) {
        if (D_004F7810[i].id != FLD(s32, o, 0x164)
) return i;
    }
    return 18;
}

void *memset(void *, s32, u32);
typedef struct { u8 type; u8 pad1[2]; s8 flag; s32 a, b; } C3190b;
extern C3190b D_002E3190;
extern u8 D_002C5BB0[];
extern V53 D_004F7800;
extern s32 (*D_002E27D4)(u8 *, u8 *, V53 *);
s32 func_00137618(u8 *, V53 *);
void func_00124e08(u8 *o, u8 *p, V53 *out);
void func_00126f18(u8 *, u8 *, V53 *);
u8 *func_0013dfb8(u8 *, V53 *);
void func_00126c10(u8 *, V53 *);
void func_001586a8(s32);

void func_001271b0(u8 *o, V53 *v) {
    V53 s;
    u8 *p;
    if (func_00137618(o, v)) {
        func_00124e08(o, D_002C5BB0, v);
        func_002675a8(&D_004F7800, v);
        if (D_002E27D4) {
            if (D_002E27D4(o, D_002C5BB0, v)) func_00126f18(o, D_002C5BB0, v);
        } else {
            func_00126f18(o, D_002C5BB0, v);
        }
    }
    if (D_002E3190.flag & 1) {
        if ((FLD(s32, o, 0x164) == 7 || FLD(s32, o, 0x164) == 12) && (FLD(s32, o, 0x70) == 0 || FLD(s32, o, 0x70) == 12)) {
            FLD(u32, o, 0) &= ~4;
            func_002675a8(&s, &D_002C58A0);
            p = func_0013dfb8(o, &s);
            if (p) FLD(f32, o, 0x3b0) = FLD(f32, p, 4) = 2.0f;
        }
    } else if (D_002E3190.type) {
        func_00126c10(o, v);
    }
    memset(&D_002E3190, 0, 12);
    p = FLD(u8 *, o, 0x14c);
    if (p && FLD(u8 *, p, 0x2c) && (FLD(u32, FLD(u8 *, p, 0x2c), 4) & 1)) func_001586a8(11);
}

/* needs make: uses rodata */
extern V53 D_002C5C70;
void func_002675a8(V53 *, V53 *);
void func_00267548(V53 *, V53 *, V53 *);

void func_00122588(u8 *o) {
    V53 *acc = (V53 *)(o + 0x430);
    V53 d;
    Light53 *l;
    s32 i;
    u32 mask = 0;
    f32 dist, r;
    func_002675a8(acc, &D_002C5C70);
    l = D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (l->flags & 0x11) continue;
        switch (l->type) {
        case 1:
            func_00267548(acc, acc, &l->col);
            break;
        case 2:
            mask |= 1 << i;
            break;
        case 3:
            mask |= 1 << i;
            break;
        case 4:
            mask |= 1 << i;
            break;
        case 5:
            func_00267530(&d, (V53 *)(o + 0x10), &l->pos);
            dist = func_00120bf8(&d);
            r = l->radius;
            if (dist < r) {
                func_002674f0(&d, &l->col, &D_002C5C70, cosf(dist / r * 3.1415928f * 0.5f));
                func_00267548(acc, acc, &d);
            }
            break;
        }
    }
    *(u32 *)(o + 0x420) = mask;
}

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
extern s32 D_002E27A8;
extern f32 D_002C58D0[4][4];
extern V53 D_002C58A0;
extern f32 D_004F77E0;
void func_00267810(f32 (*)[4], f32 (*)[4], f32);
void func_00124d58(V53 *, V53 *, f32, f32);

void func_00124e08(u8 *o, u8 *p, V53 *out) {
    f32 m[4][4];
    V53 v;
    switch (D_002E27A8) {
    case 2:
        func_00267810(m, D_002C58D0, FLD(f32, p, 0x40) * 0.0523598762229085f);
        func_002672f8(out, m, (V53 *)(o + 0x30));
        out->y = out->w = 0.0f;
        return;
    case 11:
        if (FLD(f32, p, 0x44) <= 0.0f) {
            func_00267810(m, D_002C58D0, FLD(f32, p, 0x40) * 0.0523598762229085f);
            func_002672f8(out, m, (V53 *)(o + 0x20));
            out->y = 0.0f;
            func_002673b8(out, out);
            out->w = -FLD(f32, p, 0x44);
            return;
        }
        if ((FLD(u32, p, 8) & 0x400000) && FLD(f32, p, 0x40) == 0.0f) {
            func_00267530(out, &D_002C58A0, (V53 *)(o + 0x20));
        } else {
            func_002675a8(out, o + 0x20);
        }
        out->y = 0.0f;
        func_002673b8(out, out);
        out->w = 0.0f;
        return;
    }
    func_002675a8(&v, p + 0x60);
    switch (FLD(s32, o, 0x70)) {
    case 10:
    case 13:
    case 15:
        break;
    case 18:
        v.y = 0.0f;
        break;
    case 29:
        func_002675a8(out, &v);
        out->w = FLD(f32, p, 0x4c);
        return;
    default:
        v.z = v.y;
        v.y = 0.0f;
        break;
    }
    func_00124d58(&v, out, D_004F77E0, FLD(f32, p, 0x4c));
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
/* D_0046A6A8 stays extern: the dktitle.x overlay also writes it (two %lo fields), so it is shared. */
extern u8 D_0048D2C8[];
extern u8 D_0048D2D0[];
extern u8 D_0048D2D8[];
extern u8 D_0048D2E0[];
extern u8 D_0048D2E8[];
extern u8 D_0048D2F0[];
extern u8 D_0048D2F8[];
extern u8 D_0048D300[];
extern u8 D_0048D308[];
extern u8 D_0048D310[];
extern u8 D_0048D318[];
char *D_002C6460[0xb] ALIGNED(16) = {
    (void *)D_0048D318, (void *)D_0048D310, (void *)D_0048D308, (void *)D_0048D300,
    (void *)D_0048D2F8, (void *)D_0048D2F0, (void *)D_0048D2E8, (void *)D_0048D2E0,
    (void *)D_0048D2D8, (void *)D_0048D2D0, (void *)D_0048D2C8,
};
