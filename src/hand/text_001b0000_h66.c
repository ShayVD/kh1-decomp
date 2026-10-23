#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

double asin(double);
double cos(double);
double atan2(double, double);
f32 acosf(f32);
#include "data/pieces/D_002E2780.h"
typedef FVec4 V4;
f32 sinf(f32);
f32 sqrtf(f32);
void func_001bf290(f32 *q);
typedef struct { u16 h0, h2, h4, h6; u8 *ctx; u8 *stk; u8 pad[32]; } Task_bfcd8;
#include "data/pieces/D_0037A170.h"
typedef RunQ_37a170 RunQ_bfcd8;
extern Task_bfcd8 *D_0037A16C;
extern s32 D_0037A164, D_0037A168, D_0037A174;
extern u8 *D_006257D4;
void func_001be820(void *p, u32 n);
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
extern u32 D_002C5958;
void func_0011ef10(s32, void *);
typedef struct { u8 pad[16]; V4 pos; u8 pad32[28]; f32 roty; } Obj_c5168;
typedef struct { u8 pad[16]; V4 pos; u8 pad32[32]; V4 tgt; u8 pad80[16]; f32 f96; } Cam_c5168;
typedef struct { u8 pad[12376]; s32 mode; u8 pad12380[16]; Obj_c5168 *p12396; Obj_c5168 *p12400; } Big_c5168;
void sceVu0UnitMatrix(f32 (*m)[4]);
void func_00267810(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_002672f8(V4 *d, f32 (*m)[4], V4 *s);
void func_001e9d00(V4 *d, V4 *a, V4 *b, f32 t);
void func_001e9fe8(V4 *dst, V4 *src);
void func_001e9f18(V4 *dst, V4 *a, V4 *b, f32 t);
f32 func_001e9e58(V4 *a, V4 *b);
typedef struct { f32 x, y, z, w; } __attribute__((aligned(8))) V4a_c5b88;
typedef struct { u8 pad[8]; s32 end; } Track_c5b88;
typedef struct {
    f32 t; u8 pad4[12]; V4a_c5b88 v16; V4a_c5b88 v32; V4a_c5b88 v48; V4a_c5b88 v64; V4a_c5b88 v80; f32 f96;
    u8 pad100[0xE0F4 - 100]; f32 fE0F4; u8 padE0F8[4]; Track_c5b88 *trk;
} CamPlay_c5b88;
typedef struct {
    u64 flags; u8 pad8[184]; V4a_c5b88 v192; V4a_c5b88 v208; V4a_c5b88 v224; V4a_c5b88 v240; V4a_c5b88 v256; V4a_c5b88 v272; f32 f288; f32 f292;
} Tw_c5b88;
typedef struct { u8 pad[12400]; u64 d12400; u8 pad12408[212]; f32 f12620; } Big_c5b88;
extern f32 D_002BBDFC;
void func_001c53c8(f32 t);
void func_001c6a20(void);
void func_002675a8(void *a, void *b);
typedef union { u64 flags; struct { s32 lo; f32 f[74]; } s;
} Tw_c6720;
void func_001c6890(void);
typedef struct {
    u64 flags; u8 pad8[200]; V4 v208; V4 v224; V4 v240; V4 v256; V4 v272; f32 f288; f32 f292;
} Tw_c6890;
#include "data/pieces/D_002E2790.h"
extern f32 D_002E27A0;
#include "data/pieces/D_002E27A4.h"
void *memset(void *, s32, u32);
void func_00267768(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_002676c0(f32 (*d)[4], f32 (*s)[4], f32 r);
typedef struct {
    u64 flags; u8 pad8[4]; f32 dur[3]; u8 pad24[8]; f32 t[3]; u32 m[8]; u8 pad76[20];
    f32 start[3]; u8 pad108[36]; f32 end[3]; u8 pad156[132]; f32 cur[3];
} Tw_c9ac8;
typedef struct {
    u64 flags; u8 pad8[4]; f32 dur[3]; u8 pad24[8]; f32 t[3]; u32 m[8]; u8 pad76[20];
    f32 start[3]; u8 pad108[36]; f32 end[3]; u8 pad156[132]; f32 cur[3];
} Tw_c9e80;
typedef struct { u64 flags; u8 pad[184]; V4 v192; V4 v208; } Tw_ca800;
extern u64 D_0038CD00;
s32 func_001c5b88(void);
void func_001c8e20(void);
void func_001c8758(void);
void func_001c8930(void);
void func_001c8c10(void);
void func_001c8d18(void);
void func_001c9308(void);
void func_001c96c0(void);
void func_001c9ac8(void);
void func_001c9d40(void);
void func_001c9e80(void);
#include "data/pieces/D_0037A380.h"
extern u8 D_00389C90[];
extern u8 D_003C5510[];

void func_001bea58(f32 *a, f32 *b) {
    s32 i;
    for (i = 0; i < 4; i++) {
        f32 x = a[i], y = b[i];
        f32 xa = x, ya = y;
        double d;
        f32 d1;
        if (x < 0.0f) xa = x + 6.2831850051879883f;
        if (y < 0.0f) ya = y + 6.2831850051879883f;
        d = ya - xa;
        if (d < 0.0) d = 0.0 - d;
        d1 = d;
        d = y - x;
        if (d < 0.0) d = 0.0 - d;
        if (d1 < (f32)d) { a[i] = xa; b[i] = ya; }
        else { a[i] = x; b[i] = y; }
    }
}

void func_001bf0e8(V4 *pos, V4 *rot, f32 *m) {
    f32 rx, ry, rz = 0.0f, c;
    pos->x = m[12];
    pos->y = m[13];
    pos->z = m[14];
    pos->w = 1.0f;
    ry = -asin(m[2]);
    c = cos(ry);
    if (c > -0.0009999999310821295f && c < 0.0009999999310821295f) {
        rx = rz;
        rz = acosf(m[5]);
    } else {
        rx = atan2(m[6], m[10]);
        rz = asin(m[1] / c);
        if (m[0] < 0.0f) rz = 3.1415925621986389f - rz;
    }
    rot->x = rx;
    rot->y = ry;
    rot->z = rz;
    rot->w = 1.0f;
}

void func_001bf3e8(f32 m[4][4], V4 *q) {
    m[0][0] = 1.0f - 2.0f * (q->y * q->y + q->z * q->z);
    m[1][0] = 2.0f * (q->x * q->y - q->w * q->z);
    m[2][0] = 2.0f * (q->x * q->z + q->w * q->y);
    m[3][0] = 0.0f;
    m[0][1] = 2.0f * (q->x * q->y + q->w * q->z);
    m[1][1] = 1.0f - 2.0f * (q->x * q->x + q->z * q->z);
    m[2][1] = 2.0f * (q->y * q->z - q->w * q->x);
    m[3][1] = 0.0f;
    m[0][2] = 2.0f * (q->x * q->z - q->w * q->y);
    m[1][2] = 2.0f * (q->y * q->z + q->w * q->x);
    m[2][2] = 1.0f - 2.0f * (q->x * q->x + q->y * q->y);
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001bf710(f32 *d, f32 *a, f32 *b, f32 t) {
    f32 th, s, sa, sb;
    s32 i;
    th = acosf(a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
    s = sinf(th);
    sa = sinf(th * (1.0f - t));
    sb = sinf(th * t);
    if (s > -0.01f && s < 0.01f) {
        d[0] = a[0];
        d[1] = a[1];
        d[2] = a[2];
        d[3] = a[3];
        return;
    }
    s = 1.0f / s;
    for (i = 0; i < 4; i++) d[i] = (a[i] * sa + b[i] * sb) * s;
}

void func_001bf888(f32 *q, f32 m[4][4]) {
    s32 i, j, k;
    f32 s, t; f32 *p;
    i = 0;
    if (m[1][1] > m[0][0]) i = 1;
    if (m[2][2] > m[i][i]) i = 2;
    j = (i + 1) % 3;
    k = (j + 1) % 3;

    q[i] = s = sqrtf(m[i][i] - m[j][j] - m[k][k] + 1.0f) * 0.5f;
    if (s == 0.0f) {
        func_001bf290(q);
        return;
    }
    t = s * 4.0f;
    q[j] = (m[i][j] + m[j][i]) / t;
    q[k] = (m[i][k] + m[k][i]) / t;
    q[3] = (m[j][k] - m[k][j]) / t;
}

void func_001bfcd8(void) {
    u8 *p;
    Task_bfcd8 *t;
    s32 i;
/*P*/
    D_0037A174 = 1;
    D_0037A164 = 0;
    D_0037A168 = 0;
    p = D_006257D4;
/*Q*/
    func_001be820(D_0037A16C, 48);
    t = D_0037A16C;
    t->h0 = 1;
    t->stk = 0;
    t->h2 = 0;
    t->h4 = 0;
    t->h6 = 0;
    t->ctx = p;
    p += 448;
    for (i = 1; i < 16; i++) {
        func_001be820(&D_0037A16C[i], 48);
        D_0037A16C[i].ctx = p;
        p += 0x81b0;
        D_0037A16C[i].stk = p;
        p += 16;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
        D_0037A16C[i].h6 = 0;
        D_0037A16C[i].h0 = 0;

    }
    for (i = 0; i < 384; i++) {
        func_001be820(&D_0037A16C[i + 16], 48);
        D_0037A16C[i + 16].ctx = p;
        p += 0x9b0;
        D_0037A16C[i + 16].stk = p;
        p += 16;
        D_0037A16C[i + 16].h2 = 0;
        D_0037A16C[i + 16].h4 = 0;
        D_0037A16C[i + 16].h6 = 0;
        D_0037A16C[i + 16].h0 = 0;

    }
    {
        u8 *c = D_0037A16C->ctx;
        RunQ_bfcd8 *q = D_0037A170;
        q[1].arg = -1;
        q->ctx = c;
        q[1].ctx = 0;
        q->arg = 0;
    }
}

#define D_00389C90 (*(Big_c5168 *)&D_00389C90)
#define D_0037A380 (*(Cam_c5168 *)&D_0037A380)
void func_001c5168(void) {
    V4 a;
    V4 b;
    f32 m[4][4] __attribute__((aligned(16)));
    Big_c5168 *g = &D_00389C90;
    switch ((u32)g->mode) {
    case 0:
        break;
    case 1:
        D_0037A380.pos.x += g->p12396->pos.x;
        D_0037A380.pos.y += g->p12396->pos.y;
        D_0037A380.pos.z += g->p12396->pos.z;
        break;
    case 2:
        D_0037A380.tgt.y += g->p12396->roty;
        sceVu0UnitMatrix(m);
        func_00267810(m, m, g->p12396->roty);
        func_002672f8(&D_0037A380.pos, m, &D_0037A380.pos);
        D_0037A380.pos.x += g->p12396->pos.x;
        D_0037A380.pos.y += g->p12396->pos.y;
        D_0037A380.pos.z += g->p12396->pos.z;
        break;
    case 3:
        func_001e9d00(&b, &g->p12400->pos, &g->p12396->pos, D_0037A380.tgt.z);
        D_0037A380.tgt.y += b.y;
        func_001e9fe8(&b, &D_0037A380.tgt);
        func_001e9f18(&a, &D_0037A380.pos, &b, D_0037A380.f96);
        a.x += g->p12400->pos.x;
        a.y += g->p12400->pos.y;
        a.z += g->p12400->pos.z;
        sceVu0UnitMatrix(m);
        func_00267810(m, m, g->p12396->roty);
        func_002672f8(&D_0037A380.pos, m, &D_0037A380.pos);
        D_0037A380.pos.x += g->p12396->pos.x;
        D_0037A380.pos.y += g->p12396->pos.y;
        D_0037A380.pos.z += g->p12396->pos.z;
        D_0037A380.f96 = func_001e9e58(&a, &D_0037A380.pos);
        func_001e9d00(&D_0037A380.tgt, &D_0037A380.pos, &a, D_0037A380.tgt.z);
        break;
    }
}
#undef D_00389C90
#undef D_0037A380

#define D_00389C90 (*(Big_c5b88 *)&D_00389C90)
#define D_0037A380 (*(CamPlay_c5b88 *)&D_0037A380)
#define D_003C5510 (*(Tw_c5b88 *)&D_003C5510)
static inline void inl_cp(V4a_c5b88 *d, V4a_c5b88 *a) {
    *d = *a;
}
s32 func_001c5b88(void) {
    Big_c5b88 *g = &D_00389C90;
    CamPlay_c5b88 *c = &D_0037A380;
    f32 t;
    t = c->t + D_002BBDFC * 0.5f * g->f12620;
    c->t = t;
    if ((f32)c->trk->end < t) {
        c->t = (f32)c->trk->end;
        func_001c53c8(c->t);
        inl_cp(&D_003C5510.v208, &c->v16);
        inl_cp(&D_003C5510.v224, &c->v64);
        inl_cp(&D_003C5510.v240, &c->v80);
        inl_cp(&D_003C5510.v272, &c->v48);
        inl_cp(&D_003C5510.v256, &c->v32);
        D_003C5510.f288 = c->f96;
        D_003C5510.f292 = c->fE0F4;
        func_001c6a20();
        g->d12400 &= ~(1ULL << 37);
    } else {
        func_001c53c8(t);
        inl_cp(&D_003C5510.v208, &c->v16);
        inl_cp(&D_003C5510.v224, &c->v64);
        inl_cp(&D_003C5510.v240, &c->v80);
        inl_cp(&D_003C5510.v272, &c->v48);
        inl_cp(&D_003C5510.v256, &c->v32);
        D_003C5510.f288 = c->f96;
        D_003C5510.f292 = c->fE0F4;
        func_001c6a20();
        if ((s32)(D_003C5510.flags >> 8) & 1) func_002675a8(&D_003C5510.v192, &D_003C5510.v208);
    }
    return 4;
}
#undef D_00389C90
#undef D_0037A380
#undef D_003C5510

#define D_003C5510 (*(Tw_c6720 *)&D_003C5510)
#define T D_003C5510
void func_001c6720(void) {
    V4 v;
    T.flags &= ~1;
    T.flags &= ~2;
    T.flags &= ~4;
    T.flags &= ~8;
    T.flags &= ~16;
    T.flags &= ~32;
    T.flags &= ~64;
    T.flags &= ~128;
    T.flags &= ~256;
    T.s.f[0] = 0.0f;
    T.s.f[1] = 0.0f;
    T.s.f[2] = 0.0f;
    T.s.f[3] = 0.0f;
    T.s.f[15] = 0.0f;
    T.s.f[16] = 0.0f;
    T.s.f[17] = 0.0f;
    T.s.f[18] = 1.0f;
    T.s.f[19] = 0.0f;
    T.s.f[20] = 0.0f;
    T.s.f[21] = 0.0f;
    T.s.f[22] = 0.0f;
    T.s.f[23] = 1000.0f;
    T.s.f[24] = 53.0f;
    T.s.f[27] = 0.0f;
    T.s.f[28] = 0.0f;
    T.s.f[29] = 0.0f;
    T.s.f[30] = 1.0f;
    T.s.f[31] = 0.0f;
    T.s.f[32] = 0.0f;
    T.s.f[33] = 0.0f;
    T.s.f[34] = 0.0f;
    T.s.f[35] = 1000.0f;
    T.s.f[36] = 53.0f;
    T.s.f[51] = 0.0f;
    T.s.f[52] = 0.0f;
    T.s.f[53] = 0.0f;
    T.s.f[54] = 1.0f;
    T.s.f[55] = 0.0f;
    T.s.f[56] = 0.0f;
    T.s.f[57] = 0.0f;
    T.s.f[58] = 0.0f;
    T.s.f[63] = 0.0f;
    T.s.f[64] = 0.0f;
    T.s.f[65] = 1.0f;
    T.s.f[66] = 1.0f;
    T.s.f[67] = 0.0f;
    T.s.f[68] = 1.0f;
    T.s.f[69] = 0.0f;
    T.s.f[70] = 1.0f;
    T.s.f[71] = 1000.0f;
    T.s.f[72] = 53.0f;
    func_001c6890();
    func_002675a8(&v, (V4 *)&T.s.f[55]);
    v.y += 3.1415928f;
    func_001e9fe8(&v, &v);
    T.s.f[73] = v.y;
}
#undef D_003C5510
#undef T

#define D_003C5510 (*(Tw_c6890 *)&D_003C5510)
void func_001c6890(void) {
    V4 a;
    f32 m[4][4] __attribute__((aligned(16)));
    V4 r;

    memset(&a, 0, 16);
    a.w = 1.0f;
    memset(&r, 0, 16);
    func_002675a8(&a, &D_002E2780);
    func_002675a8(&D_003C5510.v208, &D_002E2790);
    D_003C5510.f288 = func_001e9e58(&a, &D_003C5510.v208);
    D_003C5510.f292 = D_002E27A0;
    func_001e9d00(&r, &D_003C5510.v208, &a, D_002E27A4);
/*P*/
    D_003C5510.v256.x = 0.0f;
    D_003C5510.v256.y = 0.0f;
    D_003C5510.v256.z = 1.0f;
    D_003C5510.v256.w = 1.0f;
    D_003C5510.v272.x = 0.0f;
    D_003C5510.v272.y = 1.0f;
    D_003C5510.v272.z = 0.0f;
    D_003C5510.v272.w = 1.0f;
/*Q*/
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002672f8(&D_003C5510.v256, m, &D_003C5510.v256);
    func_002672f8(&a, m, &a);
    func_002675a8(&D_003C5510.v224, &r);
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002676c0(m, m, r.z);
    func_002672f8(&D_003C5510.v272, m, &D_003C5510.v272);
}
#undef D_003C5510

#define D_003C5510 (*(Tw_c9ac8 *)&D_003C5510)
void func_001c9ac8(void) {
    f32 t0, t1, a, u, u2, u3, d;
    f32 *s, *e;
    t1 = t0 = 0.0f;
    D_003C5510.t[0] += D_002BBDFC;
    s = &D_003C5510.start[0];
    e = &D_003C5510.end[0];
    switch (D_003C5510.m[2]) {
    case 0:
    case 3:
        t0 = (*e - *s) / D_003C5510.dur[0];
        break;
    case 1:
    case 2:
        break;
    }
    switch (D_003C5510.m[2]) {
    case 0:
    case 2:
        t1 = (*e - *s) / D_003C5510.dur[0];
        break;
    case 1:
    case 3:
        t1 = 0.0f;
        break;
    }
    a = 0.0f;
    if (D_003C5510.t[0] == a) {
        D_003C5510.cur[0] = *s;
    } else if (D_003C5510.dur[0] <= D_003C5510.t[0]) {
        D_003C5510.cur[0] = *e;
    } else {
        d = D_003C5510.dur[0] - a;
        u = (D_003C5510.t[0] - a) / d;
        u2 = u * u;
        u3 = u * u2;
        D_003C5510.cur[0] = ((u3 + u3) - u2 * 3.0f + 1.0f) * *s
            + (u3 * -2.0f + u2 * 3.0f) * *e
            + ((u3 - (u2 + u2) + u) * t0 + (u3 - u2) * t1) * d;
    }
    func_001c6a20();
    if (D_003C5510.t[0] > D_003C5510.dur[0]) D_003C5510.flags &= ~64;
}
#undef D_003C5510

#define D_003C5510 (*(Tw_c9e80 *)&D_003C5510)
void func_001c9e80(void) {
    f32 t0, t1, a, u, u2, u3, d;
    f32 *s, *e;
    t1 = t0 = 0.0f;
    D_003C5510.t[1] += D_002BBDFC;
    s = &D_003C5510.start[1];
    e = &D_003C5510.end[1];
    switch (D_003C5510.m[3]) {
    case 0:
    case 3:
        t0 = (*e - *s) / D_003C5510.dur[1];
        break;
    case 1:
    case 2:
        break;
    }
    switch (D_003C5510.m[0]) {
    case 0:
    case 2:
        t1 = (*e - *s) / D_003C5510.dur[1];
        break;
    case 1:
    case 3:
        t1 = 0.0f;
        break;
    }
    a = 0.0f;
    if (D_003C5510.t[1] == a) {
        D_003C5510.cur[1] = *s;
    } else if (D_003C5510.dur[1] <= D_003C5510.t[1]) {
        D_003C5510.cur[1] = *e;
    } else {
        d = D_003C5510.dur[1] - a;
        u = (D_003C5510.t[1] - a) / d;
        u2 = u * u;
        u3 = u * u2;
        D_003C5510.cur[1] = ((u3 + u3) - u2 * 3.0f + 1.0f) * *s
            + (u3 * -2.0f + u2 * 3.0f) * *e
            + ((u3 - (u2 + u2) + u) * t0 + (u3 - u2) * t1) * d;
    }
    func_001c6a20();
    if (D_003C5510.t[1] > D_003C5510.dur[1]) D_003C5510.flags &= ~128;
}
#undef D_003C5510

#define D_003C5510 (*(Tw_ca800 *)&D_003C5510)
#define B(n) ((s32)(D_003C5510.flags >> (n)) & 1)
void func_001ca800(void) {
    if ((u32)(D_0038CD00 >> 37) % 2 == 1) {
        func_0011ef10(99999, func_001c5b88);
    }
    if (B(0)) {
        func_001c8758();
        if (B(8)) {
            func_002675a8(&D_003C5510.v192, &D_003C5510.v208);
        }
    }
    if (B(4)) {
        func_001c9308();
        if (B(8)) {
            func_002675a8(&D_003C5510.v192, &D_003C5510.v208);
        }
    }
    if (B(1)) func_001c8930();
    if (B(5)) func_001c96c0();
    if (B(2)) func_001c8c10();
    if (B(6)) func_001c9ac8();
    if (B(3)) func_001c8d18();
    if (B(7)) func_001c9e80();
    if (B(8)) func_0011ef10(99999, func_001c8e20);
    if (B(9)) func_001c9d40();
}
#undef D_003C5510
#undef B

typedef VmRec VM_c91e8;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4_c91e8;
typedef struct {
    union {
        u64 flags;
        struct { s32 lo; f32 dur0; f32 dur1; } s;
    } u;
    u8 pad10[8];
    f32 t0;
    f32 t1;
    u8 pad20[0xc];
    s32 x2c;
    u8 pad30[0x10];
    V4_c91e8 p40;
    V4_c91e8 p50;
    V4_c91e8 p60;
    V4_c91e8 p70;
    V4_c91e8 p80;
    u8 pad90[0x10];
    f32 r[3];
    s32 xac;
    f32 fb0;
    s32 xb4;
    u8 padb8[8];
    V4_c91e8 v0;
    V4_c91e8 a, b, c, d, e;
    f32 f50;
    f32 f54;
} Cam_c91e8;
#define D_003C5510 (*(Cam_c91e8 *)&D_003C5510)
s32 func_001c91e8(VM_c91e8 *vm) {
    if (vm->stk[vm->sp] > 0) {
        func_001c6890();
        D_003C5510.xb4 = 0;
        D_003C5510.u.flags |= 0x100;
        D_003C5510.r[0] = vm->stk[vm->sp - 4];
        D_003C5510.r[1] = vm->stk[vm->sp - 3];
        D_003C5510.r[2] = vm->stk[vm->sp - 2];
        D_003C5510.xac = vm->stk[vm->sp - 1];
        D_003C5510.fb0 = vm->stk[vm->sp] * 2.0f;
        func_002675a8(&D_003C5510.v0, &D_003C5510.a);
    } else {
        D_003C5510.u.flags &= ~0x100;
    }
    vm->sp -= 5;
    return 2;
}
#undef D_003C5510
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0037.h"
#include "data/data_0038.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003C.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
