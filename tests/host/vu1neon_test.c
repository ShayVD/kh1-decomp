/* host/port/vu1.c's vu_ope / vu_opbe (session 141): the four-lane form of the FMACs vu1_tr.c ran field by
 * field (the MAC flag's, OPMULA / OPMSUB) against that scalar form, on random operands weighted to the
 * edges (0, -0, denormals, the smallest normals, the largest, inf / NaN patterns fin() clamps).  Where it
 * answers 1, every field of dest and the MAC bits must equal the scalar form's; where it answers 0, the
 * caller runs the scalar form.  Meaningful on ARM with NEON (tests/selftest.sh: arm-linux-gnueabihf-gcc
 * -mfpu=neon under qemu-arm, when both are there); elsewhere vu_ope always answers 0. */
#include "common.h"
#include "../../host/port/vu1.c"

unsigned long kh1_host_frame(void) { return 0; }
int atoi(const char *);

static u32 rs = 99;
static u32 rnd(void) {
    rs ^= rs << 13;
    rs ^= rs >> 17;
    rs ^= rs << 5;
    return rs;
}

static u32 val(void) {
    u32 s = rnd() & 0x80000000u, r = rnd();
    switch (rnd() % 10) {
    case 0: return s;                                   /* +-0 */
    case 1: return s | (r & 0x7FFFFF);                  /* denormal */
    case 2: return s | (1 + rnd() % 3) << 23 | (r & 0x7FFFFF); /* the smallest normals */
    case 3: return s | (0xFC + rnd() % 4) << 23 | (r & 0x7FFFFF); /* the largest, and inf / NaN patterns */
    case 4: return s | (0x3F000000 + (r & 0x00FFFFFF));  /* around 1 */
    case 5: return s | (0x20 + rnd() % 0x20) << 23 | (r & 0x7FFFFF); /* products that underflow */
    default: return r;
    }
}

/* the scalar form vu1_translate.py writes */
static void scalar(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, u32 dest, u32 *macf) {
    u32 f;
    for (f = 0; f < 4; f++) {
        f32 r, x, y;
        if (!(dest >> (3 - f) & 1)) continue;
        x = fin(a[f]);
        y = fin(b[f]);
        switch (k) {
        case K_ADD: r = x + y; break;
        case K_SUB: r = x - y; break;
        case K_MUL: r = x * y; break;
        case K_MADD: r = fin(c[f]) + x * y; break;
        default: r = fin(c[f]) - x * y; break;
        }
        t[f] = macf ? fout(r, f, macf) : fo(r);
    }
}

int main(int argc, char **argv) {
    static const int ks[5] = { K_ADD, K_SUB, K_MUL, K_MADD, K_MSUB };
    u32 n = argc > 1 ? (u32)atoi(argv[1]) : 2000000, i, fast = 0, bad = 0;
    for (i = 0; i < n; i++) {
        u32 a[4], b[4], c[4], bb[4], te[4], tv[4], me = 0, mv = 0, dest = 1 + rnd() % 15, f, ok;
        int k = ks[rnd() % 5], withmac = rnd() & 1, bcast = rnd() % 3 == 0;
        for (f = 0; f < 4; f++) { a[f] = val(); b[f] = val(); c[f] = val(); }
        for (f = 0; f < 4; f++) bb[f] = bcast ? b[0] : b[f];
        scalar(te, k, a, bb, c, dest, withmac ? &me : 0);
        ok = bcast ? vu_opbe(tv, k, a, b[0], c, dest, withmac ? &mv : 0) : vu_ope(tv, k, a, b, c, dest, withmac ? &mv : 0);
        if (!ok) continue;
        fast++;
        for (f = 0; f < 4; f++)
            if (dest >> (3 - f) & 1 && te[f] != tv[f]) break;
        if (f < 4 || me != mv) {
            if (bad++ < 10)
                printf("vu1neon_test: k %d dest %x mac %d field %u: scalar %08x mac %04x, lanes %08x mac %04x (a %08x b %08x c %08x)\n",
                       k, dest, withmac, f, f < 4 ? te[f] : 0, me, f < 4 ? tv[f] : 0, mv, a[f & 3], bb[f & 3], c[f & 3]);
        }
    }
    printf("vu1neon_test: %u cases, %u on four lanes, %u differ: %s\n", n, fast, bad, bad ? "FAIL" : "PASS");
    return bad != 0;
}
