/* The ppp object controls, default flags (docs/modules.md "Session 51"):
 * func_0017f8e0 (the third ppp task: runs func_0017f688 while D_00362704 is
 * set), the work buffer (func_0017f910: D_0061622C / D_00616230, by default
 * D_00575E40 of 0x20000 bytes), the effect heap and draw-list wrappers
 * (func_0017f948 ... func_0017f9a8), and the calls on every live object of
 * D_00364130: kill them all (func_0017f9d8, func_0017fc48), hide or show
 * them all or one by key (flag 0x20: func_0017fa68 ... func_0017fb40), and a
 * key's owner value (func_0017ff98); func_0017ffd8 rebases a packed
 * texture's GS addresses (the twin of pppsys.c's func_00180180).
 * pppobj.nostrict.c has the kills by key or range and func_0017ff38.  Each
 * section names the file its code came from.  Read from the code, not
 * proved by a boot. */
#include "m2c.h"
#include "data/pieces/D_00362438.h"
#include "data/bss_0057.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362710.h"
#include "common.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/text_00170000_h11_p3.h"
#include "data/pieces/D_003626F8.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"

/* func_0017f8e0 (from auto/text_00170000_3.c). */
M2C_UNK func_0017f688();
extern s32 D_00362704;
s32 func_0017f8e0(void) {
    if (D_00362704 != 0) {
        func_0017f688();
    }
    return 0;
}

/* func_0017f910 (from auto/text_00170000_2.c). */
extern M2C_UNK *D_0061622C;
M2C_UNK D_00575E40[0x8000] ALIGNED(64);
extern s32 D_00616230;
void func_0017f910(M2C_UNK *arg0, s32 arg1) {
    if (arg0 != NULL) {
        D_0061622C = arg0;
        D_00616230 = arg1;
        return;
    }
    D_0061622C = &D_00575E40;
    D_00616230 = 0x20000;
}

/* func_0017f948 (from auto/text_00170000.c). */
s32 D_00616238 ALIGNED(8);
void func_0017f948(void) {
    D_00616238 = 0;
}

/* func_0017f958 (from auto/text_00170000.c). */
M2C_UNK func_00183a48();
void func_0017f958(void) {
    func_00183a48();
}

/* func_0017f970 (from auto/text_00170000.c). */
M2C_UNK func_001a9f88();
M2C_UNK func_001aa650();
extern s32 D_00616228;
void func_0017f970(void) {
    if (D_00616228 != 0) {
        func_001aa650();
        func_001a9f88();
    }
}

/* func_0017f9a8 (from auto/text_00170000_8.c). */
M2C_UNK func_001a9e70();
M2C_UNK func_001a9eb8();
M2C_UNK func_001aa858();
void func_0017f9a8(void) {
    func_001a9e70();
    func_001a9eb8();
    func_001a9f88();
    func_001aa858();
}

/* func_0017f9d8 (from hand/text_00170000_h11.c). */
typedef E0C0_364130_2 E0C0;
void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_001827f0(E0C0 *);
void func_0017f9d8(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        E0C0 *e = &D_00364130.e0C0_2[i];
        if (e->flags & 1) {
            if (e->p8c && e->p8c->xfc) func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            func_001827f0(e);
        }
    }
}

/* func_0017fa68 (from hand/text_00170000_h11.c). */
void func_0017fa68(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].flags & 1) D_00364130.e0C0_2[i].flags |= 0x20;
    }
}

/* func_0017faa8 (from hand/text_00170000_h11.c). */
void func_0017faa8(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].flags & 1) D_00364130.e0C0_2[i].flags &= ~0x20;
    }
}

/* func_0017fae8 (from hand/text_00170000_h11.c). */
void func_0017fae8(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if ((D_00364130.e0C0_2[i].flags & 1) && D_00364130.e0C0_2[i].key == key) {
            D_00364130.e0C0_2[i].flags |= 0x20;
            return;
        }
    }
}

/* func_0017fb40 (from hand/text_00170000_h11.c). */
void func_0017fb40(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if ((D_00364130.e0C0_2[i].flags & 1) && D_00364130.e0C0_2[i].key == key) {
            D_00364130.e0C0_2[i].flags &= ~0x20;
            return;
        }
    }
}

/* func_0017fc48 (from hand/text_00170000_h11.c). */
void func_00182840(E0C0 *);
void func_0017fc48(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        E0C0 *e = &D_00364130.e0C0_2[i];
        if (e->flags & 1) {
            if (e->p8c && e->p8c->xfc) func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            func_00182840(e);
        }
    }
}

/* func_0017ff98 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad[0x104]; s32 x104; } S104;
s32 func_0017ff98(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].key == key) return ((S104 *)D_00364130.e0C0_2[i].p8c)->x104;
    }
    return -2;
}

/* func_0017ffd8 (from hand/text_00180000_h62.c). */
typedef struct {
    s8 unk0;
    s8 type;   /* +0x1 */
    s16 count; /* +0x2 */
    s32 unk4;
    union {
        u32 w;
        u16 h;
    } u8_;     /* +0x8 */
    union {
        u32 w;
        struct {
            u32 lo : 5;
            u32 y : 14;
            u32 rest : 13;
        } b;
    } uc;      /* +0xC */
} TexItem;
typedef struct {
    s32 unk0;
    s32 off; /* +0x4 */
} TexHdr;
typedef struct {
    u16 unk0;
    u16 x; /* +0x2 */
    u16 y; /* +0x4 */
} TexRef;
void func_0017ffd8(TexHdr *h, TexRef *r, s16 x, s16 y) {
    TexItem *p = (TexItem *) ((u8 *) h + h->off);
    s16 dx, dy;
    s32 size;
    s32 flag;
    s32 v;
    u32 w;

    if (x == 0 && y == 0)
        return;
    if (x != 0)
        dx = x - r->x;
    if (y != 0)
        dy = y - r->y;
    if (dx == 0 && dy == 0)
        return;
    while (p->type != -1) {
        flag = 1;
        switch (p->type) {
        case 0:
            size = 20;
            flag = 0;
            break;
        case 1:
            size = 28;
            flag = 0;
            break;
        case 2:
            size = 32;
            break;
        case 4:
            size = 24;
            flag = 0;
            break;
        case 5:
            size = 32;
            flag = 0;
            break;
        case 3:
        case 6:
            size = 40;
            break;
        case 7:
            size = 48;
            break;
        }
        if (flag) {
            if (x != 0 && dx != 0) {
                v = p->u8_.h & 0x3FFF;
                if (v >= 0x3800)
                    p->u8_.w = (p->u8_.w & ~0x3FFF) + (v + dx);
            }
            if (y != 0 && dy != 0) {
                w = p->uc.w;
                v = (w >> 5) & 0x3FFF;
                if (v >= 0x3D40)
                    p->uc.w = (w & 0xFFF8001F) + ((v + dy) << 5);
            }
        }
        p = (TexItem *) ((u8 *) p + size * p->count);
        p++;
    }
}

