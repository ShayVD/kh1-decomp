/* The command menu (docs/modules.md "Session 46"), nostrict_nofill part.
 * func_0023a318 draws one list: the drawing environment D_00648630, the
 * sprite buffer at D_00351E10, func_0023bb98 (mode 0 without a sub list) or
 * func_00239e30, then one GIF send of what was written.  func_0023a490 draws
 * the five-part frame of D_0064FD60 and three entries of a Btn in grey 115
 * (bit set in unk4) or 230. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0065.h"
#include "data/pieces/D_00426820.h"
#include "data/pieces/D_004267F0.h"
#include "data/data_0045.h"
extern s32 D_006488F0;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
extern u8 D_00351E10[];
extern u8 *D_006488F4;
typedef struct { u8 pad[0x1C4]; s32 unk1C4; } Obj1C4;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023bb98(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);
void func_00239e30(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);
typedef struct { s32 unk0; u32 unk4; u8 pad8[0xC]; u8 unk14[3]; } Btn;
extern u8 D_0064FD60[];
void func_0024ac08(void *, s32 *);
void func_00239558(s32, s32, s32, s32);
void func_00239630(void *, void *, s32, s32, f32);
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
Q D_00648630 ALIGNED(16);
#include "data/bss_0064_mixed.h"

void func_0023a318(s32 a0, s32 a1, s32 a2, s32 a3, Obj1C4 *o, s32 a5, s32 a6, f32 f) {
    func_002370c8(&D_00648630);
    D_00648630.unkE0 = 5;
    D_00648630.unk60 = 0x30003;
    func_00237018(&D_00648630, 0x16, 1);
    D_006488F4 = D_00351E10;
    *(u8 **)&D_006488F0 = D_00351E10 + 0x10;
    if (a0 == 0 && o->unk1C4 == 0) {
        func_0023bb98(0, a1, a2, a3, o, a5, a6, f);
    } else {
        func_00239e30(a0, a1, a2, a3, o, a5, a6, f);
    }
    if (f != 0.0f) {
        func_00237018(D_006488F4, (*(u8 **)&D_006488F0 - D_006488F4) >> 4, 1);
    }
}

void func_0023a490(s32 a0, Btn *b, s32 x, s32 y, f32 f) {
    s32 pos[2];
    s32 i, k;
    u8 *p;
    D_00650DD4 = D_00650DD0 = f;
    func_00239630(D_0064FD60, D_00426820, x, y, 1.0f);
    func_00239630(D_0064FD60 + 192, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 384, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 576, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 768, D_004267F0, x, y, 1.0f);
    func_0024ac08(D_0064FD60, pos);
    for (k = 20, i = 0, p = b->unk14; i < 3; i++) {
        func_00239558(*p, x + pos[0], y + k + pos[1], (b->unk4 & (1 << i)) ? 115 : 230);
        p++;
        k += 22;
    }
}
