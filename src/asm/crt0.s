/* Startup code (crt0, game segment): a frameless tail jump and a syscall before the stack setup, neither of which ee-gcc produces. Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text._exit,"ax",@progbits
	.globl	_exit
	.ent	_exit
_exit:  /* 0x001001C8 */
	.word	0x08000000  /* 001001C8 j func_0025f9a8 */
	.reloc	.-4, R_MIPS_26, func_0025f9a8
	.word	0x0000202D  /* 001001CC move $a0,$zero */
	.end	_exit

	.section	.text.func_001001d0,"ax",@progbits
	.globl	func_001001d0
	.ent	func_001001d0
func_001001d0:  /* 0x001001D0 */
	.word	0x24030023  /* 001001D0 li $v1,35 */
	.word	0x0000000C  /* 001001D4 syscall */
	.globl	func_001001d8
func_001001d8:  /* mid-function entry point */
	.word	0x27BDFFF0  /* 001001D8 addiu $sp,$sp,-16 */
	.word	0xFFBF0000  /* 001001DC sd $ra,0($sp) */
	.word	0x0C000000  /* 001001E0 jal func_00106c10 */
	.reloc	.-4, R_MIPS_26, func_00106c10
	.word	0x00000000  /* 001001E4 nop */
	.word	0xDFBF0000  /* 001001E8 ld $ra,0($sp) */
	.word	0x0000102D  /* 001001EC move $v0,$zero */
	.word	0x03E00008  /* 001001F0 jr $ra */
	.word	0x27BD0010  /* 001001F4 addiu $sp,$sp,16 */
	.end	func_001001d0
