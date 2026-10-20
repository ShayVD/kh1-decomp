/* Shared data names 0048xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0048.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_0048BFD0, 0x8, 8  /* untyped: users disagree: const W29P8 D_0048BFD0 | s32 D_0048BFD0[2] */
	PIECE D_0048CC30, 0x8, 8  /* untyped: users disagree: M2C_UNK D_0048CC30 | char D_0048CC30[] */
	PIECE D_0048CFF8, 0x8, 8
	PIECE D_0048DCB0, 0x8, 8
	PIECE D_0048E410, 0x8, 8
	PIECE D_0048FE18, 0x18, 8
