#include "ppp.h"

typedef int u128 __attribute__((mode(TI)));
typedef void (*H39CompFn)(void *, PppEntry *);

/* The current matrix object (D_00615E68): +0x10 its matrix, +0x50 a
 * second (drawing) matrix. */
typedef struct {
    u8 pad[0x10];
    f32 m[4][4];  /* +0x10 */
    f32 m2[4][4]; /* +0x50 */
} H39MObj;

extern H39MObj *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
void func_002672f8(f32 *, f32 (*)[4], f32 *);

/* A texture header inside a sprite record (+0x10): +8/+0xC are offsets
 * from itself to its pixels and palette, +0x10..+0x14 its sizes. */
#include "data/types/nostrict_text_00180000_h39.h"

typedef struct {
    s16 id, w, h;
    s16 pad06;
    s32 unk08;
    s32 pad0C;
    H39Tex tex; /* +0x10 */
} H39Spr2;

/* Texture slots (0x24 bytes), indexed by the sprite's id. */

#include "data/pieces/D_00362730.h"

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

typedef struct {
    u8 pad00[0x20];
    s32 dataoff;  /* +0x20 */
    s16 prio;     /* +0x24 */
    s16 n;        /* +0x26 */
    PppEntry ent[1]; /* +0x28 */
} H39Prog;
struct H39Inst;
/* A program slot: the program, its newest instance, ... */
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
/* The effect system (D_00615E60). */
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
extern H39ShSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
H39Inst *func_0017f958(H39ShSys *, s32);
void pppConComponents(H39Inst *);
/* Makes an instance of the slot's program and links it into the
 * system's list, which is sorted by program priority (+0x24). */
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

typedef union { f32 f[4]; } H39V4 __attribute__((aligned(16)));
typedef struct { u8 pad[0xC]; s32 slot; s32 off; } H39NKey;
extern H39PSys *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
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
    func_002672f8(v.f, D_00615E68->m, v.f);
    out = (f32 *) ((u8 *) inst + key->off + 0xA0);
    out[0] = v.f[0];
    out[1] = v.f[1];
    out[2] = v.f[2];
}

/* The object a program runs in: +0x0C is its frame counter. */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef struct {
    s32 frame;
    u16 d[4]; /* +0x4 */
} H39ColKey;

typedef struct {
    u16 c[4]; /* +0x0 */
    u32 rgba; /* +0x8: c scaled by the system colour, packed */
} H39Col;

extern s32 D_0061621C;

void pppColorFrame(PppObject *obj, H39ColKey *key, PppEntry *e) {
    H39Col *w = (H39Col *) ((u8 *) obj + e->offsets[0] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->c[0] += key->d[0];
        w->c[1] += key->d[1];
        w->c[2] += key->d[2];
        w->c[3] += key->d[3];
    }
    /* Widen the four u16 to words, scale by col in VU0, pack to bytes. */
    __asm__ volatile(
        "lw $2, 4(%0)\n"
        "pextlw $2, $2, $0\n"
        "lw $3, 0(%0)\n"
        "or $2, $2, $3\n"
        "pextlh $2, $0, $2\n"
        "qmtc2 $2, $vf1\n"
        "vitof0.xyzw $vf1xyzw, $vf1xyzw\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmul.xyzw $vf1xyzw, $vf1xyzw, $vf2xyzw\n"
        "vftoi0.xyzw $vf1xyzw, $vf1xyzw\n"
        "qmfc2 $2, $vf1\n"
        "psrlw $2, $2, 7\n"
        "ppach $2, $0, $2\n"
        "ppacb $2, $0, $2\n"
        "sw $2, 8(%0)\n"
        :
        : "r"(w), "r"(D_00615E60->col)
        : "$2", "$3", "memory");
}


void func_00183be0(f32 (*)[4], f32 *);
void func_001a5250(f32 (*)[4], f32 *);
void func_001a52e0(f32 (*)[4], f32 *);
void func_001a5370(f32 (*)[4], f32 *);
void func_001a5400(f32 (*)[4], f32 *);
void func_001a5490(f32 (*)[4], f32 *);

/* Scales the xyz of a matrix row in VU0. */
static inline void h39ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        :
        : "r"(row), "r"(s));
}

/* The matrix classes: work 0 is the position, 1 the rotation (made into
 * the matrix by the class's rotation order), 2 the scale. */
#define H39_MATRIX_FRAME(name, rot)                                       \
    void name(void *obj, void *key, PppEntry *e) {                        \
        f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);           \
        f32 *ang = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);           \
        f32 *scl = (f32 *) ((u8 *) obj + e->offsets[2] + 0xA0);           \
                                                                          \
        rot(D_00615E68->m, ang);                                          \
        h39ScaleRow(D_00615E68->m[0], scl[0]);                            \
        h39ScaleRow(D_00615E68->m[1], scl[1]);                            \
        h39ScaleRow(D_00615E68->m[2], scl[2]);                            \
        D_00615E68->m[3][0] = pos[0];                                     \
        D_00615E68->m[3][1] = pos[1];                                     \
        D_00615E68->m[3][2] = pos[2];                                     \
    }

H39_MATRIX_FRAME(pppMatrixFrame, func_00183be0)
H39_MATRIX_FRAME(pppMatrixXZYFrame, func_001a5250)
H39_MATRIX_FRAME(pppMatrixYZXFrame, func_001a52e0)
H39_MATRIX_FRAME(pppMatrixYXZFrame, func_001a5370)
H39_MATRIX_FRAME(pppMatrixZXYFrame, func_001a5400)
H39_MATRIX_FRAME(pppMatrixZYXFrame, func_001a5490)

void sceVu0UnitMatrix(f32 (*)[4]);

void pppMatrixSclFrame(void *obj, void *key, PppEntry *e) {
    f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);
    f32 *scl = (f32 *) ((u8 *) obj + e->offsets[1] + 0xA0);

    sceVu0UnitMatrix(D_00615E68->m);
    D_00615E68->m[0][0] = scl[0];
    D_00615E68->m[1][1] = scl[1];
    D_00615E68->m[2][2] = scl[2];
    D_00615E68->m[3][0] = pos[0];
    D_00615E68->m[3][1] = pos[1];
    D_00615E68->m[3][2] = pos[2];
}

#include "data/pieces/D_003701F0.h"
extern f32 D_006160C0[4][4];
extern f32 D_00616080[4][4]; /* src/data/bss_0061.c: u8 D_00616080[0x40] */
void func_00267560(f32 *, f32 *, f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

void pppDrawMatrixWoodFrame(void) {
    func_00267560(D_00615E68->m2[0], D_00615E68->m[0], D_003701F0[0]);
    func_00267560(D_00615E68->m2[1], D_00615E68->m[1], D_003701F0[1]);
    func_00267560(D_00615E68->m2[2], D_00615E68->m[2], D_003701F0[2]);
    *(u128 *) D_00615E68->m2[3] = *(u128 *) D_00615E68->m[3];
    sceVu0MulMatrix(D_00615E68->m2, D_006160C0, D_00615E68->m2);
    func_002672f8(D_00615E68->m2[3], D_00616080, D_00615E68->m[3]);
}

typedef struct {
    s32 frame;
    s32 unk04;
    f32 d[6]; /* +0x8 */
} H39TsKey;

/* Work 2: two (value, speed, accel) triples, stepped every frame; the
 * keyframe adds to all six. */
void pppDrawMdlTsFrame(PppObject *obj, H39TsKey *key, PppEntry *e) {
    f32 *w = (f32 *) ((u8 *) obj + e->offsets[2] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w[1] += w[2];
    w[0] += w[1];
    w[4] += w[5];
    w[3] += w[4];
    if (key->frame == obj->frame) {
        w[0] += key->d[0];
        w[1] += key->d[1];
        w[2] += key->d[2];
        w[3] += key->d[3];
        w[4] += key->d[4];
        w[5] += key->d[5];
    }
}

typedef struct {
    s32 frame;
    s32 slot;   /* +0x4: program slot to start, -1 none */
    s32 off;    /* +0x8: work offset of its position */
    u8 every;   /* +0xC */
} H39PApKey;

/* Every `every` frames, starts the slot's program at work 0's position. */
void pppPointApFrame(PppObject *obj, H39PApKey *key, PppEntry *e) {
    f32 *pos = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);
    u8 *w = (u8 *) obj + e->offsets[1] + 0xA0;
    H39Inst *inst;
    H39Slot2 *s;
    f32 *out;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (w[1] == 0) {
        if (key->slot == -1)
            return;
        inst = NULL;
        s = &D_00615E60->slots[key->slot];
        if (s != NULL) {
            inst = func_00182588(D_00615E60, s);
            inst->unk04 = (s32) obj;
        }
        out = (f32 *) ((u8 *) inst + key->off + 0xA0);
        out[0] = pos[0];
        out[1] = pos[1];
        out[2] = pos[2];
        w[1] = key->every;
    }
    w[1]--;
}

/* --- The float-vector random classes (pppSRand*FVFrame): on the first
 * frame they draw one random number per component into the work area, then
 * add amp * r - amp (amp * r for Up/Down) to the vector in the object. */

extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */

typedef struct {
    s32 frame;
    s32 dst;    /* +0x4: work offset of the value, -1: scratch */
    f32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} H39RandFVKey;

f32 func_001892a8(u8);
f32 func_00189470(u8);
f32 func_00189648(u8);
f32 func_00189298(f32, f32);
f32 func_00189468(f32, f32);
f32 func_00189640(f32, f32);

#define H39_SRAND_FV(name, rnd, add)                                       \
    void name(PppObject *obj, H39RandFVKey *key, PppEntry *e) {            \
        f32 *w;                                                            \
        f32 *v;                                                            \
                                                                           \
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))    \
            return;                                                        \
        if (obj->frame == 0) {                                             \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
            w[0] = rnd(key->twice);                                        \
            w[1] = rnd(key->twice);                                        \
            w[2] = rnd(key->twice);                                        \
        } else {                                                           \
            if (key->frame != obj->frame)                                  \
                return;                                                    \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
        }                                                                  \
        if (key->dst != -1)                                                \
            v = (f32 *) ((u8 *) obj + key->dst + 0xA0);                    \
        else                                                               \
            v = &D_00575A00;                                               \
        v[0] += add(key->amp[0], w[0]);                                    \
        v[1] += add(key->amp[1], w[1]);                                    \
        v[2] += add(key->amp[2], w[2]);                                    \
    }

H39_SRAND_FV(pppSRandFVFrame, func_001892a8, func_00189298)
H39_SRAND_FV(pppSRandUpFVFrame, func_00189470, func_00189468)
H39_SRAND_FV(pppSRandDownFVFrame, func_00189648, func_00189640)


/* --- Depth sorting of the effect objects (D_00364130, 256 of 0xC0). */

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

extern H39Obj D_00364130[256];
extern f32 D_00615EB0[4][4]; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */

/* Quicksort of a[lo..hi] into descending order, moving b along. */
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

/* Lists the live objects far to near (by view depth) into list; returns
 * how many. */
s32 func_00181608(H39Obj **list) {
    f32 depth[256];
    H39Q v;
    H39Obj *e = D_00364130;
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
                func_002672f8(v.f, D_00615EB0, v.f);
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

/* --- Program loading. A loaded program file holds, from +0x110, a header
 * (+8/+0xC: offsets of the class-id table and the pointer table) and from
 * +0x10 a chain of programs, each starting with the offset of the next
 * (0 ends it; the last link is cleared). */

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

typedef struct { s32 frame; s32 id; u16 speed; } H39ShKey;
typedef struct { u16 time, frame, prev; } H39ShW;
void pppDrawShapeFrame(PppObject *obj, H39ShKey *key, PppEntry *e) {
    H39ShW *w;
    H39Shape *sh;
    H39ShFrm *f;
    u16 cur;
    H39ShEnt *se;
    s8 fl;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = (H39ShW *) ((u8 *) obj + e->offsets[0] + 0xA0);
    if (key->id == 0xFFFF)
        return;
    cur = w->frame;
    se = &D_00615E64->shapes[key->id];
    sh = se->shape;
    f = &sh->frm[w->prev];
    w->prev = cur;
    w->time += key->speed;
    if (w->time < f->dur)
        return;
    w->time -= f->dur;
    w->frame = cur + 1;
    if (w->frame < sh->n)
        return;
    fl = f->flags;
    w->time = 0;
    if (fl & 0x80) {
        w->frame = 0;
        return;
    }
    w->frame--;
}
