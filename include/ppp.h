/* ppp: the particle/effect program system (session 5).
 *
 * An effect program is a list of components. Each component names a class
 * from the class table D_00370200 (236 records of 0x28 bytes, indexed by
 * class id; record 0 is empty). The record's first word points to the
 * class name ("pppMove", "pppDrawMdl", "pppKeThRes16x4"...), the rest are
 * callbacks or 0. Programs come from data loaded at run time:
 * func_00182d58 relocates one, turning each component's class id into
 * `&D_00370200[id]` and its data-relative words into pointers.
 *
 * Who calls which slot (docs/structs.md):
 *   frame  (+0x04)  pppFrame step, func_001830a0, every frame;
 *                   fn(obj, data, entry)
 *   draw   (+0x0C)  set by the drawing classes (pppDrawMdl*, pppKeLns*...);
 *                   fn(obj, data, entry)
 *   con    (+0x1C)  func_001824e8, when the program's object is created;
 *                   fn(obj, entry)
 *   reset  (+0x20)  func_00182448, when the program restarts (timer back
 *                   to 0); often the same function as con; fn(obj, entry)
 *   des    (+0x24)  func_001826a8, before the object is freed; fn(obj, entry)
 *   +0x08 and +0x10 are never set; +0x14 (returns a float) is set by 3
 *   classes and +0x18 by one.
 *
 * Session 4 called the per-component entry "CompClass"; it is PppEntry. */
#ifndef KH1_PPP_H
#define KH1_PPP_H

#include "common.h"

struct PppEntry;

typedef struct PppClass {
    char *name;   /* +0x00 */
    void *frame;  /* +0x04 */
    void *fn08;   /* +0x08: never set */
    void *draw;   /* +0x0C */
    void *fn10;   /* +0x10: never set */
    void *fn14;   /* +0x14: returns a float (3 classes) */
    void *fn18;   /* +0x18: pppKeAcmSolid only */
    void *con;    /* +0x1C */
    void *reset;  /* +0x20 */
    void *des;    /* +0x24 */
} PppClass; /* 0x28 bytes */

/* One component of a loaded program (entries of 0x10 bytes from +0x28 of
 * the program header; +0x26 holds their count, +0x20 the offset in the
 * object of the per-component data pointers). */
typedef struct PppEntry {
    PppClass *cls; /* +0x0 */
    s32 stride;    /* +0x4: added to the data pointer when the object's
                    * timer reaches the next keyframe */
    void *data;    /* +0x8: first keyframe; copied into the object on reset */
    s32 *offsets;  /* +0xC: offsets[0] is the byte offset of this
                    * component's work area in the object */
} PppEntry;

/* layout checks */
typedef char PppClass_check_size[(sizeof(struct PppClass) == 0x28) ? 1 : -1];
typedef char PppEntry_check_size[(sizeof(struct PppEntry) == 0x10) ? 1 : -1];

#endif /* KH1_PPP_H */
