/* Game hand-written assembly (docs/elf-notes.md): 0x0024E0A4-0x0024F004 (sq context save, lq/VU0 code, decoders) and three routines that start off gcc's 8-byte function alignment (0x00121F6C lq/sq block copy, 0x00121FC4 VU0 normalize, 0x00162C5C VU0 4x4 matrix multiply). Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.func_0024e0a4,"ax",@progbits
	.globl	func_0024e0a4
	.ent	func_0024e0a4
func_0024e0a4:  /* 0x0024E0A4 */
	.word	0x3C080000  /* 0024E0A4 lui $t0,%hi(D_0046A048) */
	.reloc	.-4, R_MIPS_HI16, D_0046A048
	.word	0x25080000  /* 0024E0A8 addiu $t0,$t0,%lo(D_0046A048) */
	.reloc	.-4, R_MIPS_LO16, D_0046A048
	.word	0x8D080000  /* 0024E0AC lw $t0,0($t0) */
	.word	0x3C090000  /* 0024E0B0 lui $t1,%hi(D_0046A03C) */
	.reloc	.-4, R_MIPS_HI16, D_0046A03C
	.word	0x25290000  /* 0024E0B4 addiu $t1,$t1,%lo(D_0046A03C) */
	.reloc	.-4, R_MIPS_LO16, D_0046A03C
	.word	0x8D290000  /* 0024E0B8 lw $t1,0($t1) */
	.word	0x00000000  /* 0024E0BC nop */
	.word	0x3C010001  /* 0024E0C0 lui $at,0x1 */
	.word	0x34210320  /* 0024E0C4 ori $at,$at,0x320 */
	.word	0x2508FFFF  /* 0024E0C8 addiu $t0,$t0,-1 */
	.word	0x7D2000B0  /* 0024E0CC sq $zero,176($t1) */
	.word	0x01214821  /* 0024E0D0 addu $t1,$t1,$at */
	.word	0x1500FFF9  /* 0024E0D4 bnez $t0,.L0024E0BC */
	.word	0x00000000  /* 0024E0D8 nop */
	.word	0x03E00008  /* 0024E0DC jr $ra */
	.word	0x00000000  /* 0024E0E0 nop */
	.end	func_0024e0a4

	.section	.text.func_0024e0e4,"ax",@progbits
	.globl	func_0024e0e4
	.ent	func_0024e0e4
func_0024e0e4:  /* 0x0024E0E4 */
	.word	0x7C8000B0  /* 0024E0E4 sq $zero,176($a0) */
	.word	0x03E00008  /* 0024E0E8 jr $ra */
	.word	0x00000000  /* 0024E0EC nop */
	.end	func_0024e0e4

	.section	.text.func_0024e0f0,"ax",@progbits
	.globl	func_0024e0f0
	.ent	func_0024e0f0
func_0024e0f0:  /* 0x0024E0F0 */
	.word	0x3C0A0000  /* 0024E0F0 lui $t2,%hi(D_0046A048) */
	.reloc	.-4, R_MIPS_HI16, D_0046A048
	.word	0x254A0000  /* 0024E0F4 addiu $t2,$t2,%lo(D_0046A048) */
	.reloc	.-4, R_MIPS_LO16, D_0046A048
	.word	0x8D480000  /* 0024E0F8 lw $t0,0($t2) */
	.word	0x3C020000  /* 0024E0FC lui $v0,%hi(D_0046A03C) */
	.reloc	.-4, R_MIPS_HI16, D_0046A03C
	.word	0x24420000  /* 0024E100 addiu $v0,$v0,%lo(D_0046A03C) */
	.reloc	.-4, R_MIPS_LO16, D_0046A03C
	.word	0x8C420000  /* 0024E104 lw $v0,0($v0) */
	.word	0x784A00B0  /* 0024E108 lq $t2,176($v0) */
	.word	0x2508FFFF  /* 0024E10C addiu $t0,$t0,-1 */
	.word	0x1140000D  /* 0024E110 beqz $t2,.L0024E148 */
	.word	0x00000000  /* 0024E114 nop */
	.word	0x3C010001  /* 0024E118 lui $at,0x1 */
	.word	0x34210320  /* 0024E11C ori $at,$at,0x320 */
	.word	0x00411021  /* 0024E120 addu $v0,$v0,$at */
	.word	0x1500FFF8  /* 0024E124 bnez $t0,.L0024E108 */
	.word	0x00000000  /* 0024E128 nop */
	.word	0x00000000  /* 0024E12C nop */
	.word	0x00000000  /* 0024E130 nop */
	.word	0x00000000  /* 0024E134 nop */
	.word	0x00000000  /* 0024E138 nop */
	.word	0x00000000  /* 0024E13C nop */
	.word	0x08000000  /* 0024E140 j .L0024E12C */
	.reloc	.-4, R_MIPS_26, func_0024e0f0+0x3c
	.word	0x00000000  /* 0024E144 nop */
	.word	0x3C080000  /* 0024E148 lui $t0,%hi(func_0024e18c) */
	.reloc	.-4, R_MIPS_HI16, func_0024e18c
	.word	0x25080000  /* 0024E14C addiu $t0,$t0,%lo(func_0024e18c) */
	.reloc	.-4, R_MIPS_LO16, func_0024e18c
	.word	0x7C4800B0  /* 0024E150 sq $t0,176($v0) */
	.word	0x7C440030  /* 0024E154 sq $a0,48($v0) */
	.word	0x7C450010  /* 0024E158 sq $a1,16($v0) */
	.word	0x7C460020  /* 0024E15C sq $a2,32($v0) */
	.word	0x7C5C00E0  /* 0024E160 sq $gp,224($v0) */
	.word	0x7C5E00D0  /* 0024E164 sq $s8,208($v0) */
	.word	0x24080001  /* 0024E168 li $t0,1 */
	.word	0x7C480300  /* 0024E16C sq $t0,768($v0) */
	.word	0x7C480310  /* 0024E170 sq $t0,784($v0) */
	.word	0x3C010001  /* 0024E174 lui $at,0x1 */
	.word	0x342102E0  /* 0024E178 ori $at,$at,0x2e0 */
	.word	0x00414021  /* 0024E17C addu $t0,$v0,$at */
	.word	0x7C4800C0  /* 0024E180 sq $t0,192($v0) */
	.word	0x03E00008  /* 0024E184 jr $ra */
	.word	0x00000000  /* 0024E188 nop */
	.end	func_0024e0f0

	.section	.text.func_0024e18c,"ax",@progbits
	.globl	func_0024e18c
	.ent	func_0024e18c
func_0024e18c:  /* 0x0024E18C */
	.word	0x8D240000  /* 0024E18C lw $a0,0($t1) */
	.word	0x8D250004  /* 0024E190 lw $a1,4($t1) */
	.word	0x8D260008  /* 0024E194 lw $a2,8($t1) */
	.word	0x8D27000C  /* 0024E198 lw $a3,12($t1) */
	.word	0x3C1F0000  /* 0024E19C lui $ra,%hi(func_0024e1ac) */
	.reloc	.-4, R_MIPS_HI16, func_0024e18c+0x20
	.word	0x27FF0000  /* 0024E1A0 addiu $ra,$ra,%lo(func_0024e1ac) */
	.reloc	.-4, R_MIPS_LO16, func_0024e18c+0x20
	.word	0x02000008  /* 0024E1A4 jr $s0 */
	.word	0x00000000  /* 0024E1A8 nop */
	.word	0x3C080000  /* 0024E1AC lui $t0,%hi(D_0046A040) */
	.reloc	.-4, R_MIPS_HI16, D_0046A040
	.word	0x25080000  /* 0024E1B0 addiu $t0,$t0,%lo(D_0046A040) */
	.reloc	.-4, R_MIPS_LO16, D_0046A040
	.word	0x8D080000  /* 0024E1B4 lw $t0,0($t0) */
	.word	0x00000000  /* 0024E1B8 nop */
	.word	0x790902D0  /* 0024E1BC lq $t1,720($t0) */
	.word	0x00000000  /* 0024E1C0 nop */
	.word	0x7D2000B0  /* 0024E1C4 sq $zero,176($t1) */
	.word	0x08000000  /* 0024E1C8 j func_0024e53c */
	.reloc	.-4, R_MIPS_26, func_0024e1d0+0x36c
	.word	0x00000000  /* 0024E1CC nop */
	.end	func_0024e18c

	.section	.text.func_0024e1d0,"ax",@progbits
	.globl	func_0024e1d0
	.ent	func_0024e1d0
func_0024e1d0:  /* 0x0024E1D0 */
	.word	0x3C080000  /* 0024E1D0 lui $t0,%hi(D_0046A040) */
	.reloc	.-4, R_MIPS_HI16, D_0046A040
	.word	0x25080000  /* 0024E1D4 addiu $t0,$t0,%lo(D_0046A040) */
	.reloc	.-4, R_MIPS_LO16, D_0046A040
	.word	0x8D080000  /* 0024E1D8 lw $t0,0($t0) */
	.word	0x00000000  /* 0024E1DC nop */
	.word	0x7D100000  /* 0024E1E0 sq $s0,0($t0) */
	.word	0x7D110010  /* 0024E1E4 sq $s1,16($t0) */
	.word	0x7D120020  /* 0024E1E8 sq $s2,32($t0) */
	.word	0x7D130030  /* 0024E1EC sq $s3,48($t0) */
	.word	0x7D140040  /* 0024E1F0 sq $s4,64($t0) */
	.word	0x7D150050  /* 0024E1F4 sq $s5,80($t0) */
	.word	0x7D160060  /* 0024E1F8 sq $s6,96($t0) */
	.word	0x7D170070  /* 0024E1FC sq $s7,112($t0) */
	.word	0x7D1F0080  /* 0024E200 sq $ra,128($t0) */
	.word	0x7D1D0090  /* 0024E204 sq $sp,144($t0) */
	.word	0x7D1E00A0  /* 0024E208 sq $s8,160($t0) */
	.word	0x7D1C00B0  /* 0024E20C sq $gp,176($t0) */
	.word	0x7D1B00C0  /* 0024E210 sq $k1,192($t0) */
	.word	0xE50000D0  /* 0024E214 swc1 $f0,208($t0) */
	.word	0xE50100E0  /* 0024E218 swc1 $f1,224($t0) */
	.word	0xE50200F0  /* 0024E21C swc1 $f2,240($t0) */
	.word	0xE5030100  /* 0024E220 swc1 $f3,256($t0) */
	.word	0xE5040110  /* 0024E224 swc1 $f4,272($t0) */
	.word	0xE5050120  /* 0024E228 swc1 $f5,288($t0) */
	.word	0xE5060130  /* 0024E22C swc1 $f6,304($t0) */
	.word	0xE5070140  /* 0024E230 swc1 $f7,320($t0) */
	.word	0xE5080150  /* 0024E234 swc1 $f8,336($t0) */
	.word	0xE5090160  /* 0024E238 swc1 $f9,352($t0) */
	.word	0xE50A0170  /* 0024E23C swc1 $f10,368($t0) */
	.word	0xE50B0180  /* 0024E240 swc1 $f11,384($t0) */
	.word	0xE50C0190  /* 0024E244 swc1 $f12,400($t0) */
	.word	0xE50D01A0  /* 0024E248 swc1 $f13,416($t0) */
	.word	0xE50E01B0  /* 0024E24C swc1 $f14,432($t0) */
	.word	0xE50F01C0  /* 0024E250 swc1 $f15,448($t0) */
	.word	0xE51001D0  /* 0024E254 swc1 $f16,464($t0) */
	.word	0xE51101E0  /* 0024E258 swc1 $f17,480($t0) */
	.word	0xE51201F0  /* 0024E25C swc1 $f18,496($t0) */
	.word	0xE5130200  /* 0024E260 swc1 $f19,512($t0) */
	.word	0xE5140210  /* 0024E264 swc1 $f20,528($t0) */
	.word	0xE5150220  /* 0024E268 swc1 $f21,544($t0) */
	.word	0xE5160230  /* 0024E26C swc1 $f22,560($t0) */
	.word	0xE5170240  /* 0024E270 swc1 $f23,576($t0) */
	.word	0xE5180250  /* 0024E274 swc1 $f24,592($t0) */
	.word	0xE5190260  /* 0024E278 swc1 $f25,608($t0) */
	.word	0xE51A0270  /* 0024E27C swc1 $f26,624($t0) */
	.word	0xE51B0280  /* 0024E280 swc1 $f27,640($t0) */
	.word	0xE51C0290  /* 0024E284 swc1 $f28,656($t0) */
	.word	0xE51D02A0  /* 0024E288 swc1 $f29,672($t0) */
	.word	0xE51E02B0  /* 0024E28C swc1 $f30,688($t0) */
	.word	0xE51F02C0  /* 0024E290 swc1 $f31,704($t0) */
	.word	0x3C0C0000  /* 0024E294 lui $t4,%hi(D_0046A044) */
	.reloc	.-4, R_MIPS_HI16, D_0046A044
	.word	0x258C0000  /* 0024E298 addiu $t4,$t4,%lo(D_0046A044) */
	.reloc	.-4, R_MIPS_LO16, D_0046A044
	.word	0x8D8C0000  /* 0024E29C lw $t4,0($t4) */
	.word	0x00000000  /* 0024E2A0 nop */
	.word	0x000C7021  /* 0024E2A4 addu $t6,$zero,$t4 */
	.word	0x24090020  /* 0024E2A8 li $t1,32 */
	.word	0x00000000  /* 0024E2AC nop */
	.word	0x00000000  /* 0024E2B0 nop */
	.word	0x7DC00000  /* 0024E2B4 sq $zero,0($t6) */
	.word	0x2529FFFF  /* 0024E2B8 addiu $t1,$t1,-1 */
	.word	0x25CE0010  /* 0024E2BC addiu $t6,$t6,16 */
	.word	0x1520FFFA  /* 0024E2C0 bnez $t1,.L0024E2AC */
	.word	0x00000000  /* 0024E2C4 nop */
	.word	0x3C090000  /* 0024E2C8 lui $t1,%hi(D_0046A03C) */
	.reloc	.-4, R_MIPS_HI16, D_0046A03C
	.word	0x25290000  /* 0024E2CC addiu $t1,$t1,%lo(D_0046A03C) */
	.reloc	.-4, R_MIPS_LO16, D_0046A03C
	.word	0x8D290000  /* 0024E2D0 lw $t1,0($t1) */
	.word	0x258B0200  /* 0024E2D4 addiu $t3,$t4,512 */
	.word	0x3C0E0000  /* 0024E2D8 lui $t6,%hi(D_0046A048) */
	.reloc	.-4, R_MIPS_HI16, D_0046A048
	.word	0x25CE0000  /* 0024E2DC addiu $t6,$t6,%lo(D_0046A048) */
	.reloc	.-4, R_MIPS_LO16, D_0046A048
	.word	0x8DCA0000  /* 0024E2E0 lw $t2,0($t6) */
	.word	0x792E00B0  /* 0024E2E4 lq $t6,176($t1) */
	.word	0x254AFFFF  /* 0024E2E8 addiu $t2,$t2,-1 */
	.word	0x11C00010  /* 0024E2EC beqz $t6,.L0024E330 */
	.word	0x00000000  /* 0024E2F0 nop */
	.word	0x792E0020  /* 0024E2F4 lq $t6,32($t1) */
	.word	0x00000000  /* 0024E2F8 nop */
	.word	0x000E7140  /* 0024E2FC sll $t6,$t6,0x5 */
	.word	0x01CC7021  /* 0024E300 addu $t6,$t6,$t4 */
	.word	0x79CD0010  /* 0024E304 lq $t5,16($t6) */
	.word	0x7DCB0010  /* 0024E308 sq $t3,16($t6) */
	.word	0x15A00004  /* 0024E30C bnez $t5,.L0024E320 */
	.word	0x00000000  /* 0024E310 nop */
	.word	0x7DCB0000  /* 0024E314 sq $t3,0($t6) */
	.word	0x08000000  /* 0024E318 j .L0024E324 */
	.reloc	.-4, R_MIPS_26, func_0024e1d0+0x154
	.word	0x00000000  /* 0024E31C nop */
	.word	0x7DAB0010  /* 0024E320 sq $t3,16($t5) */
	.word	0x7D690000  /* 0024E324 sq $t1,0($t3) */
	.word	0x7D600010  /* 0024E328 sq $zero,16($t3) */
	.word	0x256B0020  /* 0024E32C addiu $t3,$t3,32 */
	.word	0x3C010001  /* 0024E330 lui $at,0x1 */
	.word	0x34210320  /* 0024E334 ori $at,$at,0x320 */
	.word	0x01214821  /* 0024E338 addu $t1,$t1,$at */
	.word	0x1540FFE9  /* 0024E33C bnez $t2,.L0024E2E4 */
	.word	0x00000000  /* 0024E340 nop */
	.word	0x7D0002F0  /* 0024E344 sq $zero,752($t0) */
	.word	0x24090010  /* 0024E348 li $t1,16 */
	.word	0x7D0902E0  /* 0024E34C sq $t1,736($t0) */
	.word	0x798A0000  /* 0024E350 lq $t2,0($t4) */
	.word	0x258C0020  /* 0024E354 addiu $t4,$t4,32 */
	.word	0x11400083  /* 0024E358 beqz $t2,.L0024E568 */
	.word	0x00000000  /* 0024E35C nop */
	.word	0x7D0C0300  /* 0024E360 sq $t4,768($t0) */
	.word	0x7D0A0310  /* 0024E364 sq $t2,784($t0) */
	.word	0x79490000  /* 0024E368 lq $t1,0($t2) */
	.word	0x790B02F0  /* 0024E36C lq $t3,752($t0) */
	.word	0x793F00B0  /* 0024E370 lq $ra,176($t1) */
	.word	0x79210310  /* 0024E374 lq $at,784($t1) */
	.word	0x256B0001  /* 0024E378 addiu $t3,$t3,1 */
	.word	0x7D0B02F0  /* 0024E37C sq $t3,752($t0) */
	.word	0x2421FFFF  /* 0024E380 addiu $at,$at,-1 */
	.word	0x7D210310  /* 0024E384 sq $at,784($t1) */
	.word	0x1420006C  /* 0024E388 bnez $at,.L0024E53C */
	.word	0x00000000  /* 0024E38C nop */
	.word	0x00092021  /* 0024E390 addu $a0,$zero,$t1 */
	.word	0xC5200100  /* 0024E394 lwc1 $f0,256($t1) */
	.word	0xC5210110  /* 0024E398 lwc1 $f1,272($t1) */
	.word	0xC5220120  /* 0024E39C lwc1 $f2,288($t1) */
	.word	0xC5230130  /* 0024E3A0 lwc1 $f3,304($t1) */
	.word	0xC5240140  /* 0024E3A4 lwc1 $f4,320($t1) */
	.word	0xC5250150  /* 0024E3A8 lwc1 $f5,336($t1) */
	.word	0xC5260160  /* 0024E3AC lwc1 $f6,352($t1) */
	.word	0xC5270170  /* 0024E3B0 lwc1 $f7,368($t1) */
	.word	0xC5280180  /* 0024E3B4 lwc1 $f8,384($t1) */
	.word	0xC5290190  /* 0024E3B8 lwc1 $f9,400($t1) */
	.word	0xC52A01A0  /* 0024E3BC lwc1 $f10,416($t1) */
	.word	0xC52B01B0  /* 0024E3C0 lwc1 $f11,432($t1) */
	.word	0xC52C01C0  /* 0024E3C4 lwc1 $f12,448($t1) */
	.word	0xC52D01D0  /* 0024E3C8 lwc1 $f13,464($t1) */
	.word	0xC52E01E0  /* 0024E3CC lwc1 $f14,480($t1) */
	.word	0xC52F01F0  /* 0024E3D0 lwc1 $f15,496($t1) */
	.word	0xC5300200  /* 0024E3D4 lwc1 $f16,512($t1) */
	.word	0xC5310210  /* 0024E3D8 lwc1 $f17,528($t1) */
	.word	0xC5320220  /* 0024E3DC lwc1 $f18,544($t1) */
	.word	0xC5330230  /* 0024E3E0 lwc1 $f19,560($t1) */
	.word	0xC5340240  /* 0024E3E4 lwc1 $f20,576($t1) */
	.word	0xC5350250  /* 0024E3E8 lwc1 $f21,592($t1) */
	.word	0xC5360260  /* 0024E3EC lwc1 $f22,608($t1) */
	.word	0xC5370270  /* 0024E3F0 lwc1 $f23,624($t1) */
	.word	0xC5380280  /* 0024E3F4 lwc1 $f24,640($t1) */
	.word	0xC5390290  /* 0024E3F8 lwc1 $f25,656($t1) */
	.word	0xC53A02A0  /* 0024E3FC lwc1 $f26,672($t1) */
	.word	0xC53B02B0  /* 0024E400 lwc1 $f27,688($t1) */
	.word	0xC53C02C0  /* 0024E404 lwc1 $f28,704($t1) */
	.word	0xC53D02D0  /* 0024E408 lwc1 $f29,720($t1) */
	.word	0xC53E02E0  /* 0024E40C lwc1 $f30,736($t1) */
	.word	0xC53F02F0  /* 0024E410 lwc1 $f31,752($t1) */
	.word	0x79280300  /* 0024E414 lq $t0,768($t1) */
	.word	0x79300030  /* 0024E418 lq $s0,48($t1) */
	.word	0x79310040  /* 0024E41C lq $s1,64($t1) */
	.word	0x79320050  /* 0024E420 lq $s2,80($t1) */
	.word	0x79330060  /* 0024E424 lq $s3,96($t1) */
	.word	0x79340070  /* 0024E428 lq $s4,112($t1) */
	.word	0x79350080  /* 0024E42C lq $s5,128($t1) */
	.word	0x79360090  /* 0024E430 lq $s6,144($t1) */
	.word	0x793700A0  /* 0024E434 lq $s7,160($t1) */
	.word	0x15000004  /* 0024E438 bnez $t0,.L0024E44C */
	.word	0x00000000  /* 0024E43C nop */
	.word	0x793E00D0  /* 0024E440 lq $s8,208($t1) */
	.word	0x793C00E0  /* 0024E444 lq $gp,224($t1) */
	.word	0x793B00F0  /* 0024E448 lq $k1,240($t1) */
	.word	0x3C080000  /* 0024E44C lui $t0,%hi(D_0046A040) */
	.reloc	.-4, R_MIPS_HI16, D_0046A040
	.word	0x25080000  /* 0024E450 addiu $t0,$t0,%lo(D_0046A040) */
	.reloc	.-4, R_MIPS_LO16, D_0046A040
	.word	0x8D080000  /* 0024E454 lw $t0,0($t0) */
	.word	0x793D00C0  /* 0024E458 lq $sp,192($t1) */
	.word	0x7D0902D0  /* 0024E45C sq $t1,720($t0) */
	.word	0x03E00008  /* 0024E460 jr $ra */
	.word	0x00000000  /* 0024E464 nop */
	.word	0x3C080000  /* 0024E468 lui $t0,%hi(D_0046A040) */
	.reloc	.-4, R_MIPS_HI16, D_0046A040
	.word	0x25080000  /* 0024E46C addiu $t0,$t0,%lo(D_0046A040) */
	.reloc	.-4, R_MIPS_LO16, D_0046A040
	.word	0x8D080000  /* 0024E470 lw $t0,0($t0) */
	.word	0x00000000  /* 0024E474 nop */
	.word	0x790902D0  /* 0024E478 lq $t1,720($t0) */
	.word	0x00000000  /* 0024E47C nop */
	.word	0xE5200100  /* 0024E480 swc1 $f0,256($t1) */
	.word	0xE5210110  /* 0024E484 swc1 $f1,272($t1) */
	.word	0xE5220120  /* 0024E488 swc1 $f2,288($t1) */
	.word	0xE5230130  /* 0024E48C swc1 $f3,304($t1) */
	.word	0xE5240140  /* 0024E490 swc1 $f4,320($t1) */
	.word	0xE5250150  /* 0024E494 swc1 $f5,336($t1) */
	.word	0xE5260160  /* 0024E498 swc1 $f6,352($t1) */
	.word	0xE5270170  /* 0024E49C swc1 $f7,368($t1) */
	.word	0xE5280180  /* 0024E4A0 swc1 $f8,384($t1) */
	.word	0xE5290190  /* 0024E4A4 swc1 $f9,400($t1) */
	.word	0xE52A01A0  /* 0024E4A8 swc1 $f10,416($t1) */
	.word	0xE52B01B0  /* 0024E4AC swc1 $f11,432($t1) */
	.word	0xE52C01C0  /* 0024E4B0 swc1 $f12,448($t1) */
	.word	0xE52D01D0  /* 0024E4B4 swc1 $f13,464($t1) */
	.word	0xE52E01E0  /* 0024E4B8 swc1 $f14,480($t1) */
	.word	0xE52F01F0  /* 0024E4BC swc1 $f15,496($t1) */
	.word	0xE5300200  /* 0024E4C0 swc1 $f16,512($t1) */
	.word	0xE5310210  /* 0024E4C4 swc1 $f17,528($t1) */
	.word	0xE5320220  /* 0024E4C8 swc1 $f18,544($t1) */
	.word	0xE5330230  /* 0024E4CC swc1 $f19,560($t1) */
	.word	0xE5340240  /* 0024E4D0 swc1 $f20,576($t1) */
	.word	0xE5350250  /* 0024E4D4 swc1 $f21,592($t1) */
	.word	0xE5360260  /* 0024E4D8 swc1 $f22,608($t1) */
	.word	0xE5370270  /* 0024E4DC swc1 $f23,624($t1) */
	.word	0xE5380280  /* 0024E4E0 swc1 $f24,640($t1) */
	.word	0xE5390290  /* 0024E4E4 swc1 $f25,656($t1) */
	.word	0xE53A02A0  /* 0024E4E8 swc1 $f26,672($t1) */
	.word	0xE53B02B0  /* 0024E4EC swc1 $f27,688($t1) */
	.word	0xE53C02C0  /* 0024E4F0 swc1 $f28,704($t1) */
	.word	0xE53D02D0  /* 0024E4F4 swc1 $f29,720($t1) */
	.word	0xE53E02E0  /* 0024E4F8 swc1 $f30,736($t1) */
	.word	0xE53F02F0  /* 0024E4FC swc1 $f31,752($t1) */
	.word	0x7D200300  /* 0024E500 sq $zero,768($t1) */
	.word	0x7D300030  /* 0024E504 sq $s0,48($t1) */
	.word	0x7D310040  /* 0024E508 sq $s1,64($t1) */
	.word	0x7D320050  /* 0024E50C sq $s2,80($t1) */
	.word	0x7D330060  /* 0024E510 sq $s3,96($t1) */
	.word	0x7D340070  /* 0024E514 sq $s4,112($t1) */
	.word	0x7D350080  /* 0024E518 sq $s5,128($t1) */
	.word	0x7D360090  /* 0024E51C sq $s6,144($t1) */
	.word	0x7D3700A0  /* 0024E520 sq $s7,160($t1) */
	.word	0x7D3F00B0  /* 0024E524 sq $ra,176($t1) */
	.word	0x7D3D00C0  /* 0024E528 sq $sp,192($t1) */
	.word	0x7D3E00D0  /* 0024E52C sq $s8,208($t1) */
	.word	0x7D3C00E0  /* 0024E530 sq $gp,224($t1) */
	.word	0x7D3B00F0  /* 0024E534 sq $k1,240($t1) */
	.word	0x7D240310  /* 0024E538 sq $a0,784($t1) */
	.word	0x3C080000  /* 0024E53C lui $t0,%hi(D_0046A040) */
	.reloc	.-4, R_MIPS_HI16, D_0046A040
	.word	0x25080000  /* 0024E540 addiu $t0,$t0,%lo(D_0046A040) */
	.reloc	.-4, R_MIPS_LO16, D_0046A040
	.word	0x8D080000  /* 0024E544 lw $t0,0($t0) */
	.word	0x00000000  /* 0024E548 nop */
	.word	0x790A0310  /* 0024E54C lq $t2,784($t0) */
	.word	0x790C0300  /* 0024E550 lq $t4,768($t0) */
	.word	0x794A0010  /* 0024E554 lq $t2,16($t2) */
	.word	0x00000000  /* 0024E558 nop */
	.word	0x7D0A0310  /* 0024E55C sq $t2,784($t0) */
	.word	0x1540FF81  /* 0024E560 bnez $t2,.L0024E368 */
	.word	0x00000000  /* 0024E564 nop */
	.word	0x790102E0  /* 0024E568 lq $at,736($t0) */
	.word	0x00000000  /* 0024E56C nop */
	.word	0x2421FFFF  /* 0024E570 addiu $at,$at,-1 */
	.word	0x7D0102E0  /* 0024E574 sq $at,736($t0) */
	.word	0x1420FF75  /* 0024E578 bnez $at,.L0024E350 */
	.word	0x00000000  /* 0024E57C nop */
	.word	0x790202F0  /* 0024E580 lq $v0,752($t0) */
	.word	0x79100000  /* 0024E584 lq $s0,0($t0) */
	.word	0x79110010  /* 0024E588 lq $s1,16($t0) */
	.word	0x79120020  /* 0024E58C lq $s2,32($t0) */
	.word	0x79130030  /* 0024E590 lq $s3,48($t0) */
	.word	0x79140040  /* 0024E594 lq $s4,64($t0) */
	.word	0x79150050  /* 0024E598 lq $s5,80($t0) */
	.word	0x79160060  /* 0024E59C lq $s6,96($t0) */
	.word	0x79170070  /* 0024E5A0 lq $s7,112($t0) */
	.word	0x791F0080  /* 0024E5A4 lq $ra,128($t0) */
	.word	0x791D0090  /* 0024E5A8 lq $sp,144($t0) */
	.word	0x791E00A0  /* 0024E5AC lq $s8,160($t0) */
	.word	0x791C00B0  /* 0024E5B0 lq $gp,176($t0) */
	.word	0x791B00C0  /* 0024E5B4 lq $k1,192($t0) */
	.word	0xC50000D0  /* 0024E5B8 lwc1 $f0,208($t0) */
	.word	0xC50100E0  /* 0024E5BC lwc1 $f1,224($t0) */
	.word	0xC50200F0  /* 0024E5C0 lwc1 $f2,240($t0) */
	.word	0xC5030100  /* 0024E5C4 lwc1 $f3,256($t0) */
	.word	0xC5040110  /* 0024E5C8 lwc1 $f4,272($t0) */
	.word	0xC5050120  /* 0024E5CC lwc1 $f5,288($t0) */
	.word	0xC5060130  /* 0024E5D0 lwc1 $f6,304($t0) */
	.word	0xC5070140  /* 0024E5D4 lwc1 $f7,320($t0) */
	.word	0xC5080150  /* 0024E5D8 lwc1 $f8,336($t0) */
	.word	0xC5090160  /* 0024E5DC lwc1 $f9,352($t0) */
	.word	0xC50A0170  /* 0024E5E0 lwc1 $f10,368($t0) */
	.word	0xC50B0180  /* 0024E5E4 lwc1 $f11,384($t0) */
	.word	0xC50C0190  /* 0024E5E8 lwc1 $f12,400($t0) */
	.word	0xC50D01A0  /* 0024E5EC lwc1 $f13,416($t0) */
	.word	0xC50E01B0  /* 0024E5F0 lwc1 $f14,432($t0) */
	.word	0xC50F01C0  /* 0024E5F4 lwc1 $f15,448($t0) */
	.word	0xC51001D0  /* 0024E5F8 lwc1 $f16,464($t0) */
	.word	0xC51101E0  /* 0024E5FC lwc1 $f17,480($t0) */
	.word	0xC51201F0  /* 0024E600 lwc1 $f18,496($t0) */
	.word	0xC5130200  /* 0024E604 lwc1 $f19,512($t0) */
	.word	0xC5140210  /* 0024E608 lwc1 $f20,528($t0) */
	.word	0xC5150220  /* 0024E60C lwc1 $f21,544($t0) */
	.word	0xC5160230  /* 0024E610 lwc1 $f22,560($t0) */
	.word	0xC5170240  /* 0024E614 lwc1 $f23,576($t0) */
	.word	0xC5180250  /* 0024E618 lwc1 $f24,592($t0) */
	.word	0xC5190260  /* 0024E61C lwc1 $f25,608($t0) */
	.word	0xC51A0270  /* 0024E620 lwc1 $f26,624($t0) */
	.word	0xC51B0280  /* 0024E624 lwc1 $f27,640($t0) */
	.word	0xC51C0290  /* 0024E628 lwc1 $f28,656($t0) */
	.word	0xC51D02A0  /* 0024E62C lwc1 $f29,672($t0) */
	.word	0xC51E02B0  /* 0024E630 lwc1 $f30,688($t0) */
	.word	0xC51F02C0  /* 0024E634 lwc1 $f31,704($t0) */
	.word	0x03E00008  /* 0024E638 jr $ra */
	.word	0x00000000  /* 0024E63C nop */
	.end	func_0024e1d0

	.section	.text.func_0024e640,"ax",@progbits
	.globl	func_0024e640
	.ent	func_0024e640
func_0024e640:  /* 0x0024E640 */
	.word	0xAC9F0000  /* 0024E640 sw $ra,0($a0) */
	.word	0xAC9D0004  /* 0024E644 sw $sp,4($a0) */
	.word	0xAC900008  /* 0024E648 sw $s0,8($a0) */
	.word	0x0085E821  /* 0024E64C addu $sp,$a0,$a1 */
	.word	0x27BDFFF0  /* 0024E650 addiu $sp,$sp,-16 */
	.word	0x00048021  /* 0024E654 addu $s0,$zero,$a0 */
	.word	0x00060821  /* 0024E658 addu $at,$zero,$a2 */
	.word	0x0020F809  /* 0024E65C jalr $at */
	.word	0x00072021  /* 0024E660 addu $a0,$zero,$a3 */
	.word	0x8E1F0000  /* 0024E664 lw $ra,0($s0) */
	.word	0x8E1D0004  /* 0024E668 lw $sp,4($s0) */
	.word	0x8E100008  /* 0024E66C lw $s0,8($s0) */
	.word	0x03E00008  /* 0024E670 jr $ra */
	.word	0x00000000  /* 0024E674 nop */
	.end	func_0024e640

	.section	.text.func_0024e678,"ax",@progbits
	.globl	func_0024e678
	.ent	func_0024e678
func_0024e678:  /* 0x0024E678 */
	.word	0x3C090000  /* 0024E678 lui $t1,%hi(printf) */
	.reloc	.-4, R_MIPS_HI16, printf
	.word	0x25290000  /* 0024E67C addiu $t1,$t1,%lo(printf) */
	.reloc	.-4, R_MIPS_LO16, printf
	.word	0x3C080000  /* 0024E680 lui $t0,%hi(func_0024e6d0) */
	.reloc	.-4, R_MIPS_HI16, func_0024e678+0x58
	.word	0x25080000  /* 0024E684 addiu $t0,$t0,%lo(func_0024e6d0) */
	.reloc	.-4, R_MIPS_LO16, func_0024e678+0x58
	.word	0x8D210000  /* 0024E688 lw $at,0($t1) */
	.word	0xAD010000  /* 0024E68C sw $at,0($t0) */
	.word	0x8D210004  /* 0024E690 lw $at,4($t1) */
	.word	0xAD010004  /* 0024E694 sw $at,4($t0) */
	.word	0x00045821  /* 0024E698 addu $t3,$zero,$a0 */
	.word	0x240A0080  /* 0024E69C li $t2,128 */
	.word	0x000A5500  /* 0024E6A0 sll $t2,$t2,0x14 */
	.word	0x000B5882  /* 0024E6A4 srl $t3,$t3,0x2 */
	.word	0x016A5825  /* 0024E6A8 or $t3,$t3,$t2 */
	.word	0xAD2B0000  /* 0024E6AC sw $t3,0($t1) */
	.word	0xAD200004  /* 0024E6B0 sw $zero,4($t1) */
	.word	0x25210008  /* 0024E6B4 addiu $at,$t1,8 */
	.word	0x00010882  /* 0024E6B8 srl $at,$at,0x2 */
	.word	0x002A0825  /* 0024E6BC or $at,$at,$t2 */
	.word	0xAD010008  /* 0024E6C0 sw $at,8($t0) */
	.word	0xAD00000C  /* 0024E6C4 sw $zero,12($t0) */
	.word	0x03E00008  /* 0024E6C8 jr $ra */
	.word	0x00000000  /* 0024E6CC nop */
	.end	func_0024e678

	.section	.text.func_0024e6e0,"ax",@progbits
	.globl	func_0024e6e0
	.ent	func_0024e6e0
func_0024e6e0:  /* 0x0024E6E0 */
	.word	0x08000000  /* 0024E6E0 j printf */
	.reloc	.-4, R_MIPS_26, printf
	.word	0x00000000  /* 0024E6E4 nop */
	.end	func_0024e6e0

	.section	.text.func_0024e6e8,"ax",@progbits
	.globl	func_0024e6e8
	.ent	func_0024e6e8
func_0024e6e8:  /* 0x0024E6E8 */
	.word	0x0005C882  /* 0024E6E8 srl $t9,$a1,0x2 */
	.word	0x00807821  /* 0024E6EC move $t7,$a0 */
	.word	0x00807021  /* 0024E6F0 move $t6,$a0 */
	.word	0x3C0D00FF  /* 0024E6F4 lui $t5,0xff */
	.word	0x35ADFFFF  /* 0024E6F8 ori $t5,$t5,0xffff */
	.word	0xDDC80000  /* 0024E6FC ld $t0,0($t6) */
	.word	0xDDCA0008  /* 0024E700 ld $t2,8($t6) */
	.word	0x2739FFFF  /* 0024E704 addiu $t9,$t9,-1 */
	.word	0x25CE0010  /* 0024E708 addiu $t6,$t6,16 */
	.word	0x0008483E  /* 0024E70C dsrl32 $t1,$t0,0x0 */
	.word	0x010D4024  /* 0024E710 and $t0,$t0,$t5 */
	.word	0x00096600  /* 0024E714 sll $t4,$t1,0x18 */
	.word	0x010C4025  /* 0024E718 or $t0,$t0,$t4 */
	.word	0x00094A02  /* 0024E71C srl $t1,$t1,0x8 */
	.word	0x3129FFFF  /* 0024E720 andi $t1,$t1,0xffff */
	.word	0xADE80000  /* 0024E724 sw $t0,0($t7) */
	.word	0x000A583E  /* 0024E728 dsrl32 $t3,$t2,0x0 */
	.word	0x000A6400  /* 0024E72C sll $t4,$t2,0x10 */
	.word	0x012C4825  /* 0024E730 or $t1,$t1,$t4 */
	.word	0x014D5024  /* 0024E734 and $t2,$t2,$t5 */
	.word	0x000A5402  /* 0024E738 srl $t2,$t2,0x10 */
	.word	0x000B5A00  /* 0024E73C sll $t3,$t3,0x8 */
	.word	0x014B5025  /* 0024E740 or $t2,$t2,$t3 */
	.word	0xADE90004  /* 0024E744 sw $t1,4($t7) */
	.word	0xADEA0008  /* 0024E748 sw $t2,8($t7) */
	.word	0x1720FFEB  /* 0024E74C bnez $t9,.L0024E6FC */
	.word	0x25EF000C  /* 0024E750 addiu $t7,$t7,12 */
	.word	0x03E00008  /* 0024E754 jr $ra */
	.word	0x00000000  /* 0024E758 nop */
	.end	func_0024e6e8

	.section	.text.func_0024e75c,"ax",@progbits
	.globl	func_0024e75c
	.ent	func_0024e75c
func_0024e75c:  /* 0x0024E75C */
	.word	0x00046021  /* 0024E75C addu $t4,$zero,$a0 */
	.word	0x24840005  /* 0024E760 addiu $a0,$a0,5 */
	.word	0x24AA07FF  /* 0024E764 addiu $t2,$a1,2047 */
	.word	0x00055821  /* 0024E768 addu $t3,$zero,$a1 */
	.word	0x90990000  /* 0024E76C lbu $t9,0($a0) */
	.word	0x24840001  /* 0024E770 addiu $a0,$a0,1 */
	.word	0x33210080  /* 0024E774 andi $at,$t9,0x80 */
	.word	0x1420001F  /* 0024E778 bnez $at,.L0024E7F8 */
	.word	0x2721FF82  /* 0024E77C addiu $at,$t9,-126 */
	.word	0x04200045  /* 0024E780 bltz $at,.L0024E898 */
	.word	0x00000000  /* 0024E784 nop */
	.word	0x1020000F  /* 0024E788 beqz $at,.L0024E7C8 */
	.word	0x00000000  /* 0024E78C nop */
	.word	0x908F0001  /* 0024E790 lbu $t7,1($a0) */
	.word	0x90980000  /* 0024E794 lbu $t8,0($a0) */
	.word	0x000F7A00  /* 0024E798 sll $t7,$t7,0x8 */
	.word	0x01F87825  /* 0024E79C or $t7,$t7,$t8 */
	.word	0x908E0002  /* 0024E7A0 lbu $t6,2($a0) */
	.word	0x25EFFFFF  /* 0024E7A4 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024E7A8 sb $t6,0($a1) */
	.word	0x24A50001  /* 0024E7AC addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024E7B0 nop */
	.word	0x00000000  /* 0024E7B4 nop */
	.word	0x15E0FFFA  /* 0024E7B8 bnez $t7,.L0024E7A4 */
	.word	0x00000000  /* 0024E7BC nop */
	.word	0x08000000  /* 0024E7C0 j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x24840003  /* 0024E7C4 addiu $a0,$a0,3 */
	.word	0x908F0000  /* 0024E7C8 lbu $t7,0($a0) */
	.word	0x908E0001  /* 0024E7CC lbu $t6,1($a0) */
	.word	0x25EF0004  /* 0024E7D0 addiu $t7,$t7,4 */
	.word	0x25EFFFFF  /* 0024E7D4 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024E7D8 sb $t6,0($a1) */
	.word	0x24A50001  /* 0024E7DC addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024E7E0 nop */
	.word	0x00000000  /* 0024E7E4 nop */
	.word	0x15E0FFFA  /* 0024E7E8 bnez $t7,.L0024E7D4 */
	.word	0x00000000  /* 0024E7EC nop */
	.word	0x08000000  /* 0024E7F0 j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x24840002  /* 0024E7F4 addiu $a0,$a0,2 */
	.word	0x001978C2  /* 0024E7F8 srl $t7,$t9,0x3 */
	.word	0x31EF000F  /* 0024E7FC andi $t7,$t7,0xf */
	.word	0x25EF0003  /* 0024E800 addiu $t7,$t7,3 */
	.word	0x33210007  /* 0024E804 andi $at,$t9,0x7 */
	.word	0x908E0000  /* 0024E808 lbu $t6,0($a0) */
	.word	0x24840001  /* 0024E80C addiu $a0,$a0,1 */
	.word	0x00010A00  /* 0024E810 sll $at,$at,0x8 */
	.word	0x01C17025  /* 0024E814 or $t6,$t6,$at */
	.word	0x25CE0001  /* 0024E818 addiu $t6,$t6,1 */
	.word	0x0145082B  /* 0024E81C sltu $at,$t2,$a1 */
	.word	0x1020000B  /* 0024E820 beqz $at,.L0024E850 */
	.word	0x00000000  /* 0024E824 nop */
	.word	0x00AE6823  /* 0024E828 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024E82C lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024E830 addiu $t7,$t7,-1 */
	.word	0x25AD0001  /* 0024E834 addiu $t5,$t5,1 */
	.word	0xA0A10000  /* 0024E838 sb $at,0($a1) */
	.word	0x24A50001  /* 0024E83C addiu $a1,$a1,1 */
	.word	0x15E0FFFA  /* 0024E840 bnez $t7,.L0024E82C */
	.word	0x00000000  /* 0024E844 nop */
	.word	0x08000000  /* 0024E848 j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x00000000  /* 0024E84C nop */
	.word	0x01CB0821  /* 0024E850 addu $at,$t6,$t3 */
	.word	0x00A1082B  /* 0024E854 sltu $at,$a1,$at */
	.word	0x14200009  /* 0024E858 bnez $at,.L0024E880 */
	.word	0x00000000  /* 0024E85C nop */
	.word	0x00AE6823  /* 0024E860 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024E864 lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024E868 addiu $t7,$t7,-1 */
	.word	0xA0A10000  /* 0024E86C sb $at,0($a1) */
	.word	0x15E0FFF7  /* 0024E870 bnez $t7,.L0024E850 */
	.word	0x24A50001  /* 0024E874 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024E878 j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x00000000  /* 0024E87C nop */
	.word	0xA0A00000  /* 0024E880 sb $zero,0($a1) */
	.word	0x25EFFFFF  /* 0024E884 addiu $t7,$t7,-1 */
	.word	0x15E0FFF1  /* 0024E888 bnez $t7,.L0024E850 */
	.word	0x24A50001  /* 0024E88C addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024E890 j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x00000000  /* 0024E894 nop */
	.word	0x1320000A  /* 0024E898 beqz $t9,.L0024E8C4 */
	.word	0x00000000  /* 0024E89C nop */
	.word	0x90810000  /* 0024E8A0 lbu $at,0($a0) */
	.word	0x24840001  /* 0024E8A4 addiu $a0,$a0,1 */
	.word	0x2739FFFF  /* 0024E8A8 addiu $t9,$t9,-1 */
	.word	0xA0A10000  /* 0024E8AC sb $at,0($a1) */
	.word	0x24A50001  /* 0024E8B0 addiu $a1,$a1,1 */
	.word	0x1720FFFA  /* 0024E8B4 bnez $t9,.L0024E8A0 */
	.word	0x00000000  /* 0024E8B8 nop */
	.word	0x08000000  /* 0024E8BC j .L0024E76C */
	.reloc	.-4, R_MIPS_26, func_0024e75c+0x10
	.word	0x00000000  /* 0024E8C0 nop */
	.word	0x00AB0823  /* 0024E8C4 subu $at,$a1,$t3 */
	.word	0xACC10000  /* 0024E8C8 sw $at,0($a2) */
	.word	0x03E00008  /* 0024E8CC jr $ra */
	.word	0x008C1023  /* 0024E8D0 subu $v0,$a0,$t4 */
	.end	func_0024e75c

	.section	.text.func_0024e8d4,"ax",@progbits
	.globl	func_0024e8d4
	.ent	func_0024e8d4
func_0024e8d4:  /* 0x0024E8D4 */
	.word	0x00046021  /* 0024E8D4 addu $t4,$zero,$a0 */
	.word	0x24840005  /* 0024E8D8 addiu $a0,$a0,5 */
	.word	0x24AA0FFF  /* 0024E8DC addiu $t2,$a1,4095 */
	.word	0x00055821  /* 0024E8E0 addu $t3,$zero,$a1 */
	.word	0x90990000  /* 0024E8E4 lbu $t9,0($a0) */
	.word	0x24840001  /* 0024E8E8 addiu $a0,$a0,1 */
	.word	0x33210080  /* 0024E8EC andi $at,$t9,0x80 */
	.word	0x1420001F  /* 0024E8F0 bnez $at,.L0024E970 */
	.word	0x2721FF82  /* 0024E8F4 addiu $at,$t9,-126 */
	.word	0x04200045  /* 0024E8F8 bltz $at,.L0024EA10 */
	.word	0x00000000  /* 0024E8FC nop */
	.word	0x1020000F  /* 0024E900 beqz $at,.L0024E940 */
	.word	0x00000000  /* 0024E904 nop */
	.word	0x908F0001  /* 0024E908 lbu $t7,1($a0) */
	.word	0x90980000  /* 0024E90C lbu $t8,0($a0) */
	.word	0x000F7A00  /* 0024E910 sll $t7,$t7,0x8 */
	.word	0x01F87825  /* 0024E914 or $t7,$t7,$t8 */
	.word	0x908E0002  /* 0024E918 lbu $t6,2($a0) */
	.word	0x25EFFFFF  /* 0024E91C addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024E920 sb $t6,0($a1) */
	.word	0x24A50001  /* 0024E924 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024E928 nop */
	.word	0x00000000  /* 0024E92C nop */
	.word	0x15E0FFFA  /* 0024E930 bnez $t7,.L0024E91C */
	.word	0x00000000  /* 0024E934 nop */
	.word	0x08000000  /* 0024E938 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x24840003  /* 0024E93C addiu $a0,$a0,3 */
	.word	0x908F0000  /* 0024E940 lbu $t7,0($a0) */
	.word	0x908E0001  /* 0024E944 lbu $t6,1($a0) */
	.word	0x25EF0004  /* 0024E948 addiu $t7,$t7,4 */
	.word	0x25EFFFFF  /* 0024E94C addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024E950 sb $t6,0($a1) */
	.word	0x24A50001  /* 0024E954 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024E958 nop */
	.word	0x00000000  /* 0024E95C nop */
	.word	0x15E0FFFA  /* 0024E960 bnez $t7,.L0024E94C */
	.word	0x00000000  /* 0024E964 nop */
	.word	0x08000000  /* 0024E968 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x24840002  /* 0024E96C addiu $a0,$a0,2 */
	.word	0x00197902  /* 0024E970 srl $t7,$t9,0x4 */
	.word	0x31EF0007  /* 0024E974 andi $t7,$t7,0x7 */
	.word	0x25EF0003  /* 0024E978 addiu $t7,$t7,3 */
	.word	0x3321000F  /* 0024E97C andi $at,$t9,0xf */
	.word	0x908E0000  /* 0024E980 lbu $t6,0($a0) */
	.word	0x24840001  /* 0024E984 addiu $a0,$a0,1 */
	.word	0x00010A00  /* 0024E988 sll $at,$at,0x8 */
	.word	0x01C17025  /* 0024E98C or $t6,$t6,$at */
	.word	0x25CE0001  /* 0024E990 addiu $t6,$t6,1 */
	.word	0x0145082B  /* 0024E994 sltu $at,$t2,$a1 */
	.word	0x1020000B  /* 0024E998 beqz $at,.L0024E9C8 */
	.word	0x00000000  /* 0024E99C nop */
	.word	0x00AE6823  /* 0024E9A0 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024E9A4 lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024E9A8 addiu $t7,$t7,-1 */
	.word	0x25AD0001  /* 0024E9AC addiu $t5,$t5,1 */
	.word	0xA0A10000  /* 0024E9B0 sb $at,0($a1) */
	.word	0x24A50001  /* 0024E9B4 addiu $a1,$a1,1 */
	.word	0x15E0FFFA  /* 0024E9B8 bnez $t7,.L0024E9A4 */
	.word	0x00000000  /* 0024E9BC nop */
	.word	0x08000000  /* 0024E9C0 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x00000000  /* 0024E9C4 nop */
	.word	0x01CB0821  /* 0024E9C8 addu $at,$t6,$t3 */
	.word	0x00A1082B  /* 0024E9CC sltu $at,$a1,$at */
	.word	0x14200009  /* 0024E9D0 bnez $at,.L0024E9F8 */
	.word	0x00000000  /* 0024E9D4 nop */
	.word	0x00AE6823  /* 0024E9D8 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024E9DC lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024E9E0 addiu $t7,$t7,-1 */
	.word	0xA0A10000  /* 0024E9E4 sb $at,0($a1) */
	.word	0x15E0FFF7  /* 0024E9E8 bnez $t7,.L0024E9C8 */
	.word	0x24A50001  /* 0024E9EC addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024E9F0 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x00000000  /* 0024E9F4 nop */
	.word	0xA0A00000  /* 0024E9F8 sb $zero,0($a1) */
	.word	0x25EFFFFF  /* 0024E9FC addiu $t7,$t7,-1 */
	.word	0x15E0FFF1  /* 0024EA00 bnez $t7,.L0024E9C8 */
	.word	0x24A50001  /* 0024EA04 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024EA08 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x00000000  /* 0024EA0C nop */
	.word	0x1320000A  /* 0024EA10 beqz $t9,.L0024EA3C */
	.word	0x00000000  /* 0024EA14 nop */
	.word	0x90810000  /* 0024EA18 lbu $at,0($a0) */
	.word	0x24840001  /* 0024EA1C addiu $a0,$a0,1 */
	.word	0x2739FFFF  /* 0024EA20 addiu $t9,$t9,-1 */
	.word	0xA0A10000  /* 0024EA24 sb $at,0($a1) */
	.word	0x24A50001  /* 0024EA28 addiu $a1,$a1,1 */
	.word	0x1720FFFA  /* 0024EA2C bnez $t9,.L0024EA18 */
	.word	0x00000000  /* 0024EA30 nop */
	.word	0x08000000  /* 0024EA34 j .L0024E8E4 */
	.reloc	.-4, R_MIPS_26, func_0024e8d4+0x10
	.word	0x00000000  /* 0024EA38 nop */
	.word	0x00AB0823  /* 0024EA3C subu $at,$a1,$t3 */
	.word	0xACC10000  /* 0024EA40 sw $at,0($a2) */
	.word	0x03E00008  /* 0024EA44 jr $ra */
	.word	0x008C1023  /* 0024EA48 subu $v0,$a0,$t4 */
	.end	func_0024e8d4

	.section	.text.func_0024ea4c,"ax",@progbits
	.globl	func_0024ea4c
	.ent	func_0024ea4c
func_0024ea4c:  /* 0x0024EA4C */
	.word	0x001F6021  /* 0024EA4C addu $t4,$zero,$ra */
	.word	0x00C43021  /* 0024EA50 addu $a2,$a2,$a0 */
	.word	0x00004021  /* 0024EA54 move $t0,$zero */
	.word	0x24840005  /* 0024EA58 addiu $a0,$a0,5 */
	.word	0x24AA07FF  /* 0024EA5C addiu $t2,$a1,2047 */
	.word	0x00055821  /* 0024EA60 addu $t3,$zero,$a1 */
	.word	0x90990000  /* 0024EA64 lbu $t9,0($a0) */
	.word	0x0C000000  /* 0024EA68 jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EA6C addiu $a0,$a0,1 */
	.word	0x33210080  /* 0024EA70 andi $at,$t9,0x80 */
	.word	0x14200029  /* 0024EA74 bnez $at,.L0024EB1C */
	.word	0x2721FF82  /* 0024EA78 addiu $at,$t9,-126 */
	.word	0x04200050  /* 0024EA7C bltz $at,.L0024EBC0 */
	.word	0x00000000  /* 0024EA80 nop */
	.word	0x10200015  /* 0024EA84 beqz $at,.L0024EADC */
	.word	0x00000000  /* 0024EA88 nop */
	.word	0x90980000  /* 0024EA8C lbu $t8,0($a0) */
	.word	0x0C000000  /* 0024EA90 jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EA94 addiu $a0,$a0,1 */
	.word	0x908F0000  /* 0024EA98 lbu $t7,0($a0) */
	.word	0x0C000000  /* 0024EA9C jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EAA0 addiu $a0,$a0,1 */
	.word	0x000F7A00  /* 0024EAA4 sll $t7,$t7,0x8 */
	.word	0x01F87825  /* 0024EAA8 or $t7,$t7,$t8 */
	.word	0x908E0000  /* 0024EAAC lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024EAB0 jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EAB4 addiu $a0,$a0,1 */
	.word	0x25EFFFFF  /* 0024EAB8 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024EABC sb $t6,0($a1) */
	.word	0x24A50001  /* 0024EAC0 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024EAC4 nop */
	.word	0x00000000  /* 0024EAC8 nop */
	.word	0x15E0FFFA  /* 0024EACC bnez $t7,.L0024EAB8 */
	.word	0x00000000  /* 0024EAD0 nop */
	.word	0x08000000  /* 0024EAD4 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EAD8 nop */
	.word	0x908F0000  /* 0024EADC lbu $t7,0($a0) */
	.word	0x0C000000  /* 0024EAE0 jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EAE4 addiu $a0,$a0,1 */
	.word	0x908E0000  /* 0024EAE8 lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024EAEC jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EAF0 addiu $a0,$a0,1 */
	.word	0x25EF0004  /* 0024EAF4 addiu $t7,$t7,4 */
	.word	0x25EFFFFF  /* 0024EAF8 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024EAFC sb $t6,0($a1) */
	.word	0x24A50001  /* 0024EB00 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024EB04 nop */
	.word	0x00000000  /* 0024EB08 nop */
	.word	0x15E0FFFA  /* 0024EB0C bnez $t7,.L0024EAF8 */
	.word	0x00000000  /* 0024EB10 nop */
	.word	0x08000000  /* 0024EB14 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EB18 nop */
	.word	0x001978C2  /* 0024EB1C srl $t7,$t9,0x3 */
	.word	0x31EF000F  /* 0024EB20 andi $t7,$t7,0xf */
	.word	0x25EF0003  /* 0024EB24 addiu $t7,$t7,3 */
	.word	0x33210007  /* 0024EB28 andi $at,$t9,0x7 */
	.word	0x908E0000  /* 0024EB2C lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024EB30 jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EB34 addiu $a0,$a0,1 */
	.word	0x00010A00  /* 0024EB38 sll $at,$at,0x8 */
	.word	0x01C17025  /* 0024EB3C or $t6,$t6,$at */
	.word	0x25CE0001  /* 0024EB40 addiu $t6,$t6,1 */
	.word	0x0145082B  /* 0024EB44 sltu $at,$t2,$a1 */
	.word	0x1020000B  /* 0024EB48 beqz $at,.L0024EB78 */
	.word	0x00000000  /* 0024EB4C nop */
	.word	0x00AE6823  /* 0024EB50 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024EB54 lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024EB58 addiu $t7,$t7,-1 */
	.word	0x25AD0001  /* 0024EB5C addiu $t5,$t5,1 */
	.word	0xA0A10000  /* 0024EB60 sb $at,0($a1) */
	.word	0x24A50001  /* 0024EB64 addiu $a1,$a1,1 */
	.word	0x15E0FFFA  /* 0024EB68 bnez $t7,.L0024EB54 */
	.word	0x00000000  /* 0024EB6C nop */
	.word	0x08000000  /* 0024EB70 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EB74 nop */
	.word	0x01CB0821  /* 0024EB78 addu $at,$t6,$t3 */
	.word	0x00A1082B  /* 0024EB7C sltu $at,$a1,$at */
	.word	0x14200009  /* 0024EB80 bnez $at,.L0024EBA8 */
	.word	0x00000000  /* 0024EB84 nop */
	.word	0x00AE6823  /* 0024EB88 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024EB8C lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024EB90 addiu $t7,$t7,-1 */
	.word	0xA0A10000  /* 0024EB94 sb $at,0($a1) */
	.word	0x15E0FFF7  /* 0024EB98 bnez $t7,.L0024EB78 */
	.word	0x24A50001  /* 0024EB9C addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024EBA0 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EBA4 nop */
	.word	0xA0A00000  /* 0024EBA8 sb $zero,0($a1) */
	.word	0x25EFFFFF  /* 0024EBAC addiu $t7,$t7,-1 */
	.word	0x15E0FFF1  /* 0024EBB0 bnez $t7,.L0024EB78 */
	.word	0x24A50001  /* 0024EBB4 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024EBB8 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EBBC nop */
	.word	0x1320000A  /* 0024EBC0 beqz $t9,.L0024EBEC */
	.word	0x00000000  /* 0024EBC4 nop */
	.word	0x90810000  /* 0024EBC8 lbu $at,0($a0) */
	.word	0x0C000000  /* 0024EBCC jal func_0024ebf8 */
	.reloc	.-4, R_MIPS_26, func_0024ebf8
	.word	0x24840001  /* 0024EBD0 addiu $a0,$a0,1 */
	.word	0x2739FFFF  /* 0024EBD4 addiu $t9,$t9,-1 */
	.word	0xA0A10000  /* 0024EBD8 sb $at,0($a1) */
	.word	0x1720FFFA  /* 0024EBDC bnez $t9,.L0024EBC8 */
	.word	0x24A50001  /* 0024EBE0 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024EBE4 j .L0024EA64 */
	.reloc	.-4, R_MIPS_26, func_0024ea4c+0x18
	.word	0x00000000  /* 0024EBE8 nop */
	.word	0x000CF821  /* 0024EBEC addu $ra,$zero,$t4 */
	.word	0x03E00008  /* 0024EBF0 jr $ra */
	.word	0x00000000  /* 0024EBF4 nop */
	.end	func_0024ea4c

	.section	.text.func_0024ebf8,"ax",@progbits
	.globl	func_0024ebf8
	.ent	func_0024ebf8
func_0024ebf8:  /* 0x0024EBF8 */
	.word	0x15000006  /* 0024EBF8 bnez $t0,.L0024EC14 */
	.word	0x00000000  /* 0024EBFC nop */
	.word	0x00864823  /* 0024EC00 subu $t1,$a0,$a2 */
	.word	0x05200003  /* 0024EC04 bltz $t1,.L0024EC14 */
	.word	0x00000000  /* 0024EC08 nop */
	.word	0x24080001  /* 0024EC0C li $t0,1 */
	.word	0x00072021  /* 0024EC10 addu $a0,$zero,$a3 */
	.word	0x03E00008  /* 0024EC14 jr $ra */
	.word	0x00000000  /* 0024EC18 nop */
	.end	func_0024ebf8

	.section	.text.func_0024ec1c,"ax",@progbits
	.globl	func_0024ec1c
	.ent	func_0024ec1c
func_0024ec1c:  /* 0x0024EC1C */
	.word	0x001F6021  /* 0024EC1C addu $t4,$zero,$ra */
	.word	0x00C43021  /* 0024EC20 addu $a2,$a2,$a0 */
	.word	0x00004021  /* 0024EC24 move $t0,$zero */
	.word	0x24840005  /* 0024EC28 addiu $a0,$a0,5 */
	.word	0x24AA0FFF  /* 0024EC2C addiu $t2,$a1,4095 */
	.word	0x00055821  /* 0024EC30 addu $t3,$zero,$a1 */
	.word	0x90990000  /* 0024EC34 lbu $t9,0($a0) */
	.word	0x0C000000  /* 0024EC38 jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024EC3C addiu $a0,$a0,1 */
	.word	0x33210080  /* 0024EC40 andi $at,$t9,0x80 */
	.word	0x14200029  /* 0024EC44 bnez $at,.L0024ECEC */
	.word	0x2721FF82  /* 0024EC48 addiu $at,$t9,-126 */
	.word	0x04200050  /* 0024EC4C bltz $at,.L0024ED90 */
	.word	0x00000000  /* 0024EC50 nop */
	.word	0x10200015  /* 0024EC54 beqz $at,.L0024ECAC */
	.word	0x00000000  /* 0024EC58 nop */
	.word	0x90980000  /* 0024EC5C lbu $t8,0($a0) */
	.word	0x0C000000  /* 0024EC60 jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024EC64 addiu $a0,$a0,1 */
	.word	0x908F0000  /* 0024EC68 lbu $t7,0($a0) */
	.word	0x0C000000  /* 0024EC6C jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024EC70 addiu $a0,$a0,1 */
	.word	0x000F7A00  /* 0024EC74 sll $t7,$t7,0x8 */
	.word	0x01F87825  /* 0024EC78 or $t7,$t7,$t8 */
	.word	0x908E0000  /* 0024EC7C lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024EC80 jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024EC84 addiu $a0,$a0,1 */
	.word	0x25EFFFFF  /* 0024EC88 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024EC8C sb $t6,0($a1) */
	.word	0x24A50001  /* 0024EC90 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024EC94 nop */
	.word	0x00000000  /* 0024EC98 nop */
	.word	0x15E0FFFA  /* 0024EC9C bnez $t7,.L0024EC88 */
	.word	0x00000000  /* 0024ECA0 nop */
	.word	0x08000000  /* 0024ECA4 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024ECA8 nop */
	.word	0x908F0000  /* 0024ECAC lbu $t7,0($a0) */
	.word	0x0C000000  /* 0024ECB0 jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024ECB4 addiu $a0,$a0,1 */
	.word	0x908E0000  /* 0024ECB8 lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024ECBC jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024ECC0 addiu $a0,$a0,1 */
	.word	0x25EF0004  /* 0024ECC4 addiu $t7,$t7,4 */
	.word	0x25EFFFFF  /* 0024ECC8 addiu $t7,$t7,-1 */
	.word	0xA0AE0000  /* 0024ECCC sb $t6,0($a1) */
	.word	0x24A50001  /* 0024ECD0 addiu $a1,$a1,1 */
	.word	0x00000000  /* 0024ECD4 nop */
	.word	0x00000000  /* 0024ECD8 nop */
	.word	0x15E0FFFA  /* 0024ECDC bnez $t7,.L0024ECC8 */
	.word	0x00000000  /* 0024ECE0 nop */
	.word	0x08000000  /* 0024ECE4 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024ECE8 nop */
	.word	0x00197902  /* 0024ECEC srl $t7,$t9,0x4 */
	.word	0x31EF0007  /* 0024ECF0 andi $t7,$t7,0x7 */
	.word	0x25EF0003  /* 0024ECF4 addiu $t7,$t7,3 */
	.word	0x3321000F  /* 0024ECF8 andi $at,$t9,0xf */
	.word	0x908E0000  /* 0024ECFC lbu $t6,0($a0) */
	.word	0x0C000000  /* 0024ED00 jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024ED04 addiu $a0,$a0,1 */
	.word	0x00010A00  /* 0024ED08 sll $at,$at,0x8 */
	.word	0x01C17025  /* 0024ED0C or $t6,$t6,$at */
	.word	0x25CE0001  /* 0024ED10 addiu $t6,$t6,1 */
	.word	0x0145082B  /* 0024ED14 sltu $at,$t2,$a1 */
	.word	0x1020000B  /* 0024ED18 beqz $at,.L0024ED48 */
	.word	0x00000000  /* 0024ED1C nop */
	.word	0x00AE6823  /* 0024ED20 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024ED24 lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024ED28 addiu $t7,$t7,-1 */
	.word	0x25AD0001  /* 0024ED2C addiu $t5,$t5,1 */
	.word	0xA0A10000  /* 0024ED30 sb $at,0($a1) */
	.word	0x24A50001  /* 0024ED34 addiu $a1,$a1,1 */
	.word	0x15E0FFFA  /* 0024ED38 bnez $t7,.L0024ED24 */
	.word	0x00000000  /* 0024ED3C nop */
	.word	0x08000000  /* 0024ED40 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024ED44 nop */
	.word	0x01CB0821  /* 0024ED48 addu $at,$t6,$t3 */
	.word	0x00A1082B  /* 0024ED4C sltu $at,$a1,$at */
	.word	0x14200009  /* 0024ED50 bnez $at,.L0024ED78 */
	.word	0x00000000  /* 0024ED54 nop */
	.word	0x00AE6823  /* 0024ED58 subu $t5,$a1,$t6 */
	.word	0x91A10000  /* 0024ED5C lbu $at,0($t5) */
	.word	0x25EFFFFF  /* 0024ED60 addiu $t7,$t7,-1 */
	.word	0xA0A10000  /* 0024ED64 sb $at,0($a1) */
	.word	0x15E0FFF7  /* 0024ED68 bnez $t7,.L0024ED48 */
	.word	0x24A50001  /* 0024ED6C addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024ED70 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024ED74 nop */
	.word	0xA0A00000  /* 0024ED78 sb $zero,0($a1) */
	.word	0x25EFFFFF  /* 0024ED7C addiu $t7,$t7,-1 */
	.word	0x15E0FFF1  /* 0024ED80 bnez $t7,.L0024ED48 */
	.word	0x24A50001  /* 0024ED84 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024ED88 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024ED8C nop */
	.word	0x1320000A  /* 0024ED90 beqz $t9,.L0024EDBC */
	.word	0x00000000  /* 0024ED94 nop */
	.word	0x90810000  /* 0024ED98 lbu $at,0($a0) */
	.word	0x0C000000  /* 0024ED9C jal func_0024edc8 */
	.reloc	.-4, R_MIPS_26, func_0024edc8
	.word	0x24840001  /* 0024EDA0 addiu $a0,$a0,1 */
	.word	0x2739FFFF  /* 0024EDA4 addiu $t9,$t9,-1 */
	.word	0xA0A10000  /* 0024EDA8 sb $at,0($a1) */
	.word	0x1720FFFA  /* 0024EDAC bnez $t9,.L0024ED98 */
	.word	0x24A50001  /* 0024EDB0 addiu $a1,$a1,1 */
	.word	0x08000000  /* 0024EDB4 j .L0024EC34 */
	.reloc	.-4, R_MIPS_26, func_0024ec1c+0x18
	.word	0x00000000  /* 0024EDB8 nop */
	.word	0x000CF821  /* 0024EDBC addu $ra,$zero,$t4 */
	.word	0x03E00008  /* 0024EDC0 jr $ra */
	.word	0x00000000  /* 0024EDC4 nop */
	.end	func_0024ec1c

	.section	.text.func_0024edc8,"ax",@progbits
	.globl	func_0024edc8
	.ent	func_0024edc8
func_0024edc8:  /* 0x0024EDC8 */
	.word	0x15000006  /* 0024EDC8 bnez $t0,.L0024EDE4 */
	.word	0x00000000  /* 0024EDCC nop */
	.word	0x00864823  /* 0024EDD0 subu $t1,$a0,$a2 */
	.word	0x05200003  /* 0024EDD4 bltz $t1,.L0024EDE4 */
	.word	0x00000000  /* 0024EDD8 nop */
	.word	0x24080001  /* 0024EDDC li $t0,1 */
	.word	0x00072021  /* 0024EDE0 addu $a0,$zero,$a3 */
	.word	0x03E00008  /* 0024EDE4 jr $ra */
	.word	0x00000000  /* 0024EDE8 nop */
	.end	func_0024edc8

	.section	.text.func_0024edf0,"ax",@progbits
	.globl	func_0024edf0
	.ent	func_0024edf0
func_0024edf0:  /* 0x0024EDF0 */
	.word	0x3C020000  /* 0024EDF0 lui $v0,%hi(D_002BBDE0) */
	.reloc	.-4, R_MIPS_HI16, D_002BBDE0
	.word	0x24060003  /* 0024EDF4 li $a2,3 */
	.word	0x24420000  /* 0024EDF8 addiu $v0,$v0,%lo(D_002BBDE0) */
	.reloc	.-4, R_MIPS_LO16, D_002BBDE0
	.word	0x8C430000  /* 0024EDFC lw $v1,0($v0) */
	.word	0x1466005F  /* 0024EE00 bne $v1,$a2,.L0024EF80 */
	.word	0x0000102D  /* 0024EE04 move $v0,$zero */
	.word	0x2403003F  /* 0024EE08 li $v1,63 */
	.word	0xD8A80000  /* 0024EE0C lqc2 $vf8,0($a1) */
	.word	0xD8840000  /* 0024EE10 lqc2 $vf4,0($a0) */
	.word	0xD8850010  /* 0024EE14 lqc2 $vf5,16($a0) */
	.word	0xD8860020  /* 0024EE18 lqc2 $vf6,32($a0) */
	.word	0xD8870030  /* 0024EE1C lqc2 $vf7,48($a0) */
	.word	0x4BE821BC  /* 0024EE20 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EE24 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EE28 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EE2C vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80010  /* 0024EE30 lqc2 $vf8,16($a1) */
	.word	0x4A0002FF  /* 0024EE34 vnop */
	.word	0x4A0002FF  /* 0024EE38 vnop */
	.word	0x4BCC61FF  /* 0024EE3C vclipw.xyz $vf12xyz,$vf12w */
	.word	0x4BE821BC  /* 0024EE40 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EE44 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EE48 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EE4C vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80020  /* 0024EE50 lqc2 $vf8,32($a1) */
	.word	0x4A0002FF  /* 0024EE54 vnop */
	.word	0x4A0002FF  /* 0024EE58 vnop */
	.word	0x48429000  /* 0024EE5C cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EE60 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EE64 and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EE68 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EE6C vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EE70 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EE74 vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80030  /* 0024EE78 lqc2 $vf8,48($a1) */
	.word	0x4A0002FF  /* 0024EE7C vnop */
	.word	0x4A0002FF  /* 0024EE80 vnop */
	.word	0x48429000  /* 0024EE84 cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EE88 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EE8C and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EE90 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EE94 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EE98 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EE9C vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80040  /* 0024EEA0 lqc2 $vf8,64($a1) */
	.word	0x4A0002FF  /* 0024EEA4 vnop */
	.word	0x4A0002FF  /* 0024EEA8 vnop */
	.word	0x48429000  /* 0024EEAC cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EEB0 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EEB4 and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EEB8 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EEBC vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EEC0 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EEC4 vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80050  /* 0024EEC8 lqc2 $vf8,80($a1) */
	.word	0x4A0002FF  /* 0024EECC vnop */
	.word	0x4A0002FF  /* 0024EED0 vnop */
	.word	0x48429000  /* 0024EED4 cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EED8 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EEDC and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EEE0 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EEE4 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EEE8 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EEEC vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80060  /* 0024EEF0 lqc2 $vf8,96($a1) */
	.word	0x4A0002FF  /* 0024EEF4 vnop */
	.word	0x4A0002FF  /* 0024EEF8 vnop */
	.word	0x48429000  /* 0024EEFC cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EF00 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EF04 and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EF08 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EF0C vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EF10 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EF14 vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0xD8A80070  /* 0024EF18 lqc2 $vf8,112($a1) */
	.word	0x4A0002FF  /* 0024EF1C vnop */
	.word	0x4A0002FF  /* 0024EF20 vnop */
	.word	0x48429000  /* 0024EF24 cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EF28 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EF2C and $v1,$v1,$v0 */
	.word	0x4BE821BC  /* 0024EF30 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 0024EF34 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 0024EF38 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83B0B  /* 0024EF3C vmaddw.xyzw $vf12xyzw,$vf7xyzw,$vf8w */
	.word	0x4A0002FF  /* 0024EF40 vnop */
	.word	0x4A0002FF  /* 0024EF44 vnop */
	.word	0x4A0002FF  /* 0024EF48 vnop */
	.word	0x48429000  /* 0024EF4C cfc2 $v0,$vi18 */
	.word	0x4BCC61FF  /* 0024EF50 vclipw.xyz $vf12xyz,$vf12w */
	.word	0x00621824  /* 0024EF54 and $v1,$v1,$v0 */
	.word	0x4A0002FF  /* 0024EF58 vnop */
	.word	0x4A0002FF  /* 0024EF5C vnop */
	.word	0x4A0002FF  /* 0024EF60 vnop */
	.word	0x4A0002FF  /* 0024EF64 vnop */
	.word	0x4A0002FF  /* 0024EF68 vnop */
	.word	0x48429000  /* 0024EF6C cfc2 $v0,$vi18 */
	.word	0x00621824  /* 0024EF70 and $v1,$v1,$v0 */
	.word	0x240200FF  /* 0024EF74 li $v0,255 */
	.word	0x3063002F  /* 0024EF78 andi $v1,$v1,0x2f */
	.word	0x0003100A  /* 0024EF7C movz $v0,$zero,$v1 */
	.word	0x03E00008  /* 0024EF80 jr $ra */
	.word	0x00000000  /* 0024EF84 nop */
	.end	func_0024edf0

	.section	.text.func_0024ef88,"ax",@progbits
	.globl	func_0024ef88
	.ent	func_0024ef88
func_0024ef88:  /* 0x0024EF88 */
	.word	0x27BDFFE0  /* 0024EF88 addiu $sp,$sp,-32 */
	.word	0x24040001  /* 0024EF8C li $a0,1 */
	.word	0xFFB10008  /* 0024EF90 sd $s1,8($sp) */
	.word	0xFFB20010  /* 0024EF94 sd $s2,16($sp) */
	.word	0xFFB00000  /* 0024EF98 sd $s0,0($sp) */
	.word	0xFFBF0018  /* 0024EF9C sd $ra,24($sp) */
	.word	0x0C000000  /* 0024EFA0 jal func_00242b68 */
	.reloc	.-4, R_MIPS_26, func_00242b68
	.word	0x24120001  /* 0024EFA4 li $s2,1 */
	.word	0x0C000000  /* 0024EFA8 jal func_00242b68 */
	.reloc	.-4, R_MIPS_26, func_00242b68
	.word	0x24040002  /* 0024EFAC li $a0,2 */
	.word	0x3C020000  /* 0024EFB0 lui $v0,%hi(D_002E26A0) */
	.reloc	.-4, R_MIPS_HI16, D_002E26A0
	.word	0x24420000  /* 0024EFB4 addiu $v0,$v0,%lo(D_002E26A0) */
	.reloc	.-4, R_MIPS_LO16, D_002E26A0
	.word	0x24510004  /* 0024EFB8 addiu $s1,$v0,4 */
	.word	0x8E300000  /* 0024EFBC lw $s0,0($s1) */
	.word	0x12000007  /* 0024EFC0 beqz $s0,.L0024EFE0 */
	.word	0x26310004  /* 0024EFC4 addiu $s1,$s1,4 */
	.word	0x8E020130  /* 0024EFC8 lw $v0,304($s0) */
	.word	0x0C000000  /* 0024EFCC jal func_0013c318 */
	.reloc	.-4, R_MIPS_26, func_0013c318
	.word	0x9444004C  /* 0024EFD0 lhu $a0,76($v0) */
	.word	0x0200202D  /* 0024EFD4 move $a0,$s0 */
	.word	0x0C000000  /* 0024EFD8 jal func_00241c60 */
	.reloc	.-4, R_MIPS_26, func_00241c60
	.word	0x0040282D  /* 0024EFDC move $a1,$v0 */
	.word	0x2652FFFF  /* 0024EFE0 addiu $s2,$s2,-1 */
	.word	0x0643FFF6  /* 0024EFE4 bgezl $s2,.L0024EFC0 */
	.word	0x8E300000  /* 0024EFE8 lw $s0,0($s1) */
	.word	0xDFB00000  /* 0024EFEC ld $s0,0($sp) */
	.word	0xDFB10008  /* 0024EFF0 ld $s1,8($sp) */
	.word	0xDFB20010  /* 0024EFF4 ld $s2,16($sp) */
	.word	0xDFBF0018  /* 0024EFF8 ld $ra,24($sp) */
	.word	0x03E00008  /* 0024EFFC jr $ra */
	.word	0x27BD0020  /* 0024F000 addiu $sp,$sp,32 */
	.end	func_0024ef88

	.section	.text.func_00121f6c,"ax",@progbits
	.globl	func_00121f6c
	.ent	func_00121f6c
func_00121f6c:  /* 0x00121F6C */
	.word	0x78880000  /* 00121F6C lq $t0,0($a0) */
	.word	0x78890010  /* 00121F70 lq $t1,16($a0) */
	.word	0x788A0020  /* 00121F74 lq $t2,32($a0) */
	.word	0x788B0030  /* 00121F78 lq $t3,48($a0) */
	.word	0x788C0040  /* 00121F7C lq $t4,64($a0) */
	.word	0x788D0050  /* 00121F80 lq $t5,80($a0) */
	.word	0x788E0060  /* 00121F84 lq $t6,96($a0) */
	.word	0x788F0070  /* 00121F88 lq $t7,112($a0) */
	.word	0x7CA80000  /* 00121F8C sq $t0,0($a1) */
	.word	0x7CA90010  /* 00121F90 sq $t1,16($a1) */
	.word	0x7CAA0020  /* 00121F94 sq $t2,32($a1) */
	.word	0x7CAB0030  /* 00121F98 sq $t3,48($a1) */
	.word	0x7CAC0040  /* 00121F9C sq $t4,64($a1) */
	.word	0x7CAD0050  /* 00121FA0 sq $t5,80($a1) */
	.word	0x7CAE0060  /* 00121FA4 sq $t6,96($a1) */
	.word	0x7CAF0070  /* 00121FA8 sq $t7,112($a1) */
	.word	0x20C6FF80  /* 00121FAC addi $a2,$a2,-128 */
	.word	0x24840080  /* 00121FB0 addiu $a0,$a0,128 */
	.word	0x1CC0FFED  /* 00121FB4 bgtz $a2,.L00121F6C */
	.word	0x24A50080  /* 00121FB8 addiu $a1,$a1,128 */
	.word	0x03E00008  /* 00121FBC jr $ra */
	.word	0x00000000  /* 00121FC0 nop */
	.end	func_00121f6c

	.section	.text.func_00121fc4,"ax",@progbits
	.globl	func_00121fc4
	.ent	func_00121fc4
func_00121fc4:  /* 0x00121FC4 */
	.word	0xD8A40000  /* 00121FC4 lqc2 $vf4,0($a1) */
	.word	0x4BC4216A  /* 00121FC8 vmul.xyz $vf5xyz,$vf4xyz,$vf4xyz */
	.word	0x4B052941  /* 00121FCC vaddy.x $vf5x,$vf5x,$vf5y */
	.word	0x4B052942  /* 00121FD0 vaddz.x $vf5x,$vf5x,$vf5z */
	.word	0x4A0002FF  /* 00121FD4 vnop */
	.word	0x4A0002FF  /* 00121FD8 vnop */
	.word	0x4A0002FF  /* 00121FDC vnop */
	.word	0x4A0002FF  /* 00121FE0 vnop */
	.word	0x4A0002FF  /* 00121FE4 vnop */
	.word	0x48262800  /* 00121FE8 qmfc2 $a2,$vf5 */
	.word	0x10C0000A  /* 00121FEC beqz $a2,.L00122018 */
	.word	0x00000000  /* 00121FF0 nop */
	.word	0x4A2503BD  /* 00121FF4 vsqrt $Q,$vf5x */
	.word	0x4BE001AC  /* 00121FF8 vsub.xyzw $vf6xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x4A0003BF  /* 00121FFC vwaitq */
	.word	0x4A2031A0  /* 00122000 vaddq.w $vf6w,$vf6w,$Q */
	.word	0x4BE603BC  /* 00122004 vdiv $Q,$vf0w,$vf6w */
	.word	0x4A0003BF  /* 00122008 vwaitq */
	.word	0x4BC0219C  /* 0012200C vmulq.xyz $vf6xyz,$vf4xyz,$Q */
	.word	0x03E00008  /* 00122010 jr $ra */
	.word	0xF8860000  /* 00122014 sqc2 $vf6,0($a0) */
	.word	0x4BE6033D  /* 00122018 vmr32.xyzw $vf6xyzw,$vf0xyzw */
	.word	0x03E00008  /* 0012201C jr $ra */
	.word	0xF8860000  /* 00122020 sqc2 $vf6,0($a0) */
	.end	func_00121fc4

	.section	.text.func_00162c5c,"ax",@progbits
	.globl	func_00162c5c
	.ent	func_00162c5c
func_00162c5c:  /* 0x00162C5C */
	.word	0xD8A80000  /* 00162C5C lqc2 $vf8,0($a1) */
	.word	0xD8A90010  /* 00162C60 lqc2 $vf9,16($a1) */
	.word	0xD8AA0020  /* 00162C64 lqc2 $vf10,32($a1) */
	.word	0xD8AB0030  /* 00162C68 lqc2 $vf11,48($a1) */
	.word	0xD8C40000  /* 00162C6C lqc2 $vf4,0($a2) */
	.word	0xD8C50010  /* 00162C70 lqc2 $vf5,16($a2) */
	.word	0xD8C60020  /* 00162C74 lqc2 $vf6,32($a2) */
	.word	0xD8C70030  /* 00162C78 lqc2 $vf7,48($a2) */
	.word	0x4BE441BC  /* 00162C7C vmulax.xyzw $ACCxyzw,$vf8xyzw,$vf4x */
	.word	0x4BE448BD  /* 00162C80 vmadday.xyzw $ACCxyzw,$vf9xyzw,$vf4y */
	.word	0x4BE450BE  /* 00162C84 vmaddaz.xyzw $ACCxyzw,$vf10xyzw,$vf4z */
	.word	0x4BE4590B  /* 00162C88 vmaddw.xyzw $vf4xyzw,$vf11xyzw,$vf4w */
	.word	0x4BE541BC  /* 00162C8C vmulax.xyzw $ACCxyzw,$vf8xyzw,$vf5x */
	.word	0x4BE548BD  /* 00162C90 vmadday.xyzw $ACCxyzw,$vf9xyzw,$vf5y */
	.word	0x4BE550BE  /* 00162C94 vmaddaz.xyzw $ACCxyzw,$vf10xyzw,$vf5z */
	.word	0x4BE5594B  /* 00162C98 vmaddw.xyzw $vf5xyzw,$vf11xyzw,$vf5w */
	.word	0x4BE641BC  /* 00162C9C vmulax.xyzw $ACCxyzw,$vf8xyzw,$vf6x */
	.word	0x4BE648BD  /* 00162CA0 vmadday.xyzw $ACCxyzw,$vf9xyzw,$vf6y */
	.word	0x4BE650BE  /* 00162CA4 vmaddaz.xyzw $ACCxyzw,$vf10xyzw,$vf6z */
	.word	0x4BE6598B  /* 00162CA8 vmaddw.xyzw $vf6xyzw,$vf11xyzw,$vf6w */
	.word	0x4BE741BC  /* 00162CAC vmulax.xyzw $ACCxyzw,$vf8xyzw,$vf7x */
	.word	0x4BE748BD  /* 00162CB0 vmadday.xyzw $ACCxyzw,$vf9xyzw,$vf7y */
	.word	0x4BE750BE  /* 00162CB4 vmaddaz.xyzw $ACCxyzw,$vf10xyzw,$vf7z */
	.word	0x4BE759CB  /* 00162CB8 vmaddw.xyzw $vf7xyzw,$vf11xyzw,$vf7w */
	.word	0xF8840000  /* 00162CBC sqc2 $vf4,0($a0) */
	.word	0xF8850010  /* 00162CC0 sqc2 $vf5,16($a0) */
	.word	0xF8860020  /* 00162CC4 sqc2 $vf6,32($a0) */
	.word	0x03E00008  /* 00162CC8 jr $ra */
	.word	0xF8870030  /* 00162CCC sqc2 $vf7,48($a0) */
	.end	func_00162c5c
