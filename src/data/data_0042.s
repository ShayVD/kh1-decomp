/* Data names 0042xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0042.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00425B80, 0x40, 16  /* untyped: users disagree: M2C_UNK D_00425B80 | S5B80 D_00425B80 | SvF D_00425B80 */
	PIECE D_00425BC4, 0x4, 4
	PIECE D_00425BC8, 0x8, 8  /* untyped: users disagree: Cfg *D_00425BC8 | F8 *D_00425BC8 | G5bc8 *D_00425BC8 | G5bc8e *D_00425BC8 | P5BC8 *D_00425BC8 | Pad *D_00425BC8 | Pad8 *D_00425BC8 | S5bc8 *D_00425BC8 | S5bc8c *D_00425BC8 | s32 *D_00425BC8 | void *D_00425BC8; unparsed in 2 file(s) */
	PIECE D_00425C08, 0x8, 8
	PIECE D_00425C10, 0x4, 4  /* untyped: users disagree: s32 D_00425C10; unparsed in 2 file(s) */
	PIECE D_00425C14, 0x4, 4  /* untyped: users disagree: s32 D_00425C14; unparsed in 2 file(s) */
	PIECE D_00425C18, 0x4, 4
	PIECE D_00425C1C, 0x4, 4  /* untyped: users disagree: s32 D_00425C1C | u32 D_00425C1C */
	PIECE D_00425C20, 0x8, 8
	PIECE D_00425C28, 0x20, 8  /* untyped: users disagree: C28 D_00425C28 | S16 D_00425C28[] | s32 D_00425C28[2][4] | s32 D_00425C28[] | s32 D_00425C28[][4] */
	PIECE D_00425C48, 0x20, 8  /* untyped: users disagree: M2C_UNK D_00425C48 | s32 D_00425C48[2][4] | s32 D_00425C48[][4] | s8 D_00425C48 */
	PIECE D_00425C68, 0x20, 8  /* untyped: users disagree: M2C_UNK D_00425C68 | s32 D_00425C68[2][4] | s32 D_00425C68[][4] | s8 D_00425C68 */
	PIECE D_00425C88, 0x20, 8  /* untyped: users disagree: M2C_UNK D_00425C88 | s32 D_00425C88[2][4] | s32 D_00425C88[][4] | s8 D_00425C88 */
	PIECE D_00425CA8, 0x4, 4  /* untyped: users disagree: s32 D_00425CA8; unparsed in 1 file(s) */
	PIECE D_00425CAC, 0x4, 4  /* untyped: users disagree: s32 D_00425CAC; unparsed in 1 file(s) */
	PIECE D_00425CB0, 0x20, 16
	PIECE D_00425CD0, 0x10, 16
	PIECE D_00425CE0, 0xa0, 16  /* untyped: users disagree: M2C_UNK D_00425CE0 | VEC D_00425CE0 | u8 D_00425CE0[] */
	PIECE D_00425D80, 0x1f0, 16  /* untyped: type S5D80 is not a common.h basic type */
	PIECE D_00425F70, 0x8, 8  /* untyped: users disagree: Cam *D_00425F70 | Cam_q1 *D_00425F70 | S5D80 *D_00425F70 */
	PIECE D_00425F78, 0x8, 8
	PIECE D_00425F80, 0x8, 8
	PIECE D_00425F88, 0x808, 8
	PIECE D_00426790, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426790 | u8 D_00426790[] */
	PIECE D_004267C0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004267C0 | u8 D_004267C0[] */
	PIECE D_004267F0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004267F0 | u8 D_004267F0[]; unparsed in 1 file(s) */
	PIECE D_00426820, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426820 | u8 D_00426820[] */
	PIECE D_00426850, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426850 | M2C_UNK D_00426850 | u8 D_00426850[] */
	PIECE D_00426880, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426880 | u8 D_00426880[] */
	PIECE D_004268B0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004268B0 | Tex D_004268B0 | u8 D_004268B0[] */
	PIECE D_004268E0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004268E0 | u8 D_004268E0[] */
	PIECE D_00426910, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426910 | u8 D_00426910[] */
	PIECE D_00426940, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426940 | u8 D_00426940[] */
	PIECE D_00426970, 0x4e20, 16  /* untyped: users disagree: Tex4440 D_00426970 | u8 D_00426970[] */
	PIECE D_0042B790, 0x4e20, 16  /* untyped: users disagree: Tex4440 D_0042B790 | u8 D_0042B790[] */
