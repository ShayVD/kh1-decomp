/* Shared bss names 004Dxxxx declared with a moved type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004D_TYPED_H
#define KH1_DATA_BSS_004D_TYPED_H

#include "common.h"
#include "data/types/text_00110000_h29.h"
#include "data/types/text_00110000_h52.h"

extern Mtx52 D_004D8E40;
extern Mtx52 D_004D8E80;
extern Mtx52 D_004D9100;
extern Mtx52 D_004D9140;
extern Mtx52 D_004D9180;
extern Mtx52 D_004D91C0;
extern W29Clock D_004D9288;

#endif /* KH1_DATA_BSS_004D_TYPED_H */
