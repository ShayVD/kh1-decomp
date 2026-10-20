/* Shared bss names 004Fxxxx declared with a moved type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004F_TYPED_H
#define KH1_DATA_BSS_004F_TYPED_H

#include "common.h"
#include "data/types/text_00110000_h30.h"
#include "data/types/text_00110000_h4.h"
#include "data/types/text_00110000_h53.h"
#include "data/types/text_00120000_h31.h"

extern Block D_004F45B0[];
extern Block *D_004F6DB0;
extern TPool D_004F6EC0;
extern M53 D_004F7660[];
extern M53 D_004F76E0[];
extern M53 D_004F7760[];
extern A6 D_004F7820[3];
extern B6 D_004F7C10[3];
extern D6 D_004F8270[];

#endif /* KH1_DATA_BSS_004F_TYPED_H */
