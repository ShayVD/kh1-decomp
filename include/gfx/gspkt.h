/* GS packets (src/gfx/gspkt.c, gspkt.nostrict_nofill.c; docs/modules.md
 * "Session 45").  Other files still declare their own prototypes of these
 * (each a view checked by its own match); switch them one at a time. */
#ifndef KH1_GFX_GSPKT_H
#define KH1_GFX_GSPKT_H

#include "common.h"

void func_00236fd8(u64 *tag, u64 *end);
u64 *func_00237008(u64 reg, u64 data, u64 *p);
void func_00237018(void *p, s32 n, s32 wait);
void func_002370c8(u64 *p);
void func_002372e0(void);
void func_00237318(void);

#endif /* KH1_GFX_GSPKT_H */
