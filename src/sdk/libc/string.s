/* libc string functions (sdk segment): r5900 assembly using lq/sq and MMI (pcpyld, pcpyh, zero-byte tests). memcpy, memset, strcmp, strlen, memchr and memmove start 4 bytes off the 8-byte alignment every gcc function gets, so the originals were assembly; words with their disassembly. docs/sdk.md */
	.set	noreorder
	.set	noat

	.section	.text.memcmp,"ax",@progbits
	.globl	memcmp
	.ent	memcmp
memcmp:  /* 0x0024FF10 */
	.word	0x2CC20010  /* 0024FF10 sltiu $v0,$a2,16 */
	.word	0x14400011  /* 0024FF14 bnez $v0,.L0024FF5C */
	.word	0x00851025  /* 0024FF18 or $v0,$a0,$a1 */
	.word	0x3042000F  /* 0024FF1C andi $v0,$v0,0xf */
	.word	0x1440000E  /* 0024FF20 bnez $v0,.L0024FF5C */
	.word	0x00000000  /* 0024FF24 nop */
	.word	0x78830000  /* 0024FF28 lq $v1,0($a0) */
	.word	0x2CC70020  /* 0024FF2C sltiu $a3,$a2,32 */
	.word	0x78A20000  /* 0024FF30 lq $v0,0($a1) */
	.word	0x24840010  /* 0024FF34 addiu $a0,$a0,16 */
	.word	0x704344C9  /* 0024FF38 pxor $t0,$v0,$v1 */
	.word	0x24A20010  /* 0024FF3C addiu $v0,$a1,16 */
	.word	0x710753A9  /* 0024FF40 pcpyud $t2,$t0,$a3 */
	.word	0x01484825  /* 0024FF44 or $t1,$t2,$t0 */
	.word	0x0049280A  /* 0024FF48 movz $a1,$v0,$t1 */
	.word	0x55200003  /* 0024FF4C bnezl $t1,.L0024FF5C */
	.word	0x2484FFF0  /* 0024FF50 addiu $a0,$a0,-16 */
	.word	0x10E0FFF4  /* 0024FF54 beqz $a3,.L0024FF28 */
	.word	0x24C6FFF0  /* 0024FF58 addiu $a2,$a2,-16 */
	.word	0x3C02FFFF  /* 0024FF5C lui $v0,0xffff */
	.word	0x24C6FFFF  /* 0024FF60 addiu $a2,$a2,-1 */
	.word	0x3442FFFF  /* 0024FF64 ori $v0,$v0,0xffff */
	.word	0x10C2000C  /* 0024FF68 beq $a2,$v0,.L0024FF9C */
	.word	0x00000000  /* 0024FF6C nop */
	.word	0x3C07FFFF  /* 0024FF70 lui $a3,0xffff */
	.word	0x34E7FFFF  /* 0024FF74 ori $a3,$a3,0xffff */
	.word	0x90830000  /* 0024FF78 lbu $v1,0($a0) */
	.word	0x90A20000  /* 0024FF7C lbu $v0,0($a1) */
	.word	0x10620003  /* 0024FF80 beq $v1,$v0,.L0024FF90 */
	.word	0x24840001  /* 0024FF84 addiu $a0,$a0,1 */
	.word	0x03E00008  /* 0024FF88 jr $ra */
	.word	0x00621023  /* 0024FF8C subu $v0,$v1,$v0 */
	.word	0x24C6FFFF  /* 0024FF90 addiu $a2,$a2,-1 */
	.word	0x14C7FFF8  /* 0024FF94 bne $a2,$a3,.L0024FF78 */
	.word	0x24A50001  /* 0024FF98 addiu $a1,$a1,1 */
	.word	0x03E00008  /* 0024FF9C jr $ra */
	.word	0x0000102D  /* 0024FFA0 move $v0,$zero */
	.end	memcmp

	.section	.text.memcpy,"ax",@progbits
	.globl	memcpy
	.ent	memcpy
memcpy:  /* 0x0024FFA4 */
	.word	0x0080402D  /* 0024FFA4 move $t0,$a0 */
	.word	0x2CC20020  /* 0024FFA8 sltiu $v0,$a2,32 */
	.word	0x1440001C  /* 0024FFAC bnez $v0,.L00250020 */
	.word	0x0100182D  /* 0024FFB0 move $v1,$t0 */
	.word	0x00A81025  /* 0024FFB4 or $v0,$a1,$t0 */
	.word	0x3042000F  /* 0024FFB8 andi $v0,$v0,0xf */
	.word	0x54400019  /* 0024FFBC bnezl $v0,.L00250024 */
	.word	0x24C6FFFF  /* 0024FFC0 addiu $a2,$a2,-1 */
	.word	0x0100382D  /* 0024FFC4 move $a3,$t0 */
	.word	0x78A30000  /* 0024FFC8 lq $v1,0($a1) */
	.word	0x24C6FFE0  /* 0024FFCC addiu $a2,$a2,-32 */
	.word	0x24A50010  /* 0024FFD0 addiu $a1,$a1,16 */
	.word	0x2CC40020  /* 0024FFD4 sltiu $a0,$a2,32 */
	.word	0x7CE30000  /* 0024FFD8 sq $v1,0($a3) */
	.word	0x24E70010  /* 0024FFDC addiu $a3,$a3,16 */
	.word	0x78A20000  /* 0024FFE0 lq $v0,0($a1) */
	.word	0x24A50010  /* 0024FFE4 addiu $a1,$a1,16 */
	.word	0x7CE20000  /* 0024FFE8 sq $v0,0($a3) */
	.word	0x1080FFF6  /* 0024FFEC beqz $a0,.L0024FFC8 */
	.word	0x24E70010  /* 0024FFF0 addiu $a3,$a3,16 */
	.word	0x2CC20008  /* 0024FFF4 sltiu $v0,$a2,8 */
	.word	0x14400009  /* 0024FFF8 bnez $v0,.L00250020 */
	.word	0x00E0182D  /* 0024FFFC move $v1,$a3 */
	.word	0xDCA30000  /* 00250000 ld $v1,0($a1) */
	.word	0x24C6FFF8  /* 00250004 addiu $a2,$a2,-8 */
	.word	0x24A50008  /* 00250008 addiu $a1,$a1,8 */
	.word	0x2CC20008  /* 0025000C sltiu $v0,$a2,8 */
	.word	0xFCE30000  /* 00250010 sd $v1,0($a3) */
	.word	0x1040FFFA  /* 00250014 beqz $v0,.L00250000 */
	.word	0x24E70008  /* 00250018 addiu $a3,$a3,8 */
	.word	0x00E0182D  /* 0025001C move $v1,$a3 */
	.word	0x24C6FFFF  /* 00250020 addiu $a2,$a2,-1 */
	.word	0x2402FFFF  /* 00250024 li $v0,-1 */
	.word	0x10C20008  /* 00250028 beq $a2,$v0,.L0025004C */
	.word	0x0040202D  /* 0025002C move $a0,$v0 */
	.word	0x90A20000  /* 00250030 lbu $v0,0($a1) */
	.word	0x24C6FFFF  /* 00250034 addiu $a2,$a2,-1 */
	.word	0x24A50001  /* 00250038 addiu $a1,$a1,1 */
	.word	0xA0620000  /* 0025003C sb $v0,0($v1) */
	.word	0x24630001  /* 00250040 addiu $v1,$v1,1 */
	.word	0x14C4FFFA  /* 00250044 bne $a2,$a0,.L00250030 */
	.word	0x00000000  /* 00250048 nop */
	.word	0x03E00008  /* 0025004C jr $ra */
	.word	0x0100102D  /* 00250050 move $v0,$t0 */
	.end	memcpy

	.section	.text.memset,"ax",@progbits
	.globl	memset
	.ent	memset
memset:  /* 0x00250054 */
	.word	0x2CC20008  /* 00250054 sltiu $v0,$a2,8 */
	.word	0x1440001E  /* 00250058 bnez $v0,.L002500D4 */
	.word	0x0080182D  /* 0025005C move $v1,$a0 */
	.word	0x3082000F  /* 00250060 andi $v0,$a0,0xf */
	.word	0x1440001B  /* 00250064 bnez $v0,.L002500D4 */
	.word	0x0080382D  /* 00250068 move $a3,$a0 */
	.word	0x30A900FF  /* 0025006C andi $t1,$a1,0xff */
	.word	0x2CCA0020  /* 00250070 sltiu $t2,$a2,32 */
	.word	0x0120402D  /* 00250074 move $t0,$t1 */
	.word	0x00081A38  /* 00250078 dsll $v1,$t0,0x8 */
	.word	0x00694025  /* 0025007C or $t0,$v1,$t1 */
	.word	0x70081EE9  /* 00250080 pcpyh $v1,$t0 */
	.word	0x1540000E  /* 00250084 bnez $t2,.L002500C0 */
	.word	0x2CC20008  /* 00250088 sltiu $v0,$a2,8 */
	.word	0x70634389  /* 0025008C pcpyld $t0,$v1,$v1 */
	.word	0x7CE80000  /* 00250090 sq $t0,0($a3) */
	.word	0x24C6FFE0  /* 00250094 addiu $a2,$a2,-32 */
	.word	0x24E70010  /* 00250098 addiu $a3,$a3,16 */
	.word	0x2CC20020  /* 0025009C sltiu $v0,$a2,32 */
	.word	0x7CE80000  /* 002500A0 sq $t0,0($a3) */
	.word	0x1040FFFA  /* 002500A4 beqz $v0,.L00250090 */
	.word	0x24E70010  /* 002500A8 addiu $a3,$a3,16 */
	.word	0x10000004  /* 002500AC b .L002500C0 */
	.word	0x2CC20008  /* 002500B0 sltiu $v0,$a2,8 */
	.word	0x24C6FFF8  /* 002500B4 addiu $a2,$a2,-8 */
	.word	0x24E70008  /* 002500B8 addiu $a3,$a3,8 */
	.word	0x2CC20008  /* 002500BC sltiu $v0,$a2,8 */
	.word	0x00000000  /* 002500C0 nop */
	.word	0x00000000  /* 002500C4 nop */
	.word	0x5040FFFA  /* 002500C8 beqzl $v0,.L002500B4 */
	.word	0xFCE30000  /* 002500CC sd $v1,0($a3) */
	.word	0x00E0182D  /* 002500D0 move $v1,$a3 */
	.word	0x3C02FFFF  /* 002500D4 lui $v0,0xffff */
	.word	0x24C6FFFF  /* 002500D8 addiu $a2,$a2,-1 */
	.word	0x3442FFFF  /* 002500DC ori $v0,$v0,0xffff */
	.word	0x10C2000A  /* 002500E0 beq $a2,$v0,.L0025010C */
	.word	0x00000000  /* 002500E4 nop */
	.word	0x3C02FFFF  /* 002500E8 lui $v0,0xffff */
	.word	0x3442FFFF  /* 002500EC ori $v0,$v0,0xffff */
	.word	0xA0650000  /* 002500F0 sb $a1,0($v1) */
	.word	0x24C6FFFF  /* 002500F4 addiu $a2,$a2,-1 */
	.word	0x24630001  /* 002500F8 addiu $v1,$v1,1 */
	.word	0x00000000  /* 002500FC nop */
	.word	0x00000000  /* 00250100 nop */
	.word	0x14C2FFFA  /* 00250104 bne $a2,$v0,.L002500F0 */
	.word	0x00000000  /* 00250108 nop */
	.word	0x03E00008  /* 0025010C jr $ra */
	.word	0x0080102D  /* 00250110 move $v0,$a0 */
	.end	memset

	.section	.text.strcat,"ax",@progbits
	.globl	strcat
	.ent	strcat
strcat:  /* 0x00250F40 */
	.word	0x27BDFFE0  /* 00250F40 addiu $sp,$sp,-32 */
	.word	0x7FB00000  /* 00250F44 sq $s0,0($sp) */
	.word	0x0080802D  /* 00250F48 move $s0,$a0 */
	.word	0x32020007  /* 00250F4C andi $v0,$s0,0x7 */
	.word	0x14400038  /* 00250F50 bnez $v0,.L00251034 */
	.word	0x7FBF0010  /* 00250F54 sq $ra,16($sp) */
	.word	0x3202000F  /* 00250F58 andi $v0,$s0,0xf */
	.word	0x3C030101  /* 00250F5C lui $v1,0x101 */
	.word	0x34630101  /* 00250F60 ori $v1,$v1,0x101 */
	.word	0x00031C38  /* 00250F64 dsll $v1,$v1,0x10 */
	.word	0x34630101  /* 00250F68 ori $v1,$v1,0x101 */
	.word	0x00031C38  /* 00250F6C dsll $v1,$v1,0x10 */
	.word	0x34630101  /* 00250F70 ori $v1,$v1,0x101 */
	.word	0x3C048080  /* 00250F74 lui $a0,0x8080 */
	.word	0x34848080  /* 00250F78 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 00250F7C dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00250F80 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 00250F84 dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00250F88 ori $a0,$a0,0x8080 */
	.word	0x14400018  /* 00250F8C bnez $v0,.L00250FF0 */
	.word	0xDE060000  /* 00250F90 ld $a2,0($s0) */
	.word	0x7A020000  /* 00250F94 lq $v0,0($s0) */
	.word	0x70633B89  /* 00250F98 pcpyld $a3,$v1,$v1 */
	.word	0x70844389  /* 00250F9C pcpyld $t0,$a0,$a0 */
	.word	0x70471A48  /* 00250FA0 psubb $v1,$v0,$a3 */
	.word	0x700214E9  /* 00250FA4 pnor $v0,$zero,$v0 */
	.word	0x70621C89  /* 00250FA8 pand $v1,$v1,$v0 */
	.word	0x70681C89  /* 00250FAC pand $v1,$v1,$t0 */
	.word	0x706313A9  /* 00250FB0 pcpyud $v0,$v1,$v1 */
	.word	0x00431825  /* 00250FB4 or $v1,$v0,$v1 */
	.word	0x1460001E  /* 00250FB8 bnez $v1,.L00251034 */
	.word	0x0200202D  /* 00250FBC move $a0,$s0 */
	.word	0x24860010  /* 00250FC0 addiu $a2,$a0,16 */
	.word	0x78C20000  /* 00250FC4 lq $v0,0($a2) */
	.word	0x70021CE9  /* 00250FC8 pnor $v1,$zero,$v0 */
	.word	0x70471248  /* 00250FCC psubb $v0,$v0,$a3 */
	.word	0x70431489  /* 00250FD0 pand $v0,$v0,$v1 */
	.word	0x70481489  /* 00250FD4 pand $v0,$v0,$t0 */
	.word	0x70421BA9  /* 00250FD8 pcpyud $v1,$v0,$v0 */
	.word	0x00431025  /* 00250FDC or $v0,$v0,$v1 */
	.word	0x5040FFF8  /* 00250FE0 beqzl $v0,.L00250FC4 */
	.word	0x24C60010  /* 00250FE4 addiu $a2,$a2,16 */
	.word	0x10000012  /* 00250FE8 b .L00251034 */
	.word	0x00C0202D  /* 00250FEC move $a0,$a2 */
	.word	0x0060382D  /* 00250FF0 move $a3,$v1 */
	.word	0x0080402D  /* 00250FF4 move $t0,$a0 */
	.word	0x00C3182F  /* 00250FF8 dsubu $v1,$a2,$v1 */
	.word	0x00061027  /* 00250FFC nor $v0,$zero,$a2 */
	.word	0x00621824  /* 00251000 and $v1,$v1,$v0 */
	.word	0x00641824  /* 00251004 and $v1,$v1,$a0 */
	.word	0x1460000A  /* 00251008 bnez $v1,.L00251034 */
	.word	0x0200202D  /* 0025100C move $a0,$s0 */
	.word	0x26060008  /* 00251010 addiu $a2,$s0,8 */
	.word	0xDCC20000  /* 00251014 ld $v0,0($a2) */
	.word	0x00021827  /* 00251018 nor $v1,$zero,$v0 */
	.word	0x0047102F  /* 0025101C dsubu $v0,$v0,$a3 */
	.word	0x00431024  /* 00251020 and $v0,$v0,$v1 */
	.word	0x00481024  /* 00251024 and $v0,$v0,$t0 */
	.word	0x5040FFFA  /* 00251028 beqzl $v0,.L00251014 */
	.word	0x24C60008  /* 0025102C addiu $a2,$a2,8 */
	.word	0x00C0202D  /* 00251030 move $a0,$a2 */
	.word	0x80820000  /* 00251034 lb $v0,0($a0) */
	.word	0x00000000  /* 00251038 nop */
	.word	0x00000000  /* 0025103C nop */
	.word	0x00000000  /* 00251040 nop */
	.word	0x00000000  /* 00251044 nop */
	.word	0x5440FFFA  /* 00251048 bnezl $v0,.L00251034 */
	.word	0x24840001  /* 0025104C addiu $a0,$a0,1 */
	.word	0x0C000000  /* 00251050 jal strcpy */
	.reloc	.-4, R_MIPS_26, strcpy
	.word	0x00000000  /* 00251054 nop */
	.word	0x0200102D  /* 00251058 move $v0,$s0 */
	.word	0x7BBF0010  /* 0025105C lq $ra,16($sp) */
	.word	0x7BB00000  /* 00251060 lq $s0,0($sp) */
	.word	0x03E00008  /* 00251064 jr $ra */
	.word	0x27BD0020  /* 00251068 addiu $sp,$sp,32 */
	.end	strcat

	.section	.text.strcmp,"ax",@progbits
	.globl	strcmp
	.ent	strcmp
strcmp:  /* 0x0025106C */
	.word	0x00854025  /* 0025106C or $t0,$a0,$a1 */
	.word	0x31020007  /* 00251070 andi $v0,$t0,0x7 */
	.word	0x54400049  /* 00251074 bnezl $v0,.L0025119C */
	.word	0x80820000  /* 00251078 lb $v0,0($a0) */
	.word	0x3109000F  /* 0025107C andi $t1,$t0,0xf */
	.word	0x3C070101  /* 00251080 lui $a3,0x101 */
	.word	0x34E70101  /* 00251084 ori $a3,$a3,0x101 */
	.word	0x00073C38  /* 00251088 dsll $a3,$a3,0x10 */
	.word	0x34E70101  /* 0025108C ori $a3,$a3,0x101 */
	.word	0x00073C38  /* 00251090 dsll $a3,$a3,0x10 */
	.word	0x34E70101  /* 00251094 ori $a3,$a3,0x101 */
	.word	0x3C068080  /* 00251098 lui $a2,0x8080 */
	.word	0x34C68080  /* 0025109C ori $a2,$a2,0x8080 */
	.word	0x00063438  /* 002510A0 dsll $a2,$a2,0x10 */
	.word	0x34C68080  /* 002510A4 ori $a2,$a2,0x8080 */
	.word	0x00063438  /* 002510A8 dsll $a2,$a2,0x10 */
	.word	0x34C68080  /* 002510AC ori $a2,$a2,0x8080 */
	.word	0x1520001F  /* 002510B0 bnez $t1,.L00251130 */
	.word	0xDCA20000  /* 002510B4 ld $v0,0($a1) */
	.word	0x78830000  /* 002510B8 lq $v1,0($a0) */
	.word	0x70E74389  /* 002510BC pcpyld $t0,$a3,$a3 */
	.word	0x78A20000  /* 002510C0 lq $v0,0($a1) */
	.word	0x70C65389  /* 002510C4 pcpyld $t2,$a2,$a2 */
	.word	0x70433848  /* 002510C8 psubw $a3,$v0,$v1 */
	.word	0x70E433A9  /* 002510CC pcpyud $a2,$a3,$a0 */
	.word	0x00C71825  /* 002510D0 or $v1,$a2,$a3 */
	.word	0x54600031  /* 002510D4 bnezl $v1,.L0025119C */
	.word	0x80820000  /* 002510D8 lb $v0,0($a0) */
	.word	0x78820000  /* 002510DC lq $v0,0($a0) */
	.word	0x70021CE9  /* 002510E0 pnor $v1,$zero,$v0 */
	.word	0x70481248  /* 002510E4 psubb $v0,$v0,$t0 */
	.word	0x70431489  /* 002510E8 pand $v0,$v0,$v1 */
	.word	0x704A1489  /* 002510EC pand $v0,$v0,$t2 */
	.word	0x70441BA9  /* 002510F0 pcpyud $v1,$v0,$a0 */
	.word	0x00623025  /* 002510F4 or $a2,$v1,$v0 */
	.word	0x10C00003  /* 002510F8 beqz $a2,.L00251108 */
	.word	0x24840010  /* 002510FC addiu $a0,$a0,16 */
	.word	0x03E00008  /* 00251100 jr $ra */
	.word	0x0000102D  /* 00251104 move $v0,$zero */
	.word	0x24A50010  /* 00251108 addiu $a1,$a1,16 */
	.word	0x78820000  /* 0025110C lq $v0,0($a0) */
	.word	0x78A30000  /* 00251110 lq $v1,0($a1) */
	.word	0x70433848  /* 00251114 psubw $a3,$v0,$v1 */
	.word	0x70E433A9  /* 00251118 pcpyud $a2,$a3,$a0 */
	.word	0x00C74825  /* 0025111C or $t1,$a2,$a3 */
	.word	0x5120FFF0  /* 00251120 beqzl $t1,.L002510E4 */
	.word	0x70021CE9  /* 00251124 pnor $v1,$zero,$v0 */
	.word	0x1000001C  /* 00251128 b .L0025119C */
	.word	0x80820000  /* 0025112C lb $v0,0($a0) */
	.word	0xDC830000  /* 00251130 ld $v1,0($a0) */
	.word	0x54620019  /* 00251134 bnel $v1,$v0,.L0025119C */
	.word	0x80820000  /* 00251138 lb $v0,0($a0) */
	.word	0xDC820000  /* 0025113C ld $v0,0($a0) */
	.word	0x00024027  /* 00251140 nor $t0,$zero,$v0 */
	.word	0x0047102F  /* 00251144 dsubu $v0,$v0,$a3 */
	.word	0x00481024  /* 00251148 and $v0,$v0,$t0 */
	.word	0x00461024  /* 0025114C and $v0,$v0,$a2 */
	.word	0x10400003  /* 00251150 beqz $v0,.L00251160 */
	.word	0x24840008  /* 00251154 addiu $a0,$a0,8 */
	.word	0x03E00008  /* 00251158 jr $ra */
	.word	0x0000102D  /* 0025115C move $v0,$zero */
	.word	0x24A50008  /* 00251160 addiu $a1,$a1,8 */
	.word	0xDC820000  /* 00251164 ld $v0,0($a0) */
	.word	0xDCA30000  /* 00251168 ld $v1,0($a1) */
	.word	0x5062FFF5  /* 0025116C beql $v1,$v0,.L00251144 */
	.word	0x00024027  /* 00251170 nor $t0,$zero,$v0 */
	.word	0x10000009  /* 00251174 b .L0025119C */
	.word	0x80820000  /* 00251178 lb $v0,0($a0) */
	.word	0x00031600  /* 0025117C sll $v0,$v1,0x18 */
	.word	0x80A30000  /* 00251180 lb $v1,0($a1) */
	.word	0x00021603  /* 00251184 sra $v0,$v0,0x18 */
	.word	0x54430006  /* 00251188 bnel $v0,$v1,.L002511A4 */
	.word	0x90830000  /* 0025118C lbu $v1,0($a0) */
	.word	0x24840001  /* 00251190 addiu $a0,$a0,1 */
	.word	0x24A50001  /* 00251194 addiu $a1,$a1,1 */
	.word	0x80820000  /* 00251198 lb $v0,0($a0) */
	.word	0x1440FFF7  /* 0025119C bnez $v0,.L0025117C */
	.word	0x90830000  /* 002511A0 lbu $v1,0($a0) */
	.word	0x90A20000  /* 002511A4 lbu $v0,0($a1) */
	.word	0x03E00008  /* 002511A8 jr $ra */
	.word	0x00621023  /* 002511AC subu $v0,$v1,$v0 */
	.end	strcmp

	.section	.text.strcpy,"ax",@progbits
	.globl	strcpy
	.ent	strcpy
strcpy:  /* 0x002511B0 */
	.word	0x0080382D  /* 002511B0 move $a3,$a0 */
	.word	0x00A74025  /* 002511B4 or $t0,$a1,$a3 */
	.word	0x31020007  /* 002511B8 andi $v0,$t0,0x7 */
	.word	0x14400038  /* 002511BC bnez $v0,.L002512A0 */
	.word	0x00E0182D  /* 002511C0 move $v1,$a3 */
	.word	0x3102000F  /* 002511C4 andi $v0,$t0,0xf */
	.word	0x3C090101  /* 002511C8 lui $t1,0x101 */
	.word	0x35290101  /* 002511CC ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 002511D0 dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 002511D4 ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 002511D8 dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 002511DC ori $t1,$t1,0x101 */
	.word	0x3C048080  /* 002511E0 lui $a0,0x8080 */
	.word	0x34848080  /* 002511E4 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 002511E8 dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 002511EC ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 002511F0 dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 002511F4 ori $a0,$a0,0x8080 */
	.word	0x54400019  /* 002511F8 bnezl $v0,.L00251260 */
	.word	0xDCAA0000  /* 002511FC ld $t2,0($a1) */
	.word	0x71295389  /* 00251200 pcpyld $t2,$t1,$t1 */
	.word	0x78A90000  /* 00251204 lq $t1,0($a1) */
	.word	0x70844389  /* 00251208 pcpyld $t0,$a0,$a0 */
	.word	0x712A1248  /* 0025120C psubb $v0,$t1,$t2 */
	.word	0x70091CE9  /* 00251210 pnor $v1,$zero,$t1 */
	.word	0x70431489  /* 00251214 pand $v0,$v0,$v1 */
	.word	0x70481489  /* 00251218 pand $v0,$v0,$t0 */
	.word	0x704923A9  /* 0025121C pcpyud $a0,$v0,$t1 */
	.word	0x00441825  /* 00251220 or $v1,$v0,$a0 */
	.word	0x1460001D  /* 00251224 bnez $v1,.L0025129C */
	.word	0x00E0302D  /* 00251228 move $a2,$a3 */
	.word	0x7CC90000  /* 0025122C sq $t1,0($a2) */
	.word	0x24A50010  /* 00251230 addiu $a1,$a1,16 */
	.word	0x78A90000  /* 00251234 lq $t1,0($a1) */
	.word	0x712A1248  /* 00251238 psubb $v0,$t1,$t2 */
	.word	0x70091CE9  /* 0025123C pnor $v1,$zero,$t1 */
	.word	0x70431489  /* 00251240 pand $v0,$v0,$v1 */
	.word	0x70481489  /* 00251244 pand $v0,$v0,$t0 */
	.word	0x704923A9  /* 00251248 pcpyud $a0,$v0,$t1 */
	.word	0x00441825  /* 0025124C or $v1,$v0,$a0 */
	.word	0x1060FFF6  /* 00251250 beqz $v1,.L0025122C */
	.word	0x24C60010  /* 00251254 addiu $a2,$a2,16 */
	.word	0x10000011  /* 00251258 b .L002512A0 */
	.word	0x00C0182D  /* 0025125C move $v1,$a2 */
	.word	0x0149102F  /* 00251260 dsubu $v0,$t2,$t1 */
	.word	0x000A1827  /* 00251264 nor $v1,$zero,$t2 */
	.word	0x00431024  /* 00251268 and $v0,$v0,$v1 */
	.word	0x00441024  /* 0025126C and $v0,$v0,$a0 */
	.word	0x1440000A  /* 00251270 bnez $v0,.L0025129C */
	.word	0x00E0302D  /* 00251274 move $a2,$a3 */
	.word	0xFCCA0000  /* 00251278 sd $t2,0($a2) */
	.word	0x24A50008  /* 0025127C addiu $a1,$a1,8 */
	.word	0xDCAA0000  /* 00251280 ld $t2,0($a1) */
	.word	0x000A1027  /* 00251284 nor $v0,$zero,$t2 */
	.word	0x0149182F  /* 00251288 dsubu $v1,$t2,$t1 */
	.word	0x00621824  /* 0025128C and $v1,$v1,$v0 */
	.word	0x00641824  /* 00251290 and $v1,$v1,$a0 */
	.word	0x1060FFF8  /* 00251294 beqz $v1,.L00251278 */
	.word	0x24C60008  /* 00251298 addiu $a2,$a2,8 */
	.word	0x00C0182D  /* 0025129C move $v1,$a2 */
	.word	0x90A20000  /* 002512A0 lbu $v0,0($a1) */
	.word	0x24A50001  /* 002512A4 addiu $a1,$a1,1 */
	.word	0xA0620000  /* 002512A8 sb $v0,0($v1) */
	.word	0x00021600  /* 002512AC sll $v0,$v0,0x18 */
	.word	0x24630001  /* 002512B0 addiu $v1,$v1,1 */
	.word	0x1440FFFA  /* 002512B4 bnez $v0,.L002512A0 */
	.word	0x00000000  /* 002512B8 nop */
	.word	0x03E00008  /* 002512BC jr $ra */
	.word	0x00E0102D  /* 002512C0 move $v0,$a3 */
	.end	strcpy

	.section	.text.strlen,"ax",@progbits
	.globl	strlen
	.ent	strlen
strlen:  /* 0x002512C4 */
	.word	0x30820007  /* 002512C4 andi $v0,$a0,0x7 */
	.word	0x14400043  /* 002512C8 bnez $v0,.L002513D8 */
	.word	0x0080382D  /* 002512CC move $a3,$a0 */
	.word	0x3083000F  /* 002512D0 andi $v1,$a0,0xf */
	.word	0x3C020101  /* 002512D4 lui $v0,0x101 */
	.word	0x34420101  /* 002512D8 ori $v0,$v0,0x101 */
	.word	0x00021438  /* 002512DC dsll $v0,$v0,0x10 */
	.word	0x34420101  /* 002512E0 ori $v0,$v0,0x101 */
	.word	0x00021438  /* 002512E4 dsll $v0,$v0,0x10 */
	.word	0x34420101  /* 002512E8 ori $v0,$v0,0x101 */
	.word	0x1460001E  /* 002512EC bnez $v1,.L00251368 */
	.word	0x0080282D  /* 002512F0 move $a1,$a0 */
	.word	0x78A30000  /* 002512F4 lq $v1,0($a1) */
	.word	0x70424389  /* 002512F8 pcpyld $t0,$v0,$v0 */
	.word	0x3C048080  /* 002512FC lui $a0,0x8080 */
	.word	0x34848080  /* 00251300 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 00251304 dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00251308 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 0025130C dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00251310 ori $a0,$a0,0x8080 */
	.word	0x70681248  /* 00251314 psubb $v0,$v1,$t0 */
	.word	0x70031CE9  /* 00251318 pnor $v1,$zero,$v1 */
	.word	0x70844B89  /* 0025131C pcpyld $t1,$a0,$a0 */
	.word	0x70431489  /* 00251320 pand $v0,$v0,$v1 */
	.word	0x70491489  /* 00251324 pand $v0,$v0,$t1 */
	.word	0x70481BA9  /* 00251328 pcpyud $v1,$v0,$t0 */
	.word	0x00623025  /* 0025132C or $a2,$v1,$v0 */
	.word	0x54C00029  /* 00251330 bnezl $a2,.L002513D8 */
	.word	0x00A0202D  /* 00251334 move $a0,$a1 */
	.word	0x24A50010  /* 00251338 addiu $a1,$a1,16 */
	.word	0x78A20000  /* 0025133C lq $v0,0($a1) */
	.word	0x70021CE9  /* 00251340 pnor $v1,$zero,$v0 */
	.word	0x70481248  /* 00251344 psubb $v0,$v0,$t0 */
	.word	0x70431489  /* 00251348 pand $v0,$v0,$v1 */
	.word	0x70492489  /* 0025134C pand $a0,$v0,$t1 */
	.word	0x70861BA9  /* 00251350 pcpyud $v1,$a0,$a2 */
	.word	0x00641825  /* 00251354 or $v1,$v1,$a0 */
	.word	0x5060FFF8  /* 00251358 beqzl $v1,.L0025133C */
	.word	0x24A50010  /* 0025135C addiu $a1,$a1,16 */
	.word	0x1000001D  /* 00251360 b .L002513D8 */
	.word	0x00A0202D  /* 00251364 move $a0,$a1 */
	.word	0xDCA30000  /* 00251368 ld $v1,0($a1) */
	.word	0x3C048080  /* 0025136C lui $a0,0x8080 */
	.word	0x34848080  /* 00251370 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 00251374 dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00251378 ori $a0,$a0,0x8080 */
	.word	0x00042438  /* 0025137C dsll $a0,$a0,0x10 */
	.word	0x34848080  /* 00251380 ori $a0,$a0,0x8080 */
	.word	0x0062102F  /* 00251384 dsubu $v0,$v1,$v0 */
	.word	0x00031827  /* 00251388 nor $v1,$zero,$v1 */
	.word	0x00431024  /* 0025138C and $v0,$v0,$v1 */
	.word	0x00441024  /* 00251390 and $v0,$v0,$a0 */
	.word	0x54400010  /* 00251394 bnezl $v0,.L002513D8 */
	.word	0x00A0202D  /* 00251398 move $a0,$a1 */
	.word	0x3C060101  /* 0025139C lui $a2,0x101 */
	.word	0x34C60101  /* 002513A0 ori $a2,$a2,0x101 */
	.word	0x00063438  /* 002513A4 dsll $a2,$a2,0x10 */
	.word	0x34C60101  /* 002513A8 ori $a2,$a2,0x101 */
	.word	0x00063438  /* 002513AC dsll $a2,$a2,0x10 */
	.word	0x34C60101  /* 002513B0 ori $a2,$a2,0x101 */
	.word	0x24A50008  /* 002513B4 addiu $a1,$a1,8 */
	.word	0xDCA20000  /* 002513B8 ld $v0,0($a1) */
	.word	0x00021827  /* 002513BC nor $v1,$zero,$v0 */
	.word	0x0046102F  /* 002513C0 dsubu $v0,$v0,$a2 */
	.word	0x00431024  /* 002513C4 and $v0,$v0,$v1 */
	.word	0x00441024  /* 002513C8 and $v0,$v0,$a0 */
	.word	0x5040FFFA  /* 002513CC beqzl $v0,.L002513B8 */
	.word	0x24A50008  /* 002513D0 addiu $a1,$a1,8 */
	.word	0x00A0202D  /* 002513D4 move $a0,$a1 */
	.word	0x80820000  /* 002513D8 lb $v0,0($a0) */
	.word	0x00000000  /* 002513DC nop */
	.word	0x00000000  /* 002513E0 nop */
	.word	0x00000000  /* 002513E4 nop */
	.word	0x00000000  /* 002513E8 nop */
	.word	0x5440FFFA  /* 002513EC bnezl $v0,.L002513D8 */
	.word	0x24840001  /* 002513F0 addiu $a0,$a0,1 */
	.word	0x03E00008  /* 002513F4 jr $ra */
	.word	0x00871023  /* 002513F8 subu $v0,$a0,$a3 */
	.end	strlen

	.section	.text.strncmp,"ax",@progbits
	.globl	strncmp
	.ent	strncmp
strncmp:  /* 0x00251400 */
	.word	0x14C00003  /* 00251400 bnez $a2,.L00251410 */
	.word	0x00851825  /* 00251404 or $v1,$a0,$a1 */
	.word	0x03E00008  /* 00251408 jr $ra */
	.word	0x0000102D  /* 0025140C move $v0,$zero */
	.word	0x30620007  /* 00251410 andi $v0,$v1,0x7 */
	.word	0x14400055  /* 00251414 bnez $v0,.L0025156C */
	.word	0x00C0102D  /* 00251418 move $v0,$a2 */
	.word	0x3062000F  /* 0025141C andi $v0,$v1,0xf */
	.word	0x2CC70010  /* 00251420 sltiu $a3,$a2,16 */
	.word	0x3C090101  /* 00251424 lui $t1,0x101 */
	.word	0x35290101  /* 00251428 ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 0025142C dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 00251430 ori $t1,$t1,0x101 */
	.word	0x00094C38  /* 00251434 dsll $t1,$t1,0x10 */
	.word	0x35290101  /* 00251438 ori $t1,$t1,0x101 */
	.word	0x00471025  /* 0025143C or $v0,$v0,$a3 */
	.word	0x14400029  /* 00251440 bnez $v0,.L002514E8 */
	.word	0x0080382D  /* 00251444 move $a3,$a0 */
	.word	0x78830000  /* 00251448 lq $v1,0($a0) */
	.word	0x71295389  /* 0025144C pcpyld $t2,$t1,$t1 */
	.word	0x78A20000  /* 00251450 lq $v0,0($a1) */
	.word	0x3C088080  /* 00251454 lui $t0,0x8080 */
	.word	0x35088080  /* 00251458 ori $t0,$t0,0x8080 */
	.word	0x00084438  /* 0025145C dsll $t0,$t0,0x10 */
	.word	0x35088080  /* 00251460 ori $t0,$t0,0x8080 */
	.word	0x00084438  /* 00251464 dsll $t0,$t0,0x10 */
	.word	0x35088080  /* 00251468 ori $t0,$t0,0x8080 */
	.word	0x70621848  /* 0025146C psubw $v1,$v1,$v0 */
	.word	0x71084B89  /* 00251470 pcpyld $t1,$t0,$t0 */
	.word	0x706413A9  /* 00251474 pcpyud $v0,$v1,$a0 */
	.word	0x00A0402D  /* 00251478 move $t0,$a1 */
	.word	0x00431825  /* 0025147C or $v1,$v0,$v1 */
	.word	0x1460003A  /* 00251480 bnez $v1,.L0025156C */
	.word	0x00C0102D  /* 00251484 move $v0,$a2 */
	.word	0x24C6FFF0  /* 00251488 addiu $a2,$a2,-16 */
	.word	0x10C0FFDE  /* 0025148C beqz $a2,.L00251408 */
	.word	0x00000000  /* 00251490 nop */
	.word	0x78E20000  /* 00251494 lq $v0,0($a3) */
	.word	0x70021CE9  /* 00251498 pnor $v1,$zero,$v0 */
	.word	0x704A1248  /* 0025149C psubb $v0,$v0,$t2 */
	.word	0x70431489  /* 002514A0 pand $v0,$v0,$v1 */
	.word	0x70491C89  /* 002514A4 pand $v1,$v0,$t1 */
	.word	0x706413A9  /* 002514A8 pcpyud $v0,$v1,$a0 */
	.word	0x00431025  /* 002514AC or $v0,$v0,$v1 */
	.word	0x1440FFD5  /* 002514B0 bnez $v0,.L00251408 */
	.word	0x24E70010  /* 002514B4 addiu $a3,$a3,16 */
	.word	0x2CC20010  /* 002514B8 sltiu $v0,$a2,16 */
	.word	0x78E30000  /* 002514BC lq $v1,0($a3) */
	.word	0x14400027  /* 002514C0 bnez $v0,.L00251560 */
	.word	0x25080010  /* 002514C4 addiu $t0,$t0,16 */
	.word	0x79020000  /* 002514C8 lq $v0,0($t0) */
	.word	0x70621848  /* 002514CC psubw $v1,$v1,$v0 */
	.word	0x706413A9  /* 002514D0 pcpyud $v0,$v1,$a0 */
	.word	0x00431025  /* 002514D4 or $v0,$v0,$v1 */
	.word	0x5040FFEC  /* 002514D8 beqzl $v0,.L0025148C */
	.word	0x24C6FFF0  /* 002514DC addiu $a2,$a2,-16 */
	.word	0x10000020  /* 002514E0 b .L00251564 */
	.word	0x00E0202D  /* 002514E4 move $a0,$a3 */
	.word	0x2CC20008  /* 002514E8 sltiu $v0,$a2,8 */
	.word	0x1440001C  /* 002514EC bnez $v0,.L00251560 */
	.word	0x00A0402D  /* 002514F0 move $t0,$a1 */
	.word	0xDC830000  /* 002514F4 ld $v1,0($a0) */
	.word	0xDCA20000  /* 002514F8 ld $v0,0($a1) */
	.word	0x1462001B  /* 002514FC bne $v1,$v0,.L0025156C */
	.word	0x00C0102D  /* 00251500 move $v0,$a2 */
	.word	0x24C6FFF8  /* 00251504 addiu $a2,$a2,-8 */
	.word	0x3C0A8080  /* 00251508 lui $t2,0x8080 */
	.word	0x354A8080  /* 0025150C ori $t2,$t2,0x8080 */
	.word	0x000A5438  /* 00251510 dsll $t2,$t2,0x10 */
	.word	0x354A8080  /* 00251514 ori $t2,$t2,0x8080 */
	.word	0x000A5438  /* 00251518 dsll $t2,$t2,0x10 */
	.word	0x354A8080  /* 0025151C ori $t2,$t2,0x8080 */
	.word	0x10C0FFB9  /* 00251520 beqz $a2,.L00251408 */
	.word	0x00000000  /* 00251524 nop */
	.word	0xDCE20000  /* 00251528 ld $v0,0($a3) */
	.word	0x00021827  /* 0025152C nor $v1,$zero,$v0 */
	.word	0x0049102F  /* 00251530 dsubu $v0,$v0,$t1 */
	.word	0x00431024  /* 00251534 and $v0,$v0,$v1 */
	.word	0x004A1024  /* 00251538 and $v0,$v0,$t2 */
	.word	0x1440FFB2  /* 0025153C bnez $v0,.L00251408 */
	.word	0x24E70008  /* 00251540 addiu $a3,$a3,8 */
	.word	0x2CC20008  /* 00251544 sltiu $v0,$a2,8 */
	.word	0x14400005  /* 00251548 bnez $v0,.L00251560 */
	.word	0x25080008  /* 0025154C addiu $t0,$t0,8 */
	.word	0xDCE30000  /* 00251550 ld $v1,0($a3) */
	.word	0xDD020000  /* 00251554 ld $v0,0($t0) */
	.word	0x5062FFF1  /* 00251558 beql $v1,$v0,.L00251520 */
	.word	0x24C6FFF8  /* 0025155C addiu $a2,$a2,-8 */
	.word	0x00E0202D  /* 00251560 move $a0,$a3 */
	.word	0x0100282D  /* 00251564 move $a1,$t0 */
	.word	0x00C0102D  /* 00251568 move $v0,$a2 */
	.word	0x1040000E  /* 0025156C beqz $v0,.L002515A8 */
	.word	0x24C6FFFF  /* 00251570 addiu $a2,$a2,-1 */
	.word	0x10000009  /* 00251574 b .L0025159C */
	.word	0x80830000  /* 00251578 lb $v1,0($a0) */
	.word	0x00000000  /* 0025157C nop */
	.word	0x10C0FFA1  /* 00251580 beqz $a2,.L00251408 */
	.word	0x00000000  /* 00251584 nop */
	.word	0x10E0FF9F  /* 00251588 beqz $a3,.L00251408 */
	.word	0x24840001  /* 0025158C addiu $a0,$a0,1 */
	.word	0x24A50001  /* 00251590 addiu $a1,$a1,1 */
	.word	0x80830000  /* 00251594 lb $v1,0($a0) */
	.word	0x24C6FFFF  /* 00251598 addiu $a2,$a2,-1 */
	.word	0x80A20000  /* 0025159C lb $v0,0($a1) */
	.word	0x1062FFF7  /* 002515A0 beq $v1,$v0,.L00251580 */
	.word	0x90870000  /* 002515A4 lbu $a3,0($a0) */
	.word	0x90A20000  /* 002515A8 lbu $v0,0($a1) */
	.word	0x90830000  /* 002515AC lbu $v1,0($a0) */
	.word	0x03E00008  /* 002515B0 jr $ra */
	.word	0x00621023  /* 002515B4 subu $v0,$v1,$v0 */
	.end	strncmp

	.section	.text.memchr,"ax",@progbits
	.globl	memchr
	.ent	memchr
memchr:  /* 0x0025632C */
	.word	0x2CC20010  /* 0025632C sltiu $v0,$a2,16 */
	.word	0x14400026  /* 00256330 bnez $v0,.L002563CC */
	.word	0x30A500FF  /* 00256334 andi $a1,$a1,0xff */
	.word	0x3082000F  /* 00256338 andi $v0,$a0,0xf */
	.word	0x14400023  /* 0025633C bnez $v0,.L002563CC */
	.word	0x0080382D  /* 00256340 move $a3,$a0 */
	.word	0x00051A38  /* 00256344 dsll $v1,$a1,0x8 */
	.word	0x3C020101  /* 00256348 lui $v0,0x101 */
	.word	0x34420101  /* 0025634C ori $v0,$v0,0x101 */
	.word	0x00021438  /* 00256350 dsll $v0,$v0,0x10 */
	.word	0x34420101  /* 00256354 ori $v0,$v0,0x101 */
	.word	0x00021438  /* 00256358 dsll $v0,$v0,0x10 */
	.word	0x34420101  /* 0025635C ori $v0,$v0,0x101 */
	.word	0x0065502D  /* 00256360 daddu $t2,$v1,$a1 */
	.word	0x3C038080  /* 00256364 lui $v1,0x8080 */
	.word	0x34638080  /* 00256368 ori $v1,$v1,0x8080 */
	.word	0x00031C38  /* 0025636C dsll $v1,$v1,0x10 */
	.word	0x34638080  /* 00256370 ori $v1,$v1,0x8080 */
	.word	0x00031C38  /* 00256374 dsll $v1,$v1,0x10 */
	.word	0x34638080  /* 00256378 ori $v1,$v1,0x8080 */
	.word	0x700A46E9  /* 0025637C pcpyh $t0,$t2 */
	.word	0x71084B89  /* 00256380 pcpyld $t1,$t0,$t0 */
	.word	0x0040202D  /* 00256384 move $a0,$v0 */
	.word	0x70634389  /* 00256388 pcpyld $t0,$v1,$v1 */
	.word	0x78E20000  /* 0025638C lq $v0,0($a3) */
	.word	0x704914C9  /* 00256390 pxor $v0,$v0,$t1 */
	.word	0x70845389  /* 00256394 pcpyld $t2,$a0,$a0 */
	.word	0x70021CE9  /* 00256398 pnor $v1,$zero,$v0 */
	.word	0x704A1248  /* 0025639C psubb $v0,$v0,$t2 */
	.word	0x70431489  /* 002563A0 pand $v0,$v0,$v1 */
	.word	0x70481489  /* 002563A4 pand $v0,$v0,$t0 */
	.word	0x70491BA9  /* 002563A8 pcpyud $v1,$v0,$t1 */
	.word	0x00431025  /* 002563AC or $v0,$v0,$v1 */
	.word	0x54400006  /* 002563B0 bnezl $v0,.L002563CC */
	.word	0x00E0202D  /* 002563B4 move $a0,$a3 */
	.word	0x24C6FFF0  /* 002563B8 addiu $a2,$a2,-16 */
	.word	0x2CC20010  /* 002563BC sltiu $v0,$a2,16 */
	.word	0x1040FFF2  /* 002563C0 beqz $v0,.L0025638C */
	.word	0x24E70010  /* 002563C4 addiu $a3,$a3,16 */
	.word	0x00E0202D  /* 002563C8 move $a0,$a3 */
	.word	0x3C02FFFF  /* 002563CC lui $v0,0xffff */
	.word	0x24C6FFFF  /* 002563D0 addiu $a2,$a2,-1 */
	.word	0x3442FFFF  /* 002563D4 ori $v0,$v0,0xffff */
	.word	0x10C20008  /* 002563D8 beq $a2,$v0,.L002563FC */
	.word	0x00000000  /* 002563DC nop */
	.word	0x3C03FFFF  /* 002563E0 lui $v1,0xffff */
	.word	0x3463FFFF  /* 002563E4 ori $v1,$v1,0xffff */
	.word	0x90820000  /* 002563E8 lbu $v0,0($a0) */
	.word	0x10450005  /* 002563EC beq $v0,$a1,.L00256404 */
	.word	0x24C6FFFF  /* 002563F0 addiu $a2,$a2,-1 */
	.word	0x14C3FFFC  /* 002563F4 bne $a2,$v1,.L002563E8 */
	.word	0x24840001  /* 002563F8 addiu $a0,$a0,1 */
	.word	0x03E00008  /* 002563FC jr $ra */
	.word	0x0000102D  /* 00256400 move $v0,$zero */
	.word	0x03E00008  /* 00256404 jr $ra */
	.word	0x0080102D  /* 00256408 move $v0,$a0 */
	.end	memchr

	.section	.text.memmove,"ax",@progbits
	.globl	memmove
	.ent	memmove
memmove:  /* 0x0025640C */
	.word	0x0080402D  /* 0025640C move $t0,$a0 */
	.word	0x00A8102B  /* 00256410 sltu $v0,$a1,$t0 */
	.word	0x10400013  /* 00256414 beqz $v0,.L00256464 */
	.word	0x0100182D  /* 00256418 move $v1,$t0 */
	.word	0x00A63821  /* 0025641C addu $a3,$a1,$a2 */
	.word	0x0107102B  /* 00256420 sltu $v0,$t0,$a3 */
	.word	0x1040000F  /* 00256424 beqz $v0,.L00256464 */
	.word	0x2402FFFF  /* 00256428 li $v0,-1 */
	.word	0x01061821  /* 0025642C addu $v1,$t0,$a2 */
	.word	0x24C6FFFF  /* 00256430 addiu $a2,$a2,-1 */
	.word	0x10C20034  /* 00256434 beq $a2,$v0,.L00256508 */
	.word	0x00E0282D  /* 00256438 move $a1,$a3 */
	.word	0x0040202D  /* 0025643C move $a0,$v0 */
	.word	0x24A5FFFF  /* 00256440 addiu $a1,$a1,-1 */
	.word	0x2463FFFF  /* 00256444 addiu $v1,$v1,-1 */
	.word	0x90A20000  /* 00256448 lbu $v0,0($a1) */
	.word	0x24C6FFFF  /* 0025644C addiu $a2,$a2,-1 */
	.word	0xA0620000  /* 00256450 sb $v0,0($v1) */
	.word	0x14C4FFFA  /* 00256454 bne $a2,$a0,.L00256440 */
	.word	0x00000000  /* 00256458 nop */
	.word	0x03E00008  /* 0025645C jr $ra */
	.word	0x0100102D  /* 00256460 move $v0,$t0 */
	.word	0x2CC20020  /* 00256464 sltiu $v0,$a2,32 */
	.word	0x5440001D  /* 00256468 bnezl $v0,.L002564E0 */
	.word	0x24C6FFFF  /* 0025646C addiu $a2,$a2,-1 */
	.word	0x00A31025  /* 00256470 or $v0,$a1,$v1 */
	.word	0x3042000F  /* 00256474 andi $v0,$v0,0xf */
	.word	0x54400019  /* 00256478 bnezl $v0,.L002564E0 */
	.word	0x24C6FFFF  /* 0025647C addiu $a2,$a2,-1 */
	.word	0x0060382D  /* 00256480 move $a3,$v1 */
	.word	0x78A30000  /* 00256484 lq $v1,0($a1) */
	.word	0x24C6FFE0  /* 00256488 addiu $a2,$a2,-32 */
	.word	0x24A50010  /* 0025648C addiu $a1,$a1,16 */
	.word	0x2CC40020  /* 00256490 sltiu $a0,$a2,32 */
	.word	0x7CE30000  /* 00256494 sq $v1,0($a3) */
	.word	0x24E70010  /* 00256498 addiu $a3,$a3,16 */
	.word	0x78A20000  /* 0025649C lq $v0,0($a1) */
	.word	0x24A50010  /* 002564A0 addiu $a1,$a1,16 */
	.word	0x7CE20000  /* 002564A4 sq $v0,0($a3) */
	.word	0x1080FFF6  /* 002564A8 beqz $a0,.L00256484 */
	.word	0x24E70010  /* 002564AC addiu $a3,$a3,16 */
	.word	0x2CC20008  /* 002564B0 sltiu $v0,$a2,8 */
	.word	0x14400009  /* 002564B4 bnez $v0,.L002564DC */
	.word	0x00E0182D  /* 002564B8 move $v1,$a3 */
	.word	0xDCA30000  /* 002564BC ld $v1,0($a1) */
	.word	0x24C6FFF8  /* 002564C0 addiu $a2,$a2,-8 */
	.word	0x24A50008  /* 002564C4 addiu $a1,$a1,8 */
	.word	0x2CC20008  /* 002564C8 sltiu $v0,$a2,8 */
	.word	0xFCE30000  /* 002564CC sd $v1,0($a3) */
	.word	0x1040FFFA  /* 002564D0 beqz $v0,.L002564BC */
	.word	0x24E70008  /* 002564D4 addiu $a3,$a3,8 */
	.word	0x00E0182D  /* 002564D8 move $v1,$a3 */
	.word	0x24C6FFFF  /* 002564DC addiu $a2,$a2,-1 */
	.word	0x2402FFFF  /* 002564E0 li $v0,-1 */
	.word	0x10C20008  /* 002564E4 beq $a2,$v0,.L00256508 */
	.word	0x0040202D  /* 002564E8 move $a0,$v0 */
	.word	0x90A20000  /* 002564EC lbu $v0,0($a1) */
	.word	0x24C6FFFF  /* 002564F0 addiu $a2,$a2,-1 */
	.word	0x24A50001  /* 002564F4 addiu $a1,$a1,1 */
	.word	0xA0620000  /* 002564F8 sb $v0,0($v1) */
	.word	0x24630001  /* 002564FC addiu $v1,$v1,1 */
	.word	0x14C4FFFA  /* 00256500 bne $a2,$a0,.L002564EC */
	.word	0x00000000  /* 00256504 nop */
	.word	0x03E00008  /* 00256508 jr $ra */
	.word	0x0100102D  /* 0025650C move $v0,$t0 */
	.end	memmove
