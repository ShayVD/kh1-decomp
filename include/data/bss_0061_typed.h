/* Shared bss names 0061xxxx declared with a moved type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0061_TYPED_H
#define KH1_DATA_BSS_0061_TYPED_H

#include "common.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h12.h"
#include "data/types/text_00180000_h39.h"
#include "data/types/text_00180000_h40.h"
#include "data/types/text_001a0000_h13.h"

extern H39Mtx D_00615F30;
extern u128 D_00615F80;
extern PppQv D_00616010[3];
extern H39Mtx D_00616180;
extern PppHookFn *D_00616220;
extern PppLight *D_0061E310[256];
extern PppMtx D_0061E780;
extern PppMtx D_0061E7C0;
extern GsTag D_0061EEA0[];

#endif /* KH1_DATA_BSS_0061_TYPED_H */
