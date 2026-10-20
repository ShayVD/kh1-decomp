/* Data names 002Exxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_002E.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_002E26A0, 0xc, 4  /* untyped: users disagree: Act *D_002E26A0[] | Act D_002E26A0[] | ActD0 *D_002E26A0 | Actor *D_002E26A0 | B3Ob *D_002E26A0[] | B4Ent *D_002E26A0 | C01Ply *D_002E26A0[3] | ChrEA *D_002E26A0[3] | Ent *D_002E26A0 | M2C_UNK D_002E26A0 | M2C_UNK D_002E26A0[] | Obj123 *D_002E26A0[] | Obj70 *D_002E26A0[] | ObjBD40 *D_002E26A0[] | P26A0 D_002E26A0 | Pair20 D_002E26A0 | Pl *D_002E26A0 | Pl1557d0 *D_002E26A0[] | Pl57_0ec8 *D_002E26A0 | S26A0 D_002E26A0 | Src *D_002E26A0[3] | W55Ob *D_002E26A0[] | W55Pl *D_002E26A0[] | W606O26a0 *D_002E26A0 | W7Obj *D_002E26A0[] | W9Ent *D_002E26A0 | s32 D_002E26A0 | u32 *D_002E26A0[] | u8 *D_002E26A0 | void *D_002E26A0 | void *D_002E26A0[3] | void *D_002E26A0[]; unparsed in 3 file(s) */
	PIECE D_002E26AC, 0x4, 4  /* untyped: users disagree: Obj1200 *D_002E26AC | void *D_002E26AC */
	PIECE D_002E26B0, 0x10, 16  /* untyped: type V53 is not a common.h basic type */
	PIECE D_002E26C0, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002E26C0 | M53 D_002E26C0 | f32 D_002E26C0[4][4] | u8 D_002E26C0[] */
	PIECE D_002E2700, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002E2700 | M53 D_002E2700 | f32 D_002E2700[] | u8 D_002E2700[] | volatile M2C_UNK D_002E2700 */
	PIECE D_002E2740, 0x40, 16  /* untyped: users disagree: M2C_UNK D_002E2740 | M53 D_002E2740 | volatile M2C_UNK D_002E2740 */
	PIECE D_002E2780, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002E2780 | V3 D_002E2780 | V4 D_002E2780 | V53 D_002E2780 | Vec D_002E2780 | Vec3 D_002E2780 | f32 D_002E2780[4] | f32 D_002E2780[] | u8 D_002E2780[] */
	PIECE D_002E2790, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002E2790 | V3 D_002E2790 | V4 D_002E2790 | V53 D_002E2790 | Vec D_002E2790 | f32 D_002E2790[4] | f32 D_002E2790[] | u8 D_002E2790[] */
	PIECE D_002E27A0, 0x4, 4
	PIECE D_002E27A4, 0x4, 4  /* untyped: users disagree: f32 D_002E27A4 | s32 D_002E27A4 */
	PIECE D_002E27A8, 0x4, 4
	PIECE D_002E27AC, 0x14, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_002E27C0, 0x8, 8  /* untyped: type Pair8 is not a common.h basic type */
	PIECE D_002E27C8, 0x4, 4  /* untyped: users disagree: C01Flg27C8 D_002E27C8 | F27c8 D_002E27C8 | Flg13 D_002E27C8 | u32 D_002E27C8 | u8 D_002E27C8 */
	PIECE D_002E27CC, 0x4, 4  /* untyped: users disagree: f32 D_002E27CC; unparsed in 1 file(s) */
	PIECE D_002E27D0, 0x4, 4  /* untyped: users disagree: f32 D_002E27D0; unparsed in 1 file(s) */
	PIECE D_002E27D4, 0xc, 4  /* untyped: users disagree: s32 D_002E27D4; unparsed in 1 file(s) */
	PIECE D_002E27E0, 0x10, 16
	PIECE D_002E27F0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_002E2800, 0x10, 16
	PIECE_BEGIN D_002E2F20, 0x8, 8
	.word D_002E2810
	.word D_00362340
	PIECE_END D_002E2F20, 0x8
	PIECE D_002E2F28, 0xc, 4  /* untyped: users disagree: G18 D_002E2F28 | M2C_UNK D_002E2F28 */
	PIECE D_002E2F34, 0x84, 4
	PIECE D_002E2FB8, 0x17, 1
	PIECE D_002E2FCF, 0x9, 1
	PIECE D_002E2FEC, 0x24, 4  /* untyped: users disagree: M2C_UNK D_002E2FEC; unparsed in 1 file(s) */
	PIECE D_002E3010, 0x70, 16  /* untyped: users disagree: Q5 D_002E3010; unparsed in 1 file(s) */
	PIECE D_002E3080, 0x38, 8  /* untyped: type L5 is not a common.h basic type */
	PIECE D_002E30B8, 0x38, 8  /* untyped: users disagree: D18 D_002E30B8 | Q8 D_002E30B8 */
	PIECE D_002E30F0, 0x48, 8  /* untyped: type D17 is not a common.h basic type */
	PIECE D_002E3138, 0x28, 8
	PIECE D_002E3160, 0x8, 8
	PIECE D_002E3168, 0x8, 8  /* untyped: users disagree: s32 D_002E3168 | u32 D_002E3168 */
	PIECE D_002E3170, 0x20, 16  /* untyped: users disagree: It17 *D_002E3170[] | M2C_UNK D_002E3170 | Q8 *D_002E3170[8] | Q8 *D_002E3170[] | Spr *D_002E3170[] */
	PIECE D_002E3194, 0x8, 4
	PIECE D_002E319C, 0x4, 4  /* untyped: users disagree: O8 *D_002E319C | u16 *D_002E319C */
	PIECE D_002E31A0, 0x4, 4  /* untyped: users disagree: O8 *D_002E31A0 | S31a0 *D_002E31A0 */
	PIECE D_002E31A4, 0x4, 4  /* untyped: users disagree: s32 D_002E31A4 | u8 *D_002E31A4 */
	PIECE D_002E31A8, 0x8, 8  /* untyped: users disagree: s32 D_002E31A8 | u32 D_002E31A8 */
	PIECE D_002E31B0, 0x8, 8  /* untyped: users disagree: B4Pair D_002E31B0 | LockEA D_002E31B0 | M2C_UNK D_002E31B0 | P8 D_002E31B0 | S31b0 D_002E31B0 | V8 D_002E31B0 | s32 D_002E31B0 | s32 D_002E31B0[2] | u8 D_002E31B0[] */
	PIECE D_002E31B8, 0x4, 4  /* untyped: users disagree: s32 D_002E31B8 | u32 D_002E31B8 */
	PIECE D_002E31BC, 0x2c, 4
	PIECE D_002E31E8, 0x8, 8
	PIECE D_002E31F0, 0x20000, 16
