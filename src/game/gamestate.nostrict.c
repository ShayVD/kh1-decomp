/* The boot and the game's states (gamestate.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s6_01_p2.h"
#include "data/types/nostrict_text_00100000_s6_01.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F30.h"
#include "data/types/nostrict_text_00100000_s6_01_p.h"
#include "data/pieces/D_002BBDE0.h"

/* func_00109388 (from hand/nostrict/text_00100000_s6_01.c). */
extern volatile s32 D_002BBE08;
extern s32 D_002BBD40;
extern volatile s32 D_00495164;
extern volatile s32 D_00495160;
extern f32 D_002BBE00;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC12C;
extern s32 D_002BC134;
extern s32 D_003F34A4;
extern u8 D_009A0000[];
extern void func_00111000(void);
extern void func_0010fe80(void);
extern void func_00109268(void);
extern void func_0010c240(void);
extern void func_00120aa0(void);
extern void func_0011edc8(void);
extern void func_0011c9c0(void);
extern void func_00110458(void);
extern void func_001103a0(void);
extern void func_00100278(void);
extern void func_001117e0(void);
extern void func_001759a8(void);
extern void func_001ee520(void);
extern void func_001c0750(void);
extern void func_001ba798(void);
extern void func_00236f00(void);
extern void func_0010fc38(void);
extern void func_0010c3c0(void);
extern void func_0011cb80(void *);
extern void func_0011cd20(s32, void *, s32);
extern void func_0010fc98(void);
extern void func_001ef950(void);
extern void func_001559f0(s32, s32);
extern void func_001104e0(void);
extern void func_00105f28(void);
extern void func_0010ff60(s32);
void func_00109388(void) {
    D_002BBE08 = 1;
    D_002BBD40 = 0;
    func_00111000();
    func_0010fe80();
    func_00109268();
    func_0010c240();
    func_00120aa0();
    func_0011edc8();
    D_00495164 = D_002BBDE0 = 0;
    D_00495160 = 0;
    D_002BBE00 = 1.0f;
    D_002BC128 = 0;
    D_002BC12C = 0;
    D_002BC130 = 0;
    D_002BC134 = 0;
    func_0011c9c0();
    func_00110458();
    func_001103a0();
    func_00100278();
    func_001117e0();
    func_001759a8();
    func_001ee520();
    D_003F34A4 = 0;
    func_001c0750();
    func_001ba798();
    func_00236f00();
    func_0010fc38();
    func_0010c3c0();
    func_0011cb80(D_009A0000);
    func_0011cd20(2, D_009A0000, 0);
    func_0010fc98();
    func_001ef950();
    func_001559f0(0, 64);
    func_001104e0();
    func_00105f28();
    func_0010ff60(0);
}

