/* Data names 003Exxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003E.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003E0D20, 0x220, 16
	PIECE D_003E0F40, 0x210, 16
	PIECE D_003E1150, 0x190, 16
	PIECE D_003E12E0, 0x9d0, 16
	PIECE D_003E1CB0, 0x1a50, 16
	PIECE D_003E3700, 0x580, 16
	PIECE D_003E3C80, 0x8, 8
	PIECE_BEGIN D_003E3C88, 0x48, 8  /* untyped: merged (a user declares it larger than the next name): D_003E3CB0, D_003E3CB8 */
	PIECE_BYTES D_003E3C88, 0x0, 0x28
	PIECE_LABEL D_003E3C88, D_003E3CB0, 0x28
	PIECE_BYTES D_003E3C88, 0x28, 0x8
	PIECE_LABEL D_003E3C88, D_003E3CB8, 0x30
	PIECE_BYTES D_003E3C88, 0x30, 0x18
	PIECE_END D_003E3C88, 0x48
	PIECE D_003E3CD0, 0x28, 8
	PIECE D_003E3CF8, 0x28, 8  /* data/pieces/D_003E3CF8.h */
	PIECE D_003E3D20, 0x28, 8
	PIECE D_003E3D48, 0x10, 8
	PIECE D_003E3D58, 0x10, 8
	PIECE D_003E3D68, 0x4, 4  /* data/pieces/D_003E3D68.h */
	PIECE D_003E3D6C, 0x4, 4  /* data/pieces/D_003E3D6C.h */
	PIECE D_003E3D70, 0xe0, 16  /* untyped: users disagree: E228 D_003E3D70[] | E3D70 D_003E3D70[] | E3D70c D_003E3D70[] | Rec D_003E3D70[] | S3D70 D_003E3D70[]; session 25: as E3D70 D_003E3D70[]: new warning in text_001e0000_h22.c, text_00210000_b14.c; does not compile in text_00210000_s10_r2_7.c, text_00210000_s7_w16.c +1 */
	PIECE D_003E3E50, 0x808, 8  /* data/pieces/D_003E3E50.h */
	PIECE_BEGIN D_003E4658, 0x42b8, 8  /* untyped: merged (a user declares it larger than the next name): D_003E4658, D_003E4660, D_003E4670, D_003E4680, D_003E4690, D_003E46A0 */
	PIECE_BYTES D_003E4658, 0x0, 0x8
	PIECE_LABEL D_003E4658, D_003E4660, 0x8
	PIECE_BYTES D_003E4658, 0x8, 0x8
	PIECE_LABEL D_003E4658, D_003E4668, 0x10
	PIECE_BYTES D_003E4658, 0x10, 0x8
	PIECE_LABEL D_003E4658, D_003E4670, 0x18
	PIECE_BYTES D_003E4658, 0x18, 0x8
	PIECE_LABEL D_003E4658, D_003E4678, 0x20
	PIECE_BYTES D_003E4658, 0x20, 0x8
	PIECE_LABEL D_003E4658, D_003E4680, 0x28
	PIECE_BYTES D_003E4658, 0x28, 0x8
	PIECE_LABEL D_003E4658, D_003E4688, 0x30
	PIECE_BYTES D_003E4658, 0x30, 0x8
	PIECE_LABEL D_003E4658, D_003E4690, 0x38
	PIECE_BYTES D_003E4658, 0x38, 0x8
	PIECE_LABEL D_003E4658, D_003E4698, 0x40
	PIECE_BYTES D_003E4658, 0x40, 0x8
	PIECE_LABEL D_003E4658, D_003E46A0, 0x48
	PIECE_BYTES D_003E4658, 0x48, 0x8
	PIECE_LABEL D_003E4658, D_003E46A8, 0x50
	PIECE_BYTES D_003E4658, 0x50, 0x10
	PIECE_LABEL D_003E4658, D_003E46B8, 0x60
	PIECE_BYTES D_003E4658, 0x60, 0x1820
	PIECE_LABEL D_003E4658, D_003E5ED8, 0x1880
	PIECE_BYTES D_003E4658, 0x1880, 0x2a36
	PIECE_LABEL D_003E4658, D_003E890E, 0x42b6
	PIECE_BYTES D_003E4658, 0x42b6, 0x2
	PIECE_END D_003E4658, 0x42b8
	PIECE D_003E8910, 0x3c0, 16
	PIECE_BEGIN D_003E8CD0, 0x8, 8  /* untyped: type Glyph is not a common.h basic type */
	.word D_003E46B8
	PIECE_BYTES D_003E8CD0, 0x4, 0x4
	PIECE_END D_003E8CD0, 0x8
	PIECE_BEGIN D_003E8CD8, 0x28, 8  /* untyped: type Glyph is not a common.h basic type */
	.word D_003E4660
	.word D_003E4668
	.word D_003E4670
	.word D_003E4678
	.word D_003E4680
	.word D_003E4688
	.word D_003E4690
	.word D_003E4698
	.word D_003E46A0
	.word D_003E46A8
	PIECE_END D_003E8CD8, 0x28
	PIECE D_003E8D00, 0x4, 4
	PIECE D_003E8D04, 0x24, 4  /* data/pieces/D_003E8D04.h */
	PIECE D_003E8D28, 0x18, 8
	PIECE D_003E8D40, 0xc0, 16
	PIECE D_003E8E00, 0x4, 4
	PIECE D_003E8E04, 0x4, 4
	PIECE D_003E8E08, 0x20, 8  /* untyped: users disagree: P8 D_003E8E08 | S4 D_003E8E08 | S8E08 D_003E8E08 | St14 D_003E8E08 | s32 D_003E8E08 | s32 D_003E8E08[2] | s32 D_003E8E08[] | u8 *D_003E8E08[]; unparsed in 1 file(s); session 25: as s32 D_003E8E08: does not compile in text_00230000_s7.c; code changes in text_001f0000_s12_s12w16.c, text_001f0000_s7_w32.c +2 */
	PIECE D_003E8E28, 0x4, 4  /* untyped: users disagree: E8E28 *D_003E8E28 | Glyph *D_003E8E28 | M2C_UNK *D_003E8E28 | s32 D_003E8E28; session 25: as Glyph *D_003E8E28: does not compile in text_001f0000_s6_17.c, text_001f0000_s12_s12w16.c +3 */
	PIECE D_003E8E2C, 0x4, 4
	PIECE D_003E8E30, 0x270, 16  /* data/pieces/D_003E8E30.h */
	PIECE_BEGIN D_003E90A0, 0x70, 16  /* untyped: merged (a user declares it larger than the next name): D_003E90AC, D_003E9104 */
	PIECE_BYTES D_003E90A0, 0x0, 0xc
	PIECE_LABEL D_003E90A0, D_003E90AC, 0xc
	PIECE_BYTES D_003E90A0, 0xc, 0x58
	PIECE_LABEL D_003E90A0, D_003E9104, 0x64
	PIECE_BYTES D_003E90A0, 0x64, 0xc
	PIECE_END D_003E90A0, 0x70
	PIECE D_003E9110, 0x28, 8  /* untyped: type SmG is not a common.h basic type */
	PIECE D_003E9138, 0x118, 8  /* untyped: type Spr is not a common.h basic type */
	PIECE D_003E9250, 0x3e0, 16  /* untyped: type BigG is not a common.h basic type */
	PIECE D_003E9630, 0x30, 16
	PIECE D_003E9660, 0x8000, 16  /* data/pieces/D_003E9660.h */
