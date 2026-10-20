/* Shared data names 002Bxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_002B.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_002B1C60, 0x1200, 16  /* untyped: users disagree: E90 D_002B1C60[][64] | M2C_UNK D_002B1C60 */
	PIECE D_002B6474, 0x4, 4
	PIECE D_002B6478, 0x4, 4
	PIECE D_002B647C, 0x4, 4
	PIECE D_002B6480, 0x4, 4
	PIECE D_002B6484, 0xc, 4
	PIECE D_002B6668, 0x48, 8
	PIECE_BEGIN D_002B66B0, 0x10, 16
	PIECE_BYTES D_002B66B0, 0x0, 0x4
	.word D_002B65F0
	PIECE_BYTES D_002B66B0, 0x8, 0x8
	PIECE_END D_002B66B0, 0x10
	PIECE D_002B6770, 0x4, 4
	PIECE D_002B6774, 0x4, 4
	PIECE D_002B6778, 0x4, 4  /* untyped: users disagree: s32 *D_002B6778 | s32 D_002B6778 | void *D_002B6778; unparsed in 1 file(s) */
	PIECE D_002B677C, 0x4, 4  /* untyped: users disagree: s32 D_002B677C | void *D_002B677C */
	PIECE D_002B7590, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002B7590 | u8 D_002B7590[] */
	PIECE D_002B75A0, 0x20, 16  /* untyped: users disagree: M2C_UNK D_002B75A0 | SemaCb D_002B75A0[2] | s32 D_002B75A0 */
	PIECE_BEGIN D_002BBAA0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002BBAA0 | u8 D_002BBAA0[] */
	PIECE_BYTES D_002BBAA0, 0x0, 0x4
	.word D_002BBA20
	PIECE_BYTES D_002BBAA0, 0x8, 0x8
	PIECE_END D_002BBAA0, 0x10
	PIECE D_002BBAB0, 0x4, 4
	PIECE D_002BBAB4, 0x4, 4
	PIECE D_002BBAB8, 0x4, 4
	PIECE D_002BBABC, 0x4, 4
	PIECE D_002BBAC0, 0x4, 4
	PIECE D_002BBAC4, 0x4, 4
	PIECE D_002BBAC8, 0x8, 8
	PIECE D_002BBAD0, 0x10, 16
	PIECE D_002BBAE0, 0x10, 16
	PIECE D_002BBBA0, 0x10, 16
	PIECE D_002BBD40, 0x8, 8
	PIECE D_002BBD48, 0x48, 8  /* untyped: users disagree: M2C_UNK D_002BBD48 | W29Map *D_002BBD48[] */
	PIECE D_002BBD90, 0x50, 16  /* untyped: users disagree: M2C_UNK D_002BBD90 | s32 D_002BBD90[] */
	PIECE D_002BBDE0, 0x4, 4  /* untyped: users disagree: volatile s32 D_002BBDE0 | volatile u32 D_002BBDE0; unparsed in 1 file(s) */
	PIECE D_002BBDE4, 0x4, 4  /* untyped: users disagree: s32 D_002BBDE4 | u32 D_002BBDE4 */
	PIECE D_002BBDEC, 0x4, 4  /* untyped: users disagree: f32 D_002BBDEC; unparsed in 1 file(s) */
	PIECE D_002BBDF0, 0x4, 4  /* untyped: users disagree: volatile s32 D_002BBDF0 | volatile u32 D_002BBDF0 */
	PIECE D_002BBDF4, 0x4, 4  /* untyped: users disagree: s32 D_002BBDF4 | u32 D_002BBDF4 | volatile s32 D_002BBDF4 | volatile u32 D_002BBDF4 */
	PIECE D_002BBDF8, 0x4, 4  /* untyped: users disagree: volatile s32 D_002BBDF8 | volatile u32 D_002BBDF8 */
	PIECE D_002BBDFC, 0x4, 4  /* untyped: users disagree: f32 D_002BBDFC; unparsed in 5 file(s) */
	PIECE D_002BBE00, 0x4, 4
	PIECE D_002BBE04, 0x4, 4  /* untyped: users disagree: s32 D_002BBE04 | volatile s32 D_002BBE04 */
	PIECE D_002BBE08, 0x4, 4
	PIECE D_002BBE0C, 0x4, 4
	PIECE D_002BBE10, 0x4, 4
	PIECE D_002BBE14, 0x4, 4
	PIECE D_002BBE18, 0x4, 4
	PIECE D_002BBE1C, 0x4, 4
	PIECE D_002BBE20, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBE20 | M53 D_002BBE20 | Mtx52 D_002BBE20 */
	PIECE D_002BBE60, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBE60 | Mtx52 D_002BBE60 */
	PIECE D_002BBEA0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBEA0 | Mtx52 D_002BBEA0 */
	PIECE D_002BBEE0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBEE0 | Mtx52 D_002BBEE0 */
	PIECE D_002BBF20, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBF20 | Mtx52 D_002BBF20 */
	PIECE D_002BBF60, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBF60 | Mtx52 D_002BBF60 | s32 D_002BBF60[4][4] */
	PIECE D_002BBFA0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBFA0 | Mtx D_002BBFA0 | f32 D_002BBFA0[4][4] | u8 D_002BBFA0[] */
	PIECE D_002BBFE0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BBFE0 | f32 D_002BBFE0[4][4] */
	PIECE D_002BC020, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BC020 | s32 D_002BC020[4][4] */
	PIECE D_002BC060, 0x10, 16
	PIECE D_002BC070, 0x10, 16  /* untyped: users disagree: Col D_002BC070 | s32 D_002BC070 | volatile s32 D_002BC070[] */
	PIECE D_002BC090, 0x4, 4
	PIECE D_002BC094, 0x4, 4
	PIECE D_002BC098, 0x4, 4  /* untyped: users disagree: f32 D_002BC098 | s32 D_002BC098 */
	PIECE D_002BC09C, 0x4, 4
	PIECE D_002BC0A0, 0x4, 4
	PIECE D_002BC0A4, 0x4, 4
	PIECE D_002BC0A8, 0x8, 8  /* untyped: users disagree: Fl0A8 D_002BC0A8 | Flags D_002BC0A8 | s32 D_002BC0A8 | u32 D_002BC0A8 */
	PIECE D_002BC0BC, 0x4, 4
	PIECE D_002BC0C0, 0x30, 16  /* untyped: users disagree: B48 D_002BC0C0 | View30 D_002BC0C0 */
	PIECE D_002BC0F0, 0x30, 16  /* untyped: users disagree: B48 D_002BC0F0 | Cam D_002BC0F0 | Cam0 D_002BC0F0 | CamS D_002BC0F0 | S2BC0F0 D_002BC0F0 | View30 D_002BC0F0 | f32 D_002BC0F0[] | s32 D_002BC0F0[] */
	PIECE D_002BC120, 0x4, 4
	PIECE D_002BC124, 0x4, 4
	PIECE D_002BC128, 0x4, 4  /* untyped: users disagree: s32 D_002BC128; unparsed in 1 file(s) */
	PIECE D_002BC12C, 0x4, 4
	PIECE D_002BC130, 0x4, 4
	PIECE D_002BC134, 0x4, 4
	PIECE D_002BC138, 0x4, 4
	PIECE D_002BC13C, 0x4, 4
	PIECE D_002BC140, 0x4, 4  /* untyped: users disagree: s32 D_002BC140 | void *D_002BC140 | volatile s8 *D_002BC140 */
	PIECE D_002BC144, 0x4, 4  /* untyped: users disagree: s32 D_002BC144 | void *D_002BC144 | volatile s8 *D_002BC144 */
	PIECE D_002BC148, 0x28, 8  /* untyped: users disagree: Pair D_002BC148 | s32 D_002BC148[4] */
	PIECE D_002BC190, 0x20, 16  /* untyped: users disagree: M2C_UNK D_002BC190 | f32 D_002BC190[] */
	PIECE D_002BC210, 0x60, 16  /* untyped: users disagree: M2C_UNK D_002BC210 | u8 D_002BC210[] */
	PIECE D_002BC720, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002BC720 | u8 D_002BC720[] */
	PIECE D_002BC730, 0x4, 4
	PIECE D_002BC734, 0x4, 4
	PIECE D_002BC738, 0x4, 4
	PIECE D_002BC740, 0x4, 4
	PIECE D_002BC744, 0xc, 4
	PIECE D_002BCAE0, 0x10, 16
	PIECE D_002BCAF0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BCAF0 | f32 D_002BCAF0[4][4] | u8 D_002BCAF0[] */
	PIECE D_002BCB34, 0xc, 4
	PIECE D_002BCB40, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002BCB40 | f32 D_002BCB40[4] */
	PIECE D_002BCB50, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002BCB50 | f32 D_002BCB50[3] */
	PIECE D_002BCB60, 0x8, 8  /* untyped: users disagree: Ctx *D_002BCB60 | W29Ply *D_002BCB60 | s32 D_002BCB60 | void *D_002BCB60 */
	PIECE D_002BCC1C, 0x4, 4  /* untyped: users disagree: s32 D_002BCC1C; unparsed in 1 file(s) */
	PIECE D_002BCC20, 0x4, 4
	PIECE D_002BCC24, 0x4, 4  /* untyped: users disagree: int D_002BCC24 | s32 D_002BCC24 */
	PIECE D_002BCC90, 0x4, 4
	PIECE D_002BCC94, 0x4, 4
	PIECE D_002BCC98, 0x4, 4
	PIECE D_002BCC9C, 0x4, 4  /* untyped: users disagree: s32 D_002BCC9C | u32 *D_002BCC9C */
	PIECE D_002BCCA0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BCCA0 | u8 D_002BCCA0[] */
	PIECE D_002BCCE0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BCCE0 | char D_002BCCE0[] */
	PIECE D_002BCD60, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002BCD60 | u8 D_002BCD60[] */
	PIECE D_002BCDA0, 0x4, 4  /* untyped: users disagree: Ent40 *D_002BCDA0 | Room *D_002BCDA0 | W29Rec40 *D_002BCDA0 | s32 D_002BCDA0 */
	PIECE D_002BCDA4, 0x4, 4  /* untyped: users disagree: s32 D_002BCDA4 | u32 D_002BCDA4 */
	PIECE D_002BCDA8, 0x4, 4
	PIECE D_002BCDAC, 0x4, 4  /* untyped: users disagree: Room *D_002BCDAC | W29Rec40 *D_002BCDAC | s32 D_002BCDAC */
	PIECE D_002BCDB4, 0x4, 4
	PIECE D_002BCDB8, 0x4, 4
	PIECE D_002BCDBC, 0x4, 4
	PIECE D_002BCDC0, 0x4, 4
	PIECE D_002BCDC4, 0x4, 4
	PIECE D_002BCDC8, 0x10, 8  /* untyped: users disagree: Trip D_002BCDC8 | s32 D_002BCDC8[4] */
	PIECE D_002BCDD8, 0x4, 4
	PIECE D_002BCDDC, 0x4, 4
	PIECE D_002BCDE0, 0x4, 4
	PIECE D_002BCDE4, 0x4, 4
	PIECE D_002BCDE8, 0x4, 4
	PIECE D_002BCDEC, 0x4, 4
	PIECE D_002BCDF0, 0x10, 16
	PIECE D_002BD110, 0x4, 4  /* untyped: users disagree: s32 D_002BD110; unparsed in 1 file(s) */
	PIECE D_002BD114, 0x4, 4  /* untyped: users disagree: volatile s32 D_002BD114; unparsed in 1 file(s) */
	PIECE D_002BD118, 0x4, 4  /* untyped: users disagree: s32 D_002BD118 | u32 D_002BD118 */
	PIECE D_002BD11C, 0x4, 4
	PIECE D_002BD150, 0x10, 16
	PIECE D_002BD160, 0x10, 16
	PIECE D_002BD250, 0x2000, 16  /* untyped: users disagree: M2C_UNK D_002BD250 | s32 D_002BD250[] | u8 D_002BD250[] | void *D_002BD250[] */
