/* Types moved from src/hand/text_00180000_h12.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00180000_H12_H
#define KH1_DATA_TYPES_TEXT_00180000_H12_H

#include "common.h"
#include "ppp.h"

typedef struct {
    u8 pad[0xE];
    u8 hook;     /* +0xE */
} PppProgHdr;
typedef struct {
    s32 unk0, unk4;
    PppProgHdr *hdr;  /* +0x8 */
} PppHookObj;
typedef void (*PppHookFn)(PppHookObj *, s32);

#endif /* KH1_DATA_TYPES_TEXT_00180000_H12_H */
