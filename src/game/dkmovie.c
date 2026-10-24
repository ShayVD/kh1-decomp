/* The movie overlay, 0x00110fc8-0x00111288: func_00111020 loads dkmovie.x
 * to D_00F20000 (func_00120748) with func_00110fc8 as its callback, and the
 * small wrappers call the overlay's entry with a command (0 start, 1 to 9);
 * func_00111238 stops the disc reads and resets the IPU (platform code: the
 * MPEG decoder). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "data/bss_0049.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BBDE0.h"

/* func_00110fc8 (from auto/text_00110000_16.c). */
extern s32 D_002BCAE0;
void D_00F20000(M2C_UNK, s32);
void FlushCache(M2C_UNK);
void func_00110fc8(void) {
    D_002BCAE0 = 1;
    FlushCache(2);
    D_00F20000(0, D_004D9244);
}

/* func_00111000 (from auto/text_00110000.c). */
extern s32 D_002A6B80;
extern s32 D_002BCB34;
void func_00111000(void) {
    D_002A6B80 = 0;
    D_002BCAE0 = 0;
    D_002BCB34 = 0;
}

/* func_00111020 (from auto/text_00110000.c).  It loads the overlay
 * dkmovie.x to D_00F20000, which the others call as a function: the load
 * address is viewed as data here. */
M2C_UNK func_00120748(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_0048CF30;
extern M2C_UNK D_00F20000_data __asm__("D_00F20000");
void func_00111020(s32 arg0) {
    D_004D9244 = arg0;
    D_002BCAE0 = 0;
    func_00120748(&D_0048CF30, &D_00F20000_data, (M2C_UNK *) &func_00110fc8, 0);
}

/* func_00111060 (from auto/text_00110000_1.c). */
M2C_UNK func_00113e28(M2C_UNK);
M2C_UNK func_001edb48(M2C_UNK);
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_00111060(void) {
    func_00113e28(2);
    func_001edb48(0x7B);
    D_00F20000(1, 0);
}
#undef D_00F20000

/* func_00111090 (from hand/text_00100000_h2.c). */
#define D_00F20000 ((s32 (*)(s32, s32)) D_00F20000)
s32 func_00111090(void) {
    if (!D_002BCAE0) return 0;
    return D_00F20000(2, 0);
}
#undef D_00F20000

/* func_001110d0 (from auto/text_00110000_1.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_001110d0(void) {
    D_00F20000(3, 0);
}
#undef D_00F20000

/* func_001110f0 (from auto/text_00110000_1.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_001110f0(void) {
    D_00F20000(8, 0);
}
#undef D_00F20000

/* func_00111110 (from auto/text_00110000_1.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_00111110(void) {
    D_00F20000(9, 0);
}
#undef D_00F20000

/* func_00111130 (from auto/text_00110000_1.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_00111130(void) {
    D_00F20000(4, 0);
}
#undef D_00F20000

/* func_00111150 (from auto/text_00110000_11.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_00111150(void) {
    D_00F20000(5, 0);
}
#undef D_00F20000

/* func_00111170 (from auto/text_00110000_12.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, s32)) D_00F20000)
void func_00111170(s32 arg0) {
    D_00F20000(6, arg0);
}
#undef D_00F20000

/* func_00111190 (from auto/text_00110000_1.c). */
#define D_00F20000 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) D_00F20000)
void func_00111190(void) {
    D_00F20000(7, 0);
}
#undef D_00F20000

/* func_001111b0 (from auto/text_00110000_11.c). */
extern s32 D_002A3F44;
extern s32 D_002BBE04;
extern s32 D_002BBE18;
void func_001017b8(void);
void func_00114830(void);
#define func_00113e28 ((void (*)(s32)) func_00113e28)
#define func_001edb48 ((void (*)(s32)) func_001edb48)
void func_001111b0(void) {
    if ((D_002BBDE0 == 3) && (D_002A3F44 == 1)) {
        D_002A3F44 = 0;
        func_001017b8();
    }
    func_001edb48(9);
    func_00114830();
    D_002BBE04 = 3;
    D_002BBE18 = 0;
    func_00111130();
    D_002BCAE0 = 0;
    D_002BCB34 = 1;
    func_00113e28(0);
}
#undef func_00113e28
#undef func_001edb48

/* func_00111238 (from auto/text_00110000_11.c). */
M2C_UNK func_0024b138();
M2C_UNK func_0026aaa0();
M2C_UNK func_0026ab38();
M2C_UNK func_0026abf0();
M2C_UNK sceCdRead(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceIpuInit();
M2C_UNK sceIpuSync();
void func_00111238(void) {
    sceCdRead(0, 0, 0, 0);
    func_0024b138();
    func_0026ab38();
    func_0026abf0();
    func_0026aaa0();
    sceIpuInit();
    sceIpuSync();
}

