/* The HUD's set up (docs/modules.md "Session 45"), 0x00236f00-0x00236fd8.
 * func_00236f18 (called from the start up in h13 and in
 * text_00100000_9.c) clears the draw list D_00425F80 (256 buckets
 * at D_00425F88) and calls the set up of each part from 0x0023b570 to
 * 0x00249250 (most likely the battle HUD: the gauges drawn as arcs up to
 * 3/2 pi, the command menu; not proved by a boot); func_00239488 is the
 * matching step.  func_00236f00 runs func_00239368 at start up: the HUD's
 * textures ("command2/uitex.bin", hudtex.nostrict_nofill.c) and a 16x16
 * CLUT into GS memory.  func_00236fc0 / func_00236fc8 / func_00236fd0 are
 * empty hooks (no C caller).
 * 0x00239368-0x00239558: func_002393d8 loads the font (text.c's
 * func_001f2e98: a 256x256 4-bit image at 0x3600 and its CLUT at 0x3A00);
 * func_002394f8 is 1 while one of five HUD parts is busy (vm_lib.c's
 * func_001da178 reads it). */
#include "common.h"
#include "gfx/drawlist.h"
#include "data/data_0042.h"
#include "data/types/nostrict_nofill_text_00230000_s6_24.h"

/* sceGsLoadImage (libgraph): 0x60 bytes of GIF / DMA tags. */
typedef struct { u8 b[0x60]; } GsLoadImage;

extern DrawList D_00425F80;
extern DrawBucket D_00425F88[256];
void func_00239368(void);
void func_0023b570(void);
void func_0023c968(void);
void func_00242a38(void);
void func_00243a90(void);
void func_00244500(void);
void func_00245148(void);
void func_002456e8(void);
void func_00245e40(void);
void func_00246438(void);
void func_00246bc8(void);
void func_00247258(void);
void func_00248400(void);
void func_00248ea0(void);
void func_00249250(void);
void func_00238a70(void);
void func_002499f0(void);
void func_001f2e98(void **img, void **clut);
void sceGsSetDefLoadImage(GsLoadImage *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(GsLoadImage *, void *);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
void func_0023cfd8(void);
void func_00243668(void);
void func_002444a0(void);
void func_00244b00(void);
void func_002452f0(void);
void func_002458e0(void);
void func_00246020(void);
void func_00246a60(void);
void func_00247350(void);
void func_002485e0(void);
void func_00248b00(void);
void func_00249240(void);
s32 func_00243bd8(void);
s32 func_002448d8(void);
s32 func_00245228(void);
s32 func_00245f18(void);
s32 func_002474a8(void);
extern Slot32 D_00648230[]; /* src/data/bss_0064.c: Slot32 D_00648230[0xc] */

void func_00236f00(void) {
    func_00239368();
}

void func_00236f18(void) {
    func_00237660(&D_00425F80, D_00425F88, 8);
    func_0023b570();
    func_0023c968();
    func_00242a38();
    func_00243a90();
    func_00244500();
    func_00245148();
    func_002456e8();
    func_00245e40();
    func_00246438();
    func_00246bc8();
    func_00247258();
    func_00248400();
    func_00248ea0();
    func_00249250();
    D_00425F78 = 0;
}

void func_00236fc0(void) {
}

void func_00236fc8(void) {
}

s32 func_00236fd0(void) {
    return 0;
}

/* func_00237018 ... func_00238a70 are in src/gfx/ and hudtex*.c. */

void func_00239368(void) {
    GsLoadImage li;
    func_00238a70();
    sceGsSetDefLoadImage(&li, 0x3FD8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&li, D_00648230);
    func_002499f0();
}

void func_002393d8(void) {
    GsLoadImage li;
    void *img;
    void *clut;
    func_001f2e98(&img, &clut);
    sceGsSetDefLoadImage(&li, 0x3600, 4, 0x14, 0, 0, 256, 256);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&li, img);
    sceGsSetDefLoadImage(&li, 0x3A00, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&li, clut);
    func_002499f0();
}

void func_00239488(void) {
    func_002452f0();
    func_00244b00();
    func_002444a0();
    func_00243668();
    func_002458e0();
    func_00246020();
    func_00246a60();
    func_00247350();
    func_002485e0();
    func_00248b00();
    func_00249240();
    func_0023cfd8();
}

s32 func_002394f8(void) {
    if (func_002448d8()) return 1;
    if (func_00245228()) return 1;
    if (func_00243bd8()) return 1;
    if (func_00245f18()) return 1;
    return func_002474a8() != 0;
}
