/* Data names 002Cxxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_002C.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_002C1250, 0x10, 16
	PIECE D_002C1260, 0x60, 16  /* untyped: users disagree: Box01 D_002C1260 | Box25 D_002C1260 | Box368 D_002C1260 | V4 D_002C1260[6] | s8 D_002C1260 */
	PIECE D_002C12C0, 0x4, 4
	PIECE D_002C12C4, 0x1c, 4
	PIECE D_002C12E0, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_002C12F0, 0x10, 16  /* untyped: type u128 is not a common.h basic type */
	PIECE D_002C1300, 0x4, 4  /* untyped: users disagree: RFn D_002C1300 | void *D_002C1300; unparsed in 1 file(s) */
	PIECE D_002C1304, 0x4, 4
	PIECE D_002C1308, 0x4, 4  /* untyped: users disagree: s32 D_002C1308 | volatile s32 D_002C1308 */
	PIECE D_002C130C, 0x4, 4
	PIECE D_002C1310, 0x10, 16
	PIECE D_002C1320, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_002C1330, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_002C1340, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_002C1350, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_002C1360, 0x4, 4
	PIECE D_002C1364, 0x4, 4
	PIECE D_002C1368, 0x8, 8  /* untyped: users disagree: s32 D_002C1368[]; unparsed in 1 file(s) */
	PIECE D_002C1370, 0x8, 8
	PIECE D_002C137C, 0x4, 4
	PIECE D_002C1380, 0x4, 4
	PIECE D_002C1384, 0x4, 4
	PIECE D_002C1388, 0x4, 4
	PIECE D_002C138C, 0x4, 4
	PIECE D_002C1390, 0x4, 4
	PIECE D_002C1394, 0xc, 4
	PIECE D_002C13A0, 0x3880, 16
	PIECE D_002C4C20, 0xc80, 16
	PIECE D_002C58A0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002C58A0 | V4 D_002C58A0 | V4 D_002C58A0[] | V4f D_002C58A0 | f32 D_002C58A0[4] | f32 D_002C58A0[] | u8 D_002C58A0[]; unparsed in 6 file(s) */
	PIECE D_002C58B0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002C58B0 | V4 D_002C58B0 | V4D0 D_002C58B0 | V53 D_002C58B0 | f32 D_002C58B0[4] | f32 D_002C58B0[] | u8 D_002C58B0[] */
	PIECE D_002C58C0, 0x10, 16
	PIECE D_002C58D0, 0x40, 16  /* untyped: users disagree: C01Mat D_002C58D0 | M2C_UNK D_002C58D0 | M4 D_002C58D0 | Mtx D_002C58D0 | V4 D_002C58D0[4] | f32 D_002C58D0[4] | f32 D_002C58D0[4][4] | f32 D_002C58D0[] | u8 D_002C58D0[] */
	PIECE D_002C5910, 0x40, 16  /* untyped: users disagree: f32 D_002C5910[4][4] | s32 D_002C5910[4][4] */
	PIECE D_002C5950, 0x8, 8
	PIECE D_002C595A, 0x6, 2  /* untyped: users disagree: s16 D_002C595A | u16 D_002C595A */
	PIECE D_002C5960, 0x8, 8  /* untyped: users disagree: Fl5960 D_002C5960 | s32 D_002C5960 | u32 D_002C5960 */
	PIECE D_002C5968, 0x4, 4  /* untyped: users disagree: F5968 D_002C5968 | volatile Bits8 D_002C5968 | volatile F5968 D_002C5968 | volatile Flags5968 D_002C5968 | volatile HddSt D_002C5968 | volatile Sema5968 D_002C5968 | volatile s32 D_002C5968 */
	PIECE D_002C596C, 0x4, 4
	PIECE D_002C5970, 0x8, 8  /* untyped: users disagree: f32 D_002C5970; unparsed in 1 file(s) */
	PIECE D_002C597A, 0x6, 2
	PIECE D_002C5980, 0x10, 16
	PIECE D_002C5990, 0xf0, 16  /* untyped: type MaskEnt is not a common.h basic type */
	PIECE D_002C5A80, 0x8, 8
	PIECE D_002C5A88, 0x48, 8
	PIECE D_002C5AD2, 0x2, 2  /* untyped: element size does not divide the extent */
	PIECE D_002C5AD4, 0x4, 4  /* untyped: users disagree: s32 D_002C5AD4 | u32 D_002C5AD4 */
	PIECE D_002C5AD8, 0x8, 8  /* untyped: users disagree: s32 D_002C5AD8 | u32 D_002C5AD8 */
	PIECE D_002C5AE0, 0x64, 4  /* untyped: users disagree: u32 D_002C5AE0; unparsed in 1 file(s) */
	PIECE D_002C5B44, 0x6c, 4
	PIECE D_002C5BB4, 0x4, 4  /* untyped: users disagree: s32 D_002C5BB4 | u32 D_002C5BB4 */
	PIECE D_002C5BB8, 0x68, 8  /* untyped: users disagree: s32 D_002C5BB8 | u32 D_002C5BB8 | u64 D_002C5BB8; unparsed in 1 file(s) */
	PIECE D_002C5C20, 0x4, 4
	PIECE D_002C5C24, 0x4, 4
	PIECE D_002C5C28, 0x4, 4
	PIECE D_002C5C2C, 0x4, 4
	PIECE D_002C5C30, 0x8, 8
	PIECE D_002C5C38, 0x4, 4
	PIECE D_002C5C3C, 0x4, 4
	PIECE D_002C5C40, 0x4, 4
	PIECE D_002C5C44, 0x4, 4
	PIECE D_002C5C48, 0x4, 4  /* untyped: users disagree: s32 D_002C5C48 | u32 D_002C5C48 */
	PIECE D_002C5C4C, 0x4, 4
	PIECE D_002C5C50, 0x4, 4
	PIECE D_002C5C54, 0xc, 4
	PIECE D_002C5C60, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002C5C60 | Vec4 D_002C5C60 | u8 D_002C5C60[] */
	PIECE D_002C5C70, 0x10, 16  /* untyped: type V53 is not a common.h basic type */
	PIECE D_002C5C80, 0x7c0, 16  /* untyped: users disagree: Ent40 D_002C5C80[] | Ent5C80 D_002C5C80[] | Light53 D_002C5C80[] | Lt2 D_002C5C80[31] | Lt64 D_002C5C80[] | M2C_UNK D_002C5C80 */
	PIECE D_002C6440, 0x10, 16  /* untyped: users disagree: s32 D_002C6440 | void *D_002C6440 */
	PIECE D_002C6450, 0x10, 16  /* untyped: users disagree: V4 D_002C6450 | f32 D_002C6450[4] */
	PIECE D_002C648C, 0x4, 4
	PIECE D_002C6490, 0x10, 16  /* untyped: type V53 is not a common.h basic type */
	PIECE D_002C6814, 0x1be8c, 4  /* untyped: type A2 is not a common.h basic type */
