/* The pppRyjMegaBirthModelFilter class (docs/modules.md "Session 49"),
 * with ryjmbmfilter.nostrict.c: the model variant of ryjmbfilter.c's
 * class, with the same layout of helpers: func_001a3698 a random s8 around
 * 0 (from ryjmbmfilter.nostrict.c's VU0 random func_001a3650),
 * func_001a36f0 whether to run, func_001a4028 places a new particle inside
 * the emitter's radius, func_001a47b0 runs the particles (the step
 * func_001a4168, new ones after the key's interval), the Fn14 slot makes
 * D_0061E730 the unit vector of D_00615F80 - D_00615F70, the Con / Des set
 * up and free the particle blocks.  Read from the code, not proved by a
 * boot. */
#include "m2c.h"
#include "platform/vu.h"
#include "ppp.h"

f32 func_001a3650(void);

s8 func_001a3698(u8 a) {
    f32 f;

    f = func_001a3650();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    s32 unk0;
    s32 unk4;
} PppA2218A;

typedef struct {
    u8 pad[0xF2];
    u8 unkF2;
} PppA36f0B;

s32 func_001a36f0(PppA2218A *p, PppA36f0B *q) {
    if (p->unk0 == 0)
        return 0;
    if (q->unkF2 != 0 && p->unk4 == 0)
        return 0;
    return 1;
}

void *memset(void *, s32, u32);
f32 func_001a3650(void);
void func_001a3720(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a4028;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a4028;

static inline f32 vlen3_1a4028(V4_1a4028 *v) {
    f32 r;
#ifdef KH1_PS2
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
#else
    r = PlatVu0Length3(v);
#endif
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
    PlatVu0Normalize(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a3650() - r;
        m->y = d * func_001a3650() - r;
        m->z = d * func_001a3650() - r;
    } while (r < vlen3_1a4028(m));
    m->w = 1.0f;
    PlatVu0ApplyMatrix(m, D_00615F30, m);
    func_001a3720(e, m, b);
}

typedef struct { f32 x, y, z, w; } V4_1a47b0;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a47b0;

static inline f32 vlen3_1a47b0(V4_1a47b0 *v) {
    f32 r;
#ifdef KH1_PS2
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
#else
    r = PlatVu0Length3(v);
#endif
    return r;
}

typedef struct { u8 pad[0xB0]; u64 flags; } PppSys;
extern s32 D_0061621C;
extern volatile void *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
#define D_00615E60 (*(PppSys **)&D_00615E60)
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



void func_001a4a90(void) {

}

extern M2C_UNK D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
extern M2C_UNK D_00615F80; /* src/data/bss_0061.c: u128 D_00615F80 */
extern M2C_UNK D_0061E730; /* src/data/bss_0061.c: u8 D_0061E730[0x50] */

#undef D_00615E60

void pppRyjMegaBirthModelFilterFn14(void) {
    PlatVu0SubVector(&D_0061E730, &D_00615F80, &D_00615F70);
    PlatVu0Normalize(&D_0061E730, &D_0061E730);
    M2C_FIELD(&D_0061E730, f32 *, 0xC) = 1.0f;
}

void pppRyjMegaBirthModelFilterCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 0x12) = 1;
    M2C_FIELD(temp_a0_2, s32 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, f32 *, 0xC) = 1.0f;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
}

M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;

void pppRyjMegaBirthModelFilterDes(s32 arg0, PppEntry *arg1) {
    s32 temp_a1;
    s32 temp_v0;
    void *temp_a0;
    void *temp_s0;

    temp_a0 = (void *)arg0 + arg1->offsets[2];
    temp_s0 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xA0);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 4);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
    }
}
