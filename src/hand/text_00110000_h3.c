/* Hand-matched functions in 0x00114000-0x0011e000 (worker h3). Grouped by
 * address; the original translation units are not known yet. */
#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"

typedef int u128 __attribute__((mode(TI)));

/* Quadword copy through $6, the way the SDK's sceVu0CopyVector-style inline
 * asm does it (lq/sq plus trailing nops; the delay slot after it stays empty). */
static inline void CopyQword(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop\nnop" : : "r"(dst), "r"(src) : "$6");
}

/* ---- externs ---- */
extern s32 D_004D9370;

/* Entry with a 4-bit kind in the high nibble of its first byte. */

/* Sound-slot table: D_004E344C entries of 24 bytes at *D_004E3450. */
#include "data/types/text_00110000_h3.h"

/* Strings in .rodata, referenced through their data symbols so the copies
 * stay block moves without emitting new rodata: "%3d", "amusic/music",
 * ".dat", "amusic/se". */
#include "data/types/text_00110000_h3_p.h"

typedef struct {
    s32 n;
    s32 x4[5];
    s32 off; /* byte offset of the payload from the header */
} RelHdr;
extern s32 D_004DBC28[][64][36];
extern s32 D_00351BD0;
extern s32 D_002BC170[4][4];
void func_001089d0(void *);
void func_00108fd0(s32, s32, s32, void *, s32);

/* Taking &a (an ADDRESSOF that gcc later folds away) is what keeps the
 * original from turning the call into a sibcall. */
void func_001149b0(RelHdr *a) {
    s32 *p = &a->off;
    RelHdr **pp = &a;
    if ((*pp)->n >= 2) func_001089d0((u8 *)a + *p);
}

s32 func_001149e8(s32 a0, u8 *a1, s32 a2, s32 a3) {
    void *p = a1 + *(s32 *)(a1 + 0x20);
    func_00108fd0(D_004D9370++, a2, a0, p, a3);
    return 1;
}

void func_00114db0(s32 a0, s32 (*a1)[4]) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_004DBC28[D_00351BD0][a0][k] = a1[i][j];
            D_004DBC28[D_00351BD0][a0][k + 16] = D_002BC170[i][j];
            k++;
        }
    }
}

/* Fill a 4-float vector with *b (inline asm block, ends in a nop). */

/* List filters: append a0 to D_002BD250 when the flags at *a1 match. */

/* Clear word 12 of each of the 64 table entries. */

/* Claim the first inactive slot; the extra arguments pass straight through. */
#include "data/bss_004E_typed.h"
#include "data/bss_004E_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BC170.h"
