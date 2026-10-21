/* Shared data names 0043xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0043.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_004305B0, 0x1770, 16  /* untyped: users disagree: Tex1440 D_004305B0 | u8 D_004305B0[] */
	PIECE D_00431D20, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00431D20 | M2C_UNK D_00431D20 | u8 D_00431D20[] */
	PIECE D_00431D50, 0x1e0, 16  /* untyped: users disagree: Fnt D_00431D50[] | GsTexHdr D_00431D50[10] */
	PIECE D_00431F30, 0xea64, 4  /* data/pieces/D_00431F30.h */
