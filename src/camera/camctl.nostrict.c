/* The field camera's control, without strict aliasing (docs/modules.md
 * "Session 51"): the zone test that picks mode 9 and its path from the boxes
 * of the map's camera data (func_0017d628), func_0017e768, saving the camera
 * (func_0017f1c8: D_00575870), the camera's init (func_0017f510: registers
 * func_0017ecf8 as a task) and starting a screen shake (func_0017f580).
 * camctl.c has the rest.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/types/nostrict_text_00170000_b06.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/types/nostrict_text_00170000_b06_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/nostrict_text_00170000_b06_p2.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/nostrict_text_00170000_s6_10.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362454.h"
#include "data/pieces/D_00362710.h"

/* func_0017d628 (from hand/nostrict/text_00170000_b06.c). */
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Cam D_00575940;
extern ActB *D_00575894;
extern s32 D_00575890;
extern V4 D_005758E0;
void func_00176f08(s32, f32);
extern s32 D_00362448;
extern s32 D_002E27A8;
extern S920 D_00575920;
/* ---- func_0017d628 ---- */
s32 func_0017d628(void) {
    V4 pos;
    s32 i;
    s32 found = 0;
    Box *e;

    if (D_002E27A8 == 7) return 0;
    if (D_002E27A8 == 2) return 0;
    if (!D_00362424) return 0;
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    PlatVu0CopyVector(&pos, &D_00575894->x10);
    pos.y -= 100.0f;
    for (i = 0; i < D_00362448; i++) {
        e = &D_00362430[i];
        if (e->min.x <= pos.x && pos.x <= e->max.x && e->min.y <= pos.y && pos.y <= e->max.y
            && e->min.z <= pos.z && pos.z <= e->max.z) {
            if (e->x20) {
                if (D_002E27A8 != 9) {
                    if ((e->x24 & 2) && !(D_00575890 & 1)) D_00575940.x65 = 1;
                    func_00176f08(9, 30.0f);
                } else if (D_0036243C && D_0036243C != e && (D_0036243C->x24 & 2) && (e->x24 & 2)
                           && e->x20 != D_0036243C->x20 && !(D_00575890 & 1)) {
                    D_00575940.x65 = 1;
                }
                if (e->x24 & 2) {
                    D_00362434 = 0;
                    D_00362438 = (Path_362438 *)((s32)e->x20);
                } else {
                    D_00362434 = e->x20;
                    D_00362438 = 0;
                }
            } else if (D_002E27A8 == 9) {
                if (D_0036243C && (D_0036243C->x24 & 2)) {
                    if (D_00575920.x0) func_00176f08(3, 30.0f);
                    else func_00176f08(1, 30.0f);
                } else {
                    func_00176f08(1, 0.0f);
                }
                D_00362434 = 0;
                D_00362438 = 0;
            } else if (D_0036243C != e) {
                func_00176f08(1, 30.0f);
            }
            D_0036243C = e;
            found = 1;
            break;
        }
    }
    if (i == D_00362448 && D_0036243C) {
        if (D_0036243C->x24 & 1) {
            if (D_0036243C->x24 & 2) {
                if (D_00575920.x0) {
                    PlatVu0CopyVector(&D_00575920.x10, &D_005758E0);
                    func_00176f08(3, 30.0f);
                } else {
                    func_00176f08(1, 30.0f);
                }
            } else {
                func_00176f08(1, 30.0f);
            }
            D_00362434 = 0;
            D_00362438 = 0;
            D_0036243C = 0;
        }
    }
    return found;
}

/* func_0017e768 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00575894 D_00575894_e768
extern s32 D_00362420;
extern void *D_00575894 __asm__("D_00575894");
CONTEXT_ONLY s32 func_0017dc40(void) { return 0; }
s32 func_001773b0(void);
void func_0017e768(void) {
    s32 *p = &D_00362420;
    if (*p == 0) return;
    *p = 0;
    if (D_00575894 == 0) return;
    if (func_0017dc40()) return;
    if (func_001773b0()) {
        func_00176f08(1, 30.0f);
        return;
    }
}
#undef D_00575894

/* func_0017f1c8 (from hand/nostrict/text_00170000_s7_w2.c). */
typedef struct { V3 a; V3 b; f32 c; u8 x1c, x1d, x1e; } S870;
extern f32 D_002E27A0;
S870 D_00575870 ALIGNED(16);
/* session 7 w2: func_0017f1c8 (nostrict). Returning the symbol again ('return &D_00575870;' instead of 'return d;') gives the v0/t0 copy and the slot layout. */
S870 *func_0017f1c8(void) {
    S870 *d = &D_00575870;
    d->a.x = D_002E2780.x;
    d->a.y = D_002E2780.y;
    d->a.z = D_002E2780.z;
    d->b.x = D_002E2790.x;
    d->b.y = D_002E2790.y;
    d->b.z = D_002E2790.z;
    d->c = D_002E27A0;
    d->x1c = *(u8 *)&D_002E27A8;
    if (D_002E27A8 == 9) {
        if (D_00362434) {
            d->x1d = D_00362434->x1c;
            d->x1e = 0;
        } else if (D_00362438) {
            d->x1d = D_00362438->x1c;
            d->x1e = 1;
        }
    } else {
        d->x1d = 0;
    }
    return &D_00575870;
}

/* func_0017f510 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00575894 D_00575894_f510
extern void *D_00575894 __asm__("D_00575894");
extern s32 D_005758C4;
void func_0017ecf8(void);
s32 func_0011ef10(s32, void *);
void func_0017f150(void);
void func_0017f1a0(void);
void func_0017db68(void);
void func_0017eb20(void);
void func_0017f510(void) {
    D_00575894 = 0;
    func_0011ef10(100000, func_0017ecf8);
    D_002E27A8 = 0;
    D_005758C4 = 0;
    func_0017f150();
    func_0017f1a0();
    func_0017db68();
    D_00362424 = 0;
    D_0036244C = 0;
    D_00362454 = 0;
    func_0017eb20();
}
#undef D_00575894

/* func_0017f580 (from hand/nostrict/text_00170000_s6_10.c). */
extern s32 D_00362704;
extern s32 D_00362708;
extern s32 D_0036270C;
extern f32 D_00362714;
extern f32 D_00362718;
extern f32 D_0036271C;
extern f32 D_00362720;
extern f32 D_00362724;
extern f32 D_002BBDFC;
void func_0010ffb8(void *, void *);
void func_0017f580(f32 t, f32 a, f32 b, f32 c, s32 flag) {
    s32 *p = &D_00362704;
    if (*p == 0) func_0010ffb8(&D_00362708, &D_0036270C);
    *p = 1;
    D_00362710 = t + D_002BBDFC;
    D_00362718 = b;
    D_0036271C = c;
    if (flag) {
        D_00362720 = b / t;
        D_00362724 = c / t;
    } else {
        D_00362720 = 0.0f;
        D_00362724 = 0.0f;
    }
    D_00362714 = a;
}

