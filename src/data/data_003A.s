/* Shared data names 003Axxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_003A.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_003A7980, 0x10, 16
	PIECE D_003A7990, 0xd400, 16  /* untyped: users disagree: E848 D_003A7990[] | E848b D_003A7990[] | Obj350 D_003A7990[] | VM D_003A7990[] | VmC D_003A7990[]; session 25: as E848 D_003A7990[]: new warning in text_001c0000_b10.c, text_001b0000_s6_13.c; does not compile in text_001c0000_h67.c, text_001e0000_h68.c +1 */
