/* ttlib/ui.c (include/hud/ui.h, docs/modules.md "Session 47"): the two
 * built with -fno-strict-aliasing.  From a sprite file (its elements at
 * +off), func_0024af40 copies the elements an index list (ended by -1)
 * names and func_0024afc0 stores pointers to them. */
#include "common.h"
#include "hud/ui.h"

typedef struct { s32 unk0; s32 unk4; s32 off; } UiHdr;

void func_0024af40(s32 *idx, UiSpr *out, UiHdr *h) {
    UiSpr *base = (UiSpr *)((u8 *)h + h->off);
    for (; *idx != -1; idx++, out++)
        *out = base[*idx];
}

void func_0024afc0(s32 *idx, UiSpr **out, UiHdr *h) {
    UiSpr *base = (UiSpr *)((u8 *)h + h->off);
    while (*idx != -1)
        *out++ = &base[*idx++];
}
