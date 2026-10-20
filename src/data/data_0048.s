/* Data names 0048xxxx as pieces of the user's ELF (phase 4, step 4;
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
	PIECE D_0048BFD8, 0x88, 8  /* untyped: element size does not divide the extent */
	PIECE D_0048C068, 0x80, 8
	PIECE D_0048C0E8, 0x100, 8
	PIECE D_0048C1E8, 0x40, 8
	PIECE D_0048C228, 0xd8, 8
	PIECE D_0048C300, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048C308, 0x88, 8  /* untyped: element size does not divide the extent */
	PIECE D_0048C390, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048C398, 0x80, 8
	PIECE D_0048C418, 0x100, 8
	PIECE D_0048C518, 0x40, 8
	PIECE D_0048C558, 0xd8, 8
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
	PIECE D_0048C770, 0x364, 4
	PIECE D_0048CAE0, 0x48, 8
	PIECE D_0048CB28, 0x48, 8
	PIECE D_0048CB70, 0x48, 8
	PIECE D_0048CBB8, 0x58, 8
	PIECE D_0048CC30, 0x8, 8  /* untyped: users disagree: M2C_UNK D_0048CC30 | char D_0048CC30[] */
	PIECE D_0048CC38, 0x8, 8
	PIECE D_0048CCA0, 0x18, 8
	PIECE D_0048CCB8, 0x10, 8
	PIECE D_0048CCC8, 0x18, 8
	PIECE D_0048CD50, 0x10, 16
	PIECE D_0048CDF0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048CF10, 0x10, 16
	PIECE D_0048CF20, 0x10, 16
	PIECE D_0048CF30, 0x10, 16
	PIECE D_0048CF70, 0x8, 8
	PIECE D_0048CF78, 0x8, 8
	PIECE D_0048CF80, 0x8, 8
	PIECE D_0048CF88, 0x8, 8
	PIECE D_0048CF90, 0x8, 8
	PIECE D_0048CF98, 0x8, 8
	PIECE D_0048CFA0, 0x8, 8
	PIECE D_0048CFA8, 0x8, 8
	PIECE D_0048CFB0, 0x8, 8
	PIECE D_0048CFB8, 0x8, 8
	PIECE D_0048CFC0, 0x8, 8
	PIECE D_0048CFC8, 0x8, 8
	PIECE D_0048CFD0, 0x8, 8
	PIECE D_0048CFD8, 0x8, 8
	PIECE D_0048CFE0, 0x8, 8
	PIECE D_0048CFE8, 0x8, 8
	PIECE D_0048CFF0, 0x8, 8
	PIECE D_0048CFF8, 0x8, 8
	PIECE D_0048D008, 0x8, 8
	PIECE D_0048D010, 0x20, 16
	PIECE D_0048D128, 0x8, 8
	PIECE D_0048D130, 0x10, 16  /* untyped: type Str10 is not a common.h basic type */
	PIECE D_0048D140, 0x18, 8
	PIECE D_0048D158, 0x8, 8
	PIECE D_0048D198, 0x8, 8
	PIECE D_0048D1A0, 0x8, 8
	PIECE D_0048D1A8, 0x10, 8  /* untyped: type Str12 is not a common.h basic type */
	PIECE D_0048D1B8, 0x8, 8
	PIECE D_0048D260, 0x18, 8
	PIECE D_0048D278, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048D2A0, 0x10, 16
	PIECE D_0048D2C8, 0x8, 8
	PIECE D_0048D2D0, 0x8, 8
	PIECE D_0048D2D8, 0x8, 8
	PIECE D_0048D2E0, 0x8, 8
	PIECE D_0048D2E8, 0x8, 8
	PIECE D_0048D2F0, 0x8, 8
	PIECE D_0048D2F8, 0x8, 8
	PIECE D_0048D300, 0x8, 8
	PIECE D_0048D308, 0x8, 8
	PIECE D_0048D310, 0x8, 8
	PIECE D_0048D318, 0x8, 8
	PIECE D_0048D320, 0x8, 8
	PIECE D_0048D328, 0x8, 8
	PIECE D_0048D330, 0x10, 16
	PIECE D_0048D628, 0x10, 8
	PIECE D_0048DC48, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DC58, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DC68, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DC70, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DC80, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DC90, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048DCA0, 0x8, 8
	PIECE D_0048DCA8, 0x8, 8
	PIECE D_0048DCB0, 0x8, 8
	PIECE D_0048DCB8, 0x8, 8
	PIECE D_0048DDA0, 0x8, 8
	PIECE D_0048DDA8, 0x10, 8
	PIECE D_0048DDB8, 0x8, 8
	PIECE D_0048DDC0, 0x8, 8
	PIECE D_0048DDC8, 0x8, 8
	PIECE D_0048DDD0, 0x8, 8
	PIECE D_0048DDD8, 0x8, 8
	PIECE D_0048DDE0, 0x8, 8
	PIECE D_0048DDE8, 0x8, 8
	PIECE D_0048DDF0, 0x10, 16
	PIECE D_0048E398, 0x18, 8
	PIECE D_0048E408, 0x8, 8
	PIECE D_0048E410, 0x8, 8
	PIECE D_0048E418, 0x8, 8
	PIECE D_0048E718, 0x10, 8
	PIECE D_0048E8D4, 0xc, 4
	PIECE D_0048E94C, 0x4, 4
	PIECE D_0048E950, 0x10, 16
	PIECE D_0048E9EC, 0x4, 4
	PIECE D_0048E9F0, 0x10, 16
	PIECE D_0048EA68, 0x4, 4
	PIECE D_0048EA6C, 0x4, 4
	PIECE D_0048FB68, 0x4, 4
	PIECE D_0048FB6C, 0x4, 4
	PIECE D_0048FE18, 0x18, 8
	PIECE D_0048FEA0, 0x50, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048FF10, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0048FFF0, 0x10, 16
