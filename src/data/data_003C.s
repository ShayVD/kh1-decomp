/* Data names 003Cxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003C.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003C21A0, 0x8, 8
	PIECE D_003C21A8, 0xb88, 8  /* untyped: users disagree: s32 D_003C21A8[] | u8 *D_003C21A8[] */
	PIECE D_003C2D30, 0xc78, 8
	PIECE D_003C39A8, 0x4, 4
	PIECE D_003C39AC, 0x4, 4
	PIECE D_003C39B0, 0x40, 16
	PIECE D_003C39F0, 0x40, 16
	PIECE D_003C3A30, 0x40, 16
	PIECE D_003C3A70, 0x1a80, 16  /* untyped: users disagree: E848 D_003C3A70[] | E848b D_003C3A70[] | Obj350 D_003C3A70[] | VM D_003C3A70[] */
	PIECE D_003C54F0, 0x10, 16
	PIECE D_003C5500, 0x10, 16
	PIECE D_003C55E0, 0x4, 4  /* untyped: users disagree: f32 D_003C55E0 | u8 D_003C55E0[]; unparsed in 2 file(s) */
	PIECE D_003C55E4, 0x4, 4
	PIECE D_003C55E8, 0x8, 8
	PIECE D_003C55F4, 0x4, 4
	PIECE D_003C55F8, 0x38, 8
	PIECE D_003C5630, 0x4, 4
	PIECE D_003C5634, 0xc, 4
	PIECE D_003C5640, 0x10, 16
	PIECE D_003C5650, 0x10, 16
	PIECE D_003C5660, 0x20, 16
	PIECE D_003C5680, 0x20, 16
	PIECE D_003C56A0, 0x20, 16
	PIECE D_003C56C0, 0x30, 16
	PIECE D_003C56F0, 0x38, 8
	PIECE D_003C5728, 0x28, 8
	PIECE D_003C5750, 0x30, 16
	PIECE D_003C5780, 0x30, 16
	PIECE D_003C57B0, 0x30, 16
	PIECE D_003C57E0, 0x28, 8
	PIECE D_003C5808, 0x28, 8
	PIECE D_003C5830, 0x40, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_003C5870, 0x20, 16
	PIECE D_003C5890, 0x8, 8
	PIECE D_003C58E0, 0x13f00, 16
