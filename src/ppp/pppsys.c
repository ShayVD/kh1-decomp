/* The ppp effect manager core, default flags (docs/modules.md "Session 51"):
 * the effect resource walkers (func_001803b8 / 001803c0 skip a resource's
 * sections, func_00180540 relocates its programs), the sprite and texture
 * uploads to GS memory (func_00180180 ... func_00180e10: rebase a sprite's
 * TBP / CBP to the slot it was given, sceGsSetDefLoadImage / sceGsExecLoadImage),
 * the texture-slot allocator (func_00180f18: a run of free 128 / 32 block slots
 * per owner, func_00181238 / 00181280), the per-frame draw loop over the 0x10c
 * depth-sorted objects of D_00575A10 (func_00181b30), the camera copy
 * (func_00182148), the object table D_00364130 (256 entries of 0xC0 bytes:
 * find a free one, kill the oldest, free one), the system steps (module
 * callbacks fn[4..6], instance spawning func_001837a8, the frame clock
 * func_00183878 / 00183958), the effect heap (func_00183a00 init,
 * func_00183b20 free), pppResetComponents / pppConComponents, nine empty class
 * slots (pppKeThLz*, pppKeThCp*, pppKeAccSpdSv*) and func_00183be0, the
 * rotation-order matrix pppKeMatSN uses.  pppsys.nostrict.c has the rest.
 * Each section names the file its code came from.  Read from the code, not
 * proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00370130.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/text_00170000_h11_p3.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_003626F8.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/types/text_00180000_h39.h"
#include "data/pieces/D_002BBDF8.h"

/* func_00180180 (from hand/text_00170000_h38.c). */
typedef struct { s16 off; u8 pad[6]; } TEnt;
typedef struct Hdr_80180 {
    u8 pad0[6];
    s16 n;          /* 0x06 */
    u8 pad8[8];
    TEnt tbl[1];    /* 0x10 */
} Hdr_80180;
typedef struct Ref { u16 x0; u16 x2; u16 x4; } Ref;
typedef struct Ent {
    u8 pad0[0x10];
    union { u16 h; u32 w; } x10;
    u32 x14;
} Ent;
void func_00180180(Hdr_80180 *h, Ref *r, s16 dx, s16 dy) {
    s16 ox = 0, oy = 0;
    s32 n;
    TEnt *t;
    if (dx == 0 && dy == 0) return;
    if (dx) ox = dx - r->x2;
    if (dy) oy = dy - r->x4;
    n = h->n;
    for (t = h->tbl; n > 0; n--, t++) {
        Ent *e = (Ent *)((u8 *)h + t->off);
        if (dx && ox) {
            s32 v = e->x10.h & 0x3fff;
            if (v >= 0x3800) e->x10.w = (e->x10.w & 0xffffc000) + (v + ox);
        }
        if (dy && oy) {
            u32 w = e->x14;
            s32 v = (w & 0x7ffe0) >> 5;
            if (v >= 0x3d40) e->x14 = (w & 0xfff8001f) + ((v + oy) << 5);
        }
    }
}

/* func_001803b8 (from auto/text_00180000.c). */
s32 func_001803b8(s32 arg0) {
    return arg0 + 4;
}

/* func_001803c0 (from hand/text_00170000_h11.c). */
s32 *func_001803c0(s32 *p, s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        s32 k = *p++;
        p += k;
    }
    return p;
}

/* func_001803f0 (from hand/text_00170000_h38.c). */
typedef struct Obj {
    u8 pad0[0x8c];
    s32 x8c;    /* 0x8C */
    u8 pad90;
    u8 x91;     /* 0x91 */
    u8 x92;     /* 0x92 */
} Obj;
void func_001803f0(void *a0, s32 id, s32 *out, Obj *o) {
    s32 *p = func_001803b8(a0);
    s32 n, i;
    *out = 0;
    n = *p++;
    for (i = 0; i < n; i++, p++) {
        if (id == i) {
            s32 v = *p;
            o->x8c = v;
            *out = v + 272;
        }
    }
    p = func_001803c0(p, 4);
    if (p[0] != -1) {
        s32 y = (p[1] - 0x3781) / 128;
        s32 x = (p[3] - 0x3d21) / 32;
        o->x91 = y;
        o->x92 = x;
    } else {
        o->x91 = 0;
        o->x92 = 0;
    }
}

/* func_001804d0 (from auto/text_00180000_4.c). */
#define func_001803b8 ((s32 *(*)()) func_001803b8)
s32 *func_001804d0(s32 arg0, s32 arg1) {
    s32 *var_v1;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;

    var_v1 = func_001803b8();
    var_a1 = 4;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        if (temp_v0 > 0) {
            var_a0 = temp_v0;
            do {
                var_a0 -= 1;
                *var_v1 += arg1;
                var_v1 += 1;
            } while (var_a0 != 0);
        }
        var_a1 -= 1;
    } while (var_a1 >= 0);
    return var_v1;
}
#undef func_001803b8

/* func_00180540 (from hand/text_00170000_h11.c). */
void pppRelocProgram(s32, void *);
extern u8 D_00370200[];
#define TBL D_00370200
void func_00180540(void *h) {
    s32 *p;
    s32 n, i;
    func_001804d0(h, h);
    p = func_001803b8(h);
    n = *p++;
    for (i = 0; i < n; i++) pppRelocProgram(*p++, TBL);
}
#undef TBL

/* func_001805b8 (from hand/text_00180000_h39.c). */
typedef struct {
    s16 unk00, w, h;
    s16 pad06[5];
    u8 data[1]; /* +0x10 */
} H39Spr;
s32 *func_001805b8(s32 *p, u8 *mask, s16 w, s16 h) {
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Spr *s = (H39Spr *) *p++;
        s32 k = i >> 3;

        if (!(i & 7))
            m = mask[k];
        if (m & 1) {
            u8 *d = s->data;

            if (s->w == 0)
                s->w = 0x3800;
            if (s->h == 0)
                s->h = 0x3D40;
            func_00180180(d, s, w, h);
            if (w)
                s->w = w;
            if (h)
                s->h = h;
        }
    }
    return p;
}

/* func_001806c8 (from hand/text_00180000_h39.c). */
void func_0017ffd8(void *, H39Spr *, s16, s16);
s32 *func_001806c8(s32 *p, u8 *mask, s16 w, s16 h) {
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Spr *s = (H39Spr *) *p++;
        s32 k = i >> 3;

        if (!(i & 7))
            m = mask[k];
        if (m & 1) {
            u8 *d = s->data;

            if (s->w == 0)
                s->w = 0x3800;
            if (s->h == 0)
                s->h = 0x3D40;
            func_0017ffd8(d, s, w, h);
            if (w)
                s->w = w;
            if (h)
                s->h = h;
        }
    }
    return p;
}

/* func_001807d8 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad[0x88]; void *x88; u8 *x8c; u8 pad90[0x14]; s16 xa4; s16 xa6; } O88;
#define func_001805b8 ((s32 *(*)(s32 *, void *, s32, s32)) func_001805b8)
#define func_001806c8 ((s32 *(*)(s32 *, void *, s32, s32)) func_001806c8)
void func_001807d8(O88 *o) {
    s32 a = o->xa4;
    s32 b = o->xa6;
    void *q = o->x88;
    s32 *p;
    if (a == 0 && b == 0) return;
    p = func_001803b8(q);
    p = func_001803c0(p, 2);
    p = func_001805b8(p, o->x8c + 192, a, b);
    func_001806c8(p, o->x8c + 208, a, b);
}
#undef func_001805b8
#undef func_001806c8

/* func_00180a48 (from auto/text_00180000_1.c). */
M2C_UNK func_001809b8(s32, s32);
s32 func_00180878(s32, s32);
s32 func_001808f8(s32, s32);
void func_00180a48(void *arg0) {
    func_001809b8(func_001808f8(func_00180878(func_001803c0(func_001803b8(M2C_FIELD(arg0, s32 *, 0x88)), 2), M2C_FIELD(arg0, s32 *, 0x8C) + 0xC0), M2C_FIELD(arg0, s32 *, 0x8C) + 0xD0), M2C_FIELD(arg0, s32 *, 0x8C) + 0xE0);
}

/* func_00180aa8 (from auto/text_00180000.c). */
void func_00180aa8(s32 arg0) {
    D_00370130 = arg0;
}

/* func_00180ab8 (from hand/text_00180000_h39.c). */
typedef struct {
    u64 q[12];
} H39LoadImage;
typedef struct { s16 dbp, b, c, d, e, f, g, h; s32 pad[4]; u8 data[1]; } AB;
void func_00180ab8(AB *a, s16 base) {
    H39LoadImage li; s16 v = a->dbp;
    if (v >= 0x3800) v = v + base - 0x3800;
    PlatGsSetDefLoadImage(&li, v, a->c, a->d, a->e, a->f, a->g, a->h);
    PlatFlushCache(0); PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&li, a->data);
}

/* func_00180b40 (from hand/text_00180000_h39.c). */
typedef struct {
    s16 unk00, dbp;
    s16 unk04, psm;
    s32 pad08[4];
    s32 off18;
} H39Img;
void func_00180b40(H39Img *img, s16 base) {
    H39LoadImage li;
    s16 dbp = img->dbp;

    if (dbp == 0)
        return;
    if (dbp >= 0x3D40)
        dbp = dbp + base - 0x3D40;
    switch (img->psm) {
    case 19:
        PlatGsSetDefLoadImage(&li, dbp, 1, 0, 0, 0, 16, 16);
        break;
    case 20:
        PlatGsSetDefLoadImage(&li, dbp, 1, 0, 0, 0, 8, 2);
        break;
    default:
        return;
    }
    PlatFlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&li, (u8 *) img + img->off18 + 0x20);
}

/* func_00180c20 (from hand/text_00180000_h39.c). */
void func_00180c20(s32 *data, u8 *mask, s16 base) {
    s32 *p;
    s32 n;
    s32 i;
    u8 m;

    i = 0;
    m = 0;
    p = func_001803c0(func_001803b8(data), 1);
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        void *s = (void *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;
        if (!j)
            m = mask[k];
        if (m & 1)
            func_00180ab8(s, base);
    }
}

/* func_00180ce0 (from hand/text_00170000_h11.c). */
void func_00180ce0(void *h) {
    s32 *p = func_001803c0(func_001803b8(h), 1);
    s32 n = *p++;
    s32 i;
    for (i = 0; i < n; i++) func_00180ab8(*p++, 0);
}

/* func_00180d50 (from hand/text_00180000_h39.c). */
void func_00180d50(s32 *data, u8 *mask, s16 base) {
    s32 *p;
    s32 n;
    s32 i;
    u8 m;

    m = 0;
    if (data == NULL)
        return;
    i = 0;
    p = func_001803c0(func_001803b8(data), 1);
    n = *p++;
    for (; i < n; i++, m >>= 1) {
        H39Img *s = (H39Img *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;

        if (!j)
            m = mask[k];
        if (m & 1)
            func_00180b40(s, base);
    }
}

/* func_00180e10 (from hand/text_00170000_h11.c). */
void func_00180e10(void *h) {
    s32 *p;
    s32 n;
    s32 i;
    if (!h) return;
    p = func_001803c0(func_001803b8(h), 1);
    n = *p++;
    for (i = 0; i < n; i++) func_00180b40(*p++, 0);
}

/* func_00180e80 (from auto/text_00180000_4.c). */
void func_00180e80(void *arg0) {
    M2C_FIELD(arg0, s8 *, 8) = -1;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
}

/* func_00180ea0 (from hand/text_00170000_h11.c). */
typedef struct { s32 a, b, c; } V12;
typedef struct { V12 a[10]; V12 b[6]; } SEA0;
void func_00180ea0(SEA0 *s) {
    s32 i;
    for (i = 0; i < 10; i++) func_00180e80(&s->a[i]);
    for (i = 0; i < 6; i++) func_00180e80(&s->b[i]);
}

/* func_00180f18 (from hand/text_00180000_b07.c). */
typedef kh1_s128 u128_80f18;
typedef struct {
    s32 key;
    s32 mask;
    s8 start;
    s8 len;
    u8 used;
} Slot;
typedef struct {
    u8 pad[0x88];
    s32 key;
    u8 pad8c[7];
    u8 bit;
} SlotOwner;
s32 func_00180f18(Slot *slots, s32 cnt, SlotOwner *o, u8 n) {
    union { u128_80f18 q; u8 b[16]; } buf;
    s32 i;
    s32 j;
    s32 run;
    s32 found;
    s32 key;
    s32 bit;
    Slot *best;
    Slot *s;

    key = o->key;
    bit = o->bit;
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && key == slots[i].key) {
            s32 m = slots[i].mask;
            j = 1 << bit;
            if (m & j) return -1;
            slots[i].mask = m | j;
            return slots[i].start;
        }
    }
    buf.q = KH1_Q(0);
    for (i = 0; i < cnt; i++) {
        if (slots[i].used) {
            j = slots[i].len;
            if (j > 0) {
                u8 *p = (u8 *)((u32)slots[i].start + (u32)buf.b);
                do {
                    j--;
                    *p++ = 1;
                } while (j != 0);
            }
        }
    }
    run = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        if (buf.b[i]) {
            run = 0;
        } else {
            run++;
            if (run == n) {
                found = i - n + 1;
                break;
            }
        }
    }
    if (found > 0) {
        for (i = 0; i < cnt; i++) {
            if (!slots[i].used) {
                slots[i].key = key;
                slots[i].mask = 1 << bit;
                slots[i].used = 1;
                slots[i].len = n;
                slots[i].start = found;
                return found;
            }
        }
    }
    best = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        s = &slots[i];
        if (s->used) {
            if (n == s->len) {
                s->key = key;
                s->mask = 1 << bit;
                return s->start;
            }
            if (n < s->len) {
                if (best == 0 || s->len - n < found) {
                    found = s->len - n;
                    best = s;
                }
            }
        }
    }
    if (best) {
        best->key = key;
        best->len = n;
        best->mask = 1 << bit;
        return best->start;
    }
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && slots[i].start < n) func_00180e80(&slots[i]);
    }
    for (i = 0; i < cnt; i++) {
        if (!slots[i].used) {
            slots[i].key = key;
            slots[i].mask = 1 << bit;
                slots[i].used = 1;
            slots[i].len = n;
            slots[i].start = 0;
            return 0;
        }
    }
    return -1;
}

/* func_00181238 (from auto/text_00180000_3.c). */
void func_00181238(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00180f18(arg0, 0xA, arg1, (s32) M2C_FIELD(arg1, u8 *, 0x91));
    if (temp_v0 < 0) {
        M2C_FIELD(arg1, s16 *, 0xA4) = 0;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xA4) = (s16) ((temp_v0 << 7) + 0x3800);
}

/* func_00181280 (from auto/text_00180000.c). */
void func_00181280(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = func_00180f18(arg0 + 0x78, 6, arg1, M2C_FIELD(arg1, u8 *, 0x92));
    if (temp_v0 < 0) {
        M2C_FIELD(arg1, s16 *, 0xA6) = 0;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xA6) = (s16) ((temp_v0 << 5) + 0x3D40);
}

/* func_001812d0 (from auto/text_00180000_5.c). */
M2C_UNK func_0024edf0(void *, s32);
extern M2C_UNK D_00615E70;
void func_001812d0(void *arg0) {
    s32 sp[16];
    PlatVu0MulMatrix(sp, (M2C_UNK *)&D_002BBFA0, &D_00615E70);
    func_0024edf0(sp, M2C_FIELD(arg0, s32 *, 0x8C));
}

/* func_00181318 (from auto/text_00180000_3.c). */
s32 func_00181318(void) {
    s8 *var_a0;
    s32 var_a1;
    s32 var_a2;
    u16 temp_v1;

    var_a2 = 0;
    var_a0 = &D_00364130.i;
    var_a1 = 0xFF;
    do {
        temp_v1 = M2C_FIELD(var_a0, u16 *, 0x86);
        if ((temp_v1 & 1 & 0xFFFF) && !(temp_v1 & 4)) {
            var_a2 += M2C_FIELD(M2C_FIELD(var_a0, void **, 0x8C), s32 *, 0xF0);
        }
        var_a1 -= 1;
        var_a0 += 0xC0;
    } while (var_a1 >= 0);
    return var_a2;
}

/* func_00181368 (from hand/text_00180000_h39.c). */
typedef H39Obj_364130 H39Obj;
void func_0011d3c8(u16, s32, s32);
void func_00182788();
#define func_00182788 ((void (*)(H39Obj *)) func_00182788)
s32 func_00181368(s32 t) {
    s32 i;

    for (i = 0; i < 256; i++) {
        H39Obj *e = &D_00364130.h39Obj[i];

        if ((e->flags & 1) && !(e->flags & 4) && e->x98 < t) {
            if (e->p8c->xfc)
                func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            e->flags |= 4;
            return 1;
        }
    }
    return 0;
}
#undef func_00182788

/* func_00181410 (from hand/text_00180000_h12.c). */
typedef PppMng_364130 PppMng;
void func_00182840();
#define func_00182788 ((void (*)(PppMng *)) func_00182788)
#define func_00182840 ((void (*)(PppMng *)) func_00182840)
s32 func_00181410(void) {
    PppMng *m = D_00364130.pppMng;
    s32 i;

    for (i = 0; i < 256; i++, m++) {
        if ((m->st & 1) && !(m->st & 4) && m->unk98 < 0) {
            if (m->owner->unkFC != 0)
                func_0011d3c8(m->owner->unkFC, m->unkA8, 60);
            func_00182788(m);
            func_00182840(m);
            return 1;
        }
    }
    return 0;
}
#undef func_00182788
#undef func_00182840

/* func_00181b30 (from hand/text_00180000_b07.c). */
typedef struct {
    u8 pad[0x14];
    s32 flags;
} PLink;
typedef struct {
    u8 pad[0xb0];
    u8 xb0[0x48];
    u8 xf8;
    u8 padf9[3];
    u16 xfc;
    u16 xfe;
} POwner;
typedef struct PObj {
    u8 pad0[0x58];
    s32 x58;
    u8 pad5c[4];
    s32 x60;
    u8 pad64[0x22];
    u16 flags;
    s32 key;
    POwner *own;
    u8 x90;
    u8 x91;
    u8 pad92;
    u8 x93;
    PLink *link;
    s32 x98;
    f32 x9c;
    union {
        u64 d;
        struct {
            s32 lo;
            s16 a4;
            s16 a6;
        } s;
    } xa0;
    s32 xa8;
    f32 xac;
    union {
        u64 d;
        u8 b[8];
    } xb0;
    u8 padb8[8];
} PObj;
typedef struct {
    s32 key;
    s32 bit;
} PCur;
typedef struct {
    V12 a[16];
} SEA0_81b30;
PObj *D_00575A10[0x10c] ALIGNED(16);
extern PCur D_003701B0;
extern u8 D_00370140[];
extern u8 D_00370170[];
extern PlatDmaChan *D_00372908;
extern s32 D_0061621C;
extern s32 D_00616224;
extern s32 D_00616228;
extern s32 D_0061622C;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;
void func_001aa008(void);
void func_001aa8d0(void);
void *func_00122048(s32, s32);
void func_0017f948(void);
s32 func_00181608(PObj **);
void func_00180280(PObj *);
s32 func_00183878();
void func_001827f0();
void func_0017f970(void);
s32 func_00183958();
void func_001220b8(void *);
#define func_00183878 ((s32 (*)(PObj *, s32)) func_00183878)
#define func_00182788 ((void (*)(PObj *)) func_00182788)
#define func_001827f0 ((void (*)(PObj *)) func_001827f0)
#define func_00182840 ((void (*)(PObj *)) func_00182840)
#define func_00183958 ((s32 (*)(PObj *)) func_00183958)
void func_00181b30(void) {
    SEA0_81b30 tmp;
    void *h;
    PCur *cur;
    s32 first;
    s32 i;
    s32 n;

    first = 1;
    D_003701B0.bit = -1;
    D_003701B0.key = 0;
    func_00180ea0(&tmp);
    func_001aa008();
    func_001aa8d0();
    h = func_00122048(0x4000, 16);
    func_0017f948();
    n = func_00181608(D_00575A10);
    for (i = 0; i < n; i++) {
        PObj *e = D_00575A10[i];

        if ((e->flags & 1) && !(e->flags & 4)) {
            f32 lim = 0.0f;
            s32 same;
            s32 k;

            if (e->link->flags & 0x20) lim -= D_002BBDEC + D_002BBDEC;
            if (lim < e->xac) {
                if (D_0061621C) continue;
                if (e->xb0.d & 0xFF0000FF00) continue;
                e->xac -= D_002BBDFC;
                continue;
            }
            func_00180280(e);
            if (e->x90 && e->own->xf8) continue;
            if (e->flags & 0x20) continue;
            if (first) {
                func_00180ce0(D_00370130);
                first = 0;
                func_00180e10(D_00370130);
                PlatFlushCache(0);
                PlatGsSyncPath(0, 0);
                PlatDmaSend(D_00372908, D_00370140);
            }
            if (!e->x90 && !e->xb0.b[7] && e->x91) {
                func_00181238(&tmp, e);
                func_00181280(&tmp, e);
                if (e->xa0.s.a4) func_00180c20(e->key, e->own->xb0, e->xa0.s.a4);
                if (e->xa0.s.a6) func_00180d50(e->key, e->own->xb0, e->xa0.s.a6);
                if (e->xa0.d & 0xFFFFFFFF00000000) {
                    PlatFlushCache(0);
                    PlatGsSyncPath(0, 0);
                    PlatDmaSend(D_00372908, D_00370140);
                }
            } else {
                e->xa0.s.a4 = 0;
                e->xa0.s.a6 = 0;
            }
            same = 0;
            if (D_003701B0.key == e->key) same = D_003701B0.bit == e->x93;
            if (!same) func_00180a48(e);
            func_001807d8(e);
            k = 1;
            if (e->x90 || e->xb0.b[7]) k = 0;
            D_00616228 = 0;
            D_00616224 = D_0061622C;
            if (func_00183878(e, k)) {
                if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                func_00182788(e);
                func_001827f0(e);
            }
            if (!e->x90 && !e->xb0.b[7]) func_0017f970();
            cur = &D_003701B0;
            cur->key = e->key;
            cur->bit = e->x93;
        } else if (e->flags & 2) {
            if (e->flags & 0x10) e->flags &= ~0x10;
            else func_00182840(e);
        } else if (e->flags & 4) {
            if (func_00183958(e)) {
                e->flags &= ~4;
                func_001827f0(e);
            }
        }
    }
    PlatFlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatDmaSend(D_00372908, D_00370170);
    func_001220b8(h);
}
#undef func_00183878
#undef func_00182788
#undef func_001827f0
#undef func_00182840
#undef func_00183958

/* func_00181f50 (from auto/text_00180000_12.c). */
void memset(s32, s32, s32);
void func_00181f50(s32 arg0) {
  memset(arg0, 0, 0xC0);
  *((s32 *) (((s8 *) arg0) + 0)) = 0;
  *((s16 *) (((s8 *) arg0) + 0x86)) = 9;
  *((f32 *) (((s8 *) arg0) + 0x4C)) = 1.0f;
  *((s32 *) (((s8 *) arg0) + 4)) = 0;
  *((s32 *) (((s8 *) arg0) + 8)) = 0;
  *((f32 *) (((s8 *) arg0) + 0xC)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x20)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x24)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x28)) = 1.0f;
 do { *((f32 *) (((s8 *) arg0) + 0x2C)) = 1.0f; *((s32 *) (((s8 *) arg0) + 0x10)) = 0; *((s32 *) (((s8 *) arg0) + 0x14)) = 0; *((s32 *) (((s8 *) arg0) + 0x18)) = 0; *((s32 *) (((s8 *) arg0) + 0x1C)) = 0; *((f32 *) (((s8 *) arg0) + 0x30)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x34)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x38)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x3C)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x40)) = 1.0f; } while (0);
  *((f32 *) (((s8 *) arg0) + 0x44)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x48)) = 1.0f;
}

/* func_00181fe0 (from hand/text_s7_w24.c). */
typedef E0C0_364130_3 E0C0;
void func_00181fe0(E0C0 **out) {
    s32 i;
    E0C0 *e;
    for (i = 0; i < 256; i++) {
        e = &D_00364130.e0C0_3[i];
        if (!(e->x80 & 0x3000000000000)) {
            func_00181f50(e);
            *out = e;
            break;
        }
    }
}

/* func_00182148 (from hand/text_00180000_h39.c). */
extern H39Mtx D_00615EB0;
H39Mtx D_00615EF0 ALIGNED(16);
extern H39Mtx D_00615F30;
extern u128 D_00615F70;
extern u128 D_00615F80;
u128 D_00615F90 ALIGNED(16);
u128 D_00615FA0 ALIGNED(16);
f32 D_00615FB0 ALIGNED(16);
extern H39Mtx D_00616040;
extern H39Mtx D_00616180;
extern f32 D_002E27A0;
void func_00182148(H39Mtx *view, H39Mtx *world, u128 *eye, u128 *at) {
    H39Mtx unused; /* only takes stack space */

    PlatVu0CopyMatrix(&D_00615EF0, &D_00615EB0);
    D_00615EB0.r[0] = view->r[0];
    D_00615EB0.r[1] = view->r[1];
    D_00615EB0.r[2] = view->r[2];
    D_00615EB0.r[3] = view->r[3];
    D_00616040.r[0] = world->r[0];
    D_00616040.r[1] = world->r[1];
    D_00616040.r[2] = world->r[2];
    D_00616040.r[3] = world->r[3];
    D_00615F90 = D_00615F70;
    D_00615FA0 = D_00615F80;
    D_00615F70 = *eye;
    D_00615F80 = *at;
    D_00615FB0 = D_002E27A0;
    PlatVu0InversMatrix(&D_00615F30, &D_00615EB0);
    PlatVu0MulMatrix(&D_00616180, &D_00616040, &D_00615EB0);
}

/* func_00182270 (from hand/text_00170000_s6_10.c). */
void func_00182270(void) {
    f32 f = (f32)D_002BBDF8 * 1.3435446;
#ifdef KH1_PS2
    __asm__ volatile(
        "mfc1 $3, %0\n"
        "qmtc2 $3, $vf1\n"
        "vrinit R, $vf1x\n"
        "qmtc2 %1, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrget.x $vf1x, R\n"
        "qmfc2 $8, $vf1\n"
        :
        : "f"(f), "r"(-1)
        : "$3", "$8");
#else
    PlatVu0RInit(PlatVu0Bits(f));
    PlatVu0RXor(0xFFFFFFFF);
#endif
}

/* func_001822f8 (from hand/text_00180000_h12.c). */
typedef struct PppSys PppSys;
typedef void (*PppSysFn)(PppSys *);
typedef struct {
    void *fn[8];
} PppModule;
typedef struct {
    u8 pad[0x9C];
    u8 unk9C;
} PppInst;
typedef struct {
    s32 unk0;
    PppInst *inst;  /* +0x4 */
    s32 time;       /* +0x8 */
    s32 unkC;
} PppSlotE;
struct PppSys {
    u8 pad00[0x44];
    f32 scale;         /* +0x44 */
    u8 pad48[0xC];
    s32 end;           /* +0x54 */
    s32 time;          /* +0x58 */
    s32 prev;          /* +0x5C */
    u8 pad60[4];
    s32 nmod;          /* +0x64 */
    s32 nslot;         /* +0x68 */
    u8 pad6C[8];
    s32 unk74;         /* +0x74 */
    PppModule **mods;  /* +0x78 */
    s32 pad7C;
    PppSlotE *slots;   /* +0x80 */
    u8 unk84;          /* +0x84 */
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 unkB0;         /* +0xB0 */
};
void func_001822f8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[4];
        if (fn)
            fn(s);
    }
}

/* func_00182368 (from hand/text_00180000_h12.c). */
void func_00182368(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[5];
        if (fn)
            fn(s);
    }
}

/* func_001823d8 (from hand/text_00180000_h12.c). */
void func_001823d8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nmod; i++) {
        PppSysFn fn = (PppSysFn) s->mods[i]->fn[6];
        if (fn)
            fn(s);
    }
}

/* pppResetComponents (from hand/text_00180000_h12.c). */
typedef void (*PppCompFn)(void *, PppEntry *);
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;       /* +0x20 */
    s16 pad24;
    s16 n;             /* +0x26 */
    PppEntry ent[1];   /* +0x28 */
} PppProg;
typedef struct {
    s32 unk00, unk04;
    PppProg **prog;    /* +0x08 */
} PppObj;
typedef union {
    void *p;
    s16 h;
} PppSlot;
void pppResetComponents(PppObj *obj) {
    PppProg *p = *obj->prog;
    PppSlot *d = (PppSlot *) ((u8 *) obj + p->dataoff);
    s32 i;

    for (i = 0; i < p->n; i++) {
        PppEntry *e = &p->ent[i];
        PppClass *c = e->cls;
        d->p = e->data;
        d++;
        if (c && c->reset)
            ((PppCompFn) c->reset)(obj, e);
    }
}

/* pppConComponents (from hand/text_00180000_h12.c). */
void pppConComponents(PppObj *obj) {
    PppProg *p = *obj->prog;
    PppSlot *d = (PppSlot *) ((u8 *) obj + p->dataoff);
    s32 i;

    for (i = 0; i < p->n; i++) {
        PppEntry *e = &p->ent[i];
        PppClass *c = e->cls;
        d->p = e->data;
        d++;
        if (c && c->con)
            ((PppCompFn) c->con)(obj, e);
    }
}

/* func_00182788 (from auto/text_00180000_2.c). */
M2C_UNK pppDesObject(M2C_UNK *);
void func_00183b20();
extern s32 D_00615E64;
#define func_00183b20 ((M2C_UNK (*)(s32, s32)) func_00183b20)
void func_00182788(void *arg0) {
    M2C_UNK *temp_s0;
    M2C_UNK *var_a0;
    s32 temp_a1;

    var_a0 = M2C_FIELD(arg0, M2C_UNK **, 0x74);
    if (var_a0 != NULL) {
        do {
            temp_s0 = *var_a0;
            pppDesObject(var_a0);
            var_a0 = temp_s0;
        } while (var_a0 != NULL);
    }
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x80);
    M2C_FIELD(arg0, M2C_UNK **, 0x74) = NULL;
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(arg0, s32 *, 0x80) = 0;
    }
}
#undef func_00183b20

/* func_001827f0 (from hand/text_00180000_h12.c). */
typedef struct {
    u8 pad00[0x14];
    s32 flags;
} PppLink;
void func_001827f0(PppMng *m) {
    if (m->link) {
        ((PppLink *) m->link)->flags &= ~1;
        ((PppLink *) m->link)->flags |= 2;
    }
    if (m->st & 1)
        m->st = (m->st & ~1) | 2;
}

/* func_00182840 (from auto/text_00180000_5.c). */
void func_00182840(s32 arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x94);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        memset(arg0, 0, 0xC0);
    }
}

/* func_00182e78 (from auto/text_00180000_5.c). */
void func_00183a00();
#define func_00183a00 ((void (*)(s32, s32, s32)) func_00183a00)
void func_00182e78(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00615E64 = arg0;
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
    }
    func_00183a00(arg0, arg2, arg3);
}
#undef func_00183a00

/* func_001837a8 (from hand/text_00180000_h12.c). */
PppInst *func_00182588(PppSys *, PppSlotE *);
void func_001837a8(PppSys *s) {
    s32 i;

    for (i = 0; i < s->nslot; i++) {
        PppSlotE *e = &s->slots[i];
        if (e->time <= s->time) {
            e->time = 0x7FFFFFFF;
            e->inst = func_00182588(s, e);
            e->inst->unk9C = 0;
        }
    }
}

/* func_00183840 (from auto/text_00180000.c). */
M2C_UNK func_00182ec0(s32);
extern s32 D_00615E60;
#define func_00182368 ((M2C_UNK (*)()) func_00182368)
void func_00183840(s32 arg0) {
    D_00615E60 = arg0;
    func_00182368();
    func_001837a8(arg0);
    func_00182ec0(arg0);
}
#undef func_00182368

/* func_00183878 (from hand/text_00180000_h39.c). */
typedef struct H39Sys {
    u8 pad00[0x54];
    s32 end;           /* +0x54 */
    s32 time;          /* +0x58 */
    s32 prev;          /* +0x5C */
    u8 pad60[0x14];
    s32 unk74;         /* +0x74 */
    u8 pad78[0xC];
    u8 unk84;          /* +0x84 */
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 flags;         /* +0xB0 */
} H39Sys;
void pppStepPrograms(void);
#define D_00615E60 (*(H39Sys **)&D_00615E60)
s32 func_00183878(H39Sys *s) {
    s32 t;

    D_00615E60 = s;
    pppStepPrograms();
    func_001823d8(s);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return 0;
    t = s->time;
    s->prev = t;
    s->time = t + 0x1000;
    if (s->unk84) {
        if (s->unk85)
            return s->unk74 == 0;
        if (s->time > 0x6FFFFFFF) {
            s->time = 0x70000000;
            s->prev = 0x6FFFF000;
        }
        return 0;
    }
    return s->time >= s->end;
}
#undef D_00615E60

/* func_00183958 (from hand/text_00180000_h12.c). */
#define D_00615E60 (*(PppSys **)&D_00615E60)
s32 func_00183958(PppSys *s) {
    s32 t;

    D_00615E60 = s;
    if (D_0061621C != 0 || (s->unkB0 & 0xFF0000FF00ULL))
        return 0;
    t = s->time;
    s->prev = t;
    s->time = t + 0x1000;
    if (s->unk84 != 0) {
        if (s->unk85)
            return s->unk74 == 0;
        if (s->time > 0x6FFFFFFF) {
            s->time = 0x70000000;
            s->prev = 0x6FFFF000;
        }
        return 0;
    }
    return s->time >= s->end;
}
#undef D_00615E60

/* func_001839f8 (from auto/text_00180000_2.c). */
void func_001839f8(void) {

}

/* func_00183a00 (from hand/text_00180000_h12.c). */
typedef struct PppBlk {
    struct PppBlk *next;  /* +0x0 */
    struct PppBlk *prev;  /* +0x4 */
    struct PppBlk *used;             /* +0x8 */
    s32 pad;
} PppBlk;
typedef struct {
    PppBlk *unk0;
    PppBlk *first;  /* +0x4 */
    PppBlk *last;   /* +0x8 */
    PppBlk *unkC;
} PppHeap;
void func_00183a00(PppHeap *h, PppBlk *mem, s32 size) {
    h->first = mem;
    h->unk0 = NULL;
    h->last = (PppBlk *) ((u8 *) mem + size - 16);
    mem->prev = NULL;
    mem->next = h->last;
    mem->used = NULL;
    {
        PppBlk *l = h->last;
        PppBlk *f = h->first;
        l->used = (PppBlk *) 1;
        l->prev = f;
        l->next = NULL;
    }
    h->unkC = NULL;
}

/* func_00183b20 (from hand/text_00180000_h12.c). */
void func_00183b20(PppHeap *h, u8 *p) {
    PppBlk *b = (PppBlk *) (p - 16);
    PppBlk *q;

    b->used = NULL;
    h->unk0 = b;
    h->unkC = (PppBlk *) ((s32) h->unkC - ((s32) b->next - (s32) b));
    q = b->prev;
    if (q != NULL && q->used == NULL) {
        q->next = b->next;
        b->next->prev = q;
        b = q;
    }
    {
        PppBlk *n = b->next;
        if (n->used == NULL) {
            b->next = n->next;
            n->next->prev = b;
        }
    }
}

/* pppKeThLzFrame (from auto/text_00180000.c). */
void pppKeThLzFrame(void) {

}

/* pppKeThLzCon (from auto/text_00180000.c). */
void pppKeThLzCon(void) {

}

/* pppKeThLzDes (from auto/text_00180000.c). */
void pppKeThLzDes(void) {

}

/* pppKeThCpFrame (from auto/text_00180000.c). */
void pppKeThCpFrame(void) {

}

/* pppKeThCpCon (from auto/text_00180000.c). */
void pppKeThCpCon(void) {

}

/* pppKeThCpDes (from auto/text_00180000.c). */
void pppKeThCpDes(void) {

}

/* pppKeThCpSftFrame (from auto/text_00180000.c). */
void pppKeThCpSftFrame(void) {

}

/* pppKeAccSpdSvFrame (from auto/text_00180000.c). */
void pppKeAccSpdSvFrame(void) {

}

/* pppKeAccSpdSvCon (from auto/text_00180000.c). */
void pppKeAccSpdSvCon(void) {

}

/* func_00183be0 (from auto/text_00180000_6.c). */
M2C_UNK func_001a50d0(M2C_UNK *, s32);
M2C_UNK func_001a5150(M2C_UNK *, s32);
M2C_UNK func_001a51d0(M2C_UNK *, s32);
void func_00183be0(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a51d0(sp, M2C_FIELD(arg1, s32 *, 8));
    func_001a5150(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 4));
    PlatVu0MulMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a50d0(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 0));
    PlatVu0MulMatrix(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

