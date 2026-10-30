/* Round 68 wwm2: score 39 -> 37 at the same size (292 vs 296). The element address now comes from an inline helper, `static inline GG *slot(s32 i) { GG *g = D_00FC1DE0; g += i; return g; }`, called as `g = slot(i++)` in the do-while. The i*416 step is still strength-reduced (the original computes it with shifts each pass). Earlier header below. */
/* Round 67 wwm2: score 74 -> 39 at 292 vs 296 bytes (was 288). The allocator search is written inline as a do-while: `g = D_00FC1DE0; g = &g[i++];`, with the found path, copy loop, call and `return g` inside the loop, as in the original's layout (the found code sits between the test and the loop latch, and `return 0` is after the loop). Setting g twice keeps loop.c from turning g into a pointer giv; the inline/for forms all strength-reduce. Left: the original also leaves i*416 unreduced (sll/addu each pass, base address hoisted into a2), while here the multiply becomes a 416-step register and the base is rematerialised each pass. -fno-strength-reduce does not give that either (75). The nostrict_norcse mode scores 33, but no overlay file uses that mode, so this stays in the default mode. */
/* xs_genie.x func_00f22078: near miss (session 141), score 74. The inner copy loop matches; the original's outer search loop is not strength-reduced (i*416 each pass, i++ before the used test) and every for/do/goto/inline-allocator form tried here strength-reduces it. */
#include "ovl.h"
typedef struct { s32 a, b; void *owner; s32 c[4]; } GE;
typedef struct { s32 used; s32 f4; u8 pad[32]; u8 f40[208]; GE e[5]; GE x; } GG;
extern GG D_00FC1DE0[];
extern GE D_00FC0DA0[];
void func_00f222d0(void *, GE *);
static inline GG *slot(s32 i) { GG *g = D_00FC1DE0; g += i; return g; }
GG *func_00f22078(void) {
    s32 i, j;
    GG *g;
    i = 0;
    do {
        g = slot(i++);
        if (g->used == 0) {
            g->used = 1;
            g->f4 = 0;
            for (j = 0; j < 5; j++) {
                g->e[j] = D_00FC0DA0[j];
                g->e[j].owner = g;
            }
            g->x = D_00FC0DA0[5];
            func_00f222d0(g->f40, g->e);
            return g;
        }
    } while (i < 10);
    return 0;
}
