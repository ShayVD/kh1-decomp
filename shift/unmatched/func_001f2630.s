/* func_001f2630: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001f2630,"ax",@progbits
	.globl	func_001f2630
	.ent	func_001f2630
func_001f2630:  /* 0x001F2630 */
	.word	0x27BDFF90  /* 001F2630 addiu $sp,$sp,-112 */
	.word	0xAFA40000  /* 001F2634 sw $a0,0($sp) */
	.word	0x0000202D  /* 001F2638 move $a0,$zero */
	.word	0xFFB00020  /* 001F263C sd $s0,32($sp) */
	.word	0x00A0802D  /* 001F2640 move $s0,$a1 */
	.word	0xFFB10028  /* 001F2644 sd $s1,40($sp) */
	.word	0x00E0882D  /* 001F2648 move $s1,$a3 */
	.word	0xFFB40040  /* 001F264C sd $s4,64($sp) */
	.word	0x0010803C  /* 001F2650 dsll32 $s0,$s0,0x0 */
	.word	0xFFB60050  /* 001F2654 sd $s6,80($sp) */
	.word	0x0100B02D  /* 001F2658 move $s6,$t0 */
	.word	0xFFBE0060  /* 001F265C sd $s8,96($sp) */
	.word	0x0010803E  /* 001F2660 dsrl32 $s0,$s0,0x0 */
	.word	0xAFA90008  /* 001F2664 sw $t1,8($sp) */
	.word	0x00118900  /* 001F2668 sll $s1,$s1,0x4 */
	.word	0xAFA60004  /* 001F266C sw $a2,4($sp) */
	.word	0xFFB20030  /* 001F2670 sd $s2,48($sp) */
	.word	0xFFB30038  /* 001F2674 sd $s3,56($sp) */
	.word	0xFFB50048  /* 001F2678 sd $s5,72($sp) */
	.word	0xFFB70058  /* 001F267C sd $s7,88($sp) */
	.word	0xFFBF0068  /* 001F2680 sd $ra,104($sp) */
	.word	0x0C000000  /* 001F2684 jal func_001efb78 */
	.reloc	.-4, R_MIPS_26, func_001efb78
	.word	0x263E7400  /* 001F2688 addiu $s8,$s1,29696 */
	.word	0x8FA20008  /* 001F268C lw $v0,8($sp) */
	.word	0x0000202D  /* 001F2690 move $a0,$zero */
	.word	0x00021100  /* 001F2694 sll $v0,$v0,0x4 */
	.word	0x0C000000  /* 001F2698 jal func_001efb98 */
	.reloc	.-4, R_MIPS_26, func_001efb98
	.word	0xAFA20014  /* 001F269C sw $v0,20($sp) */
	.word	0x0C000000  /* 001F26A0 jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0x24040002  /* 001F26A4 li $a0,2 */
	.word	0x3C050000  /* 001F26A8 lui $a1,%hi(D_003F2270) */
	.reloc	.-4, R_MIPS_HI16, D_003F2270
	.word	0x0040202D  /* 001F26AC move $a0,$v0 */
	.word	0x0C000000  /* 001F26B0 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x24A50000  /* 001F26B4 addiu $a1,$a1,%lo(D_003F2270) */
	.reloc	.-4, R_MIPS_LO16, D_003F2270
	.word	0x24040400  /* 001F26B8 li $a0,1024 */
	.word	0x0C000000  /* 001F26BC jal func_00122048 */
	.reloc	.-4, R_MIPS_26, func_00122048
	.word	0x24050080  /* 001F26C0 li $a1,128 */
	.word	0x3C030FFF  /* 001F26C4 lui $v1,0xfff */
	.word	0x3463FFFF  /* 001F26C8 ori $v1,$v1,0xffff */
	.word	0x3C068000  /* 001F26CC lui $a2,0x8000 */
	.word	0x00431824  /* 001F26D0 and $v1,$v0,$v1 */
	.word	0xAFA2000C  /* 001F26D4 sw $v0,12($sp) */
	.word	0x24540010  /* 001F26D8 addiu $s4,$v0,16 */
	.word	0x3C020004  /* 001F26DC lui $v0,0x4 */
	.word	0x3442343E  /* 001F26E0 ori $v0,$v0,0x343e */
	.word	0x3C044000  /* 001F26E4 lui $a0,0x4000 */
	.word	0x0004203C  /* 001F26E8 dsll32 $a0,$a0,0x0 */
	.word	0x34840001  /* 001F26EC ori $a0,$a0,0x1 */
	.word	0x00661825  /* 001F26F0 or $v1,$v1,$a2 */
	.word	0x3405EEEE  /* 001F26F4 li $a1,0xeeee */
	.word	0x2407003F  /* 001F26F8 li $a3,63 */
	.word	0x3C084007  /* 001F26FC lui $t0,0x4007 */
	.word	0x3508FF80  /* 001F2700 ori $t0,$t0,0xff80 */
	.word	0x00084438  /* 001F2704 dsll $t0,$t0,0x10 */
	.word	0x35080130  /* 001F2708 ori $t0,$t0,0x130 */
	.word	0x00084438  /* 001F270C dsll $t0,$t0,0x10 */
	.word	0x24090016  /* 001F2710 li $t1,22 */
	.word	0x240A0044  /* 001F2714 li $t2,68 */
	.word	0x240B0042  /* 001F2718 li $t3,66 */
	.word	0x240C0001  /* 001F271C li $t4,1 */
	.word	0x3C0D50AB  /* 001F2720 lui $t5,0x50ab */
	.word	0x35AD4000  /* 001F2724 ori $t5,$t5,0x4000 */
	.word	0x000D683C  /* 001F2728 dsll32 $t5,$t5,0x0 */
	.word	0x35AD8001  /* 001F272C ori $t5,$t5,0x8001 */
	.word	0xFE820058  /* 001F2730 sd $v0,88($s4) */
	.word	0x3C0E7000  /* 001F2734 lui $t6,0x7000 */
	.word	0x35CE000B  /* 001F2738 ori $t6,$t6,0xb */
	.word	0xFE840000  /* 001F273C sd $a0,0($s4) */
	.word	0x240F0001  /* 001F2740 li $t7,1 */
	.word	0xAFA30010  /* 001F2744 sw $v1,16($sp) */
	.word	0xFE850008  /* 001F2748 sd $a1,8($s4) */
	.word	0xFE870018  /* 001F274C sd $a3,24($s4) */
	.word	0xFE880020  /* 001F2750 sd $t0,32($s4) */
	.word	0xFE890028  /* 001F2754 sd $t1,40($s4) */
	.word	0xFE8A0030  /* 001F2758 sd $t2,48($s4) */
	.word	0xFE8B0038  /* 001F275C sd $t3,56($s4) */
	.word	0xFE900040  /* 001F2760 sd $s0,64($s4) */
	.word	0xFE8C0048  /* 001F2764 sd $t4,72($s4) */
	.word	0xFE8D0050  /* 001F2768 sd $t5,80($s4) */
	.word	0xFE800010  /* 001F276C sd $zero,16($s4) */
	.word	0x8FA3000C  /* 001F2770 lw $v1,12($sp) */
	.word	0xFC6E0000  /* 001F2774 sd $t6,0($v1) */
	.word	0x8FA40000  /* 001F2778 lw $a0,0($sp) */
	.word	0x108F000A  /* 001F277C beq $a0,$t7,.L001F27A8 */
	.word	0x24740070  /* 001F2780 addiu $s4,$v1,112 */
	.word	0x28820002  /* 001F2784 slti $v0,$a0,2 */
	.word	0x14400004  /* 001F2788 bnez $v0,.L001F279C */
	.word	0x8FA30004  /* 001F278C lw $v1,4($sp) */
	.word	0x24020002  /* 001F2790 li $v0,2 */
	.word	0x1082000C  /* 001F2794 beq $a0,$v0,.L001F27C8 */
	.word	0x8FA50008  /* 001F2798 lw $a1,8($sp) */
	.word	0x00031100  /* 001F279C sll $v0,$v1,0x4 */
	.word	0x10000012  /* 001F27A0 b .L001F27EC */
	.word	0x24557000  /* 001F27A4 addiu $s5,$v0,28672 */
	.word	0x8FA50008  /* 001F27A8 lw $a1,8($sp) */
	.word	0x0C000000  /* 001F27AC jal func_001f0340 */
	.reloc	.-4, R_MIPS_26, func_001f0340
	.word	0x02C0202D  /* 001F27B0 move $a0,$s6 */
	.word	0x8FA40004  /* 001F27B4 lw $a0,4($sp) */
	.word	0x00821023  /* 001F27B8 subu $v0,$a0,$v0 */
	.word	0x00021100  /* 001F27BC sll $v0,$v0,0x4 */
	.word	0x1000000A  /* 001F27C0 b .L001F27EC */
	.word	0x24557000  /* 001F27C4 addiu $s5,$v0,28672 */
	.word	0x0C000000  /* 001F27C8 jal func_001f0340 */
	.reloc	.-4, R_MIPS_26, func_001f0340
	.word	0x02C0202D  /* 001F27CC move $a0,$s6 */
	.word	0x00021FC2  /* 001F27D0 srl $v1,$v0,0x1f */
	.word	0x00621821  /* 001F27D4 addu $v1,$v1,$v0 */
	.word	0x8FA20004  /* 001F27D8 lw $v0,4($sp) */
	.word	0x00031843  /* 001F27DC sra $v1,$v1,0x1 */
	.word	0x00431823  /* 001F27E0 subu $v1,$v0,$v1 */
	.word	0x00031900  /* 001F27E4 sll $v1,$v1,0x4 */
	.word	0x24757000  /* 001F27E8 addiu $s5,$v1,28672 */
	.word	0x8FA30008  /* 001F27EC lw $v1,8($sp) */
	.word	0x24170012  /* 001F27F0 li $s7,18 */
	.word	0x00031A00  /* 001F27F4 sll $v1,$v1,0x8 */
	.word	0xAFA30018  /* 001F27F8 sw $v1,24($sp) */
	.word	0x00000000  /* 001F27FC nop */
	.word	0x92C40000  /* 001F2800 lbu $a0,0($s6) */
	.word	0x1080007C  /* 001F2804 beqz $a0,.L001F29F8 */
	.word	0x2402000A  /* 001F2808 li $v0,10 */
	.word	0x54820026  /* 001F280C bnel $a0,$v0,.L001F28A8 */
	.word	0x92C20001  /* 001F2810 lbu $v0,1($s6) */
	.word	0x3C040000  /* 001F2814 lui $a0,%hi(D_0063F740) */
	.reloc	.-4, R_MIPS_HI16, D_0063F740
	.word	0x24030001  /* 001F2818 li $v1,1 */
	.word	0x8C820000  /* 001F281C lw $v0,%lo(D_0063F740)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0063F740
	.word	0x03C2F021  /* 001F2820 addu $s8,$s8,$v0 */
	.word	0x8FA20000  /* 001F2824 lw $v0,0($sp) */
	.word	0x1043000D  /* 001F2828 beq $v0,$v1,.L001F2860 */
	.word	0x26D60001  /* 001F282C addiu $s6,$s6,1 */
	.word	0x28420002  /* 001F2830 slti $v0,$v0,2 */
	.word	0x14400006  /* 001F2834 bnez $v0,.L001F2850 */
	.word	0x8FA40004  /* 001F2838 lw $a0,4($sp) */
	.word	0x8FA30000  /* 001F283C lw $v1,0($sp) */
	.word	0x24020002  /* 001F2840 li $v0,2 */
	.word	0x1062000E  /* 001F2844 beq $v1,$v0,.L001F2880 */
	.word	0x8FA50008  /* 001F2848 lw $a1,8($sp) */
	.word	0x8FA40004  /* 001F284C lw $a0,4($sp) */
	.word	0x00041100  /* 001F2850 sll $v0,$a0,0x4 */
	.word	0x1000FFEA  /* 001F2854 b .L001F2800 */
	.word	0x24557000  /* 001F2858 addiu $s5,$v0,28672 */
	.word	0x00000000  /* 001F285C nop */
	.word	0x8FA50008  /* 001F2860 lw $a1,8($sp) */
	.word	0x0C000000  /* 001F2864 jal func_001f0340 */
	.reloc	.-4, R_MIPS_26, func_001f0340
	.word	0x02C0202D  /* 001F2868 move $a0,$s6 */
	.word	0x8FA30004  /* 001F286C lw $v1,4($sp) */
	.word	0x00621023  /* 001F2870 subu $v0,$v1,$v0 */
	.word	0x00021100  /* 001F2874 sll $v0,$v0,0x4 */
	.word	0x1000FFE1  /* 001F2878 b .L001F2800 */
	.word	0x24557000  /* 001F287C addiu $s5,$v0,28672 */
	.word	0x0C000000  /* 001F2880 jal func_001f0340 */
	.reloc	.-4, R_MIPS_26, func_001f0340
	.word	0x02C0202D  /* 001F2884 move $a0,$s6 */
	.word	0x00021FC2  /* 001F2888 srl $v1,$v0,0x1f */
	.word	0x8FA40004  /* 001F288C lw $a0,4($sp) */
	.word	0x00621821  /* 001F2890 addu $v1,$v1,$v0 */
	.word	0x00031843  /* 001F2894 sra $v1,$v1,0x1 */
	.word	0x00831823  /* 001F2898 subu $v1,$a0,$v1 */
	.word	0x00031900  /* 001F289C sll $v1,$v1,0x4 */
	.word	0x1000FFD7  /* 001F28A0 b .L001F2800 */
	.word	0x24757000  /* 001F28A4 addiu $s5,$v1,28672 */
	.word	0x24034081  /* 001F28A8 li $v1,16513 */
	.word	0x00021200  /* 001F28AC sll $v0,$v0,0x8 */
	.word	0x00822025  /* 001F28B0 or $a0,$a0,$v0 */
	.word	0x14830008  /* 001F28B4 bne $a0,$v1,.L001F28D8 */
	.word	0x26D60002  /* 001F28B8 addiu $s6,$s6,2 */
	.word	0x8FA30018  /* 001F28BC lw $v1,24($sp) */
	.word	0x52E00001  /* 001F28C0 beqzl $s7,.L001F28C8 */
	.word	0x000001CD  /* 001F28C4 break 0x0,0x7 */
	.word	0x0077001A  /* 001F28C8 div $zero,$v1,$s7 */
	.word	0x00001012  /* 001F28CC mflo $v0 */
	.word	0x1000FFCB  /* 001F28D0 b .L001F2800 */
	.word	0x02A2A821  /* 001F28D4 addu $s5,$s5,$v0 */
	.word	0x0C000000  /* 001F28D8 jal func_001eff50 */
	.reloc	.-4, R_MIPS_26, func_001eff50
	.word	0x00000000  /* 001F28DC nop */
	.word	0x3C040000  /* 001F28E0 lui $a0,%hi(D_003E8E28) */
	.reloc	.-4, R_MIPS_HI16, D_003E8E28
	.word	0x8C910000  /* 001F28E4 lw $s1,%lo(D_003E8E28)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_003E8E28
	.word	0x000210C0  /* 001F28E8 sll $v0,$v0,0x3 */
	.word	0x52E00001  /* 001F28EC beqzl $s7,.L001F28F4 */
	.word	0x000001CD  /* 001F28F0 break 0x0,0x7 */
	.word	0x02228821  /* 001F28F4 addu $s1,$s1,$v0 */
	.word	0x8FA20008  /* 001F28F8 lw $v0,8($sp) */
	.word	0x92300006  /* 001F28FC lbu $s0,6($s1) */
	.word	0x00108100  /* 001F2900 sll $s0,$s0,0x4 */
	.word	0x02029018  /* 001F2904 mult $s2,$s0,$v0 */
	.word	0x0257001A  /* 001F2908 div $zero,$s2,$s7 */
	.word	0x00009012  /* 001F290C mflo $s2 */
	.word	0x0C000000  /* 001F2910 jal func_001efb88 */
	.reloc	.-4, R_MIPS_26, func_001efb88
	.word	0x00000000  /* 001F2914 nop */
	.word	0x02029821  /* 001F2918 addu $s3,$s0,$v0 */
	.word	0x52E00001  /* 001F291C beqzl $s7,.L001F2924 */
	.word	0x000001CD  /* 001F2920 break 0x0,0x7 */
	.word	0x8FA20008  /* 001F2924 lw $v0,8($sp) */
	.word	0x3409FFF0  /* 001F2928 li $t1,0xfff0 */
	.word	0x000948FC  /* 001F292C dsll32 $t1,$t1,0x3 */
	.word	0x92240007  /* 001F2930 lbu $a0,7($s1) */
	.word	0x24070016  /* 001F2934 li $a3,22 */
	.word	0x02629818  /* 001F2938 mult $s3,$s3,$v0 */
	.word	0x3C020000  /* 001F293C lui $v0,%hi(D_003E8D00) */
	.reloc	.-4, R_MIPS_HI16, D_003E8D00
	.word	0x00041902  /* 001F2940 srl $v1,$a0,0x4 */
	.word	0x3084000F  /* 001F2944 andi $a0,$a0,0xf */
	.word	0x24420000  /* 001F2948 addiu $v0,$v0,%lo(D_003E8D00) */
	.reloc	.-4, R_MIPS_LO16, D_003E8D00
	.word	0x00031880  /* 001F294C sll $v1,$v1,0x2 */
	.word	0x00621821  /* 001F2950 addu $v1,$v1,$v0 */
	.word	0x0004263C  /* 001F2954 dsll32 $a0,$a0,0x18 */
	.word	0x0277001A  /* 001F2958 div $zero,$s3,$s7 */
	.word	0x8C620000  /* 001F295C lw $v0,0($v1) */
	.word	0x962A0002  /* 001F2960 lhu $t2,2($s1) */
	.word	0x34058000  /* 001F2964 li $a1,0x8000 */
	.word	0x00021538  /* 001F2968 dsll $v0,$v0,0x14 */
	.word	0x96280004  /* 001F296C lhu $t0,4($s1) */
	.word	0x00441025  /* 001F2970 or $v0,$v0,$a0 */
	.word	0x8FA40014  /* 001F2974 lw $a0,20($sp) */
	.word	0x00491025  /* 001F2978 or $v0,$v0,$t1 */
	.word	0x01508021  /* 001F297C addu $s0,$t2,$s0 */
	.word	0x03C41821  /* 001F2980 addu $v1,$s8,$a0 */
	.word	0x24040002  /* 001F2984 li $a0,2 */
	.word	0x25060120  /* 001F2988 addiu $a2,$t0,288 */
	.word	0xFE820000  /* 001F298C sd $v0,0($s4) */
	.word	0x02B29021  /* 001F2990 addu $s2,$s5,$s2 */
	.word	0x3C020010  /* 001F2994 lui $v0,0x10 */
	.word	0xFE870008  /* 001F2998 sd $a3,8($s4) */
	.word	0xAE860034  /* 001F299C sw $a2,52($s4) */
	.word	0xAE830044  /* 001F29A0 sw $v1,68($s4) */
	.word	0xAE8A0010  /* 001F29A4 sw $t2,16($s4) */
	.word	0xAE880014  /* 001F29A8 sw $t0,20($s4) */
	.word	0xAE85002C  /* 001F29AC sw $a1,44($s4) */
	.word	0xAE950020  /* 001F29B0 sw $s5,32($s4) */
	.word	0xAE900030  /* 001F29B4 sw $s0,48($s4) */
	.word	0xAE9E0024  /* 001F29B8 sw $s8,36($s4) */
	.word	0xAE820028  /* 001F29BC sw $v0,40($s4) */
	.word	0xAE820048  /* 001F29C0 sw $v0,72($s4) */
	.word	0xAE80004C  /* 001F29C4 sw $zero,76($s4) */
	.word	0x00009812  /* 001F29C8 mflo $s3 */
	.word	0x0C000000  /* 001F29CC jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0xAE920040  /* 001F29D0 sw $s2,64($s4) */
	.word	0x8FA50010  /* 001F29D4 lw $a1,16($sp) */
	.word	0x0040202D  /* 001F29D8 move $a0,$v0 */
	.word	0x0C000000  /* 001F29DC jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x02B3A821  /* 001F29E0 addu $s5,$s5,$s3 */
	.word	0x0000202D  /* 001F29E4 move $a0,$zero */
	.word	0x0C000000  /* 001F29E8 jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000282D  /* 001F29EC move $a1,$zero */
	.word	0x1000FF84  /* 001F29F0 b .L001F2804 */
	.word	0x92C40000  /* 001F29F4 lbu $a0,0($s6) */
	.word	0x0C000000  /* 001F29F8 jal func_001220b8 */
	.reloc	.-4, R_MIPS_26, func_001220b8
	.word	0x8FA4000C  /* 001F29FC lw $a0,12($sp) */
	.word	0x3C050000  /* 001F2A00 lui $a1,%hi(D_0063F74C) */
	.reloc	.-4, R_MIPS_HI16, D_0063F74C
	.word	0x26A29000  /* 001F2A04 addiu $v0,$s5,-28672 */
	.word	0xDFB50048  /* 001F2A08 ld $s5,72($sp) */
	.word	0x27C38C00  /* 001F2A0C addiu $v1,$s8,-29696 */
	.word	0xDFBE0060  /* 001F2A10 ld $s8,96($sp) */
	.word	0xDFB00020  /* 001F2A14 ld $s0,32($sp) */
	.word	0x00021103  /* 001F2A18 sra $v0,$v0,0x4 */
	.word	0xDFB10028  /* 001F2A1C ld $s1,40($sp) */
	.word	0x00031903  /* 001F2A20 sra $v1,$v1,0x4 */
	.word	0xDFB20030  /* 001F2A24 ld $s2,48($sp) */
	.word	0x3C040000  /* 001F2A28 lui $a0,%hi(D_0063F750) */
	.reloc	.-4, R_MIPS_HI16, D_0063F750
	.word	0xDFB30038  /* 001F2A2C ld $s3,56($sp) */
	.word	0xDFB40040  /* 001F2A30 ld $s4,64($sp) */
	.word	0xDFB60050  /* 001F2A34 ld $s6,80($sp) */
	.word	0xDFB70058  /* 001F2A38 ld $s7,88($sp) */
	.word	0xDFBF0068  /* 001F2A3C ld $ra,104($sp) */
	.word	0xACA20000  /* 001F2A40 sw $v0,%lo(D_0063F74C)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_0063F74C
	.word	0xAC830000  /* 001F2A44 sw $v1,%lo(D_0063F750)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0063F750
	.word	0x03E00008  /* 001F2A48 jr $ra */
	.word	0x27BD0070  /* 001F2A4C addiu $sp,$sp,112 */
	.end	func_001f2630
