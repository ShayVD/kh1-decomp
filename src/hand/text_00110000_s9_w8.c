#include "common.h"
#include "data/pieces/D_002A6244.h"
#include "data/bss_004E.h"
/* func_00116368 (hand): both id loops written out with function-level `s32 id; s32 *fl;` shared by the two loops (global pseudos: fl is not tied to the address chain, gets a1 by copy preference; id ends in a1). */
typedef Node01 Node368;
#include "data/pieces/D_002A6238.h"
typedef struct { u8 pad[0x18]; u16 cnt; } Out368;
extern s32 D_002C12C4;
extern s32 D_004E0428[];
/* Per-kind triangle callbacks for func_00116368: D_002BD178 for nodes inside the box,
 * D_002BD1A8 for nodes that only overlap it (defined here: only this file uses them). */
void func_00115e90(s32, s32 *), func_00115ed0(s32, s32 *), func_00115f10(s32, s32 *), func_00115f50(s32, s32 *), func_00115f90(s32, s32 *), func_00115fd8(s32, s32 *), func_00116020(s32, s32 *), func_00116060(s32, s32 *), func_001160b0(s32, s32 *), func_001160f0(s32, s32 *), func_00116130(s32, s32 *), func_00116160(s32, s32 *), func_00116198(s32, s32 *), func_001161d0(s32, s32 *), func_00116200(s32, s32 *), func_00116240(s32, s32 *), func_00116278(s32, s32 *), func_001162b0(s32, s32 *), func_001162f8(s32, s32 *), func_00116330(s32, s32 *);
void (*D_002BD178[11])(s32, s32 *) = {
    func_00115e90, func_00115ed0, func_00115f10, func_00115f50, func_00115f90, func_00115fd8,
    func_00116020, func_00115f50, func_00116060, func_001160b0, func_001160f0,
};
void (*D_002BD1A8[11])(s32, s32 *) = {
    func_00116130, func_00116160, func_00116198, func_001161d0, func_00116200, func_00116240,
    func_00116278, func_001161d0, func_001162b0, func_001162f8, func_00116330,
};
#include "data/pieces/D_002C1260.h"
s32 func_00115d58(void);
void func_001158c8(Out368 *);

static inline s32 overlap(f32 *mn, f32 *mx, Box_2c1260 *b) {
    if (mn[0] <= b->mx[0][0] && b->mn[0][0] <= mx[0]
        && b->mx[1][0] >= mn[1] && b->mn[1][0] <= mx[1]
        && b->mx[2][0] >= mn[2] && b->mn[2][0] <= mx[2]) return 1;
    return 0;
}
static inline s32 inside(f32 *mn, f32 *mx, Box_2c1260 *b) {
    if (b->mn[0][0] < mn[0] && b->mx[0][0] > mx[0]
        && b->mn[1][0] < mn[1] && b->mx[1][0] > mx[1]
        && b->mn[2][0] < mn[2] && b->mx[2][0] > mx[2]) return 1;
    return 0;
}

void func_00116368(Out368 *o, s32 k) {
    s32 n, i, j;
    u16 *q;
    s32 *p;
    Node368 *nd;
    void (*f1)(s32, s32 *);
    void (*f2)(s32, s32 *);
    s32 id; s32 *fl;
    D_002C12C4 = 0;
    n = func_00115d58();
    p = D_004E0428;
    func_001158c8(o);
    f2 = D_002BD1A8[k];
    f1 = D_002BD178[k];
    for (j = 0; j < n; j++) {
        nd = D_002A6244[*p++];
        if (overlap(nd->mn, nd->mx, &D_002C1260)) {
            if (inside(nd->mn, nd->mx, &D_002C1260)) {
                q = nd->ids;
                for (i = 0; i < nd->n; i++) {
                    id = *q++;
                    fl = &D_002A6238[id].f.w;
                    if (!(*fl & 1)) f1(id, fl);
                }
            } else {
                q = nd->ids;
                for (i = 0; i < nd->n; i++) {
                    id = *q++;
                    fl = &D_002A6238[id].f.w;
                    if (!(*fl & 1)) f2(id, fl);
                }
            }
        }
    }
    o->cnt = *(u16 *)&D_002C12C4;
}
#include "data/data_002C.h"
