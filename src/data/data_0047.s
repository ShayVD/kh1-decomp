/* Shared data names 0047xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0047.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00472150, 0x10, 16  /* untyped: users disagree: P8 D_00472150 | V4i52 D_00472150 | s32 D_00472150[] */
	PIECE_BEGIN D_00472190, 0x40, 16  /* untyped: users disagree: E16 D_00472190[] | Ent32 D_00472190[] | s32 D_00472190[] */
	PIECE_BYTES D_00472190, 0x0, 0x4
	.word D_004862A0
	PIECE_BYTES D_00472190, 0x8, 0xc
	.word D_004862A0
	PIECE_BYTES D_00472190, 0x18, 0xc
	.word D_004862A0
	PIECE_BYTES D_00472190, 0x28, 0xc
	.word D_004862A0
	PIECE_BYTES D_00472190, 0x38, 0x8
	PIECE_END D_00472190, 0x40
	PIECE_BEGIN D_004761D0, 0x40, 16  /* untyped: users disagree: E16 D_004761D0[] | s32 D_004761D0[] | s8 D_004761D0 */
	PIECE_BYTES D_004761D0, 0x0, 0x4
	.word D_004862A0
	PIECE_BYTES D_004761D0, 0x8, 0xc
	.word D_004862A0
	PIECE_BYTES D_004761D0, 0x18, 0xc
	.word D_004862A0
	PIECE_BYTES D_004761D0, 0x28, 0xc
	.word D_004862A0
	PIECE_BYTES D_004761D0, 0x38, 0x8
	PIECE_END D_004761D0, 0x40
	PIECE D_0047A1D0, 0x10, 16  /* untyped: users disagree: P8 D_0047A1D0 | s32 D_0047A1D0[2] */
	PIECE_BEGIN D_0047A210, 0x40, 16  /* untyped: users disagree: E16 D_0047A210[] | s32 D_0047A210[] */
	PIECE_BYTES D_0047A210, 0x0, 0x4
	.word D_004862A0
	PIECE_BYTES D_0047A210, 0x8, 0xc
	.word D_004862A0
	PIECE_BYTES D_0047A210, 0x18, 0xc
	.word D_004862A0
	PIECE_BYTES D_0047A210, 0x28, 0xc
	.word D_004862A0
	PIECE_BYTES D_0047A210, 0x38, 0x8
	PIECE_END D_0047A210, 0x40
	PIECE_BEGIN D_0047E220, 0x30, 16  /* untyped: users disagree: s32 D_0047E220[] | u8 D_0047E220[] */
	PIECE_BYTES D_0047E220, 0x0, 0x4
	.word D_0048BFD0
	PIECE_BYTES D_0047E220, 0x8, 0xc
	.word D_0048C060
	PIECE_BYTES D_0047E220, 0x18, 0xc
	.word D_004862B0
	PIECE_BYTES D_0047E220, 0x28, 0x8
	PIECE_END D_0047E220, 0x30
