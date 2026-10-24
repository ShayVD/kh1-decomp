/* The room's background files (a guess at the name), 0x00100b18-0x00101970:
 * func_00100b18 sets the far view (near 15000, far 20000) and the texture
 * scrolls, func_00100d18 ... upload the background's textures,
 * func_00101048 reads the background file, and func_001012e0 /
 * func_001015a8 / func_001017e8 load a room's files (".img") through
 * src/game/roomload.c's names. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002A6238.h"
#include "data/bss_0049.h"
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
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/types/text_00100000_s6_00.h"
#include "m2c.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_0029B420.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C6F0.h"

/* func_00100b18 (from hand/text_00100000_h28.c). */
typedef struct {
    u8 pad0[0x21];
    u8 b21, b22, b23, b24, b25;
    u8 pad26[0xe];
    f32 f34, f38, f3c;
    f32 uv[16][2];
} Setup;
extern f32 D_0029B270;
void func_00100b18(Setup *s) {
    s32 i;
    D_002BC0F0.view30.near_ = 15000.0f;
    D_002BC0F0.view30.far_ = 20000.0f;
    for (i = 0; i < 16; i++) {
        D_002A3F60.v[i].a = 0;
        D_002A3F60.v[i].b = 0;
        D_002A4060.v[i].a = s->uv[i][0] * 0.00006103515625f;
        D_002A4060.v[i].b = s->uv[i][1] * 0.00006103515625f;
    }
    D_0029B270 = s->f34;
    D_002BC0F0.view30.a = s->f3c;
    D_002BC0F0.view30.b = s->f38;
    D_002BC0F0.view30.c = s->b21;
    D_002BC0F0.view30.d = s->b22;
    D_002BC0F0.view30.e = s->b23;
    D_002BC0F0.view30.f = s->b24;
    D_002BC0F0.view30.g = s->b25;
    D_002BC0C0.view30 = D_002BC0F0.view30;
}

/* func_00100c30 (from hand/text_00100000_s6_00.c). */
extern V4f D_0029B310[16];
void func_00100c30(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        D_002A4060.v[i].a = D_0029B310[i].a * 6.103515625e-05f;
        D_002A4060.v[i].b = D_0029B310[i].b * 6.103515625e-05f;
        D_002A4060.v[i].c = D_0029B310[i].c * 6.103515625e-05f;
        D_002A4060.v[i].d = D_0029B310[i].d * 6.103515625e-05f;
    }
/*P*/
    D_0029B270 = 0.0005454153478331864f;
    D_002BC0F0.cam0.f24 = 20000.0f;
    D_002BC0F0.cam0.f20 = 15000.0f;
    D_002BC0F0.cam0.f0 = 30000.0f;
    D_002BC0F0.cam0.f4 = 20000.0f;
    D_002BC0F0.cam0.f8 = 64.0f;
    D_002BC0F0.cam0.fc = 255.0f;
    D_002BC0F0.cam0.i10 = 0x10;
    D_002BC0F0.cam0.i14 = 0x70;
    D_002BC0F0.cam0.i18 = 0x80;
/*Q*/
}

/* func_00100d18 (from auto/text_00100000_3.c). */
extern M2C_UNK D_002BC1B0;
void func_00100d18(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg1, 1, 0, 0, 0, 8, 2);
    PlatFlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg0);
    PlatGsSyncPath(0, 0);
}

/* func_00100d90 (from auto/text_00100000_3.c). */
void func_00100d90(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg1, 1, 0, 0, 0, 0x10, 0x10);
    PlatFlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg0);
    PlatGsSyncPath(0, 0);
}

/* func_00100e08 (from auto/text_00100000_3.c). */
void func_00100e08(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg1, 8, 0x14, 0, 0, 0x200, 0x100);
    PlatFlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg0);
    PlatGsSyncPath(0, 0);
}

/* func_00100e80 (from auto/text_00100000_3.c). */
void func_00100e80(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg1, 4, 0x13, 0, 0, 0x100, 0x100);
    PlatFlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg0);
    PlatGsSyncPath(0, 0);
}

/* func_00100ef8 (from auto/text_00100000_3.c). */
void func_00100ef8(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC1B0, arg1, 4, 0x1B, 0, 0, 0x100, 0x400);
    PlatFlushCache(0);
    PlatGsExecLoadImage(&D_002BC1B0, arg0);
    PlatGsSyncPath(0, 0);
}

/* func_00100f70 (from hand/text_00100000_h28.c). */
typedef struct { s32 m[32][16]; s32 v[4]; } Blk810;
extern s32 D_0029BE20[][32][16];
extern s32 D_002A3F24;
void func_00100f70(Blk810 *src) {
    s32 i, j, k;
    for (i = 0; i < D_002A3F24; i++) {
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 16; k++) {
                D_0029BE20[i][j][k] = src[i].m[j][k];
            }
        }
        ((s32 (*)[4])&D_002A3E20)[i][0] = src[i].v[0];
        ((s32 (*)[4])&D_002A3E20)[i][1] = src[i].v[1];
        ((s32 (*)[4])&D_002A3E20)[i][2] = src[i].v[2];
        ((s32 (*)[4])&D_002A3E20)[i][3] = src[i].v[3];
    }
}

/* func_00101048 (from hand/text_00100000_s7_w4.c). */
typedef struct { u64 x[20]; } Blk160;
static inline void cp160(void *d, void *s) {
    *(Blk160 *)d = *(Blk160 *)s;
}
typedef struct { u8 kind[16]; u8 pad10[4]; u16 n0; u16 n1; } Setup_01048;
typedef Hdr_2a3f3c Hdr;
extern s32 D_002A3F20;
s32 func_00108618(void);
void func_00101e70(void);
void func_00102978(void);
void func_0011ef10(s32, void (*)(void));
void func_00113768(void);
#define func_00100b18 ((void (*)(Setup_01048 *)) func_00100b18)
#define func_00100d18 ((void (*)(void *, s32)) func_00100d18)
#define func_00100d90 ((void (*)(void *, s32)) func_00100d90)
#define func_00100e08 ((void (*)(void *, s32)) func_00100e08)
#define func_00100e80 ((void (*)(void *, s32)) func_00100e80)
#define func_00100ef8 ((void (*)(void *, s32)) func_00100ef8)
s32 func_00101048(void) {
    s32 i;
    Hdr *h;
    Blk160 *src;
    Blk810 *mt;
    Setup_01048 *s;
    u8 *tex;
    u8 *big;
    i = 0;
    func_00108618();
    h = D_002A3F3C;
    src = (Blk160 *)((u8 *)h + h->o0);
    D_002A3F20 = h->sz4 / sizeof(Blk160);
    for (; i < D_002A3F20; i++) {
        cp160(&D_0029B420[i], &src[i]);
    }
    s = (Setup_01048 *)((u8 *)h + h->o8);
    tex = (u8 *)h + h->o10;
    big = (u8 *)h + h->o18;
    func_00100b18(s);
    for (i = 0; i < s->n0; i++) {
        func_00100d18(tex + i * 256, i + 0x3e00);
    }
    for (i = s->n0; i < s->n1; i += 4) {
        func_00100d90(tex + i * 256, i + 0x3e00);
    }
    for (i = 0; i < 16; i++) {
        if (s->kind[i] != 19) {
            if (s->kind[i] == 20) {
                func_00100e08(big + i * 0x10000, i * 256 + 0x2600);
            }
        } else {
            func_00100e80(big + i * 0x10000, i * 256 + 0x2600);
        }
    }
    func_00100ef8(big + 0x100000, 0);
    mt = (Blk810 *)((u8 *)h + h->o20);
    D_002A3F24 = h->sz24 / sizeof(Blk810);
    func_00100f70(mt);
    func_00101e70();
    func_00102978();
    func_0011ef10(0xc350, func_00113768);
    return 4;
}
#undef func_00100b18
#undef func_00100d18
#undef func_00100d90
#undef func_00100e08
#undef func_00100e80
#undef func_00100ef8

/* func_001012b8 (from auto/text_00100000_9.c). */
#define func_0011ef10 ((M2C_UNK (*)(M2C_UNK, M2C_UNK *)) func_0011ef10)
void func_001012b8(void) {
    func_0011ef10(0x2E630, &func_00101048);
}
#undef func_0011ef10

/* func_001012e0 (from hand/text_00100000_s6_00.c). */
typedef struct { s32 off; s32 size; } Ent;
typedef struct { s32 ver; s32 pad[3]; Ent e[10]; } Hdr_012e0;
extern s32 D_002A3F38;
extern s32 D_002A3F28;
extern s32 D_002A3F40;
extern s32 D_002A3F34;
extern s32 D_002A3F2C;
s32 D_00494418 ALIGNED(8);
s32 D_0049441C ALIGNED(4);
extern s32 D_0029B410;
extern s32 D_0029B418;
extern s32 D_0029B414;
extern s32 D_0029B41C;
extern s32 D_002BCDF0;
extern s32 D_002BCDBC;
void func_00105288(s32, s32);
void func_00108cf8(s32, s32, s32);
void func_00100768(void);
void func_001007b0(void);
void func_001763f0(s32);
void func_00105d88(s32);
s32 func_001137c8(s32, s32);
void func_00120748(char *, s32, void *, s32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
#define func_001012b8 ((void (*)(s32, s32, s32)) func_001012b8)
void func_001012e0(s32 arg) {
    char tmp[16];
    char buf[64];
    Hdr_012e0 *h;
    Ent *e;
    s32 ver;
    h = (Hdr_012e0 *)D_002A3F38;
    e = &h->e[1];
    ver = h->ver;
    D_002A3F2C = (s32)h + h->e[0].off;
    D_002A3F30 = (s32)h + e->off;
    D_002A3F34 = e->size;
    e = &h->e[5];
    D_00494418 = (s32)h + h->e[2].off;
    D_0049441C = (s32)h + h->e[3].off;
    D_002A3F48 = (s32)h + h->e[4].off;
    func_00106ed0(D_002A3F30, D_002A3F34);
    func_00105288(D_002A3F2C, 1);
    func_00108cf8(D_00494418, 0, 4);
    func_00100768();
    func_00108cf8(D_0049441C, 1, 4);
    func_001007b0();
    D_0029B414 = D_0029B410 = 0;
    D_0029B418 = 0;
    D_0029B41C = 0;
    if (ver >= 6) {
        if (e->size != 0) {
            D_0029B410 = D_002A3F38 + e->off;
            func_001763f0(D_0029B410);
        }
        e = &h->e[6];
        if (e->size != 0) {
            D_0029B414 = D_002A3F38 + e->off;
        }
        e = &h->e[7];
        if (ver >= 8) {
            if (e->size != 0) {
                D_0029B418 = D_002A3F38 + e->off;
                func_001763f0(D_0029B418);
            }
            e = &h->e[8];
            if (e->size != 0) {
                D_0029B41C = D_002A3F38 + e->off;
            }
            e = &h->e[9];
        }
        if (ver >= 10) {
            if (e->size != 0) {
                D_002A3F28 = D_002A3F38 + e->off;
                func_00105d88(D_002A3F28);
            }
        }
    }
    D_002BCDF0 = D_002A3F38 + arg;
    if (D_002BCDBC == 0) {
        strcpy(buf, D_002BCCE0);
        strcat(buf, D_0048CC30);
        D_002A3F3C = (Hdr_2a3f3c *)(D_002A3F38 + arg);
        (*(s32 *)&D_002A3F3C) = func_001137c8(((s32)D_002A3F3C), 128);
        func_00120748(buf, ((s32)D_002A3F3C), func_001012b8, 0);
    } else {
        func_001012b8(D_002A3F40, 0, ((s32)D_002A3F3C));
    }
}
#undef func_001012b8

/* func_001015a8 (from auto/text_00100000_10.c). */
s32 func_001559f0(M2C_UNK, M2C_UNK);
#define func_00120748 ((M2C_UNK (*)(void *, s32, M2C_UNK *, M2C_UNK)) func_00120748)
#define strcat ((M2C_UNK (*)(void *, M2C_UNK *)) strcat)
#define strcpy ((M2C_UNK (*)(void *, M2C_UNK *)) strcpy)
#define func_001137c8 ((s32 (*)(s32, M2C_UNK)) func_001137c8)
void func_001015a8(void) {
    s32 sp[16];
    s32 temp_v0;
    s32 temp_v0_2;

    strcpy(sp, (M2C_UNK *)&D_002BCCE0);
    strcat(sp, (M2C_UNK *)&D_0048CC30);
    temp_v0 = func_001559f0(0x34, 8);
    D_002A3F3C = (Hdr_2a3f3c *)temp_v0;
    temp_v0_2 = func_001137c8(temp_v0, 0x80);
    D_002A3F3C = (Hdr_2a3f3c *)temp_v0_2;
    func_00120748(sp, temp_v0_2, &func_001012b8, 0);
}
#undef func_00120748
#undef strcat
#undef strcpy
#undef func_001137c8

/* func_00101628 (from hand/text_00100000_h1.c). */
extern s32 D_002BCDE8;
extern s32 D_002C1368[];
extern s32 D_002C138C;
extern s32 D_00494410[];
void func_00101628(void) {
    D_00494410[0] = -1;
    D_00494410[1] = -1;
    D_002C1368[0] = 0;
    D_002C1368[1] = 0;
    D_002C138C = 0;
    D_002BCDE8 = 0;
}

/* func_00101660 (from auto/text_00100000_3.c). */
extern s32 D_002BC138;
extern s32 D_002BC13C;
void func_00101660(void) {
    D_002BC138 = -1;
    D_002BC13C = -1;
    D_002BCDBC = 0;
}

/* func_00101680 (from hand/text_00100000_h28.c). */
extern void func_0011d240(s32, s32, void *, s32);
extern s32 D_00494410_00101680[2] __asm__("D_00494410");
#define D_00494410 D_00494410_00101680
void func_00101680(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_00494410[i] != (*(s32 (*)[2])&D_002A3F50)[i]) {
            if ((*(s32 (*)[2])&D_002A3F50)[i] != 0) {
                func_0011d240((*(s32 (*)[2])&D_002A3F50)[i], i, D_002BCAF0, 0x3FFF);
            }
            D_00494410[i] = (*(s32 (*)[2])&D_002A3F50)[i];
        }
    }
}
#undef D_00494410

/* func_00101728 (from hand/text_00100000_h1.c). */
void func_0011d3c8(s32, s32, s32);
void func_00101728(s32 arg) {
    s32 i;
    for (i = 0; i < 2; i++) {
        s32 v = D_00494410[i];
        if (v != ((s32 *)&D_002A3F50)[i] || v == 0) {
            func_0011d3c8(v, i, arg);
        }
    }
}

/* func_001017b8 (from auto/text_00100000_9.c). */
M2C_UNK func_0011c898(M2C_UNK);
#define func_00101680 ((M2C_UNK (*)()) func_00101680)
extern volatile s32 D_00494410_001017b8[] __asm__("D_00494410");
#define D_00494410 D_00494410_001017b8
void func_001017b8(void) {
    func_0011c898(0);
    D_00494410[1] = -1;
    D_00494410[0] = -1;
    func_00101680();
}
#undef func_00101680
#undef D_00494410

/* func_001017e8 (from hand/text_00100000_h51.c). */
extern s32 D_002BC128;
extern s32 D_002BC12C;
extern s32 D_002BCDB4;
extern s32 D_002BCDB8;
extern s32 D_002BCDD8;
extern char D_0048CC38[];
void func_00112400(s32);
void func_0011d4e0(s32);
#define func_0011c898 ((void (*)(s32)) func_0011c898)
#define func_0011ef10 ((void (*)(s32, void *)) func_0011ef10)
s32 func_001017e8(void) {
    char tmp[16];
    char buf[64];

    func_00112400(D_002BC12C);
    if (D_002BCDB4 == 1 && D_002BC13C == D_002BC12C) {
        D_002BCDB8 = D_002BCDB4;
    }
    func_0011d4e0(480);
    func_00101728(960);
    if (D_002BC128 == 8 && D_002BC12C == D_002BC128) {
        func_0011c898(1);
    }
    if (D_002BC138 == 8 && D_002BC13C == D_002BC138) {
        func_0011c898(0);
    }
    D_002BC138 = D_002BC128;
    if (D_002BCDB8 == 1) {
        if (D_002BCDD8 != 0) {
            func_001015a8();
        } else {
            func_0011ef10(50000, func_00113768);
        }
    } else {
        strcpy(buf, D_002BCCE0);
        strcat(buf, D_0048CC38);
        D_002A3F38 = func_001137c8(D_002A3F38, 128);
        func_00120748(buf, D_002A3F38, func_001012e0, 0);
    }
    D_002BC13C = D_002BC12C;
    return 4;
}
#undef func_0011c898
#undef func_0011ef10

