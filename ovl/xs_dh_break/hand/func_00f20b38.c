/* xs_dh_break.x func_00f20b38: matched by hand. */
#include "ovl.h"

/* xs_dh_break.x func_00f20b38: draft (session 136), not byte-identical; the port runs it
 * (ovl/xs_dh_break/drafts.tsv). The entry's work: the player to the origin, the 2,500 shards
 * (50 x 50, func_00f20820), the shards' 256 x 256 8-bit texture and its CLUT from the file's
 * D_00F20D80 (+0x40, +0x10040) as upload chains, the draw settings chain D_00F313F0 (TEX0_1 etc.),
 * D_00FA2000's (func_00f20080), clears D_002BC0A8 bit 0 and installs func_00f20288 as a task. */
/* xs_dh_break.x (Dive to the Heart: the station's floor breaking into 2,500 falling shards): the
 * shard record of the session 136 drafts (0xB0 bytes, 2,500 from D_00F317F0). */
#ifndef KH1_XS_DH_BREAK_SHARD_H
#define KH1_XS_DH_BREAK_SHARD_H
#include "ovl.h"

typedef struct {
    OvlVec pt[4];  /* 0x00: the corners, from the centre after func_00f20820 */
    OvlVec c;      /* 0x40: the centre (y 0, w 1) */
    OvlVec rot;    /* 0x50: the angles */
    OvlVec drot;   /* 0x60: the angles' steps (x y z) */
    OvlVec vel;    /* 0x70: the fall (y only) */
    f32 tu[4];     /* 0x80: the corners' texture u */
    f32 tv[4];     /* 0x90: and v (1 - grid y) */
    f32 start;     /* 0xA0: D_00F311C4's time it starts to fall */
    u8 padA4[0xB0 - 0xA4];
} DhShard;

extern DhShard D_00F317F0[2500];
#endif


void func_00f206a0(void);
void func_00f20080(void);
void func_00f20820(DhShard *, s32, s32);
s32 func_00f20288(void);
void *func_0011fb38(s32, u64, void *);
void func_0011fb78(void *, s32, void *);
void *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, u32, u32, void *);
void *func_0011ef10(s32, s32 (*)(void));
extern f32 *D_002E26A0[];
extern OvlVec D_002C58A0;
extern s32 D_00425BC4;
extern s32 D_002BC0A8;
extern u8 D_00F20D80[];
extern u8 *D_00F31280;
extern u64 D_00F31290[], D_00F31340[], D_00F313F0[];

void func_00f20b38(void) {
    s32 row, col;
    DhShard *s;
    u64 *p;
    u64 *q;
    D_00425BC4 = 1;
    D_00F31280 = D_00F20D80;
    sceVu0CopyVector(D_002E26A0[0] + 4, D_002C58A0);
    func_00f206a0();
    s = D_00F317F0;
    for (row = 0; row < 50; row++)
        for (col = 0; col < 50; col++)
            func_00f20820(s++, row, col);
    func_0011fbb0(0x3A00, 1, 0, 0, 0, 16, 16, 64, (u32)(D_00F31280 + 0x10040), D_00F31340);
    func_0011fbb0(0x3600, 4, 0x13, 0, 0, 256, 256, 4096, (u32)(D_00F31280 + 0x40), D_00F31290);
    p = D_00F313F0;
    q = p;
    p += 2;
    p[0] = 0x1000000000008003ULL;
    p[1] = 0xE;
    p = func_0011fb38(0x47, 0x5000D, p + 2);
    p = func_0011fb38(6, 0x2007400621313600ULL, p);
    p = func_0011fb38(0x14, 0x61, p);
    p = func_0011fb38(0x3F, 0, p);
    func_0011fb78(q, 7, p);
    func_00f20080();
    D_002BC0A8 &= ~1;
    func_0011ef10(0x27100, func_00f20288);
}
