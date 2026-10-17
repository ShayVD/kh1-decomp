/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */
#include "common.h"

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
u16 *func_001477c8(u16 *p);
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

void func_0013cec8(W7Stack *q, void *src, u32 n) {
    memcpy(q->u.p, src, n);
    q->u.p += n >> 2;
    *q->u.p++ = n;
}

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
