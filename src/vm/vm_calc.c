/* Script VM opcode 1, the arithmetic and comparison instruction
 * (0x001cce38-0x001cd238; docs/modules.md "src/vm/vm_calc.c").
 *
 * D_0037A198[1] is func_001cd208: its argument picks one of the 18
 * operations in D_0037A198's sub-table D_003C5898, each of which works on
 * the top of the VM's operand stack (binary ones pop the right operand and
 * replace the left one).  The 18 operations, the table and the dispatcher
 * are contiguous and in that order, apart from the rest of the script VM
 * (src/vm/script_vm.c ends at 0x001c4ed0), so they are their own file. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"

/* An operation of D_003C5898. */
typedef void (*VmCalcOp)(VmRec *vm);

/* 0: a + b */
void func_001cce38(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] += vm->stk[vm->sp + 1];
}

/* 1: a - b */
void func_001cce70(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] -= vm->stk[vm->sp + 1];
}

/* 5: -a */
void func_001ccea8(VmRec *vm) {
    vm->stk[vm->sp] = -vm->stk[vm->sp];
}

/* 2: a * b */
void func_001ccec8(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] *= vm->stk[vm->sp + 1];
}

/* 3: a / b */
void func_001ccf00(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] /= vm->stk[vm->sp + 1];
}

/* 4: a % b */
void func_001ccf40(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] %= vm->stk[vm->sp + 1];
}

/* 6: a == b */
void func_001ccf80(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] == vm->stk[vm->sp + 1];
}

/* 7: a > b */
void func_001ccfb8(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] > vm->stk[vm->sp + 1];
}

/* 8: a >= b */
void func_001ccff0(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] >= vm->stk[vm->sp + 1];
}

/* 9: a < b */
void func_001cd028(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] < vm->stk[vm->sp + 1];
}

/* 10: a <= b */
void func_001cd060(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] <= vm->stk[vm->sp + 1];
}

/* 11: a != b */
void func_001cd098(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] != vm->stk[vm->sp + 1];
}

/* 12: a & b */
void func_001cd0d0(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] & vm->stk[vm->sp + 1];
}

/* 13: a | b */
void func_001cd108(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] | vm->stk[vm->sp + 1];
}

/* 14: a ^ b */
void func_001cd140(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] ^ vm->stk[vm->sp + 1];
}

/* 15: ~a */
void func_001cd178(VmRec *vm) {
    vm->stk[vm->sp] = ~vm->stk[vm->sp];
}

/* 16: a >> b */
void func_001cd198(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] >> vm->stk[vm->sp + 1];
}

/* 17: a << b */
void func_001cd1d0(VmRec *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] << vm->stk[vm->sp + 1];
}

/* The operations by sub-opcode (the order above is the address order). */
VmCalcOp D_003C5898[18] ALIGNED(8) = {
    func_001cce38, func_001cce70, func_001ccec8, func_001ccf00,
    func_001ccf40, func_001ccea8, func_001ccf80, func_001ccfb8,
    func_001ccff0, func_001cd028, func_001cd060, func_001cd098,
    func_001cd0d0, func_001cd108, func_001cd140, func_001cd178,
    func_001cd198, func_001cd1d0,
};

/* op 1: run operation `k` on the operand stack */
s32 func_001cd208(VmRec *vm, s32 k) {
    D_003C5898[k](vm);
    return 2;
}
