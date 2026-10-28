/* gb.x func_00f50db0: an endless loop calling func_0024e468(1) with no frame and no $ra save (gcc 2.96 always saves $ra around a call): hand-written assembly. Session 141. */
	.set	noreorder
	.set	noat

	.section	.text.func_00f50db0,"ax",@progbits
	.globl	func_00f50db0
	.ent	func_00f50db0
func_00f50db0:  /* 0x00F50DB0 */
	.word	0x3C0200F8  /* 00F50DB0 lui $v0,%hi(D_00F829C4) */
	.word	0x3C0400F7  /* 00F50DB4 lui $a0,%hi(D_00F7073A) */
	.word	0x24030001  /* 00F50DB8 li $v1,1 */
	.word	0xAC4029C4  /* 00F50DBC sw $zero,%lo(D_00F829C4)($v0) */
	.word	0xA083073A  /* 00F50DC0 sb $v1,%lo(D_00F7073A)($a0) */
	.word	0x00000000  /* 00F50DC4 nop */
	.word	0x0C09391A  /* 00F50DC8 jal func_0024e468 */
	.word	0x24040001  /* 00F50DCC li $a0,1 */
	.word	0x1000FFFD  /* 00F50DD0 b .L00F50DC8 */
	.word	0x00000000  /* 00F50DD4 nop */
	.end	func_00f50db0
