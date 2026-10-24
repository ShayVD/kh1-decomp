/* The disc read queue under src/io/discfile.c: the request slots D_004F3230
 * (func_0011ffd0 takes one), func_0011fd60 a synchronous read (sceCdRead),
 * func_0011fd40 a wait (a guess), func_0011fe20 loads the file table at
 * boot, func_0011fec0 compares the disc's name (strncmp). Flag mode: default
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "platform/cd.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "platform/math.h"
#include "data/types/text_00110000_h4_p.h"

/* func_0011fd30 (from auto/text_00110000.c). */
extern char D_004F2A00[];
#define D_004F2A00 (*(M2C_UNK (*)) &D_004F2A00)
M2C_UNK *func_0011fd30(void) {
    return &D_004F2A00;
}
#undef D_004F2A00

/* func_0011fd40 (from auto/text_00110000.c). */
M2C_UNK func_001104e0();
M2C_UNK func_001220d0();
void func_0011fd40(void) {
    func_001220d0();
    func_001104e0();
}

/* func_0011fd60 (from hand/text_00110000_h30.c). */
extern u8 D_002C5C38[];
void func_0011fd60(u32 lsn, u32 n, void *buf) {
    do {
        while (PlatCdDiskReady(1) != 2 || !PlatCdRead(lsn, n, buf, D_002C5C38)) func_0011fd40();
        while (PlatCdSync(1)) func_0011fd40();
    } while (PlatCdGetError());
}

/* func_0011fec0 (from hand/text_00110000_h30.c). */
extern s32 D_002C5C3C;
extern s32 D_002C5C40;
extern s32 D_004F3208;
extern char D_00351E10[];
s32 func_001ecfb0(void);
int strncmp(const char *, const char *, u32);
void func_0011fec0(void) {
    if (func_001ecfb0() == 1) {
        if (D_002C5C3C > 30) {
            (*(volatile Fl_2c5968 *)&D_002C5968).b1 = 1;
            return;
        }
        D_002C5C3C++;
        return;
    }
    if ((*(volatile Fl_2c5968 *)&D_002C5968).b1) {
        if (D_002C5C40 > 0) {
            D_002C5C40--;
            return;
        }
        func_0011fd60(D_004F3208, 1, D_00351E10);
        if (strncmp(D_00351E10, D_004F2A00, 2048)) {
            D_002C5C40 = 60;
            return;
        }
    }
    D_002C5C3C = 0;
    (*(volatile Fl_2c5968 *)&D_002C5968).b1 = 0;
}

/* func_0011ffd0 (from hand/text_00110000_h4.c). */
typedef struct { u32 flags; u8 pad[44]; s32 x30; s32 x34; } Slot;
extern Slot D_004F3230[0x10];
extern s32 D_002C5C44;
Slot *func_0011ffd0(void) {
    s32 i;
    Slot *s = D_004F3230;
    for (i = 0; i < 16; i++, s++) {
        if (!(s->flags & 1)) {
            s->flags |= 1;
            s->x34 = D_002C5C44++;
            s->x30 = -1;
            return s;
        }
    }
    return 0;
}

