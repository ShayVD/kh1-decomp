/* The data piece D_00304B78 (src/data/data_0030.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00304B78_H
#define KH1_DATA_PIECES_D_00304B78_H

#include "common.h"

typedef struct {
    u32 lv:3;
    u32 on:1;
    u32 :28;
} W55Bf_304b78;

extern W55Bf_304b78 D_00304B78;

#endif /* KH1_DATA_PIECES_D_00304B78_H */
