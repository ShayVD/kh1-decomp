/* Shared data names 0045xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0045.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00451040, 0x33f0, 16  /* untyped: users disagree: Blob D_00451040 | M2C_UNK D_00451040 | u8 D_00451040[] */
	PIECE D_00454A24, 0x8, 4  /* untyped: users disagree: s32 D_00454A24; unparsed in 1 file(s) */
	PIECE D_0045FAC0, 0x5be0, 16  /* untyped: users disagree: E930 D_0045FAC0[10] | Fx D_0045FAC0[10] | volatile M2C_UNK D_0045FAC0 */
