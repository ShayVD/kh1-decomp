#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
typedef struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x20];
    f32 f3c;
    u8 pad40[0x330];
    u64 f370;
} Ent;
typedef VmRec VM;
double sin(double);
double cos(double);
#include "data/types/text_001c0000_h67.h"
extern Str D_00389C90;

/* func_001cb7d0, func_001cb960, func_001cbbd0 and func_001cbfc0 (and D_0062A1F0) are in src/msgwin/msgwin.c. */

/* func_001cf478 and func_001cf5d0 are in src/vm/vm_lib.c. */
void *func_001559f0(s32, s32);
void func_00120748(char *, void *, void *, s32);

#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003C3A70.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"

#include "data/types/text_001c0000_h67_p.h"
extern V4 D_00490630;
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00267518(f32 *, f32 *, f32 *);

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

#include "data/pieces/D_002BC0F0.h"
extern f32 D_002BBDFC;
void func_001d8f38(void) {
    Str *g = &D_00389C90;
    f32 r, t;
    t = g->t + D_002BBDFC;
    g->t = t;
    if (g->dur < t) {
        D_002BC0F0.camS = g->tgt;
        g->f3078.x &= ~2ULL;
        return;
    }
    r = g->t / g->dur;
    D_002BC0F0.camS.b[0] = g->start.b[0] + (g->tgt.b[0] - g->start.b[0]) * r;
    g->t += D_002BBDFC;
    D_002BC0F0.camS.b[1] = g->start.b[1] + (g->tgt.b[1] - g->start.b[1]) * r;
    D_002BC0F0.camS.b[2] = g->start.b[2] + (g->tgt.b[2] - g->start.b[2]) * r;
    D_002BC0F0.camS.a[0] = g->start.a[0] + (g->tgt.a[0] - g->start.a[0]) * r;
    D_002BC0F0.camS.a[1] = g->start.a[1] + (g->tgt.a[1] - g->start.a[1]) * r;
    D_002BC0F0.camS.a[2] = g->start.a[2] + (g->tgt.a[2] - g->start.a[2]) * r;
    D_002BC0F0.camS.a[3] = g->start.a[3] + (g->tgt.a[3] - g->start.a[3]) * r;
    if (g->dur < g->t) {
        D_002BC0F0.camS = g->tgt;
        g->f3078.x &= ~2ULL;
    }
}

s32 func_001d9100(VM *vm) {
    Str *g = &D_00389C90;
    g->tgt = g->start = D_002BC0F0.camS;
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
        D_002BC0F0.camS.b[0] = g->tgt.b[0];
        D_002BC0F0.camS.b[1] = g->tgt.b[1];
        D_002BC0F0.camS.b[2] = g->tgt.b[2];
        D_002BC0F0.camS.a[0] = g->tgt.a[0];
        D_002BC0F0.camS.a[1] = g->tgt.a[1];
        D_002BC0F0.camS.a[2] = g->tgt.a[2];
        D_002BC0F0.camS.a[3] = g->tgt.a[3];
        g->f3078.x &= ~2ULL;
    } else {
        g->f3078.x |= 2;
    }
    vm->sp -= 8;
    return 2;
}

void func_001dcfd0(VM *vm) {
    VmMsg m;
    Ent *e;
    if ((s32)(vm->fl.x >> 14) & 1) {
        e = vm->obj;
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
        if (vm->f330 < 0.0f) vm->fl.x &= ~0x4000;
    }
    if ((s32)(vm->fl.x >> 15) & 1) {
        if (vm->obj) {
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
        if (vm->f330 < 0.0f) vm->fl.x &= ~0x8000;
    }
}

typedef struct { s32 x0; u8 pad4[0x10]; s32 f14; } Q10;
typedef struct { u8 pad0[0x10]; Q10 *q; u8 * f14; s32 f18; f32 f1c; f32 f20; f32 f24; } Task;
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
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
    d = func_001e9e58(&D_002E2790.x, &D_002E2780.x);
    func_00267530(v, &D_002E2790.x, &D_002E2780.x);
    v[0] = v[0] / d * o->f1c;
    v[1] = v[1] / d * o->f1c;
    v[2] = v[2] / d * o->f1c;
    func_00267518(v, &D_002E2780.x, v);
    func_001e9d00(r, &D_002E2790.x, &D_002E2780.x, 0.0f);
    t[0] = o->f20;
    t[1] = o->f24;
    t[2] = 0.0f;
    t[3] = 1.0f;
    func_001e9dc8(v, r, t);
    func_002675a8(o->q->x0, v);
    return 0;
}

extern void *D_0062A220; /* src/data/bss_0062.c: s32 D_0062A220 */
extern void *D_0062A224; /* src/data/bss_0062.c: s32 D_0062A224 */
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
    d = func_001e9e58(&D_002E2790.x, &D_002E2780.x);
    func_00267530(v, &D_002E2790.x, &D_002E2780.x);
    s = vm->stk[vm->sp - 2];
    v[0] = v[0] / d * s;
    v[1] = v[1] / d * s;
    v[2] = v[2] / d * s;
    func_00267518(v, &D_002E2780.x, v);
    func_001e9d00(r, &D_002E2790.x, &D_002E2780.x, 0.0f);
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
#include "data/pieces/D_003DAD3C.h"
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
char D_0062A228[0x100]; /* no ALIGNED: a known 8-byte alignment turns the strcpy below into ld/sd moves */
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
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
#include "data/data_003D.h"
#include "data/pieces/D_00389C90.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003DABD8.h"
#include "data/pieces/D_00490630.h"
