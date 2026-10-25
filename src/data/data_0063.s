/* The sound driver's RPC status block D_0063D640 (0x2000 bytes in .bss), as one piece (session 28).
 * Its address is sent to the IOP (text_001e0000_h68.c, D_00633640[0]) and the IOP writes it by DMA,
 * so its fields only work at their offsets from the block: D_0063EE40 (+0x1800, h68/h21's entries),
 * D_0063F248 (+0x1c08) and D_0063F540 (+0x1f00), polled after FlushCache(0). Floated alone, those
 * fields left the block (session 18); as labels of one zero-filled section (like the C bss names:
 * -fdata-sections makes them .data.<name> progbits) they move with it. No game bytes: .space only.
 *
 * Session 86: the piece runs on to 0x0063F740 (0x2100 bytes): it holds the IOP's message buffer
 * D_0063F640 (+0x2000, was bss_0063.c's u8 [256]), whose address RPC 0 also sends. snd_rpc.c's
 * func_001ecb08 reads 24 more 0xB4-byte "entries" after a wildcard loop finds nothing
 * (docs/sound-spec.md 3), up to +0x2118: with the buffer here they keep their distances from the
 * block on the host and in the float build (portability.md rule 12). The last 0x18 bytes (entry 47,
 * the text words D_0063F744 ... D_0063F754) stay outside: a section aligned to 16 or more is padded to
 * 16 by MIPS gas, and 0x2118 would run into D_0063F758. The host gives the piece 0x18 zero bytes after
 * it instead (tools/host/census.py HOST_TAIL; entry 47 cannot match on the PS2 either). */
	.include "include/data/piece.inc"

	.section .data.D_0063D640, "aw", @progbits
	.balign 64
	.globl D_0063D640
	.type D_0063D640, @object
	.size D_0063D640, 0x2100
D_0063D640:
	.space 0x1800
	PIECE_LABEL D_0063D640, D_0063EE40, 0x1800
	.space 0x408
	PIECE_LABEL D_0063D640, D_0063F248, 0x1c08
	.space 0x2f8
	PIECE_LABEL D_0063D640, D_0063F540, 0x1f00
	.space 0x100
	PIECE_LABEL D_0063D640, D_0063F640, 0x2000
	.space 0x100
	PIECE_END D_0063D640, 0x2100
