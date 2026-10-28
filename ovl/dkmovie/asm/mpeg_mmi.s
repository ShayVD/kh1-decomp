/* dkmovie.x: hand-written MMI routines of the movie player (motion compensation with qfsrv/paddsh/ppacb, sq block clears and copies). Not C: daddiu/daddu idioms, nop padding in loops. Session 141. */
	.set	noreorder
	.set	noat

	.section	.text.func_00f203a4,"ax",@progbits
	.globl	func_00f203a4
	.ent	func_00f203a4
func_00f203a4:  /* 0x00F203A4 */
	.word	0x788B0050  /* 00F203A4 lq $t3,80($a0) */
	.word	0x640E0010  /* 00F203A8 daddiu $t6,$zero,16 */
	.word	0x640F0008  /* 00F203AC daddiu $t7,$zero,8 */
	.word	0x8C8C0060  /* 00F203B0 lw $t4,96($a0) */
	.word	0x8C8D0064  /* 00F203B4 lw $t5,100($a0) */
	.word	0x8C980000  /* 00F203B8 lw $t8,0($a0) */
	.word	0x8C990004  /* 00F203BC lw $t9,4($a0) */
	.word	0x8C860010  /* 00F203C0 lw $a2,16($a0) */
	.word	0x8C870014  /* 00F203C4 lw $a3,20($a0) */
	.word	0x30C90008  /* 00F203C8 andi $t1,$a2,0x8 */
	.word	0x30C60007  /* 00F203CC andi $a2,$a2,0x7 */
	.word	0x04D90000  /* 00F203D0 mtsah $a2,0 */
	.word	0x01C7282F  /* 00F203D4 dsubu $a1,$t6,$a3 */
	.word	0x00074178  /* 00F203D8 dsll $t0,$a3,0x5 */
	.word	0x0308C02D  /* 00F203DC daddu $t8,$t8,$t0 */
	.word	0x0328C82D  /* 00F203E0 daddu $t9,$t9,$t0 */
	.word	0x640A0000  /* 00F203E4 daddiu $t2,$zero,0 */
	.word	0x15200005  /* 00F203E8 bnez $t1,.L00F20400 */
	.word	0x799B0000  /* 00F203EC lq $k1,0($t4) */
	.word	0x7B060000  /* 00F203F0 lq $a2,0($t8) */
	.word	0x7B070010  /* 00F203F4 lq $a3,16($t8) */
	.word	0x08000000  /* 00F203F8 j .L00F2040C */
	.reloc	.-4, R_MIPS_26, func_00f203a4+0x68
	.word	0x7B280000  /* 00F203FC lq $t0,0($t9) */
	.word	0x7B060010  /* 00F20400 lq $a2,16($t8) */
	.word	0x7B270000  /* 00F20404 lq $a3,0($t9) */
	.word	0x7B280010  /* 00F20408 lq $t0,16($t9) */
	.word	0x70E616E8  /* 00F2040C qfsrv $v0,$a3,$a2 */
	.word	0x71071EE8  /* 00F20410 qfsrv $v1,$t0,$a3 */
	.word	0x79870010  /* 00F20414 lq $a3,16($t4) */
	.word	0x73623508  /* 00F20418 paddsh $a2,$k1,$v0 */
	.word	0x70E33D08  /* 00F2041C paddsh $a3,$a3,$v1 */
	.word	0x70CB3508  /* 00F20420 paddsh $a2,$a2,$t3 */
	.word	0x70CB3568  /* 00F20424 psubuh $a2,$a2,$t3 */
	.word	0x70EB3D08  /* 00F20428 paddsh $a3,$a3,$t3 */
	.word	0x70EB3D68  /* 00F2042C psubuh $a3,$a3,$t3 */
	.word	0x70E636C8  /* 00F20430 ppacb $a2,$a3,$a2 */
	.word	0x7DA60000  /* 00F20434 sq $a2,0($t5) */
	.word	0x25AD0010  /* 00F20438 addiu $t5,$t5,16 */
	.word	0x258C0020  /* 00F2043C addiu $t4,$t4,32 */
	.word	0x27180020  /* 00F20440 addiu $t8,$t8,32 */
	.word	0x64A5FFFF  /* 00F20444 daddiu $a1,$a1,-1 */
	.word	0x14A0FFE7  /* 00F20448 bnez $a1,.L00F203E8 */
	.word	0x27390020  /* 00F2044C addiu $t9,$t9,32 */
	.word	0x15400006  /* 00F20450 bnez $t2,.L00F2046C */
	.word	0x00000000  /* 00F20454 nop */
	.word	0x640A0001  /* 00F20458 daddiu $t2,$zero,1 */
	.word	0x8C850014  /* 00F2045C lw $a1,20($a0) */
	.word	0x67180400  /* 00F20460 daddiu $t8,$t8,1024 */
	.word	0x14A0FFE0  /* 00F20464 bnez $a1,.L00F203E8 */
	.word	0x67390400  /* 00F20468 daddiu $t9,$t9,1024 */
	.word	0x8C8C0060  /* 00F2046C lw $t4,96($a0) */
	.word	0x8C8D0064  /* 00F20470 lw $t5,100($a0) */
	.word	0x8C980000  /* 00F20474 lw $t8,0($a0) */
	.word	0x8C990004  /* 00F20478 lw $t9,4($a0) */
	.word	0x8C860010  /* 00F2047C lw $a2,16($a0) */
	.word	0x8C870014  /* 00F20480 lw $a3,20($a0) */
	.word	0x0006307A  /* 00F20484 dsrl $a2,$a2,0x1 */
	.word	0x0007387A  /* 00F20488 dsrl $a3,$a3,0x1 */
	.word	0x04D90000  /* 00F2048C mtsah $a2,0 */
	.word	0x01E7282F  /* 00F20490 dsubu $a1,$t7,$a3 */
	.word	0x00074138  /* 00F20494 dsll $t0,$a3,0x4 */
	.word	0x0308C02D  /* 00F20498 daddu $t8,$t8,$t0 */
	.word	0x0328C82D  /* 00F2049C daddu $t9,$t9,$t0 */
	.word	0x640A0000  /* 00F204A0 daddiu $t2,$zero,0 */
	.word	0x7B060200  /* 00F204A4 lq $a2,512($t8) */
	.word	0x7B270200  /* 00F204A8 lq $a3,512($t9) */
	.word	0x79880200  /* 00F204AC lq $t0,512($t4) */
	.word	0x70E636E8  /* 00F204B0 qfsrv $a2,$a3,$a2 */
	.word	0x70C83508  /* 00F204B4 paddsh $a2,$a2,$t0 */
	.word	0x70CB3508  /* 00F204B8 paddsh $a2,$a2,$t3 */
	.word	0x70CB3568  /* 00F204BC psubuh $a2,$a2,$t3 */
	.word	0x70C636C8  /* 00F204C0 ppacb $a2,$a2,$a2 */
	.word	0xFDA60100  /* 00F204C4 sd $a2,256($t5) */
	.word	0x7B060280  /* 00F204C8 lq $a2,640($t8) */
	.word	0x7B270280  /* 00F204CC lq $a3,640($t9) */
	.word	0x79880280  /* 00F204D0 lq $t0,640($t4) */
	.word	0x70E636E8  /* 00F204D4 qfsrv $a2,$a3,$a2 */
	.word	0x70C83508  /* 00F204D8 paddsh $a2,$a2,$t0 */
	.word	0x70CB3508  /* 00F204DC paddsh $a2,$a2,$t3 */
	.word	0x70CB3568  /* 00F204E0 psubuh $a2,$a2,$t3 */
	.word	0x70C636C8  /* 00F204E4 ppacb $a2,$a2,$a2 */
	.word	0xFDA60140  /* 00F204E8 sd $a2,320($t5) */
	.word	0x25AD0008  /* 00F204EC addiu $t5,$t5,8 */
	.word	0x258C0010  /* 00F204F0 addiu $t4,$t4,16 */
	.word	0x27180010  /* 00F204F4 addiu $t8,$t8,16 */
	.word	0x64A5FFFF  /* 00F204F8 daddiu $a1,$a1,-1 */
	.word	0x14A0FFE9  /* 00F204FC bnez $a1,.L00F204A4 */
	.word	0x27390010  /* 00F20500 addiu $t9,$t9,16 */
	.word	0x15400007  /* 00F20504 bnez $t2,.L00F20524 */
	.word	0x00000000  /* 00F20508 nop */
	.word	0x640A0001  /* 00F2050C daddiu $t2,$zero,1 */
	.word	0x8C850014  /* 00F20510 lw $a1,20($a0) */
	.word	0x67180580  /* 00F20514 daddiu $t8,$t8,1408 */
	.word	0x0005287A  /* 00F20518 dsrl $a1,$a1,0x1 */
	.word	0x14A0FFE1  /* 00F2051C bnez $a1,.L00F204A4 */
	.word	0x67390580  /* 00F20520 daddiu $t9,$t9,1408 */
	.word	0x03E00008  /* 00F20524 jr $ra */
	.word	0x00000000  /* 00F20528 nop */
	.end	func_00f203a4

	.section	.text.func_00f2052c,"ax",@progbits
	.globl	func_00f2052c
	.ent	func_00f2052c
func_00f2052c:  /* 0x00F2052C */
	.word	0x8C8D0060  /* 00F2052C lw $t5,96($a0) */
	.word	0x8C8E0064  /* 00F20530 lw $t6,100($a0) */
	.word	0x788B0050  /* 00F20534 lq $t3,80($a0) */
	.word	0x64A50018  /* 00F20538 daddiu $a1,$a1,24 */
	.word	0x79A60000  /* 00F2053C lq $a2,0($t5) */
	.word	0x79A70010  /* 00F20540 lq $a3,16($t5) */
	.word	0x70CB3508  /* 00F20544 paddsh $a2,$a2,$t3 */
	.word	0x70CB3568  /* 00F20548 psubuh $a2,$a2,$t3 */
	.word	0x70C636C8  /* 00F2054C ppacb $a2,$a2,$a2 */
	.word	0x70EB3D08  /* 00F20550 paddsh $a3,$a3,$t3 */
	.word	0x79A80020  /* 00F20554 lq $t0,32($t5) */
	.word	0x79A20030  /* 00F20558 lq $v0,48($t5) */
	.word	0x70EB3D68  /* 00F2055C psubuh $a3,$a3,$t3 */
	.word	0x70E73EC8  /* 00F20560 ppacb $a3,$a3,$a3 */
	.word	0x710B4508  /* 00F20564 paddsh $t0,$t0,$t3 */
	.word	0x710B4568  /* 00F20568 psubuh $t0,$t0,$t3 */
	.word	0xFDC60000  /* 00F2056C sd $a2,0($t6) */
	.word	0xFDC70008  /* 00F20570 sd $a3,8($t6) */
	.word	0x710846C8  /* 00F20574 ppacb $t0,$t0,$t0 */
	.word	0x704B1508  /* 00F20578 paddsh $v0,$v0,$t3 */
	.word	0x704B1568  /* 00F2057C psubuh $v0,$v0,$t3 */
	.word	0x704216C8  /* 00F20580 ppacb $v0,$v0,$v0 */
	.word	0xFDC80010  /* 00F20584 sd $t0,16($t6) */
	.word	0xFDC20018  /* 00F20588 sd $v0,24($t6) */
	.word	0x64A5FFFF  /* 00F2058C daddiu $a1,$a1,-1 */
	.word	0x65CE0020  /* 00F20590 daddiu $t6,$t6,32 */
	.word	0x14A0FFE9  /* 00F20594 bnez $a1,.L00F2053C */
	.word	0x65AD0040  /* 00F20598 daddiu $t5,$t5,64 */
	.word	0x03E00008  /* 00F2059C jr $ra */
	.word	0x00000000  /* 00F205A0 nop */
	.end	func_00f2052c

	.section	.text.func_00f205a4,"ax",@progbits
	.globl	func_00f205a4
	.ent	func_00f205a4
func_00f205a4:  /* 0x00F205A4 */
	.word	0x64080020  /* 00F205A4 daddiu $t0,$zero,32 */
	.word	0x7C800000  /* 00F205A8 sq $zero,0($a0) */
	.word	0x00000000  /* 00F205AC nop */
	.word	0x00000000  /* 00F205B0 nop */
	.word	0x6508FFFF  /* 00F205B4 daddiu $t0,$t0,-1 */
	.word	0x64840010  /* 00F205B8 daddiu $a0,$a0,16 */
	.word	0x1500FFFA  /* 00F205BC bnez $t0,.L00F205A8 */
	.word	0x00000000  /* 00F205C0 nop */
	.word	0x64080020  /* 00F205C4 daddiu $t0,$zero,32 */
	.word	0x3C090080  /* 00F205C8 lui $t1,0x80 */
	.word	0x35290080  /* 00F205CC ori $t1,$t1,0x80 */
	.word	0xAC890000  /* 00F205D0 sw $t1,0($a0) */
	.word	0xAC890004  /* 00F205D4 sw $t1,4($a0) */
	.word	0x00000000  /* 00F205D8 nop */
	.word	0x6508FFFF  /* 00F205DC daddiu $t0,$t0,-1 */
	.word	0x64840008  /* 00F205E0 daddiu $a0,$a0,8 */
	.word	0x1500FFFA  /* 00F205E4 bnez $t0,.L00F205D0 */
	.word	0x00000000  /* 00F205E8 nop */
	.word	0x03E00008  /* 00F205EC jr $ra */
	.word	0x00000000  /* 00F205F0 nop */
	.end	func_00f205a4

	.section	.text.func_00f205f4,"ax",@progbits
	.globl	func_00f205f4
	.ent	func_00f205f4
func_00f205f4:  /* 0x00F205F4 */
	.word	0x64080018  /* 00F205F4 daddiu $t0,$zero,24 */
	.word	0x7C800000  /* 00F205F8 sq $zero,0($a0) */
	.word	0x7C800010  /* 00F205FC sq $zero,16($a0) */
	.word	0x00000000  /* 00F20600 nop */
	.word	0x6508FFFF  /* 00F20604 daddiu $t0,$t0,-1 */
	.word	0x64840020  /* 00F20608 daddiu $a0,$a0,32 */
	.word	0x1500FFFA  /* 00F2060C bnez $t0,.L00F205F8 */
	.word	0x00000000  /* 00F20610 nop */
	.word	0x03E00008  /* 00F20614 jr $ra */
	.word	0x00000000  /* 00F20618 nop */
	.end	func_00f205f4

	.section	.text.func_00f2061c,"ax",@progbits
	.globl	func_00f2061c
	.ent	func_00f2061c
func_00f2061c:  /* 0x00F2061C */
	.word	0x0006402D  /* 00F2061C daddu $t0,$zero,$a2 */
	.word	0x0006482D  /* 00F20620 daddu $t1,$zero,$a2 */
	.word	0x00094AB8  /* 00F20624 dsll $t1,$t1,0xa */
	.word	0x0089582D  /* 00F20628 daddu $t3,$a0,$t1 */
	.word	0x640C0008  /* 00F2062C daddiu $t4,$zero,8 */
	.word	0x78A90000  /* 00F20630 lq $t1,0($a1) */
	.word	0x78AA0010  /* 00F20634 lq $t2,16($a1) */
	.word	0x7C890000  /* 00F20638 sq $t1,0($a0) */
	.word	0x7C8A0010  /* 00F2063C sq $t2,16($a0) */
	.word	0x7C890040  /* 00F20640 sq $t1,64($a0) */
	.word	0x7C8A0050  /* 00F20644 sq $t2,80($a0) */
	.word	0x78A90020  /* 00F20648 lq $t1,32($a1) */
	.word	0x78AA0030  /* 00F2064C lq $t2,48($a1) */
	.word	0x7C890020  /* 00F20650 sq $t1,32($a0) */
	.word	0x7C8A0030  /* 00F20654 sq $t2,48($a0) */
	.word	0x7C890060  /* 00F20658 sq $t1,96($a0) */
	.word	0x7C8A0070  /* 00F2065C sq $t2,112($a0) */
	.word	0x64A50040  /* 00F20660 daddiu $a1,$a1,64 */
	.word	0x658CFFFF  /* 00F20664 daddiu $t4,$t4,-1 */
	.word	0x1580FFF1  /* 00F20668 bnez $t4,.L00F20630 */
	.word	0x64840080  /* 00F2066C daddiu $a0,$a0,128 */
	.word	0x640C0008  /* 00F20670 daddiu $t4,$zero,8 */
	.word	0x78A90000  /* 00F20674 lq $t1,0($a1) */
	.word	0x78AA0010  /* 00F20678 lq $t2,16($a1) */
	.word	0x7D690000  /* 00F2067C sq $t1,0($t3) */
	.word	0x7D6A0010  /* 00F20680 sq $t2,16($t3) */
	.word	0x7D690040  /* 00F20684 sq $t1,64($t3) */
	.word	0x7D6A0050  /* 00F20688 sq $t2,80($t3) */
	.word	0x78A90020  /* 00F2068C lq $t1,32($a1) */
	.word	0x78AA0030  /* 00F20690 lq $t2,48($a1) */
	.word	0x7D690020  /* 00F20694 sq $t1,32($t3) */
	.word	0x7D6A0030  /* 00F20698 sq $t2,48($t3) */
	.word	0x7D690060  /* 00F2069C sq $t1,96($t3) */
	.word	0x7D6A0070  /* 00F206A0 sq $t2,112($t3) */
	.word	0x64A50040  /* 00F206A4 daddiu $a1,$a1,64 */
	.word	0x658CFFFF  /* 00F206A8 daddiu $t4,$t4,-1 */
	.word	0x1580FFF1  /* 00F206AC bnez $t4,.L00F20674 */
	.word	0x656B0080  /* 00F206B0 daddiu $t3,$t3,128 */
	.word	0x6508FFFF  /* 00F206B4 daddiu $t0,$t0,-1 */
	.word	0x1500FFDC  /* 00F206B8 bnez $t0,.L00F2062C */
	.word	0x00000000  /* 00F206BC nop */
	.word	0x03E00008  /* 00F206C0 jr $ra */
	.word	0x00000000  /* 00F206C4 nop */
	.end	func_00f2061c

	.section	.text.func_00f206c8,"ax",@progbits
	.globl	func_00f206c8
	.ent	func_00f206c8
func_00f206c8:  /* 0x00F206C8 */
	.word	0x0006402D  /* 00F206C8 daddu $t0,$zero,$a2 */
	.word	0x0006482D  /* 00F206CC daddu $t1,$zero,$a2 */
	.word	0x00094AB8  /* 00F206D0 dsll $t1,$t1,0xa */
	.word	0x0089582D  /* 00F206D4 daddu $t3,$a0,$t1 */
	.word	0x640C0008  /* 00F206D8 daddiu $t4,$zero,8 */
	.word	0x78A90000  /* 00F206DC lq $t1,0($a1) */
	.word	0x78AA0010  /* 00F206E0 lq $t2,16($a1) */
	.word	0x7C890000  /* 00F206E4 sq $t1,0($a0) */
	.word	0x7C8A0010  /* 00F206E8 sq $t2,16($a0) */
	.word	0x78E90000  /* 00F206EC lq $t1,0($a3) */
	.word	0x78EA0010  /* 00F206F0 lq $t2,16($a3) */
	.word	0x7C890040  /* 00F206F4 sq $t1,64($a0) */
	.word	0x7C8A0050  /* 00F206F8 sq $t2,80($a0) */
	.word	0x78A90020  /* 00F206FC lq $t1,32($a1) */
	.word	0x78AA0030  /* 00F20700 lq $t2,48($a1) */
	.word	0x7C890020  /* 00F20704 sq $t1,32($a0) */
	.word	0x7C8A0030  /* 00F20708 sq $t2,48($a0) */
	.word	0x78E90020  /* 00F2070C lq $t1,32($a3) */
	.word	0x78EA0030  /* 00F20710 lq $t2,48($a3) */
	.word	0x7C890060  /* 00F20714 sq $t1,96($a0) */
	.word	0x7C8A0070  /* 00F20718 sq $t2,112($a0) */
	.word	0x64A50040  /* 00F2071C daddiu $a1,$a1,64 */
	.word	0x64E70040  /* 00F20720 daddiu $a3,$a3,64 */
	.word	0x658CFFFF  /* 00F20724 daddiu $t4,$t4,-1 */
	.word	0x1580FFEC  /* 00F20728 bnez $t4,.L00F206DC */
	.word	0x64840080  /* 00F2072C daddiu $a0,$a0,128 */
	.word	0x640C0008  /* 00F20730 daddiu $t4,$zero,8 */
	.word	0x78A90000  /* 00F20734 lq $t1,0($a1) */
	.word	0x78AA0010  /* 00F20738 lq $t2,16($a1) */
	.word	0x7D690000  /* 00F2073C sq $t1,0($t3) */
	.word	0x7D6A0010  /* 00F20740 sq $t2,16($t3) */
	.word	0x78E90000  /* 00F20744 lq $t1,0($a3) */
	.word	0x78EA0010  /* 00F20748 lq $t2,16($a3) */
	.word	0x7D690040  /* 00F2074C sq $t1,64($t3) */
	.word	0x7D6A0050  /* 00F20750 sq $t2,80($t3) */
	.word	0x78A90020  /* 00F20754 lq $t1,32($a1) */
	.word	0x78AA0030  /* 00F20758 lq $t2,48($a1) */
	.word	0x7D690020  /* 00F2075C sq $t1,32($t3) */
	.word	0x7D6A0030  /* 00F20760 sq $t2,48($t3) */
	.word	0x78E90020  /* 00F20764 lq $t1,32($a3) */
	.word	0x78EA0030  /* 00F20768 lq $t2,48($a3) */
	.word	0x7D690060  /* 00F2076C sq $t1,96($t3) */
	.word	0x7D6A0070  /* 00F20770 sq $t2,112($t3) */
	.word	0x64A50040  /* 00F20774 daddiu $a1,$a1,64 */
	.word	0x64E70040  /* 00F20778 daddiu $a3,$a3,64 */
	.word	0x658CFFFF  /* 00F2077C daddiu $t4,$t4,-1 */
	.word	0x1580FFEC  /* 00F20780 bnez $t4,.L00F20734 */
	.word	0x656B0080  /* 00F20784 daddiu $t3,$t3,128 */
	.word	0x6508FFFF  /* 00F20788 daddiu $t0,$t0,-1 */
	.word	0x1500FFD2  /* 00F2078C bnez $t0,.L00F206D8 */
	.word	0x00000000  /* 00F20790 nop */
	.word	0x03E00008  /* 00F20794 jr $ra */
	.word	0x00000000  /* 00F20798 nop */
	.word	0x00000000  /* 00F2079C nop */
	.end	func_00f206c8
