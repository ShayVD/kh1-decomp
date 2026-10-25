/* The depth state a port's GPU runs for the GS's ZBUF / ZTE / ZTST and the vertices' Z (include/platform/
 * depth.h, docs/renderer-spec.md 4.13 "Session 122"), checked by tests/host/depth_test.c against the GS's
 * rules and host/null/gsmem.c's sprite.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/depth.h"

static u32 zbits(u32 psm) {
    switch (psm) {
    case 0x30: return 32;
    case 0x31: return 24;
    }
    return 16; /* Z16 0x32, Z16S 0x3A */
}

void kh1_depth_state(u32 zbuf_lo, u32 zbuf_hi, u32 test_lo, KH1DepthState *out) {
    u32 zte = test_lo >> 16 & 1, ztst = test_lo >> 17 & 3;
    out->psm = 0x30 | (zbuf_lo >> 24 & 15);
    out->bits = zbits(out->psm);
    out->draw = !(zte && ztst == KH1_ZTST_NEVER);
    out->func = zte && out->draw ? ztst : KH1_ZTST_ALWAYS;
    out->write = zte && out->draw && !(zbuf_hi & 1);
}

u32 kh1_depth_clamp(u32 z, u32 psm) {
    u32 b = zbits(psm), max = b == 32 ? ~0u : (1u << b) - 1;
    return z > max ? max : z;
}

/* 2^-bits as a float: exact (a power of two) */
static float scale(u32 b) { return b == 32 ? 1.0f / 4294967296.0f : b == 24 ? 1.0f / 16777216.0f : 1.0f / 65536.0f; }

float kh1_depth_f32(u32 z, u32 psm) { return (float)kh1_depth_clamp(z, psm) * scale(zbits(psm)); }

u32 kh1_depth_bits(float d, u32 psm) {
    u32 b = zbits(psm);
    double v = (double)d / (double)scale(b);
    if (v <= 0.0) return 0;
    if (b < 32 && v >= (double)(1u << b)) return (1u << b) - 1;
    if (v >= 4294967295.0) return ~0u;
    return (u32)(v + 0.5);
}

/* volatile: rounded to a float as a GPU's 32-bit ALU does, not kept in the x87's wider registers
 * (the -m32 host build) */
float kh1_depth_d24(u32 z) {
    volatile float d = (float)kh1_depth_clamp(z, 0x31) / 16777215.0f;
    return d;
}

u32 kh1_depth_d24_store(float d) {
    volatile float v = d * 16777215.0f;
    if (v <= 0.0f) return 0;
    if (v >= 16777215.0f) return 0xFFFFFF;
    return (u32)((double)v + 0.5);
}

int kh1_depth_gs(u32 zte, u32 ztst, u32 z, u32 zb) {
    if (!zte) return 1;
    switch (ztst & 3) {
    case KH1_ZTST_NEVER: return 0;
    case KH1_ZTST_ALWAYS: return 1;
    case KH1_ZTST_GEQUAL: return z >= zb;
    }
    return z > zb;
}

int kh1_depth_gpu(const KH1DepthState *st, float d, float db) {
    if (!st->draw) return 0;
    switch (st->func) {
    case KH1_ZTST_GEQUAL: return d >= db;
    case KH1_ZTST_GREATER: return d > db;
    }
    return 1;
}
