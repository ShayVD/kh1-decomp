/* More types moved from src/hand/text_00180000_h12.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00180000_H12_P_H
#define KH1_DATA_TYPES_TEXT_00180000_H12_P_H

#include "common.h"
#include "ppp.h"
#include "data/types/text_00180000_h12.h"

typedef struct {
    s32 unk0;
    s32 n;
} PppTblHdr;
typedef struct {
    s32 unk0, unk4;
    s32 key;    /* +0x8 */
    u8 pad[0x44];
} PppTblEnt;
typedef struct {
    s32 unk0;
    PppTblHdr *hdr;   /* +0x4 */
    PppTblEnt *ent;   /* +0x8 */
} PppTbl;

#endif /* KH1_DATA_TYPES_TEXT_00180000_H12_P_H */
