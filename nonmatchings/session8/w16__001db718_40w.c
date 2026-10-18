/* func_001db718: 40w by LCS, right size (368), mode hand. Was 75 (s6 draft, fixed to compile). Shape: Sub with sp at 0x17c (w6's VM), goto loops (no loop.c motion: D_00304BE8 and stk[sp] reloaded per iteration), byte arrays as true struct arrays indexed [j + 0x590] / e->x[j + 0x40] (keeps j+K as a PRE'd index), top s->stk[i - 1] with i = vm->s.sp, loops vm->s.stk via vm->s.sp (= PRE copy 'move t2,t3' of the sp load), else s->sp (stk[sp-1] reloaded like the orig). Left: t2/t3 swapped (copy should get t2), else should index via the copy instead of reloading s->sp, loop 1 tail (orig: label after the D load with an alignment nop, bnezl back with D reload in the slot = real rotated loop + PRE edge insert), loop 2 'move v0,v1' before sb, v0/v1 swaps. */
#include "common.h"
typedef struct { void *obj; u8 pad4[0x178]; s32 sp; s32 stk[100]; } Sub;
typedef struct { s32 x0; Sub s; } VM;
typedef struct { u8 x[0x74]; } Ch;
typedef struct { u8 pad0[4]; Ch ch[12]; } SaveA;
typedef struct { u8 pad0[9]; u8 arr[0x700]; } SaveB;
extern SaveA *D_00304BE8;
#define SB ((SaveB *)D_00304BE8)
s32 func_001db718(VM *vm) {
    Sub *s = &vm->s;
    s32 i = vm->s.sp;
    s32 j;
    u8 b;
    if (s->stk[i - 1] == 11) {
        j = 0;
        if (SB->arr[j + 0x590] & 0x7f) {
        loop1:
            b = SB->arr[j + 0x590];
            if ((b & 0x7f) == s->stk[vm->s.sp] && (b & 0x80)) {
                SB->arr[j + 0x590] = b & 0x7f;
                goto end;
            }
            j++;
            if (j < 48 && (SB->arr[j + 0x590] & 0x7f)) goto loop1;
        }
    } else {
        Ch *e = &D_00304BE8->ch[s->stk[s->sp - 1]];
        j = 0;
        if (e->x[j + 0x40] & 0x7f) {
        loop2:
            b = e->x[j + 0x40];
            if ((b & 0x7f) == s->stk[vm->s.sp] && (b & 0x80)) {
                e->x[j + 0x40] = b & 0x7f;
                goto end;
            }
            j++;
            if (j < 48 && (e->x[j + 0x40] & 0x7f)) goto loop2;
        }
    }
end:
    vm->s.sp -= 2;
    return 2;
}
