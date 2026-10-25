/* The primitive assembly a port's GIF parser runs: the GS's vertex queue as GPU points, lines and
 * triangles (include/platform/primasm.h, docs/renderer-spec.md 4.13 "Session 122"), checked by
 * tests/host/primasm_test.c against host/null/gsregs.c's queue and gsmem.c's sprites.  Not part of
 * the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/primasm.h"

/* POINT 1, LINE / LINESTRIP 2, TRIANGLE / TRISTRIP / TRIFAN 3, SPRITE 2, 7 none (gsregs.c's) */
static const u8 verts[8] = { 1, 2, 2, 3, 3, 3, 2, 0 };

u32 kh1_pa_class(u32 prim) {
    static const u8 cls[8] = { KH1_PA_POINTS, KH1_PA_LINES, KH1_PA_LINES, KH1_PA_TRIANGLES, KH1_PA_TRIANGLES,
                               KH1_PA_TRIANGLES, KH1_PA_TRIANGLES, KH1_PA_NONE };
    return cls[prim & 7];
}

void kh1_pa_prim(KH1PrimAsm *a, u32 prim) {
    a->prim = prim;
    a->n = 0;
}

void kh1_pa_attr(KH1PrimAsm *a, u32 prim) { a->prim = prim; }

u32 kh1_pa_vertex(KH1PrimAsm *a, const KH1PaVert *v, int draw, KH1PaVert out[6]) {
    u32 type = a->prim & 7, need = verts[type], i, n;
    if (!need) return 0;
    if (a->n < need) {
        a->q[a->n++] = *v;
    } else { /* a strip's next vertex: the oldest leaves; the fan keeps its first */
        for (i = type == 5 ? 2 : 1; i < need; i++) a->q[i - 1] = a->q[i];
        a->q[need - 1] = *v;
    }
    if (a->n < need) return 0;
    n = 0;
    if (draw) {
        if (type == 6) { /* SPRITE: corners (x0 y0) (x1 y0) (x0 y1) (x1 y1) as two triangles */
            static const u8 cx[6] = { 0, 1, 0, 0, 1, 1 }, cy[6] = { 0, 0, 1, 1, 0, 1 };
            const KH1PaVert *v0 = &a->q[0], *v1 = &a->q[1];
            for (i = 0; i < 6; i++) {
                const KH1PaVert *px = cx[i] ? v1 : v0, *py = cy[i] ? v1 : v0;
                out[i] = *v1; /* RGBA, Z, F, Q */
                out[i].xy = (px->xy & 0xFFFF) | (py->xy & 0xFFFF0000u);
                out[i].uv = (px->uv & 0xFFFF) | (py->uv & 0xFFFF0000u);
                out[i].s = px->s;
                out[i].t = py->t;
            }
            n = 6;
        } else {
            for (i = 0; i < need; i++) out[i] = a->q[i];
            if (!(a->prim >> 3 & 1)) /* IIP 0: the colour of the vertex that drew */
                for (i = 0; i + 1 < need; i++) out[i].rgba = a->q[need - 1].rgba;
            n = need;
        }
    }
    if (type == 0 || type == 1 || type == 3 || type == 6) a->n = 0; /* the lists start again */
    return n;
}
