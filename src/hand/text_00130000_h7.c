#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */

#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W7Member;

typedef Save_304be8 W7Save;

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
        if (D_00304BE8->x48e[i] == v) {
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
    if (D_00304BE8->m[i].sub.lv >= 100) {
        return 0;
    }
    p = func_0013c3f8(i);
    e = D_00304BE8->m[i].sub.exp;
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
        u8 c = D_00304BE8->x48e[i];
        if (c != 0xFF) {
            W7Member *m = &D_00304BE8->m[c];
            func_00141b10(c, buf);
            m->sub.x1 = buf[64];
            m->sub.x3 = buf[72];
            m->sub.x38 = 0;
        }
    }
}

void func_0013c778(u32 a, u32 b, u32 c) {
    D_00304BE8->x48e[1] = a < 10 ? a : -1;
    D_00304BE8->x48e[2] = b < 10 ? b : -1;
    D_00304BE8->x48e[3] = c < 10 ? c : -1;
}

void func_0013c7d8(u32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->x48e[i] == v) {
            return;
        }
        if (D_00304BE8->x48e[i] == 0xFF) {
            if (v < 10) {
                D_00304BE8->x48e[i] = v;
            } else {
                D_00304BE8->x48e[i] = -1;
            }
            return;
        }
    }
}

void func_0013c840(u32 v) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        if (D_00304BE8->x48e[i] == v) {
            for (j = i; j < 3; j++) {
                D_00304BE8->x48e[j] = D_00304BE8->x48e[j + 1];
            }
            D_00304BE8->x48e[j] = -1;
            return;
        }
    }
}

void func_0013c8c8(s32 c, u32 k) {
    u8 *p;
    s32 i;
    if (k < 10) {
        p = D_00304BE8->m[k].sub.name;
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
        p = D_00304BE8->m[k].sub.name;
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

typedef struct Actor W7Obj;
struct Actor {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W7Info *info;
    u8 pad134[0x398 - 0x134];
    W7Obj *x398;
};

#include "data/pieces/D_002E26A0.h"
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

#include "data/pieces/D_00304C70.h"

typedef St6C_304c70 W7Lv;

typedef struct {
    u8 pad00[0x6C];
    union {
        W7Lv *p;
        s16 h;
    } x6c;
} W7Pl;

void func_00141468(W7Pl *o, s32 v);

typedef struct {
    u8 pad[0xE4];
} W7Fx;

W7Fx D_0052AE98[32] ALIGNED(8);

typedef unsigned int u128 __attribute__((mode(TI)));

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
#include "data/pieces/D_00350DA4.h"
