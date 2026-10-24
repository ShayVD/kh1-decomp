/* The ppp effect manager core, without strict aliasing (docs/modules.md
 * "Session 51"): the object matrices (func_00180280, func_00182870 builds
 * D_00615E70), the texture, CLUT and palette tables of a resource
 * (func_00180878 / 001808f8 / 001809b8 fill D_00363930 ... by mask), the depth
 * sort (func_001814b0 quicksort, func_00181608 collects the live objects),
 * the update loop over D_00364130 (func_00181738), the manager init
 * (func_00182058: heap D_00595E40 of 0x80000 bytes, tables, unit matrix),
 * making and destroying an instance (func_00182588, pppDesObject), loading a
 * system from its data (func_00182c10), pppRelocProgram, the frame steps of
 * the programs (func_00182ec0, pppStepPrograms) and the effect heap's
 * allocator (func_00183a48).  pppsys.c has the rest.  Each section names the
 * file its code came from.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/types/nostrict_text_00170000_s6_10.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362454.h"
#include "data/pieces/D_00362710.h"
#include "data/pieces/D_00364130.h"
#include "ppp.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

/* func_00180280 (from hand/nostrict/text_00180000_c2.c). */
typedef kh1_s128 u128;
typedef union { V4 v; u128 q; } V4A;
void func_00182870();
extern V4A D_00615FC0[4];
extern V4A D_00615EB0[4];
extern V4A D_00615E70[4];
extern V4A D_00616000_rows[4] __asm__("D_00616000");
#define D_00616010 (D_00616000_rows + 1)
extern V4A D_00616040[4];
extern V4A D_00616080[4];
extern V4A D_006160C0[4];
/* func_00180280 and func_00181738, which needs it defined above (moved from
 * text_00170000_h38.c; both match without strict aliasing). */
void func_00180280(void *o) {
    V4A b, a, c;
    func_00182870(o);
    PlatVu0MulMatrix(D_00615FC0, D_00615EB0, D_00615E70);
    PlatVu0MulMatrix(D_00616080, D_00616040, D_00615FC0);
    a.v.x = D_00615FC0[1].v.x;
    a.v.y = D_00615FC0[1].v.y;
    a.v.z = D_00615FC0[1].v.z;
    a.v.w = 0.0f;
    PlatVu0Normalize(&a, &a);
    D_00616010[0].q = a.q;
    b.v.x = a.v.y;
    b.v.y = -a.v.x;
    b.v.z = 0.0f;
    b.v.w = 0.0f;
    PlatVu0Normalize(&b, &b);
    D_00616010[-1].q = b.q;
    PlatVu0OuterProduct(&c, &b, &a);
    PlatVu0Normalize(&c, &c);
    D_00616010[1].q = c.q;
    D_00616010[2].q = D_00615FC0[3].q;
    PlatVu0MulMatrix(D_006160C0, D_00616040, &D_00616010[-1]);
}

/* func_00180878 (from hand/nostrict/text_00170000_s6_10.c). */
typedef struct { s16 idx; s16 pad2; s32 x4; s32 x8; s32 xc; } It10;
typedef struct { void *p; s32 x4; } E8;
extern E8 D_00363930[];
s32 *func_00180878(s32 *p, u8 *mask) {
    s32 n;
    s32 i;
    u8 m;

    n = *p++;
    m = 0;
    i = 0;
    for (; i < n; i++, m >>= 1) {
        It10 *it = (It10 *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;

        if (!j)
            m = mask[k];
        if (m & 1) {
            E8 *d = &D_00363930[it->idx];
            d->p = it + 1;
            d->x4 = it->x8;
        }
    }
    return p;
}

/* func_001808f8 (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    s16 id, w, h;
    s16 pad06;
    s32 unk08;
    s32 pad0C;
    H39Tex tex; /* +0x10 */
} H39Spr2;
s32 *func_001808f8(s32 *p, u8 *mask) {
    s32 n;
    s32 i;
    u8 m;

    n = *p++;
    m = 0;
    i = 0;
    for (; i < n; i++, m >>= 1) {
        H39Spr2 *s = (H39Spr2 *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;

        if (!j)
            m = mask[k];
        if (m & 1) {
            H39Tex *t = &s->tex;
            H39Slot *d = &D_00362730[s->id];

            d->tex = t;
            d->a = t->unk12;
            d->b = t->unk14;
            d->c = t->unk10;
            d->p14 = (u8 *) t + t->off08;
            d->p18 = (u8 *) t + t->off0C;
            d->unk20 = s->unk08;
        }
    }
    return p;
}

/* func_001809b8 (from hand/nostrict/text_00170000_s6_10.c). */
typedef struct { s32 idx; u16 x4; u16 pad6; u16 x8; u16 pada; } It0C;
typedef struct { u16 a; u16 b; void *p; } E8b;
extern E8b D_00363D30[];
s32 *func_001809b8(s32 *p, u8 *mask) {
    s32 n;
    s32 i;
    u8 m;

    n = *p++;
    m = 0;
    i = 0;
    for (; i < n; i++, m >>= 1) {
        It0C *it = (It0C *) *p++;
        s32 k = i >> 3;
        s32 j = i & 7;

        if (!j)
            m = mask[k];
        if (m & 1) {
            E8b *d = &D_00363D30[it->idx];
            d->a = it->x4;
            d->b = it->x8;
            d->p = it + 1;
        }
    }
    return p;
}

/* func_001814b0 (from hand/nostrict/text_00180000_h39.c). */
typedef union {
    u128 q;
    f32 f[4];
} H39Q;
typedef struct H39Obj {
    H39Q pos;   /* +0x00 */
    u8 pad10[0x86 - 0x10];
    u16 flags;  /* +0x86 */
    u8 pad88[0xB0 - 0x88];
    u8 mode;    /* +0xB0: 1 always behind, 2 always in front */
    u8 padb1[0xC0 - 0xB1];
} H39Obj;
void func_001814b0(f32 *a, H39Obj **b, s32 lo, s32 hi) {
    f32 p = a[(lo + hi) / 2];
    s32 i = lo;
    s32 j = hi;

    for (;;) {
        while (p < a[i])
            i++;
        while (a[j] < p)
            j--;
        if (i >= j)
            break;
        {
            f32 t = a[i];
            H39Obj *u;

            a[i] = a[j];
            a[j] = t;
            u = b[i];
            b[i] = b[j];
            b[j] = u;
        }
        i++;
        j--;
    }
    if (lo < i - 1)
        func_001814b0(a, b, lo, i - 1);
    if (j + 1 < hi)
        func_001814b0(a, b, j + 1, hi);
}

/* func_00181608 (from hand/nostrict/text_00180000_h39.c). */
#define D_00615EB0 ((f32 (*)[4]) D_00615EB0)
s32 func_00181608(H39Obj **list) {
    f32 depth[256];
    H39Q v;
    H39Obj *e = (*(H39Obj (*)[256])&D_00364130);
    H39Obj **l = list;
    s32 n = 0;
    s32 i;

    for (i = 0; i < 256; i++, e++) {
        if (e->flags) {
            switch (e->mode) {
            case 1:
                depth[n] = 1000000.0f;
                break;
            case 2:
                depth[n] = 0.0f;
                break;
            default:
                v.q = e->pos.q;
                v.f[3] = 1.0f;
                PlatVu0ApplyMatrix(v.f, D_00615EB0, v.f);
                depth[n] = v.f[2];
                break;
            }
            *l++ = e;
            n++;
        }
    }
    if (n >= 2)
        func_001814b0(depth, list, 0, n - 1);
    return n;
}
#undef D_00615EB0

/* func_00181738 (from hand/nostrict/text_00180000_c2.c). */
typedef POwner_364130 POwner;
typedef PObj_364130 PObj;
typedef struct {
    s32 key;
    s32 bit;
} PCur;
extern PCur D_003701B0;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;
void func_0011d210(u16, s32, PObj *, u16);
void func_0011d1e0(u16, s32, PObj *, u16);
void func_0011d2d0(u16, s32, s32);
void func_0011d3c8(u16, s32, s32);
u8 func_001812d0(PObj *);
void func_00180a48(PObj *);
void func_00183840(PObj *);
s32 func_00183878(PObj *, s32);
void func_00182788(PObj *);
void func_001827f0(PObj *);
void func_00181738(void) {
    s32 i;

    D_003701B0.bit = -1;
    D_003701B0.key = 0;
    for (i = 0; i < 256; i++) {
        PObj *e = &D_00364130.pObj[i];
        f32 lim;
        s32 fl;
        s32 done;
        s32 same;

        if (!(e->flags & 1)) continue;
        if (e->flags & 4) continue;
        lim = 0.0f;
        fl = e->link->flags;
        if (fl & 0x20) lim -= D_002BBDEC + D_002BBDEC;
        if (lim < e->xac) {
            e->link->flags = fl | 0x10;
            if (e->xac <= D_002BBDFC) e->link->flags &= ~0x10;
            continue;
        }
        e->link->flags = fl & ~0x10;
        if (e->flags & 8) {
            POwner *o = e->own;
            if (o->xfc) {
                if (e->xb5 == 1) func_0011d210(o->xfc, e->xa8, e, o->xfe);
                else func_0011d1e0(o->xfc, e->xa8, e, o->xfe);
            }
            e->flags &= ~8;
        } else if (e->xb1) {
            if (!(e->flags & 0x40) && e->own->xfc) {
                func_0011d2d0(e->own->xfc, e->xa8, 1);
                e->flags |= 0x40;
            }
        } else if ((e->flags & 0x40) && e->own->xfc) {
            func_0011d2d0(e->own->xfc, e->xa8, 0);
            e->flags &= ~0x40;
        }
        func_00180280(e);
        if (e->x58 && !e->xb3) e->x90 = func_001812d0(e);
        else e->x90 = 0;
        if (e->x90 && e->own->xf8) continue;
        if (e->flags & 0x20) continue;
        same = 0;
        if (D_003701B0.key == e->key) same = D_003701B0.bit == e->x93;
        if (!same) func_00180a48(e);
        e->x9c += D_002BBDFC;
        if (e->x9c >= 2.0f) {
            done = 0;
            e->xb4 = 0;
            if (e->x60 > 0) {
                for (; e->x60 > 0; e->x60--) {
                    func_00183840(e);
                    if (func_00183878(e, 0)) {
                        if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                        func_00182788(e);
                        done = 1;
                        func_001827f0(e);
                        e->flags |= 0x10;
                        break;
                    }
                }
            }
            if (!done) {
                for (e->x9c -= 2.0f; e->x9c >= 2.0f; e->x9c -= 2.0f) {
                    func_00183840(e);
                    if (func_00183878(e, 0)) {
                        if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                        func_00182788(e);
                        done = 1;
                        func_001827f0(e);
                        e->flags |= 0x10;
                        break;
                    }
                }
                if (!done) func_00183840(e);
            }
        } else {
            e->xb4 = 1;
            func_00183840(e);
        }
        D_003701B0.key = e->key;
        D_003701B0.bit = e->x93;
    }
}

/* func_00182058 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00362730 D_00362730_2058
#define D_00363930 D_00363930_2058
#define D_00363D30 D_00363D30_2058
#define D_00364130 D_00364130_2058
#define D_00595E40 D_00595E40_2058
#define D_00615E40 D_00615E40_2058
#define D_00615E64 D_00615E64_2058
#define D_006161C0 D_006161C0_2058
#define D_00616200 D_00616200_2058
#define D_0061621C D_0061621C_2058
#define D_00616220 D_00616220_2058
typedef kh1_u128 u128_82058;
typedef struct { u8 pad[0x10]; void *x10; void *x14; void *x18; } Pmgr;
extern V4 D_00616200 __asm__("D_00616200");
typedef struct E0C0_82058 {
    u8 pad0[0x86];
    u16 flags;
    u8 pad88[0xc0 - 0x88];
} E0C0_82058;
extern Pmgr D_00615E40 __asm__("D_00615E40");
extern u8 D_00595E40[] __asm__("D_00595E40");
extern s32 D_0061621C __asm__("D_0061621C");
extern Pmgr *D_00615E64 __asm__("D_00615E64");
extern u8 D_00362730[] __asm__("D_00362730");
extern u8 D_00363930[] __asm__("D_00363930");
extern u8 D_00363D30[] __asm__("D_00363D30");
extern E0C0_82058 D_00364130[256] __asm__("D_00364130");
extern s32 D_00616220 __asm__("D_00616220");
extern V4 D_006161C0[4] __asm__("D_006161C0");
void func_0017f9a8(void) __asm__("func_0017f9a8");
void func_00183a00(void *, void *, s32) __asm__("func_00183a00");
void *memset(void *, s32, u32);
void func_0017f910(s32, s32) __asm__("func_0017f910");
void func_00182058(void) {
    Pmgr *m;
    s32 i;
    func_0017f9a8();
    m = &D_00615E40;
    D_0061621C = 0;
    func_00183a00(m, D_00595E40, 0x80000);
    m->x10 = D_00362730;
    m->x14 = D_00363930;
    m->x18 = D_00363D30;
    D_00615E64 = m;
    D_00616220 = 0;
    memset(D_00364130, 0, sizeof(D_00364130));
    for (i = 0; i < 256; i++) D_00364130[i].flags = 0;
    PlatVu0UnitMatrix(D_006161C0);
    *(u128_82058 *)&D_00616200 = KH1_Q(0);
    D_00616200.w = 1.0f;
    func_0017f910(0, -1);
}
#undef D_00362730
#undef D_00363930
#undef D_00363D30
#undef D_00364130
#undef D_00595E40
#undef D_00615E40
#undef D_00615E64
#undef D_006161C0
#undef D_00616200
#undef D_0061621C
#undef D_00616220

/* func_00182588 (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;  /* +0x20 */
    s16 prio;     /* +0x24 */
    s16 n;        /* +0x26 */
    PppEntry ent[1]; /* +0x28 */
} H39Prog;
struct H39Inst;
typedef struct {
    H39Prog *prog;          /* +0x0 */
    struct H39Inst *last;   /* +0x4 */
    s32 time;               /* +0x8 */
    u16 count;              /* +0xC */
} H39Slot2;
typedef struct H39Inst {
    struct H39Inst *next;   /* +0x0 */
    s32 unk04;
    H39Slot2 *slot;         /* +0x8 */
    s32 frame;              /* +0xC */
    u8 pad10[0x80];
    s32 unk90, unk94;
    u8 pad98[4];
    u8 unk9C, unk9D, unk9E;
} H39Inst;
typedef struct {
    u8 pad00[0x30];
    f32 col[4];             /* +0x30: colour scale */
    u8 pad40[0x34];
    H39Inst *head;          /* +0x74 */
    u8 pad78[8];
    H39Slot2 *slots;        /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;              /* +0xB0 */
} H39PSys;
typedef struct {
    s16 unk00;
    s16 dur;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad5[3];
} H39ShFrm;
typedef struct {
    u8 pad[6];
    s16 n;      /* +0x6 */
    u8 pad8[8];
    H39ShFrm frm[1]; /* +0x10 */
} H39Shape;
typedef struct { H39Shape *shape; s32 unk04; } H39ShEnt;
typedef struct {
    u8 pad00[0x14];
    H39ShEnt *shapes;  /* +0x14 */
} H39ShSys;
extern H39ShSys *D_00615E64;
H39Inst *func_0017f958(H39ShSys *, s32);
void pppConComponents(H39Inst *);
H39Inst *func_00182588(H39PSys *sys, H39Slot2 *slot) {
    H39Prog *prog = slot->prog;
    H39Inst *inst = func_0017f958(D_00615E64, prog->dataoff + prog->n * 4);
    H39Inst *q;
    H39Inst **pp;

    inst->unk9C = 1;
    inst->frame = 0;
    inst->unk90 = 0;
    inst->unk94 = 0;
    inst->slot = slot;
    inst->unk9D = 0;
    inst->unk9E = 0;
    q = sys->head;
    if (q == NULL) {
        slot->last = inst;
        sys->head = inst;
        inst->next = NULL;
    } else if (slot->last != NULL) {
        inst->next = slot->last->next;
        slot->last->next = inst;
    } else {
        pp = &sys->head;
        do {
            if (q->slot->prog->prio >= prog->prio) {
                slot->last = inst;
                *pp = inst;
                inst->next = q;
                goto done;
            }
            pp = &q->next;
            q = *pp;
        } while (q != NULL);
        slot->last = inst;
        *pp = inst;
        inst->next = NULL;
    }
done:
    slot->count++;
    pppConComponents(inst);
    return inst;
}

/* pppDesObject (from hand/nostrict/text_00180000_h39.c). */
typedef void (*H39CompFn)(void *, PppEntry *);
void func_00183b20(H39ShSys *, H39Inst *);
void pppDesObject(H39Inst *obj) {
    H39Slot2 *slot = obj->slot;
    H39Prog *p = slot->prog;
    s32 i;

    for (i = 0; i < p->n; i++) {
        PppEntry *e = &p->ent[i];
        PppClass *c = e->cls;

        if (c && c->des)
            ((H39CompFn) c->des)(obj, e);
    }
    if (--slot->count == 0)
        slot->last = NULL;
    else if (slot->last == obj)
        slot->last = obj->next;
    func_00183b20(D_00615E64, obj);
}

/* func_00182870 (from hand/nostrict/text_00180000_b07.c). */
typedef struct {
    f32 x, y, z, w;
} V4F __attribute__((aligned(16)));
typedef struct {
    u8 pad0[0x80];
    f32 x80, x84, x88;
    u8 pad8c[4];
    u8 x90[0x10];
    f32 xa0, xa4, xa8;
    u8 padac[0xf9 - 0xac];
    u8 xf9;
    u8 xfa;
    u8 padfb[0x104 - 0xfb];
    s32 x104;
} MOwner;
typedef struct {
    f32 x0, x4, x8;
    u8 padc[4];
    u8 x10[0x10];
    f32 x20, x24, x28;
    u8 pad2c[0x14];
    f32 x40, x44, x48;
    u8 pad4c[0x8c - 0x4c];
    MOwner *own;
    u8 pad90[0xb2 - 0x90];
    u8 xb2;
} MObj;
/* The object matrix D_00615E70 (func_00182870 writes all four rows, PlatVu0MulMatrix 0x40 bytes): rows 1-3
 * were their own variables D_00615E80 / 90 / A0, and D_00615E70 had no C definition, so on the host the
 * matrix ran over whatever followed its first row. One definition (vita-port-plan 5.1i). */
V4F D_00615E70_rows[4] __asm__("D_00615E70") ALIGNED(16);
#define D_00615E80 (D_00615E70_rows[1])
#define D_00615E90 (D_00615E70_rows[2])
#define D_00615EA0 (D_00615E70_rows[3])
extern V4F D_00615F70;
void func_00183be0(void *, void *);
void func_00121fc4(void *, void *);
f32 atan2f(f32, f32);
f32 asinf(f32);
static inline void vu0ScaleRow2(f32 s, void *row) {
#ifdef KH1_PS2
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
#else
    PlatVu0ScaleXYZ(row, s);
#endif
}
static inline void setTrans(V4F *m, MObj *o) {
    m[3].x = o->x0;
    m[3].y = o->x4;
    m[3].z = o->x8;
}
static inline void addTrans(V4F *m, V4F *d) {
    m[3].x += d->x;
    m[3].z += d->z;
}
#define D_00615E70 (*(V4F (*)) &D_00615E70)
/* --- func_00182870: build the object matrix D_00615E70 --- */
void func_00182870(MObj *o) {
    V4F m[4];
    f32 ang[3];
    s32 i;

    func_00183be0(&D_00615E70, o->x10);
    vu0ScaleRow2(o->x20, &D_00615E70);
    vu0ScaleRow2(o->x24, &D_00615E80);
    vu0ScaleRow2(o->x28, &D_00615E90);
    if (o->own->xf9) {
        vu0ScaleRow2(o->x40, &D_00615E70);
        vu0ScaleRow2(o->x44, &D_00615E80);
        vu0ScaleRow2(o->x48, &D_00615E90);
    }
    setTrans(&D_00615E70, o);
    func_00183be0(m, o->own->x90);
    vu0ScaleRow2(o->own->xa0, &m[0]);
    vu0ScaleRow2(o->own->xa4, &m[1]);
    vu0ScaleRow2(o->own->xa8, &m[2]);
    m[3].x = o->own->x80;
    m[3].y = o->own->x84;
    m[3].z = o->own->x88;
    PlatVu0MulMatrix(&D_00615E70, &D_00615E70, m);
    if (o->own->xfa && o->own->x104 >= 0) {
        func_00183be0(m, o->own->x90);
        vu0ScaleRow2(o->own->xa0 * o->x20, &m[0]);
        vu0ScaleRow2(o->own->xa4 * o->x24, &m[1]);
        vu0ScaleRow2(o->own->xa8 * o->x28, &m[2]);
        PlatVu0CopyVector(&D_00615E70, &m[0]);
        PlatVu0CopyVector(&(&D_00615E70)[1], &m[1]);
        PlatVu0CopyVector(&(&D_00615E70)[2], &m[2]);
    }
    if (o->xb2) {
        addTrans(&D_00615E70, &D_00615F70);
    }
    {
        f32 *w;
        i = 0;
        w = &m[0].w;
        for (; i < 3; i++) {
            func_00121fc4(&m[i], &(&D_00615E70)[i]);
            D_003701F0[i] = *w;
            *w = 0.0f;
            w += 4;
        }
    }
    ang[0] = atan2f(-m[1].z, m[0].z);
    ang[1] = asinf(-m[2].z);
    ang[2] = atan2f(m[2].y, m[2].x);
    for (i = 0; i < 3; i++) D_003701E0[i] = ang[i] * 32768.0f / 3.1415926f;
    PlatVu0CopyVector(&D_003701D0, &D_00615EA0);
}
#undef D_00615E70

/* func_00182c10 (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60;
typedef struct {
    s16 x, y, z;
} VtxS16;
typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;
typedef struct {
    s32 n;       /* +0x0 */
    s32 pad04[4];
    VtxS16 *vtx; /* +0x14 */
    s32 pad18;
    DMdl *mdl;   /* +0x1C */
    s32 unk20;   /* +0x20 */
} VtxSlot;
typedef struct {
    u8 pad00[0x10];
    VtxSlot *slots; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} VtxSys;
typedef struct PNode {
    struct PNode *next; /* +0x0 */
    s32 pad[3];
    s32 val;            /* +0x10 */
} PNode;
typedef struct {
    PNode *node; /* +0x0 */
    s32 unk4;    /* +0x4 */
    s32 val;     /* +0x8 */
    s16 unkC;    /* +0xC */
    s8 idx;      /* +0xE */
    u8 padF;
} PSlot;
typedef struct {
    u8 pad[0x108];
    f32 unk108;
} POwner_82c10;
typedef struct {
    u8 pad00[0x54];
    s32 end;       /* +0x54 */
    s32 time;      /* +0x58 */
    u8 pad5C[8];
    s32 nmod;      /* +0x64 */
    s32 nslot;     /* +0x68 */
    u8 pad6C[4];
    PNode *list;   /* +0x70 */
    s32 unk74;     /* +0x74 */
    s32 *mods;     /* +0x78 */
    s32 *slotdata; /* +0x7C */
    PSlot *slots;  /* +0x80 */
    u8 unk84;      /* +0x84 */
    u8 unk85;      /* +0x85 */
    u8 pad86[6];
    POwner_82c10 *owner; /* +0x8C */
    u8 pad90[0xC];
    s32 unk9C;     /* +0x9C */
    u8 padA0[0xC];
    f32 unkAC;     /* +0xAC */
} PSys;
void func_001822f8(PSys *);
#define D_00615E64 ((VtxSys *) D_00615E64)
void func_00182c10(PSys *o, s32 *d, s32 flag) {
    s32 *p = d;
    s32 a, b, c;
    s32 *q, *r;
    PNode *n;
    PSlot *e;
    u8 i;

    *(PSys **) &D_00615E60 = o;
    o->end = *p++;
    a = *p++;
    b = *p++;
    c = *p++;
    q = (s32 *) ((u8 *) d + b);
    r = (s32 *) ((u8 *) d + c);
    if (a & 1)
        o->unk84 = 1;
    else
        o->unk84 = 0;
    o->nmod = *q++;
    o->mods = q;
    o->nslot = *r++;
    o->slotdata = r;
    if (o->nslot)
        o->slots = func_0017f958(D_00615E64, o->nslot << 4);
    else
        o->slots = 0;
    n = (PNode *) p;
    if (n->next)
        o->list = 0;
    o->time = 0;
    o->unk85 = 0;
    o->list = o->nslot ? n : 0;
    o->unk74 = 0;
    i = 0;
    e = o->slots;
    do {
        e->node = n;
        e->val = n->val; 
        e->idx = i++; 
        e->unk4 = 0; 
        e->unkC = 0; 
        n = n->next;
        e++;
    } while (n);
    if (flag)
        func_001822f8(o);
    o->unk9C = 0;
    o->unkAC = o->owner->unk108;
}
#undef D_00615E64

/* pppRelocProgram (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    s32 cls;     /* class id -> PppClass * */
    s32 stride;
    s32 data;    /* offset -> pointer */
    s32 offsets; /* offset -> pointer */
} H39REnt;
typedef struct H39RProg {
    union {
        s32 off;
        struct H39RProg *p;
    } next;          /* +0x0 */
    u8 pad04[0x22];
    s16 n;           /* +0x26 */
    H39REnt ent[1];  /* +0x28 */
} H39RProg;
typedef struct {
    s32 unk00, unk04;
    s32 offA;        /* +0x8: count, then class ids to turn into pointers */
    s32 offB;        /* +0xC: count, then offsets to turn into pointers */
    H39RProg first;  /* +0x10 */
} H39RHdr;
void pppRelocProgram(H39RHdr *h, PppClass *classes) {
    H39RProg *p;
    s32 *ta;
    s32 *tb;
    s32 na;
    s32 nb;
    s32 i, j, k;
    s32 off;

    /* Moving the parameter itself (not a new variable) keeps &h->first
     * as h + 0x10. */
    h = (H39RHdr *) ((u8 *) h + 0x110);
    ta = (s32 *) ((u8 *) h + h->offA);
    tb = (s32 *) ((u8 *) h + h->offB);
    na = *ta++;
    nb = *tb++;
    p = &h->first;

    off = p->next.off;
    if (off == 0)
        return;
    for (;;) {
        H39REnt *e;
        H39RProg *q;

        p->next.p = (H39RProg *) ((u8 *) h + off);
        for (i = 0; i < p->n; i++) {
            e = &p->ent[i];
            e->data = (s32) h + e->data;
            e->cls = (s32) &classes[e->cls];
            e->offsets = (s32) h + e->offsets;
        }
        q = p->next.p;
        if (q->next.off == 0)
            break;
        p = q;
        off = q->next.off;
    }
    p->next.p = NULL;
    for (j = 0; j < na; j++)
        ta[j] = (s32) &classes[ta[j]];
    for (k = 0; k < nb; k++)
        tb[k] += (s32) h;
}

/* func_00182ec0 (from hand/nostrict/text_00180000_s7_w13.c). */
typedef struct Cls { char *name; void (*frame)(void *, void *, void *); void *fn08; void *draw; } Cls;
typedef struct Ent { Cls *cls; u16 stride; u16 pad6; void *data; s32 *offsets; } Ent;
typedef struct Prog { u8 pad0[0x20]; s32 off20; u8 pad24[2]; s16 n; Ent ent[1]; } Prog;
typedef struct Obj {
    struct Obj *next;
    u8 pad4[8];
    s32 frame;
    u8 pad10[0x9c - 0x10];
    u8 x9c, x9d, x9e;
} Obj;
typedef struct { Prog *prog; Obj *obj; s32 val; u16 cnt; s8 idx; u8 padf; } Slot;
typedef struct { u8 pad0[0x68]; s32 nslot; u8 pad6c[0x80 - 0x6c]; Slot *slots; } PSys_82ec0;
extern s32 D_0061621C;
extern Obj *D_00615E68;
void pppResetComponents(Obj *);
/* func_00182ec0 (w13): c->draw read into a local before the 'fn == 0 || dr' test (loaded before the branch, fills the beqz slot). */
void func_00182ec0(PSys_82ec0 *o) {
    s32 i, j;
    for (i = 0; i < o->nslot; i++) {
        Slot *sl = &o->slots[i];
        Prog *pg = sl->prog;
        Ent *e;
        if (sl->cnt == 0) continue;
        for (j = 0; j < pg->n; j++) {
            Cls *c = (e = &pg->ent[j])->cls;
            Obj *ob = sl->obj;
            void (*fn)(void *, void *, void *) = c->frame;
            void *dr = c->draw;
            s32 k;
            if (fn == 0 || dr) continue;
            k = sl->cnt;
            do {
                s32 *pp = (s32 *)((u8 *)ob + pg->off20 + j * 4);
                Obj *nx = ob->next;
                if (!ob->x9c) {
                    s32 *d = (s32 *)*pp;
                    s32 *d2 = (s32 *)((u8 *)d + e->stride);
                    D_00615E68 = ob;
                    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) && ob->x9e) {
                        ob->frame = 0;
                        ob->x9d = 1;
                        pppResetComponents(ob);
                        ob->x9e = 0;
                    }
                    if (*d2 == ob->frame) {
                        d = d2;
                        *pp = (s32)d;
                    }
                    fn(ob, d, e);
                }
                ob = nx;
            } while (--k);
        }
    }
}

/* pppStepPrograms (from hand/nostrict/text_00180000_s7_w11.c). */
typedef struct PppObjS PppObjS;
typedef struct {
    PppClass *cls;
    u16 stride;
    u16 pad6;
    void *data;
    s32 *offsets;
} PppEnt;
typedef struct {
    u8 pad00[0x14];
    u32 life;          /* +0x14 */
    s32 start;         /* +0x18 */
    s32 delay;         /* +0x1C */
    s32 dataoff;       /* +0x20 */
    s16 pad24;
    s16 n;             /* +0x26 */
    PppEnt ent[1];     /* +0x28 */
} PppProgS;
struct PppObjS {
    PppObjS *next;     /* +0x00 */
    s32 unk04;
    PppProgS **prog;   /* +0x08 */
    s32 frame;         /* +0x0C */
    u8 pad10[0x8C];
    u8 skip;           /* +0x9C */
    u8 b9D;            /* +0x9D */
    u8 reset;          /* +0x9E */
};
typedef struct {
    PppProgS *prog;    /* +0x0 */
    PppObjS *obj;      /* +0x4 */
    s32 unk8;
    u16 n;             /* +0xC */
    u16 padE;
} PppSlotS;
typedef struct {
    u8 pad00[0x68];
    s32 nslot;         /* +0x68 */
    u8 pad6C[8];
    PppObjS *list;     /* +0x74 */
    u8 pad78[8];
    PppSlotS *slots;   /* +0x80 */
    u8 unk84;
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 flags;         /* +0xB0 */
} PppSysS;
typedef union {
    void *p;
    s16 h;
} PppDSlot;
typedef void (*PppStepFn)(PppObjS *, void *, PppEnt *);
#define D_00615E68 (*(PppObjS **) &D_00615E68)
extern s32 D_00616234[1];
/* frame functions pppStepPrograms skips (the program steps them itself) */
void pppRyjMegaBirthFrame();
void pppRyjMegaBirthModelFrame();
PppStepFn D_003701C0[0x4] ALIGNED(16) = {
    (void *)pppRyjMegaBirthFrame, (void *)pppRyjMegaBirthModelFrame, 0, 0,
};
static inline void stepObj(PppObjS *o) {
/*D*/
    PppProgS *p;
    PppDSlot *d;
    s32 i;
    PppEnt *e;
/*E*/
    p = *o->prog;
    d = (PppDSlot *) ((u8 *) o + p->dataoff);

    D_00615E68 = o;
    for (i = 0; i < p->n; i++) {
        PppClass *c;
        e = &p->ent[i];
        c = e->cls;
        if (c) {
            void *data = d->p;
            s32 *nx = (s32 *) ((u8 *) data + e->stride);
            PppStepFn fn;
            if (*nx == o->frame) {
                data = nx;
                (d++)->p = data;
            } else
                d++;
            fn = (PppStepFn) c->frame;
            if (fn) {
                s32 found = 0;
                PppStepFn *q;
                for (q = D_003701C0; *q; q++) {
                    if (fn == *q) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    fn(o, data, e);
            }
        }
    }
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        o->frame += 0x1000;
        if (o->frame > 0x6FFFFFFF)
            o->frame = 0x70000000;
    }
}
#define D_00615E60 ((PppSysS *) D_00615E60)
void pppStepPrograms(PppSysS *sys, s32 draw) {
    s32 i;

    for (i = 0; i < sys->nslot; i++) {
        PppSlotS *sl = &sys->slots[i];
        PppProgS *p = sl->prog;
        s32 k;

        if (sl->n == 0)
            continue;
        for (k = 0; k < p->n; k++) {
            PppEnt *e = &p->ent[k];
            PppObjS *o = sl->obj;
            PppStepFn ffn, dfn;
            s32 n;

            dfn = (PppStepFn) e->cls->draw;
            ffn = (PppStepFn) e->cls->frame;

            if (!dfn)
                continue;
            if (ffn) {
                n = sl->n;
                do {
                    PppObjS *next = o->next;
                    void **d = (void **) ((u8 *) o + p->dataoff + k * 4);
                    if (!o->skip) {
                        void *data = *d;
                        s32 *nx = (s32 *) ((u8 *) data + e->stride);
                        D_00615E68 = o;
                        if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) && o->reset) {
                            o->frame = 0;
                            o->b9D = 1;
                            pppResetComponents(o);
                            o->reset = 0;
                        }
                        if (*nx == o->frame) {
                            data = nx;
                            *d = data;
                        }
                        ffn(o, data, e);
                        if (draw)
                            dfn(o, data, e);
                    }
                    o = next;
                } while (--n);
            } else {
                n = sl->n;
                do {
                    void **d = (void **) ((u8 *) o + p->dataoff + k * 4);
                    if (!o->skip) {
                        void *data = *d;
                        s32 *nx = (s32 *) ((u8 *) data + e->stride);
                        D_00615E68 = o;
                        if (*nx == o->frame) {
                            data = nx;
                            *d = data;
                        }
                        if (draw)
                            dfn(o, data, e);
                    }
                    o = o->next;
                } while (--n);
            }
        }
        if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
            PppObjS *o = sl->obj;
            s32 n = sl->n;
            do {
                if (!o->skip) {
                    o->frame += 0x1000;
                    if (o->frame > 0x6FFFFFFF)
                        o->frame = 0x70000000;
                } else
                    o->skip = 0;
                o = o->next;
            } while (--n);
        }
    }
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        u32 acc = 0;
        PppObjS **prev = &sys->list;
        PppObjS *o = *prev;
        PppObjS *next;

        for (; o; o = next) {
            PppProgS *p;
            next = o->next;
            p = *o->prog;

            if (!sys->unk85 && !(o->frame < p->delay) && !(p->start > 0x6FFFFFFF) && !(p->delay > 0x6FFFFFFF)) {
                o->frame = 0;
                o->b9D = 1;
                pppResetComponents(o);
                if (p->start == 0) {
                    D_00616234[0] = 1;
                    stepObj(o);
                    D_00616234[0] = 0;
                    o->reset = 1;
                } else {
                    D_00616234[0] = 1;
                    while (o->frame < p->start)
                        stepObj(o);
                    D_00616234[0] = 0;
                }
            } else {
                acc |= p->life;
                if ((u32) o->frame >= p->life) {
                    *prev = next;
                    pppDesObject(o);
                    continue;
                }
            }
            prev = &o->next;
        }
        if (sys->unk85 && acc == 0x70000000) {
            PppObjS *q = sys->list;
            while (q) {
                PppObjS *nx = q->next;
                pppDesObject(q);
                q = nx;
            }
            sys->list = 0;
        }
    }
}
#undef D_00615E60
#undef D_00615E68

/* func_00183a48 (from hand/nostrict/text_00170000_s6_10.c). */
typedef struct PppBlk {
    struct PppBlk *next;
    struct PppBlk *prev;
    struct PppBlk *used;
    s32 pad;
} PppBlk;
typedef struct {
    PppBlk *unk0;
    PppBlk *first;
    PppBlk *last;
    PppBlk *unkC;
} PppHeap;
void *func_00183a48(PppHeap *h, s32 size) {
    PppBlk *b, *n, *nb, *p;
    size = ((size + 15) & ~15) + 16;
    if (h->unk0) {
        b = h->unk0->next;
    } else {
        goto init;
restart:
        h->unk0 = 0;
        b = h->last;
        goto search;
init:
        b = h->first->next;
        h->unk0 = h->first;
    }
search:
    for (;;) {
        p = b->prev;
        if (p == 0) {
            if (h->unk0) goto restart;
            return 0;
        }
        b = p;
        if (b->used) continue;
        n = b->next;
        if ((u8 *)n - (u8 *)b < size) continue;
        h->unkC = (PppBlk *)((s32)h->unkC + size);
        nb = (PppBlk *)((u8 *)b->next - size);
        if (nb != b && (u32)((u8 *)nb - (u8 *)b) >= 16) {
            h->unk0 = b;
            nb->prev = b;
            nb->next = n;
            n->prev = nb;
            b->next = nb;
            b = nb;
        } else {
            h->unk0 = 0;
        }
        b->used = (PppBlk *)1;
        return b + 1;
    }
}

