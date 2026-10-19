/* 00120cf8 5 LCS, mode hand (strict), same code as session6 draft. New finding: in the original preheader the order is 'li t3,1; move t2,zero; li t0,3' (ours 'li 3; li 1; move t2,zero'): the giv init (t2 = 4i) sits between the two hoisted constants, so the divisor 3 was hoisted out of the outer loop by the second loop pass (after strength reduction emitted the giv inits), not by pass 1 like ours (-dL: 'Insn 566: regno 136 ... halved since already moved moved to 663'). Pass 1 skips a movable whose reg was made by loop optimization (regno >= max_reg_before_loop), so in the original the 3 was probably not an expand-time pseudo. Global-alloc: mii 5 refs/19 (.526) vs const 3 10/62 (.484); duplicated store arms raise both lives (+3 mii / +6 const), never crossing. Tried: div by a local k=3 (8), divisor = final value of the t-loop counter (31), arms/continue shapes (5). */
#include "common.h"
f32 sinf(f32);
f32 cosf(f32);
void func_00267560(f32 *, f32 *, f32);
void func_00120cf8(f32 *axis, f32 m[4][4], f32 angle) {
    f32 t[3][4];
    f32 s[4];
    f32 c;
    s32 i, j;
    for (i = 0; i < 3; i++) {
        m[i][3] = m[3][i] = 0.0f;
    }
    m[3][3] = 1.0f;
    func_00267560(s, axis, sinf(angle));
    c = cosf(angle);
    for (i = 0; i < 3; i++) func_00267560(t[i], axis, axis[i]);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % 3 == 1) v = -v;
                m[i][j] = v;
            }
        }
    }
    c = 1.0f - c;
    for (i = 0; i < 3; i++) func_00267560(t[i], t[i], c);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) m[i][j] += t[i][j];
    }
}
