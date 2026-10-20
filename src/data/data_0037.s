/* Data names 0037xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0037.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00370130, 0x10, 16  /* untyped: users disagree: s32 D_00370130 | void *D_00370130 */
	PIECE D_00370140, 0x30, 16
	PIECE D_00370170, 0x40, 16
	PIECE D_003701B0, 0x10, 16  /* untyped: type PCur is not a common.h basic type */
	PIECE D_003701D0, 0x10, 16  /* untyped: users disagree: FV4 D_003701D0 | M2C_UNK D_003701D0 | f32 D_003701D0[4] | u8 D_003701D0[] */
	PIECE D_003701E0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_003701E0 | PppFVec D_003701E0 | s32 D_003701E0[3] */
	PIECE D_003701F0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_003701F0 | f32 D_003701F0[2] | f32 D_003701F0[3] | f32 D_003701F0[] | u8 D_003701F0[] */
	PIECE D_00372708, 0x8, 8
	PIECE D_00372710, 0x10, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_00372720, 0x10, 16  /* untyped: type SplV4 is not a common.h basic type */
	PIECE D_00372730, 0x10, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_00372740, 0x10, 16  /* untyped: type SplV4 is not a common.h basic type */
	PIECE D_00372760, 0x10, 16
	PIECE D_00372770, 0x20, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_00372790, 0x20, 16
	PIECE D_003727B0, 0x40, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_003727F0, 0x10, 16
	PIECE D_00372800, 0xc0, 16  /* untyped: users disagree: M2C_UNK D_00372800 | f32 D_00372800[16] */
	PIECE D_003728C0, 0x48, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00372908, 0x598, 8
	PIECE D_00372EA0, 0x8, 8
	PIECE D_00372EA8, 0x80, 8  /* untyped: users disagree: M2C_UNK D_00372EA8 | s32 D_00372EA8 | s32 D_00372EA8[] */
	PIECE D_00372F28, 0x8, 8
	PIECE D_00372F30, 0x4, 4  /* untyped: users disagree: s32 D_00372F30 | s32 D_00372F30[] */
	PIECE D_00372F34, 0xcc, 4
	PIECE D_00373000, 0x30, 16
	PIECE D_00373030, 0x30, 16
	PIECE D_00373060, 0x40, 16  /* untyped: type Gs060 is not a common.h basic type */
	PIECE D_003730A0, 0x230, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003732D0, 0x4000, 16
	PIECE D_003772D0, 0x4, 4
	PIECE D_003772D4, 0x4, 4
	PIECE D_003772D8, 0x4, 4
	PIECE D_003772DC, 0x60, 4
	PIECE D_0037733C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377340, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377344, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377348, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037734C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377350, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377354, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377358, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037735C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377360, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377364, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377368, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037736C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377370, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377374, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377378, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037737C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377380, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377384, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377388, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037738C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377390, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377394, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00377398, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0037739C, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773A0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773A4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773A8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773AC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773B0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773B4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773B8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773BC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773C0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773C4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773C8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773CC, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773D0, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773D4, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773D8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773DC, 0x4, 4
	PIECE D_003773E0, 0x4, 4
	PIECE D_003773E4, 0x4, 4
	PIECE D_003773E8, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003773EC, 0xc, 4
	PIECE D_00377648, 0x100, 8  /* untyped: users disagree: s32 D_00377648[]; unparsed in 1 file(s) */
	PIECE_BEGIN D_00377748, 0x100, 8  /* untyped: users disagree: u8 *D_00377748[]; unparsed in 1 file(s) */
	.word D_003773F8
	PIECE_BYTES D_00377748, 0x4, 0xfc
	PIECE_END D_00377748, 0x100
	PIECE D_00377848, 0x1200, 8  /* untyped: type ItTbl is not a common.h basic type */
	PIECE D_0037A128, 0x8, 8
	PIECE D_0037A148, 0x4, 4  /* untyped: users disagree: s32 D_0037A148 | u32 D_0037A148 */
	PIECE D_0037A14C, 0x4, 4
	PIECE D_0037A150, 0x4, 4
	PIECE D_0037A154, 0x4, 4
	PIECE D_0037A158, 0x4, 4
	PIECE D_0037A15C, 0x4, 4
	PIECE D_0037A160, 0x4, 4
	PIECE D_0037A164, 0x4, 4
	PIECE D_0037A168, 0x4, 4
	PIECE D_0037A16C, 0x4, 4  /* untyped: users disagree: Slot *D_0037A16C | Task *D_0037A16C | Task_bfcd8 *D_0037A16C | s32 D_0037A16C | u8 *D_0037A16C */
	PIECE D_0037A170, 0x4, 4  /* untyped: users disagree: RunQ *D_0037A170 | RunQ_bfcd8 *D_0037A170 | u8 *D_0037A170 */
	PIECE D_0037A174, 0x4, 4
	PIECE D_0037A178, 0x18, 8  /* untyped: users disagree: M2C_UNK D_0037A178 | s32 D_0037A178[] | u32 D_0037A178[] */
	PIECE D_0037A190, 0x8, 8
	PIECE_BEGIN D_0037A198, 0x84, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	.word func_001c08e8
	.word func_001cd208
	.word func_001c08f0
	.word func_001c0910
	.word func_001c0960
	.word func_001c0b40
	.word func_001c0968
	.word func_001c09a0
	.word func_001c0b28
	.word func_001c0d20
	.word func_001c0d70
	.word func_001c13b8
	.word func_001c0f30
	.word func_001c13e8
	.word func_001c1118
	.word func_001c1628
	.word func_001c11d8
	.word func_001c1718
	.word func_001c1318
	.word func_001c1320
	.word func_001c1328
	.word func_001c1960
	.word func_001c19f8
	.word func_001c1aa8
	.word func_001dcad0
	.word func_001c1b58
	.word func_001c09e8
	.word func_001c0a38
	.word func_001c0a88
	.word func_001c0ad8
	.word func_001c1330
	.word func_001c1880
	.word D_00490578
	PIECE_END D_0037A198, 0x84
	PIECE D_0037A378, 0x8, 8  /* untyped: users disagree: Bits D_0037A378 | Bits52 D_0037A378 | C2Flags D_0037A378 | Flags D_0037A378 | s32 D_0037A378 | u32 D_0037A378 | volatile s32 D_0037A378; unparsed in 1 file(s) */
	PIECE D_0037A380, 0xe100, 16  /* untyped: users disagree: Cam D_0037A380 | Scn D_0037A380 | u8 D_0037A380[] */
