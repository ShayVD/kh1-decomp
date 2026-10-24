/* SCE libkernl / libvu0 hand-written assembly (docs/sdk.md Session 6): func_00260738 cache line loop + sync, func_002607e4 a lone jr ra (addr%8==4, so a .s file), func_00265190 MMI strncpy, sceGsResetPath VU0 cfc2/ctc2, func_00260b00 (t9 live across calls). Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.func_00260738,"ax",@progbits
	.globl	func_00260738
	.ent	func_00260738
func_00260738:  /* 0x00260738 */
	.word	0x3C19FFFF  /* 00260738 lui $t9,0xffff */
	.word	0x3739FFC0  /* 0026073C ori $t9,$t9,0xffc0 */
	.word	0x18A00026  /* 00260740 blez $a1,.L002607DC */
	.word	0x00855021  /* 00260744 addu $t2,$a0,$a1 */
	.word	0x00994024  /* 00260748 and $t0,$a0,$t9 */
	.word	0x254AFFFF  /* 0026074C addiu $t2,$t2,-1 */
	.word	0x01594824  /* 00260750 and $t1,$t2,$t9 */
	.word	0x01285023  /* 00260754 subu $t2,$t1,$t0 */
	.word	0x000A5982  /* 00260758 srl $t3,$t2,0x6 */
	.word	0x256B0001  /* 0026075C addiu $t3,$t3,1 */
	.word	0x31690007  /* 00260760 andi $t1,$t3,0x7 */
	.word	0x11200008  /* 00260764 beqz $t1,.L00260788 */
	.word	0x000B50C2  /* 00260768 srl $t2,$t3,0x3 */
	.word	0x0000000F  /* 0026076C sync */
	.word	0xBD180000  /* 00260770 cache 0x18,0($t0) */
	.word	0x0000000F  /* 00260774 sync */
	.word	0x2529FFFF  /* 00260778 addiu $t1,$t1,-1 */
	.word	0x00000000  /* 0026077C nop */
	.word	0x1D20FFFA  /* 00260780 bgtz $t1,.L0026076C */
	.word	0x25080040  /* 00260784 addiu $t0,$t0,64 */
	.word	0x11400014  /* 00260788 beqz $t2,.L002607DC */
	.word	0x254AFFFF  /* 0026078C addiu $t2,$t2,-1 */
	.word	0x0000000F  /* 00260790 sync */
	.word	0xBD180000  /* 00260794 cache 0x18,0($t0) */
	.word	0x0000000F  /* 00260798 sync */
	.word	0xBD180040  /* 0026079C cache 0x18,64($t0) */
	.word	0x0000000F  /* 002607A0 sync */
	.word	0xBD180080  /* 002607A4 cache 0x18,128($t0) */
	.word	0x0000000F  /* 002607A8 sync */
	.word	0xBD1800C0  /* 002607AC cache 0x18,192($t0) */
	.word	0x0000000F  /* 002607B0 sync */
	.word	0xBD180100  /* 002607B4 cache 0x18,256($t0) */
	.word	0x0000000F  /* 002607B8 sync */
	.word	0xBD180140  /* 002607BC cache 0x18,320($t0) */
	.word	0x0000000F  /* 002607C0 sync */
	.word	0xBD180180  /* 002607C4 cache 0x18,384($t0) */
	.word	0x0000000F  /* 002607C8 sync */
	.word	0xBD1801C0  /* 002607CC cache 0x18,448($t0) */
	.word	0x0000000F  /* 002607D0 sync */
	.word	0x1D40FFED  /* 002607D4 bgtz $t2,.L0026078C */
	.word	0x25080200  /* 002607D8 addiu $t0,$t0,512 */
	.word	0x03E00008  /* 002607DC jr $ra */
	.word	0x00000000  /* 002607E0 nop */
	.end	func_00260738

	.section	.text.func_002607e4,"ax",@progbits
	.globl	func_002607e4
	.ent	func_002607e4
func_002607e4:  /* 0x002607E4 */
	.word	0x03E00008  /* 002607E4 jr $ra */
	.end	func_002607e4

	.section	.text.func_00265190,"ax",@progbits
	.globl	func_00265190
	.ent	func_00265190
func_00265190:  /* 0x00265190 */
	.word	0x0080402D  /* 00265190 move $t0,$a0 */
	.word	0x00A43825  /* 00265194 or $a3,$a1,$a0 */
	.word	0x240A0010  /* 00265198 li $t2,16 */
	.word	0x30E20007  /* 0026519C andi $v0,$a3,0x7 */
	.word	0x24090008  /* 002651A0 li $t1,8 */
	.word	0x14400054  /* 002651A4 bnez $v0,.L002652F8 */
	.word	0x30E2000F  /* 002651A8 andi $v0,$a3,0xf */
	.word	0x0142480A  /* 002651AC movz $t1,$t2,$v0 */
	.word	0x1440002C  /* 002651B0 bnez $v0,.L00265264 */
	.word	0x00C9102B  /* 002651B4 sltu $v0,$a2,$t1 */
	.word	0x1440004F  /* 002651B8 bnez $v0,.L002652F8 */
	.word	0x00000000  /* 002651BC nop */
	.word	0x3C070101  /* 002651C0 lui $a3,0x101 */
	.word	0x34E70101  /* 002651C4 ori $a3,$a3,0x101 */
	.word	0x00073C38  /* 002651C8 dsll $a3,$a3,0x10 */
	.word	0x34E70101  /* 002651CC ori $a3,$a3,0x101 */
	.word	0x00073C38  /* 002651D0 dsll $a3,$a3,0x10 */
	.word	0x34E70101  /* 002651D4 ori $a3,$a3,0x101 */
	.word	0x78A30000  /* 002651D8 lq $v1,0($a1) */
	.word	0x70E74B89  /* 002651DC pcpyld $t1,$a3,$a3 */
	.word	0x70031CE9  /* 002651E0 pnor $v1,$zero,$v1 */
	.word	0x3C078080  /* 002651E4 lui $a3,0x8080 */
	.word	0x34E78080  /* 002651E8 ori $a3,$a3,0x8080 */
	.word	0x00073C38  /* 002651EC dsll $a3,$a3,0x10 */
	.word	0x34E78080  /* 002651F0 ori $a3,$a3,0x8080 */
	.word	0x00073C38  /* 002651F4 dsll $a3,$a3,0x10 */
	.word	0x34E78080  /* 002651F8 ori $a3,$a3,0x8080 */
	.word	0x70691248  /* 002651FC psubb $v0,$v1,$t1 */
	.word	0x70E75389  /* 00265200 pcpyld $t2,$a3,$a3 */
	.word	0x70431489  /* 00265204 pand $v0,$v0,$v1 */
	.word	0x704A1489  /* 00265208 pand $v0,$v0,$t2 */
	.word	0x70441BA9  /* 0026520C pcpyud $v1,$v0,$a0 */
	.word	0x00431825  /* 00265210 or $v1,$v0,$v1 */
	.word	0x14600037  /* 00265214 bnez $v1,.L002652F4 */
	.word	0x0100382D  /* 00265218 move $a3,$t0 */
	.word	0x78A30000  /* 0026521C lq $v1,0($a1) */
	.word	0x24C6FFF0  /* 00265220 addiu $a2,$a2,-16 */
	.word	0x24A50010  /* 00265224 addiu $a1,$a1,16 */
	.word	0x2CC20010  /* 00265228 sltiu $v0,$a2,16 */
	.word	0x7CE30000  /* 0026522C sq $v1,0($a3) */
	.word	0x14400030  /* 00265230 bnez $v0,.L002652F4 */
	.word	0x24E70010  /* 00265234 addiu $a3,$a3,16 */
	.word	0x78A20000  /* 00265238 lq $v0,0($a1) */
	.word	0x70021CE9  /* 0026523C pnor $v1,$zero,$v0 */
	.word	0x70491248  /* 00265240 psubb $v0,$v0,$t1 */
	.word	0x70431489  /* 00265244 pand $v0,$v0,$v1 */
	.word	0x704A1489  /* 00265248 pand $v0,$v0,$t2 */
	.word	0x70441BA9  /* 0026524C pcpyud $v1,$v0,$a0 */
	.word	0x00431025  /* 00265250 or $v0,$v0,$v1 */
	.word	0x5040001A  /* 00265254 beqzl $v0,.L002652C0 */
	.word	0x78A30000  /* 00265258 lq $v1,0($a1) */
	.word	0x10000026  /* 0026525C b .L002652F8 */
	.word	0x00E0202D  /* 00265260 move $a0,$a3 */
	.word	0x14400024  /* 00265264 bnez $v0,.L002652F8 */
	.word	0x00000000  /* 00265268 nop */
	.word	0xDCA30000  /* 0026526C ld $v1,0($a1) */
	.word	0x3C090101  /* 00265270 lui $t1,0x101 */
	.word	0x35290101  /* 00265274 ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 00265278 dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 0026527C ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 00265280 dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 00265284 ori $t1,$t1,0x101 */
	.word	0x3C0A8080  /* 00265288 lui $t2,0x8080 */
	.word	0x354A8080  /* 0026528C ori $t2,$t2,0x8080 */
	.word	0x000A5438  /* 00265290 dsll $t2,$t2,0x10 */
	.word	0x354A8080  /* 00265294 ori $t2,$t2,0x8080 */
	.word	0x000A5438  /* 00265298 dsll $t2,$t2,0x10 */
	.word	0x354A8080  /* 0026529C ori $t2,$t2,0x8080 */
	.word	0x0069102F  /* 002652A0 dsubu $v0,$v1,$t1 */
	.word	0x00031827  /* 002652A4 nor $v1,$zero,$v1 */
	.word	0x00431024  /* 002652A8 and $v0,$v0,$v1 */
	.word	0x004A1024  /* 002652AC and $v0,$v0,$t2 */
	.word	0x14400010  /* 002652B0 bnez $v0,.L002652F4 */
	.word	0x0100382D  /* 002652B4 move $a3,$t0 */
	.word	0xDCA30000  /* 002652B8 ld $v1,0($a1) */
	.word	0x00000000  /* 002652BC nop */
	.word	0x24C6FFF8  /* 002652C0 addiu $a2,$a2,-8 */
	.word	0x24A50008  /* 002652C4 addiu $a1,$a1,8 */
	.word	0x2CC20008  /* 002652C8 sltiu $v0,$a2,8 */
	.word	0xFCE30000  /* 002652CC sd $v1,0($a3) */
	.word	0x14400008  /* 002652D0 bnez $v0,.L002652F4 */
	.word	0x24E70008  /* 002652D4 addiu $a3,$a3,8 */
	.word	0xDCA20000  /* 002652D8 ld $v0,0($a1) */
	.word	0x00021827  /* 002652DC nor $v1,$zero,$v0 */
	.word	0x0049102F  /* 002652E0 dsubu $v0,$v0,$t1 */
	.word	0x00431024  /* 002652E4 and $v0,$v0,$v1 */
	.word	0x004A1024  /* 002652E8 and $v0,$v0,$t2 */
	.word	0x5040FFF4  /* 002652EC beqzl $v0,.L002652C0 */
	.word	0xDCA30000  /* 002652F0 ld $v1,0($a1) */
	.word	0x00E0202D  /* 002652F4 move $a0,$a3 */
	.word	0x10C00012  /* 002652F8 beqz $a2,.L00265344 */
	.word	0x00C0102D  /* 002652FC move $v0,$a2 */
	.word	0x90A20000  /* 00265300 lbu $v0,0($a1) */
	.word	0x24C6FFFF  /* 00265304 addiu $a2,$a2,-1 */
	.word	0x24A50001  /* 00265308 addiu $a1,$a1,1 */
	.word	0xA0820000  /* 0026530C sb $v0,0($a0) */
	.word	0x00021600  /* 00265310 sll $v0,$v0,0x18 */
	.word	0x1440FFF8  /* 00265314 bnez $v0,.L002652F8 */
	.word	0x24840001  /* 00265318 addiu $a0,$a0,1 */
	.word	0x00C0102D  /* 0026531C move $v0,$a2 */
	.word	0x10400008  /* 00265320 beqz $v0,.L00265344 */
	.word	0x24C6FFFF  /* 00265324 addiu $a2,$a2,-1 */
	.word	0xA0800000  /* 00265328 sb $zero,0($a0) */
	.word	0x00C0102D  /* 0026532C move $v0,$a2 */
	.word	0x24840001  /* 00265330 addiu $a0,$a0,1 */
	.word	0x24C6FFFF  /* 00265334 addiu $a2,$a2,-1 */
	.word	0x00000000  /* 00265338 nop */
	.word	0x1440FFFA  /* 0026533C bnez $v0,.L00265328 */
	.word	0x00000000  /* 00265340 nop */
	.word	0x03E00008  /* 00265344 jr $ra */
	.word	0x0100102D  /* 00265348 move $v0,$t0 */
	.end	func_00265190

	.section	.text.sceGsResetPath,"ax",@progbits
	.globl	sceGsResetPath
	.ent	sceGsResetPath
sceGsResetPath:  /* 0x002654F0 */
	.word	0x3C021000  /* 002654F0 lui $v0,0x1000 */
	.word	0x24070001  /* 002654F4 li $a3,1 */
	.word	0x34423C10  /* 002654F8 ori $v0,$v0,0x3c10 */
	.word	0x3C031000  /* 002654FC lui $v1,0x1000 */
	.word	0xAC470000  /* 00265500 sw $a3,0($v0) */
	.word	0x34633C20  /* 00265504 ori $v1,$v1,0x3c20 */
	.word	0x24020002  /* 00265508 li $v0,2 */
	.word	0x0000202D  /* 0026550C move $a0,$zero */
	.word	0xAC620000  /* 00265510 sw $v0,0($v1) */
	.word	0x0000000F  /* 00265514 sync */
	.word	0x4844E000  /* 00265518 cfc2 $a0,$vi28 */
	.word	0x34840200  /* 0026551C ori $a0,$a0,0x200 */
	.word	0x48C4E000  /* 00265520 ctc2 $a0,$vi28 */
	.word	0x0000040F  /* 00265524 sync.p */
	.word	0x3C050000  /* 00265528 lui $a1,%hi(D_0046C510) */
	.reloc	.-4, R_MIPS_HI16, D_0046C510
	.word	0x3C061000  /* 0026552C lui $a2,0x1000 */
	.word	0x24A50000  /* 00265530 addiu $a1,$a1,%lo(D_0046C510) */
	.reloc	.-4, R_MIPS_LO16, D_0046C510
	.word	0x34C65000  /* 00265534 ori $a2,$a2,0x5000 */
	.word	0x78A40000  /* 00265538 lq $a0,0($a1) */
	.word	0x3C031000  /* 0026553C lui $v1,0x1000 */
	.word	0x34633000  /* 00265540 ori $v1,$v1,0x3000 */
	.word	0x7CC40000  /* 00265544 sq $a0,0($a2) */
	.word	0x78A20010  /* 00265548 lq $v0,16($a1) */
	.word	0x7CC20000  /* 0026554C sq $v0,0($a2) */
	.word	0x03E00008  /* 00265550 jr $ra */
	.word	0xAC670000  /* 00265554 sw $a3,0($v1) */
	.end	sceGsResetPath

	.section	.text.func_00260b00,"ax",@progbits
	.globl	func_00260b00
	.ent	func_00260b00
func_00260b00:  /* 0x00260B00 */
	.word	0x27BDFFC0  /* 00260B00 addiu $sp,$sp,-64 */
	.word	0x3C040000  /* 00260B04 lui $a0,%hi(D_004923B0) */
	.reloc	.-4, R_MIPS_HI16, D_004923B0
	.word	0xFFB20020  /* 00260B08 sd $s2,32($sp) */
	.word	0x24840000  /* 00260B0C addiu $a0,$a0,%lo(D_004923B0) */
	.reloc	.-4, R_MIPS_LO16, D_004923B0
	.word	0xFFB10010  /* 00260B10 sd $s1,16($sp) */
	.word	0x3C120000  /* 00260B14 lui $s2,%hi(D_0046C4C0) */
	.reloc	.-4, R_MIPS_HI16, D_0046C4C0
	.word	0xFFB00000  /* 00260B18 sd $s0,0($sp) */
	.word	0xFFBF0030  /* 00260B1C sd $ra,48($sp) */
	.word	0x26500000  /* 00260B20 addiu $s0,$s2,%lo(D_0046C4C0) */
	.reloc	.-4, R_MIPS_LO16, D_0046C4C0
	.word	0x8E450000  /* 00260B24 lw $a1,%lo(D_0046C4C0)($s2) */
	.reloc	.-4, R_MIPS_LO16, D_0046C4C0
	.word	0x8E070004  /* 00260B28 lw $a3,4($s0) */
	.word	0x8E090008  /* 00260B2C lw $t1,8($s0) */
	.word	0x00A0302D  /* 00260B30 move $a2,$a1 */
	.word	0x00A73821  /* 00260B34 addu $a3,$a1,$a3 */
	.word	0x00E94821  /* 00260B38 addu $t1,$a3,$t1 */
	.word	0x00E0402D  /* 00260B3C move $t0,$a3 */
	.word	0x24A5FFFF  /* 00260B40 addiu $a1,$a1,-1 */
	.word	0x2529FFFF  /* 00260B44 addiu $t1,$t1,-1 */
	.word	0x0C000000  /* 00260B48 jal func_00259c88 */
	.reloc	.-4, R_MIPS_26, func_00259c88
	.word	0x24E7FFFF  /* 00260B4C addiu $a3,$a3,-1 */
	.word	0x40803000  /* 00260B50 mtc0 $zero,c0_wired */
	.word	0x0000040F  /* 00260B54 sync.p */
	.word	0x8E510000  /* 00260B58 lw $s1,%lo(D_0046C4C0)($s2) */
	.reloc	.-4, R_MIPS_LO16, D_0046C4C0
	.word	0x2A220031  /* 00260B5C slti $v0,$s1,49 */
	.word	0x14400006  /* 00260B60 bnez $v0,.L00260B7C */
	.word	0x0000C82D  /* 00260B64 move $t9,$zero */
	.word	0x3C040000  /* 00260B68 lui $a0,%hi(D_004923E8) */
	.reloc	.-4, R_MIPS_HI16, D_004923E8
	.word	0x0C000000  /* 00260B6C jal func_00259c88 */
	.reloc	.-4, R_MIPS_26, func_00259c88
	.word	0x24840000  /* 00260B70 addiu $a0,$a0,%lo(D_004923E8) */
	.reloc	.-4, R_MIPS_LO16, D_004923E8
	.word	0x0C000000  /* 00260B74 jal func_0025f9a8 */
	.reloc	.-4, R_MIPS_26, func_0025f9a8
	.word	0x24040001  /* 00260B78 li $a0,1 */
	.word	0x0331102A  /* 00260B7C slt $v0,$t9,$s1 */
	.word	0x1040000D  /* 00260B80 beqz $v0,.L00260BB8 */
	.word	0x8E100010  /* 00260B84 lw $s0,16($s0) */
	.word	0x8E050000  /* 00260B88 lw $a1,0($s0) */
	.word	0x00000000  /* 00260B8C nop */
	.word	0x0320202D  /* 00260B90 move $a0,$t9 */
	.word	0x8E060004  /* 00260B94 lw $a2,4($s0) */
	.word	0x8E070008  /* 00260B98 lw $a3,8($s0) */
	.word	0x8E08000C  /* 00260B9C lw $t0,12($s0) */
	.word	0x0C000000  /* 00260BA0 jal func_00260a20 */
	.reloc	.-4, R_MIPS_26, func_00260a20
	.word	0x26100010  /* 00260BA4 addiu $s0,$s0,16 */
	.word	0x27390001  /* 00260BA8 addiu $t9,$t9,1 */
	.word	0x0331102A  /* 00260BAC slt $v0,$t9,$s1 */
	.word	0x5440FFF7  /* 00260BB0 bnezl $v0,.L00260B90 */
	.word	0x8E050000  /* 00260BB4 lw $a1,0($s0) */
	.word	0x26500000  /* 00260BB8 addiu $s0,$s2,-15168 */
	.reloc	.-4, R_MIPS_LO16, D_0046C4C0
	.word	0x8E020004  /* 00260BBC lw $v0,4($s0) */
	.word	0x03228821  /* 00260BC0 addu $s1,$t9,$v0 */
	.word	0x2A230031  /* 00260BC4 slti $v1,$s1,49 */
	.word	0x14600007  /* 00260BC8 bnez $v1,.L00260BE8 */
	.word	0x0331102A  /* 00260BCC slt $v0,$t9,$s1 */
	.word	0x3C040000  /* 00260BD0 lui $a0,%hi(D_00492400) */
	.reloc	.-4, R_MIPS_HI16, D_00492400
	.word	0x0C000000  /* 00260BD4 jal func_00259c88 */
	.reloc	.-4, R_MIPS_26, func_00259c88
	.word	0x24840000  /* 00260BD8 addiu $a0,$a0,%lo(D_00492400) */
	.reloc	.-4, R_MIPS_LO16, D_00492400
	.word	0x0C000000  /* 00260BDC jal func_0025f9a8 */
	.reloc	.-4, R_MIPS_26, func_0025f9a8
	.word	0x24040001  /* 00260BE0 li $a0,1 */
	.word	0x0331102A  /* 00260BE4 slt $v0,$t9,$s1 */
	.word	0x1040000D  /* 00260BE8 beqz $v0,.L00260C20 */
	.word	0x8E100014  /* 00260BEC lw $s0,20($s0) */
	.word	0x8E050000  /* 00260BF0 lw $a1,0($s0) */
	.word	0x00000000  /* 00260BF4 nop */
	.word	0x0320202D  /* 00260BF8 move $a0,$t9 */
	.word	0x8E060004  /* 00260BFC lw $a2,4($s0) */
	.word	0x8E070008  /* 00260C00 lw $a3,8($s0) */
	.word	0x8E08000C  /* 00260C04 lw $t0,12($s0) */
	.word	0x0C000000  /* 00260C08 jal func_00260a20 */
	.reloc	.-4, R_MIPS_26, func_00260a20
	.word	0x26100010  /* 00260C0C addiu $s0,$s0,16 */
	.word	0x27390001  /* 00260C10 addiu $t9,$t9,1 */
	.word	0x0331102A  /* 00260C14 slt $v0,$t9,$s1 */
	.word	0x5440FFF7  /* 00260C18 bnezl $v0,.L00260BF8 */
	.word	0x8E050000  /* 00260C1C lw $a1,0($s0) */
	.word	0x26500000  /* 00260C20 addiu $s0,$s2,-15168 */
	.reloc	.-4, R_MIPS_LO16, D_0046C4C0
	.word	0xAE19000C  /* 00260C24 sw $t9,12($s0) */
	.word	0x40993000  /* 00260C28 mtc0 $t9,c0_wired */
	.word	0x0000040F  /* 00260C2C sync.p */
	.word	0x8E020008  /* 00260C30 lw $v0,8($s0) */
	.word	0x58400019  /* 00260C34 blezl $v0,.L00260C9C */
	.word	0x0320802D  /* 00260C38 move $s0,$t9 */
	.word	0x03228821  /* 00260C3C addu $s1,$t9,$v0 */
	.word	0x2A220031  /* 00260C40 slti $v0,$s1,49 */
	.word	0x14400007  /* 00260C44 bnez $v0,.L00260C64 */
	.word	0x0331102A  /* 00260C48 slt $v0,$t9,$s1 */
	.word	0x3C040000  /* 00260C4C lui $a0,%hi(D_00492418) */
	.reloc	.-4, R_MIPS_HI16, D_00492418
	.word	0x0C000000  /* 00260C50 jal func_00259c88 */
	.reloc	.-4, R_MIPS_26, func_00259c88
	.word	0x24840000  /* 00260C54 addiu $a0,$a0,%lo(D_00492418) */
	.reloc	.-4, R_MIPS_LO16, D_00492418
	.word	0x0C000000  /* 00260C58 jal func_0025f9a8 */
	.reloc	.-4, R_MIPS_26, func_0025f9a8
	.word	0x24040001  /* 00260C5C li $a0,1 */
	.word	0x0331102A  /* 00260C60 slt $v0,$t9,$s1 */
	.word	0x1040000C  /* 00260C64 beqz $v0,.L00260C98 */
	.word	0x8E100018  /* 00260C68 lw $s0,24($s0) */
	.word	0x8E050000  /* 00260C6C lw $a1,0($s0) */
	.word	0x0320202D  /* 00260C70 move $a0,$t9 */
	.word	0x8E060004  /* 00260C74 lw $a2,4($s0) */
	.word	0x8E070008  /* 00260C78 lw $a3,8($s0) */
	.word	0x8E08000C  /* 00260C7C lw $t0,12($s0) */
	.word	0x0C000000  /* 00260C80 jal func_00260a20 */
	.reloc	.-4, R_MIPS_26, func_00260a20
	.word	0x26100010  /* 00260C84 addiu $s0,$s0,16 */
	.word	0x27390001  /* 00260C88 addiu $t9,$t9,1 */
	.word	0x0331102A  /* 00260C8C slt $v0,$t9,$s1 */
	.word	0x5440FFF7  /* 00260C90 bnezl $v0,.L00260C70 */
	.word	0x8E050000  /* 00260C94 lw $a1,0($s0) */
	.word	0x0320802D  /* 00260C98 move $s0,$t9 */
	.word	0x2A020030  /* 00260C9C slti $v0,$s0,48 */
	.word	0x1040000D  /* 00260CA0 beqz $v0,.L00260CD8 */
	.word	0x0019CB40  /* 00260CA4 sll $t9,$t9,0xd */
	.word	0x3C02E000  /* 00260CA8 lui $v0,0xe000 */
	.word	0x03228821  /* 00260CAC addu $s1,$t9,$v0 */
	.word	0x0200202D  /* 00260CB0 move $a0,$s0 */
	.word	0x0220302D  /* 00260CB4 move $a2,$s1 */
	.word	0x0000282D  /* 00260CB8 move $a1,$zero */
	.word	0x0000382D  /* 00260CBC move $a3,$zero */
	.word	0x0000402D  /* 00260CC0 move $t0,$zero */
	.word	0x0C000000  /* 00260CC4 jal func_00260a20 */
	.reloc	.-4, R_MIPS_26, func_00260a20
	.word	0x26100001  /* 00260CC8 addiu $s0,$s0,1 */
	.word	0x2A020030  /* 00260CCC slti $v0,$s0,48 */
	.word	0x1440FFF7  /* 00260CD0 bnez $v0,.L00260CB0 */
	.word	0x26312000  /* 00260CD4 addiu $s1,$s1,8192 */
	.word	0xDFBF0030  /* 00260CD8 ld $ra,48($sp) */
	.word	0x0320102D  /* 00260CDC move $v0,$t9 */
	.word	0xDFB20020  /* 00260CE0 ld $s2,32($sp) */
	.word	0xDFB10010  /* 00260CE4 ld $s1,16($sp) */
	.word	0xDFB00000  /* 00260CE8 ld $s0,0($sp) */
	.word	0x03E00008  /* 00260CEC jr $ra */
	.word	0x27BD0040  /* 00260CF0 addiu $sp,$sp,64 */
	.end	func_00260b00
