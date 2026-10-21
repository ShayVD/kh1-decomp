#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */

typedef struct {
    u8 lv;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 pad04[0x38 - 0x4];
    s16 x38;
    u8 pad3a[2];
    s32 exp;
    u8 name[0x30];
    u8 bits;
    u8 pad71[3];
} W7Member;

typedef struct {
    u8 pad000[4];
    W7Member m[10];
    u8 x48c;
    u8 x48d;
    u8 party[4];
    u8 pad492[0x599 - 0x492];
    u8 list599[0x30];
    u8 pad5c9[0x5CC - 0x5C9];
    u32 bits5cc[(0x7D0 - 0x5CC) / 4];
    s8 x7d0[7];
    u8 pad7d7[0x844 - 0x7D7];
    s8 x844[3];
    u8 pad847[0x878 - 0x847];
    u64 x878;
} W7Save;

extern W7Save *D_00304BE8;

extern u16 *D_00304BB0[];
extern u16 *D_00304B88[];
void *func_001477c8(void *p);
void func_00141b10(s32 c, u8 *buf);
void *memcpy(void *, const void *, u32);

s32 func_0013c188(s32 i, s32 b) {
    W7Member *m = D_00304BE8->m;
    return (m[i].bits >> b) & 1;
}

void func_0013c2a0(s32 b, s32 on) {
    if (on) {
        D_00304BE8->x878 |= (u64)1 << b;
    } else {
        D_00304BE8->x878 &= ~((u64)1 << b);
    }
}

s32 func_0013c318(s32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->party[i] == v) {
            return i;
        }
    }
    return -1;
}

s32 func_0013c360(s32 v) {
    s32 i;
    for (i = 0; i < 7; i++) {
        if (D_00304BE8->x7d0[i] == v) {
            return 1;
        }
    }
    return 0;
}

void func_0013c3a8(s32 v) {
    s32 i;
    for (i = 0; i < 7; i++) {
        if (D_00304BE8->x7d0[i] == v) {
            return;
        }
        if (D_00304BE8->x7d0[i] == -1) {
            D_00304BE8->x7d0[i] = v;
            return;
        }
    }
}

u16 *func_0013c3f8(s32 i) {
    W7Save *s = D_00304BE8;
    u16 *r;
    if (i == 0) {
        r = func_001477c8(D_00304BB0[s->x48d]);
    } else {
        r = func_001477c8(D_00304B88[i]);
    }
    return r;
}

s32 func_0013c598(s32 i) {
    u16 *p;
    s32 e;
    if (D_00304BE8->m[i].lv >= 100) {
        return 0;
    }
    p = func_0013c3f8(i);
    e = D_00304BE8->m[i].exp;
    while (e >= 0) {
        e -= *p++;
    }
    return -e;
}

void func_0013c638(u32 i, s32 on) {
    if (on) {
        D_00304BE8->bits5cc[i >> 2] |= 1 << (i & 3);
    } else {
        D_00304BE8->bits5cc[i >> 2] &= ~(1 << (i & 3));
    }
}

void func_0013c6d8(void) {
    u8 buf[0xF0];
    s32 i;
    for (i = 0; i < 4; i++) {
        u8 c = D_00304BE8->party[i];
        if (c != 0xFF) {
            W7Member *m = &D_00304BE8->m[c];
            func_00141b10(c, buf);
            m->x1 = buf[64];
            m->x3 = buf[72];
            m->x38 = 0;
        }
    }
}

void func_0013c778(u32 a, u32 b, u32 c) {
    D_00304BE8->party[1] = a < 10 ? a : -1;
    D_00304BE8->party[2] = b < 10 ? b : -1;
    D_00304BE8->party[3] = c < 10 ? c : -1;
}

void func_0013c7d8(u32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->party[i] == v) {
            return;
        }
        if (D_00304BE8->party[i] == 0xFF) {
            if (v < 10) {
                D_00304BE8->party[i] = v;
            } else {
                D_00304BE8->party[i] = -1;
            }
            return;
        }
    }
}

void func_0013c840(u32 v) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->party[i] == v) {
            for (j = i; j < 3; j++) {
                D_00304BE8->party[j] = D_00304BE8->party[j + 1];
            }
            D_00304BE8->party[j] = -1;
            return;
        }
    }
}

void func_0013c8c8(s32 c, u32 k) {
    u8 *p;
    s32 i;
    if (k < 10) {
        p = D_00304BE8->m[k].name;
    } else {
        p = D_00304BE8->list599;
    }
    i = 0;
    while (p[i] != 0) {
        i++;
        if (i >= 48) return;
    }
    p[i] = c | 0x80;
}

s32 func_0013c968(s32 c, u32 k) {
    u8 *p;
    s32 n;
    if (k < 10) {
        p = D_00304BE8->m[k].name;
    } else {
        p = D_00304BE8->list599;
    }
    n = 0;
    while (*p) {
        if (*p++ == c) n++;
    }
    return n;
}

typedef struct {
    u8 pad00[8];
    union {
        u32 *p;
        u32 v;
    } u;
} W7Stack;


u32 func_0013cf28(W7Stack *q, void *dst) {
    u32 n = *--q->u.p;
    q->u.p -= n >> 2;
    memcpy(dst, q->u.p, n);
    return n;
}

u32 func_0013cfc0(W7Stack *q) {
    u32 n = *--q->u.p;
    q->u.p -= n >> 2;
    return n;
}

typedef struct {
    u8 pad00[0x48];
    s16 x48;
    s16 x4a;
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
    u8 pad55[0x5D - 0x55];
    u8 x5d;
} W7Info;

typedef struct W7Obj W7Obj;
struct W7Obj {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W7Info *info;
    u8 pad134[0x398 - 0x134];
    W7Obj *x398;
};

extern W7Obj *D_002E26A0[];
s32 func_00137618(W7Obj *o);
s32 func_00130030(W7Obj *o);

s32 func_0013daa8(u32 id) {
    s32 i;
    for (i = 0; i < 3; i++) {
        W7Obj *o = D_002E26A0[i];
        if (o && o->info->x4c == id) {
            return i;
        }
    }
    return -1;
}

s32 func_0013db30(W7Obj *o) {
    s32 r = 0;
    W7Obj *p;
    if (func_00137618(o) || func_00130030(o)) {
        p = o->x398;
        if (p == 0 || (p = p->x398) == 0 || p->info->x54 != 10) {
            r = 1;
        }
    }
    return r;
}

#include "data/types/text_00130000_h7.h"



extern W7Fn D_00350DA4[];
extern void *D_00304C18[];
extern void *D_0052AE70[];
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_00121fc4(f32 *d, f32 *s);
f32 func_00267390(f32 *a, f32 *b);
f32 fmodf(f32, f32);
void func_0014cc88(W7Ob *o, f32 f);
void func_00267560(f32 *d, f32 *s, f32 f);
extern f32 D_002C5970;
typedef struct {
    u8 pad[0xC];
    void (*fn)(W7Ob *);
} W7Ev;
W7Ev *func_00130398(W7Ob *o, s32 k, f32 f);
W7Ev *func_00130578(W7Ob *o, s32 k, f32 f);
f32 func_001376e8(W7Ob *o, f32 *v);
void func_00137688(W7Ob *o, f32 f);

void func_0013df40(W7Ob *o, s32 f) {
    if (o->x14c && !(o->flags & 0x4000)) {
        o->x14c->c = -1;
        o->x14c->d = -1;
        o->x14c->e = -1;
        if (f) {
            o->x14c->f = -128;
        } else {
            o->x14c->f = -1;
        }
    }
    o->flags |= 0x4000;
}

s32 func_0013dfb8(W7Ob *o, s32 a) {
    s32 r;
    s32 (*fn)(W7Ob *, s32);
    o->x3d0 = 0;
    fn = D_00350DA4[o->x70].fn;
    r = 0;
    if (fn) {
        r = fn(o, a);
    }
    return r;
}

void func_0013f2c0(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        D_0052AE70[i] = func_001477c8(D_00304C18[i]);
    }
}

s32 func_0013f478(W7Ob *o, f32 *v) {
    f32 t[4];
    if (o->x300 == 0.0f || v[3] == 0.0f) {
        return 0;
    }
    func_00267530(t, o->x2f0, o->x10);
    t[1] = 0.0f;
    func_00121fc4(t, t);
    if (func_00267390(t, v) < 0.7f) {
        return 0;
    }
    return 1;
}

f32 func_0013fd88(f32 a) {
    f32 r = fmodf(a, 66.66666412353516f);
    while (r < 0.0f) {
        r += 66.66666412353516f;
    }
    return r / 66.66666412353516f;
}

void func_00140fa8(W7Ob *o) {
    func_0014cc88(o, 0.0f);
    o->flags &= ~0x400;
    o->x3b0 = 6.0f;
    o->x3b4 -= 8.724489212036133f;
    func_00267560(o->x3c0, o->x200, D_002C5970);
}

void func_00141018(W7Ob *o) {
    func_00130398(o, 0x01000019, 0.0f);
    func_00130578(o, 0x40000006, 0.0f)->fn = func_00140fa8;
}

void func_001410d8(W7Ob *o) {
    func_00130398(o, 0x01000019, 0.0f);
    func_00130578(o, 0x40000006, 0.0f)->fn = func_00140fa8;
}

void func_001447a0(W7Ob *o) {
    func_0014cc88(o, 0.0f);
    o->flags &= ~0x400;
    o->x3b0 = 6.0f;
    o->x3b4 -= 8.724489212036133f;
    func_00267560(o->x3c0, o->x200, D_002C5970);
}

void func_00141078(W7Ob *o) {
    func_00267560(o->x20, o->x148, -1.0f);
    o->x20[1] = o->x20[3] = 0.0f;
    func_00137688(o, func_001376e8(o, o->x20));
}

typedef struct {
    u8 pad00[0x38];
    s16 x38;
} W7Gauge;

typedef struct {
    u8 pad00[0x40];
    s32 x40;
    s32 x44;
    s32 x48;
    u8 pad4c[0xBE - 0x4C];
    u16 xbe;
    u8 padc0[0xC8 - 0xC0];
    W7Gauge *xc8;
} W7Lv;

typedef struct {
    u8 pad00[0x6C];
    union {
        W7Lv *p;
        s16 h;
    } x6c;
} W7Pl;

#include "data/pieces/D_00304C70.h"
void func_00141468(W7Pl *o, s32 v);
void func_00141540(W7Pl *o, s32 v);
void func_00141608(W7Pl *o, s32 v);


s32 func_00141288(W7Pl *o, s32 n) {
    W7Lv *p;
    s32 t;
    if (n >= 100) {
        return o->x6c.p->x44 >= n / 100;
    }
    p = o->x6c.p;
    t = p->x44;
    return p->xbe + (t * t + t) / 2 * 30 >= n;
}

void func_001412f8(W7Pl *o, s32 n) {
    if (n >= 100) {
        func_00141540(o, -n / 100);
    } else {
        func_00141608(o, -n);
    }
}

void func_00141720(W7Pl *o) {
    W7Lv *p = o->x6c.p;
    s32 x, t;
    if (p == 0 || p == ((W7Lv *)&D_00304C70)) return;
    x = p->xbe;
    t = p->x44 * 30 + 30;
    if (x >= t) {
        func_00141540(o, 1);
        x -= t;
    }
    p->xbe = x;
    if (p->xc8) {
        p->xc8->x38 = x;
    }
}

typedef struct {
    u8 pad[0xE4];
} W7Fx;

W7Fx D_0052AE98[32] ALIGNED(8);
extern u32 D_0052CB18;
void func_001418b8(W7Fx *p);

W7Fx *func_00141a40(void) {
    W7Fx *p = D_0052AE98;
    s32 i;
    for (i = 0; i < 32; i++, p++) {
        if (!(D_0052CB18 & (1 << i))) {
            D_0052CB18 |= 1 << i;
            func_001418b8(p);
            return p;
        }
    }
    return 0;
}

void func_00141ab8(W7Fx *p) {
    if (p >= D_0052AE98 && p < D_0052AE98 + 32) {
        D_0052CB18 &= ~(1 << (p - D_0052AE98));
    }
}

typedef struct {
    s32 key;
    s32 val;
} W7Kv;

typedef struct {
    s32 x0;
    s32 x4;
    W7Kv e[256];
} W7Tbl;

extern W7Tbl *D_0052EB40; /* src/data/bss_0052.c: W55Cache *D_0052EB40 */
extern W7Tbl D_0052CB20[4]; /* src/data/bss_0052.c: W55Cache D_0052CB20[4] */
extern s32 D_0052EB44;

void func_001421d0(s32 k, s32 v) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W7Kv *e = D_0052EB40->e;
        s32 *p = &e[i].key;
        if (*p == k) {
            D_0052EB40->e[i].val = v;
            return;
        }
        if (*p == -1) {
            *p = k;
            D_0052EB40->e[i].val = v;
            return;
        }
    }
}

s32 func_00142240(s32 k) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W7Kv *e = D_0052EB40->e;
        s32 *p = &e[i].key;
        if (*p == k) {
            return D_0052EB40->e[i].val;
        }
        if (*p == -1) {
            *p = k;
            D_0052EB40->e[i].val = 0;
            return 0;
        }
    }
    return 0;
}

void func_001422b0(s32 n) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        if (D_0052CB20[i].x0 >= 0 && D_0052CB20[i].x4 >= D_0052EB44 - n - 1) {
            for (j = 0; j < 256; j++) {
                D_0052CB20[i].e[j].key = -1;
            }
        }
    }
}

void func_00142340(void) {
    s32 i;
    D_0052EB44 = 0;
    for (i = 0; i < 4; i++) {
        D_0052CB20[i].x0 = -1;
    }
}

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    u8 pad[0x350];
    u128 x350;
} W7Q;

void func_00142470(W7Q *o, u128 *v) {
    o->x350 = *v;
}


typedef struct {
    u8 pad00[0x5C];
    s32 x5c;
    u8 pad60[0x90 - 0x60];
    s32 x90;
    s32 x94;
    u8 pad98[0xB0 - 0x98];
    s32 xb0;
    u8 padb4[0xBC - 0xB4];
    s32 xbc;
} W7Ai;

typedef struct W7Ch W7Ch;
struct W7Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    u8 pad018[0x70 - 0x18];
    s32 x70;
    u8 pad074[0x130 - 0x74];
    W7Info *info;
    u8 pad134[0x148 - 0x134];
    union {
        W7Ai *p;
        s32 i;
    } x148;
    u8 pad14c[0x2CC - 0x14C];
    s32 x2cc;
    u8 pad2d0[0x2D4 - 0x2D0];
    f32 x2d4;
    u8 pad2d8[0x2DC - 0x2D8];
    union {
        u16 h;
        s32 i;
    } x2dc;
    u8 pad2e0[0x360 - 0x2E0];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W7Ch *x398;
};

f32 func_00144368(W7Ch *o);
void func_002675a8(f32 *d, f32 *s);
void func_00118668(void *p);
s32 func_00137450(s32 a);


typedef struct {
    f32 p[4];
    f32 d[4];
    u8 pad20[4];
    f32 x24;
    u8 pad28[8];
    s16 x30;
    u8 pad32[0x40 - 0x32];
} W7Ray;

s32 func_001426a8(f32 *pos, f32 r) {
    W7Ray t;
    func_002675a8(t.p, pos);
    t.p[1] -= r;
    t.d[0] = 0.0f;
    t.p[3] = 1.0f;
    t.d[3] = 1.0f;
    t.d[1] = r + r;
    t.d[2] = 0.0f;
    func_00118668(&t);
    if (t.x30 >= 0) {
        pos[1] = t.x24;
        return t.x30 + 1;
    }
    return 0;
}

s32 func_00142730(W7Ch *o, s32 *out) {
    switch (o->x70) {
    case 13:
        *out = -1;
        return o->x148.p->x5c;
    case 15:
    case 16:
        *out = func_00137450(o->x148.p->x94);
        return o->x148.p->x90;
    }
    *out = o->x2cc;
    return o->x2dc.h;
}

void func_00144350(W7Ch *o) {
    o->x148.p->xbc = 0;
    o->x148.p->xb0 = 0;
}

typedef struct {
    f32 f;
    s32 pad;
} W7F8;
extern W7F8 D_00304D60[];



extern s32 D_00531B64;
void func_001315c0(W7Ch *o, s32 k, void *buf, f32 f);
void func_00144eb0(s32 v, void *buf);

void func_00145008(W7Ch *o, s32 k) {
    u8 buf[16];
    s32 v;
    if (D_00531B64) return;
    switch (k) {
    case 0:
        v = o->info->x48;
        break;
    case 1:
        v = o->info->x4a;
        break;
    default:
        return;
    }
    func_001315c0(o, 0x8003, buf, 0.0f);
    func_00144eb0(v, buf);
}
#include "data/bss_0052_mixed.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5970.h"
#include "data/pieces/D_00350DA4.h"
