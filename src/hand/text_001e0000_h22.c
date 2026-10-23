#include "common.h"

#include "data/types/text_001e0000_h22.h"

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
