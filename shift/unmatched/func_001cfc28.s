/* func_001cfc28: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001cfc28,"ax",@progbits
	.globl	func_001cfc28
	.ent	func_001cfc28
func_001cfc28:  /* 0x001CFC28 */
	.word	0x27BDFFC0  /* 001CFC28 addiu $sp,$sp,-64 */
	.word	0xFFB00020  /* 001CFC2C sd $s0,32($sp) */
	.word	0x0080802D  /* 001CFC30 move $s0,$a0 */
	.word	0xFFB10028  /* 001CFC34 sd $s1,40($sp) */
	.word	0x26030004  /* 001CFC38 addiu $v1,$s0,4 */
	.word	0xFFB20030  /* 001CFC3C sd $s2,48($sp) */
	.word	0xFFBF0038  /* 001CFC40 sd $ra,56($sp) */
	.word	0x8E020180  /* 001CFC44 lw $v0,384($s0) */
	.word	0xDE040328  /* 001CFC48 ld $a0,808($s0) */
	.word	0x00021080  /* 001CFC4C sll $v0,$v0,0x2 */
	.word	0x00433021  /* 001CFC50 addu $a2,$v0,$v1 */
	.word	0x000426F8  /* 001CFC54 dsll $a0,$a0,0x1b */
	.word	0x0004203F  /* 001CFC58 dsra32 $a0,$a0,0x0 */
	.word	0x00C0382D  /* 001CFC5C move $a3,$a2 */
	.word	0x8CC50178  /* 001CFC60 lw $a1,376($a2) */
	.word	0x00E0102D  /* 001CFC64 move $v0,$a3 */
	.word	0x30840001  /* 001CFC68 andi $a0,$a0,0x1 */
	.word	0x8C52017C  /* 001CFC6C lw $s2,380($v0) */
	.word	0x0C000000  /* 001CFC70 jal func_001e98d0 */
	.reloc	.-4, R_MIPS_26, func_001e98d0
	.word	0x8CF10180  /* 001CFC74 lw $s1,384($a3) */
	.word	0x0040182D  /* 001CFC78 move $v1,$v0 */
	.word	0x14600004  /* 001CFC7C bnez $v1,.L001CFC90 */
	.word	0x24020002  /* 001CFC80 li $v0,2 */
	.word	0x10000022  /* 001CFC84 b .L001CFD10 */
	.word	0x8E030180  /* 001CFC88 lw $v1,384($s0) */
	.word	0x00000000  /* 001CFC8C nop */
	.word	0x8C620004  /* 001CFC90 lw $v0,4($v1) */
	.word	0x1040001C  /* 001CFC94 beqz $v0,.L001CFD08 */
	.word	0x2405001D  /* 001CFC98 li $a1,29 */
	.word	0x8C420004  /* 001CFC9C lw $v0,4($v0) */
	.word	0xAFA20004  /* 001CFCA0 sw $v0,4($sp) */
	.word	0x44910000  /* 001CFCA4 mtc1 $s1,$f0 */
	.word	0x46800020  /* 001CFCA8 cvt.s.w $f0,$f0 */
	.word	0xA3A50000  /* 001CFCAC sb $a1,0($sp) */
	.word	0x0012183C  /* 001CFCB0 dsll32 $v1,$s2,0x0 */
	.word	0x3C0200FF  /* 001CFCB4 lui $v0,0xff */
	.word	0x3442FFFF  /* 001CFCB8 ori $v0,$v0,0xffff */
	.word	0x0003183E  /* 001CFCBC dsrl32 $v1,$v1,0x0 */
	.word	0x00621824  /* 001CFCC0 and $v1,$v1,$v0 */
	.word	0xDFA20000  /* 001CFCC4 ld $v0,0($sp) */
	.word	0x46000000  /* 001CFCC8 add.s $f0,$f0,$f0 */
	.word	0x2406FFFF  /* 001CFCCC li $a2,-1 */
	.word	0x0006303C  /* 001CFCD0 dsll32 $a2,$a2,0x0 */
	.word	0x34C600FF  /* 001CFCD4 ori $a2,$a2,0xff */
	.word	0x00031A38  /* 001CFCD8 dsll $v1,$v1,0x8 */
	.word	0x3C013F80  /* 001CFCDC lui $at,0x3f80 */
	.word	0x44810800  /* 001CFCE0 mtc1 $at,$f1 */
	.word	0x00461024  /* 001CFCE4 and $v0,$v0,$a2 */
	.word	0x03A0202D  /* 001CFCE8 move $a0,$sp */
	.word	0x00431025  /* 001CFCEC or $v0,$v0,$v1 */
	.word	0xAFA00014  /* 001CFCF0 sw $zero,20($sp) */
	.word	0xAFA00018  /* 001CFCF4 sw $zero,24($sp) */
	.word	0xE7A1001C  /* 001CFCF8 swc1 $f1,28($sp) */
	.word	0xE7A00010  /* 001CFCFC swc1 $f0,16($sp) */
	.word	0x0C000000  /* 001CFD00 jal func_001c4640 */
	.reloc	.-4, R_MIPS_26, func_001c4640
	.word	0xFFA20000  /* 001CFD04 sd $v0,0($sp) */
	.word	0x8E030180  /* 001CFD08 lw $v1,384($s0) */
	.word	0x24020002  /* 001CFD0C li $v0,2 */
	.word	0x2463FFFD  /* 001CFD10 addiu $v1,$v1,-3 */
	.word	0xAE030180  /* 001CFD14 sw $v1,384($s0) */
	.word	0xDFB00020  /* 001CFD18 ld $s0,32($sp) */
	.word	0xDFB10028  /* 001CFD1C ld $s1,40($sp) */
	.word	0xDFB20030  /* 001CFD20 ld $s2,48($sp) */
	.word	0xDFBF0038  /* 001CFD24 ld $ra,56($sp) */
	.word	0x03E00008  /* 001CFD28 jr $ra */
	.word	0x27BD0040  /* 001CFD2C addiu $sp,$sp,64 */
	.end	func_001cfc28
