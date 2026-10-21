#include "common.h"
/* kh1-decomp session 7, worker w25: func_00115940 (hand; also matches hand/nostrict).
   VU0 bounding-box cull: C with the vsub/cfc2 MAC-flag test as an inline-asm macro. */
typedef f32 V4_25[4] __attribute__((aligned(16)));
typedef struct { V4_25 mn[3]; V4_25 mx[3]; } Box25;
typedef struct { u16 a, b, c; s16 d; u8 pad[12]; } Tri25;
typedef struct { f32 x[3]; } Vtx25;
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002C1260.h"
extern s32 D_002C12C4;
#include "data/pieces/D_002BD250.h"

#define VSUB_MAC(r, a, b) \
    __asm__ volatile( \
        "lqc2 $vf4, 0(%1)\n" \
        "lqc2 $vf5, 0(%2)\n" \
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "vnop\n" \
        "cfc2 %0, $vi17\n" \
        : "=&r"(r) : "r"(a), "r"(b) : "memory")

void func_00115940(s32 id) {
    V4_25 v;
    Tri25 *t = &((Tri25 *)D_002A6238)[id];
    u16 *q = &t->a;
    Vtx25 *p0, *p1, *p2, *p3;
    register s32 r asm("$2");
    register s32 r2 asm("$3");
    p0 = &((Vtx25 *)D_002A624C)[*q++];
    p1 = &((Vtx25 *)D_002A624C)[*q++];
    p2 = &((Vtx25 *)D_002A624C)[*q++];
    switch (t->d) {
    case -1: case -2:
        v[0] = p0->x[0]; v[1] = p1->x[0]; v[2] = p2->x[0];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[0], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[0]); if ((r2 & 0xe0) == 0xe0) return;
        v[0] = p0->x[1]; v[1] = p1->x[1]; v[2] = p2->x[1];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[1], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[1]); if ((r2 & 0xe0) == 0xe0) return;
        v[0] = p0->x[2]; v[1] = p1->x[2]; v[2] = p2->x[2];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[2], v); if ((r & 0xe0) == 0xe0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[2]); if ((r2 & 0xe0) == 0xe0) return;
        break;
    default:
        p3 = &((Vtx25 *)D_002A624C)[*q];
        v[0] = p0->x[0]; v[1] = p1->x[0]; v[2] = p2->x[0]; v[3] = p3->x[0];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[0], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[0]); if ((r2 & 0xf0) == 0xf0) return;
        v[0] = p0->x[1]; v[1] = p1->x[1]; v[2] = p2->x[1]; v[3] = p3->x[1];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[1], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[1]); if ((r2 & 0xf0) == 0xf0) return;
        v[0] = p0->x[2]; v[1] = p1->x[2]; v[2] = p2->x[2]; v[3] = p3->x[2];
        VSUB_MAC(r, (*(Box25 *)&D_002C1260).mx[2], v); if ((r & 0xf0) == 0xf0) return;
        VSUB_MAC(r2, v, (*(Box25 *)&D_002C1260).mn[2]); if ((r2 & 0xf0) == 0xf0) return;
        break;
    }
    D_002BD250[D_002C12C4++] = id;
}
#include "data/data_002C.h"
