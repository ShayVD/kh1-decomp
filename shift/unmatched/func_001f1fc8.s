/* func_001f1fc8: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001f1fc8,"ax",@progbits
	.globl	func_001f1fc8
	.ent	func_001f1fc8
func_001f1fc8:  /* 0x001F1FC8 */
	.word	0x27BDFF70  /* 001F1FC8 addiu $sp,$sp,-144 */
	.word	0xAFA40000  /* 001F1FCC sw $a0,0($sp) */
	.word	0x0000202D  /* 001F1FD0 move $a0,$zero */
	.word	0xFFB00040  /* 001F1FD4 sd $s0,64($sp) */
	.word	0x00E0802D  /* 001F1FD8 move $s0,$a3 */
	.word	0xFFB50068  /* 001F1FDC sd $s5,104($sp) */
	.word	0x0100A82D  /* 001F1FE0 move $s5,$t0 */
	.word	0xFFB70078  /* 001F1FE4 sd $s7,120($sp) */
	.word	0x00108100  /* 001F1FE8 sll $s0,$s0,0x4 */
	.word	0xFFBE0080  /* 001F1FEC sd $s8,128($sp) */
	.word	0xAFA90024  /* 001F1FF0 sw $t1,36($sp) */
	.word	0xAFA50010  /* 001F1FF4 sw $a1,16($sp) */
	.word	0xAFA60020  /* 001F1FF8 sw $a2,32($sp) */
	.word	0xFFB10048  /* 001F1FFC sd $s1,72($sp) */
	.word	0xFFB20050  /* 001F2000 sd $s2,80($sp) */
	.word	0xFFB30058  /* 001F2004 sd $s3,88($sp) */
	.word	0xFFB40060  /* 001F2008 sd $s4,96($sp) */
	.word	0xFFB60070  /* 001F200C sd $s6,112($sp) */
	.word	0xFFBF0088  /* 001F2010 sd $ra,136($sp) */
	.word	0x0C000000  /* 001F2014 jal func_001efb78 */
	.reloc	.-4, R_MIPS_26, func_001efb78
	.word	0x261E7400  /* 001F2018 addiu $s8,$s0,29696 */
	.word	0x8FA20024  /* 001F201C lw $v0,36($sp) */
	.word	0x0000202D  /* 001F2020 move $a0,$zero */
	.word	0x00021100  /* 001F2024 sll $v0,$v0,0x4 */
	.word	0x0C000000  /* 001F2028 jal func_001efb98 */
	.reloc	.-4, R_MIPS_26, func_001efb98
	.word	0xAFA20030  /* 001F202C sw $v0,48($sp) */
	.word	0x0C000000  /* 001F2030 jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0x24040002  /* 001F2034 li $a0,2 */
	.word	0x3C050000  /* 001F2038 lui $a1,%hi(D_003F2270) */
	.reloc	.-4, R_MIPS_HI16, D_003F2270
	.word	0x0040202D  /* 001F203C move $a0,$v0 */
	.word	0x0C000000  /* 001F2040 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x24A50000  /* 001F2044 addiu $a1,$a1,%lo(D_003F2270) */
	.reloc	.-4, R_MIPS_LO16, D_003F2270
	.word	0x24040400  /* 001F2048 li $a0,1024 */
	.word	0x8FA30010  /* 001F204C lw $v1,16($sp) */
	.word	0x24050080  /* 001F2050 li $a1,128 */
	.word	0x0C000000  /* 001F2054 jal func_00122048 */
	.reloc	.-4, R_MIPS_26, func_00122048
	.word	0xAFA30038  /* 001F2058 sw $v1,56($sp) */
	.word	0xAFA20028  /* 001F205C sw $v0,40($sp) */
	.word	0x3C020FFF  /* 001F2060 lui $v0,0xfff */
	.word	0x3442FFFF  /* 001F2064 ori $v0,$v0,0xffff */
	.word	0x3C078000  /* 001F2068 lui $a3,0x8000 */
	.word	0x8FA40028  /* 001F206C lw $a0,40($sp) */
	.word	0x3C051000  /* 001F2070 lui $a1,0x1000 */
	.word	0x0005283C  /* 001F2074 dsll32 $a1,$a1,0x0 */
	.word	0x34A50003  /* 001F2078 ori $a1,$a1,0x3 */
	.word	0x2406000E  /* 001F207C li $a2,14 */
	.word	0x2408003F  /* 001F2080 li $t0,63 */
	.word	0x24970010  /* 001F2084 addiu $s7,$a0,16 */
	.word	0x00821024  /* 001F2088 and $v0,$a0,$v0 */
	.word	0x3C040000  /* 001F208C lui $a0,%hi(D_003E8E08) */
	.reloc	.-4, R_MIPS_HI16, D_003E8E08
	.word	0x00471025  /* 001F2090 or $v0,$v0,$a3 */
	.word	0x3C094007  /* 001F2094 lui $t1,0x4007 */
	.word	0x3529FF80  /* 001F2098 ori $t1,$t1,0xff80 */
	.word	0x00094C38  /* 001F209C dsll $t1,$t1,0x10 */
	.word	0x35290130  /* 001F20A0 ori $t1,$t1,0x130 */
	.word	0x00094C38  /* 001F20A4 dsll $t1,$t1,0x10 */
	.word	0x240A0016  /* 001F20A8 li $t2,22 */
	.word	0x240B0044  /* 001F20AC li $t3,68 */
	.word	0x240C0042  /* 001F20B0 li $t4,66 */
	.word	0x3C0D60AB  /* 001F20B4 lui $t5,0x60ab */
	.word	0x35AD4000  /* 001F20B8 ori $t5,$t5,0x4000 */
	.word	0x000D683C  /* 001F20BC dsll32 $t5,$t5,0x0 */
	.word	0x35AD8001  /* 001F20C0 ori $t5,$t5,0x8001 */
	.word	0x3C030043  /* 001F20C4 lui $v1,0x43 */
	.word	0x346343EE  /* 001F20C8 ori $v1,$v1,0x43ee */
	.word	0x24840000  /* 001F20CC addiu $a0,$a0,%lo(D_003E8E08) */
	.reloc	.-4, R_MIPS_LO16, D_003E8E08
	.word	0xFEE30048  /* 001F20D0 sd $v1,72($s7) */
	.word	0xFEE50000  /* 001F20D4 sd $a1,0($s7) */
	.word	0x3C0F7000  /* 001F20D8 lui $t7,0x7000 */
	.word	0x35EF000B  /* 001F20DC ori $t7,$t7,0xb */
	.word	0xAFA2002C  /* 001F20E0 sw $v0,44($sp) */
	.word	0x240E0001  /* 001F20E4 li $t6,1 */
	.word	0xFEE60008  /* 001F20E8 sd $a2,8($s7) */
	.word	0xFEE80018  /* 001F20EC sd $t0,24($s7) */
	.word	0xAFA40034  /* 001F20F0 sw $a0,52($sp) */
	.word	0xFEE90020  /* 001F20F4 sd $t1,32($s7) */
	.word	0xFEEA0028  /* 001F20F8 sd $t2,40($s7) */
	.word	0xFEEB0030  /* 001F20FC sd $t3,48($s7) */
	.word	0xFEEC0038  /* 001F2100 sd $t4,56($s7) */
	.word	0xFEED0040  /* 001F2104 sd $t5,64($s7) */
	.word	0xFEE00010  /* 001F2108 sd $zero,16($s7) */
	.word	0x8FA50028  /* 001F210C lw $a1,40($sp) */
	.word	0xFCAF0000  /* 001F2110 sd $t7,0($a1) */
	.word	0x8FA20000  /* 001F2114 lw $v0,0($sp) */
	.word	0x104E0041  /* 001F2118 beq $v0,$t6,.L001F2220 */
	.word	0x24B70060  /* 001F211C addiu $s7,$a1,96 */
	.word	0x28420002  /* 001F2120 slti $v0,$v0,2 */
	.word	0x1440003A  /* 001F2124 bnez $v0,.L001F2210 */
	.word	0x8FA40020  /* 001F2128 lw $a0,32($sp) */
	.word	0x8FA30000  /* 001F212C lw $v1,0($sp) */
	.word	0x24020002  /* 001F2130 li $v0,2 */
	.word	0x14620037  /* 001F2134 bne $v1,$v0,.L001F2214 */
	.word	0x00041100  /* 001F2138 sll $v0,$a0,0x4 */
	.word	0x8FA50024  /* 001F213C lw $a1,36($sp) */
	.word	0x0C000000  /* 001F2140 jal func_001f0148 */
	.reloc	.-4, R_MIPS_26, func_001f0148
	.word	0x02A0202D  /* 001F2144 move $a0,$s5 */
	.word	0x00021FC2  /* 001F2148 srl $v1,$v0,0x1f */
	.word	0x00621821  /* 001F214C addu $v1,$v1,$v0 */
	.word	0x8FA20020  /* 001F2150 lw $v0,32($sp) */
	.word	0x00031843  /* 001F2154 sra $v1,$v1,0x1 */
	.word	0x00431823  /* 001F2158 subu $v1,$v0,$v1 */
	.word	0x00031900  /* 001F215C sll $v1,$v1,0x4 */
	.word	0x24767000  /* 001F2160 addiu $s6,$v1,28672 */
	.word	0x00000000  /* 001F2164 nop */
	.word	0x92A30000  /* 001F2168 lbu $v1,0($s5) */
	.word	0x2C620015  /* 001F216C sltiu $v0,$v1,21 */
	.word	0x504000B7  /* 001F2170 beqzl $v0,.L001F2450 */
	.word	0x24020018  /* 001F2174 li $v0,24 */
	.word	0x00000000  /* 001F2178 nop */
	.word	0x00000000  /* 001F217C nop */
	.word	0x00000000  /* 001F2180 nop */
	.word	0x5040FFF8  /* 001F2184 beqzl $v0,.L001F2168 */
	.word	0x26B50001  /* 001F2188 addiu $s5,$s5,1 */
	.word	0x3C040000  /* 001F218C lui $a0,%hi(D_00490A80) */
	.reloc	.-4, R_MIPS_HI16, D_00490A80
	.word	0x00031080  /* 001F2190 sll $v0,$v1,0x2 */
	.word	0x24830000  /* 001F2194 addiu $v1,$a0,%lo(D_00490A80) */
	.reloc	.-4, R_MIPS_LO16, D_00490A80
	.word	0x00431021  /* 001F2198 addu $v0,$v0,$v1 */
	.word	0x8C440000  /* 001F219C lw $a0,0($v0) */
	.word	0x00800008  /* 001F21A0 jr $a0 */
	.word	0x00000000  /* 001F21A4 nop */
	.word	0x8FA50024  /* 001F21A8 lw $a1,36($sp) */
	.word	0x24020012  /* 001F21AC li $v0,18 */
	.word	0x50400001  /* 001F21B0 beqzl $v0,.L001F21B8 */
	.word	0x000001CD  /* 001F21B4 break 0x0,0x7 */
	.word	0x26B50001  /* 001F21B8 addiu $s5,$s5,1 */
	.word	0x00051A00  /* 001F21BC sll $v1,$a1,0x8 */
	.word	0x0062001A  /* 001F21C0 div $zero,$v1,$v0 */
	.word	0x00001812  /* 001F21C4 mflo $v1 */
	.word	0x1000FFE7  /* 001F21C8 b .L001F2168 */
	.word	0x02C3B021  /* 001F21CC addu $s6,$s6,$v1 */
	.word	0x26B50001  /* 001F21D0 addiu $s5,$s5,1 */
	.word	0x3C030000  /* 001F21D4 lui $v1,%hi(D_0063F740) */
	.reloc	.-4, R_MIPS_HI16, D_0063F740
	.word	0x92A20000  /* 001F21D8 lbu $v0,0($s5) */
	.word	0x00021100  /* 001F21DC sll $v0,$v0,0x4 */
	.word	0x10000002  /* 001F21E0 b .L001F21EC */
	.word	0xAC620000  /* 001F21E4 sw $v0,%lo(D_0063F740)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_0063F740
	.word	0x3C030000  /* 001F21E8 lui $v1,0x64 */
	.reloc	.-4, R_MIPS_HI16, D_0063F740
	.word	0x8C620000  /* 001F21EC lw $v0,-2240($v1) */
	.reloc	.-4, R_MIPS_LO16, D_0063F740
	.word	0x24030001  /* 001F21F0 li $v1,1 */
	.word	0x03C2F021  /* 001F21F4 addu $s8,$s8,$v0 */
	.word	0x8FA20000  /* 001F21F8 lw $v0,0($sp) */
	.word	0x10430008  /* 001F21FC beq $v0,$v1,.L001F2220 */
	.word	0x26B50001  /* 001F2200 addiu $s5,$s5,1 */
	.word	0x1000FFC7  /* 001F2204 b .L001F2124 */
	.word	0x28420002  /* 001F2208 slti $v0,$v0,2 */
	.word	0x00000000  /* 001F220C nop */
	.word	0x00041100  /* 001F2210 sll $v0,$a0,0x4 */
	.word	0x1000FFD4  /* 001F2214 b .L001F2168 */
	.word	0x24567000  /* 001F2218 addiu $s6,$v0,28672 */
	.word	0x00000000  /* 001F221C nop */
	.word	0x8FA50024  /* 001F2220 lw $a1,36($sp) */
	.word	0x0C000000  /* 001F2224 jal func_001f0148 */
	.reloc	.-4, R_MIPS_26, func_001f0148
	.word	0x02A0202D  /* 001F2228 move $a0,$s5 */
	.word	0x8FA50020  /* 001F222C lw $a1,32($sp) */
	.word	0x00A21023  /* 001F2230 subu $v0,$a1,$v0 */
	.word	0x00021100  /* 001F2234 sll $v0,$v0,0x4 */
	.word	0x1000FFCB  /* 001F2238 b .L001F2168 */
	.word	0x24567000  /* 001F223C addiu $s6,$v0,28672 */
	.word	0x26B50001  /* 001F2240 addiu $s5,$s5,1 */
	.word	0x1000FFC8  /* 001F2244 b .L001F2168 */
	.word	0xAFA00000  /* 001F2248 sw $zero,0($sp) */
	.word	0x00000000  /* 001F224C nop */
	.word	0x24030001  /* 001F2250 li $v1,1 */
	.word	0x26B50001  /* 001F2254 addiu $s5,$s5,1 */
	.word	0x1000FFC3  /* 001F2258 b .L001F2168 */
	.word	0xAFA30000  /* 001F225C sw $v1,0($sp) */
	.word	0x24040002  /* 001F2260 li $a0,2 */
	.word	0x26B50001  /* 001F2264 addiu $s5,$s5,1 */
	.word	0x1000FFBF  /* 001F2268 b .L001F2168 */
	.word	0xAFA40000  /* 001F226C sw $a0,0($sp) */
	.word	0x92A20001  /* 001F2270 lbu $v0,1($s5) */
	.word	0x10400006  /* 001F2274 beqz $v0,.L001F2290 */
	.word	0x00021080  /* 001F2278 sll $v0,$v0,0x2 */
	.word	0x3C010000  /* 001F227C lui $at,%hi(D_003E8D04) */
	.reloc	.-4, R_MIPS_HI16, D_003E8D04
	.word	0x00220821  /* 001F2280 addu $at,$at,$v0 */
	.word	0x8C220000  /* 001F2284 lw $v0,%lo(D_003E8D04)($at) */
	.reloc	.-4, R_MIPS_LO16, D_003E8D04
	.word	0x10000059  /* 001F2288 b .L001F23F0 */
	.word	0xAFA20010  /* 001F228C sw $v0,16($sp) */
	.word	0x8FA50038  /* 001F2290 lw $a1,56($sp) */
	.word	0x10000056  /* 001F2294 b .L001F23F0 */
	.word	0xAFA50010  /* 001F2298 sw $a1,16($sp) */
	.word	0x00000000  /* 001F229C nop */
	.word	0x92A50004  /* 001F22A0 lbu $a1,4($s5) */
	.word	0x92A20003  /* 001F22A4 lbu $v0,3($s5) */
	.word	0x92A40002  /* 001F22A8 lbu $a0,2($s5) */
	.word	0x00052E00  /* 001F22AC sll $a1,$a1,0x18 */
	.word	0x92A30001  /* 001F22B0 lbu $v1,1($s5) */
	.word	0x26B50005  /* 001F22B4 addiu $s5,$s5,5 */
	.word	0x00021400  /* 001F22B8 sll $v0,$v0,0x10 */
	.word	0x00042200  /* 001F22BC sll $a0,$a0,0x8 */
	.word	0x00651825  /* 001F22C0 or $v1,$v1,$a1 */
	.word	0x00441025  /* 001F22C4 or $v0,$v0,$a0 */
	.word	0x00621825  /* 001F22C8 or $v1,$v1,$v0 */
	.word	0x1000FFA6  /* 001F22CC b .L001F2168 */
	.word	0xAFA30010  /* 001F22D0 sw $v1,16($sp) */
	.word	0x00000000  /* 001F22D4 nop */
	.word	0x8FA20034  /* 001F22D8 lw $v0,52($sp) */
	.word	0x26B50001  /* 001F22DC addiu $s5,$s5,1 */
	.word	0x8FA30034  /* 001F22E0 lw $v1,52($sp) */
	.word	0x8C420000  /* 001F22E4 lw $v0,0($v0) */
	.word	0x24630004  /* 001F22E8 addiu $v1,$v1,4 */
	.word	0xAFA20010  /* 001F22EC sw $v0,16($sp) */
	.word	0x1000FF9D  /* 001F22F0 b .L001F2168 */
	.word	0xAFA30034  /* 001F22F4 sw $v1,52($sp) */
	.word	0x8FA40034  /* 001F22F8 lw $a0,52($sp) */
	.word	0x8C880000  /* 001F22FC lw $t0,0($a0) */
	.word	0x1100000A  /* 001F2300 beqz $t0,.L001F232C */
	.word	0x8FA50010  /* 001F2304 lw $a1,16($sp) */
	.word	0x00163103  /* 001F2308 sra $a2,$s6,0x4 */
	.word	0x8FA90024  /* 001F230C lw $t1,36($sp) */
	.word	0x001E3903  /* 001F2310 sra $a3,$s8,0x4 */
	.word	0x0C000000  /* 001F2314 jal func_001f1fc8 */
	.reloc	.-4, R_MIPS_26, func_001f1fc8
	.word	0x0000202D  /* 001F2318 move $a0,$zero */
	.word	0x3C050000  /* 001F231C lui $a1,%hi(D_0063F750) */
	.reloc	.-4, R_MIPS_HI16, D_0063F750
	.word	0x8CA30000  /* 001F2320 lw $v1,%lo(D_0063F750)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_0063F750
	.word	0x0002B100  /* 001F2324 sll $s6,$v0,0x4 */
	.word	0x0003F100  /* 001F2328 sll $s8,$v1,0x4 */
	.word	0x8FA20034  /* 001F232C lw $v0,52($sp) */
	.word	0x26B50001  /* 001F2330 addiu $s5,$s5,1 */
	.word	0x24420004  /* 001F2334 addiu $v0,$v0,4 */
	.word	0x1000FF8B  /* 001F2338 b .L001F2168 */
	.word	0xAFA20034  /* 001F233C sw $v0,52($sp) */
	.word	0x8FA30034  /* 001F2340 lw $v1,52($sp) */
	.word	0x00163903  /* 001F2344 sra $a3,$s6,0x4 */
	.word	0x92A40001  /* 001F2348 lbu $a0,1($s5) */
	.word	0x001E4103  /* 001F234C sra $t0,$s8,0x4 */
	.word	0x92A50002  /* 001F2350 lbu $a1,2($s5) */
	.word	0x92A60003  /* 001F2354 lbu $a2,3($s5) */
	.word	0x26B50004  /* 001F2358 addiu $s5,$s5,4 */
	.word	0x8C690000  /* 001F235C lw $t1,0($v1) */
	.word	0x24630004  /* 001F2360 addiu $v1,$v1,4 */
	.word	0x8FAA0024  /* 001F2364 lw $t2,36($sp) */
	.word	0x8FAB0010  /* 001F2368 lw $t3,16($sp) */
	.word	0x0C000000  /* 001F236C jal func_001f2d68 */
	.reloc	.-4, R_MIPS_26, func_001f2d68
	.word	0xAFA30034  /* 001F2370 sw $v1,52($sp) */
	.word	0x3C040000  /* 001F2374 lui $a0,%hi(D_0063F750) */
	.reloc	.-4, R_MIPS_HI16, D_0063F750
	.word	0x8C830000  /* 001F2378 lw $v1,%lo(D_0063F750)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0063F750
	.word	0x0002B100  /* 001F237C sll $s6,$v0,0x4 */
	.word	0x1000FF79  /* 001F2380 b .L001F2168 */
	.word	0x0003F100  /* 001F2384 sll $s8,$v1,0x4 */
	.word	0x92A50001  /* 001F2388 lbu $a1,1($s5) */
	.word	0x26B50002  /* 001F238C addiu $s5,$s5,2 */
	.word	0x00051100  /* 001F2390 sll $v0,$a1,0x4 */
	.word	0xAFA50024  /* 001F2394 sw $a1,36($sp) */
	.word	0x1000FF73  /* 001F2398 b .L001F2168 */
	.word	0xAFA20030  /* 001F239C sw $v0,48($sp) */
	.word	0x92A30002  /* 001F23A0 lbu $v1,2($s5) */
	.word	0x92A20001  /* 001F23A4 lbu $v0,1($s5) */
	.word	0x26B50003  /* 001F23A8 addiu $s5,$s5,3 */
	.word	0x00031A00  /* 001F23AC sll $v1,$v1,0x8 */
	.word	0x00431025  /* 001F23B0 or $v0,$v0,$v1 */
	.word	0x00021400  /* 001F23B4 sll $v0,$v0,0x10 */
	.word	0x00021303  /* 001F23B8 sra $v0,$v0,0xc */
	.word	0x1000FF6A  /* 001F23BC b .L001F2168 */
	.word	0x02C2B021  /* 001F23C0 addu $s6,$s6,$v0 */
	.word	0x00000000  /* 001F23C4 nop */
	.word	0x92A30002  /* 001F23C8 lbu $v1,2($s5) */
	.word	0x92A20001  /* 001F23CC lbu $v0,1($s5) */
	.word	0x26B50003  /* 001F23D0 addiu $s5,$s5,3 */
	.word	0x00031A00  /* 001F23D4 sll $v1,$v1,0x8 */
	.word	0x00431025  /* 001F23D8 or $v0,$v0,$v1 */
	.word	0x00021400  /* 001F23DC sll $v0,$v0,0x10 */
	.word	0x00021303  /* 001F23E0 sra $v0,$v0,0xc */
	.word	0x1000FF60  /* 001F23E4 b .L001F2168 */
	.word	0x03C2F021  /* 001F23E8 addu $s8,$s8,$v0 */
	.word	0x00000000  /* 001F23EC nop */
	.word	0x1000FF5D  /* 001F23F0 b .L001F2168 */
	.word	0x26B50002  /* 001F23F4 addiu $s5,$s5,2 */
	.word	0x92A20002  /* 001F23F8 lbu $v0,2($s5) */
	.word	0x92A30001  /* 001F23FC lbu $v1,1($s5) */
	.word	0x26B50003  /* 001F2400 addiu $s5,$s5,3 */
	.word	0x00021200  /* 001F2404 sll $v0,$v0,0x8 */
	.word	0x00621825  /* 001F2408 or $v1,$v1,$v0 */
	.word	0x00031C00  /* 001F240C sll $v1,$v1,0x10 */
	.word	0x00031C03  /* 001F2410 sra $v1,$v1,0x10 */
	.word	0x00031100  /* 001F2414 sll $v0,$v1,0x4 */
	.word	0xAFA30020  /* 001F2418 sw $v1,32($sp) */
	.word	0x1000FF52  /* 001F241C b .L001F2168 */
	.word	0x24567000  /* 001F2420 addiu $s6,$v0,28672 */
	.word	0x00000000  /* 001F2424 nop */
	.word	0x92A30002  /* 001F2428 lbu $v1,2($s5) */
	.word	0x92A20001  /* 001F242C lbu $v0,1($s5) */
	.word	0x26B50003  /* 001F2430 addiu $s5,$s5,3 */
	.word	0x00031A00  /* 001F2434 sll $v1,$v1,0x8 */
	.word	0x00431025  /* 001F2438 or $v0,$v0,$v1 */
	.word	0x00021400  /* 001F243C sll $v0,$v0,0x10 */
	.word	0x00021303  /* 001F2440 sra $v0,$v0,0xc */
	.word	0x1000FF48  /* 001F2444 b .L001F2168 */
	.word	0x245E7400  /* 001F2448 addiu $s8,$v0,29696 */
	.word	0x00000000  /* 001F244C nop */
	.word	0x14620007  /* 001F2450 bne $v1,$v0,.L001F2470 */
	.word	0x2C620020  /* 001F2454 sltiu $v0,$v1,32 */
	.word	0x92A20001  /* 001F2458 lbu $v0,1($s5) */
	.word	0x26B50002  /* 001F245C addiu $s5,$s5,2 */
	.word	0x00021200  /* 001F2460 sll $v0,$v0,0x8 */
	.word	0x1000000C  /* 001F2464 b .L001F2498 */
	.word	0x2443E7E0  /* 001F2468 addiu $v1,$v0,-6176 */
	.word	0x00000000  /* 001F246C nop */
	.word	0x10400007  /* 001F2470 beqz $v0,.L001F2490 */
	.word	0x92A20000  /* 001F2474 lbu $v0,0($s5) */
	.word	0x92A30001  /* 001F2478 lbu $v1,1($s5) */
	.word	0x26B50002  /* 001F247C addiu $s5,$s5,2 */
	.word	0x00021200  /* 001F2480 sll $v0,$v0,0x8 */
	.word	0x00431025  /* 001F2484 or $v0,$v0,$v1 */
	.word	0x10000003  /* 001F2488 b .L001F2498 */
	.word	0x2443E7E0  /* 001F248C addiu $v1,$v0,-6176 */
	.word	0x26B50001  /* 001F2490 addiu $s5,$s5,1 */
	.word	0x2443FFE0  /* 001F2494 addiu $v1,$v0,-32 */
	.word	0x3C020000  /* 001F2498 lui $v0,%hi(D_003E8E28) */
	.reloc	.-4, R_MIPS_HI16, D_003E8E28
	.word	0x000318C0  /* 001F249C sll $v1,$v1,0x3 */
	.word	0x8C510000  /* 001F24A0 lw $s1,%lo(D_003E8E28)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_003E8E28
	.word	0x24100012  /* 001F24A4 li $s0,18 */
	.word	0x52000001  /* 001F24A8 beqzl $s0,.L001F24B0 */
	.word	0x000001CD  /* 001F24AC break 0x0,0x7 */
	.word	0x8FA20024  /* 001F24B0 lw $v0,36($sp) */
	.word	0x02238821  /* 001F24B4 addu $s1,$s1,$v1 */
	.word	0x92320006  /* 001F24B8 lbu $s2,6($s1) */
	.word	0x00129100  /* 001F24BC sll $s2,$s2,0x4 */
	.word	0x02429818  /* 001F24C0 mult $s3,$s2,$v0 */
	.word	0x0270001A  /* 001F24C4 div $zero,$s3,$s0 */
	.word	0x00009812  /* 001F24C8 mflo $s3 */
	.word	0x0C000000  /* 001F24CC jal func_001efb88 */
	.reloc	.-4, R_MIPS_26, func_001efb88
	.word	0x00000000  /* 001F24D0 nop */
	.word	0x8FA30024  /* 001F24D4 lw $v1,36($sp) */
	.word	0x0242A021  /* 001F24D8 addu $s4,$s2,$v0 */
	.word	0x24020012  /* 001F24DC li $v0,18 */
	.word	0x3405FFF0  /* 001F24E0 li $a1,0xfff0 */
	.word	0x000528FC  /* 001F24E4 dsll32 $a1,$a1,0x3 */
	.word	0x0283A018  /* 001F24E8 mult $s4,$s4,$v1 */
	.word	0x50400001  /* 001F24EC beqzl $v0,.L001F24F4 */
	.word	0x000001CD  /* 001F24F0 break 0x0,0x7 */
	.word	0x8FA20010  /* 001F24F4 lw $v0,16($sp) */
	.word	0x3C090010  /* 001F24F8 lui $t1,0x10 */
	.word	0x92240007  /* 001F24FC lbu $a0,7($s1) */
	.word	0x34068000  /* 001F2500 li $a2,0x8000 */
	.word	0x0002383C  /* 001F2504 dsll32 $a3,$v0,0x0 */
	.word	0x962C0002  /* 001F2508 lhu $t4,2($s1) */
	.word	0x0290001A  /* 001F250C div $zero,$s4,$s0 */
	.word	0x00041102  /* 001F2510 srl $v0,$a0,0x4 */
	.word	0x00021080  /* 001F2514 sll $v0,$v0,0x2 */
	.word	0x3084000F  /* 001F2518 andi $a0,$a0,0xf */
	.word	0x3C030000  /* 001F251C lui $v1,%hi(D_003E8D00) */
	.reloc	.-4, R_MIPS_HI16, D_003E8D00
	.word	0x00621821  /* 001F2520 addu $v1,$v1,$v0 */
	.word	0x8C630000  /* 001F2524 lw $v1,%lo(D_003E8D00)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_003E8D00
	.word	0x24020016  /* 001F2528 li $v0,22 */
	.word	0x0004263C  /* 001F252C dsll32 $a0,$a0,0x18 */
	.word	0x962B0004  /* 001F2530 lhu $t3,4($s1) */
	.word	0x00031D38  /* 001F2534 dsll $v1,$v1,0x14 */
	.word	0x01929021  /* 001F2538 addu $s2,$t4,$s2 */
	.word	0x00641825  /* 001F253C or $v1,$v1,$a0 */
	.word	0x8FA40030  /* 001F2540 lw $a0,48($sp) */
	.word	0x00651825  /* 001F2544 or $v1,$v1,$a1 */
	.word	0x24050001  /* 001F2548 li $a1,1 */
	.word	0x03C44021  /* 001F254C addu $t0,$s8,$a0 */
	.word	0x24040002  /* 001F2550 li $a0,2 */
	.word	0x0007383E  /* 001F2554 dsrl32 $a3,$a3,0x0 */
	.word	0x256A0120  /* 001F2558 addiu $t2,$t3,288 */
	.word	0x02D39821  /* 001F255C addu $s3,$s6,$s3 */
	.word	0xFEE30000  /* 001F2560 sd $v1,0($s7) */
	.word	0xFEE70010  /* 001F2564 sd $a3,16($s7) */
	.word	0xAEE6003C  /* 001F2568 sw $a2,60($s7) */
	.word	0xAEEA0044  /* 001F256C sw $t2,68($s7) */
	.word	0xAEE80054  /* 001F2570 sw $t0,84($s7) */
	.word	0xAEE90058  /* 001F2574 sw $t1,88($s7) */
	.word	0xAEEC0020  /* 001F2578 sw $t4,32($s7) */
	.word	0xAEEB0024  /* 001F257C sw $t3,36($s7) */
	.word	0xAEE90038  /* 001F2580 sw $t1,56($s7) */
	.word	0xFEE50018  /* 001F2584 sd $a1,24($s7) */
	.word	0xAEF60030  /* 001F2588 sw $s6,48($s7) */
	.word	0xFEE20008  /* 001F258C sd $v0,8($s7) */
	.word	0xAEF20040  /* 001F2590 sw $s2,64($s7) */
	.word	0xAEFE0034  /* 001F2594 sw $s8,52($s7) */
	.word	0xAEE0005C  /* 001F2598 sw $zero,92($s7) */
	.word	0x0000A012  /* 001F259C mflo $s4 */
	.word	0x0C000000  /* 001F25A0 jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0xAEF30050  /* 001F25A4 sw $s3,80($s7) */
	.word	0x8FA5002C  /* 001F25A8 lw $a1,44($sp) */
	.word	0x0040202D  /* 001F25AC move $a0,$v0 */
	.word	0x0C000000  /* 001F25B0 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x02D4B021  /* 001F25B4 addu $s6,$s6,$s4 */
	.word	0x0000202D  /* 001F25B8 move $a0,$zero */
	.word	0x0C000000  /* 001F25BC jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000282D  /* 001F25C0 move $a1,$zero */
	.word	0x1000FEE9  /* 001F25C4 b .L001F216C */
	.word	0x92A30000  /* 001F25C8 lbu $v1,0($s5) */
	.word	0x00000000  /* 001F25CC nop */
	.word	0x0C000000  /* 001F25D0 jal func_001220b8 */
	.reloc	.-4, R_MIPS_26, func_001220b8
	.word	0x8FA40028  /* 001F25D4 lw $a0,40($sp) */
	.word	0x3C040000  /* 001F25D8 lui $a0,%hi(D_0063F74C) */
	.reloc	.-4, R_MIPS_HI16, D_0063F74C
	.word	0x26C39000  /* 001F25DC addiu $v1,$s6,-28672 */
	.word	0xDFB60070  /* 001F25E0 ld $s6,112($sp) */
	.word	0x27C28C00  /* 001F25E4 addiu $v0,$s8,-29696 */
	.word	0xDFBE0080  /* 001F25E8 ld $s8,128($sp) */
	.word	0x00031903  /* 001F25EC sra $v1,$v1,0x4 */
	.word	0x00021103  /* 001F25F0 sra $v0,$v0,0x4 */
	.word	0x3C050000  /* 001F25F4 lui $a1,%hi(D_0063F750) */
	.reloc	.-4, R_MIPS_HI16, D_0063F750
	.word	0xDFB00040  /* 001F25F8 ld $s0,64($sp) */
	.word	0xDFB10048  /* 001F25FC ld $s1,72($sp) */
	.word	0xDFB20050  /* 001F2600 ld $s2,80($sp) */
	.word	0xDFB30058  /* 001F2604 ld $s3,88($sp) */
	.word	0xDFB40060  /* 001F2608 ld $s4,96($sp) */
	.word	0xDFB50068  /* 001F260C ld $s5,104($sp) */
	.word	0xDFB70078  /* 001F2610 ld $s7,120($sp) */
	.word	0xDFBF0088  /* 001F2614 ld $ra,136($sp) */
	.word	0xACA20000  /* 001F2618 sw $v0,%lo(D_0063F750)($a1) */
	.reloc	.-4, R_MIPS_LO16, D_0063F750
	.word	0x0060102D  /* 001F261C move $v0,$v1 */
	.word	0xAC830000  /* 001F2620 sw $v1,%lo(D_0063F74C)($a0) */
	.reloc	.-4, R_MIPS_LO16, D_0063F74C
	.word	0x03E00008  /* 001F2624 jr $ra */
	.word	0x27BD0090  /* 001F2628 addiu $sp,$sp,144 */
	.end	func_001f1fc8
