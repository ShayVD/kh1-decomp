/* Data names 0049xxxx as pieces of the user's ELF (phase 4, step 4;
 * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an
 * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from
 * the ELF at build time: no game bytes are in the repo. Declarations: the header
 * include/data/data_0049.h (names whose C users agree on the type). */
	.include "include/data/piece.inc"

	PIECE D_00490000, 0x8, 8
	PIECE D_00490008, 0x10, 8
	PIECE D_00490018, 0x8, 8
	PIECE D_00490020, 0x10, 16
	PIECE D_004900A8, 0x18, 8  /* untyped: type Str11 is not a common.h basic type */
	PIECE D_00490300, 0x20, 16
	PIECE_BEGIN D_00490340, 0x40, 16  /* untyped: merged (a user declares it larger than the next name): D_00490340, D_00490348, D_00490358, D_00490368, D_00490378 */
	PIECE_BYTES D_00490340, 0x0, 0x8
	PIECE_LABEL D_00490340, D_00490348, 0x8
	PIECE_BYTES D_00490340, 0x8, 0x10
	PIECE_LABEL D_00490340, D_00490358, 0x18
	PIECE_BYTES D_00490340, 0x18, 0x10
	PIECE_LABEL D_00490340, D_00490368, 0x28
	PIECE_BYTES D_00490340, 0x28, 0x10
	PIECE_LABEL D_00490340, D_00490378, 0x38
	PIECE_BYTES D_00490340, 0x38, 0x8
	PIECE_END D_00490340, 0x40
	PIECE D_00490380, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490390, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004903A0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004903B0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004903C0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004903D0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_004903E0, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_004903E0, D_004903E8 */
	PIECE_BYTES D_004903E0, 0x0, 0x8
	PIECE_LABEL D_004903E0, D_004903E8, 0x8
	PIECE_BYTES D_004903E0, 0x8, 0x8
	PIECE_END D_004903E0, 0x10
	PIECE D_004903F0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490400, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490410, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490420, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490430, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490440, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_00490450, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00490450, D_00490458 */
	PIECE_BYTES D_00490450, 0x0, 0x8
	PIECE_LABEL D_00490450, D_00490458, 0x8
	PIECE_BYTES D_00490450, 0x8, 0x8
	PIECE_END D_00490450, 0x10
	PIECE D_00490460, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490470, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490480, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00490490, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004904A0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004904B0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004904C0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004904D0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_004904E0, 0x60, 16  /* untyped: merged (a user declares it larger than the next name): D_004904E0, D_004904E8, D_004904F8, D_00490508, D_00490518, D_00490528, D_00490538 */
	PIECE_BYTES D_004904E0, 0x0, 0x8
	PIECE_LABEL D_004904E0, D_004904E8, 0x8
	PIECE_BYTES D_004904E0, 0x8, 0x10
	PIECE_LABEL D_004904E0, D_004904F8, 0x18
	PIECE_BYTES D_004904E0, 0x18, 0x10
	PIECE_LABEL D_004904E0, D_00490508, 0x28
	PIECE_BYTES D_004904E0, 0x28, 0x10
	PIECE_LABEL D_004904E0, D_00490518, 0x38
	PIECE_BYTES D_004904E0, 0x38, 0x10
	PIECE_LABEL D_004904E0, D_00490528, 0x48
	PIECE_BYTES D_004904E0, 0x48, 0x10
	PIECE_LABEL D_004904E0, D_00490538, 0x58
	PIECE_BYTES D_004904E0, 0x58, 0x8
	PIECE_END D_004904E0, 0x60
	PIECE_BEGIN D_00490540, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00490540, D_00490548 */
	PIECE_BYTES D_00490540, 0x0, 0x8
	PIECE_LABEL D_00490540, D_00490548, 0x8
	PIECE_BYTES D_00490540, 0x8, 0x8
	PIECE_END D_00490540, 0x10
	PIECE_BEGIN D_00490550, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00490550, D_00490558 */
	PIECE_BYTES D_00490550, 0x0, 0x8
	PIECE_LABEL D_00490550, D_00490558, 0x8
	PIECE_BYTES D_00490550, 0x8, 0x8
	PIECE_END D_00490550, 0x10
	PIECE_BEGIN D_00490560, 0x30, 16  /* untyped: merged (a user declares it larger than the next name): D_00490560, D_00490578 */
	PIECE_BYTES D_00490560, 0x0, 0x18
	PIECE_LABEL D_00490560, D_00490578, 0x18
	PIECE_BYTES D_00490560, 0x18, 0x18
	PIECE_END D_00490560, 0x30
	PIECE D_00490620, 0x10, 16
	PIECE D_00490630, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_004906C0, 0x10, 16
	PIECE D_004906D0, 0xe0, 16  /* untyped: type Tbl55 is not a common.h basic type */
	PIECE D_004908C8, 0x18, 8
	PIECE D_004908E0, 0x10, 16  /* untyped: type S10 is not a common.h basic type */
	PIECE D_004908F0, 0x10, 16  /* untyped: type Str10 is not a common.h basic type */
	PIECE D_00490900, 0x10, 16  /* untyped: type S10 is not a common.h basic type */
	PIECE D_00490910, 0x18, 8
	PIECE D_00490928, 0x18, 8
	PIECE D_00490940, 0x20, 16
	PIECE_BEGIN D_00490A80, 0x60, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	.word func_001f1fc8+0x608
	.word func_001f1fc8+0x1e0
	.word func_001f1fc8+0x220
	.word func_001f1fc8+0x208
	.word func_001f1fc8+0x278
	.word func_001f1fc8+0x288
	.word func_001f1fc8+0x298
	.word func_001f1fc8+0x2a8
	.word func_001f1fc8+0x2d8
	.word func_001f1fc8+0x310
	.word func_001f1fc8+0x330
	.word func_001f1fc8+0x378
	.word func_001f1fc8+0x3c0
	.word func_001f1fc8+0x3d8
	.word func_001f1fc8+0x400
	.word func_001f1fc8+0x428
	.word func_001f1fc8+0x608
	.word func_001f1fc8+0x430
	.word func_001f1fc8+0x460
	.word func_001f1fc8+0x430
	.word func_001f1fc8+0x460
	PIECE_BYTES D_00490A80, 0x54, 0xc
	PIECE_END D_00490A80, 0x60
	PIECE D_00490AE0, 0x10, 16  /* untyped: users disagree: M2C_UNK D_00490AE0 | u8 D_00490AE0[] */
	PIECE D_00490F10, 0x10, 16
	PIECE D_00490F58, 0x18, 8
	PIECE D_00490F70, 0x18, 8
	PIECE D_00490F88, 0x18, 8
	PIECE D_00490FA0, 0x18, 8
	PIECE D_00490FB8, 0x18, 8
	PIECE D_00490FD0, 0x20, 16
	PIECE D_00491030, 0x18, 8
	PIECE D_00491048, 0x18, 8
	PIECE D_00491060, 0x18, 8
	PIECE D_004910B8, 0x10, 8
	PIECE D_004910C8, 0x18, 8
	PIECE D_00491390, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004914C0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004914D0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004914E0, 0x40, 16  /* untyped: type Col4 is not a common.h basic type */
	PIECE D_004915A0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004915B0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004915C0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004915D0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004915E0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_004915F0, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_00491600, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_00491610, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_00491620, 0x10, 16  /* untyped: type Col is not a common.h basic type */
	PIECE D_00491820, 0x10, 16
	PIECE D_00491830, 0x10, 16  /* untyped: type V4 is not a common.h basic type */
	PIECE D_00491840, 0x8, 8
	PIECE D_00491860, 0x18, 8
	PIECE D_00491878, 0x8, 8
	PIECE D_00491880, 0x10, 16
	PIECE D_004918B8, 0x10, 8
	PIECE D_004918C8, 0x10, 8
	PIECE D_004918D8, 0x10, 8
	PIECE D_004918E8, 0x10, 8
	PIECE D_004918F8, 0x8, 8
	PIECE D_00491900, 0x8, 8
	PIECE D_004919B0, 0x8, 8  /* untyped: users disagree: M2C_UNK D_004919B0 | char D_004919B0[] */
	PIECE D_004919C8, 0x10, 8
	PIECE D_004919E8, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491A18, 0x108, 8
	PIECE_BEGIN D_00491B20, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00491B20, D_00491B28 */
	PIECE_BYTES D_00491B20, 0x0, 0x8
	PIECE_LABEL D_00491B20, D_00491B28, 0x8
	PIECE_BYTES D_00491B20, 0x8, 0x8
	PIECE_END D_00491B20, 0x10
	PIECE D_00491B30, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B40, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B50, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B68, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B70, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B88, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D20, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D30, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D40, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D48, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D50, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D68, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D70, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D88, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491DA8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491DB0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_00491F88, 0x38, 8  /* untyped: merged (a user declares it larger than the next name): D_00491F88, D_00491FB8 */
	.word D_00491FC0
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	.word D_00491FB8
	PIECE_BYTES D_00491F88, 0x28, 0x8
	PIECE_LABEL D_00491F88, D_00491FB8, 0x30
	PIECE_BYTES D_00491F88, 0x30, 0x8
	PIECE_END D_00491F88, 0x38
	PIECE_BEGIN D_00491FC0, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00491FC0, D_00491FC8 */
	PIECE_BYTES D_00491FC0, 0x0, 0x8
	PIECE_LABEL D_00491FC0, D_00491FC8, 0x8
	PIECE_BYTES D_00491FC0, 0x8, 0x8
	PIECE_END D_00491FC0, 0x10
	PIECE D_00491FE0, 0xc8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004920A8, 0x50, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004920F8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492120, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492138, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492150, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492338, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_00492340, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_00492340, D_00492348 */
	PIECE_BYTES D_00492340, 0x0, 0x8
	PIECE_LABEL D_00492340, D_00492348, 0x8
	PIECE_BYTES D_00492340, 0x8, 0x8
	PIECE_END D_00492340, 0x10
	PIECE D_00492350, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492360, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492380, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492388, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004923B0, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004923E8, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492400, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492418, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492430, 0x100, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492530, 0x100, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492630, 0x100, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492730, 0x100, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492830, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492850, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492858, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492920, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492930, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492968, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492998, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929C8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929D8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929E8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929F8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A08, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A18, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A28, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A38, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A48, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A60, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492A78, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492AA8, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492AD8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492B00, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492B30, 0x30, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492C50, 0x40, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492C90, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492CC8, 0x30, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492CF8, 0x40, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492D38, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492E60, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492E78, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492EA0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492EB0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492EC0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492ED0, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492EE8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492F10, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492F38, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492F50, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492F70, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492F90, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492FB0, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492FD0, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492FF0, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_00493010, 0xb0, 16  /* untyped: merged (a user declares it larger than the next name): D_00493010, D_00493038, D_00493058, D_00493078, D_00493098, D_004930B8 */
	PIECE_BYTES D_00493010, 0x0, 0x28
	PIECE_LABEL D_00493010, D_00493038, 0x28
	PIECE_BYTES D_00493010, 0x28, 0x20
	PIECE_LABEL D_00493010, D_00493058, 0x48
	PIECE_BYTES D_00493010, 0x48, 0x20
	PIECE_LABEL D_00493010, D_00493078, 0x68
	PIECE_BYTES D_00493010, 0x68, 0x20
	PIECE_LABEL D_00493010, D_00493098, 0x88
	PIECE_BYTES D_00493010, 0x88, 0x20
	PIECE_LABEL D_00493010, D_004930B8, 0xa8
	PIECE_BYTES D_00493010, 0xa8, 0x8
	PIECE_END D_00493010, 0xb0
	PIECE_BEGIN D_004930C0, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_004930C0, D_004930C8 */
	PIECE_BYTES D_004930C0, 0x0, 0x8
	PIECE_LABEL D_004930C0, D_004930C8, 0x8
	PIECE_BYTES D_004930C0, 0x8, 0x8
	PIECE_END D_004930C0, 0x10
	PIECE_BEGIN D_004930D0, 0x10, 16  /* untyped: merged (a user declares it larger than the next name): D_004930D0, D_004930D8 */
	PIECE_BYTES D_004930D0, 0x0, 0x8
	PIECE_LABEL D_004930D0, D_004930D8, 0x8
	PIECE_BYTES D_004930D0, 0x8, 0x8
	PIECE_END D_004930D0, 0x10
	PIECE D_004930E0, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493108, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493128, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493140, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493150, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493160, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493178, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004931A0, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004931B8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004931C8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004931D8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493200, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493218, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493238, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493248, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493258, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493278, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493290, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004932A8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004932B8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493888, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493890, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493898, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004938A0, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493918, 0x318, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493C30, 0xe8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493E48, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493E58, 0x68, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493EC0, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493F38, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493F48, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493F58, 0x48, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493FA0, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493FB8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE_BEGIN D_00493FE0, 0x60, 16  /* untyped: merged (a user declares it larger than the next name): D_00493FE0, D_00494008, D_00494028, D_0049402C, D_00494038 */
	PIECE_BYTES D_00493FE0, 0x0, 0x28
	PIECE_LABEL D_00493FE0, D_00494008, 0x28
	PIECE_BYTES D_00493FE0, 0x28, 0x20
	PIECE_LABEL D_00493FE0, D_00494028, 0x48
	PIECE_BYTES D_00493FE0, 0x48, 0x4
	PIECE_LABEL D_00493FE0, D_0049402C, 0x4c
	PIECE_BYTES D_00493FE0, 0x4c, 0xc
	PIECE_LABEL D_00493FE0, D_00494038, 0x58
	PIECE_BYTES D_00493FE0, 0x58, 0x8
	PIECE_END D_00493FE0, 0x60
	PIECE D_00494040, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
