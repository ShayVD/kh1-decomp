/* func_00166248 (r2_10 s10): MATCH, hand/nostrict. session9 r2_1 4w draft plus CONTEXT_ONLY {} stubs of func_00164ba8 and func_001655e0 above it (both matched in src/hand/nostrict/text_00150000_h59.c and text_00160000_c03.c; a stub for func_00121e28 must NOT be added: it costs 2w). With the stubs the calls get REG_EH_REGION 0 and the entry bltz is no longer bltzl. */
#include "common.h"
/* ---- func_00165cf8 ---- */
typedef f32 C03Mtx[4][4];
typedef struct { u32 n; u32 ids[1]; } C03Ids;
typedef struct { u8 pad[0x90]; s32 x90[4]; } C03Sk8;
typedef struct { C03Ids *p; s32 pad[3]; } C03HdE;
typedef struct { s16 n; s16 pad2; s32 x4; C03Sk8 *p8; s32 xC; C03HdE e[1]; } C03Hdr;
typedef struct { u32 lo:21; u32 k:2; u32 hi:9; } C03BF;
typedef struct { u16 idx; u8 type; u8 pad3[3]; } C03Ch;
typedef struct { f32 t[3]; s32 parent; f32 r[3]; f32 s[3]; } C03Jnt;
typedef struct { f32 t[4]; f32 x[4]; f32 r[4]; f32 s[4]; } C03Pose;
typedef struct {
    u8 pad[0x10];
    s32 n10;             /* 0x10 */
    C03BF *p14;          /* 0x14 */
    s32 n18;             /* 0x18 */
    C03Ch *p1C;          /* 0x1C */
    s32 n20;             /* 0x20 */
    C03Ch *p24;          /* 0x24 */
    void *p28;           /* 0x28 */
    s32 n2C;             /* 0x2C */
    C03Jnt *p30;         /* 0x30 */
} C03Bits;
typedef struct { s16 h0; s16 h2; u8 pad4[0xC]; f32 v10[4]; f32 v20[4]; } __attribute__((aligned(8))) C03Lnk;
typedef struct {
    C03Hdr **p0;         /* 0x0 */
    C03Bits *p4;         /* 0x4 */
    f32 f8;              /* 0x8 */
    u32 wC;              /* 0xC */
    u8 pad10[0x90 - 0x10];
    f32 v90[4];          /* 0x90 */
    f32 vA0[4];          /* 0xA0 */
    f32 vB0[4];          /* 0xB0 */
    f32 vC0[4];          /* 0xC0 */
    C03Mtx mD0;          /* 0xD0 */
    C03Mtx m110;         /* 0x110 */
    C03Mtx *p150;        /* 0x150 */
    C03Mtx *p154;        /* 0x154 */
    void *p158;          /* 0x158 */
    void *p15C;          /* 0x15C */
    void *p160;          /* 0x160 */
    f32 (*p164)[4];      /* 0x164 */
    f32 (*p168)[4];      /* 0x168 */
    C03Lnk *p16C;        /* 0x16C */
} C03Mdl;

extern s16 D_00574F30[];
CONTEXT_ONLY void func_00164ba8(C03Mdl * p0, C03Bits * p1) {}
CONTEXT_ONLY void func_001655e0(f32 (*p0)[4], C03Mdl * p1, f32 p2, C03Bits * p3) {}
