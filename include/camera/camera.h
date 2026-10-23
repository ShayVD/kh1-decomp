/* The event camera (src/camera/camera*.c; docs/modules.md "src/camera/").
 *
 * Two blocks of state:
 *
 * - D_0037A380 (data/pieces/D_0037A380.h, U0037A380): the camera path a
 *   script loads (func_001c5ee8 copies it from the script file): up to 256
 *   keys (`cam.ent`, `scn.arr`) linked first .. last, the play time `t`,
 *   and the current output (`a` position, `b`..`e`, `f60`, `fE0F4`) that
 *   func_001c53c8 interpolates for a time and func_001c5168 moves with the
 *   followed objects.
 * - D_003C5510 (CamState below): the camera itself: flags, the per-axis
 *   tweens the script functions start (0x001c6d08-0x001ca9e8), the base,
 *   position (D_003C55E0) and rotation (D_003C55F0) vectors, the up / view
 *   vectors and two scalars.  func_001c6a20 turns it into the view
 *   (D_002E2780 / D_002E2790 / D_002E27A4); func_001c6890 sets it back
 *   from the view.
 *
 * The script VM runs func_001c6720 (reset) when it loads a script and
 * func_001c5b88 (play the path) every frame (src/vm/script_vm.c). */
#ifndef KH1_CAMERA_CAMERA_H
#define KH1_CAMERA_CAMERA_H

#include "common.h"
#include "data/pieces/D_0037A380.h"

/* A 16-byte vector slot of CamState (the type b10's CamS gives them). */
typedef f32 CamVec[4] __attribute__((aligned(16)));

/* The same 16 bytes as func_001c5b88 copies them: an 8-byte aligned
 * struct, so the copy is two ld/sd pairs. */
typedef struct { f32 x, y, z, w; } __attribute__((aligned(8))) CamV4q;

/* D_003C5510 (0x130 bytes: the size of data/pieces/D_003C5510.h's CamS,
 * so the float keep list does not change).
 *
 * Five tween channels, each with a duration, a time and a mode: 0 the
 * position (p0[0] -> p1[0]), 1 the rotation (p0[1] -> p1[1]), 2 f120,
 * 3 f124 and 4 D_0036266C (from p0[2][0..2] to p1[2][0..2]).  Bits 0-3
 * run channel 0-3's linear tween, bits 4-7 their curved one
 * (func_001ca800 runs them every frame), bit 8 shakes the camera around
 * `base` (func_001c8e20, amp / smode / sdur / st), bit 9 runs channel 4
 * (func_001c9d40).
 *
 * The bits share the first word with dur[0].  Some functions change them
 * with 64-bit operations on the doubleword at 0 (`fl.x`), others with
 * 32-bit bit-field operations (`fl.s.b4`) or 64-bit ones (`fl.w.b5`): all
 * three are in the original, so the word is a union. */
typedef struct {
    union {
        u64 x;
        struct {
            u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
            f32 dur[5];             /* 0x004 */
        } s;
        struct {
            u64 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:54;
        } w;
    } fl;                           /* 0x000 */
    f32 t[5];                       /* 0x018 */
    u32 mode[5];                    /* 0x02c */
    CamVec p0[3];                   /* 0x040: from (p0[2]: channels 2-4) */
    CamVec p1[3];                   /* 0x070: to */
    f32 amp[3];                     /* 0x0a0: shake */
    s32 smode;                      /* 0x0ac */
    f32 sdur;                       /* 0x0b0 */
    f32 st;                         /* 0x0b4 */
    u8 padb8[8];
    CamVec base;                    /* 0x0c0 */
    CamVec pos;                     /* 0x0d0: D_003C55E0 */
    CamVec rot;                     /* 0x0e0: D_003C55F0 */
    f32 rx, ry, rz;                 /* 0x0f0 */
    u8 padfc[4];
    CamVec v100;                    /* 0x100 */
    CamVec v110;                    /* 0x110 */
    f32 f120;                       /* 0x120: D_003C5630 */
    f32 f124;                       /* 0x124: D_003C5634 */
    f32 f128;                       /* 0x128 */
    f32 f12c;                       /* 0x12c: D_0036266C saved */
} __attribute__((aligned(16))) CamState;

/* src/camera/camera.c */
void func_001c5168(void);
void func_001c53c8(f32 t);
s32 func_001c5b88(void);
s32 func_001c5db8(void);
void func_001c5ee8(s32 *p);
void func_001c6720(void);
void func_001c6890(void);
void func_001c6a20(void);

#endif /* KH1_CAMERA_CAMERA_H */
