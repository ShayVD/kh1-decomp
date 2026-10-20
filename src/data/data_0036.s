/* Shared data names 0036xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0036.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00360F30, 0x1410, 16
	PIECE D_003623F0, 0x4, 4
	PIECE D_003623F4, 0x4, 4
	PIECE D_003623F8, 0x8, 8
	PIECE D_00362420, 0x4, 4
	PIECE D_00362424, 0x4, 4  /* untyped: users disagree: Hdr *D_00362424 | s32 D_00362424 */
	PIECE D_00362428, 0x4, 4  /* untyped: users disagree: Rec20 *D_00362428 | Rec32 *D_00362428 | s32 D_00362428 */
	PIECE D_0036242C, 0x4, 4  /* untyped: users disagree: Rec *D_0036242C | s32 D_0036242C */
	PIECE D_00362430, 0x4, 4  /* untyped: users disagree: Box *D_00362430 | E30 *D_00362430 | s32 D_00362430 */
	PIECE D_00362434, 0x4, 4  /* untyped: users disagree: CamPt *D_00362434 | P1c *D_00362434 | Rec20 *D_00362434 | s32 D_00362434 | void *D_00362434 */
	PIECE D_00362438, 0x4, 4  /* untyped: users disagree: P1c *D_00362438 | Path *D_00362438 | PathB *D_00362438 | Rec20 *D_00362438 | S18 *D_00362438 | s32 D_00362438 | void *D_00362438; unparsed in 1 file(s) */
	PIECE D_0036243C, 0x4, 4  /* untyped: users disagree: Box *D_0036243C | s32 D_0036243C | void *D_0036243C */
	PIECE D_00362440, 0x4, 4
	PIECE D_00362444, 0x4, 4
	PIECE D_00362448, 0x4, 4
	PIECE D_0036244C, 0x4, 4  /* untyped: users disagree: s32 D_0036244C | void *D_0036244C */
	PIECE D_00362450, 0x4, 4  /* untyped: users disagree: Path *D_00362450 | s32 D_00362450 */
	PIECE D_00362454, 0x4, 4  /* untyped: users disagree: s32 D_00362454 | void *D_00362454 */
	PIECE D_0036266C, 0x4, 4
	PIECE D_00362674, 0xc, 4
	PIECE D_00362684, 0x8, 4
	PIECE D_003626A0, 0x10, 16  /* untyped: users disagree: V4 D_003626A0; unparsed in 1 file(s) */
	PIECE D_003626C0, 0x30, 16  /* untyped: users disagree: M2C_UNK D_003626C0 | S26C0 D_003626C0 */
	PIECE D_003626F0, 0x8, 8  /* untyped: users disagree: Arg D_003626F0[] | M2C_UNK D_003626F0 | S26F0 D_003626F0 */
	PIECE D_003626F8, 0xc, 4  /* untyped: users disagree: M2C_UNK D_003626F8 | f32 D_003626F8[3] */
	PIECE D_00362704, 0x4, 4
	PIECE D_00362708, 0x4, 4
	PIECE D_0036270C, 0x4, 4
	PIECE D_00362710, 0x4, 4  /* untyped: users disagree: f32 D_00362710 | s32 D_00362710 */
	PIECE D_00362714, 0x4, 4
	PIECE D_00362718, 0x4, 4
	PIECE D_0036271C, 0x4, 4
	PIECE D_00362720, 0x4, 4
	PIECE D_00362724, 0x4, 4
	PIECE D_00362730, 0x1200, 16  /* untyped: users disagree: H39Slot D_00362730[]; unparsed in 1 file(s) */
	PIECE D_00364130, 0xc000, 16  /* untyped: users disagree: E0C0 D_00364130[256] | H39Obj D_00364130[256] | M2C_UNK D_00364130 | PObj D_00364130[256] | PppMng D_00364130[256]; unparsed in 1 file(s) */
