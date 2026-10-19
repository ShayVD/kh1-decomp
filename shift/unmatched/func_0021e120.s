/* func_0021e120: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */
	.set	noreorder
	.set	noat

	.section	.text.func_0021e120,"ax",@progbits
	.globl	func_0021e120
	.ent	func_0021e120
func_0021e120:  /* 0x0021E120 */
	.word	0x3C020000  /* 0021E120 lui $v0,%hi(D_0064324C) */
	.reloc	.-4, R_MIPS_HI16, D_0064324C
	.word	0x27BDFFB0  /* 0021E124 addiu $sp,$sp,-80 */
	.word	0x8C490000  /* 0021E128 lw $t1,%lo(D_0064324C)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_0064324C
	.word	0x24080040  /* 0021E12C li $t0,64 */
	.word	0xFFB00010  /* 0021E130 sd $s0,16($sp) */
	.word	0x00E0802D  /* 0021E134 move $s0,$a3 */
	.word	0x00094900  /* 0021E138 sll $t1,$t1,0x4 */
	.word	0x24070040  /* 0021E13C li $a3,64 */
	.word	0x3C010000  /* 0021E140 lui $at,%hi(D_003F5E00) */
	.reloc	.-4, R_MIPS_HI16, D_003F5E00
	.word	0x24210000  /* 0021E144 addiu $at,$at,%lo(D_003F5E00) */
	.reloc	.-4, R_MIPS_LO16, D_003F5E00
	.word	0x00294821  /* 0021E148 addu $t1,$at,$t1 */
	.word	0xFFB10018  /* 0021E14C sd $s1,24($sp) */
	.word	0xFFB20020  /* 0021E150 sd $s2,32($sp) */
	.word	0x3C120000  /* 0021E154 lui $s2,%hi(D_00643290) */
	.reloc	.-4, R_MIPS_HI16, D_00643290
	.word	0xFFB30028  /* 0021E158 sd $s3,40($sp) */
	.word	0x00C0982D  /* 0021E15C move $s3,$a2 */
	.word	0xFFB40030  /* 0021E160 sd $s4,48($sp) */
	.word	0x00A0A02D  /* 0021E164 move $s4,$a1 */
	.word	0xFFB50038  /* 0021E168 sd $s5,56($sp) */
	.word	0x0080A82D  /* 0021E16C move $s5,$a0 */
	.word	0xFFB60040  /* 0021E170 sd $s6,64($sp) */
	.word	0xFFBF0048  /* 0021E174 sd $ra,72($sp) */
	.word	0x0C000000  /* 0021E178 jal func_00205618 */
	.reloc	.-4, R_MIPS_26, func_00205618
	.word	0x26520000  /* 0021E17C addiu $s2,$s2,%lo(D_00643290) */
	.reloc	.-4, R_MIPS_LO16, D_00643290
	.word	0x3C030000  /* 0021E180 lui $v1,%hi(D_003F5028) */
	.reloc	.-4, R_MIPS_HI16, D_003F5028
	.word	0x00701821  /* 0021E184 addu $v1,$v1,$s0 */
	.word	0x90630000  /* 0021E188 lbu $v1,%lo(D_003F5028)($v1) */
	.reloc	.-4, R_MIPS_LO16, D_003F5028
	.word	0x3C020000  /* 0021E18C lui $v0,%hi(D_003F3510) */
	.reloc	.-4, R_MIPS_HI16, D_003F3510
	.word	0x8C500000  /* 0021E190 lw $s0,%lo(D_003F3510)($v0) */
	.reloc	.-4, R_MIPS_LO16, D_003F3510
	.word	0x24043600  /* 0021E194 li $a0,13824 */
	.word	0x00031080  /* 0021E198 sll $v0,$v1,0x2 */
	.word	0x24050002  /* 0021E19C li $a1,2 */
	.word	0x00431021  /* 0021E1A0 addu $v0,$v0,$v1 */
	.word	0x24060013  /* 0021E1A4 li $a2,19 */
	.word	0x00021280  /* 0021E1A8 sll $v0,$v0,0xa */
	.word	0x0000382D  /* 0021E1AC move $a3,$zero */
	.word	0x02028021  /* 0021E1B0 addu $s0,$s0,$v0 */
	.word	0x0000402D  /* 0021E1B4 move $t0,$zero */
	.word	0x24090040  /* 0021E1B8 li $t1,64 */
	.word	0x240A0040  /* 0021E1BC li $t2,64 */
	.word	0x240B0100  /* 0021E1C0 li $t3,256 */
	.word	0x3C110000  /* 0021E1C4 lui $s1,%hi(D_00643340) */
	.reloc	.-4, R_MIPS_HI16, D_00643340
	.word	0xAFB00000  /* 0021E1C8 sw $s0,0($sp) */
	.word	0x26101000  /* 0021E1CC addiu $s0,$s0,4096 */
	.word	0x0C000000  /* 0021E1D0 jal func_0011fbb0 */
	.reloc	.-4, R_MIPS_26, func_0011fbb0
	.word	0xAFB20008  /* 0021E1D4 sw $s2,8($sp) */
	.word	0x26310000  /* 0021E1D8 addiu $s1,$s1,%lo(D_00643340) */
	.reloc	.-4, R_MIPS_LO16, D_00643340
	.word	0x0000302D  /* 0021E1DC move $a2,$zero */
	.word	0x0000382D  /* 0021E1E0 move $a3,$zero */
	.word	0x0000402D  /* 0021E1E4 move $t0,$zero */
	.word	0x24090010  /* 0021E1E8 li $t1,16 */
	.word	0x240A0010  /* 0021E1EC li $t2,16 */
	.word	0x240B0040  /* 0021E1F0 li $t3,64 */
	.word	0x24050001  /* 0021E1F4 li $a1,1 */
	.word	0x24043680  /* 0021E1F8 li $a0,13952 */
	.word	0xAFB00000  /* 0021E1FC sw $s0,0($sp) */
	.word	0x0C000000  /* 0021E200 jal func_0011fbb0 */
	.reloc	.-4, R_MIPS_26, func_0011fbb0
	.word	0xAFB10008  /* 0021E204 sw $s1,8($sp) */
	.word	0x3C10000E  /* 0021E208 lui $s0,0xe */
	.word	0x3610EEEE  /* 0021E20C ori $s0,$s0,0xeeee */
	.word	0x0C000000  /* 0021E210 jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0x24040002  /* 0021E214 li $a0,2 */
	.word	0x0240282D  /* 0021E218 move $a1,$s2 */
	.word	0x0040202D  /* 0021E21C move $a0,$v0 */
	.word	0x0C000000  /* 0021E220 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x0014A100  /* 0021E224 sll $s4,$s4,0x4 */
	.word	0x0C000000  /* 0021E228 jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0x24040002  /* 0021E22C li $a0,2 */
	.word	0x0220282D  /* 0021E230 move $a1,$s1 */
	.word	0x0040202D  /* 0021E234 move $a0,$v0 */
	.word	0x0C000000  /* 0021E238 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x00139900  /* 0021E23C sll $s3,$s3,0x4 */
	.word	0x24040400  /* 0021E240 li $a0,1024 */
	.word	0x0C000000  /* 0021E244 jal func_00122048 */
	.reloc	.-4, R_MIPS_26, func_00122048
	.word	0x24050080  /* 0021E248 li $a1,128 */
	.word	0x3C030FFF  /* 0021E24C lui $v1,0xfff */
	.word	0x0040902D  /* 0021E250 move $s2,$v0 */
	.word	0x240204E3  /* 0021E254 li $v0,1251 */
	.word	0x26510010  /* 0021E258 addiu $s1,$s2,16 */
	.word	0x3C095000  /* 0021E25C lui $t1,0x5000 */
	.word	0x0009483C  /* 0021E260 dsll32 $t1,$t1,0x0 */
	.word	0x35298001  /* 0021E264 ori $t1,$t1,0x8001 */
	.word	0x2406003F  /* 0021E268 li $a2,63 */
	.word	0x3C072006  /* 0021E26C lui $a3,0x2006 */
	.word	0x34E7D005  /* 0021E270 ori $a3,$a3,0xd005 */
	.word	0x00073C38  /* 0021E274 dsll $a3,$a3,0x10 */
	.word	0x34E79D30  /* 0021E278 ori $a3,$a3,0x9d30 */
	.word	0x00073C38  /* 0021E27C dsll $a3,$a3,0x10 */
	.word	0x34E7B600  /* 0021E280 ori $a3,$a3,0xb600 */
	.word	0x240A0061  /* 0021E284 li $t2,97 */
	.word	0x24040044  /* 0021E288 li $a0,68 */
	.word	0x24080042  /* 0021E28C li $t0,66 */
	.word	0x3C0B0004  /* 0021E290 lui $t3,0x4 */
	.word	0x356B000D  /* 0021E294 ori $t3,$t3,0xd */
	.word	0x240D0047  /* 0021E298 li $t5,71 */
	.word	0x240F0006  /* 0021E29C li $t7,6 */
	.word	0x240C0014  /* 0021E2A0 li $t4,20 */
	.word	0x3C0E30AE  /* 0021E2A4 lui $t6,0x30ae */
	.word	0x35CE4000  /* 0021E2A8 ori $t6,$t6,0x4000 */
	.word	0x000E703C  /* 0021E2AC dsll32 $t6,$t6,0x0 */
	.word	0x35CE8004  /* 0021E2B0 ori $t6,$t6,0x8004 */
	.word	0xFE290000  /* 0021E2B4 sd $t1,0($s1) */
	.word	0x240903F8  /* 0021E2B8 li $t1,1016 */
	.word	0xFE260028  /* 0021E2BC sd $a2,40($s1) */
	.word	0x24060008  /* 0021E2C0 li $a2,8 */
	.word	0xFE270030  /* 0021E2C4 sd $a3,48($s1) */
	.word	0x24070001  /* 0021E2C8 li $a3,1 */
	.word	0xFE280058  /* 0021E2CC sd $t0,88($s1) */
	.word	0x3C080010  /* 0021E2D0 lui $t0,0x10 */
	.word	0xFE240050  /* 0021E2D4 sd $a0,80($s1) */
	.word	0x3463FFFF  /* 0021E2D8 ori $v1,$v1,0xffff */
	.word	0xFE2A0040  /* 0021E2DC sd $t2,64($s1) */
	.word	0x02431824  /* 0021E2E0 and $v1,$s2,$v1 */
	.word	0xFE200020  /* 0021E2E4 sd $zero,32($s1) */
	.word	0x3C050080  /* 0021E2E8 lui $a1,0x80 */
	.word	0xFE220068  /* 0021E2EC sd $v0,104($s1) */
	.word	0x3C028000  /* 0021E2F0 lui $v0,0x8000 */
	.word	0xFE2B0010  /* 0021E2F4 sd $t3,16($s1) */
	.word	0x0062B025  /* 0021E2F8 or $s6,$v1,$v0 */
	.word	0xFE2D0018  /* 0021E2FC sd $t5,24($s1) */
	.word	0x34A58080  /* 0021E300 ori $a1,$a1,0x8080 */
	.word	0xFE2C0048  /* 0021E304 sd $t4,72($s1) */
	.word	0xFE300008  /* 0021E308 sd $s0,8($s1) */
	.word	0xFE2F0038  /* 0021E30C sd $t7,56($s1) */
	.word	0xFE2E0060  /* 0021E310 sd $t6,96($s1) */
	.word	0x26510080  /* 0021E314 addiu $s1,$s2,128 */
	.word	0x8EA20090  /* 0021E318 lw $v0,144($s5) */
	.word	0x8EA400B0  /* 0021E31C lw $a0,176($s5) */
	.word	0x8EA300B4  /* 0021E320 lw $v1,180($s5) */
	.word	0x00021600  /* 0021E324 sll $v0,$v0,0x18 */
	.word	0x00451025  /* 0021E328 or $v0,$v0,$a1 */
	.word	0x00942021  /* 0021E32C addu $a0,$a0,$s4 */
	.word	0x00731821  /* 0021E330 addu $v1,$v1,$s3 */
	.word	0x0002103C  /* 0021E334 dsll32 $v0,$v0,0x0 */
	.word	0x0002103E  /* 0021E338 dsrl32 $v0,$v0,0x0 */
	.word	0x246A0400  /* 0021E33C addiu $t2,$v1,1024 */
	.word	0x24850400  /* 0021E340 addiu $a1,$a0,1024 */
	.word	0xFE220010  /* 0021E344 sd $v0,16($s1) */
	.word	0xFE220040  /* 0021E348 sd $v0,64($s1) */
	.word	0xAE260000  /* 0021E34C sw $a2,0($s1) */
	.word	0xAE260004  /* 0021E350 sw $a2,4($s1) */
	.word	0xFE270018  /* 0021E354 sd $a3,24($s1) */
	.word	0xAE240020  /* 0021E358 sw $a0,32($s1) */
	.word	0xAE230024  /* 0021E35C sw $v1,36($s1) */
	.word	0xAE280028  /* 0021E360 sw $t0,40($s1) */
	.word	0xAE20002C  /* 0021E364 sw $zero,44($s1) */
	.word	0xAE290030  /* 0021E368 sw $t1,48($s1) */
	.word	0xAE260034  /* 0021E36C sw $a2,52($s1) */
	.word	0xFE270048  /* 0021E370 sd $a3,72($s1) */
	.word	0xAE250050  /* 0021E374 sw $a1,80($s1) */
	.word	0xAE230054  /* 0021E378 sw $v1,84($s1) */
	.word	0xAE280058  /* 0021E37C sw $t0,88($s1) */
	.word	0xAE20005C  /* 0021E380 sw $zero,92($s1) */
	.word	0xAE260060  /* 0021E384 sw $a2,96($s1) */
	.word	0xAE240080  /* 0021E388 sw $a0,128($s1) */
	.word	0xAE290094  /* 0021E38C sw $t1,148($s1) */
	.word	0xFE2200A0  /* 0021E390 sd $v0,160($s1) */
	.word	0xFE2700A8  /* 0021E394 sd $a3,168($s1) */
	.word	0xAE2500B0  /* 0021E398 sw $a1,176($s1) */
	.word	0xAE2A00B4  /* 0021E39C sw $t2,180($s1) */
	.word	0xAE2800B8  /* 0021E3A0 sw $t0,184($s1) */
	.word	0xAE290064  /* 0021E3A4 sw $t1,100($s1) */
	.word	0xFE220070  /* 0021E3A8 sd $v0,112($s1) */
	.word	0xFE270078  /* 0021E3AC sd $a3,120($s1) */
	.word	0xAE2A0084  /* 0021E3B0 sw $t2,132($s1) */
	.word	0xAE280088  /* 0021E3B4 sw $t0,136($s1) */
	.word	0xAE20008C  /* 0021E3B8 sw $zero,140($s1) */
	.word	0xAE290090  /* 0021E3BC sw $t1,144($s1) */
	.word	0xAE2000BC  /* 0021E3C0 sw $zero,188($s1) */
	.word	0x8EA20048  /* 0021E3C4 lw $v0,72($s5) */
	.word	0x30420001  /* 0021E3C8 andi $v0,$v0,0x1 */
	.word	0x50400035  /* 0021E3CC beqzl $v0,.L0021E4A4 */
	.word	0x02321023  /* 0021E3D0 subu $v0,$s1,$s2 */
	.word	0x0C000000  /* 0021E3D4 jal func_001f4570 */
	.reloc	.-4, R_MIPS_26, func_001f4570
	.word	0x02A0202D  /* 0021E3D8 move $a0,$s5 */
	.word	0x02A0202D  /* 0021E3DC move $a0,$s5 */
	.word	0x0C000000  /* 0021E3E0 jal func_001f45e0 */
	.reloc	.-4, R_MIPS_26, func_001f45e0
	.word	0x0040802D  /* 0021E3E4 move $s0,$v0 */
	.word	0x8E250020  /* 0021E3E8 lw $a1,32($s1) */
	.word	0x44822800  /* 0021E3EC mtc1 $v0,$f5 */
	.word	0x46802960  /* 0021E3F0 cvt.s.w $f5,$f5 */
	.word	0x8E260024  /* 0021E3F4 lw $a2,36($s1) */
	.word	0x44903000  /* 0021E3F8 mtc1 $s0,$f6 */
	.word	0x468031A0  /* 0021E3FC cvt.s.w $f6,$f6 */
	.word	0x8E230050  /* 0021E400 lw $v1,80($s1) */
	.word	0x00B02823  /* 0021E404 subu $a1,$a1,$s0 */
	.word	0x8E240084  /* 0021E408 lw $a0,132($s1) */
	.word	0x00C23023  /* 0021E40C subu $a2,$a2,$v0 */
	.word	0x00701823  /* 0021E410 subu $v1,$v1,$s0 */
	.word	0x44851800  /* 0021E414 mtc1 $a1,$f3 */
	.word	0x468018E0  /* 0021E418 cvt.s.w $f3,$f3 */
	.word	0x00822023  /* 0021E41C subu $a0,$a0,$v0 */
	.word	0x44831000  /* 0021E420 mtc1 $v1,$f2 */
	.word	0x468010A0  /* 0021E424 cvt.s.w $f2,$f2 */
	.word	0x44840000  /* 0021E428 mtc1 $a0,$f0 */
	.word	0x46800020  /* 0021E42C cvt.s.w $f0,$f0 */
	.word	0xC6A70074  /* 0021E430 lwc1 $f7,116($s5) */
	.word	0x44860800  /* 0021E434 mtc1 $a2,$f1 */
	.word	0x46800860  /* 0021E438 cvt.s.w $f1,$f1 */
	.word	0xC6A40078  /* 0021E43C lwc1 $f4,120($s5) */
	.word	0x460718C2  /* 0021E440 mul.s $f3,$f3,$f7 */
	.word	0x46071082  /* 0021E444 mul.s $f2,$f2,$f7 */
	.word	0x46040002  /* 0021E448 mul.s $f0,$f0,$f4 */
	.word	0x46040842  /* 0021E44C mul.s $f1,$f1,$f4 */
	.word	0x460330C0  /* 0021E450 add.s $f3,$f6,$f3 */
	.word	0x46023180  /* 0021E454 add.s $f6,$f6,$f2 */
	.word	0x46012840  /* 0021E458 add.s $f1,$f5,$f1 */
	.word	0x46002940  /* 0021E45C add.s $f5,$f5,$f0 */
	.word	0x46001824  /* 0021E460 trunc.w.s $f0,$f3 */
	.word	0x44020000  /* 0021E464 mfc1 $v0,$f0 */
	.word	0x46000824  /* 0021E468 trunc.w.s $f0,$f1 */
	.word	0x44030000  /* 0021E46C mfc1 $v1,$f0 */
	.word	0x46003024  /* 0021E470 trunc.w.s $f0,$f6 */
	.word	0x44040000  /* 0021E474 mfc1 $a0,$f0 */
	.word	0x46002824  /* 0021E478 trunc.w.s $f0,$f5 */
	.word	0x44050000  /* 0021E47C mfc1 $a1,$f0 */
	.word	0xAE220080  /* 0021E480 sw $v0,128($s1) */
	.word	0xAE220020  /* 0021E484 sw $v0,32($s1) */
	.word	0xAE230054  /* 0021E488 sw $v1,84($s1) */
	.word	0xAE2400B0  /* 0021E48C sw $a0,176($s1) */
	.word	0xAE2500B4  /* 0021E490 sw $a1,180($s1) */
	.word	0xAE230024  /* 0021E494 sw $v1,36($s1) */
	.word	0xAE240050  /* 0021E498 sw $a0,80($s1) */
	.word	0xAE250084  /* 0021E49C sw $a1,132($s1) */
	.word	0x02321023  /* 0021E4A0 subu $v0,$s1,$s2 */
	.word	0x3C037000  /* 0021E4A4 lui $v1,0x7000 */
	.word	0x244200C0  /* 0021E4A8 addiu $v0,$v0,192 */
	.word	0x24040002  /* 0021E4AC li $a0,2 */
	.word	0x00021103  /* 0021E4B0 sra $v0,$v0,0x4 */
	.word	0x2442FFFF  /* 0021E4B4 addiu $v0,$v0,-1 */
	.word	0x00431825  /* 0021E4B8 or $v1,$v0,$v1 */
	.word	0x0C000000  /* 0021E4BC jal func_00266c08 */
	.reloc	.-4, R_MIPS_26, func_00266c08
	.word	0xFE430000  /* 0021E4C0 sd $v1,0($s2) */
	.word	0x02C0282D  /* 0021E4C4 move $a1,$s6 */
	.word	0x0C000000  /* 0021E4C8 jal func_00266f38 */
	.reloc	.-4, R_MIPS_26, func_00266f38
	.word	0x0040202D  /* 0021E4CC move $a0,$v0 */
	.word	0x0000202D  /* 0021E4D0 move $a0,$zero */
	.word	0x0C000000  /* 0021E4D4 jal sceGsSyncPath */
	.reloc	.-4, R_MIPS_26, sceGsSyncPath
	.word	0x0000282D  /* 0021E4D8 move $a1,$zero */
	.word	0x0240202D  /* 0021E4DC move $a0,$s2 */
	.word	0xDFB00010  /* 0021E4E0 ld $s0,16($sp) */
	.word	0xDFB10018  /* 0021E4E4 ld $s1,24($sp) */
	.word	0xDFB20020  /* 0021E4E8 ld $s2,32($sp) */
	.word	0xDFB30028  /* 0021E4EC ld $s3,40($sp) */
	.word	0xDFB40030  /* 0021E4F0 ld $s4,48($sp) */
	.word	0xDFB50038  /* 0021E4F4 ld $s5,56($sp) */
	.word	0xDFB60040  /* 0021E4F8 ld $s6,64($sp) */
	.word	0xDFBF0048  /* 0021E4FC ld $ra,72($sp) */
	.word	0x08000000  /* 0021E500 j func_001220b8 */
	.reloc	.-4, R_MIPS_26, func_001220b8
	.word	0x27BD0050  /* 0021E504 addiu $sp,$sp,80 */
	.end	func_0021e120
