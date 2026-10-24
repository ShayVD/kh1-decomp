/* The map collision file's tables, 0x00104528-0x00105f28: func_00105d88 /
 * func_00104528 / func_00104678 set the pointers D_002A6234 ... from the
 * file's header (the triangles D_002A6238, the vertices D_002A624C, the
 * normals D_002A6250, the tree D_002A6244 ...), and the accessors
 * func_00104ae0 (a triangle's corners), func_00104eb0, func_00104f10 (its
 * normal) ... serve src/coll/mapcoll.c. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A623C.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6250.h"
#include "data/pieces/D_002A6274.h"
#include "data/pieces/D_002A62A8.h"
#include "data/pieces/D_002A6210.h"
#include "data/pieces/D_002A6220.h"
#include "data/pieces/D_002A62AC.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A62B4.h"
#include "data/pieces/D_002A62BC.h"
#include "data/pieces/D_002A62C0.h"
#include "data/pieces/D_002A62C4.h"
#include "data/pieces/D_002A62C8.h"
#include "data/pieces/D_002A62CC.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002A62D4.h"
#include "data/pieces/D_002A62D8.h"
#include "data/pieces/D_002A62DC.h"
#include "data/pieces/D_002A62E0.h"
#include "data/pieces/D_002A62E4.h"
#include "common.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
#include "data/types/text_00100000_s7_w6.h"
#include "data/types/text_00100000_s6_00.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/types/text_00100000_s6_00_p.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00100000_s11_w68.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_s11_w56.h"

/* func_00104528 (from auto/text_00100000_6.c). */
extern s32 D_002A6240;
extern s32 D_002A6248;
extern s32 D_002A6254;
extern s32 D_002A6258;
extern s32 D_002A625C;
extern s32 D_002A6260;
extern s32 D_002A6264;
extern s32 D_002A6268;
extern s32 D_002A626C;
extern s32 D_002A6270;
extern s32 D_002A6278;
extern s32 D_002A627C;
extern s32 D_002A6280;
extern s32 D_002A6284;
extern s32 D_002A6288;
extern s32 D_002A628C;
extern s32 D_002A6290;
extern s32 D_002A6294;
extern s32 D_002A6298;
extern s32 D_002A629C;
extern s32 D_002A62A0;
extern s32 D_002A62A4;
extern s32 D_002A62EC;
void func_00104528(void) {
    D_002A6234 = (Grid_2a6234 *)D_002A6270;
    D_002A6238 = D_002A6274;
    (*(s32 *)&D_002A623C) = D_002A6278;
    D_002A6240 = D_002A627C;
    (*(s32 *)&D_002A6244) = D_002A6280;
    D_002A6248 = D_002A6284;
    (*(s32 *)&D_002A624C) = D_002A6288;
    (*(s32 *)&D_002A6250) = D_002A628C;
    D_002A6254 = D_002A6290;
    D_002A6258 = D_002A6294;
    D_002A625C = D_002A6298;
    D_002A6260 = D_002A629C;
    D_002A6264 = D_002A62A0;
    D_002A6268 = D_002A62A4;
    D_002A626C = (*(s32 *)&D_002A62A8);
    D_002A62EC = 0;
}

/* func_00104678 (from auto/text_00100000_7.c). */
extern s32 D_002A62B8;
void func_00104678(void) {
    D_002A6234 = D_002A62AC;
    D_002A6238 = D_002A62B0;
    (*(s32 *)&D_002A623C) = ((s32)D_002A62B4);
    D_002A6240 = D_002A62B8;
    (*(s32 *)&D_002A6244) = ((s32)D_002A62BC);
    D_002A6248 = (*(s32 *)&D_002A62C0);
    (*(s32 *)&D_002A624C) = (*(s32 *)&D_002A62C4);
    (*(s32 *)&D_002A6250) = (*(s32 *)&D_002A62C8);
    D_002A6254 = (*(s32 *)&D_002A62CC);
    D_002A6258 = D_002A62D0;
    D_002A625C = D_002A62D4;
    D_002A6260 = D_002A62D8;
    D_002A6264 = D_002A62DC;
    D_002A6268 = D_002A62E0;
    D_002A626C = D_002A62E4;
    D_002A62EC = 1;
}

/* func_001047c8 (from hand/text_00100000_h1.c). */
extern s32 D_002A3F28;
extern s32 D_002BC130;
extern s32 D_002BC128;
extern s32 D_002BC134;
void func_001047c8(void) {
    if (D_002A3F28 != 0) {
        if (D_002BC128 == 15 && D_002BC130 == 12 && (D_002BC134 == 24 || D_002BC134 == 2)) {
            func_00104528();
            return;
        }
        func_00104678();
    } else {
        func_00104528();
    }
}

/* func_00104850 (from hand/text_00100000_h28.c). */
void func_00104850(f32 *pos, s32 *out) {
    out[0] = (pos[0] - D_002A6234->x0) / D_002A6234->cw;
    out[2] = (pos[2] - D_002A6234->z0) / D_002A6234->ch;
    if (out[0] < 0) {
        out[0] = 0;
    } else if (out[0] >= D_002A6234->nx) {
        out[0] = D_002A6234->nx - 1;
    }
    if (out[2] < 0) {
        out[2] = 0;
    } else if (out[2] >= D_002A6234->nz) {
        out[2] = D_002A6234->nz - 1;
    }
}

/* func_00104908 (from hand/text_00100000_s6_na.c). */
void func_00104908(void) {
    (*(s32 (*)[3])&D_002A6318)[0] = (*(s32 (*)[3])&D_002A6308)[0] = (*(s32 (*)[3])&D_002A6318)[1] = (*(s32 (*)[3])&D_002A6318)[2] = (*(s32 (*)[3])&D_002A6308)[1] = (*(s32 (*)[3])&D_002A6308)[2] = -1;
    D_002A6324 = 0;
}

/* func_00104a90 (from hand/text_00100000_h1.c). */
typedef Ent20_2a6238 Ent20;
s32 func_00104a90(s32 i, s32 *out) {
    Ent20 *e = &D_002A6238[i]; s32 d;
    out[0] = e->v[0]; out[1] = e->v[1]; out[2] = e->v[2]; out[3] = d = e->v[3];
    if (d == -2 || d == -1) return 3; return 4;
}

/* func_00104ae0 (from hand/text_00100000_s7_w6.c). */
typedef Ent20_2a6238 Face;
/* func_00104ae0 (session 7, w6): the face pointer is built from a local
 * copy of the table base (`base` first, so its lui is scheduled first),
 * and the two counts are separate returns (li v0,3 hoisted). */
s32 func_00104ae0(s32 i, f32 *o) {
    u32 base = (u32)D_002A6238;
    Face *f = (Face *)(i * 20 + base);
    s32 a = f->v[0], b = f->v[1], c = f->v[2], d = f->v[3];
    o[0] = D_002A624C[a].x;
    o[1] = D_002A624C[a].y;
    o[2] = D_002A624C[a].z;
    o[3] = 1.0f;
    o[4] = D_002A624C[b].x;
    o[5] = D_002A624C[b].y;
    o[6] = D_002A624C[b].z;
    o[7] = 1.0f;
    o[8] = D_002A624C[c].x;
    o[9] = D_002A624C[c].y;
    o[10] = D_002A624C[c].z;
    o[11] = 1.0f;
    if ((u32)(d + 2) < 2) return 3;
    o[12] = D_002A624C[d].x;
    o[13] = D_002A624C[d].y;
    o[14] = D_002A624C[d].z;
    o[15] = 1.0f;
    return 4;
}

/* func_00104eb0 (from hand/text_00100000_h1.c). */
typedef Vtx Vec3;
void func_00104eb0(s32 i, f32 *out) {
    Vec3 *v = &D_002A624C[D_002A6238[i].v[0]];
    out[0] = v->x;
    out[1] = v->y;
    out[2] = v->z;
    out[3] = 1.0f;
}

/* func_00104f10 (from hand/text_00100000_s6_00.c). */
static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
static inline void scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
void func_00104f10(s32 i, f32 *o) {
    s16 *p = &D_002A6250[D_002A6238[i].n].x;
    o[3] = 1.0f;
    o[0] = *p++;
    o[1] = *p++;
    o[2] = *p;
    scale(o, o, 0.0001220703125f);
}

/* func_00104fa8 (from auto/text_00100000_2.c). */
void func_00104fa8(s32 arg0, f32 *arg1) {
    *arg1 = M2C_FIELD(((arg0 * 0x14) + ((s32)D_002A6238)), f32 *, 0xC);
}

/* func_00104fd0 (from auto/text_00100000_3.c). */
void func_00104fd0(s32 arg0, void *arg1) {
    s32 temp_a0;

    temp_a0 = arg0 * 0x10;
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 4);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 8);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 0xC);
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}

/* func_00105020 (from hand/text_00100000_h1.c). */
s32 func_00105020(void) {
    s32 i;
    for (i = 0; i < D_002A6294; i++) {
        if ((D_002A6274[i].f.w & 0xf6) == 80) return 1;
    }
    return 0;
}

/* func_00105078 (from hand/text_00100000_h1.c). */
s32 func_00105078(void) {
    s32 i;
    for (i = 0; i < D_002A6294; i++) {
        if ((D_002A6274[i].f.w & 0xf6) == 144) return 1;
    }
    return 0;
}

/* func_00105218 (from hand/text_00100000_h1.c). */
extern s32 D_002A6230;
extern u16 D_002A62F8[];
void func_0011d3c8(s32, s32, s32);
void func_00105218(void) {
    s32 i;
    for (i = 0; i < D_002A6230; i++) func_0011d3c8(D_002A62F8[i], i, 960);
}

/* func_00105288 (from hand/text_00100000_s11_w68.c). */
extern s32 D_002A62E8;
extern s32 D_002A62F0;
void func_00115d18(void);
void func_001050d0(void);
typedef struct { u32 f0; u32 f1; u32 f2; u32 f3; u32 f4; u32 f5; u32 f6; u32 f7; u32 f8; u32 f9; u32 f10; u32 f11; u32 f12; u32 f13; u32 f14; u32 f15; u32 f16; } H;
void func_00105288(H *h, s32 mode) {
    s32 n, b, q, m;
    s32 *p;
    D_002A6270 = (s32)h + h->f0;
    (*(s32 *)&D_002A6274) = (s32)h + h->f6;
    D_002A6294 = h->f7 / 20;
    D_002A6290 = (s32)h + h->f8;
    D_002A62A4 = h->f9 / 16;
    D_002A6278 = (s32)h + h->f10;
    D_002A62A0 = h->f11 / 4;
    q = (s32)h + h->f12;
    m = h->f13 / 4;
    D_002A6280 = q;
    D_002A6288 = (s32)h + h->f2;
    D_002A6298 = h->f3 / 12;
    D_002A62A8.v = m;
    D_002A628C = (s32)h + h->f4;
    D_002A629C = h->f5 / 8;
    D_002A627C = (s32)h + h->f14;
    D_002A6284 = (s32)h + h->f16;
    func_00115d18();
    func_00104528();
    D_002A3F28 = 0;
    func_00104908();
    if (mode != 1) return;
    n = D_002A62A8.v;
    if (n > 0) {
        s32 *q;
        b = D_002A6284;
        q = (s32 *)D_002A6280;
        do {
            *q++ += b;
        } while (--n);
    }
    n = D_002A62A0;
    if (n > 0) {
        p = (s32 *)((s32 *)&D_002A6274)[1];
        do {
            if (*p != -1) *p += D_002A627C;
            p++;
        } while (--n);
    }
    D_002A62E8 = func_00105020();
    D_002A62F0 = func_00105078();
    func_00105218();
    func_001050d0();
}

/* func_001054d0 (from hand/text_00100000_h51.c). */
void func_001054d0(s32 group, s32 which, s32 on) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        Tri20 *t = &D_002A6238[i];
        if (t->id != group) continue;
        switch (which) {
        case 0: t->f.t.b3 = on; break;
        case 1: t->f.t.b8 = on; break;
        case 2: t->f.t.b9 = on; break;
        case 3: t->f.t.b10 = on; break;
        case 4: t->f.t.b15 = on; break;
        case 5: t->f.t.b16 = on; break;
        case 6: t->f.t.b17 = on; break;
        case 7: t->f.t.b22 = on; break;
        case 8: t->f.t.b23 = on; break;
        case 9: t->f.t.b24 = on; break;
        case 10: t->f.t.b25 = on; break;
        case 11: t->f.t.b26 = on; break;
        case 12: t->f.t.b27 = on; break;
        case 13: t->f.t.b28 = on; break;
        }
    }
}

/* func_00105710 (from auto/text_00100000.c). */
void func_00105710(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & ~0xF0) | ((arg1 & 0xF) * 0x10));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

/* func_00105760 (from auto/text_00100000_3.c). */
void func_00105760(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & 0xFFC3FFFF) | ((arg1 & 0xF) << 0x12));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

/* func_001057b8 (from hand/text_00100000_h28.c). */
void func_001057b8(s32 id, s32 on) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        if (D_002A6238[i].id == id) {
            D_002A6238[i].f.o.on = on;
        }
    }
    if (D_002A3F28 != 0) {
        for (i = 0; i < D_002A62D0; i++) {
            if (D_002A62B0[i].id == id) {
                D_002A62B0[i].f.o.on = on;
            }
        }
    }
}

/* func_00105860 (from hand/text_00100000_h28.c). */
void func_00105860(void) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        if (D_002A6238[i].act != 0 && D_002A6238[i].id != 0 && D_002A6238[i].id < 100) {
            D_002A6238[i].f.o.on = 0;
            if (D_002A6238[i].id != D_002BC130 + 1) {
                D_002A6238[i].f.o.on = 1;
            }
        }
    }
    if (D_002A3F28 != 0) {
        for (i = 0; i < D_002A62D0; i++) {
            if (D_002A62B0[i].id != 0 && D_002A62B0[i].id < 100) {
                D_002A62B0[i].f.o.on = 0;
                if (D_002A62B0[i].id != D_002BC130 + 1) {
                    D_002A62B0[i].f.o.on = 1;
                }
            }
        }
    }
}

/* func_00105960 (from hand/text_00100000_h1.c). */
u8 func_0011ab60(s32, s32);
s32 func_00142730(s32, s32 *);
s32 func_00105960(s32 a, s32 b) {
    s32 sub;
    s32 idx = func_00142730(a, &sub);
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->id == b; }
    return func_0011ab60(sub, idx) == b;
}

/* func_001059d0 (from auto/text_00100000_9.c). */
#define func_0011ab60 ((s32 (*)(s32, s32)) func_0011ab60)
#define func_00142730 ((s32 (*)(s32, s32)) func_00142730)
s32 func_001059d0(s32 arg0) {
    s32 sp[4];
    s32 temp_a3;
    s32 temp_v0;

    temp_v0 = func_00142730(arg0, (s32) sp);
    temp_a3 = temp_v0 * 0x14;
    if (M2C_FIELD(sp, M2C_UNK *, 0x0) == -1) {
        return (s32) M2C_FIELD((((s32)D_002A6238) + temp_a3), u8 *, 0xB);
    }
    return func_0011ab60(M2C_FIELD(sp, M2C_UNK *, 0x0), temp_v0);
}
#undef func_0011ab60
#undef func_00142730

/* func_00105a30 (from auto/text_00100000_3.c). */
void func_0011a978(s32, s32, s32);
#define func_00104f10 ((void (*)(s32, s32)) func_00104f10)
void func_00105a30(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104f10(arg1, arg2);
        return;
    }
    func_0011a978(arg0, arg1, arg2);
}
#undef func_00104f10

/* func_00105a70 (from auto/text_00100000.c). */
#define func_00104528 ((M2C_UNK (*)()) func_00104528)
#define func_001047c8 ((M2C_UNK (*)()) func_001047c8)
#define func_00104f10 ((M2C_UNK (*)(s32, s32)) func_00104f10)
#define func_0011a978 ((M2C_UNK (*)()) func_0011a978)
void func_00105a70(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_001047c8();
        func_00104f10(arg1, arg2);
        func_00104528();
        return;
    }
    func_0011a978();
}
#undef func_00104528
#undef func_001047c8
#undef func_00104f10
#undef func_0011a978

/* func_00105ad0 (from auto/text_00100000_3.c). */
s32 func_0011aa18(s32, s32, s32);
#define func_00104ae0 ((s32 (*)(s32, s32)) func_00104ae0)
s32 func_00105ad0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        return func_00104ae0(arg1, arg2);
    }
    return func_0011aa18(arg0, arg1, arg2);
}
#undef func_00104ae0

/* func_00105b10 (from hand/text_00100000_h1.c). */
typedef EntBits_2a6238 EntBits;
EntBits *func_0011ab38(s32, s32);
s32 func_00105b10(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f22; }
    return func_0011ab38(sub, idx)->f22;
}

/* func_00105b68 (from hand/text_00100000_h1.c). */
s32 func_00105b68(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f4; }
    return func_0011ab38(sub, idx)->f4;

}

/* func_00105bc0 (from hand/text_00100000_h1.c). */
s32 func_00105bc0(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f18; }
    return func_0011ab38(sub, idx)->f18;

}

/* func_00105c18 (from hand/text_00100000_h1.c). */
s32 func_00105c18(s32 sub, s32 idx) {
    if (sub == -1) { s32 off = idx * 20; return ((Ent20 *)((u8 *)D_002A6238 + off))->f.e.f28; }
    return func_0011ab38(sub, idx)->f28;

}

/* func_00105c70 (from auto/text_00100000_3.c). */
s32 func_002675a8(s32, s32);
void func_00105c70(s32 arg0, s32 arg1) {
    func_002675a8(arg1, D_002A3F48 + (arg0 * 0x10));
}

/* func_00105c98 (from auto/text_00100000_4.c). */
s32 func_00105c98(s32 arg0, s32 arg1) {
    return func_002675a8(arg1, D_002A3F48 + (((u32) M2C_FIELD(((arg0 * 0x14) + ((s32)D_002A6238)), u32 *, 0x10) >> 7) & 0xF0));
}

/* func_00105ce0 (from hand/text_00100000_h1.c). */
s32 func_00105ce0(s32 id) {
    s32 i; for (i = 0; i < D_002A6258; i++) { Ent20 *e = &D_002A6238[i]; if (e->id == id) return e->f.e.f11; } return 0;
}

/* func_00105d38 (from auto/text_00100000.c). */
void func_00105d38(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & ~0x7800) | ((arg1 & 0xF) << 0xB));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

/* func_00105d88 (from hand/text_00100000_s11_w56.c). */
/* func_00105d88 (hand), s11w56. FLAGGED DEAD CODE: the four `if (n <cmp> 0) { m = 1; m = 2; } else { m = 1; m = 2; }` tests in loop 1 are dead (m is reloaded before loop 2; identical multi-set arms keep each branch alive through sched2, jump2 removes them, no code). They give the shared counter n (loop-1 count-down and loop-2 reversed counter, one variable) 8 extra loop-depth-weighted refs, so global-alloc allocates n before the loop-2 pointer giv: a1 for both counters as in the original. From session8 w12/w8 7w draft. */
void func_00105d88(u8 *h) {
    u32 *w = (u32 *)h;
    s32 n;
    s32 i;
    s32 m;
    D_002A62AC = (Grid_2a6234 *)(h + w[0]);
    D_002A62B0 = (Ent20_2a6238 *)(h + w[6]);
    D_002A62D0 = w[7] / 20;
    D_002A62CC = h + w[8];
    D_002A62E0 = w[9] / 16;
    D_002A62B4 = (SV62B4 *)(h + w[10]);
    D_002A62DC = w[11] / 4;
    D_002A62BC = (SV62B4 *)(h + w[12]);
    D_002A62E4 = n = w[13] / 4;
    D_002A62C4 = h + w[2];
    D_002A62D4 = w[3] / 12;
    D_002A62C8 = h + w[4];
    D_002A62D8 = w[5] / 8;
    D_002A62B8 = (s32)(h + w[14]);
    D_002A62C0 = h + w[16];
    for (i = 0; n != 0; n--, i++) {
        D_002A62BC[i].v += (s32)D_002A62C0;
        if (n < 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n > 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n >= 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n <= 0) { m = 1; m = 2; } else { m = 1; m = 2; }
    }
    m = D_002A62DC;
    for (n = 0; n < m; n++) {
        if (D_002A62B4[n].v != -1) {
            D_002A62B4[n].v += D_002A62B8;
        }
    }
}

