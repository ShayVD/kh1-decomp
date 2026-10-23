#include "common.h"
#include "data/bss_0064.h"
/* What is left of a session-6 file (func_0022ebf8, the item / member check of a
   shop); the rest moved into src/menu/ (sessions 40 to 43). */

/* ---- febf8/MATCH_ebf8.c ---- */

typedef struct {
    u8 pad00[0x21];
    u8 n;
    u8 items[0x74 - 0x22];
} EbMember_q8;
typedef struct {
    u8 pad000[4];
    EbMember_q8 m[10];
    u8 x48c;
    u8 x48d;
    u8 party[11];
    u8 cnt[1];
} EbSave_q8;
extern EbSave_q8 *D_00304BE8_q8 __asm__("D_00304BE8");
extern s32 *D_00646A0C;
extern s32 D_00646A18;
extern u32 D_00646A20;
extern s32 D_00646A28;
#include "data/pieces/D_003E3D6C.h"
extern EbMember_q8 *D_00647634; /* src/data/bss_0064.c: s32 D_00647634 */
extern s32 D_00647638;
extern u32 D_0064763C; /* src/data/bss_0064.c: s32 D_0064763C */
s32 func_001ee708(s32);
u32 func_001ef7a0(void);
s32 func_001ee9e0(s32);

void func_0022ebf8(s32 idx) {
    s32 id, i, n, r;
    EbMember_q8 *m;

    id = D_00646A0C[idx];
    D_00646A18 = id;
    D_0064763C = func_001ee708(id) * D_00646A28;
    if (func_001ef7a0() < D_0064763C) goto err;
    if (D_00646A20 < D_003E3D6C) {
        if (D_00646A28 == 1) {
        if (func_001ee9e0(id)) {
            m = &D_00304BE8_q8->m[D_00304BE8_q8->party[D_00646A20]];
            D_00647634 = m;
            n = m->n;
            for (i = 0; i < n; i++) {
                if (!m->items[i]) goto found;
            }
            D_00646A18 = -2;
            return;
        }
        D_00646A18 = -3;
        return;
        }
        D_00646A18 = -4;
        return;
    }
    if (D_00304BE8_q8->cnt[D_00646A18] == 99) {
        D_00646A18 = -2;
        return;
    }
    if (D_00304BE8_q8->cnt[D_00646A18] + D_00646A28 >= 100) {
        D_00646A18 = -4;
        return;
    }
    D_00647634 = 0;
    D_00647638 = D_00646A18;
    return;
found:
    D_00647638 = i;
    return;
err:
    D_00646A18 = -1;
}

#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/data_003E.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F50E0.h"
