#include "common.h"
typedef struct { u16 x0; u8 pad2[10]; u8 xc; } W29Sub;
typedef struct {
    s32 x0;
    s32 x4;
    s16 x8, xa;
    u16 xc, xe;
    u8 x10, x11, x12, x13;
    s32 x14;
    f32 x18, x1c;
    W29Sub *x20;
    void *x24;
    s32 x28;
} W29Obj;
extern s32 D_004D59F0[];
extern s32 D_004D5AF0;
void *func_00121e28(s32, void *);
void func_00121ee0(void *);
void func_0010d470(W29Obj *, W29Sub *);

s32 func_0010ef90(s32 a, s32 *out) {
    struct { W29Obj *o; W29Sub *s; } l;
    W29Obj *p, *p2, *p3, *p4, *p5;
    s32 i, m;
    p = l.o = func_00121e28(0x2C, &l.o);
    p->x12 = 0;
    p2 = l.o;
    p2->x10 = 1;
    p2->x0 = 0;
    p3 = l.o;
    p3->x4 = a;
    p3->x13 |= 2;
    p3->x8 = 0;
    p3->xa = 0;
    p3->x24 = 0;
    p3->x14 = 0;
    p4 = l.o;
    p4->x11 = 0;
    p5 = l.o;
    p5->xc = 0;
    p5->xe = 0;
    p5->x18 = 0;
    p5->x1c = 0;
    p5->x20 = 0;
    p5->x28 = 0;
    l.s = func_00121e28(0x1890, &l.s);
    func_0010d470(l.o, l.s);
    func_00121ee0(l.s);
    func_00121ee0(l.o);
    m = 0;
    for (i = 0; i < D_004D5AF0; i++) {
        if (m < D_004D59F0[i]) m = D_004D59F0[i];
    }
    *out = D_004D5AF0;
    return m;
}

typedef struct { u8 pad[6]; u16 v; u8 pad8[8]; } W29Ent;
typedef struct { u16 n; u8 pad[0xe]; W29Ent e[1]; } W29Tbl;
typedef struct { u8 pad[0x88]; u16 x88; u8 pad8a[0x16]; W29Tbl *xa0; } W29Mdl;
typedef struct { s32 a, b; } W29Pair;
typedef struct { s32 x0, x4; } W29Cnt;
extern W29Pair *D_004D5AF4;

void func_0010f258(W29Cnt *c, W29Mdl *m) {
    s32 idx[32];
    W29Tbl *t;
    s32 i, k;
    u16 id;
    k = 0;
    t = m->xa0;
    c->x0--;
    c->x4--;
    id = m->x88;
    for (i = 0; i < t->n - 1; i++) {
        if (t->e[i].v != t->e[i + 1].v) idx[k++] = i;
    }
    idx[k++] = t->n - 1;
    D_004D5AF4 = func_00121e28(k * 8, &D_004D5AF4);
    for (i = 0; i < k; i++) {
        s32 j = idx[i];
        D_004D5AF4[i].a = id;
        D_004D5AF4[i].b = ((W29Ent *)t)[j + 1].v;
    }
}

typedef struct { u64 d[14]; } W29S70;
extern s32 D_004D9240;
extern W29S70 D_002C5AD0[2];
extern W29S70 D_002BCA00[2];
s32 func_0010f8a0(void);
void func_0011f668(void);
void func_001ba4a8(void);

void func_0010fd40(void) {
    s32 i;
    func_0010f8a0();
    if (D_004D9240) {
        for (i = 0; i < 2; i++) D_002C5AD0[i] = D_002BCA00[i];
    }
    func_0011f668();
    for (i = 0; i < 2; i++) D_002BCA00[i] = D_002C5AD0[i];
    if (D_004D9240) func_001ba4a8();
}

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u64 d, a; } W29Ad;
typedef struct {
    union {
        u128 q;
        struct {
            u64 nloop : 15;
            u64 eop : 1;
            u64 pad16 : 16;
            u64 id : 14;
            u64 pre : 1;
            u64 prim : 11;
            u64 flg : 2;
            u64 nreg : 4;
            u64 regs : 4;
            u64 regs_hi : 60;
        } b;
    } tag;
    W29Ad r[31];
} W29Env;
extern W29Env D_004D8EF0;
extern u64 D_002BC750[];
extern u64 D_002BC7C0[];
extern u64 D_002BC830[];
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void sceGsPutDrawEnv(void *);

void func_001100a8(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        D_004D8EF0.r[i].d = D_002BC830[i];
        D_004D8EF0.r[i].a = D_002BC750[i];
        D_004D8EF0.r[i + 13].d = D_002BC830[i];
        D_004D8EF0.r[i + 13].a = D_002BC7C0[i];
    }
    D_004D8EF0.tag.q = 0;
    D_004D8EF0.tag.b.nloop = 31;
    D_004D8EF0.tag.b.eop = 1;
    D_004D8EF0.tag.b.nreg = 1;
    D_004D8EF0.tag.b.regs = 0xe;
    D_004D8EF0.r[26].d = 1;
    D_004D8EF0.r[26].a = 0x1a;
    D_004D8EF0.r[27].d = 1;
    D_004D8EF0.r[27].a = 0x46;
    D_004D8EF0.r[28].d = 0;
    D_004D8EF0.r[28].a = 0x45;
    D_004D8EF0.r[29].d = 0;
    D_004D8EF0.r[29].a = 0x49;
    D_004D8EF0.r[30].d = -4;
    D_004D8EF0.r[30].a = 0x44;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(&D_004D8EF0);
}

extern s32 D_002BBE04, D_002BBE14, D_002BBE18, D_002A6208, D_002A61F4, D_002BC738, D_002A6204, D_002A61F0;
extern s32 D_002BC060[4];
extern s32 D_002BC080[4];
extern s32 D_002BC0B0[4];
void func_00110360(void);

void func_001103a0(void) {
    D_002BBE04 = 0;
    D_002BBE14 = 0;
    D_002BBE18 = 0;
    D_002A6208 = 0;
    D_002A61F4 = 0;
    D_002BC738 = 0;
    D_002A6204 = 0;
    D_002A61F0 = 0;
    D_002BC060[0] = D_002BC060[1] = D_002BC060[2] = 0;
    D_002BC060[3] = 0x80;
    D_002BC080[0] = D_002BC080[1] = D_002BC080[2] = 0x80;
    D_002BC080[3] = 0x60;
    D_002BC0B0[0] = D_002BC0B0[1] = D_002BC0B0[2] = 0xFF;
    D_002BC0B0[3] = 0;
    func_00110360();
}

extern volatile s32 D_004D90F4;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;
extern f32 D_002BBE00;
extern s32 D_002BBE0C;
extern s32 D_002BBE10;
extern s32 D_002BC740;
void func_0010c348(void);

void func_001104e0(void) {
    s32 i;
    func_0010c348();
    D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
    if (D_004D90F4 < D_002BBE0C + 1) {
        for (i = 0; i < D_002BBE0C; i++) {
            func_0010c348();
            D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
        }
    }
    if (D_002BBE10) D_002BBDFC = D_002BBDEC + D_002BBDEC;
    D_002BBDFC = D_002BBDFC * D_002BBE00;
    if (D_002BC740 != 1) {
        if (D_002BBDFC > 5.0f) D_002BBDFC = 5.0f;
    } else {
        D_002BBDFC = 128.0f;
    }
    D_004D90F4 = 0;
}

typedef struct { u8 x0; u8 w; u8 d[1]; } W29Map;
extern s32 D_002BBD90[];
extern W29Map *D_002BBD48[];
void func_00111600(s32, s32, u8);

void func_001116b0(s32 id, s32 row) {
    W29Map *m;
    u8 *hdr, *r;
    s32 i;
    if (D_002BBD90[id] == 0) return;
    m = D_002BBD48[id];
    hdr = m->d;
    r = hdr + m->w * (row + 1);
    for (i = 0; i < m->w; i++) {
        if (r[i] != '#') func_00111600(id, hdr[i] - 1, r[i] - 'a');
    }
}

u32 func_00111b08(void);

u32 func_00111be8(void) {
    u32 t, h, m, s;
    t = func_00111b08();
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    t = t % 3600;
    s = t / 60;
    t = t % 60;
    {
        f32 r = (f32)t;
        r *= 1.6666667f;
        return (u32)r;
    }
}

extern s32 D_004D925C;
extern s32 D_002BCC1C;
extern s32 D_004D9254;
extern volatile u32 D_002BBDF0;
extern u32 D_004D9250;

s32 func_00111cb8(void) {
    switch (D_004D925C) {
    case 2:
        return 4;
    case 0:
        if (D_002BCC1C < D_004D9254) {
            D_002BCC1C = (f32)(D_002BBDF0 - D_004D9250) * D_002BBDEC;
            return 0;
        }
        D_002BCC1C = D_004D9254;
        return 4;
    case 1:
        return 0;
    }
    return 0;
}
