/* func_001aa1f8 / func_001aa448: 128-bit block clears with sq $zero and MMI; func_001bfac8: thread context switch (saves and restores every GPR with sq). Hand-written assembly in the original. Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.func_001aa1f8,"ax",@progbits
	.globl	func_001aa1f8
	.ent	func_001aa1f8
func_001aa1f8:  /* 0x001AA1F8 */
	.word	0x27BDFF10  /* 001AA1F8 addiu $sp,$sp,-240 */
	.word	0xFFB100C8  /* 001AA1FC sd $s1,200($sp) */
	.word	0x00A0882D  /* 001AA200 move $s1,$a1 */
	.word	0x2A220011  /* 001AA204 slti $v0,$s1,17 */
	.word	0xFFB200D0  /* 001AA208 sd $s2,208($sp) */
	.word	0xFFB300D8  /* 001AA20C sd $s3,216($sp) */
	.word	0x0080982D  /* 001AA210 move $s3,$a0 */
	.word	0xFFB400E0  /* 001AA214 sd $s4,224($sp) */
	.word	0x00E0A02D  /* 001AA218 move $s4,$a3 */
	.word	0xFFB000C0  /* 001AA21C sd $s0,192($sp) */
	.word	0x30D2FFFF  /* 001AA220 andi $s2,$a2,0xffff */
	.word	0x1040004F  /* 001AA224 beqz $v0,.L001AA364 */
	.word	0xFFBF00E8  /* 001AA228 sd $ra,232($sp) */
	.word	0x0C000000  /* 001AA22C jal func_001aa950 */
	.reloc	.-4, R_MIPS_26, func_001aa950
	.word	0x24040800  /* 001AA230 li $a0,2048 */
	.word	0x00122C00  /* 001AA234 sll $a1,$s2,0x10 */
	.word	0x0040802D  /* 001AA238 move $s0,$v0 */
	.word	0x00052C03  /* 001AA23C sra $a1,$a1,0x10 */
	.word	0x0200202D  /* 001AA240 move $a0,$s0 */
	.word	0x24060001  /* 001AA244 li $a2,1 */
	.word	0x0000382D  /* 001AA248 move $a3,$zero */
	.word	0x0000402D  /* 001AA24C move $t0,$zero */
	.word	0x0000482D  /* 001AA250 move $t1,$zero */
	.word	0x240A0010  /* 001AA254 li $t2,16 */
	.word	0x0C000000  /* 001AA258 jal sceGsSetDefLoadImage */
	.reloc	.-4, R_MIPS_26, sceGsSetDefLoadImage
	.word	0x240B0010  /* 001AA25C li $t3,16 */
	.word	0x26030100  /* 001AA260 addiu $v1,$s0,256 */
	.word	0x3C023000  /* 001AA264 lui $v0,0x3000 */
	.word	0x34420005  /* 001AA268 ori $v0,$v0,0x5 */
	.word	0xAC620000  /* 001AA26C sw $v0,0($v1) */
	.word	0x3C028000  /* 001AA270 lui $v0,0x8000 */
	.word	0x02021021  /* 001AA274 addu $v0,$s0,$v0 */
	.word	0xAC620004  /* 001AA278 sw $v0,4($v1) */
	.word	0x0240282D  /* 001AA27C move $a1,$s2 */
	.word	0x0260202D  /* 001AA280 move $a0,$s3 */
	.word	0x1A20001C  /* 001AA284 blez $s1,.L001AA2F8 */
	.word	0x26030110  /* 001AA288 addiu $v1,$s0,272 */
	.word	0x0220302D  /* 001AA28C move $a2,$s1 */
	.word	0x3C081000  /* 001AA290 lui $t0,0x1000 */
	.word	0x0008403C  /* 001AA294 dsll32 $t0,$t0,0x0 */
	.word	0x35088001  /* 001AA298 ori $t0,$t0,0x8001 */
	.word	0x2407000E  /* 001AA29C li $a3,14 */
	.word	0x7C600000  /* 001AA2A0 sq $zero,0($v1) */
	.word	0x3C021000  /* 001AA2A4 lui $v0,0x1000 */
	.word	0x34420003  /* 001AA2A8 ori $v0,$v0,0x3 */
	.word	0xAC620000  /* 001AA2AC sw $v0,0($v1) */
	.word	0xFC680010  /* 001AA2B0 sd $t0,16($v1) */
	.word	0xFC670018  /* 001AA2B4 sd $a3,24($v1) */
	.word	0x7A020010  /* 001AA2B8 lq $v0,16($s0) */
	.word	0x7C620020  /* 001AA2BC sq $v0,32($v1) */
	.word	0xA4650024  /* 001AA2C0 sh $a1,36($v1) */
	.word	0x7A020050  /* 001AA2C4 lq $v0,80($s0) */
	.word	0x7C620030  /* 001AA2C8 sq $v0,48($v1) */
	.word	0x7C600040  /* 001AA2CC sq $zero,64($v1) */
	.word	0x3C023000  /* 001AA2D0 lui $v0,0x3000 */
	.word	0x34420040  /* 001AA2D4 ori $v0,$v0,0x40 */
	.word	0xAC620040  /* 001AA2D8 sw $v0,64($v1) */
	.word	0xAC640044  /* 001AA2DC sw $a0,68($v1) */
	.word	0x24A20004  /* 001AA2E0 addiu $v0,$a1,4 */
	.word	0x24C6FFFF  /* 001AA2E4 addiu $a2,$a2,-1 */
	.word	0x3045FFFF  /* 001AA2E8 andi $a1,$v0,0xffff */
	.word	0x24840400  /* 001AA2EC addiu $a0,$a0,1024 */
	.word	0x14C0FFEB  /* 001AA2F0 bnez $a2,.L001AA2A0 */
	.word	0x24630050  /* 001AA2F4 addiu $v1,$v1,80 */
	.word	0x7C600000  /* 001AA2F8 sq $zero,0($v1) */
	.word	0x3C027000  /* 001AA2FC lui $v0,0x7000 */
	.word	0xAC620000  /* 001AA300 sw $v0,0($v1) */
	.word	0x3C021001  /* 001AA304 lui $v0,%hi(D_1000A000) */
	.word	0x8C42A000  /* 001AA308 lw $v0,%lo(D_1000A000)($v0) */
	.word	0x30420100  /* 001AA30C andi $v0,$v0,0x100 */
	.word	0x00000000  /* 001AA310 nop */
	.word	0x00000000  /* 001AA314 nop */
	.word	0x00000000  /* 001AA318 nop */
	.word	0x1440FFF9  /* 001AA31C bnez $v0,.L001AA304 */
	.word	0x00000000  /* 001AA320 nop */
	.word	0x3C058000  /* 001AA324 lui $a1,0x8000 */
	.word	0x34A50100  /* 001AA328 ori $a1,$a1,0x100 */
	.word	0x02052821  /* 001AA32C addu $a1,$s0,$a1 */
	.word	0x3C021000  /* 001AA330 lui $v0,0x1000 */
	.word	0x34428000  /* 001AA334 ori $v0,$v0,0x8000 */
	.word	0x24030004  /* 001AA338 li $v1,4 */
	.word	0x24040105  /* 001AA33C li $a0,261 */
	.word	0xAC402020  /* 001AA340 sw $zero,8224($v0) */
	.word	0xAC452030  /* 001AA344 sw $a1,8240($v0) */
	.word	0x12800004  /* 001AA348 beqz $s4,.L001AA35C */
	.word	0xAC442000  /* 001AA34C sw $a0,8192($v0) */
	.word	0x0000202D  /* 001AA350 move $a0,$zero */
	.word	0x0C000000  /* 001AA354 jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000282D  /* 001AA358 move $a1,$zero */
	.word	0x0C000000  /* 001AA35C jal func_001aa9d0 */
	.reloc	.-4, R_MIPS_26, func_001aa9d0
	.word	0x24040800  /* 001AA360 li $a0,2048 */
	.word	0xDFB000C0  /* 001AA364 ld $s0,192($sp) */
	.word	0xDFB100C8  /* 001AA368 ld $s1,200($sp) */
	.word	0xDFB200D0  /* 001AA36C ld $s2,208($sp) */
	.word	0xDFB300D8  /* 001AA370 ld $s3,216($sp) */
	.word	0xDFB400E0  /* 001AA374 ld $s4,224($sp) */
	.word	0xDFBF00E8  /* 001AA378 ld $ra,232($sp) */
	.word	0x03E00008  /* 001AA37C jr $ra */
	.word	0x27BD00F0  /* 001AA380 addiu $sp,$sp,240 */
	.end	func_001aa1f8

	.section	.text.func_001aa448,"ax",@progbits
	.globl	func_001aa448
	.ent	func_001aa448
func_001aa448:  /* 0x001AA448 */
	.word	0x27BDFF00  /* 001AA448 addiu $sp,$sp,-256 */
	.word	0x0080102D  /* 001AA44C move $v0,$a0 */
	.word	0x24040C00  /* 001AA450 li $a0,3072 */
	.word	0xFFB000C0  /* 001AA454 sd $s0,192($sp) */
	.word	0xFFB100C8  /* 001AA458 sd $s1,200($sp) */
	.word	0x3051FFFF  /* 001AA45C andi $s1,$v0,0xffff */
	.word	0xFFB200D0  /* 001AA460 sd $s2,208($sp) */
	.word	0xFFB400E0  /* 001AA464 sd $s4,224($sp) */
	.word	0xFFB300D8  /* 001AA468 sd $s3,216($sp) */
	.word	0xFFB500E8  /* 001AA46C sd $s5,232($sp) */
	.word	0xFFB600F0  /* 001AA470 sd $s6,240($sp) */
	.word	0xFFBF00F8  /* 001AA474 sd $ra,248($sp) */
	.word	0x0C000000  /* 001AA478 jal func_001aa950 */
	.reloc	.-4, R_MIPS_26, func_001aa950
	.word	0x00A0A02D  /* 001AA47C move $s4,$a1 */
	.word	0x0040802D  /* 001AA480 move $s0,$v0 */
	.word	0x00112C00  /* 001AA484 sll $a1,$s1,0x10 */
	.word	0x0200202D  /* 001AA488 move $a0,$s0 */
	.word	0x00052C03  /* 001AA48C sra $a1,$a1,0x10 */
	.word	0x24060001  /* 001AA490 li $a2,1 */
	.word	0x0000382D  /* 001AA494 move $a3,$zero */
	.word	0x0000402D  /* 001AA498 move $t0,$zero */
	.word	0x0000482D  /* 001AA49C move $t1,$zero */
	.word	0x240A0010  /* 001AA4A0 li $t2,16 */
	.word	0x0C000000  /* 001AA4A4 jal sceGsSetDefLoadImage */
	.reloc	.-4, R_MIPS_26, sceGsSetDefLoadImage
	.word	0x240B0010  /* 001AA4A8 li $t3,16 */
	.word	0x26040800  /* 001AA4AC addiu $a0,$s0,2048 */
	.word	0x3C038000  /* 001AA4B0 lui $v1,0x8000 */
	.word	0x3C053000  /* 001AA4B4 lui $a1,0x3000 */
	.word	0x00839021  /* 001AA4B8 addu $s2,$a0,$v1 */
	.word	0x26040100  /* 001AA4BC addiu $a0,$s0,256 */
	.word	0x34A50005  /* 001AA4C0 ori $a1,$a1,0x5 */
	.word	0xAC850000  /* 001AA4C4 sw $a1,0($a0) */
	.word	0x02031821  /* 001AA4C8 addu $v1,$s0,$v1 */
	.word	0xAC830004  /* 001AA4CC sw $v1,4($a0) */
	.word	0x3C027FFF  /* 001AA4D0 lui $v0,0x7fff */
	.word	0x3C034444  /* 001AA4D4 lui $v1,0x4444 */
	.word	0x34634444  /* 001AA4D8 ori $v1,$v1,0x4444 */
	.word	0x00031C38  /* 001AA4DC dsll $v1,$v1,0x10 */
	.word	0x34634444  /* 001AA4E0 ori $v1,$v1,0x4444 */
	.word	0x00031C38  /* 001AA4E4 dsll $v1,$v1,0x10 */
	.word	0x34634444  /* 001AA4E8 ori $v1,$v1,0x4444 */
	.word	0x70601B89  /* 001AA4EC pcpyld $v1,$v1,$zero */
	.word	0x3C034444  /* 001AA4F0 lui $v1,0x4444 */
	.word	0x34634444  /* 001AA4F4 ori $v1,$v1,0x4444 */
	.word	0x00031C38  /* 001AA4F8 dsll $v1,$v1,0x10 */
	.word	0x34634444  /* 001AA4FC ori $v1,$v1,0x4444 */
	.word	0x00031C38  /* 001AA500 dsll $v1,$v1,0x10 */
	.word	0x34634444  /* 001AA504 ori $v1,$v1,0x4444 */
	.word	0x3442FFFF  /* 001AA508 ori $v0,$v0,0xffff */
	.word	0x240603F0  /* 001AA50C li $a2,1008 */
	.word	0x02421024  /* 001AA510 and $v0,$s2,$v0 */
	.word	0x244203F0  /* 001AA514 addiu $v0,$v0,1008 */
	.word	0x24C6FFF0  /* 001AA518 addiu $a2,$a2,-16 */
	.word	0x7C430000  /* 001AA51C sq $v1,0($v0) */
	.word	0x00000000  /* 001AA520 nop */
	.word	0x00000000  /* 001AA524 nop */
	.word	0x00000000  /* 001AA528 nop */
	.word	0x04C1FFFA  /* 001AA52C bgez $a2,.L001AA518 */
	.word	0x2442FFF0  /* 001AA530 addiu $v0,$v0,-16 */
	.word	0x0000982D  /* 001AA534 move $s3,$zero */
	.word	0x2696001F  /* 001AA538 addiu $s6,$s4,31 */
	.word	0x1000002F  /* 001AA53C b .L001AA5FC */
	.word	0x2A950000  /* 001AA540 slti $s5,$s4,0 */
	.word	0x00000000  /* 001AA544 nop */
	.word	0x0C000000  /* 001AA548 jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000282D  /* 001AA54C move $a1,$zero */
	.word	0x26040110  /* 001AA550 addiu $a0,$s0,272 */
	.word	0x3C082000  /* 001AA554 lui $t0,0x2000 */
	.word	0x0008403C  /* 001AA558 dsll32 $t0,$t0,0x0 */
	.word	0x35080001  /* 001AA55C ori $t0,$t0,0x1 */
	.word	0x3407EEEE  /* 001AA560 li $a3,0xeeee */
	.word	0x24060007  /* 001AA564 li $a2,7 */
	.word	0x7C800000  /* 001AA568 sq $zero,0($a0) */
	.word	0x3C051000  /* 001AA56C lui $a1,0x1000 */
	.word	0x34A50004  /* 001AA570 ori $a1,$a1,0x4 */
	.word	0xAC850000  /* 001AA574 sw $a1,0($a0) */
	.word	0xFC880010  /* 001AA578 sd $t0,16($a0) */
	.word	0xFC870018  /* 001AA57C sd $a3,24($a0) */
	.word	0x7A020010  /* 001AA580 lq $v0,16($s0) */
	.word	0x7C820020  /* 001AA584 sq $v0,32($a0) */
	.word	0x7A030040  /* 001AA588 lq $v1,64($s0) */
	.word	0x7C830030  /* 001AA58C sq $v1,48($a0) */
	.word	0xA4910024  /* 001AA590 sh $s1,36($a0) */
	.word	0x7A020050  /* 001AA594 lq $v0,80($s0) */
	.word	0x7C820040  /* 001AA598 sq $v0,64($a0) */
	.word	0x7C800050  /* 001AA59C sq $zero,80($a0) */
	.word	0x3C053000  /* 001AA5A0 lui $a1,0x3000 */
	.word	0x34A50040  /* 001AA5A4 ori $a1,$a1,0x40 */
	.word	0xAC850050  /* 001AA5A8 sw $a1,80($a0) */
	.word	0xAC920054  /* 001AA5AC sw $s2,84($a0) */
	.word	0x26220004  /* 001AA5B0 addiu $v0,$s1,4 */
	.word	0x24C6FFFF  /* 001AA5B4 addiu $a2,$a2,-1 */
	.word	0x3051FFFF  /* 001AA5B8 andi $s1,$v0,0xffff */
	.word	0x04C1FFEA  /* 001AA5BC bgez $a2,.L001AA568 */
	.word	0x24840060  /* 001AA5C0 addiu $a0,$a0,96 */
	.word	0x7C800000  /* 001AA5C4 sq $zero,0($a0) */
	.word	0x3C057000  /* 001AA5C8 lui $a1,0x7000 */
	.word	0xAC850000  /* 001AA5CC sw $a1,0($a0) */
	.word	0x3C058000  /* 001AA5D0 lui $a1,0x8000 */
	.word	0x34A50100  /* 001AA5D4 ori $a1,$a1,0x100 */
	.word	0x02052821  /* 001AA5D8 addu $a1,$s0,$a1 */
	.word	0x3C021000  /* 001AA5DC lui $v0,0x1000 */
	.word	0x34428000  /* 001AA5E0 ori $v0,$v0,0x8000 */
	.word	0x24030004  /* 001AA5E4 li $v1,4 */
	.word	0x24040105  /* 001AA5E8 li $a0,261 */
	.word	0xAC402020  /* 001AA5EC sw $zero,8224($v0) */
	.word	0xAC452030  /* 001AA5F0 sw $a1,8240($v0) */
	.word	0xAC442000  /* 001AA5F4 sw $a0,8192($v0) */
	.word	0x26730001  /* 001AA5F8 addiu $s3,$s3,1 */
	.word	0x0280102D  /* 001AA5FC move $v0,$s4 */
	.word	0x02D5100B  /* 001AA600 movn $v0,$s6,$s5 */
	.word	0x00021143  /* 001AA604 sra $v0,$v0,0x5 */
	.word	0x0262102A  /* 001AA608 slt $v0,$s3,$v0 */
	.word	0x5440FFCE  /* 001AA60C bnezl $v0,.L001AA548 */
	.word	0x0000202D  /* 001AA610 move $a0,$zero */
	.word	0x0000282D  /* 001AA614 move $a1,$zero */
	.word	0x0C000000  /* 001AA618 jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000202D  /* 001AA61C move $a0,$zero */
	.word	0x0C000000  /* 001AA620 jal func_001aa9d0 */
	.reloc	.-4, R_MIPS_26, func_001aa9d0
	.word	0x24040C00  /* 001AA624 li $a0,3072 */
	.word	0xDFB000C0  /* 001AA628 ld $s0,192($sp) */
	.word	0xDFB100C8  /* 001AA62C ld $s1,200($sp) */
	.word	0xDFB200D0  /* 001AA630 ld $s2,208($sp) */
	.word	0xDFB300D8  /* 001AA634 ld $s3,216($sp) */
	.word	0xDFB400E0  /* 001AA638 ld $s4,224($sp) */
	.word	0xDFB500E8  /* 001AA63C ld $s5,232($sp) */
	.word	0xDFB600F0  /* 001AA640 ld $s6,240($sp) */
	.word	0xDFBF00F8  /* 001AA644 ld $ra,248($sp) */
	.word	0x03E00008  /* 001AA648 jr $ra */
	.word	0x27BD0100  /* 001AA64C addiu $sp,$sp,256 */
	.end	func_001aa448

	.section	.text.func_001bfac8,"ax",@progbits
	.globl	func_001bfac8
	.ent	func_001bfac8
func_001bfac8:  /* 0x001BFAC8 */
	.word	0x3C040000  /* 001BFAC8 lui $a0,%hi(D_0037A170) */
	.reloc	.-4, R_MIPS_HI16, D_0037A170
	.word	0x8C840000  /* 001BFACC lw $a0,%lo(D_0037A170)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A170
	.word	0x3C020000  /* 001BFAD0 lui $v0,%hi(D_0037A164) */
	.reloc	.-4, R_MIPS_HI16, D_0037A164
	.word	0x8C420000  /* 001BFAD4 lw $v0,%lo(D_0037A164)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A164
	.word	0x000218C0  /* 001BFAD8 sll $v1,$v0,0x3 */
	.word	0x00832820  /* 001BFADC add $a1,$a0,$v1 */
	.word	0x8CA50000  /* 001BFAE0 lw $a1,0($a1) */
	.word	0x7CB00000  /* 001BFAE4 sq $s0,0($a1) */
	.word	0x7CB10010  /* 001BFAE8 sq $s1,16($a1) */
	.word	0x7CB20020  /* 001BFAEC sq $s2,32($a1) */
	.word	0x7CB30030  /* 001BFAF0 sq $s3,48($a1) */
	.word	0x7CB40040  /* 001BFAF4 sq $s4,64($a1) */
	.word	0x7CB50050  /* 001BFAF8 sq $s5,80($a1) */
	.word	0x7CB60060  /* 001BFAFC sq $s6,96($a1) */
	.word	0x7CB70070  /* 001BFB00 sq $s7,112($a1) */
	.word	0x7CB80080  /* 001BFB04 sq $t8,128($a1) */
	.word	0x7CB90090  /* 001BFB08 sq $t9,144($a1) */
	.word	0x7CBA00A0  /* 001BFB0C sq $k0,160($a1) */
	.word	0x7CBB00B0  /* 001BFB10 sq $k1,176($a1) */
	.word	0x7CBD00D0  /* 001BFB14 sq $sp,208($a1) */
	.word	0x7CBE00E0  /* 001BFB18 sq $s8,224($a1) */
	.word	0x7CBF00F0  /* 001BFB1C sq $ra,240($a1) */
	.word	0xE4B40100  /* 001BFB20 swc1 $f20,256($a1) */
	.word	0xE4B50104  /* 001BFB24 swc1 $f21,260($a1) */
	.word	0xE4B60108  /* 001BFB28 swc1 $f22,264($a1) */
	.word	0xE4B7010C  /* 001BFB2C swc1 $f23,268($a1) */
	.word	0xE4B80110  /* 001BFB30 swc1 $f24,272($a1) */
	.word	0xE4B90114  /* 001BFB34 swc1 $f25,276($a1) */
	.word	0xE4BA0118  /* 001BFB38 swc1 $f26,280($a1) */
	.word	0xE4BB011C  /* 001BFB3C swc1 $f27,284($a1) */
	.word	0xE4BC0120  /* 001BFB40 swc1 $f28,288($a1) */
	.word	0xE4BD0124  /* 001BFB44 swc1 $f29,292($a1) */
	.word	0xE4BE0128  /* 001BFB48 swc1 $f30,296($a1) */
	.word	0xE4BF012C  /* 001BFB4C swc1 $f31,300($a1) */
	.word	0x20420001  /* 001BFB50 addi $v0,$v0,1 */
	.word	0x000218C0  /* 001BFB54 sll $v1,$v0,0x3 */
	.word	0x00832820  /* 001BFB58 add $a1,$a0,$v1 */
	.word	0x8CA30004  /* 001BFB5C lw $v1,4($a1) */
	.word	0x8CA50000  /* 001BFB60 lw $a1,0($a1) */
	.word	0x14A0000D  /* 001BFB64 bnez $a1,.L001BFB9C */
	.word	0x00000000  /* 001BFB68 nop */
	.word	0x00000000  /* 001BFB6C nop */
	.word	0x8C850000  /* 001BFB70 lw $a1,0($a0) */
	.word	0x0C000000  /* 001BFB74 jal func_001c0460 */
	.reloc	.-4, R_MIPS_26, func_001c0460
	.word	0x78BD00D0  /* 001BFB78 lq $sp,208($a1) */
	.word	0x00000000  /* 001BFB7C nop */
	.word	0x3C040000  /* 001BFB80 lui $a0,%hi(D_0037A170) */
	.reloc	.-4, R_MIPS_HI16, D_0037A170
	.word	0x8C840000  /* 001BFB84 lw $a0,%lo(D_0037A170)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A170
	.word	0x20020000  /* 001BFB88 addi $v0,$zero,0 */
	.word	0x000218C0  /* 001BFB8C sll $v1,$v0,0x3 */
	.word	0x00832820  /* 001BFB90 add $a1,$a0,$v1 */
	.word	0x8CA30004  /* 001BFB94 lw $v1,4($a1) */
	.word	0x8CA50000  /* 001BFB98 lw $a1,0($a1) */
	.word	0x3C010000  /* 001BFB9C lui $at,%hi(D_0037A164) */
	.reloc	.-4, R_MIPS_HI16, D_0037A164
	.word	0xAC220000  /* 001BFBA0 sw $v0,%lo(D_0037A164)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0037A164
	.word	0x3C010000  /* 001BFBA4 lui $at,%hi(D_0037A168) */
	.reloc	.-4, R_MIPS_HI16, D_0037A168
	.word	0xAC230000  /* 001BFBA8 sw $v1,%lo(D_0037A168)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0037A168
	.word	0x78B00000  /* 001BFBAC lq $s0,0($a1) */
	.word	0x78B10010  /* 001BFBB0 lq $s1,16($a1) */
	.word	0x78B20020  /* 001BFBB4 lq $s2,32($a1) */
	.word	0x78B30030  /* 001BFBB8 lq $s3,48($a1) */
	.word	0x78B40040  /* 001BFBBC lq $s4,64($a1) */
	.word	0x78B50050  /* 001BFBC0 lq $s5,80($a1) */
	.word	0x78B60060  /* 001BFBC4 lq $s6,96($a1) */
	.word	0x78B70070  /* 001BFBC8 lq $s7,112($a1) */
	.word	0x78B80080  /* 001BFBCC lq $t8,128($a1) */
	.word	0x78B90090  /* 001BFBD0 lq $t9,144($a1) */
	.word	0x78BA00A0  /* 001BFBD4 lq $k0,160($a1) */
	.word	0x78BB00B0  /* 001BFBD8 lq $k1,176($a1) */
	.word	0x78BD00D0  /* 001BFBDC lq $sp,208($a1) */
	.word	0x78BE00E0  /* 001BFBE0 lq $s8,224($a1) */
	.word	0x78A200F0  /* 001BFBE4 lq $v0,240($a1) */
	.word	0xC4B40100  /* 001BFBE8 lwc1 $f20,256($a1) */
	.word	0xC4B50104  /* 001BFBEC lwc1 $f21,260($a1) */
	.word	0xC4B60108  /* 001BFBF0 lwc1 $f22,264($a1) */
	.word	0xC4B7010C  /* 001BFBF4 lwc1 $f23,268($a1) */
	.word	0xC4B80110  /* 001BFBF8 lwc1 $f24,272($a1) */
	.word	0xC4B90114  /* 001BFBFC lwc1 $f25,276($a1) */
	.word	0xC4BA0118  /* 001BFC00 lwc1 $f26,280($a1) */
	.word	0xC4BB011C  /* 001BFC04 lwc1 $f27,284($a1) */
	.word	0xC4BC0120  /* 001BFC08 lwc1 $f28,288($a1) */
	.word	0xC4BD0124  /* 001BFC0C lwc1 $f29,292($a1) */
	.word	0xC4BE0128  /* 001BFC10 lwc1 $f30,296($a1) */
	.word	0xC4BF012C  /* 001BFC14 lwc1 $f31,300($a1) */
	.word	0x78A80180  /* 001BFC18 lq $t0,384($a1) */
	.word	0x78A90190  /* 001BFC1C lq $t1,400($a1) */
	.word	0x78AA01A0  /* 001BFC20 lq $t2,416($a1) */
	.word	0x78AB01B0  /* 001BFC24 lq $t3,432($a1) */
	.word	0x78A40140  /* 001BFC28 lq $a0,320($a1) */
	.word	0x78A60160  /* 001BFC2C lq $a2,352($a1) */
	.word	0x78A70170  /* 001BFC30 lq $a3,368($a1) */
	.word	0x0040F809  /* 001BFC34 jalr $v0 */
	.word	0x78A50150  /* 001BFC38 lq $a1,336($a1) */
	.word	0x00000000  /* 001BFC3C nop */
	.word	0x3C040000  /* 001BFC40 lui $a0,%hi(D_0037A170) */
	.reloc	.-4, R_MIPS_HI16, D_0037A170
	.word	0x8C840000  /* 001BFC44 lw $a0,%lo(D_0037A170)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A170
	.word	0x8C850000  /* 001BFC48 lw $a1,0($a0) */
	.word	0x78BD00D0  /* 001BFC4C lq $sp,208($a1) */
	.word	0x3C040000  /* 001BFC50 lui $a0,%hi(D_0037A168) */
	.reloc	.-4, R_MIPS_HI16, D_0037A168
	.word	0x8C840000  /* 001BFC54 lw $a0,%lo(D_0037A168)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A168
	.word	0x0C000000  /* 001BFC58 jal func_001bffa0 */
	.reloc	.-4, R_MIPS_26, func_001bffa0
	.word	0x00000000  /* 001BFC5C nop */
	.word	0x00000000  /* 001BFC60 nop */
	.word	0x3C020000  /* 001BFC64 lui $v0,%hi(D_0037A164) */
	.reloc	.-4, R_MIPS_HI16, D_0037A164
	.word	0x8C420000  /* 001BFC68 lw $v0,%lo(D_0037A164)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A164
	.word	0x3C040000  /* 001BFC6C lui $a0,%hi(D_0037A170) */
	.reloc	.-4, R_MIPS_HI16, D_0037A170
	.word	0x8C840000  /* 001BFC70 lw $a0,%lo(D_0037A170)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0037A170
	.word	0x08000000  /* 001BFC74 j .L001BFB50 */
	.reloc	.-4, R_MIPS_26, func_001bfac8+0x88
	.word	0x00000000  /* 001BFC78 nop */
	.word	0x00000000  /* 001BFC7C nop */
	.word	0x3C030000  /* 001BFC80 lui $v1,%hi(D_0037A174) */
	.reloc	.-4, R_MIPS_HI16, D_0037A174
	.word	0x03E00008  /* 001BFC84 jr $ra */
	.word	0x8C620000  /* 001BFC88 lw $v0,%lo(D_0037A174)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_0037A174
	.end	func_001bfac8
