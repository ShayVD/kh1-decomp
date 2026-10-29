/* dkmovie.x movie work area (D_00F28460 points at it), shared by the session 141 drafts.
 * Drafts include it as "../nonmatchings/session141/dkmovie/movie_work.h" (resolved through -Iinclude).
 * Field names are their offsets; the matched files in ovl/dkmovie/hand use the same names
 * (flat s32 fields from 0x3DD00). Here the per-slot tables are arrays: the slot count is
 * f3DF50 (s8), slot indices are f3DD40 (decode) and f3DD44 (read). */
#ifndef MOVIE_WORK_H
#define MOVIE_WORK_H

typedef struct MovieWork {
    u8 pad0[0x80];
    u8 f80[0x40];             /* 64 bytes copied to D_00F28690 by func_00f26d90 */
    u8 fC0[0x40];             /* 64 bytes copied to D_00F286D0 */
    s32 size[(0x1E900 - 0x100) / 4]; /* stream frame sizes, 0-terminated (func_00f245c0, func_00f275e0) */
    u8 f1E900[0x6400];        /* f3DD9C points here */
    u8 f24D00[0x6400];        /* f3DDA0 points here */
    u8 pic[2][0x6400];        /* 0x2B100: f3DD94 / f3DD98, double-buffered picture (func_00f20b48) */
    u8 aux[2][0x2300];        /* 0x37900: f3DDAC, second plane (func_00f20b48) */
    u8 pad3BF00[0x3DD00 - 0x3BF00];
    s32 f3DD00;
    s32 f3DD04;
    s32 f3DD08;               /* decoded frame buffer base (u8 *) */
    s32 f3DD0C;
    s32 f3DD10;
    s32 f3DD14;               /* guard word pointer: *(s32 *)f3DD14 == 0x12345678 */
    s32 f3DD18;               /* width in macroblocks */
    s32 f3DD1C;               /* height in macroblocks */
    s32 f3DD20;               /* width in pixels */
    s32 f3DD24;               /* height in pixels */
    s32 f3DD28;
    s32 f3DD2C;               /* frames shown */
    s32 f3DD30;
    s32 f3DD34;
    s32 f3DD38;
    s32 f3DD3C;
    s32 f3DD40;               /* decode slot */
    s32 f3DD44;               /* read slot */
    s32 f3DD48;               /* stream handle */
    s32 f3DD4C;               /* stream position (frame index) */
    s32 f3DD50[3];            /* per-slot first frame */
    s32 f3DD5C[3];            /* per-slot buffer */
    s32 f3DD68[3];            /* per-slot byte count */
    s32 f3DD74[4];            /* per-slot state: 0 free, 1 reading, 2 ready */
    s32 f3DD84[3];            /* per-slot read pointer */
    s32 f3DD90;               /* current packet header (u8 *) */
    s32 f3DD94;
    s32 f3DD98;
    s32 f3DD9C;
    s32 f3DDA0;
    s32 f3DDA4;
    s32 f3DDA8;
    s32 f3DDAC;
    s32 f3DDB0;
    s8 f3DDB4; u8 p3DDB4[3];
    s32 f3DDB8;
    s8 f3DDBC; u8 p3DDBC[3];
    s32 f3DDC0;
    s32 f3DDC4;
    s32 f3DDC8;
    s32 f3DDCC;
    s32 f3DDD0;               /* flags: 4 frame done, 8 stop, 0x40, 0x100, 0x200, 0x1000, 0x2000, 0x8000 task end */
    s8 f3DDD4[0x80];
    s8 f3DE54[0x80];
    s32 f3DED4;
    s32 f3DED8;
    s32 f3DEDC;
    s32 f3DEE0;
    s32 f3DEE4;
    s32 f3DEE8;
    s32 f3DEEC;
    s32 f3DEF0;
    s32 f3DEF4;
    s32 f3DEF8;
    s32 f3DEFC;
    s32 f3DF00;
    s32 f3DF04;
    s32 f3DF08;
    s32 f3DF0C;
    s32 f3DF10;
    s32 f3DF14;
    s32 f3DF18;
    s32 f3DF1C;               /* frame count */
    s32 f3DF20;
    s32 f3DF24;
    s32 f3DF28;
    s32 f3DF2C;
    s32 f3DF30;
    s32 f3DF34;               /* current time */
    s32 f3DF38[2];            /* per-picture time */
    s32 f3DF40;
    s32 f3DF44;
    s32 f3DF48;
    s32 f3DF4C;
    s8 f3DF50;                /* slot count */
    s8 f3DF51;
    s8 f3DF52;
    s8 f3DF53;
    s8 f3DF54;
    s8 f3DF55;
    s8 f3DF56;
    s8 f3DF57;
    s8 f3DF58;
    s8 f3DF59;
    s8 f3DF5A;
    s8 f3DF5B[2];             /* per-picture aux valid */
    s8 f3DF5D[2];             /* per-picture valid */
    s8 f3DF5F;
    s8 f3DF60;
    s8 f3DF61;
    s8 f3DF62;
    s8 f3DF63;
    s8 f3DF64;
    s8 f3DF65;
    s8 f3DF66;
    s8 f3DF67;
    s8 f3DF68;
    s8 f3DF69;
    s8 f3DF6A;
    s8 f3DF6B;
} MovieWork;

extern MovieWork *D_00F28460;
extern u8 *D_00F28464;

#define IPU_CMD (*(volatile s32 *)0x10002000)
#define IPU_CTRL (*(volatile s32 *)0x10002010)
#define D3_CHCR (*(volatile u32 *)0x1000B000)
#define D4_CHCR (*(volatile u32 *)0x1000B400)
#define D1_CHCR (*(volatile u32 *)0x1000D000)

#endif
