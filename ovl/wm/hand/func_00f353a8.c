/* wm.x func_00f353a8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; u8 pad2[6]; } IE;
typedef struct { u8 pad[4]; u16 n; u8 pad2[106]; IE e[1]; } Info;
typedef struct { s32 h[5]; s16 n; s16 m; s16 cnt[192]; s16 best[192]; } R;
void func_001be820(void *, s32);
Info *func_001ba9d8(s32);
extern s32 D_00F8C14C;
extern s32 D_00FBB5A0, D_00FBB5A4, D_00FBB5A8;
extern s32 D_00FBB5AC, D_00FBB5B0, D_00FBB5B4, D_00FBB5B8, D_00FBB5BC;

void func_00f353a8(R *r) {
    s16 tmp[192];
    Info *inf;
    s32 i;
    IE *e;
    func_001be820(r, sizeof(R));
    func_001be820(tmp, sizeof(tmp));
    inf = func_001ba9d8(D_00FBB5A0);
    for (i = 0, e = inf->e; i < inf->n; i++, e++) r->cnt[e->id - 1]++;
    r->n = inf->n;
    if (D_00F8C14C != 0 && D_00FBB5A8 > 0) {
        inf = func_001ba9d8(D_00FBB5A4);
        for (i = 0, e = inf->e; i < inf->n; i++, e++) tmp[(u32)e->id - 1]++; /* u32 keeps the -1 out of the address fold */
        for (i = 0; i < 192; i++) {
            if (tmp[i] > r->cnt[i]) {
                r->best[i] = r->cnt[i];
                r->cnt[i] = tmp[i];
            } else {
                r->best[i] = tmp[i];
            }
        }
        if (inf->n > r->n) {
            r->m = r->n;
            r->n = inf->n;
        } else {
            r->m = inf->n;
        }
    } else {
        for (i = 0; i < 192; i++) r->best[i] = r->cnt[i];
        r->m = r->n;
    }
    r->h[0] = D_00FBB5AC;
    r->h[1] = D_00FBB5B0;
    r->h[2] = D_00FBB5B4;
    r->h[3] = D_00FBB5B8;
    r->h[4] = D_00FBB5BC;
}
