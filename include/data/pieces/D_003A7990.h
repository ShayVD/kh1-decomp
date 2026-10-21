/* The data piece D_003A7990 (src/data/data_003A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_003A7990_H
#define KH1_DATA_PIECES_D_003A7990_H

#include "common.h"
#include "data/types/text_001e0000_s6_16.h"

typedef struct {
    void *p;
    u8 pad_4[0x34c];
} E848_3a7990;

extern E848b D_003A7990[];

#endif /* KH1_DATA_PIECES_D_003A7990_H */
