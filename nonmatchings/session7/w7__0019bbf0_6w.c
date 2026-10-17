/* func_0019bbf0, hand/nostrict, rodata 0048FBF0: 6 words off: v.x/v.y/v.z lh register choice v0/v1 swapped at 0x19c320-0x19c340. Fixed from s6: case 0 and case 1-5 paths each write the whole tail (v = tbl[s->idx[k]]; pos = v*sc), crossjumped like the original. */
#include "common.h"

typedef struct { s16 x, y, z; } MgV6;
typedef struct { s16 h0; u16 n; u16 *idx; } MgSet;
typedef struct { u8 pad[0x14]; MgV6 *v; u8 pad18[0xC]; } MgSlot;
typedef struct { u8 pad[0x10]; MgSlot *slots; u8 pad14[4]; MgSet *sets; } MgSys;
typedef struct { u8 pad[0x10]; f32 m10[4][4]; u8 pad50[0x40]; MgV6 *v90; } MgCur;
extern MgSys *D_00615E64;
extern MgCur *D_00615E68;

typedef struct {
    u8 pad0[0x22];
    u16 live;      /* 0x22 */
    u8 b24, b25, type, b27;
    f32 f28, f2C, f30, f34; /* 0x28 */
    u8 pad38[0x10];
    u8 col[4];     /* 0x48 */
    f32 f4C, f50, f54, f58, f5C; /* 0x4C */
    u8 pad60[0x10];
    f32 f70, f74, f78, f7C, f80, f84, f88; /* 0x70 */
    f32 v8C[3];    /* 0x8C */
    u8 pad98[0xC];
    f32 fA4, fA8, fAC, fB0, fB4, fB8; /* 0xA4 */
    f32 sc[3];     /* 0xBC */
    u8 c8, c9, ca, cb, cc, cd; /* 0xC8 */
    u8 padCE[2];
    s16 set;       /* 0xD0 */
} MgKey;

typedef struct {
    f32 pos[4];
    f32 dir[4];
    u8 pad20[6];
    u16 live;      /* 0x26 */
    s8 col[4];     /* 0x28 */
    f32 f2C, f30, f34, f38, f3C, f40, f44, f48, f4C, f50, f54, f58; /* 0x2C */
    u8 b5C, b5D, b5E, b5F;
} MgPart;

typedef struct { u8 pad[0x10]; f32 f10, f14, f18, f1C; } MgB;
typedef struct { u8 pad[0x62]; u16 h62; } MgObj;
typedef struct { u8 pad[0xB]; u8 bB; } MgE;

f32 func_0019baf8(void);
s8 func_0019bb40(u8);
void *memset(void *, s32, u32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0CopyMatrix(void *, void *);
void func_002678b8(f32 (*)[4], f32 (*)[4], f32 *);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267e90(MgPart *, f32 *, f32);


f32 func_0019baf8(void) {
    f32 ret;

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
    return ret;
}

s8 func_0019bb40(u8 a) {
    f32 f = func_0019baf8();

    return (f32) (a * 2) * f - (f32) (a >> 1);
}

#define R func_0019baf8()
#define TAIL(E) { v = tbl[E]; p->pos[0] = (f32)v.x * key->sc[0]; p->pos[1] = (f32)v.y * key->sc[1]; p->pos[2] = (f32)v.z * key->sc[2]; }
void func_0019bbf0(MgObj *obj, s32 keyi, MgE *e, MgPart *p, void *a, MgB *b) {
    f32 vec[4] __attribute__((aligned(16)));
    f32 ang[4] __attribute__((aligned(16)));
    f32 m[4][4] __attribute__((aligned(16)));
    MgKey *key = (MgKey *)keyi;
    f32 rng = key->b27;
    f32 rng2 = 2.0f * rng;
    s32 i;
    s32 t;
    f32 f, h, r1, r2, r3, r4, r;
    MgV6 v;

    memset(p, 0, sizeof(MgPart));
    if (a)
        memset(a, 0, 0x40);
    if (b)
        memset(b, 0, 0x20);
    switch (key->type) {
    case 0 ... 7:
        { f32 x0 = key->v8C[0], x1 = key->v8C[1], x2 = key->v8C[2]; vec[0] = x0; vec[1] = x1; vec[2] = x2; }
        vec[3] = 1.0f;
        for (i = 0; i < 3; i++)
            ang[i] = (rng2 * func_0019baf8() - rng) * 3.141592562f / 180.0f;
        if ((u8)(key->type - 2) < 2) {
            ang[0] = 0.0f;
            ang[1] = 0.0f;
        }
        sceVu0UnitMatrix(m);
        func_002678b8(m, m, ang);
        func_002672f8(p->dir, m, vec);
        p->dir[0] *= key->sc[0];
        p->dir[1] *= key->sc[1];
        p->dir[2] *= key->sc[2];
        func_002673b8(p->dir, p->dir);
    }
    switch (key->type) {
    case 0: case 1: case 2: case 3:
    default:
        f = key->fB8;
        if (f == 0.0f)
            break;
        switch (key->c8) {
        case 0:
            break;
        case 1:
            func_0019baf8();
            f = key->fB8 * func_0019baf8();
            break;
        case 2:
            f = key->fB8 * R * R;
            break;
        case 3:
            f = key->fB8 - key->fB8 * R * R * 0.7f;
            break;
        case 4:
            f = key->fB8 * R * R * R * R;
            break;
        case 5:
            f = key->fB8 - key->fB8 * R * R * R * 0.5f;
            break;
        }
        func_00267e90(p, p->dir, f);
        break;
    case 4: case 5:
        if (key->fB8 == 0.0f)
            break;
        rng2 = key->fB8 * 0.5f;
        switch (key->c8) {
        case 0:
        default:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * func_0019baf8() - rng2;
            break;
        case 1:
            func_0019baf8();
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * func_0019baf8() - rng2;
            break;
        case 2:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * R * R - rng2;
            break;
        case 3:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 - key->fB8 * R * R * 0.7f - rng2;
            break;
        case 4:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 * R * R * R * R - rng2;
            break;
        case 5:
            for (i = 0; i < 3; i++)
                p->pos[i] = key->fB8 - key->fB8 * R * R * R * 0.5f - rng2;
            break;
        }
        p->pos[0] *= key->sc[0];
        p->pos[1] *= key->sc[1];
        p->pos[2] *= key->sc[2];
        break;
    case 6: case 7: case 8: case 9: {
        s16 id = key->set;
        MgV6 *tbl = D_00615E68->v90;
        MgSet *s;
        u16 *ip;
        if (id < 0)
            break;
        s = &D_00615E64->sets[id];
        if (!tbl)
            tbl = D_00615E64->slots[s->h0].v;
        switch (key->c8) {
        case 0:
        default:
            if (obj->h62 >= (s16)s->n)
                obj->h62 = 0;
            { s32 k = s->idx[obj->h62++]; TAIL(k); }
            goto ty;
        case 1:
            R;
            r = R;
            break;
        case 2:
            r = R * R * R;
            break;
        case 3:
            r = 1.0 - R * R * R;
            break;
        case 4:
            r = R * R * R * R;
            break;
        case 5:
            r = 1.0 - R * R * R * R * R;
            break;
        }
        if (obj->h62 >= (s16)s->n)
            obj->h62 = 0;
        { s32 k = s->idx[(s32)(r * (f32)(s16)s->n)]; TAIL(k); }
    ty:
        if ((u8)(key->type - 8) < 2)
            func_002673b8(p->dir, p->pos);
        break;
    }
    }
    p->col[0] = func_0019bb40(key->col[0]);
    p->col[1] = func_0019bb40(key->col[1]);
    p->col[2] = func_0019bb40(key->col[2]);
    p->col[3] = func_0019bb40(key->col[3]);
    if (key->b24) {
        p->f58 = e->bB;
        p->b5D = key->b24;
    }
    if (key->b25)
        p->b5E = key->b25;
    p->f2C = key->f7C;
    p->f30 = key->f80;
    if (key->cb) {
        p->f34 = func_0019baf8() * key->f88;
        if (key->cb & 1) {
            if (key->cb & 2) {
                if (func_0019baf8() > 0.5)
                    p->f34 = -p->f34;
            }
        } else if (key->cb & 2) {
            p->f34 = -p->f34;
        }
    }
    if (key->cb & 4)
        p->f2C += p->f34;
    if (key->cb & 8)
        p->f30 += p->f34;
    while (p->f2C >= 180.0f)
        p->f2C -= 360.0f;
    while (p->f2C < -180.0f)
        p->f2C += 360.0f;
    p->f38 = key->f4C;
    p->f3C = key->f50;
    p->f40 = key->f58;
    p->f44 = key->f5C;
    if (key->ca) {
        if (key->ca & 0x20) {
            p->f48 = p->f4C = func_0019baf8() * key->f70;
            if (key->ca & 1) {
                if (key->ca & 2) {
                    if (func_0019baf8() > 0.5) {
                        p->f48 = -p->f48;
                        p->f4C = -p->f4C;
                    }
                }
            } else if (key->ca & 2) {
                p->f48 = -p->f48;
                p->f4C = -p->f4C;
            }
        } else {
            p->f48 = func_0019baf8() * key->f70;
            p->f4C = func_0019baf8() * key->f74;
            if (key->ca & 1) {
                if (key->ca & 2) {
                    if (func_0019baf8() > 0.5)
                        p->f48 = -p->f48;
                    if (func_0019baf8() > 0.5)
                        p->f4C = -p->f4C;
                }
            } else if (key->ca & 2) {
                p->f48 = -p->f48;
                p->f4C = -p->f4C;
            }
        }
    }
    if (key->ca & 4) {
        p->f38 += p->f48;
        p->f3C += p->f4C;
    }
    if (key->ca & 8) {
        p->f40 += p->f48;
        p->f44 += p->f4C;
    }
    p->f50 = key->fA4;
    p->f54 = key->fB0;
    if (key->fAC != 0.0f)
        p->f50 += 2.0f * key->fAC * func_0019baf8() - key->fAC;
    if (key->live) p->live = key->live; else p->live = -1;
    p->b5C = 0;
    switch (key->cc) {
    case 1:
        sceVu0CopyMatrix(a, obj);
        break;
    case 2:
        sceVu0CopyMatrix(a, D_00615E68->m10);
        break;
    }
    if (b) {
        b->f10 = key->f28;
        b->f14 = key->f2C;
        b->f18 = key->f30;
        b->f1C = key->f34;
    }
}
