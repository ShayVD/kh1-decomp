/* host/port/vu1.c's vu_ope / vu_opbe (session 141): the four-lane form of the FMACs vu1_tr.c ran field by
 * field (the MAC flag's, OPMULA / OPMSUB) against that scalar form, on random operands weighted to the
 * edges (0, -0, denormals, the smallest normals, the largest, inf / NaN patterns fin() clamps).  Where it
 * answers 1, every field of dest and the MAC bits must equal the scalar form's; where it answers 0, the
 * caller runs the scalar form.  Session 147: also vu_op / vu_opb (the FMACs' usual form) against their
 * session 141 form, kept here verbatim (old_*), bit for bit on every lane (their fin() / fout() clamps
 * changed; vu_opbl takes the broadcast field from the vector), and vu_put against the field copy it replaced.  Session 149:
 * a third of the cases with fields that cancel (b = +-a, c = +-a*b, some one bit off), the exact 0's Z.  Meaningful on ARM with NEON (tests/selftest.sh: arm-linux-gnueabihf-gcc
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

#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
static float32x4_t old_vfin(uint32x4_t u) {
    uint32x4_t s = vandq_u32(u, vdupq_n_u32(0x80000000u));
    uint32x4_t m = vminq_u32(vandq_u32(u, vdupq_n_u32(0x7FFFFFFFu)), vdupq_n_u32(0x7F7FFFFFu));
    return vreinterpretq_f32_u32(vorrq_u32(s, m));
}
static uint32x4_t old_vfo(float32x4_t r) {
    uint32x4_t u = vreinterpretq_u32_f32(r);
    uint32x4_t s = vandq_u32(u, vdupq_n_u32(0x80000000u));
    return vorrq_u32(s, vminq_u32(vandq_u32(u, vdupq_n_u32(0x7FFFFFFFu)), vdupq_n_u32(0x7F7FFFFFu)));
}
static float32x4_t old_vin(uint32x4_t u, int fi) { return fi ? old_vfin(u) : vreinterpretq_f32_u32(u); }
static void old_vu_op(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, int fa, int fb, int fc) {
    float32x4_t x = old_vin(vld1q_u32(a), fa), y = old_vin(vld1q_u32(b), fb), r;
    switch (k) {
    case K_ADD: r = vaddq_f32(x, y); break;
    case K_SUB: r = vsubq_f32(x, y); break;
    case K_MUL: r = vmulq_f32(x, y); break;
    case K_MADD: r = vaddq_f32(old_vin(vld1q_u32(c), fc), vmulq_f32(x, y)); break;
    case K_MSUB: r = vsubq_f32(old_vin(vld1q_u32(c), fc), vmulq_f32(x, y)); break;
    default: {
        uint32x4_t gt = k == K_MAX ? vcgtq_f32(x, y) : vcltq_f32(x, y);
        vst1q_u32(t, old_vfo(vreinterpretq_f32_u32(vflush(vbslq_u32(gt, vreinterpretq_u32_f32(x), vreinterpretq_u32_f32(y))))));
        return;
    }
    }
    vst1q_u32(t, old_vfo(r));
}
/* an operand the translator passes without fin() (fa 0) is one the VU wrote: canonical, never inf / NaN */
static u32 canon(u32 u) { return fo(fin(u) * 1.0f); }
static u32 op_check(u32 n) {
    static const int ks[7] = { K_ADD, K_SUB, K_MUL, K_MADD, K_MSUB, K_MAX, K_MINI };
    u32 i, f, bad = 0;
    for (i = 0; i < n; i++) {
        u32 a[4], b[4], c[4], t0[4], t1[4], put[4], ref[4], dest = rnd() % 16;
        int k = ks[rnd() % 7], fa = rnd() & 1, fb = rnd() & 1, fc = rnd() & 1, bc = rnd() % 3 == 0;
        for (f = 0; f < 4; f++) {
            a[f] = fa ? val() : canon(val());
            b[f] = fb ? val() : canon(val());
            c[f] = fc ? val() : canon(val());
            put[f] = ref[f] = rnd();
        }
        if (bc) {
            u32 l = rnd() & 3, bb[4];
            bb[0] = bb[1] = bb[2] = bb[3] = b[l];
            old_vu_op(t0, k, a, bb, c, fa, fb, fc);
            if (rnd() & 1) vu_opb(t1, k, a, &b[l], c, fa, fb, fc);
            else switch (l) { /* vu_opbl's lane is a constant where vu1_tr.c calls it */
                case 0: vu_opbl(t1, k, a, b, 0, c, fa, fb, fc); break;
                case 1: vu_opbl(t1, k, a, b, 1, c, fa, fb, fc); break;
                case 2: vu_opbl(t1, k, a, b, 2, c, fa, fb, fc); break;
                default: vu_opbl(t1, k, a, b, 3, c, fa, fb, fc); break;
            }
        } else {
            old_vu_op(t0, k, a, b, c, fa, fb, fc);
            vu_op(t1, k, a, b, c, fa, fb, fc);
        }
        vu_put(put, t1, dest);
        for (f = 0; f < 4; f++)
            if (dest >> (3 - f) & 1) ref[f] = t0[f];
        for (f = 0; f < 4; f++)
            if (t0[f] != t1[f] || put[f] != ref[f]) break;
        if (f < 4 && bad++ < 10)
            printf("vu1neon_test: vu_op%s k %d fa %d fb %d fc %d field %u: old %08x new %08x put %08x / %08x\n", bc ? "b" : "",
                   k, fa, fb, fc, f, t0[f], t1[f], put[f], ref[f]);
    }
    for (i = 0; i < n; i++) { /* vu_clipw against clipw */
        u32 a[4], t[4], x, y;
        for (f = 0; f < 4; f++) { a[f] = val(); t[f] = val(); }
        if (rnd() % 4 == 0) t[3] = a[rnd() % 3] ^ (rnd() & 0x80000000u); /* ties with a field */
        clip_last = rnd();
        x = clipw(a, t[3]);
        y = vu_clipw(a, t);
        if (x != y && bad++ < 10) printf("vu1neon_test: clipw %08x %08x %08x w %08x: %06x, vu_clipw %06x\n", a[0], a[1], a[2], t[3], x, y);
    }
    printf("vu1neon_test: vu_op / vu_opb / vu_opbl / vu_put / vu_clipw, %u cases, %u differ\n", n, bad);
    return bad;
}
#else
static u32 op_check(u32 n) { return 0; }
#endif

#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
/* 2026-11-01: native P0's per-vertex colour and ST (vu1_draw.h nd0_vert) against its scalar form, on colours and scales
 * weighted to bytes, 1.0, the saturating edges and huge values, and ST of any s32 */
static u32 nd0_check(u32 n) {
    u32 i, bad = 0;
    for (i = 0; i < n; i++) {
        u32 c[4], t[2], o1[2], o2[2], r1, r2, k;
        f32 sc[4];
        for (k = 0; k < 4; k++) {
            u32 m = rnd() % 6;
            c[k] = m < 3 ? rnd() & 0xFF : m == 3 ? rnd() : m == 4 ? (u32)(s32)(s16)rnd() : 0x7FFFFF80u + rnd() % 0x100;
            m = rnd() % 5;
            sc[k] = m == 0 ? 1.0f : m == 1 ? fin(val()) : m == 2 ? (f32)(rnd() % 512) / 256.0f : m == 3 ? 128.0f : -fin(val());
        }
        t[0] = rnd() % 3 ? (u32)(s32)(s16)rnd() : rnd();
        t[1] = rnd() % 3 ? (u32)(s32)(s16)rnd() : rnd();
        nd0_vert_c(c, t, sc, o1, &r1);
        nd0_vert(c, t, vld1q_f32(sc), sc, o2, &r2);
        if ((r1 != r2 || o1[0] != o2[0] || o1[1] != o2[1]) && bad++ < 10)
            printf("vu1neon_test: nd0_vert c %08x %08x %08x %08x sc %08x: %08x / %08x st %08x %08x / %08x %08x\n", c[0], c[1],
                   c[2], c[3], fo(sc[0]), r1, r2, o1[0], o1[1], o2[0], o2[1]);
    }
    printf("vu1neon_test: nd0_vert, %u cases, %u differ\n", n, bad);
    return bad;
}
#else
static u32 nd0_check(u32 n) { return 0; }
#endif

int main(int argc, char **argv) {
    static const int ks[5] = { K_ADD, K_SUB, K_MUL, K_MADD, K_MSUB };
    u32 n = argc > 1 ? (u32)atoi(argv[1]) : 2000000, i, fast = 0, bad = 0;
    for (i = 0; i < n; i++) {
        u32 a[4], b[4], c[4], bb[4], te[4], tv[4], me = 0, mv = 0, dest = 1 + rnd() % 15, f, ok;
        int k = ks[rnd() % 5], withmac = rnd() & 1, bcast = rnd() % 3 == 0;
        for (f = 0; f < 4; f++) { a[f] = val(); b[f] = val(); c[f] = val(); }
        if (rnd() % 3 == 0) /* session 149: results that cancel to 0 (or a denormal NEON flushes): b = +-a, c = +-a*b */
            for (f = 0; f < 4; f++) {
                Fu x;
                if (rnd() & 1) continue;
                if (k == K_MADD || k == K_MSUB) {
                    x.f = fin(a[f]) * fin(bcast ? b[0] : b[f]);
                    c[f] = (x.u & 0x7F800000u ? x.u : x.u & 0x80000000u) ^ (k == K_MADD ? 0x80000000u : 0) ^ (rnd() % 4 ? 0 : 1);
                } else if (!bcast)
                    b[f] = a[f] ^ (k == K_ADD ? 0x80000000u : 0) ^ (rnd() % 4 ? 0 : 1);
            }
        for (f = 0; f < 4; f++) bb[f] = bcast ? b[0] : b[f];
        scalar(te, k, a, bb, c, dest, withmac ? &me : 0);
        ok = bcast ? vu_opbe(tv, k, a, b, c, dest, withmac ? &mv : 0) : vu_ope(tv, k, a, b, c, dest, withmac ? &mv : 0);
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
    bad += op_check(n);
    bad += nd0_check(n);
    printf("vu1neon_test: %u cases, %u on four lanes, %u differ: %s\n", n, fast, bad, bad ? "FAIL" : "PASS");
    return bad != 0;
}
