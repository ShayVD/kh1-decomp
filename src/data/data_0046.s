/* Data names 0046xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0046.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_004656A0, 0x930, 16
	PIECE D_00465FD0, 0x1b0, 16
	PIECE D_00466180, 0x630, 16
	PIECE D_004667B0, 0x630, 16
	PIECE D_00466DE0, 0x570, 16
	PIECE D_00467350, 0x38, 8
	PIECE D_00467388, 0x10, 8
	PIECE D_00467398, 0x28, 8
	PIECE D_004673C0, 0x28, 8
	PIECE D_004673E8, 0x20, 8
	PIECE D_00467408, 0x4, 4  /* untyped: users disagree: s32 D_00467408 | void *D_00467408 */
	PIECE D_0046740C, 0x4, 4
	PIECE D_00467410, 0xe10, 16
	PIECE D_00468220, 0xbf0, 16
	PIECE D_00468E10, 0xe10, 16
	PIECE D_00469C20, 0x28, 8
	PIECE D_00469C48, 0x28, 8
	PIECE D_00469C70, 0x24, 4
	PIECE D_00469C94, 0x4, 4
	PIECE D_00469C98, 0x8, 8
	PIECE D_00469CA0, 0x2b0, 16
	PIECE D_00469F50, 0x10, 16
	PIECE D_00469F60, 0x30, 16
	PIECE D_00469F90, 0x10, 16
	PIECE D_00469FA0, 0x10, 16
	PIECE D_00469FB0, 0x18, 8  /* untyped: type PsmEnt is not a common.h basic type */
	PIECE D_0046A038, 0x4, 4  /* untyped: type Prm is not a common.h basic type */
	PIECE D_0046A03C, 0x4, 4  /* untyped: users disagree: s32 D_0046A03C | u8 *D_0046A03C */
	PIECE D_0046A040, 0x4, 4  /* untyped: users disagree: s32 D_0046A040 | u8 *D_0046A040 */
	PIECE D_0046A044, 0x4, 4  /* untyped: users disagree: s32 D_0046A044 | u8 *D_0046A044 */
	PIECE_BEGIN D_0046A048, 0x10, 8
	PIECE_BYTES D_0046A048, 0x0, 0x8
	.word func_0024d1c8
	PIECE_BYTES D_0046A048, 0xc, 0x4
	PIECE_END D_0046A048, 0x10
	PIECE D_0046A070, 0x10, 16
	PIECE D_0046A0C0, 0x8, 8
	PIECE D_0046A0C8, 0x4a, 2  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046A112, 0x96, 2
	PIECE D_0046A1A8, 0x4a, 2  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046A1F2, 0x96, 2
	PIECE D_0046A288, 0x4a, 2  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046A2D2, 0x96, 2
	PIECE D_0046A368, 0x4a, 2  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046A3B2, 0x96, 2
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
	PIECE_BEGIN D_0046A568, 0x18, 8  /* untyped: users disagree: E *D_0046A568[] | u32 *D_0046A568[] */
	.word D_0046A0C8
	.word D_0046A1A8
	.word D_0046A288
	.word D_0046A368
	.word D_0046A448
	PIECE_BYTES D_0046A568, 0x14, 0x4
	PIECE_END D_0046A568, 0x18
	PIECE D_0046A580, 0x8, 8
	PIECE D_0046A588, 0x8, 8
	PIECE D_0046A590, 0x8, 8
	PIECE D_0046A598, 0x8, 8
	PIECE D_0046A5A0, 0x8, 8
	PIECE D_0046A5A8, 0x14, 4
	PIECE D_0046A5BC, 0x4, 4
	PIECE D_0046A5C0, 0x10, 16
	PIECE D_0046A5D8, 0x8, 8
	PIECE D_0046A608, 0x4, 4  /* untyped: users disagree: s32 D_0046A608 | u32 D_0046A608 */
	PIECE D_0046A60C, 0x4, 4
	PIECE D_0046A610, 0x4, 4
	PIECE D_0046A614, 0x4, 4
	PIECE D_0046A618, 0x8, 8
	PIECE D_0046A620, 0x8, 8
	PIECE D_0046A628, 0x18, 8  /* untyped: users disagree: M2C_UNK D_0046A628 | char D_0046A628[] */
	PIECE D_0046A640, 0x10, 16
	PIECE D_0046A650, 0x10, 16  /* untyped: users disagree: M2C_UNK D_0046A650 | char D_0046A650[] */
	PIECE D_0046A660, 0x14, 4
	PIECE D_0046A674, 0x4, 4
	PIECE D_0046A678, 0x4, 4
	PIECE D_0046A67C, 0x4, 4
	PIECE D_0046A680, 0x8, 8
	PIECE D_0046A6AC, 0x4, 4
	PIECE D_0046A6B0, 0x28, 8
	PIECE_BEGIN D_0046A9C8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	.word D_0046A6D8
	PIECE_BYTES D_0046A9C8, 0x4, 0x4
	PIECE_END D_0046A9C8, 0x8
	PIECE D_0046A9D0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046ADD8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046ADE0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046ADE8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046ADF0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046ADF8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE00, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE28, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE2C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE30, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE40, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE44, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE4C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_0046AE50, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	.word func_00259468
	PIECE_END D_0046AE50, 0x4
	PIECE D_0046AE54, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AE58, 0x80, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AED8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEDC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEE0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEE4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEEC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AEF8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AF10, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046AF14, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046BE20, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046BE88, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046BE8C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C1C0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C1C8, 0x40, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C208, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C4E0, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C500, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C510, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C530, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C550, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C580, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C590, 0x40, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C5D0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C5D8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C610, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C614, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C618, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
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
	PIECE D_0046C64C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C650, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C654, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C658, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C680, 0x80, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046C700, 0x1000, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D700, 0xc0, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D7C0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D7D0, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046D800, 0x440, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046DC40, 0x408, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E048, 0x48, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E090, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E094, 0x1c, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E0B0, 0x50, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0046E100, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
