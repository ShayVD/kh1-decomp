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
	PIECE D_003E3CF8, 0x28, 8  /* untyped: users disagree: M2C_UNK D_003E3CF8 | s32 D_003E3CF8[] */
	PIECE D_003E3D20, 0x28, 8
	PIECE D_003E3D48, 0x10, 8
	PIECE D_003E3D58, 0x10, 8
	PIECE D_003E3D68, 0x4, 4  /* untyped: users disagree: int D_003E3D68 | s32 D_003E3D68 | u32 D_003E3D68 | unsigned int D_003E3D68 */
	PIECE D_003E3D6C, 0x4, 4  /* untyped: users disagree: s32 D_003E3D6C | u32 D_003E3D6C */
	PIECE D_003E3D70, 0xe0, 16  /* untyped: users disagree: E228 D_003E3D70[] | E3D70 D_003E3D70[] | E3D70c D_003E3D70[] | Rec D_003E3D70[] | S3D70 D_003E3D70[] */
	PIECE D_003E3E50, 0x808, 8  /* untyped: users disagree: M2C_UNK D_003E3E50 | RecE0 D_003E3E50[] */
	PIECE D_003E4658, 0x8, 8
	PIECE D_003E4660, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4668, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4670, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4678, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4680, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4688, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4690, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E4698, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E46A0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E46A8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E46B8, 0x1820, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003E5ED8, 0x2a36, 2  /* untyped: users disagree: M2C_UNK D_003E5ED8 | u8 D_003E5ED8[] */
	PIECE D_003E890E, 0x2, 2
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
	PIECE D_003E8D04, 0x24, 4  /* untyped: users disagree: s32 D_003E8D04[]; unparsed in 1 file(s) */
	PIECE D_003E8D28, 0x18, 8
	PIECE D_003E8D40, 0xc0, 16
	PIECE D_003E8E00, 0x4, 4
	PIECE D_003E8E04, 0x4, 4
	PIECE D_003E8E08, 0x20, 8  /* untyped: users disagree: P8 D_003E8E08 | S4 D_003E8E08 | S8E08 D_003E8E08 | St14 D_003E8E08 | s32 D_003E8E08 | s32 D_003E8E08[2] | s32 D_003E8E08[] | u8 *D_003E8E08[]; unparsed in 1 file(s) */
	PIECE D_003E8E28, 0x4, 4  /* untyped: users disagree: E8E28 *D_003E8E28 | Glyph *D_003E8E28 | M2C_UNK *D_003E8E28 | s32 D_003E8E28 */
	PIECE D_003E8E2C, 0x4, 4
	PIECE D_003E8E30, 0x270, 16  /* untyped: users disagree: E8E30 D_003E8E30[] | u32 D_003E8E30[][12]; unparsed in 1 file(s) */
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
	PIECE D_003E9660, 0x8000, 16  /* untyped: users disagree: M2C_UNK D_003E9660 | Q D_003E9660[] */
