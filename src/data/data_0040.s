/* Data names 0040xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0040.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_0040EF80, 0x16c00, 16  /* untyped: src/hand/text_00220000_h25.c does not compile with it (type u128 is not a common.h basic type) */
