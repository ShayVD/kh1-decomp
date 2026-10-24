/* The Gummi ship types (docs/modules.md "Session 48"): the ships kept in the
 * Gummi save block (src/gummi/gumisave.c), the block table and the garage's
 * lists (src/gummi/ship.c).  Field names are read from the code. */
#ifndef KH1_GUMMI_GUMMI_H
#define KH1_GUMMI_GUMMI_H

#include "common.h"
#include "data/types/fvec.h"

/* One block placed in a ship (12 bytes): its cell in the 16^3 grid, three
 * axis indices into D_0037A130 for its turn, and its block id (1-based). */
typedef struct {
    u16 pos;            /* 0x0: x, y, z nibbles */
    union {
        u16 h;
        struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 w : 4; } b;
    } rot;              /* 0x2 */
    u16 id;             /* 0x4: block id + 1 */
    u16 x6;
    u8 pad8[4];
} GumiPiece;

/* A ship (0xF70 bytes): the ten in the save block (func_001ba9d8), the
 * edited one D_006257D0 and the work copies D_00621320 / D_00622290. */
typedef struct {
    s32 x0;
    u16 n;              /* 0x04: blocks used */
    u16 sx;             /* 0x06: grid size (checked against func_001bb678) */
    u16 sy;             /* 0x08 */
    u16 sz;             /* 0x0a */
    u8 link;            /* 0x0c: the paired ship + 1, or 0 */
    u8 pad0d[0x50 - 0x0d];
    char name[32];      /* 0x50 */
    GumiPiece p[(0xF70 - 0x70) / 12]; /* 0x70 */
} GumiShip;

/* A block's entry in the block table D_00377848 (0x1c bytes). */
typedef struct {
    u8 pad0[4];
    u8 type;            /* 0x04: 0 ends the held kinds; 1, 2 (engines?), 6 ... */
    u8 pad5[2];
    u8 size;            /* 0x07: x, y, z sizes - 1 in two bits each */
    u8 pad8[3];
    u8 max;             /* 0x0b: how many can be held */
    u8 b12;             /* 0x0c */
    u8 b13;             /* 0x0d */
    u8 b14;             /* 0x0e */
    u8 pad0f[5];
    u16 h14;            /* 0x14 */
    u16 h16;            /* 0x16 */
    f32 f24;            /* 0x18 */
} GumiBlock;

typedef struct {
    s32 n;              /* blocks in the table */
    u8 pad4[12];
    GumiBlock e[1];
} GumiBlockTbl;

/* A unit direction of D_0037A130 (the six axis directions first). */
typedef struct { s8 x, y, z, w; } GumiDir;

/* The garage list's summary of one ship (D_00623E40[], 96 bytes). */
typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
    u8 pad12[4];
    FVec4 v16;          /* the bounds' low corner */
    FVec4 v32;          /* the high corner */
    f32 f48;            /* the radius */
    char name[32];      /* 0x34 */
    u8 pad84[12];
} GumiInfo;

/* A ship's stats (func_001bd090, 40 bytes). */
typedef struct { s32 x0, x4, x8, lv, x16, x20, x24, x28, x32, x36; } GumiStat;

/* A held block's line in the garage's block list (D_00623230[], 16 bytes). */
typedef struct { u8 b0, b1, b2, b3, b4, b5, b6, b7, b8; u8 pad9[7]; } GumiCell;

/* A part slot (D_00625750[]): which of ten kinds, and a value. */
typedef struct { u8 id; u8 b; u8 pad[2]; u32 n; } GumiSlot;

GumiShip *func_001ba9d8(s32 i);

#endif /* KH1_GUMMI_GUMMI_H */
