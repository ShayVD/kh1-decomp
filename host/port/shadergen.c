/* The shaders as Cg source and a CPU interpreter of what is generated (include/platform/shadergen.h,
 * docs/renderer-spec.md 4.13 "Session 127"), both from the table `forms`: the generator writes each
 * statement as one of them, the interpreter matches each line back against them.  Checked by
 * tests/host/shadergen_test.c against texfunc.c, fog.c, blend.c, atest.c, texfmt.c and sampler.c.  Plain C
 * with no libc but memset / memcpy (the Vita build compiles host/port/).  Not part of the PS2 build (it lives
 * outside src/). */
#include "common.h"
#include "platform/shadergen.h"
#include "platform/vertex.h"
#include "platform/texfmt.h"
#include "platform/texfunc.h"

void *memset(void *, int, __SIZE_TYPE__);

/* ---- the table: each statement's right-hand side ('%' an operand), or a statement of its own ---- */
enum {
    F_MOV, F_ADD, F_SUB, F_MUL, F_MAD, F_DIV, F_FLOORMUL, F_FLOORMUL3, F_CEILMUL, F_ROUND, F_MIN, F_CLAMP,
    F_STEP, F_LERP, F_TEX, F_DOTM, F_CLIP, F_COUNT
};
static const char *forms[F_COUNT] = {
    "%",                    /* F_MOV */
    "% + %",                /* F_ADD */
    "% - %",                /* F_SUB */
    "% * %",                /* F_MUL */
    "% * % + %",            /* F_MAD */
    "% / %",                /* F_DIV */
    "floor(% * %)",         /* F_FLOORMUL: the GS's >> as a floored product by a power of 2 */
    "floor(% * % * %)",     /* F_FLOORMUL3 */
    "ceil(% * %)",          /* F_CEILMUL: a negated floored product */
    "floor(% * % + %)",     /* F_ROUND: a UNORM back to its 8 bits (x 255 + 0.5) */
    "min(%, %)",            /* F_MIN */
    "clamp(%, %, %)",       /* F_CLAMP */
    "step(%, %)",           /* F_STEP: 1 where the second >= the first */
    "lerp(%, %, %)",        /* F_LERP: a select by a 0 / 1 weight */
    "tex2D(tex, %)",        /* F_TEX */
    "dot(u_m[(int)%], %)",  /* F_DOTM: a row of the native renderer's matrices (natdraw.h) times a vector */
    "clip(%)"               /* F_CLIP: a statement: discard where a component < 0 */
};
static u32 form_uses[F_COUNT];

u32 kh1_shader_forms(const char ***f, const u32 **uses) {
    *f = forms;
    *uses = form_uses;
    return F_COUNT;
}

static const char *names[KH1_SV_COUNT] = { "col", "tc", "fog", "pos", "dst", "u_a", "u_b", "u_r", "u_c", "u_xf", "r0", "r1", "r2",
                                           "r3", "r4", "r5", "r6", "r7", "ocolor", "opos", "ocol", "otc", "ofog", "mi", "mi2", "pos2" };
static int scalar_var(u32 i) { return i == KH1_SV_FOG || i == KH1_SV_OFOG || i == KH1_SV_MI || i == KH1_SV_MI2; }

/* ---- the writer ---- */
typedef struct {
    char *buf;
    u32 cap, n, over;
} Gen;

static void put(Gen *g, const char *s) {
    while (*s) {
        if (g->n + 1 < g->cap) g->buf[g->n++] = *s;
        else g->over = 1;
        s++;
    }
    if (g->cap) g->buf[g->n < g->cap ? g->n : g->cap - 1] = 0;
}

/* "    dst = <form with a, b, c>;" (F_CLIP: "    clip(a);") */
static void st(Gen *g, const char *dst, u32 f, const char *a, const char *b, const char *c) {
    const char *op[3], *p;
    u32 i = 0;
    op[0] = a;
    op[1] = b;
    op[2] = c;
    put(g, "    ");
    if (f != F_CLIP) {
        put(g, dst);
        put(g, " = ");
    }
    for (p = forms[f]; *p; p++) {
        char ch[2];
        if (*p == '%') { put(g, i < 3 && op[i] ? op[i] : "?"); i++; continue; }
        ch[0] = *p;
        ch[1] = 0;
        put(g, ch);
    }
    put(g, ";\n");
}

static void regs(Gen *g) {
    u32 i;
    for (i = 0; i < 8; i++) {
        put(g, "    float4 ");
        put(g, names[KH1_SV_R0 + i]);
        put(g, " = float4(0.0, 0.0, 0.0, 0.0);\n");
    }
}

static const char *lit(s32 v) {
    switch (v) {
    case -2: return "-2.0";
    case -1: return "-1.0";
    case 0: return "0.0";
    case 1: return "1.0";
    case 2: return "2.0";
    }
    return "3.0";
}

static void key_str(Gen *g, const KH1ShaderKey *k) {
    static const char *fmt[] = { "none", "rgba8", "a1b5g5r5", "p8", "p4" };
    static const char *tfx[] = { "modulate", "decal", "highlight", "highlight2" };
    static const char *at[] = { "never", "always", "less", "lequal", "equal", "gequal", "greater", "notequal" };
    char n[4];
    if (k->setup == 2) { put(g, "DATE clear"); return; }
    if (k->setup) { put(g, k->datm ? "DATE set-up (DATM 1)" : "DATE set-up (DATM 0)"); return; }
    if (k->tex) {
        put(g, "tex ");
        put(g, k->tex < 5 ? fmt[k->tex] : "?");
        if (k->texa) put(g, "+texa");
        put(g, " ");
        put(g, tfx[k->tfx & 3]);
        put(g, k->tcc ? " tcc" : "");
        put(g, k->fst ? " uv" : " stq");
        if (k->su == KH1_SHADER_CLAMP) put(g, " clamp-u");
        if (k->sv == KH1_SHADER_CLAMP) put(g, " clamp-v");
        if (k->su == KH1_SHADER_TAPS) put(g, " region-u");
        if (k->sv == KH1_SHADER_TAPS) put(g, " region-v");
    } else {
        put(g, "flat");
    }
    if (k->fog) put(g, " fog");
    if (k->lin) put(g, " lin");
    if (k->discard) {
        put(g, k->discard == KH1_DISCARD_FAIL ? " discard-fail " : " discard-pass ");
        put(g, at[k->atst & 7]);
    }
    if (k->fetch) {
        static const char hex[] = "0123456789abcdef";
        char h[10];
        u32 i;
        put(g, k->fetch == 1 ? " fetch " : " fetch-mask");
        if (k->fetch == 1) { h[0] = hex[k->fabcd >> 4]; h[1] = hex[k->fabcd & 15]; h[2] = 0; put(g, h); }
        if (k->fpsm == 1) put(g, " ct24");
        if (k->fbm[0] | k->fbm[1] | k->fbm[2] | k->fbm[3]) {
            for (i = 0; i < 4; i++) { h[i * 2] = hex[k->fbm[3 - i] >> 4]; h[i * 2 + 1] = hex[k->fbm[3 - i] & 15]; }
            h[8] = 0;
            put(g, " fbmsk ");
            put(g, h);
        }
    }
    if (k->fetch != 1 && (k->pre_a != 2 || k->pre_d != 3)) {
        put(g, " pre ");
        n[0] = (char)('0' + k->pre_a);
        n[1] = (char)('0' + k->pre_d);
        n[2] = (char)('0' + k->pre_floor);
        n[3] = 0;
        put(g, n);
        if (k->pre_a != 2) put(g, k->csel == 2 ? " fix" : " as");
    }
}

/* a colour byte's FBMSK as a float merge: 0 written, 8 kept, 1 .. 7 the low k bits kept (*hi 0) or the
 * low k bits written and the rest kept (*hi 1); -1 another shape */
static s32 mask_shape(u32 m, u32 *hi) {
    s32 k;
    *hi = 0;
    if (!m) return 0;
    if (m == 0xFF) return 8;
    for (k = 1; k < 8; k++) {
        if (m == (1u << k) - 1) return k;
        if (m == (0xFFu & ~((1u << k) - 1))) { *hi = 1; return k; }
    }
    return -1;
}

/* the GS's blend on Cs (r4) and the target (dst): r4.xyz = clamp(((A - B) x C >> 7) + D) (blend.h kh1_blend_gs) */
static void fetch_blend(Gen *g, const KH1ShaderKey *k) {
    static const char *cs = "r4.xyz", *cd = "r3.xyz";
    u32 A = k->fabcd & 3, B = k->fabcd >> 2 & 3, C = k->fabcd >> 4 & 3, D = k->fabcd >> 6 & 3;
    const char *a = A == 0 ? cs : A == 1 ? cd : 0, *b = B == 0 ? cs : B == 1 ? cd : 0, *d = D == 0 ? cs : D == 1 ? cd : 0;
    st(g, "r3", F_MOV, "dst", 0, 0); /* Cd, and Ad read back from the 0x80 scale: (a8 x 128 + 127) / 255 */
    if (k->fpsm == 1) st(g, "r3.w", F_MOV, "128.0", 0, 0);
    else {
        st(g, "r3.w", F_MAD, "r3.w", "128.0", "127.5");
        st(g, "r3.w", F_FLOORMUL, "r3.w", "0.00392156862745098", 0);
    }
    if (A == B || (!a && !b)) st(g, "r6.xyz", F_MOV, "0.0", 0, 0);
    else if (!b) st(g, "r6.xyz", F_MOV, a, 0, 0);
    else st(g, "r6.xyz", F_SUB, a ? a : "0.0", b, 0);
    st(g, "r6.xyz", F_FLOORMUL3, "r6.xyz", C == 0 ? "r4.www" : C == 1 ? "r3.www" : "u_a.yyy", "0.0078125");
    if (d) st(g, "r6.xyz", F_ADD, "r6.xyz", d, 0);
    st(g, "r4.xyz", F_CLAMP, "r6.xyz", "0.0", "255.0");
}

/* FBMSK's bits kept from the target, on r7 (the 8-bit colour and the stored alpha) */
static void fetch_mask(Gen *g, const KH1ShaderKey *k) {
    static const char *p[8] = { 0, "0.5", "0.25", "0.125", "0.0625", "0.03125", "0.015625", "0.0078125" };
    static const char *q[8] = { 0, "2.0", "4.0", "8.0", "16.0", "32.0", "64.0", "128.0" };
    static const char *r7c[3] = { "r7.x", "r7.y", "r7.z" }, *dc[3] = { "dst.x", "dst.y", "dst.z" };
    static const char *r5c[3] = { "r5.x", "r5.y", "r5.z" }, *r6c[3] = { "r6.x", "r6.y", "r6.z" };
    u32 i, hi;
    for (i = 0; i < 3; i++) {
        s32 n = mask_shape(k->fbm[i], &hi);
        const char *x = hi ? dc[i] : r7c[i], *y = hi ? r7c[i] : dc[i];
        if (!n) continue;
        if (n == 8) { st(g, r7c[i], F_MOV, dc[i], 0, 0); continue; }
        /* x's high bits and y's low k: floor(x / 2^k) x 2^k + y - floor(y / 2^k) x 2^k */
        st(g, r5c[i], F_FLOORMUL, x, p[n], 0);
        st(g, r6c[i], F_FLOORMUL, y, p[n], 0);
        st(g, r5c[i], F_SUB, r5c[i], r6c[i], 0);
        st(g, r7c[i], F_MAD, r5c[i], q[n], y);
    }
    if (k->fbm[3] == 0xFF) st(g, "r7.w", F_MOV, "dst.w", 0, 0);
}

u32 kh1_shader_frag_cg(const KH1ShaderKey *k, char *buf, u32 cap) {
    Gen g;
    s32 pa = (s32)k->pre_a - 2, pd = (s32)k->pre_d - 2;
    u32 i, hi;
    int nat = k->fetch && !k->setup; /* the frame read's declarations (below) */
    g.buf = buf;
    g.cap = cap;
    g.n = g.over = 0;
    if (cap) buf[0] = 0;
    if (k->fetch) { /* a frame read: a CT16 target, or a mask with no float form */
        if (k->fpsm == 2) return 0;
        for (i = 0; i < 3; i++)
            if (mask_shape(k->fbm[i], &hi) < 0) return 0;
        if (k->fbm[3] && k->fbm[3] != 0xFF) return 0;
    }
    if (k->fetch == 1) pa = 0, pd = 1;                                /* the shader blends itself */
    if (pa && k->csel == 1) return 0;                                 /* Cs x Ad: blend.h makes that a FETCH */
    put(&g, "// kh1-decomp fragment shader: ");
    key_str(&g, k);
    /* a frame read is the Vita's programmable blending (session 136, from SceShaccCg's own diagnostics): the
     * entry is __nativecolor, the target's pixel a __regformat FRAGCOLOR input, and the COLOR output a
     * __regformat one of the same size, so it is written as bytes (0..255), not / 255 */
    put(&g, "\n// generated by host/port/shadergen.c (docs/renderer-spec.md 4.13 \"Session 127\")\n");
    put(&g, nat ? "__nativecolor void main(\n" : "void main(\n");
    if (k->setup == 2) {} /* the clear: stencil only (its colour mask is 0) */
    else if (k->setup) put(&g, "    float4 pos : WPOS,\n    uniform sampler2D tex,\n    uniform float4 u_xf,\n");
    else {
        /* 2026-10-31: a lin draw's colour is col x w (the native vertex shader's, below), far past 1.0: a TEXCOORD,
         * as a COLOR varying is clamped to 0 .. 1 on the Vita's GPU (P0's floor and P11's Keyblade drew black) */
        put(&g, k->lin && k->tex ? "    float4 col : TEXCOORD3,\n" : "    float4 col : COLOR0,\n");
        if (k->tex) put(&g, "    float4 tc : TEXCOORD0,\n");
        if (k->fog) put(&g, "    float fog : TEXCOORD1,\n");
        if (k->tex) put(&g, "    uniform sampler2D tex,\n");
        put(&g, "    uniform float4 u_a,\n    uniform float4 u_b,\n    uniform float4 u_r,\n");
        if (k->tex && (k->su == KH1_SHADER_TAPS || k->sv == KH1_SHADER_TAPS)) put(&g, "    uniform float4 u_c,\n"); /* the region offset */
        if (nat) put(&g, "    __regformat unsigned char4 dst : FRAGCOLOR,\n"); /* the target's pixel */
    }
    put(&g, nat ? "    out __regformat unsigned char4 ocolor : COLOR)\n{\n" : "    out float4 ocolor : COLOR)\n{\n");
    regs(&g);
    if (k->setup == 2) {
        st(&g, "ocolor", F_MOV, "r0", 0, 0);
        put(&g, "}\n");
        return g.over ? 0 : g.n;
    }
    if (k->setup) { /* the target's alpha at this pixel: 1.0 (255) is the GS's bit 7 */
        st(&g, "r1.xy", F_MUL, "pos.xy", "u_xf.xy", 0);
        st(&g, "r1.xy", F_MUL, "r1.xy", "0.5", 0);
        st(&g, "r2", F_TEX, "r1.xy", 0, 0);
        st(&g, "r2.w", F_ROUND, "r2.w", "255.0", "0.5");
        st(&g, "r5.z", F_STEP, "255.0", "r2.w", 0);
        st(&g, "r5.z", F_SUB, k->datm ? "r5.z" : "0.5", k->datm ? "0.5" : "r5.z", 0);
        st(&g, 0, F_CLIP, "r5.z", 0, 0);
        st(&g, "ocolor", F_MOV, "r0", 0, 0);
        put(&g, "}\n");
        return g.over ? 0 : g.n;
    }
    if (k->lin && k->tex) { /* 2026-10-31 (drawstate.h): col x w / w, straight across the screen */
        st(&g, "r0", F_DIV, "col", "tc.wwww", 0);
        st(&g, "r0", F_ROUND, "r0", "255.0", "0.5");
    } else {
        st(&g, "r0", F_ROUND, "col", "255.0", "0.5"); /* Cv, 0x80 = 1.0 */
    }
    if (k->tex) {
        if (k->fst) st(&g, "r1.xy", F_MOV, "tc.xy", 0, 0);
        else st(&g, "r1.xy", F_DIV, "tc.xy", "tc.zz", 0);
        if (k->su == KH1_SHADER_CLAMP) st(&g, "r1.x", F_CLAMP, "r1.x", "u_r.x", "u_r.y");
        if (k->sv == KH1_SHADER_CLAMP) st(&g, "r1.y", F_CLAMP, "r1.y", "u_r.z", "u_r.w");
        /* session 137v: REGION_REPEAT, (c & MASK) | FIX, with MASK's low run of ones as a period P and FIX's bits
         * above it added: the coordinate wrapped into [0, P / n) then moved by FIX / n (kh1_shader_uniforms).  One
         * tap: exact for point sampling (the textured points' sampler); bilinear blends across the region's
         * seam where the GS would wrap each tap */
        if (k->su == KH1_SHADER_TAPS) {
            st(&g, "r5.x", F_FLOORMUL, "r1.x", "u_r.x", 0);
            st(&g, "r1.x", F_MAD, "r5.x", "u_r.y", "r1.x");
            st(&g, "r1.x", F_ADD, "r1.x", "u_c.z", 0);
        }
        if (k->sv == KH1_SHADER_TAPS) {
            st(&g, "r5.y", F_FLOORMUL, "r1.y", "u_r.z", 0);
            st(&g, "r1.y", F_MAD, "r5.y", "u_r.w", "r1.y");
            st(&g, "r1.y", F_ADD, "r1.y", "u_c.w", 0);
        }
        st(&g, "r2", F_TEX, "r1.xy", 0, 0);
        if (k->tex == KH1_TEXFMT_A1B5G5R5) { /* the GS's 5 bits shifted up 3; the STP bit */
            st(&g, "r2.xyz", F_ROUND, "r2.xyz", "31.0", "0.5");
            st(&g, "r2.xyz", F_MUL, "r2.xyz", "8.0", 0);
            st(&g, "r2.w", F_ROUND, "r2.w", "1.0", "0.5");
        } else {
            st(&g, "r2", F_ROUND, "r2", "255.0", "0.5");
        }
        if (k->texa) { /* A: TA1 with the bit (16-bit), else TA0, or 0 for black with AEM */
            st(&g, "r3.x", F_ADD, "r2.x", "r2.y", 0);
            st(&g, "r3.x", F_ADD, "r3.x", "r2.z", 0);
            st(&g, "r3.x", F_STEP, "r3.x", "0.0", 0);
            st(&g, "r3.x", F_MUL, "r3.x", "u_b.x", 0);
            st(&g, "r3.y", F_LERP, "u_a.z", "0.0", "r3.x");
            if (k->tex == KH1_TEXFMT_A1B5G5R5) st(&g, "r2.w", F_LERP, "r3.y", "u_a.w", "r2.w");
            else st(&g, "r2.w", F_MOV, "r3.y", 0, 0);
        }
        /* the texture function (texfunc.h), each result at most 0xFF */
        if ((k->tfx & 3) == KH1_TFX_DECAL) {
            st(&g, "r4.xyz", F_MOV, "r2.xyz", 0, 0);
        } else {
            st(&g, "r4.xyz", F_FLOORMUL3, "r2.xyz", "r0.xyz", "0.0078125");
            if ((k->tfx & 3) != KH1_TFX_MODULATE) st(&g, "r4.xyz", F_ADD, "r4.xyz", "r0.www", 0);
            st(&g, "r4.xyz", F_MIN, "r4.xyz", "255.0", 0);
        }
        if (!k->tcc) {
            st(&g, "r4.w", F_MOV, "r0.w", 0, 0);
        } else if ((k->tfx & 3) == KH1_TFX_MODULATE) {
            st(&g, "r4.w", F_FLOORMUL3, "r2.w", "r0.w", "0.0078125");
            st(&g, "r4.w", F_MIN, "r4.w", "255.0", 0);
        } else if ((k->tfx & 3) == KH1_TFX_HIGHLIGHT) {
            st(&g, "r4.w", F_ADD, "r2.w", "r0.w", 0);
            st(&g, "r4.w", F_MIN, "r4.w", "255.0", 0);
        } else {
            st(&g, "r4.w", F_MOV, "r2.w", 0, 0);
        }
    } else {
        st(&g, "r4", F_MOV, "r0", 0, 0);
    }
    if (k->fog) { /* (F x C + (0xFF - F) x FOGCOL) >> 8 (fog.h) */
        if (k->lin && k->tex) {
            st(&g, "r5.x", F_DIV, "fog", "tc.w", 0);
            st(&g, "r5.x", F_ROUND, "r5.x", "255.0", "0.5");
        } else {
            st(&g, "r5.x", F_ROUND, "fog", "255.0", "0.5");
        }
        st(&g, "r5.y", F_SUB, "255.0", "r5.x", 0);
        st(&g, "r6.xyz", F_MUL, "r4.xyz", "r5.xxx", 0);
        st(&g, "r6.xyz", F_MAD, "u_b.yzw", "r5.yyy", "r6.xyz");
        st(&g, "r4.xyz", F_FLOORMUL, "r6.xyz", "0.00390625", 0);
    }
    if (k->discard) { /* the alpha test on As against AREF (atest.h): r5.z 1 where it passes */
        switch (k->atst & 7) {
        case KH1_ATST_NEVER: st(&g, "r5.z", F_MOV, "0.0", 0, 0); break;
        case KH1_ATST_ALWAYS: st(&g, "r5.z", F_MOV, "1.0", 0, 0); break;
        case KH1_ATST_LESS:
            st(&g, "r5.z", F_STEP, "u_a.x", "r4.w", 0);
            st(&g, "r5.z", F_SUB, "1.0", "r5.z", 0);
            break;
        case KH1_ATST_LEQUAL: st(&g, "r5.z", F_STEP, "r4.w", "u_a.x", 0); break;
        case KH1_ATST_GEQUAL: st(&g, "r5.z", F_STEP, "u_a.x", "r4.w", 0); break;
        case KH1_ATST_GREATER:
            st(&g, "r5.z", F_STEP, "r4.w", "u_a.x", 0);
            st(&g, "r5.z", F_SUB, "1.0", "r5.z", 0);
            break;
        default: /* EQUAL, NOTEQUAL */
            st(&g, "r5.z", F_STEP, "u_a.x", "r4.w", 0);
            st(&g, "r5.w", F_STEP, "r4.w", "u_a.x", 0);
            st(&g, "r5.z", F_MUL, "r5.z", "r5.w", 0);
            if ((k->atst & 7) == KH1_ATST_NOTEQUAL) st(&g, "r5.z", F_SUB, "1.0", "r5.z", 0);
            break;
        }
        if (k->discard == KH1_DISCARD_FAIL) st(&g, "r5.z", F_SUB, "r5.z", "0.5", 0);
        else st(&g, "r5.z", F_SUB, "0.5", "r5.z", 0);
        st(&g, 0, F_CLIP, "r5.z", 0, 0);
    }
    if (k->fetch == 1) fetch_blend(&g, k);
    /* the blend's pre-scale (blend.h): pre_a x (Cs x C / 0x80, floored or ceiled) + pre_d x Cs, clamped */
    if (pa) {
        st(&g, "r6.xyz", F_MUL, "r4.xyz", k->csel == 2 ? "u_a.yyy" : "r4.www", 0);
        if (pa != 1) st(&g, "r6.xyz", F_MUL, "r6.xyz", lit(pa), 0);
        if (k->pre_floor == 1) st(&g, "r6.xyz", F_FLOORMUL, "r6.xyz", "0.0078125", 0);
        else if (k->pre_floor == 2) st(&g, "r6.xyz", F_CEILMUL, "r6.xyz", "0.0078125", 0);
        else st(&g, "r6.xyz", F_MUL, "r6.xyz", "0.0078125", 0);
        st(&g, "r6.xyz", F_MAD, "r4.xyz", lit(pd), "r6.xyz");
        if (!k->pre_floor) st(&g, "r6.xyz", F_ROUND, "r6.xyz", "1.0", "0.5");
        st(&g, "r4.xyz", F_CLAMP, "r6.xyz", "0.0", "255.0");
    } else if (pd != 1) {
        st(&g, "r4.xyz", F_MUL, "r4.xyz", lit(pd), 0);
        st(&g, "r4.xyz", F_CLAMP, "r4.xyz", "0.0", "255.0");
    }
    /* the alpha written: min(As, 0x80) on the 0x80 scale, (As x 255 + 64) / 128 (r4 keeps the GS's colour) */
    st(&g, "r7.xyz", F_MOV, "r4.xyz", 0, 0);
    st(&g, "r7.w", F_ROUND, "r4.w", "1.9921875", "0.5");
    st(&g, "r7.w", F_MIN, "r7.w", "255.0", 0);
    if (k->fetch) fetch_mask(&g, k);
    if (nat) st(&g, "ocolor", F_MOV, "r7", 0, 0);
    else st(&g, "ocolor", F_DIV, "r7", "255.0", 0);
    put(&g, "}\n");
    return g.over ? 0 : g.n;
}

u32 kh1_shader_vert_cg(u32 index, char *buf, u32 cap) {
    Gen g;
    u32 nat = index >= KH1_VERT_NAT, skin = index >= KH1_VERT_SKIN, tex, fog;
    g.buf = buf;
    g.cap = cap;
    g.n = g.over = 0;
    if (cap) buf[0] = 0;
    if (index >= KH1_VERT_VARIANTS) return 0;
    put(&g, "// kh1-decomp vertex shader: ");
    put(&g, kh1_vertkey_str(index));
    if (skin) index -= KH1_VERT_SKIN;
    else if (nat) index -= KH1_VERT_NAT;
    tex = index >= 5 ? KH1_VTX_STQ : index >= 3 ? KH1_VTX_UV : KH1_VTX_NONE;
    fog = index && !(index & 1) ? 1 : 0;
    put(&g, "\n// generated by host/port/shadergen.c (docs/renderer-spec.md 4.13 \"Session 127\")\nvoid main(\n");
    put(&g, skin ? "    float4 pos : POSITION,\n" : "    float3 pos : POSITION,\n");
    if (index) put(&g, "    float4 col : COLOR0,\n");
    if (tex) put(&g, tex == KH1_VTX_STQ ? "    float3 tc : TEXCOORD0,\n" : "    float2 tc : TEXCOORD0,\n"); /* vertex.h kh1_vertex_attrs */
    if (fog) put(&g, "    float fog : TEXCOORD1,\n");
    if (nat) put(&g, "    float mi : TEXCOORD2,\n");
    if (skin) put(&g, "    float mi2 : TEXCOORD4,\n    float4 pos2 : TEXCOORD5,\n");
    if (nat) put(&g, "    uniform float4 u_m[128],\n    out float4 opos : POSITION");
    else put(&g, "    uniform float4 u_xf,\n    out float4 opos : POSITION");
    /* 2026-10-31: a native textured variant's colour is col x w (with mi's bit 7), and its fragment shader is always
     * lin (cmdbuf.c kh1_cmd_native): a TEXCOORD, never clamped; the lin fragment shader's col matches it */
    if (index) put(&g, nat && tex ? ",\n    out float4 ocol : TEXCOORD3" : ",\n    out float4 ocol : COLOR0");
    if (tex) put(&g, ",\n    out float4 otc : TEXCOORD0");
    if (fog) put(&g, ",\n    out float ofog : TEXCOORD1");
    put(&g, ")\n{\n");
    if (nat) {
        /* natdraw.h: clip = F x (pos, 1), F the 4 rows at u_m[4 mi]; z clamped to 0 .. w (the GS clamps Z) but with
         * mi's bit 7 */
        regs(&g);
        if (skin) st(&g, "r0", F_MOV, "pos", 0, 0);
        else {
            st(&g, "r0.xyz", F_MOV, "pos.xyz", 0, 0);
            st(&g, "r0.w", F_MOV, "1.0", 0, 0);
        }
        st(&g, "r1.x", F_ROUND, "mi", "255.0", "0.5");
        /* 2026-10-31: mi's bit 7 (natdraw.h, P0's vertices) leaves z as it is, for the GPU to clip at 0 and w as
         * the VU's own clipper would at its near and far planes */
        st(&g, "r3.y", F_STEP, "128.0", "r1.x", 0);
        st(&g, "r1.x", F_MAD, "r3.y", "-128.0", "r1.x");
        st(&g, "r1.x", F_MUL, "r1.x", "4.0", 0);
        st(&g, "r1.y", F_ADD, "r1.x", "1.0", 0);
        st(&g, "r1.z", F_ADD, "r1.x", "2.0", 0);
        st(&g, "r1.w", F_ADD, "r1.x", "3.0", 0);
        st(&g, "r2.x", F_DOTM, "r1.x", "r0", 0);
        st(&g, "r2.y", F_DOTM, "r1.y", "r0", 0);
        st(&g, "r2.z", F_DOTM, "r1.z", "r0", 0);
        st(&g, "r2.w", F_DOTM, "r1.w", "r0", 0);
        if (skin) { /* 2026-11-01 (natdraw.h "GPU skinning"): the second bone's matrix times its pre-weighted position,
                     * added: the sum P13 forms before its divide (0 for a one-bone vertex: pos2 is 0) */
            st(&g, "r4.x", F_ROUND, "mi2", "255.0", "0.5");
            st(&g, "r4.x", F_MUL, "r4.x", "4.0", 0);
            st(&g, "r4.y", F_ADD, "r4.x", "1.0", 0);
            st(&g, "r4.z", F_ADD, "r4.x", "2.0", 0);
            st(&g, "r4.w", F_ADD, "r4.x", "3.0", 0);
            st(&g, "r5.x", F_DOTM, "r4.x", "pos2", 0);
            st(&g, "r5.y", F_DOTM, "r4.y", "pos2", 0);
            st(&g, "r5.z", F_DOTM, "r4.z", "pos2", 0);
            st(&g, "r5.w", F_DOTM, "r4.w", "pos2", 0);
            st(&g, "r2", F_ADD, "r2", "r5", 0);
        }
        st(&g, "opos.xy", F_MOV, "r2.xy", 0, 0);
        st(&g, "r3.x", F_CLAMP, "r2.z", "0.0", "r2.w");
        st(&g, "r3.z", F_SUB, "r2.z", "r3.x", 0);
        st(&g, "opos.z", F_MAD, "r3.y", "r3.z", "r3.x");
        st(&g, "opos.w", F_MOV, "r2.w", 0, 0);
    } else {
        /* target pixels to clip space (vertex.h): x x 2 / w - 1, y x 2 / h - 1, w 1 */
        st(&g, "opos.xy", F_MAD, "pos.xy", "u_xf.xy", "u_xf.zw");
        st(&g, "opos.z", F_MOV, "pos.z", 0, 0);
        st(&g, "opos.w", F_MOV, "1.0", 0, 0);
    }
    if (nat && tex) { /* 2026-10-31: with mi's bit 7, colour and fog times w and w in otc.w (the fragment's lin
                       * divides them back); else times 1 and 1 */
        st(&g, "r3.w", F_SUB, "r2.w", "1.0", 0);
        st(&g, "r3.w", F_MAD, "r3.y", "r3.w", "1.0");
        if (index) st(&g, "ocol", F_MUL, "col", "r3.wwww", 0);
        st(&g, "otc.xy", F_MOV, "tc.xy", 0, 0);
        st(&g, "otc.z", F_MOV, tex == KH1_VTX_STQ ? "tc.z" : "1.0", 0, 0);
        st(&g, "otc.w", F_MOV, "r3.w", 0, 0);
        if (fog) st(&g, "ofog", F_MUL, "fog", "r3.w", 0);
    } else {
        if (index) st(&g, "ocol", F_MOV, "col", 0, 0);
        if (tex) {
            st(&g, "otc.xy", F_MOV, "tc.xy", 0, 0);
            st(&g, "otc.z", F_MOV, tex == KH1_VTX_STQ ? "tc.z" : "1.0", 0, 0);
            st(&g, "otc.w", F_MOV, "1.0", 0, 0);
        }
        if (fog) st(&g, "ofog", F_MOV, "fog", 0, 0);
    }
    put(&g, "}\n");
    return g.over ? 0 : g.n;
}

/* session 137v: a REGION_REPEAT axis's (n / P, -P / n) and FIX / n: P is 2 to the run of ones at MASK's bottom (the
 * period), FIX's bits under P are dropped (the rare mask with a hole in it reads as its low run) */
static void taps(const KH1SamplerAxis *a, f32 *pq, f32 *fix) {
    u32 p = 1;
    if (a->shader != KH1_SHADER_TAPS || !a->n) return;
    while (p < a->n && a->lo & p) p <<= 1;
    pq[0] = (f32)a->n / (f32)p;
    pq[1] = -(f32)p / (f32)a->n;
    *fix = (f32)(a->hi & (a->n - 1) & ~(p - 1)) / (f32)a->n;
}

void kh1_shader_uniforms(const KH1DrawState *d, f32 o[16]) {
    const KH1SamplerAxis *u = &d->sampler.u, *v = &d->sampler.v;
    memset(o, 0, 16 * sizeof *o);
    o[0] = (f32)d->u.aref;
    o[1] = (f32)d->u.fix;
    o[2] = (f32)d->u.ta0;
    o[3] = (f32)d->u.ta1;
    o[4] = (f32)d->u.aem;
    o[5] = (f32)(d->u.fogcol & 0xFF);
    o[6] = (f32)(d->u.fogcol >> 8 & 0xFF);
    o[7] = (f32)(d->u.fogcol >> 16 & 0xFF);
    o[8] = u->shader == KH1_SHADER_CLAMP && u->n ? (u->lo + 0.5f) / u->n : 0.0f; /* exact: n is a power of 2 */
    o[9] = u->shader == KH1_SHADER_CLAMP && u->n ? (u->hi + 0.5f) / u->n : 1.0f;
    o[10] = v->shader == KH1_SHADER_CLAMP && v->n ? (v->lo + 0.5f) / v->n : 0.0f;
    o[11] = v->shader == KH1_SHADER_CLAMP && v->n ? (v->hi + 0.5f) / v->n : 1.0f;
    o[12] = (f32)d->u.abcd;
    o[13] = (f32)d->u.psm;
    taps(u, &o[8], &o[14]);
    taps(v, &o[10], &o[15]);
}

/* ---- the interpreter ---- */
typedef struct {
    f32 c[4];
    u32 n;
} Val;

static f32 flo(f32 x) {
    s32 i = (s32)x;
    return (f32)(x < (f32)i ? i - 1 : i);
}

static int is_tok(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '-';
}

/* a decimal literal ("255.0", "-0.5", "0.0078125"): exact for the generator's (a short decimal of a dyadic) */
static int literal(const char *s, u32 n, f32 *out) {
    u32 i = 0;
    int neg = 0;
    double v = 0.0, scale = 1.0;
    int dot = 0;
    if (i < n && s[i] == '-') { neg = 1; i++; }
    if (i == n) return 0;
    for (; i < n; i++) {
        if (s[i] == '.') { if (dot) return 0; dot = 1; continue; }
        if (s[i] < '0' || s[i] > '9') return 0;
        if (dot) { scale /= 10.0; v += (s[i] - '0') * scale; }
        else v = v * 10.0 + (s[i] - '0');
    }
    *out = (f32)(neg ? -v : v);
    return 1;
}

/* a variable's index and its swizzle (component indices, count) */
static int var(const char *s, u32 n, u32 *idx, u32 sw[4], u32 *nsw) {
    u32 i, l, j;
    for (l = 0; l < n && s[l] != '.'; l++) ;
    for (i = 0; i < KH1_SV_COUNT; i++) {
        const char *m = names[i];
        for (j = 0; j < l && m[j] && m[j] == s[j]; j++) ;
        if (j == l && !m[l]) break;
    }
    if (i == KH1_SV_COUNT) return 0;
    *idx = i;
    if (l == n) {
        *nsw = scalar_var(i) ? 1 : 4;
        for (j = 0; j < 4; j++) sw[j] = j;
        return 1;
    }
    if (n - l - 1 < 1 || n - l - 1 > 4) return 0;
    *nsw = n - l - 1;
    for (j = 0; j < *nsw; j++) {
        char c = s[l + 1 + j];
        sw[j] = c == 'x' ? 0 : c == 'y' ? 1 : c == 'z' ? 2 : c == 'w' ? 3 : 4;
        if (sw[j] > 3 || (scalar_var(i) && sw[j])) return 0;
    }
    return 1;
}

static int operand(const KH1ShaderRun *r, const char *s, u32 n, Val *v) {
    u32 idx, sw[4], ns, j;
    if (literal(s, n, &v->c[0])) {
        v->n = 1;
        return 1;
    }
    if (!var(s, n, &idx, sw, &ns)) return 0;
    v->n = ns;
    for (j = 0; j < ns; j++) v->c[j] = r->v[idx][sw[j]];
    return 1;
}

/* the components of a result from operands of sizes a and b: a scalar widens, other sizes must agree */
static int width(u32 a, u32 b, u32 *w) {
    if (a == 1 || a == b) { *w = b; return 1; }
    if (b == 1) { *w = a; return 1; }
    return 0;
}
static f32 at(const Val *v, u32 i) { return v->c[v->n == 1 ? 0 : i]; }

/* matches text s (n chars, no trailing ';') against form f; the operands into o */
static int match(const KH1ShaderRun *r, const char *s, u32 n, u32 f, Val *o, u32 *no) {
    const char *p = forms[f];
    u32 i = 0;
    *no = 0;
    for (; *p; p++) {
        if (*p == '%') {
            u32 t = i;
            while (i < n && is_tok(s[i])) i++;
            if (i == t || *no == 3 || !operand(r, s + t, i - t, &o[*no])) return 0;
            (*no)++;
            continue;
        }
        if (i == n || s[i] != *p) return 0;
        i++;
    }
    return i == n;
}

static int eval(KH1ShaderRun *r, u32 f, const Val *o, Val *out) {
    u32 i, w = o[0].n;
    if (f == F_DOTM) { /* (int) truncates, as Cg's cast does */
        s32 row = (s32)o[0].c[0];
        if (o[0].n != 1 || o[1].n != 4 || !r->um || row < 0 || (u32)row >= r->um_rows) return 0;
        out->c[0] = r->um[row * 4] * o[1].c[0] + r->um[row * 4 + 1] * o[1].c[1] + r->um[row * 4 + 2] * o[1].c[2] +
                    r->um[row * 4 + 3] * o[1].c[3];
        out->n = 1;
        return 1;
    }
    if (f == F_TEX) {
        if (o[0].n < 2 || !r->tex) return 0;
        r->tex(r->ctx, o[0].c[0], o[0].c[1], out->c);
        out->n = 4;
        return 1;
    }
    if (f != F_MOV && f != F_CLIP && !width(w, o[1].n, &w)) return 0;
    if ((f == F_MAD || f == F_FLOORMUL3 || f == F_ROUND || f == F_CLAMP || f == F_LERP) && !width(w, o[2].n, &w))
        return 0;
    out->n = w;
    for (i = 0; i < w; i++) {
        f32 a = at(&o[0], i), b = f == F_MOV || f == F_CLIP ? 0.0f : at(&o[1], i), c, v;
        c = f == F_MAD || f == F_FLOORMUL3 || f == F_ROUND || f == F_CLAMP || f == F_LERP ? at(&o[2], i) : 0.0f;
        switch (f) {
        case F_MOV: case F_CLIP: v = a; break;
        case F_ADD: v = a + b; break;
        case F_SUB: v = a - b; break;
        case F_MUL: v = a * b; break;
        case F_MAD: v = a * b + c; break;
        case F_DIV: v = a / b; break;
        case F_FLOORMUL: v = flo(a * b); break;
        case F_FLOORMUL3: v = flo(a * b * c); break;
        case F_CEILMUL: v = -flo(-(a * b)); break;
        case F_ROUND: v = flo(a * b + c); break;
        case F_MIN: v = a < b ? a : b; break;
        case F_CLAMP: v = a < b ? b : a > c ? c : a; break;
        case F_STEP: v = b >= a ? 1.0f : 0.0f; break;
        default: v = a + (b - a) * c; break; /* F_LERP */
        }
        out->c[i] = v;
    }
    return 1;
}

static int line(KH1ShaderRun *r, const char *s, u32 n) {
    Val o[3], v;
    u32 f, no, e, idx, sw[4], ns, j;
    while (n && (s[n - 1] == ' ' || s[n - 1] == '\r')) n--;
    if (!n || s[n - 1] != ';') return 0;
    n--;
    if (n >= 5 && s[0] == 'c' && s[1] == 'l' && s[2] == 'i' && s[3] == 'p' && s[4] == '(') {
        if (!match(r, s, n, F_CLIP, o, &no) || !eval(r, F_CLIP, o, &v)) return 0;
        form_uses[F_CLIP]++;
        for (j = 0; j < v.n; j++)
            if (v.c[j] < 0.0f) r->discarded = 1;
        return 1;
    }
    for (e = 0; e + 2 < n && !(s[e] == ' ' && s[e + 1] == '=' && s[e + 2] == ' '); e++) ;
    if (e + 2 >= n || !var(s, e, &idx, sw, &ns) || idx < KH1_SV_R0) return 0; /* only registers and outputs are written */
    for (f = 0; f < F_CLIP; f++)
        if (match(r, s + e + 3, n - e - 3, f, o, &no)) break;
    if (f == F_CLIP || !eval(r, f, o, &v) || (v.n != 1 && v.n != ns)) return 0;
    form_uses[f]++;
    for (j = 0; j < ns; j++) r->v[idx][sw[j]] = v.c[v.n == 1 ? 0 : j];
    return 1;
}

void kh1_shader_run(const char *text, KH1ShaderRun *r) {
    const char *p = text;
    u32 no = 0, i;
    int body = 0, nat = 0;
    r->discarded = 0;
    r->lines = r->bad = r->bad_line = 0;
    memset(r->v[KH1_SV_R0], 0, 8 * sizeof r->v[0]); /* the registers' declarations: float4(0.0, ...) */
    while (*p) {
        const char *e = p, *s;
        while (*e && *e != '\n') e++;
        no++;
        for (s = p; s < e && *s == ' '; s++) ;
        if (!body && e - s > 14) { /* the frame read's entry: "__nativecolor void main(" */
            const char *m = "__nativecolor ";
            for (i = 0; m[i] && s[i] == m[i]; i++) ;
            if (!m[i]) nat = 1;
        }
        if (s < e && *s == '{') body = 1;
        else if (s < e && *s == '}') body = 0;
        else if (body && s < e && !(s + 1 < e && s[0] == '/' && s[1] == '/') &&
                 !(e - s > 7 && s[0] == 'f' && s[1] == 'l' && s[2] == 'o' && s[3] == 'a' && s[4] == 't' && s[5] == '4' && s[6] == ' ')) {
            if (line(r, s, (u32)(e - s))) r->lines++;
            else if (!r->bad++) r->bad_line = no;
        }
        p = *e ? e + 1 : e;
    }
    if (nat) /* a __regformat output holds the bytes: the run gives every shader's output on the 0..1 scale */
        for (i = 0; i < 4; i++) r->v[KH1_SV_OCOLOR][i] /= 255.0f;
}
