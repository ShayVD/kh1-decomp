/* Data names 0042xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0042.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00425B80, 0x40, 16  /* untyped: users disagree: M2C_UNK D_00425B80 | S5B80 D_00425B80 | SvF D_00425B80; session 25: as SvF D_00425B80: does not compile in text_00230000_s8_w8.c */
	PIECE_BEGIN D_00425BC0, 0x4, 4
	.word D_00491390
	PIECE_END D_00425BC0, 0x4
	PIECE D_00425BC4, 0x4, 4
	PIECE D_00425BC8, 0x8, 8  /* untyped: users disagree: Cfg *D_00425BC8 | F8 *D_00425BC8 | G5bc8 *D_00425BC8 | G5bc8e *D_00425BC8 | P5BC8 *D_00425BC8 | Pad *D_00425BC8 | Pad8 *D_00425BC8 | S5bc8 *D_00425BC8 | S5bc8c *D_00425BC8 | s32 *D_00425BC8 | void *D_00425BC8; unparsed in 2 file(s); session 25: as Cfg *D_00425BC8: does not compile in text_00220000_b15.c, text_00210000_s11_w35.c +2; new warning in text_001f0000_h69.c */
	PIECE D_00425C08, 0x8, 8
	PIECE D_00425C10, 0x4, 4  /* data/pieces/D_00425C10.h */
	PIECE D_00425C14, 0x4, 4  /* data/pieces/D_00425C14.h */
	PIECE D_00425C18, 0x4, 4
	PIECE D_00425C1C, 0x4, 4  /* data/pieces/D_00425C1C.h */
	PIECE D_00425C20, 0x8, 8
	PIECE D_00425C28, 0x20, 8  /* untyped: users disagree: C28 D_00425C28 | S16 D_00425C28[] | s32 D_00425C28[2][4] | s32 D_00425C28[] | s32 D_00425C28[][4]; session 25: as s32 D_00425C28[0x2][4]: does not compile in text_00220000_h48.c, text_00220000_h72.c +1 */
	PIECE D_00425C48, 0x20, 8  /* data/pieces/D_00425C48.h */
	PIECE D_00425C68, 0x20, 8  /* data/pieces/D_00425C68.h */
	PIECE D_00425C88, 0x20, 8  /* data/pieces/D_00425C88.h */
	PIECE D_00425CA8, 0x4, 4  /* data/pieces/D_00425CA8.h */
	PIECE D_00425CAC, 0x4, 4  /* data/pieces/D_00425CAC.h */
	PIECE D_00425CB0, 0x20, 16
	PIECE D_00425CD0, 0x10, 16
	PIECE D_00425CE0, 0xa0, 16  /* data/pieces/D_00425CE0.h */
	PIECE D_00425D80, 0x1f0, 16  /* data/pieces/D_00425D80.h */
	PIECE D_00425F70, 0x8, 8  /* untyped: users disagree: Cam *D_00425F70 | Cam_q1 *D_00425F70 | S5D80 *D_00425F70; session 25: as Cam *D_00425F70: does not compile in text_00200000_h47.c, text_00220000_h73.c */
	PIECE D_00425F78, 0x8, 8
	PIECE D_00425F80, 0x8, 8
	PIECE D_00425F88, 0x808, 8
	PIECE D_00426790, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426790 | u8 D_00426790[]; session 25: as u8 D_00426790[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_004267C0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004267C0 | u8 D_004267C0[]; session 25: as u8 D_004267C0[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_004267F0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004267F0 | u8 D_004267F0[]; unparsed in 1 file(s); session 25: as u8 D_004267F0[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426820, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426820 | u8 D_00426820[]; session 25: as u8 D_00426820[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426850, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426850 | M2C_UNK D_00426850 | u8 D_00426850[]; session 25: as u8 D_00426850[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426880, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426880 | u8 D_00426880[]; session 25: as u8 D_00426880[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_004268B0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004268B0 | Tex D_004268B0 | u8 D_004268B0[]; session 25: as u8 D_004268B0[0x30]: new warning in text_00230000_s6_24.c; does not compile in text_00230000_s6_24.c */
	PIECE D_004268E0, 0x30, 16  /* untyped: users disagree: GsTexHdr D_004268E0 | u8 D_004268E0[]; session 25: as u8 D_004268E0[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426910, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426910 | u8 D_00426910[]; session 25: as u8 D_00426910[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426940, 0x30, 16  /* untyped: users disagree: GsTexHdr D_00426940 | u8 D_00426940[]; session 25: as u8 D_00426940[0x30]: does not compile in text_00230000_s6_24.c */
	PIECE D_00426970, 0x4e20, 16  /* untyped: users disagree: Tex4440 D_00426970 | u8 D_00426970[]; session 25: as u8 D_00426970[0x4e20]: does not compile in text_00230000_s6_24.c */
	PIECE D_0042B790, 0x4e20, 16  /* untyped: users disagree: Tex4440 D_0042B790 | u8 D_0042B790[]; session 25: as u8 D_0042B790[0x4e20]: does not compile in text_00230000_s6_24.c */
