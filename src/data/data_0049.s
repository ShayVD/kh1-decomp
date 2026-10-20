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
	PIECE D_00490578, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
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
	PIECE D_00491B28, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B30, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B50, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B68, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B70, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491B88, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D20, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D40, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D48, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D50, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D68, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D70, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491D88, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491DA8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491DB0, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491FB8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491FC8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00491FE0, 0xc8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004920A8, 0x50, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004920F8, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492120, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492138, 0x18, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492150, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492348, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492350, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492360, 0x20, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492380, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00492388, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004923B0, 0x38, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
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
	PIECE D_004929D8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929E8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004929F8, 0x10, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
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
	PIECE D_00493010, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493038, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493058, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493078, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00493098, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_004930D8, 0x8, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
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
	PIECE D_00493FE0, 0x28, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00494008, 0x20, 8  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00494028, 0x4, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_0049402C, 0xc, 4  /* untyped: no C user outside src/sdk/ with one file-scope extern */
	PIECE D_00494040, 0x10, 16  /* untyped: no C user outside src/sdk/ with one file-scope extern */
