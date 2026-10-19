/* func_001fd858: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001fd858,"ax",@progbits
	.globl	func_001fd858
	.ent	func_001fd858
func_001fd858:  /* 0x001FD858 */
	.word	0x27BDFFD0  /* 001FD858 addiu $sp,$sp,-48 */
	.word	0xFFB00000  /* 001FD85C sd $s0,0($sp) */
	.word	0x0080802D  /* 001FD860 move $s0,$a0 */
	.word	0xFFB10008  /* 001FD864 sd $s1,8($sp) */
	.word	0xFFB20010  /* 001FD868 sd $s2,16($sp) */
	.word	0xFFB30018  /* 001FD86C sd $s3,24($sp) */
	.word	0xFFBF0020  /* 001FD870 sd $ra,32($sp) */
	.word	0x860800CC  /* 001FD874 lh $t0,204($s0) */
	.word	0x29020002  /* 001FD878 slti $v0,$t0,2 */
	.word	0x14400004  /* 001FD87C bnez $v0,.L001FD890 */
	.word	0x960E00CC  /* 001FD880 lhu $t6,204($s0) */
	.word	0x860200CE  /* 001FD884 lh $v0,206($s0) */
	.word	0x14400003  /* 001FD888 bnez $v0,.L001FD898 */
	.word	0x0040602D  /* 001FD88C move $t4,$v0 */
	.word	0x100001C7  /* 001FD890 b .L001FDFB0 */
	.word	0xA60000D2  /* 001FD894 sh $zero,210($s0) */
	.word	0x0102102A  /* 001FD898 slt $v0,$t0,$v0 */
	.word	0x50400004  /* 001FD89C beqzl $v0,.L001FD8B0 */
	.word	0x961800D2  /* 001FD8A0 lhu $t8,210($s0) */
	.word	0xA60E00CE  /* 001FD8A4 sh $t6,206($s0) */
	.word	0x01C0602D  /* 001FD8A8 move $t4,$t6 */
	.word	0x961800D2  /* 001FD8AC lhu $t8,210($s0) */
	.word	0x000C1C00  /* 001FD8B0 sll $v1,$t4,0x10 */
	.word	0x00032C03  /* 001FD8B4 sra $a1,$v1,0x10 */
	.word	0x00181400  /* 001FD8B8 sll $v0,$t8,0x10 */
	.word	0x00021503  /* 001FD8BC sra $v0,$v0,0x14 */
	.word	0x0045102A  /* 001FD8C0 slt $v0,$v0,$a1 */
	.word	0x54400006  /* 001FD8C4 bnezl $v0,.L001FD8E0 */
	.word	0x960900D0  /* 001FD8C8 lhu $t1,208($s0) */
	.word	0x2582FFFF  /* 001FD8CC addiu $v0,$t4,-1 */
	.word	0x00021100  /* 001FD8D0 sll $v0,$v0,0x4 */
	.word	0xA60200D2  /* 001FD8D4 sh $v0,210($s0) */
	.word	0x0040C02D  /* 001FD8D8 move $t8,$v0 */
	.word	0x960900D0  /* 001FD8DC lhu $t1,208($s0) */
	.word	0x00181400  /* 001FD8E0 sll $v0,$t8,0x10 */
	.word	0x860300BC  /* 001FD8E4 lh $v1,188($s0) */
	.word	0x0002CC03  /* 001FD8E8 sra $t9,$v0,0x10 */
	.word	0x00097C00  /* 001FD8EC sll $t7,$t1,0x10 */
	.word	0x0000882D  /* 001FD8F0 move $s1,$zero */
	.word	0x14600064  /* 001FD8F4 bnez $v1,.L001FDA88 */
	.word	0x000F6C03  /* 001FD8F8 sra $t5,$t7,0x10 */
	.word	0x3C120000  /* 001FD8FC lui $s2,%hi(D_00425BC8) */
	.reloc	.-4, R_MIPS_HI16, D_00425BC8
	.word	0x8E4A0000  /* 001FD900 lw $t2,%lo(D_00425BC8)($s2) */
	.reloc	.-4, R_MIPS_LO16, D_00425BC8
	.word	0x8D4B0004  /* 001FD904 lw $t3,4($t2) */
	.word	0x31620300  /* 001FD908 andi $v0,$t3,0x300 */
	.word	0x10400062  /* 001FD90C beqz $v0,.L001FDA98 */
	.word	0x0100302D  /* 001FD910 move $a2,$t0 */
	.word	0x00A0102D  /* 001FD914 move $v0,$a1 */
	.word	0x10C20099  /* 001FD918 beq $a2,$v0,.L001FDB80 */
	.word	0x0046102A  /* 001FD91C slt $v0,$v0,$a2 */
	.word	0x10400059  /* 001FD920 beqz $v0,.L001FDA88 */
	.word	0x3C020000  /* 001FD924 lui $v0,%hi(D_00640DEC) */
	.reloc	.-4, R_MIPS_HI16, D_00640DEC
	.word	0x3C130000  /* 001FD928 lui $s3,%hi(D_00640DE4) */
	.reloc	.-4, R_MIPS_HI16, D_00640DE4
	.word	0x8C430000  /* 001FD92C lw $v1,%lo(D_00640DEC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_00640DEC
	.word	0x8E670000  /* 001FD930 lw $a3,%lo(D_00640DE4)($s3) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE4
	.word	0x01631824  /* 001FD934 and $v1,$t3,$v1 */
	.word	0x00671024  /* 001FD938 and $v0,$v1,$a3 */
	.word	0x10400028  /* 001FD93C beqz $v0,.L001FD9E0 */
	.word	0x3C020000  /* 001FD940 lui $v0,0x64 */
	.reloc	.-4, R_MIPS_HI16, D_00640DE8
	.word	0x59A0001C  /* 001FD944 blezl $t5,.L001FD9B8 */
	.word	0x8D420008  /* 001FD948 lw $v0,8($t2) */
	.word	0x3C020000  /* 001FD94C lui $v0,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014100  /* 001FD950 lui $at,0x4100 */
	.word	0x44811000  /* 001FD954 mtc1 $at,$f2 */
	.word	0xC4410000  /* 001FD958 lwc1 $f1,%lo(D_002BBDFC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x448D0000  /* 001FD95C mtc1 $t5,$f0 */
	.word	0x46800020  /* 001FD960 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FD964 mul.s $f1,$f1,$f2 */
	.word	0x46010001  /* 001FD968 sub.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FD96C trunc.w.s $f2,$f0 */
	.word	0x44021000  /* 001FD970 mfc1 $v0,$f2 */
	.word	0x00022400  /* 001FD974 sll $a0,$v0,0x10 */
	.word	0x04810005  /* 001FD978 bgez $a0,.L001FD990 */
	.word	0xA60200D0  /* 001FD97C sh $v0,208($s0) */
	.word	0xA60000D0  /* 001FD980 sh $zero,208($s0) */
	.word	0x24110001  /* 001FD984 li $s1,1 */
	.word	0x10000079  /* 001FD988 b .L001FDB70 */
	.word	0xA60000D6  /* 001FD98C sh $zero,214($s0) */
	.word	0x46000807  /* 001FD990 neg.s $f0,$f1 */
	.word	0x00042503  /* 001FD994 sra $a0,$a0,0x14 */
	.word	0x000F1D03  /* 001FD998 sra $v1,$t7,0x14 */
	.word	0x46000064  /* 001FD99C trunc.w.s $f1,$f0 */
	.word	0x44020800  /* 001FD9A0 mfc1 $v0,$f1 */
	.word	0x10830072  /* 001FD9A4 beq $a0,$v1,.L001FDB70 */
	.word	0xA60200D6  /* 001FD9A8 sh $v0,214($s0) */
	.word	0x10000070  /* 001FD9AC b .L001FDB70 */
	.word	0x24110001  /* 001FD9B0 li $s1,1 */
	.word	0x00000000  /* 001FD9B4 nop */
	.word	0x00471024  /* 001FD9B8 and $v0,$v0,$a3 */
	.word	0x1040006C  /* 001FD9BC beqz $v0,.L001FDB70 */
	.word	0x24020002  /* 001FD9C0 li $v0,2 */
	.word	0x14C20048  /* 001FD9C4 bne $a2,$v0,.L001FDAE8 */
	.word	0x01CC1023  /* 001FD9C8 subu $v0,$t6,$t4 */
	.word	0x532000DB  /* 001FD9CC beqzl $t9,.L001FDD3C */
	.word	0x000C1400  /* 001FD9D0 sll $v0,$t4,0x10 */
	.word	0x10000045  /* 001FD9D4 b .L001FDAEC */
	.word	0x2583FFFF  /* 001FD9D8 addiu $v1,$t4,-1 */
	.word	0x00000000  /* 001FD9DC nop */
	.word	0x8C470000  /* 001FD9E0 lw $a3,3560($v0) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE8
	.word	0x00671824  /* 001FD9E4 and $v1,$v1,$a3 */
	.word	0x10600027  /* 001FD9E8 beqz $v1,.L001FDA88 */
	.word	0x00C51023  /* 001FD9EC subu $v0,$a2,$a1 */
	.word	0x00022100  /* 001FD9F0 sll $a0,$v0,0x4 */
	.word	0x01A4182A  /* 001FD9F4 slt $v1,$t5,$a0 */
	.word	0x50600019  /* 001FD9F8 beqzl $v1,.L001FDA60 */
	.word	0x8D420008  /* 001FD9FC lw $v0,8($t2) */
	.word	0x3C020000  /* 001FDA00 lui $v0,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014100  /* 001FDA04 lui $at,0x4100 */
	.word	0x44811000  /* 001FDA08 mtc1 $at,$f2 */
	.word	0xC4410000  /* 001FDA0C lwc1 $f1,%lo(D_002BBDFC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x448D0000  /* 001FDA10 mtc1 $t5,$f0 */
	.word	0x46800020  /* 001FDA14 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDA18 mul.s $f1,$f1,$f2 */
	.word	0x46010000  /* 001FDA1C add.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FDA20 trunc.w.s $f2,$f0 */
	.word	0x44031000  /* 001FDA24 mfc1 $v1,$f2 */
	.word	0x00032C00  /* 001FDA28 sll $a1,$v1,0x10 */
	.word	0x00051403  /* 001FDA2C sra $v0,$a1,0x10 */
	.word	0x0082102A  /* 001FDA30 slt $v0,$a0,$v0 */
	.word	0x10400004  /* 001FDA34 beqz $v0,.L001FDA48 */
	.word	0xA60300D0  /* 001FDA38 sh $v1,208($s0) */
	.word	0x1000FFD1  /* 001FDA3C b .L001FD984 */
	.word	0xA60400D0  /* 001FDA40 sh $a0,208($s0) */
	.word	0x00000000  /* 001FDA44 nop */
	.word	0x46000824  /* 001FDA48 trunc.w.s $f0,$f1 */
	.word	0x44020000  /* 001FDA4C mfc1 $v0,$f0 */
	.word	0x000F1D03  /* 001FDA50 sra $v1,$t7,0x14 */
	.word	0x1000FFD3  /* 001FDA54 b .L001FD9A4 */
	.word	0x00052503  /* 001FDA58 sra $a0,$a1,0x14 */
	.word	0x00000000  /* 001FDA5C nop */
	.word	0x00471024  /* 001FDA60 and $v0,$v0,$a3 */
	.word	0x10400042  /* 001FDA64 beqz $v0,.L001FDB70 */
	.word	0x24020002  /* 001FDA68 li $v0,2 */
	.word	0x5502003E  /* 001FDA6C bnel $t0,$v0,.L001FDB68 */
	.word	0xA60000D0  /* 001FDA70 sh $zero,208($s0) */
	.word	0x24020010  /* 001FDA74 li $v0,16 */
	.word	0x1322004C  /* 001FDA78 beq $t9,$v0,.L001FDBAC */
	.word	0x00181400  /* 001FDA7C sll $v0,$t8,0x10 */
	.word	0x10000039  /* 001FDA80 b .L001FDB68 */
	.word	0xA60000D0  /* 001FDA84 sh $zero,208($s0) */
	.word	0x0C000000  /* 001FDA88 jal func_001fe1b8 */
	.reloc	.-4, R_MIPS_26, func_001fe1b8
	.word	0x00000000  /* 001FDA8C nop */
	.word	0x10000140  /* 001FDA90 b .L001FDF94 */
	.word	0x0040882D  /* 001FDA94 move $s1,$v0 */
	.word	0x8D430010  /* 001FDA98 lw $v1,16($t2) */
	.word	0x30620400  /* 001FDA9C andi $v0,$v1,0x400 */
	.word	0x10400019  /* 001FDAA0 beqz $v0,.L001FDB08 */
	.word	0x00A8102A  /* 001FDAA4 slt $v0,$a1,$t0 */
	.word	0x10400031  /* 001FDAA8 beqz $v0,.L001FDB70 */
	.word	0x00000000  /* 001FDAAC nop */
	.word	0x19A00009  /* 001FDAB0 blez $t5,.L001FDAD8 */
	.word	0x00052100  /* 001FDAB4 sll $a0,$a1,0x4 */
	.word	0x01241023  /* 001FDAB8 subu $v0,$t1,$a0 */
	.word	0x24110001  /* 001FDABC li $s1,1 */
	.word	0x00021C00  /* 001FDAC0 sll $v1,$v0,0x10 */
	.word	0x0461002A  /* 001FDAC4 bgez $v1,.L001FDB70 */
	.word	0xA60200D0  /* 001FDAC8 sh $v0,208($s0) */
	.word	0xA60000D0  /* 001FDACC sh $zero,208($s0) */
	.word	0x10000027  /* 001FDAD0 b .L001FDB70 */
	.word	0xA60000D6  /* 001FDAD4 sh $zero,214($s0) */
	.word	0x8D420008  /* 001FDAD8 lw $v0,8($t2) */
	.word	0x30420400  /* 001FDADC andi $v0,$v0,0x400 */
	.word	0x10400023  /* 001FDAE0 beqz $v0,.L001FDB70 */
	.word	0x01CC1023  /* 001FDAE4 subu $v0,$t6,$t4 */
	.word	0x2583FFFF  /* 001FDAE8 addiu $v1,$t4,-1 */
	.word	0x00021100  /* 001FDAEC sll $v0,$v0,0x4 */
	.word	0x00031900  /* 001FDAF0 sll $v1,$v1,0x4 */
	.word	0xA60200D0  /* 001FDAF4 sh $v0,208($s0) */
	.word	0x24110001  /* 001FDAF8 li $s1,1 */
	.word	0x1000001C  /* 001FDAFC b .L001FDB70 */
	.word	0xA60300D2  /* 001FDB00 sh $v1,210($s0) */
	.word	0x00000000  /* 001FDB04 nop */
	.word	0x30620800  /* 001FDB08 andi $v0,$v1,0x800 */
	.word	0x1040001C  /* 001FDB0C beqz $v0,.L001FDB80 */
	.word	0x00A8102A  /* 001FDB10 slt $v0,$a1,$t0 */
	.word	0x10400016  /* 001FDB14 beqz $v0,.L001FDB70 */
	.word	0x01051023  /* 001FDB18 subu $v0,$t0,$a1 */
	.word	0x00022100  /* 001FDB1C sll $a0,$v0,0x4 */
	.word	0x01A4182A  /* 001FDB20 slt $v1,$t5,$a0 */
	.word	0x5060000C  /* 001FDB24 beqzl $v1,.L001FDB58 */
	.word	0x8D420008  /* 001FDB28 lw $v0,8($t2) */
	.word	0x000C1900  /* 001FDB2C sll $v1,$t4,0x4 */
	.word	0x24110001  /* 001FDB30 li $s1,1 */
	.word	0x01231821  /* 001FDB34 addu $v1,$t1,$v1 */
	.word	0x00031400  /* 001FDB38 sll $v0,$v1,0x10 */
	.word	0x00021403  /* 001FDB3C sra $v0,$v0,0x10 */
	.word	0x0082102A  /* 001FDB40 slt $v0,$a0,$v0 */
	.word	0x1040000A  /* 001FDB44 beqz $v0,.L001FDB70 */
	.word	0xA60300D0  /* 001FDB48 sh $v1,208($s0) */
	.word	0xA60400D0  /* 001FDB4C sh $a0,208($s0) */
	.word	0x10000007  /* 001FDB50 b .L001FDB70 */
	.word	0xA60000D6  /* 001FDB54 sh $zero,214($s0) */
	.word	0x30420800  /* 001FDB58 andi $v0,$v0,0x800 */
	.word	0x10400004  /* 001FDB5C beqz $v0,.L001FDB70 */
	.word	0x00000000  /* 001FDB60 nop */
	.word	0xA60000D0  /* 001FDB64 sh $zero,208($s0) */
	.word	0x24110001  /* 001FDB68 li $s1,1 */
	.word	0xA60000D2  /* 001FDB6C sh $zero,210($s0) */
	.word	0x0C000000  /* 001FDB70 jal func_001fe4e0 */
	.reloc	.-4, R_MIPS_26, func_001fe4e0
	.word	0x0200202D  /* 001FDB74 move $a0,$s0 */
	.word	0x10000106  /* 001FDB78 b .L001FDF94 */
	.word	0x00000000  /* 001FDB7C nop */
	.word	0x8E440000  /* 001FDB80 lw $a0,23496($s2) */
	.reloc	.-4, R_MIPS_LO16, D_00425BC8
	.word	0x3C020000  /* 001FDB84 lui $v0,%hi(D_00640DEC) */
	.reloc	.-4, R_MIPS_HI16, D_00640DEC
	.word	0x8C450000  /* 001FDB88 lw $a1,%lo(D_00640DEC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_00640DEC
	.word	0x3C130000  /* 001FDB8C lui $s3,%hi(D_00640DE4) */
	.reloc	.-4, R_MIPS_HI16, D_00640DE4
	.word	0x8C830010  /* 001FDB90 lw $v1,16($a0) */
	.word	0x8E620000  /* 001FDB94 lw $v0,%lo(D_00640DE4)($s3) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE4
	.word	0x00652024  /* 001FDB98 and $a0,$v1,$a1 */
	.word	0x00821024  /* 001FDB9C and $v0,$a0,$v0 */
	.word	0x10400061  /* 001FDBA0 beqz $v0,.L001FDD28 */
	.word	0x3C030000  /* 001FDBA4 lui $v1,0x64 */
	.reloc	.-4, R_MIPS_HI16, D_00640DE8
	.word	0x00181400  /* 001FDBA8 sll $v0,$t8,0x10 */
	.word	0x00021403  /* 001FDBAC sra $v0,$v0,0x10 */
	.word	0x58400035  /* 001FDBB0 blezl $v0,.L001FDC88 */
	.word	0x00091400  /* 001FDBB4 sll $v0,$t1,0x10 */
	.word	0x3C070000  /* 001FDBB8 lui $a3,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014080  /* 001FDBBC lui $at,0x4080 */
	.word	0x44811000  /* 001FDBC0 mtc1 $at,$f2 */
	.word	0xC4E10000  /* 001FDBC4 lwc1 $f1,%lo(D_002BBDFC)($a3) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x44820000  /* 001FDBC8 mtc1 $v0,$f0 */
	.word	0x46800020  /* 001FDBCC cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDBD0 mul.s $f1,$f1,$f2 */
	.word	0x46010001  /* 001FDBD4 sub.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FDBD8 trunc.w.s $f2,$f0 */
	.word	0x44021000  /* 001FDBDC mfc1 $v0,$f2 */
	.word	0x00021C00  /* 001FDBE0 sll $v1,$v0,0x10 */
	.word	0x04610006  /* 001FDBE4 bgez $v1,.L001FDC00 */
	.word	0xA60200D2  /* 001FDBE8 sh $v0,210($s0) */
	.word	0xA60000D2  /* 001FDBEC sh $zero,210($s0) */
	.word	0x24110001  /* 001FDBF0 li $s1,1 */
	.word	0x1000000A  /* 001FDBF4 b .L001FDC20 */
	.word	0xA60000D4  /* 001FDBF8 sh $zero,212($s0) */
	.word	0x00000000  /* 001FDBFC nop */
	.word	0x46000807  /* 001FDC00 neg.s $f0,$f1 */
	.word	0x00031503  /* 001FDC04 sra $v0,$v1,0x14 */
	.word	0x00191903  /* 001FDC08 sra $v1,$t9,0x4 */
	.word	0x00431026  /* 001FDC0C xor $v0,$v0,$v1 */
	.word	0x0002882B  /* 001FDC10 sltu $s1,$zero,$v0 */
	.word	0x46000064  /* 001FDC14 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 001FDC18 mfc1 $v1,$f1 */
	.word	0xA60300D4  /* 001FDC1C sh $v1,212($s0) */
	.word	0x860200D6  /* 001FDC20 lh $v0,214($s0) */
	.word	0x04410084  /* 001FDC24 bgez $v0,.L001FDE38 */
	.word	0x3125000F  /* 001FDC28 andi $a1,$t1,0xf */
	.word	0x2402FFF0  /* 001FDC2C li $v0,-16 */
	.word	0x01221024  /* 001FDC30 and $v0,$t1,$v0 */
	.word	0x00021400  /* 001FDC34 sll $v0,$v0,0x10 */
	.word	0x10A0007A  /* 001FDC38 beqz $a1,.L001FDE24 */
	.word	0x00023403  /* 001FDC3C sra $a2,$v0,0x10 */
	.word	0xC4E10000  /* 001FDC40 lwc1 $f1,-16900($a3) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x00091400  /* 001FDC44 sll $v0,$t1,0x10 */
	.word	0x3C014080  /* 001FDC48 lui $at,0x4080 */
	.word	0x44811000  /* 001FDC4C mtc1 $at,$f2 */
	.word	0x00021403  /* 001FDC50 sra $v0,$v0,0x10 */
	.word	0x44820000  /* 001FDC54 mtc1 $v0,$f0 */
	.word	0x46800020  /* 001FDC58 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDC5C mul.s $f1,$f1,$f2 */
	.word	0x46010001  /* 001FDC60 sub.s $f0,$f0,$f1 */
	.word	0x46000064  /* 001FDC64 trunc.w.s $f1,$f0 */
	.word	0x44020800  /* 001FDC68 mfc1 $v0,$f1 */
	.word	0x00021C00  /* 001FDC6C sll $v1,$v0,0x10 */
	.word	0x00031C03  /* 001FDC70 sra $v1,$v1,0x10 */
	.word	0x1860006A  /* 001FDC74 blez $v1,.L001FDE20 */
	.word	0xA60200D0  /* 001FDC78 sh $v0,208($s0) */
	.word	0x10000090  /* 001FDC7C b .L001FDEC0 */
	.word	0x00C3102A  /* 001FDC80 slt $v0,$a2,$v1 */
	.word	0x00000000  /* 001FDC84 nop */
	.word	0x00021C03  /* 001FDC88 sra $v1,$v0,0x10 */
	.word	0x18600016  /* 001FDC8C blez $v1,.L001FDCE8 */
	.word	0x8E420000  /* 001FDC90 lw $v0,23496($s2) */
	.reloc	.-4, R_MIPS_LO16, D_00425BC8
	.word	0x3C020000  /* 001FDC94 lui $v0,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014080  /* 001FDC98 lui $at,0x4080 */
	.word	0x44811000  /* 001FDC9C mtc1 $at,$f2 */
	.word	0xC4410000  /* 001FDCA0 lwc1 $f1,%lo(D_002BBDFC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x44830000  /* 001FDCA4 mtc1 $v1,$f0 */
	.word	0x46800020  /* 001FDCA8 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDCAC mul.s $f1,$f1,$f2 */
	.word	0x46010001  /* 001FDCB0 sub.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FDCB4 trunc.w.s $f2,$f0 */
	.word	0x44021000  /* 001FDCB8 mfc1 $v0,$f2 */
	.word	0x00022400  /* 001FDCBC sll $a0,$v0,0x10 */
	.word	0x04810003  /* 001FDCC0 bgez $a0,.L001FDCD0 */
	.word	0xA60200D0  /* 001FDCC4 sh $v0,208($s0) */
	.word	0x10000099  /* 001FDCC8 b .L001FDF30 */
	.word	0xA60000D0  /* 001FDCCC sh $zero,208($s0) */
	.word	0x46000807  /* 001FDCD0 neg.s $f0,$f1 */
	.word	0x00042503  /* 001FDCD4 sra $a0,$a0,0x14 */
	.word	0x46000064  /* 001FDCD8 trunc.w.s $f1,$f0 */
	.word	0x44020800  /* 001FDCDC mfc1 $v0,$f1 */
	.word	0x10000099  /* 001FDCE0 b .L001FDF48 */
	.word	0x000D1903  /* 001FDCE4 sra $v1,$t5,0x4 */
	.word	0x8E640000  /* 001FDCE8 lw $a0,3556($s3) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE4
	.word	0x8C430008  /* 001FDCEC lw $v1,8($v0) */
	.word	0x00641824  /* 001FDCF0 and $v1,$v1,$a0 */
	.word	0x106000A7  /* 001FDCF4 beqz $v1,.L001FDF94 */
	.word	0x000E1400  /* 001FDCF8 sll $v0,$t6,0x10 */
	.word	0x24030002  /* 001FDCFC li $v1,2 */
	.word	0x00021403  /* 001FDD00 sra $v0,$v0,0x10 */
	.word	0x1043000C  /* 001FDD04 beq $v0,$v1,.L001FDD38 */
	.word	0x01CC1023  /* 001FDD08 subu $v0,$t6,$t4 */
	.word	0x2583FFFF  /* 001FDD0C addiu $v1,$t4,-1 */
	.word	0x00021100  /* 001FDD10 sll $v0,$v0,0x4 */
	.word	0x00031900  /* 001FDD14 sll $v1,$v1,0x4 */
	.word	0xA60200D0  /* 001FDD18 sh $v0,208($s0) */
	.word	0x24110001  /* 001FDD1C li $s1,1 */
	.word	0x1000009C  /* 001FDD20 b .L001FDF94 */
	.word	0xA60300D2  /* 001FDD24 sh $v1,210($s0) */
	.word	0x8C620000  /* 001FDD28 lw $v0,3560($v1) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE8
	.word	0x00821024  /* 001FDD2C and $v0,$a0,$v0 */
	.word	0x10400095  /* 001FDD30 beqz $v0,.L001FDF88 */
	.word	0x00000000  /* 001FDD34 nop */
	.word	0x000C1400  /* 001FDD38 sll $v0,$t4,0x10 */
	.word	0x00181C00  /* 001FDD3C sll $v1,$t8,0x10 */
	.word	0x00023403  /* 001FDD40 sra $a2,$v0,0x10 */
	.word	0x00032C03  /* 001FDD44 sra $a1,$v1,0x10 */
	.word	0x24C2FFFF  /* 001FDD48 addiu $v0,$a2,-1 */
	.word	0x00022100  /* 001FDD4C sll $a0,$v0,0x4 */
	.word	0x00A4182A  /* 001FDD50 slt $v1,$a1,$a0 */
	.word	0x1060005E  /* 001FDD54 beqz $v1,.L001FDED0 */
	.word	0x000E1400  /* 001FDD58 sll $v0,$t6,0x10 */
	.word	0x3C070000  /* 001FDD5C lui $a3,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014080  /* 001FDD60 lui $at,0x4080 */
	.word	0x44811000  /* 001FDD64 mtc1 $at,$f2 */
	.word	0xC4E10000  /* 001FDD68 lwc1 $f1,%lo(D_002BBDFC)($a3) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x44850000  /* 001FDD6C mtc1 $a1,$f0 */
	.word	0x46800020  /* 001FDD70 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDD74 mul.s $f1,$f1,$f2 */
	.word	0x46010000  /* 001FDD78 add.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FDD7C trunc.w.s $f2,$f0 */
	.word	0x44031000  /* 001FDD80 mfc1 $v1,$f2 */
	.word	0x00032C00  /* 001FDD84 sll $a1,$v1,0x10 */
	.word	0x00051403  /* 001FDD88 sra $v0,$a1,0x10 */
	.word	0x0082102A  /* 001FDD8C slt $v0,$a0,$v0 */
	.word	0x10400005  /* 001FDD90 beqz $v0,.L001FDDA8 */
	.word	0xA60300D2  /* 001FDD94 sh $v1,210($s0) */
	.word	0xA60400D2  /* 001FDD98 sh $a0,210($s0) */
	.word	0x24110001  /* 001FDD9C li $s1,1 */
	.word	0x10000008  /* 001FDDA0 b .L001FDDC4 */
	.word	0xA60000D4  /* 001FDDA4 sh $zero,212($s0) */
	.word	0x46000824  /* 001FDDA8 trunc.w.s $f0,$f1 */
	.word	0x44020000  /* 001FDDAC mfc1 $v0,$f0 */
	.word	0x00051D03  /* 001FDDB0 sra $v1,$a1,0x14 */
	.word	0x00192103  /* 001FDDB4 sra $a0,$t9,0x4 */
	.word	0x00641826  /* 001FDDB8 xor $v1,$v1,$a0 */
	.word	0x0003882B  /* 001FDDBC sltu $s1,$zero,$v1 */
	.word	0xA60200D4  /* 001FDDC0 sh $v0,212($s0) */
	.word	0x860200D6  /* 001FDDC4 lh $v0,214($s0) */
	.word	0x0441001B  /* 001FDDC8 bgez $v0,.L001FDE38 */
	.word	0x3125000F  /* 001FDDCC andi $a1,$t1,0xf */
	.word	0x2402FFF0  /* 001FDDD0 li $v0,-16 */
	.word	0x01221024  /* 001FDDD4 and $v0,$t1,$v0 */
	.word	0x00021400  /* 001FDDD8 sll $v0,$v0,0x10 */
	.word	0x10A00011  /* 001FDDDC beqz $a1,.L001FDE24 */
	.word	0x00023403  /* 001FDDE0 sra $a2,$v0,0x10 */
	.word	0xC4E10000  /* 001FDDE4 lwc1 $f1,-16900($a3) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x00091400  /* 001FDDE8 sll $v0,$t1,0x10 */
	.word	0x3C014080  /* 001FDDEC lui $at,0x4080 */
	.word	0x44811000  /* 001FDDF0 mtc1 $at,$f2 */
	.word	0x00021403  /* 001FDDF4 sra $v0,$v0,0x10 */
	.word	0x44820000  /* 001FDDF8 mtc1 $v0,$f0 */
	.word	0x46800020  /* 001FDDFC cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDE00 mul.s $f1,$f1,$f2 */
	.word	0x46010001  /* 001FDE04 sub.s $f0,$f0,$f1 */
	.word	0x46000064  /* 001FDE08 trunc.w.s $f1,$f0 */
	.word	0x44020800  /* 001FDE0C mfc1 $v0,$f1 */
	.word	0x00021C00  /* 001FDE10 sll $v1,$v0,0x10 */
	.word	0x00031C03  /* 001FDE14 sra $v1,$v1,0x10 */
	.word	0x1C600005  /* 001FDE18 bgtz $v1,.L001FDE30 */
	.word	0xA60200D0  /* 001FDE1C sh $v0,208($s0) */
	.word	0xA60000D0  /* 001FDE20 sh $zero,208($s0) */
	.word	0x1000005B  /* 001FDE24 b .L001FDF94 */
	.word	0xA60000D6  /* 001FDE28 sh $zero,214($s0) */
	.word	0x00000000  /* 001FDE2C nop */
	.word	0x10000023  /* 001FDE30 b .L001FDEC0 */
	.word	0x00C3102A  /* 001FDE34 slt $v0,$a2,$v1 */
	.word	0x18400056  /* 001FDE38 blez $v0,.L001FDF94 */
	.word	0x2402FFF0  /* 001FDE3C li $v0,-16 */
	.word	0x000E2400  /* 001FDE40 sll $a0,$t6,0x10 */
	.word	0x01221024  /* 001FDE44 and $v0,$t1,$v0 */
	.word	0x000C1C00  /* 001FDE48 sll $v1,$t4,0x10 */
	.word	0x00021400  /* 001FDE4C sll $v0,$v0,0x10 */
	.word	0x00042403  /* 001FDE50 sra $a0,$a0,0x10 */
	.word	0x00031C03  /* 001FDE54 sra $v1,$v1,0x10 */
	.word	0x00021403  /* 001FDE58 sra $v0,$v0,0x10 */
	.word	0x00832023  /* 001FDE5C subu $a0,$a0,$v1 */
	.word	0x3125000F  /* 001FDE60 andi $a1,$t1,0xf */
	.word	0x24460010  /* 001FDE64 addiu $a2,$v0,16 */
	.word	0x10A0004A  /* 001FDE68 beqz $a1,.L001FDF94 */
	.word	0x00042100  /* 001FDE6C sll $a0,$a0,0x4 */
	.word	0xC4E10000  /* 001FDE70 lwc1 $f1,-16900($a3) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x00091400  /* 001FDE74 sll $v0,$t1,0x10 */
	.word	0x3C014080  /* 001FDE78 lui $at,0x4080 */
	.word	0x44811000  /* 001FDE7C mtc1 $at,$f2 */
	.word	0x00021403  /* 001FDE80 sra $v0,$v0,0x10 */
	.word	0x44820000  /* 001FDE84 mtc1 $v0,$f0 */
	.word	0x46800020  /* 001FDE88 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDE8C mul.s $f1,$f1,$f2 */
	.word	0x46010000  /* 001FDE90 add.s $f0,$f0,$f1 */
	.word	0x46000064  /* 001FDE94 trunc.w.s $f1,$f0 */
	.word	0x44020800  /* 001FDE98 mfc1 $v0,$f1 */
	.word	0x00021C00  /* 001FDE9C sll $v1,$v0,0x10 */
	.word	0xA60200D0  /* 001FDEA0 sh $v0,208($s0) */
	.word	0x00031C03  /* 001FDEA4 sra $v1,$v1,0x10 */
	.word	0x0064102A  /* 001FDEA8 slt $v0,$v1,$a0 */
	.word	0x54400004  /* 001FDEAC bnezl $v0,.L001FDEC0 */
	.word	0x0066102A  /* 001FDEB0 slt $v0,$v1,$a2 */
	.word	0x1000FFDB  /* 001FDEB4 b .L001FDE24 */
	.word	0xA60400D0  /* 001FDEB8 sh $a0,208($s0) */
	.word	0x00000000  /* 001FDEBC nop */
	.word	0x14400034  /* 001FDEC0 bnez $v0,.L001FDF94 */
	.word	0x00000000  /* 001FDEC4 nop */
	.word	0x1000FFD6  /* 001FDEC8 b .L001FDE24 */
	.word	0xA60600D0  /* 001FDECC sh $a2,208($s0) */
	.word	0x00091C00  /* 001FDED0 sll $v1,$t1,0x10 */
	.word	0x00023C03  /* 001FDED4 sra $a3,$v0,0x10 */
	.word	0x00032C03  /* 001FDED8 sra $a1,$v1,0x10 */
	.word	0x00E61023  /* 001FDEDC subu $v0,$a3,$a2 */
	.word	0x00022100  /* 001FDEE0 sll $a0,$v0,0x4 */
	.word	0x00A4182A  /* 001FDEE4 slt $v1,$a1,$a0 */
	.word	0x5060001B  /* 001FDEE8 beqzl $v1,.L001FDF58 */
	.word	0x8E450000  /* 001FDEEC lw $a1,23496($s2) */
	.reloc	.-4, R_MIPS_LO16, D_00425BC8
	.word	0x3C020000  /* 001FDEF0 lui $v0,%hi(D_002BBDFC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDFC
	.word	0x3C014080  /* 001FDEF4 lui $at,0x4080 */
	.word	0x44811000  /* 001FDEF8 mtc1 $at,$f2 */
	.word	0xC4410000  /* 001FDEFC lwc1 $f1,%lo(D_002BBDFC)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDFC
	.word	0x44850000  /* 001FDF00 mtc1 $a1,$f0 */
	.word	0x46800020  /* 001FDF04 cvt.s.w $f0,$f0 */
	.word	0x46020842  /* 001FDF08 mul.s $f1,$f1,$f2 */
	.word	0x46010000  /* 001FDF0C add.s $f0,$f0,$f1 */
	.word	0x460000A4  /* 001FDF10 trunc.w.s $f2,$f0 */
	.word	0x44031000  /* 001FDF14 mfc1 $v1,$f2 */
	.word	0x00032C00  /* 001FDF18 sll $a1,$v1,0x10 */
	.word	0x00051403  /* 001FDF1C sra $v0,$a1,0x10 */
	.word	0x0082102A  /* 001FDF20 slt $v0,$a0,$v0 */
	.word	0x10400004  /* 001FDF24 beqz $v0,.L001FDF38 */
	.word	0xA60300D0  /* 001FDF28 sh $v1,208($s0) */
	.word	0xA60400D0  /* 001FDF2C sh $a0,208($s0) */
	.word	0x1000FFBC  /* 001FDF30 b .L001FDE24 */
	.word	0x24110001  /* 001FDF34 li $s1,1 */
	.word	0x46000824  /* 001FDF38 trunc.w.s $f0,$f1 */
	.word	0x44020000  /* 001FDF3C mfc1 $v0,$f0 */
	.word	0x000D1903  /* 001FDF40 sra $v1,$t5,0x4 */
	.word	0x00052503  /* 001FDF44 sra $a0,$a1,0x14 */
	.word	0x10830012  /* 001FDF48 beq $a0,$v1,.L001FDF94 */
	.word	0xA60200D6  /* 001FDF4C sh $v0,214($s0) */
	.word	0x10000010  /* 001FDF50 b .L001FDF94 */
	.word	0x24110001  /* 001FDF54 li $s1,1 */
	.word	0x3C030000  /* 001FDF58 lui $v1,%hi(D_00640DE8) */
	.reloc	.-4, R_MIPS_HI16, D_00640DE8
	.word	0x8C640000  /* 001FDF5C lw $a0,%lo(D_00640DE8)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_00640DE8
	.word	0x8CA20008  /* 001FDF60 lw $v0,8($a1) */
	.word	0x00441024  /* 001FDF64 and $v0,$v0,$a0 */
	.word	0x1040000A  /* 001FDF68 beqz $v0,.L001FDF94 */
	.word	0x24020002  /* 001FDF6C li $v0,2 */
	.word	0x10E2FF0E  /* 001FDF70 beq $a3,$v0,.L001FDBAC */
	.word	0x00181400  /* 001FDF74 sll $v0,$t8,0x10 */
	.word	0xA60000D0  /* 001FDF78 sh $zero,208($s0) */
	.word	0x24110001  /* 001FDF7C li $s1,1 */
	.word	0x10000004  /* 001FDF80 b .L001FDF94 */
	.word	0xA60000D2  /* 001FDF84 sh $zero,210($s0) */
	.word	0x0C000000  /* 001FDF88 jal func_001fe1b8 */
	.reloc	.-4, R_MIPS_26, func_001fe1b8
	.word	0x0200202D  /* 001FDF8C move $a0,$s0 */
	.word	0x0040882D  /* 001FDF90 move $s1,$v0 */
	.word	0x0C000000  /* 001FDF94 jal func_001fe408 */
	.reloc	.-4, R_MIPS_26, func_001fe408
	.word	0x0200202D  /* 001FDF98 move $a0,$s0 */
	.word	0x52200005  /* 001FDF9C beqzl $s1,.L001FDFB4 */
	.word	0xDFB00000  /* 001FDFA0 ld $s0,0($sp) */
	.word	0x0C000000  /* 001FDFA4 jal func_0011d768 */
	.reloc	.-4, R_MIPS_26, func_0011d768
	.word	0x24040001  /* 001FDFA8 li $a0,1 */
	.word	0xAE000098  /* 001FDFAC sw $zero,152($s0) */
	.word	0xDFB00000  /* 001FDFB0 ld $s0,0($sp) */
	.word	0xDFB10008  /* 001FDFB4 ld $s1,8($sp) */
	.word	0xDFB20010  /* 001FDFB8 ld $s2,16($sp) */
	.word	0xDFB30018  /* 001FDFBC ld $s3,24($sp) */
	.word	0xDFBF0020  /* 001FDFC0 ld $ra,32($sp) */
	.word	0x03E00008  /* 001FDFC4 jr $ra */
	.word	0x27BD0030  /* 001FDFC8 addiu $sp,$sp,48 */
	.end	func_001fd858
