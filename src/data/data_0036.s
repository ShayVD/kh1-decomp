/* Data names 0036xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0036.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00360F30, 0x1410, 16
	PIECE_BEGIN D_00362340, 0xb0, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	.word func_00176898
	PIECE_BYTES D_00362340, 0x4, 0x4
	.word func_001768a0
	PIECE_BYTES D_00362340, 0xc, 0x4
	.word func_001768a8
	PIECE_BYTES D_00362340, 0x14, 0x4
	.word func_001768c8
	PIECE_BYTES D_00362340, 0x1c, 0x4
	.word func_001768e8
	PIECE_BYTES D_00362340, 0x24, 0x4
	.word func_00176a60
	PIECE_BYTES D_00362340, 0x2c, 0x4
	.word func_00176a80
	PIECE_BYTES D_00362340, 0x34, 0x4
	.word func_001768b0
	PIECE_BYTES D_00362340, 0x3c, 0x4
	.word func_00176920
	PIECE_BYTES D_00362340, 0x44, 0x4
	.word func_00176940
	PIECE_BYTES D_00362340, 0x4c, 0x4
	.word func_00176960
	PIECE_BYTES D_00362340, 0x54, 0x4
	.word func_001769f0
	PIECE_BYTES D_00362340, 0x5c, 0x4
	.word func_00176b20
	PIECE_BYTES D_00362340, 0x64, 0x4
	.word func_00176aa0
	PIECE_BYTES D_00362340, 0x6c, 0x4
	.word func_00176af0
	PIECE_BYTES D_00362340, 0x74, 0x4
	.word func_00176a18
	PIECE_BYTES D_00362340, 0x7c, 0x4
	.word func_00176b50
	PIECE_BYTES D_00362340, 0x84, 0x4
	.word func_00176b68
	PIECE_BYTES D_00362340, 0x8c, 0x4
	.word func_001768b8
	PIECE_BYTES D_00362340, 0x94, 0x4
	.word func_001768c0
	PIECE_BYTES D_00362340, 0x9c, 0x4
	.word func_00176b80
	PIECE_BYTES D_00362340, 0xa4, 0xc
	PIECE_END D_00362340, 0xb0
	PIECE D_003623F0, 0x4, 4
	PIECE D_003623F4, 0x4, 4
	PIECE D_003623F8, 0x8, 8
	PIECE D_00362400, 0x10, 16
	PIECE D_00362410, 0x10, 16
	PIECE D_00362420, 0x4, 4
	PIECE D_00362424, 0x4, 4  /* data/pieces/D_00362424.h */
	PIECE D_00362428, 0x4, 4  /* data/pieces/D_00362428.h */
	PIECE D_0036242C, 0x4, 4  /* data/pieces/D_0036242C.h */
	PIECE D_00362430, 0x4, 4  /* untyped: users disagree: Box *D_00362430 | E30 *D_00362430 | s32 D_00362430; session 25: as Box *D_00362430: new warning in text_00170000_h11.c */
	PIECE D_00362434, 0x4, 4  /* data/pieces/D_00362434.h */
	PIECE D_00362438, 0x4, 4  /* untyped: users disagree: P1c *D_00362438 | Path *D_00362438 | PathB *D_00362438 | Rec20 *D_00362438 | S18 *D_00362438 | s32 D_00362438 | void *D_00362438; unparsed in 1 file(s); session 25: as Path *D_00362438: does not compile in text_00170000_s6_10.c, text_00170000_s7_w2.c +2; new warning in text_s7_w27.c */
	PIECE D_0036243C, 0x4, 4  /* data/pieces/D_0036243C.h */
	PIECE D_00362440, 0x4, 4
	PIECE D_00362444, 0x4, 4
	PIECE D_00362448, 0x4, 4
	PIECE D_0036244C, 0x4, 4  /* data/pieces/D_0036244C.h */
	PIECE D_00362450, 0x4, 4  /* data/pieces/D_00362450.h */
	PIECE D_00362454, 0x4, 4  /* data/pieces/D_00362454.h */
	PIECE D_00362458, 0x4, 4  /* untyped: type Fn8 is not a common.h basic type */
	PIECE_BEGIN D_0036245C, 0x5c, 4  /* data/pieces/D_0036245C.h */
	PIECE_BYTES D_0036245C, 0x0, 0x4
	.word func_00178ef8
	PIECE_BYTES D_0036245C, 0x8, 0x4
	.word func_00179700
	.word func_00179690
	.word func_00179ee8
	PIECE_BYTES D_0036245C, 0x18, 0x4
	.word func_0017a510
	PIECE_BYTES D_0036245C, 0x20, 0x4
	.word func_0017a6c0
	PIECE_BYTES D_0036245C, 0x28, 0x4
	.word func_0017a7b0
	PIECE_BYTES D_0036245C, 0x30, 0x4
	.word func_0017df08
	PIECE_BYTES D_0036245C, 0x38, 0x4
	.word func_0017a958
	PIECE_BYTES D_0036245C, 0x40, 0x4
	.word func_0017d5d0
	PIECE_BYTES D_0036245C, 0x48, 0x4
	.word func_0017dd00
	PIECE_BYTES D_0036245C, 0x50, 0x4
	.word func_00179a80
	PIECE_BYTES D_0036245C, 0x58, 0x4
	PIECE_END D_0036245C, 0x5c
	PIECE D_003624B8, 0x4, 4
	PIECE D_003624BC, 0x4, 4
	PIECE D_003624C0, 0x4, 4
	PIECE D_003624C4, 0x4, 4
	PIECE D_003624C8, 0x4, 4
	PIECE D_003624CC, 0x4, 4
	PIECE D_003624D0, 0x4, 4
	PIECE D_003624D4, 0xc, 4
	PIECE D_003624E0, 0x10, 16  /* data/pieces/D_003624E0.h */
	PIECE D_003624F0, 0x10, 16  /* data/pieces/D_003624F0.h */
	PIECE D_00362500, 0x10, 16
	PIECE D_00362510, 0x10, 16  /* data/pieces/D_00362510.h */
	PIECE D_00362520, 0x10, 16
	PIECE D_00362530, 0x10, 16  /* data/pieces/D_00362530.h */
	PIECE D_00362540, 0x10, 16  /* data/pieces/D_00362540.h */
	PIECE D_00362550, 0x10, 16
	PIECE D_00362560, 0x10, 16  /* data/pieces/D_00362560.h */
	PIECE D_00362570, 0x10, 16  /* data/pieces/D_00362570.h */
	PIECE D_00362580, 0x10, 16  /* data/pieces/D_00362580.h */
	PIECE D_00362590, 0x10, 16  /* data/pieces/D_00362590.h */
	PIECE D_003625A0, 0x10, 16  /* data/pieces/D_003625A0.h */
	PIECE D_003625B0, 0x10, 16  /* data/pieces/D_003625B0.h */
	PIECE D_003625C0, 0x10, 16  /* data/pieces/D_003625C0.h */
	PIECE D_003625D0, 0x10, 16  /* data/pieces/D_003625D0.h */
	PIECE D_003625E0, 0x4, 4
	PIECE D_003625E4, 0xc, 4
	PIECE D_003625F0, 0x10, 16  /* data/pieces/D_003625F0.h */
	PIECE D_00362600, 0x10, 16  /* data/pieces/D_00362600.h */
	PIECE D_00362610, 0x10, 16
	PIECE D_00362620, 0x10, 16  /* data/pieces/D_00362620.h */
	PIECE D_00362630, 0x10, 16  /* data/pieces/D_00362630.h */
	PIECE D_00362640, 0x20, 16  /* data/pieces/D_00362640.h */
	PIECE_BEGIN D_00362660, 0x10, 16  /* merged (a user declares it larger than the next name): D_0036266C; data/pieces/D_00362660.h */
	PIECE_BYTES D_00362660, 0x0, 0xc
	PIECE_LABEL D_00362660, D_0036266C, 0xc
	PIECE_BYTES D_00362660, 0xc, 0x4
	PIECE_END D_00362660, 0x10
	PIECE_BEGIN D_00362670, 0x10, 16  /* merged (a user declares it larger than the next name): D_00362674; data/pieces/D_00362670.h */
	PIECE_BYTES D_00362670, 0x0, 0x4
	PIECE_LABEL D_00362670, D_00362674, 0x4
	PIECE_BYTES D_00362670, 0x4, 0xc
	PIECE_END D_00362670, 0x10
	PIECE_BEGIN D_00362680, 0x10, 16  /* merged (a user declares it larger than the next name): D_00362684, D_0036268C; data/pieces/D_00362680.h */
	PIECE_BYTES D_00362680, 0x0, 0x4
	PIECE_LABEL D_00362680, D_00362684, 0x4
	PIECE_BYTES D_00362680, 0x4, 0x8
	PIECE_LABEL D_00362680, D_0036268C, 0xc
	PIECE_BYTES D_00362680, 0xc, 0x4
	PIECE_END D_00362680, 0x10
	PIECE_BEGIN D_00362690, 0x30, 16  /* merged (a user declares it larger than the next name): D_003626A0, D_003626B0; data/pieces/D_00362690.h */
	PIECE_BYTES D_00362690, 0x0, 0x10
	PIECE_LABEL D_00362690, D_003626A0, 0x10
	PIECE_BYTES D_00362690, 0x10, 0x10
	PIECE_LABEL D_00362690, D_003626B0, 0x20
	PIECE_BYTES D_00362690, 0x20, 0x10
	PIECE_END D_00362690, 0x30
	PIECE D_003626C0, 0x30, 16  /* untyped: users disagree: M2C_UNK D_003626C0 | S26C0 D_003626C0; session 25: as S26C0 D_003626C0: does not compile in text_00170000_h61.c */
	PIECE D_003626F0, 0x8, 8  /* data/pieces/D_003626F0.h */
	PIECE D_003626F8, 0xc, 4  /* data/pieces/D_003626F8.h */
	PIECE D_00362704, 0x4, 4
	PIECE D_00362708, 0x4, 4
	PIECE D_0036270C, 0x4, 4
	PIECE D_00362710, 0x4, 4  /* data/pieces/D_00362710.h */
	PIECE D_00362714, 0x4, 4
	PIECE D_00362718, 0x4, 4
	PIECE D_0036271C, 0x4, 4
	PIECE D_00362720, 0x4, 4
	PIECE D_00362724, 0x4, 4
	PIECE D_00362728, 0x4, 4
	PIECE D_0036272C, 0x4, 4
	PIECE D_00362730, 0x1200, 16  /* untyped: users disagree: H39Slot D_00362730[]; unparsed in 1 file(s); session 25: as H39Slot D_00362730[]: code changes in text_00170000_s6_10.c */
	PIECE D_00363930, 0x400, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00363D30, 0x400, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00364130, 0xc000, 16  /* untyped: users disagree: E0C0 D_00364130[256] | H39Obj D_00364130[256] | M2C_UNK D_00364130 | PObj D_00364130[256] | PppMng D_00364130[256]; unparsed in 1 file(s); session 25: as H39Obj D_00364130[256]: does not compile in text_00180000_3.c, text_00170000_s6_10.c +2; no file-scope extern in text_00180000_b07.c */
