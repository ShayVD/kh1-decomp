/* Types moved from src/hand/text_00120000_h5.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00120000_H5_H
#define KH1_DATA_TYPES_TEXT_00120000_H5_H

#include "common.h"

typedef struct Node {
    union {
        u64 flags;
        u8 b[8];
    };
    u8 pad008[0xc];
    struct Node *f14;
    void *f18;
    u8 pad01c[0x720 - 0x1c];
    struct Node *next;
    u8 pad724[0x730 - 0x724];
} Node;

#endif /* KH1_DATA_TYPES_TEXT_00120000_H5_H */
