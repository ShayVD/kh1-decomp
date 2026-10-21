#include "common.h"
#include "data/pieces/D_004268B0.h"
typedef Tex_4268b0 GsTexHdr;
typedef struct { u8 pad[0x10]; GsTexHdr h; } GsTex;
#include "data/pieces/D_00426970.h"
typedef Tex4440_426970 Tex4440;
#include "data/types/nostrict_nofill_text_00230000_s6_24_p.h"
#include "data/types/nostrict_nofill_text_00230000_s6_24.h"
extern s32 D_00440994;
#include "data/pieces/D_00431D20.h"
#include "data/pieces/D_00426940.h"
#include "data/pieces/D_00426910.h"
#include "data/pieces/D_004268E0.h"
#include "data/pieces/D_00426880.h"
#include "data/pieces/D_00426850.h"
#include "data/pieces/D_00426820.h"
#include "data/pieces/D_004267F0.h"
#include "data/pieces/D_004267C0.h"
#include "data/pieces/D_00426790.h"
#include "data/pieces/D_0042B790.h"
#include "data/pieces/D_004305B0.h"
#include "data/pieces/D_00431F30.h"
#include "data/pieces/D_00431D50.h"
extern Slot32 D_00648230[];
Slot32 D_006483B0[0x14] ALIGNED(16);
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
    t = func_002389f0(2); h = func_00249f08(t, 5120, 36, 16344, 0, 0); (*(GsTexHdr *)&D_00426790) = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[0], t);
    t = func_002389f0(3); h = func_00249f08(t, 5120, 44, 16344, 1, 0); (*(GsTexHdr *)&D_004267C0) = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[1], t);
    t = func_002389f0(1); h = func_00249f08(t, 5376, 36, 16344, 2, 0); (*(GsTexHdr *)&D_004267F0) = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[4], t);
    t = func_002389f0(10); h = func_00249f08(t, 5376, 44, 16344, 3, 0); (*(GsTexHdr *)&D_00426850) = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[5], t);
    t = func_002389f0(7); h = func_00249f08(t, 5632, 36, 16344, 4, 0); (*(GsTexHdr *)&D_00426880) = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[8], t);
    t = func_002389f0(6); h = func_00249f08(t, 5632, 44, 16344, 5, 0); D_004268B0 = *h; func_00249dc8(t, 1); func_00249eb8(&D_00648230[9], t);
    t = func_002389f0(5); D_00426970 = *(Tex4440 *)t; func_00249d50(&D_00426970, 13824, 14848); h = func_00249da0(&D_00426970); (*(GsTexHdr *)&D_004268E0) = *h;
    t = func_002389f0(8); (*(Tex4440 *)&D_0042B790) = *(Tex4440 *)t; func_00249d50(((Tex4440 *)&D_0042B790), 13824, 14848); h = func_00249da0(((Tex4440 *)&D_0042B790)); (*(GsTexHdr *)&D_00426910) = *h;
    t = func_002389f0(9); (*(Tex1440 *)&D_004305B0) = *(Tex1440 *)t; func_00249d50(((Tex1440 *)&D_004305B0), 13824, 14848); h = func_00249da0(((Tex1440 *)&D_004305B0)); (*(GsTexHdr *)&D_00426940) = *h;
    t = func_002389f0(0); h = func_00249f08(t, 5888, 36, 16344, 6, 0); (*(GsTexHdr *)&D_00426820) = *h; func_00249dc8(t, 1); func_00249eb8(&D_006483B0[0], t);
    t = func_002389f0(4); h = func_00249f08(t, 5888, 44, 16344, 7, 0); (*(GsTexHdr *)&D_00431D20) = *h; func_00249dc8(t, 1); func_00249eb8(&D_006483B0[1], t);
    j = 11;
    for (i = 0; i < 10; i++) {
        t = func_002389f0(j);
        D_00431F30[i].t = *(Tex1440 *)t;
        func_00249d50(&D_00431F30[i], 13824, 14848);
        h = func_00249da0(&D_00431F30[i]);
        { u64 *q = (u64 *)&h->tb; *q |= 1ULL << 34; }
        (*(GsTexHdr (*)[10])&D_00431D50)[i] = *h;
        j++;
    }
}
#include "data/bss_0064_typed.h"
#include "data/data_0044.h"
