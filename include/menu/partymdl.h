/* The party models of the menus (docs/modules.md "Session 39"): D_003F3530 holds
 * four models of 0xd0 bytes (the party members 0-2 from func_001ef8f8, and a
 * fourth that src/hand/text_00220000_h72.c turns on), D_003F3870 counts the
 * party members.  src/menu/partymdl.c. */
#ifndef KH1_MENU_PARTYMDL_H
#define KH1_MENU_PARTYMDL_H

#include "common.h"

typedef f32 Mtx9[4][4];

typedef struct {
    s32 x0;                 /* the character (func_00162070 / func_00162110) */
    s32 x4, x8, xc, x10;
    void *x14;              /* the model */
    u8 x18[4];              /* the motion (func_001301d8) */
    s32 x1c;
    u8 pad20[8];
    s32 x28, x2c, x30;      /* x30 the draw id */
    union { s32 w; s8 c[4]; } u34;   /* the colour (func_0020a248 sets its bytes) */
    s8 c38[4];
    s32 x3c;
    s8 c40[8];
    s32 x48, x4c, x50;
    u8 pad54[0x60 - 0x54];
    u64 x60, x68;
    f32 x70;                /* the motion frame */
    s32 x74, x78;           /* the bones from the bone 52 on: count, first */
    u8 pad7c[4];
    Mtx9 x80;
    f32 (*xc0)[4];          /* x74 matrices */
    u8 padc4[0xcc - 0xc4];
    s32 active;
} PartyMdl;                 /* 0xd0 */

void func_00209d48(void);
void func_00209f70(void);
void func_0020a1d8(void);
void func_0020a248(s32);
void func_0020a6c0(s32);
void func_0020a728(s32);

#endif /* KH1_MENU_PARTYMDL_H */
