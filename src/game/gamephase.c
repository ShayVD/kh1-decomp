/* The game's phases: func_001220e8 the per-frame updates of the object
 * systems, func_00122130 the resets at a new game, func_00122198 a room's
 * load (the area set, docs/structs.md), func_00122330 / func_001223b8 the
 * resets when a room starts and ends. Flag mode: default (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5C48.h"
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00110000_h53_p.h"

/* func_001220e8 (from auto/text_00120000.c). */
M2C_UNK func_00127340();
M2C_UNK func_00132e38();
M2C_UNK func_0013f2c0();
M2C_UNK func_001478e0();
M2C_UNK func_00148e60();
M2C_UNK func_0014f868();
M2C_UNK func_00151b90();
void func_001220e8(void) {
    func_00148e60();
    func_001478e0();
    func_0013f2c0();
    func_00127340();
    func_0014f868();
    func_00151b90();
    func_00132e38();
}

/* func_00122130 (from auto/text_00120000_8.c). */
M2C_UNK func_00124b90();
M2C_UNK func_00125240();
M2C_UNK func_00128b20();
M2C_UNK func_0012ff80();
M2C_UNK func_00133628();
M2C_UNK func_0013ce98();
M2C_UNK func_00142340();
M2C_UNK func_00148f08();
M2C_UNK func_0014a090();
M2C_UNK func_001561f8();
M2C_UNK func_00157dc8();
extern s32 D_002C5958;
void func_00122130(void) {
    D_002C5958 = 0;
    func_0013ce98();
    func_00125240();
    func_00124b90();
    func_00128b20();
    func_00133628();
    func_00148f08();
    func_00142340();
    func_00157dc8();
    func_001561f8();
    func_0014a090();
    func_0012ff80();
}

/* func_00122198 (from hand/text_00110000_h53.c). */
extern s32 D_002BC130;
extern s32 D_002BC128;
extern s32 D_002BC134;
extern s32 D_002C5C54;
extern s32 D_002C5C4C;
extern s32 D_002C5C50;
void func_0012b738(void);
void func_00142030(void);
void func_001561b0(void);
void func_00132c70(s32, s32);
void func_00133520(void);
void func_00146590(void);
void func_00151808(void);
void func_001356a8(void);
void func_0014c378(void);
void func_00122cf0(void);
void func_00134718(void);
void func_0013bd08(void);
void func_0012ea38(void);
#define D_002C5958 (*(u32 (*)) &D_002C5958)
#define func_00124b90 ((void (*)(void)) func_00124b90)
#define func_0012ff80 ((void (*)(void)) func_0012ff80)
void func_00122198(s32 a0, s32 a1) {
    D_002C5958 = 0;
    if (D_002BC128 == 16 && (D_002BC130 == 26 || D_002BC130 == 33 || D_002BC130 == 34)) {
        *(volatile u32 *)&D_002C5958 |= 0x20;
    }
    D_002C5C4C = D_002BC128 == 9 || (D_002BC128 == 16 && D_002BC130 == 21);
    D_002C5C50 = D_002BC128 == 10 || (D_002BC128 == 16 && D_002BC130 == 22);
    D_002C5C54 = D_002BC128 == 15 && D_002BC134 == 10;
    func_0012b738();
    func_00124b90();
    func_00142030();
    func_001561b0();
    func_00132c70(a0, a1);
    func_00133520();
    func_00146590();
    func_00151808();
    func_001356a8();
    func_0014c378();
    func_0012ff80();
    func_00122cf0();
    func_00134718();
    func_0013bd08();
    func_0012ea38();
}
#undef D_002C5958
#undef func_00124b90
#undef func_0012ff80

/* func_00122330 (from auto/text_00120000_2.c). */
M2C_UNK func_001249d8();
M2C_UNK func_0012fc20();
M2C_UNK func_00146508();
M2C_UNK func_001574f0();
M2C_UNK func_00168518();
M2C_UNK func_001762c8();
M2C_UNK func_00176c60(M2C_UNK);
M2C_UNK func_0017db68();
M2C_UNK func_0017ebd0();
M2C_UNK func_00239488();
extern s32 D_00351A48;
#define func_00133520 ((M2C_UNK (*)()) func_00133520)
#define func_0013bd08 ((M2C_UNK (*)()) func_0013bd08)
#define func_0014c378 ((M2C_UNK (*)()) func_0014c378)
#define func_00151808 ((M2C_UNK (*)()) func_00151808)
void func_00122330(void) {
    func_00239488();
    func_00176c60(0);
    func_0013bd08();
    func_0014c378();
    func_001249d8();
    func_0012fc20();
    func_0017ebd0();
    func_0017db68();
    func_00133520();
    func_00146508();
    func_00151808();
    func_001762c8();
    func_00168518();
    D_00351A48 = 6;
    func_001574f0();
}
#undef func_00133520
#undef func_0013bd08
#undef func_0014c378
#undef func_00151808

/* func_001223b8 (from auto/text_00120000_8.c). */
M2C_UNK func_00122c08();
M2C_UNK func_00124a28();
M2C_UNK func_0012fc58();
M2C_UNK func_00148e98();
M2C_UNK func_0014c330();
M2C_UNK func_001590a8();
M2C_UNK func_0016f548();
#define func_0012b738 ((M2C_UNK (*)()) func_0012b738)
#define func_00133520 ((M2C_UNK (*)()) func_00133520)
#define func_001356a8 ((M2C_UNK (*)()) func_001356a8)
#define func_0013bd08 ((M2C_UNK (*)()) func_0013bd08)
#define func_00146590 ((M2C_UNK (*)()) func_00146590)
void func_001223b8(void) {
    func_00176c60(0);
    func_0013bd08();
    func_001590a8();
    func_00124a28();
    func_00133520();
    func_00146590();
    func_00148e98();
    func_0012b738();
    func_00122c08();
    func_0014c330();
    func_001356a8();
    func_0012fc58();
    func_0016f548();
}
#undef func_0012b738
#undef func_00133520
#undef func_001356a8
#undef func_0013bd08
#undef func_00146590

