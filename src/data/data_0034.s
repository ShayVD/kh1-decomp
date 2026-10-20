/* Data names 0034xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0034.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00348CE0, 0x8000, 16
