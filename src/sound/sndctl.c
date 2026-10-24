/* Sound control over the IOP driver (src/sound/snd_rpc.c): one-call wrappers
 * of the driver (func_0011c7a8 ... func_0011c880), the sound-effect slots
 * D_004E3450 (count D_004E344C: func_0011cfa8 starts one, func_0011d350 /
 * func_0011d3c8 / func_0011d448 stop or change one), func_0011d768 a system
 * sound (144 callers), the music tracks D_002C1368 / D_002C1378
 * (func_0011e7f8, func_0011e8d0 load and start one; func_0011e610 the volume
 * fades), the bank and file names built with sprintf (func_0011ca68,
 * func_0011ea40, func_0011eae0) and the bank loads (func_0011cbe0,
 * func_0011eb88, func_0011ec08). The names are guesses from the calls. Flag
 * mode: default (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
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
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BD250.h"
#include "data/types/text_00110000_h3.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/types/text_00110000_h3_p.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002B1C60.h"
#include "data/types/text_00110000_b01.h"
#include "data/types/text_00110000_b01_p2.h"
#include "data/types/text_00110000_b01_p.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A6238.h"
#include "platform/math.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/pieces/D_002C5C80.h"
#include "data/types/text_00110000_h4.h"
#include "data/types/text_00110000_h30_p.h"

/* func_0011c768 (from auto/text_00110000.c). */
extern s32 D_002C1308;
void func_0011c768(s32 arg0) {
    D_002C1308 = arg0;
}

/* func_0011c778 (from auto/text_00110000.c). */
void func_0011c778(void) {
    D_002C1308 = 0;
}

/* func_0011c788 (from auto/text_00110000.c). */
extern s32 D_002C130C;
void func_0011c788(void) {
    D_002C130C = 1;
}

/* func_0011c798 (from auto/text_00110000.c). */
void func_0011c798(void) {
    D_002C130C = 0;
}

/* func_0011c7a8 (from auto/text_00110000.c). */
M2C_UNK func_001ed4b8();
void func_0011c7a8(void) {
    func_001ed4b8();
}

/* func_0011c7c0 (from auto/text_00110000.c). */
M2C_UNK func_001ed560();
void func_0011c7c0(void) {
    func_001ed560();
}

/* func_0011c7d8 (from auto/text_00110000.c). */
s32 func_001ed520(s32);
void func_0011c7d8(s32 a) {
    func_001ed520(a);
}

/* func_0011c7f0 (from auto/text_00110000.c). */
M2C_UNK func_001ed5a8();
void func_0011c7f0(void) {
    func_001ed5a8();
}

/* func_0011c808 (from auto/text_00110000.c). */
M2C_UNK func_001ed600();
void func_0011c808(void) {
    func_001ed600();
}

/* func_0011c820 (from auto/text_00110000.c). */
M2C_UNK func_001ecfd8();
void func_0011c820(void) {
    func_001ecfd8();
}

/* func_0011c838 (from auto/text_00110000.c). */
M2C_UNK func_001ed278();
void func_0011c838(void) {
    func_001ed278();
}

/* func_0011c850 (from auto/text_00110000.c). */
s32 func_001ed2d8(s32, s32, s32);
void func_0011c850(s32 a, s32 b, s32 c) {
    func_001ed2d8(a, b, c);
}

/* func_0011c868 (from auto/text_00110000.c). */
s32 func_001ed370(s32, s32, s32, s32, s32);
void func_0011c868(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_001ed370(a, b, c, d, e);
}

/* func_0011c880 (from auto/text_00110000.c). */
M2C_UNK func_001ed3c0();
void func_0011c880(void) {
    func_001ed3c0();
}

/* func_0011c898 (from hand/text_00110000_h30.c). */
typedef struct { s32 id, x4, x8, handle, x10; u8 active, x15, kind, x17; } SndSlot_1c898;
extern SndSlot_1c898 *D_004E3450;
extern Slot12 *D_004E3454;
extern SndSlot D_004E3458[];
Slot12 D_004E3818[0x28] ALIGNED(8);
extern Pair D_004E39F8[];
void *func_001559f0(s32, s32);
extern SndSlot_1c898 D_004E3458_0011c898[] __asm__("D_004E3458");
#define D_004E3458 D_004E3458_0011c898
void func_0011c898(s32 a0) {
    s32 i;
    SndSlot_1c898 *e;
    Slot12 *p;
    if (a0 == 0) {
        D_004E3450 = D_004E3458;
        D_004E3454 = D_004E3818;
        D_004E344C = 40;
    } else {
        D_004E3450 = func_001559f0(16, 1);
        D_004E3454 = func_001559f0(17, 1);
        D_004E344C = 128;
    }
    e = D_004E3450;
    p = D_004E3454;
    for (i = 0; i < D_004E344C; i++, e++, p++) {
        e->active = 0;
        p->x0 = 0;
        p->x4 = 0;
        p->x8 = 0;
    }
    for (i = 0; i < 4; i++) {
        D_004E39F8[i].a = 0;
        D_004E39F8[i].b = 0;
    }
}
#undef D_004E3458

/* func_0011c9a0 (from auto/text_00110000.c). */
void func_0011c9a0(void) {
    D_004E3A40 = 0;
}

/* func_0011c9b0 (from auto/text_00110000.c). */
void func_0011c9b0(void) {
    D_004E3A40 = 1;
}

/* func_0011c9c0 (from auto/text_00110000_3.c). */
M2C_UNK func_00101628();
M2C_UNK func_00113df8(M2C_UNK);
M2C_UNK func_001ed128(M2C_UNK, M2C_UNK);
M2C_UNK func_001ed170(M2C_UNK);
M2C_UNK func_001edba0();
#define func_0011c898 ((M2C_UNK (*)(M2C_UNK)) func_0011c898)
#define func_0011c9a0 ((M2C_UNK (*)()) func_0011c9a0)
#define func_001ed2d8 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK)) func_001ed2d8)
#define func_001ed520 ((M2C_UNK (*)(M2C_UNK)) func_001ed520)
void func_0011c9c0(void) {
    func_0011c9a0();
    func_0011c898(0);
    func_001ed520(0);
    func_001ed520(1);
    func_001ed2d8(-0x64, -1, -1);
    func_001ed128(0, 0);
    func_001ed128(0, 1);
    func_001ed128(1, 0);
    func_001ed128(1, 1);
    func_001ed128(0, -8);
    func_001ed128(3, -8);
    func_001ed170(0xA);
    func_00113df8(0);
    func_001edba0();
    func_00101628();
}
#undef func_0011c898
#undef func_0011c9a0
#undef func_001ed2d8
#undef func_001ed520

/* func_0011ca68 (from hand/text_00110000_h3.c). */
typedef struct {
    char c[13];
} Str13;
extern char D_0048D110[];
extern Str13 D_0048D118;
extern char D_0048D128[];
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
void func_0011ca68(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D110, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    *(Str13 *)a1 = D_0048D118;
    strcat(a1, buf);
    strcat(a1, D_0048D128);
}

/* func_0011cb08 (from hand/text_00110000_h3.c). */
extern s32 D_002BC128;
extern Str10 D_0048D130;
void func_00112270(s32, char *);
void func_0011cb08(char *a0) {
    char buf[16];
    *(Str10 *)a0 = D_0048D130;
    func_00112270(D_002BC128, buf);
    strcat(a0, buf);
    strcat(a0, D_0048D128);
}

/* func_0011cb80 (from auto/text_00110000_11.c). */
M2C_UNK func_001205f0(M2C_UNK *, s32);
extern M2C_UNK D_0048D140;
void func_0011cb80(s32 arg0) {
    func_001205f0(&D_0048D140, arg0);
}

/* func_0011cba0 (from hand/text_00110000_h3.c). */
extern void (*D_004E3430)(void);
#define func_001ecfd8 ((s32 (*)(void)) func_001ecfd8)
s32 func_0011cba0(void) {
    if (func_001ecfd8()) return 0;
    if (D_004E3430) D_004E3430();
    return 4;
}
#undef func_001ecfd8

/* func_0011cbe0 (from hand/text_00110000_h30.c). */
typedef struct { s32 off, size; } Chunk;
typedef struct { u8 pad[16]; Chunk c[2]; } SndHdr;
extern s32 D_002C1368[];
void func_001ed460(s32, void *, s32);
void func_001ed658(s32, void *, s32);
void *func_0011ef10(s32, void *);
#define func_001ed128 ((s32 (*)(s32, s32)) func_001ed128)
void func_0011cbe0(s32 a0, SndHdr *a1, s32 a2, void (*a3)(void)) {
    Chunk *c = &a1->c[0];
    s32 off0 = c->off, sz0 = c->size;
    s32 off1, sz1;
    u8 *p0, *p1;
    c = &a1->c[1];
    off1 = c->off; sz1 = c->size;
    D_004E3430 = a3;
    p0 = (u8 *)a1 + off0;
    if (((s32 *)(p1 = (u8 *)a1 + off1))[1] > 0x7547f) {
        func_001ed128(0, 0);
        func_001ed128(1, 0);
        func_001ed128(0, 1);
        func_001ed128(1, 1);
        D_002C1368[1] = D_002C1368[0] = -2;
        if (a0 == 1) {
            a0 = 0;
            goto skip;
        }
    }
    D_002C1368[a0] = a2;
    func_001ed128(0, a0);
    func_001ed128(1, a0);
skip:
    func_001ed460(a0, p0, sz0);
    func_001ed658(a0, p1, sz1);
    func_0011ef10(10000, func_0011cba0);
}
#undef func_001ed128

/* func_0011cd20 (from hand/text_00110000_s6_03.c). */
typedef struct { s32 off; s32 size; } Chunk_1cd20;
typedef struct { u8 pad[16]; Chunk_1cd20 c[2]; } SndHdr_1cd20;
s32 func_001ed220();
void func_001104e0(void);
#define func_001ed128 ((void (*)(s32, s32)) func_001ed128)
#define func_001edba0 ((void (*)(void)) func_001edba0)
#define func_001ecfd8 ((s32 (*)(void)) func_001ecfd8)
void func_0011cd20(s32 a0, SndHdr_1cd20 *a1, void (*a3)(void)) {
    Chunk_1cd20 *c = &a1->c[0];
    s32 off0 = c->off, sz0 = c->size;
    s32 off1, sz1;
    u8 *p0, *p1;
    c = &a1->c[1];
    off1 = c->off; sz1 = c->size;
    D_004E3430 = a3;
    p0 = (u8 *)a1 + off0;
    p1 = (u8 *)a1 + off1;
    func_001ed128(0, 2);
    func_001ed128(2, 2);
    func_001ed220(a0, p0, sz0);
    func_001ed658(a0, p1, sz1);
    func_001edba0();
    while (!func_001ecfd8()) func_001104e0();
}
#undef func_001ed128
#undef func_001edba0
#undef func_001ecfd8

/* func_0011cdf0 (from hand/text_00110000_s6_03.c). */
typedef struct { s32 off; s32 size; } Chunk_1cdf0;
extern char D_0048D158[];
s32 strcmp(const char *, const char *);
typedef struct { s32 n; u8 pad[12]; Chunk_1cdf0 c[1]; } SndHdr2;
#define func_001ed128 ((void (*)(s32, s32)) func_001ed128)
#define func_0011ef10 ((void (*)(s32, void (*)(void))) func_0011ef10)
void func_0011cdf0(s32 a0, SndHdr2 *h, void (*cb)(void)) {
    s32 i, cnt, total, n;
    Chunk_1cdf0 *c;
    u8 *p0;
    Chunk_1cdf0 *c0;
    char *s;
    cnt = 0;
    total = 0;
    c = c0 = h->c;
    n = h->n;
    p0 = (u8 *)h + c->off;
    for (i = 0; i < n; i++, c++) {
        s = (char *)h + c->off;
        if (strcmp(s, D_0048D158) == 0) {
            cnt++;
            total += *(s32 *)(s + 12) + 16;
        }
    }
    if (cnt) {
        func_001ed128(0, a0);
        func_001ed128(3, a0);
        func_001ed220(a0, p0, total);
        c = c0 + cnt;
        for (i = 0; i < n - cnt; i++, c++) {
            func_001ed658(a0, (u8 *)h + c->off, c->size);
        }
        D_004E3430 = cb;
        func_0011ef10(10000, func_0011cba0);
    } else {
        cb();
    }
}
#undef func_001ed128
#undef func_0011ef10

/* func_0011cf88 (from auto/text_00110000_6.c). */
void func_0011cf88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, void *arg5, s32 arg6) {
    M2C_FIELD(arg5, s32 *, 0xC) = arg6;
    M2C_FIELD(arg5, s32 *, 0) = arg0;
    M2C_FIELD(arg5, s32 *, 0x10) = arg1;
    M2C_FIELD(arg5, s32 *, 4) = arg2;
    M2C_FIELD(arg5, s32 *, 8) = arg3;
    M2C_FIELD(arg5, s8 *, 0x16) = arg4;
    M2C_FIELD(arg5, s8 *, 0x15) = 0;
}

/* func_0011cfa8 (from hand/text_00110000_h3.c). */
extern SndSlot *D_004E3450_0011cfa8 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011cfa8
#define func_0011cf88 ((void (*)(s32, s32, s32, s32, s32, SndSlot *, s32)) func_0011cf88)
SndSlot *func_0011cfa8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active == 0) {
            func_0011cf88(a0, a1, a2, a3, t0, e, a0 < 1000 ? 2 : -1);
            return e;
        }
    }
    return 0;
}
#undef D_004E3450
#undef func_0011cf88

/* func_0011d028 (from hand/text_00110000_h3.c). */
void func_0011d028(s32 a0, s32 a1) {
    s32 i;
    Slot12 *p = D_004E3454;
    for (i = 0; i < D_004E344C; i++, p++) {
        if (!p->x0) goto found;
    }
found:
    p->x0 = a0;
    p->x4 = a1;
    p->x8 = 2;
}

/* func_0011d080 (from hand/text_00110000_h3.c). */
#define func_0011c838 ((void (*)(s32, s32, s32, s32, s32)) func_0011c838)
void func_0011d080(s32 a0, s32 a1) {
    func_0011c838(a0 < 1000 ? 2 : -8, a0, a1, 0x3fff, 0x3fff);
    func_0011d028(a0, a1);
}
#undef func_0011c838

/* func_0011d0d8 (from hand/text_00110000_h3.c). */
#define func_0011c850 ((void (*)(s32, s32, s32)) func_0011c850)
void func_0011d0d8(s32 a0, s32 a1) {
    func_0011c850(a0 < 1000 ? 2 : -8, a0, a1);
}
#undef func_0011c850

/* func_0011d108 (from hand/text_00110000_h3.c). */
#define func_0011c868 ((void (*)(s32, s32, s32, s32, s32)) func_0011c868)
void func_0011d108(s32 a0, s32 a1, s32 a2) {
    func_0011c868(a0 < 1000 ? 2 : -8, a0, a1, -1, a2);
}
#undef func_0011c868

/* func_0011d140 (from hand/text_00110000_h3.c). */
#define func_0011c838 ((void (*)(s32, s32, s32, s32, s32)) func_0011c838)
void func_0011d140(s32 a0, s32 a1) {
    func_0011c838(a0 < 1000 ? 2 : -1, a0, a1, 0x3fff, 0x3fff);
}
#undef func_0011c838

/* func_0011d178 (from hand/text_00110000_h3.c). */
#define func_0011c850 ((void (*)(s32, s32, s32)) func_0011c850)
void func_0011d178(s32 a0, s32 a1) {
    func_0011c850(a0 < 1000 ? 2 : -1, a0, a1);
}
#undef func_0011c850

/* func_0011d1a8 (from hand/text_00110000_h3.c). */
#define func_0011c868 ((void (*)(s32, s32, s32, s32, s32)) func_0011c868)
void func_0011d1a8(s32 a0, s32 a1, s32 a2) {
    func_0011c868(a0 < 1000 ? 2 : -1, a0, a1, -1, a2);
}
#undef func_0011c868

/* func_0011d1e0 (from auto/text_00110000_6.c). */
#define func_0011cfa8 ((s32 (*)(s32, s32, s32, s32, s32)) func_0011cfa8)
void func_0011d1e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 1;
    }
}
#undef func_0011cfa8

/* func_0011d210 (from auto/text_00110000_6.c). */
#define func_0011cfa8 ((s32 (*)(s32, s32, s32, s32, s32)) func_0011cfa8)
void func_0011d210(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 1);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}
#undef func_0011cfa8

/* func_0011d240 (from auto/text_00110000_6.c). */
#define func_0011cfa8 ((s32 (*)(s32, s32, s32, s32, s32)) func_0011cfa8)
void func_0011d240(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 2);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 1;
    }
}
#undef func_0011cfa8

/* func_0011d270 (from auto/text_00110000_6.c). */
#define func_0011cfa8 ((s32 (*)(s32, s32, s32, s32, s32)) func_0011cfa8)
void func_0011d270(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 3);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}
#undef func_0011cfa8

/* func_0011d2a0 (from auto/text_00110000_6.c). */
#define func_0011cfa8 ((s32 (*)(s32, s32, s32, s32, s32)) func_0011cfa8)
void func_0011d2a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 4);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}
#undef func_0011cfa8

/* func_0011d2d0 (from hand/text_00110000_h3.c). */
void func_001ed320(s32, s32, s32, s32);
void func_0011d2d0(s32 a0, s32 a1, s32 a2) {
    s32 i;
    SndSlot *e = D_004E3458;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            func_001ed320(e->handle, a0, a1, a2);
            return;
        }
    }
}

/* func_0011d350 (from hand/text_00110000_s6_03.c). */
extern SndSlot *D_004E3450_0011d350 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d350
void func_0011d350(s32 a0, s32 a1) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            e->active = 0;
            func_0011c850(e->handle, a0, a1);
            return;
        }
    }
}
#undef D_004E3450

/* func_0011d3c8 (from hand/text_00110000_s6_03.c). */
extern SndSlot *D_004E3450_0011d3c8 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d3c8
void func_0011d3c8(s32 a0, s32 a1, s32 a2) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            e->active = 0;
            func_0011c868(e->handle, a0, a1, -1, a2);
            return;
        }
    }
}
#undef D_004E3450

/* func_0011d448 (from hand/text_00110000_s6_03.c). */
extern SndSlot *D_004E3450_0011d448 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d448
void func_0011d448(void) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 4) {
            e->active = 0;
            func_0011c850(e->handle, e->id, e->x10);
        }
    }
}
#undef D_004E3450

/* func_0011d4e0 (from hand/text_00110000_s6_03.c). */
extern SndSlot *D_004E3450_0011d4e0 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d4e0
void func_0011d4e0(s32 a0) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 4) {
            e->active = 0;
            func_0011c868(e->handle, e->id, e->x10, -1, a0);
        }
    }
}
#undef D_004E3450

/* func_0011d588 (from hand/text_00110000_h3.c). */
#define func_0011d240 ((void (*)(s32, s32, void *, s32)) func_0011d240)
void func_0011d588(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        func_0011d240(((s32 *)&D_002A3F50)[i], i, D_002BCAF0, 0x3fff);
    }
}
#undef func_0011d240

/* func_0011d5f0 (from hand/text_00110000_s6_03.c). */
extern SndSlot *D_004E3450_0011d5f0 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d5f0
void func_0011d5f0(void) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 2) {
            e->active = 0;
            func_0011c850(e->handle, e->id, e->x10);
        }
    }
}
#undef D_004E3450

/* func_0011d688 (from auto/text_00110000_13.c). */
#define func_0011c868 ((f32 (*)(M2C_UNK, s32, s32, M2C_UNK, s32)) func_0011c868)
void func_0011d688(s32 arg0) {
    s32 *var_s1;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = ((s32 *)&D_002A3F50);
    do {
        temp_a1 = *var_s1;
        var_s1 += 1;
        temp_a2 = var_s0;
        var_s0 += 1;
        func_0011c868(-1, temp_a1, temp_a2, -1, arg0);
    } while (var_s0 < 2);
}
#undef func_0011c868

/* func_0011d6f0 (from hand/text_00110000_h3.c). */
s32 func_001ecb08(s32, s32, s32);
extern SndSlot *D_004E3450_0011d6f0 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011d6f0
s32 func_0011d6f0(s32 a0, s32 a1) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) return func_001ecb08(e->handle, a0, a1);
    }
    return 0;
}
#undef D_004E3450

/* func_0011d768 (from auto/text_00110000_6.c). */
#define func_0011c838 ((M2C_UNK (*)(M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK)) func_0011c838)
void func_0011d768(s32 arg0) {
    func_0011c838(2, arg0, 0, 0x3FFF, 0x3FFF);
}
#undef func_0011c838

/* func_0011d790 (from hand/text_00110000_h3.c). */
#define func_0011c880 ((void (*)(s32, s32, s32, s32, s32)) func_0011c880)
void func_0011d790(s32 a0, s32 a1) {
    s32 v = 0x3fff;
    if (a1) v = 0x1fff;
    func_0011c880(2, a0, 0, v, v);
}
#undef func_0011c880

/* func_0011d7c0 (from auto/text_00110000_1.c). */
#define func_0011c850 ((M2C_UNK (*)(M2C_UNK, s32, M2C_UNK)) func_0011c850)
void func_0011d7c0(s32 arg0) {
    func_0011c850(2, arg0, 0);
}
#undef func_0011c850

/* func_0011d7e0 (from hand/text_00110000_b01.c). */
typedef struct { s32 id; f32 *pos; s32 x8, handle, x10; u8 active, on, kind, x17; } Snd01;
extern s32 D_002C1370;
extern s32 D_003F34A4;
extern s32 D_002C1360;
extern s32 D_002C1384;
extern V4_01 D_004E3A20;
extern V4_01 D_004E3A30;
s32 func_00104f10(f32 *, V4_01);
s32 func_00119fc0(f32 *, V4_01, V4_01, V4_01, f32 *);
s32 func_00119ad8(s32, f32 *, V4_01, V4_01, V4_01, f32 *);
static inline f32 vd01(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
/* Split out of func_0011d7e0 / func_0011de90's old layout entries. */
void func_0011d7e0(Snd01 *e, s32 *a, s32 *b) {
    V4_01 hit;
    V4_01 n;
    f32 md;
    V4_01 unused;
    f32 *t;
    f32 *p;
    f32 s, d;
    if (e->x8 == 0x3fff) return;
    if ((D_002BBDE0 == 5 || D_002BBDE0 == 7) && D_002C1370) {
        *a = 0x3fff;
        *b = 0x3fff;
        return;
    }
    if (D_003F34A4) {
        *a = 0;
        *b = 0;
        return;
    }
    p = e->pos;
    s = 0.0f;
    switch (e->kind) {
    case 0:
        s = D_002C1360;
        break;
    case 1:
    case 2:
    case 4:
        s = D_002C1384;
        break;
    case 3:
        md = 5000.0f;
        func_00104f10(p, n);
        t = D_004E3A20;
        s = 50.0f;
        if (func_00119fc0(p, n, t, hit, &md) || func_00119ad8(-1, p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *a = 16383.0f - d * d / s;
        } else {
            *a = 0;
        }
        t = D_004E3A30;
        if (func_00119fc0(p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *b = 16383.0f - d * d / s;
        } else if (func_00119ad8(-1, p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *b = 16383.0f - d * d / s;
        } else {
            *b = 0;
        }
        return;
    }
    d = vd01(D_004E3A20, p);
    *a = 16383.0f - d * d / s;
    d = vd01(D_004E3A30, p);
    *b = 16383.0f - d * d / s;
}

/* func_0011db50 (from hand/text_00110000_b01.c). */
void func_0011db50(s32 *a, s32 *b) {
    if (*a < 0) *a = 0;
    if (*b < 0) *b = 0;
    if (*a >= 0x4000) *a = 0x3fff;
    if (*b >= 0x4000) *b = 0x3fff;
}

/* func_0011dba0 (from hand/text_00110000_h3.c). */
extern s32 D_002A3F44;
void func_0011dba0(s32 *a0, s32 *a1, s32 a2, s32 a3) {
    if (a3 == 2 && D_002A3F44) {
        *a0 = 0;
        *a1 = 0;
        return;
    }
    if (a2 == 0x3fff) {
        *a0 = a2;
        *a1 = a2;
        return;
    }
    *a0 += a2;
    *a1 += a2;
    func_0011db50(a0, a1);
}

/* func_0011dc28 (from hand/text_00110000_h4.c). */
extern s32 D_002C1310[];
void func_0011dc28(s32 *a, s32 *b, s32 *c) {
    s32 i = 3;
    s32 *p;
    if (D_002BBDE0 == i) return;
    p = D_002C1310;
    for (; i >= 0; i--) {
        if (*a == *p++) {
            if (*b < 9216 && *c < 9216) { *b = 9216; *c = 9216; }
        }
    }
}

/* func_0011dc98 (from hand/text_00110000_h4.c). */
typedef struct { s32 id; u8 pad[16]; u8 f14; } S0011dc98;
void func_0011dc98(S0011dc98 *a) {
    s32 i;
    s32 *p;
    if (D_002BBDE0 == 3) return;
    p = D_002C1310;
    for (i = 3; i >= 0; i--) {
        if (a->id == *p++) {
            a->f14 = 0;
        }
    }
}

/* func_0011dcf0 (from hand/text_00110000_h30.c). */
static inline f32 vdist(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define D_004E3A20 (*(V4 (*)) &D_004E3A20)
#define D_004E3A30 (*(V4 (*)) &D_004E3A30)
void func_0011dcf0(void *a0, s32 *a1, s32 *a2) {
    f32 n = D_002C1360;
    f32 d;
    d = vdist(&D_004E3A20, a0);
    *a1 = 16383.0f - d * d / n;
    d = vdist(&D_004E3A30, a0);
    *a2 = 16383.0f - d * d / n;
    func_0011db50(a1, a2);
}
#undef D_004E3A20
#undef D_004E3A30

/* func_0011ddd0 (from hand/text_00110000_h30.c). */
extern V4 D_002C1340;
extern V4 D_002C1320;
extern V4 D_002C1330;
extern V4 D_002C1350;
extern V4 D_004E3A20_0011ddd0 __asm__("D_004E3A20");
#define D_004E3A20 D_004E3A20_0011ddd0
extern V4 D_004E3A30_0011ddd0 __asm__("D_004E3A30");
#define D_004E3A30 D_004E3A30_0011ddd0
void func_0011ddd0(void) {
    V4 m[4];
    PlatVu0InversMatrix(m, D_002BC140);
    if (D_002BBDE0 == 3) {
        PlatVu0ApplyMatrix(D_004E3A30, m, D_002C1350);
        PlatVu0ApplyMatrix(D_004E3A20, m, D_002C1340);
        return;
    }
    PlatVu0ApplyMatrix(D_004E3A30, m, D_002C1330);
    PlatVu0ApplyMatrix(D_004E3A20, m, D_002C1320);
    D_004E3A20[2] = D_004E3A30[2] = 1000.0f;
}
#undef D_004E3A20
#undef D_004E3A30

/* func_0011de90 (from hand/text_00110000_b01.c). */
typedef struct { s32 x0, x4, x8; } Sl01;
typedef struct { s32 a, b; } Pr01;
s32 func_0011e248();
s32 func_0011e368();
extern Pr01 D_004E39F8_0011de90[] __asm__("D_004E39F8");
#define D_004E39F8 D_004E39F8_0011de90
extern Sl01 *D_004E3454_0011de90 __asm__("D_004E3454");
#define D_004E3454 D_004E3454_0011de90
extern Snd01 *D_004E3450_0011de90 __asm__("D_004E3450");
#define D_004E3450 D_004E3450_0011de90
#define func_0011dc28 ((void (*)(Snd01 *, s32 *, s32 *)) func_0011dc28)
#define func_0011dc98 ((void (*)(Snd01 *)) func_0011dc98)
#define func_0011c838 ((void (*)(s32, s32, s32, s32, s32)) func_0011c838)
#define func_0011c880 ((void (*)(s32, s32, s32, s32, s32)) func_0011c880)
#define func_0011c850 ((void (*)(s32, s32, s32)) func_0011c850)
#define func_0011e248 ((void (*)(s32)) func_0011e248)
#define func_0011e368 ((void (*)(s32, s32)) func_0011e368)
#define func_001edba0 ((void (*)(void)) func_001edba0)
/* Split out of func_0011d7e0 / func_0011de90's old layout entries. */
void func_0011de90(void) {
    s32 l, r;
    s32 i;
    Sl01 *sl;
    Snd01 *s;
    sl = D_004E3454;
    D_004E3A18 = 0;
    for (i = 0; i < 4; i++) {
        if (D_004E39F8[i].b) {
            D_004E3A18 = 1;
            D_004E39F8[i].b--;
        }
    }
    D_004E3A1C = 0;
    for (i = 0; i < D_004E344C; i++, sl++) {
        if (sl->x8) {
            sl->x8--;
            D_004E3A1C = 1;
        }
    }
    func_0011e248(0);
    func_0011e368(-1, -1);
    func_0011ddd0();
    s = D_004E3450;
    for (i = 0; i < D_004E344C; i++, s++) {
        switch (s->active) {
        case 0:
            break;
        case 1:
            func_0011d7e0(s, &l, &r);
            func_0011dc28(s, &l, &r);
            func_0011dba0(&l, &r, s->x8, s->kind);
            func_0011c838(s->handle, s->id, s->x10, l, r);
            s->active = 3;
            func_0011dc98(s);
            break;
        case 2:
            if (D_004E3A40 == 0) {
                func_0011d7e0(s, &l, &r);
                func_0011dba0(&l, &r, s->x8, s->kind);
                if (l || r) {
                    func_0011c838(s->handle, s->id, s->x10, l, r);
                    s->on = 1;
                }
                s->active = 4;
            }
            break;
        case 3:
            func_0011d7e0(s, &l, &r);
            func_0011dba0(&l, &r, s->x8, s->kind);
            func_0011c880(s->handle, s->id, s->x10, l, r);
            break;
        case 4:
            if (D_004E3A40 == 0) {
                func_0011d7e0(s, &l, &r);
                func_0011dba0(&l, &r, s->x8, s->kind);
                if (l == 0 && r == 0) {
                    s->on = 0;
                    func_0011c850(s->handle, s->id, s->x10);
                    break;
                }
                if (s->on == 0) {
                    func_0011c838(s->handle, s->id, s->x10, l, r);
                } else if (l != 0x3fff || r != 0x3fff) {
                    func_0011c880(s->handle, s->id, s->x10, l, r);
                }
                s->on = 1;
            } else {
                s->on = 0;
                func_0011c850(s->handle, s->id, s->x10);
            }
            break;
        }
    }
    func_001edba0();
}
#undef D_004E39F8
#undef D_004E3454
#undef D_004E3450
#undef func_0011dc28
#undef func_0011dc98
#undef func_0011c838
#undef func_0011c880
#undef func_0011c850
#undef func_0011e248
#undef func_0011e368
#undef func_001edba0

/* func_0011e1c8 (from hand/text_00110000_b01.c). */
extern Pr01 D_004E39F8_0011e1c8[] __asm__("D_004E39F8");
#define D_004E39F8 D_004E39F8_0011e1c8
void func_0011e1c8(s32 x) {
    s32 i;
    i = 0;
    do {
        if (D_004E39F8[i].a == 0) break;
        i++;
    } while (i < 4);
    D_004E39F8[i].a = x;
    D_004E39F8[i].b = 2;
}
#undef D_004E39F8

/* func_0011e220 (from auto/text_00110000.c). */
M2C_UNK func_001ecc68();
#define func_0011e1c8 ((M2C_UNK (*)(s32)) func_0011e1c8)
void func_0011e220(s32 arg0) {
    func_001ecc68();
    func_0011e1c8(arg0);
}
#undef func_0011e1c8

/* func_0011e248 (from hand/text_00110000_h30.c). */
s32 func_00157090(void);
s32 func_001ecd08(s32, s32, s32);
s32 func_0011e248(s32 a0) {
    s32 i, r;
    Pair *p;
    if (func_00157090()) return 8;
    if (a0 == 0) {
        if (D_004E3A18) return 9;
        r = func_001ecd08(-1, -1, 0);
        if (r == 0) {
            for (i = 3; i >= 0; i--) D_004E39F8[i].a = 0;
        }
        return r;
    }
    p = D_004E39F8;
    for (i = 0; i < 4; i++, p++) {
        if (p->a == a0) {
            if (p->b) return 9;
            r = func_001ecd08(-1, -1, a0);
            if (r == 0) p->a = 0;
            return r;
        }
    }
    return 0;
}

/* func_0011e340 (from auto/text_00110000.c). */
extern s32 D_002C1394;
#define func_0011e248 ((s32 (*)()) func_0011e248)
void func_0011e340(void) {
    D_002C1394 = func_0011e248();
}
#undef func_0011e248

/* func_0011e368 (from hand/text_00110000_h30.c). */
s32 func_0011e368(s32 a0, s32 a1) {
    s32 i, r;
    Slot12 *p = D_004E3454;
    if (a0 == -1) {
        if (D_004E3A1C) return 1;
        r = func_001ecb08(-8, -1, -1);
        if (r == 0) {
            for (i = 0; i < D_004E344C; i++) {
                p->x0 = 0;
                p->x4 = 0;
            }
        }
        return r;
    }
    for (i = 0; i < D_004E344C; i++, p++) {
        if (p->x0 == a0 && p->x4 == a1) {
            if (p->x8) return 1;
            r = func_001ecb08(-8, a0, a1);
            if (r == 0) {
                p->x0 = 0;
                p->x4 = 0;
            }
            return r;
        }
    }
    return 0;
}

/* func_0011e480 (from auto/text_00110000_6.c). */
extern s32 D_002C1364;
#define func_0011c7a8 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK)) func_0011c7a8)
#define func_0011c7c0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK)) func_0011c7c0)
void func_0011e480(void) {
    func_0011c7c0(0, 0, 0x3C0);
    func_0011c7a8(1, 0, 0x3000, 0xF0, 0, 0xF0);
    D_002C1364 = 1;
}
#undef func_0011c7a8
#undef func_0011c7c0

/* func_0011e4d0 (from auto/text_00110000_7.c). */
#define func_0011c7c0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK)) func_0011c7c0)
#define func_0011c7a8 ((f32 (*)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK)) func_0011c7a8)
void func_0011e4d0(void) {
    func_0011c7c0(1, 0, 0x2D0);
    func_0011c7a8(0, 0, 0x3000, 0x1E0, 1, 0xF0);
    D_002C1364 = 0;
}
#undef func_0011c7c0
#undef func_0011c7a8

/* func_0011e518 (from auto/text_00110000.c). */
extern s32 D_002C1390;
void func_0011e518(void) {
    D_002C1390 = 1;
}

/* func_0011e528 (from auto/text_00110000.c). */
void func_0011e528(void) {
    D_002C1390 = 0;
}

/* func_0011e538 (from hand/text_00110000_h30.c). */
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
extern s32 D_002BCDC4;
extern s32 D_002C138C;
void func_0011e538(void) {
    if (D_002BCDC4) return;
    if (D_002C1390 == 0 && D_002C1368[0] != D_002C1368[1]) {
        if (D_002C5958.b0 == 1) {
            if (D_002C138C == 0) func_0011e480();
        } else {
            if (D_002C138C == 1) func_0011e4d0();
        }
    }
    D_002C138C = D_002C5958.b0;
}

/* func_0011e5f0 (from auto/text_00110000_1.c). */
#define func_0011c9a0 ((M2C_UNK (*)()) func_0011c9a0)
void func_0011e5f0(void) {
    func_0011c9a0();
    func_00101628();
}
#undef func_0011c9a0

/* func_0011e610 (from hand/text_00110000_h30.c). */
#define func_0011c7c0 ((void (*)(s32, s32, s32)) func_0011c7c0)
#define func_0011c7a8 ((void (*)(s32, s32, s32, s32, s32, s32)) func_0011c7a8)
void func_0011e610(void) {
    if (D_002C5958.b0 == 1) {
        func_0011c7c0(0, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(1, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(1, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 1;
    } else {
        func_0011c7c0(1, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(0, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(0, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 0;
    }
}
#undef func_0011c7c0
#undef func_0011c7a8

/* func_0011e700 (from hand/text_00110000_s6_03.c). */
extern s32 D_002C1388;
extern void (*D_004E3434)(void);
extern s32 D_004E3444;
void func_0011e700(void) {
    if (!D_002C1388) func_0011e528();
    if (!D_004E3444) func_0011e610();
    if (D_004E3434) D_004E3434();
}

/* func_0011e758 (from hand/text_00110000_s6_04.c). */
void func_0011e758(void) {
    s32 *p = &D_002C1388;
    if (*p == 0) func_0011e528();
    if (D_004E3444 == 0 && *p == 0) func_0011e610();
    if (D_004E3434) D_004E3434();
}

/* func_0011e7c8 (from auto/text_00110000_6.c). */
extern s32 D_002C1378[];
#define func_0011cbe0 ((M2C_UNK (*)(M2C_UNK, s32, s32, M2C_UNK *)) func_0011cbe0)
extern s32 D_002C1378_0011e7c8 __asm__("D_002C1378");
#define D_002C1378 D_002C1378_0011e7c8
void func_0011e7c8(s32 arg0, s32 arg1, s32 arg2) {
    func_0011cbe0(0, arg2, D_002C1378, &func_0011e700);
}
#undef func_0011cbe0
#undef D_002C1378

/* func_0011e7f8 (from hand/text_00110000_h30.c). */
s32 func_00120748(char *, s32, void (*)(void), s32);
#define func_0011c7c0 ((void (*)(s32, s32, s32)) func_0011c7c0)
#define func_0011c7d8 ((void (*)(s32)) func_0011c7d8)
void func_0011e7f8(void) {
    char buf[64];
    if (D_002C1368[0] != D_002C1378[0] && D_002C1378[0] != 0) {
        if (D_002C1368[1] == -2) func_0011c7d8(0);
        else func_0011c7c0(0, 0, 100);
        func_0011ca68(D_002C1378[0], buf);
        func_00120748(buf, D_004E3448, func_0011e7c8, 0);
        return;
    }
    func_0011e758();
}
#undef func_0011c7c0
#undef func_0011c7d8

/* func_0011e8a0 (from auto/text_00110000_11.c). */
extern s32 D_002C137C;
#define func_0011cbe0 ((M2C_UNK (*)(M2C_UNK, s32, s32, M2C_UNK *)) func_0011cbe0)
void func_0011e8a0(s32 arg0, s32 arg1, s32 arg2) {
    func_0011cbe0(1, arg2, D_002C137C, &func_0011e7f8);
}
#undef func_0011cbe0

/* func_0011e8d0 (from hand/text_00110000_s6_04.c). */
#define func_0011c7c0 ((void (*)(s32, s32, s32)) func_0011c7c0)
void func_0011e8d0(s32 a0, s32 a1, s32 a2, void (*a3)(void), s32 a4, s32 a5) {
    char buf[64];
    D_004E3434 = a3;
    D_004E3438 = a1;
    D_004E343C = a2;
    D_004E3440 = a0;
    D_004E3444 = a4;
    D_004E3448 = a5;
    if (D_002C1368[1] != D_002C1378[1] && D_002C1378[1] != 0) {
        if (D_002C1368[1] == -2) func_0011c7d8(0);
        else func_0011c7c0(1, 0, 100);
        func_0011ca68(D_002C1378[1], buf);
        func_00120748(buf, D_004E3448, func_0011e8a0, 0);
        return;
    }
    func_0011e7f8();
}
#undef func_0011c7c0

/* func_0011e9a8 (from auto/text_00110000_6.c). */
#define func_0011e8d0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, s32)) func_0011e8d0)
void func_0011e9a8(s32 arg0, s32 arg1) {
    func_0011e8d0(0, 0x3000, 0, arg0, 0, arg1);
}
#undef func_0011e8d0

/* func_0011e9d8 (from auto/text_00110000_7.c). */
#define func_0011e8d0 ((M2C_UNK (*)(M2C_UNK, s32, s32, s32, M2C_UNK, s32)) func_0011e8d0)
void func_0011e9d8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0011e8d0(1, arg0, arg1, arg2, 0, arg3);
}
#undef func_0011e8d0

/* func_0011ea10 (from auto/text_00110000_6.c). */
#define func_0011e8d0 ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, s32)) func_0011e8d0)
void func_0011ea10(s32 arg0, s32 arg1) {
    func_0011e8d0(0, 0x3000, 0, arg0, 1, arg1);
}
#undef func_0011e8d0

/* func_0011ea40 (from hand/text_00110000_h4.c). */
char *strcpy(char *, const char *);
extern char D_0048D198[];
void func_0011ea40(s32 n, char *out) {
    char buf[80];
    sprintf(buf, "%3d", n);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    strcpy(out, "amusic/music");
    strcat(out, buf);
    strcat(out, D_0048D198);
}

/* func_0011eae0 (from hand/text_00110000_h30.c). */
extern char D_0048D1A0[];
extern Str12 D_0048D1A8;
extern char D_0048D1B8[];
void func_0011eae0(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D1A0, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') {
            buf[1] = '0';
            if (buf[2] == ' ') buf[2] = '0';
        }
    }
    *(Str12 *)a1 = D_0048D1A8;
    strcat(a1, buf);
    strcat(a1, D_0048D1B8);
}

/* func_0011eb88 (from hand/text_00110000_s6_04.c). */
#define func_001ed128 ((s32 (*)(s32, s32)) func_001ed128)
#define func_001ed460 ((void (*)(s32, s32, s32)) func_001ed460)
#define func_0011ef10 ((void (*)(s32, s32 (*)(void))) func_0011ef10)
void func_0011eb88(s32 a0, s32 a1, s32 a2, void (*a3)(void)) {
    D_002C1368[a0] = -1;
    D_004E3430 = a3;
    func_001ed128(1, a0);
    func_001ed460(a0, a1, a2);
    func_0011ef10(10000, func_0011cba0);
}
#undef func_001ed128
#undef func_001ed460
#undef func_0011ef10

/* func_0011ec08 (from hand/text_00110000_h30.c). */
#define func_001ed128 ((s32 (*)(s32, s32)) func_001ed128)
void func_0011ec08(s32 a0, s32 *a1, s32 a2, void (*a3)(void)) {
    D_004E3430 = a3;
    if (a1[1] > 0x7547f) {
        D_002C1368[1] = D_002C1368[0] = -2;
        func_001ed128(0, 0);
        func_001ed128(0, 1);
        if (a0 == 1) a0 = 0;
    } else {
        D_002C1368[a0] = -1;
        func_001ed128(0, a0);
    }
    func_001ed658(a0, a1, a2);
    func_0011ef10(10000, func_0011cba0);
}
#undef func_001ed128

