/* func_001636d0: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001636d0,"ax",@progbits
	.globl	func_001636d0
	.ent	func_001636d0
func_001636d0:  /* 0x001636D0 */
	.word	0x27BDFE20  /* 001636D0 addiu $sp,$sp,-480 */
	.word	0x2406FFFF  /* 001636D4 li $a2,-1 */
	.word	0xFFB401A0  /* 001636D8 sd $s4,416($sp) */
	.word	0x0080A02D  /* 001636DC move $s4,$a0 */
	.word	0xFFB00180  /* 001636E0 sd $s0,384($sp) */
	.word	0xFFB10188  /* 001636E4 sd $s1,392($sp) */
	.word	0xFFB20190  /* 001636E8 sd $s2,400($sp) */
	.word	0xFFB30198  /* 001636EC sd $s3,408($sp) */
	.word	0xFFB501A8  /* 001636F0 sd $s5,424($sp) */
	.word	0xFFB601B0  /* 001636F4 sd $s6,432($sp) */
	.word	0xFFB701B8  /* 001636F8 sd $s7,440($sp) */
	.word	0xFFBE01C0  /* 001636FC sd $s8,448($sp) */
	.word	0xFFBF01C8  /* 00163700 sd $ra,456($sp) */
	.word	0xE7B501D8  /* 00163704 swc1 $f21,472($sp) */
	.word	0xE7B401D0  /* 00163708 swc1 $f20,464($sp) */
	.word	0x8E840000  /* 0016370C lw $a0,0($s4) */
	.word	0xAFA50160  /* 00163710 sw $a1,352($sp) */
	.word	0x8E82000C  /* 00163714 lw $v0,12($s4) */
	.word	0x8C830000  /* 00163718 lw $v1,0($a0) */
	.word	0x00021103  /* 0016371C sra $v0,$v0,0x4 */
	.word	0x30420001  /* 00163720 andi $v0,$v0,0x1 */
	.word	0x8C630008  /* 00163724 lw $v1,8($v1) */
	.word	0xAFA20168  /* 00163728 sw $v0,360($sp) */
	.word	0x8C620020  /* 0016372C lw $v0,32($v1) */
	.word	0x10460007  /* 00163730 beq $v0,$a2,.L00163750 */
	.word	0x00021080  /* 00163734 sll $v0,$v0,0x2 */
	.word	0x8CA30014  /* 00163738 lw $v1,20($a1) */
	.word	0x3C04FDFF  /* 0016373C lui $a0,0xfdff */
	.word	0x00621821  /* 00163740 addu $v1,$v1,$v0 */
	.word	0x1000000C  /* 00163744 b .L00163778 */
	.word	0x3484FFFF  /* 00163748 ori $a0,$a0,0xffff */
	.word	0x00000000  /* 0016374C nop */
	.word	0x8C650010  /* 00163750 lw $a1,16($v1) */
	.word	0x24020001  /* 00163754 li $v0,1 */
	.word	0x50A2000D  /* 00163758 beql $a1,$v0,.L00163790 */
	.word	0x8C820000  /* 0016375C lw $v0,0($a0) */
	.word	0x8FA20160  /* 00163760 lw $v0,352($sp) */
	.word	0x3C04FDFF  /* 00163764 lui $a0,0xfdff */
	.word	0x3484FFFF  /* 00163768 ori $a0,$a0,0xffff */
	.word	0x8C430014  /* 0016376C lw $v1,20($v0) */
	.word	0x00051080  /* 00163770 sll $v0,$a1,0x2 */
	.word	0x00621821  /* 00163774 addu $v1,$v1,$v0 */
	.word	0x2463FFFC  /* 00163778 addiu $v1,$v1,-4 */
	.word	0x8C620000  /* 0016377C lw $v0,0($v1) */
	.word	0x00441024  /* 00163780 and $v0,$v0,$a0 */
	.word	0xAC620000  /* 00163784 sw $v0,0($v1) */
	.word	0x8E840000  /* 00163788 lw $a0,0($s4) */
	.word	0x8C820000  /* 0016378C lw $v0,0($a0) */
	.word	0xAFA00164  /* 00163790 sw $zero,356($sp) */
	.word	0x84430000  /* 00163794 lh $v1,0($v0) */
	.word	0x186003E5  /* 00163798 blez $v1,.L00164730 */
	.word	0x8C420004  /* 0016379C lw $v0,4($v0) */
	.word	0x3C013F80  /* 001637A0 lui $at,0x3f80 */
	.word	0x4481A800  /* 001637A4 mtc1 $at,$f21 */
	.word	0x0000B02D  /* 001637A8 move $s6,$zero */
	.word	0xAFA20178  /* 001637AC sw $v0,376($sp) */
	.word	0x8FA50160  /* 001637B0 lw $a1,352($sp) */
	.word	0x8FA20164  /* 001637B4 lw $v0,356($sp) */
	.word	0x8CA30014  /* 001637B8 lw $v1,20($a1) */
	.word	0x00028080  /* 001637BC sll $s0,$v0,0x2 */
	.word	0x02031821  /* 001637C0 addu $v1,$s0,$v1 */
	.word	0x8C7E0000  /* 001637C4 lw $s8,0($v1) */
	.word	0x001E1682  /* 001637C8 srl $v0,$s8,0x1a */
	.word	0x30420001  /* 001637CC andi $v0,$v0,0x1 */
	.word	0x544003CD  /* 001637D0 bnezl $v0,.L00164708 */
	.word	0x8FA50164  /* 001637D4 lw $a1,356($sp) */
	.word	0x8FA30178  /* 001637D8 lw $v1,376($sp) */
	.word	0x8C62002C  /* 001637DC lw $v0,44($v1) */
	.word	0x240303FF  /* 001637E0 li $v1,1023 */
	.word	0x304203FF  /* 001637E4 andi $v0,$v0,0x3ff */
	.word	0x54430013  /* 001637E8 bnel $v0,$v1,.L00163838 */
	.word	0x8E840150  /* 001637EC lw $a0,336($s4) */
	.word	0x8E830150  /* 001637F0 lw $v1,336($s4) */
	.word	0x3C040000  /* 001637F4 lui $a0,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0xAFB6016C  /* 001637F8 sw $s6,364($sp) */
	.word	0x24930000  /* 001637FC addiu $s3,$a0,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x02C31821  /* 00163800 addu $v1,$s6,$v1 */
	.word	0x3C110000  /* 00163804 lui $s1,0x35 */
	.reloc	.-4, R_MIPS_HI16, D_00351E10
	.word	0xC4600000  /* 00163808 lwc1 $f0,0($v1) */
	.word	0xE4600010  /* 0016380C swc1 $f0,16($v1) */
	.word	0x8E820150  /* 00163810 lw $v0,336($s4) */
	.word	0x02C21021  /* 00163814 addu $v0,$s6,$v0 */
	.word	0xC4400004  /* 00163818 lwc1 $f0,4($v0) */
	.word	0xE4400014  /* 0016381C swc1 $f0,20($v0) */
	.word	0x8E830150  /* 00163820 lw $v1,336($s4) */
	.word	0x02C31821  /* 00163824 addu $v1,$s6,$v1 */
	.word	0xC4600008  /* 00163828 lwc1 $f0,8($v1) */
	.word	0x1000000E  /* 0016382C b .L00163868 */
	.word	0xE4600018  /* 00163830 swc1 $f0,24($v1) */
	.word	0x00000000  /* 00163834 nop */
	.word	0x00022980  /* 00163838 sll $a1,$v0,0x6 */
	.word	0x3C130000  /* 0016383C lui $s3,%hi(D_00351E10) */
	.reloc	.-4, R_MIPS_HI16, D_00351E10
	.word	0x26730000  /* 00163840 addiu $s3,$s3,%lo(D_00351E10) */
	.reloc	.-4, R_MIPS_LO16, D_00351E10
	.word	0x02659821  /* 00163844 addu $s3,$s3,$a1 */
	.word	0x3C110000  /* 00163848 lui $s1,0x35 */
	.reloc	.-4, R_MIPS_HI16, D_00351E10
	.word	0x00852821  /* 0016384C addu $a1,$a0,$a1 */
	.word	0x00962021  /* 00163850 addu $a0,$a0,$s6 */
	.word	0x0080302D  /* 00163854 move $a2,$a0 */
	.word	0x24840000  /* 00163858 addiu $a0,$a0,16 */
	.reloc	.-4, R_MIPS_LO16, D_00573F10-0x3f00
	.word	0x24A50010  /* 0016385C addiu $a1,$a1,16 */
	.word	0x0C000000  /* 00163860 jal func_001627d0 */
	.reloc	.-4, R_MIPS_26, func_001627d0
	.word	0xAFB6016C  /* 00163864 sw $s6,364($sp) */
	.word	0x8E820158  /* 00163868 lw $v0,344($s4) */
	.word	0x001E9542  /* 0016386C srl $s2,$s8,0x15 */
	.word	0x26230000  /* 00163870 addiu $v1,$s1,7696 */
	.reloc	.-4, R_MIPS_LO16, D_00351E10
	.word	0x0000882D  /* 00163874 move $s1,$zero */
	.word	0x32470003  /* 00163878 andi $a3,$s2,0x3 */
	.word	0x24040001  /* 0016387C li $a0,1 */
	.word	0x02C3B821  /* 00163880 addu $s7,$s6,$v1 */
	.word	0x4480A000  /* 00163884 mtc1 $zero,$f20 */
	.word	0x10E40009  /* 00163888 beq $a3,$a0,.L001638B0 */
	.word	0x0056A821  /* 0016388C addu $s5,$v0,$s6 */
	.word	0x10E0023F  /* 00163890 beqz $a3,.L00164190 */
	.word	0x001E3482  /* 00163894 srl $a2,$s8,0x12 */
	.word	0x28E20004  /* 00163898 slti $v0,$a3,4 */
	.word	0x1040023D  /* 0016389C beqz $v0,.L00164194 */
	.word	0x001E1882  /* 001638A0 srl $v1,$s8,0x2 */
	.word	0x100000A2  /* 001638A4 b .L00163B30 */
	.word	0x8E82000C  /* 001638A8 lw $v0,12($s4) */
	.word	0x00000000  /* 001638AC nop */
	.word	0x8FA4016C  /* 001638B0 lw $a0,364($sp) */
	.word	0x27B30050  /* 001638B4 addiu $s3,$sp,80 */
	.word	0x8E820150  /* 001638B8 lw $v0,336($s4) */
	.word	0x3C030000  /* 001638BC lui $v1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x0260282D  /* 001638C0 move $a1,$s3 */
	.word	0x24720000  /* 001638C4 addiu $s2,$v1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x00821021  /* 001638C8 addu $v0,$a0,$v0 */
	.word	0xC4400030  /* 001638CC lwc1 $f0,48($v0) */
	.word	0xE6A00030  /* 001638D0 swc1 $f0,48($s5) */
	.word	0x8E820150  /* 001638D4 lw $v0,336($s4) */
	.word	0x00821021  /* 001638D8 addu $v0,$a0,$v0 */
	.word	0xC4400034  /* 001638DC lwc1 $f0,52($v0) */
	.word	0xE6A00034  /* 001638E0 swc1 $f0,52($s5) */
	.word	0x8E820150  /* 001638E4 lw $v0,336($s4) */
	.word	0x00821021  /* 001638E8 addu $v0,$a0,$v0 */
	.word	0xC4400038  /* 001638EC lwc1 $f0,56($v0) */
	.word	0xE6A00038  /* 001638F0 swc1 $f0,56($s5) */
	.word	0x8FA20178  /* 001638F4 lw $v0,376($sp) */
	.word	0x8C44002C  /* 001638F8 lw $a0,44($v0) */
	.word	0x8E820154  /* 001638FC lw $v0,340($s4) */
	.word	0x308403FF  /* 00163900 andi $a0,$a0,0x3ff */
	.word	0x00042180  /* 00163904 sll $a0,$a0,0x6 */
	.word	0x0C000000  /* 00163908 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x00442021  /* 0016390C addu $a0,$v0,$a0 */
	.word	0x0260282D  /* 00163910 move $a1,$s3 */
	.word	0x8FA30160  /* 00163914 lw $v1,352($sp) */
	.word	0x03A0202D  /* 00163918 move $a0,$sp */
	.word	0x27A60010  /* 0016391C addiu $a2,$sp,16 */
	.word	0x8C620014  /* 00163920 lw $v0,20($v1) */
	.word	0x02021021  /* 00163924 addu $v0,$s0,$v0 */
	.word	0x8C430004  /* 00163928 lw $v1,4($v0) */
	.word	0xE7B5001C  /* 0016392C swc1 $f21,28($sp) */
	.word	0x00033AC2  /* 00163930 srl $a3,$v1,0xb */
	.word	0x00031CC2  /* 00163934 srl $v1,$v1,0x13 */
	.word	0x30630200  /* 00163938 andi $v1,$v1,0x200 */
	.word	0x30E701FF  /* 0016393C andi $a3,$a3,0x1ff */
	.word	0x00678025  /* 00163940 or $s0,$v1,$a3 */
	.word	0x2602FFFF  /* 00163944 addiu $v0,$s0,-1 */
	.word	0x00021180  /* 00163948 sll $v0,$v0,0x6 */
	.word	0x00523821  /* 0016394C addu $a3,$v0,$s2 */
	.word	0x00E0182D  /* 00163950 move $v1,$a3 */
	.word	0xC4E20038  /* 00163954 lwc1 $f2,56($a3) */
	.word	0x0060102D  /* 00163958 move $v0,$v1 */
	.word	0xC4600030  /* 0016395C lwc1 $f0,48($v1) */
	.word	0xC4410034  /* 00163960 lwc1 $f1,52($v0) */
	.word	0xE7A00010  /* 00163964 swc1 $f0,16($sp) */
	.word	0xE7A10014  /* 00163968 swc1 $f1,20($sp) */
	.word	0x0C000000  /* 0016396C jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xE7A20018  /* 00163970 swc1 $f2,24($sp) */
	.word	0x33C30003  /* 00163974 andi $v1,$s8,0x3 */
	.word	0x24020003  /* 00163978 li $v0,3 */
	.word	0x54620020  /* 0016397C bnel $v1,$v0,.L00163A00 */
	.word	0x8FA5016C  /* 00163980 lw $a1,364($sp) */
	.word	0x001E1882  /* 00163984 srl $v1,$s8,0x2 */
	.word	0x001E1482  /* 00163988 srl $v0,$s8,0x12 */
	.word	0x306301FF  /* 0016398C andi $v1,$v1,0x1ff */
	.word	0x30420200  /* 00163990 andi $v0,$v0,0x200 */
	.word	0x00438825  /* 00163994 or $s1,$v0,$v1 */
	.word	0x27A20040  /* 00163998 addiu $v0,$sp,64 */
	.word	0x2644FFF0  /* 0016399C addiu $a0,$s2,-16 */
	.word	0x00113180  /* 001639A0 sll $a2,$s1,0x6 */
	.word	0x00C43021  /* 001639A4 addu $a2,$a2,$a0 */
	.word	0x0040202D  /* 001639A8 move $a0,$v0 */
	.word	0x0C000000  /* 001639AC jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x0260282D  /* 001639B0 move $a1,$s3 */
	.word	0x8E820150  /* 001639B4 lw $v0,336($s4) */
	.word	0x8FA4016C  /* 001639B8 lw $a0,364($sp) */
	.word	0x4600A346  /* 001639BC mov.s $f13,$f20 */
	.word	0x8FA30178  /* 001639C0 lw $v1,376($sp) */
	.word	0x0000282D  /* 001639C4 move $a1,$zero */
	.word	0x00821021  /* 001639C8 addu $v0,$a0,$v0 */
	.word	0x03A0202D  /* 001639CC move $a0,$sp */
	.word	0xC44C0000  /* 001639D0 lwc1 $f12,0($v0) */
	.word	0x02A0302D  /* 001639D4 move $a2,$s5 */
	.word	0xC4600050  /* 001639D8 lwc1 $f0,80($v1) */
	.word	0x0000382D  /* 001639DC move $a3,$zero */
	.word	0xC44E0020  /* 001639E0 lwc1 $f14,32($v0) */
	.word	0x27A20040  /* 001639E4 addiu $v0,$sp,64 */
	.word	0x46006302  /* 001639E8 mul.s $f12,$f12,$f0 */
	.word	0x46006BC6  /* 001639EC mov.s $f15,$f13 */
	.word	0x0C000000  /* 001639F0 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0x0040402D  /* 001639F4 move $t0,$v0 */
	.word	0x10000011  /* 001639F8 b .L00163A40 */
	.word	0x26E20030  /* 001639FC addiu $v0,$s7,48 */
	.word	0x4600A346  /* 00163A00 mov.s $f13,$f20 */
	.word	0x8E820150  /* 00163A04 lw $v0,336($s4) */
	.word	0x03A0202D  /* 00163A08 move $a0,$sp */
	.word	0x8FA30178  /* 00163A0C lw $v1,376($sp) */
	.word	0x02A0302D  /* 00163A10 move $a2,$s5 */
	.word	0x00A21021  /* 00163A14 addu $v0,$a1,$v0 */
	.word	0x0000282D  /* 00163A18 move $a1,$zero */
	.word	0xC4600050  /* 00163A1C lwc1 $f0,80($v1) */
	.word	0x0000382D  /* 00163A20 move $a3,$zero */
	.word	0xC44C0000  /* 00163A24 lwc1 $f12,0($v0) */
	.word	0x46006BC6  /* 00163A28 mov.s $f15,$f13 */
	.word	0xC44E0020  /* 00163A2C lwc1 $f14,32($v0) */
	.word	0x0000402D  /* 00163A30 move $t0,$zero */
	.word	0x0C000000  /* 00163A34 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0x46006302  /* 00163A38 mul.s $f12,$f12,$f0 */
	.word	0x26E20030  /* 00163A3C addiu $v0,$s7,48 */
	.word	0x8E900150  /* 00163A40 lw $s0,336($s4) */
	.word	0xAFA20170  /* 00163A44 sw $v0,368($sp) */
	.word	0x27A400D0  /* 00163A48 addiu $a0,$sp,208 */
	.word	0x02D08021  /* 00163A4C addu $s0,$s6,$s0 */
	.word	0x02A0282D  /* 00163A50 move $a1,$s5 */
	.word	0x0C000000  /* 00163A54 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00163A58 lwc1 $f12,0($s0) */
	.word	0x26A50010  /* 00163A5C addiu $a1,$s5,16 */
	.word	0xC60C0004  /* 00163A60 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00163A64 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A400E0  /* 00163A68 addiu $a0,$sp,224 */
	.word	0x26A50020  /* 00163A6C addiu $a1,$s5,32 */
	.word	0xC60C0008  /* 00163A70 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00163A74 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A400F0  /* 00163A78 addiu $a0,$sp,240 */
	.word	0x26A50030  /* 00163A7C addiu $a1,$s5,48 */
	.word	0x0C000000  /* 00163A80 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x27A40100  /* 00163A84 addiu $a0,$sp,256 */
	.word	0x8E820154  /* 00163A88 lw $v0,340($s4) */
	.word	0x8FA30178  /* 00163A8C lw $v1,376($sp) */
	.word	0x27A600D0  /* 00163A90 addiu $a2,$sp,208 */
	.word	0x00562021  /* 00163A94 addu $a0,$v0,$s6 */
	.word	0x8C65002C  /* 00163A98 lw $a1,44($v1) */
	.word	0x30A503FF  /* 00163A9C andi $a1,$a1,0x3ff */
	.word	0x00052980  /* 00163AA0 sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00163AA4 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00452821  /* 00163AA8 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00163AAC lw $v0,340($s4) */
	.word	0x8FA40178  /* 00163AB0 lw $a0,376($sp) */
	.word	0x8E860150  /* 00163AB4 lw $a2,336($s4) */
	.word	0x8C85002C  /* 00163AB8 lw $a1,44($a0) */
	.word	0x00562021  /* 00163ABC addu $a0,$v0,$s6 */
	.word	0x00D63021  /* 00163AC0 addu $a2,$a2,$s6 */
	.word	0x24840030  /* 00163AC4 addiu $a0,$a0,48 */
	.word	0x30A503FF  /* 00163AC8 andi $a1,$a1,0x3ff */
	.word	0x24C60030  /* 00163ACC addiu $a2,$a2,48 */
	.word	0x00052980  /* 00163AD0 sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00163AD4 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x00452821  /* 00163AD8 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00163ADC lw $v0,340($s4) */
	.word	0x02E0202D  /* 00163AE0 move $a0,$s7 */
	.word	0x02C21021  /* 00163AE4 addu $v0,$s6,$v0 */
	.word	0xE455003C  /* 00163AE8 swc1 $f21,60($v0) */
	.word	0x8E860150  /* 00163AEC lw $a2,336($s4) */
	.word	0x8E850154  /* 00163AF0 lw $a1,340($s4) */
	.word	0x00D63021  /* 00163AF4 addu $a2,$a2,$s6 */
	.word	0x00B62821  /* 00163AF8 addu $a1,$a1,$s6 */
	.word	0x0C000000  /* 00163AFC jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x24C60010  /* 00163B00 addiu $a2,$a2,16 */
	.word	0x8E840154  /* 00163B04 lw $a0,340($s4) */
	.word	0x8FA50178  /* 00163B08 lw $a1,376($sp) */
	.word	0x00962021  /* 00163B0C addu $a0,$a0,$s6 */
	.word	0x24A60050  /* 00163B10 addiu $a2,$a1,80 */
	.word	0x0080282D  /* 00163B14 move $a1,$a0 */
	.word	0x0C000000  /* 00163B18 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24840070  /* 00163B1C addiu $a0,$a0,112 */
	.word	0x8E820154  /* 00163B20 lw $v0,340($s4) */
	.word	0x02C21021  /* 00163B24 addu $v0,$s6,$v0 */
	.word	0x100002ED  /* 00163B28 b .L001646E0 */
	.word	0xE455007C  /* 00163B2C swc1 $f21,124($v0) */
	.word	0x30420003  /* 00163B30 andi $v0,$v0,0x3 */
	.word	0x5040001E  /* 00163B34 beqzl $v0,.L00163BB0 */
	.word	0x8E820150  /* 00163B38 lw $v0,336($s4) */
	.word	0x8E840000  /* 00163B3C lw $a0,0($s4) */
	.word	0x0080382D  /* 00163B40 move $a3,$a0 */
	.word	0x8FA40164  /* 00163B44 lw $a0,356($sp) */
	.word	0x8CE30000  /* 00163B48 lw $v1,0($a3) */
	.word	0x8C630008  /* 00163B4C lw $v1,8($v1) */
	.word	0x8C620090  /* 00163B50 lw $v0,144($v1) */
	.word	0x2442FFFF  /* 00163B54 addiu $v0,$v0,-1 */
	.word	0x14820005  /* 00163B58 bne $a0,$v0,.L00163B70 */
	.word	0x0000302D  /* 00163B5C move $a2,$zero */
	.word	0xC4740000  /* 00163B60 lwc1 $f20,0($v1) */
	.word	0x10000011  /* 00163B64 b .L00163BAC */
	.word	0x24110001  /* 00163B68 li $s1,1 */
	.word	0x00000000  /* 00163B6C nop */
	.word	0x24C60001  /* 00163B70 addiu $a2,$a2,1 */
	.word	0x28C20004  /* 00163B74 slti $v0,$a2,4 */
	.word	0x1040000C  /* 00163B78 beqz $v0,.L00163BAC */
	.word	0x00062880  /* 00163B7C sll $a1,$a2,0x2 */
	.word	0x8CE20000  /* 00163B80 lw $v0,0($a3) */
	.word	0x8C440008  /* 00163B84 lw $a0,8($v0) */
	.word	0x00A41821  /* 00163B88 addu $v1,$a1,$a0 */
	.word	0x8C620090  /* 00163B8C lw $v0,144($v1) */
	.word	0x8FA30164  /* 00163B90 lw $v1,356($sp) */
	.word	0x2442FFFF  /* 00163B94 addiu $v0,$v0,-1 */
	.word	0x5462FFF6  /* 00163B98 bnel $v1,$v0,.L00163B74 */
	.word	0x24C60001  /* 00163B9C addiu $a2,$a2,1 */
	.word	0x00851021  /* 00163BA0 addu $v0,$a0,$a1 */
	.word	0x24110001  /* 00163BA4 li $s1,1 */
	.word	0xC4540000  /* 00163BA8 lwc1 $f20,0($v0) */
	.word	0x8E820150  /* 00163BAC lw $v0,336($s4) */
	.word	0x27A40050  /* 00163BB0 addiu $a0,$sp,80 */
	.word	0x0080282D  /* 00163BB4 move $a1,$a0 */
	.word	0x02C21021  /* 00163BB8 addu $v0,$s6,$v0 */
	.word	0xC4400030  /* 00163BBC lwc1 $f0,48($v0) */
	.word	0xE6A00030  /* 00163BC0 swc1 $f0,48($s5) */
	.word	0x8E820150  /* 00163BC4 lw $v0,336($s4) */
	.word	0x02C21021  /* 00163BC8 addu $v0,$s6,$v0 */
	.word	0xC4400034  /* 00163BCC lwc1 $f0,52($v0) */
	.word	0xE6A00034  /* 00163BD0 swc1 $f0,52($s5) */
	.word	0x8E820150  /* 00163BD4 lw $v0,336($s4) */
	.word	0x02C21021  /* 00163BD8 addu $v0,$s6,$v0 */
	.word	0xC4400038  /* 00163BDC lwc1 $f0,56($v0) */
	.word	0xE6A00038  /* 00163BE0 swc1 $f0,56($s5) */
	.word	0x8FA20178  /* 00163BE4 lw $v0,376($sp) */
	.word	0x8C44002C  /* 00163BE8 lw $a0,44($v0) */
	.word	0x8E820154  /* 00163BEC lw $v0,340($s4) */
	.word	0x308403FF  /* 00163BF0 andi $a0,$a0,0x3ff */
	.word	0x00042180  /* 00163BF4 sll $a0,$a0,0x6 */
	.word	0x0C000000  /* 00163BF8 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x00442021  /* 00163BFC addu $a0,$v0,$a0 */
	.word	0x8E820158  /* 00163C00 lw $v0,344($s4) */
	.word	0x8E850150  /* 00163C04 lw $a1,336($s4) */
	.word	0x00561021  /* 00163C08 addu $v0,$v0,$s6 */
	.word	0x00B62821  /* 00163C0C addu $a1,$a1,$s6 */
	.word	0x24530040  /* 00163C10 addiu $s3,$v0,64 */
	.word	0x24A40050  /* 00163C14 addiu $a0,$a1,80 */
	.word	0x24A60040  /* 00163C18 addiu $a2,$a1,64 */
	.word	0x0C000000  /* 00163C1C jal func_001627d0 */
	.reloc	.-4, R_MIPS_26, func_001627d0
	.word	0x24A50010  /* 00163C20 addiu $a1,$a1,16 */
	.word	0x3C013F80  /* 00163C24 lui $at,0x3f80 */
	.word	0x44813800  /* 00163C28 mtc1 $at,$f7 */
	.word	0x8FA30160  /* 00163C2C lw $v1,352($sp) */
	.word	0x3C050000  /* 00163C30 lui $a1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x24A50000  /* 00163C34 addiu $a1,$a1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x8C620014  /* 00163C38 lw $v0,20($v1) */
	.word	0x02021021  /* 00163C3C addu $v0,$s0,$v0 */
	.word	0x8C430008  /* 00163C40 lw $v1,8($v0) */
	.word	0xE7A7001C  /* 00163C44 swc1 $f7,28($sp) */
	.word	0x000322C2  /* 00163C48 srl $a0,$v1,0xb */
	.word	0x00031CC2  /* 00163C4C srl $v1,$v1,0x13 */
	.word	0x30630200  /* 00163C50 andi $v1,$v1,0x200 */
	.word	0x308401FF  /* 00163C54 andi $a0,$a0,0x1ff */
	.word	0x00648025  /* 00163C58 or $s0,$v1,$a0 */
	.word	0x2602FFFF  /* 00163C5C addiu $v0,$s0,-1 */
	.word	0x00021180  /* 00163C60 sll $v0,$v0,0x6 */
	.word	0x00452021  /* 00163C64 addu $a0,$v0,$a1 */
	.word	0x0080182D  /* 00163C68 move $v1,$a0 */
	.word	0xC4810038  /* 00163C6C lwc1 $f1,56($a0) */
	.word	0x0060102D  /* 00163C70 move $v0,$v1 */
	.word	0xC4600030  /* 00163C74 lwc1 $f0,48($v1) */
	.word	0xC4460034  /* 00163C78 lwc1 $f6,52($v0) */
	.word	0xE7A00010  /* 00163C7C swc1 $f0,16($sp) */
	.word	0xE7A60014  /* 00163C80 swc1 $f6,20($sp) */
	.word	0x12200060  /* 00163C84 beqz $s1,.L00163E08 */
	.word	0xE7A10018  /* 00163C88 swc1 $f1,24($sp) */
	.word	0x3C020000  /* 00163C8C lui $v0,%hi(D_00574F20) */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0x3C030000  /* 00163C90 lui $v1,%hi(D_00574F10) */
	.reloc	.-4, R_MIPS_HI16, D_00574F10
	.word	0x24510000  /* 00163C94 addiu $s1,$v0,%lo(D_00574F20) */
	.reloc	.-4, R_MIPS_LO16, D_00574F20
	.word	0x24700000  /* 00163C98 addiu $s0,$v1,%lo(D_00574F10) */
	.reloc	.-4, R_MIPS_LO16, D_00574F10
	.word	0xC6220000  /* 00163C9C lwc1 $f2,0($s1) */
	.word	0x27A40110  /* 00163CA0 addiu $a0,$sp,272 */
	.word	0xC6030000  /* 00163CA4 lwc1 $f3,0($s0) */
	.word	0x46020082  /* 00163CA8 mul.s $f2,$f0,$f2 */
	.word	0xC6200008  /* 00163CAC lwc1 $f0,8($s1) */
	.word	0x8FA30178  /* 00163CB0 lw $v1,376($sp) */
	.word	0x46000802  /* 00163CB4 mul.s $f0,$f1,$f0 */
	.word	0xC6010008  /* 00163CB8 lwc1 $f1,8($s0) */
	.word	0xC6250004  /* 00163CBC lwc1 $f5,4($s1) */
	.word	0x24620060  /* 00163CC0 addiu $v0,$v1,96 */
	.word	0x46031080  /* 00163CC4 add.s $f2,$f2,$f3 */
	.word	0xC6040004  /* 00163CC8 lwc1 $f4,4($s0) */
	.word	0x8FA50168  /* 00163CCC lw $a1,360($sp) */
	.word	0x46010000  /* 00163CD0 add.s $f0,$f0,$f1 */
	.word	0xE7A20110  /* 00163CD4 swc1 $f2,272($sp) */
	.word	0xC4410020  /* 00163CD8 lwc1 $f1,32($v0) */
	.word	0xE7A00118  /* 00163CDC swc1 $f0,280($sp) */
	.word	0x46013041  /* 00163CE0 sub.s $f1,$f6,$f1 */
	.word	0xE7A7011C  /* 00163CE4 swc1 $f7,284($sp) */
	.word	0xAFA00120  /* 00163CE8 sw $zero,288($sp) */
	.word	0x46050842  /* 00163CEC mul.s $f1,$f1,$f5 */
	.word	0x46040840  /* 00163CF0 add.s $f1,$f1,$f4 */
	.word	0xE7A10114  /* 00163CF4 swc1 $f1,276($sp) */
	.word	0xC4400020  /* 00163CF8 lwc1 $f0,32($v0) */
	.word	0xE7A7012C  /* 00163CFC swc1 $f7,300($sp) */
	.word	0x46000000  /* 00163D00 add.s $f0,$f0,$f0 */
	.word	0xAFA00128  /* 00163D04 sw $zero,296($sp) */
	.word	0x46140000  /* 00163D08 add.s $f0,$f0,$f20 */
	.word	0x46050002  /* 00163D0C mul.s $f0,$f0,$f5 */
	.word	0x0C000000  /* 00163D10 jal func_00118590 */
	.reloc	.-4, R_MIPS_26, func_00118590
	.word	0xE7A00124  /* 00163D14 swc1 $f0,292($sp) */
	.word	0x87A60140  /* 00163D18 lh $a2,320($sp) */
	.word	0x2402FFFF  /* 00163D1C li $v0,-1 */
	.word	0x10C20033  /* 00163D20 beq $a2,$v0,.L00163DF0 */
	.word	0x27A30050  /* 00163D24 addiu $v1,$sp,80 */
	.word	0x8E82000C  /* 00163D28 lw $v0,12($s4) */
	.word	0x30420002  /* 00163D2C andi $v0,$v0,0x2 */
	.word	0x1440000D  /* 00163D30 bnez $v0,.L00163D68 */
	.word	0xC6250004  /* 00163D34 lwc1 $f5,4($s1) */
	.word	0xC7A00014  /* 00163D38 lwc1 $f0,20($sp) */
	.word	0x46140000  /* 00163D3C add.s $f0,$f0,$f20 */
	.word	0xC6010004  /* 00163D40 lwc1 $f1,4($s0) */
	.word	0xC7A40134  /* 00163D44 lwc1 $f4,308($sp) */
	.word	0x46050002  /* 00163D48 mul.s $f0,$f0,$f5 */
	.word	0x46010000  /* 00163D4C add.s $f0,$f0,$f1 */
	.word	0x46002034  /* 00163D50 c.lt.s $f4,$f0 */
	.word	0x45000027  /* 00163D54 bc1f .L00163DF4 */
	.word	0x03A0202D  /* 00163D58 move $a0,$sp */
	.word	0x10000005  /* 00163D5C b .L00163D74 */
	.word	0x46012101  /* 00163D60 sub.s $f4,$f4,$f1 */
	.word	0x00000000  /* 00163D64 nop */
	.word	0xC6010004  /* 00163D68 lwc1 $f1,4($s0) */
	.word	0xC7A40134  /* 00163D6C lwc1 $f4,308($sp) */
	.word	0x46012101  /* 00163D70 sub.s $f4,$f4,$f1 */
	.word	0xC7A10138  /* 00163D74 lwc1 $f1,312($sp) */
	.word	0xC6060008  /* 00163D78 lwc1 $f6,8($s0) */
	.word	0x27A20050  /* 00163D7C addiu $v0,$sp,80 */
	.word	0xC6030000  /* 00163D80 lwc1 $f3,0($s0) */
	.word	0x0040282D  /* 00163D84 move $a1,$v0 */
	.word	0xC7A20130  /* 00163D88 lwc1 $f2,304($sp) */
	.word	0x46060841  /* 00163D8C sub.s $f1,$f1,$f6 */
	.word	0x00000000  /* 00163D90 nop */
	.word	0x00000000  /* 00163D94 nop */
	.word	0x46052103  /* 00163D98 div.s $f4,$f4,$f5 */
	.word	0xC6250008  /* 00163D9C lwc1 $f5,8($s1) */
	.word	0x46031081  /* 00163DA0 sub.s $f2,$f2,$f3 */
	.word	0xC6200000  /* 00163DA4 lwc1 $f0,0($s1) */
	.word	0x03A0202D  /* 00163DA8 move $a0,$sp */
	.word	0x27A60130  /* 00163DAC addiu $a2,$sp,304 */
	.word	0x00000000  /* 00163DB0 nop */
	.word	0x00000000  /* 00163DB4 nop */
	.word	0x46001083  /* 00163DB8 div.s $f2,$f2,$f0 */
	.word	0x46142101  /* 00163DBC sub.s $f4,$f4,$f20 */
	.word	0x00000000  /* 00163DC0 nop */
	.word	0x00000000  /* 00163DC4 nop */
	.word	0x46050843  /* 00163DC8 div.s $f1,$f1,$f5 */
	.word	0xE7A40134  /* 00163DCC swc1 $f4,308($sp) */
	.word	0xE7A20130  /* 00163DD0 swc1 $f2,304($sp) */
	.word	0x0C000000  /* 00163DD4 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xE7A10138  /* 00163DD8 swc1 $f1,312($sp) */
	.word	0x8E82000C  /* 00163DDC lw $v0,12($s4) */
	.word	0x3C030020  /* 00163DE0 lui $v1,0x20 */
	.word	0x00431025  /* 00163DE4 or $v0,$v0,$v1 */
	.word	0x1000000C  /* 00163DE8 b .L00163E1C */
	.word	0xAE82000C  /* 00163DEC sw $v0,12($s4) */
	.word	0x03A0202D  /* 00163DF0 move $a0,$sp */
	.word	0x0060282D  /* 00163DF4 move $a1,$v1 */
	.word	0x0C000000  /* 00163DF8 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x27A60010  /* 00163DFC addiu $a2,$sp,16 */
	.word	0x10000007  /* 00163E00 b .L00163E20 */
	.word	0x33C30003  /* 00163E04 andi $v1,$s8,0x3 */
	.word	0x27A20050  /* 00163E08 addiu $v0,$sp,80 */
	.word	0x03A0202D  /* 00163E0C move $a0,$sp */
	.word	0x0040282D  /* 00163E10 move $a1,$v0 */
	.word	0x0C000000  /* 00163E14 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x27A60010  /* 00163E18 addiu $a2,$sp,16 */
	.word	0x33C30003  /* 00163E1C andi $v1,$s8,0x3 */
	.word	0x24020003  /* 00163E20 li $v0,3 */
	.word	0x54620026  /* 00163E24 bnel $v1,$v0,.L00163EC0 */
	.word	0x8E820150  /* 00163E28 lw $v0,336($s4) */
	.word	0x001E1882  /* 00163E2C srl $v1,$s8,0x2 */
	.word	0x001E1482  /* 00163E30 srl $v0,$s8,0x12 */
	.word	0x30420200  /* 00163E34 andi $v0,$v0,0x200 */
	.word	0x306301FF  /* 00163E38 andi $v1,$v1,0x1ff */
	.word	0x00438825  /* 00163E3C or $s1,$v0,$v1 */
	.word	0x27A30040  /* 00163E40 addiu $v1,$sp,64 */
	.word	0x27A20050  /* 00163E44 addiu $v0,$sp,80 */
	.word	0x00113180  /* 00163E48 sll $a2,$s1,0x6 */
	.word	0x0060202D  /* 00163E4C move $a0,$v1 */
	.word	0x3C010000  /* 00163E50 lui $at,%hi(D_00573F00) */
	.reloc	.-4, R_MIPS_HI16, D_00573F00
	.word	0x24210000  /* 00163E54 addiu $at,$at,%lo(D_00573F00) */
	.reloc	.-4, R_MIPS_LO16, D_00573F00
	.word	0x00263021  /* 00163E58 addu $a2,$at,$a2 */
	.word	0x0C000000  /* 00163E5C jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x0040282D  /* 00163E60 move $a1,$v0 */
	.word	0x8E820150  /* 00163E64 lw $v0,336($s4) */
	.word	0x8FA30178  /* 00163E68 lw $v1,376($sp) */
	.word	0x32450003  /* 00163E6C andi $a1,$s2,0x3 */
	.word	0x02C21021  /* 00163E70 addu $v0,$s6,$v0 */
	.word	0x24A5FFFE  /* 00163E74 addiu $a1,$a1,-2 */
	.word	0xC46C0050  /* 00163E78 lwc1 $f12,80($v1) */
	.word	0x03A0202D  /* 00163E7C move $a0,$sp */
	.word	0xC46D0080  /* 00163E80 lwc1 $f13,128($v1) */
	.word	0x24430040  /* 00163E84 addiu $v1,$v0,64 */
	.word	0xC4400000  /* 00163E88 lwc1 $f0,0($v0) */
	.word	0x02A0302D  /* 00163E8C move $a2,$s5 */
	.word	0xC4610000  /* 00163E90 lwc1 $f1,0($v1) */
	.word	0x0260382D  /* 00163E94 move $a3,$s3 */
	.word	0x460C0302  /* 00163E98 mul.s $f12,$f0,$f12 */
	.word	0xC44E0020  /* 00163E9C lwc1 $f14,32($v0) */
	.word	0x46010002  /* 00163EA0 mul.s $f0,$f0,$f1 */
	.word	0xC46F0020  /* 00163EA4 lwc1 $f15,32($v1) */
	.word	0x27A20040  /* 00163EA8 addiu $v0,$sp,64 */
	.word	0x0040402D  /* 00163EAC move $t0,$v0 */
	.word	0x0C000000  /* 00163EB0 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0x460D0342  /* 00163EB4 mul.s $f13,$f0,$f13 */
	.word	0x10000015  /* 00163EB8 b .L00163F10 */
	.word	0x8FA30164  /* 00163EBC lw $v1,356($sp) */
	.word	0x32450003  /* 00163EC0 andi $a1,$s2,0x3 */
	.word	0x8FA30178  /* 00163EC4 lw $v1,376($sp) */
	.word	0x24A5FFFE  /* 00163EC8 addiu $a1,$a1,-2 */
	.word	0x02C21021  /* 00163ECC addu $v0,$s6,$v0 */
	.word	0x03A0202D  /* 00163ED0 move $a0,$sp */
	.word	0xC46C0050  /* 00163ED4 lwc1 $f12,80($v1) */
	.word	0x02A0302D  /* 00163ED8 move $a2,$s5 */
	.word	0xC46D0080  /* 00163EDC lwc1 $f13,128($v1) */
	.word	0x24430040  /* 00163EE0 addiu $v1,$v0,64 */
	.word	0xC4400000  /* 00163EE4 lwc1 $f0,0($v0) */
	.word	0x0260382D  /* 00163EE8 move $a3,$s3 */
	.word	0xC4610000  /* 00163EEC lwc1 $f1,0($v1) */
	.word	0x0000402D  /* 00163EF0 move $t0,$zero */
	.word	0x460C0302  /* 00163EF4 mul.s $f12,$f0,$f12 */
	.word	0xC44E0020  /* 00163EF8 lwc1 $f14,32($v0) */
	.word	0x46010002  /* 00163EFC mul.s $f0,$f0,$f1 */
	.word	0xC46F0020  /* 00163F00 lwc1 $f15,32($v1) */
	.word	0x0C000000  /* 00163F04 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0x460D0342  /* 00163F08 mul.s $f13,$f0,$f13 */
	.word	0x8FA30164  /* 00163F0C lw $v1,356($sp) */
	.word	0x26E20030  /* 00163F10 addiu $v0,$s7,48 */
	.word	0x8E900150  /* 00163F14 lw $s0,336($s4) */
	.word	0x27A400D0  /* 00163F18 addiu $a0,$sp,208 */
	.word	0x24630001  /* 00163F1C addiu $v1,$v1,1 */
	.word	0xAFA20170  /* 00163F20 sw $v0,368($sp) */
	.word	0xAFA30164  /* 00163F24 sw $v1,356($sp) */
	.word	0x02D08021  /* 00163F28 addu $s0,$s6,$s0 */
	.word	0x02A0282D  /* 00163F2C move $a1,$s5 */
	.word	0x0C000000  /* 00163F30 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00163F34 lwc1 $f12,0($s0) */
	.word	0x26A50010  /* 00163F38 addiu $a1,$s5,16 */
	.word	0xC60C0004  /* 00163F3C lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00163F40 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A400E0  /* 00163F44 addiu $a0,$sp,224 */
	.word	0x26A50020  /* 00163F48 addiu $a1,$s5,32 */
	.word	0xC60C0008  /* 00163F4C lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00163F50 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A400F0  /* 00163F54 addiu $a0,$sp,240 */
	.word	0x26A50030  /* 00163F58 addiu $a1,$s5,48 */
	.word	0x0C000000  /* 00163F5C jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x27A40100  /* 00163F60 addiu $a0,$sp,256 */
	.word	0x8E820154  /* 00163F64 lw $v0,340($s4) */
	.word	0x8FA40178  /* 00163F68 lw $a0,376($sp) */
	.word	0x27A300D0  /* 00163F6C addiu $v1,$sp,208 */
	.word	0x0060302D  /* 00163F70 move $a2,$v1 */
	.word	0x8C85002C  /* 00163F74 lw $a1,44($a0) */
	.word	0x00562021  /* 00163F78 addu $a0,$v0,$s6 */
	.word	0x30A503FF  /* 00163F7C andi $a1,$a1,0x3ff */
	.word	0x00052980  /* 00163F80 sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00163F84 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00452821  /* 00163F88 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00163F8C lw $v0,340($s4) */
	.word	0x8FA40178  /* 00163F90 lw $a0,376($sp) */
	.word	0x8E860150  /* 00163F94 lw $a2,336($s4) */
	.word	0x8C85002C  /* 00163F98 lw $a1,44($a0) */
	.word	0x00562021  /* 00163F9C addu $a0,$v0,$s6 */
	.word	0x00D63021  /* 00163FA0 addu $a2,$a2,$s6 */
	.word	0x24840030  /* 00163FA4 addiu $a0,$a0,48 */
	.word	0x30A503FF  /* 00163FA8 andi $a1,$a1,0x3ff */
	.word	0x24C60030  /* 00163FAC addiu $a2,$a2,48 */
	.word	0x00052980  /* 00163FB0 sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00163FB4 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x00452821  /* 00163FB8 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00163FBC lw $v0,340($s4) */
	.word	0x02E0202D  /* 00163FC0 move $a0,$s7 */
	.word	0x02C21021  /* 00163FC4 addu $v0,$s6,$v0 */
	.word	0xE455003C  /* 00163FC8 swc1 $f21,60($v0) */
	.word	0x8E860150  /* 00163FCC lw $a2,336($s4) */
	.word	0x8E850154  /* 00163FD0 lw $a1,340($s4) */
	.word	0x00D63021  /* 00163FD4 addu $a2,$a2,$s6 */
	.word	0x00B62821  /* 00163FD8 addu $a1,$a1,$s6 */
	.word	0x0C000000  /* 00163FDC jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x24C60010  /* 00163FE0 addiu $a2,$a2,16 */
	.word	0x27A500D0  /* 00163FE4 addiu $a1,$sp,208 */
	.word	0x0C000000  /* 00163FE8 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x00A0202D  /* 00163FEC move $a0,$a1 */
	.word	0x8E820150  /* 00163FF0 lw $v0,336($s4) */
	.word	0x27A300D0  /* 00163FF4 addiu $v1,$sp,208 */
	.word	0x0260302D  /* 00163FF8 move $a2,$s3 */
	.word	0x02C21021  /* 00163FFC addu $v0,$s6,$v0 */
	.word	0x0060202D  /* 00164000 move $a0,$v1 */
	.word	0xC4400000  /* 00164004 lwc1 $f0,0($v0) */
	.word	0x0060282D  /* 00164008 move $a1,$v1 */
	.word	0x00000000  /* 0016400C nop */
	.word	0x00000000  /* 00164010 nop */
	.word	0x4600A803  /* 00164014 div.s $f0,$f21,$f0 */
	.word	0xE7A000D0  /* 00164018 swc1 $f0,208($sp) */
	.word	0xC4410004  /* 0016401C lwc1 $f1,4($v0) */
	.word	0x00000000  /* 00164020 nop */
	.word	0x00000000  /* 00164024 nop */
	.word	0x4601A843  /* 00164028 div.s $f1,$f21,$f1 */
	.word	0xE7A100E4  /* 0016402C swc1 $f1,228($sp) */
	.word	0xC4400008  /* 00164030 lwc1 $f0,8($v0) */
	.word	0x00000000  /* 00164034 nop */
	.word	0x00000000  /* 00164038 nop */
	.word	0x4600A803  /* 0016403C div.s $f0,$f21,$f0 */
	.word	0x0C000000  /* 00164040 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0xE7A000F8  /* 00164044 swc1 $f0,248($sp) */
	.word	0x8E840150  /* 00164048 lw $a0,336($s4) */
	.word	0x00962021  /* 0016404C addu $a0,$a0,$s6 */
	.word	0x0080282D  /* 00164050 move $a1,$a0 */
	.word	0x24840050  /* 00164054 addiu $a0,$a0,80 */
	.word	0x0C000000  /* 00164058 jal func_001627d0 */
	.reloc	.-4, R_MIPS_26, func_001627d0
	.word	0x24A60040  /* 0016405C addiu $a2,$a1,64 */
	.word	0x8E900150  /* 00164060 lw $s0,336($s4) */
	.word	0x27A500D0  /* 00164064 addiu $a1,$sp,208 */
	.word	0x02D08021  /* 00164068 addu $s0,$s6,$s0 */
	.word	0x00A0202D  /* 0016406C move $a0,$a1 */
	.word	0x26100050  /* 00164070 addiu $s0,$s0,80 */
	.word	0x0C000000  /* 00164074 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00164078 lwc1 $f12,0($s0) */
	.word	0xC60C0004  /* 0016407C lwc1 $f12,4($s0) */
	.word	0x27A400E0  /* 00164080 addiu $a0,$sp,224 */
	.word	0x0C000000  /* 00164084 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0080282D  /* 00164088 move $a1,$a0 */
	.word	0xC60C0008  /* 0016408C lwc1 $f12,8($s0) */
	.word	0x27A400F0  /* 00164090 addiu $a0,$sp,240 */
	.word	0x0C000000  /* 00164094 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0080282D  /* 00164098 move $a1,$a0 */
	.word	0x27A40100  /* 0016409C addiu $a0,$sp,256 */
	.word	0x0C000000  /* 001640A0 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x0080282D  /* 001640A4 move $a1,$a0 */
	.word	0x8E840154  /* 001640A8 lw $a0,340($s4) */
	.word	0x27A200D0  /* 001640AC addiu $v0,$sp,208 */
	.word	0x00962021  /* 001640B0 addu $a0,$a0,$s6 */
	.word	0x0040302D  /* 001640B4 move $a2,$v0 */
	.word	0x0080282D  /* 001640B8 move $a1,$a0 */
	.word	0x0C000000  /* 001640BC jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x24840040  /* 001640C0 addiu $a0,$a0,64 */
	.word	0x8E840154  /* 001640C4 lw $a0,340($s4) */
	.word	0x8FA30178  /* 001640C8 lw $v1,376($sp) */
	.word	0x00962021  /* 001640CC addu $a0,$a0,$s6 */
	.word	0x24660050  /* 001640D0 addiu $a2,$v1,80 */
	.word	0x0080282D  /* 001640D4 move $a1,$a0 */
	.word	0x0C000000  /* 001640D8 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24840070  /* 001640DC addiu $a0,$a0,112 */
	.word	0x8E820154  /* 001640E0 lw $v0,340($s4) */
	.word	0x3C040000  /* 001640E4 lui $a0,%hi(D_00351E50) */
	.reloc	.-4, R_MIPS_HI16, D_00351E50
	.word	0x24840000  /* 001640E8 addiu $a0,$a0,%lo(D_00351E50) */
	.reloc	.-4, R_MIPS_LO16, D_00351E50
	.word	0x00962021  /* 001640EC addu $a0,$a0,$s6 */
	.word	0x02C21021  /* 001640F0 addu $v0,$s6,$v0 */
	.word	0xE455007C  /* 001640F4 swc1 $f21,124($v0) */
	.word	0x8E850154  /* 001640F8 lw $a1,340($s4) */
	.word	0x8E860150  /* 001640FC lw $a2,336($s4) */
	.word	0x00B62821  /* 00164100 addu $a1,$a1,$s6 */
	.word	0x00D63021  /* 00164104 addu $a2,$a2,$s6 */
	.word	0x24A50040  /* 00164108 addiu $a1,$a1,64 */
	.word	0x0C000000  /* 0016410C jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x24C60050  /* 00164110 addiu $a2,$a2,80 */
	.word	0x8E840154  /* 00164114 lw $a0,340($s4) */
	.word	0x8FA50178  /* 00164118 lw $a1,376($sp) */
	.word	0x00962021  /* 0016411C addu $a0,$a0,$s6 */
	.word	0x24A60080  /* 00164120 addiu $a2,$a1,128 */
	.word	0x24A50030  /* 00164124 addiu $a1,$a1,48 */
	.word	0xAFA50178  /* 00164128 sw $a1,376($sp) */
	.word	0x24850040  /* 0016412C addiu $a1,$a0,64 */
	.word	0x0C000000  /* 00164130 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x248400B0  /* 00164134 addiu $a0,$a0,176 */
	.word	0x8E820154  /* 00164138 lw $v0,340($s4) */
	.word	0x27A30050  /* 0016413C addiu $v1,$sp,80 */
	.word	0x02C21021  /* 00164140 addu $v0,$s6,$v0 */
	.word	0x0060282D  /* 00164144 move $a1,$v1 */
	.word	0xE45500BC  /* 00164148 swc1 $f21,188($v0) */
	.word	0x8E840154  /* 0016414C lw $a0,340($s4) */
	.word	0x0C000000  /* 00164150 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x00962021  /* 00164154 addu $a0,$a0,$s6 */
	.word	0x8E860154  /* 00164158 lw $a2,340($s4) */
	.word	0x27A20050  /* 0016415C addiu $v0,$sp,80 */
	.word	0x0260202D  /* 00164160 move $a0,$s3 */
	.word	0x00D63021  /* 00164164 addu $a2,$a2,$s6 */
	.word	0x0040282D  /* 00164168 move $a1,$v0 */
	.word	0x0C000000  /* 0016416C jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x24C60040  /* 00164170 addiu $a2,$a2,64 */
	.word	0x8E820150  /* 00164174 lw $v0,336($s4) */
	.word	0x02C21021  /* 00164178 addu $v0,$s6,$v0 */
	.word	0x26D60040  /* 0016417C addiu $s6,$s6,64 */
	.word	0x24420040  /* 00164180 addiu $v0,$v0,64 */
	.word	0xC4400020  /* 00164184 lwc1 $f0,32($v0) */
	.word	0x10000155  /* 00164188 b .L001646E0 */
	.word	0xE440000C  /* 0016418C swc1 $f0,12($v0) */
	.word	0x001E1882  /* 00164190 srl $v1,$s8,0x2 */
	.word	0x001E24C2  /* 00164194 srl $a0,$s8,0x13 */
	.word	0x001E12C2  /* 00164198 srl $v0,$s8,0xb */
	.word	0x001E95C2  /* 0016419C srl $s2,$s8,0x17 */
	.word	0x30C60200  /* 001641A0 andi $a2,$a2,0x200 */
	.word	0x306301FF  /* 001641A4 andi $v1,$v1,0x1ff */
	.word	0x30840200  /* 001641A8 andi $a0,$a0,0x200 */
	.word	0x304201FF  /* 001641AC andi $v0,$v0,0x1ff */
	.word	0x32450001  /* 001641B0 andi $a1,$s2,0x1 */
	.word	0x00C38825  /* 001641B4 or $s1,$a2,$v1 */
	.word	0x14A00008  /* 001641B8 bnez $a1,.L001641DC */
	.word	0x00828025  /* 001641BC or $s0,$a0,$v0 */
	.word	0x56000007  /* 001641C0 bnezl $s0,.L001641E0 */
	.word	0x8FA30178  /* 001641C4 lw $v1,376($sp) */
	.word	0x3C020100  /* 001641C8 lui $v0,0x100 */
	.word	0x34420003  /* 001641CC ori $v0,$v0,0x3 */
	.word	0x03C21024  /* 001641D0 and $v0,$s8,$v0 */
	.word	0x10400013  /* 001641D4 beqz $v0,.L00164224 */
	.word	0x32420001  /* 001641D8 andi $v0,$s2,0x1 */
	.word	0x8FA30178  /* 001641DC lw $v1,376($sp) */
	.word	0x8C62002C  /* 001641E0 lw $v0,44($v1) */
	.word	0x240303FF  /* 001641E4 li $v1,1023 */
	.word	0x304403FF  /* 001641E8 andi $a0,$v0,0x3ff */
	.word	0x54830008  /* 001641EC bnel $a0,$v1,.L00164210 */
	.word	0x8E820154  /* 001641F0 lw $v0,340($s4) */
	.word	0x3C050000  /* 001641F4 lui $a1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x24A40000  /* 001641F8 addiu $a0,$a1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x0C000000  /* 001641FC jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x27A50050  /* 00164200 addiu $a1,$sp,80 */
	.word	0x10000007  /* 00164204 b .L00164224 */
	.word	0x32420001  /* 00164208 andi $v0,$s2,0x1 */
	.word	0x00000000  /* 0016420C nop */
	.word	0x00042180  /* 00164210 sll $a0,$a0,0x6 */
	.word	0x27A50050  /* 00164214 addiu $a1,$sp,80 */
	.word	0x0C000000  /* 00164218 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x00442021  /* 0016421C addu $a0,$v0,$a0 */
	.word	0x32420001  /* 00164220 andi $v0,$s2,0x1 */
	.word	0x10400012  /* 00164224 beqz $v0,.L00164270 */
	.word	0x27A30010  /* 00164228 addiu $v1,$sp,16 */
	.word	0x8E820154  /* 0016422C lw $v0,340($s4) */
	.word	0xAFA30174  /* 00164230 sw $v1,372($sp) */
	.word	0x26A40030  /* 00164234 addiu $a0,$s5,48 */
	.word	0x02C21021  /* 00164238 addu $v0,$s6,$v0 */
	.word	0x27A50050  /* 0016423C addiu $a1,$sp,80 */
	.word	0xC4400030  /* 00164240 lwc1 $f0,48($v0) */
	.word	0x0060302D  /* 00164244 move $a2,$v1 */
	.word	0xE7A00010  /* 00164248 swc1 $f0,16($sp) */
	.word	0xC4410034  /* 0016424C lwc1 $f1,52($v0) */
	.word	0xE7A10014  /* 00164250 swc1 $f1,20($sp) */
	.word	0xC4400038  /* 00164254 lwc1 $f0,56($v0) */
	.word	0xE7B5001C  /* 00164258 swc1 $f21,28($sp) */
	.word	0x0C000000  /* 0016425C jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xE7A00018  /* 00164260 swc1 $f0,24($sp) */
	.word	0x10000035  /* 00164264 b .L0016433C */
	.word	0x33C30003  /* 00164268 andi $v1,$s8,0x3 */
	.word	0x00000000  /* 0016426C nop */
	.word	0x12000017  /* 00164270 beqz $s0,.L001642D0 */
	.word	0x2602FFFF  /* 00164274 addiu $v0,$s0,-1 */
	.word	0x3C050000  /* 00164278 lui $a1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x00021180  /* 0016427C sll $v0,$v0,0x6 */
	.word	0x24A50000  /* 00164280 addiu $a1,$a1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x00453021  /* 00164284 addu $a2,$v0,$a1 */
	.word	0x27A50050  /* 00164288 addiu $a1,$sp,80 */
	.word	0x27A40010  /* 0016428C addiu $a0,$sp,16 */
	.word	0x00C0182D  /* 00164290 move $v1,$a2 */
	.word	0xAFA40174  /* 00164294 sw $a0,372($sp) */
	.word	0x26A40030  /* 00164298 addiu $a0,$s5,48 */
	.word	0x0060102D  /* 0016429C move $v0,$v1 */
	.word	0xC4C00038  /* 001642A0 lwc1 $f0,56($a2) */
	.word	0xC4610030  /* 001642A4 lwc1 $f1,48($v1) */
	.word	0xC4420034  /* 001642A8 lwc1 $f2,52($v0) */
	.word	0x8FA60174  /* 001642AC lw $a2,372($sp) */
	.word	0xE7A10010  /* 001642B0 swc1 $f1,16($sp) */
	.word	0xE7A20014  /* 001642B4 swc1 $f2,20($sp) */
	.word	0xE7A00018  /* 001642B8 swc1 $f0,24($sp) */
	.word	0x0C000000  /* 001642BC jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xE7B5001C  /* 001642C0 swc1 $f21,28($sp) */
	.word	0x1000001D  /* 001642C4 b .L0016433C */
	.word	0x33C30003  /* 001642C8 andi $v1,$s8,0x3 */
	.word	0x00000000  /* 001642CC nop */
	.word	0x8FA30178  /* 001642D0 lw $v1,376($sp) */
	.word	0x8C62002C  /* 001642D4 lw $v0,44($v1) */
	.word	0x240303FF  /* 001642D8 li $v1,1023 */
	.word	0x304203FF  /* 001642DC andi $v0,$v0,0x3ff */
	.word	0x1443000B  /* 001642E0 bne $v0,$v1,.L00164310 */
	.word	0x8E860150  /* 001642E4 lw $a2,336($s4) */
	.word	0x3C020000  /* 001642E8 lui $v0,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x27A40010  /* 001642EC addiu $a0,$sp,16 */
	.word	0x24450000  /* 001642F0 addiu $a1,$v0,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x00D63021  /* 001642F4 addu $a2,$a2,$s6 */
	.word	0xAFA40174  /* 001642F8 sw $a0,372($sp) */
	.word	0x0C000000  /* 001642FC jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24C60030  /* 00164300 addiu $a2,$a2,48 */
	.word	0x1000000C  /* 00164304 b .L00164338 */
	.word	0xE7B5001C  /* 00164308 swc1 $f21,28($sp) */
	.word	0x00000000  /* 0016430C nop */
	.word	0x27A30010  /* 00164310 addiu $v1,$sp,16 */
	.word	0x8E850154  /* 00164314 lw $a1,340($s4) */
	.word	0x00021180  /* 00164318 sll $v0,$v0,0x6 */
	.word	0x00D63021  /* 0016431C addu $a2,$a2,$s6 */
	.word	0x0060202D  /* 00164320 move $a0,$v1 */
	.word	0x00A22821  /* 00164324 addu $a1,$a1,$v0 */
	.word	0x24C60030  /* 00164328 addiu $a2,$a2,48 */
	.word	0x0C000000  /* 0016432C jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xAFA30174  /* 00164330 sw $v1,372($sp) */
	.word	0xE7B5001C  /* 00164334 swc1 $f21,28($sp) */
	.word	0x33C30003  /* 00164338 andi $v1,$s8,0x3 */
	.word	0x24020001  /* 0016433C li $v0,1 */
	.word	0x1062003B  /* 00164340 beq $v1,$v0,.L00164430 */
	.word	0x28620002  /* 00164344 slti $v0,$v1,2 */
	.word	0x50400005  /* 00164348 beqzl $v0,.L00164360 */
	.word	0x24020002  /* 0016434C li $v0,2 */
	.word	0x10600099  /* 00164350 beqz $v1,.L001645B8 */
	.word	0x001E1602  /* 00164354 srl $v0,$s8,0x18 */
	.word	0x100000CD  /* 00164358 b .L00164690 */
	.word	0x26F70030  /* 0016435C addiu $s7,$s7,48 */
	.word	0x546200CB  /* 00164360 bnel $v1,$v0,.L00164690 */
	.word	0x26F70030  /* 00164364 addiu $s7,$s7,48 */
	.word	0x00111180  /* 00164368 sll $v0,$s1,0x6 */
	.word	0x0000402D  /* 0016436C move $t0,$zero */
	.word	0x3C040000  /* 00164370 lui $a0,%hi(D_00573ED0) */
	.reloc	.-4, R_MIPS_HI16, D_00573ED0
	.word	0x24840000  /* 00164374 addiu $a0,$a0,%lo(D_00573ED0) */
	.reloc	.-4, R_MIPS_LO16, D_00573ED0
	.word	0x00822021  /* 00164378 addu $a0,$a0,$v0 */
	.word	0x00082900  /* 0016437C sll $a1,$t0,0x4 */
	.word	0x24070002  /* 00164380 li $a3,2 */
	.word	0x00000000  /* 00164384 nop */
	.word	0x00A41021  /* 00164388 addu $v0,$a1,$a0 */
	.word	0x00B71821  /* 0016438C addu $v1,$a1,$s7 */
	.word	0xC4400000  /* 00164390 lwc1 $f0,0($v0) */
	.word	0x24E7FFFF  /* 00164394 addiu $a3,$a3,-1 */
	.word	0x24A50004  /* 00164398 addiu $a1,$a1,4 */
	.word	0x04E1FFFA  /* 0016439C bgez $a3,.L00164388 */
	.word	0xE4600000  /* 001643A0 swc1 $f0,0($v1) */
	.word	0x25080001  /* 001643A4 addiu $t0,$t0,1 */
	.word	0x29020003  /* 001643A8 slti $v0,$t0,3 */
	.word	0x1440FFF4  /* 001643AC bnez $v0,.L00164380 */
	.word	0x00082900  /* 001643B0 sll $a1,$t0,0x4 */
	.word	0x26F20010  /* 001643B4 addiu $s2,$s7,16 */
	.word	0x02E0202D  /* 001643B8 move $a0,$s7 */
	.word	0x02E0282D  /* 001643BC move $a1,$s7 */
	.word	0x0C000000  /* 001643C0 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0x26F30020  /* 001643C4 addiu $s3,$s7,32 */
	.word	0x0240202D  /* 001643C8 move $a0,$s2 */
	.word	0x26E20030  /* 001643CC addiu $v0,$s7,48 */
	.word	0x0240282D  /* 001643D0 move $a1,$s2 */
	.word	0x0C000000  /* 001643D4 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0xAFA20170  /* 001643D8 sw $v0,368($sp) */
	.word	0x0260202D  /* 001643DC move $a0,$s3 */
	.word	0x0C000000  /* 001643E0 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0x0260282D  /* 001643E4 move $a1,$s3 */
	.word	0x8E910154  /* 001643E8 lw $s1,340($s4) */
	.word	0x8E900150  /* 001643EC lw $s0,336($s4) */
	.word	0x02E0282D  /* 001643F0 move $a1,$s7 */
	.word	0x02D18821  /* 001643F4 addu $s1,$s6,$s1 */
	.word	0x02D08021  /* 001643F8 addu $s0,$s6,$s0 */
	.word	0x0220202D  /* 001643FC move $a0,$s1 */
	.word	0x26100010  /* 00164400 addiu $s0,$s0,16 */
	.word	0x0C000000  /* 00164404 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00164408 lwc1 $f12,0($s0) */
	.word	0x26240010  /* 0016440C addiu $a0,$s1,16 */
	.word	0xC60C0004  /* 00164410 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00164414 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0240282D  /* 00164418 move $a1,$s2 */
	.word	0x26240020  /* 0016441C addiu $a0,$s1,32 */
	.word	0xC60C0008  /* 00164420 lwc1 $f12,8($s0) */
	.word	0x1000005D  /* 00164424 b .L0016459C */
	.word	0x0260282D  /* 00164428 move $a1,$s3 */
	.word	0x00000000  /* 0016442C nop */
	.word	0x00113180  /* 00164430 sll $a2,$s1,0x6 */
	.word	0x03A0202D  /* 00164434 move $a0,$sp */
	.word	0x3C010000  /* 00164438 lui $at,%hi(D_00573F00) */
	.reloc	.-4, R_MIPS_HI16, D_00573F00
	.word	0x24210000  /* 0016443C addiu $at,$at,%lo(D_00573F00) */
	.reloc	.-4, R_MIPS_LO16, D_00573F00
	.word	0x00263021  /* 00164440 addu $a2,$at,$a2 */
	.word	0x0C000000  /* 00164444 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x27A50050  /* 00164448 addiu $a1,$sp,80 */
	.word	0x32420001  /* 0016444C andi $v0,$s2,0x1 */
	.word	0x14400003  /* 00164450 bnez $v0,.L00164460 */
	.word	0x27A40020  /* 00164454 addiu $a0,$sp,32 */
	.word	0x52000007  /* 00164458 beqzl $s0,.L00164478 */
	.word	0x8E860150  /* 0016445C lw $a2,336($s4) */
	.word	0x03A0282D  /* 00164460 move $a1,$sp */
	.word	0x0C000000  /* 00164464 jal func_00267530 */
	.reloc	.-4, R_MIPS_26, func_00267530
	.word	0x26A60030  /* 00164468 addiu $a2,$s5,48 */
	.word	0x1000000C  /* 0016446C b .L001644A0 */
	.word	0x26E30030  /* 00164470 addiu $v1,$s7,48 */
	.word	0x00000000  /* 00164474 nop */
	.word	0x03A0282D  /* 00164478 move $a1,$sp */
	.word	0x00D63021  /* 0016447C addu $a2,$a2,$s6 */
	.word	0x0C000000  /* 00164480 jal func_00267530 */
	.reloc	.-4, R_MIPS_26, func_00267530
	.word	0x24C60030  /* 00164484 addiu $a2,$a2,48 */
	.word	0x8E850150  /* 00164488 lw $a1,336($s4) */
	.word	0x26A40030  /* 0016448C addiu $a0,$s5,48 */
	.word	0x00B62821  /* 00164490 addu $a1,$a1,$s6 */
	.word	0x0C000000  /* 00164494 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x24A50030  /* 00164498 addiu $a1,$a1,48 */
	.word	0x26E30030  /* 0016449C addiu $v1,$s7,48 */
	.word	0xAFA00030  /* 001644A0 sw $zero,48($sp) */
	.word	0xE7B50034  /* 001644A4 swc1 $f21,52($sp) */
	.word	0x27A50020  /* 001644A8 addiu $a1,$sp,32 */
	.word	0xAFA00038  /* 001644AC sw $zero,56($sp) */
	.word	0x02A0202D  /* 001644B0 move $a0,$s5 */
	.word	0xAEA0002C  /* 001644B4 sw $zero,44($s5) */
	.word	0x26B00010  /* 001644B8 addiu $s0,$s5,16 */
	.word	0xAEA0001C  /* 001644BC sw $zero,28($s5) */
	.word	0x26B10020  /* 001644C0 addiu $s1,$s5,32 */
	.word	0xAFA30170  /* 001644C4 sw $v1,368($sp) */
	.word	0x0C000000  /* 001644C8 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0xAEA0000C  /* 001644CC sw $zero,12($s5) */
	.word	0x27A40150  /* 001644D0 addiu $a0,$sp,336 */
	.word	0x27A50020  /* 001644D4 addiu $a1,$sp,32 */
	.word	0x0C000000  /* 001644D8 jal func_00267370 */
	.reloc	.-4, R_MIPS_26, func_00267370
	.word	0x27A60030  /* 001644DC addiu $a2,$sp,48 */
	.word	0x0200202D  /* 001644E0 move $a0,$s0 */
	.word	0x27A60020  /* 001644E4 addiu $a2,$sp,32 */
	.word	0x0C000000  /* 001644E8 jal func_00267370 */
	.reloc	.-4, R_MIPS_26, func_00267370
	.word	0x27A50150  /* 001644EC addiu $a1,$sp,336 */
	.word	0x0200202D  /* 001644F0 move $a0,$s0 */
	.word	0x0C000000  /* 001644F4 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0x0200282D  /* 001644F8 move $a1,$s0 */
	.word	0x0220202D  /* 001644FC move $a0,$s1 */
	.word	0x27A50020  /* 00164500 addiu $a1,$sp,32 */
	.word	0x0C000000  /* 00164504 jal func_00267370 */
	.reloc	.-4, R_MIPS_26, func_00267370
	.word	0x0200302D  /* 00164508 move $a2,$s0 */
	.word	0x0220202D  /* 0016450C move $a0,$s1 */
	.word	0x0C000000  /* 00164510 jal func_002673b8 */
	.reloc	.-4, R_MIPS_26, func_002673b8
	.word	0x0080282D  /* 00164514 move $a1,$a0 */
	.word	0x27B00090  /* 00164518 addiu $s0,$sp,144 */
	.word	0x0C000000  /* 0016451C jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x0200202D  /* 00164520 move $a0,$s0 */
	.word	0x8E820150  /* 00164524 lw $v0,336($s4) */
	.word	0x0200202D  /* 00164528 move $a0,$s0 */
	.word	0x0200282D  /* 0016452C move $a1,$s0 */
	.word	0x02C21021  /* 00164530 addu $v0,$s6,$v0 */
	.word	0x0C000000  /* 00164534 jal func_00267768 */
	.reloc	.-4, R_MIPS_26, func_00267768
	.word	0xC44C0020  /* 00164538 lwc1 $f12,32($v0) */
	.word	0x02A0202D  /* 0016453C move $a0,$s5 */
	.word	0x0200302D  /* 00164540 move $a2,$s0 */
	.word	0x0C000000  /* 00164544 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x02A0282D  /* 00164548 move $a1,$s5 */
	.word	0x02E0202D  /* 0016454C move $a0,$s7 */
	.word	0x02A0302D  /* 00164550 move $a2,$s5 */
	.word	0x0C000000  /* 00164554 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x0260282D  /* 00164558 move $a1,$s3 */
	.word	0x8E910154  /* 0016455C lw $s1,340($s4) */
	.word	0x8E900150  /* 00164560 lw $s0,336($s4) */
	.word	0x02E0282D  /* 00164564 move $a1,$s7 */
	.word	0x02D18821  /* 00164568 addu $s1,$s6,$s1 */
	.word	0x02D08021  /* 0016456C addu $s0,$s6,$s0 */
	.word	0x0220202D  /* 00164570 move $a0,$s1 */
	.word	0x26100010  /* 00164574 addiu $s0,$s0,16 */
	.word	0x0C000000  /* 00164578 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 0016457C lwc1 $f12,0($s0) */
	.word	0x26240010  /* 00164580 addiu $a0,$s1,16 */
	.word	0xC60C0004  /* 00164584 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00164588 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26E50010  /* 0016458C addiu $a1,$s7,16 */
	.word	0x26240020  /* 00164590 addiu $a0,$s1,32 */
	.word	0xC60C0008  /* 00164594 lwc1 $f12,8($s0) */
	.word	0x26E50020  /* 00164598 addiu $a1,$s7,32 */
	.word	0x0C000000  /* 0016459C jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x00000000  /* 001645A0 nop */
	.word	0x26240030  /* 001645A4 addiu $a0,$s1,48 */
	.word	0x0C000000  /* 001645A8 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x8FA50170  /* 001645AC lw $a1,368($sp) */
	.word	0x10000039  /* 001645B0 b .L00164698 */
	.word	0x8E840154  /* 001645B4 lw $a0,340($s4) */
	.word	0x30420001  /* 001645B8 andi $v0,$v0,0x1 */
	.word	0x1040000E  /* 001645BC beqz $v0,.L001645F8 */
	.word	0x02A0302D  /* 001645C0 move $a2,$s5 */
	.word	0x8E840150  /* 001645C4 lw $a0,336($s4) */
	.word	0x00962021  /* 001645C8 addu $a0,$a0,$s6 */
	.word	0x24850030  /* 001645CC addiu $a1,$a0,48 */
	.word	0x0C000000  /* 001645D0 jal func_00162cd0 */
	.reloc	.-4, R_MIPS_26, func_00162cd0
	.word	0x24840020  /* 001645D4 addiu $a0,$a0,32 */
	.word	0x02E0202D  /* 001645D8 move $a0,$s7 */
	.word	0x3C020000  /* 001645DC lui $v0,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x02A0302D  /* 001645E0 move $a2,$s5 */
	.word	0x0C000000  /* 001645E4 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x24450000  /* 001645E8 addiu $a1,$v0,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x10000011  /* 001645EC b .L00164634 */
	.word	0x8E900150  /* 001645F0 lw $s0,336($s4) */
	.word	0x00000000  /* 001645F4 nop */
	.word	0x001E1642  /* 001645F8 srl $v0,$s8,0x19 */
	.word	0x30420001  /* 001645FC andi $v0,$v0,0x1 */
	.word	0x14400008  /* 00164600 bnez $v0,.L00164624 */
	.word	0x0260282D  /* 00164604 move $a1,$s3 */
	.word	0x8E840150  /* 00164608 lw $a0,336($s4) */
	.word	0x02A0302D  /* 0016460C move $a2,$s5 */
	.word	0x00962021  /* 00164610 addu $a0,$a0,$s6 */
	.word	0x24850030  /* 00164614 addiu $a1,$a0,48 */
	.word	0x0C000000  /* 00164618 jal func_00162cd0 */
	.reloc	.-4, R_MIPS_26, func_00162cd0
	.word	0x24840020  /* 0016461C addiu $a0,$a0,32 */
	.word	0x0260282D  /* 00164620 move $a1,$s3 */
	.word	0x02E0202D  /* 00164624 move $a0,$s7 */
	.word	0x0C000000  /* 00164628 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x02A0302D  /* 0016462C move $a2,$s5 */
	.word	0x8E900150  /* 00164630 lw $s0,336($s4) */
	.word	0x26E30030  /* 00164634 addiu $v1,$s7,48 */
	.word	0x8E910154  /* 00164638 lw $s1,340($s4) */
	.word	0x02E0282D  /* 0016463C move $a1,$s7 */
	.word	0xAFA30170  /* 00164640 sw $v1,368($sp) */
	.word	0x02D08021  /* 00164644 addu $s0,$s6,$s0 */
	.word	0x26100010  /* 00164648 addiu $s0,$s0,16 */
	.word	0x02D18821  /* 0016464C addu $s1,$s6,$s1 */
	.word	0xC60C0000  /* 00164650 lwc1 $f12,0($s0) */
	.word	0x0C000000  /* 00164654 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0220202D  /* 00164658 move $a0,$s1 */
	.word	0x26240010  /* 0016465C addiu $a0,$s1,16 */
	.word	0xC60C0004  /* 00164660 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00164664 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26E50010  /* 00164668 addiu $a1,$s7,16 */
	.word	0x26240020  /* 0016466C addiu $a0,$s1,32 */
	.word	0xC60C0008  /* 00164670 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00164674 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26E50020  /* 00164678 addiu $a1,$s7,32 */
	.word	0x26240030  /* 0016467C addiu $a0,$s1,48 */
	.word	0x0C000000  /* 00164680 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x8FA50170  /* 00164684 lw $a1,368($sp) */
	.word	0x10000003  /* 00164688 b .L00164698 */
	.word	0x8E840154  /* 0016468C lw $a0,340($s4) */
	.word	0xAFB70170  /* 00164690 sw $s7,368($sp) */
	.word	0x8E840154  /* 00164694 lw $a0,340($s4) */
	.word	0x8FA50174  /* 00164698 lw $a1,372($sp) */
	.word	0x00962021  /* 0016469C addu $a0,$a0,$s6 */
	.word	0x0C000000  /* 001646A0 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x24840030  /* 001646A4 addiu $a0,$a0,48 */
	.word	0x3C020100  /* 001646A8 lui $v0,0x100 */
	.word	0x34420003  /* 001646AC ori $v0,$v0,0x3 */
	.word	0x03C21024  /* 001646B0 and $v0,$s8,$v0 */
	.word	0x1040000A  /* 001646B4 beqz $v0,.L001646E0 */
	.word	0x02A0202D  /* 001646B8 move $a0,$s5 */
	.word	0x8E860154  /* 001646BC lw $a2,340($s4) */
	.word	0x8FA2016C  /* 001646C0 lw $v0,364($sp) */
	.word	0x27A50050  /* 001646C4 addiu $a1,$sp,80 */
	.word	0x0C000000  /* 001646C8 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00C23021  /* 001646CC addu $a2,$a2,$v0 */
	.word	0x02A0202D  /* 001646D0 move $a0,$s5 */
	.word	0x0080282D  /* 001646D4 move $a1,$a0 */
	.word	0x0C000000  /* 001646D8 jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x27A60020  /* 001646DC addiu $a2,$sp,32 */
	.word	0x8FA30170  /* 001646E0 lw $v1,368($sp) */
	.word	0xF8600000  /* 001646E4 sqc2 $vf0,0($v1) */
	.word	0x8E82000C  /* 001646E8 lw $v0,12($s4) */
	.word	0x3042000C  /* 001646EC andi $v0,$v0,0xc */
	.word	0x10400003  /* 001646F0 beqz $v0,.L00164700 */
	.word	0x8FA50164  /* 001646F4 lw $a1,356($sp) */
	.word	0x0C000000  /* 001646F8 jal func_00163150 */
	.reloc	.-4, R_MIPS_26, func_00163150
	.word	0x0280202D  /* 001646FC move $a0,$s4 */
	.word	0x8E840000  /* 00164700 lw $a0,0($s4) */
	.word	0x8FA50164  /* 00164704 lw $a1,356($sp) */
	.word	0x8FA20178  /* 00164708 lw $v0,376($sp) */
	.word	0x24A50001  /* 0016470C addiu $a1,$a1,1 */
	.word	0x8C830000  /* 00164710 lw $v1,0($a0) */
	.word	0x24420030  /* 00164714 addiu $v0,$v0,48 */
	.word	0xAFA50164  /* 00164718 sw $a1,356($sp) */
	.word	0xAFA20178  /* 0016471C sw $v0,376($sp) */
	.word	0x84620000  /* 00164720 lh $v0,0($v1) */
	.word	0x00A2102A  /* 00164724 slt $v0,$a1,$v0 */
	.word	0x1440FC21  /* 00164728 bnez $v0,.L001637B0 */
	.word	0x26D60040  /* 0016472C addiu $s6,$s6,64 */
	.word	0xDFB00180  /* 00164730 ld $s0,384($sp) */
	.word	0xDFB10188  /* 00164734 ld $s1,392($sp) */
	.word	0xDFB20190  /* 00164738 ld $s2,400($sp) */
	.word	0xDFB30198  /* 0016473C ld $s3,408($sp) */
	.word	0xDFB401A0  /* 00164740 ld $s4,416($sp) */
	.word	0xDFB501A8  /* 00164744 ld $s5,424($sp) */
	.word	0xDFB601B0  /* 00164748 ld $s6,432($sp) */
	.word	0xDFB701B8  /* 0016474C ld $s7,440($sp) */
	.word	0xDFBE01C0  /* 00164750 ld $s8,448($sp) */
	.word	0xDFBF01C8  /* 00164754 ld $ra,456($sp) */
	.word	0xC7B501D8  /* 00164758 lwc1 $f21,472($sp) */
	.word	0xC7B401D0  /* 0016475C lwc1 $f20,464($sp) */
	.word	0x03E00008  /* 00164760 jr $ra */
	.word	0x27BD01E0  /* 00164764 addiu $sp,$sp,480 */
	.end	func_001636d0
