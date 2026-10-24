/* Model packets (mdlpkt.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/gs.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s6_01_p2.h"
#include "data/types/nostrict_text_00100000_s6_01.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F30.h"
#include "data/types/nostrict_text_00100000_s6_01_p.h"

/* func_001090e8 (from hand/nostrict/text_00100000_s6_01.c). */
extern s32 FlushCache(s32);
extern u8 D_002BC1B0[];
s32 func_001090e8(void *src, s32 w, s32 h, s32 dbp) {
    PlatGsSetDefLoadImage(D_002BC1B0, dbp, w / 64, 20, 0, 0, w, h);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    return PlatGsExecLoadImage(D_002BC1B0, src);
}

