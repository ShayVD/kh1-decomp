/* Data names 0035xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0035.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00350CE0, 0x8, 8  /* untyped: users disagree: M2C_UNK *D_00350CE0 | s32 D_00350CE0 */
	PIECE D_00350CE8, 0x28, 8  /* untyped: users disagree: s32 D_00350CE8[] | void *D_00350CE8[] */
	PIECE D_00350D18, 0x10, 8
	PIECE D_00350D28, 0x8, 8
	PIECE D_00350D30, 0x48, 8  /* untyped: type W9Tab12 is not a common.h basic type */
	PIECE D_00350D78, 0x4, 4  /* untyped: users disagree: BoxSet57_f1b8 *D_00350D78 | W34Boxes *D_00350D78 */
	PIECE D_00350D7C, 0x4, 4
	PIECE D_00350D80, 0x8, 8
	PIECE D_00350D88, 0xc, 4  /* untyped: users disagree: M2C_UNK D_00350D88 | MvTab D_00350D88[] | S88 D_00350D88[] | Tb20 D_00350D88[] | W55Ent32 D_00350D88[] | W9Tab32 D_00350D88[] | s8 D_00350D88 | volatile M2C_UNK D_00350D88 */
	PIECE D_00350D94, 0xc, 4  /* untyped: users disagree: M2C_UNK D_00350D94; unparsed in 1 file(s) */
	PIECE D_00350DA0, 0x4, 4  /* untyped: type Handler is not a common.h basic type */
	PIECE D_00350DA4, 0x744, 4  /* untyped: type W7Fn is not a common.h basic type */
	PIECE D_003514E8, 0x48, 8  /* untyped: type Kind57_15d0 is not a common.h basic type */
	PIECE D_00351530, 0x400, 16  /* untyped: users disagree: H1530 D_00351530[] | u16 D_00351530[512] */
	PIECE D_00351930, 0xc, 4  /* untyped: type W9F4 is not a common.h basic type */
	PIECE D_0035193C, 0x34, 4  /* untyped: type W34Tbl is not a common.h basic type */
	PIECE D_00351990, 0x20, 16
	PIECE D_003519B0, 0x30, 16
	PIECE D_003519E0, 0x20, 16  /* untyped: users disagree: S3519E0 D_003519E0 | s32 D_003519E0[] */
	PIECE D_00351A00, 0x10, 16
	PIECE D_00351A10, 0x10, 16
	PIECE D_00351A20, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_00351A30, 0x10, 16  /* untyped: users disagree: P2 D_00351A30[] | u8 D_00351A30[] */
	PIECE D_00351A40, 0x8, 8
	PIECE D_00351A48, 0x8, 8  /* untyped: users disagree: s32 D_00351A48; unparsed in 1 file(s) */
	PIECE D_00351A50, 0x10, 16
	PIECE D_00351A60, 0x10, 16
	PIECE D_00351A70, 0x10, 16
	PIECE D_00351A80, 0x10, 16
	PIECE D_00351A90, 0x10, 16
	PIECE D_00351AA0, 0x10, 16
	PIECE D_00351AB0, 0x10, 16
	PIECE D_00351AC0, 0x8, 8
	PIECE D_00351AC8, 0x50, 8
	PIECE D_00351B18, 0x8, 8
	PIECE D_00351B20, 0x40, 16
	PIECE D_00351B60, 0x28, 8
	PIECE D_00351B88, 0x28, 8
	PIECE D_00351BB0, 0x10, 16
	PIECE D_00351BC0, 0x4, 4  /* untyped: users disagree: s32 D_00351BC0 | volatile s32 D_00351BC0 */
	PIECE D_00351BC4, 0x4, 4  /* untyped: users disagree: s32 D_00351BC4 | volatile s32 D_00351BC4 */
	PIECE_BEGIN D_00351BC8, 0x8, 8  /* untyped: users disagree: void *D_00351BC8; unparsed in 4 file(s) */
	.word func_002583e0
	.word func_00258a58
	PIECE_END D_00351BC8, 0x8
	PIECE D_00351BD0, 0x10, 16
	PIECE D_00351E50, 0x9030, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0035AF20, 0x20, 16  /* untyped: users disagree: u8 D_0035AF20; unparsed in 1 file(s) */
	PIECE D_0035AF40, 0x114, 4  /* untyped: users disagree: f32 D_0035AF40; unparsed in 1 file(s) */
	PIECE D_0035B054, 0xc2c, 4  /* untyped: users disagree: f32 D_0035B054; unparsed in 1 file(s) */
	PIECE D_0035BCA8, 0x8, 8
	PIECE D_0035BCB0, 0x8, 8
	PIECE D_0035BCC8, 0x28, 8
	PIECE D_0035BCF0, 0x20, 16
	PIECE D_0035BD10, 0x10, 16
	PIECE D_0035BD20, 0x20, 16  /* untyped: type V4E3 is not a common.h basic type */
	PIECE D_0035BD40, 0x10, 16  /* untyped: users disagree: Act6C *D_0035BD40[] | Chr *D_0035BD40[] | Chr9F *D_0035BD40[] | ChrE3 *D_0035BD40[3] | ChrEA *D_0035BD40[3] | EntB *D_0035BD40[] | M2C_UNK D_0035BD40 | ObjBD40 *D_0035BD40[] | s32 D_0035BD40 | s32 D_0035BD40[] | void *D_0035BD40[] */
	PIECE D_0035BE40, 0x10, 16
	PIECE D_0035C080, 0x10, 16
	PIECE D_0035C130, 0x10, 16
	PIECE D_0035C1E0, 0x10, 16
	PIECE D_0035C2B0, 0x10, 16
	PIECE D_0035C350, 0x10, 16
	PIECE D_0035C410, 0x10, 16
	PIECE D_0035C420, 0x4, 4
	PIECE D_0035C424, 0x4, 4
	PIECE D_0035C428, 0x4, 4
	PIECE D_0035C42C, 0x4, 4
	PIECE D_0035C430, 0x10, 16  /* untyped: type Q16 is not a common.h basic type */
	PIECE D_0035C440, 0x10, 16  /* untyped: users disagree: f32 D_0035C440[4] | u8 D_0035C440[] */
	PIECE D_0035C450, 0x10, 16  /* untyped: type Q16 is not a common.h basic type */
	PIECE D_0035C460, 0x10, 16  /* untyped: users disagree: f32 D_0035C460[4] | u8 D_0035C460[] */
	PIECE D_0035C470, 0x10, 16
	PIECE D_0035C480, 0x10, 16
	PIECE D_0035C490, 0x10, 16  /* untyped: users disagree: V4 D_0035C490 | u8 D_0035C490[] */
	PIECE D_0035C660, 0x90, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_0035C6F0, 0x4, 4
	PIECE D_0035C6F4, 0x4, 4
	PIECE D_0035C6F8, 0x4, 4
	PIECE D_0035C6FC, 0x4, 4
	PIECE D_0035C700, 0x10, 16
	PIECE D_0035C710, 0x2000, 16  /* untyped: users disagree: B3PjE D_0035C710[] | M2C_UNK D_0035C710 | PppLight D_0035C710[256] | Spr D_0035C710[] | W8Ent35 D_0035C710[] */
	PIECE D_0035E710, 0x1410, 16  /* untyped: users disagree: M2C_UNK D_0035E710 | PppTbl D_0035E710 */
	PIECE D_0035FB20, 0x1410, 16
