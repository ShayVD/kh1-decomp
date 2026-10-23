/* Event effects (docs/modules.md "Session 34"), 0x001dd148-0x001e01b8.
 *
 * The script functions after the library's dispatcher (src/vm/vm_lib.c)
 * that load "eveffect/<name>_<n>.dpp / .dpx" (func_001ddc78), start, move
 * and stop its effect instances, and keep an instance on a VM's entity
 * through the per-frame tasks of D_0062A630.  Their data is their own: the
 * bss D_0062A220-D_0062A640 (after vm_lib's D_0062A210) and the name table
 * D_003DABD8 (after vm_lib's D_003DABD4), and their D_003D9FE0 indices are
 * not part of the library's increasing run.  func_001dd5c0 (the task that
 * runs a request) is in effect.norlo.c, func_001ddbf8 in effect.nofill.c. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "event/effect.h"
#include "vm/vm_obj.h"
#include "vm/vm_mgr.h"
#include "vm/vm_find.h"
#include "data/bss_0062.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003DABD8.h"
#include "data/data_0029.h"

extern VmMgr D_00389C90;
extern u64 D_0038CD00;
extern char D_0062A328[];

/* The task list's records (80 of 256 bytes). */
u8 D_0062A640[0x5000] ALIGNED(64);

s32 func_0011f130(void *, s32);
void func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef10(s32, s32 (*)());
void *func_001559f0(s32, s32);
void func_00120748(char *, void *, void *, s32);
void func_001315c0(struct VmObj *, s32, f32 *, f32);
void func_00131a30(struct VmObj *, s32, f32 *);
void func_001318e8(struct VmObj *, s32, void *);
void func_00147e08(EvFx *, void *);
s32 func_00176040(void *, void *, s32, s32);

/* A 4x4 matrix (func_001623e0's bones); v is its translation. */
typedef struct { u8 pad0[0x30]; f32 v[3]; u8 pad3c[4]; } EvMat;
EvMat *func_001623e0(s32);

/* Run the task list (func_0011ef10's callback). */
s32 func_001dd148(void) {
    func_0011f130(&D_0062A630, 0);
    return 0;
}

/* Set up: the effect buffer, the task list in D_0062A640, and the frame
 * callback. */
s32 func_001dd170(void) {
    void **p = &D_0062A220;
    s32 r;
    *p = func_001559f0(50, 2);
    D_0062A224 = (u8 *)*p + 0x7d000;
    func_0011efa8(D_0062A630, D_0062A640, 80, 256);
    r = func_0011ef10(0xc34f, func_001dd148);
    D_0062A628 = 0;
    return r;
}

/* Use the given buffers (script_vm.c's func_001c4d90). */
void func_001dd1f0(s32 arg0, s32 arg1) {
    D_0062A220 = (void *)arg0;
    D_0062A224 = (void *)arg1;
}

/* Every frame: put the instance at bone f18 of the entity (and, for models
 * 4236 / 4247, give it the entity's colour). */
s32 func_001dd208(EvTask *h) {
    f32 buf[4];
    if ((s32)(D_00389C90.f3070.x >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_001315c0(h->f14->obj, h->f18, buf, h->f1c);
    h->f10->f0[0] = buf[0];
    h->f10->f0[1] = buf[1];
    h->f10->f0[2] = buf[2];
    if (h->f18 == 4236 || h->f18 == 4247) {
        if (!((s32)(D_00389C90.f3078.x >> 3) & 1)) {
            h->f10->fc[0] = h->f14->obj->f370.col[0] * 0.0078125f;
            h->f10->fc[1] = h->f14->obj->f370.col[1] * 0.0078125f;
            h->f10->fc[2] = h->f14->obj->f370.col[2] * 0.0078125f;
        }
    }
    return 0;
}

/* Every frame: give the instance the rotation of bone f18. */
s32 func_001dd320(EvTask *h) {
    f32 buf[4];
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_00131a30(h->f14->obj, h->f18, buf);
    h->f10->f4[0] = buf[0] * 32768.0f / 3.1415928f;
    h->f10->f4[1] = buf[1] * 32768.0f / 3.1415928f;
    h->f10->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    return 0;
}

/* Every frame: put the instance at the translation of matrix f18 of the
 * entity's f15c. */
s32 func_001dd3f8(EvTask *h) {
    EvMat *m;
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    m = func_001623e0(h->f14->obj->f15c);
    h->f10->f0[0] = m[h->f18].v[0];
    h->f10->f0[1] = m[h->f18].v[1];
    h->f10->f0[2] = m[h->f18].v[2];
    return 0;
}

/* Every frame for f30 frames: add the step f40 to the colour (not below 0). */
s32 func_001dd488(EvTask *h) {
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

/* Every frame: give the instance the whole transform of bone f18. */
s32 func_001dd550(EvTask *h) {
    u8 buf[64];
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_001318e8(h->f14->obj, h->f18, buf);
    func_00147e08(h->f10, buf);
    return 0;
}

/* func_001dd5c0 is in effect.norlo.c, func_001ddbf8 in effect.nofill.c. */

/* The .dpp is loaded: load the .dpx. */
void func_001ddc48(void) {
    func_00120748(D_0062A328, D_0062A220, func_001ddbf8, 0);
}

char *strcpy(char *, const char *);
char *strcat(char *, const char *);
int sprintf(char *, const char *, ...);
/* no ALIGNED: a known 8-byte alignment turns the strcpy below into ld/sd
 * moves (h67) */
char D_0062A228[0x100];

/* Load eveffect/<D_003DABD8[stk[sp-1]]>_<stk[sp]>.dpp (then .dpx) into a
 * 50-block buffer; bit 44 of f3070 stays set until it is loaded. */
s32 func_001ddc78(VmRec *vm) {
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
    D_00389C90.x3094 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

/* The same into a 60-block buffer. */
s32 func_001dde08(VmRec *vm) {
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
    D_00389C90.x3094 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

/* The script functions (D_003D9FE0 entries).  Each pops its arguments and
 * returns 2 (4: wait). */

/* Wait until the effect files are loaded (bit 44 of D_0038CD00). */
s32 func_001ddf98(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 44) & 1) return 4;
    return 2;
}

/* h20's view of a VM from +4 (obj, then the stack at +0x180): four
 * requests index the stack off vm + 4, as the original does. */
typedef struct { struct VmObj *obj; u8 pad4[0x17c]; s32 stk[33]; } EvVmSub;

/* Start effect stk[sp] (request 0), on this VM's entity if it has one. */
s32 func_001ddfb8(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    EvVmSub *s = (EvVmSub *)&vm->obj;
    s32 i;
    t->f2c = 0;
    i = vm->sp;
    t->f14 = s->obj ? vm : 0;
    t->f28 = s->stk[i];
    vm->sp -= 1;
    return 2;
}

/* The same with request 10 (start and follow the entity). */
s32 func_001de030(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    EvVmSub *s = (EvVmSub *)&vm->obj;
    s32 i;
    t->f2c = 10;
    i = vm->sp;
    t->f14 = s->obj ? vm : 0;
    t->f28 = s->stk[i];
    vm->sp -= 1;
    return 2;
}

/* The same with request 16 (the second kind, following the entity). */
s32 func_001de0b0(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    EvVmSub *s = (EvVmSub *)&vm->obj;
    s32 i;
    t->f2c = 16;
    i = vm->sp;
    t->f14 = s->obj ? vm : 0;
    t->f28 = s->stk[i];
    vm->sp -= 1;
    return 2;
}

/* Request 10 for effect stk[sp-1] on the entity of VM stk[sp]. */
s32 func_001de130(VmRec *vm) {
    EvTask *h;
    VmRec *r;
    h = func_0011f090(D_0062A630, 0, func_001dd5c0);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    h->f2c = 10;
    h->f14 = r->obj ? r : 0;
    h->f28 = vm->stk[vm->sp - 1];
    vm->sp -= 2;
    return 2;
}

/* Request 16 for effect stk[sp-1] on the entity of VM stk[sp]. */
s32 func_001de1e0(VmRec *vm) {
    EvTask *h;
    VmRec *r;
    h = func_0011f090(D_0062A630, 0, func_001dd5c0);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    h->f2c = 16;
    h->f14 = r->obj ? r : 0;
    h->f28 = vm->stk[vm->sp - 1];
    vm->sp -= 2;
    return 2;
}

/* Instance stk[sp-3] (first kind): position, rotation (degrees), scale
 * (percent), its f28, stop. */
s32 func_001de290(VmRec *vm) {
    EvFx *o = func_001760d0(vm->stk[vm->sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->f0;
        i = vm->sp;
        v[0] = vm->stk[i - 2];
        v[1] = vm->stk[i - 1];
        v[2] = vm->stk[i];
    } else {
        i = vm->sp;
    }
    vm->sp = i - 4;
    return 2;
}

s32 func_001de328(VmRec *vm) {
    EvFx *o = func_001760d0(vm->stk[vm->sp - 3]);
    if (o != 0) {
        s32 *r = o->f4;
        r[0] = (s32)(((f32)vm->stk[vm->sp - 2] / 360.0f) * 65535.0f);
        r[1] = (s32)(((f32)vm->stk[vm->sp - 1] / 360.0f) * 65535.0f);
        r[2] = (s32)(((f32)vm->stk[vm->sp] / 360.0f) * 65535.0f);
    }
    vm->sp = vm->sp - 4;
    return 2;
}

s32 func_001de420(VmRec *vm) {
    EvFx *p = func_001760d0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001de4e8(VmRec *vm) {
    EvFx *o = func_001760d0(vm->stk[vm->sp - 1]);
    if (o != 0) {
        *o->f28 = vm->stk[vm->sp];
    }
    vm->sp = vm->sp - 2;
    return 2;
}

s32 func_001de558(VmRec *vm) {
    EvFx *o = func_001760d0(vm->stk[vm->sp]);
    if (o != 0) {
        *o->f10 = 1;
    }
    vm->sp = vm->sp - 1;
    return 2;
}

/* Keep instance stk[sp-3] at bone stk[sp-1] of VM stk[sp-2]'s entity
 * (func_001dd208; stk[sp] / 2 is passed on). */
s32 func_001de5b0(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

void func_002675a8(f32 *, f32 *);

/* Put instance stk[sp-3] at bone stk[sp-1] of VM stk[sp-2]'s entity once. */
s32 func_001de6a8(VmRec *vm) {
    f32 buf[4];
    EvFx *o;
    VmRec *r;
    o = func_001760d0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        func_001315c0(r->obj, vm->stk[vm->sp - 1], buf, vm->stk[vm->sp] * 0.5f);
        func_002675a8(o->f0, buf);
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001de778(VmRec *vm) {
    f32 buf[4];
    EvFx *o;
    VmRec *r;
    o = func_001760f0(vm->stk[vm->sp - 3]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (o && r) {
        func_001315c0(r->obj, vm->stk[vm->sp - 1], buf, vm->stk[vm->sp] * 0.5f);
        func_002675a8(o->f0, buf);
    }
    vm->sp -= 4;
    return 2;
}

/* Keep instance stk[sp-2] at matrix stk[sp] of VM stk[sp-1]'s entity
 * (func_001dd3f8). */
s32 func_001de848(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

/* Keep the rotation of instance stk[sp-2] that of bone stk[sp] of VM
 * stk[sp-1]'s entity (func_001dd320). */
s32 func_001de910(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

s32 func_001de9e0(VmRec *vm) {
    f32 buf[4];
    EvFx *o;
    VmRec *r;
    o = func_001760d0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        func_00131a30(r->obj, vm->stk[vm->sp], buf);
        o->f4[0] = buf[0] * 32768.0f / 3.1415928f;
        o->f4[1] = buf[1] * 32768.0f / 3.1415928f;
        o->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001deaf8(VmRec *vm) {
    f32 buf[4];
    EvFx *o;
    VmRec *r;
    o = func_001760f0(vm->stk[vm->sp - 2]);
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (o && r) {
        func_00131a30(r->obj, vm->stk[vm->sp], buf);
        o->f4[0] = buf[0] * 32768.0f / 3.1415928f;
        o->f4[1] = buf[1] * 32768.0f / 3.1415928f;
        o->f4[2] = buf[2] * 32768.0f / 3.1415928f;
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001dec10(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

s32 func_001ded08(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
f32 func_001e9e58(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_001e9d00(f32 *, f32 *, f32 *, f32);
void func_001e9dc8(f32 *, f32 *, f32 *);

/* Every frame: keep the instance f1c along the view direction (D_002E2780
 * -> D_002E2790), offset by (f20, f24) on the screen. */
s32 func_001dedd8(EvTask *o) {
    f32 v[4];
    f32 r[4];
    f32 t[4];
    f32 d;
    if (o->f10->f14 & 2) return 4;
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
    func_002675a8(o->f10->f0, v);
    return 0;
}

/* Start effect stk[sp-3] in front of the camera (distance stk[sp-2],
 * screen offset stk[sp-1], stk[sp]) and keep it there (func_001dedd8). */
s32 func_001def20(VmRec *vm) {
    f32 v[4];
    f32 r[4];
    f32 t[4];
    f32 d, s;
    EvFx *k;
    EvTask *n;
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
        func_002675a8(k->f0, v);
        n = func_0011f090(D_0062A630, 0, func_001dedd8);
        n->f18 = 0;
        n->f10 = k;
        n->f14 = 0;
        n->f1c = vm->stk[vm->sp - 2];
        n->f20 = vm->stk[vm->sp - 1];
        n->f24 = vm->stk[vm->sp];
    }
    vm->sp -= 4;
    return 2;
}

/* Requests without arguments or with the effect id stk[sp]. */
s32 func_001df130(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 1;
    t->f28 = 0;
    return 2;
}

s32 func_001df170(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 2;
    t->f28 = vm->stk[vm->sp];
    vm->sp -= 1;
    return 2;
}

/* Request 3 (second kind) when its buffers D_0029B418 / D_0029B41C are set. */
s32 func_001df1d8(VmRec *vm) {
    if (D_0029B418 && D_0029B41C) {
        EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
        EvVmSub *s;
        s32 i;
        t->f2c = 3;
        s = (EvVmSub *)&vm->obj;
        i = vm->sp;
        t->f14 = s->obj ? vm : 0;
        t->f28 = s->stk[i];
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001df268(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 4;
    t->f28 = 0;
    return 2;
}

s32 func_001df2a8(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 5;
    t->f28 = vm->stk[vm->sp];
    vm->sp = vm->sp - 1;
    return 2;
}

/* Instance stk[sp-3] (second kind): position, rotation, scale, f28, stop. */
s32 func_001df310(VmRec *vm) {
    EvFx *o = func_001760f0(vm->stk[vm->sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->f0;
        i = vm->sp;
        v[0] = vm->stk[i - 2];
        v[1] = vm->stk[i - 1];
        v[2] = vm->stk[i];
    } else {
        i = vm->sp;
    }
    vm->sp = i - 4;
    return 2;
}

s32 func_001df3a8(VmRec *vm) {
    EvFx *o = func_001760f0(vm->stk[vm->sp - 3]);
    if (o != 0) {
        s32 *r = o->f4;
        r[0] = (s32)(((f32)vm->stk[vm->sp - 2] / 360.0f) * 65535.0f);
        r[1] = (s32)(((f32)vm->stk[vm->sp - 1] / 360.0f) * 65535.0f);
        r[2] = (s32)(((f32)vm->stk[vm->sp] / 360.0f) * 65535.0f);
    }
    vm->sp = vm->sp - 4;
    return 2;
}

s32 func_001df4a0(VmRec *vm) {
    EvFx *p = func_001760f0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001df568(VmRec *vm) {
    EvFx *o = func_001760f0(vm->stk[vm->sp - 1]);
    if (o != 0) {
        *o->f28 = vm->stk[vm->sp];
    }
    vm->sp = vm->sp - 2;
    return 2;
}

s32 func_001df5d8(VmRec *vm) {
    EvFx *o = func_001760f0(vm->stk[vm->sp]);
    if (o != 0) {
        *o->f10 = 1;
    }
    vm->sp = vm->sp - 1;
    return 2;
}

/* Request 6: start model effect stk[sp] in D_0062A428[0]. */
s32 func_001df630(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 6;
    t->f28 = vm->stk[vm->sp];
    vm->sp = vm->sp - 1;
    return 2;
}

typedef struct { f32 x, y, z; } EvVec3;

/* Every frame: put the instance at bone f18 of the entity (h20's Vec3
 * locals: f32 buf[4] would change the frame). */
s32 func_001df698(EvTask *c) {
    EvVec3 v;
    EvVec3 *p;
    if (c->f10->f14 & 2) return 4;
    func_001315c0(c->f14->obj, c->f18, (f32 *)&v, c->f1c);
    p = (EvVec3 *)c->f10->f0;
    p->x = v.x;
    p->y = v.y;
    p->z = v.z;
    return 0;
}

/* Keep D_0062A428[0] at bone stk[sp-1] of VM stk[sp-2]'s entity. */
s32 func_001df708(VmRec *vm) {
    VmRec *r;
    EvTask *h;
    r = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 2]);
    if (r) {
        h = func_0011f090(D_0062A630, 1, func_001df698);
        h->f10 = D_0062A428;
        h->f14 = r;
        h->f18 = vm->stk[vm->sp - 1];
        h->f1c = vm->stk[vm->sp] * 0.5f;
    }
    vm->sp -= 3;
    return 2;
}

/* Requests 7 / 8: model effect stk[sp] on the entity's model f68, in the
 * next of the eight slots D_0062A608 / D_0062A428. */
s32 func_001df7e0(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    s32 n, v; void *o;
    t->f2c = 7;
    n = D_0062A628;
    v = vm->stk[vm->sp];
    o = vm->obj->f68;
    t->f28 = v; t->f10 = o; t->f14 = vm; t->f18 = n; D_0062A608[n] = v;
    D_0062A628 = n + 1;
    if (D_0062A628 >= 8) D_0062A628 = 0;
    vm->sp--;
    return 2;
}

s32 func_001df890(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    s32 n, v; void *o;
    t->f2c = 8;
    n = D_0062A628;
    v = vm->stk[vm->sp];
    o = vm->obj->f68;
    t->f28 = v; t->f10 = o; t->f14 = vm; t->f18 = n; D_0062A608[n] = v;
    D_0062A628 = n + 1;
    if (D_0062A628 >= 8) D_0062A628 = 0;
    vm->sp--;
    return 2;
}

/* D_0062A428[0].f8 (its scale), as h20 named it. */
f32 *D_0062A430 ALIGNED(16);

/* Scale D_0062A428[0] to stk[sp-2..sp] percent. */
s32 func_001df940(VmRec *vm) {
    s32 i = vm->sp; f32 *p = D_0062A430; f32 x = vm->stk[i - 2], y = vm->stk[i - 1], z = vm->stk[i]; vm->sp = i - 4; p[0] = x / 100.0f; p[1] = y / 100.0f; p[2] = z / 100.0f;
    return 2;
}

/* Put D_0062A428[0] at the entity's position plus stk[sp-2..sp]. */
s32 func_001df9c0(VmRec *vm) {
    struct VmObj *o = vm->obj;
    s32 i = vm->sp;
    EvVec3 *p;
    struct VmObj *o2;
    f32 x, y, z, ox;

    x = vm->stk[i - 2];
    o2 = vm->obj;
    y = vm->stk[i - 1];
    p = (EvVec3 *)D_0062A428[0].f0;
    ox = o->pos[0];
    z = vm->stk[i];
    vm->sp = i - 4;
    p->x = ox + x;
    p->y = o2->pos[1] + y;
    p->z = o2->pos[2] + z;
    return 2;
}

s32 func_001dfa38(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 9;
    t->f28 = vm->stk[vm->sp];
    vm->sp = vm->sp - 1;
    return 2;
}

/* Request 11 (third kind) when its buffers D_0029B410 / D_0029B414 are set. */
s32 func_001dfaa0(VmRec *vm) {
    EvTask *t;
    if ((D_0029B410 != 0) && (D_0029B414 != 0)) {
        t = func_0011f090(D_0062A630, 0, func_001dd5c0);
        t->f2c = 0xB;
        t->f28 = vm->stk[vm->sp];
    }
    vm->sp = vm->sp - 1;
    return 2;
}

/* Instance stk[sp-3] (third kind): position, rotation, scale. */
s32 func_001dfb20(VmRec *vm) {
    EvFx *o = func_001760b0(vm->stk[vm->sp - 3]);
    s32 i;
    if (o) {
        f32 *v = o->f0;
        i = vm->sp;
        v[0] = vm->stk[i - 2];
        v[1] = vm->stk[i - 1];
        v[2] = vm->stk[i];
    } else {
        i = vm->sp;
    }
    vm->sp = i - 4;
    return 2;
}

s32 func_001dfbb8(VmRec *vm) {
    EvFx *o = func_001760b0(vm->stk[vm->sp - 3]);
    if (o != 0) {
        s32 *r = o->f4;
        r[0] = (s32)(((f32)vm->stk[vm->sp - 2] / 360.0f) * 65535.0f);
        r[1] = (s32)(((f32)vm->stk[vm->sp - 1] / 360.0f) * 65535.0f);
        r[2] = (s32)(((f32)vm->stk[vm->sp] / 360.0f) * 65535.0f);
    }
    vm->sp = vm->sp - 4;
    return 2;
}

s32 func_001dfcb0(VmRec *vm) {
    EvFx *p = func_001760b0(vm->stk[vm->sp - 3]);
    if (p) {
        p->f8[0] = vm->stk[vm->sp - 2] / 100.0f;
        p->f8[1] = vm->stk[vm->sp - 1] / 100.0f;
        p->f8[2] = vm->stk[vm->sp] / 100.0f;
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001dfd78(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 0xC;
    t->f28 = vm->stk[vm->sp];
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001dfde0(VmRec *vm) {
    EvFx *o = func_001760b0(vm->stk[vm->sp - 1]);
    if (o != 0) {
        *o->f28 = vm->stk[vm->sp];
    }
    vm->sp = vm->sp - 2;
    return 2;
}

s32 func_001dfe50(VmRec *vm) {
    EvFx *o = func_001760b0(vm->stk[vm->sp]);
    if (o != 0) {
        *o->f10 = 1;
    }
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001dfea8(VmRec *vm) {
    EvFx *o;
    VmRec *r;
    EvTask *h;
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

/* Request 13: model effect stk[sp] on this VM's entity. */
s32 func_001dffa0(VmRec *vm) {
    EvTask *t;
    if (vm->obj != 0) {
        t = func_0011f090(D_0062A630, 0, func_001dd5c0);
        t->f2c = 0xD;
        t->f14 = vm;
        t->f28 = vm->stk[vm->sp];
    }
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001e0010(VmRec *vm) {
    EvTask *t = func_0011f090(D_0062A630, 0, func_001dd5c0);
    t->f2c = 0xE;
    t->f28 = vm->stk[vm->sp];
    vm->sp = vm->sp - 1;
    return 2;
}

/* Request 15: fade the colour of instance stk[sp-4] (second kind) towards
 * stk[sp-3..sp-1] / 255 over stk[sp] frames. */
s32 func_001e0078(VmRec *vm) {
    EvTask *h;
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
    D_00389C90.f3078.w.b3 = 1;
    vm->sp -= 5;
    return 2;
}
