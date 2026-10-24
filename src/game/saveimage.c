/* The save image's blocks (docs/modules.md "Session 44"), 0x00232ad0-0x00232de0.
 * D_003F8380 is the 0x16c00 bytes a save holds (the load screen,
 * src/menu/loadmenu.c, reads a slot into it), in seven blocks: 0
 * D_003F8380 (0xc00 bytes), 1 D_003F8F80 (0x1000, src/msgwin/msgwin.c), 2
 * D_003F9F80 (0x400), 3 D_003FA380 (0x400), 4 D_003FA780 (0x14000), 5
 * D_0040E780 (0x400, D_003F34B8: the munny, src/game/gamedata.c) and 6
 * D_0040EB80 (0x400).  func_00232ad0(k) clears block k (-1: all of it),
 * func_00232cc0(k) returns it; func_00232d60 / func_00232da0 copy the whole
 * image to the backup D_0040EF80 and back. */
#include "common.h"

typedef kh1_s128 u128;

extern u128 D_003F8380[];
extern u128 D_003F8F80[];
extern u128 D_003F9F80[];
extern u128 D_003FA380[];
extern u128 D_003FA780[];
extern u128 D_0040E780[];
extern u128 D_0040EB80[];
extern u128 D_0040EF80[];

static inline void clr(u128 *p, s32 n) { for (; n > 0; n--) *p++ = 0; }

s32 func_00232ad0(s32 a) {

    switch (a) {
    case -1:
        clr(D_003F8380, 5824);
        return 0;
    case 0:
        clr(D_003F8380, 192);
        return 0;
    case 1:
        clr(D_003F8F80, 256);
        return 0;
    case 2:
        clr(D_003F9F80, 64);
        return 0;
    case 3:
        clr(D_003FA380, 64);
        return 0;
    case 4:
        clr(D_003FA780, 5120);
        return 0;
    case 5:
        clr(D_0040E780, 64);
        return 0;
    case 6:
        clr(D_0040EB80, 64);
        return 0;
    }
    return -1;
}

void *func_00232cc0(u32 arg0) {
    switch (arg0) {
    case 0: return D_003F8380;
    case 1: return D_003F8F80;
    case 2: return D_003F9F80;
    case 3: return D_003FA380;
    case 4: return D_003FA780;
    case 5: return D_0040E780;
    case 6: return D_0040EB80;
    }
    return 0;
}

void func_00232d60(void) {
    u128 *s = D_003F8380;
    u128 *d = D_0040EF80;
    s32 i;
    for (i = 0x16C0; i > 0; i--) {
        *d++ = *s++;
    }
}

void func_00232da0(void) {
    u128 *s = D_0040EF80;
    u128 *d = D_003F8380;
    s32 i;
    for (i = 0x16C0; i > 0; i--) {
        *d++ = *s++;
    }
}
