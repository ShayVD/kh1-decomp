/* sceDbcCreateSocket 0x2682a8: 7 words off (s6 draft 9w), sdk/gcc991111. `i = 0;` as its own first statement and the copies in the order below give the original registers (i t0, src base t1, dst base t2); left: the store schedule of the first block (orig: sw a1 40; move t0,0; lw w0; addiu t2; sw a2 44; sw w0; lw w1...). All 1680 orders of {i=0, p[10], p[11], [0]} around the fixed [1..4] sequence give >= 7w. */
#include "common.h"
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
void func_00268a78(const char *, ...);
extern u8 D_0066FB08[];
extern s32 D_0066FB80[];
extern char D_00492F70[];
typedef struct { s32 w[5]; u8 name[16]; } DbcSockCfg;
s32 sceDbcCreateSocket(DbcSockCfg *cfg, s32 a, s32 b) {
    s32 *p = D_0066FB80;
    s32 i;
    i = 0;
    p[1] = cfg->w[1];
    D_0066FB80[0] = cfg->w[0];
    p[10] = a;
    p[11] = b;
    p[2] = cfg->w[2];
    p[3] = cfg->w[3];
    p[4] = cfg->w[4];
    for (; i < 16; i++) {
        u8 *dst = (u8 *) &p[5];
        dst[i] = cfg->name[i];
    }
    if (sceSifCallRpc(D_0066FB08, 0x80000901, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F70);
        return 0;
    }
    return p[9];
}
