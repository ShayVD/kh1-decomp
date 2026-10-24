/* The game over's continue (a guess), 0x0011c5e8-0x0011c768: func_0011c710
 * resets the frame state, opens the choice func_0022eb00 and starts the task
 * func_0011c698, which on choice 0 goes to phase 0xA (func_00109558) and on 1
 * opens the load screen (func_0022bcb8) and waits in func_0011c630 for it to
 * close; func_0011c5e8 applies a setting of src/menu/settings.c.  Read from
 * the code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BD250.h"
#include "data/types/text_00110000_h3.h"
#include "data/types/text_00110000_h3_p.h"

/* func_0011c5e8 (from auto/text_00110000_3.c). */
M2C_UNK func_002193e0(M2C_UNK);
extern s32 D_002B6478;
s32 func_002193b8();
void func_0011c5e8(void) {
    if ((func_002193b8() == 1) && (D_002B6478 != 2)) {
        func_002193e0(0);
    }
}

/* func_0011c630 (from auto/text_00110000_6.c). */
extern s32 D_003F34A4;
extern s32 D_003F720C;
void func_00109558(s32);
void func_0011c710(void);
void func_001c07a8(void);
s32 func_0011c630(void) {
    if (D_003F34A4 == 0) {
        if (D_003F720C == 1) {
            func_0011c5e8();
            func_00109558(0xF);
            func_001c07a8();
            return 4;
        }
        func_0011c710();
        return 4;
    }
    return 0;
}

/* func_0011c698 (from auto/text_00110000_5.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0022bcb8(M2C_UNK);
extern s32 D_003F7774;
extern s32 D_003F7778;
#define func_00109558 ((M2C_UNK (*)(M2C_UNK)) func_00109558)
s32 func_0011c698(void) {
    if (D_003F7774 == 0) {
        switch (D_003F7778) {                       /* irregular */
        case 0:
            func_00109558(0xA);
            return 4;
        case 1:
            func_0022bcb8(0xFFFF);
            func_0011ef10(0x7530, &func_0011c630);
            return 4;
        default:
            return 0;
        }
    } else {
        return 0;
    }
}
#undef func_00109558

/* func_0011c710 (from hand/text_00110000_h3.c). */
extern s32 D_002BBE0C;
extern s32 D_002C1304;
void func_00114820(void);
void func_0017f678(void);
void func_0022eb00(s32);
void func_0011e518(void);
void func_0011d688(s32);
#define func_0011ef10 ((void (*)(s32, void *)) func_0011ef10)
void func_0011c710(void) {
    D_002BBE0C = 0;
    D_002C1304 = 1;
    func_00114820();
    func_0017f678();
    func_0022eb00(0xffff);
    func_0011e518();
    func_0011ef10(30000, func_0011c698);
    func_0011d688(120);
}
#undef func_0011ef10

