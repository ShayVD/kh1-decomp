/* Shared data names 003Fxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003F.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003F1A60, 0x4, 4
	PIECE D_003F1A64, 0x4, 4
	PIECE D_003F1A68, 0x8, 8  /* untyped: users disagree: s32 D_003F1A68; unparsed in 1 file(s) */
	PIECE D_003F1A70, 0x400, 16  /* untyped: users disagree: Q D_003F1A70[] | u8 D_003F1A70[]; unparsed in 1 file(s) */
	PIECE D_003F1E70, 0x400, 16  /* untyped: users disagree: Q D_003F1E70[] | u8 D_003F1E70[] */
	PIECE D_003F2270, 0x400, 16  /* untyped: users disagree: Q D_003F2270[] | u8 D_003F2270[] */
	PIECE D_003F2670, 0xb0, 16  /* untyped: users disagree: M2C_UNK D_003F2670 | Q D_003F2670[] */
	PIECE D_003F2720, 0xb0, 16  /* untyped: users disagree: M2C_UNK D_003F2720 | Q D_003F2720[] */
	PIECE D_003F27D0, 0x400, 16  /* untyped: users disagree: Q D_003F27D0[] | u8 D_003F27D0[]; unparsed in 1 file(s) */
	PIECE D_003F2BD0, 0x4, 4
	PIECE D_003F2BD4, 0x4, 4
	PIECE D_003F2BD8, 0x68, 8  /* untyped: element size does not divide the extent */
	PIECE D_003F2C40, 0x10, 16  /* untyped: users disagree: E20 D_003F2C40[] | M2C_UNK D_003F2C40 | S2C40 D_003F2C40[] | s8 D_003F2C40 */
	PIECE D_003F3468, 0x20, 8
	PIECE D_003F3488, 0x1c, 4  /* untyped: users disagree: s32 D_003F3488[]; unparsed in 1 file(s) */
	PIECE D_003F34A4, 0x4, 4
	PIECE D_003F34A8, 0x8, 8
	PIECE D_003F34B0, 0x8, 8  /* untyped: users disagree: M2C_UNK D_003F34B0 | u32 D_003F34B0[] */
	PIECE D_003F34B8, 0x8, 8  /* untyped: users disagree: Flags *D_003F34B8 | S34B8 *D_003F34B8 | s32 *D_003F34B8 | s32 D_003F34B8 | void *D_003F34B8; unparsed in 1 file(s) */
	PIECE D_003F34C0, 0x4, 4
	PIECE D_003F34C4, 0x4, 4  /* untyped: users disagree: N *D_003F34C4 | Nd *D_003F34C4 | Obj2 *D_003F34C4 | s32 D_003F34C4 */
	PIECE D_003F34C8, 0x4, 4  /* untyped: users disagree: s32 D_003F34C8; unparsed in 1 file(s) */
	PIECE D_003F34CC, 0x4, 4
	PIECE D_003F34D0, 0x4, 4
	PIECE D_003F34D4, 0x4, 4
	PIECE D_003F34D8, 0x4, 4  /* untyped: users disagree: s32 D_003F34D8 | void *D_003F34D8 */
	PIECE D_003F34DC, 0x4, 4
	PIECE D_003F34E0, 0x4, 4
	PIECE D_003F34E4, 0x4, 4
	PIECE D_003F34E8, 0x4, 4
	PIECE D_003F34EC, 0x4, 4
	PIECE D_003F34F0, 0x4, 4
	PIECE D_003F34F4, 0x4, 4
	PIECE D_003F34F8, 0x4, 4
	PIECE D_003F34FC, 0x4, 4
	PIECE D_003F3500, 0x4, 4
	PIECE D_003F3504, 0x4, 4
	PIECE D_003F350C, 0x4, 4
	PIECE D_003F3510, 0x4, 4
	PIECE D_003F3514, 0x4, 4
	PIECE D_003F3518, 0x4, 4
	PIECE D_003F351C, 0x4, 4
	PIECE D_003F3520, 0x10, 16
	PIECE D_003F3870, 0x10, 16
	PIECE D_003F4200, 0x168, 8
	PIECE D_003F4368, 0x18, 8
	PIECE D_003F4380, 0x28, 8
	PIECE D_003F43F0, 0x18, 8
	PIECE D_003F4408, 0x28, 8
	PIECE D_003F44C8, 0x18, 8
	PIECE D_003F47A8, 0x10, 8  /* untyped: users disagree: M2C_UNK D_003F47A8 | u8 D_003F47A8[] */
	PIECE D_003F50E0, 0x2e0, 16  /* untyped: users disagree: s32 D_003F50E0[]; unparsed in 1 file(s) */
	PIECE D_003F53C0, 0x2e0, 16
	PIECE D_003F59A0, 0x4, 4  /* untyped: users disagree: f32 D_003F59A0[] | u8 D_003F59A0[] */
	PIECE D_003F59A4, 0xc, 4
	PIECE D_003F59B0, 0x4, 4
	PIECE D_003F59B4, 0x4, 4
	PIECE D_003F59B8, 0x8, 8
	PIECE D_003F59D0, 0x18, 8
	PIECE D_003F5C18, 0x4, 4  /* untyped: users disagree: s32 D_003F5C18 | s32 D_003F5C18[] */
	PIECE D_003F5FF0, 0x80, 16  /* untyped: users disagree: M2C_UNK D_003F5FF0 | s32 D_003F5FF0[] */
	PIECE D_003F61E0, 0x90, 16  /* untyped: users disagree: M2C_UNK D_003F61E0 | s32 D_003F61E0[] */
	PIECE D_003F6740, 0x18, 8
	PIECE D_003F6828, 0x18, 8
	PIECE D_003F6840, 0x14, 4
	PIECE D_003F6854, 0xc, 4
	PIECE D_003F6E24, 0x4, 4
	PIECE D_003F6E28, 0x4, 4  /* untyped: users disagree: s32 D_003F6E28; unparsed in 1 file(s) */
	PIECE D_003F6E2C, 0x4, 4
	PIECE D_003F6E30, 0x10, 16
	PIECE D_003F720C, 0x4, 4
	PIECE D_003F7210, 0x18, 8
	PIECE D_003F7238, 0x8, 8  /* untyped: users disagree: s32 D_003F7238[] | u8 D_003F7238[] */
	PIECE D_003F73A4, 0xc, 4
	PIECE D_003F76B4, 0x4, 4
	PIECE D_003F76B8, 0x4, 4
	PIECE D_003F76BC, 0x4, 4
	PIECE D_003F7774, 0x4, 4
	PIECE D_003F7778, 0x8, 8
	PIECE D_003F7780, 0x10, 16
	PIECE D_003F7790, 0x10, 16
	PIECE D_003F77A0, 0x10, 16
	PIECE D_003F77B0, 0x100, 16  /* untyped: users disagree: T78D8 D_003F77B0[8] | u8 D_003F77B0[8][32] */
	PIECE D_003F7A64, 0x4, 4
	PIECE D_003F7A68, 0x8, 8  /* untyped: users disagree: s32 D_003F7A68; unparsed in 1 file(s) */
	PIECE D_003F7A70, 0x1d8, 8  /* untyped: users disagree: E7A70 D_003F7A70[] | T7A70 D_003F7A70[] */
	PIECE D_003F7E94, 0x4, 4
	PIECE D_003F7E98, 0x8, 8
	PIECE D_003F7EC4, 0x4, 4
	PIECE D_003F7EC8, 0x8, 8
	PIECE D_003F8380, 0xc00, 16  /* untyped: users disagree: u128 D_003F8380[] | u8 D_003F8380[] */
	PIECE D_003F8F80, 0x1000, 16  /* untyped: users disagree: u128 D_003F8F80[] | u8 D_003F8F80[] */
	PIECE D_003F9F80, 0x400, 16  /* untyped: users disagree: u128 D_003F9F80[] | u8 D_003F9F80[] */
	PIECE D_003FA380, 0x400, 16  /* untyped: users disagree: u128 D_003FA380[] | u8 D_003FA380[] */
	PIECE D_003FA780, 0x14000, 16  /* untyped: users disagree: u128 D_003FA780[] | u8 D_003FA780[] */
