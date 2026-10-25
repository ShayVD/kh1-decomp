/* The fog a port's fragment shader runs: (F x C + (0xFF - F) x FOGCOL) >> 8 on the colour after the
 * texture function (include/platform/fog.h, docs/renderer-spec.md 4.13 "Session 122"), checked by
 * tests/host/fog_test.c against the GS's formula and host/null/gsmem.c's sprite.  Not part of the PS2
 * build (it lives outside src/). */
#include "common.h"
#include "platform/fog.h"

u32 kh1_fog_gs(u32 c, u32 f, u32 fogcol) {
    u32 i, out = c & 0xFF000000u;
    f &= 0xFF;
    for (i = 0; i < 24; i += 8) out |= ((f * (c >> i & 0xFF) + (0xFF - f) * (fogcol >> i & 0xFF)) >> 8) << i;
    return out;
}

/* the shader's UNORM inputs and its 8-bit output */
static float unorm(u32 v) { return (float)v / 255.0f; }
static u32 back8(float f) { return f <= 0.0f ? 0 : f >= 1.0f ? 255 : (u32)(f * 255.0f + 0.5f); }

u32 kh1_fog_shader(u32 c, u32 f, u32 fogcol, int exact) {
    float cf[3], ff = unorm(f & 0xFF), fc[3];
    u32 i, out = c & 0xFF000000u;
    for (i = 0; i < 3; i++) {
        cf[i] = unorm(c >> i * 8 & 0xFF);
        fc[i] = unorm(fogcol >> i * 8 & 0xFF);
    }
    if (exact) { /* the 8-bit values back, then the GS's integer step */
        u32 ci = c & 0xFF000000u, fi = 0;
        for (i = 0; i < 3; i++) {
            ci |= back8(cf[i]) << i * 8;
            fi |= back8(fc[i]) << i * 8;
        }
        return kh1_fog_gs(ci, back8(ff), fi);
    }
    for (i = 0; i < 3; i++) out |= back8(fc[i] + (cf[i] - fc[i]) * ff) << i * 8;
    return out;
}
