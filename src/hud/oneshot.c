/* A two-sprite display shown once (docs/modules.md "Session 46"),
 * 0x00248fb8-0x002492d0.  func_00249250 (the set up) loads D_00469CA0 into
 * the two objects D_00669A10 (D_00469F50) and registers the draw hook
 * func_002491f8; func_00249230 starts it (D_00469F60 = 1) and
 * func_00249240 stops it.  func_002490f0 starts both animations, steps them
 * until the first one's flag 4 and ends; func_00249010 draws them with its
 * own drawing environment D_006697C0 (with 0x8000000048 at +0x70).  What it
 * shows is not proved by a boot. */
#include "common.h"
#include "data/types/text_00240000_h50.h"

typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 pad[0x60]; u64 x60; u64 x68; u64 x70; u8 pad2[0x68]; u64 xe0; u8 tail[0x160 - 0xE8]; } S7df0;

S7df0 D_006697C0 ALIGNED(64);
Q4 *D_00669924 ALIGNED(4);
Panel D_00669930 ALIGNED(16);
extern Q4 *D_00669920; /* src/data/bss_0066.c: s32 D_00669920 */
extern void *D_00669A10[];
extern Q4 D_00351E10[];
extern s32 D_00469F60;
extern u8 D_00469CA0[], D_00469F50[];
extern u8 D_004267F0[];
void func_0011ef10(s32, s32 (*)(void));
s32 func_0011ef38(s32 (*)(void));
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_0024aa48(void *, void *, void *);
void func_0024aac8(void *);
s32 func_0024a1c0(void *);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0024afc0(void *, void *, void *);

void func_00248fb8(void *spr, void *tex) {
    func_0024aa48(spr, &D_00669930, tex);
    D_00669920 = func_002388b8(&D_00669930, 1, D_00669920);
}

void func_00249010(void) {
    s32 i;
    func_002370c8(&D_006697C0);
    D_006697C0.xe0 = 5;
    D_006697C0.x60 = 0x30003;
    D_006697C0.x70 = 0x8000000048ULL;
    func_00237018(&D_006697C0, 22, 1);
    D_00669924 = D_00351E10;
    D_00669920 = D_00351E10 + 1;
    for (i = 0; i < 2; i++) {
        func_00248fb8(D_00669A10[i], D_004267F0);
    }
    func_00237018(D_00669924, D_00669920 - D_00669924, 1);
}

void func_002490f0(s32 *st) {
    s32 i;
    switch (*st) {
    case 1:
        for (i = 0; i < 2; i++) func_0024ae00(D_00669A10[i]);
        (*st)++;
        break;
    case 2:
        for (i = 0; i < 2; i++) func_0024af00(D_00669A10[i]);
        if (func_0024a1c0(D_00669A10[0]) & 4) (*st)++;
        break;
    case 3:
        *st = 0;
        return;
    }
    func_00249010();
}

s32 func_002491f8(void) {
    if (D_00469F60 == 0) {
        return 0;
    }
    func_002490f0(&D_00469F60);
    return 0;
}

void func_00249230(void) {
    D_00469F60 = 1;
}

void func_00249240(void) {
    D_00469F60 = 0;
}

void func_00249250(void) {
    D_00469F60 = 0;
    func_0024aac8(D_00469CA0);
    func_0024afc0(D_00469F50, D_00669A10, D_00469CA0);
    if (func_0011ef38(func_002491f8) == 0) {
        func_0011ef10(0x28489, func_002491f8);
    }
}
