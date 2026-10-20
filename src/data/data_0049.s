/* Shared data names 0049xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0049.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00490AE0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_00490AE0 | u8 D_00490AE0[] */
	PIECE D_004919B0, 0x8, 8  /* untyped: users disagree: M2C_UNK D_004919B0 | char D_004919B0[] */
	PIECE D_00491A18, 0x108, 8
	PIECE D_00491FC8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491FE0, 0xc8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492380, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492830, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00494028, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
