/* Shared bss names 004Exxxx declared with a moved type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004E_TYPED_H
#define KH1_DATA_BSS_004E_TYPED_H

#include "common.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/types/text_00110000_h3.h"
#include "data/types/text_00110000_h30.h"

extern SndSlot *D_004E3450;
extern Slot12 *D_004E3454;
extern SndSlot D_004E3458[];
extern Pair D_004E39F8[];
extern V4 D_004E3A20;
extern V4 D_004E3A30;
extern FileEnt D_004E4A00[];

#endif /* KH1_DATA_BSS_004E_TYPED_H */
