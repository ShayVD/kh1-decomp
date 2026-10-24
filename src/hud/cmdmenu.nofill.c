/* The command menu (docs/modules.md "Session 46"), nofill part.
 * func_0023a608 draws the frame list of func_0023a490 with its own drawing
 * environment D_00648790.  func_0023a720 sets each entry's grey (0x73 when
 * its bit is set or a list follows, 0xE6 otherwise) for every list in
 * D_002E3170; func_0023a7e8 fades them towards it at 32 per second
 * (D_002BBDFC, the frame time).  func_0023b4b8 sets D_00449908's f7c / f80
 * (a value and its step: 1 / -0.1, 0 / 0.1, 1 / 0, 0 / 0) for states 0-3. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_00449908.h"
#include "data/data_002E.h"
#include "data/data_0045.h"
#include "data/pieces/D_002BBDFC.h"
extern u8 D_00351E10[];
extern u8 *D_006488F0; /* src/data/bss_0064.c: s32 D_006488F0 */
extern u8 *D_006488F4;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023a490(s32, s32, s32, s32, f32);
#include "data/types/nofill_text_00230000_h49_p2.h"
extern f32 D_002BBDFC;
#include "data/types/nofill_text_00230000_h49_p.h"
#include "data/types/nofill_text_00230000_h49.h"

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
Q D_00648790 ALIGNED(16);

void func_0023a608(s32 a0, s32 a1, s32 a2, s32 a3, f32 f) {
    func_002370c8(&D_00648790);
    D_00648790.unkE0 = 5;
    D_00648790.unk60 = 0x30003;
    func_00237018(&D_00648790, 0x16, 1);
    D_006488F4 = D_00351E10;
    D_006488F0 = D_00351E10 + 0x10;
    func_0023a490(a0, a1, a2, a3, f);
    if (f != 0.0f) {
        func_00237018(D_006488F4, (D_006488F0 - D_006488F4) >> 4, 1);
    }
}

void func_0023a720(void) {
    Spr **pp;
    Spr *p;
    s32 i;
    for (pp = D_002E3170; *pp != 0; pp++) {
        p = *pp;
        if (pp[1] == 0) {
            for (i = 0; i < p->n; i++) {
                if (p->f4 & (1 << i)) p->bright[i] = 0x73;
                else p->bright[i] = 0xE6;
            }
        } else {
            for (i = 0; i < p->n; i++) p->bright[i] = 0x73;
        }
    }
}

void func_0023a7e8(void) {
    Spr **pp;
    Spr *p;
    s32 i, v;
    for (pp = D_002E3170; *pp != 0; pp++) {
        p = *pp;
        if (pp[1] == 0) {
            for (i = 0; i < p->n; i++) {
                if (p->f4 & (1 << i)) {
                    v = p->bright[i]; v = v - D_002BBDFC * 32.0f;
                    if (v < 0x73) v = 0x73;
                    p->bright[i] = v;
                } else {
                    v = p->bright[i]; v = v + D_002BBDFC * 32.0f;
                    if (v > 0xE6) v = 0xE6;
                    p->bright[i] = v;
                }
            }
        }
    }
}

void func_0023b4b8(s32 a) {
    switch (a) {
    case 0:
        D_00449908.f7c = 1.0f;
        D_00449908.f80 = -0.0999999940395355224609375f;
        break;
    case 1:
        D_00449908.f80 = 0.0999999940395355224609375f;
        D_00449908.f7c = 0.0f;
        break;
    case 2:
        D_00449908.f7c = 1.0f;
        D_00449908.f80 = 0.0f;
        break;
    case 3:
        D_00449908.f80 = 0.0f;
        D_00449908.f7c = 0.0f;
        break;
    }
}
