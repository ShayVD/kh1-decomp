/* The ppp vertex classes, -fno-strict-aliasing (docs/modules.md "Session
 * 50"): pppVertexAp / ApLc / ApAt start effects at a mesh's vertices (all of
 * them, in turn, or at random; func_00184918 / func_00184cb8 fill the new
 * instance from the vertex), and pppVtMimeDraw morphs a mesh's vertices
 * towards a target by the work area's weight.  Read from the code, not
 * proved by a boot. */
#include "ppp.h"
#include "platform/vu.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/bss_0061.h"
#include "m2c.h"

/* func_00184918 (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad[0x10];
    f32 m[4][4];  /* +0x10 */
    f32 m2[4][4]; /* +0x50 */
} H39MObj;
extern H39MObj *D_00615E68;
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
H39Inst *func_00182588(H39PSys *, H39Slot2 *);
typedef union { f32 f[4]; } H39V4 __attribute__((aligned(16)));
typedef struct { u8 pad[0xC]; s32 slot; s32 off; } H39NKey;
extern H39PSys *D_00615E60;
void func_00184918(s32 owner, H39NKey *key, s16 *pos) {
    H39V4 v;
    H39Inst *inst;
    H39Slot2 *s;
    f32 *out;

    if (key->slot == -1)
        return;
    inst = NULL;
    s = &D_00615E60->slots[key->slot];
    if (s != NULL) {
        inst = func_00182588(D_00615E60, s);
        inst->unk04 = owner;
    }
    v.f[0] = pos[0];
    v.f[1] = pos[1];
    v.f[2] = pos[2];
    v.f[3] = 1.0f;
    PlatVu0ApplyMatrix(v.f, D_00615E68->m, v.f);
    out = (f32 *) ((u8 *) inst + key->off + 0xA0);
    out[0] = v.f[0];
    out[1] = v.f[1];
    out[2] = v.f[2];
}

/* pppVertexApFrame (from hand/nostrict/text_00180000_h62.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;
extern s32 D_0061621C;
static inline f32 vu0Rand(void) {
    f32 r;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r)
        :
        : "$8");
    return r;
}
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
typedef struct {
    u8 pad00[0x10];
    u8 m10[0x40];   /* +0x10 */
    u8 m50[0x40];   /* +0x50 */
    VtxS16 *vtx;    /* +0x90 */
    s32 unk94;      /* +0x94 */
} VtxCur;
extern VtxSys *D_00615E64;
extern s32 D_00616234;
typedef struct {
    s32 frame;
    s16 map;     /* +0x4 */
    u8 count;    /* +0x6 */
    u8 interval; /* +0x7 */
    u8 mode;     /* +0x8 */
} VtxApKey;
typedef struct {
    u16 idx;   /* +0x0 */
    u16 timer; /* +0x2 */
} VtxApWork;
#define D_00615E60 ((PppSystem *) D_00615E60)
#define D_00615E68 ((VtxCur *) D_00615E68)
void pppVertexApFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxS16 v;
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    VtxS16 *vtx;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        vtx = D_00615E68->vtx;
        if (vtx == 0)
            vtx = D_00615E64->slots[m->slot].vtx;
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                v = vtx[m->map[i]];
                func_00184918(obj, key, &v);
            }
            break;
        case 1:
            while (n--) {
                v = vtx[m->map[(s32) (vu0Rand() * m->n)]];
                func_00184918(obj, key, &v);
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}
#undef D_00615E60
#undef D_00615E68

/* func_00184cb8 (from hand/nostrict/text_00180000.c). */
#define func_00182588 ((void *(*)(void *, s32, M2C_UNK)) func_00182588)
#define D_00615E60 ((void *) D_00615E60)
void func_00184cb8(s32 arg0, void *arg1, void *arg2) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *var_a2;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0xC);
    if (temp_v0 != -1) {
        var_a2 = NULL;
        temp_v0_2 = M2C_FIELD(D_00615E60, s32 *, 0x80) + (temp_v0 * 0x10);
        if (temp_v0_2 != 0) {
            var_a2 = func_00182588(D_00615E60, temp_v0_2, 0);
            M2C_FIELD(var_a2, s32 *, 4) = arg0;
        }
        temp_v0_3 = var_a2 + M2C_FIELD(arg1, s32 *, 0x10);
        temp_v0_4 = temp_v0_3 + 0xA0;
        M2C_FIELD(temp_v0_3, f32 *, 0xA0) = (f32) M2C_FIELD(arg2, s16 *, 0);
        M2C_FIELD(temp_v0_4, f32 *, 4) = (f32) M2C_FIELD(arg2, s16 *, 2);
        M2C_FIELD(temp_v0_4, f32 *, 8) = (f32) M2C_FIELD(arg2, s16 *, 4);
    }
}
#undef func_00182588
#undef D_00615E60

/* pppVertexApLcFrame (from hand/nostrict/text_00180000_h62.c). */
#define D_00615E60 ((PppSystem *) D_00615E60)
#define D_00615E68 ((VtxCur *) D_00615E68)
void pppVertexApLcFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxS16 v;
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    VtxS16 *vtx;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        vtx = D_00615E68->vtx;
        if (vtx == 0)
            vtx = D_00615E64->slots[m->slot].vtx;
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                v = vtx[m->map[i]];
                func_00184cb8(obj, key, &v);
            }
            break;
        case 1:
            while (n--) {
                v = vtx[m->map[(s32) (vu0Rand() * m->n)]];
                func_00184cb8(obj, key, &v);
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}
#undef D_00615E60
#undef D_00615E68

/* pppVertexApAtFrame (from hand/nostrict/text_00180000_h62.c). */
void func_00185000(PppObject *, VtxApKey *, u16);
#define D_00615E60 ((PppSystem *) D_00615E60)
void pppVertexApAtFrame(PppObject *obj, VtxApKey *key, PppEntry *e) {
    VtxApWork *w = PPP_WORK(VtxApWork, obj, e, 0);
    VtxMap *m;
    s32 n;
    u16 i;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL) || D_00616234 != 0)
        return;
    if (key->map < 0)
        return;
    if (w->timer == 0) {
        m = &D_00615E64->maps[key->map];
        n = key->count;
        switch (key->mode) {
        case 0:
            while (n--) {
                if (w->idx >= m->n)
                    w->idx = 0;
                i = w->idx++;
                func_00185000(obj, key, i);
            }
            break;
        case 1:
            while (n--) {
                func_00185000(obj, key, (s32) (vu0Rand() * m->n));
            }
            break;
        }
        w->timer = key->interval;
    }
    w->timer--;
}
#undef D_00615E60

/* pppVtMimeDraw (from hand/nostrict/text_00180000_h62.c). */
void *func_0017f958(VtxSys *, s32);
typedef struct {
    s32 frame;
    s32 from; /* +0x4 */
    s32 to;   /* +0x8 */
} MKey;
typedef struct {
    f32 t;       /* +0x0 */
    f32 y, z;
    VtxS16 *buf; /* +0xC */
} MWork;
#define D_00615E68 ((VtxCur *) D_00615E68)
void pppVtMimeDraw(PppObject *obj, MKey *key, PppEntry *e) {
    MWork *w;
    VtxSys *sys;
    VtxS16 *a, *b, *o;
    s32 n;

    if (key->from == 0xFFFF && key->to == 0xFFFF)
        return;
    w = PPP_WORK(MWork, obj, e, 0);
    sys = D_00615E64;
    a = sys->slots[key->from].vtx;
    b = sys->slots[key->to].vtx;
    n = sys->slots[key->from].n;
    if (w->buf == 0)
        w->buf = func_0017f958(sys, n * 6);
    o = w->buf;
    while (n--) {
        o->x = (b->x - a->x) * w->t + a->x;
        o->y = (b->y - a->y) * w->t + a->y;
        o->z = (b->z - a->z) * w->t + a->z;
        o++;
        a++;
        b++;
    }
    D_00615E68->vtx = w->buf;
}
#undef D_00615E68

