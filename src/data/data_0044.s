/* Shared data names 0044xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0044.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00440994, 0xc, 4
	PIECE D_00449900, 0x8, 8
	PIECE D_00449908, 0x88, 8  /* untyped: users disagree: Cam D_00449908 | St17 D_00449908 | St570 D_00449908; unparsed in 1 file(s) */
	PIECE D_00449990, 0xe70, 16  /* untyped: users disagree: Hdr D_00449990 | M2C_UNK D_00449990 */
	PIECE D_0044A820, 0x10, 16  /* untyped: users disagree: M2C_UNK D_0044A820 | s32 D_0044A820 */
	PIECE D_0044A830, 0x1d70, 16  /* untyped: users disagree: Blob D_0044A830 | M2C_UNK D_0044A830 */
	PIECE D_0044C5A0, 0x1a30, 16  /* untyped: users disagree: Blob D_0044C5A0 | M2C_UNK D_0044C5A0 */
	PIECE D_0044DFD0, 0x13b0, 16  /* untyped: users disagree: Blob D_0044DFD0 | M2C_UNK D_0044DFD0 */
	PIECE D_0044F380, 0x150, 16  /* untyped: users disagree: Blob D_0044F380 | M2C_UNK D_0044F380 */
	PIECE D_0044F4D0, 0x1b70, 16  /* untyped: users disagree: Blob D_0044F4D0 | M2C_UNK D_0044F4D0 */
