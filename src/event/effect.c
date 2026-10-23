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
