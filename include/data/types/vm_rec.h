/* The 0x350-byte script VM record (session 29: one type for the VM tables
 * D_0038D170, D_0039A580, D_003A7990, D_003B4DA0, D_003C3A70 and the locals of
 * the files that walk them).  Offsets are in the comments.
 *
 * `obj` points at the entity the VM drives; each file that reads through it
 * completes `struct VmObj` with its own view of that entity. */
#ifndef KH1_DATA_TYPES_VM_REC_H
#define KH1_DATA_TYPES_VM_REC_H

#include "common.h"

struct VmObj;

/* 0x328: state flags */
typedef union {
    u64 x;
    s32 i[2];
    struct {
        u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
        u32 b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
        u32 brest:16;
        u32 hi;
    } b;
} VmFl;

typedef struct {
    s32 x0;                 /* 0x000: id / handle */
    struct VmObj *obj;      /* 0x004: the entity this VM drives */
    u8 pad8[0xc];
    f32 f14, f18, f1c, f20; /* 0x014 */
    u8 pad24[0x8];
    f32 f2c[3];             /* 0x02c */
    f32 f38[3];             /* 0x038 */
    f32 f44;                /* 0x044 */
    s32 f48;                /* 0x048 */
    u8 pad4c[0x14];
    s32 f60;                /* 0x060 */
    f32 f64;                /* 0x064 */
    u8 pad68[0x8];
    s8 *code;               /* 0x070: script */
    s32 n;                  /* 0x074 */
    s32 x78;                /* 0x078 */
    s32 lbl[64];            /* 0x07c: labels */
    s32 pc;                 /* 0x17c */
    s32 sp;                 /* 0x180 */
    s32 stk[33];            /* 0x184: operand stack */
    s32 var[26];            /* 0x208: registers */
    s32 x270[32];           /* 0x270 */
    s32 x2f0;               /* 0x2f0 */
    f32 x2f4;               /* 0x2f4: wait timer */
    s32 ret[8];             /* 0x2f8: return stack */
    s32 rsp;                /* 0x318 */
    s32 x31c, x320, x324;   /* 0x31c */
    VmFl fl;                /* 0x328 */
    u8 pad330[0x20];
} VmRec;

#endif /* KH1_DATA_TYPES_VM_REC_H */
