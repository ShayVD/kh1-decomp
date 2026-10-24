/* The field's set up and frame (a guess at the name), 0x001001f8-0x00100b18:
 * func_00100278 resets the field state and opens the DMA channel,
 * func_00100360 / func_00100448 call the systems' set ups and frame
 * updates, and the rest draw the sky and the room's background models
 * (func_00100988 over the model packets of src/gfx/grideff.c and
 * src/gfx/mdlpkt.c). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/pieces/D_002B677C.h"

/* func_001001f8 (from auto/text_00100000.c). */
M2C_UNK func_00106c78();
s32 func_001001f8(void) {
    PlatGsSyncPath(0, 0);
    func_00106c78();
    return 0;
}

/* func_00100228 (from auto/text_00100000_1.c). */
extern M2C_UNK func_001001d8;
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00100228(void) {
    M2C_FIELD(func_0011ef10(0x270FE, &func_001001d8), s16 *, 2) = -1;
    M2C_FIELD(func_0011ef10(0x2D29E, &func_001001f8), s16 *, 2) = -1;
}

/* func_00100278 (from hand/text_00100000_h28.c). */
extern s32 D_002A3F44;
extern PlatDmaChan *D_002A6B84;
extern s32 D_002B6474;
extern s32 D_002B6770;
extern s32 D_002BC740;
extern s32 D_002BC744;
extern s32 D_002BCDA8;
extern s32 D_002BCDD8;
extern s32 D_002BCDDC;
extern s32 func_00112fd0(s32);
extern void func_00101660(void);
extern void func_00106900(void);
extern void func_00106910(void);
extern void func_00111ca8(void);
extern void func_00113de0(void);
extern void func_00114090(void);
extern void func_00114840(void);
void func_00100278(void) {
    D_002A6B84 = PlatDmaGetChan(2);
    D_002B6770 = 0;
    func_00106900();
    func_00106910();
    D_002B6474 = 0;
    (*(Bits_37a378 *)&D_0037A378).b0 = 0;
    D_002BCDA8 = 0;
    D_002A3F44 = 0;
    D_002BC740 = 0;
    D_002BC744 = 0;
    func_00114090();
    func_00113de0();
    func_00114840();
    func_00111ca8();
    { s32 z = 0; D_002BCDDC = z; D_002BCDD8 = z; func_00112fd0(z); }
    func_00101660();
    D_002BC0A8.flags_2.b1 = 0;
    (*(void **)&D_002BC140) = D_002BCAF0;
    (*(void **)&D_002BC144) = D_002BCAF0;
}

/* func_00100360 (from hand/text_00100000_h28.c). */
extern f32 D_002A6200;
extern s32 D_002BBBA0;
extern s32 D_002BCDC0;
extern s32 D_002BCDC4;
extern s32 D_002C1304;
void func_00100610();
extern s32 func_001039f8(void);
extern s32 func_0010c078(void);
extern s32 func_0010e8d0(void);
extern s32 func_001129c8(void);
extern s32 func_00114e50(void);
extern s32 func_0011a068(void);
extern s32 func_0011c898(s32);
extern s32 func_0011e528(void);
extern s32 func_0011e5f0(void);
extern void func_001118a0(void);
extern s32 func_00100448(void);
#define func_00100228 ((s32 (*)(void)) func_00100228)
#define func_0011ef10 ((s32 (*)(s32, void *)) func_0011ef10)
void func_00100360(void) {
    D_002C1304 = 0;
    func_0011c898(0);
    func_001118a0();
    D_002BBBA0 = 0;
    func_0011ef10(0x2903, func_0011a068);
    func_0011ef10(0x280A3, func_001039f8);
    func_00100228();
    func_0011e528();
    D_002BCDC4 = 0;
    D_002BC0A8.flags_2.b1 = 0;
    func_0011e5f0();
    D_002BCDC0 = 0;
    func_0010e8d0();
    func_0010c078();
    func_0011ef10(0xC350, func_001129c8);
    func_00100610();
    func_00114e50();
    func_0011ef10(0x1D4C0, func_00100448);
    D_002A6200 = 0.05f;
}
#undef func_00100228
#undef func_0011ef10

/* func_00100448 (from hand/text_00100000_h28.c). */
extern s32 D_002A61F4;
extern s32 D_002BC734;
extern s32 D_002BC738;
void func_001007e8();
void func_001008e8();
extern s32 func_00101f10(void);
extern s32 func_00102a28(void);
extern s32 func_00103258(void);
extern s32 func_001037e8(void);
extern s32 func_00104220(void);
extern s32 func_00114c00(void);
extern s32 func_0011e538(void);
extern void func_00100818(void);
extern void func_00100988(void);
s32 func_00100448(void) {
    D_002BC744 = D_002BC740;
    D_002BC740 = (*(Bits_37a378 *)&D_0037A378).b0;
    func_00114c00();
    if (D_002BC0A8.flags_2.b1 == 1) {
        func_001007e8();
        if (D_002BC0A8.flags_2.b0 == 1) {
            if (D_002BC0A8.flags_2.b3 == 1) {
                func_00100818();
                func_001008e8();
            }
            func_00100988();
            func_00101f10();
            func_00102a28();
        }
    }
    if (D_002A61F4 != 0) {
        func_00103258();
    }
    if (D_002BC734 != 0) {
        func_001037e8();
    }
    if (D_002BC738 != 0) {
        func_00104220();
    }
    func_0011e538();
    return 0;
}

/* func_00100558 (from hand/text_00100000_s6_00b.c). */
void func_00262c78(void);
void func_00109288(void);
void func_00109770(void);
void func_00100558(void) {
    func_00262c78();
    func_00109288();
    for (;;) func_00109770();
}

/* func_00100580 (from hand/text_00100000_h1.c). */
extern s32 D_00472150[];
void func_00100580(s32 idx, s32 *dst) {
    s32 i;
    for (i = 0; i < 2; i++) { 
        dst[0] = D_0048C6F0[idx].v[0];
        dst[1] = D_0048C6F0[idx].v[1];
        dst[2] = D_0048C6F0[idx].v[2];
        dst[3] = D_0048C6F0[idx].v[3];
        dst[4] = D_00472150[0];
        dst[5] = D_00472150[1];
        dst[6] = D_00472150[2];
        dst[7] = D_00472150[3];
        dst += 8;
    }
}

/* func_00100610 (from auto/text_00100000.c). */
extern E32 D_004941D0[];
extern E32 D_00494210[];
extern E32 D_00494250[];
extern E32 D_00494290[];
extern E32 D_004942D0[];
#define func_00100580 ((M2C_UNK (*)(M2C_UNK, M2C_UNK *)) func_00100580)
#define D_004941D0 (*(M2C_UNK (*)) &D_004941D0)
#define D_00494210 (*(M2C_UNK (*)) &D_00494210)
#define D_00494250 (*(M2C_UNK (*)) &D_00494250)
#define D_00494290 (*(M2C_UNK (*)) &D_00494290)
#define D_004942D0 (*(M2C_UNK (*)) &D_004942D0)
void func_00100610(void) {
    func_00100580(0, &D_004941D0);
    func_00100580(1, &D_00494210);
    func_00100580(3, &D_00494250);
    func_00100580(6, &D_00494290);
    func_00100580(7, &D_004942D0);
}
#undef func_00100580
#undef D_004941D0
#undef D_00494210
#undef D_00494250
#undef D_00494290
#undef D_004942D0

/* func_00100768 (from auto/text_00100000.c). */
M2C_UNK func_00104480(M2C_UNK, M2C_UNK *);
extern u8 D_00494320[];
#define D_00494320 (*(M2C_UNK (*)) &D_00494320)
void func_00100768(void) {
    func_00104480(-1, ((M2C_UNK *)&D_0029B280));
    func_00104480(-1, &D_00494320);
    M2C_FIELD(&D_00494320, s32 *, 0x44) = 0;
}
#undef D_00494320

/* func_001007b0 (from auto/text_00100000.c). */
extern M2C_UNK D_004943A0[]; /* D_00494310[1] + 0x10 */
void func_001007b0(void) {
    func_00104480(-1, &D_004943A0);
    M2C_FIELD(&D_004943A0, s32 *, 0x44) = 0;
}

/* func_001007e8 (from auto/text_00100000.c). */
M2C_UNK func_001044c0(M2C_UNK *);
M2C_UNK func_00107ec0(M2C_UNK *);
void func_001007e8(void) {
    func_001044c0(((M2C_UNK *)&D_0029B280));
    func_00107ec0(((M2C_UNK *)&D_0029B280));
}

/* func_00100818 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad0[0x54]; f32 rot; u8 pad58[8]; f32 x; s32 y; f32 z; u8 pad6c[0x14]; } Cam80;
/* The two field cameras D_00494310[2] (0x80 each, to D_00494410) are one definition (vita-port-plan 5.1i):
 * D_00494320 / D_004943A0 (each camera's +0x10, what func_00104480 / func_001044c0 take) and
 * D_004943E4 (camera 1's rot, func_001008d8) were their own variables and D_00494310 had none. */
Cam80 D_00494310[2] ALIGNED(16);
extern f32 D_0029B270;
extern f32 D_002BBDFC;
void func_00100818(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_00494310[i].x = D_002E2780.x;
        D_00494310[i].y = 0;
        D_00494310[i].z = D_002E2780.z;
    }
    D_00494310[1].rot += D_0029B270 * D_002BBDFC;
    if (D_00494310[1].rot > 3.1415928f) {
        D_00494310[1].rot -= 6.2831855f;
    }
    if (D_00494310[1].rot < -3.1415928f) {
        D_00494310[1].rot += 6.2831855f;
    }
}

/* func_001008d8 (from auto/text_00100000.c). */
extern f32 D_004943E4; /* D_00494310[1].rot */
void func_001008d8(f32 fparg0) {
    D_004943E4 = fparg0;
}

/* func_001008e8 (from hand/text_00100000_h1.c). */
typedef struct { u8 m[64]; u8 v64[16]; u8 v80[16]; s32 w96; } Xf;
extern char D_0029B170[];
void func_00106bd8(char *, s32);
void func_00108f18(s32, s32, void *);
#define func_001044c0 ((void (*)(Xf *)) func_001044c0)
void func_001008e8(void) {
    func_00106bd8(D_0029B170, 10010);
    func_001044c0((Xf *)D_00494320);
    func_00108f18(0, 10010, D_00494320);
    if (D_002BC0A8.flags.b5 == 1) {
        func_001044c0((Xf *)(D_00494320 + 128));
        func_00108f18(1, 10010, D_00494320 + 128);
    }
}
#undef func_001044c0

/* func_00100988 (from hand/text_00100000_h28.c). */
extern void func_00100670(u32, s32);
extern s32 D_0029B2F0;
extern s32 D_0029B2F4;
extern s32 D_0029B2FC;
extern u8 D_0029B1C0[];
extern u8 D_0029B200[];
extern u8 D_0029B260[];
extern void func_00106e98(s32);
extern void func_00107548(void *, s32);
extern void func_00108708(void);
extern void func_00107d30(s32, s32);
extern s32 func_00107c48(s32);
#define func_00106bd8 ((void (*)(void *, s32)) func_00106bd8)
void func_00100988(void) {
    D_0029B2F0 = 0;
    func_00106e98(10020);
    func_00106bd8(D_0029B1C0, 10020);
    func_00107548(&D_0029B280, D_002A3F30);
    if (D_0029B2F4 != 0) {
        func_00100670(1, 10020);
        func_00107d30(10020, 1);
    }
    if (D_0029B2FC != 0) {
        if (D_002BC0A8.flags_2.b4 == 1) {
            func_00100670(6, 10020);
        } else {
            func_00100670(0, 10020);
        }
        func_00107d30(10020, 0);
    }
    func_00106bd8(D_0029B200, 50000);
    func_00106e98(50000);
    if ((D_0029B2F0 = func_00107c48(D_002A3F30)) != 0) {
        func_00100670(3, 50000);
        func_00107d30(50000, 3);
    }
    func_00108708();
    func_00106bd8(D_0029B260, 50100);
}
#undef func_00106bd8

/* func_00100670 (from hand/text_00100000_h28.c). */
/* Below func_00100988, which matches only when it is not defined above
 * it (beq, not beql), as in hand/text_00100000_h28.c. */
typedef struct { u8 pad[16]; void *p; } Obj10;
extern Obj10 *func_0015ed80(s32, void (*)(void));
extern s32 D_00351BD0;
extern void func_00108d90(void);
void func_00100670(u32 arg0, s32 arg1) {
    Obj10 *o = func_0015ed80(arg1, func_00108d90);
    switch (arg0) {
    case 1:
        o->p = &D_00494210[D_00351BD0];
        break;
    case 3:
        o->p = &D_00494250[D_00351BD0];
        break;
    case 0:
        o->p = &D_004941D0[D_00351BD0];
        break;
    case 6:
        o->p = &D_00494290[D_00351BD0];
        break;
    case 7:
        o->p = &D_004942D0[D_00351BD0];
        break;
    }
}

/* func_00100ab0 (from auto/text_00100000.c). */
M2C_UNK func_00176250();
M2C_UNK func_00176290();
void func_00100ab0(void) {
    D_002BC0A8.i |= 3;
    func_00176250();
    func_00176290();
}

/* func_00100ae0 (from hand/text_00100000_h1.c). */
void func_001761f0(void);
void func_00176230(void);
void func_00100ae0(void) {
    D_002BC0A8.flags.b0 = 0;
    D_002BC0A8.flags.b1 = 0;
    func_001761f0();
    func_00176230();
}

