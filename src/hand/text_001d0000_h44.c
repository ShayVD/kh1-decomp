#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"
typedef struct VmObj {
    u8 pad0[0x30];
    f32 v30[4];
    u8 pad40[0x68 - 0x40];
    void *f68;
    u8 pad6c[0xac - 0x6c];
    f32 fac;
    u8 padb0[0x370 - 0xb0];
    union { u64 x; struct { u32 lo; u32 p:12; u32 b44:1; u32 hi:19; } b; } f370;
} Obj;
typedef VmRec VM;

typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    u8 pad3038[0x3070 - 0x3038];
    union { u64 x; struct { u64 b0:50; u64 b50:1; u64 b51:1; u64 b52:1; u64 r:11; } b; } x3070;
    union { u64 x; struct { u64 b0:3; u64 b3:1; u64 r:60; } b; } x3078;
    u8 pad3080[0x3150 - 0x3080];
    s32 x3150;
    VM *x3154;
} G389C90;
extern G389C90 D_00389C90;
typedef struct { u8 pad0[0x370]; u8 c[3]; } HObj4;
typedef struct { f32 *f0; s32 *f4; f32 *f8; f32 *fc; u8 pad10[4]; s32 f14; } HObj;
typedef struct { u8 pad0[4]; HObj4 *f4; } HSub;
typedef struct { u8 pad0[0x10]; HObj *f10; HSub *f14; s32 f18; f32 f1c; u8 pad20[8]; s32 f28; s32 f2c; f32 f30; u8 pad34[0xc]; f32 f40[3]; } Handler;
extern f32 D_002BBDFC;
extern u8 D_0062A630[];
s32 func_001dd5c0(Handler *);
Handler *func_0011f090(void *, s32, s32 (*)(Handler *));
HSub *func_001e98d0(s32, s32);
HObj *func_001760d0(s32);
void func_001315c0(HObj4 *, s32, f32 *, f32);
HObj *func_001760f0(s32);
void func_002675a8(f32 *, f32 *);
void func_00131a30(HObj4 *, s32, f32 *);
s32 func_001dd320(Handler *h);
s32 func_001dd208(Handler *h);
HObj *func_001760b0(s32);
extern u64 D_0038CD00;
extern s32 D_003DC470;
extern s32 D_003DC474;
extern s32 D_003DC478;
extern s32 D_003DC47C;
extern s32 D_003DC494;
extern u8 D_003DC468[];
extern u8 D_0062F760[];
extern u8 D_0062FA00[];
extern u8 D_0062F6E0[];
extern s32 D_0062FF00[];
extern s32 D_0062FB00[];
void func_0010e3f0(void *);
void func_001ea128(void *, void *);
void func_001ea268(void *, s32);
void func_0010ef70(void *, void *, void (*)());
void func_001e2810(void);


void func_00105c70(s32, s32 *);
s32 func_001da2c8(VM *vm) {
    VmMsg m;
    s32 buf[3];
    func_00105c70(vm->stk[vm->sp - 1], buf);
    m.type = 23;
    m.v[0] = buf[0] * 0.0078125f;
    m.val = (u32)vm->stk[vm->sp];
    m.v[1] = buf[1] * 0.0078125f;
    m.v[2] = buf[2] * 0.0078125f;
    m.x = vm->x0;
    m.v[3] = vm->obj->fac;
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}

s32 func_00142388(f32 *, f32 *);
void func_00142470(Obj *, f32 *);
s32 func_001da628(VM *vm) {
    f32 v[4];
    f32 r[4];
    Obj *o;
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, r);
    o = vm->obj;
    if (o) {
        func_00142470(o, r);
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001dc000(VM *vm) {
    VmMsg m;
    m.type = 44;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 4] / 255.0f;
    m.v[1] = vm->stk[vm->sp - 3] / 255.0f;
    m.v[2] = vm->stk[vm->sp - 2] / 255.0f;
    m.v[3] = vm->stk[vm->sp - 1] * 0.0078125f;
    func_001c4640(&m);
    vm->sp -= 5;
    return 2;
}

typedef struct { u8 pad0[4]; s32 f4; u8 pad8[0x370 - 8]; union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } f370; } Obj3;
Obj3 *func_001230a0(Obj3 *);
s32 func_001dc3c0(void) {
    VmMsg m;
    Obj3 *o;
    m.type = 27;
    m.val = 0;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.v[3] = 1.0f;
    for (o = func_001230a0(0); o; o = func_001230a0(o)) {
        if (o->f370.b.kind == 2) {
            m.x = o->f4;
            func_001c4640(&m);
        }
    }
    return 2;
}

s32 func_001dc470(void) {
    VmMsg m;
    Obj3 *o;
    m.type = 28;
    m.val = 0;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.v[3] = 1.0f;
    for (o = func_001230a0(0); o; o = func_001230a0(o)) {
        if (o->f370.b.kind == 2) {
            m.x = o->f4;
            func_001c4640(&m);
        }
    }
    return 2;
}

#include "data/pieces/D_0037A178.h"
s32 func_001dc8c8(VM *vm) {
    s32 id = vm->stk[vm->sp - 1];
    s32 v, q, b;
    u32 *p;
    if (id < 0 || id >= 128) {
        vm->sp -= 2;
        return 2;
    }
    v = vm->stk[vm->sp];
    if (v < 0 || v >= 2) {
        vm->sp -= 2;
        return 2;
    }
    q = id / 32;
    b = 31 - (id - q * 32);
    if (v) {
        D_0037A178[q] |= 1 << b;
    } else {
        D_0037A178[q] &= ~(1 << b);
    }
    vm->sp -= 2;
    return 2;
}

#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
extern s32 D_0039A570;
extern s32 D_003A7980;
#include "data/pieces/D_0037A378.h"
void func_001dcd98(s32 a) {
    VM *vm;
    s32 n, i;
    D_00389C90.x3150 = a;
    if (D_00389C90.x3034 == 0) {
        vm = D_0038D170;
        n = D_0039A570;
    } else {
        n = D_003A7980;
        vm = D_0039A580;
    }
    for (i = 0; i < n; i++) {
        if (&vm[i] == D_00389C90.x3154) break;
    }
    if (a > 0) D_0037A378 &= ~8;
    vm->stk[++vm->sp] = 3;
    vm->stk[++vm->sp] = i;
    func_001c19f8(vm, 8);
}

void func_001d1080(VM *);
void func_001d3e30(VM *);
void func_001d7898(VM *);
void func_001d9510(VM *);
void func_001d9348(VM *);
void func_001dcea8(VM *vm) {
    s32 n, i;
    n = D_002BBDFC * 0.5f;
    if (n == 0) n = 1;
    for (i = 0; i < n; i++) {
        if ((s32)(vm->fl.x >> 6) & 1) func_001d1080(vm);
        if ((s32)(vm->fl.x >> 9) & 1) func_001d3e30(vm);
        if ((s32)(vm->fl.x >> 10) & 1) func_001d7898(vm);
        if ((s32)(vm->fl.x >> 12) & 1) func_001d9510(vm);
    }
    if ((s32)(vm->fl.x >> 11) & 1) func_001d9348(vm);
}

s32 func_001dd208(Handler *h) {
    f32 buf[4];
    f32 *p;
    HObj *ho;
    HObj4 *o;
    if ((s32)(D_00389C90.x3070.x >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_001315c0(h->f14->f4, h->f18, buf, h->f1c);
    h->f10->f0[0] = buf[0];
    h->f10->f0[1] = buf[1];
    h->f10->f0[2] = buf[2];
    if (h->f18 == 4236 || h->f18 == 4247) {
        if (!((s32)(D_00389C90.x3078.x >> 3) & 1)) {
            h->f10->fc[0] = h->f14->f4->c[0] * 0.0078125f;
            h->f10->fc[1] = h->f14->f4->c[1] * 0.0078125f;
            h->f10->fc[2] = h->f14->f4->c[2] * 0.0078125f;
        }
    }
    return 0;
}

s32 func_001dd320(Handler *h) {
    f32 buf[4];
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_00131a30(h->f14->f4, h->f18, buf);
    h->f10->f4[0] = buf[0] * 32768.0f / 3.1415928f;
    h->f10->f4[1] = buf[1] * 32768.0f / 3.1415928f;
    h->f10->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    return 0;
}

s32 func_001dd488(Handler *h) {
    f32 *c;
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    h->f30 -= D_002BBDFC;
    if (h->f30 < 0.0f) return 4;
    c = h->f10->fc;
    c[0] += h->f40[0];
    c[1] += h->f40[1];
    c[2] += h->f40[2];
    if (h->f10->fc[0] < 0.0f) h->f10->fc[0] = 0.0f;
    if (h->f10->fc[1] < 0.0f) h->f10->fc[1] = 0.0f;
    if (h->f10->fc[2] < 0.0f) h->f10->fc[2] = 0.0f;
    return 0;
}

s32 func_001de130(VM *vm) {
    Handler *h;
    HSub *r;
    h = func_0011f090(D_0062A630, 0, func_001dd5c0);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    h->f2c = 10;
    h->f14 = r->f4 ? r : 0;
    h->f28 = vm->stk[vm->sp - 1];
    vm->sp -= 2;
    return 2;
}

s32 func_001de1e0(VM *vm) {
    Handler *h;
    HSub *r;
    h = func_0011f090(D_0062A630, 0, func_001dd5c0);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    h->f2c = 16;
    h->f14 = r->f4 ? r : 0;
    h->f28 = vm->stk[vm->sp - 1];
    vm->sp -= 2;
    return 2;
}

s32 func_001de420(VM *vm) {
    HObj *p = func_001760d0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001de5b0(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760d0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd208);
        h->f10 = o;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp - 1];
        h->f1c = vm->stk[vm->sp] * 0.5f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001de6a8(VM *vm) {
    f32 buf[4];
    HObj *o;
    HSub *r;
    o = func_001760d0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        func_001315c0(r->f4, vm->stk[vm->sp - 1], buf, vm->stk[vm->sp] * 0.5f);
        func_002675a8(o->f0, buf);
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001de778(VM *vm) {
    f32 buf[4];
    HObj *o;
    HSub *r;
    o = func_001760f0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        func_001315c0(r->f4, vm->stk[vm->sp - 1], buf, vm->stk[vm->sp] * 0.5f);
        func_002675a8(o->f0, buf);
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001dd3f8(Handler *h);
s32 func_001de848(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760f0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd3f8);
        h->f10 = o;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp];
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001de910(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760d0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd320);
        h->f10 = o;
        h->f14 = r;
        h->f1c = 0;
        h->f18 = vm->stk[vm->sp];
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001de9e0(VM *vm) {
    f32 buf[4];
    HObj *o;
    HSub *r;
    o = func_001760d0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        func_00131a30(r->f4, vm->stk[vm->sp], buf);
        o->f4[0] = buf[0] * 32768.0f / 3.1415928f;
        o->f4[1] = buf[1] * 32768.0f / 3.1415928f;
        o->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001deaf8(VM *vm) {
    f32 buf[4];
    HObj *o;
    HSub *r;
    o = func_001760f0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        func_00131a30(r->f4, vm->stk[vm->sp], buf);
        o->f4[0] = buf[0] * 32768.0f / 3.1415928f;
        o->f4[1] = buf[1] * 32768.0f / 3.1415928f;
        o->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001dec10(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760f0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd208);
        h->f10 = o;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp - 1];
        h->f1c = vm->stk[vm->sp] * 0.5f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001ded08(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760f0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd320);
        h->f10 = o;
        h->f14 = r;
        h->f1c = 0;
        h->f18 = vm->stk[vm->sp];
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001df4a0(VM *vm) {
    HObj *p = func_001760f0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

extern u8 D_0062A428[];
s32 func_001df698(Handler *h);
s32 func_001df708(VM *vm) {
    HSub *r;
    Handler *h;
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (r) {
        h = func_0011f090(D_0062A630, 1, func_001df698);
        h->f10 = (HObj *)D_0062A428;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp - 1];
        h->f1c = vm->stk[vm->sp] * 0.5f;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001dfcb0(VM *vm) {
    HObj *p = func_001760b0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001dfea8(VM *vm) {
    HObj *o;
    HSub *r;
    Handler *h;
    o = func_001760b0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        h = func_0011f090(D_0062A630, 1, func_001dd208);
        h->f10 = o;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp - 1];
        h->f1c = vm->stk[vm->sp] * 0.5f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001e0078(VM *vm) {
    Handler *h;
    f32 t;
    h = func_0011f090(D_0062A630, 0, func_001dd5c0);
    h->f2c = 15;
    h->f28 = vm->stk[vm->sp - 4];
    t = vm->stk[vm->sp];
    h->f30 = t * 2;
    h->f40[0] = (vm->stk[vm->sp - 3] - 255.0f) / 255.0f / t;
    h->f40[1] = (vm->stk[vm->sp - 2] - 255.0f) / 255.0f / t;
    h->f40[2] = (vm->stk[vm->sp - 1] - 255.0f) / 255.0f / t;
    h->f10 = func_001760f0(h->f28);
    D_00389C90.x3078.b.b3 = 1;
    vm->sp -= 5;
    return 2;
}

#include "data/types/text_001d0000_h44.h"
extern Col4 D_003DACC0;
extern s32 D_003DACD0;
extern u64 D_003DB028;
extern u8 D_00F20000[];
extern u8 D_003DB050[];
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);
s32 func_001e15a0(void) {
    s32 i, j;
    u8 *p;
    D_003DACC0.d += D_003DACD0;
    if (D_003DACC0.d > 128) {
        D_003DACC0.d = 128;
    } else if (D_003DACC0.d < 0) {
        return 4;
    }
    {
        u64 r = (s64)D_003DACC0.a | 0x100000000LL;
        r |= (s64)D_003DACC0.c << 16 | (s64)D_003DACC0.b << 8;
        r |= (s64)D_003DACC0.d << 24;
        D_003DB028 = r;
    }
    func_001e1480();
    p = D_00F20000;
    for (i = 0; i < 384; i++) {
        for (j = 0; j < 512; j++) {
            p[2] = p[0] = p[1];
            p += 3;
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}

void func_001e2810(void) {
    s32 n = D_003DC470;
    if (n != D_003DC474 && n != 0) {
        {
            D_003DC474 = n;
            if (D_003DC478 == 0) {
                func_0010e3f0(D_0062F760);
                func_001ea128(D_0062FA00, D_003DC468);
                if (D_003DC494) {
                    func_001ea268(D_0062FA00, D_0062FF00[D_003DC470]);
                } else {
                    func_001ea268(D_0062FA00, D_0062FB00[D_003DC470]);
                }
                func_0010ef70(D_0062F6E0, D_0062FA00, func_001e2810);
            } else {
                D_003DC47C = 0;
            }
        }
    }
}

extern s32 D_003F7A68;
s32 func_001e2920(void) {
    if (D_003DC478 == 0) return 4;
    if (--D_003DC47C < 0) {
        D_003DC478 = 0;
        if (D_003F7A68 == 1 && D_003DC470 != 0) {
            func_0010e3f0(D_0062F760);
            func_001ea128(D_0062FA00, D_003DC468);
            if (D_003DC494) {
                func_001ea268(D_0062FA00, D_0062FF00[D_003DC470]);
            } else {
                func_001ea268(D_0062FA00, D_0062FB00[D_003DC470]);
            }
            func_0010ef70(D_0062F6E0, D_0062FA00, func_001e2810);
        }
        return 4;
    }
    return 0;
}

/* needs make: uses rodata */
typedef struct { u8 pad0[2]; u8 f2; } P147840;
P147840 *func_00147840(s32);
s32 func_001daa18(VM *vm) {
    s32 r = -1;
    switch (func_00147840(vm->stk[vm->sp])->f2) {
    case 0: r = 0; break;
    case 12: r = 1; break;
    case 13: r = 2; break;
    case 2: r = 4; break;
    case 3: r = 5; break;
    case 4: r = 6; break;
    case 1: r = 3; break;
    }
    vm->stk[vm->sp] = r;
    return 2;
}

#include "data/types/text_001d0000_h44_p.h"
extern Tbl55 D_004906D0;
void func_001ba358(s32, s32);
s32 func_001dc140(void) {
    Tbl55 t = D_004906D0;
    u32 i;
    for (i = 0; i < 55; i++) {
        func_001ba358(t.a[i], 99);
    }
    return 2;
}

extern char D_003DACD8[][6];
extern u8 D_00F20000[];
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
int sprintf(char *, const char *, ...);
s32 func_00120748(void *, void *, void (*)(), s32);
void func_001e2498();
s32 func_001e24c8(VM *vm) {
    char buf[256];
    char tmp[16];
    strcpy(buf, "image/");
    strcat(buf, D_003DACD8[vm->stk[vm->sp - 1]]);
    sprintf(tmp, "_%03d.rgb", vm->stk[vm->sp]);
    strcat(buf, tmp);
    func_00120748(buf, D_00F20000, func_001e2498, 0);
    D_00389C90.x3070.b.b50 = 1;
    vm->sp -= 2;
    return 2;
}

#include "data/bss_0062_mixed.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DACC0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_004906D0.h"
