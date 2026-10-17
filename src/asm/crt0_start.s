/* Startup code (crt0 _start, game segment): clears every GPR/FPR/HI/LO/SA with MMI and COP1 moves, sets up the stack and calls the init syscalls. Assembly in the original. Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.func_00100008,"ax",@progbits
	.globl	func_00100008
	.ent	func_00100008
func_00100008:  /* 0x00100008 */
	.word	0x70000C28  /* 00100008 padduw $at,$zero,$zero */
	.word	0x70001428  /* 0010000C padduw $v0,$zero,$zero */
	.word	0x70001C28  /* 00100010 padduw $v1,$zero,$zero */
	.word	0x70002428  /* 00100014 padduw $a0,$zero,$zero */
	.word	0x70002C28  /* 00100018 padduw $a1,$zero,$zero */
	.word	0x70003428  /* 0010001C padduw $a2,$zero,$zero */
	.word	0x70003C28  /* 00100020 padduw $a3,$zero,$zero */
	.word	0x70004428  /* 00100024 padduw $t0,$zero,$zero */
	.word	0x70004C28  /* 00100028 padduw $t1,$zero,$zero */
	.word	0x70005428  /* 0010002C padduw $t2,$zero,$zero */
	.word	0x70005C28  /* 00100030 padduw $t3,$zero,$zero */
	.word	0x70006428  /* 00100034 padduw $t4,$zero,$zero */
	.word	0x70006C28  /* 00100038 padduw $t5,$zero,$zero */
	.word	0x70007428  /* 0010003C padduw $t6,$zero,$zero */
	.word	0x70007C28  /* 00100040 padduw $t7,$zero,$zero */
	.word	0x70008428  /* 00100044 padduw $s0,$zero,$zero */
	.word	0x70008C28  /* 00100048 padduw $s1,$zero,$zero */
	.word	0x70009428  /* 0010004C padduw $s2,$zero,$zero */
	.word	0x70009C28  /* 00100050 padduw $s3,$zero,$zero */
	.word	0x7000A428  /* 00100054 padduw $s4,$zero,$zero */
	.word	0x7000AC28  /* 00100058 padduw $s5,$zero,$zero */
	.word	0x7000B428  /* 0010005C padduw $s6,$zero,$zero */
	.word	0x7000BC28  /* 00100060 padduw $s7,$zero,$zero */
	.word	0x7000C428  /* 00100064 padduw $t8,$zero,$zero */
	.word	0x7000CC28  /* 00100068 padduw $t9,$zero,$zero */
	.word	0x7000E428  /* 0010006C padduw $gp,$zero,$zero */
	.word	0x7000EC28  /* 00100070 padduw $sp,$zero,$zero */
	.word	0x7000F428  /* 00100074 padduw $s8,$zero,$zero */
	.word	0x7000FC28  /* 00100078 padduw $ra,$zero,$zero */
	.word	0x00000011  /* 0010007C mthi $zero */
	.word	0x70000011  /* 00100080 mthi1 $zero */
	.word	0x00000013  /* 00100084 mtlo $zero */
	.word	0x70000013  /* 00100088 mtlo1 $zero */
	.word	0x04190000  /* 0010008C mtsah $zero,0 */
	.word	0x44800000  /* 00100090 mtc1 $zero,$f0 */
	.word	0x44800800  /* 00100094 mtc1 $zero,$f1 */
	.word	0x44801000  /* 00100098 mtc1 $zero,$f2 */
	.word	0x44801800  /* 0010009C mtc1 $zero,$f3 */
	.word	0x44802000  /* 001000A0 mtc1 $zero,$f4 */
	.word	0x44802800  /* 001000A4 mtc1 $zero,$f5 */
	.word	0x44803000  /* 001000A8 mtc1 $zero,$f6 */
	.word	0x44803800  /* 001000AC mtc1 $zero,$f7 */
	.word	0x44804000  /* 001000B0 mtc1 $zero,$f8 */
	.word	0x44804800  /* 001000B4 mtc1 $zero,$f9 */
	.word	0x44805000  /* 001000B8 mtc1 $zero,$f10 */
	.word	0x44805800  /* 001000BC mtc1 $zero,$f11 */
	.word	0x44806000  /* 001000C0 mtc1 $zero,$f12 */
	.word	0x44806800  /* 001000C4 mtc1 $zero,$f13 */
	.word	0x44807000  /* 001000C8 mtc1 $zero,$f14 */
	.word	0x44807800  /* 001000CC mtc1 $zero,$f15 */
	.word	0x44808000  /* 001000D0 mtc1 $zero,$f16 */
	.word	0x44808800  /* 001000D4 mtc1 $zero,$f17 */
	.word	0x44809000  /* 001000D8 mtc1 $zero,$f18 */
	.word	0x44809800  /* 001000DC mtc1 $zero,$f19 */
	.word	0x4480A000  /* 001000E0 mtc1 $zero,$f20 */
	.word	0x4480A800  /* 001000E4 mtc1 $zero,$f21 */
	.word	0x4480B000  /* 001000E8 mtc1 $zero,$f22 */
	.word	0x4480B800  /* 001000EC mtc1 $zero,$f23 */
	.word	0x4480C000  /* 001000F0 mtc1 $zero,$f24 */
	.word	0x4480C800  /* 001000F4 mtc1 $zero,$f25 */
	.word	0x4480D000  /* 001000F8 mtc1 $zero,$f26 */
	.word	0x4480D800  /* 001000FC mtc1 $zero,$f27 */
	.word	0x4480E000  /* 00100100 mtc1 $zero,$f28 */
	.word	0x4480E800  /* 00100104 mtc1 $zero,$f29 */
	.word	0x4480F000  /* 00100108 mtc1 $zero,$f30 */
	.word	0x4480F800  /* 0010010C mtc1 $zero,$f31 */
	.word	0x46010018  /* 00100110 adda.s $f0,$f1 */
	.word	0x0000040F  /* 00100114 sync.p */
	.word	0x44C0F800  /* 00100118 ctc1 $zero,c1_fcsr */
	.word	0x3C020049  /* 0010011C lui $v0,%hi(D_00494050) */
	.word	0x3C030067  /* 00100120 lui $v1,%hi(D_00675018) */
	.word	0x24424050  /* 00100124 addiu $v0,$v0,%lo(D_00494050) */
	.word	0x24635018  /* 00100128 addiu $v1,$v1,%lo(D_00675018) */
	.word	0x7C400000  /* 0010012C sq $zero,0($v0) */
	.word	0x00000000  /* 00100130 nop */
	.word	0x0043082B  /* 00100134 sltu $at,$v0,$v1 */
	.word	0x00000000  /* 00100138 nop */
	.word	0x00000000  /* 0010013C nop */
	.word	0x1420FFFA  /* 00100140 bnez $at,.L0010012C */
	.word	0x24420010  /* 00100144 addiu $v0,$v0,16 */
	.word	0x3C040049  /* 00100148 lui $a0,%hi(D_00494050) */
	.word	0x3C0501FE  /* 0010014C lui $a1,%hi(D_01FE0000) */
	.word	0x3C060002  /* 00100150 lui $a2,0x2 */
	.word	0x3C070049  /* 00100154 lui $a3,%hi(D_00494080) */
	.word	0x3C080010  /* 00100158 lui $t0,%hi(func_001001d0) */
	.word	0x24844050  /* 0010015C addiu $a0,$a0,%lo(D_00494050) */
	.word	0x24A50000  /* 00100160 addiu $a1,$a1,%lo(D_01FE0000) */
	.word	0x24C60000  /* 00100164 addiu $a2,$a2,0 */
	.word	0x24E74080  /* 00100168 addiu $a3,$a3,%lo(D_00494080) */
	.word	0x250801D0  /* 0010016C addiu $t0,$t0,%lo(func_001001d0) */
	.word	0x0080E02D  /* 00100170 move $gp,$a0 */
	.word	0x2403003C  /* 00100174 li $v1,60 */
	.word	0x0000000C  /* 00100178 syscall */
	.word	0x0040E82D  /* 0010017C move $sp,$v0 */
	.word	0x3C040067  /* 00100180 lui $a0,%hi(D_00675018) */
	.word	0x3C050001  /* 00100184 lui $a1,0x1 */
	.word	0x24845018  /* 00100188 addiu $a0,$a0,%lo(D_00675018) */
	.word	0x24A5A000  /* 0010018C addiu $a1,$a1,-24576 */
	.word	0x2403003D  /* 00100190 li $v1,61 */
	.word	0x0000000C  /* 00100194 syscall */
	.word	0x0C097D70  /* 00100198 jal func_0025f5c0 */
	.word	0x00000000  /* 0010019C nop */
	.word	0x0C0960F8  /* 001001A0 jal FlushCache */
	.word	0x0000202D  /* 001001A4 move $a0,$zero */
	.word	0x42000038  /* 001001A8 ei */
	.word	0x3C020049  /* 001001AC lui $v0,%hi(D_00494080) */
	.word	0x24424080  /* 001001B0 addiu $v0,$v0,%lo(D_00494080) */
	.word	0x8C440000  /* 001001B4 lw $a0,0($v0) */
	.word	0x0C040156  /* 001001B8 jal func_00100558 */
	.word	0x24450004  /* 001001BC addiu $a1,$v0,4 */
	.word	0x08097E6A  /* 001001C0 j func_0025f9a8 */
	.word	0x0040202D  /* 001001C4 move $a0,$v0 */
	.end	func_00100008
