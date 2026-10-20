/* Shared data names 003Exxxx: pieces of the user's ELF defined in
 * src/data/data_003E.s (phase 4, tools/shift/define_pieces.py). Only names whose
 * C users agree on the type are declared here; users include this at their end. */
#ifndef KH1_DATA_DATA_003E_H
#define KH1_DATA_DATA_003E_H

#include "common.h"
#include "m2c.h"

extern s32 D_003E3C80;
extern s32 D_003E3CB0;
extern M2C_UNK D_003E3CB8;
extern s32 D_003E8D00[];
extern u16 D_003E8D40[];
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003E8E2C;
extern u16 D_003E9104;
extern M2C_UNK D_003E9630;

#endif /* KH1_DATA_DATA_003E_H */
