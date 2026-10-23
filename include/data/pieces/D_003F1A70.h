/* The data piece D_003F1A70 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F1A70_H
#define KH1_DATA_PIECES_D_003F1A70_H

#include "common.h"

/* A GIF packet quadword (session 31): D_003F1A70, D_003F1E70 and D_003F2270
 * are 0x400-byte packet buffers h69's func_001f2eb8 fills with these. */
typedef struct {
    u64 a;
    u64 b;
} Q_3f1a70;

extern Q_3f1a70 D_003F1A70;

#endif /* KH1_DATA_PIECES_D_003F1A70_H */
