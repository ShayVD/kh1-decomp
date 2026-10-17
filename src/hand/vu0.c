/* Game leaf functions that are one VU0 inline-asm block (tools/asm_to_c.py). The arguments are the vectors and matrices the block loads with lqc2; names and types are not known yet. */
#include "common.h"

s32 func_00107ab8(s32 a0, s32 a1) {
    s32 ret;

    __asm__ volatile(
        ".set noreorder\n"
        "move $8, $0\n"
        "li $6, 63\n"
        "lqc2 $vf8, 0(%2)\n"
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 16(%2)\n"
        "vnop\n"
        "vnop\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 32(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 48(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 64(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 80(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 96(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "lqc2 $vf8, 112(%2)\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "vnop\n"
        "cfc2 %0, $vi18\n"
        "andi $3, %0, 0x10\n"
        "vclipw.xyz $vf12xyz, $vf12w\n"
        "and $6, $6, %0\n"
        "addu $8, $8, $3\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi18\n"
        "and $6, $6, %0\n"
        "ori %1, $6, 0x80\n"
        "movz $6, %1, $8\n"
        "li %0, 2\n"
        "andi $3, $6, 0x2f\n"
        "bnez $3, func_00107ab8_00107c3c\n"
        "andi $6, $6, 0x80\n"
        ".set reorder\n"
        "sltiu %0, $6, 1\n"
        "func_00107ab8_00107c3c:\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1)
        : "$3", "$6", "$8", "memory");
    return ret;
}

void func_0010a4d8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    __asm__ volatile(
        ".set noreorder\n"
        "move $11, %5\n"
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf24, 0($11)\n"
        "lqc2 $vf25, 0(%6)\n"
        "vftoi0.xyzw $vf25xyzw, $vf25xyzw\n"
        "func_0010a4d8_0010a4f8:\n"
        "lqc2 $vf8, 0(%2)\n"
        "vadd.xy $vf8xy, $vf24xy, $vf8xy\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf12xyzw, $vf7xyzw, $vf8w\n"
        "vdiv Q, $vf0w, $vf12w\n"
        "lqc2 $vf9, 0(%3)\n"
        "addi %4, %4, -1\n"
        "addi %2, %2, 16\n"
        "addi %3, %3, 16\n"
        "sqc2 $vf25, 16(%0)\n"
        "vwaitq\n"
        "vmulq.xyzw $vf15xyzw, $vf9xyzw, Q\n"
        "vmulq.xyzw $vf12xyzw, $vf12xyzw, Q\n"
        "vftoi4.xyzw $vf13xyzw, $vf12xyzw\n"
        "sqc2 $vf15, 0(%0)\n"
        "sqc2 $vf13, 32(%0)\n"
        "bne $0, %4, func_0010a4d8_0010a4f8\n"
        "addi %0, %0, 48\n"
        ".set reorder\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6)
        : "$11", "memory");
}

void func_001627d0(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf6, 0(%0)\n"
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf6xyz, $vf4xyz, $vf5xyz\n"
        "sqc2 $vf6, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

s32 func_001627e8(s32 a0) {
    s32 ret;

    __asm__ volatile(
        "qmtc2 %1, $vf1\n"
        "vrnext.w $vf2w, R\n"
        "vitof0.x $vf1x, $vf1x\n"
        "vsub.w $vf2w, $vf2w, $vf0w\n"
        "vmulw.x $vf1x, $vf1x, $vf2w\n"
        "vftoi0.x $vf1x, $vf1x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        : "r"(a0)
        : "memory");
    return ret;
}

s32 func_00162808(void) {
    s32 ret;

    __asm__ volatile(
        "cfc2 %0, $vi29\n"
        : "=&r"(ret)
        : 
        : "memory");
    return ret;
}

void func_00162818(void) {
    __asm__ volatile(
        ".set noreorder\n"
        "func_00162818_00162818:\n"
        "bc2f func_00162818_00162840\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "j func_00162818_00162818\n"
        "nop\n"
        ".set reorder\n"
        "nop\n"
        "func_00162818_00162840:\n"
        : 
        : 
        : "memory");
}

void func_00162848(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf8, 0(%2)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf9xyzw, $vf7xyzw, $vf0w\n"
        "sqc2 $vf9, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

void func_00162878(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf8, 0(%2)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddz.xyzw $vf9xyzw, $vf6xyzw, $vf8z\n"
        "sqc2 $vf9, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

f32 func_00162950(s32 a0, s32 a1) {
    f32 ret;

    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vaddw.x $vf5x, $vf5x, $vf5w\n"
        "qmfc2 %0, $vf5\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1)
        : "memory");
    return ret;
}

f32 func_00162a58(s32 a0) {
    f32 ret;

    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf4xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf4x, $vf4x, $vf4y\n"
        "vaddz.x $vf4x, $vf4x, $vf4z\n"
        "vsqrt Q, $vf4x\n"
        "vwaitq\n"
        "vaddq.x $vf4x, $vf0x, Q\n"
        "qmfc2 %0, $vf4\n"
        : "=&r"(ret)
        : "r"(a0)
        : "memory");
    return ret;
}

s32 func_00162a88(s32 a0) {
    s32 ret;

    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf4xyz, $vf4xyz, $vf4xyz\n"
        "vaddz.x $vf4x, $vf4x, $vf4z\n"
        "vsuby.x $vf4x, $vf4x, $vf4y\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi17\n"
        "andi %0, %0, 0x80\n"
        : "=&r"(ret)
        : "r"(a0)
        : "memory");
    return ret;
}

f32 func_00162c20(s32 a0) {
    f32 ret;

    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "cfc2 $8, $vi22\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "mtc1 $8, %0\n"
        "vnop\n"
        "vdiv Q, $vf0w, $vf5x\n"
        "vwaitq\n"
        "vmulq.xyz $vf4xyz, $vf4xyz, Q\n"
        "sqc2 $vf4, 0(%1)\n"
        : "=&f"(ret)
        : "r"(a0)
        : "$8", "memory");
    return ret;
}

void func_00162cd0(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "vcallms 0x0\n"
        "lq $9, 0(%1)\n"
        "lui $8, 0x3f80\n"
        "sq $9, 48(%2)\n"
        "sw $8, 60(%2)\n"
        "qmfc2.i $8, $vf26\n"
        "sqc2 $vf27, 16(%2)\n"
        "sqc2 $vf28, 32(%2)\n"
        "sq $8, 0(%2)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "$8", "$9", "memory");
}

f32 func_00176850(void) {
    f32 ret;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        : 
        : "$8", "memory");
    return ret;
}

f32 func_0019baf8(void) {
    f32 ret;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        : 
        : "$8", "memory");
    return ret;
}

f32 func_0019f100(void) {
    f32 ret;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        : 
        : "$8", "memory");
    return ret;
}

void func_001a9080(s32 a0, s32 a1) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmove.xy $vf1xy, $vf2xy\n"
        "sqc2 $vf31, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1)
        : "memory");
}

void func_001a9098(s32 a0, s32 a1) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmove.xyz $vf1xyz, $vf2xyz\n"
        "sqc2 $vf1, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1)
        : "memory");
}

void func_001a90b0(s32 a0, s32 a1, f32 f0) {
    __asm__ volatile(
        "swc1 %2, 0(%0)\n"
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmulx.xyz $vf2xyz, $vf2xyz, $vf1x\n"
        "sqc2 $vf2, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "f"(f0)
        : "memory");
}

void func_001a90c8(s32 a0, s32 a1, f32 f0) {
    __asm__ volatile(
        "swc1 %2, 0(%0)\n"
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "vmulx.xy $vf2xy, $vf2xy, $vf1x\n"
        "sqc2 $vf2, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "f"(f0)
        : "memory");
}

void func_001a90e0(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 0(%2)\n"
        "lqc2 $vf3, 0(%0)\n"
        "vadd.xy $vf3xy, $vf1xy, $vf2xy\n"
        "sqc2 $vf3, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

void func_001a90f8(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 0(%2)\n"
        "lqc2 $vf3, 0(%0)\n"
        "vsub.xyz $vf3xyz, $vf1xyz, $vf2xyz\n"
        "sqc2 $vf3, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

void func_001a9110(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 0(%2)\n"
        "lqc2 $vf3, 0(%0)\n"
        "vadd.xyz $vf3xyz, $vf1xyz, $vf2xyz\n"
        "sqc2 $vf3, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

void func_001a9128(s32 a0, s32 a1, s32 a2) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 0(%2)\n"
        "lqc2 $vf3, 0(%0)\n"
        "vsub.xy $vf3xy, $vf1xy, $vf2xy\n"
        "sqc2 $vf3, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
}

s32 func_001a9140(s32 a0, s32 a1, s32 a2) {
    s32 ret;

    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%2)\n"
        "lqc2 $vf2, 0(%3)\n"
        "vadd.xy $vf1xy, $vf1xy, $vf2xy\n"
        "vftoi4.xy $vf31xy, $vf1xy\n"
        "vftoi0.zw $vf31zw, $vf1zw\n"
        "lui %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "ori %0, %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "qmtc2 %0, $vf29\n"
        "ctc2 $0, $vi16\n"
        "vsub.xyw $vf0xyw, $vf1xyw, $vf0xyw\n"
        "vsub.xy $vf0xy, $vf29xy, $vf1xy\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi16\n"
        "andi %0, %0, 0xc0\n"
        "beqz %0, func_001a9140_001a91a4\n"
        "nop\n"
        ".set reorder\n"
        "li %0, 0\n"
        "li %0, 0x8000\n"
        "ctc2 %0, $vi1\n"
        "vmfir.w $vf31w, $vi1\n"
        "func_001a9140_001a91a4:\n"
        "sqc2 $vf31, 0(%1)\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
    return ret;
}

s32 func_001a91b0(s32 a0, s32 a1) {
    s32 ret;

    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%2)\n"
        "vftoi4.xy $vf2xy, $vf1xy\n"
        "vftoi0.zw $vf2zw, $vf1zw\n"
        "lui %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "ori %0, %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "qmtc2 %0, $vf29\n"
        "ctc2 $0, $vi16\n"
        "vsub.xyw $vf0xyw, $vf1xyw, $vf0xyw\n"
        "vsub.xy $vf0xy, $vf29xy, $vf1xy\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi16\n"
        "andi %0, %0, 0xc0\n"
        "beqz %0, func_001a91b0_001a920c\n"
        "nop\n"
        ".set reorder\n"
        "li %0, 0\n"
        "li %0, 0x8000\n"
        "ctc2 %0, $vi1\n"
        "vmfir.w $vf2w, $vi1\n"
        "func_001a91b0_001a920c:\n"
        "sqc2 $vf2, 0(%1)\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1)
        : "memory");
    return ret;
}

void func_001a9218(s32 a0, s32 a1) {
    __asm__ volatile(
        "lqc2 $vf1, 0(%1)\n"
        "vmul.xy $vf31xy, $vf1xy, $vf1xy\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vsqrt Q, $vf31x\n"
        "vwaitq\n"
        "vaddq.x $vf31x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf31x\n"
        "vwaitq\n"
        "vmulq.xy $vf31xy, $vf1xy, Q\n"
        "sqc2 $vf31, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1)
        : "memory");
}

s32 func_001a9248(s32 a0, s32 a1, s32 a2) {
    s32 ret;

    __asm__ volatile(
        "lqc2 $vf1, 0(%2)\n"
        "lqc2 $vf2, 16(%2)\n"
        "lqc2 $vf3, 32(%2)\n"
        "lqc2 $vf4, 48(%2)\n"
        "lqc2 $vf5, 0(%3)\n"
        "vmulax.xyzw ACC, $vf1xyzw, $vf5x\n"
        "vmadday.xyzw ACC, $vf2xyzw, $vf5y\n"
        "vmaddaz.xyzw ACC, $vf3xyzw, $vf5z\n"
        "vmaddw.xyzw $vf5xyzw, $vf4xyzw, $vf5w\n"
        "vdiv Q, $vf0w, $vf5w\n"
        "lui %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "ori %0, %0, 0x4580\n"
        "dsll %0, %0, 0x10\n"
        "qmtc2 %0, $vf29\n"
        "vwaitq\n"
        "vmulq.xyz $vf5xyz, $vf5xyz, Q\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "ctc2 $0, $vi16\n"
        "vsub.xyw $vf0xyw, $vf5xyw, $vf0xyw\n"
        "vsub.xy $vf0xy, $vf29xy, $vf5xy\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi16\n"
        "andi %0, %0, 0xc0\n"
        "sqc2 $vf5, 0(%1)\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1), "r"(a2)
        : "memory");
    return ret;
}

void func_001a92c8(s32 a0, s32 a1) {
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vdiv Q, $vf0w, $vf10w\n"
        "vwaitq\n"
        "vmulq.xyz $vf9xyz, $vf10xyz, Q\n"
        "vftoi4.xy $vf9xy, $vf9xy\n"
        "vftoi0.z $vf9z, $vf9z\n"
        "vftoi0.w $vf9w, $vf10w\n"
        "sqc2 $vf9, 0(%0)\n"
        : 
        : "r"(a0), "r"(a1)
        : "memory");
}

f32 func_001a9388(s32 a0) {
    f32 ret;

    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xy $vf10xy, $vf10xy, $vf10xy\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vsqrt Q, $vf10y\n"
        "vwaitq\n"
        "cfc2 %0, $vi22\n"
        : "=&r"(ret)
        : "r"(a0)
        : "memory");
    return ret;
}

f32 func_001aae48(f32 f0) {
    f32 ret;

    __asm__ volatile(
        "mfc1 $2, %1\n"
        "lui $3, 0x4000\n"
        "lui $4, 0x4040\n"
        "lui $5, 0x3ff1\n"
        "ori $5, $5, 0x9120\n"
        "vrnext.xyzw $vf31xyzw, R\n"
        "qmtc2 $2, $vf30\n"
        "qmtc2 $3, $vf29\n"
        "qmtc2 $4, $vf28\n"
        "qmtc2 $5, $vf27\n"
        "vmul.x $vf31x, $vf31x, $vf29x\n"
        "vsubx.w $vf25w, $vf31w, $vf27x\n"
        "vsub.x $vf31x, $vf31x, $vf28x\n"
        "vmul.x $vf31x, $vf31x, $vf30x\n"
        "qmfc2 $2, $vf31\n"
        "mtc1 $2, %0\n"
        "vrinit R, $vf25w\n"
        : "=&f"(ret)
        : "f"(f0)
        : "$3", "$4", "$5", "memory");
    return ret;
}

f32 func_001aae90(f32 f0) {
    f32 ret;

    __asm__ volatile(
        "mfc1 $2, %1\n"
        "lui $3, 0x3f80\n"
        "lui $5, 0x3ff1\n"
        "ori $5, $5, 0x9120\n"
        "vrnext.xyzw $vf31xyzw, R\n"
        "qmtc2 $2, $vf30\n"
        "qmtc2 $3, $vf29\n"
        "qmtc2 $5, $vf27\n"
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf29xyzw\n"
        "vsubx.w $vf25w, $vf31w, $vf27x\n"
        "vmul.x $vf31x, $vf31x, $vf30x\n"
        "qmfc2 $2, $vf31\n"
        "mtc1 $2, %0\n"
        "vrinit R, $vf25w\n"
        : "=&f"(ret)
        : "f"(f0)
        : "$3", "$5", "memory");
    return ret;
}

s32 func_001b99b8(s32 a0, s32 a1, s32 a2) {
    s32 ret;

    __asm__ volatile(
        "move $12, %1\n"
        "move $11, %2\n"
        "move $10, %3\n"
        "lui %0, 0xbf80\n"
        "qmtc2 %0, $vf19\n"
        "lqc2 $vf28, 0($11)\n"
        "lqc2 $vf29, 16($11)\n"
        "lqc2 $vf30, 32($11)\n"
        "lqc2 $vf31, 48($11)\n"
        "vmulx.xyz $vf28xyz, $vf28xyz, $vf19x\n"
        "vmulx.xyz $vf29xyz, $vf29xyz, $vf19x\n"
        "vmulx.xyz $vf30xyz, $vf30xyz, $vf19x\n"
        "vmulx.xyz $vf31xyz, $vf31xyz, $vf19x\n"
        "vmul.xyz $vf18xyz, $vf28xyz, $vf28xyz\n"
        "vaddy.x $vf18x, $vf18x, $vf18y\n"
        "vaddz.x $vf18x, $vf18x, $vf18z\n"
        "vsqrt Q, $vf18x\n"
        "vwaitq\n"
        "vaddq.x $vf18x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf18x\n"
        "vwaitq\n"
        "vmulq.xyz $vf28xyz, $vf28xyz, Q\n"
        "vmul.xyz $vf18xyz, $vf29xyz, $vf29xyz\n"
        "vaddy.x $vf18x, $vf18x, $vf18y\n"
        "vaddz.x $vf18x, $vf18x, $vf18z\n"
        "vsqrt Q, $vf18x\n"
        "vwaitq\n"
        "vaddq.x $vf18x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf18x\n"
        "vwaitq\n"
        "vmulq.xyz $vf29xyz, $vf29xyz, Q\n"
        "vmul.xyz $vf18xyz, $vf30xyz, $vf30xyz\n"
        "vaddy.x $vf18x, $vf18x, $vf18y\n"
        "vaddz.x $vf18x, $vf18x, $vf18z\n"
        "vsqrt Q, $vf18x\n"
        "vwaitq\n"
        "vaddq.x $vf18x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf18x\n"
        "vwaitq\n"
        "vmulq.xyz $vf30xyz, $vf30xyz, Q\n"
        "vmul.xyz $vf18xyz, $vf31xyz, $vf31xyz\n"
        "vaddy.x $vf18x, $vf18x, $vf18y\n"
        "vaddz.x $vf18x, $vf18x, $vf18z\n"
        "vsqrt Q, $vf18x\n"
        "vwaitq\n"
        "vaddq.x $vf18x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf18x\n"
        "vwaitq\n"
        "vmulq.xyz $vf31xyz, $vf31xyz, Q\n"
        "qmtc2 $0, $vf18\n"
        "vmulw.xyz $vf28xyz, $vf28xyz, $vf28w\n"
        "vmulw.xyz $vf29xyz, $vf29xyz, $vf29w\n"
        "vmulw.xyz $vf30xyz, $vf30xyz, $vf30w\n"
        "vmulw.xyz $vf31xyz, $vf31xyz, $vf31w\n"
        "vmove.w $vf28w, $vf18w\n"
        "vmove.w $vf29w, $vf18w\n"
        "vmove.w $vf30w, $vf18w\n"
        "vmove.w $vf31w, $vf18w\n"
        "qmfc2 %0, $vf28\n"
        "qmfc2 $3, $vf29\n"
        "qmfc2 %1, $vf30\n"
        "qmfc2 %2, $vf31\n"
        "pextlw %3, $3, %0\n"
        "pextuw $7, $3, %0\n"
        "pextlw $8, %2, %1\n"
        "pextuw $9, %2, %1\n"
        "pcpyld %0, $8, %3\n"
        "pcpyud $3, %3, $8\n"
        "pcpyld %1, $9, $7\n"
        "pcpyud %2, $7, $9\n"
        "qmtc2 %0, $vf28\n"
        "qmtc2 $3, $vf29\n"
        "qmtc2 %1, $vf30\n"
        "qmtc2 %2, $vf31\n"
        "lqc2 $vf24, 0($10)\n"
        "lqc2 $vf25, 16($10)\n"
        "lqc2 $vf26, 32($10)\n"
        "vmove.w $vf24w, $vf18w\n"
        "vmove.w $vf25w, $vf18w\n"
        "vmove.w $vf26w, $vf18w\n"
        "vmulax.xyzw ACC, $vf28xyzw, $vf24x\n"
        "vmadday.xyzw ACC, $vf29xyzw, $vf24y\n"
        "vmaddz.xyzw $vf20xyzw, $vf30xyzw, $vf24z\n"
        "vmulax.xyzw ACC, $vf28xyzw, $vf25x\n"
        "vmadday.xyzw ACC, $vf29xyzw, $vf25y\n"
        "vmaddz.xyzw $vf21xyzw, $vf30xyzw, $vf25z\n"
        "vmulax.xyzw ACC, $vf28xyzw, $vf26x\n"
        "vmadday.xyzw ACC, $vf29xyzw, $vf26y\n"
        "vmaddz.xyzw $vf22xyzw, $vf30xyzw, $vf26z\n"
        "sqc2 $vf20, 0($12)\n"
        "sqc2 $vf21, 16($12)\n"
        "sqc2 $vf22, 32($12)\n"
        "sqc2 $vf31, 48($12)\n"
        : "=&r"(ret)
        : "r"(a0), "r"(a1), "r"(a2)
        : "$3", "$7", "$8", "$9", "$10", "$11", "$12", "memory");
    return ret;
}
