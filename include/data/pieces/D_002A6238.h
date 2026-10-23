/* The data piece D_002A6238 (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002A6238_H
#define KH1_DATA_PIECES_D_002A6238_H

#include "common.h"

/* The attribute word at 0x10: its users split the bits differently (session 30:
 * one struct per split, all members of one union; `w` is the whole word). */
typedef struct {
    u32 f0:4; u32 f4:4; u32 f8:3; u32 f11:4; u32 f15:3;
    u32 f18:4; u32 f22:1; u32 f23:5; u32 f28:1; u32 f29:3;
} EntBits_2a6238;           /* h1 */
typedef struct {
    u32 on:1; u32 rest:31;
} OnBits_2a6238;            /* h28 */
typedef struct {
    u32 p0:3; u32 b3:1; u32 p4:4; u32 b8:1; u32 b9:1; u32 b10:1; u32 p11:4;
    u32 b15:1; u32 b16:1; u32 b17:1; u32 p18:4; u32 b22:1; u32 b23:1; u32 b24:1;
    u32 b25:1; u32 b26:1; u32 b27:1; u32 b28:1; u32 p29:3;
} TriBits_2a6238;           /* h51 */
typedef struct {
    u32 lo:11; u32 k:4; u32 m:3; u32 x40:4; u32 hi:10;
} PlaneBits_2a6238;         /* h52 */
typedef struct {
    u32 b0:1; u32 sub:2; u32 b3:1; u32 kind:4; u32 b8:7; u32 b15:1;
    u32 b16:7; u32 b23:1; u32 rest:8;
} ColBits_2a6238;           /* s10_r2_10 */

typedef union {
    u32 w;
    EntBits_2a6238 e;
    OnBits_2a6238 o;
    TriBits_2a6238 t;
    PlaneBits_2a6238 p;
    ColBits_2a6238 c;
} Fl20_2a6238;

typedef struct {
    s16 v[4];
    s16 n;
    u8 act;
    u8 id;
    union {                 /* 0xc: the plane's d; an id before the load sets it */
        f32 d;
        s32 i;
        u16 h;
    };
    Fl20_2a6238 f;
} Ent20_2a6238;

extern Ent20_2a6238 *D_002A6238;

#endif /* KH1_DATA_PIECES_D_002A6238_H */
