/* D_00389C90: the script manager state the VM runtime (src/vm/script_vm*.c)
 * reads and writes (session 30, docs/modules.md).  One type for the views
 * the runtime's functions had in h14, h42, h66, b09, b10, c08, c09, s6_13,
 * s11_w1 and s11_w1b; other files still declare their own view.
 *
 * Where those views disagreed on a field's type or bit layout, the field is a
 * union and each function keeps the member that gives its code: the flag
 * words at 0x3070 / 0x3078 as `x` (u64), `b` (u32 bit-fields) or `w` (u64
 * bit-fields, b09).  0x3180 holds h42's trigger boxes and 0x3384 the eight
 * sound / event slots.  h42 declared 15 boxes, which would run into the
 * slots; until session 32 the two were a union, but h18's func_001d7840
 * reads the slots through a whole-object view (D + 0x3384 + 0x18 i, in one
 * step), which a member of a union cannot give.  So box[] stops at 10
 * (script_vm.c indexes it by nbox only) and the slots are plain fields;
 * script_vm.c's slot and box accesses compile the same.  The size stays below the largest
 * view other files declare (0x34d8), so the float keep list does not change. */
#ifndef KH1_VM_VM_MGR_H
#define KH1_VM_VM_MGR_H

#include "common.h"
#include "data/pieces/D_002BC0F0.h"

/* 0x3070 */
typedef union {
    u64 x;
    s32 i[2];
    struct { u32 lo; u32 h0:6; u32 b38:1; u32 b39:1; u32 b40:1; u32 h9:2; u32 b43:1; u32 h12:9; u32 b53:1; u32 h22:10; } b;
    struct {
        u64 pad0 : 32;
        u64 b32 : 1; u64 b33 : 1; u64 b34 : 1; u64 b35 : 2; u64 b37 : 1; u64 b38 : 1; u64 b39 : 1;
        u64 b40 : 1; u64 b41 : 2; u64 b43 : 1; u64 b44 : 2; u64 b46 : 1; u64 b47 : 1;
        u64 b48 : 1; u64 b49 : 1; u64 b50 : 1; u64 b51 : 1; u64 b52 : 1; u64 b53 : 1; u64 b54 : 1; u64 b55 : 1;
        u64 b56 : 1; u64 b57 : 1; u64 b58 : 1; u64 b59 : 1; u64 b60 : 1; u64 b61 : 1; u64 b62 : 1; u64 b63 : 1;
    } w;
} VmMgrF3070;

/* 0x3078 */
typedef union {
    u64 x;
    struct {
        u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
        u32 b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, brest:18;
        u32 hi;
    } b;
    struct {
        u64 b0 : 1; u64 b1 : 1; u64 b2 : 1; u64 b3 : 1; u64 b4 : 1; u64 b5 : 1; u64 b6 : 1; u64 b7 : 1;
        u64 b8 : 2; u64 b10 : 1; u64 b11 : 1; u64 b12 : 1; u64 b13 : 1; u64 rest : 50;
    } w;
} VmMgrF3078;

/* An effect record of D_0038CD3C[] (made by func_001226f0; src/vm/vm_lib.c):
 * x0, the fade f0c, two positions and the colour v30. */
typedef struct VmFx {
    s32 x0;
    u8 pad4[8];
    f32 f0c;
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];             /* colour (r, g, b, a) */
} VmFx;

/* h42's trigger box: id, centre, size */
typedef struct { s32 id; u8 pad[12]; f32 c[4]; f32 s[4]; } __attribute__((aligned(8))) VmBox;

/* 0x3384: the eight slots func_001c4ed0 clears (obj, sound, return value ...) */
typedef struct { s32 obj, x4, snd, ret, x10, h; } VmSlot;

typedef struct {
    u8 wst[4];              /* 0x0000: state of the 4 open message windows (src/msgwin/) */
    u8 tst[8];              /* 0x0004: state of the 8 window templates */
    u8 xc[4];               /* 0x000c: cleared for 8 templates (runs into tbl) */
    u16 tbl[8][256];        /* 0x0010: each template's message ids (D_00388480 indices) */
    s32 cnt[8];             /* 0x1010 */
    s8 ids[4];              /* 0x1030: the template each open window shows */
    s32 a1034[512];         /* 0x1034 */
    s32 a1834[512];         /* 0x1834 */
    s32 a2034[512];         /* 0x2034: saved copy of a1034 */
    s32 a2834[512];         /* 0x2834: saved copy of a1834 */
    s32 x3034;              /* 0x3034: which VM table runs (0: D_0038D170) */
    s32 x3038;              /* 0x3038: same for D_003A7990 / D_003B4DA0 */
    s32 x303c;
    s8 *x3040;              /* 0x3040: the loaded script file */
    s8 *x3044;
    s32 x3048;
    s32 *x304c;
    s32 x3050;
    s32 *x3054;
    s32 x3058;
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    s32 x306c;
    VmMgrF3070 f3070;       /* 0x3070 */
    VmMgrF3078 f3078;       /* 0x3078 */
    s32 py0;                /* 0x3080: three screen points (func_001d2fd8 ..): y of the first, */
    s32 px1, py1;           /*   whose x is f3078.b.hi (h17's w[1]) */
    s32 px2, py2;
    s32 x3094;
    s32 fxk;                /* 0x3098: the effect func_001cebe8 fades (D_0038CD3C index) */
    s32 fxn;                /* 0x309c: frames left */
    f32 fxd[3];             /* 0x30a0: colour step */
    VmFx *fx[4];            /* 0x30ac */
    u8 pad30bc[0x3128 - 0x30bc];
    s32 an;                 /* 0x3128: frames left of the alpha fade (func_001cff28, D_002BC080[3]) */
    s32 ad;                 /* 0x312c: alpha step */
    s32 rgbn;               /* 0x3130: frames left of the colour fade (func_001cfff8, D_002BC080[0..2]) */
    s32 rgbd[3];            /* 0x3134 */
    s32 x3140;
    s32 *x3144;             /* 0x3144: where func_001cac60 stores the choice */
    u32 x3148;
    f32 x314c;
    u8 pad3150[0x3158 - 0x3150];
    s32 x3158[5];
    void *x316c;
    s32 x3170;
    s32 x3174;
    s32 nbox;               /* 0x3178 */
    u8 pad317c[4];
    VmBox box[10];          /* 0x3180: h42's trigger boxes (nbox of them) */
    u8 pad3360[0x3380 - 0x3360];
    s32 x3380;
    VmSlot e[8];            /* 0x3384 */
    s32 x3444;
    u8 pad3448[0x3450 - 0x3448];
    s32 x3450;
    u8 pad3454[0x3460 - 0x3454];
    f32 cdur;               /* 0x3460: camera tween length (func_001d9100) */
    f32 ct;                 /* 0x3464: its time (func_001d8f38) */
    u8 pad3468[8];
    CamS_2BC0F0 c0;         /* 0x3470: tween start (a camera setting, D_002BC0F0's 0x30 bytes) */
    CamS_2BC0F0 c1;         /* 0x34a0: tween target */
} VmMgr;

#endif /* KH1_VM_VM_MGR_H */
