/* func_00166570: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_00166570,"ax",@progbits
	.globl	func_00166570
	.ent	func_00166570
func_00166570:  /* 0x00166570 */
	.word	0x27BDFE00  /* 00166570 addiu $sp,$sp,-512 */
	.word	0xFFB10198  /* 00166574 sd $s1,408($sp) */
	.word	0x0080882D  /* 00166578 move $s1,$a0 */
	.word	0xFFB401B0  /* 0016657C sd $s4,432($sp) */
	.word	0x00A0A02D  /* 00166580 move $s4,$a1 */
	.word	0xE7B501E8  /* 00166584 swc1 $f21,488($sp) */
	.word	0x46006546  /* 00166588 mov.s $f21,$f12 */
	.word	0xFFB00190  /* 0016658C sd $s0,400($sp) */
	.word	0x0220282D  /* 00166590 move $a1,$s1 */
	.word	0xFFB201A0  /* 00166594 sd $s2,416($sp) */
	.word	0xFFB301A8  /* 00166598 sd $s3,424($sp) */
	.word	0xFFB501B8  /* 0016659C sd $s5,440($sp) */
	.word	0xFFB601C0  /* 001665A0 sd $s6,448($sp) */
	.word	0xFFB701C8  /* 001665A4 sd $s7,456($sp) */
	.word	0xFFBE01D0  /* 001665A8 sd $s8,464($sp) */
	.word	0xFFBF01D8  /* 001665AC sd $ra,472($sp) */
	.word	0xE7B601F0  /* 001665B0 swc1 $f22,496($sp) */
	.word	0xE7B401E0  /* 001665B4 swc1 $f20,480($sp) */
	.word	0x8E82000C  /* 001665B8 lw $v0,12($s4) */
	.word	0x00021103  /* 001665BC sra $v0,$v0,0x4 */
	.word	0x30420001  /* 001665C0 andi $v0,$v0,0x1 */
	.word	0x0C000000  /* 001665C4 jal func_00267390 */
	.reloc	.-4, R_MIPS_26, func_00267390
	.word	0xAFA2018C  /* 001665C8 sw $v0,396($sp) */
	.word	0x46000004  /* 001665CC sqrt.s $f0,$f0 */
	.word	0x3C020000  /* 001665D0 lui $v0,%hi(D_00574F20) */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0x24520000  /* 001665D4 addiu $s2,$v0,%lo(D_00574F20) */
	.reloc	.-4, R_MIPS_LO16, D_00574F20
	.word	0x26240010  /* 001665D8 addiu $a0,$s1,16 */
	.word	0xE6400000  /* 001665DC swc1 $f0,0($s2) */
	.word	0x0C000000  /* 001665E0 jal func_00267390 */
	.reloc	.-4, R_MIPS_26, func_00267390
	.word	0x0080282D  /* 001665E4 move $a1,$a0 */
	.word	0x46000004  /* 001665E8 sqrt.s $f0,$f0 */
	.word	0x26240020  /* 001665EC addiu $a0,$s1,32 */
	.word	0xE6400004  /* 001665F0 swc1 $f0,4($s2) */
	.word	0x0C000000  /* 001665F4 jal func_00267390 */
	.reloc	.-4, R_MIPS_26, func_00267390
	.word	0x0080282D  /* 001665F8 move $a1,$a0 */
	.word	0x46000004  /* 001665FC sqrt.s $f0,$f0 */
	.word	0x3C030000  /* 00166600 lui $v1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0xE6400008  /* 00166604 swc1 $f0,8($s2) */
	.word	0x24700000  /* 00166608 addiu $s0,$v1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x0220282D  /* 0016660C move $a1,$s1 */
	.word	0x0200202D  /* 00166610 move $a0,$s0 */
	.word	0x0C000000  /* 00166614 jal sceVu0CopyMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0CopyMatrix
	.word	0x269100A0  /* 00166618 addiu $s1,$s4,160 */
	.word	0xC6030010  /* 0016661C lwc1 $f3,16($s0) */
	.word	0xC6050014  /* 00166620 lwc1 $f5,20($s0) */
	.word	0x0200202D  /* 00166624 move $a0,$s0 */
	.word	0xC6040018  /* 00166628 lwc1 $f4,24($s0) */
	.word	0x460018C7  /* 0016662C neg.s $f3,$f3 */
	.word	0xC6020020  /* 00166630 lwc1 $f2,32($s0) */
	.word	0x46002947  /* 00166634 neg.s $f5,$f5 */
	.word	0xC6010024  /* 00166638 lwc1 $f1,36($s0) */
	.word	0x46002107  /* 0016663C neg.s $f4,$f4 */
	.word	0xC6000028  /* 00166640 lwc1 $f0,40($s0) */
	.word	0x46001087  /* 00166644 neg.s $f2,$f2 */
	.word	0x46000847  /* 00166648 neg.s $f1,$f1 */
	.word	0xC64C0000  /* 0016664C lwc1 $f12,0($s2) */
	.word	0x46000007  /* 00166650 neg.s $f0,$f0 */
	.word	0xE6030010  /* 00166654 swc1 $f3,16($s0) */
	.word	0xE6050014  /* 00166658 swc1 $f5,20($s0) */
	.word	0x0200282D  /* 0016665C move $a1,$s0 */
	.word	0xE6020020  /* 00166660 swc1 $f2,32($s0) */
	.word	0xE6010024  /* 00166664 swc1 $f1,36($s0) */
	.word	0xE6000028  /* 00166668 swc1 $f0,40($s0) */
	.word	0x0C000000  /* 0016666C jal func_002674b0 */
	.reloc	.-4, R_MIPS_26, func_002674b0
	.word	0xE6040018  /* 00166670 swc1 $f4,24($s0) */
	.word	0x26040010  /* 00166674 addiu $a0,$s0,16 */
	.word	0xC64C0004  /* 00166678 lwc1 $f12,4($s2) */
	.word	0x0C000000  /* 0016667C jal func_002674b0 */
	.reloc	.-4, R_MIPS_26, func_002674b0
	.word	0x0080282D  /* 00166680 move $a1,$a0 */
	.word	0x26040020  /* 00166684 addiu $a0,$s0,32 */
	.word	0xC64C0008  /* 00166688 lwc1 $f12,8($s2) */
	.word	0x0C000000  /* 0016668C jal func_002674b0 */
	.reloc	.-4, R_MIPS_26, func_002674b0
	.word	0x0080282D  /* 00166690 move $a1,$a0 */
	.word	0x0220202D  /* 00166694 move $a0,$s1 */
	.word	0x268500C0  /* 00166698 addiu $a1,$s4,192 */
	.word	0x268600B0  /* 0016669C addiu $a2,$s4,176 */
	.word	0x0C000000  /* 001666A0 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x4600AB06  /* 001666A4 mov.s $f12,$f21 */
	.word	0xC6200000  /* 001666A8 lwc1 $f0,0($s1) */
	.word	0xC6420000  /* 001666AC lwc1 $f2,0($s2) */
	.word	0x3C040000  /* 001666B0 lui $a0,%hi(D_00574F10) */
	.reloc	.-4, R_MIPS_HI16, D_00574F10
	.word	0xC6030030  /* 001666B4 lwc1 $f3,48($s0) */
	.word	0x24820000  /* 001666B8 addiu $v0,$a0,%lo(D_00574F10) */
	.reloc	.-4, R_MIPS_LO16, D_00574F10
	.word	0x46020002  /* 001666BC mul.s $f0,$f0,$f2 */
	.word	0xC68200A8  /* 001666C0 lwc1 $f2,168($s4) */
	.word	0xC68100A4  /* 001666C4 lwc1 $f1,164($s4) */
	.word	0x46030000  /* 001666C8 add.s $f0,$f0,$f3 */
	.word	0xE6800090  /* 001666CC swc1 $f0,144($s4) */
	.word	0xC6430004  /* 001666D0 lwc1 $f3,4($s2) */
	.word	0xC6000034  /* 001666D4 lwc1 $f0,52($s0) */
	.word	0x46030842  /* 001666D8 mul.s $f1,$f1,$f3 */
	.word	0x46000840  /* 001666DC add.s $f1,$f1,$f0 */
	.word	0xE6810094  /* 001666E0 swc1 $f1,148($s4) */
	.word	0xC6400008  /* 001666E4 lwc1 $f0,8($s2) */
	.word	0xC6010038  /* 001666E8 lwc1 $f1,56($s0) */
	.word	0x46001082  /* 001666EC mul.s $f2,$f2,$f0 */
	.word	0x46011080  /* 001666F0 add.s $f2,$f2,$f1 */
	.word	0xE6820098  /* 001666F4 swc1 $f2,152($s4) */
	.word	0xC6010030  /* 001666F8 lwc1 $f1,48($s0) */
	.word	0xC6020034  /* 001666FC lwc1 $f2,52($s0) */
	.word	0xC6000038  /* 00166700 lwc1 $f0,56($s0) */
	.word	0xE4410000  /* 00166704 swc1 $f1,0($v0) */
	.word	0xE4400008  /* 00166708 swc1 $f0,8($v0) */
	.word	0xE4420004  /* 0016670C swc1 $f2,4($v0) */
	.word	0xAE000038  /* 00166710 sw $zero,56($s0) */
	.word	0xAE000030  /* 00166714 sw $zero,48($s0) */
	.word	0xAE000034  /* 00166718 sw $zero,52($s0) */
	.word	0x8E85016C  /* 0016671C lw $a1,364($s4) */
	.word	0x84A20000  /* 00166720 lh $v0,0($a1) */
	.word	0x04400030  /* 00166724 bltz $v0,.L001667E8 */
	.word	0x00A0202D  /* 00166728 move $a0,$a1 */
	.word	0x3C094000  /* 0016672C lui $t1,0x4000 */
	.word	0x0000402D  /* 00166730 move $t0,$zero */
	.word	0x00000000  /* 00166734 nop */
	.word	0x8E830000  /* 00166738 lw $v1,0($s4) */
	.word	0x01043821  /* 0016673C addu $a3,$t0,$a0 */
	.word	0x84E40000  /* 00166740 lh $a0,0($a3) */
	.word	0x8C650000  /* 00166744 lw $a1,0($v1) */
	.word	0x00041040  /* 00166748 sll $v0,$a0,0x1 */
	.word	0x8CA60004  /* 0016674C lw $a2,4($a1) */
	.word	0x00441021  /* 00166750 addu $v0,$v0,$a0 */
	.word	0x00021100  /* 00166754 sll $v0,$v0,0x4 */
	.word	0x00461021  /* 00166758 addu $v0,$v0,$a2 */
	.word	0x8C43002C  /* 0016675C lw $v1,44($v0) */
	.word	0x306303FF  /* 00166760 andi $v1,$v1,0x3ff */
	.word	0x00031040  /* 00166764 sll $v0,$v1,0x1 */
	.word	0x00431021  /* 00166768 addu $v0,$v0,$v1 */
	.word	0x00021100  /* 0016676C sll $v0,$v0,0x4 */
	.word	0x00461021  /* 00166770 addu $v0,$v0,$a2 */
	.word	0x8C43002C  /* 00166774 lw $v1,44($v0) */
	.word	0x00031F82  /* 00166778 srl $v1,$v1,0x1e */
	.word	0x30630001  /* 0016677C andi $v1,$v1,0x1 */
	.word	0xACE30004  /* 00166780 sw $v1,4($a3) */
	.word	0x8E82016C  /* 00166784 lw $v0,364($s4) */
	.word	0x8E850000  /* 00166788 lw $a1,0($s4) */
	.word	0x01021021  /* 0016678C addu $v0,$t0,$v0 */
	.word	0x25080030  /* 00166790 addiu $t0,$t0,48 */
	.word	0x84430000  /* 00166794 lh $v1,0($v0) */
	.word	0x8CA40000  /* 00166798 lw $a0,0($a1) */
	.word	0x00031040  /* 0016679C sll $v0,$v1,0x1 */
	.word	0x8C850004  /* 001667A0 lw $a1,4($a0) */
	.word	0x00431021  /* 001667A4 addu $v0,$v0,$v1 */
	.word	0x00021100  /* 001667A8 sll $v0,$v0,0x4 */
	.word	0x00451021  /* 001667AC addu $v0,$v0,$a1 */
	.word	0x8C43002C  /* 001667B0 lw $v1,44($v0) */
	.word	0x306303FF  /* 001667B4 andi $v1,$v1,0x3ff */
	.word	0x00031040  /* 001667B8 sll $v0,$v1,0x1 */
	.word	0x00431021  /* 001667BC addu $v0,$v0,$v1 */
	.word	0x00021100  /* 001667C0 sll $v0,$v0,0x4 */
	.word	0x00451021  /* 001667C4 addu $v0,$v0,$a1 */
	.word	0x8C43002C  /* 001667C8 lw $v1,44($v0) */
	.word	0x00691825  /* 001667CC or $v1,$v1,$t1 */
	.word	0xAC43002C  /* 001667D0 sw $v1,44($v0) */
	.word	0x8E85016C  /* 001667D4 lw $a1,364($s4) */
	.word	0x01051821  /* 001667D8 addu $v1,$t0,$a1 */
	.word	0x84620000  /* 001667DC lh $v0,0($v1) */
	.word	0x0441FFD5  /* 001667E0 bgez $v0,.L00166738 */
	.word	0x00A0202D  /* 001667E4 move $a0,$a1 */
	.word	0x8E840000  /* 001667E8 lw $a0,0($s4) */
	.word	0xAFA50188  /* 001667EC sw $a1,392($sp) */
	.word	0xAFA00180  /* 001667F0 sw $zero,384($sp) */
	.word	0x8C820000  /* 001667F4 lw $v0,0($a0) */
	.word	0x84430000  /* 001667F8 lh $v1,0($v0) */
	.word	0x8C420004  /* 001667FC lw $v0,4($v0) */
	.word	0x186002D0  /* 00166800 blez $v1,.L00167344 */
	.word	0xAFA20184  /* 00166804 sw $v0,388($sp) */
	.word	0x3C013F80  /* 00166808 lui $at,0x3f80 */
	.word	0x4481B000  /* 0016680C mtc1 $at,$f22 */
	.word	0x0000A82D  /* 00166810 move $s5,$zero */
	.word	0x8FB70184  /* 00166814 lw $s7,388($sp) */
	.word	0x8FA20180  /* 00166818 lw $v0,384($sp) */
	.word	0x4600AB06  /* 0016681C mov.s $f12,$f21 */
	.word	0x8E840150  /* 00166820 lw $a0,336($s4) */
	.word	0x02A0902D  /* 00166824 move $s2,$s5 */
	.word	0x8E850168  /* 00166828 lw $a1,360($s4) */
	.word	0x00028900  /* 0016682C sll $s1,$v0,0x4 */
	.word	0x8E860164  /* 00166830 lw $a2,356($s4) */
	.word	0x00952021  /* 00166834 addu $a0,$a0,$s5 */
	.word	0x00B12821  /* 00166838 addu $a1,$a1,$s1 */
	.word	0x0C000000  /* 0016683C jal func_002674f0 */
	.reloc	.-4, R_MIPS_26, func_002674f0
	.word	0x00D13021  /* 00166840 addu $a2,$a2,$s1 */
	.word	0x8EE2002C  /* 00166844 lw $v0,44($s7) */
	.word	0x240303FF  /* 00166848 li $v1,1023 */
	.word	0x304203FF  /* 0016684C andi $v0,$v0,0x3ff */
	.word	0x5443000F  /* 00166850 bnel $v0,$v1,.L00166890 */
	.word	0x8E840150  /* 00166854 lw $a0,336($s4) */
	.word	0x8E820150  /* 00166858 lw $v0,336($s4) */
	.word	0x02A21021  /* 0016685C addu $v0,$s5,$v0 */
	.word	0xC4400000  /* 00166860 lwc1 $f0,0($v0) */
	.word	0xE4400010  /* 00166864 swc1 $f0,16($v0) */
	.word	0x8E830150  /* 00166868 lw $v1,336($s4) */
	.word	0x02A31821  /* 0016686C addu $v1,$s5,$v1 */
	.word	0xC4600004  /* 00166870 lwc1 $f0,4($v1) */
	.word	0xE4600014  /* 00166874 swc1 $f0,20($v1) */
	.word	0x8E820150  /* 00166878 lw $v0,336($s4) */
	.word	0x02A21021  /* 0016687C addu $v0,$s5,$v0 */
	.word	0xC4400008  /* 00166880 lwc1 $f0,8($v0) */
	.word	0x10000009  /* 00166884 b .L001668AC */
	.word	0xE4400018  /* 00166888 swc1 $f0,24($v0) */
	.word	0x00000000  /* 0016688C nop */
	.word	0x00022980  /* 00166890 sll $a1,$v0,0x6 */
	.word	0x00852821  /* 00166894 addu $a1,$a0,$a1 */
	.word	0x00952021  /* 00166898 addu $a0,$a0,$s5 */
	.word	0x0080302D  /* 0016689C move $a2,$a0 */
	.word	0x24840010  /* 001668A0 addiu $a0,$a0,16 */
	.word	0x0C000000  /* 001668A4 jal func_001627d0 */
	.reloc	.-4, R_MIPS_26, func_001627d0
	.word	0x24A50010  /* 001668A8 addiu $a1,$a1,16 */
	.word	0x8FA30188  /* 001668AC lw $v1,392($sp) */
	.word	0x8FA40180  /* 001668B0 lw $a0,384($sp) */
	.word	0x84620000  /* 001668B4 lh $v0,0($v1) */
	.word	0x544401ED  /* 001668B8 bnel $v0,$a0,.L00167070 */
	.word	0x8EE3002C  /* 001668BC lw $v1,44($s7) */
	.word	0x27B300C0  /* 001668C0 addiu $s3,$sp,192 */
	.word	0x24650020  /* 001668C4 addiu $a1,$v1,32 */
	.word	0x24660010  /* 001668C8 addiu $a2,$v1,16 */
	.word	0x4600AB06  /* 001668CC mov.s $f12,$f21 */
	.word	0x3C013F80  /* 001668D0 lui $at,0x3f80 */
	.word	0x4481A000  /* 001668D4 mtc1 $at,$f20 */
	.word	0x0C000000  /* 001668D8 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x0260202D  /* 001668DC move $a0,$s3 */
	.word	0x0260202D  /* 001668E0 move $a0,$s3 */
	.word	0x3C020000  /* 001668E4 lui $v0,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x0260302D  /* 001668E8 move $a2,$s3 */
	.word	0x24450000  /* 001668EC addiu $a1,$v0,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x0C000000  /* 001668F0 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xE7B400CC  /* 001668F4 swc1 $f20,204($sp) */
	.word	0x8E820150  /* 001668F8 lw $v0,336($s4) */
	.word	0x8E830158  /* 001668FC lw $v1,344($s4) */
	.word	0x27B600D0  /* 00166900 addiu $s6,$sp,208 */
	.word	0x02A21021  /* 00166904 addu $v0,$s5,$v0 */
	.word	0x02C0202D  /* 00166908 move $a0,$s6 */
	.word	0xC4400030  /* 0016690C lwc1 $f0,48($v0) */
	.word	0x02A31821  /* 00166910 addu $v1,$s5,$v1 */
	.word	0x4600AB06  /* 00166914 mov.s $f12,$f21 */
	.word	0xE4600030  /* 00166918 swc1 $f0,48($v1) */
	.word	0x8E820150  /* 0016691C lw $v0,336($s4) */
	.word	0x8E830158  /* 00166920 lw $v1,344($s4) */
	.word	0x02A21021  /* 00166924 addu $v0,$s5,$v0 */
	.word	0xC4400034  /* 00166928 lwc1 $f0,52($v0) */
	.word	0x02A31821  /* 0016692C addu $v1,$s5,$v1 */
	.word	0xE4600034  /* 00166930 swc1 $f0,52($v1) */
	.word	0x8E820150  /* 00166934 lw $v0,336($s4) */
	.word	0x8E830158  /* 00166938 lw $v1,344($s4) */
	.word	0x02A21021  /* 0016693C addu $v0,$s5,$v0 */
	.word	0xC4400038  /* 00166940 lwc1 $f0,56($v0) */
	.word	0x02A31821  /* 00166944 addu $v1,$s5,$v1 */
	.word	0xE4600038  /* 00166948 swc1 $f0,56($v1) */
	.word	0x8E850160  /* 0016694C lw $a1,352($s4) */
	.word	0x8E86015C  /* 00166950 lw $a2,348($s4) */
	.word	0x00B52821  /* 00166954 addu $a1,$a1,$s5 */
	.word	0x00D53021  /* 00166958 addu $a2,$a2,$s5 */
	.word	0x24A50010  /* 0016695C addiu $a1,$a1,16 */
	.word	0x0C000000  /* 00166960 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x24C60010  /* 00166964 addiu $a2,$a2,16 */
	.word	0x8E860150  /* 00166968 lw $a2,336($s4) */
	.word	0x02C0202D  /* 0016696C move $a0,$s6 */
	.word	0x02C0282D  /* 00166970 move $a1,$s6 */
	.word	0x00D53021  /* 00166974 addu $a2,$a2,$s5 */
	.word	0x0C000000  /* 00166978 jal func_00267518 */
	.reloc	.-4, R_MIPS_26, func_00267518
	.word	0x24C60030  /* 0016697C addiu $a2,$a2,48 */
	.word	0x24020001  /* 00166980 li $v0,1 */
	.word	0xAFA000DC  /* 00166984 sw $zero,220($sp) */
	.word	0x8FA40188  /* 00166988 lw $a0,392($sp) */
	.word	0x84830002  /* 0016698C lh $v1,2($a0) */
	.word	0x50620009  /* 00166990 beql $v1,$v0,.L001669B8 */
	.word	0x8EE4002C  /* 00166994 lw $a0,44($s7) */
	.word	0x586001B5  /* 00166998 blezl $v1,.L00167070 */
	.word	0x8EE3002C  /* 0016699C lw $v1,44($s7) */
	.word	0x28620004  /* 001669A0 slti $v0,$v1,4 */
	.word	0x504001B2  /* 001669A4 beqzl $v0,.L00167070 */
	.word	0x8EE3002C  /* 001669A8 lw $v1,44($s7) */
	.word	0x10000052  /* 001669AC b .L00166AF8 */
	.word	0x8E850164  /* 001669B0 lw $a1,356($s4) */
	.word	0x00000000  /* 001669B4 nop */
	.word	0x27B00100  /* 001669B8 addiu $s0,$sp,256 */
	.word	0x8FA30188  /* 001669BC lw $v1,392($sp) */
	.word	0x0200282D  /* 001669C0 move $a1,$s0 */
	.word	0x8E820154  /* 001669C4 lw $v0,340($s4) */
	.word	0x308403FF  /* 001669C8 andi $a0,$a0,0x3ff */
	.word	0x00042180  /* 001669CC sll $a0,$a0,0x6 */
	.word	0x24630030  /* 001669D0 addiu $v1,$v1,48 */
	.word	0x00442021  /* 001669D4 addu $a0,$v0,$a0 */
	.word	0x0C000000  /* 001669D8 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0xAFA30188  /* 001669DC sw $v1,392($sp) */
	.word	0x0260202D  /* 001669E0 move $a0,$s3 */
	.word	0x0200282D  /* 001669E4 move $a1,$s0 */
	.word	0x0C000000  /* 001669E8 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x0260302D  /* 001669EC move $a2,$s3 */
	.word	0x8E820150  /* 001669F0 lw $v0,336($s4) */
	.word	0xC6E00050  /* 001669F4 lwc1 $f0,80($s7) */
	.word	0x02C0402D  /* 001669F8 move $t0,$s6 */
	.word	0x02421021  /* 001669FC addu $v0,$s2,$v0 */
	.word	0x44806800  /* 00166A00 mtc1 $zero,$f13 */
	.word	0xC44C0000  /* 00166A04 lwc1 $f12,0($v0) */
	.word	0x0000382D  /* 00166A08 move $a3,$zero */
	.word	0x8E860158  /* 00166A0C lw $a2,344($s4) */
	.word	0x46006B86  /* 00166A10 mov.s $f14,$f13 */
	.word	0x46006302  /* 00166A14 mul.s $f12,$f12,$f0 */
	.word	0x46006BC6  /* 00166A18 mov.s $f15,$f13 */
	.word	0x00D23021  /* 00166A1C addu $a2,$a2,$s2 */
	.word	0x0260202D  /* 00166A20 move $a0,$s3 */
	.word	0x0C000000  /* 00166A24 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0x0000282D  /* 00166A28 move $a1,$zero */
	.word	0x8E910158  /* 00166A2C lw $s1,344($s4) */
	.word	0x8E900150  /* 00166A30 lw $s0,336($s4) */
	.word	0x03A0202D  /* 00166A34 move $a0,$sp */
	.word	0x02518821  /* 00166A38 addu $s1,$s2,$s1 */
	.word	0x02508021  /* 00166A3C addu $s0,$s2,$s0 */
	.word	0x0220282D  /* 00166A40 move $a1,$s1 */
	.word	0x0C000000  /* 00166A44 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00166A48 lwc1 $f12,0($s0) */
	.word	0x26250010  /* 00166A4C addiu $a1,$s1,16 */
	.word	0xC60C0004  /* 00166A50 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00166A54 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A40010  /* 00166A58 addiu $a0,$sp,16 */
	.word	0x26250020  /* 00166A5C addiu $a1,$s1,32 */
	.word	0xC60C0008  /* 00166A60 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00166A64 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x27A40020  /* 00166A68 addiu $a0,$sp,32 */
	.word	0x26250030  /* 00166A6C addiu $a1,$s1,48 */
	.word	0x0C000000  /* 00166A70 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x27A40030  /* 00166A74 addiu $a0,$sp,48 */
	.word	0x8E820154  /* 00166A78 lw $v0,340($s4) */
	.word	0x8EE5002C  /* 00166A7C lw $a1,44($s7) */
	.word	0x03A0302D  /* 00166A80 move $a2,$sp */
	.word	0x00522021  /* 00166A84 addu $a0,$v0,$s2 */
	.word	0x30A503FF  /* 00166A88 andi $a1,$a1,0x3ff */
	.word	0x00052980  /* 00166A8C sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00166A90 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00452821  /* 00166A94 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00166A98 lw $v0,340($s4) */
	.word	0x8EE5002C  /* 00166A9C lw $a1,44($s7) */
	.word	0x8E860150  /* 00166AA0 lw $a2,336($s4) */
	.word	0x00522021  /* 00166AA4 addu $a0,$v0,$s2 */
	.word	0x30A503FF  /* 00166AA8 andi $a1,$a1,0x3ff */
	.word	0x24840030  /* 00166AAC addiu $a0,$a0,48 */
	.word	0x00052980  /* 00166AB0 sll $a1,$a1,0x6 */
	.word	0x00D23021  /* 00166AB4 addu $a2,$a2,$s2 */
	.word	0x00452821  /* 00166AB8 addu $a1,$v0,$a1 */
	.word	0x0C000000  /* 00166ABC jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24C60030  /* 00166AC0 addiu $a2,$a2,48 */
	.word	0x8E820154  /* 00166AC4 lw $v0,340($s4) */
	.word	0x02421021  /* 00166AC8 addu $v0,$s2,$v0 */
	.word	0xE454003C  /* 00166ACC swc1 $f20,60($v0) */
	.word	0x8E860150  /* 00166AD0 lw $a2,336($s4) */
	.word	0x8E840158  /* 00166AD4 lw $a0,344($s4) */
	.word	0x8E850154  /* 00166AD8 lw $a1,340($s4) */
	.word	0x00D23021  /* 00166ADC addu $a2,$a2,$s2 */
	.word	0x00922021  /* 00166AE0 addu $a0,$a0,$s2 */
	.word	0x24C60010  /* 00166AE4 addiu $a2,$a2,16 */
	.word	0x0C000000  /* 00166AE8 jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x00B22821  /* 00166AEC addu $a1,$a1,$s2 */
	.word	0x10000209  /* 00166AF0 b .L00167318 */
	.word	0x8FA20180  /* 00166AF4 lw $v0,384($sp) */
	.word	0x27B200E0  /* 00166AF8 addiu $s2,$sp,224 */
	.word	0x0240202D  /* 00166AFC move $a0,$s2 */
	.word	0x00B12821  /* 00166B00 addu $a1,$a1,$s1 */
	.word	0x0C000000  /* 00166B04 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x24A50010  /* 00166B08 addiu $a1,$a1,16 */
	.word	0x8E850168  /* 00166B0C lw $a1,360($s4) */
	.word	0x27B000F0  /* 00166B10 addiu $s0,$sp,240 */
	.word	0x00B12821  /* 00166B14 addu $a1,$a1,$s1 */
	.word	0x0200202D  /* 00166B18 move $a0,$s0 */
	.word	0x0C000000  /* 00166B1C jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x24A50010  /* 00166B20 addiu $a1,$a1,16 */
	.word	0x3C014049  /* 00166B24 lui $at,0x4049 */
	.word	0x34210FDA  /* 00166B28 ori $at,$at,0xfda */
	.word	0x44811800  /* 00166B2C mtc1 $at,$f3 */
	.word	0xC7A000EC  /* 00166B30 lwc1 $f0,236($sp) */
	.word	0xC7A100FC  /* 00166B34 lwc1 $f1,252($sp) */
	.word	0x3C0140C9  /* 00166B38 lui $at,0x40c9 */
	.word	0x34210FDA  /* 00166B3C ori $at,$at,0xfda */
	.word	0x44811000  /* 00166B40 mtc1 $at,$f2 */
	.word	0x46000841  /* 00166B44 sub.s $f1,$f1,$f0 */
	.word	0x3C01C049  /* 00166B48 lui $at,0xc049 */
	.word	0x34210FDA  /* 00166B4C ori $at,$at,0xfda */
	.word	0x44810000  /* 00166B50 mtc1 $at,$f0 */
	.word	0x00000000  /* 00166B54 nop */
	.word	0x46011834  /* 00166B58 c.lt.s $f3,$f1 */
	.word	0x45000004  /* 00166B5C bc1f .L00166B70 */
	.word	0x00000000  /* 00166B60 nop */
	.word	0x1000FFFC  /* 00166B64 b .L00166B58 */
	.word	0x46020841  /* 00166B68 sub.s $f1,$f1,$f2 */
	.word	0x00000000  /* 00166B6C nop */
	.word	0x46000834  /* 00166B70 c.lt.s $f1,$f0 */
	.word	0x45020004  /* 00166B74 bc1fl .L00166B88 */
	.word	0x8E840150  /* 00166B78 lw $a0,336($s4) */
	.word	0x1000FFF6  /* 00166B7C b .L00166B58 */
	.word	0x46020840  /* 00166B80 add.s $f1,$f1,$f2 */
	.word	0x00000000  /* 00166B84 nop */
	.word	0x0200282D  /* 00166B88 move $a1,$s0 */
	.word	0x0240302D  /* 00166B8C move $a2,$s2 */
	.word	0x4600AB06  /* 00166B90 mov.s $f12,$f21 */
	.word	0x00952021  /* 00166B94 addu $a0,$a0,$s5 */
	.word	0xE7A100FC  /* 00166B98 swc1 $f1,252($sp) */
	.word	0x24840040  /* 00166B9C addiu $a0,$a0,64 */
	.word	0x0C000000  /* 00166BA0 jal func_002674f0 */
	.reloc	.-4, R_MIPS_26, func_002674f0
	.word	0xAFA000EC  /* 00166BA4 sw $zero,236($sp) */
	.word	0x8E840150  /* 00166BA8 lw $a0,336($s4) */
	.word	0x8E820164  /* 00166BAC lw $v0,356($s4) */
	.word	0x02A41821  /* 00166BB0 addu $v1,$s5,$a0 */
	.word	0x3C014049  /* 00166BB4 lui $at,0x4049 */
	.word	0x34210FDA  /* 00166BB8 ori $at,$at,0xfda */
	.word	0x44811800  /* 00166BBC mtc1 $at,$f3 */
	.word	0x02221021  /* 00166BC0 addu $v0,$s1,$v0 */
	.word	0xC461004C  /* 00166BC4 lwc1 $f1,76($v1) */
	.word	0xC440001C  /* 00166BC8 lwc1 $f0,28($v0) */
	.word	0x3C0140C9  /* 00166BCC lui $at,0x40c9 */
	.word	0x34210FDA  /* 00166BD0 ori $at,$at,0xfda */
	.word	0x44811000  /* 00166BD4 mtc1 $at,$f2 */
	.word	0x46000840  /* 00166BD8 add.s $f1,$f1,$f0 */
	.word	0x3C01C049  /* 00166BDC lui $at,0xc049 */
	.word	0x34210FDA  /* 00166BE0 ori $at,$at,0xfda */
	.word	0x44810000  /* 00166BE4 mtc1 $at,$f0 */
	.word	0x46011834  /* 00166BE8 c.lt.s $f3,$f1 */
	.word	0x45000004  /* 00166BEC bc1f .L00166C00 */
	.word	0x00000000  /* 00166BF0 nop */
	.word	0x1000FFFC  /* 00166BF4 b .L00166BE8 */
	.word	0x46020841  /* 00166BF8 sub.s $f1,$f1,$f2 */
	.word	0x00000000  /* 00166BFC nop */
	.word	0x46000834  /* 00166C00 c.lt.s $f1,$f0 */
	.word	0x45000004  /* 00166C04 bc1f .L00166C18 */
	.word	0x02A41021  /* 00166C08 addu $v0,$s5,$a0 */
	.word	0x1000FFF6  /* 00166C0C b .L00166BE8 */
	.word	0x46020840  /* 00166C10 add.s $f1,$f1,$f2 */
	.word	0x00000000  /* 00166C14 nop */
	.word	0x27B20100  /* 00166C18 addiu $s2,$sp,256 */
	.word	0xE441004C  /* 00166C1C swc1 $f1,76($v0) */
	.word	0x0240282D  /* 00166C20 move $a1,$s2 */
	.word	0x4480A000  /* 00166C24 mtc1 $zero,$f20 */
	.word	0x8EE4002C  /* 00166C28 lw $a0,44($s7) */
	.word	0x8E820154  /* 00166C2C lw $v0,340($s4) */
	.word	0x308403FF  /* 00166C30 andi $a0,$a0,0x3ff */
	.word	0x00042180  /* 00166C34 sll $a0,$a0,0x6 */
	.word	0x0C000000  /* 00166C38 jal func_001625c8 */
	.reloc	.-4, R_MIPS_26, func_001625c8
	.word	0x00442021  /* 00166C3C addu $a0,$v0,$a0 */
	.word	0x8E83000C  /* 00166C40 lw $v1,12($s4) */
	.word	0x30620003  /* 00166C44 andi $v0,$v1,0x3 */
	.word	0x10400012  /* 00166C48 beqz $v0,.L00166C94 */
	.word	0x0000382D  /* 00166C4C move $a3,$zero */
	.word	0x8E840000  /* 00166C50 lw $a0,0($s4) */
	.word	0x30660020  /* 00166C54 andi $a2,$v1,0x20 */
	.word	0x24050003  /* 00166C58 li $a1,3 */
	.word	0x8C820000  /* 00166C5C lw $v0,0($a0) */
	.word	0x8C430008  /* 00166C60 lw $v1,8($v0) */
	.word	0x00000000  /* 00166C64 nop */
	.word	0x8C620090  /* 00166C68 lw $v0,144($v1) */
	.word	0x8FA40180  /* 00166C6C lw $a0,384($sp) */
	.word	0x2442FFFF  /* 00166C70 addiu $v0,$v0,-1 */
	.word	0x54820005  /* 00166C74 bnel $a0,$v0,.L00166C8C */
	.word	0x24A5FFFF  /* 00166C78 addiu $a1,$a1,-1 */
	.word	0x14C00002  /* 00166C7C bnez $a2,.L00166C88 */
	.word	0x24070001  /* 00166C80 li $a3,1 */
	.word	0xC4740000  /* 00166C84 lwc1 $f20,0($v1) */
	.word	0x24A5FFFF  /* 00166C88 addiu $a1,$a1,-1 */
	.word	0x04A1FFF6  /* 00166C8C bgez $a1,.L00166C68 */
	.word	0x24630004  /* 00166C90 addiu $v1,$v1,4 */
	.word	0x10E00053  /* 00166C94 beqz $a3,.L00166DE4 */
	.word	0x3C020000  /* 00166C98 lui $v0,%hi(D_00574F20) */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0xC7A400C0  /* 00166C9C lwc1 $f4,192($sp) */
	.word	0x24510000  /* 00166CA0 addiu $s1,$v0,%lo(D_00574F20) */
	.reloc	.-4, R_MIPS_LO16, D_00574F20
	.word	0x3C030000  /* 00166CA4 lui $v1,%hi(D_00574F10) */
	.reloc	.-4, R_MIPS_HI16, D_00574F10
	.word	0xC6200000  /* 00166CA8 lwc1 $f0,0($s1) */
	.word	0x24700000  /* 00166CAC addiu $s0,$v1,%lo(D_00574F10) */
	.reloc	.-4, R_MIPS_LO16, D_00574F10
	.word	0xC6050000  /* 00166CB0 lwc1 $f5,0($s0) */
	.word	0x27A40140  /* 00166CB4 addiu $a0,$sp,320 */
	.word	0x46002102  /* 00166CB8 mul.s $f4,$f4,$f0 */
	.word	0xC6000008  /* 00166CBC lwc1 $f0,8($s0) */
	.word	0xC6270004  /* 00166CC0 lwc1 $f7,4($s1) */
	.word	0xC6210008  /* 00166CC4 lwc1 $f1,8($s1) */
	.word	0xC6060004  /* 00166CC8 lwc1 $f6,4($s0) */
	.word	0x46052100  /* 00166CCC add.s $f4,$f4,$f5 */
	.word	0xC7A300C8  /* 00166CD0 lwc1 $f3,200($sp) */
	.word	0xC7A200C4  /* 00166CD4 lwc1 $f2,196($sp) */
	.word	0x460118C2  /* 00166CD8 mul.s $f3,$f3,$f1 */
	.word	0x8FA5018C  /* 00166CDC lw $a1,396($sp) */
	.word	0xE7A40140  /* 00166CE0 swc1 $f4,320($sp) */
	.word	0xC6E10080  /* 00166CE4 lwc1 $f1,128($s7) */
	.word	0x460018C0  /* 00166CE8 add.s $f3,$f3,$f0 */
	.word	0xE7B6014C  /* 00166CEC swc1 $f22,332($sp) */
	.word	0x46011081  /* 00166CF0 sub.s $f2,$f2,$f1 */
	.word	0xAFA00150  /* 00166CF4 sw $zero,336($sp) */
	.word	0xE7A30148  /* 00166CF8 swc1 $f3,328($sp) */
	.word	0x46071082  /* 00166CFC mul.s $f2,$f2,$f7 */
	.word	0x46061080  /* 00166D00 add.s $f2,$f2,$f6 */
	.word	0xE7A20144  /* 00166D04 swc1 $f2,324($sp) */
	.word	0xC6E00080  /* 00166D08 lwc1 $f0,128($s7) */
	.word	0xAFA00158  /* 00166D0C sw $zero,344($sp) */
	.word	0x46000000  /* 00166D10 add.s $f0,$f0,$f0 */
	.word	0xE7B6015C  /* 00166D14 swc1 $f22,348($sp) */
	.word	0x46140000  /* 00166D18 add.s $f0,$f0,$f20 */
	.word	0x46070002  /* 00166D1C mul.s $f0,$f0,$f7 */
	.word	0x0C000000  /* 00166D20 jal func_00118590 */
	.reloc	.-4, R_MIPS_26, func_00118590
	.word	0xE7A00154  /* 00166D24 swc1 $f0,340($sp) */
	.word	0x87A30170  /* 00166D28 lh $v1,368($sp) */
	.word	0x2402FFFF  /* 00166D2C li $v0,-1 */
	.word	0x1062002D  /* 00166D30 beq $v1,$v0,.L00166DE8 */
	.word	0x8FA20180  /* 00166D34 lw $v0,384($sp) */
	.word	0x8E83000C  /* 00166D38 lw $v1,12($s4) */
	.word	0x30620002  /* 00166D3C andi $v0,$v1,0x2 */
	.word	0x1440000D  /* 00166D40 bnez $v0,.L00166D78 */
	.word	0xC6260004  /* 00166D44 lwc1 $f6,4($s1) */
	.word	0xC7A000C4  /* 00166D48 lwc1 $f0,196($sp) */
	.word	0x46140000  /* 00166D4C add.s $f0,$f0,$f20 */
	.word	0xC6010004  /* 00166D50 lwc1 $f1,4($s0) */
	.word	0xC7A30164  /* 00166D54 lwc1 $f3,356($sp) */
	.word	0x46060002  /* 00166D58 mul.s $f0,$f0,$f6 */
	.word	0x46010000  /* 00166D5C add.s $f0,$f0,$f1 */
	.word	0x46001834  /* 00166D60 c.lt.s $f3,$f0 */
	.word	0x45000020  /* 00166D64 bc1f .L00166DE8 */
	.word	0x8FA20180  /* 00166D68 lw $v0,384($sp) */
	.word	0x10000005  /* 00166D6C b .L00166D84 */
	.word	0x460118C1  /* 00166D70 sub.s $f3,$f3,$f1 */
	.word	0x00000000  /* 00166D74 nop */
	.word	0xC6010004  /* 00166D78 lwc1 $f1,4($s0) */
	.word	0xC7A30164  /* 00166D7C lwc1 $f3,356($sp) */
	.word	0x460118C1  /* 00166D80 sub.s $f3,$f3,$f1 */
	.word	0xC7A10160  /* 00166D84 lwc1 $f1,352($sp) */
	.word	0xC6020000  /* 00166D88 lwc1 $f2,0($s0) */
	.word	0x3C020020  /* 00166D8C lui $v0,0x20 */
	.word	0xC6050008  /* 00166D90 lwc1 $f5,8($s0) */
	.word	0x00621025  /* 00166D94 or $v0,$v1,$v0 */
	.word	0xC7A00168  /* 00166D98 lwc1 $f0,360($sp) */
	.word	0x46020841  /* 00166D9C sub.s $f1,$f1,$f2 */
	.word	0x00000000  /* 00166DA0 nop */
	.word	0x00000000  /* 00166DA4 nop */
	.word	0x460618C3  /* 00166DA8 div.s $f3,$f3,$f6 */
	.word	0xC6240008  /* 00166DAC lwc1 $f4,8($s1) */
	.word	0x46050001  /* 00166DB0 sub.s $f0,$f0,$f5 */
	.word	0xC6220000  /* 00166DB4 lwc1 $f2,0($s1) */
	.word	0xAE82000C  /* 00166DB8 sw $v0,12($s4) */
	.word	0x00000000  /* 00166DBC nop */
	.word	0x00000000  /* 00166DC0 nop */
	.word	0x46020843  /* 00166DC4 div.s $f1,$f1,$f2 */
	.word	0x461418C1  /* 00166DC8 sub.s $f3,$f3,$f20 */
	.word	0x00000000  /* 00166DCC nop */
	.word	0x00000000  /* 00166DD0 nop */
	.word	0x46040003  /* 00166DD4 div.s $f0,$f0,$f4 */
	.word	0xE7A300C4  /* 00166DD8 swc1 $f3,196($sp) */
	.word	0xE7A100C0  /* 00166DDC swc1 $f1,192($sp) */
	.word	0xE7A000C8  /* 00166DE0 swc1 $f0,200($sp) */
	.word	0x8FA20180  /* 00166DE4 lw $v0,384($sp) */
	.word	0x0240282D  /* 00166DE8 move $a1,$s2 */
	.word	0x0260202D  /* 00166DEC move $a0,$s3 */
	.word	0x0260302D  /* 00166DF0 move $a2,$s3 */
	.word	0x24420001  /* 00166DF4 addiu $v0,$v0,1 */
	.word	0x0C000000  /* 00166DF8 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0xAFA20180  /* 00166DFC sw $v0,384($sp) */
	.word	0x8E820150  /* 00166E00 lw $v0,336($s4) */
	.word	0x02C0402D  /* 00166E04 move $t0,$s6 */
	.word	0xC6EC0050  /* 00166E08 lwc1 $f12,80($s7) */
	.word	0x0260202D  /* 00166E0C move $a0,$s3 */
	.word	0x02A21021  /* 00166E10 addu $v0,$s5,$v0 */
	.word	0xC6ED0080  /* 00166E14 lwc1 $f13,128($s7) */
	.word	0x24430040  /* 00166E18 addiu $v1,$v0,64 */
	.word	0xC4400000  /* 00166E1C lwc1 $f0,0($v0) */
	.word	0xC4610000  /* 00166E20 lwc1 $f1,0($v1) */
	.word	0x460C0302  /* 00166E24 mul.s $f12,$f0,$f12 */
	.word	0x8FA20188  /* 00166E28 lw $v0,392($sp) */
	.word	0x46010002  /* 00166E2C mul.s $f0,$f0,$f1 */
	.word	0x8E860158  /* 00166E30 lw $a2,344($s4) */
	.word	0x84450002  /* 00166E34 lh $a1,2($v0) */
	.word	0x24420030  /* 00166E38 addiu $v0,$v0,48 */
	.word	0xC46F000C  /* 00166E3C lwc1 $f15,12($v1) */
	.word	0x00D53021  /* 00166E40 addu $a2,$a2,$s5 */
	.word	0x44807000  /* 00166E44 mtc1 $zero,$f14 */
	.word	0x24C70040  /* 00166E48 addiu $a3,$a2,64 */
	.word	0x460D0342  /* 00166E4C mul.s $f13,$f0,$f13 */
	.word	0x24A5FFFE  /* 00166E50 addiu $a1,$a1,-2 */
	.word	0x0C000000  /* 00166E54 jal func_00162d00 */
	.reloc	.-4, R_MIPS_26, func_00162d00
	.word	0xAFA20188  /* 00166E58 sw $v0,392($sp) */
	.word	0x8E910158  /* 00166E5C lw $s1,344($s4) */
	.word	0x8E900150  /* 00166E60 lw $s0,336($s4) */
	.word	0x03A0202D  /* 00166E64 move $a0,$sp */
	.word	0x02B18821  /* 00166E68 addu $s1,$s5,$s1 */
	.word	0x02B08021  /* 00166E6C addu $s0,$s5,$s0 */
	.word	0x0220282D  /* 00166E70 move $a1,$s1 */
	.word	0x0C000000  /* 00166E74 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00166E78 lwc1 $f12,0($s0) */
	.word	0x26250010  /* 00166E7C addiu $a1,$s1,16 */
	.word	0x27A30010  /* 00166E80 addiu $v1,$sp,16 */
	.word	0xC60C0004  /* 00166E84 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00166E88 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0060202D  /* 00166E8C move $a0,$v1 */
	.word	0x26250020  /* 00166E90 addiu $a1,$s1,32 */
	.word	0x27A20020  /* 00166E94 addiu $v0,$sp,32 */
	.word	0xC60C0008  /* 00166E98 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00166E9C jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0040202D  /* 00166EA0 move $a0,$v0 */
	.word	0x26250030  /* 00166EA4 addiu $a1,$s1,48 */
	.word	0x27A30030  /* 00166EA8 addiu $v1,$sp,48 */
	.word	0x0C000000  /* 00166EAC jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x0060202D  /* 00166EB0 move $a0,$v1 */
	.word	0x8E820154  /* 00166EB4 lw $v0,340($s4) */
	.word	0x8EE5002C  /* 00166EB8 lw $a1,44($s7) */
	.word	0x03A0302D  /* 00166EBC move $a2,$sp */
	.word	0x00552021  /* 00166EC0 addu $a0,$v0,$s5 */
	.word	0x30A503FF  /* 00166EC4 andi $a1,$a1,0x3ff */
	.word	0x00052980  /* 00166EC8 sll $a1,$a1,0x6 */
	.word	0x0C000000  /* 00166ECC jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00452821  /* 00166ED0 addu $a1,$v0,$a1 */
	.word	0x8E820154  /* 00166ED4 lw $v0,340($s4) */
	.word	0x8EE5002C  /* 00166ED8 lw $a1,44($s7) */
	.word	0x8E860150  /* 00166EDC lw $a2,336($s4) */
	.word	0x00552021  /* 00166EE0 addu $a0,$v0,$s5 */
	.word	0x30A503FF  /* 00166EE4 andi $a1,$a1,0x3ff */
	.word	0x24840030  /* 00166EE8 addiu $a0,$a0,48 */
	.word	0x00D53021  /* 00166EEC addu $a2,$a2,$s5 */
	.word	0x00052980  /* 00166EF0 sll $a1,$a1,0x6 */
	.word	0x00452821  /* 00166EF4 addu $a1,$v0,$a1 */
	.word	0x0C000000  /* 00166EF8 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24C60030  /* 00166EFC addiu $a2,$a2,48 */
	.word	0x8E820154  /* 00166F00 lw $v0,340($s4) */
	.word	0x02A21021  /* 00166F04 addu $v0,$s5,$v0 */
	.word	0xE456003C  /* 00166F08 swc1 $f22,60($v0) */
	.word	0x8E860150  /* 00166F0C lw $a2,336($s4) */
	.word	0x8E840158  /* 00166F10 lw $a0,344($s4) */
	.word	0x8E850154  /* 00166F14 lw $a1,340($s4) */
	.word	0x00D53021  /* 00166F18 addu $a2,$a2,$s5 */
	.word	0x24C60010  /* 00166F1C addiu $a2,$a2,16 */
	.word	0x00952021  /* 00166F20 addu $a0,$a0,$s5 */
	.word	0x0C000000  /* 00166F24 jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x00B52821  /* 00166F28 addu $a1,$a1,$s5 */
	.word	0x0C000000  /* 00166F2C jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x03A0202D  /* 00166F30 move $a0,$sp */
	.word	0x8E820150  /* 00166F34 lw $v0,336($s4) */
	.word	0x8E860158  /* 00166F38 lw $a2,344($s4) */
	.word	0x03A0202D  /* 00166F3C move $a0,$sp */
	.word	0x02A21021  /* 00166F40 addu $v0,$s5,$v0 */
	.word	0x03A0282D  /* 00166F44 move $a1,$sp */
	.word	0xC4410000  /* 00166F48 lwc1 $f1,0($v0) */
	.word	0x00D53021  /* 00166F4C addu $a2,$a2,$s5 */
	.word	0x24C60040  /* 00166F50 addiu $a2,$a2,64 */
	.word	0x00000000  /* 00166F54 nop */
	.word	0x00000000  /* 00166F58 nop */
	.word	0x4601B043  /* 00166F5C div.s $f1,$f22,$f1 */
	.word	0xE7A10000  /* 00166F60 swc1 $f1,0($sp) */
	.word	0xC4400004  /* 00166F64 lwc1 $f0,4($v0) */
	.word	0x00000000  /* 00166F68 nop */
	.word	0x00000000  /* 00166F6C nop */
	.word	0x4600B003  /* 00166F70 div.s $f0,$f22,$f0 */
	.word	0xE7A00014  /* 00166F74 swc1 $f0,20($sp) */
	.word	0xC4410008  /* 00166F78 lwc1 $f1,8($v0) */
	.word	0x00000000  /* 00166F7C nop */
	.word	0x00000000  /* 00166F80 nop */
	.word	0x4601B043  /* 00166F84 div.s $f1,$f22,$f1 */
	.word	0x0C000000  /* 00166F88 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0xE7A10028  /* 00166F8C swc1 $f1,40($sp) */
	.word	0x8E840150  /* 00166F90 lw $a0,336($s4) */
	.word	0x00952021  /* 00166F94 addu $a0,$a0,$s5 */
	.word	0x0080282D  /* 00166F98 move $a1,$a0 */
	.word	0x24840050  /* 00166F9C addiu $a0,$a0,80 */
	.word	0x0C000000  /* 00166FA0 jal func_001627d0 */
	.reloc	.-4, R_MIPS_26, func_001627d0
	.word	0x24A60040  /* 00166FA4 addiu $a2,$a1,64 */
	.word	0x8E900150  /* 00166FA8 lw $s0,336($s4) */
	.word	0x03A0202D  /* 00166FAC move $a0,$sp */
	.word	0x03A0282D  /* 00166FB0 move $a1,$sp */
	.word	0x02B08021  /* 00166FB4 addu $s0,$s5,$s0 */
	.word	0x26100050  /* 00166FB8 addiu $s0,$s0,80 */
	.word	0x0C000000  /* 00166FBC jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0xC60C0000  /* 00166FC0 lwc1 $f12,0($s0) */
	.word	0xC60C0004  /* 00166FC4 lwc1 $f12,4($s0) */
	.word	0x27A20010  /* 00166FC8 addiu $v0,$sp,16 */
	.word	0x0040202D  /* 00166FCC move $a0,$v0 */
	.word	0x0C000000  /* 00166FD0 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0040282D  /* 00166FD4 move $a1,$v0 */
	.word	0xC60C0008  /* 00166FD8 lwc1 $f12,8($s0) */
	.word	0x27A30020  /* 00166FDC addiu $v1,$sp,32 */
	.word	0x0060202D  /* 00166FE0 move $a0,$v1 */
	.word	0x0C000000  /* 00166FE4 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0060282D  /* 00166FE8 move $a1,$v1 */
	.word	0x27A20030  /* 00166FEC addiu $v0,$sp,48 */
	.word	0x0040202D  /* 00166FF0 move $a0,$v0 */
	.word	0x0C000000  /* 00166FF4 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x0040282D  /* 00166FF8 move $a1,$v0 */
	.word	0x8E840154  /* 00166FFC lw $a0,340($s4) */
	.word	0x03A0302D  /* 00167000 move $a2,$sp */
	.word	0x00952021  /* 00167004 addu $a0,$a0,$s5 */
	.word	0x0080282D  /* 00167008 move $a1,$a0 */
	.word	0x0C000000  /* 0016700C jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x24840040  /* 00167010 addiu $a0,$a0,64 */
	.word	0x8E840154  /* 00167014 lw $a0,340($s4) */
	.word	0x26E60050  /* 00167018 addiu $a2,$s7,80 */
	.word	0x26F70030  /* 0016701C addiu $s7,$s7,48 */
	.word	0x00952021  /* 00167020 addu $a0,$a0,$s5 */
	.word	0x0080282D  /* 00167024 move $a1,$a0 */
	.word	0x0C000000  /* 00167028 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24840070  /* 0016702C addiu $a0,$a0,112 */
	.word	0x8E820154  /* 00167030 lw $v0,340($s4) */
	.word	0x02A21021  /* 00167034 addu $v0,$s5,$v0 */
	.word	0xE456007C  /* 00167038 swc1 $f22,124($v0) */
	.word	0x8E840158  /* 0016703C lw $a0,344($s4) */
	.word	0x8E850154  /* 00167040 lw $a1,340($s4) */
	.word	0x8E860150  /* 00167044 lw $a2,336($s4) */
	.word	0x00952021  /* 00167048 addu $a0,$a0,$s5 */
	.word	0x00B52821  /* 0016704C addu $a1,$a1,$s5 */
	.word	0x24840040  /* 00167050 addiu $a0,$a0,64 */
	.word	0x00D53021  /* 00167054 addu $a2,$a2,$s5 */
	.word	0x26B50040  /* 00167058 addiu $s5,$s5,64 */
	.word	0x24A50040  /* 0016705C addiu $a1,$a1,64 */
	.word	0x0C000000  /* 00167060 jal func_001628a0 */
	.reloc	.-4, R_MIPS_26, func_001628a0
	.word	0x24C60050  /* 00167064 addiu $a2,$a2,80 */
	.word	0x100000AB  /* 00167068 b .L00167318 */
	.word	0x8FA20180  /* 0016706C lw $v0,384($sp) */
	.word	0x00031782  /* 00167070 srl $v0,$v1,0x1e */
	.word	0x30420001  /* 00167074 andi $v0,$v0,0x1 */
	.word	0x104000A6  /* 00167078 beqz $v0,.L00167314 */
	.word	0x307303FF  /* 0016707C andi $s3,$v1,0x3ff */
	.word	0x8E85015C  /* 00167080 lw $a1,348($s4) */
	.word	0x27B20040  /* 00167084 addiu $s2,$sp,64 */
	.word	0x0240202D  /* 00167088 move $a0,$s2 */
	.word	0x0C000000  /* 0016708C jal sceVu0CopyMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0CopyMatrix
	.word	0x00B52821  /* 00167090 addu $a1,$a1,$s5 */
	.word	0x8E850160  /* 00167094 lw $a1,352($s4) */
	.word	0x27B00080  /* 00167098 addiu $s0,$sp,128 */
	.word	0x00B52821  /* 0016709C addu $a1,$a1,$s5 */
	.word	0x0C000000  /* 001670A0 jal sceVu0CopyMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0CopyMatrix
	.word	0x0200202D  /* 001670A4 move $a0,$s0 */
	.word	0x240203FF  /* 001670A8 li $v0,1023 */
	.word	0x12620029  /* 001670AC beq $s3,$v0,.L00167154 */
	.word	0x8FA30184  /* 001670B0 lw $v1,388($sp) */
	.word	0x00138840  /* 001670B4 sll $s1,$s3,0x1 */
	.word	0x02331021  /* 001670B8 addu $v0,$s1,$s3 */
	.word	0x00021100  /* 001670BC sll $v0,$v0,0x4 */
	.word	0x00431021  /* 001670C0 addu $v0,$v0,$v1 */
	.word	0x8C43002C  /* 001670C4 lw $v1,44($v0) */
	.word	0x00031F82  /* 001670C8 srl $v1,$v1,0x1e */
	.word	0x30630001  /* 001670CC andi $v1,$v1,0x1 */
	.word	0x14600021  /* 001670D0 bnez $v1,.L00167158 */
	.word	0x27B60030  /* 001670D4 addiu $s6,$sp,48 */
	.word	0x0240B02D  /* 001670D8 move $s6,$s2 */
	.word	0x0200902D  /* 001670DC move $s2,$s0 */
	.word	0x241E03FF  /* 001670E0 li $s8,1023 */
	.word	0x8E85015C  /* 001670E4 lw $a1,348($s4) */
	.word	0x00138180  /* 001670E8 sll $s0,$s3,0x6 */
	.word	0x02C0202D  /* 001670EC move $a0,$s6 */
	.word	0x02C0302D  /* 001670F0 move $a2,$s6 */
	.word	0x0C000000  /* 001670F4 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00B02821  /* 001670F8 addu $a1,$a1,$s0 */
	.word	0x8E850160  /* 001670FC lw $a1,352($s4) */
	.word	0x0240202D  /* 00167100 move $a0,$s2 */
	.word	0x0240302D  /* 00167104 move $a2,$s2 */
	.word	0x0C000000  /* 00167108 jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00B02821  /* 0016710C addu $a1,$a1,$s0 */
	.word	0x02331021  /* 00167110 addu $v0,$s1,$s3 */
	.word	0x8FA40184  /* 00167114 lw $a0,388($sp) */
	.word	0x00021100  /* 00167118 sll $v0,$v0,0x4 */
	.word	0x00441021  /* 0016711C addu $v0,$v0,$a0 */
	.word	0x8C43002C  /* 00167120 lw $v1,44($v0) */
	.word	0x307303FF  /* 00167124 andi $s3,$v1,0x3ff */
	.word	0x127E000A  /* 00167128 beq $s3,$s8,.L00167154 */
	.word	0x00131040  /* 0016712C sll $v0,$s3,0x1 */
	.word	0x0040882D  /* 00167130 move $s1,$v0 */
	.word	0x02331021  /* 00167134 addu $v0,$s1,$s3 */
	.word	0x00021100  /* 00167138 sll $v0,$v0,0x4 */
	.word	0x00441021  /* 0016713C addu $v0,$v0,$a0 */
	.word	0x8C43002C  /* 00167140 lw $v1,44($v0) */
	.word	0x00031F82  /* 00167144 srl $v1,$v1,0x1e */
	.word	0x30630001  /* 00167148 andi $v1,$v1,0x1 */
	.word	0x5060FFE6  /* 0016714C beqzl $v1,.L001670E8 */
	.word	0x8E85015C  /* 00167150 lw $a1,348($s4) */
	.word	0x27B60030  /* 00167154 addiu $s6,$sp,48 */
	.word	0x27A500B0  /* 00167158 addiu $a1,$sp,176 */
	.word	0x27A60070  /* 0016715C addiu $a2,$sp,112 */
	.word	0x4600AB06  /* 00167160 mov.s $f12,$f21 */
	.word	0x0C000000  /* 00167164 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x02C0202D  /* 00167168 move $a0,$s6 */
	.word	0x4600AB06  /* 0016716C mov.s $f12,$f21 */
	.word	0x03A0202D  /* 00167170 move $a0,$sp */
	.word	0x27A50080  /* 00167174 addiu $a1,$sp,128 */
	.word	0x0C000000  /* 00167178 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x27A60040  /* 0016717C addiu $a2,$sp,64 */
	.word	0x0C000000  /* 00167180 jal func_00162c20 */
	.reloc	.-4, R_MIPS_26, func_00162c20
	.word	0x03A0202D  /* 00167184 move $a0,$sp */
	.word	0x4600AB06  /* 00167188 mov.s $f12,$f21 */
	.word	0x27A20010  /* 0016718C addiu $v0,$sp,16 */
	.word	0x27A50090  /* 00167190 addiu $a1,$sp,144 */
	.word	0x27A60050  /* 00167194 addiu $a2,$sp,80 */
	.word	0x0C000000  /* 00167198 jal func_00267e60 */
	.reloc	.-4, R_MIPS_26, func_00267e60
	.word	0x0040202D  /* 0016719C move $a0,$v0 */
	.word	0x27A30010  /* 001671A0 addiu $v1,$sp,16 */
	.word	0x0C000000  /* 001671A4 jal func_00162c20 */
	.reloc	.-4, R_MIPS_26, func_00162c20
	.word	0x0060202D  /* 001671A8 move $a0,$v1 */
	.word	0x27A20020  /* 001671AC addiu $v0,$sp,32 */
	.word	0x27A30010  /* 001671B0 addiu $v1,$sp,16 */
	.word	0x03A0282D  /* 001671B4 move $a1,$sp */
	.word	0x0060302D  /* 001671B8 move $a2,$v1 */
	.word	0x0C000000  /* 001671BC jal func_00267370 */
	.reloc	.-4, R_MIPS_26, func_00267370
	.word	0x0040202D  /* 001671C0 move $a0,$v0 */
	.word	0x27A20020  /* 001671C4 addiu $v0,$sp,32 */
	.word	0x0C000000  /* 001671C8 jal func_00162c20 */
	.reloc	.-4, R_MIPS_26, func_00162c20
	.word	0x0040202D  /* 001671CC move $a0,$v0 */
	.word	0x27A30010  /* 001671D0 addiu $v1,$sp,16 */
	.word	0x27A20020  /* 001671D4 addiu $v0,$sp,32 */
	.word	0x0060202D  /* 001671D8 move $a0,$v1 */
	.word	0x0040282D  /* 001671DC move $a1,$v0 */
	.word	0x0C000000  /* 001671E0 jal func_00267370 */
	.reloc	.-4, R_MIPS_26, func_00267370
	.word	0x03A0302D  /* 001671E4 move $a2,$sp */
	.word	0x27A30010  /* 001671E8 addiu $v1,$sp,16 */
	.word	0x0C000000  /* 001671EC jal func_00162c20 */
	.reloc	.-4, R_MIPS_26, func_00162c20
	.word	0x0060202D  /* 001671F0 move $a0,$v1 */
	.word	0x240203FF  /* 001671F4 li $v0,1023 */
	.word	0x16620025  /* 001671F8 bne $s3,$v0,.L00167290 */
	.word	0x8E840158  /* 001671FC lw $a0,344($s4) */
	.word	0x03A0302D  /* 00167200 move $a2,$sp */
	.word	0x3C050000  /* 00167204 lui $a1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x24A50000  /* 00167208 addiu $a1,$a1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x0C000000  /* 0016720C jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00952021  /* 00167210 addu $a0,$a0,$s5 */
	.word	0x8E920154  /* 00167214 lw $s2,340($s4) */
	.word	0x8E900150  /* 00167218 lw $s0,336($s4) */
	.word	0x8E910158  /* 0016721C lw $s1,344($s4) */
	.word	0x02B29021  /* 00167220 addu $s2,$s5,$s2 */
	.word	0x02B08021  /* 00167224 addu $s0,$s5,$s0 */
	.word	0x0240202D  /* 00167228 move $a0,$s2 */
	.word	0x26100010  /* 0016722C addiu $s0,$s0,16 */
	.word	0x02B18821  /* 00167230 addu $s1,$s5,$s1 */
	.word	0xC60C0000  /* 00167234 lwc1 $f12,0($s0) */
	.word	0x0C000000  /* 00167238 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0220282D  /* 0016723C move $a1,$s1 */
	.word	0x26440010  /* 00167240 addiu $a0,$s2,16 */
	.word	0xC60C0004  /* 00167244 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 00167248 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26250010  /* 0016724C addiu $a1,$s1,16 */
	.word	0x26440020  /* 00167250 addiu $a0,$s2,32 */
	.word	0xC60C0008  /* 00167254 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 00167258 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26250020  /* 0016725C addiu $a1,$s1,32 */
	.word	0x26440030  /* 00167260 addiu $a0,$s2,48 */
	.word	0x0C000000  /* 00167264 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x26250030  /* 00167268 addiu $a1,$s1,48 */
	.word	0x8E840154  /* 0016726C lw $a0,340($s4) */
	.word	0x02C0302D  /* 00167270 move $a2,$s6 */
	.word	0x3C050000  /* 00167274 lui $a1,%hi(D_00573F10) */
	.reloc	.-4, R_MIPS_HI16, D_00573F10
	.word	0x24A50000  /* 00167278 addiu $a1,$a1,%lo(D_00573F10) */
	.reloc	.-4, R_MIPS_LO16, D_00573F10
	.word	0x00952021  /* 0016727C addu $a0,$a0,$s5 */
	.word	0x0C000000  /* 00167280 jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24840030  /* 00167284 addiu $a0,$a0,48 */
	.word	0x10000023  /* 00167288 b .L00167318 */
	.word	0x8FA20180  /* 0016728C lw $v0,384($sp) */
	.word	0x00139980  /* 00167290 sll $s3,$s3,0x6 */
	.word	0x03A0302D  /* 00167294 move $a2,$sp */
	.word	0x00932821  /* 00167298 addu $a1,$a0,$s3 */
	.word	0x0C000000  /* 0016729C jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x00952021  /* 001672A0 addu $a0,$a0,$s5 */
	.word	0x8E920154  /* 001672A4 lw $s2,340($s4) */
	.word	0x8E900150  /* 001672A8 lw $s0,336($s4) */
	.word	0x8E910158  /* 001672AC lw $s1,344($s4) */
	.word	0x02B29021  /* 001672B0 addu $s2,$s5,$s2 */
	.word	0x02B08021  /* 001672B4 addu $s0,$s5,$s0 */
	.word	0x0240202D  /* 001672B8 move $a0,$s2 */
	.word	0x26100010  /* 001672BC addiu $s0,$s0,16 */
	.word	0x02B18821  /* 001672C0 addu $s1,$s5,$s1 */
	.word	0xC60C0000  /* 001672C4 lwc1 $f12,0($s0) */
	.word	0x0C000000  /* 001672C8 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x0220282D  /* 001672CC move $a1,$s1 */
	.word	0x26440010  /* 001672D0 addiu $a0,$s2,16 */
	.word	0xC60C0004  /* 001672D4 lwc1 $f12,4($s0) */
	.word	0x0C000000  /* 001672D8 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26250010  /* 001672DC addiu $a1,$s1,16 */
	.word	0x26440020  /* 001672E0 addiu $a0,$s2,32 */
	.word	0xC60C0008  /* 001672E4 lwc1 $f12,8($s0) */
	.word	0x0C000000  /* 001672E8 jal func_00267e90 */
	.reloc	.-4, R_MIPS_26, func_00267e90
	.word	0x26250020  /* 001672EC addiu $a1,$s1,32 */
	.word	0x26440030  /* 001672F0 addiu $a0,$s2,48 */
	.word	0x0C000000  /* 001672F4 jal func_002675a8 */
	.reloc	.-4, R_MIPS_26, func_002675a8
	.word	0x26250030  /* 001672F8 addiu $a1,$s1,48 */
	.word	0x8E850154  /* 001672FC lw $a1,340($s4) */
	.word	0x02C0302D  /* 00167300 move $a2,$s6 */
	.word	0x00B52021  /* 00167304 addu $a0,$a1,$s5 */
	.word	0x00B32821  /* 00167308 addu $a1,$a1,$s3 */
	.word	0x0C000000  /* 0016730C jal func_00162848 */
	.reloc	.-4, R_MIPS_26, func_00162848
	.word	0x24840030  /* 00167310 addiu $a0,$a0,48 */
	.word	0x8FA20180  /* 00167314 lw $v0,384($sp) */
	.word	0x26B50040  /* 00167318 addiu $s5,$s5,64 */
	.word	0x8E840000  /* 0016731C lw $a0,0($s4) */
	.word	0x24420001  /* 00167320 addiu $v0,$v0,1 */
	.word	0xAFA20180  /* 00167324 sw $v0,384($sp) */
	.word	0x8C830000  /* 00167328 lw $v1,0($a0) */
	.word	0x84620000  /* 0016732C lh $v0,0($v1) */
	.word	0x8FA30180  /* 00167330 lw $v1,384($sp) */
	.word	0x0062102A  /* 00167334 slt $v0,$v1,$v0 */
	.word	0x1440FD37  /* 00167338 bnez $v0,.L00166818 */
	.word	0x26F70030  /* 0016733C addiu $s7,$s7,48 */
	.word	0x8E85016C  /* 00167340 lw $a1,364($s4) */
	.word	0xAFA00180  /* 00167344 sw $zero,384($sp) */
	.word	0x00A0302D  /* 00167348 move $a2,$a1 */
	.word	0x84C20000  /* 0016734C lh $v0,0($a2) */
	.word	0x0442002A  /* 00167350 bltzl $v0,.L001673FC */
	.word	0x3C040000  /* 00167354 lui $a0,0x57 */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0x0000482D  /* 00167358 move $t1,$zero */
	.word	0x8FA20180  /* 0016735C lw $v0,384($sp) */
	.word	0x3C07BFFF  /* 00167360 lui $a3,0xbfff */
	.word	0x34E7FFFF  /* 00167364 ori $a3,$a3,0xffff */
	.word	0x01221821  /* 00167368 addu $v1,$t1,$v0 */
	.word	0x24420001  /* 0016736C addiu $v0,$v0,1 */
	.word	0xAFA20180  /* 00167370 sw $v0,384($sp) */
	.word	0x00031900  /* 00167374 sll $v1,$v1,0x4 */
	.word	0x00661821  /* 00167378 addu $v1,$v1,$a2 */
	.word	0x8C820000  /* 0016737C lw $v0,0($a0) */
	.word	0x84640000  /* 00167380 lh $a0,0($v1) */
	.word	0x8C480004  /* 00167384 lw $t0,4($v0) */
	.word	0x8FA20180  /* 00167388 lw $v0,384($sp) */
	.word	0x8C660004  /* 0016738C lw $a2,4($v1) */
	.word	0x00022840  /* 00167390 sll $a1,$v0,0x1 */
	.word	0x00041040  /* 00167394 sll $v0,$a0,0x1 */
	.word	0x00441021  /* 00167398 addu $v0,$v0,$a0 */
	.word	0x8FA30180  /* 0016739C lw $v1,384($sp) */
	.word	0x00021100  /* 001673A0 sll $v0,$v0,0x4 */
	.word	0x00A0482D  /* 001673A4 move $t1,$a1 */
	.word	0x00481021  /* 001673A8 addu $v0,$v0,$t0 */
	.word	0x01232821  /* 001673AC addu $a1,$t1,$v1 */
	.word	0x8C44002C  /* 001673B0 lw $a0,44($v0) */
	.word	0x30C60001  /* 001673B4 andi $a2,$a2,0x1 */
	.word	0x00063780  /* 001673B8 sll $a2,$a2,0x1e */
	.word	0x00052900  /* 001673BC sll $a1,$a1,0x4 */
	.word	0x308403FF  /* 001673C0 andi $a0,$a0,0x3ff */
	.word	0x00041840  /* 001673C4 sll $v1,$a0,0x1 */
	.word	0x00641821  /* 001673C8 addu $v1,$v1,$a0 */
	.word	0x00031900  /* 001673CC sll $v1,$v1,0x4 */
	.word	0x00681821  /* 001673D0 addu $v1,$v1,$t0 */
	.word	0x8C62002C  /* 001673D4 lw $v0,44($v1) */
	.word	0x00471024  /* 001673D8 and $v0,$v0,$a3 */
	.word	0x00461025  /* 001673DC or $v0,$v0,$a2 */
	.word	0xAC62002C  /* 001673E0 sw $v0,44($v1) */
	.word	0x8E86016C  /* 001673E4 lw $a2,364($s4) */
	.word	0x00A62821  /* 001673E8 addu $a1,$a1,$a2 */
	.word	0x84A20000  /* 001673EC lh $v0,0($a1) */
	.word	0x0443FFDA  /* 001673F0 bgezl $v0,.L0016735C */
	.word	0x8E840000  /* 001673F4 lw $a0,0($s4) */
	.word	0x3C040000  /* 001673F8 lui $a0,0x57 */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0x3C013F80  /* 001673FC lui $at,0x3f80 */
	.word	0x44810800  /* 00167400 mtc1 $at,$f1 */
	.word	0x24820000  /* 00167404 addiu $v0,$a0,20256 */
	.reloc	.-4, R_MIPS_LO16, D_00574F20
	.word	0x3C013BA3  /* 00167408 lui $at,0x3ba3 */
	.word	0x3421D70A  /* 0016740C ori $at,$at,0xd70a */
	.word	0x44811000  /* 00167410 mtc1 $at,$f2 */
	.word	0xC4400000  /* 00167414 lwc1 $f0,0($v0) */
	.word	0x46010001  /* 00167418 sub.s $f0,$f0,$f1 */
	.word	0x46000005  /* 0016741C abs.s $f0,$f0 */
	.word	0x46001034  /* 00167420 c.lt.s $f2,$f0 */
	.word	0x4501000E  /* 00167424 bc1t .L00167460 */
	.word	0x27B00040  /* 00167428 addiu $s0,$sp,64 */
	.word	0xC4400004  /* 0016742C lwc1 $f0,4($v0) */
	.word	0x46010001  /* 00167430 sub.s $f0,$f0,$f1 */
	.word	0x46000005  /* 00167434 abs.s $f0,$f0 */
	.word	0x46001034  /* 00167438 c.lt.s $f2,$f0 */
	.word	0x45030009  /* 0016743C bc1tl .L00167464 */
	.word	0xAFA00180  /* 00167440 sw $zero,384($sp) */
	.word	0xC4400008  /* 00167444 lwc1 $f0,8($v0) */
	.word	0x46010001  /* 00167448 sub.s $f0,$f0,$f1 */
	.word	0x46000005  /* 0016744C abs.s $f0,$f0 */
	.word	0x46001034  /* 00167450 c.lt.s $f2,$f0 */
	.word	0x45020024  /* 00167454 bc1fl .L001674E8 */
	.word	0x8E840000  /* 00167458 lw $a0,0($s4) */
	.word	0x27B00040  /* 0016745C addiu $s0,$sp,64 */
	.word	0xAFA00180  /* 00167460 sw $zero,384($sp) */
	.word	0x0C000000  /* 00167464 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x0200202D  /* 00167468 move $a0,$s0 */
	.word	0x3C030000  /* 0016746C lui $v1,%hi(D_00574F20) */
	.reloc	.-4, R_MIPS_HI16, D_00574F20
	.word	0x24620000  /* 00167470 addiu $v0,$v1,%lo(D_00574F20) */
	.reloc	.-4, R_MIPS_LO16, D_00574F20
	.word	0xC4420008  /* 00167474 lwc1 $f2,8($v0) */
	.word	0xC4400000  /* 00167478 lwc1 $f0,0($v0) */
	.word	0xC4410004  /* 0016747C lwc1 $f1,4($v0) */
	.word	0xE7A00040  /* 00167480 swc1 $f0,64($sp) */
	.word	0xE7A10054  /* 00167484 swc1 $f1,84($sp) */
	.word	0xE7A20068  /* 00167488 swc1 $f2,104($sp) */
	.word	0x8E840000  /* 0016748C lw $a0,0($s4) */
	.word	0x8C820000  /* 00167490 lw $v0,0($a0) */
	.word	0x84430000  /* 00167494 lh $v1,0($v0) */
	.word	0x58600014  /* 00167498 blezl $v1,.L001674EC */
	.word	0x8C830000  /* 0016749C lw $v1,0($a0) */
	.word	0x8FA30180  /* 001674A0 lw $v1,384($sp) */
	.word	0x0200282D  /* 001674A4 move $a1,$s0 */
	.word	0x8E840154  /* 001674A8 lw $a0,340($s4) */
	.word	0x00031180  /* 001674AC sll $v0,$v1,0x6 */
	.word	0x24630001  /* 001674B0 addiu $v1,$v1,1 */
	.word	0x00822021  /* 001674B4 addu $a0,$a0,$v0 */
	.word	0xAFA30180  /* 001674B8 sw $v1,384($sp) */
	.word	0x0C000000  /* 001674BC jal func_00162c5c */
	.reloc	.-4, R_MIPS_26, func_00162c5c
	.word	0x0080302D  /* 001674C0 move $a2,$a0 */
	.word	0x8E840000  /* 001674C4 lw $a0,0($s4) */
	.word	0x8C830000  /* 001674C8 lw $v1,0($a0) */
	.word	0x84620000  /* 001674CC lh $v0,0($v1) */
	.word	0x8FA30180  /* 001674D0 lw $v1,384($sp) */
	.word	0x0062102A  /* 001674D4 slt $v0,$v1,$v0 */
	.word	0x1440FFF3  /* 001674D8 bnez $v0,.L001674A8 */
	.word	0x0200282D  /* 001674DC move $a1,$s0 */
	.word	0x10000002  /* 001674E0 b .L001674EC */
	.word	0x8C830000  /* 001674E4 lw $v1,0($a0) */
	.word	0x8C830000  /* 001674E8 lw $v1,0($a0) */
	.word	0xAFA00180  /* 001674EC sw $zero,384($sp) */
	.word	0x84620000  /* 001674F0 lh $v0,0($v1) */
	.word	0x18400024  /* 001674F4 blez $v0,.L00167588 */
	.word	0xDFB00190  /* 001674F8 ld $s0,400($sp) */
	.word	0x3C020000  /* 001674FC lui $v0,%hi(D_00574F10) */
	.reloc	.-4, R_MIPS_HI16, D_00574F10
	.word	0x24450000  /* 00167500 addiu $a1,$v0,%lo(D_00574F10) */
	.reloc	.-4, R_MIPS_LO16, D_00574F10
	.word	0x8FA20180  /* 00167504 lw $v0,384($sp) */
	.word	0x8E830154  /* 00167508 lw $v1,340($s4) */
	.word	0x00022180  /* 0016750C sll $a0,$v0,0x6 */
	.word	0x24420001  /* 00167510 addiu $v0,$v0,1 */
	.word	0xC4A10000  /* 00167514 lwc1 $f1,0($a1) */
	.word	0x00831821  /* 00167518 addu $v1,$a0,$v1 */
	.word	0xAFA20180  /* 0016751C sw $v0,384($sp) */
	.word	0x24630030  /* 00167520 addiu $v1,$v1,48 */
	.word	0xC4600000  /* 00167524 lwc1 $f0,0($v1) */
	.word	0x46010000  /* 00167528 add.s $f0,$f0,$f1 */
	.word	0xE4600000  /* 0016752C swc1 $f0,0($v1) */
	.word	0x8E820154  /* 00167530 lw $v0,340($s4) */
	.word	0xC4A10004  /* 00167534 lwc1 $f1,4($a1) */
	.word	0x00821021  /* 00167538 addu $v0,$a0,$v0 */
	.word	0x24420034  /* 0016753C addiu $v0,$v0,52 */
	.word	0xC4400000  /* 00167540 lwc1 $f0,0($v0) */
	.word	0x46010000  /* 00167544 add.s $f0,$f0,$f1 */
	.word	0xE4400000  /* 00167548 swc1 $f0,0($v0) */
	.word	0x8E830154  /* 0016754C lw $v1,340($s4) */
	.word	0xC4A10008  /* 00167550 lwc1 $f1,8($a1) */
	.word	0x00832021  /* 00167554 addu $a0,$a0,$v1 */
	.word	0x24840038  /* 00167558 addiu $a0,$a0,56 */
	.word	0xC4800000  /* 0016755C lwc1 $f0,0($a0) */
	.word	0x46010000  /* 00167560 add.s $f0,$f0,$f1 */
	.word	0xE4800000  /* 00167564 swc1 $f0,0($a0) */
	.word	0x8E830000  /* 00167568 lw $v1,0($s4) */
	.word	0x8C640000  /* 0016756C lw $a0,0($v1) */
	.word	0x8FA30180  /* 00167570 lw $v1,384($sp) */
	.word	0x84820000  /* 00167574 lh $v0,0($a0) */
	.word	0x0062102A  /* 00167578 slt $v0,$v1,$v0 */
	.word	0x1440FFE2  /* 0016757C bnez $v0,.L00167508 */
	.word	0x8FA20180  /* 00167580 lw $v0,384($sp) */
	.word	0xDFB00190  /* 00167584 ld $s0,400($sp) */
	.word	0xDFB10198  /* 00167588 ld $s1,408($sp) */
	.word	0xDFB201A0  /* 0016758C ld $s2,416($sp) */
	.word	0xDFB301A8  /* 00167590 ld $s3,424($sp) */
	.word	0xDFB401B0  /* 00167594 ld $s4,432($sp) */
	.word	0xDFB501B8  /* 00167598 ld $s5,440($sp) */
	.word	0xDFB601C0  /* 0016759C ld $s6,448($sp) */
	.word	0xDFB701C8  /* 001675A0 ld $s7,456($sp) */
	.word	0xDFBE01D0  /* 001675A4 ld $s8,464($sp) */
	.word	0xDFBF01D8  /* 001675A8 ld $ra,472($sp) */
	.word	0xC7B601F0  /* 001675AC lwc1 $f22,496($sp) */
	.word	0xC7B501E8  /* 001675B0 lwc1 $f21,488($sp) */
	.word	0xC7B401E0  /* 001675B4 lwc1 $f20,480($sp) */
	.word	0x03E00008  /* 001675B8 jr $ra */
	.word	0x27BD0200  /* 001675BC addiu $sp,$sp,512 */
	.end	func_00166570
