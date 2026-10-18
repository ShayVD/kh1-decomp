/* 00214a68: LCS 14 words (23 pos), 192 bytes vs 184 (the beqzl exit adds a nop and the reorder), hand/nosi (-fno-sched-interblock), no context. NOT better than w5 8w by count, but the inner loop body is now the original shape: real do{}while(1) inner loop (loop.c moves the lui into the INNER preheader; the outer loop then refuses it because moved_once doubles insn_count), q set twice (`q = &D_00642C74[1];` before the *p test, `q += k;` after it: set in two blocks, so neither the lo_sum nor the add is movable; fill_simple puts the lo_sum into the *p beqz slot). In plain hand mode sched1 interblock speculation lifts the addu above the *p branch (14w too). Left: (1) i/k<<2 swap a1/a2; (2) the i>=48 exit has REG_BR_PROB 5000 (mostly_true_jump=1) so reorg takes k++ from the target (beqzl) where the orig takes p++ from the fall-through; all spellings of the i test give 5000. */
/* 00214a68: LCS 8 words (12 pos, right size), hand, no context (s9 draft 16). New: inner counter through a pointer into the middle of the previous word, `s32 *cnt = &D_00642C74[1];` declared in the if-block (a different symbol expression than the outer D_00642C78[k] stores, so gcse does not share the la; outer k<<2 stays unreduced and the outer la/1/n hoist exactly). Left: (1) loop.c hoists cnt's lui out of the outer loop (lui t5 at entry) and leaves addiu t0,t5 in the inner preheader; orig has lui t0 in the inner preheader and addiu+addu in the inner body; (2) reorg fills the i>=48 exit from its target (beqzl ...; addiu t1) where the orig uses beqz with the fall-through p++ in the slot. A real inner loop (for/while/do) is worse (24-31). */
#include "common.h"
typedef struct { u8 x0[0x44]; u8 x44[48]; } Ch74;
typedef struct { union { Ch74 c[1]; struct { u8 pad[0x48e]; u8 ids[8]; } h; } u; } P48E;
extern P48E *D_00304BE8;
extern u32 D_003E3D68;
extern s32 D_00642C78[];
extern s32 D_00642C74[];
void func_00214a68(void) {
    u32 k;
    s32 i;
    u8 *p;
    s32 *q;
    for (k = 0; k < D_003E3D68; k++) {
        Ch74 *c = &D_00304BE8->u.c[D_00304BE8->u.h.ids[k]];
        D_00642C78[k] = 0;
        i = 0;
        if (c->x44[0]) {
            D_00642C78[k] = 1;
            p = c->x44;
            do {
                i++;
                if (i >= 48) break;
                p++;
                q = &D_00642C74[1];
                if (*p == 0) break;
                q += k; (*q)++;
            } while (1);
        }
    }
}
