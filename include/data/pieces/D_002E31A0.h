/* The data piece D_002E31A0 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002E31A0_H
#define KH1_DATA_PIECES_D_002E31A0_H

#include "common.h"
#include "data/pieces/D_002E319C.h"

/* the current menu item, which D_002E319C also points to (session 28) */
extern O8_2e319c *D_002E31A0;

#endif /* KH1_DATA_PIECES_D_002E31A0_H */
