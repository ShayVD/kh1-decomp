/* libpc (sdk segment): scePcStart/scePcStop program the performance counters with mtps/mtpc and return through eret; register use and the unfilled jr ra slot do not come from ee-gcc, so the originals were assembly. Words with their disassembly (tools/asm_export.py). */
	.set	noreorder
	.set	noat

	.section	.text.scePcStart,"ax",@progbits
	.globl	scePcStart
	.ent	scePcStart
scePcStart:  /* 0x00270AD8 */
	.word	0x3C030001  /* 00270AD8 lui $v1,0x1 */
	.word	0x00000000  /* 00270ADC nop */
	.word	0x42000039  /* 00270AE0 di */
	.word	0x0000040F  /* 00270AE4 sync.p */
	.word	0x40026000  /* 00270AE8 mfc0 $v0,c0_sr */
	.word	0x00431024  /* 00270AEC and $v0,$v0,$v1 */
	.word	0x00000000  /* 00270AF0 nop */
	.word	0x1440FFFA  /* 00270AF4 bnez $v0,.L00270AE0 */
	.word	0x00000000  /* 00270AF8 nop */
	.word	0x40026000  /* 00270AFC mfc0 $v0,c0_sr */
	.word	0x0000040F  /* 00270B00 sync.p */
	.word	0x34420006  /* 00270B04 ori $v0,$v0,0x6 */
	.word	0x38420002  /* 00270B08 xori $v0,$v0,0x2 */
	.word	0x3C030001  /* 00270B0C lui $v1,0x1 */
	.word	0x00431025  /* 00270B10 or $v0,$v0,$v1 */
	.word	0x40826000  /* 00270B14 mtc0 $v0,c0_sr */
	.word	0x0000040F  /* 00270B18 sync.p */
	.word	0x4084C800  /* 00270B1C mtps $a0,0 */
	.word	0x4085C801  /* 00270B20 mtpc $a1,0 */
	.word	0x4086C803  /* 00270B24 mtpc $a2,1 */
	.word	0x409FF000  /* 00270B28 mtc0 $ra,c0_errorepc */
	.word	0x0000040F  /* 00270B2C sync.p */
	.word	0x42000018  /* 00270B30 eret */
	.word	0x03E00008  /* 00270B34 jr $ra */
	.word	0x00000000  /* 00270B38 nop */
	.end	scePcStart

	.section	.text.scePcStop,"ax",@progbits
	.globl	scePcStop
	.ent	scePcStop
scePcStop:  /* 0x00270B40 */
	.word	0x4003C800  /* 00270B40 mfps $v1,0 */
	.word	0x3C028000  /* 00270B44 lui $v0,0x8000 */
	.word	0x00621825  /* 00270B48 or $v1,$v1,$v0 */
	.word	0x00621826  /* 00270B4C xor $v1,$v1,$v0 */
	.word	0x4083C800  /* 00270B50 mtps $v1,0 */
	.word	0x03E00008  /* 00270B54 jr $ra */
	.word	0x00000000  /* 00270B58 nop */
	.end	scePcStop
