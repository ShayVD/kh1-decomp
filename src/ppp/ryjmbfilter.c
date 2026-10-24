/* The pppRyjMegaBirthFilter class (docs/modules.md "Session 49"), with
 * ryjmbfilter.nostrict.c and ryjmbfilter.nostrict_nofill.c: a particle
 * emitter of sprites filtered through the scene.  func_001a2178 is a VU0
 * random number in 0 .. 1 (five steps of R), func_001a21c0 a random s8
 * around 0 of width a, func_001a2218 whether the work and key say to run;
 * func_001a2248 starts a particle from the key (life, colour, speeds and
 * their random spreads), func_001a26f0 places it at a random point inside
 * the emitter's radius (x D_00615F30); func_001a30d8 builds a sprite's
 * matrix (scale, Z rotation, x D_00615EB0, the camera's height scale, x
 * D_00616040); the Fn14 slot (pppRyjMegaBirthFilterFn14) makes D_0061E720
 * the unit vector of D_00615F80 - D_00615F70; the Con / Des set up and
 * free the two particle blocks.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "platform/vu.h"
#include "ppp.h"

f32 func_001a2178(void) {
    f32 ret;

#ifdef KH1_PS2
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
        : "=&r"(ret)
        :
        : "$8", "memory");
#else
    ret = PlatVu0Rand();
#endif
    return ret;
}

s8 func_001a21c0(u8 a) {
    f32 f;

    f = func_001a2178();
    return (f32) (a * 2) * f - (f32) (a >> 1);
}

typedef struct {
    s32 unk0;
    s32 unk4;
} PppA2218A;

typedef struct {
    u8 pad[0xB6];
    u8 unkB6;
} PppA2218B;

s32 func_001a2218(PppA2218A *p, PppA2218B *q) {
    if (p->unk0 == 0)
        return 0;
    if (q->unkB6 != 0 && p->unk4 == 0)
        return 0;
    return 1;
}

typedef struct { u8 pad0[6]; s16 n; } P9Shape;
typedef struct { u8 pad0[0x14]; struct { P9Shape *s; s32 pad; } *shapes; } P9Res;
extern P9Res *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */

typedef struct {
    u8 pad0[4];
    s32 shape;
    u8 pad8[0xc];
    u16 life;
    u8 x16;
    u8 pad17;
    f32 c[4];
    u8 pad28[0x10];
    u8 col[4];
    f32 x3c;
    f32 x40;
    u8 pad44[4];
    f32 x48;
    f32 x4c;
    u8 pad50[0x10];
    f32 x60;
    f32 x64;
    u8 pad68[4];
    f32 x6c;
    f32 x70;
    u8 pad74[4];
    f32 x78;
    u8 pad7c[0xc];
    f32 x88;
    u8 pad8c[4];
    f32 x90;
    u8 pad94[0x23];
    u8 fl2;
    u8 fl1;
} P9Key;

typedef struct {
    u8 pad0[0x22];
    u16 frame;
    u8 pad24[2];
    s16 life;
    s8 col[4];
    f32 x2c;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4c;
    f32 x50;
    s32 x54;
    union { u64 d; u8 b; } x58;
} P9Part;


typedef struct { u8 pad0[0x10]; f32 c[4]; } P9Out;

void func_001a2248(P9Key *a, P9Part *b, P9Out *c) {
    P9Shape *s;
    u8 v;
    f32 r;
    s32 l; u16 v16;

    b->col[0] = func_001a21c0(a->col[0]);
    b->col[1] = func_001a21c0(a->col[1]);
    b->col[2] = func_001a21c0(a->col[2]);
    b->col[3] = func_001a21c0(a->col[3]);
    { s32 o = a->shape * 8; s = *(P9Shape **)((u8 *)D_00615E64->shapes + o); }
    b->frame = s->n * func_001a2178();
    v = a->x16;
    if (v) {
        b->x58.b = v;
        b->x58.d |= 0x200;
    }
    b->x2c = a->x6c;
    b->x30 = a->x70;
    if (a->fl1) {
        b->x34 = func_001a2178() * a->x78;
        if (a->fl1 & 1) {
            if (a->fl1 & 2) {
                if (func_001a2178() > 0.5) b->x34 = -b->x34;
            }
        } else if (a->fl1 & 2) {
            b->x34 = -b->x34;
        }
    }
    if (a->fl1 & 4) b->x2c += b->x34;
    if (a->fl1 & 8) b->x30 += b->x34;
    while (b->x2c >= 180.0f) b->x2c -= 360.0f;
    while (b->x2c < -180.0f) b->x2c += 360.0f;
    b->x38 = a->x3c;
    b->x3c = a->x40;
    b->x40 = a->x48;
    b->x44 = a->x4c;
    if (a->fl2) {
        if (a->fl2 & 0x20) {
            b->x48 = b->x4c = func_001a2178() * a->x60;
            if (a->fl2 & 1) {
                if (a->fl2 & 2) {
                    if (func_001a2178() > 0.5) {
                        b->x48 = -b->x48;
                        b->x4c = -b->x4c;
                    }
                }
            } else if (a->fl2 & 2) {
                b->x48 = -b->x48;
                b->x4c = -b->x4c;
            }
        } else {
            b->x48 = func_001a2178() * a->x60;
            b->x4c = func_001a2178() * a->x64;
            if (a->fl2 & 1) {
                if (a->fl2 & 2) {
                    if (func_001a2178() > 0.5) b->x48 = -b->x48;
                    if (func_001a2178() > 0.5) b->x4c = -b->x4c;
                }
            } else if (a->fl2 & 2) {
                b->x48 = -b->x48;
                b->x4c = -b->x4c;
            }
        }
    }
    if (a->fl2 & 4) {
        b->x38 += b->x48;
        b->x3c += b->x4c;
    }
    if (a->fl2 & 8) {
        b->x40 += b->x48;
        b->x44 += b->x4c;
    }
    b->x50 = a->x88;
    if (a->x90 != 0.0f) {
        b->x50 += (a->x90 + a->x90) * func_001a2178() - a->x90;
    }
    if (a->life) b->life = a->life; else b->life = -1;
    if (c) {
        c->c[0] = a->c[0];
        c->c[1] = a->c[1];
        c->c[2] = a->c[2];
        c->c[3] = a->c[3];
    }
    b->x54 = 0;
}

void *memset(void *, s32, u32);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a26f0;
typedef struct { u8 pad[124]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a26f0;

static inline f32 vlen3_1a26f0(V4_1a26f0 *v) {
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

void func_001a26f0(s32 a0, Emit_1a26f0 *e, V4_1a26f0 *m, void *b) {
    V4_1a26f0 t;
    f32 r, d;
    memset(m, 0, 96);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    PlatVu0Normalize(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a2178() - r;
        m->y = d * func_001a2178() - r;
        m->z = d * func_001a2178() - r;
    } while (r < vlen3_1a26f0(m));
    m->w = 1.0f;
    PlatVu0ApplyMatrix(m, D_00615F30, m);
    func_001a2248((P9Key *)e, (P9Part *)m, (P9Out *)b);
}

void func_001a30d0(void) {

}

#include "data/pieces/D_003701F0.h"
extern f32 D_00615EB0[4][4]; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
typedef struct { u8 pad[44]; f32 rot; u8 pad2[8]; f32 sx, sy; } Spr;
typedef struct { u8 pad[164]; f32 sc, of; } Cam;

f32 func_001a30d8(s32 a0, f32 (*m)[4], Cam *c, s32 a3, Spr *s) {
    f32 r;
    PlatVu0UnitMatrix(m);
    m[0][0] = s->sx * D_003701F0[0];
    m[1][1] = s->sy * D_003701F0[1];
    m[2][2] = s->sx * D_003701F0[0];
    if (s->rot != 0.0f) PlatVu0RotMatrixZ(m, m, s->rot * 3.1415927f / 180.0f);
    PlatVu0CopyVector(m[3], s);
    PlatVu0ApplyMatrix(m[3], D_00615EB0, m[3]);
    m[3][1] *= c->sc;
    r = m[3][2];
    m[3][1] += c->of;
    PlatVu0MulMatrix(m, D_00616040, m);
    return r;
}

extern M2C_UNK D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
extern M2C_UNK D_00615F80; /* src/data/bss_0061.c: u128 D_00615F80 */
extern M2C_UNK D_0061E720; /* src/data/bss_0061.c: u8 D_0061E720[0x10] */

void pppRyjMegaBirthFilterFn14(void) {
    PlatVu0SubVector(&D_0061E720, &D_00615F80, &D_00615F70);
    PlatVu0Normalize(&D_0061E720, &D_0061E720);
    M2C_FIELD(&D_0061E720, f32 *, 0xC) = 1.0f;
}

extern volatile void *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

void pppRyjMegaBirthFilterCon(s32 arg0, PppEntry *arg1) {
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
/* m2c's view of the resource: an address */
#define D_00615E64 ((s32)D_00615E64)

void pppRyjMegaBirthFilterDes(s32 arg0, PppEntry *arg1) {
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
#undef D_00615E64
