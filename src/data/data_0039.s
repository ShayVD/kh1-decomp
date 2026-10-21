/* Shared data names 0039xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0039.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_0039A570, 0x10, 16
	PIECE D_0039A580, 0xd400, 16  /* untyped: users disagree: E848 D_0039A580[] | E848b D_0039A580[] | Ent D_0039A580[] | KEnt D_0039A580[] | M2C_UNK D_0039A580 | Obj350 D_0039A580[] | VM D_0039A580 | VM D_0039A580[] | VM_c2778 D_0039A580[] | VMa D_0039A580[] | VmE D_0039A580[]; session 25: as VMa D_0039A580[]: new warning in text_001d0000_b11.c, text_001d0000_h43.c +1; does not compile in text_001c0000_c09b.c, text_001c0000_s10_r2_9.c */
