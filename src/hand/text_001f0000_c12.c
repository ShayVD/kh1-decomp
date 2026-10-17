#include "common.h"

/*
 * NEEDS LAYOUT SPLIT (not applied; layout.tsv untouched):
 *   func_001ffaf0  0x1ffaf0-0x1ffb30  (60 bytes code + 1 pad nop)
 *   func_001ffb30  0x1ffb30-0x200038  (new symbol, GIF packet builder like func_001ff488)
 * With the split, the following matches in this (strict) dir:
 *
 * typedef struct {
 *     u8 pad0[0xb8];
 *     u16 xb8;
 *     u16 xba;
 * } WinD;
 *
 * s32 func_001ff488(WinD *, s32, s32, s32, s32, s32);
 *
 * s32 func_001ffaf0(WinD *o, s32 a) {
 *     return func_001ff488(o, 0, 0, (s16)o->xb8 >> 4, (s16)o->xba >> 4, a);
 * }
 */
