/* The data piece D_00364130 (src/data/data_0036.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_00364130_H
#define KH1_DATA_PIECES_D_00364130_H

#include "common.h"
#include "m2c.h"

typedef struct Sub80_364130 {
    u8 pad0[6];
    u16 flags;
    s32 x88;
    struct { u8 pad[0xfc]; u16 xfc; } *p8c;
    u8 pad10[4];
    s32 key;
    u8 pad18[0x10];
    s32 xa8;
    u8 pad2c[0x40 - 0x2c];
} Sub80_364130;
typedef struct E0C0_364130 {
    u8 pad0[0x80];
    Sub80_364130 s;
} E0C0_364130;
typedef struct {
    u8 pad[0x14];
    s32 flags;
} PLink_364130;
typedef struct {
    u8 pad[0xf8];
    u8 xf8;
    u8 padf9[3];
    u16 xfc;
    u16 xfe;
} POwner_364130;
typedef struct PObj_364130 {
    u8 pad0[0x58];
    s32 x58;
    u8 pad5c[4];
    s32 x60;
    u8 pad64[0x22];
    u16 flags;
    s32 key;
    POwner_364130 *own;
    u8 x90;
    u8 pad91[2];
    u8 x93;
    PLink_364130 *link;
    s32 x98;
    f32 x9c;
    u8 pada0[8];
    s32 xa8;
    f32 xac;
    u8 padb0;
    u8 xb1;
    u8 padb2;
    u8 xb3;
    u8 xb4;
    u8 xb5;
    u8 padb6[10];
} PObj_364130;
typedef struct E0C0_364130_2 {
    u8 pad0[0x86];
    u16 flags;   /* 0x86: bit 0 = in use, bit 5 = paused */
    u8 pad88[4];
    struct { u8 pad[0xfc]; u16 xfc; } *p8c; /* 0x8C */
    u8 pad90[4];
    s32 key;     /* 0x94 */
    u8 pad98[0x10];
    s32 xa8;     /* 0xA8 */
    u8 padac[0xc0 - 0xac];
} E0C0_364130_2;
typedef struct {
    u8 pad[0xFC];
    u16 unkFC;
} PppOwner_364130;
typedef struct PppMng_364130 {
    u8 pad00[0x86];
    u16 st;          /* +0x86 */
    u8 pad88[4];
    PppOwner_364130 *owner; /* +0x8C */
    u8 pad90[4];
    s32 link;        /* +0x94: a PppLink *, typed s32 (see func_001827f0) */
    s32 unk98;       /* +0x98 */
    u8 pad9C[0xC];
    s32 unkA8;       /* +0xA8 */
    u8 padAC[0x14];
} PppMng_364130;
typedef struct H39Obj_364130 {
    u8 pad0[0x86];
    u16 flags; /* 0x86: bit 0 in use, bit 2 stopping */
    u8 pad88[4];
    struct {
        u8 pad[0xfc];
        u16 xfc;
    } *p8c;   /* 0x8C */
    u8 pad90[4];
    s32 key;  /* 0x94 */
    s32 x98;  /* 0x98 */
    u8 pad9c[0xc];
    s32 xa8;  /* 0xA8 */
    u8 padac[0xc0 - 0xac];
} H39Obj_364130;
typedef struct E0C0_364130_3 { u8 pad0[0x80]; u64 x80; u8 pad88[0xc0 - 0x88]; } E0C0_364130_3;
typedef union { M2C_UNK i; E0C0_364130 e0C0[256]; PObj_364130 pObj[256]; E0C0_364130_2 e0C0_2[256]; PppMng_364130 pppMng[256]; H39Obj_364130 h39Obj[256]; E0C0_364130_3 e0C0_3[256]; } U00364130;

extern U00364130 D_00364130;

#endif /* KH1_DATA_PIECES_D_00364130_H */
