/* sceDbcCreateSocket (0x2682a8): same size, 9 words: loop index i gets a1 in ours, t0 in the original (src base t1, dst base t2); everything else matches. Uninitialised i (live from entry) gives t0, so i=0 must conflict with param a1. Mode sdk/gcc991111. */
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
/*P*/
    p[10] = a;
    p[11] = b;
    D_0066FB80[0] = cfg->w[0];
    p[1] = cfg->w[1];
    p[2] = cfg->w[2];
    p[3] = cfg->w[3];
    p[4] = cfg->w[4];
/*Q*/
    for (i = 0; i < 16; i++) {
        u8 *dst = (u8 *) &p[5];
        dst[i] = cfg->name[i];
    }
    if (sceSifCallRpc(D_0066FB08, 0x80000901, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F70);
        return 0;
    }
    return p[9];
}
