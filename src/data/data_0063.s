/* The sound driver's RPC status block D_0063D640 (0x2000 bytes in .bss), as one piece (session 28).
 * Its address is sent to the IOP (text_001e0000_h68.c, D_00633640[0]) and the IOP writes it by DMA,
 * so its fields only work at their offsets from the block: D_0063EE40 (+0x1800, h68/h21's entries),
 * D_0063F248 (+0x1c08) and D_0063F540 (+0x1f00), polled after FlushCache(0). Floated alone, those
 * fields left the block (session 18); as labels of one zero-filled section (like the C bss names:
 * -fdata-sections makes them .data.<name> progbits) they move with it. No game bytes: .space only. */
	.include "include/data/piece.inc"

	.section .data.D_0063D640, "aw", @progbits
	.balign 64
	.globl D_0063D640
	.type D_0063D640, @object
	.size D_0063D640, 0x2000
D_0063D640:
	.space 0x1800
	PIECE_LABEL D_0063D640, D_0063EE40, 0x1800
	.space 0x408
	PIECE_LABEL D_0063D640, D_0063F248, 0x1c08
	.space 0x2f8
	PIECE_LABEL D_0063D640, D_0063F540, 0x1f00
	.space 0x100
	PIECE_END D_0063D640, 0x2000
