#include "ppp.h"

typedef void (*H39CompFn)(void *, PppEntry *);

/* The current matrix object (D_00615E68): +0x10 its matrix, +0x50 a
 * second (drawing) matrix. */
typedef struct {
    u8 pad[0x10];
    f32 m[4][4];  /* +0x10 */
    f32 m2[4][4]; /* +0x50 */
} H39MObj;

extern H39MObj *D_00615E68;
void func_002672f8(f32 *, f32 (*)[4], f32 *);

/* A texture header inside a sprite record (+0x10): +8/+0xC are offsets
 * from itself to its pixels and palette, +0x10..+0x14 its sizes. */
typedef struct {
    s32 unk00, unk04;
    s32 off08, off0C;
    s16 unk10, unk12, unk14;
} H39Tex;

typedef struct {
    s16 id, w, h;
    s16 pad06;
    s32 unk08;
    s32 pad0C;
    H39Tex tex; /* +0x10 */
} H39Spr2;

/* Texture slots (0x24 bytes), indexed by the sprite's id. */
typedef struct {
    s32 a, b, c;
    s32 pad0C, pad10;
    void *p14, *p18;
    H39Tex *tex;
    s32 unk20;
} H39Slot;

extern H39Slot D_00362730[];

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
extern s32 D_00615E64;
H39Inst *func_0017f958(s32, s32);
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

void func_00183b20(s32, H39Inst *);

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

typedef int u128 __attribute__((mode(TI)));

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

extern f32 D_003701F0[3];
extern f32 D_006160C0[4][4];
extern f32 D_00616080[4][4];
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
