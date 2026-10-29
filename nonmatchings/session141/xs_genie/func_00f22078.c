/* xs_genie.x func_00f22078: near miss (session 141), score 74. The inner copy loop matches; the original's outer search loop is not strength-reduced (i*416 each pass, i++ before the used test) and every for/do/goto/inline-allocator form tried here strength-reduces it. */
#include "ovl.h"
typedef struct { s32 a, b; void *owner; s32 c[4]; } GE;
typedef struct { s32 used; s32 f4; u8 pad[32]; u8 f40[208]; GE e[5]; GE x; } GG;
extern GG D_00FC1DE0[];
extern GE D_00FC0DA0[];
void func_00f222d0(void *, GE *);
static inline GG *alloc(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_00FC1DE0[i].used == 0) {
            D_00FC1DE0[i].used = 1;
            return &D_00FC1DE0[i];
        }
    }
    return 0;
}
GG *func_00f22078(void) {
    s32 j;
    GG *g = alloc();
    if (g) {
    g->f4 = 0;
    for (j = 0; j < 5; j++) {
        g->e[j] = D_00FC0DA0[j];
        g->e[j].owner = g;
    }
    g->x = D_00FC0DA0[5];
    func_00f222d0(g->f40, g->e);
    }
    return g;
}
