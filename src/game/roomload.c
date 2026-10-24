/* The rooms' files and the room change (a guess at the name),
 * 0x00112270-0x001137f8: D_002BCC28 holds each world's two-letter prefix
 * ("dh" ... "zz"), func_00112298 / func_00112400 build a room's file name
 * (prefix, "%2d" room number, "00_", ".img"), func_001124f8 reads the room
 * file's header (the entrances D_002BCDA0, the room table D_002BCDAC ...),
 * func_00112840 / func_00112968 / func_001129c8 load a room,
 * func_00113138 ... take an entrance's position, and func_00113558 starts
 * the room. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002A3F50.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "data/types/text_00110000_s8_w7.h"
#include "data/pieces/D_002BCC9C.h"
#include "data/pieces/D_002BCDA4.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E27A4.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/bss_0049.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC148.h"
#include "data/types/text_00100000_h2_p2.h"
#include "data/pieces/D_002BCDC8.h"
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
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"

/* func_00112270 (from auto/text_00110000_6.c). */
M2C_UNK strcpy(s32, s32);
/* The worlds' file prefixes, by world (defined here: only func_00112270
 * reads them). */
extern u8 D_0048CF70[];
extern u8 D_0048CF78[];
extern u8 D_0048CF80[];
extern u8 D_0048CF88[];
extern u8 D_0048CF90[];
extern u8 D_0048CF98[];
extern u8 D_0048CFA0[];
extern u8 D_0048CFA8[];
extern u8 D_0048CFB0[];
extern u8 D_0048CFB8[];
extern u8 D_0048CFC0[];
extern u8 D_0048CFC8[];
extern u8 D_0048CFD0[];
extern u8 D_0048CFD8[];
extern u8 D_0048CFE0[];
extern u8 D_0048CFE8[];
extern u8 D_0048CFF0[];
M2C_UNK D_002BCC28[0x16] ALIGNED(8) = {
    (s32)D_0048CFF0, (s32)D_0048CFE8, (s32)D_0048CFE0, (s32)D_0048CFD8,
    (s32)D_0048CFD0, (s32)D_0048CFC8, (s32)D_0048CFC0, (s32)D_0048CFB8,
    (s32)D_0048CFB0, (s32)D_0048CFA8, (s32)D_0048CFA0, (s32)D_0048CF98,
    (s32)D_0048CF90, (s32)D_0048CF88, (s32)D_0048CFB8, (s32)D_0048CF80,
    (s32)D_0048CF78, (s32)D_0048CFB8, (s32)D_0048CFB8, (s32)D_0048CFB8,
    (s32)D_0048CF70, 0,
};
void func_00112270(s32 arg0, s32 arg1) {
    strcpy(arg1, *(M2C_UNK *)((s8 *)&D_002BCC28 + (arg0 * 4)));
}

/* func_00112298 (from auto/text_00110000_15.c). */
extern M2C_UNK D_0048CFF8;
void sprintf(s32, s32, ...);
void strcat(s32, s32);
#define strcpy ((void (*)(s32, s32)) strcpy)
void func_00112298(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[20];
    func_00112270(arg0, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf((s32) sp, (s32) &D_0048CFF8, arg1 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy(arg3, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat(arg3, (s32) sp);
}
#undef strcpy

/* func_00112320 (from auto/text_00110000_11.c). */
extern M2C_UNK D_002BCC80;
extern M2C_UNK D_002BCC88;
extern M2C_UNK D_002BCD20;
extern s32 D_002BC128;
extern s32 D_002BC130;
#define func_00112270 ((M2C_UNK (*)(s32, M2C_UNK *)) func_00112270)
#define sprintf ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *, s32)) sprintf)
#define strcat ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *)) strcat)
#define strcpy ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *)) strcpy)
void func_00112320(void) {
    s32 sp[20];
    func_00112270(D_002BC128, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf(sp, &D_0048CFF8, D_002BC130 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy((M2C_UNK *)&D_002BCCA0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCCA0, &D_002BCC80);
    strcpy((M2C_UNK *)&D_002BCD60, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCD60, sp);
    strcat((M2C_UNK *)&D_002BCD60, &D_002BCC88);
    strcpy(&D_002BCD20, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat(&D_002BCD20, sp);
}
#undef func_00112270
#undef sprintf
#undef strcat
#undef strcpy

/* func_00112400 (from auto/text_00110000_11.c). */
extern M2C_UNK D_0048D000;
#define func_00112270 ((M2C_UNK (*)(s32, M2C_UNK *)) func_00112270)
#define sprintf ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *, s32)) sprintf)
#define strcat ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *)) strcat)
#define strcpy ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *)) strcpy)
void func_00112400(s32 arg0) {
    s32 sp[20];
    func_00112270(D_002BC128, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf(sp, &D_0048CFF8, arg0 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy((M2C_UNK *)&D_002BCCE0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCCE0, &D_0048D000);
    strcat((M2C_UNK *)&D_002BCCE0, sp);
}
#undef func_00112270
#undef sprintf
#undef strcat
#undef strcpy

/* func_00112498 (from auto/text_00110000.c). */
extern s32 D_002BCC98;
void func_00112498(void) {
    D_002BCC98 = M2C_FIELD(((D_002BC130 << 6) + (*(s32 *)&D_002BCDAC)), s32 *, 4);
}

/* func_001124c0 (from auto/text_00110000.c). */
void func_001124c0(void) {
    D_002BC0A8.i |= 0x20;
}

/* func_001124d8 (from auto/text_00110000.c). */
void func_001124d8(void) {
    D_002BC0A8.i &= ~0x20;
}

/* func_001124f8 (from hand/text_00110000_s8_w7.c). */
typedef struct { s32 x0, x4, x8, xc, x10, x14, x18, x1c, x20, x24, x28, x2c, x30, x34, x38; } MapHdr;
extern MapHdr *D_004D92DC;
extern s32 D_002BCC90;
extern s32 D_002BCDE0;
extern s32 D_002BCC94;
extern u32 D_002BCDB0;
extern s32 D_002BC134;
extern s32 D_002BCDA8;
extern s32 D_002BCDDC;
extern s32 D_002BC12C;
extern s32 D_002BC734;
extern s32 D_002BCDD8;
extern s32 D_002C1360;
extern s32 D_002C1380;
extern s32 D_002BCB30;
extern s32 D_002C1384;
extern s32 D_002C12C0;
extern s32 D_002C1378[2];
s32 func_00111660(s32, s32);
void func_001119d0(void);
void func_00103280(f32, f32, f32, f32);
void func_00110e38(f32, f32, f32, f32);
s32 func_001ed170(s32);
u8 *func_001eaff8(void);
/* func_001124f8: matched in session 8 (w7): func_001ed170 takes one s32 argument, called with D_002C1380. */
void func_001124f8(void) {
    MapHdr *h = D_004D92DC;
    s32 *sub;
    f32 one;
    s32 t;
    sub = (s32 *)((u8 *)h + h->x10);
    D_002BCC90 = (s32)h + h->x18;
    t = D_002BCDD8;
    D_002BCC9C = (s32)h + h->x20;
    D_002BCC94 = (s32)h + h->x30;
    D_002BCDE0 = (s32)h + h->x38;
    D_002BCDAC = (Room *)((u8 *)sub + sub[0]);
    D_002BCDB0 = (u32)sub[1] >> 6;
    D_002BCDA0 = (Room *)((u8 *)sub + sub[2]);
    D_002BCDA4 = (u32)sub[3] >> 6;
    if (t) {
        D_002BC130 = D_002BCDA0[D_002BCDA8].x0;
        D_002BC134 = func_00111660(D_002BC128, D_002BC130);
        func_00112320();
        if (D_002BCDDC == 0) func_001119d0();
    }
    D_002BC12C = D_002BCDAC[D_002BC130].x0;
    one = 1.0f;
    func_00103280(one, one, one, one);
    func_00110e38(one, one, one, one);
    D_002BC734 = D_002BCDAC[D_002BC130].fl.b1;
    if (D_002BC734) func_00110e38(one, 0.9f, one, 0.05f);
    D_002BC0A8.fl0A8.b2 = !D_002BCDAC[D_002BC130].fl.b0;
    D_002BC0A8.fl0A8.b3 = !D_002BCDAC[D_002BC130].fl.b2;
    func_001124c0();
    D_002BCB30 = D_002BCDAC[D_002BC130].fl.b3;
    D_002C12C0 = D_002BCDAC[D_002BC130].fl.b6;
    D_002C1380 = D_002BCDAC[D_002BC130].x14;
    D_002C1360 = D_002BCDAC[D_002BC130].x18;
    D_002C1384 = D_002BCDAC[D_002BC130].x1c;
    (*(s32 (*)[2])&D_002A3F50)[0] = D_002BCDAC[D_002BC130].x20;
    (*(s32 (*)[2])&D_002A3F50)[1] = D_002BCDAC[D_002BC130].x24;
    func_001ed170(D_002C1380);
    D_002C1378[0] = D_002BCDAC[D_002BC130].x8;
    D_002C1378[1] = D_002BCDAC[D_002BC130].xc;
    if (D_002BC128 == 3 && *func_001eaff8() >= 43) {
        D_002C1378[0] = D_002BCDAC[D_002BC130].x28;
        D_002C1378[1] = D_002BCDAC[D_002BC130].x2c;
    }
    D_002E27A4 = 0;
}

/* func_00112820 (from auto/text_00110000_11.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
void func_001017e8();
void func_00112820(void) {
    func_0011ef10(0xC350, &func_001017e8);
}

/* func_00112840 (from auto/text_00110000_12.c). */
M2C_UNK func_00101628();
M2C_UNK func_0011cdf0(M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_00146928(M2C_UNK);
M2C_UNK func_0014a090();
M2C_UNK func_001ec7d0(M2C_UNK);
M2C_UNK func_001ed128(M2C_UNK, M2C_UNK);
void func_00112840(s32 arg0, s32 arg1, s32 arg2) {
    func_001ec7d0(2);
    func_001ed128(3, -9);
    func_00101628();
    func_001ed128(0, -1);
    func_001ed128(3, -1);
    func_001ed128(0, 0);
    func_001ed128(0, 1);
    func_001ed128(1, 0);
    func_001ed128(1, 1);
    func_0014a090();
    func_00146928(-3);
    func_00146928(-4);
    func_00146928(-5);
    func_00146928(-6);
    func_00146928(-7);
    func_001ed128(0, -8);
    func_001ed128(3, -8);
    func_001ed128(3, -0xA);
    func_0011cdf0(-1, arg2, &func_00112820);
}

/* func_00112928 (from auto/text_00110000_11.c). */
M2C_UNK func_0011cb08(void *);
M2C_UNK func_00120748(void *, s32, M2C_UNK *, M2C_UNK);
s32 func_001559f0(M2C_UNK, M2C_UNK);
void func_00112928(void) {
    s32 sp[16];
    func_0011cb08(sp);
    func_00120748(sp, func_001559f0(0x34, 4), &func_00112840, 0);
}

/* func_00112968 (from auto/text_00110000_12.c). */
M2C_UNK func_0010b030(s32);
M2C_UNK func_0010e750();
extern s32 D_002A3F38;
s32 func_001137c8();
#define func_001124f8 ((M2C_UNK (*)()) func_001124f8)
#define func_00112928 ((M2C_UNK (*)()) func_00112928)
#define func_001137c8 ((s32 (*)(s32, M2C_UNK)) func_001137c8)
void func_00112968(void) {
    func_001124f8();
    func_0010e750();
    func_0010b030(D_002BCDE0);
    D_002A3F38 = D_002BCDE0;
    D_002A3F38 = func_001137c8(D_002BCDE0, 0x40);
    func_00112928();
}
#undef func_001124f8
#undef func_00112928
#undef func_001137c8

/* func_001129c8 (from hand/text_00110000_h29.c). */
extern s32 D_002BCDC0;
extern s32 D_002BCDB8;
extern s32 D_002BCDC4;
extern s32 D_002BCDB4;
extern s32 D_002BCDBC;
extern u8 D_009A0000[];
extern s32 D_002BC138;
void func_00176170(void);
void func_001761b0(void);
extern void *D_004D92DC_001129c8 __asm__("D_004D92DC");
#define D_004D92DC D_004D92DC_001129c8
#define func_00120748 ((void (*)(void *, void *, void (*)(void), s32)) func_00120748)
s32 func_001129c8(void) {
    if (D_002BCDBC == 1 && D_002BCDC0 == 0) return 0;
    func_00112320();
    D_002BCDB4 = 0;
    D_002BCDB8 = 0;
    D_002BCDC4 = 1;
    D_004D92DC = D_009A0000;
    func_00176170();
    func_001761b0();
    if (D_002BC138 == D_002BC128) D_002BCDB4 = 1;
    if (D_002BCDB4 == 1) {
        func_001124f8();
        if (D_002BCDD8) func_00112928();
        else func_00112820();
    } else {
        func_00120748(D_002BCCA0, D_004D92DC, func_00112968, 0);
    }
    return 4;
}
#undef D_004D92DC
#undef func_00120748

/* func_00112ad8 (from auto/text_00110000_6.c). */
extern s32 D_002B6474;
void func_00122330(void);
#define func_0011ef10 ((s32 (*)(s32, s32)) func_0011ef10)
s32 func_00112ad8(void) {
    func_001c1f60();
    D_002B6474 = 0;
    func_00122330();
    func_0011ef10(0x2E62F, (s32) &func_001129c8);
    return 4;
}
#undef func_0011ef10

/* func_00112b18 (from auto/text_00110000_7.c). */
M2C_UNK func_00100ae0();
void func_00112b18(void) {
    func_00100ae0();
    func_0011ef10(0x2E630, &func_00112ad8);
}

/* func_00112b48 (from auto/text_00110000_8.c). */
void func_00111600(s32, s32, s32);
#define func_00112b18 ((s32 (*)(void)) func_00112b18)
void func_00112b48(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_002BCDA8 = arg3;
    D_002BC128 = arg0;
    D_002BC130 = arg1;
    D_002BC134 = arg2;
    func_00111600(arg0, arg1, arg2);
    func_00112b18();
}
#undef func_00112b18

/* func_00112b80 (from auto/text_00110000.c). */
#define func_00112b18 ((M2C_UNK (*)()) func_00112b18)
void func_00112b80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_002BCDA8 = arg3;
    D_002BC128 = arg0;
    D_002BC130 = arg1;
    D_002BC134 = arg2;
    func_00112b18();
}
#undef func_00112b18

/* func_00112bb8 (from auto/text_00110000_16.c). */
#define func_00112b18 ((s32 (*)(void)) func_00112b18)
void func_00112bb8(s32 arg0) {
    s32 temp_v0;

    D_002BCDA8 = arg0;
    temp_v0 = *(M2C_UNK *)((s32) ((arg0 << 6)) + (s32) D_002BCDA0);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(D_002BC128, temp_v0);
    func_00112b18();
}
#undef func_00112b18

/* func_00112c08 (from auto/text_00110000_11.c). */
extern s32 D_002A3F40;
void func_00112c08(s32 arg0) {
    D_002A3F40 = arg0;
    D_002BCDC0 = 1;
}

/* func_00112c20 (from hand/text_00110000_h29.c). */
typedef struct { u32 lo:13; u32 b13:1; u32 hi:18; } W29Flg;
extern s32 D_002BC13C;
extern char D_0048D008[];
#define func_00120748 ((void (*)(void *, void *, void (*)(void), s32)) func_00120748)
extern W29Flg D_002C5958_00112c20 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_00112c20
#define strcpy ((char *(*)(char *, const char *)) strcpy)
#define strcat ((char *(*)(char *, const char *)) strcat)
#define func_001559f0 ((void *(*)(s32, s32)) func_001559f0)
#define func_001137c8 ((void *(*)(void *, s32)) func_001137c8)
void func_00112c20(s32 i) {
    char buf[64];
    s32 id;
    if (D_002C5958.b13 == 1) return;
    id = D_002BCDAC[((Ent40_2bcda0 *)D_002BCDA0)[i].id].x0;
    if (D_002BC13C == id) return;
    D_002BCDBC = 1;
    func_00112400(id);
    strcpy(buf, D_002BCCE0);
    strcat(buf, D_0048D008);
    D_002A3F3C = func_001559f0(0x34, 8);
    D_002A3F3C = func_001137c8(D_002A3F3C, 0x80);
    func_00120748(buf, D_002A3F3C, func_00112c08, 0);
}
#undef func_00120748
#undef D_002C5958
#undef strcpy
#undef strcat
#undef func_001559f0
#undef func_001137c8

/* func_00112cf8 (from auto/text_00110000.c). */
M2C_UNK func_0011c898(M2C_UNK);
#define func_00122330 ((M2C_UNK (*)()) func_00122330)
s32 func_00112cf8(void) {
    func_0011c898(0);
    D_002B6474 = 0;
    func_00122330();
    return 4;
}
#undef func_00122330

/* func_00112d28 (from auto/text_00110000_15.c). */
void func_00101728(s32);
void func_0011c7c0(s32, s32, s32);
void func_0011d4e0(s32);
void func_00157668(void);
void func_00112d28(void) {
    func_00157668();
    D_002A3F50[0] = 0;
    D_002A3F50[1] = 0;
    func_0011c7c0(0, 0, 0x168);
    func_0011c7c0(1, 0, 0x168);
    func_0011d4e0(0x168);
    func_00101728(0x168);
}

/* func_00112d80 (from hand/text_00100000_h2.c). */
void func_0012cac8(s32, s32);
s32 func_00109558(s32);
#define func_0011ef10 ((s32 (*)(s32, s32 (*)(void))) func_0011ef10)
extern volatile u32 D_002C5958_00112d80 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_00112d80
s32 func_00112d80(void) {
    func_0012cac8(2, 0);
    func_0012cac8(6, 0);
    D_002C5958 |= 0x80000;
    func_00112d28();
    func_001c1f60();
    func_0011ef10(0x2e630, func_00112cf8);
    D_002BC148[0] = D_002BC128;
    D_002BC148[1] = D_002BC130;
    return func_00109558(4);
}
#undef func_0011ef10
#undef D_002C5958

/* func_00112e08 (from hand/text_00100000_h2.c). */
void func_00113048(void);
#define func_0011ef10 ((s32 (*)(s32, s32 (*)(void))) func_0011ef10)
extern volatile u32 D_002C5958_00112e08 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_00112e08
s32 func_00112e08(void) {
    D_002C5958 |= 0x80000;
    func_00112d28();
    func_001c1f60();
    func_00113048();
    func_0011ef10(0x2e630, func_00112cf8);
    D_002BCDC8.a = D_002BC128;
    D_002BCDC8.b = D_002BC130;
    D_002BCDC8.c = D_002BCDA8;
    return func_00109558(6);
}
#undef func_0011ef10
#undef D_002C5958

/* func_00112e90 (from auto/text_00110000.c). */
void func_00112e90(void) {

}

/* func_00112e98 (from auto/text_00110000_11.c). */
void func_00112e98(void) {
    func_001ec7d0(2);
    func_001ed128(3, -9);
    func_001ed128(0, -1);
    func_001ed128(3, -1);
    func_001ed128(0, 0);
    func_001ed128(0, 1);
    func_001ed128(1, 0);
    func_001ed128(1, 1);
    func_001ed128(0, -8);
    func_001ed128(3, -8);
    func_001ed128(0, -3);
    func_001ed128(3, -3);
    func_001ed128(0, -4);
    func_001ed128(3, -4);
    func_001ed128(0, -5);
    func_001ed128(3, -5);
    func_001ed128(0, -6);
    func_001ed128(3, -6);
    func_001ed128(0, -7);
    func_001ed128(3, -7);
    func_001ed128(3, -0xA);
}

/* func_00112fa0 (from auto/text_00110000_11.c). */
M2C_UNK func_00114820();
#define func_00109558 ((M2C_UNK (*)(M2C_UNK)) func_00109558)
void func_00112fa0(void) {
    func_00114820();
    func_00109558(9);
}
#undef func_00109558

/* func_00112fc0 (from auto/text_00110000_11.c). */
s32 func_00112fc0(void) {
    return D_004D92E0;
}

/* func_00112fd0 (from auto/text_00110000.c). */
void func_00112fd0(s32 arg0) {
    D_004D92E0 = arg0;
}

/* func_00112fe0 (from auto/text_00110000_1.c). */
#define func_00109558 ((M2C_UNK (*)(M2C_UNK)) func_00109558)
#define func_00112fd0 ((M2C_UNK (*)(M2C_UNK)) func_00112fd0)
void func_00112fe0(void) {
    func_00114820();
    func_00112fd0(1);
    func_00109558(8);
}
#undef func_00109558
#undef func_00112fd0

/* func_00113008 (from auto/text_00110000_12.c). */
#define func_001559f0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) func_001559f0)
void *func_00113008(void) {
    return func_001559f0(0x3D, 3);
}
#undef func_001559f0

/* func_00113028 (from auto/text_00110000_12.c). */
#define func_001559f0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK)) func_001559f0)
void func_00113028(void) {
    func_001559f0(0, 0x40);
}
#undef func_001559f0

/* func_00113048 (from hand/text_00100000_h2.c). */
typedef struct Actor_13048 { u8 pad[0x10]; f32 x, y, z; u8 pad2[0x20]; f32 w; } Src;
f32 D_004D92F0[3][4] ALIGNED(16);
void func_00113048(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        Src *s = D_002E26A0[i];
        if (s) {
            D_004D92F0[i][0] = s->x;
            D_004D92F0[i][1] = s->y;
            D_004D92F0[i][2] = s->z;
            D_004D92F0[i][3] = s->w;
        }
    }
}

/* func_001130a0 (from hand/text_00100000_h2.c). */
/* These three only match with func_001130a0 defined above them. */
void func_001130a0(s32 i, f32 *d) {
    d[0] = D_004D92F0[i][0];
    d[1] = D_004D92F0[i][1];
    d[2] = D_004D92F0[i][2];
    d[3] = D_004D92F0[i][3];
}

/* func_001130e0 (from hand/text_00100000_h2.c). */
s32 func_001130e0(void) {
    s32 i;
    for (i = 0; i < D_002BCDA4; i++) {
        if (D_002BC130 == ((Ent40_2bcda0 *)D_002BCDA0)[i].id) return i;
    }
    return 1000;
}

/* func_00113138 (from hand/text_00100000_h2.c). */
extern s32 D_002BBE1C;
void func_00104fd0(s32, f32 *);
void func_00111590(s32, f32 *);
void func_00113138(f32 *out) {
    if (D_002BCDA8 == -1) D_002BCDA8 = func_001130e0();
    if (D_002BCDA8 < D_002BCDA4) {
        out[0] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[0][0];
        out[1] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[0][1];
        out[2] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[0][2];
        out[3] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[0][3];
        if (D_002BCDD8 && D_002BCDDC == 1) func_001130a0(0, out);
        if (D_002BBE1C == 1) func_00111590(0, out);
    } else {
        func_00104fd0(0, out);
    }
}

/* func_00113270 (from hand/text_00100000_h2.c). */
void func_00113270(f32 *out) {
    if (D_002BCDA8 == -1) D_002BCDA8 = func_001130e0();
    if (D_002BCDA8 < D_002BCDA4) {
        out[0] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[1][0];
        out[1] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[1][1];
        out[2] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[1][2];
        out[3] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[1][3];
        if (D_002BCDD8 && D_002BCDDC == 1) func_001130a0(1, out);
        if (D_002BBE1C == 1) func_00111590(1, out);
    } else {
        func_00104fd0(0, out);
    }
}

/* func_001133a0 (from hand/text_00100000_h2.c). */
void func_001133a0(f32 *out) {
    if (D_002BCDA8 == -1) D_002BCDA8 = func_001130e0();
    if (D_002BCDA8 < D_002BCDA4) {
        out[0] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[2][0];
        out[1] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[2][1];
        out[2] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[2][2];
        out[3] = ((Ent40_2bcda0 *)D_002BCDA0)[D_002BCDA8].v[2][3];
        if (D_002BCDD8 && D_002BCDDC == 1) func_001130a0(2, out);
        if (D_002BBE1C == 1) func_00111590(2, out);
    } else {
        func_00104fd0(0, out);
    }
}

/* func_001134d8 (from auto/text_00110000_6.c). */
extern s32 D_002BCDE4;
extern s32 D_002BCDEC;
s32 func_00110360(void);
void func_001134d8(s32 arg0) {
    D_002BCDE4 = arg0;
    if (arg0 != 0) {
        D_002BCDEC = 0;
        func_001c2ec8((s8 *) arg0, 0);
        return;
    }
    func_00110360();
}

/* func_00113518 (from auto/text_00110000_3.c). */
M2C_UNK func_0013c078();
void func_00113518(void) {
    if (D_002BCDD8 != 0) {
        if (D_002BCDDC == 0) {
            func_0013c078();
        }
    }
}

/* func_00113558 (from hand/text_00110000_s6_02.c). */
extern s32 D_002BBE0C;
extern s32 D_0029B414;
extern s32 D_0029B410;
extern s32 D_002B6774;
extern s32 D_002C1388;
s32 func_00105860(void);
void func_0017f678(void);
void func_00132550(void);
void func_00175f58(s32, s32, s32, s32);
void func_00100ab0(void);
void func_00114830(void);
void func_001115e0(void);
void func_00111380(void);
void func_001118c0(void);
void func_001ec7c0(s32);
#define D_002C5958 (*(volatile u32 (*)) &D_002C5958)
s32 func_00113558(void) {
    if (D_002B6774) return 0;
    D_002BBE0C = 1;
    func_00105860();
    func_0017f678();
    func_00132550();
    D_002BCDEC = 1;
    if (D_0029B410 && D_0029B414) func_00175f58(D_0029B410, D_0029B414, D_002BC130 + 1, 100000);
    func_00100ab0();
    { Fl_2c5958 *p = (Fl_2c5958 *)&D_002C5958; p->b2 = 0; p->b27 = 0; }
    func_001c3770((s8 *)D_002BCC90, 0);
    D_002BCDBC = 0;
    D_002BCDC0 = 0;
    D_002BCDD8 = 0;
    func_00114830();
    D_002C1388 = 0;
    if (D_002BBE1C == 1 || D_002B6474 == 1) func_001115e0();
    D_002BBE1C = 0;
    func_00111380();
    func_001118c0();
    func_001ec7c0(0);
    D_002BCDC4 = 0;
    return 4;
}
#undef D_002C5958

/* func_00113688 (from auto/text_00110000_11.c). */
void func_00113688(void) {
    func_0011ef10(0xC2EC, &func_00113558);
}

/* func_001136a8 (from auto/text_00110000_12.c). */
M2C_UNK func_00122198(s32, M2C_UNK *);
extern s32 D_002BCDF0;
#define func_00113518 ((void (*)(void)) func_00113518)
void func_001136a8(void) {
    func_00113518();
    func_00122198(D_002BCDF0, &func_00113688);
}
#undef func_00113518

/* func_001136d8 (from hand/text_00110000_s6_02b.c). */
extern s32 D_002BCDE8;
void func_0013c6d8(void);
s32 func_001148c8(void);
void func_0011e9a8(void *, s32);
#define func_001559f0 ((s32 (*)(s32, s32)) func_001559f0)
void func_001136d8(void) {
    if (D_002B6474 == 1) func_0013c6d8();
    func_001148c8();
    if (D_002BCDE8 == 0) {
        D_002C1388 = 1;
        func_0011e9a8(func_001136a8, func_001559f0(52, 4));
        return;
    }
    func_001136a8();
}
#undef func_001559f0

/* func_00113768 (from hand/text_00110000_s6_02b.c). */
void func_00101680(void);
#define func_00120748 ((s32 (*)(void *, s32, void (*)(void), s32)) func_00120748)
s32 func_00113768(void) {
    s32 t;
    func_00112498();
    func_00101680();
    t = func_001137c8(D_002BCDF0, 128);
    D_002BCDF0 = t;
    func_00120748(D_002BCD60, t, func_001136d8, 0);
    return 4;
}
#undef func_00120748

/* func_001137c8 (from auto/text_00110000.c). */
s32 func_001137c8(s32 arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = arg0;
    if ((var_a0 % arg1) != 0) {
        var_a0 = ((var_a0 / arg1) * arg1) + arg1;
    }
    return var_a0;
}

