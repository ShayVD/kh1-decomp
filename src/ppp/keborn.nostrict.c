/* The KeBornRnd helper, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a5520 calls fn(obj, key, point) cnt times on the points of group
 * id (D_00615E64's group table, the points from the current matrix owner
 * D_00615E68 or the group's resource), in order from *pidx or at random
 * (func_001a8f30) when rnd is set.  pppKeBornRnd2Frame ... 6 call it.
 * Read from the code, not proved by a boot. */
#include "common.h"

typedef f32 Mtx4[4][4];
typedef struct { u32 flags; u8 pad04[0x12]; u16 h16; } DMdl;
typedef struct { u8 pad[0x14]; void *x14; u8 pad18[4]; DMdl *mdl; s32 x20; } Ent24;
typedef struct { u8 pad[0x10]; Mtx4 m; Mtx4 m2; u8 *x90; s32 x94; } PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
typedef struct { s16 a; s16 n; u16 *list; } Grp;
typedef struct { u8 pad0[0x10]; Ent24 *x10; void *anims; Grp *grps; } PppRes;
extern PppRes *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
s32 func_001a8f30(void);

void func_001a5520(void *obj, void *key, void (*fn)(void *, void *, void *), u16 *pidx, s16 id, u8 rnd, u8 cnt) {
    Grp *g = &D_00615E64->grps[id];
    u8 *base = D_00615E68->x90;
    s32 idx;

    if (base == NULL)
        base = D_00615E64->x10[g->a].x14;
    if (rnd)
        idx = func_001a8f30() % g->n;
    else
        idx = *pidx;
    for (; cnt != 0; cnt--) {
        fn(obj, key, base + g->list[idx++] * 6);
        if (rnd)
            idx = func_001a8f30() % g->n;
        else if (idx >= g->n)
            idx = 0;
    }
    *pidx = idx;
}
