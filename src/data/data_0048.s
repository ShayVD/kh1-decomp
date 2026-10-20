/* Shared data names 0048xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0048.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE_BEGIN D_00482260, 0x30, 16  /* untyped: users disagree: s32 D_00482260[] | u8 D_00482260[] */
	PIECE_BYTES D_00482260, 0x0, 0x4
	.word D_0048C300
	PIECE_BYTES D_00482260, 0x8, 0xc
	.word D_0048C390
	PIECE_BYTES D_00482260, 0x18, 0xc
	.word D_004862B0
	PIECE_BYTES D_00482260, 0x28, 0x8
	PIECE_END D_00482260, 0x30
	PIECE D_0048BFD0, 0x8, 8  /* untyped: users disagree: const W29P8 D_0048BFD0 | s32 D_0048BFD0[2] */
	PIECE_BEGIN D_0048C630, 0x60, 16  /* untyped: users disagree: Blk32 D_0048C630 | Tpl52 D_0048C630 | s32 D_0048C630[] */
	PIECE_BYTES D_0048C630, 0x0, 0x4
	.word D_00487B80
	PIECE_BYTES D_0048C630, 0x8, 0xc
	.word D_0048BFD0
	PIECE_BYTES D_0048C630, 0x18, 0xc
	.word D_0048C060
	PIECE_BYTES D_0048C630, 0x28, 0xc
	.word D_004862A0
	PIECE_BYTES D_0048C630, 0x38, 0xc
	.word D_004862A0
	PIECE_BYTES D_0048C630, 0x48, 0x18
	PIECE_END D_0048C630, 0x60
	PIECE_BEGIN D_0048C690, 0x60, 16  /* untyped: users disagree: Blk32 D_0048C690 | Tpl52 D_0048C690 | s32 D_0048C690[] */
	PIECE_BYTES D_0048C690, 0x0, 0x4
	.word D_00487B80
	PIECE_BYTES D_0048C690, 0x8, 0xc
	.word D_0048C300
	PIECE_BYTES D_0048C690, 0x18, 0xc
	.word D_0048C390
	PIECE_BYTES D_0048C690, 0x28, 0xc
	.word D_004862A0
	PIECE_BYTES D_0048C690, 0x38, 0xc
	.word D_004862A0
	PIECE_BYTES D_0048C690, 0x48, 0x18
	PIECE_END D_0048C690, 0x60
	PIECE_BEGIN D_0048C6F0, 0x80, 16  /* untyped: users disagree: V4i52 D_0048C6F0[] | s32 D_0048C6F0[] | s32 D_0048C6F0[][4] */
	PIECE_BYTES D_0048C6F0, 0x0, 0x4
	.word D_00486360
	PIECE_BYTES D_0048C6F0, 0x8, 0xc
	.word D_00487B80
	PIECE_BYTES D_0048C6F0, 0x18, 0xc
	.word D_00486FF0
	PIECE_BYTES D_0048C6F0, 0x28, 0xc
	.word D_00488880
	PIECE_BYTES D_0048C6F0, 0x38, 0xc
	.word D_00489730
	PIECE_BYTES D_0048C6F0, 0x48, 0xc
	.word D_0048A2F0
	PIECE_BYTES D_0048C6F0, 0x58, 0xc
	.word D_0048A540
	PIECE_BYTES D_0048C6F0, 0x68, 0xc
	.word D_0048B2D0
	PIECE_BYTES D_0048C6F0, 0x78, 0x8
	PIECE_END D_0048C6F0, 0x80
	PIECE D_0048CC30, 0x8, 8  /* untyped: users disagree: M2C_UNK D_0048CC30 | char D_0048CC30[] */
	PIECE D_0048CFF8, 0x8, 8
	PIECE D_0048DCB0, 0x8, 8
	PIECE D_0048E410, 0x8, 8
	PIECE D_0048FE18, 0x18, 8
