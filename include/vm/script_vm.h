/* The script VM's instruction set (src/vm/vm_ops.c; docs/modules.md).
 *
 * A VM is a VmRec (data/types/vm_rec.h): the script (`code`), its program
 * counter `pc` (in 4-byte instructions), an operand stack `stk` / `sp`,
 * registers `var`, a variable bank `x270` indexed by `x2f0`, and a return
 * stack `ret` / `rsp`.  The interpreter loops (func_001c1d20, func_001c3408,
 * func_001c3770 ...) fetch the opcode with func_001c1ce8 and its 24-bit
 * argument with func_001c1cf8 and call D_0037A198[op](vm, arg).  What the
 * loop in func_001c3408 does with a handler's result: bit 2 advances pc (a
 * handler that sets pc itself returns 1), bit 4 ends the loop, bit 8 leaves
 * the interpreter. */
#ifndef KH1_VM_SCRIPT_VM_H
#define KH1_VM_SCRIPT_VM_H

#include "common.h"
#include "data/types/vm_rec.h"

/* D_0037A198: the 32 handlers, indexed by opcode. */
typedef s32 (*VmOp)(VmRec *vm, s32 arg);

/* Script fetch: instruction `pc` of `code` is 4 bytes, arg (s24) then opcode (s8). */
s32 func_001c1ce8(s8 *code, s32 pc);
s32 func_001c1cf8(s8 *code, s32 pc);

/* Clamp a value to the range of a variable type (0/1 bool, 2 s8, 3 s16, 4 s24,
 * 5 u8, 6 u16, 7 u24). */
s64 func_001c0bf0(s64 x, u32 type);

/* Byte access to save block 2 (func_00232cc0(2)): read / write `size` bytes. */
void func_001c0da0(s32 off, s32 size, void *dst);
void func_001c0e80(s32 off, s32 size, void *src);

/* Jump another VM to `pc` at return level `lvl`. */
s32 func_001c1980(VmRec *vm, s32 lvl, s32 pc);

#endif /* KH1_VM_SCRIPT_VM_H */
