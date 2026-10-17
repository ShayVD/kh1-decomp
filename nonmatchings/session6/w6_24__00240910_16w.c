/* func_00240910 16w off (nostrict_nogcse; 17w nostrict): ours uses movn for 'if (n) r = p', orig has bnezl; regs k in a0/r in v0 differ */
#include "common.h"
typedef struct { u8 pad[0xD00]; } EntA;
typedef struct {
    s32 used[8];
    EntA ent[5];
    s32 unk4120;
    s32 unk4124;
} G51E50;
extern G51E50 D_00651E50;
typedef struct { u8 pad[0x4C]; u16 x4c; } O130;
typedef struct { u8 pad[0x130]; O130 *x130; } Obj;
s32 func_0013c318(u16);
EntA *func_00240910(Obj *o) {
    EntA *r;
    s32 n;
    EntA *p;
    s32 k = func_0013c318(o->x130->x4c);
    r = 0;
    if (k == 1 || k == 2) {
        if (k == 1) { n = D_00651E50.used[1]; p = &D_00651E50.ent[1]; }
        else { n = D_00651E50.used[2]; p = &D_00651E50.ent[2]; }
        if (n) r = p;
    }
    return r;
}
