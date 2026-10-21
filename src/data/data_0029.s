/* Data names 0029xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0029.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_0029B140, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_0029B170, 0x10, 16
	PIECE_BYTES D_0029B170, 0x0, 0x4
	.word D_0029B140
	PIECE_BYTES D_0029B170, 0x8, 0x8
	PIECE_END D_0029B170, 0x10
	PIECE D_0029B180, 0x40, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_0029B1C0, 0x10, 16
	PIECE_BYTES D_0029B1C0, 0x0, 0x4
	.word D_0029B180
	PIECE_BYTES D_0029B1C0, 0x8, 0x8
	PIECE_END D_0029B1C0, 0x10
	PIECE D_0029B1D0, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_0029B200, 0x10, 16
	PIECE_BYTES D_0029B200, 0x0, 0x4
	.word D_0029B1D0
	PIECE_BYTES D_0029B200, 0x8, 0x8
	PIECE_END D_0029B200, 0x10
	PIECE D_0029B210, 0x50, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_0029B260, 0x10, 16
	PIECE_BYTES D_0029B260, 0x0, 0x4
	.word D_0029B210
	PIECE_BYTES D_0029B260, 0x8, 0x8
	PIECE_END D_0029B260, 0x10
	PIECE D_0029B270, 0x10, 16
	PIECE D_0029B280, 0x70, 16  /* untyped: users disagree: M2C_UNK D_0029B280 | f32 D_0029B280[4][4] | f32 D_0029B280[] | s32 D_0029B280[4][4] | u8 D_0029B280[]; session 25: as s32 D_0029B280[4][4]: new warning in text_00110000_s6_02.c */
	PIECE D_0029B2F0, 0x4, 4
	PIECE D_0029B2F4, 0x4, 4
	PIECE D_0029B2F8, 0x4, 4
	PIECE D_0029B2FC, 0x4, 4
	PIECE D_0029B300, 0x10, 16
	PIECE D_0029B310, 0x100, 16  /* data/pieces/D_0029B310.h */
	PIECE D_0029B410, 0x4, 4
	PIECE D_0029B414, 0x4, 4
	PIECE D_0029B418, 0x4, 4
	PIECE D_0029B41C, 0x4, 4
	PIECE D_0029B420, 0xa00, 16  /* untyped: users disagree: Blk160 D_0029B420[] | Tex D_0029B420[]; session 25: as Tex D_0029B420[]: does not compile in text_00100000_s7_w4.c */
	PIECE D_0029BE20, 0x8000, 16
