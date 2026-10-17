#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x20];
    f32 f3c;
    u8 pad40[0x330];
    u64 f370;
} Ent;
typedef struct {
    s32 x0;
    Ent *ent;
    u8 pad8[0x60];
    f32 f68;
    s32 f6c;
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    u64 flags;
    f32 f330;
    u8 pad334[0xc];
    f32 f340[3];
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
double sin(double);
double cos(double);
typedef struct { f32 a[4]; s32 b[3]; s32 pad; u64 d[2]; } CamS;
typedef struct { u8 st[4]; u8 x4[12]; u16 tbl[8][256]; s32 cnt[8]; s8 ids[4]; u8 pad1034[0x3034 - 0x1034]; s32 f3034; s32 f3038; u8 pad303c[0x3070 - 0x303c]; union { u64 x; s32 i[2]; } f3070; union { u64 x; s32 i[2]; } f3078; u8 pad3080[0x14]; s32 f3094; u8 pad3098[0x316c - 0x3098]; s32 f316c; u8 pad3170[0x3460 - 0x3170]; f32 dur; f32 t; u8 pad3468[8]; CamS start; CamS tgt; } Str;
extern Str D_00389C90;
extern s32 D_00389C80;
extern char *D_00388480[];
typedef struct { u64 d[22]; } Win;
extern Win D_00629E70[];
extern s32 D_0037A378;
void func_0010ef70(Win *, char *, void *);
s32 func_001cbd80();
extern u8 D_003C5650[];
extern char D_0062A1F0[];

s32 func_001cb7d0(VM *vm) {
    s32 val = vm->stk[vm->sp];
    s32 idx = vm->stk[vm->sp - 1];
    s32 n, i, j, d, q;
    vm->sp -= 2;
    n = 1;
    for (d = val / 10; d > 0; d /= 10) n++;
    for (i = 0; i < n; i++) {
        d = 1;
        for (j = 0; j < n - 1 - i; j++) d *= 10;
        q = val / d;
        D_0062A1F0[i] = q + 33;
        val -= q * d;
    }
    for (j = 0; (u32)j < 12; j++) D_0062A1F0[i++] = D_003C5650[j];
    D_00388480[D_00389C80] = D_0062A1F0;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = *(u16 *)&D_00389C80;
    D_00389C80++;
    return 2;
}

s32 func_001cb960(VM *vm) {
    s32 idx, v, i;
    if (D_0037A378 & 1) { vm->sp -= 2; return 2; }
    idx = vm->stk[vm->sp - 1];
    v = vm->stk[vm->sp];
    vm->sp -= 2;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = v;
    for (i = 0; i < 4; i++) if (idx == D_00389C90.ids[i]) break;
    if (i < 4) {
        if (D_00389C90.st[i] == 4) {
            D_00389C90.st[i] = 2;
            D_00389C90.x4[idx] = 2;
            func_0010ef70(&D_00629E70[i], D_00388480[v], func_001cbd80);
        }
    }
    return 2;
}

extern Win D_006298F0[];
void func_0010bdd0(Win *, void *);
s32 func_001cbab0();
s32 func_001cbbd0(VM *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.st[i] == 0) break;
    if (i >= 4 || D_00389C90.x4[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbab0);
    D_00389C90.st[i] = 1;
    D_00389C90.x4[idx] = 1;
    return 2;
}

s32 func_001cbea0();
s32 func_001cbfc0(VM *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.st[i] == 0) break;
    if (i >= 4 || D_00389C90.x4[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbea0);
    D_00389C90.st[i] = 1;
    D_00389C90.x4[idx] = 1;
    return 2;
}

extern void *D_003DABD0[];
extern char D_003C58E0[][256];
void *func_001559f0(s32, s32);
void func_00120748(char *, void *, void *, s32);
s32 func_001cf348();
s32 func_001cf3e0();
s32 func_001cf478(VM *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}

extern char D_003D97E0[][256];
s32 func_001cf5d0(VM *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}

typedef struct { void *p; u8 pad[0x34c]; } Obj350;
extern Obj350 D_003C3A70[];
extern s32 D_003C54F0;
extern Obj350 D_003A7990[];
extern s32 D_003B4D90;
extern Obj350 D_0038D170[];
extern s32 D_0039A570;
extern Obj350 D_0039A580[];
extern s32 D_003A7980;
s32 func_00123488(void *);
s32 func_001d0b90(VM *vm) {
    Msg m;
    s32 i;
    m.type = 13;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    if (D_00389C90.f316c) {
        for (i = 0; i < D_003C54F0; i++) {
            if (func_00123488(D_003C3A70[i].p)) { m.x = (s32)D_003C3A70[i].p; func_001c4640(&m); }
        }
    } else if (((s32)(vm->flags >> 5) & 1) == 1U) {
        if (D_00389C90.f3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123488(D_003A7990[i].p)) { m.x = (s32)D_003A7990[i].p; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].p)) { m.x = (s32)D_0039A580[i].p; func_001c4640(&m); }
            }
        }
    } else {
        if (D_00389C90.f3034 == 0) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123488(D_0038D170[i].p)) { m.x = (s32)D_0038D170[i].p; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].p)) { m.x = (s32)D_0039A580[i].p; func_001c4640(&m); }
            }
        }
    }
    return 2;
}

s32 func_001d0dd0(VM *vm) {
    Msg m;
    s32 i;
    m.type = 14;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    if (D_00389C90.f316c) {
        for (i = 0; i < D_003C54F0; i++) {
            if (func_00123488(D_003C3A70[i].p)) { m.x = (s32)D_003C3A70[i].p; func_001c4640(&m); }
        }
    } else if (((s32)(vm->flags >> 5) & 1) == 1U) {
        if (D_00389C90.f3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123488(D_003A7990[i].p)) { m.x = (s32)D_003A7990[i].p; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].p)) { m.x = (s32)D_0039A580[i].p; func_001c4640(&m); }
            }
        }
    } else {
        if (D_00389C90.f3034 == 0) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123488(D_0038D170[i].p)) { m.x = (s32)D_0038D170[i].p; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].p)) { m.x = (s32)D_0039A580[i].p; func_001c4640(&m); }
            }
        }
    }
    return 2;
}

typedef struct { f32 x[4]; } __attribute__((aligned(16))) V4;
extern V4 D_00490630;
void func_001e9fe8(f32 *, f32 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00267768(f32 (*)[4], f32 (*)[4], f32);
void func_00267810(f32 (*)[4], f32 (*)[4], f32);
void func_002672f8(V4 *, f32 (*)[4], V4 *);
void func_001315c0(Ent *, s32, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_0014f9b0(Ent *, V4 *, f32);
s32 func_001d2958(VM *vm) {
    V4 v;
    f32 rot[4];
    f32 out[4];
    f32 t[4];
    f32 m[4][4] __attribute__((aligned(16)));
    Ent *e;
    v = D_00490630;
    e = vm->ent;
    if (e) {
        rot[0] = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
        rot[1] = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f + vm->ent->f3c;
        rot[2] = 0.0f;
        func_001e9fe8(out, rot);
        sceVu0UnitMatrix(m);
        func_00267768(m, m, out[0]);
        func_00267810(m, m, out[1]);
        func_002672f8(&v, m, &v);
        func_001315c0(vm->ent, 0, t, 0.0f);
        func_00267518(v.x, t, v.x);
        func_0014f9b0(vm->ent, &v, vm->stk[vm->sp] * 2.0f);
    }
end:
    vm->sp -= 3;
    return 2;
}

typedef struct { u8 pad[0xa80]; u8 a[10]; u8 b[10]; u8 c[10]; u8 d[50]; } Save;
Save *func_00232cc0(s32);
s32 func_001d8400(VM *vm) {
    Save *p = func_00232cc0(1);
    s32 i;
    switch (vm->stk[vm->sp]) {
    case 0:
        for (i = 0; i < 10; i++) if (!p->a[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 1:
        for (i = 0; i < 10; i++) if (!p->b[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 2:
        for (i = 0; i < 10; i++) if (!p->c[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 3:
        for (i = 0; i < 50; i++) if (!p->d[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    }
    return 2;
}

extern CamS D_002BC0F0;
extern f32 D_002BBDFC;
void func_001d8f38(void) {
    Str *g = &D_00389C90;
    f32 r, t;
    t = g->t + D_002BBDFC;
    g->t = t;
    if (g->dur < t) {
        D_002BC0F0 = g->tgt;
        g->f3078.x &= ~2ULL;
        return;
    }
    r = g->t / g->dur;
    D_002BC0F0.b[0] = g->start.b[0] + (g->tgt.b[0] - g->start.b[0]) * r;
    g->t += D_002BBDFC;
    D_002BC0F0.b[1] = g->start.b[1] + (g->tgt.b[1] - g->start.b[1]) * r;
    D_002BC0F0.b[2] = g->start.b[2] + (g->tgt.b[2] - g->start.b[2]) * r;
    D_002BC0F0.a[0] = g->start.a[0] + (g->tgt.a[0] - g->start.a[0]) * r;
    D_002BC0F0.a[1] = g->start.a[1] + (g->tgt.a[1] - g->start.a[1]) * r;
    D_002BC0F0.a[2] = g->start.a[2] + (g->tgt.a[2] - g->start.a[2]) * r;
    D_002BC0F0.a[3] = g->start.a[3] + (g->tgt.a[3] - g->start.a[3]) * r;
    if (g->dur < g->t) {
        D_002BC0F0 = g->tgt;
        g->f3078.x &= ~2ULL;
    }
}

s32 func_001d9100(VM *vm) {
    Str *g = &D_00389C90;
    g->tgt = g->start = D_002BC0F0;
    g->t = 0.0f;
    g->dur = vm->stk[vm->sp - 7] * 2.0f;
    g->tgt.b[0] = vm->stk[vm->sp - 6];
    g->tgt.b[1] = vm->stk[vm->sp - 5];
    g->tgt.b[2] = vm->stk[vm->sp - 4];
    g->tgt.a[0] = vm->stk[vm->sp - 2];
    g->tgt.a[1] = vm->stk[vm->sp - 3];
    g->tgt.a[2] = vm->stk[vm->sp - 1];
    g->tgt.a[3] = vm->stk[vm->sp];
    if (g->dur < 2.0f) {
        D_002BC0F0.b[0] = g->tgt.b[0];
        D_002BC0F0.b[1] = g->tgt.b[1];
        D_002BC0F0.b[2] = g->tgt.b[2];
        D_002BC0F0.a[0] = g->tgt.a[0];
        D_002BC0F0.a[1] = g->tgt.a[1];
        D_002BC0F0.a[2] = g->tgt.a[2];
        D_002BC0F0.a[3] = g->tgt.a[3];
        g->f3078.x &= ~2ULL;
    } else {
        g->f3078.x |= 2;
    }
    vm->sp -= 8;
    return 2;
}

void func_001dcfd0(VM *vm) {
    Msg m;
    Ent *e;
    if ((s32)(vm->flags >> 14) & 1) {
        e = vm->ent;
        if (e) {
            m.type = 39;
            m.x = vm->x0;
            m.val = 0;
            m.v[0] = e->pos[0];
            m.v[1] = e->pos[1] - 20.0f;
            m.v[2] = e->pos[2];
            m.v[3] = 1.0f;
            func_001c4640(&m);
        }
        vm->f330 -= D_002BBDFC;
        if (vm->f330 < 0.0f) vm->flags &= ~0x4000;
    }
    if ((s32)(vm->flags >> 15) & 1) {
        if (vm->ent) {
            m.type = 39;
            m.x = vm->x0;
            m.val = 0;
            m.v[0] = vm->f340[0];
            m.v[1] = vm->f340[1];
            m.v[2] = vm->f340[2];
            m.v[3] = 1.0f;
            func_001c4640(&m);
        }
        vm->f330 -= D_002BBDFC;
        if (vm->f330 < 0.0f) vm->flags &= ~0x8000;
    }
}

typedef struct { s32 x0; u8 pad4[0x10]; s32 f14; } Q10;
typedef struct { u8 pad0[0x10]; Q10 *q; u8 * f14; s32 f18; f32 f1c; f32 f20; f32 f24; } Task;
extern f32 D_002E2790[4];
extern f32 D_002E2780[4];
f32 func_001e9e58(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_001e9d00(f32 *, f32 *, f32 *, f32);
void func_001e9dc8(f32 *, f32 *, f32 *);
void func_002675a8(s32, f32 *);
s32 func_001dedd8(Task *o) {
    f32 v[4];
    f32 r[4];
    f32 t[4];
    f32 d;
    if (o->q->f14 & 2) return 4;
    d = func_001e9e58(D_002E2790, D_002E2780);
    func_00267530(v, D_002E2790, D_002E2780);
    v[0] = v[0] / d * o->f1c;
    v[1] = v[1] / d * o->f1c;
    v[2] = v[2] / d * o->f1c;
    func_00267518(v, D_002E2780, v);
    func_001e9d00(r, D_002E2790, D_002E2780, 0.0f);
    t[0] = o->f20;
    t[1] = o->f24;
    t[2] = 0.0f;
    t[3] = 1.0f;
    func_001e9dc8(v, r, t);
    func_002675a8(o->q->x0, v);
    return 0;
}

extern void *D_0062A220;
extern void *D_0062A224;
extern u8 D_0062A630[];
s32 func_00176040(void *, void *, s32, s32);
Q10 *func_001760d0(s32);
Task *func_0011f090(void *, s32, void *);
s32 func_001def20(VM *vm) {
    f32 v[4];
    f32 r[4];
    f32 t[4];
    f32 d, s;
    Q10 *k;
    Task *n;
    d = func_001e9e58(D_002E2790, D_002E2780);
    func_00267530(v, D_002E2790, D_002E2780);
    s = vm->stk[vm->sp - 2];
    v[0] = v[0] / d * s;
    v[1] = v[1] / d * s;
    v[2] = v[2] / d * s;
    func_00267518(v, D_002E2780, v);
    func_001e9d00(r, D_002E2790, D_002E2780, 0.0f);
    t[0] = vm->stk[vm->sp - 1];
    t[1] = vm->stk[vm->sp];
    t[2] = 0.0f;
    t[3] = 1.0f;
    func_001e9dc8(v, r, t);
    func_00176040(D_0062A220, D_0062A224, vm->stk[vm->sp - 3], 0);
    k = func_001760d0(vm->stk[vm->sp - 3]);
    if (k) {
        func_002675a8(k->x0, v);
        n = func_0011f090(D_0062A630, 0, func_001dedd8);
        n->f18 = 0;
        n->q = k;
        n->f14 = 0;
        n->f1c = vm->stk[vm->sp - 2];
        n->f20 = vm->stk[vm->sp - 1];
        n->f24 = vm->stk[vm->sp];
    }
    vm->sp -= 4;
    return 2;
}

extern s32 D_003DAD38;
extern f32 D_003DAD3C;
extern f32 D_003DACB0;
extern f32 D_003DACB4;
extern s32 D_003DACB8;
extern s32 D_003DACBC;
extern u64 D_003DAE40[];
extern u8 D_003DAF60[];
void func_001e06c8(s32);
void func_001e05a8(void *);
s32 func_001e08d8(void) {
    f32 sx, sy;
    s32 ox, oy;
    u64 v, w;
    if (!D_003DAD38) return 4;
    func_001e06c8(D_003DAD3C);
    D_003DAE40[26] = 0x8080;
    sx = D_003DACB0;
    ox = D_003DACB8;
    D_003DAE40[15] = 0x180808080ULL;
    v = (f32)(ox + 0x7000) + (4096.0f - sx * 4096.0f);
    oy = D_003DACBC;
    sy = D_003DACB4;
    w = (f32)(oy + 0x73f8) + (3072.0f - sy * 3072.0f);
    D_003DAE40[31] = 0x180808080ULL;
    D_003DAE40[33] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    v = (sx * 8192.0f * 0.5f - 4096.0f + 36864.0f) + (f32)ox;
    w = (sy * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f) + (f32)oy;
    D_003DAE40[35] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    func_001e05a8(D_003DAF60);
    return 0;
}

/* needs make: uses rodata */
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
int sprintf(char *, const char *, ...);
extern char D_0062A228[];
extern char D_0062A328[];
extern char D_003DABD8[][6];
s32 func_001ddc48();
s32 func_001ddc78(VM *vm) {
    char buf[256];
    void **pp = &D_0062A220;
    void *p = func_001559f0(50, 2);
    strcpy(D_0062A228, "eveffect/");
    *pp = p;
    D_0062A224 = (u8 *)p + 0x7d000;
    strcat(D_0062A228, D_003DABD8[vm->stk[vm->sp - 1]]);
    sprintf(buf, "_%03d", vm->stk[vm->sp]);
    strcat(D_0062A228, buf);
    strcpy(D_0062A328, D_0062A228);
    strcat(D_0062A228, ".dpp");
    strcat(D_0062A328, ".dpx");
    func_00120748(D_0062A228, D_0062A224, func_001ddc48, 0);
    D_00389C90.f3070.x |= 0x100000000000ULL;
    D_00389C90.f3094 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

s32 func_001dde08(VM *vm) {
    char buf[256];
    void **pp = &D_0062A220;
    void *p = func_001559f0(60, 2);
    strcpy(D_0062A228, "eveffect/");
    *pp = p;
    D_0062A224 = (u8 *)p + 0x7d000;
    strcat(D_0062A228, D_003DABD8[vm->stk[vm->sp - 1]]);
    sprintf(buf, "_%03d", vm->stk[vm->sp]);
    strcat(D_0062A228, buf);
    strcpy(D_0062A328, D_0062A228);
    strcat(D_0062A228, ".dpp");
    strcat(D_0062A328, ".dpx");
    func_00120748(D_0062A228, D_0062A224, func_001ddc48, 0);
    D_00389C90.f3070.x |= 0x100000000000ULL;
    D_00389C90.f3094 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}
