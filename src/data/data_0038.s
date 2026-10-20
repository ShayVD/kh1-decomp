/* Data names 0038xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0038.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00388480, 0x444, 4  /* untyped: users disagree: char *D_00388480[] | s32 D_00388480[] | s8 *D_00388480[] | u8 *D_00388480[] */
	PIECE D_003888C4, 0x400, 4
	PIECE D_00388CC4, 0xfbc, 4  /* untyped: users disagree: M2C_UNK D_00388CC4 | s32 D_00388CC4[] */
	PIECE D_00389C80, 0x10, 16  /* untyped: users disagree: s32 D_00389C80 | u32 D_00389C80; unparsed in 1 file(s) */
	PIECE D_0038ACC4, 0x800, 4
	PIECE D_0038B4C4, 0x1800, 4
	PIECE D_0038CCC4, 0x8, 4  /* untyped: users disagree: s32 D_0038CCC4; unparsed in 1 file(s) */
	PIECE D_0038CCCC, 0x34, 4
	PIECE D_0038CD04, 0x4, 4  /* untyped: users disagree: s32 D_0038CD04; unparsed in 1 file(s) */
	PIECE D_0038CD08, 0x34, 4
	PIECE D_0038CD3C, 0xa0, 4  /* untyped: users disagree: Fx *D_0038CD3C[] | Lt *D_0038CD3C[] | M2C_UNK D_0038CD3C */
	PIECE D_0038CDDC, 0x4, 4
	PIECE D_0038CDE0, 0x4, 4
	PIECE D_0038CDE4, 0x4, 4
	PIECE D_0038CDE8, 0x4, 4
	PIECE D_0038CDEC, 0x4, 4
	PIECE D_0038CDF0, 0x4, 4
	PIECE D_0038CDF4, 0x4, 4
	PIECE D_0038CDF8, 0x8, 8
	PIECE D_0038CE00, 0x4, 4
	PIECE D_0038CE04, 0x20c, 4
	PIECE D_0038D010, 0xc4, 4
	PIECE D_0038D0D4, 0xc, 4
	PIECE D_0038D0E0, 0x80, 16
	PIECE D_0038D160, 0x10, 16
	PIECE D_0038D170, 0xd400, 16  /* untyped: users disagree: E848 D_0038D170[] | E848b D_0038D170[] | Ent D_0038D170[] | KEnt D_0038D170[] | M2C_UNK D_0038D170 | Obj350 D_0038D170[] | VM D_0038D170 | VM D_0038D170[] | VM_c2778 D_0038D170[] | VMa D_0038D170[] | VmE D_0038D170[] */
