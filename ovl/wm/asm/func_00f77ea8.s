/* wm.x func_00f77ea8 (gb func_00f50db0's twin): an endless loop calling func_0024e468(1) with no frame and no $ra save: hand-written assembly. Session 141. */
	.set	noreorder
	.set	noat

	.section	.text.func_00f77ea8,"ax",@progbits
	.globl	func_00f77ea8
	.ent	func_00f77ea8
func_00f77ea8:  /* 0x00F77EA8 */
	.word	0x3C020109  /* 00F77EA8 lui $v0,%hi(D_0108F184) */
	.word	0x3C0400FB  /* 00F77EAC lui $a0,%hi(D_00FB4EBA) */
	.word	0x24030001  /* 00F77EB0 li $v1,1 */
	.word	0xAC40F184  /* 00F77EB4 sw $zero,%lo(D_0108F184)($v0) */
	.word	0xA0834EBA  /* 00F77EB8 sb $v1,%lo(D_00FB4EBA)($a0) */
	.word	0x00000000  /* 00F77EBC nop */
	.word	0x0C09391A  /* 00F77EC0 jal func_0024e468 */
	.word	0x24040001  /* 00F77EC4 li $a0,1 */
	.word	0x1000FFFD  /* 00F77EC8 b .L00F77EC0 */
	.word	0x00000000  /* 00F77ECC nop */
	.end	func_00f77ea8
