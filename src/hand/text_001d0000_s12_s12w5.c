#include "common.h"

/* func_001db718: script op, clears the flag bit (0x80) of the first entry whose 7-bit id
 * equals the operand on the VM stack, in one of two 48-byte tables. Natural shape (s12w5):
 * - `for (;;)` with the exits at the bottom: expand_end_loop rotates it (the `!X` break is the
 *   only exit in its 30-insn window), the leftover `jump start` block takes gcse's PRE insertion
 *   of j+0x590 / j+0x40, so loop.c calls the loop phony and hoists nothing (stk[sp], D address).
 * - the cleared value as `(u8)(b << 1) >> 1`: a separate pseudo that combine turns into a copy
 *   of the compare value, which makes `b & 0x7f` block-local (4 qtys: qsort order in local-alloc;
 *   with 3 qtys local-alloc's hand-sort gives the D chain v0) and gives loop 2 its `move v0,v1`. */
typedef struct { void *obj; u8 pad4[0x178]; s32 sp; s32 stk[100]; } Sub;
typedef struct { s32 x0; Sub s; } VM;
typedef struct { u8 x[0x74]; } Ch;
typedef struct { u8 pad0[4]; Ch ch[12]; } SaveA;
typedef struct { u8 pad0[9]; u8 arr[0x700]; } SaveB;
#include "data/pieces/D_00304BE8.h"
#define SB ((SaveB *)((SaveA *)D_00304BE8))

s32 func_001db718(VM *vm) {
    Sub *s = &vm->s;
    s32 j;
    u8 b;

    if (s->stk[vm->s.sp - 1] == 11) {
        j = 0;
        if (SB->arr[j + 0x590] & 0x7f) {
            for (;;) {
                b = SB->arr[j + 0x590];
                if ((b & 0x7f) == s->stk[vm->s.sp] && (b & 0x80)) {
                    SB->arr[j + 0x590] = (u8)(b << 1) >> 1;
                    goto end;
                }
                if (++j >= 48) goto end;
                if (!(SB->arr[j + 0x590] & 0x7f)) break;
            }
        }
    } else {
        Ch *e = &((SaveA *)D_00304BE8)->ch[s->stk[vm->s.sp - 1]];
        j = 0;
        if (e->x[j + 0x40] & 0x7f) {
            for (;;) {
                b = e->x[j + 0x40];
                if ((b & 0x7f) == s->stk[vm->s.sp] && (b & 0x80)) {
                    e->x[j + 0x40] = (u8)(b << 1) >> 1;
                    goto end;
                }
                if (++j >= 48) goto end;
                if (!(e->x[j + 0x40] & 0x7f)) break;
            }
        }
    }
end:
    vm->s.sp -= 2;
    return 2;
}
