#include "common.h"
typedef struct {
    u64 f0:14; u64 f14:6; u64 f20:6; u64 f26:11; u64 f37:14; u64 f51:5; u64 f56:5; u64 f61:3;
} TexBits;
typedef struct {
    u8 pad[8]; s32 x8; u8 padc[8]; s16 w; s16 h;
    TexBits tb;
    u8 pad20[0x10];
} GsTexHdr;
typedef struct { u8 pad[0x10]; GsTexHdr h; } GsTex;
typedef struct { u8 b[0x4440]; } Tex4440;
typedef struct { u8 b[0x1440]; } Tex1440;
typedef struct { Tex1440 t; u8 pad[6000 - 0x1440]; } Tex6000;
typedef struct { u8 b[32]; } Slot32;
extern s32 D_00440994;
extern GsTexHdr D_00426790, D_004267C0, D_004267F0, D_00426850, D_00426880, D_004268B0, D_00426820, D_00431D20, D_004268E0, D_00426910, D_00426940;
extern Tex4440 D_00426970, D_0042B790;
extern Tex1440 D_004305B0;
extern Tex6000 D_00431F30[10];
extern GsTexHdr D_00431D50[10];
extern Slot32 D_00648230[], D_006483B0[];
s32 func_001559f0(s32, s32);
s32 func_001205f0(char *, s32);
GsTexHdr *func_00249f08(void *t, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_00249dc8(void *, s32);
void func_00249eb8(void *, void *);
void func_00249d50(void *, s32, s32);
GsTexHdr *func_00249da0(void *);
void *func_002389f0(s32 n);
/* rodata */
void func_00238a70(void) {
    s32 i, j;
    void *t;
    GsTexHdr *h;
    { s32 *p = &D_00440994; *p = func_001559f0(52, 12); func_001205f0("command2/uitex.bin", *p); }
    t = func_002389f0(2); h = func_00249f08(t, 5120, 36, 16344, 0, 0); D_00426790 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[0], t);
    t = func_002389f0(3); h = func_00249f08(t, 5120, 44, 16344, 1, 0); D_004267C0 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[1], t);
    t = func_002389f0(1); h = func_00249f08(t, 5376, 36, 16344, 2, 0); D_004267F0 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[4], t);
    t = func_002389f0(10); h = func_00249f08(t, 5376, 44, 16344, 3, 0); D_00426850 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[5], t);
    t = func_002389f0(7); h = func_00249f08(t, 5632, 36, 16344, 4, 0); D_00426880 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[8], t);
    t = func_002389f0(6); h = func_00249f08(t, 5632, 44, 16344, 5, 0); D_004268B0 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[9], t);
    t = func_002389f0(5); D_00426970 = *(Tex4440 *)t; func_00249d50(&D_00426970, 13824, 14848); h = func_00249da0(&D_00426970); D_004268E0 = *h;
    t = func_002389f0(8); D_0042B790 = *(Tex4440 *)t; func_00249d50(&D_0042B790, 13824, 14848); h = func_00249da0(&D_0042B790); D_00426910 = *h;
    t = func_002389f0(9); D_004305B0 = *(Tex1440 *)t; func_00249d50(&D_004305B0, 13824, 14848); h = func_00249da0(&D_004305B0); D_00426940 = *h;
    t = func_002389f0(0); h = func_00249f08(t, 5888, 36, 16344, 6, 0); D_00426820 = *h; func_00249dc8(t, 1); func_00249eb8(&D_006483B0[0], t);
    t = func_002389f0(4); h = func_00249f08(t, 5888, 44, 16344, 7, 0); D_00431D20 = *h; func_00249dc8(t, 1); func_00249eb8(&D_006483B0[1], t);
    j = 11;
    for (i = 0; i < 10; i++) {
        t = func_002389f0(j);
        D_00431F30[i].t = *(Tex1440 *)t;
        func_00249d50(&D_00431F30[i], 13824, 14848);
        h = func_00249da0(&D_00431F30[i]);
        { u64 *q = (u64 *)&h->tb; *q |= 1ULL << 34; }
        D_00431D50[i] = *h;
        j++;
    }
}
