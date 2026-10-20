/* Shared data names 0037xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0037.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00370130, 0x10, 16  /* untyped: users disagree: s32 D_00370130 | void *D_00370130 */
	PIECE D_003701B0, 0x10, 16  /* untyped: type PCur is not a common.h basic type */
	PIECE D_003701D0, 0x10, 16  /* untyped: users disagree: FV4 D_003701D0 | M2C_UNK D_003701D0 | f32 D_003701D0[4] | u8 D_003701D0[] */
	PIECE D_003701E0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_003701E0 | PppFVec D_003701E0 | s32 D_003701E0[3] */
	PIECE D_003701F0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_003701F0 | f32 D_003701F0[2] | f32 D_003701F0[3] | f32 D_003701F0[] | u8 D_003701F0[] */
	PIECE D_00372770, 0x20, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_00372790, 0x20, 16
	PIECE D_00372800, 0xc0, 16  /* untyped: users disagree: M2C_UNK D_00372800 | f32 D_00372800[16] */
	PIECE D_003728C0, 0x48, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00372908, 0x598, 8
	PIECE D_00372EA0, 0x8, 8
	PIECE D_00372EA8, 0x80, 8  /* untyped: users disagree: M2C_UNK D_00372EA8 | s32 D_00372EA8 | s32 D_00372EA8[] */
	PIECE D_00372F28, 0x8, 8
	PIECE D_00372F30, 0x4, 4  /* untyped: users disagree: s32 D_00372F30 | s32 D_00372F30[] */
	PIECE D_003730A0, 0x230, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003732D0, 0x4000, 16
	PIECE D_003772D0, 0x4, 4
	PIECE D_003772DC, 0x60, 4
	PIECE D_003773EC, 0xc, 4
	PIECE D_00377648, 0x100, 8  /* untyped: users disagree: s32 D_00377648[]; unparsed in 1 file(s) */
	PIECE D_0037A128, 0x8, 8
	PIECE D_0037A148, 0x4, 4  /* untyped: users disagree: s32 D_0037A148 | u32 D_0037A148 */
	PIECE D_0037A150, 0x4, 4
	PIECE D_0037A154, 0x4, 4
	PIECE D_0037A15C, 0x4, 4
	PIECE D_0037A160, 0x4, 4
	PIECE D_0037A164, 0x4, 4
	PIECE D_0037A168, 0x4, 4
	PIECE D_0037A16C, 0x4, 4  /* untyped: users disagree: Slot *D_0037A16C | Task *D_0037A16C | Task_bfcd8 *D_0037A16C | s32 D_0037A16C | u8 *D_0037A16C */
	PIECE D_0037A170, 0x4, 4  /* untyped: users disagree: RunQ *D_0037A170 | RunQ_bfcd8 *D_0037A170 | u8 *D_0037A170 */
	PIECE D_0037A174, 0x4, 4
	PIECE D_0037A178, 0x18, 8  /* untyped: users disagree: M2C_UNK D_0037A178 | s32 D_0037A178[] | u32 D_0037A178[] */
	PIECE D_0037A190, 0x8, 8
	PIECE D_0037A378, 0x8, 8  /* untyped: users disagree: Bits D_0037A378 | Bits52 D_0037A378 | C2Flags D_0037A378 | Flags D_0037A378 | s32 D_0037A378 | u32 D_0037A378 | volatile s32 D_0037A378; unparsed in 1 file(s) */
	PIECE D_0037A380, 0xe100, 16  /* untyped: users disagree: Cam D_0037A380 | Scn D_0037A380 | u8 D_0037A380[] */
