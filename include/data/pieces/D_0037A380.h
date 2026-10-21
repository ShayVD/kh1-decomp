/* The data piece D_0037A380 (src/data/data_0037.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_0037A380_H
#define KH1_DATA_PIECES_D_0037A380_H

#include "common.h"

typedef f32 Vec_37A380[4] __attribute__((aligned(16)));
typedef struct Elem_37A380 {
    s32 a;
    s32 b;
    s32 c;
    s32 pad;
    Vec_37A380 m[11];
    f32 f[6];
    struct Elem_37A380 *next;
    struct Elem_37A380 *prev;
} Elem_37A380;
typedef struct {
    f32 x0;
    u8 pad4[0xc];
    Vec_37A380 q10, q20, q30, q40;
    Vec_37A380 q50;
    f32 x60;
    u8 pad64[0xf0 - 0x64];
    Elem_37A380 arr[256];
    s32 n;
    f32 xE0F4;
    Elem_37A380 *first;
    Elem_37A380 *last;
} Scn_37A380;
typedef union { Scn_37A380 scn; u8 b[0xe100]; } U0037A380;

extern U0037A380 D_0037A380;

#endif /* KH1_DATA_PIECES_D_0037A380_H */
