/* The pppRyjMegaBirthModel class's Con and Des (docs/modules.md "Session
 * 49"): the Con clears the work area's quadword, its four pointers and two
 * counters; the Des frees the three particle blocks with func_00183b20.
 * ryjmbmodel.nostrict.c has the frame and the draw.  Read from the code. */
#include "m2c.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    u128 q;     /* +0x00 */
    s32 i[4];   /* +0x10 */
    s16 h[2];   /* +0x20 */
} PppMegaBirthModel;

void pppRyjMegaBirthModelCon(void *obj, PppEntry *e) {
    PppMegaBirthModel *w = PPP_WORK(PppMegaBirthModel, obj, e, 2);

    w->q = 0;
    w->i[0] = 0;
    w->i[1] = 0;
    w->i[2] = 0;
    w->i[3] = 0;
    w->h[0] = 0;
    w->h[1] = 0;
}

M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;

void pppRyjMegaBirthModelDes(s32 arg0, PppEntry *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = (void *)arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0x10);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x14);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x18);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x18) = 0;
    }
}
