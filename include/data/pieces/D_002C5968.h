/* The data piece D_002C5968 (src/data/data_002C.s): one declaration its users
 * share (phase 4, session 26: users whose own type differs cast at each use). */
#ifndef KH1_DATA_PIECES_D_002C5968_H
#define KH1_DATA_PIECES_D_002C5968_H

#include "common.h"

/* The flag word's views (session 31).  Users keep the declaration's volatile s32
 * and cast to the view they read: the low byte's bit-fields (byte loads and
 * stores: the semaphore `mode` at bits 3-4), the word's flag bits (word loads
 * and stores), or the union of both widths. */
typedef struct { u8 b0 : 1; u8 lo : 2; u8 mode : 2; u8 hi : 3; } Sema_2c5968;
typedef struct { u32 b0 : 1; u32 b1 : 1; u32 b2 : 1; u32 r : 29; } Fl_2c5968;
typedef union { u32 w; Fl_2c5968 f; u8 c[4]; } W_2c5968;

extern volatile s32 D_002C5968;

#endif /* KH1_DATA_PIECES_D_002C5968_H */
