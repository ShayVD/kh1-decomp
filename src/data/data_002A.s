/* Shared data names 002Axxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_002A.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_002A3E20, 0x100, 16  /* untyped: users disagree: Cfg D_002A3E20[] | s32 D_002A3E20[][4] */
	PIECE D_002A3F20, 0x4, 4
	PIECE D_002A3F24, 0x4, 4
	PIECE D_002A3F28, 0x4, 4
	PIECE D_002A3F30, 0x4, 4  /* untyped: users disagree: s32 *D_002A3F30 | s32 D_002A3F30 */
	PIECE D_002A3F38, 0x4, 4
	PIECE D_002A3F3C, 0x4, 4  /* untyped: users disagree: Hdr *D_002A3F3C | s32 D_002A3F3C | void *D_002A3F3C */
	PIECE D_002A3F40, 0x4, 4
	PIECE D_002A3F44, 0x4, 4
	PIECE D_002A3F48, 0x8, 8  /* untyped: users disagree: V4_52 *D_002A3F48 | s32 D_002A3F48 */
	PIECE D_002A3F50, 0x10, 16  /* untyped: users disagree: s32 D_002A3F50 | s32 D_002A3F50[2] | s32 D_002A3F50[] | volatile s32 D_002A3F50[] */
	PIECE D_002A3F60, 0x100, 16  /* untyped: users disagree: F16 D_002A3F60[16] | f32 D_002A3F60[16][4] | s32 D_002A3F60[4][4][4] */
	PIECE D_002A4060, 0x100, 16  /* untyped: users disagree: F16 D_002A4060[16] | V4f D_002A4060[16] | f32 D_002A4060[16][4] */
	PIECE D_002A6178, 0x68, 8
	PIECE D_002A61F0, 0x4, 4
	PIECE D_002A61F4, 0x4, 4
	PIECE D_002A61F8, 0x4, 4
	PIECE D_002A61FC, 0x4, 4
	PIECE D_002A6200, 0x4, 4
	PIECE D_002A6204, 0x4, 4
	PIECE D_002A6208, 0x8, 8  /* untyped: users disagree: s32 D_002A6208 | u32 D_002A6208 */
	PIECE D_002A6210, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002A6210 | f32 D_002A6210[4] */
	PIECE D_002A6220, 0x10, 16  /* untyped: users disagree: M2C_UNK D_002A6220 | f32 D_002A6220[3] */
	PIECE D_002A6230, 0x4, 4
	PIECE D_002A6234, 0x4, 4  /* untyped: users disagree: Grid *D_002A6234 | s32 D_002A6234 */
	PIECE D_002A6238, 0x4, 4  /* untyped: users disagree: ColE *D_002A6238 | Ent14 *D_002A6238 | Ent20 *D_002A6238 | Face *D_002A6238 | Plane *D_002A6238 | Plane52 *D_002A6238 | Tri01 *D_002A6238 | Tri20 *D_002A6238 | Tri25 *D_002A6238 | Tri368 *D_002A6238 | W29Plane *D_002A6238 | s32 D_002A6238 | void *D_002A6238 */
	PIECE D_002A623C, 0x4, 4  /* untyped: users disagree: s32 D_002A623C | u16 **D_002A623C */
	PIECE D_002A6240, 0x4, 4
	PIECE D_002A6244, 0x4, 4  /* untyped: users disagree: Node01 **D_002A6244 | Node368 **D_002A6244 | s32 D_002A6244 */
	PIECE D_002A6248, 0x4, 4
	PIECE D_002A624C, 0x4, 4  /* untyped: users disagree: Vec3 *D_002A624C | Vtx *D_002A624C | Vtx25 *D_002A624C | s32 D_002A624C */
	PIECE D_002A6250, 0x4, 4  /* untyped: users disagree: SV *D_002A6250 | s32 D_002A6250 */
	PIECE D_002A6254, 0x4, 4
	PIECE D_002A6258, 0x4, 4
	PIECE D_002A625C, 0x4, 4
	PIECE D_002A6260, 0x4, 4
	PIECE D_002A6264, 0x4, 4
	PIECE D_002A6268, 0x4, 4
	PIECE D_002A626C, 0x4, 4
	PIECE D_002A6270, 0x4, 4
	PIECE D_002A6274, 0x4, 4  /* untyped: users disagree: Ent20b *D_002A6274 | Tri20 *D_002A6274 | s32 D_002A6274 */
	PIECE D_002A6278, 0x4, 4
	PIECE D_002A627C, 0x4, 4
	PIECE D_002A6280, 0x4, 4
	PIECE D_002A6284, 0x4, 4
	PIECE D_002A6288, 0x4, 4
	PIECE D_002A628C, 0x4, 4
	PIECE D_002A6290, 0x4, 4
	PIECE D_002A6294, 0x4, 4
	PIECE D_002A6298, 0x4, 4
	PIECE D_002A629C, 0x4, 4
	PIECE D_002A62A0, 0x4, 4
	PIECE D_002A62A4, 0x4, 4
	PIECE D_002A62A8, 0x4, 4  /* untyped: users disagree: I1 D_002A62A8 | s32 D_002A62A8 */
	PIECE D_002A62AC, 0x4, 4  /* untyped: users disagree: s32 D_002A62AC | u8 *D_002A62AC */
	PIECE D_002A62B0, 0x4, 4  /* untyped: users disagree: Ent14 *D_002A62B0 | s32 D_002A62B0 | u8 *D_002A62B0 */
	PIECE D_002A62B4, 0x4, 4  /* untyped: users disagree: s32 D_002A62B4; unparsed in 1 file(s) */
	PIECE D_002A62B8, 0x4, 4
	PIECE D_002A62BC, 0x4, 4  /* untyped: users disagree: SV *D_002A62BC | s32 D_002A62BC */
	PIECE D_002A62C0, 0x4, 4  /* untyped: users disagree: s32 D_002A62C0 | u8 *D_002A62C0 */
	PIECE D_002A62C4, 0x4, 4  /* untyped: users disagree: s32 D_002A62C4 | u8 *D_002A62C4 */
	PIECE D_002A62C8, 0x4, 4  /* untyped: users disagree: s32 D_002A62C8 | u8 *D_002A62C8 */
	PIECE D_002A62CC, 0x4, 4  /* untyped: users disagree: s32 D_002A62CC | u8 *D_002A62CC */
	PIECE D_002A62D0, 0x4, 4  /* untyped: users disagree: s32 D_002A62D0 | u32 D_002A62D0 */
	PIECE D_002A62D4, 0x4, 4  /* untyped: users disagree: s32 D_002A62D4 | u32 D_002A62D4 */
	PIECE D_002A62D8, 0x4, 4  /* untyped: users disagree: s32 D_002A62D8 | u32 D_002A62D8 */
	PIECE D_002A62DC, 0x4, 4  /* untyped: users disagree: s32 D_002A62DC | u32 D_002A62DC */
	PIECE D_002A62E0, 0x4, 4  /* untyped: users disagree: s32 D_002A62E0 | u32 D_002A62E0 */
	PIECE D_002A62E4, 0x4, 4  /* untyped: users disagree: s32 D_002A62E4 | u32 D_002A62E4 */
	PIECE D_002A62E8, 0x4, 4
	PIECE D_002A62EC, 0x4, 4
	PIECE D_002A62F0, 0x8, 8
	PIECE D_002A62F8, 0x10, 8
	PIECE D_002A6308, 0x10, 8  /* untyped: users disagree: IVec3 D_002A6308 | s32 D_002A6308[3] */
	PIECE D_002A6318, 0xc, 4  /* untyped: users disagree: IVec3 D_002A6318 | s32 D_002A6318[3] */
	PIECE D_002A6324, 0xc, 4  /* untyped: users disagree: Grid *D_002A6324 | s32 D_002A6324 */
	PIECE D_002A6B80, 0x4, 4
	PIECE D_002A6B84, 0x8c, 4
	PIECE D_002A6C10, 0x40, 16  /* untyped: users disagree: f32 D_002A6C10[] | s32 D_002A6C10[4][4] */
	PIECE D_002A6C50, 0x4, 4
	PIECE D_002A6C54, 0xc, 4
	PIECE D_002A6C60, 0x3400, 16  /* untyped: users disagree: M2C_UNK D_002A6C60 | volatile unsigned char D_002A6C60 */
	PIECE D_002AA060, 0x3400, 16  /* untyped: users disagree: ED0 D_002AA060[] | M2C_UNK D_002AA060 */
	PIECE D_002AD460, 0x4800, 16
