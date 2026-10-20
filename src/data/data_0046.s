/* Shared data names 0046xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0046.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00467408, 0x4, 4  /* untyped: users disagree: s32 D_00467408 | void *D_00467408 */
	PIECE D_00469F60, 0x30, 16
	PIECE D_0046A03C, 0x4, 4  /* untyped: users disagree: s32 D_0046A03C | u8 *D_0046A03C */
	PIECE D_0046A040, 0x4, 4  /* untyped: users disagree: s32 D_0046A040 | u8 *D_0046A040 */
	PIECE D_0046A044, 0x4, 4  /* untyped: users disagree: s32 D_0046A044 | u8 *D_0046A044 */
	PIECE D_0046A53C, 0x4, 4
	PIECE D_0046A540, 0x4, 4
	PIECE D_0046A544, 0x4, 4
	PIECE D_0046A548, 0x4, 4
	PIECE D_0046A54C, 0x4, 4
	PIECE D_0046A550, 0x4, 4
	PIECE D_0046A554, 0x4, 4
	PIECE D_0046A558, 0x4, 4
	PIECE D_0046A55C, 0x4, 4
	PIECE D_0046A560, 0x8, 8
	PIECE D_0046A5BC, 0x4, 4
	PIECE D_0046A5D8, 0x8, 8
	PIECE D_0046A608, 0x4, 4  /* untyped: users disagree: s32 D_0046A608 | u32 D_0046A608 */
	PIECE D_0046A60C, 0x4, 4
	PIECE D_0046A610, 0x4, 4
	PIECE D_0046A614, 0x4, 4
	PIECE D_0046A618, 0x8, 8
	PIECE D_0046A650, 0x10, 16  /* untyped: users disagree: M2C_UNK D_0046A650 | char D_0046A650[] */
	PIECE D_0046A674, 0x4, 4
	PIECE D_0046A67C, 0x4, 4
	PIECE D_0046A680, 0x8, 8
	PIECE D_0046AE28, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE2C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE30, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE44, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE54, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE58, 0x80, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AED8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEDC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEE0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEE4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEEC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AF10, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AF14, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046BE8C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C1C0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C1C8, 0x40, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C208, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C5D0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C610, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C614, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C61C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C620, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C624, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C628, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C62C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C630, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C634, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C638, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C63C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C640, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C644, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C648, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C654, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C658, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D7D0, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D800, 0x440, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E090, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E094, 0x1c, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
