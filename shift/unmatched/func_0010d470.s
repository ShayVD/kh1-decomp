/* func_0010d470: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_0010d470,"ax",@progbits
	.globl	func_0010d470
	.ent	func_0010d470
func_0010d470:  /* 0x0010D470 */
	.word	0x27BDFF30  /* 0010D470 addiu $sp,$sp,-208 */
	.word	0x3C020000  /* 0010D474 lui $v0,%hi(D_004D5AF0) */
	.reloc	.-4, R_MIPS_HI16, D_004D5AF0
	.word	0xFFB10068  /* 0010D478 sd $s1,104($sp) */
	.word	0x00A0882D  /* 0010D47C move $s1,$a1 */
	.word	0xFFB20070  /* 0010D480 sd $s2,112($sp) */
	.word	0x0080902D  /* 0010D484 move $s2,$a0 */
	.word	0xFFB40080  /* 0010D488 sd $s4,128($sp) */
	.word	0x0000A02D  /* 0010D48C move $s4,$zero */
	.word	0xFFB50088  /* 0010D490 sd $s5,136($sp) */
	.word	0x0000A82D  /* 0010D494 move $s5,$zero */
	.word	0xFFB70098  /* 0010D498 sd $s7,152($sp) */
	.word	0x0000B82D  /* 0010D49C move $s7,$zero */
	.word	0xAC400000  /* 0010D4A0 sw $zero,%lo(D_004D5AF0)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5AF0
	.word	0x24020080  /* 0010D4A4 li $v0,128 */
	.word	0xFFB00060  /* 0010D4A8 sd $s0,96($sp) */
	.word	0xFFB30078  /* 0010D4AC sd $s3,120($sp) */
	.word	0xFFB60090  /* 0010D4B0 sd $s6,144($sp) */
	.word	0xFFBE00A0  /* 0010D4B4 sd $s8,160($sp) */
	.word	0xFFBF00A8  /* 0010D4B8 sd $ra,168($sp) */
	.word	0xE7B600C0  /* 0010D4BC swc1 $f22,192($sp) */
	.word	0xE7B500B8  /* 0010D4C0 swc1 $f21,184($sp) */
	.word	0xE7B400B0  /* 0010D4C4 swc1 $f20,176($sp) */
	.word	0x92430013  /* 0010D4C8 lbu $v1,19($s2) */
	.word	0xAFA00044  /* 0010D4CC sw $zero,68($sp) */
	.word	0x30640002  /* 0010D4D0 andi $a0,$v1,0x2 */
	.word	0x30630004  /* 0010D4D4 andi $v1,$v1,0x4 */
	.word	0x0003100B  /* 0010D4D8 movn $v0,$zero,$v1 */
	.word	0xAFA20050  /* 0010D4DC sw $v0,80($sp) */
	.word	0x96500008  /* 0010D4E0 lhu $s0,8($s2) */
	.word	0x9656000A  /* 0010D4E4 lhu $s6,10($s2) */
	.word	0x8E530004  /* 0010D4E8 lw $s3,4($s2) */
	.word	0x1080000A  /* 0010D4EC beqz $a0,.L0010D518 */
	.word	0x925E0010  /* 0010D4F0 lbu $s8,16($s2) */
	.word	0x24030014  /* 0010D4F4 li $v1,20 */
	.word	0x24020012  /* 0010D4F8 li $v0,18 */
	.word	0xA223000D  /* 0010D4FC sb $v1,13($s1) */
	.word	0x3C030000  /* 0010D500 lui $v1,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0x3C013F55  /* 0010D504 lui $at,0x3f55 */
	.word	0x3421554F  /* 0010D508 ori $at,$at,0x554f */
	.word	0x4481B000  /* 0010D50C mtc1 $at,$f22 */
	.word	0x10000008  /* 0010D510 b .L0010D534 */
	.word	0xAC620000  /* 0010D514 sw $v0,%lo(D_004D59E8)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0x24030018  /* 0010D518 li $v1,24 */
	.word	0x24020014  /* 0010D51C li $v0,20 */
	.word	0x3C040000  /* 0010D520 lui $a0,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0xA223000D  /* 0010D524 sb $v1,13($s1) */
	.word	0x3C013F80  /* 0010D528 lui $at,0x3f80 */
	.word	0x4481B000  /* 0010D52C mtc1 $at,$f22 */
	.word	0xAC820000  /* 0010D530 sw $v0,%lo(D_004D59E8)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0xC6400014  /* 0010D534 lwc1 $f0,20($s2) */
	.word	0x44800800  /* 0010D538 mtc1 $zero,$f1 */
	.word	0x46010032  /* 0010D53C c.eq.s $f0,$f1 */
	.word	0x45000005  /* 0010D540 bc1f .L0010D558 */
	.word	0x3C050000  /* 0010D544 lui $a1,0x4d */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x3C013586  /* 0010D548 lui $at,0x3586 */
	.word	0x342137BD  /* 0010D54C ori $at,$at,0x37bd */
	.word	0x44810000  /* 0010D550 mtc1 $at,$f0 */
	.word	0xE6400014  /* 0010D554 swc1 $f0,20($s2) */
	.word	0x24060001  /* 0010D558 li $a2,1 */
	.word	0xACA00000  /* 0010D55C sw $zero,23012($a1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x46000D46  /* 0010D560 mov.s $f21,$f1 */
	.word	0xAFA0004C  /* 0010D564 sw $zero,76($sp) */
	.word	0xAFA60048  /* 0010D568 sw $a2,72($sp) */
	.word	0xAFA00040  /* 0010D56C sw $zero,64($sp) */
	.word	0xC6540014  /* 0010D570 lwc1 $f20,20($s2) */
	.word	0x00000000  /* 0010D574 nop */
	.word	0x8FA20040  /* 0010D578 lw $v0,64($sp) */
	.word	0x02621021  /* 0010D57C addu $v0,$s3,$v0 */
	.word	0x90480000  /* 0010D580 lbu $t0,0($v0) */
	.word	0x2D030020  /* 0010D584 sltiu $v1,$t0,32 */
	.word	0x14600057  /* 0010D588 bnez $v1,.L0010D6E8 */
	.word	0x00081080  /* 0010D58C sll $v0,$t0,0x2 */
	.word	0x00172900  /* 0010D590 sll $a1,$s7,0x4 */
	.word	0x3402FFE0  /* 0010D594 li $v0,0xffe0 */
	.word	0x00481021  /* 0010D598 addu $v0,$v0,$t0 */
	.word	0x24A30010  /* 0010D59C addiu $v1,$a1,16 */
	.word	0x3054FFFF  /* 0010D5A0 andi $s4,$v0,0xffff */
	.word	0x02232021  /* 0010D5A4 addu $a0,$s1,$v1 */
	.word	0x3C030000  /* 0010D5A8 lui $v1,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0xA4940000  /* 0010D5AC sh $s4,0($a0) */
	.word	0x8C620000  /* 0010D5B0 lw $v0,%lo(D_004D59E4)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x14400022  /* 0010D5B4 bnez $v0,.L0010D640 */
	.word	0x24020020  /* 0010D5B8 li $v0,32 */
	.word	0x1502000E  /* 0010D5BC bne $t0,$v0,.L0010D5F8 */
	.word	0xA4900004  /* 0010D5C0 sh $s0,4($a0) */
	.word	0x3C020000  /* 0010D5C4 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010D5C8 addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010D5CC lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44900800  /* 0010D5D0 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010D5D4 cvt.s.w $f1,$f1 */
	.word	0x44820000  /* 0010D5D8 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D5DC cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010D5E0 mul.s $f0,$f0,$f22 */
	.word	0x46000840  /* 0010D5E4 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010D5E8 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010D5EC mfc1 $s0,$f0 */
	.word	0x1000000F  /* 0010D5F0 b .L0010D630 */
	.word	0x96420008  /* 0010D5F4 lhu $v0,8($s2) */
	.word	0x3C020000  /* 0010D5F8 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010D5FC addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010D600 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44900800  /* 0010D604 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010D608 cvt.s.w $f1,$f1 */
	.word	0x44801000  /* 0010D60C mtc1 $zero,$f2 */
	.word	0x44820000  /* 0010D610 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D614 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010D618 mul.s $f0,$f0,$f22 */
	.word	0x46020000  /* 0010D61C add.s $f0,$f0,$f2 */
	.word	0x46000840  /* 0010D620 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010D624 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010D628 mfc1 $s0,$f0 */
	.word	0x96420008  /* 0010D62C lhu $v0,8($s2) */
	.word	0x00B11821  /* 0010D630 addu $v1,$a1,$s1 */
	.word	0x02021023  /* 0010D634 subu $v0,$s0,$v0 */
	.word	0x10000020  /* 0010D638 b .L0010D6BC */
	.word	0xA4620018  /* 0010D63C sh $v0,24($v1) */
	.word	0x3C020000  /* 0010D640 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010D644 addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010D648 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44901800  /* 0010D64C mtc1 $s0,$f3 */
	.word	0x468018E0  /* 0010D650 cvt.s.w $f3,$f3 */
	.word	0x3C0141C0  /* 0010D654 lui $at,0x41c0 */
	.word	0x44810800  /* 0010D658 mtc1 $at,$f1 */
	.word	0x44820000  /* 0010D65C mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D660 cvt.s.w $f0,$f0 */
	.word	0x3C013F00  /* 0010D664 lui $at,0x3f00 */
	.word	0x44811000  /* 0010D668 mtc1 $at,$f2 */
	.word	0x3C014F00  /* 0010D66C lui $at,0x4f00 */
	.word	0x44812000  /* 0010D670 mtc1 $at,$f4 */
	.word	0x46160002  /* 0010D674 mul.s $f0,$f0,$f22 */
	.word	0x46000841  /* 0010D678 sub.s $f1,$f1,$f0 */
	.word	0x46020842  /* 0010D67C mul.s $f1,$f1,$f2 */
	.word	0x46011800  /* 0010D680 add.s $f0,$f3,$f1 */
	.word	0x46002036  /* 0010D684 c.le.s $f4,$f0 */
	.word	0x46000064  /* 0010D688 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010D68C mfc1 $v1,$f1 */
	.word	0x45020007  /* 0010D690 bc1fl .L0010D6B0 */
	.word	0xA4830004  /* 0010D694 sh $v1,4($a0) */
	.word	0x46040001  /* 0010D698 sub.s $f0,$f0,$f4 */
	.word	0x3C028000  /* 0010D69C lui $v0,0x8000 */
	.word	0x46000064  /* 0010D6A0 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010D6A4 mfc1 $v1,$f1 */
	.word	0x00621825  /* 0010D6A8 or $v1,$v1,$v0 */
	.word	0xA4830004  /* 0010D6AC sh $v1,4($a0) */
	.word	0x3C030000  /* 0010D6B0 lui $v1,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0x8C620000  /* 0010D6B4 lw $v0,%lo(D_004D59E8)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0x02028021  /* 0010D6B8 addu $s0,$s0,$v0 */
	.word	0x24A20010  /* 0010D6BC addiu $v0,$a1,16 */
	.word	0x8FA40050  /* 0010D6C0 lw $a0,80($sp) */
	.word	0x02221821  /* 0010D6C4 addu $v1,$s1,$v0 */
	.word	0x4614AD40  /* 0010D6C8 add.s $f21,$f21,$f20 */
	.word	0x0060102D  /* 0010D6CC move $v0,$v1 */
	.word	0x26F70001  /* 0010D6D0 addiu $s7,$s7,1 */
	.word	0xA444000A  /* 0010D6D4 sh $a0,10($v0) */
	.word	0xE474000C  /* 0010D6D8 swc1 $f20,12($v1) */
	.word	0xA4560006  /* 0010D6DC sh $s6,6($v0) */
	.word	0x10000319  /* 0010D6E0 b .L0010E348 */
	.word	0xA45E0002  /* 0010D6E4 sh $s8,2($v0) */
	.word	0x3C030000  /* 0010D6E8 lui $v1,%hi(jtbl_0048CE00) */
	.reloc	.-4, R_MIPS_HI16, D_0048CE00
	.word	0x00621821  /* 0010D6EC addu $v1,$v1,$v0 */
	.word	0x8C630000  /* 0010D6F0 lw $v1,%lo(jtbl_0048CE00)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_0048CE00
	.word	0x00600008  /* 0010D6F4 jr $v1 */
	.word	0x00000000  /* 0010D6F8 nop */
	.word	0x00000000  /* 0010D6FC nop */
	.word	0x3C060000  /* 0010D700 lui $a2,%hi(D_004D5AF0) */
	.reloc	.-4, R_MIPS_HI16, D_004D5AF0
	.word	0x96440008  /* 0010D704 lhu $a0,8($s2) */
	.word	0x24C50000  /* 0010D708 addiu $a1,$a2,%lo(D_004D5AF0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5AF0
	.word	0x8FA60044  /* 0010D70C lw $a2,68($sp) */
	.word	0x8CA20000  /* 0010D710 lw $v0,0($a1) */
	.word	0x02042023  /* 0010D714 subu $a0,$s0,$a0 */
	.word	0x00061880  /* 0010D718 sll $v1,$a2,0x2 */
	.word	0x3C0147F1  /* 0010D71C lui $at,0x47f1 */
	.word	0x34212000  /* 0010D720 ori $at,$at,0x2000 */
	.word	0x44810000  /* 0010D724 mtc1 $at,$f0 */
	.word	0x00023080  /* 0010D728 sll $a2,$v0,0x2 */
	.word	0x24420001  /* 0010D72C addiu $v0,$v0,1 */
	.word	0xACA20000  /* 0010D730 sw $v0,0($a1) */
	.word	0x00713821  /* 0010D734 addu $a3,$v1,$s1 */
	.word	0x00E0182D  /* 0010D738 move $v1,$a3 */
	.word	0x3C010000  /* 0010D73C lui $at,%hi(D_004D59F0) */
	.reloc	.-4, R_MIPS_HI16, D_004D59F0
	.word	0x00260821  /* 0010D740 addu $at,$at,$a2 */
	.word	0xAC240000  /* 0010D744 sw $a0,%lo(D_004D59F0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_004D59F0
	.word	0x8FA20044  /* 0010D748 lw $v0,68($sp) */
	.word	0x8FA90040  /* 0010D74C lw $t1,64($sp) */
	.word	0x24420001  /* 0010D750 addiu $v0,$v0,1 */
	.word	0xAFA20044  /* 0010D754 sw $v0,68($sp) */
	.word	0xE4601850  /* 0010D758 swc1 $f0,6224($v1) */
	.word	0xAFA00048  /* 0010D75C sw $zero,72($sp) */
	.word	0x100002FA  /* 0010D760 b .L0010E34C */
	.word	0xE4F51810  /* 0010D764 swc1 $f21,6160($a3) */
	.word	0x3C030000  /* 0010D768 lui $v1,%hi(D_004D5AF0) */
	.reloc	.-4, R_MIPS_HI16, D_004D5AF0
	.word	0x96440008  /* 0010D76C lhu $a0,8($s2) */
	.word	0x24650000  /* 0010D770 addiu $a1,$v1,%lo(D_004D5AF0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5AF0
	.word	0x8FA90040  /* 0010D774 lw $t1,64($sp) */
	.word	0x8CA20000  /* 0010D778 lw $v0,0($a1) */
	.word	0x02042023  /* 0010D77C subu $a0,$s0,$a0 */
	.word	0xAFA00048  /* 0010D780 sw $zero,72($sp) */
	.word	0x00021880  /* 0010D784 sll $v1,$v0,0x2 */
	.word	0x24420001  /* 0010D788 addiu $v0,$v0,1 */
	.word	0x3C010000  /* 0010D78C lui $at,%hi(D_004D59F0) */
	.reloc	.-4, R_MIPS_HI16, D_004D59F0
	.word	0x00230821  /* 0010D790 addu $at,$at,$v1 */
	.word	0xAC240000  /* 0010D794 sw $a0,%lo(D_004D59F0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_004D59F0
	.word	0x100002EC  /* 0010D798 b .L0010E34C */
	.word	0xACA20000  /* 0010D79C sw $v0,0($a1) */
	.word	0x00172900  /* 0010D7A0 sll $a1,$s7,0x4 */
	.word	0x2402270F  /* 0010D7A4 li $v0,9999 */
	.word	0x24A30010  /* 0010D7A8 addiu $v1,$a1,16 */
	.word	0x3C060000  /* 0010D7AC lui $a2,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x02232021  /* 0010D7B0 addu $a0,$s1,$v1 */
	.word	0xA4820000  /* 0010D7B4 sh $v0,0($a0) */
	.word	0x8CC30000  /* 0010D7B8 lw $v1,%lo(D_004D59E4)($a2) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x1460000E  /* 0010D7BC bnez $v1,.L0010D7F8 */
	.word	0x00000000  /* 0010D7C0 nop */
	.word	0x3C014140  /* 0010D7C4 lui $at,0x4140 */
	.word	0x44810000  /* 0010D7C8 mtc1 $at,$f0 */
	.word	0x44900800  /* 0010D7CC mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010D7D0 cvt.s.w $f1,$f1 */
	.word	0x44801000  /* 0010D7D4 mtc1 $zero,$f2 */
	.word	0x4600B002  /* 0010D7D8 mul.s $f0,$f22,$f0 */
	.word	0xA4900004  /* 0010D7DC sh $s0,4($a0) */
	.word	0x46020000  /* 0010D7E0 add.s $f0,$f0,$f2 */
	.word	0x46000840  /* 0010D7E4 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010D7E8 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010D7EC mfc1 $s0,$f0 */
	.word	0x10000021  /* 0010D7F0 b .L0010D878 */
	.word	0x96420008  /* 0010D7F4 lhu $v0,8($s2) */
	.word	0x3C020000  /* 0010D7F8 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010D7FC addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010D800 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44901800  /* 0010D804 mtc1 $s0,$f3 */
	.word	0x468018E0  /* 0010D808 cvt.s.w $f3,$f3 */
	.word	0x3C0141C0  /* 0010D80C lui $at,0x41c0 */
	.word	0x44810800  /* 0010D810 mtc1 $at,$f1 */
	.word	0x44820000  /* 0010D814 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D818 cvt.s.w $f0,$f0 */
	.word	0x3C013F00  /* 0010D81C lui $at,0x3f00 */
	.word	0x44811000  /* 0010D820 mtc1 $at,$f2 */
	.word	0x3C014F00  /* 0010D824 lui $at,0x4f00 */
	.word	0x44812000  /* 0010D828 mtc1 $at,$f4 */
	.word	0x46160002  /* 0010D82C mul.s $f0,$f0,$f22 */
	.word	0x46000841  /* 0010D830 sub.s $f1,$f1,$f0 */
	.word	0x46020842  /* 0010D834 mul.s $f1,$f1,$f2 */
	.word	0x46011800  /* 0010D838 add.s $f0,$f3,$f1 */
	.word	0x46002036  /* 0010D83C c.le.s $f4,$f0 */
	.word	0x46000064  /* 0010D840 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010D844 mfc1 $v1,$f1 */
	.word	0x45020007  /* 0010D848 bc1fl .L0010D868 */
	.word	0xA4830004  /* 0010D84C sh $v1,4($a0) */
	.word	0x46040001  /* 0010D850 sub.s $f0,$f0,$f4 */
	.word	0x3C028000  /* 0010D854 lui $v0,0x8000 */
	.word	0x46000064  /* 0010D858 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010D85C mfc1 $v1,$f1 */
	.word	0x00621825  /* 0010D860 or $v1,$v1,$v0 */
	.word	0xA4830004  /* 0010D864 sh $v1,4($a0) */
	.word	0x3C030000  /* 0010D868 lui $v1,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0x8C620000  /* 0010D86C lw $v0,%lo(D_004D59E8)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0x02028021  /* 0010D870 addu $s0,$s0,$v0 */
	.word	0x96420008  /* 0010D874 lhu $v0,8($s2) */
	.word	0x24A30010  /* 0010D878 addiu $v1,$a1,16 */
	.word	0x02232021  /* 0010D87C addu $a0,$s1,$v1 */
	.word	0x8FA50050  /* 0010D880 lw $a1,80($sp) */
	.word	0x0080182D  /* 0010D884 move $v1,$a0 */
	.word	0x02021023  /* 0010D888 subu $v0,$s0,$v0 */
	.word	0xA465000A  /* 0010D88C sh $a1,10($v1) */
	.word	0x4614AD40  /* 0010D890 add.s $f21,$f21,$f20 */
	.word	0xA4620008  /* 0010D894 sh $v0,8($v1) */
	.word	0x26F70001  /* 0010D898 addiu $s7,$s7,1 */
	.word	0xE494000C  /* 0010D89C swc1 $f20,12($a0) */
	.word	0xA4760006  /* 0010D8A0 sh $s6,6($v1) */
	.word	0x100002A8  /* 0010D8A4 b .L0010E348 */
	.word	0xA47E0002  /* 0010D8A8 sh $s8,2($v1) */
	.word	0x00000000  /* 0010D8AC nop */
	.word	0x3C020000  /* 0010D8B0 lui $v0,%hi(D_004D5AF0) */
	.reloc	.-4, R_MIPS_HI16, D_004D5AF0
	.word	0x24460000  /* 0010D8B4 addiu $a2,$v0,%lo(D_004D5AF0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5AF0
	.word	0x96420008  /* 0010D8B8 lhu $v0,8($s2) */
	.word	0x8CC30000  /* 0010D8BC lw $v1,0($a2) */
	.word	0x02022823  /* 0010D8C0 subu $a1,$s0,$v0 */
	.word	0x0040802D  /* 0010D8C4 move $s0,$v0 */
	.word	0x00032080  /* 0010D8C8 sll $a0,$v1,0x2 */
	.word	0x24630001  /* 0010D8CC addiu $v1,$v1,1 */
	.word	0x3C010000  /* 0010D8D0 lui $at,%hi(D_004D59F0) */
	.reloc	.-4, R_MIPS_HI16, D_004D59F0
	.word	0x00240821  /* 0010D8D4 addu $at,$at,$a0 */
	.word	0xAC250000  /* 0010D8D8 sw $a1,%lo(D_004D59F0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_004D59F0
	.word	0xACC30000  /* 0010D8DC sw $v1,0($a2) */
	.word	0x92420013  /* 0010D8E0 lbu $v0,19($s2) */
	.word	0x30420008  /* 0010D8E4 andi $v0,$v0,0x8 */
	.word	0x1040000B  /* 0010D8E8 beqz $v0,.L0010D918 */
	.word	0x00000000  /* 0010D8EC nop */
	.word	0x3C014214  /* 0010D8F0 lui $at,0x4214 */
	.word	0x44810000  /* 0010D8F4 mtc1 $at,$f0 */
	.word	0x44960800  /* 0010D8F8 mtc1 $s6,$f1 */
	.word	0x46800860  /* 0010D8FC cvt.s.w $f1,$f1 */
	.word	0x4600B002  /* 0010D900 mul.s $f0,$f22,$f0 */
	.word	0x46000840  /* 0010D904 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010D908 trunc.w.s $f0,$f1 */
	.word	0x44160000  /* 0010D90C mfc1 $s6,$f0 */
	.word	0x1000028E  /* 0010D910 b .L0010E34C */
	.word	0x8FA90040  /* 0010D914 lw $t1,64($sp) */
	.word	0x3C0141E0  /* 0010D918 lui $at,0x41e0 */
	.word	0x44810000  /* 0010D91C mtc1 $at,$f0 */
	.word	0x44960800  /* 0010D920 mtc1 $s6,$f1 */
	.word	0x46800860  /* 0010D924 cvt.s.w $f1,$f1 */
	.word	0x4600B002  /* 0010D928 mul.s $f0,$f22,$f0 */
	.word	0x46000840  /* 0010D92C add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010D930 trunc.w.s $f0,$f1 */
	.word	0x44160000  /* 0010D934 mfc1 $s6,$f0 */
	.word	0x10000284  /* 0010D938 b .L0010E34C */
	.word	0x8FA90040  /* 0010D93C lw $t1,64($sp) */
	.word	0x8FA30044  /* 0010D940 lw $v1,68($sp) */
	.word	0x3C0147F1  /* 0010D944 lui $at,0x47f1 */
	.word	0x34212000  /* 0010D948 ori $at,$at,0x2000 */
	.word	0x44810000  /* 0010D94C mtc1 $at,$f0 */
	.word	0x00031080  /* 0010D950 sll $v0,$v1,0x2 */
	.word	0x24630001  /* 0010D954 addiu $v1,$v1,1 */
	.word	0xAFA30044  /* 0010D958 sw $v1,68($sp) */
	.word	0x00511821  /* 0010D95C addu $v1,$v0,$s1 */
	.word	0x0060102D  /* 0010D960 move $v0,$v1 */
	.word	0x10000074  /* 0010D964 b .L0010DB38 */
	.word	0x8FA90040  /* 0010D968 lw $t1,64($sp) */
	.word	0x00000000  /* 0010D96C nop */
	.word	0x27A40040  /* 0010D970 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010D974 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010D978 move $a1,$s3 */
	.word	0x3C014974  /* 0010D97C lui $at,0x4974 */
	.word	0x34212400  /* 0010D980 ori $at,$at,0x2400 */
	.word	0x44810800  /* 0010D984 mtc1 $at,$f1 */
	.word	0x44820000  /* 0010D988 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D98C cvt.s.w $f0,$f0 */
	.word	0x8FA40044  /* 0010D990 lw $a0,68($sp) */
	.word	0x8FA90040  /* 0010D994 lw $t1,64($sp) */
	.word	0x00041880  /* 0010D998 sll $v1,$a0,0x2 */
	.word	0x24840001  /* 0010D99C addiu $a0,$a0,1 */
	.word	0x00711021  /* 0010D9A0 addu $v0,$v1,$s1 */
	.word	0xAFA40044  /* 0010D9A4 sw $a0,68($sp) */
	.word	0x1000000C  /* 0010D9A8 b .L0010D9DC */
	.word	0x46010000  /* 0010D9AC add.s $f0,$f0,$f1 */
	.word	0x0260282D  /* 0010D9B0 move $a1,$s3 */
	.word	0x0C000000  /* 0010D9B4 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x27A40040  /* 0010D9B8 addiu $a0,$sp,64 */
	.word	0x8FA50044  /* 0010D9BC lw $a1,68($sp) */
	.word	0x44820000  /* 0010D9C0 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010D9C4 cvt.s.w $f0,$f0 */
	.word	0x8FA90040  /* 0010D9C8 lw $t1,64($sp) */
	.word	0x00051880  /* 0010D9CC sll $v1,$a1,0x2 */
	.word	0x24A50001  /* 0010D9D0 addiu $a1,$a1,1 */
	.word	0x00711021  /* 0010D9D4 addu $v0,$v1,$s1 */
	.word	0xAFA50044  /* 0010D9D8 sw $a1,68($sp) */
	.word	0x0040182D  /* 0010D9DC move $v1,$v0 */
	.word	0xE4601850  /* 0010D9E0 swc1 $f0,6224($v1) */
	.word	0x10000259  /* 0010D9E4 b .L0010E34C */
	.word	0xE4551810  /* 0010D9E8 swc1 $f21,6160($v0) */
	.word	0x00000000  /* 0010D9EC nop */
	.word	0x27A40040  /* 0010D9F0 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010D9F4 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010D9F8 move $a1,$s3 */
	.word	0x10000252  /* 0010D9FC b .L0010E348 */
	.word	0x02C2B021  /* 0010DA00 addu $s6,$s6,$v0 */
	.word	0x00000000  /* 0010DA04 nop */
	.word	0x8FA20040  /* 0010DA08 lw $v0,64($sp) */
	.word	0x24490001  /* 0010DA0C addiu $t1,$v0,1 */
	.word	0xAFA90040  /* 0010DA10 sw $t1,64($sp) */
	.word	0x02691021  /* 0010DA14 addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010DA18 lbu $a3,0($v0) */
	.word	0x10E00006  /* 0010DA1C beqz $a3,.L0010DA38 */
	.word	0x24020001  /* 0010DA20 li $v0,1 */
	.word	0x10E2000A  /* 0010DA24 beq $a3,$v0,.L0010DA50 */
	.word	0x8FA50048  /* 0010DA28 lw $a1,72($sp) */
	.word	0x10000249  /* 0010DA2C b .L0010E354 */
	.word	0x25290001  /* 0010DA30 addiu $t1,$t1,1 */
	.word	0x00000000  /* 0010DA34 nop */
	.word	0x27A40040  /* 0010DA38 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010DA3C jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010DA40 move $a1,$s3 */
	.word	0x10000240  /* 0010DA44 b .L0010E348 */
	.word	0x02028021  /* 0010DA48 addu $s0,$s0,$v0 */
	.word	0x00000000  /* 0010DA4C nop */
	.word	0x27A40040  /* 0010DA50 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010DA54 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010DA58 move $a1,$s3 */
	.word	0x96430008  /* 0010DA5C lhu $v1,8($s2) */
	.word	0x8FA90040  /* 0010DA60 lw $t1,64($sp) */
	.word	0x10000239  /* 0010DA64 b .L0010E34C */
	.word	0x00628021  /* 0010DA68 addu $s0,$v1,$v0 */
	.word	0x00000000  /* 0010DA6C nop */
	.word	0x8FA20040  /* 0010DA70 lw $v0,64($sp) */
	.word	0x24490001  /* 0010DA74 addiu $t1,$v0,1 */
	.word	0xAFA90040  /* 0010DA78 sw $t1,64($sp) */
	.word	0x02691021  /* 0010DA7C addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010DA80 lbu $a3,0($v0) */
	.word	0x10E00006  /* 0010DA84 beqz $a3,.L0010DAA0 */
	.word	0x24020001  /* 0010DA88 li $v0,1 */
	.word	0x10E20014  /* 0010DA8C beq $a3,$v0,.L0010DAE0 */
	.word	0x8FA50048  /* 0010DA90 lw $a1,72($sp) */
	.word	0x1000022F  /* 0010DA94 b .L0010E354 */
	.word	0x25290001  /* 0010DA98 addiu $t1,$t1,1 */
	.word	0x00000000  /* 0010DA9C nop */
	.word	0x27A40040  /* 0010DAA0 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010DAA4 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010DAA8 move $a1,$s3 */
	.word	0x24030080  /* 0010DAAC li $v1,128 */
	.word	0x0062001A  /* 0010DAB0 div $zero,$v1,$v0 */
	.word	0x50400001  /* 0010DAB4 beqzl $v0,.L0010DABC */
	.word	0x000001CD  /* 0010DAB8 break 0x0,0x7 */
	.word	0x8FA90040  /* 0010DABC lw $t1,64($sp) */
	.word	0x00001812  /* 0010DAC0 mflo $v1 */
	.word	0x44830000  /* 0010DAC4 mtc1 $v1,$f0 */
	.word	0x46800020  /* 0010DAC8 cvt.s.w $f0,$f0 */
	.word	0x46000064  /* 0010DACC trunc.w.s $f1,$f0 */
	.word	0xE7A10050  /* 0010DAD0 swc1 $f1,80($sp) */
	.word	0x1000021D  /* 0010DAD4 b .L0010E34C */
	.word	0xE6400018  /* 0010DAD8 swc1 $f0,24($s2) */
	.word	0x00000000  /* 0010DADC nop */
	.word	0x27A40040  /* 0010DAE0 addiu $a0,$sp,64 */
	.word	0x0C000000  /* 0010DAE4 jal func_0010d438 */
	.reloc	.-4, R_MIPS_26, func_0010d438
	.word	0x0260282D  /* 0010DAE8 move $a1,$s3 */
	.word	0x3C01C300  /* 0010DAEC lui $at,0xc300 */
	.word	0x44810800  /* 0010DAF0 mtc1 $at,$f1 */
	.word	0x44820000  /* 0010DAF4 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010DAF8 cvt.s.w $f0,$f0 */
	.word	0x3C0149F4  /* 0010DAFC lui $at,0x49f4 */
	.word	0x34212400  /* 0010DB00 ori $at,$at,0x2400 */
	.word	0x44811000  /* 0010DB04 mtc1 $at,$f2 */
	.word	0x8FA30044  /* 0010DB08 lw $v1,68($sp) */
	.word	0x8FA90040  /* 0010DB0C lw $t1,64($sp) */
	.word	0x00031080  /* 0010DB10 sll $v0,$v1,0x2 */
	.word	0x24630001  /* 0010DB14 addiu $v1,$v1,1 */
	.word	0x00000000  /* 0010DB18 nop */
	.word	0x00000000  /* 0010DB1C nop */
	.word	0x46000843  /* 0010DB20 div.s $f1,$f1,$f0 */
	.word	0xAFA30044  /* 0010DB24 sw $v1,68($sp) */
	.word	0x46020000  /* 0010DB28 add.s $f0,$f0,$f2 */
	.word	0x00511821  /* 0010DB2C addu $v1,$v0,$s1 */
	.word	0x0060102D  /* 0010DB30 move $v0,$v1 */
	.word	0xE641001C  /* 0010DB34 swc1 $f1,28($s2) */
	.word	0xE4401850  /* 0010DB38 swc1 $f0,6224($v0) */
	.word	0x10000203  /* 0010DB3C b .L0010E34C */
	.word	0xE4751810  /* 0010DB40 swc1 $f21,6160($v1) */
	.word	0x00000000  /* 0010DB44 nop */
	.word	0x8FA20040  /* 0010DB48 lw $v0,64($sp) */
	.word	0x24490001  /* 0010DB4C addiu $t1,$v0,1 */
	.word	0xAFA90040  /* 0010DB50 sw $t1,64($sp) */
	.word	0x02691021  /* 0010DB54 addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010DB58 lbu $a3,0($v0) */
	.word	0x2CE30024  /* 0010DB5C sltiu $v1,$a3,36 */
	.word	0x50600055  /* 0010DB60 beqzl $v1,.L0010DCB8 */
	.word	0x92A80000  /* 0010DB64 lbu $t0,0($s5) */
	.word	0x00071880  /* 0010DB68 sll $v1,$a3,0x2 */
	.word	0x3C020000  /* 0010DB6C lui $v0,%hi(jtbl_0048CE80) */
	.reloc	.-4, R_MIPS_HI16, D_0048CE80
	.word	0x00431021  /* 0010DB70 addu $v0,$v0,$v1 */
	.word	0x8C420000  /* 0010DB74 lw $v0,%lo(jtbl_0048CE80)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0048CE80
	.word	0x00400008  /* 0010DB78 jr $v0 */
	.word	0x00000000  /* 0010DB7C nop */
	.word	0x0C000000  /* 0010DB80 jal func_001ef7a0 */
	.reloc	.-4, R_MIPS_26, func_001ef7a0
	.word	0x00000000  /* 0010DB84 nop */
	.word	0x3C050000  /* 0010DB88 lui $a1,%hi(D_0048CDF0) */
	.reloc	.-4, R_MIPS_HI16, D_0048CDF0
	.word	0x24A50000  /* 0010DB8C addiu $a1,$a1,%lo(D_0048CDF0) */
	.reloc	.-4, R_MIPS_LO16, D_0048CDF0
	.word	0x0040302D  /* 0010DB90 move $a2,$v0 */
	.word	0x0C000000  /* 0010DB94 jal func_0010d388 */
	.reloc	.-4, R_MIPS_26, func_0010d388
	.word	0x03A0202D  /* 0010DB98 move $a0,$sp */
	.word	0x03A0A82D  /* 0010DB9C move $s5,$sp */
	.word	0x10000044  /* 0010DBA0 b .L0010DCB4 */
	.word	0x8FA90040  /* 0010DBA4 lw $t1,64($sp) */
	.word	0x3C020000  /* 0010DBA8 lui $v0,%hi(D_002BBAB0) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAB0
	.word	0x0C000000  /* 0010DBAC jal func_00147840 */
	.reloc	.-4, R_MIPS_26, func_00147840
	.word	0x8C440000  /* 0010DBB0 lw $a0,%lo(D_002BBAB0)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAB0
	.word	0x0C000000  /* 0010DBB4 jal func_00147808 */
	.reloc	.-4, R_MIPS_26, func_00147808
	.word	0x94440000  /* 0010DBB8 lhu $a0,0($v0) */
	.word	0x10000030  /* 0010DBBC b .L0010DC80 */
	.word	0x0040A82D  /* 0010DBC0 move $s5,$v0 */
	.word	0x00000000  /* 0010DBC4 nop */
	.word	0x3C020000  /* 0010DBC8 lui $v0,%hi(D_002BBAB4) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAB4
	.word	0x0C000000  /* 0010DBCC jal func_001ba228 */
	.reloc	.-4, R_MIPS_26, func_001ba228
	.word	0x8C440000  /* 0010DBD0 lw $a0,%lo(D_002BBAB4)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAB4
	.word	0x1000002A  /* 0010DBD4 b .L0010DC80 */
	.word	0x0040A82D  /* 0010DBD8 move $s5,$v0 */
	.word	0x00000000  /* 0010DBDC nop */
	.word	0x0C000000  /* 0010DBE0 jal func_001eafd8 */
	.reloc	.-4, R_MIPS_26, func_001eafd8
	.word	0x00000000  /* 0010DBE4 nop */
	.word	0x10000025  /* 0010DBE8 b .L0010DC80 */
	.word	0x0040A82D  /* 0010DBEC move $s5,$v0 */
	.word	0x3C020000  /* 0010DBF0 lui $v0,%hi(D_002BBAB8) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAB8
	.word	0x0C000000  /* 0010DBF4 jal func_001478a0 */
	.reloc	.-4, R_MIPS_26, func_001478a0
	.word	0x8C440000  /* 0010DBF8 lw $a0,%lo(D_002BBAB8)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAB8
	.word	0x10000020  /* 0010DBFC b .L0010DC80 */
	.word	0x8C550004  /* 0010DC00 lw $s5,4($v0) */
	.word	0x00000000  /* 0010DC04 nop */
	.word	0x3C030000  /* 0010DC08 lui $v1,%hi(D_002BBABC) */
	.reloc	.-4, R_MIPS_HI16, D_002BBABC
	.word	0x3C020000  /* 0010DC0C lui $v0,%hi(D_002BBAC0) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAC0
	.word	0x8C640000  /* 0010DC10 lw $a0,%lo(D_002BBABC)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_002BBABC
	.word	0x0C000000  /* 0010DC14 jal func_00132f60 */
	.reloc	.-4, R_MIPS_26, func_00132f60
	.word	0x8C450000  /* 0010DC18 lw $a1,%lo(D_002BBAC0)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAC0
	.word	0x10000018  /* 0010DC1C b .L0010DC80 */
	.word	0x0040A82D  /* 0010DC20 move $s5,$v0 */
	.word	0x00000000  /* 0010DC24 nop */
	.word	0x24E2FFE0  /* 0010DC28 addiu $v0,$a3,-32 */
	.word	0x00021080  /* 0010DC2C sll $v0,$v0,0x2 */
	.word	0x3C050000  /* 0010DC30 lui $a1,%hi(D_002BBAE0) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAE0
	.word	0x00A22821  /* 0010DC34 addu $a1,$a1,$v0 */
	.word	0x8CA50000  /* 0010DC38 lw $a1,%lo(D_002BBAE0)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAE0
	.word	0x3C040000  /* 0010DC3C lui $a0,%hi(D_002BBAD0) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAD0
	.word	0x00822021  /* 0010DC40 addu $a0,$a0,$v0 */
	.word	0x8C840000  /* 0010DC44 lw $a0,%lo(D_002BBAD0)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAD0
	.word	0x0C000000  /* 0010DC48 jal func_00132f60 */
	.reloc	.-4, R_MIPS_26, func_00132f60
	.word	0x00000000  /* 0010DC4C nop */
	.word	0x1000000B  /* 0010DC50 b .L0010DC80 */
	.word	0x0040A82D  /* 0010DC54 move $s5,$v0 */
	.word	0x3C020000  /* 0010DC58 lui $v0,%hi(D_002BBAC4) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAC4
	.word	0x0C000000  /* 0010DC5C jal func_00132f48 */
	.reloc	.-4, R_MIPS_26, func_00132f48
	.word	0x8C440000  /* 0010DC60 lw $a0,%lo(D_002BBAC4)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAC4
	.word	0x10000006  /* 0010DC64 b .L0010DC80 */
	.word	0x0040A82D  /* 0010DC68 move $s5,$v0 */
	.word	0x00000000  /* 0010DC6C nop */
	.word	0x3C020000  /* 0010DC70 lui $v0,%hi(D_002BBAC8) */
	.reloc	.-4, R_MIPS_HI16, D_002BBAC8
	.word	0x0C000000  /* 0010DC74 jal func_00147760 */
	.reloc	.-4, R_MIPS_26, func_00147760
	.word	0x8C440000  /* 0010DC78 lw $a0,%lo(D_002BBAC8)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBAC8
	.word	0x0040A82D  /* 0010DC7C move $s5,$v0 */
	.word	0x0C000000  /* 0010DC80 jal func_0010d350 */
	.reloc	.-4, R_MIPS_26, func_0010d350
	.word	0x02A0202D  /* 0010DC84 move $a0,$s5 */
	.word	0x1000000A  /* 0010DC88 b .L0010DCB4 */
	.word	0x8FA90040  /* 0010DC8C lw $t1,64($sp) */
	.word	0x3C060000  /* 0010DC90 lui $a2,%hi(D_003C5830) */
	.reloc	.-4, R_MIPS_HI16, D_003C5830
	.word	0x00C33021  /* 0010DC94 addu $a2,$a2,$v1 */
	.word	0x8CC60000  /* 0010DC98 lw $a2,%lo(D_003C5830)($a2) */
	.reloc	.-4, R_MIPS_LO16, D_003C5830
	.word	0x3C050000  /* 0010DC9C lui $a1,%hi(D_0048CDF0) */
	.reloc	.-4, R_MIPS_HI16, D_0048CDF0
	.word	0x24A50000  /* 0010DCA0 addiu $a1,$a1,%lo(D_0048CDF0) */
	.reloc	.-4, R_MIPS_LO16, D_0048CDF0
	.word	0x0C000000  /* 0010DCA4 jal func_0010d388 */
	.reloc	.-4, R_MIPS_26, func_0010d388
	.word	0x03A0202D  /* 0010DCA8 move $a0,$sp */
	.word	0x8FA90040  /* 0010DCAC lw $t1,64($sp) */
	.word	0x03A0A82D  /* 0010DCB0 move $s5,$sp */
	.word	0x92A80000  /* 0010DCB4 lbu $t0,0($s5) */
	.word	0x110001A4  /* 0010DCB8 beqz $t0,.L0010E34C */
	.word	0x0000502D  /* 0010DCBC move $t2,$zero */
	.word	0x00173100  /* 0010DCC0 sll $a2,$s7,0x4 */
	.word	0x3C020000  /* 0010DCC4 lui $v0,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x00D12821  /* 0010DCC8 addu $a1,$a2,$s1 */
	.word	0x24C60010  /* 0010DCCC addiu $a2,$a2,16 */
	.word	0x3C030000  /* 0010DCD0 lui $v1,%hi(D_00495280) */
	.reloc	.-4, R_MIPS_HI16, D_00495280
	.word	0x3C0B0004  /* 0010DCD4 lui $t3,0x4 */
	.word	0x3C040000  /* 0010DCD8 lui $a0,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0x44802800  /* 0010DCDC mtc1 $zero,$f5 */
	.word	0x3C0141C0  /* 0010DCE0 lui $at,0x41c0 */
	.word	0x44812000  /* 0010DCE4 mtc1 $at,$f4 */
	.word	0x244F0000  /* 0010DCE8 addiu $t7,$v0,%lo(D_004D59E4) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x3C013F00  /* 0010DCEC lui $at,0x3f00 */
	.word	0x44811800  /* 0010DCF0 mtc1 $at,$f3 */
	.word	0x246D0000  /* 0010DCF4 addiu $t5,$v1,%lo(D_00495280) */
	.reloc	.-4, R_MIPS_LO16, D_00495280
	.word	0x24840000  /* 0010DCF8 addiu $a0,$a0,%lo(D_004D59E8) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0x24A50010  /* 0010DCFC addiu $a1,$a1,16 */
	.word	0x356B0080  /* 0010DD00 ori $t3,$t3,0x80 */
	.word	0x3C0E8000  /* 0010DD04 lui $t6,0x8000 */
	.word	0x262C000C  /* 0010DD08 addiu $t4,$s1,12 */
	.word	0x00000000  /* 0010DD0C nop */
	.word	0x2D020020  /* 0010DD10 sltiu $v0,$t0,32 */
	.word	0x14400006  /* 0010DD14 bnez $v0,.L0010DD30 */
	.word	0x24020018  /* 0010DD18 li $v0,24 */
	.word	0x3402FFE0  /* 0010DD1C li $v0,0xffe0 */
	.word	0x00481021  /* 0010DD20 addu $v0,$v0,$t0 */
	.word	0x1000001A  /* 0010DD24 b .L0010DD90 */
	.word	0x3054FFFF  /* 0010DD28 andi $s4,$v0,0xffff */
	.word	0x00000000  /* 0010DD2C nop */
	.word	0x51020009  /* 0010DD30 beql $t0,$v0,.L0010DD58 */
	.word	0x254A0001  /* 0010DD34 addiu $t2,$t2,1 */
	.word	0x29020019  /* 0010DD38 slti $v0,$t0,25 */
	.word	0x14400015  /* 0010DD3C bnez $v0,.L0010DD94 */
	.word	0x24020001  /* 0010DD40 li $v0,1 */
	.word	0x29020020  /* 0010DD44 slti $v0,$t0,32 */
	.word	0x10400012  /* 0010DD48 beqz $v0,.L0010DD94 */
	.word	0x24020001  /* 0010DD4C li $v0,1 */
	.word	0x10000007  /* 0010DD50 b .L0010DD70 */
	.word	0x254A0001  /* 0010DD54 addiu $t2,$t2,1 */
	.word	0x02AA1021  /* 0010DD58 addu $v0,$s5,$t2 */
	.word	0x90480000  /* 0010DD5C lbu $t0,0($v0) */
	.word	0x250300E7  /* 0010DD60 addiu $v1,$t0,231 */
	.word	0x306800FF  /* 0010DD64 andi $t0,$v1,0xff */
	.word	0x10000007  /* 0010DD68 b .L0010DD88 */
	.word	0x00081200  /* 0010DD6C sll $v0,$t0,0x8 */
	.word	0x250200E7  /* 0010DD70 addiu $v0,$t0,231 */
	.word	0x02AA1821  /* 0010DD74 addu $v1,$s5,$t2 */
	.word	0x304800FF  /* 0010DD78 andi $t0,$v0,0xff */
	.word	0x90670000  /* 0010DD7C lbu $a3,0($v1) */
	.word	0x00081200  /* 0010DD80 sll $v0,$t0,0x8 */
	.word	0x00471021  /* 0010DD84 addu $v0,$v0,$a3 */
	.word	0x244200E0  /* 0010DD88 addiu $v0,$v0,224 */
	.word	0x3054FFFF  /* 0010DD8C andi $s4,$v0,0xffff */
	.word	0x24020001  /* 0010DD90 li $v0,1 */
	.word	0x55020036  /* 0010DD94 bnel $t0,$v0,.L0010DE70 */
	.word	0x8DE20000  /* 0010DD98 lw $v0,0($t7) */
	.word	0x8DE30000  /* 0010DD9C lw $v1,0($t7) */
	.word	0x2402270F  /* 0010DDA0 li $v0,9999 */
	.word	0xA4A20000  /* 0010DDA4 sh $v0,0($a1) */
	.word	0x1460000D  /* 0010DDA8 bnez $v1,.L0010DDE0 */
	.word	0x00A0382D  /* 0010DDAC move $a3,$a1 */
	.word	0x3C014140  /* 0010DDB0 lui $at,0x4140 */
	.word	0x44810000  /* 0010DDB4 mtc1 $at,$f0 */
	.word	0x44900800  /* 0010DDB8 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010DDBC cvt.s.w $f1,$f1 */
	.word	0xA4B00004  /* 0010DDC0 sh $s0,4($a1) */
	.word	0x4600B002  /* 0010DDC4 mul.s $f0,$f22,$f0 */
	.word	0x46050000  /* 0010DDC8 add.s $f0,$f0,$f5 */
	.word	0x46000840  /* 0010DDCC add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010DDD0 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010DDD4 mfc1 $s0,$f0 */
	.word	0x1000001B  /* 0010DDD8 b .L0010DE48 */
	.word	0x96430008  /* 0010DDDC lhu $v1,8($s2) */
	.word	0x028B1821  /* 0010DDE0 addu $v1,$s4,$t3 */
	.word	0x44900800  /* 0010DDE4 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010DDE8 cvt.s.w $f1,$f1 */
	.word	0x006D1821  /* 0010DDEC addu $v1,$v1,$t5 */
	.word	0x3C014F00  /* 0010DDF0 lui $at,0x4f00 */
	.word	0x44811000  /* 0010DDF4 mtc1 $at,$f2 */
	.word	0x80620000  /* 0010DDF8 lb $v0,0($v1) */
	.word	0x44820000  /* 0010DDFC mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010DE00 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010DE04 mul.s $f0,$f0,$f22 */
	.word	0x46002001  /* 0010DE08 sub.s $f0,$f4,$f0 */
	.word	0x46030002  /* 0010DE0C mul.s $f0,$f0,$f3 */
	.word	0x46000800  /* 0010DE10 add.s $f0,$f1,$f0 */
	.word	0x46001036  /* 0010DE14 c.le.s $f2,$f0 */
	.word	0x46000064  /* 0010DE18 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010DE1C mfc1 $v1,$f1 */
	.word	0x45020006  /* 0010DE20 bc1fl .L0010DE3C */
	.word	0x8C820000  /* 0010DE24 lw $v0,0($a0) */
	.word	0x46020001  /* 0010DE28 sub.s $f0,$f0,$f2 */
	.word	0x46000064  /* 0010DE2C trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010DE30 mfc1 $v1,$f1 */
	.word	0x006E1825  /* 0010DE34 or $v1,$v1,$t6 */
	.word	0x8C820000  /* 0010DE38 lw $v0,0($a0) */
	.word	0xA4E30004  /* 0010DE3C sh $v1,4($a3) */
	.word	0x02028021  /* 0010DE40 addu $s0,$s0,$v0 */
	.word	0x96430008  /* 0010DE44 lhu $v1,8($s2) */
	.word	0x01861021  /* 0010DE48 addu $v0,$t4,$a2 */
	.word	0xA4B60006  /* 0010DE4C sh $s6,6($a1) */
	.word	0x4614AD40  /* 0010DE50 add.s $f21,$f21,$f20 */
	.word	0x02031823  /* 0010DE54 subu $v1,$s0,$v1 */
	.word	0xA4BE0002  /* 0010DE58 sh $s8,2($a1) */
	.word	0xA4A30008  /* 0010DE5C sh $v1,8($a1) */
	.word	0x24C60010  /* 0010DE60 addiu $a2,$a2,16 */
	.word	0xE4540000  /* 0010DE64 swc1 $f20,0($v0) */
	.word	0x10000045  /* 0010DE68 b .L0010DF80 */
	.word	0x26F70001  /* 0010DE6C addiu $s7,$s7,1 */
	.word	0x00A0382D  /* 0010DE70 move $a3,$a1 */
	.word	0x14400022  /* 0010DE74 bnez $v0,.L0010DF00 */
	.word	0xA4B40000  /* 0010DE78 sh $s4,0($a1) */
	.word	0x24020020  /* 0010DE7C li $v0,32 */
	.word	0x1502000F  /* 0010DE80 bne $t0,$v0,.L0010DEC0 */
	.word	0xA4B00004  /* 0010DE84 sh $s0,4($a1) */
	.word	0x028B1021  /* 0010DE88 addu $v0,$s4,$t3 */
	.word	0x44900800  /* 0010DE8C mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010DE90 cvt.s.w $f1,$f1 */
	.word	0x004D1021  /* 0010DE94 addu $v0,$v0,$t5 */
	.word	0x80430000  /* 0010DE98 lb $v1,0($v0) */
	.word	0x44830000  /* 0010DE9C mtc1 $v1,$f0 */
	.word	0x46800020  /* 0010DEA0 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010DEA4 mul.s $f0,$f0,$f22 */
	.word	0x46000840  /* 0010DEA8 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010DEAC trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010DEB0 mfc1 $s0,$f0 */
	.word	0x1000000F  /* 0010DEB4 b .L0010DEF4 */
	.word	0x96420008  /* 0010DEB8 lhu $v0,8($s2) */
	.word	0x00000000  /* 0010DEBC nop */
	.word	0x028B1021  /* 0010DEC0 addu $v0,$s4,$t3 */
	.word	0x44900800  /* 0010DEC4 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010DEC8 cvt.s.w $f1,$f1 */
	.word	0x004D1021  /* 0010DECC addu $v0,$v0,$t5 */
	.word	0x80430000  /* 0010DED0 lb $v1,0($v0) */
	.word	0x44830000  /* 0010DED4 mtc1 $v1,$f0 */
	.word	0x46800020  /* 0010DED8 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010DEDC mul.s $f0,$f0,$f22 */
	.word	0x46050000  /* 0010DEE0 add.s $f0,$f0,$f5 */
	.word	0x46000840  /* 0010DEE4 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010DEE8 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010DEEC mfc1 $s0,$f0 */
	.word	0x96420008  /* 0010DEF0 lhu $v0,8($s2) */
	.word	0x02021023  /* 0010DEF4 subu $v0,$s0,$v0 */
	.word	0x1000001A  /* 0010DEF8 b .L0010DF64 */
	.word	0xA4A20008  /* 0010DEFC sh $v0,8($a1) */
	.word	0x028B1821  /* 0010DF00 addu $v1,$s4,$t3 */
	.word	0x44900800  /* 0010DF04 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010DF08 cvt.s.w $f1,$f1 */
	.word	0x006D1821  /* 0010DF0C addu $v1,$v1,$t5 */
	.word	0x3C014F00  /* 0010DF10 lui $at,0x4f00 */
	.word	0x44811000  /* 0010DF14 mtc1 $at,$f2 */
	.word	0x80620000  /* 0010DF18 lb $v0,0($v1) */
	.word	0x44820000  /* 0010DF1C mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010DF20 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010DF24 mul.s $f0,$f0,$f22 */
	.word	0x46002001  /* 0010DF28 sub.s $f0,$f4,$f0 */
	.word	0x46030002  /* 0010DF2C mul.s $f0,$f0,$f3 */
	.word	0x46000800  /* 0010DF30 add.s $f0,$f1,$f0 */
	.word	0x46001036  /* 0010DF34 c.le.s $f2,$f0 */
	.word	0x46000064  /* 0010DF38 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010DF3C mfc1 $v1,$f1 */
	.word	0x45020006  /* 0010DF40 bc1fl .L0010DF5C */
	.word	0x8C820000  /* 0010DF44 lw $v0,0($a0) */
	.word	0x46020001  /* 0010DF48 sub.s $f0,$f0,$f2 */
	.word	0x46000064  /* 0010DF4C trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010DF50 mfc1 $v1,$f1 */
	.word	0x006E1825  /* 0010DF54 or $v1,$v1,$t6 */
	.word	0x8C820000  /* 0010DF58 lw $v0,0($a0) */
	.word	0xA4E30004  /* 0010DF5C sh $v1,4($a3) */
	.word	0x02028021  /* 0010DF60 addu $s0,$s0,$v0 */
	.word	0x01861021  /* 0010DF64 addu $v0,$t4,$a2 */
	.word	0x24C60010  /* 0010DF68 addiu $a2,$a2,16 */
	.word	0xA4B60006  /* 0010DF6C sh $s6,6($a1) */
	.word	0x4614AD40  /* 0010DF70 add.s $f21,$f21,$f20 */
	.word	0xA4BE0002  /* 0010DF74 sh $s8,2($a1) */
	.word	0x26F70001  /* 0010DF78 addiu $s7,$s7,1 */
	.word	0xE4540000  /* 0010DF7C swc1 $f20,0($v0) */
	.word	0x8FA20050  /* 0010DF80 lw $v0,80($sp) */
	.word	0xA4A2000A  /* 0010DF84 sh $v0,10($a1) */
	.word	0x254A0001  /* 0010DF88 addiu $t2,$t2,1 */
	.word	0x02AA1021  /* 0010DF8C addu $v0,$s5,$t2 */
	.word	0x90480000  /* 0010DF90 lbu $t0,0($v0) */
	.word	0x1500FF5E  /* 0010DF94 bnez $t0,.L0010DD10 */
	.word	0x24A50010  /* 0010DF98 addiu $a1,$a1,16 */
	.word	0x100000EC  /* 0010DF9C b .L0010E350 */
	.word	0x8FA50048  /* 0010DFA0 lw $a1,72($sp) */
	.word	0x00000000  /* 0010DFA4 nop */
	.word	0x8FA20040  /* 0010DFA8 lw $v0,64($sp) */
	.word	0x240300FF  /* 0010DFAC li $v1,255 */
	.word	0x24490001  /* 0010DFB0 addiu $t1,$v0,1 */
	.word	0xAFA90040  /* 0010DFB4 sw $t1,64($sp) */
	.word	0x02691021  /* 0010DFB8 addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010DFBC lbu $a3,0($v0) */
	.word	0x14E300E2  /* 0010DFC0 bne $a3,$v1,.L0010E34C */
	.word	0x00E0F02D  /* 0010DFC4 move $s8,$a3 */
	.word	0x100000E0  /* 0010DFC8 b .L0010E34C */
	.word	0x925E0010  /* 0010DFCC lbu $s8,16($s2) */
	.word	0x24030001  /* 0010DFD0 li $v1,1 */
	.word	0x8FA90040  /* 0010DFD4 lw $t1,64($sp) */
	.word	0x100000DC  /* 0010DFD8 b .L0010E34C */
	.word	0xAFA3004C  /* 0010DFDC sw $v1,76($sp) */
	.word	0x8FA20040  /* 0010DFE0 lw $v0,64($sp) */
	.word	0x24030001  /* 0010DFE4 li $v1,1 */
	.word	0x24490001  /* 0010DFE8 addiu $t1,$v0,1 */
	.word	0xAFA90040  /* 0010DFEC sw $t1,64($sp) */
	.word	0x02691021  /* 0010DFF0 addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010DFF4 lbu $a3,0($v0) */
	.word	0x10E300D4  /* 0010DFF8 beq $a3,$v1,.L0010E34C */
	.word	0x28E20002  /* 0010DFFC slti $v0,$a3,2 */
	.word	0x50400005  /* 0010E000 beqzl $v0,.L0010E018 */
	.word	0x24020002  /* 0010E004 li $v0,2 */
	.word	0x10E00009  /* 0010E008 beqz $a3,.L0010E030 */
	.word	0x8FA50048  /* 0010E00C lw $a1,72($sp) */
	.word	0x100000D0  /* 0010E010 b .L0010E354 */
	.word	0x25290001  /* 0010E014 addiu $t1,$t1,1 */
	.word	0x10E20009  /* 0010E018 beq $a3,$v0,.L0010E040 */
	.word	0x24020003  /* 0010E01C li $v0,3 */
	.word	0x10E2000B  /* 0010E020 beq $a3,$v0,.L0010E050 */
	.word	0x8FA50048  /* 0010E024 lw $a1,72($sp) */
	.word	0x100000CA  /* 0010E028 b .L0010E354 */
	.word	0x25290001  /* 0010E02C addiu $t1,$t1,1 */
	.word	0x24040002  /* 0010E030 li $a0,2 */
	.word	0x100000C5  /* 0010E034 b .L0010E34C */
	.word	0xAFA4004C  /* 0010E038 sw $a0,76($sp) */
	.word	0x00000000  /* 0010E03C nop */
	.word	0x3C050000  /* 0010E040 lui $a1,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x100000C1  /* 0010E044 b .L0010E34C */
	.word	0xACA30000  /* 0010E048 sw $v1,%lo(D_004D59E4)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x00000000  /* 0010E04C nop */
	.word	0x3C060000  /* 0010E050 lui $a2,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x100000BD  /* 0010E054 b .L0010E34C */
	.word	0xACC00000  /* 0010E058 sw $zero,%lo(D_004D59E4)($a2) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x00000000  /* 0010E05C nop */
	.word	0x8FA20040  /* 0010E060 lw $v0,64($sp) */
	.word	0x00172100  /* 0010E064 sll $a0,$s7,0x4 */
	.word	0x24840010  /* 0010E068 addiu $a0,$a0,16 */
	.word	0x4614AD40  /* 0010E06C add.s $f21,$f21,$f20 */
	.word	0x24490001  /* 0010E070 addiu $t1,$v0,1 */
	.word	0x02242821  /* 0010E074 addu $a1,$s1,$a0 */
	.word	0xAFA90040  /* 0010E078 sw $t1,64($sp) */
	.word	0x02691021  /* 0010E07C addu $v0,$s3,$t1 */
	.word	0x00A0202D  /* 0010E080 move $a0,$a1 */
	.word	0x26F70001  /* 0010E084 addiu $s7,$s7,1 */
	.word	0x90470000  /* 0010E088 lbu $a3,0($v0) */
	.word	0xA4B00004  /* 0010E08C sh $s0,4($a1) */
	.word	0x24F42710  /* 0010E090 addiu $s4,$a3,10000 */
	.word	0xA4B40000  /* 0010E094 sh $s4,0($a1) */
	.word	0x3C030000  /* 0010E098 lui $v1,%hi(D_002BB610) */
	.reloc	.-4, R_MIPS_HI16, D_002BB610
	.word	0x00671821  /* 0010E09C addu $v1,$v1,$a3 */
	.word	0x80630000  /* 0010E0A0 lb $v1,%lo(D_002BB610)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_002BB610
	.word	0xE494000C  /* 0010E0A4 swc1 $f20,12($a0) */
	.word	0x96420008  /* 0010E0A8 lhu $v0,8($s2) */
	.word	0x02038021  /* 0010E0AC addu $s0,$s0,$v1 */
	.word	0x8FA30050  /* 0010E0B0 lw $v1,80($sp) */
	.word	0x02021023  /* 0010E0B4 subu $v0,$s0,$v0 */
	.word	0xA4B60006  /* 0010E0B8 sh $s6,6($a1) */
	.word	0xA4A3000A  /* 0010E0BC sh $v1,10($a1) */
	.word	0xA4A20008  /* 0010E0C0 sh $v0,8($a1) */
	.word	0x100000A1  /* 0010E0C4 b .L0010E34C */
	.word	0xA4BE0002  /* 0010E0C8 sh $s8,2($a1) */
	.word	0x00000000  /* 0010E0CC nop */
	.word	0x8FA40040  /* 0010E0D0 lw $a0,64($sp) */
	.word	0x24890001  /* 0010E0D4 addiu $t1,$a0,1 */
	.word	0xAFA90040  /* 0010E0D8 sw $t1,64($sp) */
	.word	0x02691021  /* 0010E0DC addu $v0,$s3,$t1 */
	.word	0x90470000  /* 0010E0E0 lbu $a3,0($v0) */
	.word	0x54E00099  /* 0010E0E4 bnezl $a3,.L0010E34C */
	.word	0xC6540014  /* 0010E0E8 lwc1 $f20,20($s2) */
	.word	0x24890002  /* 0010E0EC addiu $t1,$a0,2 */
	.word	0x2403000A  /* 0010E0F0 li $v1,10 */
	.word	0x02691021  /* 0010E0F4 addu $v0,$s3,$t1 */
	.word	0xAFA90040  /* 0010E0F8 sw $t1,64($sp) */
	.word	0x50600001  /* 0010E0FC beqzl $v1,.L0010E104 */
	.word	0x000001CD  /* 0010E100 break 0x0,0x7 */
	.word	0x90470000  /* 0010E104 lbu $a3,0($v0) */
	.word	0x24890003  /* 0010E108 addiu $t1,$a0,3 */
	.word	0x44801000  /* 0010E10C mtc1 $zero,$f2 */
	.word	0x00E3001B  /* 0010E110 divu $zero,$a3,$v1 */
	.word	0xAFA90040  /* 0010E114 sw $t1,64($sp) */
	.word	0x02692021  /* 0010E118 addu $a0,$s3,$t1 */
	.word	0x90870000  /* 0010E11C lbu $a3,0($a0) */
	.word	0x44870800  /* 0010E120 mtc1 $a3,$f1 */
	.word	0x46800860  /* 0010E124 cvt.s.w $f1,$f1 */
	.word	0x00001812  /* 0010E128 mflo $v1 */
	.word	0x44830000  /* 0010E12C mtc1 $v1,$f0 */
	.word	0x46800020  /* 0010E130 cvt.s.w $f0,$f0 */
	.word	0x46000D00  /* 0010E134 add.s $f20,$f1,$f0 */
	.word	0x4602A032  /* 0010E138 c.eq.s $f20,$f2 */
	.word	0x45000084  /* 0010E13C bc1f .L0010E350 */
	.word	0x8FA50048  /* 0010E140 lw $a1,72($sp) */
	.word	0x3C013586  /* 0010E144 lui $at,0x3586 */
	.word	0x342137BD  /* 0010E148 ori $at,$at,0x37bd */
	.word	0x4481A000  /* 0010E14C mtc1 $at,$f20 */
	.word	0x10000080  /* 0010E150 b .L0010E354 */
	.word	0x25290001  /* 0010E154 addiu $t1,$t1,1 */
	.word	0x8FA30040  /* 0010E158 lw $v1,64($sp) */
	.word	0x00172900  /* 0010E15C sll $a1,$s7,0x4 */
	.word	0x24A20010  /* 0010E160 addiu $v0,$a1,16 */
	.word	0x24690001  /* 0010E164 addiu $t1,$v1,1 */
	.word	0x02222021  /* 0010E168 addu $a0,$s1,$v0 */
	.word	0xAFA90040  /* 0010E16C sw $t1,64($sp) */
	.word	0x02691021  /* 0010E170 addu $v0,$s3,$t1 */
	.word	0x90480000  /* 0010E174 lbu $t0,0($v0) */
	.word	0x250300E7  /* 0010E178 addiu $v1,$t0,231 */
	.word	0x306800FF  /* 0010E17C andi $t0,$v1,0xff */
	.word	0x3C030000  /* 0010E180 lui $v1,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x00081200  /* 0010E184 sll $v0,$t0,0x8 */
	.word	0x244200E0  /* 0010E188 addiu $v0,$v0,224 */
	.word	0x3054FFFF  /* 0010E18C andi $s4,$v0,0xffff */
	.word	0xA4940000  /* 0010E190 sh $s4,0($a0) */
	.word	0x8C620000  /* 0010E194 lw $v0,%lo(D_004D59E4)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x14400041  /* 0010E198 bnez $v0,.L0010E2A0 */
	.word	0x24020020  /* 0010E19C li $v0,32 */
	.word	0x1502002D  /* 0010E1A0 bne $t0,$v0,.L0010E258 */
	.word	0xA4900004  /* 0010E1A4 sh $s0,4($a0) */
	.word	0x3C020000  /* 0010E1A8 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010E1AC addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010E1B0 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44900800  /* 0010E1B4 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010E1B8 cvt.s.w $f1,$f1 */
	.word	0x44820000  /* 0010E1BC mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010E1C0 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010E1C4 mul.s $f0,$f0,$f22 */
	.word	0x46000840  /* 0010E1C8 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010E1CC trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010E1D0 mfc1 $s0,$f0 */
	.word	0x1000002E  /* 0010E1D4 b .L0010E290 */
	.word	0x96420008  /* 0010E1D8 lhu $v0,8($s2) */
	.word	0x00000000  /* 0010E1DC nop */
	.word	0x8FA30040  /* 0010E1E0 lw $v1,64($sp) */
	.word	0x250200E7  /* 0010E1E4 addiu $v0,$t0,231 */
	.word	0x304800FF  /* 0010E1E8 andi $t0,$v0,0xff */
	.word	0x00172900  /* 0010E1EC sll $a1,$s7,0x4 */
	.word	0x24690001  /* 0010E1F0 addiu $t1,$v1,1 */
	.word	0x00081200  /* 0010E1F4 sll $v0,$t0,0x8 */
	.word	0xAFA90040  /* 0010E1F8 sw $t1,64($sp) */
	.word	0x02691821  /* 0010E1FC addu $v1,$s3,$t1 */
	.word	0x24A40010  /* 0010E200 addiu $a0,$a1,16 */
	.word	0x3C060000  /* 0010E204 lui $a2,%hi(D_004D59E4) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E4
	.word	0x90670000  /* 0010E208 lbu $a3,0($v1) */
	.word	0x02242021  /* 0010E20C addu $a0,$s1,$a0 */
	.word	0x00471021  /* 0010E210 addu $v0,$v0,$a3 */
	.word	0x244200E0  /* 0010E214 addiu $v0,$v0,224 */
	.word	0x3054FFFF  /* 0010E218 andi $s4,$v0,0xffff */
	.word	0xA4940000  /* 0010E21C sh $s4,0($a0) */
	.word	0x8CC20000  /* 0010E220 lw $v0,%lo(D_004D59E4)($a2) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E4
	.word	0x1440001E  /* 0010E224 bnez $v0,.L0010E2A0 */
	.word	0x24020020  /* 0010E228 li $v0,32 */
	.word	0x1502000A  /* 0010E22C bne $t0,$v0,.L0010E258 */
	.word	0xA4900004  /* 0010E230 sh $s0,4($a0) */
	.word	0x3C020000  /* 0010E234 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010E238 addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010E23C lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44900800  /* 0010E240 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010E244 cvt.s.w $f1,$f1 */
	.word	0x44820000  /* 0010E248 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010E24C cvt.s.w $f0,$f0 */
	.word	0x1000000B  /* 0010E250 b .L0010E280 */
	.word	0x46160002  /* 0010E254 mul.s $f0,$f0,$f22 */
	.word	0x3C020000  /* 0010E258 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010E25C addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010E260 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44900800  /* 0010E264 mtc1 $s0,$f1 */
	.word	0x46800860  /* 0010E268 cvt.s.w $f1,$f1 */
	.word	0x44801000  /* 0010E26C mtc1 $zero,$f2 */
	.word	0x44820000  /* 0010E270 mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010E274 cvt.s.w $f0,$f0 */
	.word	0x46160002  /* 0010E278 mul.s $f0,$f0,$f22 */
	.word	0x46020000  /* 0010E27C add.s $f0,$f0,$f2 */
	.word	0x46000840  /* 0010E280 add.s $f1,$f1,$f0 */
	.word	0x46000824  /* 0010E284 trunc.w.s $f0,$f1 */
	.word	0x44100000  /* 0010E288 mfc1 $s0,$f0 */
	.word	0x96420008  /* 0010E28C lhu $v0,8($s2) */
	.word	0x00B11821  /* 0010E290 addu $v1,$a1,$s1 */
	.word	0x02021023  /* 0010E294 subu $v0,$s0,$v0 */
	.word	0x10000020  /* 0010E298 b .L0010E31C */
	.word	0xA4620018  /* 0010E29C sh $v0,24($v1) */
	.word	0x3C020000  /* 0010E2A0 lui $v0,%hi(D_004D5300) */
	.reloc	.-4, R_MIPS_HI16, D_004D5300
	.word	0x00541021  /* 0010E2A4 addu $v0,$v0,$s4 */
	.word	0x80420000  /* 0010E2A8 lb $v0,%lo(D_004D5300)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_004D5300
	.word	0x44901800  /* 0010E2AC mtc1 $s0,$f3 */
	.word	0x468018E0  /* 0010E2B0 cvt.s.w $f3,$f3 */
	.word	0x3C0141C0  /* 0010E2B4 lui $at,0x41c0 */
	.word	0x44810800  /* 0010E2B8 mtc1 $at,$f1 */
	.word	0x44820000  /* 0010E2BC mtc1 $v0,$f0 */
	.word	0x46800020  /* 0010E2C0 cvt.s.w $f0,$f0 */
	.word	0x3C013F00  /* 0010E2C4 lui $at,0x3f00 */
	.word	0x44811000  /* 0010E2C8 mtc1 $at,$f2 */
	.word	0x3C014F00  /* 0010E2CC lui $at,0x4f00 */
	.word	0x44812000  /* 0010E2D0 mtc1 $at,$f4 */
	.word	0x46160002  /* 0010E2D4 mul.s $f0,$f0,$f22 */
	.word	0x46000841  /* 0010E2D8 sub.s $f1,$f1,$f0 */
	.word	0x46020842  /* 0010E2DC mul.s $f1,$f1,$f2 */
	.word	0x46011800  /* 0010E2E0 add.s $f0,$f3,$f1 */
	.word	0x46002036  /* 0010E2E4 c.le.s $f4,$f0 */
	.word	0x46000064  /* 0010E2E8 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010E2EC mfc1 $v1,$f1 */
	.word	0x45020007  /* 0010E2F0 bc1fl .L0010E310 */
	.word	0xA4830004  /* 0010E2F4 sh $v1,4($a0) */
	.word	0x46040001  /* 0010E2F8 sub.s $f0,$f0,$f4 */
	.word	0x3C028000  /* 0010E2FC lui $v0,0x8000 */
	.word	0x46000064  /* 0010E300 trunc.w.s $f1,$f0 */
	.word	0x44030800  /* 0010E304 mfc1 $v1,$f1 */
	.word	0x00621825  /* 0010E308 or $v1,$v1,$v0 */
	.word	0xA4830004  /* 0010E30C sh $v1,4($a0) */
	.word	0x3C030000  /* 0010E310 lui $v1,%hi(D_004D59E8) */
	.reloc	.-4, R_MIPS_HI16, D_004D59E8
	.word	0x8C620000  /* 0010E314 lw $v0,%lo(D_004D59E8)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_004D59E8
	.word	0x02028021  /* 0010E318 addu $s0,$s0,$v0 */
	.word	0x24A20010  /* 0010E31C addiu $v0,$a1,16 */
	.word	0x8FA40050  /* 0010E320 lw $a0,80($sp) */
	.word	0x02221821  /* 0010E324 addu $v1,$s1,$v0 */
	.word	0x4614AD40  /* 0010E328 add.s $f21,$f21,$f20 */
	.word	0x0060102D  /* 0010E32C move $v0,$v1 */
	.word	0x26F70001  /* 0010E330 addiu $s7,$s7,1 */
	.word	0xA444000A  /* 0010E334 sh $a0,10($v0) */
	.word	0xE474000C  /* 0010E338 swc1 $f20,12($v1) */
	.word	0xA4560006  /* 0010E33C sh $s6,6($v0) */
	.word	0x10000002  /* 0010E340 b .L0010E34C */
	.word	0xA45E0002  /* 0010E344 sh $s8,2($v0) */
	.word	0x8FA90040  /* 0010E348 lw $t1,64($sp) */
	.word	0x8FA50048  /* 0010E34C lw $a1,72($sp) */
	.word	0x25290001  /* 0010E350 addiu $t1,$t1,1 */
	.word	0x14A0FC88  /* 0010E354 bnez $a1,.L0010D578 */
	.word	0xAFA90040  /* 0010E358 sw $t1,64($sp) */
	.word	0xA6370000  /* 0010E35C sh $s7,0($s1) */
	.word	0x24020001  /* 0010E360 li $v0,1 */
	.word	0x8FA60044  /* 0010E364 lw $a2,68($sp) */
	.word	0xE6350004  /* 0010E368 swc1 $f21,4($s1) */
	.word	0xA6260002  /* 0010E36C sh $a2,2($s1) */
	.word	0xAE200008  /* 0010E370 sw $zero,8($s1) */
	.word	0x8FA3004C  /* 0010E374 lw $v1,76($sp) */
	.word	0x10620005  /* 0010E378 beq $v1,$v0,.L0010E390 */
	.word	0x24020002  /* 0010E37C li $v0,2 */
	.word	0x10620009  /* 0010E380 beq $v1,$v0,.L0010E3A8 */
	.word	0xDFB00060  /* 0010E384 ld $s0,96($sp) */
	.word	0x1000000C  /* 0010E388 b .L0010E3BC */
	.word	0xDFB10068  /* 0010E38C ld $s1,104($sp) */
	.word	0x0240202D  /* 0010E390 move $a0,$s2 */
	.word	0x0C000000  /* 0010E394 jal func_0010d138 */
	.reloc	.-4, R_MIPS_26, func_0010d138
	.word	0x0220282D  /* 0010E398 move $a1,$s1 */
	.word	0x10000006  /* 0010E39C b .L0010E3B8 */
	.word	0xDFB00060  /* 0010E3A0 ld $s0,96($sp) */
	.word	0x00000000  /* 0010E3A4 nop */
	.word	0x0240202D  /* 0010E3A8 move $a0,$s2 */
	.word	0x0C000000  /* 0010E3AC jal func_0010d230 */
	.reloc	.-4, R_MIPS_26, func_0010d230
	.word	0x0220282D  /* 0010E3B0 move $a1,$s1 */
	.word	0xDFB00060  /* 0010E3B4 ld $s0,96($sp) */
	.word	0xDFB10068  /* 0010E3B8 ld $s1,104($sp) */
	.word	0xDFB20070  /* 0010E3BC ld $s2,112($sp) */
	.word	0xDFB30078  /* 0010E3C0 ld $s3,120($sp) */
	.word	0xDFB40080  /* 0010E3C4 ld $s4,128($sp) */
	.word	0xDFB50088  /* 0010E3C8 ld $s5,136($sp) */
	.word	0xDFB60090  /* 0010E3CC ld $s6,144($sp) */
	.word	0xDFB70098  /* 0010E3D0 ld $s7,152($sp) */
	.word	0xDFBE00A0  /* 0010E3D4 ld $s8,160($sp) */
	.word	0xDFBF00A8  /* 0010E3D8 ld $ra,168($sp) */
	.word	0xC7B600C0  /* 0010E3DC lwc1 $f22,192($sp) */
	.word	0xC7B500B8  /* 0010E3E0 lwc1 $f21,184($sp) */
	.word	0xC7B400B0  /* 0010E3E4 lwc1 $f20,176($sp) */
	.word	0x03E00008  /* 0010E3E8 jr $ra */
	.word	0x27BD00D0  /* 0010E3EC addiu $sp,$sp,208 */
	.end	func_0010d470
