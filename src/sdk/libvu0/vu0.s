/* libvu0 (sdk segment): VU0 macro-mode routines. The originals were assembly / whole-function inline asm (no frames, ra kept in a2 around inner jal, delay slots filled by hand), so they are kept as assembly; words with their disassembly. docs/sdk.md */
	.set	noreorder
	.set	noat

	.section	.text.func_002672f8,"ax",@progbits
	.globl	func_002672f8
	.ent	func_002672f8
func_002672f8:  /* 0x002672F8 */
	.word	0xD8A40000  /* 002672F8 lqc2 $vf4,0($a1) */
	.word	0xD8A50010  /* 002672FC lqc2 $vf5,16($a1) */
	.word	0xD8A60020  /* 00267300 lqc2 $vf6,32($a1) */
	.word	0xD8A70030  /* 00267304 lqc2 $vf7,48($a1) */
	.word	0xD8C80000  /* 00267308 lqc2 $vf8,0($a2) */
	.word	0x4BE821BC  /* 0026730C vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 00267310 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 00267314 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83A4B  /* 00267318 vmaddw.xyzw $vf9xyzw,$vf7xyzw,$vf8w */
	.word	0x03E00008  /* 0026731C jr $ra */
	.word	0xF8890000  /* 00267320 sqc2 $vf9,0($a0) */
	.end	func_002672f8

	.section	.text.sceVu0MulMatrix,"ax",@progbits
	.globl	sceVu0MulMatrix
	.ent	sceVu0MulMatrix
sceVu0MulMatrix:  /* 0x00267328 */
	.word	0xD8A40000  /* 00267328 lqc2 $vf4,0($a1) */
	.word	0xD8A50010  /* 0026732C lqc2 $vf5,16($a1) */
	.word	0xD8A60020  /* 00267330 lqc2 $vf6,32($a1) */
	.word	0xD8A70030  /* 00267334 lqc2 $vf7,48($a1) */
	.word	0x24070004  /* 00267338 li $a3,4 */
	.word	0xD8C80000  /* 0026733C lqc2 $vf8,0($a2) */
	.word	0x4BE821BC  /* 00267340 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 00267344 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 00267348 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83A4B  /* 0026734C vmaddw.xyzw $vf9xyzw,$vf7xyzw,$vf8w */
	.word	0xF8890000  /* 00267350 sqc2 $vf9,0($a0) */
	.word	0x20E7FFFF  /* 00267354 addi $a3,$a3,-1 */
	.word	0x20C60010  /* 00267358 addi $a2,$a2,16 */
	.word	0x1407FFF7  /* 0026735C bne $zero,$a3,.L0026733C */
	.word	0x20840010  /* 00267360 addi $a0,$a0,16 */
	.word	0x03E00008  /* 00267364 jr $ra */
	.word	0x00000000  /* 00267368 nop */
	.end	sceVu0MulMatrix

	.section	.text.func_00267370,"ax",@progbits
	.globl	func_00267370
	.ent	func_00267370
func_00267370:  /* 0x00267370 */
	.word	0xD8A40000  /* 00267370 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 00267374 lqc2 $vf5,0($a2) */
	.word	0x4BC522FE  /* 00267378 vopmula.xyz $ACCxyz,$vf4xyz,$vf5xyz */
	.word	0x4BC429AE  /* 0026737C vopmsub.xyz $vf6xyz,$vf5xyz,$vf4xyz */
	.word	0x4A2631AC  /* 00267380 vsub.w $vf6w,$vf6w,$vf6w */
	.word	0x03E00008  /* 00267384 jr $ra */
	.word	0xF8860000  /* 00267388 sqc2 $vf6,0($a0) */
	.end	func_00267370

	.section	.text.func_00267390,"ax",@progbits
	.globl	func_00267390
	.ent	func_00267390
func_00267390:  /* 0x00267390 */
	.word	0xD8840000  /* 00267390 lqc2 $vf4,0($a0) */
	.word	0xD8A50000  /* 00267394 lqc2 $vf5,0($a1) */
	.word	0x4BC5216A  /* 00267398 vmul.xyz $vf5xyz,$vf4xyz,$vf5xyz */
	.word	0x4B052941  /* 0026739C vaddy.x $vf5x,$vf5x,$vf5y */
	.word	0x4B052942  /* 002673A0 vaddz.x $vf5x,$vf5x,$vf5z */
	.word	0x48222800  /* 002673A4 qmfc2 $v0,$vf5 */
	.word	0x44820000  /* 002673A8 mtc1 $v0,$f0 */
	.word	0x03E00008  /* 002673AC jr $ra */
	.word	0x00000000  /* 002673B0 nop */
	.end	func_00267390

	.section	.text.func_002673b8,"ax",@progbits
	.globl	func_002673b8
	.ent	func_002673b8
func_002673b8:  /* 0x002673B8 */
	.word	0xD8A40000  /* 002673B8 lqc2 $vf4,0($a1) */
	.word	0x4BC4216A  /* 002673BC vmul.xyz $vf5xyz,$vf4xyz,$vf4xyz */
	.word	0x4B052941  /* 002673C0 vaddy.x $vf5x,$vf5x,$vf5y */
	.word	0x4B052942  /* 002673C4 vaddz.x $vf5x,$vf5x,$vf5z */
	.word	0x4A0503BD  /* 002673C8 c2 0x503bd */
	.word	0x4A0003BF  /* 002673CC vwaitq */
	.word	0x4B000160  /* 002673D0 vaddq.x $vf5x,$vf0x,$Q */
	.word	0x4A0002FF  /* 002673D4 vnop */
	.word	0x4A0002FF  /* 002673D8 vnop */
	.word	0x4A6503BC  /* 002673DC vdiv $Q,$vf0w,$vf5x */
	.word	0x4BE001AC  /* 002673E0 vsub.xyzw $vf6xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x4A0003BF  /* 002673E4 vwaitq */
	.word	0x4BC0219C  /* 002673E8 vmulq.xyz $vf6xyz,$vf4xyz,$Q */
	.word	0x03E00008  /* 002673EC jr $ra */
	.word	0xF8860000  /* 002673F0 sqc2 $vf6,0($a0) */
	.end	func_002673b8

	.section	.text.func_002673f8,"ax",@progbits
	.globl	func_002673f8
	.ent	func_002673f8
func_002673f8:  /* 0x002673F8 */
	.word	0x78A80000  /* 002673F8 lq $t0,0($a1) */
	.word	0x78A90010  /* 002673FC lq $t1,16($a1) */
	.word	0x78AA0020  /* 00267400 lq $t2,32($a1) */
	.word	0x78AB0030  /* 00267404 lq $t3,48($a1) */
	.word	0x71286488  /* 00267408 pextlw $t4,$t1,$t0 */
	.word	0x71286CA8  /* 0026740C pextuw $t5,$t1,$t0 */
	.word	0x716A7488  /* 00267410 pextlw $t6,$t3,$t2 */
	.word	0x716A7CA8  /* 00267414 pextuw $t7,$t3,$t2 */
	.word	0x71CC4389  /* 00267418 pcpyld $t0,$t6,$t4 */
	.word	0x718E4BA9  /* 0026741C pcpyud $t1,$t4,$t6 */
	.word	0x71ED5389  /* 00267420 pcpyld $t2,$t7,$t5 */
	.word	0x71AF5BA9  /* 00267424 pcpyud $t3,$t5,$t7 */
	.word	0x7C880000  /* 00267428 sq $t0,0($a0) */
	.word	0x7C890010  /* 0026742C sq $t1,16($a0) */
	.word	0x7C8A0020  /* 00267430 sq $t2,32($a0) */
	.word	0x03E00008  /* 00267434 jr $ra */
	.word	0x7C8B0030  /* 00267438 sq $t3,48($a0) */
	.end	func_002673f8

	.section	.text.func_00267440,"ax",@progbits
	.globl	func_00267440
	.ent	func_00267440
func_00267440:  /* 0x00267440 */
	.word	0x78A80000  /* 00267440 lq $t0,0($a1) */
	.word	0x78A90010  /* 00267444 lq $t1,16($a1) */
	.word	0x78AA0020  /* 00267448 lq $t2,32($a1) */
	.word	0xD8A40030  /* 0026744C lqc2 $vf4,48($a1) */
	.word	0x4BE5233C  /* 00267450 vmove.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x4BC4212C  /* 00267454 vsub.xyz $vf4xyz,$vf4xyz,$vf4xyz */
	.word	0x4BE9233C  /* 00267458 vmove.xyzw $vf9xyzw,$vf4xyzw */
	.word	0x482B2000  /* 0026745C qmfc2 $t3,$vf4 */
	.word	0x71286488  /* 00267460 pextlw $t4,$t1,$t0 */
	.word	0x71286CA8  /* 00267464 pextuw $t5,$t1,$t0 */
	.word	0x716A7488  /* 00267468 pextlw $t6,$t3,$t2 */
	.word	0x716A7CA8  /* 0026746C pextuw $t7,$t3,$t2 */
	.word	0x71CC4389  /* 00267470 pcpyld $t0,$t6,$t4 */
	.word	0x718E4BA9  /* 00267474 pcpyud $t1,$t4,$t6 */
	.word	0x71ED5389  /* 00267478 pcpyld $t2,$t7,$t5 */
	.word	0x48A83000  /* 0026747C qmtc2 $t0,$vf6 */
	.word	0x48A93800  /* 00267480 qmtc2 $t1,$vf7 */
	.word	0x48AA4000  /* 00267484 qmtc2 $t2,$vf8 */
	.word	0x4BC531BC  /* 00267488 vmulax.xyz $ACCxyz,$vf6xyz,$vf5x */
	.word	0x4BC538BD  /* 0026748C vmadday.xyz $ACCxyz,$vf7xyz,$vf5y */
	.word	0x4BC5410A  /* 00267490 vmaddz.xyz $vf4xyz,$vf8xyz,$vf5z */
	.word	0x4BC4492C  /* 00267494 vsub.xyz $vf4xyz,$vf9xyz,$vf4xyz */
	.word	0x7C880000  /* 00267498 sq $t0,0($a0) */
	.word	0x7C890010  /* 0026749C sq $t1,16($a0) */
	.word	0x7C8A0020  /* 002674A0 sq $t2,32($a0) */
	.word	0x03E00008  /* 002674A4 jr $ra */
	.word	0xF8840030  /* 002674A8 sqc2 $vf4,48($a0) */
	.end	func_00267440

	.section	.text.func_002674b0,"ax",@progbits
	.globl	func_002674b0
	.ent	func_002674b0
func_002674b0:  /* 0x002674B0 */
	.word	0xD8A40000  /* 002674B0 lqc2 $vf4,0($a1) */
	.word	0x44086000  /* 002674B4 mfc1 $t0,$f12 */
	.word	0x48A82800  /* 002674B8 qmtc2 $t0,$vf5 */
	.word	0x4A6503BC  /* 002674BC vdiv $Q,$vf0w,$vf5x */
	.word	0x4A0003BF  /* 002674C0 vwaitq */
	.word	0x4BE0211C  /* 002674C4 vmulq.xyzw $vf4xyzw,$vf4xyzw,$Q */
	.word	0x03E00008  /* 002674C8 jr $ra */
	.word	0xF8840000  /* 002674CC sqc2 $vf4,0($a0) */
	.end	func_002674b0

	.section	.text.func_002674d0,"ax",@progbits
	.globl	func_002674d0
	.ent	func_002674d0
func_002674d0:  /* 0x002674D0 */
	.word	0xD8A40000  /* 002674D0 lqc2 $vf4,0($a1) */
	.word	0x44086000  /* 002674D4 mfc1 $t0,$f12 */
	.word	0x48A82800  /* 002674D8 qmtc2 $t0,$vf5 */
	.word	0x4A6503BC  /* 002674DC vdiv $Q,$vf0w,$vf5x */
	.word	0x4A0003BF  /* 002674E0 vwaitq */
	.word	0x4BC0211C  /* 002674E4 vmulq.xyz $vf4xyz,$vf4xyz,$Q */
	.word	0x03E00008  /* 002674E8 jr $ra */
	.word	0xF8840000  /* 002674EC sqc2 $vf4,0($a0) */
	.end	func_002674d0

	.section	.text.func_002674f0,"ax",@progbits
	.globl	func_002674f0
	.ent	func_002674f0
func_002674f0:  /* 0x002674F0 */
	.word	0xD8A40000  /* 002674F0 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 002674F4 lqc2 $vf5,0($a2) */
	.word	0x44086000  /* 002674F8 mfc1 $t0,$f12 */
	.word	0x48A83000  /* 002674FC qmtc2 $t0,$vf6 */
	.word	0x4B0001C3  /* 00267500 vaddw.x $vf7x,$vf0x,$vf0w */
	.word	0x4B063A2C  /* 00267504 vsub.x $vf8x,$vf7x,$vf6x */
	.word	0x4BE621BC  /* 00267508 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf6x */
	.word	0x4BE82A48  /* 0026750C vmaddx.xyzw $vf9xyzw,$vf5xyzw,$vf8x */
	.word	0x03E00008  /* 00267510 jr $ra */
	.word	0xF8890000  /* 00267514 sqc2 $vf9,0($a0) */
	.end	func_002674f0

	.section	.text.func_00267518,"ax",@progbits
	.globl	func_00267518
	.ent	func_00267518
func_00267518:  /* 0x00267518 */
	.word	0xD8A40000  /* 00267518 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 0026751C lqc2 $vf5,0($a2) */
	.word	0x4BE521A8  /* 00267520 vadd.xyzw $vf6xyzw,$vf4xyzw,$vf5xyzw */
	.word	0x03E00008  /* 00267524 jr $ra */
	.word	0xF8860000  /* 00267528 sqc2 $vf6,0($a0) */
	.end	func_00267518

	.section	.text.func_00267530,"ax",@progbits
	.globl	func_00267530
	.ent	func_00267530
func_00267530:  /* 0x00267530 */
	.word	0xD8A40000  /* 00267530 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 00267534 lqc2 $vf5,0($a2) */
	.word	0x4BE521AC  /* 00267538 vsub.xyzw $vf6xyzw,$vf4xyzw,$vf5xyzw */
	.word	0x03E00008  /* 0026753C jr $ra */
	.word	0xF8860000  /* 00267540 sqc2 $vf6,0($a0) */
	.end	func_00267530

	.section	.text.func_00267548,"ax",@progbits
	.globl	func_00267548
	.ent	func_00267548
func_00267548:  /* 0x00267548 */
	.word	0xD8A40000  /* 00267548 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 0026754C lqc2 $vf5,0($a2) */
	.word	0x4BE521AA  /* 00267550 vmul.xyzw $vf6xyzw,$vf4xyzw,$vf5xyzw */
	.word	0x03E00008  /* 00267554 jr $ra */
	.word	0xF8860000  /* 00267558 sqc2 $vf6,0($a0) */
	.end	func_00267548

	.section	.text.func_00267560,"ax",@progbits
	.globl	func_00267560
	.ent	func_00267560
func_00267560:  /* 0x00267560 */
	.word	0xD8A40000  /* 00267560 lqc2 $vf4,0($a1) */
	.word	0x44086000  /* 00267564 mfc1 $t0,$f12 */
	.word	0x48A82800  /* 00267568 qmtc2 $t0,$vf5 */
	.word	0x4BE52198  /* 0026756C vmulx.xyzw $vf6xyzw,$vf4xyzw,$vf5x */
	.word	0x03E00008  /* 00267570 jr $ra */
	.word	0xF8860000  /* 00267574 sqc2 $vf6,0($a0) */
	.end	func_00267560

	.section	.text.func_00267578,"ax",@progbits
	.globl	func_00267578
	.ent	func_00267578
func_00267578:  /* 0x00267578 */
	.word	0xD8C40000  /* 00267578 lqc2 $vf4,0($a2) */
	.word	0xD8A50030  /* 0026757C lqc2 $vf5,48($a1) */
	.word	0x78A70000  /* 00267580 lq $a3,0($a1) */
	.word	0x78A80010  /* 00267584 lq $t0,16($a1) */
	.word	0x78A90020  /* 00267588 lq $t1,32($a1) */
	.word	0x4BC42968  /* 0026758C vadd.xyz $vf5xyz,$vf5xyz,$vf4xyz */
	.word	0x7C870000  /* 00267590 sq $a3,0($a0) */
	.word	0x7C880010  /* 00267594 sq $t0,16($a0) */
	.word	0x7C890020  /* 00267598 sq $t1,32($a0) */
	.word	0x03E00008  /* 0026759C jr $ra */
	.word	0xF8850030  /* 002675A0 sqc2 $vf5,48($a0) */
	.end	func_00267578

	.section	.text.func_002675a8,"ax",@progbits
	.globl	func_002675a8
	.ent	func_002675a8
func_002675a8:  /* 0x002675A8 */
	.word	0x78A60000  /* 002675A8 lq $a2,0($a1) */
	.word	0x03E00008  /* 002675AC jr $ra */
	.word	0x7C860000  /* 002675B0 sq $a2,0($a0) */
	.end	func_002675a8

	.section	.text.sceVu0CopyMatrix,"ax",@progbits
	.globl	sceVu0CopyMatrix
	.ent	sceVu0CopyMatrix
sceVu0CopyMatrix:  /* 0x002675B8 */
	.word	0x78A60000  /* 002675B8 lq $a2,0($a1) */
	.word	0x78A70010  /* 002675BC lq $a3,16($a1) */
	.word	0x78A80020  /* 002675C0 lq $t0,32($a1) */
	.word	0x78A90030  /* 002675C4 lq $t1,48($a1) */
	.word	0x7C860000  /* 002675C8 sq $a2,0($a0) */
	.word	0x7C870010  /* 002675CC sq $a3,16($a0) */
	.word	0x7C880020  /* 002675D0 sq $t0,32($a0) */
	.word	0x03E00008  /* 002675D4 jr $ra */
	.word	0x7C890030  /* 002675D8 sq $t1,48($a0) */
	.end	sceVu0CopyMatrix

	.section	.text.func_002675e0,"ax",@progbits
	.globl	func_002675e0
	.ent	func_002675e0
func_002675e0:  /* 0x002675E0 */
	.word	0xD8A40000  /* 002675E0 lqc2 $vf4,0($a1) */
	.word	0x4BE5217D  /* 002675E4 vftoi4.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x03E00008  /* 002675E8 jr $ra */
	.word	0xF8850000  /* 002675EC sqc2 $vf5,0($a0) */
	.end	func_002675e0

	.section	.text.func_002675f0,"ax",@progbits
	.globl	func_002675f0
	.ent	func_002675f0
func_002675f0:  /* 0x002675F0 */
	.word	0xD8A40000  /* 002675F0 lqc2 $vf4,0($a1) */
	.word	0x4BE5217C  /* 002675F4 vftoi0.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x03E00008  /* 002675F8 jr $ra */
	.word	0xF8850000  /* 002675FC sqc2 $vf5,0($a0) */
	.end	func_002675f0

	.section	.text.func_00267600,"ax",@progbits
	.globl	func_00267600
	.ent	func_00267600
func_00267600:  /* 0x00267600 */
	.word	0xD8A40000  /* 00267600 lqc2 $vf4,0($a1) */
	.word	0x4BE5213D  /* 00267604 vitof4.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x03E00008  /* 00267608 jr $ra */
	.word	0xF8850000  /* 0026760C sqc2 $vf5,0($a0) */
	.end	func_00267600

	.section	.text.func_00267610,"ax",@progbits
	.globl	func_00267610
	.ent	func_00267610
func_00267610:  /* 0x00267610 */
	.word	0xD8A40000  /* 00267610 lqc2 $vf4,0($a1) */
	.word	0x4BE5213C  /* 00267614 vitof0.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x03E00008  /* 00267618 jr $ra */
	.word	0xF8850000  /* 0026761C sqc2 $vf5,0($a0) */
	.end	func_00267610

	.section	.text.sceVu0UnitMatrix,"ax",@progbits
	.globl	sceVu0UnitMatrix
	.ent	sceVu0UnitMatrix
sceVu0UnitMatrix:  /* 0x00267620 */
	.word	0x4BE0012C  /* 00267620 vsub.xyzw $vf4xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x4A202128  /* 00267624 vadd.w $vf4w,$vf4w,$vf0w */
	.word	0x4BE5233D  /* 00267628 vmr32.xyzw $vf5xyzw,$vf4xyzw */
	.word	0x4BE62B3D  /* 0026762C vmr32.xyzw $vf6xyzw,$vf5xyzw */
	.word	0x4BE7333D  /* 00267630 vmr32.xyzw $vf7xyzw,$vf6xyzw */
	.word	0xF8840030  /* 00267634 sqc2 $vf4,48($a0) */
	.word	0xF8850020  /* 00267638 sqc2 $vf5,32($a0) */
	.word	0xF8860010  /* 0026763C sqc2 $vf6,16($a0) */
	.word	0x03E00008  /* 00267640 jr $ra */
	.word	0xF8870000  /* 00267644 sqc2 $vf7,0($a0) */
	.end	sceVu0UnitMatrix

	.section	.text.func_00267648,"ax",@progbits
	.globl	func_00267648
	.ent	func_00267648
func_00267648:  /* 0x00267648 */
	.word	0x3C080047  /* 00267648 lui $t0,%hi(D_0046C580) */
	.word	0x2508C580  /* 0026764C addiu $t0,$t0,%lo(D_0046C580) */
	.word	0xD9050000  /* 00267650 lqc2 $vf5,0($t0) */
	.word	0x4A26333D  /* 00267654 vmr32.w $vf6w,$vf6w */
	.word	0x4B060100  /* 00267658 vaddx.x $vf4x,$vf0x,$vf6x */
	.word	0x4B0631AA  /* 0026765C vmul.x $vf6x,$vf6x,$vf6x */
	.word	0x4AE02118  /* 00267660 vmulx.yzw $vf4yzw,$vf4yzw,$vf0x */
	.word	0x4BE62A1B  /* 00267664 vmulw.xyzw $vf8xyzw,$vf5xyzw,$vf6w */
	.word	0x4BE0016C  /* 00267668 vsub.xyzw $vf5xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x4BE64218  /* 0026766C vmulx.xyzw $vf8xyzw,$vf8xyzw,$vf6x */
	.word	0x4BC64218  /* 00267670 vmulx.xyz $vf8xyz,$vf8xyz,$vf6x */
	.word	0x4B082103  /* 00267674 vaddw.x $vf4x,$vf4x,$vf8w */
	.word	0x4B864218  /* 00267678 vmulx.xy $vf8xy,$vf8xy,$vf6x */
	.word	0x4B082102  /* 0026767C vaddz.x $vf4x,$vf4x,$vf8z */
	.word	0x4B064218  /* 00267680 vmulx.x $vf8x,$vf8x,$vf6x */
	.word	0x4B082101  /* 00267684 vaddy.x $vf4x,$vf4x,$vf8y */
	.word	0x4B082100  /* 00267688 vaddx.x $vf4x,$vf4x,$vf8x */
	.word	0x4B842900  /* 0026768C vaddx.xy $vf4xy,$vf5xy,$vf4x */
	.word	0x4B0421EA  /* 00267690 vmul.x $vf7x,$vf4x,$vf4x */
	.word	0x4A2701C4  /* 00267694 vsubx.w $vf7w,$vf0w,$vf7x */
	.word	0x4B8703BD  /* 00267698 c2 0x18703bd */
	.word	0x4A0003BF  /* 0026769C vwaitq */
	.word	0x14E00003  /* 002676A0 bnez $a3,.L002676B0 */
	.word	0x4B0001E0  /* 002676A4 vaddq.x $vf7x,$vf0x,$Q */
	.word	0x10000002  /* 002676A8 b .L002676B4 */
	.word	0x4B072900  /* 002676AC vaddx.x $vf4x,$vf5x,$vf7x */
	.word	0x4B072904  /* 002676B0 vsubx.x $vf4x,$vf5x,$vf7x */
	.word	0x03E00008  /* 002676B4 jr $ra */
	.word	0x00000000  /* 002676B8 nop */
	.end	func_00267648

	.section	.text.func_002676c0,"ax",@progbits
	.globl	func_002676c0
	.ent	func_002676c0
func_002676c0:  /* 0x002676C0 */
	.word	0x44800000  /* 002676C0 mtc1 $zero,$f0 */
	.word	0x46006034  /* 002676C4 c.lt.s $f12,$f0 */
	.word	0x3C013FC9  /* 002676C8 lui $at,0x3fc9 */
	.word	0x34210FDB  /* 002676CC ori $at,$at,0xfdb */
	.word	0x44810000  /* 002676D0 mtc1 $at,$f0 */
	.word	0x45000004  /* 002676D4 bc1f .L002676E8 */
	.word	0x00000000  /* 002676D8 nop */
	.word	0x460C0300  /* 002676DC add.s $f12,$f0,$f12 */
	.word	0x08099DBC  /* 002676E0 j .L002676F0 */
	.word	0x24070001  /* 002676E4 li $a3,1 */
	.word	0x460C0301  /* 002676E8 sub.s $f12,$f0,$f12 */
	.word	0x0000382D  /* 002676EC move $a3,$zero */
	.word	0x44086000  /* 002676F0 mfc1 $t0,$f12 */
	.word	0x48A83000  /* 002676F4 qmtc2 $t0,$vf6 */
	.word	0x03E0302D  /* 002676F8 move $a2,$ra */
	.word	0x0C099D92  /* 002676FC jal func_00267648 */
	.word	0x00000000  /* 00267700 nop */
	.word	0x00C0F82D  /* 00267704 move $ra,$a2 */
	.word	0x4BE62B3C  /* 00267708 vmove.xyzw $vf6xyzw,$vf5xyzw */
	.word	0x4BE72B3C  /* 0026770C vmove.xyzw $vf7xyzw,$vf5xyzw */
	.word	0x4BE9033C  /* 00267710 vmove.xyzw $vf9xyzw,$vf0xyzw */
	.word	0x4BC94A6C  /* 00267714 vsub.xyz $vf9xyz,$vf9xyz,$vf9xyz */
	.word	0x4BE84B3D  /* 00267718 vmr32.xyzw $vf8xyzw,$vf9xyzw */
	.word	0x4A64212C  /* 0026771C vsub.zw $vf4zw,$vf4zw,$vf4zw */
	.word	0x4A842980  /* 00267720 vaddx.y $vf6y,$vf5y,$vf4x */
	.word	0x4B042981  /* 00267724 vaddy.x $vf6x,$vf5x,$vf4y */
	.word	0x4B0429C4  /* 00267728 vsubx.x $vf7x,$vf5x,$vf4x */
	.word	0x4A8429C1  /* 0026772C vaddy.y $vf7y,$vf5y,$vf4y */
	.word	0x24070004  /* 00267730 li $a3,4 */
	.word	0xD8A40000  /* 00267734 lqc2 $vf4,0($a1) */
	.word	0x4BE431BC  /* 00267738 vmulax.xyzw $ACCxyzw,$vf6xyzw,$vf4x */
	.word	0x4BE438BD  /* 0026773C vmadday.xyzw $ACCxyzw,$vf7xyzw,$vf4y */
	.word	0x4BE440BE  /* 00267740 vmaddaz.xyzw $ACCxyzw,$vf8xyzw,$vf4z */
	.word	0x4BE4494B  /* 00267744 vmaddw.xyzw $vf5xyzw,$vf9xyzw,$vf4w */
	.word	0xF8850000  /* 00267748 sqc2 $vf5,0($a0) */
	.word	0x20E7FFFF  /* 0026774C addi $a3,$a3,-1 */
	.word	0x20A50010  /* 00267750 addi $a1,$a1,16 */
	.word	0x1407FFF7  /* 00267754 bne $zero,$a3,.L00267734 */
	.word	0x20840010  /* 00267758 addi $a0,$a0,16 */
	.word	0x03E00008  /* 0026775C jr $ra */
	.word	0x00000000  /* 00267760 nop */
	.end	func_002676c0

	.section	.text.func_00267768,"ax",@progbits
	.globl	func_00267768
	.ent	func_00267768
func_00267768:  /* 0x00267768 */
	.word	0x44800000  /* 00267768 mtc1 $zero,$f0 */
	.word	0x46006034  /* 0026776C c.lt.s $f12,$f0 */
	.word	0x3C013FC9  /* 00267770 lui $at,0x3fc9 */
	.word	0x34210FDB  /* 00267774 ori $at,$at,0xfdb */
	.word	0x44810000  /* 00267778 mtc1 $at,$f0 */
	.word	0x45000004  /* 0026777C bc1f .L00267790 */
	.word	0x00000000  /* 00267780 nop */
	.word	0x460C0300  /* 00267784 add.s $f12,$f0,$f12 */
	.word	0x08099DE6  /* 00267788 j .L00267798 */
	.word	0x24070001  /* 0026778C li $a3,1 */
	.word	0x460C0301  /* 00267790 sub.s $f12,$f0,$f12 */
	.word	0x0000382D  /* 00267794 move $a3,$zero */
	.word	0x44086000  /* 00267798 mfc1 $t0,$f12 */
	.word	0x48A83000  /* 0026779C qmtc2 $t0,$vf6 */
	.word	0x03E0302D  /* 002677A0 move $a2,$ra */
	.word	0x0C099D92  /* 002677A4 jal func_00267648 */
	.word	0x00000000  /* 002677A8 nop */
	.word	0x00C0F82D  /* 002677AC move $ra,$a2 */
	.word	0x4BE62B3C  /* 002677B0 vmove.xyzw $vf6xyzw,$vf5xyzw */
	.word	0x4BE72B3C  /* 002677B4 vmove.xyzw $vf7xyzw,$vf5xyzw */
	.word	0x4BE82B3C  /* 002677B8 vmove.xyzw $vf8xyzw,$vf5xyzw */
	.word	0x4BE92B3C  /* 002677BC vmove.xyzw $vf9xyzw,$vf5xyzw */
	.word	0x4B002983  /* 002677C0 vaddw.x $vf6x,$vf5x,$vf0w */
	.word	0x4A202A43  /* 002677C4 vaddw.w $vf9w,$vf5w,$vf0w */
	.word	0x4A64212C  /* 002677C8 vsub.zw $vf4zw,$vf4zw,$vf4zw */
	.word	0x4A4429C0  /* 002677CC vaddx.z $vf7z,$vf5z,$vf4x */
	.word	0x4A8429C1  /* 002677D0 vaddy.y $vf7y,$vf5y,$vf4y */
	.word	0x4A842A04  /* 002677D4 vsubx.y $vf8y,$vf5y,$vf4x */
	.word	0x4A442A01  /* 002677D8 vaddy.z $vf8z,$vf5z,$vf4y */
	.word	0x24070004  /* 002677DC li $a3,4 */
	.word	0xD8A40000  /* 002677E0 lqc2 $vf4,0($a1) */
	.word	0x4BE431BC  /* 002677E4 vmulax.xyzw $ACCxyzw,$vf6xyzw,$vf4x */
	.word	0x4BE438BD  /* 002677E8 vmadday.xyzw $ACCxyzw,$vf7xyzw,$vf4y */
	.word	0x4BE440BE  /* 002677EC vmaddaz.xyzw $ACCxyzw,$vf8xyzw,$vf4z */
	.word	0x4BE4494B  /* 002677F0 vmaddw.xyzw $vf5xyzw,$vf9xyzw,$vf4w */
	.word	0xF8850000  /* 002677F4 sqc2 $vf5,0($a0) */
	.word	0x20E7FFFF  /* 002677F8 addi $a3,$a3,-1 */
	.word	0x20A50010  /* 002677FC addi $a1,$a1,16 */
	.word	0x1407FFF7  /* 00267800 bne $zero,$a3,.L002677E0 */
	.word	0x20840010  /* 00267804 addi $a0,$a0,16 */
	.word	0x03E00008  /* 00267808 jr $ra */
	.word	0x00000000  /* 0026780C nop */
	.end	func_00267768

	.section	.text.func_00267810,"ax",@progbits
	.globl	func_00267810
	.ent	func_00267810
func_00267810:  /* 0x00267810 */
	.word	0x44800000  /* 00267810 mtc1 $zero,$f0 */
	.word	0x46006034  /* 00267814 c.lt.s $f12,$f0 */
	.word	0x3C013FC9  /* 00267818 lui $at,0x3fc9 */
	.word	0x34210FDB  /* 0026781C ori $at,$at,0xfdb */
	.word	0x44810000  /* 00267820 mtc1 $at,$f0 */
	.word	0x45000004  /* 00267824 bc1f .L00267838 */
	.word	0x00000000  /* 00267828 nop */
	.word	0x460C0300  /* 0026782C add.s $f12,$f0,$f12 */
	.word	0x08099E10  /* 00267830 j .L00267840 */
	.word	0x24070001  /* 00267834 li $a3,1 */
	.word	0x460C0301  /* 00267838 sub.s $f12,$f0,$f12 */
	.word	0x0000382D  /* 0026783C move $a3,$zero */
	.word	0x44086000  /* 00267840 mfc1 $t0,$f12 */
	.word	0x48A83000  /* 00267844 qmtc2 $t0,$vf6 */
	.word	0x03E0302D  /* 00267848 move $a2,$ra */
	.word	0x0C099D92  /* 0026784C jal func_00267648 */
	.word	0x00000000  /* 00267850 nop */
	.word	0x00C0F82D  /* 00267854 move $ra,$a2 */
	.word	0x4BE62B3C  /* 00267858 vmove.xyzw $vf6xyzw,$vf5xyzw */
	.word	0x4BE72B3C  /* 0026785C vmove.xyzw $vf7xyzw,$vf5xyzw */
	.word	0x4BE82B3C  /* 00267860 vmove.xyzw $vf8xyzw,$vf5xyzw */
	.word	0x4BE92B3C  /* 00267864 vmove.xyzw $vf9xyzw,$vf5xyzw */
	.word	0x4A8029C3  /* 00267868 vaddw.y $vf7y,$vf5y,$vf0w */
	.word	0x4A202A43  /* 0026786C vaddw.w $vf9w,$vf5w,$vf0w */
	.word	0x4A64212C  /* 00267870 vsub.zw $vf4zw,$vf4zw,$vf4zw */
	.word	0x4A442984  /* 00267874 vsubx.z $vf6z,$vf5z,$vf4x */
	.word	0x4B042981  /* 00267878 vaddy.x $vf6x,$vf5x,$vf4y */
	.word	0x4B042A00  /* 0026787C vaddx.x $vf8x,$vf5x,$vf4x */
	.word	0x4A442A01  /* 00267880 vaddy.z $vf8z,$vf5z,$vf4y */
	.word	0x24070004  /* 00267884 li $a3,4 */
	.word	0xD8A40000  /* 00267888 lqc2 $vf4,0($a1) */
	.word	0x4BE431BC  /* 0026788C vmulax.xyzw $ACCxyzw,$vf6xyzw,$vf4x */
	.word	0x4BE438BD  /* 00267890 vmadday.xyzw $ACCxyzw,$vf7xyzw,$vf4y */
	.word	0x4BE440BE  /* 00267894 vmaddaz.xyzw $ACCxyzw,$vf8xyzw,$vf4z */
	.word	0x4BE4494B  /* 00267898 vmaddw.xyzw $vf5xyzw,$vf9xyzw,$vf4w */
	.word	0xF8850000  /* 0026789C sqc2 $vf5,0($a0) */
	.word	0x20E7FFFF  /* 002678A0 addi $a3,$a3,-1 */
	.word	0x20A50010  /* 002678A4 addi $a1,$a1,16 */
	.word	0x1407FFF7  /* 002678A8 bne $zero,$a3,.L00267888 */
	.word	0x20840010  /* 002678AC addi $a0,$a0,16 */
	.word	0x03E00008  /* 002678B0 jr $ra */
	.word	0x00000000  /* 002678B4 nop */
	.end	func_00267810

	.section	.text.func_00267908,"ax",@progbits
	.globl	func_00267908
	.ent	func_00267908
func_00267908:  /* 0x00267908 */
	.word	0x44086000  /* 00267908 mfc1 $t0,$f12 */
	.word	0x44096800  /* 0026790C mfc1 $t1,$f13 */
	.word	0xD8A60000  /* 00267910 lqc2 $vf6,0($a1) */
	.word	0x48A82000  /* 00267914 qmtc2 $t0,$vf4 */
	.word	0x48A92800  /* 00267918 qmtc2 $t1,$vf5 */
	.word	0x4BE43190  /* 0026791C vmaxx.xyzw $vf6xyzw,$vf6xyzw,$vf4x */
	.word	0x4BE53194  /* 00267920 vminix.xyzw $vf6xyzw,$vf6xyzw,$vf5x */
	.word	0x03E00008  /* 00267924 jr $ra */
	.word	0xF8860000  /* 00267928 sqc2 $vf6,0($a0) */
	.end	func_00267908

	.section	.text.func_00267da0,"ax",@progbits
	.globl	func_00267da0
	.ent	func_00267da0
func_00267da0:  /* 0x00267DA0 */
	.word	0xD8A40000  /* 00267DA0 lqc2 $vf4,0($a1) */
	.word	0xD8A50010  /* 00267DA4 lqc2 $vf5,16($a1) */
	.word	0xD8A60020  /* 00267DA8 lqc2 $vf6,32($a1) */
	.word	0xD8A70030  /* 00267DAC lqc2 $vf7,48($a1) */
	.word	0xD8C80000  /* 00267DB0 lqc2 $vf8,0($a2) */
	.word	0x4BE821BC  /* 00267DB4 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 00267DB8 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 00267DBC vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83A4B  /* 00267DC0 vmaddw.xyzw $vf9xyzw,$vf7xyzw,$vf8w */
	.word	0x4BE903BC  /* 00267DC4 vdiv $Q,$vf0w,$vf9w */
	.word	0x4A0003BF  /* 00267DC8 vwaitq */
	.word	0x4BC04A5C  /* 00267DCC vmulq.xyz $vf9xyz,$vf9xyz,$Q */
	.word	0x11000002  /* 00267DD0 beqz $t0,.L00267DDC */
	.word	0x4BEA497D  /* 00267DD4 vftoi4.xyzw $vf10xyzw,$vf9xyzw */
	.word	0x4A6A497C  /* 00267DD8 vftoi0.zw $vf10zw,$vf9zw */
	.word	0xF88A0000  /* 00267DDC sqc2 $vf10,0($a0) */
	.word	0x20E7FFFF  /* 00267DE0 addi $a3,$a3,-1 */
	.word	0x20C60010  /* 00267DE4 addi $a2,$a2,16 */
	.word	0x1407FFF1  /* 00267DE8 bne $zero,$a3,.L00267DB0 */
	.word	0x20840010  /* 00267DEC addi $a0,$a0,16 */
	.word	0x03E00008  /* 00267DF0 jr $ra */
	.word	0x00000000  /* 00267DF4 nop */
	.end	func_00267da0

	.section	.text.func_00267df8,"ax",@progbits
	.globl	func_00267df8
	.ent	func_00267df8
func_00267df8:  /* 0x00267DF8 */
	.word	0xD8A40000  /* 00267DF8 lqc2 $vf4,0($a1) */
	.word	0xD8A50010  /* 00267DFC lqc2 $vf5,16($a1) */
	.word	0xD8A60020  /* 00267E00 lqc2 $vf6,32($a1) */
	.word	0xD8A70030  /* 00267E04 lqc2 $vf7,48($a1) */
	.word	0xD8C80000  /* 00267E08 lqc2 $vf8,0($a2) */
	.word	0x4BE821BC  /* 00267E0C vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 00267E10 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 00267E14 vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83A4B  /* 00267E18 vmaddw.xyzw $vf9xyzw,$vf7xyzw,$vf8w */
	.word	0x4BE903BC  /* 00267E1C vdiv $Q,$vf0w,$vf9w */
	.word	0x4A0003BF  /* 00267E20 vwaitq */
	.word	0x4BC04A5C  /* 00267E24 vmulq.xyz $vf9xyz,$vf9xyz,$Q */
	.word	0x10E00002  /* 00267E28 beqz $a3,.L00267E34 */
	.word	0x4BEA497D  /* 00267E2C vftoi4.xyzw $vf10xyzw,$vf9xyzw */
	.word	0x4A6A497C  /* 00267E30 vftoi0.zw $vf10zw,$vf9zw */
	.word	0x03E00008  /* 00267E34 jr $ra */
	.word	0xF88A0000  /* 00267E38 sqc2 $vf10,0($a0) */
	.end	func_00267df8

	.section	.text.func_00267e60,"ax",@progbits
	.globl	func_00267e60
	.ent	func_00267e60
func_00267e60:  /* 0x00267E60 */
	.word	0xD8A40000  /* 00267E60 lqc2 $vf4,0($a1) */
	.word	0xD8C50000  /* 00267E64 lqc2 $vf5,0($a2) */
	.word	0x44086000  /* 00267E68 mfc1 $t0,$f12 */
	.word	0x48A83000  /* 00267E6C qmtc2 $t0,$vf6 */
	.word	0x4A29233C  /* 00267E70 vmove.w $vf9w,$vf4w */
	.word	0x4B0001C3  /* 00267E74 vaddw.x $vf7x,$vf0x,$vf0w */
	.word	0x4B063A2C  /* 00267E78 vsub.x $vf8x,$vf7x,$vf6x */
	.word	0x4BC621BC  /* 00267E7C vmulax.xyz $ACCxyz,$vf4xyz,$vf6x */
	.word	0x4BC82A48  /* 00267E80 vmaddx.xyz $vf9xyz,$vf5xyz,$vf8x */
	.word	0x03E00008  /* 00267E84 jr $ra */
	.word	0xF8890000  /* 00267E88 sqc2 $vf9,0($a0) */
	.end	func_00267e60

	.section	.text.func_00267e90,"ax",@progbits
	.globl	func_00267e90
	.ent	func_00267e90
func_00267e90:  /* 0x00267E90 */
	.word	0xD8A40000  /* 00267E90 lqc2 $vf4,0($a1) */
	.word	0x44086000  /* 00267E94 mfc1 $t0,$f12 */
	.word	0x48A82800  /* 00267E98 qmtc2 $t0,$vf5 */
	.word	0x4BC52118  /* 00267E9C vmulx.xyz $vf4xyz,$vf4xyz,$vf5x */
	.word	0x03E00008  /* 00267EA0 jr $ra */
	.word	0xF8840000  /* 00267EA4 sqc2 $vf4,0($a0) */
	.end	func_00267e90

	.section	.text.func_00267ea8,"ax",@progbits
	.globl	func_00267ea8
	.ent	func_00267ea8
func_00267ea8:  /* 0x00267EA8 */
	.word	0x4BE0012C  /* 00267EA8 vsub.xyzw $vf4xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x3C024580  /* 00267EAC lui $v0,0x4580 */
	.word	0x00021438  /* 00267EB0 dsll $v0,$v0,0x10 */
	.word	0x34424580  /* 00267EB4 ori $v0,$v0,0x4580 */
	.word	0x00021438  /* 00267EB8 dsll $v0,$v0,0x10 */
	.word	0xD8870000  /* 00267EBC lqc2 $vf7,0($a0) */
	.word	0x48A23000  /* 00267EC0 qmtc2 $v0,$vf6 */
	.word	0x48C08000  /* 00267EC4 ctc2 $zero,$vi16 */
	.word	0x4BA4396C  /* 00267EC8 vsub.xyw $vf5xyw,$vf7xyw,$vf4xyw */
	.word	0x4B87316C  /* 00267ECC vsub.xy $vf5xy,$vf6xy,$vf7xy */
	.word	0x4A0002FF  /* 00267ED0 vnop */
	.word	0x4A0002FF  /* 00267ED4 vnop */
	.word	0x4A0002FF  /* 00267ED8 vnop */
	.word	0x4A0002FF  /* 00267EDC vnop */
	.word	0x4A0002FF  /* 00267EE0 vnop */
	.word	0x48428000  /* 00267EE4 cfc2 $v0,$vi16 */
	.word	0x03E00008  /* 00267EE8 jr $ra */
	.word	0x304200C0  /* 00267EEC andi $v0,$v0,0xc0 */
	.end	func_00267ea8

	.section	.text.func_00267ef0,"ax",@progbits
	.globl	func_00267ef0
	.ent	func_00267ef0
func_00267ef0:  /* 0x00267EF0 */
	.word	0x4BE0012C  /* 00267EF0 vsub.xyzw $vf4xyzw,$vf0xyzw,$vf0xyzw */
	.word	0x3C024580  /* 00267EF4 lui $v0,0x4580 */
	.word	0x00021438  /* 00267EF8 dsll $v0,$v0,0x10 */
	.word	0x34424580  /* 00267EFC ori $v0,$v0,0x4580 */
	.word	0x00021438  /* 00267F00 dsll $v0,$v0,0x10 */
	.word	0xD8860000  /* 00267F04 lqc2 $vf6,0($a0) */
	.word	0xD8A80000  /* 00267F08 lqc2 $vf8,0($a1) */
	.word	0xD8C90000  /* 00267F0C lqc2 $vf9,0($a2) */
	.word	0x48A23800  /* 00267F10 qmtc2 $v0,$vf7 */
	.word	0x48C08000  /* 00267F14 ctc2 $zero,$vi16 */
	.word	0x4BA4316C  /* 00267F18 vsub.xyw $vf5xyw,$vf6xyw,$vf4xyw */
	.word	0x4B86396C  /* 00267F1C vsub.xy $vf5xy,$vf7xy,$vf6xy */
	.word	0x4BA4416C  /* 00267F20 vsub.xyw $vf5xyw,$vf8xyw,$vf4xyw */
	.word	0x4B88396C  /* 00267F24 vsub.xy $vf5xy,$vf7xy,$vf8xy */
	.word	0x4BA4496C  /* 00267F28 vsub.xyw $vf5xyw,$vf9xyw,$vf4xyw */
	.word	0x4B89396C  /* 00267F2C vsub.xy $vf5xy,$vf7xy,$vf9xy */
	.word	0x4A0002FF  /* 00267F30 vnop */
	.word	0x4A0002FF  /* 00267F34 vnop */
	.word	0x4A0002FF  /* 00267F38 vnop */
	.word	0x4A0002FF  /* 00267F3C vnop */
	.word	0x4A0002FF  /* 00267F40 vnop */
	.word	0x48428000  /* 00267F44 cfc2 $v0,$vi16 */
	.word	0x03E00008  /* 00267F48 jr $ra */
	.word	0x304200C0  /* 00267F4C andi $v0,$v0,0xc0 */
	.end	func_00267ef0

	.section	.text.func_00267f50,"ax",@progbits
	.globl	func_00267f50
	.ent	func_00267f50
func_00267f50:  /* 0x00267F50 */
	.word	0xD8E80000  /* 00267F50 lqc2 $vf8,0($a3) */
	.word	0xD8C40000  /* 00267F54 lqc2 $vf4,0($a2) */
	.word	0xD8C50010  /* 00267F58 lqc2 $vf5,16($a2) */
	.word	0xD8C60020  /* 00267F5C lqc2 $vf6,32($a2) */
	.word	0xD8C70030  /* 00267F60 lqc2 $vf7,48($a2) */
	.word	0xD8890000  /* 00267F64 lqc2 $vf9,0($a0) */
	.word	0xD8AA0000  /* 00267F68 lqc2 $vf10,0($a1) */
	.word	0xD88B0000  /* 00267F6C lqc2 $vf11,0($a0) */
	.word	0xD8AC0000  /* 00267F70 lqc2 $vf12,0($a1) */
	.word	0x4BE821BC  /* 00267F74 vmulax.xyzw $ACCxyzw,$vf4xyzw,$vf8x */
	.word	0x4BE828BD  /* 00267F78 vmadday.xyzw $ACCxyzw,$vf5xyzw,$vf8y */
	.word	0x4BE830BE  /* 00267F7C vmaddaz.xyzw $ACCxyzw,$vf6xyzw,$vf8z */
	.word	0x4BE83A0B  /* 00267F80 vmaddw.xyzw $vf8xyzw,$vf7xyzw,$vf8w */
	.word	0x4BC84ADB  /* 00267F84 vmulw.xyz $vf11xyz,$vf9xyz,$vf8w */
	.word	0x4BC8531B  /* 00267F88 vmulw.xyz $vf12xyz,$vf10xyz,$vf8w */
	.word	0x4A0002FF  /* 00267F8C vnop */
	.word	0x4A0002FF  /* 00267F90 vnop */
	.word	0x48C08000  /* 00267F94 ctc2 $zero,$vi16 */
	.word	0x4BAB42EC  /* 00267F98 vsub.xyw $vf11xyw,$vf8xyw,$vf11xyw */
	.word	0x4BA8632C  /* 00267F9C vsub.xyw $vf12xyw,$vf12xyw,$vf8xyw */
	.word	0x4A2B4B3C  /* 00267FA0 vmove.w $vf11w,$vf9w */
	.word	0x4A2C533C  /* 00267FA4 vmove.w $vf12w,$vf10w */
	.word	0x4A0002FF  /* 00267FA8 vnop */
	.word	0x20E70010  /* 00267FAC addi $a3,$a3,16 */
	.word	0xD8E80000  /* 00267FB0 lqc2 $vf8,0($a3) */
	.word	0x2108FFFF  /* 00267FB4 addi $t0,$t0,-1 */
	.word	0x48428000  /* 00267FB8 cfc2 $v0,$vi16 */
	.word	0x304200C0  /* 00267FBC andi $v0,$v0,0xc0 */
	.word	0x10400004  /* 00267FC0 beqz $v0,.L00267FD4 */
	.word	0x00000000  /* 00267FC4 nop */
	.word	0x1408FFEA  /* 00267FC8 bne $zero,$t0,.L00267F74 */
	.word	0x00000000  /* 00267FCC nop */
	.word	0x20020001  /* 00267FD0 addi $v0,$zero,1 */
	.word	0x03E00008  /* 00267FD4 jr $ra */
	.word	0x00000000  /* 00267FD8 nop */
	.end	func_00267f50

	.section	.text.func_00267fe0,"ax",@progbits
	.globl	func_00267fe0
	.ent	func_00267fe0
func_00267fe0:  /* 0x00267FE0 */
	.word	0x3C021000  /* 00267FE0 lui $v0,0x1000 */
	.word	0x3C041000  /* 00267FE4 lui $a0,0x1000 */
	.word	0x34423830  /* 00267FE8 ori $v0,$v0,0x3830 */
	.word	0x34843820  /* 00267FEC ori $a0,$a0,0x3820 */
	.word	0xAC400000  /* 00267FF0 sw $zero,0($v0) */
	.word	0x3C031000  /* 00267FF4 lui $v1,0x1000 */
	.word	0xAC800000  /* 00267FF8 sw $zero,0($a0) */
	.word	0x34633810  /* 00267FFC ori $v1,$v1,0x3810 */
	.word	0x24020001  /* 00268000 li $v0,1 */
	.word	0xAC620000  /* 00268004 sw $v0,0($v1) */
	.word	0x4848E000  /* 00268008 cfc2 $t0,$vi28 */
	.word	0x35080002  /* 0026800C ori $t0,$t0,0x2 */
	.word	0x48C8E000  /* 00268010 ctc2 $t0,$vi28 */
	.word	0x0000040F  /* 00268014 sync.p */
	.word	0x3C040047  /* 00268018 lui $a0,%hi(D_0046C590) */
	.word	0x3C051000  /* 0026801C lui $a1,0x1000 */
	.word	0x2484C590  /* 00268020 addiu $a0,$a0,%lo(D_0046C590) */
	.word	0x34A54000  /* 00268024 ori $a1,$a1,0x4000 */
	.word	0x78820000  /* 00268028 lq $v0,0($a0) */
	.word	0x7CA20000  /* 0026802C sq $v0,0($a1) */
	.word	0x78830010  /* 00268030 lq $v1,16($a0) */
	.word	0x03E00008  /* 00268034 jr $ra */
	.word	0x7CA30000  /* 00268038 sq $v1,0($a1) */
	.end	func_00267fe0
