/* Shared data names 003Bxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003B.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003B4D90, 0x10, 16
	PIECE D_003B4DA0, 0xd400, 16  /* untyped: users disagree: E848 D_003B4DA0[] | E848b D_003B4DA0[] | VM D_003B4DA0[] | VmC D_003B4DA0[] */
