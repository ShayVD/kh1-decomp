/* The alpha test and the destination alpha test a port's GPU runs for the GS's TEST: discards, write masks
 * and a stencil set-up (include/platform/atest.h, docs/renderer-spec.md 4.13 "Session 121"), checked by
 * tests/host/atest_test.c against the GS's rules and host/null/gsmem.c's sprite.  Not part of the PS2
 * build (it lives outside src/). */
#include "common.h"
#include "platform/atest.h"

int kh1_atest(u32 atst, u32 a, u32 aref) {
    switch (atst & 7) {
    case KH1_ATST_NEVER: return 0;
    case KH1_ATST_ALWAYS: return 1;
    case KH1_ATST_LESS: return a < aref;
    case KH1_ATST_LEQUAL: return a <= aref;
    case KH1_ATST_EQUAL: return a == aref;
    case KH1_ATST_GEQUAL: return a >= aref;
    case KH1_ATST_GREATER: return a > aref;
    }
    return a != aref;
}

/* what a fragment that fails writes under AFAIL, as a mask (bits 0-3 colour, 4 Z) */
static u32 afail_writes(u32 afail, u32 mask, u32 z) {
    switch (afail) {
    case KH1_AFAIL_FB_ONLY: return mask;
    case KH1_AFAIL_ZB_ONLY: return z << 4;
    case KH1_AFAIL_RGB_ONLY: return mask & 7;
    }
    return 0;
}

static void put(KH1AtestState *out, u32 discard, u32 w) {
    if (!w) return; /* writes nothing: left out */
    out->draw[out->n].discard = discard;
    out->draw[out->n].mask = w & 0xF;
    out->draw[out->n].zwrite = w >> 4 & 1;
    out->n++;
}

void kh1_atest_state(u32 test_lo, u32 mask, u32 zmsk, KH1AtestState *out) {
    u32 ate = test_lo & 1, atst = test_lo >> 1 & 7, afail = test_lo >> 12 & 3, zte = test_lo >> 16 & 1;
    u32 ztst = test_lo >> 17 & 3, z = zte && !zmsk, all = (mask & 0xF) | z << 4, fail;
    out->n = 0;
    out->atst = atst;
    out->aref = test_lo >> 4 & 0xFF;
    out->date = test_lo >> 14 & 1;
    out->datm = test_lo >> 15 & 1;
    /* ZTST NEVER draws nothing; ZTE 0 is ALWAYS (renderer-spec 3.2) */
    if (zte && ztst == 0) return;
    out->ztest = !zte || ztst == 1 ? 0 : ztst - 1;
    if (!ate || atst == KH1_ATST_ALWAYS) { put(out, KH1_DISCARD_NONE, all); return; }
    fail = afail_writes(afail, mask & 0xF, z);
    if (atst == KH1_ATST_NEVER) { put(out, KH1_DISCARD_NONE, fail); return; }
    if (fail == all) { put(out, KH1_DISCARD_NONE, all); return; } /* both write the same */
    put(out, KH1_DISCARD_FAIL, all);
    put(out, KH1_DISCARD_PASS, fail);
}

int kh1_atest_date_mark(const KH1AtestState *st, u32 a8) { return (a8 == 255) == st->datm; }

u32 kh1_atest_gpu(const KH1AtestState *st, u32 a, int marked) {
    u32 i, w = 0, pass = kh1_atest(st->atst, a & 0xFF, st->aref);
    if (st->date && !marked) return 0;
    for (i = 0; i < st->n; i++) {
        const KH1AtestDraw *d = &st->draw[i];
        if (d->discard == KH1_DISCARD_FAIL && !pass) continue;
        if (d->discard == KH1_DISCARD_PASS && pass) continue;
        w |= d->mask | (u32)d->zwrite << 4;
    }
    return w;
}

u32 kh1_atest_gs(u32 test_lo, u32 mask, u32 zmsk, u32 a, u32 ad) {
    u32 zte = test_lo >> 16 & 1, z = zte && !zmsk;
    if (zte && (test_lo >> 17 & 3) == 0) return 0;                          /* ZTST NEVER */
    if (test_lo >> 14 & 1 && (ad >> 7 & 1) != (test_lo >> 15 & 1)) return 0; /* DATE */
    if (!(test_lo & 1) || kh1_atest(test_lo >> 1 & 7, a, test_lo >> 4 & 0xFF)) return (mask & 0xF) | z << 4;
    return afail_writes(test_lo >> 12 & 3, mask & 0xF, z);
}
