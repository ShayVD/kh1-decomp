/* Shared data names 003Dxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003D.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003DABD0, 0x4, 4  /* untyped: users disagree: M2C_UNK D_003DABD0 | Tbl *D_003DABD0 | s32 D_003DABD0[] | void *D_003DABD0[] */
	PIECE D_003DABD4, 0x4, 4  /* untyped: users disagree: M2C_UNK D_003DABD4 | Tbl *D_003DABD4 | s32 D_003DABD4 */
	PIECE D_003DACA0, 0x10, 16  /* untyped: users disagree: Tbl *D_003DACA0 | s32 D_003DACA0 */
	PIECE D_003DACB0, 0x4, 4
	PIECE D_003DACB4, 0x4, 4
	PIECE D_003DACB8, 0x4, 4
	PIECE D_003DACBC, 0x4, 4
	PIECE D_003DACD0, 0x8, 8
	PIECE D_003DAD38, 0x4, 4
	PIECE D_003DAD3C, 0x4, 4  /* untyped: users disagree: f32 D_003DAD3C | s32 D_003DAD3C */
	PIECE D_003DAD40, 0x4, 4
	PIECE D_003DAD44, 0xc, 4
	PIECE D_003DAE40, 0x120, 16
	PIECE_BEGIN D_003DAF60, 0x10, 16
	PIECE_BYTES D_003DAF60, 0x0, 0x4
	.word D_003DAE40
	PIECE_BYTES D_003DAF60, 0x8, 0x8
	PIECE_END D_003DAF60, 0x10
	PIECE D_003DB028, 0x28, 8
	PIECE_BEGIN D_003DB050, 0x10, 16
	PIECE_BYTES D_003DB050, 0x0, 0x4
	.word D_003DAF70
	PIECE_BYTES D_003DB050, 0x8, 0x8
	PIECE_END D_003DB050, 0x10
	PIECE D_003DBA68, 0x300, 8  /* untyped: users disagree: M2C_UNK D_003DBA68 | u8 D_003DBA68[] */
	PIECE D_003DC2A8, 0x10, 8  /* untyped: users disagree: char D_003DC2A8[] | u8 D_003DC2A8[] */
	PIECE D_003DC368, 0x8, 8
	PIECE D_003DC370, 0x10, 16  /* untyped: users disagree: char D_003DC370[] | u8 D_003DC370[] */
	PIECE D_003DC390, 0x30, 16  /* untyped: users disagree: M2C_UNK D_003DC390 | u8 D_003DC390[] */
	PIECE D_003DC468, 0x8, 8
	PIECE D_003DC470, 0x4, 4
	PIECE D_003DC474, 0x4, 4
	PIECE D_003DC478, 0x4, 4
	PIECE D_003DC47C, 0x4, 4
	PIECE D_003DC480, 0x4, 4
	PIECE D_003DC484, 0x4, 4
	PIECE D_003DC488, 0x4, 4
	PIECE D_003DC48C, 0x4, 4
	PIECE D_003DC490, 0x4, 4
	PIECE D_003DC494, 0x4, 4
	PIECE D_003DCB10, 0x80, 16  /* untyped: users disagree: char D_003DCB10[][32] | u8 D_003DCB10[][32] */
	PIECE D_003DCB90, 0x180, 16  /* untyped: users disagree: char D_003DCB90[] | char D_003DCB90[][32] */
	PIECE D_003DCD70, 0x80, 16  /* untyped: users disagree: M2C_UNK D_003DCD70 | u8 D_003DCD70[] */
	PIECE D_003DD210, 0x10, 16
	PIECE D_003DD230, 0x8, 8  /* untyped: users disagree: char D_003DD230[] | u8 D_003DD230[] */
	PIECE D_003DD238, 0x8, 8
	PIECE D_003DD240, 0x8, 8
	PIECE D_003DD248, 0x8, 8
	PIECE D_003DD258, 0x4, 4  /* untyped: users disagree: s32 D_003DD258; unparsed in 1 file(s) */
	PIECE D_003DD25C, 0x4, 4
	PIECE D_003DD260, 0x4, 4
	PIECE D_003DD264, 0x4, 4
	PIECE D_003DD268, 0x8, 8
	PIECE D_003DD270, 0x8, 8
	PIECE D_003DD278, 0x4, 4
	PIECE D_003DD27C, 0x4, 4
	PIECE D_003DD280, 0x4, 4
	PIECE D_003DD284, 0x4, 4
	PIECE D_003DD288, 0x4, 4
	PIECE D_003DD28C, 0x4, 4  /* untyped: users disagree: s32 D_003DD28C; unparsed in 1 file(s) */
	PIECE D_003DD308, 0x4, 4
	PIECE D_003DD30C, 0x4, 4
	PIECE D_003DD310, 0x4, 4
	PIECE D_003DD314, 0x4, 4
