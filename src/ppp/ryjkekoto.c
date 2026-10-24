/* The pppRyjDrawKekoto class's Frame and Con (docs/modules.md "Session
 * 49"): the frame refreshes the UVs (ryjkekoto.nostrict.c's func_001a1158)
 * when the key's frame comes round; the Con clears the eight quadwords of
 * the work area.  Read from the code. */
#include "m2c.h"
#include "ppp.h"

typedef unsigned int u128 __attribute__((mode(TI)));
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

s32 func_001a1158(s32, s32);

s32 pppRyjDrawKekotoFrame(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 8);
    if (!(*(M2C_UNK *)arg1 == M2C_FIELD(arg0, s32 *, 0xC))) {
        return temp_v0;
    }
    return func_001a1158(arg1, temp_v0 + 0xA0);
    return temp_v0;
}

typedef struct {
    u128 m[8];
} PppKekoto;

void pppRyjDrawKekotoCon(void *obj, PppEntry *e) {
    PppKekoto *w = PPP_WORK(PppKekoto, obj, e, 2);
    s32 i;

    for (i = 7; i >= 0; i--)
        w->m[i] = 0;
}
