/* The frame captured to D_00F20000 (a guess at the name),
 * 0x00109cd0-0x0010a4d8: func_00109d98 / func_0010a058 / func_0010a3e8
 * store the frame (sceGsExecStoreImage), func_00109cd0 / func_00109f88 /
 * func_0010a470 load it back, and the tasks func_00109e20 / func_0010a120 /
 * func_0010a248 fade between them. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "common.h"
#include "platform/gs.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002BC0A8.h"
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
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B677C.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B6778.h"

/* func_00109cd0 (from auto/text_00100000_10.c). */
M2C_UNK FlushCache(M2C_UNK);
extern u8 D_002BC1B0[];
extern u8 D_002BC210[];
extern M2C_UNK D_00F20000;
#define D_002BC1B0 (*(M2C_UNK (*)) &D_002BC1B0)
#define D_002BC210 (*(M2C_UNK (*)) &D_002BC210)
void func_00109cd0(void) {
    PlatGsSetDefLoadImage(&D_002BC1B0, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&D_002BC1B0, &D_00F20000);
    PlatGsSetDefLoadImage(&D_002BC210, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&D_002BC210, (s8 *)&D_00F20000 + 0x48000);
}
#undef D_002BC1B0
#undef D_002BC210

/* func_00109d98 (from auto/text_00100000_9.c). */
s32 func_00109d98(void) {
    s32 sp[28];
    PlatGsSetDefStoreImage(sp, 0x1A00, 8, 1, 0, 0, 0x200, 0x180);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecStoreImage(sp, &D_00F20000);
    return 4;
}

/* func_00109df8 (from auto/text_00100000_10.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00109df8(void) {
    func_0011ef10(0x2E630, &func_00109d98);
}

/* func_00109e20 (from hand/text_00100000_h28.c). */
extern Pkt D_002B6490;
extern f32 D_002BBDFC;
f32 D_00495168 ALIGNED(8);
f32 D_0049516C ALIGNED(4);
extern s32 func_00106b18(void *);
extern u8 D_002B65E0[];
s32 func_00109e20(void) {
    switch (D_00495188) {
    case 0:
        D_00495188 = 1;
        D_00495168 = D_00495184;
        D_0049516C = 128.0f / D_00495184;
    case 1:
        if (D_00495184 <= 0.0f) {
            return 4;
        }
        func_00109cd0();
        {
        f32 a = D_00495168 - D_00495184;
        f32 b = D_00495184 * D_0049516C;
        a *= D_0049516C;
        D_002B6490.b = ((u64)(s32)b << 24) | 0x100808080ull;
        D_002B6490.a = ((u64)(s32)a << 24) | 0x100808080ull;
        }
        func_00106b18(D_002B65E0);
        D_00495184 -= D_002BBDFC;
        return 0;
    }
    return 0;
}

/* func_00109f48 (from auto/text_00100000_3.c). */
void func_00109f48(s32 arg0) {
    D_00495188 = 0;
    D_00495184 = (f32) (arg0 * 2);
    func_0011ef10(0x2E630, &func_00109e20);
}

/* func_00109f88 (from hand/text_00100000_h28.c). */
#define FlushCache ((s32 (*)(s32)) FlushCache)
/* func_0010a248 only matches with func_00109f88 defined above it. */
void func_00109f88(void) {
    PlatGsSetDefLoadImage(D_002BC1B0, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(D_002BC1B0, (void *)D_002B677C);
    PlatGsSetDefLoadImage(D_002BC210, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(D_002BC210, (void *)(D_002B677C + 0x48000));
}
#undef FlushCache

/* func_0010a058 (from hand/text_00100000_h2.c). */
void *func_001559f0(s32, s32);
#define FlushCache ((void (*)(s32)) FlushCache)
s32 func_0010a058(void) {
    GsImagePacket si;
    void **p;

    PlatGsSetDefStoreImage(&si, 0x1a00, 8, 1, 0, 0, 512, 384);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    p = &D_002B677C;
    *p = func_001559f0(62, 2);
    PlatGsExecStoreImage(&si, *p);
    return 4;
}
#undef FlushCache

/* func_0010a0d8 (from hand/text_00100000_h2.c). */
extern s32 D_002B6774;
void func_001038b0(s32);
#define func_0011ef10 ((s32 (*)(s32, s32 (*)(void))) func_0011ef10)
s32 func_0010a0d8(void) {
    D_002B6774 = 1;
    if ((*(s32 *)&D_002BC070) != 128) func_001038b0(1);
    return func_0011ef10(0x2e630, func_0010a058);
}
#undef func_0011ef10

/* func_0010a120 (from hand/text_00100000_h28.c). */
f32 D_00495170 ALIGNED(16);
f32 D_00495178 ALIGNED(8);
s32 D_00495174 ALIGNED(4);
extern u64 D_002B6668;
extern u8 D_002B66B0[];
extern void func_00110380(void);
s32 func_0010a120(void) {
    switch (D_00495180) {
    case 0:

        D_00495174 = 128;
        D_00495170 = 64.0f;
        D_00495178 = 2.0f;
        D_00495180 = 1;

    case 1:
        if (D_00495170 <= 0.0f) {
            D_002B6774 = 0;
            func_00110380();
            return 4;
        }
        func_00109f88();
        { s32 c = D_00495174;
        D_002B6668 = (u64)c | ((u64)c << 8) | ((u64)c << 16) | ((u64)0x80 << 24) | ((u64)1 << 32); }

        func_00106b18(D_002B66B0);
        D_00495170 -= D_002BBDFC;
        D_00495174 = D_00495170 * D_00495178;
        return 0;
    }
    return 0;
}

/* func_0010a248 (from hand/text_00100000_h28.c). */
f32 D_0049517C ALIGNED(4);
extern s32 func_00106978(s32);
/* func_0010a248 only matches with func_00109f88 defined above it. */
s32 func_0010a248(void) {
    switch (D_00495180) {
    case 0: func_00106978(32); D_00495180++; D_0049517C = 64.0f;
    case 1:
        if (!(D_0049517C <= 0.0f)) {
            func_00109f88(); D_002B6668 = 0x180808080ull;
            func_00106b18(D_002B66B0); D_0049517C -= D_002BBDFC; return 0;
        }
        D_002B6774 = 0; return 4;
    }
    return 0;
}

/* func_0010a320 (from auto/text_00100000_9.c). */
extern s32 D_002B6770;
void func_0010a320(void) {
    D_00495180 = 0;
    if (D_002B6770 != 0) {
        func_0011ef10(0x2E630, &func_0010a248);
        return;
    }
    func_0011ef10(0x2E630, &func_0010a120);
}

/* func_0010a3c0 (from auto/text_00100000_3.c). */
void func_0010a378();
void func_0010a3c0(void) {
    func_0011ef10(0x2E630, &func_0010a378);
}

/* func_0010a3e8 (from hand/text_00100000_h2.c). */
void *func_00121e28(s32, void **);
extern u8 D_002B6760[];
#define FlushCache ((void (*)(s32)) FlushCache)
#define func_00106b18 ((void (*)(void *)) func_00106b18)
void func_0010a3e8(void) {
    GsImagePacket si;
    func_00106b18(D_002B6760);
    PlatGsSetDefStoreImage(&si, 0x3600, 4, 1, 0, 0, 256, 192);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    (*(void **)&D_002B6778) = func_00121e28(0x24000, ((void **)&D_002B6778));
    PlatGsExecStoreImage(&si, ((void *)D_002B6778));
}
#undef FlushCache
#undef func_00106b18

/* func_0010a470 (from auto/text_00100000_4.c). */
#define D_002BC1B0 (*(M2C_UNK (*)) &D_002BC1B0)
void func_0010a470(void) {
    PlatGsSetDefLoadImage(&D_002BC1B0, 0x3600, 4, 1, 0, 0, 0x100, 0xC0);
    FlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&D_002BC1B0, D_002B6778);
}
#undef D_002BC1B0

