#include "common.h"
#include "data/bss_0062.h"
void func_002672f8(void *, void *, void *);

/* ---- func_001a26f0 ---- */
void *memset(void *, s32, u32);
f32 func_001a2178(void);
void func_002673b8(void *, void *);
void func_001a2248(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a26f0;
typedef struct { u8 pad[124]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a26f0;

static inline f32 vlen3_1a26f0(V4_1a26f0 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

void func_001a26f0(s32 a0, Emit_1a26f0 *e, V4_1a26f0 *m, void *b) {
    V4_1a26f0 t;
    f32 r, d;
    memset(m, 0, 96);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    func_002673b8(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a2178() - r;
        m->y = d * func_001a2178() - r;
        m->z = d * func_001a2178() - r;
    } while (r < vlen3_1a26f0(m));
    m->w = 1.0f;
    func_002672f8(m, D_00615F30, m);
    func_001a2248(e, m, b);
}

/* ---- func_001a30d8 ---- */
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_002676c0(f32 (*)[4], f32 (*)[4], f32);
void func_002675a8(f32 *, void *);
#include "data/pieces/D_003701F0.h"
extern f32 D_00615EB0[4][4]; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
typedef struct { u8 pad[44]; f32 rot; u8 pad2[8]; f32 sx, sy; } Spr;
typedef struct { u8 pad[164]; f32 sc, of; } Cam;

f32 func_001a30d8(s32 a0, f32 (*m)[4], Cam *c, s32 a3, Spr *s) {
    f32 r;
    sceVu0UnitMatrix(m);
    m[0][0] = s->sx * D_003701F0[0];
    m[1][1] = s->sy * D_003701F0[1];
    m[2][2] = s->sx * D_003701F0[0];
    if (s->rot != 0.0f) func_002676c0(m, m, s->rot * 3.1415927f / 180.0f);
    func_002675a8(m[3], s);
    func_002672f8(m[3], D_00615EB0, m[3]);
    m[3][1] *= c->sc;
    r = m[3][2];
    m[3][1] += c->of;
    sceVu0MulMatrix(m, D_00616040, m);
    return r;
}

/* ---- func_001a4028 ---- */
void *memset(void *, s32, u32);
f32 func_001a3650(void);
void func_002673b8(void *, void *);
void func_001a3720(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a4028;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a4028;

static inline f32 vlen3_1a4028(V4_1a4028 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

void func_001a4028(s32 a0, Emit_1a4028 *e, V4_1a4028 *m, void *b) {
    V4_1a4028 t;
    f32 r, d;
    memset(m, 0, 160);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    func_002673b8(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a3650() - r;
        m->y = d * func_001a3650() - r;
        m->z = d * func_001a3650() - r;
    } while (r < vlen3_1a4028(m));
    m->w = 1.0f;
    func_002672f8(m, D_00615F30, m);
    func_001a3720(e, m, b);
}

/* ---- func_001a47b0 ---- */
void *memset(void *, s32, u32);
f32 func_001a3650(void);
void func_002673b8(void *, void *);
void func_001a3720(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a47b0;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a47b0;

static inline f32 vlen3_1a47b0(V4_1a47b0 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

typedef struct { u8 pad[0xB0]; u64 flags; } PppSys;
extern s32 D_0061621C;
extern PppSys *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
typedef struct { u8 pad[32]; u16 alive; u8 pad2[126]; } Ptcl;
typedef struct { u8 pad[32]; } PtclX;
typedef struct { Ptcl *p; PtclX *x; s32 n; u8 pad[4]; u16 cnt; } PGrp;
typedef struct { u8 pad[4]; s32 id; u8 pad2[4]; u16 max; u16 ival; } PKey;
void func_001a4168(PGrp *, PKey *, Ptcl *, s32, PtclX *);

void func_001a47b0(PGrp *g, PKey *k, s32 a2) {
    Ptcl *p = g->p;
    PtclX *x = g->x;
    s32 n = g->n;
    s32 em = 0;
    s32 i;
    if (D_0061621C != 0) return;
    if (D_00615E60->flags & 0xFF0000FF00ULL) return;
    if (k->id == 0xffff) return;
    g->cnt++;
    for (i = 0; i < n; i++) {
        if (p->alive) {
            func_001a4168(g, k, p, a2, x);
        } else if (k->ival <= g->cnt && em < k->max) {
            func_001a4028((s32)g, (Emit_1a4028 *)k, (V4_1a4028 *)p, x);
            em++;
        }
        if (x) x++;
        p++;
    }
    if (em > 0) g->cnt = 0;
}



void func_001be820(void *, u32);

extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

#include "data/types/text_001a0000_h41.h"

void sceVu0UnitMatrix(f32 (*)[4]);

extern s32 D_00625640;

extern s32 D_00625640;
s32 func_001baad0(void);

extern s32 D_00625640;

typedef f32 Mtx[4][4];
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

float sqrtf(float);

float sqrtf(float);

typedef struct { f32 x, y, z, w; } Q;

/* needs make: uses rodata */

s32 func_001baad0(void);

#include "data/data_0037.h"
#include "data/data_0038.h"
#include "data/data_0048.h"
#include "data/data_003C.h"
#include "data/pieces/D_003773E0.h"
