/* The entity a library VM drives (VmRec.obj), as src/vm/vm_lib*.c read it
 * (docs/modules.md "Session 32").  Other files complete struct VmObj with
 * their own view; the library's files share this one. */
#ifndef KH1_VM_VM_OBJ_H
#define KH1_VM_VM_OBJ_H

#include "common.h"
#include "data/types/vm_rec.h"

struct VmObj130 {
    u8 pad0[0x18];
    f32 f18;                /* 0x18: read / set by func_001d3be8 / func_001d3bb0 */
};

struct VmObj6c {
    u8 pad0[0x3c];
    s32 f3c;                /* read by func_001d43d8 */
    u8 pad40[4];
    s32 f44;                /* read by func_001d4448 */
};

struct VmObj14c {
    u8 pad0[0x14];
    s32 f14;
};

struct VmObj {
    s32 x0;                 /* flags (bit 25: func_001d5308 / func_001d5330) */
    s32 x4;                 /* 0x4: its id */
    s32 f8;                 /* 0x8: compared with the VMs' f60 (func_001dcb00) */
    u8 padc[4];
    f32 pos[3];             /* 0x10 */
    u8 pad1c[4];
    f32 dir[4];             /* 0x20: direction (func_001dcb00) */
    f32 rot[3];             /* 0x30: radians */
    f32 f3c;                /* 0x3c: heading (radians) */
    u8 pad40[0x10];
    f32 p50[3];             /* 0x50: home position (func_001d3aa8 sends the entity there) */
    u8 pad5c[0x68 - 0x5c];
    void *f68;              /* 0x68: a model (src/event/: kinds 7 / 8) */
    struct VmObj6c *f6c;    /* 0x6c */
    s32 f70;                /* 0x70: pushed by func_001d9850 */
    u8 pad74[0x90 - 0x74];
    u64 f90;                /* 0x90: func_001dcb00 */
    u8 pad98[0xac - 0x98];
    f32 fac;                /* 0xac: sent by func_001da2c8 */
    u8 padb0[0x130 - 0xb0];
    struct VmObj130 *f130;  /* 0x130 */
    u8 pad134[0x14c - 0x134];
    struct VmObj14c *f14c;  /* 0x14c: f14 is a model (func_001dd5c0) */
    f32 f150;               /* 0x150: heading func_001dcb00 sets */
    u8 pad154[0x15c - 0x154];
    s32 f15c;               /* 0x15c: its skeleton (func_001dd3f8) */
    u8 pad160[0x164 - 0x160];
    s32 f164;               /* 0x164: pushed by func_001d5350 / func_001d5388 */
    u8 pad168[0x16c - 0x168];
    f32 f16c;               /* 0x16c: pushed halved by func_001d4358 / func_001d4690 */
    u8 pad170[0x370 - 0x170];
    union {
        u64 flags;
        u8 col[4];          /* func_001cf210 */
        struct { u32 lo; u32 p:12; u32 b44:1; u32 hi:19; } b;  /* h44's func_001d95f0 */
        struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } k;  /* bits 37-38: func_001dc3c0 */
    } f370;                 /* 0x370 */
};

#endif /* KH1_VM_VM_OBJ_H */
