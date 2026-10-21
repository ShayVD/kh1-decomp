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
	PIECE D_00350D94, 0xc, 4  /* data/pieces/D_00350D94.h */
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
	PIECE D_00351A48, 0x8, 8  /* data/pieces/D_00351A48.h */
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
	PIECE D_00351BC0, 0x4, 4  /* data/pieces/D_00351BC0.h */
	PIECE D_00351BC4, 0x4, 4  /* data/pieces/D_00351BC4.h */
	PIECE_BEGIN D_00351BC8, 0x8, 8  /* untyped: users disagree: void *D_00351BC8; unparsed in 4 file(s) */
	.word func_002583e0
	.word func_00258a58
	PIECE_END D_00351BC8, 0x8
	PIECE D_00351BD0, 0x10, 16
	PIECE D_00351C40, 0x1d0, 16
	PIECE_BEGIN D_00351E10, 0x9070, 16  /* merged (a user declares it larger than the next name): D_00351E50; data/pieces/D_00351E10.h */
	PIECE_BYTES D_00351E10, 0x0, 0x40
	PIECE_LABEL D_00351E10, D_00351E50, 0x40
	PIECE_BYTES D_00351E10, 0x40, 0x9030
	PIECE_END D_00351E10, 0x9070
	PIECE_BEGIN D_0035AE80, 0xe00, 16  /* merged (a user declares it larger than the next name): D_0035AF20, D_0035AF40, D_0035B054; data/pieces/D_0035AE80.h */
	PIECE_BYTES D_0035AE80, 0x0, 0xa0
	PIECE_LABEL D_0035AE80, D_0035AF20, 0xa0
	PIECE_BYTES D_0035AE80, 0xa0, 0x20
	PIECE_LABEL D_0035AE80, D_0035AF40, 0xc0
	PIECE_BYTES D_0035AE80, 0xc0, 0x114
	PIECE_LABEL D_0035AE80, D_0035B054, 0x1d4
	PIECE_BYTES D_0035AE80, 0x1d4, 0xc2c
	PIECE_END D_0035AE80, 0xe00
	PIECE D_0035BCA8, 0x8, 8
	PIECE D_0035BCB0, 0x8, 8
	PIECE_BEGIN D_0035BCB8, 0x10, 8  /* untyped: type C03Act is not a common.h basic type */
	PIECE_BYTES D_0035BCB8, 0x0, 0x8
	.word func_00171c80
	PIECE_BYTES D_0035BCB8, 0xc, 0x4
	PIECE_END D_0035BCB8, 0x10
	PIECE D_0035BCC8, 0x28, 8
	PIECE D_0035BCF0, 0x20, 16
	PIECE D_0035BD10, 0x10, 16
	PIECE D_0035BD20, 0x20, 16  /* untyped: type V4E3 is not a common.h basic type */
	PIECE D_0035BD40, 0x10, 16  /* untyped: users disagree: Act6C *D_0035BD40[] | Chr *D_0035BD40[] | Chr9F *D_0035BD40[] | ChrE3 *D_0035BD40[3] | ChrEA *D_0035BD40[3] | EntB *D_0035BD40[] | M2C_UNK D_0035BD40 | ObjBD40 *D_0035BD40[] | s32 D_0035BD40 | s32 D_0035BD40[] | void *D_0035BD40[] */
	PIECE_BEGIN D_0035BD50, 0xf0, 16
	PIECE_BYTES D_0035BD50, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035BD50, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BD50, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BD50, 0x2c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035BD50, 0x3c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035BD50, 0x4c, 0xc
	.word func_0016c480
	PIECE_BYTES D_0035BD50, 0x5c, 0xc
	.word func_0016c650
	PIECE_BYTES D_0035BD50, 0x6c, 0xc
	.word func_0016cb98
	PIECE_BYTES D_0035BD50, 0x7c, 0xc
	.word func_0016ce10
	PIECE_BYTES D_0035BD50, 0x8c, 0xc
	.word func_0016d040
	PIECE_BYTES D_0035BD50, 0x9c, 0xc
	.word func_0016d2d0
	PIECE_BYTES D_0035BD50, 0xac, 0xc
	.word func_0016d768
	PIECE_BYTES D_0035BD50, 0xbc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BD50, 0xcc, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035BD50, 0xdc, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035BD50, 0xec, 0x4
	PIECE_END D_0035BD50, 0xf0
	PIECE D_0035BE40, 0x10, 16
	PIECE_BEGIN D_0035BE50, 0x170, 16
	PIECE_BYTES D_0035BE50, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x2c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x3c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x4c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x5c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035BE50, 0x6c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035BE50, 0x7c, 0xc
	.word func_00172df8
	PIECE_BYTES D_0035BE50, 0x8c, 0xc
	.word func_00172f00
	PIECE_BYTES D_0035BE50, 0x9c, 0xc
	.word func_00173008
	PIECE_BYTES D_0035BE50, 0xac, 0xc
	.word func_00172118
	PIECE_BYTES D_0035BE50, 0xbc, 0xc
	.word func_001722e8
	PIECE_BYTES D_0035BE50, 0xcc, 0xc
	.word func_00172690
	PIECE_BYTES D_0035BE50, 0xdc, 0xc
	.word func_00172810
	PIECE_BYTES D_0035BE50, 0xec, 0xc
	.word func_00172998
	PIECE_BYTES D_0035BE50, 0xfc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x10c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BE50, 0x11c, 0xc
	.word func_001730f0
	PIECE_BYTES D_0035BE50, 0x12c, 0xc
	.word func_00172bc8
	PIECE_BYTES D_0035BE50, 0x13c, 0xc
	.word func_001724b8
	PIECE_BYTES D_0035BE50, 0x14c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035BE50, 0x15c, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035BE50, 0x16c, 0x4
	PIECE_END D_0035BE50, 0x170
	PIECE_BEGIN D_0035BFC0, 0xc0, 16
	PIECE_BYTES D_0035BFC0, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035BFC0, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BFC0, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BFC0, 0x2c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035BFC0, 0x3c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035BFC0, 0x4c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035BFC0, 0x5c, 0xc
	.word func_00173758
	PIECE_BYTES D_0035BFC0, 0x6c, 0xc
	.word func_00173860
	PIECE_BYTES D_0035BFC0, 0x7c, 0xc
	.word func_00173968
	PIECE_BYTES D_0035BFC0, 0x8c, 0xc
	.word func_00173a20
	PIECE_BYTES D_0035BFC0, 0x9c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035BFC0, 0xac, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035BFC0, 0xbc, 0x4
	PIECE_END D_0035BFC0, 0xc0
	PIECE D_0035C080, 0x10, 16
	PIECE_BEGIN D_0035C090, 0xa0, 16
	PIECE_BYTES D_0035C090, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035C090, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C090, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C090, 0x2c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C090, 0x3c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035C090, 0x4c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035C090, 0x5c, 0xc
	.word func_00173af0
	PIECE_BYTES D_0035C090, 0x6c, 0xc
	.word func_00173bf8
	PIECE_BYTES D_0035C090, 0x7c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035C090, 0x8c, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035C090, 0x9c, 0x4
	PIECE_END D_0035C090, 0xa0
	PIECE D_0035C130, 0x10, 16
	PIECE_BEGIN D_0035C140, 0xa0, 16
	PIECE_BYTES D_0035C140, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035C140, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C140, 0x1c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035C140, 0x2c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035C140, 0x3c, 0xc
	.word func_00173d00
	PIECE_BYTES D_0035C140, 0x4c, 0xc
	.word func_00173ec0
	PIECE_BYTES D_0035C140, 0x5c, 0xc
	.word func_00173f78
	PIECE_BYTES D_0035C140, 0x6c, 0xc
	.word func_00174030
	PIECE_BYTES D_0035C140, 0x7c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035C140, 0x8c, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035C140, 0x9c, 0x4
	PIECE_END D_0035C140, 0xa0
	PIECE D_0035C1E0, 0x10, 16
	PIECE_BEGIN D_0035C1F0, 0xc0, 16
	PIECE_BYTES D_0035C1F0, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035C1F0, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C1F0, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C1F0, 0x2c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035C1F0, 0x3c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035C1F0, 0x4c, 0xc
	.word func_001743b0
	PIECE_BYTES D_0035C1F0, 0x5c, 0xc
	.word func_001744b8
	PIECE_BYTES D_0035C1F0, 0x6c, 0xc
	.word func_00174570
	PIECE_BYTES D_0035C1F0, 0x7c, 0xc
	.word func_00174628
	PIECE_BYTES D_0035C1F0, 0x8c, 0xc
	.word func_001746e0
	PIECE_BYTES D_0035C1F0, 0x9c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035C1F0, 0xac, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035C1F0, 0xbc, 0x4
	PIECE_END D_0035C1F0, 0xc0
	PIECE D_0035C2B0, 0x10, 16
	PIECE_BEGIN D_0035C2C0, 0x90, 16
	PIECE_BYTES D_0035C2C0, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035C2C0, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C2C0, 0x1c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035C2C0, 0x2c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035C2C0, 0x3c, 0xc
	.word func_00174798
	PIECE_BYTES D_0035C2C0, 0x4c, 0xc
	.word func_00174968
	PIECE_BYTES D_0035C2C0, 0x5c, 0xc
	.word func_00174a20
	PIECE_BYTES D_0035C2C0, 0x6c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035C2C0, 0x7c, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035C2C0, 0x8c, 0x4
	PIECE_END D_0035C2C0, 0x90
	PIECE D_0035C350, 0x10, 16
	PIECE_BEGIN D_0035C360, 0xb0, 16
	PIECE_BYTES D_0035C360, 0x0, 0x8
	.word func_0016b670
	PIECE_BYTES D_0035C360, 0xc, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C360, 0x1c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C360, 0x2c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C360, 0x3c, 0xc
	.word func_0016b670
	PIECE_BYTES D_0035C360, 0x4c, 0xc
	.word func_0016bb68
	PIECE_BYTES D_0035C360, 0x5c, 0xc
	.word func_0016bfe8
	PIECE_BYTES D_0035C360, 0x6c, 0xc
	.word func_00174db0
	PIECE_BYTES D_0035C360, 0x7c, 0xc
	.word func_00174eb8
	PIECE_BYTES D_0035C360, 0x8c, 0xc
	.word func_0016db80
	PIECE_BYTES D_0035C360, 0x9c, 0xc
	.word func_0016dd30
	PIECE_BYTES D_0035C360, 0xac, 0x4
	PIECE_END D_0035C360, 0xb0
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
	PIECE_BEGIN D_0035C4A0, 0x1c0, 16  /* merged (a user declares it larger than the next name): D_0035C550; data/pieces/D_0035C4A0.h */
	PIECE_BYTES D_0035C4A0, 0x0, 0xb0
	PIECE_LABEL D_0035C4A0, D_0035C550, 0xb0
	PIECE_BYTES D_0035C4A0, 0xb0, 0x110
	PIECE_END D_0035C4A0, 0x1c0
	PIECE D_0035C660, 0x90, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_0035C6F0, 0x4, 4
	PIECE D_0035C6F4, 0x4, 4
	PIECE D_0035C6F8, 0x4, 4
	PIECE D_0035C6FC, 0x4, 4
	PIECE D_0035C700, 0x10, 16
	PIECE D_0035C710, 0x2000, 16  /* untyped: users disagree: B3PjE D_0035C710[] | M2C_UNK D_0035C710 | PppLight D_0035C710[256] | Spr D_0035C710[] | W8Ent35 D_0035C710[] */
	PIECE D_0035E710, 0x1410, 16  /* untyped: users disagree: M2C_UNK D_0035E710 | PppTbl D_0035E710 */
	PIECE D_0035FB20, 0x1410, 16
