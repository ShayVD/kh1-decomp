/* func_00125240: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_00125240,"ax",@progbits
	.globl	func_00125240
	.ent	func_00125240
func_00125240:  /* 0x00125240 */
	.word	0x3C020000  /* 00125240 lui $v0,%hi(D_002E2780) */
	.reloc	.-4, R_MIPS_HI16, D_002E2780
	.word	0x27BDFFF0  /* 00125244 addiu $sp,$sp,-16 */
	.word	0x24420000  /* 00125248 addiu $v0,$v0,%lo(D_002E2780) */
	.reloc	.-4, R_MIPS_LO16, D_002E2780
	.word	0xFFBF0000  /* 0012524C sd $ra,0($sp) */
	.word	0xAC400000  /* 00125250 sw $zero,0($v0) */
	.word	0x3C030000  /* 00125254 lui $v1,%hi(D_002E2790) */
	.reloc	.-4, R_MIPS_HI16, D_002E2790
	.word	0x3C013F80  /* 00125258 lui $at,0x3f80 */
	.word	0x44811800  /* 0012525C mtc1 $at,$f3 */
	.word	0x24630000  /* 00125260 addiu $v1,$v1,%lo(D_002E2790) */
	.reloc	.-4, R_MIPS_LO16, D_002E2790
	.word	0xC4410000  /* 00125264 lwc1 $f1,0($v0) */
	.word	0x3C040000  /* 00125268 lui $a0,%hi(D_002E27A4) */
	.reloc	.-4, R_MIPS_HI16, D_002E27A4
	.word	0x3C01C61C  /* 0012526C lui $at,0xc61c */
	.word	0x34214000  /* 00125270 ori $at,$at,0x4000 */
	.word	0x44811000  /* 00125274 mtc1 $at,$f2 */
	.word	0x3C050000  /* 00125278 lui $a1,%hi(D_004F77E0) */
	.reloc	.-4, R_MIPS_HI16, D_004F77E0
	.word	0x3C01461C  /* 0012527C lui $at,0x461c */
	.word	0x34214000  /* 00125280 ori $at,$at,0x4000 */
	.word	0x44810000  /* 00125284 mtc1 $at,$f0 */
	.word	0xE463000C  /* 00125288 swc1 $f3,12($v1) */
	.word	0x3C014254  /* 0012528C lui $at,0x4254 */
	.word	0x44816000  /* 00125290 mtc1 $at,$f12 */
	.word	0xE4810000  /* 00125294 swc1 $f1,%lo(D_002E27A4)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_002E27A4
	.word	0xE4420004  /* 00125298 swc1 $f2,4($v0) */
	.word	0xE4400008  /* 0012529C swc1 $f0,8($v0) */
	.word	0xE4A10000  /* 001252A0 swc1 $f1,%lo(D_004F77E0)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_004F77E0
	.word	0xE443000C  /* 001252A4 swc1 $f3,12($v0) */
	.word	0xE4610000  /* 001252A8 swc1 $f1,0($v1) */
	.word	0xE4610004  /* 001252AC swc1 $f1,4($v1) */
	.word	0x0C000000  /* 001252B0 jal func_00124c68 */
	.reloc	.-4, R_MIPS_26, func_00124c68
	.word	0xE4610008  /* 001252B4 swc1 $f1,8($v1) */
	.word	0x0C000000  /* 001252B8 jal func_00125000 */
	.reloc	.-4, R_MIPS_26, func_00125000
	.word	0x00000000  /* 001252BC nop */
	.word	0x3C050000  /* 001252C0 lui $a1,%hi(func_00125000) */
	.reloc	.-4, R_MIPS_HI16, func_00125000
	.word	0x3C040001  /* 001252C4 lui $a0,0x1 */
	.word	0x24A50000  /* 001252C8 addiu $a1,$a1,%lo(func_00125000) */
	.reloc	.-4, R_MIPS_LO16, func_00125000
	.word	0x0C000000  /* 001252CC jal func_0011ef10 */
	.reloc	.-4, R_MIPS_26, func_0011ef10
	.word	0x3484ADB0  /* 001252D0 ori $a0,$a0,0xadb0 */
	.word	0x3C050000  /* 001252D4 lui $a1,%hi(func_001251a0) */
	.reloc	.-4, R_MIPS_HI16, func_001251a0
	.word	0x3C040002  /* 001252D8 lui $a0,0x2 */
	.word	0x24A50000  /* 001252DC addiu $a1,$a1,%lo(func_001251a0) */
	.reloc	.-4, R_MIPS_LO16, func_001251a0
	.word	0x0C000000  /* 001252E0 jal func_0011ef10 */
	.reloc	.-4, R_MIPS_26, func_0011ef10
	.word	0x34840F58  /* 001252E4 ori $a0,$a0,0xf58 */
	.word	0xDFBF0000  /* 001252E8 ld $ra,0($sp) */
	.word	0x08000000  /* 001252EC j func_0017f510 */
	.reloc	.-4, R_MIPS_26, func_0017f510
	.word	0x27BD0010  /* 001252F0 addiu $sp,$sp,16 */
	.end	func_00125240
