/* Data names 0030xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0030.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003031F0, 0xff4, 4
	PIECE D_003041E4, 0xc, 4  /* untyped: element size does not divide the extent */
	PIECE D_003042F0, 0x28, 8
	PIECE D_003044A0, 0x10, 16  /* untyped: users disagree: u16 *D_003044A0; unparsed in 1 file(s) */
	PIECE D_003044B0, 0x10, 16
	PIECE D_003044C0, 0x10, 16
	PIECE D_003044D0, 0x8, 8
	PIECE D_003044D8, 0x4, 4  /* untyped: users disagree: C02Slot D_003044D8[] | ColEnt D_003044D8[] | ColEntA D_003044D8[] | Ent52b D_003044D8[] | W29E10 D_003044D8[] | W6Ent16 D_003044D8[] */
	PIECE D_003044DC, 0x4, 4  /* untyped: users disagree: MdlEnt52 D_003044DC[]; unparsed in 2 file(s) */
	PIECE D_003044E0, 0x5f8, 8  /* untyped: users disagree: B3Tbl D_003044E0[] | C02MSlot D_003044E0[] | MdlEnt D_003044E0[] */
	PIECE D_00304AD8, 0x8, 8  /* untyped: users disagree: O15 *D_00304AD8 | W32Obj3 *D_00304AD8 | s32 D_00304AD8 */
	PIECE D_00304AE0, 0x10, 16
	PIECE D_00304AF0, 0x10, 16
	PIECE_BEGIN D_00304B00, 0x20, 16
	.word D_0048DC90
	.word D_0048DC80
	.word D_0048DC70
	.word D_0048DC68
	.word D_0048DC58
	.word D_0048DC48
	PIECE_BYTES D_00304B00, 0x18, 0x8
	PIECE_END D_00304B00, 0x20
	PIECE D_00304B20, 0x10, 16
	PIECE D_00304B30, 0x10, 16
	PIECE D_00304B6C, 0x4, 4  /* untyped: users disagree: s32 D_00304B6C; unparsed in 1 file(s) */
	PIECE D_00304B70, 0x8, 8
	PIECE D_00304B78, 0x4, 4  /* untyped: users disagree: W55Bf D_00304B78 | s32 D_00304B78 | u32 D_00304B78 */
	PIECE D_00304B7C, 0x4, 4
	PIECE D_00304B80, 0x4, 4
	PIECE D_00304B84, 0x4, 4  /* untyped: users disagree: s32 D_00304B84; unparsed in 1 file(s) */
	PIECE D_00304B88, 0x28, 8
	PIECE D_00304BB0, 0x10, 16
	PIECE D_00304BC0, 0x28, 8
	PIECE D_00304BE8, 0x8, 8  /* untyped: users disagree: B3Sv *D_00304BE8 | Base4BE8 *D_00304BE8 | DbSave *D_00304BE8 | E116 *D_00304BE8 | E74 *D_00304BE8 | Ent116 *D_00304BE8 | Ent74 *D_00304BE8 | G3d *D_00304BE8 | G4BE8 *D_00304BE8 | G4BE8c *D_00304BE8 | G4BE8e *D_00304BE8 | G9 *D_00304BE8 | P48E *D_00304BE8 | P491 *D_00304BE8 | P599 *D_00304BE8 | PSave *D_00304BE8 | S304BE8 *D_00304BE8 | S48e *D_00304BE8 | S4BE8 *D_00304BE8 | S9c *D_00304BE8 | Save *D_00304BE8 | Save59 *D_00304BE8 | SaveA *D_00304BE8 | SaveB *D_00304BE8 | SaveE *D_00304BE8 | SaveM *D_00304BE8 | Sv *D_00304BE8 | SvE *D_00304BE8 | Sys *D_00304BE8 | Tbl4BE8 *D_00304BE8 | W17 *D_00304BE8 | W32Save *D_00304BE8 | W34Save *D_00304BE8 | W5 *D_00304BE8 | W606Save *D_00304BE8 | W6Save *D_00304BE8 | W7Save *D_00304BE8 | W8Save *D_00304BE8 | s32 D_00304BE8 | u8 *D_00304BE8 | void *D_00304BE8; unparsed in 3 file(s) */
	PIECE D_00304C18, 0x28, 8
	PIECE D_00304C40, 0x8, 8
	PIECE D_00304C48, 0x28, 8
	PIECE D_00304C70, 0xe4, 4  /* untyped: users disagree: M2C_UNK D_00304C70 | St6C D_00304C70 | T16s D_00304C70 | W7Lv D_00304C70 | u8 D_00304C70[] */
	PIECE D_00304D54, 0xc, 4
	PIECE D_00304D60, 0x4, 4  /* untyped: type W606F8 is not a common.h basic type */
	PIECE D_00304D64, 0x4c, 4  /* untyped: users disagree: B3F2 D_00304D64[] | volatile M2C_UNK D_00304D64 */
	PIECE D_00304DB0, 0x8c, 4  /* untyped: users disagree: B3PjInf D_00304DB0[] | HtTab D_00304DB0[] */
	PIECE D_00304E3C, 0x4, 4
	PIECE D_00306840, 0x4, 4
	PIECE D_00306844, 0x4, 4
	PIECE D_00306848, 0x8, 8
	PIECE D_00306850, 0x9d6, 2  /* untyped: type B3SeRow is not a common.h basic type */
	PIECE D_00307226, 0x13b2, 2
	PIECE D_003085D8, 0x277, 1  /* untyped: element size does not divide the extent */
	PIECE D_0030884F, 0x25, 1
	PIECE D_00308C70, 0x6c, 4
	PIECE D_00308CDC, 0x4, 4  /* untyped: users disagree: B4G *D_00308CDC | C01Tbl *D_00308CDC | Cfg *D_00308CDC | D20 *D_00308CDC | G1 *D_00308CDC | S308CDC *D_00308CDC | S8CDC *D_00308CDC | W32Prm *D_00308CDC | W6Lim *D_00308CDC | W9Cfg *D_00308CDC | s32 D_00308CDC | u32 *D_00308CDC | void *D_00308CDC; unparsed in 2 file(s) */
