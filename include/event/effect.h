/* Event effects (src/event/effect*.c; docs/modules.md "Session 34"): the
 * "eveffect/<name>_<n>.dpp / .dpx" files a script loads, the effect
 * instances it starts (func_00176040 ..) and the per-frame tasks of
 * D_0062A630 (func_0011f090) that keep an instance on its entity. */
#ifndef KH1_EVENT_EFFECT_H
#define KH1_EVENT_EFFECT_H

#include "common.h"
#include "data/types/vm_rec.h"

/* An effect instance (D_0062A428[8]; what func_001760b0 / func_001760d0 /
 * func_001760f0 return for an id): pointers into its transform. */
typedef struct {
    f32 *f0;                /* 0x00: position */
    s32 *f4;                /* 0x04: rotation (65536 per turn) */
    f32 *f8;                /* 0x08: scale */
    f32 *fc;                /* 0x0c: colour */
    u8 *f10;                /* 0x10: set to 1 to stop it */
    s32 f14;                /* 0x14: flags (bit 1: finished) */
    u8 pad18[0x28 - 0x18];
    s32 *f28;               /* 0x28 */
    u8 pad2c[0x3c - 0x2c];
} EvFx;

/* A task of the list D_0062A630 (func_0011f090(list, kind, fn)); fn runs
 * every frame with it until it returns 4. */
typedef struct {
    u8 pad0[0x10];
    EvFx *f10;              /* 0x10: the instance (a model for kinds 7 / 8) */
    VmRec *f14;             /* 0x14: the VM whose entity it follows, or 0 */
    s32 f18;                /* 0x18: bone / instance index */
    f32 f1c;                /* 0x1c */
    f32 f20, f24;           /* 0x20 */
    s32 f28;                /* 0x28: effect id */
    s32 f2c;                /* 0x2c: what func_001dd5c0 does (0-16) */
    f32 f30;                /* 0x30: frames left (kind 15) */
    u8 pad34[0xc];
    f32 f40[3];             /* 0x40: colour step (kind 15) */
} EvTask;

extern u8 D_0062A630[];
extern void *D_0062A220;   /* the loaded .dpx file (src/data/bss_0062.c: s32) */
extern void *D_0062A224;   /* the .dpp file, 0x7d000 bytes after it (s32) */
extern EvFx D_0062A428[];  /* src/data/bss_0062.c: u8 D_0062A428[0x1e0], 8 of them */

EvTask *func_0011f090(void *list, s32 kind, void *fn);
EvFx *func_001760b0(s32);
EvFx *func_001760d0(s32);
EvFx *func_001760f0(s32);

s32 func_001dd208(EvTask *t);
s32 func_001dd320(EvTask *t);
s32 func_001dd3f8(EvTask *t);
s32 func_001dd488(EvTask *t);
s32 func_001dd550(EvTask *t);
s32 func_001dd5c0(EvTask *t);
void func_001ddbf8(void);

#endif /* KH1_EVENT_EFFECT_H */
