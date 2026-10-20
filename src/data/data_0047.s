/* Shared data names 0047xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0047.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00472150, 0x10, 16  /* untyped: users disagree: P8 D_00472150 | V4i52 D_00472150 | s32 D_00472150[] */
	PIECE D_0047A1D0, 0x10, 16  /* untyped: users disagree: P8 D_0047A1D0 | s32 D_0047A1D0[2] */
