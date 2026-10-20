/* Data names 0027xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0027.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00272C70, 0x80, 16
	PIECE D_00272CF0, 0xa4, 4
	PIECE D_00272D94, 0x10, 4
	PIECE D_00272DA4, 0x40, 4
	PIECE D_00272DE4, 0x3c, 4
	PIECE D_00272E20, 0x480, 16
	PIECE D_002732A0, 0x410, 16
	PIECE D_002736B0, 0x480, 16
	PIECE D_00273B30, 0x5e0, 16
	PIECE D_00274110, 0x6b0, 16
	PIECE D_002747C0, 0xfe0, 16
	PIECE D_002757A0, 0x10d0, 16
	PIECE D_00276870, 0x1270, 16
	PIECE D_00277AE0, 0x360, 16
	PIECE D_00277E40, 0x3d0, 16
	PIECE D_00278210, 0x470, 16
	PIECE D_00278680, 0x4d0, 16
	PIECE D_00278B50, 0x225f0, 16
