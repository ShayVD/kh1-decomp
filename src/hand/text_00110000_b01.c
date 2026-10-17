#include "common.h"
typedef struct { f32 minx, p0[3], miny, p1[3], minz, p2[3], maxx, p3[3], maxy, p4[3], maxz, p5[3]; } Box01;
extern Box01 D_002C1260;
extern s32 D_002C12C4;
extern s32 D_002BD250[];
extern s32 D_004E0428[];
typedef struct { f32 mn[3]; f32 mx[3]; u16 n; u16 ids[1]; } Node01;
extern Node01 **D_002A6244;
typedef struct { u32 a, b, c, d; u32 f; } Tri01;
extern Tri01 *D_002A6238;
typedef struct { u8 pad[0x18]; s16 cnt; } Qry01;
s32 func_00115d58(Qry01 *);
void func_001158c8(Qry01 *);
void func_00115940(s32);

static inline s32 ov01(f32 *mn, f32 *mx) {
    if (mn[0] <= D_002C1260.maxx && D_002C1260.minx <= mx[0] && D_002C1260.maxy >= mn[1] &&
        D_002C1260.miny <= mx[1] && D_002C1260.maxz >= mn[2] && D_002C1260.minz <= mx[2]) return 1;
    return 0;
}
static inline s32 in01(f32 *mn, f32 *mx) {
    if (D_002C1260.minx < mn[0] && D_002C1260.maxx > mx[0] && D_002C1260.miny < mn[1] &&
        D_002C1260.maxy > mx[1] && D_002C1260.minz < mn[2] && D_002C1260.maxz > mx[2]) return 1;
    return 0;
}

void func_00117db0(Qry01 *q) {
    s32 n, i, j;
    Node01 *e;
    u16 *p;
    s32 id;
    s32 *ip;
    D_002C12C4 = 0;
    n = func_00115d58(q);
    ip = D_004E0428;
    func_001158c8(q);
    for (i = 0; i < n; i++) {
        e = D_002A6244[*ip++];
        if (ov01(e->mn, e->mx)) {
            if (in01(e->mn, e->mx)) {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f;
                    if (!(*f & 1)) {
                        D_002BD250[D_002C12C4] = id;
                        D_002C12C4++;
                    }
                }
            } else {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f;
                    if (!(*f & 1)) func_00115940(id);
                }
            }
        }
    }
    q->cnt = D_002C12C4;
}
