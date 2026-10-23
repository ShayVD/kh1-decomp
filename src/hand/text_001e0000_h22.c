#include "common.h"
#include "data/pieces/D_00304BE8_s.h"

u32 func_001ee118(void);

void func_001ee230(u32 *a, u32 *b, u32 *c, u32 *d) {
    u32 t = func_001ee118();
    *a = t / 216000U;
    t = t % 216000U;
    *b = t / 3600U;
    t = t % 3600U;
    *c = t / 60U;
    *d = t % 60U;
}

typedef W606Mem_304be8 Member;
typedef Save_304be8 S4BE8;
#include "data/pieces/D_003E3D68.h"
extern u16 D_003E3CD0[];
s32 func_00149440(s32, s32);
s32 func_001ee7c8(void);
u8 *func_001efc10(s32);

void func_001ee650(s32 a) {
    if (a > 16) a = 0;
    func_001efc10(D_003E3CD0[a]);
}

s32 func_001ee7f0(s32 a) {
    s32 n = D_003E3D68;
    s32 i = 0;
    do {
        if (func_00149440(a, D_00304BE8->x48e[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee870(s32 a, s32 i) {
    s32 n;
    if (func_001ee7c8()) {
        i = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    do {
        if (func_00149440(a, D_00304BE8->x48e[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee900(s32 a) {
    s32 v = func_00149440(a, 0);
    s32 i;
    for (i = 1; i < 7; i++) {
        if ((v >> i) & 1) return i;
    }
    return -1;
}

s32 func_001ee958(s32 a, s32 b) {
    s32 v = func_00149440(a, b);
    s32 i;
    if (v & 1) {
        for (i = 1; i < 7; i++) {
            if ((v >> i) & 1) return i;
        }
    }
    return -1;
}

s32 func_001ee768(void);
extern s32 D_003E3D20[];

s32 func_001eea00(s32 a, s32 b) {
    s32 v;
    if (a) {
        v = func_001ee768();
        if ((u32)(v - 2) < 10) {
            if (v != D_003E3D20[b]) return 0;
        }
    }
    return 1;
}

u8 *func_00147840(void);
extern s32 D_003E3D48[];

s32 func_001eea60(s32 a) {
    u32 i;
    if (a) {
        u8 k = func_00147840()[2];
        for (i = 0; i < 3; i++) {
            if (k == D_003E3D48[i]) return 1;
        }
    }
    return 0;
}

void func_00141b10(s32, s32 *);

s32 func_001eec48(s32 i, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x32;
    m->sub.x32 = v;
    func_00141b10(i, buf);
    m->sub.x32 = old;
    return buf[19];
}

s32 func_001eecb0(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[15];
}

s32 func_001eed18(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[17];
}

s32 func_001eed80(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[56];
}

s32 func_001eede8(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[19];
}

s32 func_001eee50(s32 i, s32 j, u8 v) {
    s32 buf[60];
    Member *m = &D_00304BE8->m[i];
    u8 old = m->sub.x19[j];
    m->sub.x19[j] = v;
    func_00141b10(i, buf);
    m->sub.x19[j] = old;
    return buf[20];
}

s32 func_001eefd8(s32 a, s32 skip) {
    s32 n = 0, i, j;
    for (i = 0; i < 10; i++) {
        Member *m;
        if (i == skip) continue;
        m = &D_00304BE8->m[i];
        for (j = 0; j < m->sub.x1c; j++) {
            if (m->sub.x19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef050(s32 a) {
    s32 n = 0, i, j;
    S4BE8 *d = D_00304BE8;
    for (i = 0; i < 10; i++) {
        Member *m = &d->m[i];
        if (m->sub.x32 == a) n++;
        for (j = 0; j < m->sub.x1c; j++) {
            if (m->sub.x19[j] == a) n++;
        }
    }
    return n;
}

s32 func_001ef0c0(s32 a) {
    s32 i, j;
    S4BE8 *d = D_00304BE8;
    s32 n = d->items[a];
    for (i = 0; i < 10; i++) {
        Member *m = &d->m[i];
        if (m->sub.x32 == a) n--;
        for (j = 0; j < m->sub.x1c; j++) {
            if (m->sub.x19[j] == a) n--;
        }
    }
    if (n < 0) n = 0;
    return n;
}

#include "data/pieces/D_003E3CF8.h"

s32 func_001ef2c0(s32 a) {
    u32 i;
    if (a) {
        s32 k = func_001ee768();
        for (i = 0; i < 10; i++) {
            if (k == D_003E3CF8[i]) return 1;
        }
    }
    return 0;
}

extern s32 D_003E3D58[];

s32 func_001ef320(void) {
    s32 i;
    u8 k = D_00304BE8->m[0].sub.x32;
    for (i = 3; i >= 0; i--) {
        if (k == D_003E3D58[i]) return 0;
    }
    return 1;
}

s32 func_001ef3a0(s32 i) {
    s32 n;
    Member *m = &D_00304BE8->m[i];
    for (n = 0; n < 48 && m->sub.name[n]; n++);
    return n;
}

s32 func_001ef408(void) {
    s32 n;
    for (n = 0; n < 48 && D_00304BE8->list599[n]; n++);
    return n;
}

s32 func_001ef450(s32 i, s32 a) {
    s32 n = 0, k;
    Member *m = &D_00304BE8->m[i];
    u8 c;
    for (k = 0; k < 48 && (c = m->sub.name[k]); k++) {
        if ((c & ~0x80) == a) n++;
    }
    return n;
}

s32 func_001ef4c0(s32 a) {
    s32 n = 0, k;
    u8 c;
    for (k = 0; k < 48 && (c = D_00304BE8->list599[k]); k++) {
        if ((c & ~0x80) == a) n++;
    }
    return n;
}

#include "data/pieces/D_003E3D70.h"
typedef S3D70_3E3D70 S3D70;
u8 *func_001478a0(s32);

u8 func_001ef5c0(s32 arg0) {
    if (arg0 != 0) {
        return *func_001478a0(arg0 & ~0x80);
    }
    return 0U;
}

s32 func_001ef680(s32 i) {
    s32 n = 0, k = 0;
    u8 *p = D_00304BE8->m[i].sub.name;
    u8 c;
loop:
    if (k >= 48) goto end;
    k++;
    c = *p++;
    if (!c) goto end;
    if (c & 0x80) goto loop;
    n += func_001ef5c0(c);
    goto loop;
end:
    return n;
}

s32 func_001ef720(s32 i) {
    S3D70 *e = &D_003E3D70.s3D70[i];
    s32 r = e->xe0 - func_001ef680(i);
    if (r < 0) r = 0;
    return r;
}

#include "data/pieces/D_003F34B8.h"
typedef S34B8_3f34b8 S34B8;

void func_001ef7b0(s32 a) {
    S34B8 *p = D_003F34B8;
    p->x1c += a;
    if (p->x1c < 0) p->x1c = 0;
    else if ((u32)p->x1c > 99999) p->x1c = 99999;
}

void func_001ef7f0(s32 a) {
    S34B8 *p = D_003F34B8;
    p->x1c -= a;
    if (p->x1c < 0) p->x1c = 0;
    else if ((u32)p->x1c > 99999) p->x1c = 99999;
}

void *func_0013daf8(s32);
s32 func_00122ff8(void *);

void *func_001ef8f8(s32 i) {
    void *p = func_0013daf8(D_00304BE8->x48e[i]);
    if (p && func_00122ff8(p)) goto ok;
    return 0;
ok:
    return p;
}

extern u16 *D_0063F748;
extern u8 *D_0063F744;

u8 *func_001efbb8(s32 a) {
    return D_0063F744 + D_0063F748[a - 1];
}

typedef struct { u8 pad[0x10]; s32 x10; s32 x14; } Tbl;

u8 *func_001efcb0(Tbl *t, s32 a) {
    u16 *o = (u16 *)((u8 *)t + t->x10);
    return (u8 *)t + t->x14 + o[a - 1];
}

#include "data/types/text_001e0000_h22.h"
#include "data/pieces/D_003E8E28.h"
extern s32 D_003E8E2C;

s32 func_001eff50(s32 a) {
    s32 i;
    E8E28 *e = (*(E8E28 * *)&D_003E8E28);
    for (i = 0; i < D_003E8E2C; i++, e++) {
        if (e->id == a) return i;
    }
    return 0;
}

s32 func_001f0600(s32 i, s32 b) {
    return (((*(E8E28 * *)&D_003E8E28)[i].x6 << 4) * b / 18) >> 4;
}

typedef struct Obj {
    u8 pad[0xc];
    struct Obj *x0c;
    struct Obj *next;
    struct Obj *x14;
    struct Obj *x18;
    struct Obj *x1c;
    struct Obj *x20;
    u8 pad24[0x7c - 0x24];
    s32 x7c;
    u8 pad80[0x8c - 0x80];
    s32 x8c;
    u8 pad90[0xf0 - 0x90];
} Obj;

extern Obj D_0063F758[]; /* src/data/bss_0063.c: Obj D_0063F758[24] */
extern s32 D_003F1A60, D_003F1A64;
extern Obj *D_00640DD8, *D_00640DDC;
void func_001efb78(s32);
void func_001efb98(s32);
void func_001fd708(void);
void func_001f3680(Obj *);
void func_001f3698(Obj *, s32);

void func_001f3110(void) {
    s32 i;
    Obj *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) p->x8c = 0;
    D_00640DD8 = 0;
    D_00640DDC = 0;
    D_003F1A60 = 0x80e6e6e6;
    D_003F1A64 = 320;
    func_001efb78(0);
    func_001efb98(0);
    func_001fd708();
}

s32 func_001f36b8(Obj *p) {
    if (!p) return -1;
    switch (p->x8c) {
    case 0: return 0;
    case 4: case 5: break;
    default: func_001f3680(p);
    }
    return 0;
}

s32 func_001f3708(Obj *p, s32 a) {
    if (!p) return -1;
    switch (p->x8c) {
    case 0: return 0;
    case 4: case 5: break;
    default: func_001f3698(p, a);
    }
    return 0;
}

s32 func_001f3758(Obj *p) {
    if (!p) return -1;
    for (; p; p = p->next) {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
    }
    return 0;
}

s32 func_001f37c0(Obj *p, s32 a) {
    if (!p) return -1;
    for (; p; p = p->next) {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3698(p, a);
        }
    }
    return 0;
}

s32 func_001f3840(Obj *p) {
    if (!p) return -1;
    while (p->x0c) p = p->x0c;
    do {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
        p = p->next;
    } while (p);
    return 0;
}

void func_001f3b00(s32 a) {
    s32 i;
    Obj *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default:
            if (p->x7c == a) func_001f3680(p);
        }
    }
}

void func_001f3b88(s32 a, s32 b) {
    s32 i;
    Obj *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default:
            if (p->x7c == a) func_001f3698(p, b);
        }
    }
}

void func_001f3c20(void) {
    s32 i;
    Obj *p = D_0063F758;
    for (i = 24; i > 0; i--, p++) {
        switch (p->x8c) {
        case 0: break;
        case 4: case 5: break;
        default: func_001f3680(p);
        }
    }
}


void func_001f3d70(Obj *p) {
    Obj **h;
    Obj *t;
    if (!p->x14) return;
    p->x14->x18 = p->x18;
    if (p->x18) p->x18->x14 = p->x14;
    p->x14 = 0;
    h = &D_00640DD8;
    t = *h;
    p->x18 = t;
    t->x14 = p;
    *h = p;
}

void func_001f3dc0(Obj *p) {
    Obj **h = &D_00640DDC;
    Obj *t = *h;
    if (t && t != p) {
        if (p->x1c) p->x1c->x20 = p->x20;
        if (p->x20) p->x20->x1c = p->x1c;
        t = *h;
        p->x1c = 0;
        p->x20 = t;
        t->x1c = p;
    }
    D_00640DDC = p;
}

void func_001f3f48(Obj *a, Obj *b) {
    while (a->next) a = a->next;
    while (b->x0c) b = b->x0c;
    a->next = b;
    b->x0c = a;
}

s32 func_001f4110(void) {
    s32 i, n = 0;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->x8c) n++;
    }
    return n;
}
#include "data/bss_0063_mixed.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
