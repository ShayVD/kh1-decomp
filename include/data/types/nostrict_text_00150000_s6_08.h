/* Types moved from src/hand/nostrict/text_00150000_s6_08.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_S6_08_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_S6_08_H

#include "common.h"

typedef struct C03Act C03Act;
typedef struct { u8 pad[0x4C]; u16 h4C; } C03Ch130;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x10];
    f32 v30[4];
    u8 pad40[0x70 - 0x40];
    s32 w70;
    u8 pad74[0x130 - 0x74];
    C03Ch130 *p130;
    u8 pad134[0x164 - 0x134];
    s32 w164;
    u8 pad168[0x370 - 0x168];
    u64 f370;
} C03Chr;
typedef struct { C03Chr *p; s32 i; } C03Tgt;
typedef struct C03AW {
    u8 pad00[0x18];
    s32 n18;
    C03Act *p1C;
    u8 pad20[0x38 - 0x20];
    u64 w38;
    u8 pad40[4];
    void (*cb44)(C03Chr *, struct C03AW *);
    u8 pad48[4];
    s32 w4C;
    u32 w50;
    s32 w54;
    u8 pad58[0x64 - 0x58];
    f32 f64;
    u8 pad68[0x74 - 0x68];
    C03Act *p74;
    s32 n78;
    C03Act *hist[2];
    u8 pad84[0x90 - 0x84];
    C03Tgt t90;
    C03Chr *p98;
    u8 pad9C[0xF0 - 0x9C];
    f32 vF0[4];
    u8 pad100[0x20];
    f32 v120[3];
    f32 f12C;
} C03AW;
struct C03Act {
    s32 x0;
    u32 fl;
    s32 (*cb)(C03Chr *, C03AW *, C03Act *, s32);
    s32 pad;
};

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_S6_08_H */
