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

struct VmObj {
    s32 x0;
    s32 x4;                 /* 0x4: its id */
    u8 pad8[0x8];
    f32 pos[3];             /* 0x10 */
    u8 pad1c[0x14];
    f32 rot[3];             /* 0x30: radians */
    f32 f3c;                /* 0x3c: heading (radians) */
    u8 pad40[0x10];
    f32 p50[3];             /* 0x50: home position (func_001d3aa8 sends the entity there) */
    u8 pad5c[0x130 - 0x5c];
    struct VmObj130 *f130;  /* 0x130 */
    u8 pad134[0x370 - 0x134];
    union {
        u64 flags;
        u8 col[4];          /* func_001cf210 */
    } f370;                 /* 0x370 */
};

#endif /* KH1_VM_VM_OBJ_H */
