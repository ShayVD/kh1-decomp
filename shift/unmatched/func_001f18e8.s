/* func_001f18e8: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_001f18e8,"ax",@progbits
	.globl	func_001f18e8
	.ent	func_001f18e8
func_001f18e8:  /* 0x001F18E8 */
	.word	0x27BDFF70  /* 001F18E8 addiu $sp,$sp,-144 */
	.word	0xFFB00040  /* 001F18EC sd $s0,64($sp) */
	.word	0xFFB10048  /* 001F18F0 sd $s1,72($sp) */
	.word	0x0080882D  /* 001F18F4 move $s1,$a0 */
	.word	0x8FB00098  /* 001F18F8 lw $s0,152($sp) */
	.word	0x0000202D  /* 001F18FC move $a0,$zero */
	.word	0xFFB20050  /* 001F1900 sd $s2,80($sp) */
	.word	0x0160902D  /* 001F1904 move $s2,$t3 */
	.word	0xFFB30058  /* 001F1908 sd $s3,88($sp) */
	.word	0x00E0982D  /* 001F190C move $s3,$a3 */
	.word	0xFFB40060  /* 001F1910 sd $s4,96($sp) */
	.word	0x0100A02D  /* 001F1914 move $s4,$t0 */
	.word	0xFFB50068  /* 001F1918 sd $s5,104($sp) */
	.word	0x00C0A82D  /* 001F191C move $s5,$a2 */
	.word	0xFFB60070  /* 001F1920 sd $s6,112($sp) */
	.word	0x0000B02D  /* 001F1924 move $s6,$zero */
	.word	0xFFB70078  /* 001F1928 sd $s7,120($sp) */
	.word	0x0120B82D  /* 001F192C move $s7,$t1 */
	.word	0xFFBE0080  /* 001F1930 sd $s8,128($sp) */
	.word	0x0010803C  /* 001F1934 dsll32 $s0,$s0,0x0 */
	.word	0xAFA50030  /* 001F1938 sw $a1,48($sp) */
	.word	0x0010803E  /* 001F193C dsrl32 $s0,$s0,0x0 */
	.word	0xFFBF0088  /* 001F1940 sd $ra,136($sp) */
	.word	0xAFAA0034  /* 001F1944 sw $t2,52($sp) */
	.word	0x0C000000  /* 001F1948 jal func_001efb78 */
	.reloc	.-4, R_MIPS_26, func_001efb78
	.word	0x8FBE0090  /* 001F194C lw $s8,144($sp) */
	.word	0x0C000000  /* 001F1950 jal func_001efb98 */
	.reloc	.-4, R_MIPS_26, func_001efb98
	.word	0x0000202D  /* 001F1954 move $a0,$zero */
	.word	0x3C044000  /* 001F1958 lui $a0,0x4000 */
	.word	0x0004203C  /* 001F195C dsll32 $a0,$a0,0x0 */
	.word	0x34840001  /* 001F1960 ori $a0,$a0,0x1 */
	.word	0x3402EEEE  /* 001F1964 li $v0,0xeeee */
	.word	0x2403003F  /* 001F1968 li $v1,63 */
	.word	0xFE220008  /* 001F196C sd $v0,8($s1) */
	.word	0x26220050  /* 001F1970 addiu $v0,$s1,80 */
	.word	0x3C054007  /* 001F1974 lui $a1,0x4007 */
	.word	0x34A5FF80  /* 001F1978 ori $a1,$a1,0xff80 */
	.word	0x00052C38  /* 001F197C dsll $a1,$a1,0x10 */
	.word	0x34A50130  /* 001F1980 ori $a1,$a1,0x130 */
	.word	0x00052C38  /* 001F1984 dsll $a1,$a1,0x10 */
	.word	0x24060016  /* 001F1988 li $a2,22 */
	.word	0x24070044  /* 001F198C li $a3,68 */
	.word	0x24080042  /* 001F1990 li $t0,66 */
	.word	0x24090001  /* 001F1994 li $t1,1 */
	.word	0xFE240000  /* 001F1998 sd $a0,0($s1) */
	.word	0xAFA2003C  /* 001F199C sw $v0,60($sp) */
	.word	0xFE230018  /* 001F19A0 sd $v1,24($s1) */
	.word	0xFE250020  /* 001F19A4 sd $a1,32($s1) */
	.word	0xFE260028  /* 001F19A8 sd $a2,40($s1) */
	.word	0xFE270030  /* 001F19AC sd $a3,48($s1) */
	.word	0xFE280038  /* 001F19B0 sd $t0,56($s1) */
	.word	0xFE300040  /* 001F19B4 sd $s0,64($s1) */
	.word	0xFE290048  /* 001F19B8 sd $t1,72($s1) */
	.word	0xFE200010  /* 001F19BC sd $zero,16($s1) */
	.word	0x26310060  /* 001F19C0 addiu $s1,$s1,96 */
	.word	0x16400016  /* 001F19C4 bnez $s2,.L001F1A20 */
	.word	0xAFB10038  /* 001F19C8 sw $s1,56($sp) */
	.word	0x52600004  /* 001F19CC beqzl $s3,.L001F19E0 */
	.word	0xAFA00000  /* 001F19D0 sw $zero,0($sp) */
	.word	0x16800004  /* 001F19D4 bnez $s4,.L001F19E8 */
	.word	0x2663FFFF  /* 001F19D8 addiu $v1,$s3,-1 */
	.word	0xAFA00000  /* 001F19DC sw $zero,0($sp) */
	.word	0x1000004C  /* 001F19E0 b .L001F1B14 */
	.word	0x24100001  /* 001F19E4 li $s0,1 */
	.word	0x0460000A  /* 001F19E8 bltz $v1,.L001F1A14 */
	.word	0x00031080  /* 001F19EC sll $v0,$v1,0x2 */
	.word	0x005D1021  /* 001F19F0 addu $v0,$v0,$sp */
	.word	0x00000000  /* 001F19F4 nop */
	.word	0x2463FFFF  /* 001F19F8 addiu $v1,$v1,-1 */
	.word	0xAC400000  /* 001F19FC sw $zero,0($v0) */
	.word	0x00000000  /* 001F1A00 nop */
	.word	0x00000000  /* 001F1A04 nop */
	.word	0x00000000  /* 001F1A08 nop */
	.word	0x0461FFFA  /* 001F1A0C bgez $v1,.L001F19F8 */
	.word	0x2442FFFC  /* 001F1A10 addiu $v0,$v0,-4 */
	.word	0x1000003F  /* 001F1A14 b .L001F1B14 */
	.word	0x0260802D  /* 001F1A18 move $s0,$s3 */
	.word	0x00000000  /* 001F1A1C nop */
	.word	0x06410003  /* 001F1A20 bgez $s2,.L001F1A30 */
	.word	0x00000000  /* 001F1A24 nop */
	.word	0x00129023  /* 001F1A28 negu $s2,$s2 */
	.word	0x24160001  /* 001F1A2C li $s6,1 */
	.word	0x16600013  /* 001F1A30 bnez $s3,.L001F1A80 */
	.word	0x0000802D  /* 001F1A34 move $s0,$zero */
	.word	0x2405000A  /* 001F1A38 li $a1,10 */
	.word	0x03A0302D  /* 001F1A3C move $a2,$sp */
	.word	0x0245001A  /* 001F1A40 div $zero,$s2,$a1 */
	.word	0x00000000  /* 001F1A44 nop */
	.word	0x26100001  /* 001F1A48 addiu $s0,$s0,1 */
	.word	0x50A00001  /* 001F1A4C beqzl $a1,.L001F1A54 */
	.word	0x000001CD  /* 001F1A50 break 0x0,0x7 */
	.word	0x2A04000A  /* 001F1A54 slti $a0,$s0,10 */
	.word	0x00001012  /* 001F1A58 mflo $v0 */
	.word	0x00001810  /* 001F1A5C mfhi $v1 */
	.word	0x0040902D  /* 001F1A60 move $s2,$v0 */
	.word	0xACC30000  /* 001F1A64 sw $v1,0($a2) */
	.word	0x1240002A  /* 001F1A68 beqz $s2,.L001F1B14 */
	.word	0x24C60004  /* 001F1A6C addiu $a2,$a2,4 */
	.word	0x5480FFF5  /* 001F1A70 bnezl $a0,.L001F1A48 */
	.word	0x0245001A  /* 001F1A74 div $zero,$s2,$a1 */
	.word	0x10000027  /* 001F1A78 b .L001F1B18 */
	.word	0x8FA40034  /* 001F1A7C lw $a0,52($sp) */
	.word	0x16800011  /* 001F1A80 bnez $s4,.L001F1AC8 */
	.word	0x2405000A  /* 001F1A84 li $a1,10 */
	.word	0x03A0302D  /* 001F1A88 move $a2,$sp */
	.word	0x0245001A  /* 001F1A8C div $zero,$s2,$a1 */
	.word	0x26100001  /* 001F1A90 addiu $s0,$s0,1 */
	.word	0x50A00001  /* 001F1A94 beqzl $a1,.L001F1A9C */
	.word	0x000001CD  /* 001F1A98 break 0x0,0x7 */
	.word	0x0213202A  /* 001F1A9C slt $a0,$s0,$s3 */
	.word	0x00001012  /* 001F1AA0 mflo $v0 */
	.word	0x00001810  /* 001F1AA4 mfhi $v1 */
	.word	0x0040902D  /* 001F1AA8 move $s2,$v0 */
	.word	0xACC30000  /* 001F1AAC sw $v1,0($a2) */
	.word	0x12400018  /* 001F1AB0 beqz $s2,.L001F1B14 */
	.word	0x24C60004  /* 001F1AB4 addiu $a2,$a2,4 */
	.word	0x5480FFF5  /* 001F1AB8 bnezl $a0,.L001F1A90 */
	.word	0x0245001A  /* 001F1ABC div $zero,$s2,$a1 */
	.word	0x10000015  /* 001F1AC0 b .L001F1B18 */
	.word	0x8FA40034  /* 001F1AC4 lw $a0,52($sp) */
	.word	0x03A0202D  /* 001F1AC8 move $a0,$sp */
	.word	0x00000000  /* 001F1ACC nop */
	.word	0x56400005  /* 001F1AD0 bnezl $s2,.L001F1AE8 */
	.word	0x0245001A  /* 001F1AD4 div $zero,$s2,$a1 */
	.word	0xAC800000  /* 001F1AD8 sw $zero,0($a0) */
	.word	0x24840004  /* 001F1ADC addiu $a0,$a0,4 */
	.word	0x10000009  /* 001F1AE0 b .L001F1B08 */
	.word	0x26100001  /* 001F1AE4 addiu $s0,$s0,1 */
	.word	0x50A00001  /* 001F1AE8 beqzl $a1,.L001F1AF0 */
	.word	0x000001CD  /* 001F1AEC break 0x0,0x7 */
	.word	0x26100001  /* 001F1AF0 addiu $s0,$s0,1 */
	.word	0x00001812  /* 001F1AF4 mflo $v1 */
	.word	0x00001010  /* 001F1AF8 mfhi $v0 */
	.word	0xAC820000  /* 001F1AFC sw $v0,0($a0) */
	.word	0x0060902D  /* 001F1B00 move $s2,$v1 */
	.word	0x24840004  /* 001F1B04 addiu $a0,$a0,4 */
	.word	0x0213102A  /* 001F1B08 slt $v0,$s0,$s3 */
	.word	0x1440FFF0  /* 001F1B0C bnez $v0,.L001F1AD0 */
	.word	0x00000000  /* 001F1B10 nop */
	.word	0x8FA40034  /* 001F1B14 lw $a0,52($sp) */
	.word	0x00171100  /* 001F1B18 sll $v0,$s7,0x4 */
	.word	0x24527000  /* 001F1B1C addiu $s2,$v0,28672 */
	.word	0x001E9900  /* 001F1B20 sll $s3,$s8,0x4 */
	.word	0x00041900  /* 001F1B24 sll $v1,$a0,0x4 */
	.word	0x0C000000  /* 001F1B28 jal func_001efba8 */
	.reloc	.-4, R_MIPS_26, func_001efba8
	.word	0x24747400  /* 001F1B2C addiu $s4,$v1,29696 */
	.word	0x24030001  /* 001F1B30 li $v1,1 */
	.word	0x12A30008  /* 001F1B34 beq $s5,$v1,.L001F1B58 */
	.word	0x02627821  /* 001F1B38 addu $t7,$s3,$v0 */
	.word	0x2AA20002  /* 001F1B3C slti $v0,$s5,2 */
	.word	0x1440000E  /* 001F1B40 bnez $v0,.L001F1B7C */
	.word	0x24020002  /* 001F1B44 li $v0,2 */
	.word	0x12A20007  /* 001F1B48 beq $s5,$v0,.L001F1B68 */
	.word	0x02161021  /* 001F1B4C addu $v0,$s0,$s6 */
	.word	0x1000000A  /* 001F1B50 b .L001F1B7C */
	.word	0x00000000  /* 001F1B54 nop */
	.word	0x02161021  /* 001F1B58 addu $v0,$s0,$s6 */
	.word	0x10000006  /* 001F1B5C b .L001F1B78 */
	.word	0x004F1018  /* 001F1B60 mult $v0,$v0,$t7 */
	.word	0x00000000  /* 001F1B64 nop */
	.word	0x004F1018  /* 001F1B68 mult $v0,$v0,$t7 */
	.word	0x00021FC2  /* 001F1B6C srl $v1,$v0,0x1f */
	.word	0x00431021  /* 001F1B70 addu $v0,$v0,$v1 */
	.word	0x00021043  /* 001F1B74 sra $v0,$v0,0x1 */
	.word	0x02429023  /* 001F1B78 subu $s2,$s2,$v0 */
	.word	0x12C00033  /* 001F1B7C beqz $s6,.L001F1C4C */
	.word	0x3C020000  /* 001F1B80 lui $v0,%hi(D_003E8CD0) */
	.reloc	.-4, R_MIPS_HI16, D_003E8CD0
	.word	0x24060012  /* 001F1B84 li $a2,18 */
	.word	0x8C450000  /* 001F1B88 lw $a1,%lo(D_003E8CD0)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_003E8CD0
	.word	0x50C00001  /* 001F1B8C beqzl $a2,.L001F1B94 */
	.word	0x000001CD  /* 001F1B90 break 0x0,0x7 */
	.word	0x340AFFF0  /* 001F1B94 li $t2,0xfff0 */
	.word	0x000A50FC  /* 001F1B98 dsll32 $t2,$t2,0x3 */
	.word	0x3C0C0010  /* 001F1B9C lui $t4,0x10 */
	.word	0x90A20006  /* 001F1BA0 lbu $v0,6($a1) */
	.word	0x240B0016  /* 001F1BA4 li $t3,22 */
	.word	0x90A40007  /* 001F1BA8 lbu $a0,7($a1) */
	.word	0x34098000  /* 001F1BAC li $t1,0x8000 */
	.word	0x00024100  /* 001F1BB0 sll $t0,$v0,0x4 */
	.word	0x94AE0002  /* 001F1BB4 lhu $t6,2($a1) */
	.word	0x011E3818  /* 001F1BB8 mult $a3,$t0,$s8 */
	.word	0x00041102  /* 001F1BBC srl $v0,$a0,0x4 */
	.word	0x00021080  /* 001F1BC0 sll $v0,$v0,0x2 */
	.word	0x3084000F  /* 001F1BC4 andi $a0,$a0,0xf */
	.word	0x3C030000  /* 001F1BC8 lui $v1,%hi(D_003E8D00) */
	.reloc	.-4, R_MIPS_HI16, D_003E8D00
	.word	0x00621821  /* 001F1BCC addu $v1,$v1,$v0 */
	.word	0x8C630000  /* 001F1BD0 lw $v1,%lo(D_003E8D00)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_003E8D00
	.word	0x02931021  /* 001F1BD4 addu $v0,$s4,$s3 */
	.word	0x0004263C  /* 001F1BD8 dsll32 $a0,$a0,0x18 */
	.word	0x94AD0004  /* 001F1BDC lhu $t5,4($a1) */
	.word	0x00E6001A  /* 001F1BE0 div $zero,$a3,$a2 */
	.word	0x00031D38  /* 001F1BE4 dsll $v1,$v1,0x14 */
	.word	0xAE220044  /* 001F1BE8 sw $v0,68($s1) */
	.word	0x00641825  /* 001F1BEC or $v1,$v1,$a0 */
	.word	0x006A1825  /* 001F1BF0 or $v1,$v1,$t2 */
	.word	0x01C84021  /* 001F1BF4 addu $t0,$t6,$t0 */
	.word	0xFE230000  /* 001F1BF8 sd $v1,0($s1) */
	.word	0x25A50120  /* 001F1BFC addiu $a1,$t5,288 */
	.word	0xFE2B0008  /* 001F1C00 sd $t3,8($s1) */
	.word	0xAE29002C  /* 001F1C04 sw $t1,44($s1) */
	.word	0xAE280030  /* 001F1C08 sw $t0,48($s1) */
	.word	0xAE250034  /* 001F1C0C sw $a1,52($s1) */
	.word	0xAE2C0048  /* 001F1C10 sw $t4,72($s1) */
	.word	0xAE2E0010  /* 001F1C14 sw $t6,16($s1) */
	.word	0xAE2D0014  /* 001F1C18 sw $t5,20($s1) */
	.word	0xAE340024  /* 001F1C1C sw $s4,36($s1) */
	.word	0xAE2C0028  /* 001F1C20 sw $t4,40($s1) */
	.word	0xAE20004C  /* 001F1C24 sw $zero,76($s1) */
	.word	0x00003812  /* 001F1C28 mflo $a3 */
	.word	0x02671023  /* 001F1C2C subu $v0,$s3,$a3 */
	.word	0x00021043  /* 001F1C30 sra $v0,$v0,0x1 */
	.word	0x02421821  /* 001F1C34 addu $v1,$s2,$v0 */
	.word	0x024F9021  /* 001F1C38 addu $s2,$s2,$t7 */
	.word	0x00671021  /* 001F1C3C addu $v0,$v1,$a3 */
	.word	0xAE230020  /* 001F1C40 sw $v1,32($s1) */
	.word	0xAE220040  /* 001F1C44 sw $v0,64($s1) */
	.word	0x26310050  /* 001F1C48 addiu $s1,$s1,80 */
	.word	0x2610FFFF  /* 001F1C4C addiu $s0,$s0,-1 */
	.word	0x0600003D  /* 001F1C50 bltz $s0,.L001F1D48 */
	.word	0x3C020000  /* 001F1C54 lui $v0,%hi(D_003E8CD8) */
	.reloc	.-4, R_MIPS_HI16, D_003E8CD8
	.word	0x3C030000  /* 001F1C58 lui $v1,%hi(D_003E8D00) */
	.reloc	.-4, R_MIPS_HI16, D_003E8D00
	.word	0x00102080  /* 001F1C5C sll $a0,$s0,0x2 */
	.word	0x24570000  /* 001F1C60 addiu $s7,$v0,%lo(D_003E8CD8) */
	.reloc	.-4, R_MIPS_LO16, D_003E8CD8
	.word	0x24790000  /* 001F1C64 addiu $t9,$v1,%lo(D_003E8D00) */
	.reloc	.-4, R_MIPS_LO16, D_003E8D00
	.word	0x009D4821  /* 001F1C68 addu $t1,$a0,$sp */
	.word	0x240A0012  /* 001F1C6C li $t2,18 */
	.word	0x3418FFF0  /* 001F1C70 li $t8,0xfff0 */
	.word	0x0018C0FC  /* 001F1C74 dsll32 $t8,$t8,0x3 */
	.word	0x24160016  /* 001F1C78 li $s6,22 */
	.word	0x3C0B0010  /* 001F1C7C lui $t3,0x10 */
	.word	0x34158000  /* 001F1C80 li $s5,0x8000 */
	.word	0x02936021  /* 001F1C84 addu $t4,$s4,$s3 */
	.word	0x8D220000  /* 001F1C88 lw $v0,0($t1) */
	.word	0x2529FFFC  /* 001F1C8C addiu $t1,$t1,-4 */
	.word	0x51400001  /* 001F1C90 beqzl $t2,.L001F1C98 */
	.word	0x000001CD  /* 001F1C94 break 0x0,0x7 */
	.word	0x2610FFFF  /* 001F1C98 addiu $s0,$s0,-1 */
	.word	0x00021080  /* 001F1C9C sll $v0,$v0,0x2 */
	.word	0x00571021  /* 001F1CA0 addu $v0,$v0,$s7 */
	.word	0x8C450000  /* 001F1CA4 lw $a1,0($v0) */
	.word	0x90A30006  /* 001F1CA8 lbu $v1,6($a1) */
	.word	0x90A40007  /* 001F1CAC lbu $a0,7($a1) */
	.word	0x00034100  /* 001F1CB0 sll $t0,$v1,0x4 */
	.word	0x94AD0004  /* 001F1CB4 lhu $t5,4($a1) */
	.word	0x011E3818  /* 001F1CB8 mult $a3,$t0,$s8 */
	.word	0x00041102  /* 001F1CBC srl $v0,$a0,0x4 */
	.word	0x00021080  /* 001F1CC0 sll $v0,$v0,0x2 */
	.word	0x3084000F  /* 001F1CC4 andi $a0,$a0,0xf */
	.word	0x00591021  /* 001F1CC8 addu $v0,$v0,$t9 */
	.word	0x0004263C  /* 001F1CCC dsll32 $a0,$a0,0x18 */
	.word	0x8C430000  /* 001F1CD0 lw $v1,0($v0) */
	.word	0x25A20120  /* 001F1CD4 addiu $v0,$t5,288 */
	.word	0x00EA001A  /* 001F1CD8 div $zero,$a3,$t2 */
	.word	0x94AE0002  /* 001F1CDC lhu $t6,2($a1) */
	.word	0x00031D38  /* 001F1CE0 dsll $v1,$v1,0x14 */
	.word	0xAE220034  /* 001F1CE4 sw $v0,52($s1) */
	.word	0x00641825  /* 001F1CE8 or $v1,$v1,$a0 */
	.word	0x01C83021  /* 001F1CEC addu $a2,$t6,$t0 */
	.word	0x00781825  /* 001F1CF0 or $v1,$v1,$t8 */
	.word	0xAE260030  /* 001F1CF4 sw $a2,48($s1) */
	.word	0xFE230000  /* 001F1CF8 sd $v1,0($s1) */
	.word	0xFE360008  /* 001F1CFC sd $s6,8($s1) */
	.word	0xAE2E0010  /* 001F1D00 sw $t6,16($s1) */
	.word	0xAE2D0014  /* 001F1D04 sw $t5,20($s1) */
	.word	0xAE340024  /* 001F1D08 sw $s4,36($s1) */
	.word	0xAE2B0028  /* 001F1D0C sw $t3,40($s1) */
	.word	0xAE35002C  /* 001F1D10 sw $s5,44($s1) */
	.word	0xAE2C0044  /* 001F1D14 sw $t4,68($s1) */
	.word	0xAE2B0048  /* 001F1D18 sw $t3,72($s1) */
	.word	0xAE20004C  /* 001F1D1C sw $zero,76($s1) */
	.word	0x00003812  /* 001F1D20 mflo $a3 */
	.word	0x02671023  /* 001F1D24 subu $v0,$s3,$a3 */
	.word	0x00021043  /* 001F1D28 sra $v0,$v0,0x1 */
	.word	0x02421821  /* 001F1D2C addu $v1,$s2,$v0 */
	.word	0x024F9021  /* 001F1D30 addu $s2,$s2,$t7 */
	.word	0x00671021  /* 001F1D34 addu $v0,$v1,$a3 */
	.word	0xAE230020  /* 001F1D38 sw $v1,32($s1) */
	.word	0xAE220040  /* 001F1D3C sw $v0,64($s1) */
	.word	0x0601FFD1  /* 001F1D40 bgez $s0,.L001F1C88 */
	.word	0x26310050  /* 001F1D44 addiu $s1,$s1,80 */
	.word	0x8FA30038  /* 001F1D48 lw $v1,56($sp) */
	.word	0x24040005  /* 001F1D4C li $a0,5 */
	.word	0x50800001  /* 001F1D50 beqzl $a0,.L001F1D58 */
	.word	0x000001CD  /* 001F1D54 break 0x0,0x7 */
	.word	0xDFB00040  /* 001F1D58 ld $s0,64($sp) */
	.word	0x02231023  /* 001F1D5C subu $v0,$s1,$v1 */
	.word	0x8FA30030  /* 001F1D60 lw $v1,48($sp) */
	.word	0x00021103  /* 001F1D64 sra $v0,$v0,0x4 */
	.word	0x26459000  /* 001F1D68 addiu $a1,$s2,-28672 */
	.word	0x0044001A  /* 001F1D6C div $zero,$v0,$a0 */
	.word	0x3C020004  /* 001F1D70 lui $v0,0x4 */
	.word	0x3442343E  /* 001F1D74 ori $v0,$v0,0x343e */
	.word	0x8FA4003C  /* 001F1D78 lw $a0,60($sp) */
	.word	0x00031BF8  /* 001F1D7C dsll $v1,$v1,0xf */
	.word	0x26868C00  /* 001F1D80 addiu $a2,$s4,-29696 */
	.word	0xDFB40060  /* 001F1D84 ld $s4,96($sp) */
	.word	0xFC820008  /* 001F1D88 sd $v0,8($a0) */
	.word	0x0220102D  /* 001F1D8C move $v0,$s1 */
	.word	0x3C0950AB  /* 001F1D90 lui $t1,0x50ab */
	.word	0x35294000  /* 001F1D94 ori $t1,$t1,0x4000 */
	.word	0x0009483C  /* 001F1D98 dsll32 $t1,$t1,0x0 */
	.word	0xDFB20050  /* 001F1D9C ld $s2,80($sp) */
	.word	0xDFB10048  /* 001F1DA0 ld $s1,72($sp) */
	.word	0x00052903  /* 001F1DA4 sra $a1,$a1,0x4 */
	.word	0xDFB30058  /* 001F1DA8 ld $s3,88($sp) */
	.word	0x00063103  /* 001F1DAC sra $a2,$a2,0x4 */
	.word	0xDFB50068  /* 001F1DB0 ld $s5,104($sp) */
	.word	0x3C070000  /* 001F1DB4 lui $a3,%hi(D_0063F74C) */
	.reloc	.-4, R_MIPS_HI16, D_0063F74C
	.word	0xDFB60070  /* 001F1DB8 ld $s6,112($sp) */
	.word	0x3C080000  /* 001F1DBC lui $t0,%hi(D_0063F750) */
	.reloc	.-4, R_MIPS_HI16, D_0063F750
	.word	0xDFB70078  /* 001F1DC0 ld $s7,120($sp) */
	.word	0xDFBE0080  /* 001F1DC4 ld $s8,128($sp) */
	.word	0xDFBF0088  /* 001F1DC8 ld $ra,136($sp) */
	.word	0x00002012  /* 001F1DCC mflo $a0 */
	.word	0x00831825  /* 001F1DD0 or $v1,$a0,$v1 */
	.word	0x8FA4003C  /* 001F1DD4 lw $a0,60($sp) */
	.word	0x00691825  /* 001F1DD8 or $v1,$v1,$t1 */
	.word	0xFC830000  /* 001F1DDC sd $v1,0($a0) */
	.word	0xACE50000  /* 001F1DE0 sw $a1,%lo(D_0063F74C)($a3) */
	.reloc	.-4, R_MIPS_LO16, D_0063F74C
	.word	0xAD060000  /* 001F1DE4 sw $a2,%lo(D_0063F750)($t0) */
	.reloc	.-4, R_MIPS_LO16, D_0063F750
	.word	0x03E00008  /* 001F1DE8 jr $ra */
	.word	0x27BD0090  /* 001F1DEC addiu $sp,$sp,144 */
	.end	func_001f18e8
