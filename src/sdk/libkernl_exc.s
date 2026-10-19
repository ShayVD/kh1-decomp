/* func_00260d00: libkernl exception trampoline (saves every GPR with sq through $k0, mfhi1/mflo1/mfsa, cop0 status/cause/epc, sync.p, eret, syscall). Hand-written assembly in the original. Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.func_00260d00,"ax",@progbits
	.globl	func_00260d00
	.ent	func_00260d00
func_00260d00:  /* 0x00260D00 */
	.word	0x3C1A0000  /* 00260D00 lui $k0,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x275A0000  /* 00260D04 addiu $k0,$k0,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x7F410010  /* 00260D08 sq $at,16($k0) */
	.word	0x7F420020  /* 00260D0C sq $v0,32($k0) */
	.word	0x7F430030  /* 00260D10 sq $v1,48($k0) */
	.word	0x7F440040  /* 00260D14 sq $a0,64($k0) */
	.word	0x7F450050  /* 00260D18 sq $a1,80($k0) */
	.word	0x7F460060  /* 00260D1C sq $a2,96($k0) */
	.word	0x7F470070  /* 00260D20 sq $a3,112($k0) */
	.word	0x7F480080  /* 00260D24 sq $t0,128($k0) */
	.word	0x7F490090  /* 00260D28 sq $t1,144($k0) */
	.word	0x7F4A00A0  /* 00260D2C sq $t2,160($k0) */
	.word	0x7F4B00B0  /* 00260D30 sq $t3,176($k0) */
	.word	0x7F4C00C0  /* 00260D34 sq $t4,192($k0) */
	.word	0x7F4D00D0  /* 00260D38 sq $t5,208($k0) */
	.word	0x7F4E00E0  /* 00260D3C sq $t6,224($k0) */
	.word	0x7F4F00F0  /* 00260D40 sq $t7,240($k0) */
	.word	0x7F500100  /* 00260D44 sq $s0,256($k0) */
	.word	0x7F510110  /* 00260D48 sq $s1,272($k0) */
	.word	0x7F520120  /* 00260D4C sq $s2,288($k0) */
	.word	0x7F530130  /* 00260D50 sq $s3,304($k0) */
	.word	0x7F540140  /* 00260D54 sq $s4,320($k0) */
	.word	0x7F550150  /* 00260D58 sq $s5,336($k0) */
	.word	0x7F560160  /* 00260D5C sq $s6,352($k0) */
	.word	0x7F570170  /* 00260D60 sq $s7,368($k0) */
	.word	0x7F580180  /* 00260D64 sq $t8,384($k0) */
	.word	0x7F590190  /* 00260D68 sq $t9,400($k0) */
	.word	0x7F5C01C0  /* 00260D6C sq $gp,448($k0) */
	.word	0x7F5D01D0  /* 00260D70 sq $sp,464($k0) */
	.word	0x7F5E01E0  /* 00260D74 sq $s8,480($k0) */
	.word	0x7F5F01F0  /* 00260D78 sq $ra,496($k0) */
	.word	0x00001010  /* 00260D7C mfhi $v0 */
	.word	0x3C010000  /* 00260D80 lui $at,%hi(D_0066FA80) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA80
	.word	0xFC220000  /* 00260D84 sd $v0,%lo(D_0066FA80)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA80
	.word	0x70001010  /* 00260D88 mfhi1 $v0 */
	.word	0x3C010000  /* 00260D8C lui $at,%hi(D_0066FA88) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA88
	.word	0xFC220000  /* 00260D90 sd $v0,%lo(D_0066FA88)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA88
	.word	0x00001012  /* 00260D94 mflo $v0 */
	.word	0x3C010000  /* 00260D98 lui $at,%hi(D_0066FA90) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA90
	.word	0xFC220000  /* 00260D9C sd $v0,%lo(D_0066FA90)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA90
	.word	0x70001012  /* 00260DA0 mflo1 $v0 */
	.word	0x3C010000  /* 00260DA4 lui $at,%hi(D_0066FA98) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA98
	.word	0xFC220000  /* 00260DA8 sd $v0,%lo(D_0066FA98)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA98
	.word	0x00001028  /* 00260DAC mfsa $v0 */
	.word	0x3C010000  /* 00260DB0 lui $at,%hi(D_0066FAA0) */
	.reloc	.-4, R_MIPS_HI16, D_0066FAA0
	.word	0xFC220000  /* 00260DB4 sd $v0,%lo(D_0066FAA0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FAA0
	.word	0x40046000  /* 00260DB8 mfc0 $a0,c0_sr */
	.word	0x40056800  /* 00260DBC mfc0 $a1,c0_cause */
	.word	0x40067000  /* 00260DC0 mfc0 $a2,c0_epc */
	.word	0x40074000  /* 00260DC4 mfc0 $a3,c0_badvaddr */
	.word	0x3C080000  /* 00260DC8 lui $t0,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x25080000  /* 00260DCC addiu $t0,$t0,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x3C010000  /* 00260DD0 lui $at,%hi(D_0066FAA8) */
	.reloc	.-4, R_MIPS_HI16, D_0066FAA8
	.word	0xAC260000  /* 00260DD4 sw $a2,%lo(D_0066FAA8)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FAA8
	.word	0x3C010000  /* 00260DD8 lui $at,%hi(func_00260e00) */
	.reloc	.-4, R_MIPS_HI16, func_00260d00+0x100
	.word	0x24210000  /* 00260DDC addiu $at,$at,%lo(func_00260e00) */
	.reloc	.-4, R_MIPS_LO16, func_00260d00+0x100
	.word	0x40817000  /* 00260DE0 mtc0 $at,c0_epc */
	.word	0x0000040F  /* 00260DE4 sync.p */
	.word	0x40016000  /* 00260DE8 mfc0 $at,c0_sr */
	.word	0x2402FFFE  /* 00260DEC li $v0,-2 */
	.word	0x00220824  /* 00260DF0 and $at,$at,$v0 */
	.word	0x40816000  /* 00260DF4 mtc0 $at,c0_sr */
	.word	0x0000040F  /* 00260DF8 sync.p */
	.word	0x42000018  /* 00260DFC eret */
	.word	0x3C010000  /* 00260E00 lui $at,%hi(D_0046C1C0) */
	.reloc	.-4, R_MIPS_HI16, D_0046C1C0
	.word	0x8C210000  /* 00260E04 lw $at,%lo(D_0046C1C0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0046C1C0
	.word	0x3C1D0000  /* 00260E08 lui $sp,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x0020F809  /* 00260E0C jalr $at */
	.word	0x27BD0000  /* 00260E10 addiu $sp,$sp,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x2403FFAC  /* 00260E14 li $v1,-84 */
	.word	0x0000000C  /* 00260E18 syscall */
	.word	0x00000000  /* 00260E1C nop */
	.word	0x00000000  /* 00260E20 nop */
	.word	0x00000000  /* 00260E24 nop */
	.word	0x00000000  /* 00260E28 nop */
	.word	0x00000000  /* 00260E2C nop */
	.word	0x00000000  /* 00260E30 nop */
	.word	0x00000000  /* 00260E34 nop */
	.word	0x00000000  /* 00260E38 nop */
	.word	0x00000000  /* 00260E3C nop */
	.word	0x40016000  /* 00260E40 mfc0 $at,c0_sr */
	.word	0x241AFFE4  /* 00260E44 li $k0,-28 */
	.word	0x003A0824  /* 00260E48 and $at,$at,$k0 */
	.word	0x40816000  /* 00260E4C mtc0 $at,c0_sr */
	.word	0x0000040F  /* 00260E50 sync.p */
	.word	0x3C020000  /* 00260E54 lui $v0,%hi(D_0066FAA8) */
	.reloc	.-4, R_MIPS_HI16, D_0066FAA8
	.word	0x8C420000  /* 00260E58 lw $v0,%lo(D_0066FAA8)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FAA8
	.word	0x40827000  /* 00260E5C mtc0 $v0,c0_epc */
	.word	0x0000040F  /* 00260E60 sync.p */
	.word	0x3C020000  /* 00260E64 lui $v0,%hi(D_0066FA80) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA80
	.word	0xDC420000  /* 00260E68 ld $v0,%lo(D_0066FA80)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA80
	.word	0x00400011  /* 00260E6C mthi $v0 */
	.word	0x3C020000  /* 00260E70 lui $v0,%hi(D_0066FA88) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA88
	.word	0xDC420000  /* 00260E74 ld $v0,%lo(D_0066FA88)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA88
	.word	0x70400011  /* 00260E78 mthi1 $v0 */
	.word	0x3C020000  /* 00260E7C lui $v0,%hi(D_0066FA90) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA90
	.word	0xDC420000  /* 00260E80 ld $v0,%lo(D_0066FA90)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA90
	.word	0x00400013  /* 00260E84 mtlo $v0 */
	.word	0x3C020000  /* 00260E88 lui $v0,%hi(D_0066FA98) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA98
	.word	0xDC420000  /* 00260E8C ld $v0,%lo(D_0066FA98)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA98
	.word	0x70400013  /* 00260E90 mtlo1 $v0 */
	.word	0x3C020000  /* 00260E94 lui $v0,%hi(D_0066FAA0) */
	.reloc	.-4, R_MIPS_HI16, D_0066FAA0
	.word	0xDC420000  /* 00260E98 ld $v0,%lo(D_0066FAA0)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0066FAA0
	.word	0x00400029  /* 00260E9C mtsa $v0 */
	.word	0x0000040F  /* 00260EA0 sync.p */
	.word	0x3C1A0000  /* 00260EA4 lui $k0,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x275A0000  /* 00260EA8 addiu $k0,$k0,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x7B410010  /* 00260EAC lq $at,16($k0) */
	.word	0x7B420020  /* 00260EB0 lq $v0,32($k0) */
	.word	0x7B430030  /* 00260EB4 lq $v1,48($k0) */
	.word	0x7B440040  /* 00260EB8 lq $a0,64($k0) */
	.word	0x7B450050  /* 00260EBC lq $a1,80($k0) */
	.word	0x7B460060  /* 00260EC0 lq $a2,96($k0) */
	.word	0x7B470070  /* 00260EC4 lq $a3,112($k0) */
	.word	0x7B480080  /* 00260EC8 lq $t0,128($k0) */
	.word	0x7B490090  /* 00260ECC lq $t1,144($k0) */
	.word	0x7B4A00A0  /* 00260ED0 lq $t2,160($k0) */
	.word	0x7B4B00B0  /* 00260ED4 lq $t3,176($k0) */
	.word	0x7B4C00C0  /* 00260ED8 lq $t4,192($k0) */
	.word	0x7B4D00D0  /* 00260EDC lq $t5,208($k0) */
	.word	0x7B4E00E0  /* 00260EE0 lq $t6,224($k0) */
	.word	0x7B4F00F0  /* 00260EE4 lq $t7,240($k0) */
	.word	0x7B500100  /* 00260EE8 lq $s0,256($k0) */
	.word	0x7B510110  /* 00260EEC lq $s1,272($k0) */
	.word	0x7B520120  /* 00260EF0 lq $s2,288($k0) */
	.word	0x7B530130  /* 00260EF4 lq $s3,304($k0) */
	.word	0x7B540140  /* 00260EF8 lq $s4,320($k0) */
	.word	0x7B550150  /* 00260EFC lq $s5,336($k0) */
	.word	0x7B560160  /* 00260F00 lq $s6,352($k0) */
	.word	0x7B570170  /* 00260F04 lq $s7,368($k0) */
	.word	0x7B580180  /* 00260F08 lq $t8,384($k0) */
	.word	0x7B590190  /* 00260F0C lq $t9,400($k0) */
	.word	0x7B5C01C0  /* 00260F10 lq $gp,448($k0) */
	.word	0x7B5D01D0  /* 00260F14 lq $sp,464($k0) */
	.word	0x7B5E01E0  /* 00260F18 lq $s8,480($k0) */
	.word	0x7B5F01F0  /* 00260F1C lq $ra,496($k0) */
	.word	0x401A6000  /* 00260F20 mfc0 $k0,c0_sr */
	.word	0x375A0013  /* 00260F24 ori $k0,$k0,0x13 */
	.word	0x409A6000  /* 00260F28 mtc0 $k0,c0_sr */
	.word	0x0000040F  /* 00260F2C sync.p */
	.word	0x42000018  /* 00260F30 eret */
	.word	0x00000000  /* 00260F34 nop */
	.word	0x00000000  /* 00260F38 nop */
	.word	0x00000000  /* 00260F3C nop */
	.globl	func_00260f40
func_00260f40:  /* mid-function entry point */
	.word	0x3C1A0000  /* 00260F40 lui $k0,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x275A0000  /* 00260F44 addiu $k0,$k0,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x7F410010  /* 00260F48 sq $at,16($k0) */
	.word	0x7F420020  /* 00260F4C sq $v0,32($k0) */
	.word	0x7F430030  /* 00260F50 sq $v1,48($k0) */
	.word	0x7F440040  /* 00260F54 sq $a0,64($k0) */
	.word	0x7F450050  /* 00260F58 sq $a1,80($k0) */
	.word	0x7F460060  /* 00260F5C sq $a2,96($k0) */
	.word	0x7F470070  /* 00260F60 sq $a3,112($k0) */
	.word	0x7F480080  /* 00260F64 sq $t0,128($k0) */
	.word	0x7F490090  /* 00260F68 sq $t1,144($k0) */
	.word	0x7F4A00A0  /* 00260F6C sq $t2,160($k0) */
	.word	0x7F4B00B0  /* 00260F70 sq $t3,176($k0) */
	.word	0x7F4C00C0  /* 00260F74 sq $t4,192($k0) */
	.word	0x7F4D00D0  /* 00260F78 sq $t5,208($k0) */
	.word	0x7F4E00E0  /* 00260F7C sq $t6,224($k0) */
	.word	0x7F4F00F0  /* 00260F80 sq $t7,240($k0) */
	.word	0x7F500100  /* 00260F84 sq $s0,256($k0) */
	.word	0x7F510110  /* 00260F88 sq $s1,272($k0) */
	.word	0x7F520120  /* 00260F8C sq $s2,288($k0) */
	.word	0x7F530130  /* 00260F90 sq $s3,304($k0) */
	.word	0x7F540140  /* 00260F94 sq $s4,320($k0) */
	.word	0x7F550150  /* 00260F98 sq $s5,336($k0) */
	.word	0x7F560160  /* 00260F9C sq $s6,352($k0) */
	.word	0x7F570170  /* 00260FA0 sq $s7,368($k0) */
	.word	0x7F580180  /* 00260FA4 sq $t8,384($k0) */
	.word	0x7F590190  /* 00260FA8 sq $t9,400($k0) */
	.word	0x7F5C01C0  /* 00260FAC sq $gp,448($k0) */
	.word	0x7F5D01D0  /* 00260FB0 sq $sp,464($k0) */
	.word	0x7F5E01E0  /* 00260FB4 sq $s8,480($k0) */
	.word	0x7F5F01F0  /* 00260FB8 sq $ra,496($k0) */
	.word	0x00001010  /* 00260FBC mfhi $v0 */
	.word	0x3C010000  /* 00260FC0 lui $at,%hi(D_0066FA80) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA80
	.word	0xFC220000  /* 00260FC4 sd $v0,%lo(D_0066FA80)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA80
	.word	0x70001010  /* 00260FC8 mfhi1 $v0 */
	.word	0x3C010000  /* 00260FCC lui $at,%hi(D_0066FA88) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA88
	.word	0xFC220000  /* 00260FD0 sd $v0,%lo(D_0066FA88)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA88
	.word	0x00001012  /* 00260FD4 mflo $v0 */
	.word	0x3C010000  /* 00260FD8 lui $at,%hi(D_0066FA90) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA90
	.word	0xFC220000  /* 00260FDC sd $v0,%lo(D_0066FA90)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA90
	.word	0x70001012  /* 00260FE0 mflo1 $v0 */
	.word	0x3C010000  /* 00260FE4 lui $at,%hi(D_0066FA98) */
	.reloc	.-4, R_MIPS_HI16, D_0066FA98
	.word	0xFC220000  /* 00260FE8 sd $v0,%lo(D_0066FA98)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FA98
	.word	0x00001028  /* 00260FEC mfsa $v0 */
	.word	0x3C010000  /* 00260FF0 lui $at,%hi(D_0066FAA0) */
	.reloc	.-4, R_MIPS_HI16, D_0066FAA0
	.word	0xFC220000  /* 00260FF4 sd $v0,%lo(D_0066FAA0)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0066FAA0
	.word	0x40046000  /* 00260FF8 mfc0 $a0,c0_sr */
	.word	0x40056800  /* 00260FFC mfc0 $a1,c0_cause */
	.word	0x40067000  /* 00261000 mfc0 $a2,c0_epc */
	.word	0x40074000  /* 00261004 mfc0 $a3,c0_badvaddr */
	.word	0x4008B800  /* 00261008 mfc0 $t0,c0_badpaddr */
	.word	0x3C090000  /* 0026100C lui $t1,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x25290000  /* 00261010 addiu $t1,$t1,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x3C010000  /* 00261014 lui $at,%hi(func_0026103c) */
	.reloc	.-4, R_MIPS_HI16, func_00260d00+0x33c
	.word	0x24210000  /* 00261018 addiu $at,$at,%lo(func_0026103c) */
	.reloc	.-4, R_MIPS_LO16, func_00260d00+0x33c
	.word	0x40817000  /* 0026101C mtc0 $at,c0_epc */
	.word	0x0000040F  /* 00261020 sync.p */
	.word	0x40016000  /* 00261024 mfc0 $at,c0_sr */
	.word	0x2402FFFE  /* 00261028 li $v0,-2 */
	.word	0x00220824  /* 0026102C and $at,$at,$v0 */
	.word	0x40816000  /* 00261030 mtc0 $at,c0_sr */
	.word	0x0000040F  /* 00261034 sync.p */
	.word	0x42000018  /* 00261038 eret */
	.word	0x30A2007C  /* 0026103C andi $v0,$a1,0x7c */
	.word	0x3C010000  /* 00261040 lui $at,%hi(D_0046C1C8) */
	.reloc	.-4, R_MIPS_HI16, D_0046C1C8
	.word	0x00220821  /* 00261044 addu $at,$at,$v0 */
	.word	0x8C210000  /* 00261048 lw $at,%lo(D_0046C1C8)($at) */
	.reloc	.-4, R_MIPS_LO16, D_0046C1C8
	.word	0x3C1D0000  /* 0026104C lui $sp,%hi(D_0066F880) */
	.reloc	.-4, R_MIPS_HI16, D_0066F880
	.word	0x0020F809  /* 00261050 jalr $at */
	.word	0x27BD0000  /* 00261054 addiu $sp,$sp,%lo(D_0066F880) */
	.reloc	.-4, R_MIPS_LO16, D_0066F880
	.word	0x03FFFFCD  /* 00261058 break 0x3ff,0x3ff */
	.end	func_00260d00
