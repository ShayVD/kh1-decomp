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
 * so the float keep list does not change). */
typedef struct {
    union {
        u64 x;                      /* bits 0-8: tween running, per axis */
        struct { u32 bits; f32 dur[4]; f32 x14; } s;
    } fl;                           /* 0x000 */
    f32 t[4];                       /* 0x018 */
    f32 x28;                        /* 0x028 */
    u32 mode[4];                    /* 0x02c */
    u8 pad3c[4];
    CamVec p0[3];                   /* 0x040 */
    CamVec p1[3];                   /* 0x070 */
    f32 amp[3];                     /* 0x0a0 */
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
    f32 f120;                       /* 0x120 */
    f32 f124;                       /* 0x124 */
    f32 f128;                       /* 0x128 */
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
