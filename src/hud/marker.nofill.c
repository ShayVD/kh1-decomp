/* Markers over actors and the lock-on (docs/modules.md "Session 46"), nofill
 * part.  func_0023c968 is the set up (called from the HUD's func_00236f18):
 * clears the ten markers, loads the mark sprites D_00449990 (the four kinds
 * D_006512F0 ... D_006512FC and the marker sprite D_00651300), registers the
 * hooks func_0023c8c8 (the target's mark) and func_0023c400 (every marker in
 * use, func_0023c270, with its own drawing environment D_00650DE0) and sets
 * up the sign (func_0023cf30).  func_0023c7a0 picks the target's mark kind
 * from D_002E31B8 / D_002E31BC (kind 4 for states 1, 2 and 4; 1-3 in state 3
 * while D_002E31B0 is set, which also shows the sign), draws it with
 * func_0023c5c8 (restarting its animation when the kind changes, D_00651BD0)
 * and the target's numbers (func_0023c1b0).  func_0023ca48 draws one sprite
 * moved by (x, y) with its alpha scaled by s. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/types/nofill_text_00230000_h49_p.h"
#include "data/types/nofill_text_00230000_h49.h"
#include "data/pieces/D_00449990.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
typedef struct { s32 unk0; u8 pad[0xDC]; } Ent0E0;

Q D_00650DE0 ALIGNED(32);
extern u8 D_00351E10[];
extern u8 *D_00651200; /* src/data/bss_0065.c: s32 D_00651200 */
extern u8 *D_00651204;
extern Ent0E0 D_00651310[]; /* src/data/bss_0065.c: Slot D_00651310[10] */
extern s32 D_00651BD0;
extern u8 *D_006512F0;
extern u8 *D_006512F4;
extern u8 *D_006512F8;
extern u8 *D_006512FC;
extern u8 *D_00651300;
extern Pkt D_00651210;
extern s32 D_002E31BC;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023c270(Ent0E0 *);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_0023c8c8(void);
void func_0023cf30(void);
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
void func_0023c1b0(s32 *, s32, s32);
void func_0023c5c8(s32 *, s32, s32);
void func_0023cee8(void);
void func_0023cf08(void);

s32 func_0023c400(void) {
    s32 i;
    func_002370c8(&D_00650DE0);
    D_00650DE0.unkE0 = 5;
    D_00650DE0.unk60 = 0x30003;
    func_00237018(&D_00650DE0, 0x16, 1);
    D_00651204 = D_00351E10;
    D_00651200 = D_00351E10 + 0x10;
    for (i = 0; i < 10; i++) {
        if (D_00651310[i].unk0 != 0) func_0023c270(&D_00651310[i]);
    }
    func_00237018(D_00651204, (D_00651200 - D_00651204) >> 4, 1);
    return 0;
}

void func_0023c7a0(void) {
    s32 f = 0;
    s32 m = 0;
    s32 *p;
    s32 c;
    switch (D_002E31B8) {
    case 0:
        m = 0;
        break;
    case 3:
        if ((*(s32 *)&D_002E31B0) == 0) { m = 0; break; }
        f = 1;
        func_0023cee8();
        switch (D_002E31BC) {
        case 0: m = 1; break;
        case 1: m = 2; break;
        case 2: m = 3; break;
        }
        break;
    case 1:
    case 2:
    case 4:
        m = 4;
        break;
    }
    p = &D_00651BD0;
    c = *p != m;
    if (m != 0) {
        func_0023c5c8(((s32 *)&D_002E31B0), m, c);
        func_0023c1b0(((s32 *)&D_002E31B0), 0, 0);
    }
    if (f == 0) func_0023cf08();
    *p = m;
}

void func_0023c968(void) {
    u8 *b;
    memset(D_00651310, 0, 0x8C0);
    D_00651BD0 = 0;
    func_0024aac8(&D_00449990);
    b = (u8 *)&D_00449990 + D_00449990.unk8;
    D_006512F8 = b + 0xC0;
    D_006512F4 = b;
    D_006512F0 = b + 0x180;
    D_006512FC = b + 0x240;
    D_00651300 = b + 0x300;
    if (func_0011ef38(func_0023c8c8) == 0) func_0011ef10(0x28489, func_0023c8c8);
    if (func_0011ef38(func_0023c400) == 0) func_0011ef10(0x28489, func_0023c400);
    func_0023cf30();
}

void func_0023ca48(s32 a0, s32 a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00651210, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00651210.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00651210.c[i].w = D_00651210.c[i].w * s;
    }
    D_00651200 = (u8 *)func_002388b8(&D_00651210, 1, (s32)D_00651200);
}
