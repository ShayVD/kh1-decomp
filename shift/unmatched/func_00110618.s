/* func_00110618: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_00110618,"ax",@progbits
	.globl	func_00110618
	.ent	func_00110618
func_00110618:  /* 0x00110618 */
	.word	0x460090C7  /* 00110618 neg.s $f3,$f18 */
	.word	0x27BDFF00  /* 0011061C addiu $sp,$sp,-256 */
	.word	0x46119041  /* 00110620 sub.s $f1,$f18,$f17 */
	.word	0xE7B500A0  /* 00110624 swc1 $f21,160($sp) */
	.word	0x46009D46  /* 00110628 mov.s $f21,$f19 */
	.word	0xE7B700B0  /* 0011062C swc1 $f23,176($sp) */
	.word	0xC7B70108  /* 00110630 lwc1 $f23,264($sp) */
	.word	0x461518C2  /* 00110634 mul.s $f3,$f3,$f21 */
	.word	0xE7B600A8  /* 00110638 swc1 $f22,168($sp) */
	.word	0xE7A10058  /* 0011063C swc1 $f1,88($sp) */
	.word	0x4615BD82  /* 00110640 mul.s $f22,$f23,$f21 */
	.word	0x3C0143A0  /* 00110644 lui $at,0x43a0 */
	.word	0x44810000  /* 00110648 mtc1 $at,$f0 */
	.word	0x46178882  /* 0011064C mul.s $f2,$f17,$f23 */
	.word	0xC7A40058  /* 00110650 lwc1 $f4,88($sp) */
	.word	0xE7A30054  /* 00110654 swc1 $f3,84($sp) */
	.word	0x4600A802  /* 00110658 mul.s $f0,$f21,$f0 */
	.word	0x4604B0C2  /* 0011065C mul.s $f3,$f22,$f4 */
	.word	0x3C014365  /* 00110660 lui $at,0x4365 */
	.word	0x44810800  /* 00110664 mtc1 $at,$f1 */
	.word	0xC7A40054  /* 00110668 lwc1 $f4,84($sp) */
	.word	0xE7BB00D0  /* 0011066C swc1 $f27,208($sp) */
	.word	0x4615BEC1  /* 00110670 sub.s $f27,$f23,$f21 */
	.word	0xE7B40098  /* 00110674 swc1 $f20,152($sp) */
	.word	0x46006506  /* 00110678 mov.s $f20,$f12 */
	.word	0x46022080  /* 0011067C add.s $f2,$f4,$f2 */
	.word	0xE7BC00D8  /* 00110680 swc1 $f28,216($sp) */
	.word	0x4601A842  /* 00110684 mul.s $f1,$f21,$f1 */
	.word	0xFFB00060  /* 00110688 sd $s0,96($sp) */
	.word	0x00000000  /* 0011068C nop */
	.word	0x00000000  /* 00110690 nop */
	.word	0x46140703  /* 00110694 div.s $f28,$f0,$f20 */
	.word	0x00C0802D  /* 00110698 move $s0,$a2 */
	.word	0x4615A800  /* 0011069C add.s $f0,$f21,$f21 */
	.word	0xFFB20070  /* 001106A0 sd $s2,112($sp) */
	.word	0xE7BF00F0  /* 001106A4 swc1 $f31,240($sp) */
	.word	0x0080902D  /* 001106A8 move $s2,$a0 */
	.word	0xE7BE00E8  /* 001106AC swc1 $f30,232($sp) */
	.word	0x0200202D  /* 001106B0 move $a0,$s0 */
	.word	0xFFB10068  /* 001106B4 sd $s1,104($sp) */
	.word	0x00E0882D  /* 001106B8 move $s1,$a3 */
	.word	0xFFB30078  /* 001106BC sd $s3,120($sp) */
	.word	0x00A0982D  /* 001106C0 move $s3,$a1 */
	.word	0x00000000  /* 001106C4 nop */
	.word	0x00000000  /* 001106C8 nop */
	.word	0x461B1783  /* 001106CC div.s $f30,$f2,$f27 */
	.word	0xFFB40080  /* 001106D0 sd $s4,128($sp) */
	.word	0xFFB50088  /* 001106D4 sd $s5,136($sp) */
	.word	0x0120A82D  /* 001106D8 move $s5,$t1 */
	.word	0x0100A02D  /* 001106DC move $s4,$t0 */
	.word	0xFFBF0090  /* 001106E0 sd $ra,144($sp) */
	.word	0xE7BD00E0  /* 001106E4 swc1 $f29,224($sp) */
	.word	0x4615BDC0  /* 001106E8 add.s $f23,$f23,$f21 */
	.word	0xE7BA00C8  /* 001106EC swc1 $f26,200($sp) */
	.word	0x461CE680  /* 001106F0 add.s $f26,$f28,$f28 */
	.word	0xE7B900C0  /* 001106F4 swc1 $f25,192($sp) */
	.word	0x46006E46  /* 001106F8 mov.s $f25,$f13 */
	.word	0x00000000  /* 001106FC nop */
	.word	0x00000000  /* 00110700 nop */
	.word	0x461B1FC3  /* 00110704 div.s $f31,$f3,$f27 */
	.word	0xE7B800B8  /* 00110708 swc1 $f24,184($sp) */
	.word	0xE7B20050  /* 0011070C swc1 $f18,80($sp) */
	.word	0xC7B80100  /* 00110710 lwc1 $f24,256($sp) */
	.word	0xE7A0005C  /* 00110714 swc1 $f0,92($sp) */
	.word	0xE7B1004C  /* 00110718 swc1 $f17,76($sp) */
	.word	0x4615C701  /* 0011071C sub.s $f28,$f24,$f21 */
	.word	0xE7AE0040  /* 00110720 swc1 $f14,64($sp) */
	.word	0xE7AF0044  /* 00110724 swc1 $f15,68($sp) */
	.word	0x00000000  /* 00110728 nop */
	.word	0x00000000  /* 0011072C nop */
	.word	0x46140F43  /* 00110730 div.s $f29,$f1,$f20 */
	.word	0x0C000000  /* 00110734 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0xE7B00048  /* 00110738 swc1 $f16,72($sp) */
	.word	0x3C013F80  /* 0011073C lui $at,0x3f80 */
	.word	0x44810800  /* 00110740 mtc1 $at,$f1 */
	.word	0x03A0202D  /* 00110744 move $a0,$sp */
	.word	0xE6140000  /* 00110748 swc1 $f20,0($s0) */
	.word	0xE6010038  /* 0011074C swc1 $f1,56($s0) */
	.word	0xE601002C  /* 00110750 swc1 $f1,44($s0) */
	.word	0xE6140014  /* 00110754 swc1 $f20,20($s0) */
	.word	0x00000000  /* 00110758 nop */
	.word	0x00000000  /* 0011075C nop */
	.word	0x461BBDC3  /* 00110760 div.s $f23,$f23,$f27 */
	.word	0xAE000028  /* 00110764 sw $zero,40($s0) */
	.word	0xAE00003C  /* 00110768 sw $zero,60($s0) */
	.word	0x0C000000  /* 0011076C jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x461DEF40  /* 00110770 add.s $f29,$f29,$f29 */
	.word	0x0200202D  /* 00110774 move $a0,$s0 */
	.word	0xC7A20040  /* 00110778 lwc1 $f2,64($sp) */
	.word	0x03A0282D  /* 0011077C move $a1,$sp */
	.word	0xC7A30044  /* 00110780 lwc1 $f3,68($sp) */
	.word	0x0080302D  /* 00110784 move $a2,$a0 */
	.word	0xC7A40048  /* 00110788 lwc1 $f4,72($sp) */
	.word	0xE7BF0028  /* 0011078C swc1 $f31,40($sp) */
	.word	0xE7BE0038  /* 00110790 swc1 $f30,56($sp) */
	.word	0xE7B90000  /* 00110794 swc1 $f25,0($sp) */
	.word	0xE7A20014  /* 00110798 swc1 $f2,20($sp) */
	.word	0xE7A30030  /* 0011079C swc1 $f3,48($sp) */
	.word	0x0C000000  /* 001107A0 jal sceVu0MulMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0MulMatrix
	.word	0xE7A40034  /* 001107A4 swc1 $f4,52($sp) */
	.word	0x0C000000  /* 001107A8 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x0220202D  /* 001107AC move $a0,$s1 */
	.word	0xAE20003C  /* 001107B0 sw $zero,60($s1) */
	.word	0x3C013F80  /* 001107B4 lui $at,0x3f80 */
	.word	0x44810000  /* 001107B8 mtc1 $at,$f0 */
	.word	0x0240202D  /* 001107BC move $a0,$s2 */
	.word	0x3C01C000  /* 001107C0 lui $at,0xc000 */
	.word	0x44810800  /* 001107C4 mtc1 $at,$f1 */
	.word	0xE620002C  /* 001107C8 swc1 $f0,44($s1) */
	.word	0x4601B102  /* 001107CC mul.s $f4,$f22,$f1 */
	.word	0xC7A2004C  /* 001107D0 lwc1 $f2,76($sp) */
	.word	0x4615C582  /* 001107D4 mul.s $f22,$f24,$f21 */
	.word	0xC7A3005C  /* 001107D8 lwc1 $f3,92($sp) */
	.word	0xC7A10058  /* 001107DC lwc1 $f1,88($sp) */
	.word	0x46181002  /* 001107E0 mul.s $f0,$f2,$f24 */
	.word	0x00000000  /* 001107E4 nop */
	.word	0x00000000  /* 001107E8 nop */
	.word	0x461A1E83  /* 001107EC div.s $f26,$f3,$f26 */
	.word	0x4601B0C2  /* 001107F0 mul.s $f3,$f22,$f1 */
	.word	0xC7A10054  /* 001107F4 lwc1 $f1,84($sp) */
	.word	0x4615C600  /* 001107F8 add.s $f24,$f24,$f21 */
	.word	0x46000880  /* 001107FC add.s $f2,$f1,$f0 */
	.word	0x00000000  /* 00110800 nop */
	.word	0x00000000  /* 00110804 nop */
	.word	0x461B2003  /* 00110808 div.s $f0,$f4,$f27 */
	.word	0xC7A4005C  /* 0011080C lwc1 $f4,92($sp) */
	.word	0xE6370028  /* 00110810 swc1 $f23,40($s1) */
	.word	0xE63A0000  /* 00110814 swc1 $f26,0($s1) */
	.word	0x00000000  /* 00110818 nop */
	.word	0x00000000  /* 0011081C nop */
	.word	0x461D2743  /* 00110820 div.s $f29,$f4,$f29 */
	.word	0xE6200038  /* 00110824 swc1 $f0,56($s1) */
	.word	0x00000000  /* 00110828 nop */
	.word	0x00000000  /* 0011082C nop */
	.word	0x461C1783  /* 00110830 div.s $f30,$f2,$f28 */
	.word	0x00000000  /* 00110834 nop */
	.word	0x00000000  /* 00110838 nop */
	.word	0x461C1FC3  /* 0011083C div.s $f31,$f3,$f28 */
	.word	0x0C000000  /* 00110840 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0xE63D0014  /* 00110844 swc1 $f29,20($s1) */
	.word	0x3C013F80  /* 00110848 lui $at,0x3f80 */
	.word	0x44810000  /* 0011084C mtc1 $at,$f0 */
	.word	0x03A0202D  /* 00110850 move $a0,$sp */
	.word	0xE6540000  /* 00110854 swc1 $f20,0($s2) */
	.word	0xE6400038  /* 00110858 swc1 $f0,56($s2) */
	.word	0xE640002C  /* 0011085C swc1 $f0,44($s2) */
	.word	0xE6540014  /* 00110860 swc1 $f20,20($s2) */
	.word	0xAE400028  /* 00110864 sw $zero,40($s2) */
	.word	0x00000000  /* 00110868 nop */
	.word	0x00000000  /* 0011086C nop */
	.word	0x461CC603  /* 00110870 div.s $f24,$f24,$f28 */
	.word	0x0C000000  /* 00110874 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0xAE40003C  /* 00110878 sw $zero,60($s2) */
	.word	0x0240202D  /* 0011087C move $a0,$s2 */
	.word	0xC7A10040  /* 00110880 lwc1 $f1,64($sp) */
	.word	0x0080302D  /* 00110884 move $a2,$a0 */
	.word	0xC7A20044  /* 00110888 lwc1 $f2,68($sp) */
	.word	0x03A0282D  /* 0011088C move $a1,$sp */
	.word	0xC7A30048  /* 00110890 lwc1 $f3,72($sp) */
	.word	0xE7BF0028  /* 00110894 swc1 $f31,40($sp) */
	.word	0xE7BE0038  /* 00110898 swc1 $f30,56($sp) */
	.word	0xE7B90000  /* 0011089C swc1 $f25,0($sp) */
	.word	0x4619A642  /* 001108A0 mul.s $f25,$f20,$f25 */
	.word	0xE7A10014  /* 001108A4 swc1 $f1,20($sp) */
	.word	0xE7A20030  /* 001108A8 swc1 $f2,48($sp) */
	.word	0x0C000000  /* 001108AC jal sceVu0MulMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0MulMatrix
	.word	0xE7A30034  /* 001108B0 swc1 $f3,52($sp) */
	.word	0x0C000000  /* 001108B4 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0x0260202D  /* 001108B8 move $a0,$s3 */
	.word	0xE67A0000  /* 001108BC swc1 $f26,0($s3) */
	.word	0x3C01C000  /* 001108C0 lui $at,0xc000 */
	.word	0x44812000  /* 001108C4 mtc1 $at,$f4 */
	.word	0x0280202D  /* 001108C8 move $a0,$s4 */
	.word	0x3C0144FF  /* 001108CC lui $at,0x44ff */
	.word	0x3421A000  /* 001108D0 ori $at,$at,0xa000 */
	.word	0x44810000  /* 001108D4 mtc1 $at,$f0 */
	.word	0x4604B582  /* 001108D8 mul.s $f22,$f22,$f4 */
	.word	0x3C0143B4  /* 001108DC lui $at,0x43b4 */
	.word	0x34214000  /* 001108E0 ori $at,$at,0x4000 */
	.word	0x44810800  /* 001108E4 mtc1 $at,$f1 */
	.word	0x4600A802  /* 001108E8 mul.s $f0,$f21,$f0 */
	.word	0xE67D0014  /* 001108EC swc1 $f29,20($s3) */
	.word	0x4601A842  /* 001108F0 mul.s $f1,$f21,$f1 */
	.word	0x3C013F80  /* 001108F4 lui $at,0x3f80 */
	.word	0x44811000  /* 001108F8 mtc1 $at,$f2 */
	.word	0xE6780028  /* 001108FC swc1 $f24,40($s3) */
	.word	0x00000000  /* 00110900 nop */
	.word	0x00000000  /* 00110904 nop */
	.word	0x461CB583  /* 00110908 div.s $f22,$f22,$f28 */
	.word	0xE662002C  /* 0011090C swc1 $f2,44($s3) */
	.word	0xAE60003C  /* 00110910 sw $zero,60($s3) */
	.word	0x00000000  /* 00110914 nop */
	.word	0x00000000  /* 00110918 nop */
	.word	0x46140703  /* 0011091C div.s $f28,$f0,$f20 */
	.word	0x00000000  /* 00110920 nop */
	.word	0x00000000  /* 00110924 nop */
	.word	0x46140F43  /* 00110928 div.s $f29,$f1,$f20 */
	.word	0x0C000000  /* 0011092C jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0xE6760038  /* 00110930 swc1 $f22,56($s3) */
	.word	0x3C013F80  /* 00110934 lui $at,0x3f80 */
	.word	0x44811800  /* 00110938 mtc1 $at,$f3 */
	.word	0x02A0202D  /* 0011093C move $a0,$s5 */
	.word	0xE6980028  /* 00110940 swc1 $f24,40($s4) */
	.word	0x461CE040  /* 00110944 add.s $f1,$f28,$f28 */
	.word	0xE6960038  /* 00110948 swc1 $f22,56($s4) */
	.word	0x461CCE42  /* 0011094C mul.s $f25,$f25,$f28 */
	.word	0xE683002C  /* 00110950 swc1 $f3,44($s4) */
	.word	0xAE80003C  /* 00110954 sw $zero,60($s4) */
	.word	0xC7A4005C  /* 00110958 lwc1 $f4,92($sp) */
	.word	0x00000000  /* 0011095C nop */
	.word	0x00000000  /* 00110960 nop */
	.word	0x4615CE43  /* 00110964 div.s $f25,$f25,$f21 */
	.word	0x461DE800  /* 00110968 add.s $f0,$f29,$f29 */
	.word	0x00000000  /* 0011096C nop */
	.word	0x00000000  /* 00110970 nop */
	.word	0x46012043  /* 00110974 div.s $f1,$f4,$f1 */
	.word	0x00000000  /* 00110978 nop */
	.word	0x00000000  /* 0011097C nop */
	.word	0x46002683  /* 00110980 div.s $f26,$f4,$f0 */
	.word	0xE6810000  /* 00110984 swc1 $f1,0($s4) */
	.word	0x0C000000  /* 00110988 jal sceVu0UnitMatrix */
	.reloc	.-4, R_MIPS_26, sceVu0UnitMatrix
	.word	0xE69A0014  /* 0011098C swc1 $f26,20($s4) */
	.word	0x3C013F00  /* 00110990 lui $at,0x3f00 */
	.word	0x44810800  /* 00110994 mtc1 $at,$f1 */
	.word	0xC7A00040  /* 00110998 lwc1 $f0,64($sp) */
	.word	0xC7A20050  /* 0011099C lwc1 $f2,80($sp) */
	.word	0x4600A502  /* 001109A0 mul.s $f20,$f20,$f0 */
	.word	0xC7A3004C  /* 001109A4 lwc1 $f3,76($sp) */
	.word	0x3C013F80  /* 001109A8 lui $at,0x3f80 */
	.word	0x44812000  /* 001109AC mtc1 $at,$f4 */
	.word	0x46031000  /* 001109B0 add.s $f0,$f2,$f3 */
	.word	0xE6B90000  /* 001109B4 swc1 $f25,0($s5) */
	.word	0xE6A4003C  /* 001109B8 swc1 $f4,60($s5) */
	.word	0x46021C81  /* 001109BC sub.s $f18,$f3,$f2 */
	.word	0x461DA502  /* 001109C0 mul.s $f20,$f20,$f29 */
	.word	0xC7BD00E0  /* 001109C4 lwc1 $f29,224($sp) */
	.word	0xC7A20044  /* 001109C8 lwc1 $f2,68($sp) */
	.word	0x46010002  /* 001109CC mul.s $f0,$f0,$f1 */
	.word	0xDFB00060  /* 001109D0 ld $s0,96($sp) */
	.word	0xE6A20030  /* 001109D4 swc1 $f2,48($s5) */
	.word	0x46019482  /* 001109D8 mul.s $f18,$f18,$f1 */
	.word	0x00000000  /* 001109DC nop */
	.word	0x00000000  /* 001109E0 nop */
	.word	0x4615A503  /* 001109E4 div.s $f20,$f20,$f21 */
	.word	0xC7B500A0  /* 001109E8 lwc1 $f21,160($sp) */
	.word	0xC7A30048  /* 001109EC lwc1 $f3,72($sp) */
	.word	0xDFB10068  /* 001109F0 ld $s1,104($sp) */
	.word	0xE6A30034  /* 001109F4 swc1 $f3,52($s5) */
	.word	0xE6A00038  /* 001109F8 swc1 $f0,56($s5) */
	.word	0xE6B20028  /* 001109FC swc1 $f18,40($s5) */
	.word	0xDFB20070  /* 00110A00 ld $s2,112($sp) */
	.word	0xDFB30078  /* 00110A04 ld $s3,120($sp) */
	.word	0xE6B40014  /* 00110A08 swc1 $f20,20($s5) */
	.word	0xDFB40080  /* 00110A0C ld $s4,128($sp) */
	.word	0xDFB50088  /* 00110A10 ld $s5,136($sp) */
	.word	0xDFBF0090  /* 00110A14 ld $ra,144($sp) */
	.word	0xC7BF00F0  /* 00110A18 lwc1 $f31,240($sp) */
	.word	0xC7BE00E8  /* 00110A1C lwc1 $f30,232($sp) */
	.word	0xC7BC00D8  /* 00110A20 lwc1 $f28,216($sp) */
	.word	0xC7BB00D0  /* 00110A24 lwc1 $f27,208($sp) */
	.word	0xC7BA00C8  /* 00110A28 lwc1 $f26,200($sp) */
	.word	0xC7B900C0  /* 00110A2C lwc1 $f25,192($sp) */
	.word	0xC7B800B8  /* 00110A30 lwc1 $f24,184($sp) */
	.word	0xC7B700B0  /* 00110A34 lwc1 $f23,176($sp) */
	.word	0xC7B600A8  /* 00110A38 lwc1 $f22,168($sp) */
	.word	0xC7B40098  /* 00110A3C lwc1 $f20,152($sp) */
	.word	0x03E00008  /* 00110A40 jr $ra */
	.word	0x27BD0100  /* 00110A44 addiu $sp,$sp,256 */
	.end	func_00110618
