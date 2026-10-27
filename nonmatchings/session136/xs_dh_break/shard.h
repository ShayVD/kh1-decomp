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
