/* The native renderer's VU1 side (include/platform/natdraw.h, docs/native-renderer.md; vu1_draw.h: included by vu1.c
 * after vu1_nat.h).  With kh1_vu1_draw set, a run of P18 from 007 is not run: its record stream is read as the program
 * reads it and handed over as natdraw.h's payload (the matrices it loads, its strips' untransformed vertices with the
 * matrix each one picks), for the GPU to transform.  What the run leaves in VU1 is only what a later run can read
 * there that the stream decides: the slot matrices (vf05-08, vf12-15, vf19-22) as the last loads left them, and the
 * program's end (tpc 007).  The kick's output area, vf26-31, ACC, Q and the integer registers are not written: no
 * program of the Dive reads them before writing them (P18 itself starts each strip's ADC from its third vertex), and
 * kh1_vu1_draw unset (the default) runs the program as before. */
#include "platform/natdraw.h"
void (*kh1_vu1_draw)(const u32 *q, u32 nqw);
u32 kh1_vu1_drawn; /* runs handed over so far */
int kh1_vu1_draw_p0 = 1;
int kh1_vu1_draw_p11 = 1;
int kh1_vu1_draw_p10 = 1;

#define ND_QW 4096 /* a payload's qwords: VU1's data memory is 1024, a vertex 3 there and 2 here */
static u32 nd_buf[ND_QW][4];
static u32 nd_mat[KH1_NAT_MATS][4][4];

/* P18 from 007 (vu1_nat.h nat_18 is the arithmetic this replaces): 1 when handed over, 0 to run it.  2026-10-31: P11
 * too (num 11): P18's stream and output, with a near-plane cull (w < 1) and the guard band, which the GPU's own
 * clipping replaces (pipes.c draws it with z not clamped) */
static int nd_18(u32 pc, u32 num) {
    u32 i2 = top, rq = 2, nrec = 0, nmat = 0, k;
    s32 cur[3] = { -1, -1, -1 }, last[3] = { -1, -1, -1 }; /* each slot's matrix in this payload; the last one loaded */
    static const int base[3] = { 5, 12, 19 };
    if (pc != 7) return 0;
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        u32 op = h[0] & 0xFFFF, nv, j, par;
        if (!op) { /* a matrix into slot z (0, 1, else 2): the slot's vertices that follow use it */
            u32 sl = (h[2] & 0xFFFF) == 0 ? 0 : (h[2] & 0xFFFF) == 1 ? 1 : 2;
            if (nmat == KH1_NAT_MATS) return 0;
            for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], mem[(i2 + 1 + k) & (DATA_QW - 1)], 16);
            cur[sl] = last[sl] = (s32)nmat++;
            i2 += 8;
            continue;
        }
        if (op != 1) break;
        nv = h[2] & 0xFFFF;
        par = h[3] & 0xFFFF;
        if (!nv) nv = 0x10000; /* z counts down to 0 after the first: 0 is 65536, which no stream has */
        if (rq + 1 + nv * 2 + 2 > ND_QW - KH1_NAT_MATS * 4) return 0;
        nd_buf[rq][0] = mem[(i2 + 1) & (DATA_QW - 1)][0]; /* the GIF tag's low words */
        nd_buf[rq][1] = mem[(i2 + 1) & (DATA_QW - 1)][1];
        nd_buf[rq][2] = nv;
        nd_buf[rq][3] = par;
        rq++;
        i2 += 2;
        for (j = 0; j < nv; j++, i2 += 3) {
            const u32 *n = mem[i2 & (DATA_QW - 1)], *p = mem[(i2 + 1) & (DATA_QW - 1)], *t = mem[(i2 + 2) & (DATA_QW - 1)];
            u32 sl = (n[3] & 0xFFFF) == 0 ? 0 : (n[3] & 0xFFFF) == 1 ? 1 : 2;
            if (p[3] != 0x3F800000u) return 0; /* w is 1 in every stream seen: else the program's own way */
            if (cur[sl] < 0) { /* the slot's matrix as the registers hold it now */
                if (nmat == KH1_NAT_MATS) return 0;
                for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], vf[base[sl] + k], 16);
                cur[sl] = (s32)nmat++;
            }
            nd_buf[rq][0] = p[0];
            nd_buf[rq][1] = p[1];
            nd_buf[rq][2] = p[2];
            nd_buf[rq][3] = (u32)cur[sl];
            nd_buf[rq + 1][0] = t[0];
            nd_buf[rq + 1][1] = t[1];
            nd_buf[rq + 1][2] = t[2];
            nd_buf[rq + 1][3] = 0;
            rq += 2;
        }
        nrec++;
    }
    if (!kh1_vu1_draw) return 0;
    nd_buf[0][0] = KH1_NAT_MAGIC | num;
    nd_buf[0][1] = nrec;
    nd_buf[0][2] = nmat;
    nd_buf[0][3] = rq - 2;
    nd_buf[1][0] = (vf[1][0] & 0xFF) | (vf[1][1] & 0xFF) << 8 | (vf[1][2] & 0xFF) << 16 | (vf[1][3] & 0xFF) << 24;
    nd_buf[1][1] = vi[12] >> 4 & 0xFF;
    nd_buf[1][2] = vi[12] >> 15 & 1;
    nd_buf[1][3] = vi[13] >> 15 & 1;
    memcpy(nd_buf[rq], nd_mat, nmat * 64);
    if (nrec) kh1_vu1_draw(nd_buf[0], rq + nmat * 4);
    for (k = 0; k < 3; k++) /* the slots as the program's loads leave them */
        if (last[k] >= 0) memcpy(vf[base[k]], nd_mat[last[k]], 64);
    kh1_vu1_drawn++;
    tpc = 7 & (MICRO_N - 1);
    return 1;
}

/* 2026-10-31: P10 from 006 (vu1_nat.h nat_10), the shadow pass's untextured strips: matrix records of 4 qwords, op 1
 * a GIF tag and z positions of one qword (w the slot; the position's own w is not read, as the shader's 1), XYZ2
 * only and no ADC.  Handed over in P18's payload as program 10: the colour is the RGBAQ P10's set-up run (from 000,
 * which the program still runs) kicks from qw1, kept by nd_10_setup; every triangle drawn, ST 0 (the tag's PRIM has
 * no TME).  Fewer than 3 positions (the program's count wraps) is left to the program */
static u32 nd10_rgba = 0x80808080u;
static void nd_10_setup(void) {
    nd10_rgba = (mem[1][0] & 0xFF) | (mem[1][1] & 0xFF) << 8 | (mem[1][2] & 0xFF) << 16 | (mem[1][3] & 0xFF) << 24;
}
static int nd_10(u32 pc) {
    u32 i2 = top, rq = 2, nrec = 0, nmat = 0, k;
    s32 cur[3] = { -1, -1, -1 }, last[3] = { -1, -1, -1 };
    static const int base[3] = { 5, 12, 19 };
    if (pc != 6 || !kh1_vu1_draw) return 0;
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        u32 op = h[0] & 0xFFFF, nv, j;
        if (!op) {
            u32 sl = (h[2] & 0xFFFF) == 0 ? 0 : (h[2] & 0xFFFF) == 1 ? 1 : 2;
            if (nmat == KH1_NAT_MATS) return 0;
            for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], mem[(i2 + 1 + k) & (DATA_QW - 1)], 16);
            cur[sl] = last[sl] = (s32)nmat++;
            i2 += 5;
            continue;
        }
        if (op != 1) break;
        nv = h[2] & 0xFFFF;
        if (nv < 3) return 0;
        if (rq + 1 + nv * 2 + 2 > ND_QW - KH1_NAT_MATS * 4) return 0;
        nd_buf[rq][0] = mem[(i2 + 1) & (DATA_QW - 1)][0];
        nd_buf[rq][1] = mem[(i2 + 1) & (DATA_QW - 1)][1];
        nd_buf[rq][2] = nv;
        nd_buf[rq][3] = 0;
        rq++;
        i2 += 2;
        for (j = 0; j < nv; j++, i2++) {
            const u32 *p = mem[i2 & (DATA_QW - 1)];
            u32 sl = (p[3] & 0xFFFF) == 0 ? 0 : (p[3] & 0xFFFF) == 1 ? 1 : 2;
            if (cur[sl] < 0) {
                if (nmat == KH1_NAT_MATS) return 0;
                for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], vf[base[sl] + k], 16);
                cur[sl] = (s32)nmat++;
            }
            nd_buf[rq][0] = p[0];
            nd_buf[rq][1] = p[1];
            nd_buf[rq][2] = p[2];
            nd_buf[rq][3] = (u32)cur[sl];
            nd_buf[rq + 1][0] = nd_buf[rq + 1][1] = nd_buf[rq + 1][3] = 0;
            nd_buf[rq + 1][2] = 0x3F800000u;
            rq += 2;
        }
        nrec++;
    }
    nd_buf[0][0] = KH1_NAT_MAGIC | 10;
    nd_buf[0][1] = nrec;
    nd_buf[0][2] = nmat;
    nd_buf[0][3] = rq - 2;
    nd_buf[1][0] = nd10_rgba;
    nd_buf[1][1] = 0;
    nd_buf[1][2] = 0;
    nd_buf[1][3] = 0;
    memcpy(nd_buf[rq], nd_mat, nmat * 64);
    if (nrec) kh1_vu1_draw(nd_buf[0], rq + nmat * 4);
    for (k = 0; k < 3; k++)
        if (last[k] >= 0) memcpy(vf[base[k]], nd_mat[last[k]], 64);
    kh1_vu1_drawn++;
    tpc = 6 & (MICRO_N - 1);
    return 1;
}

/* 2026-10-31 (docs/native-renderer.md stage 3): P0 from 00c (or 04e, its idle PC: the same batch), renderer A's map
 * strips (vu1_nat.h nat_0 is what this replaces).  One batch: the GIF tag at TOPS (NLOOP the vertex count n, PRE
 * PRIM the strip's), then n vertices of 3 qwords: the position with the strip flag in w, RGBA as integers, ST in
 * 20.12.  The program's matrices are folded into one, the screen matrix (vf01-04) times the clip one (vf13-16,
 * made by its MSCAL 0 set-up), so the GPU computes the same x / w, y / w, z / w the VU does after its divide.  Per
 * vertex the payload carries what the VU's arithmetic would not change: the position and the flag word, and
 * (precomputed here, a few operations) ST as floats and the colour scaled by vf31 as FTOI0 truncates it.  What
 * the run leaves: the clipped fans' template PRIM (qw48.y, from the tag's w) and the idle PC; not the kick's
 * output, the registers, Q, clip or MAC flags (nothing in the Dive reads them before the next run writes them).
 * The program's own clipper (a triangle crossing the guard box) is the GPU's clipping here: natdraw.h's notes */
static int nd0_built, nd0_p4; /* the last nd_0 call filled nd_buf, and for P4 (KH1_HOST_NATCHECK's) */
/* 2026-10-31: p4 1 for P4 (vu1_nat.h nat_4: entered at 00c or its idle 045), P0's batch with no back-face test:
 * every flag word that draws goes to the double-sided list (bit 0x20 cleared, natdraw.h) */
static int nd_0(u32 pc, int p4) {
    const u32 *h = mem[top & (DATA_QW - 1)];
    u32 nv = h[0] & 0x7FFF, rq = 2, j, k, i2 = top + 1;
    f32 sc[4], m[4][4];
    nd0_built = 0;
    nd0_p4 = p4;
    if (pc != 0xc && pc != (p4 ? 0x45u : 0x4eu)) return 0;
    if (!nv || 3 + nv * 2 + 4 > ND_QW || nv * 7u + 8 > DATA_QW) return 0;
    for (k = 0; k < 4; k++) sc[k] = fin(vf[31][k]);
    for (k = 0; k < 4; k++) { /* column k of P x W: P (vf01-04) applied to W's column k (vf13-16) */
        f32 w0 = fin(vf[13 + k][0]), w1 = fin(vf[13 + k][1]), w2 = fin(vf[13 + k][2]), w3 = fin(vf[13 + k][3]);
        u32 r;
        for (r = 0; r < 4; r++)
            m[k][r] = fin(vf[1][r]) * w0 + fin(vf[2][r]) * w1 + fin(vf[3][r]) * w2 + fin(vf[4][r]) * w3;
    }
    nd_buf[rq][0] = h[0];
    nd_buf[rq][1] = h[1];
    nd_buf[rq][2] = nv;
    nd_buf[rq][3] = 0;
    rq++;
    for (j = 0; j < nv; j++, i2 += 3) {
        const u32 *p = mem[i2 & (DATA_QW - 1)], *c = mem[(i2 + 1) & (DATA_QW - 1)], *t = mem[(i2 + 2) & (DATA_QW - 1)];
        u32 rgba = 0;
        for (k = 0; k < 4; k++) { /* ITOF0, x vf31, FTOI0 (toward 0, saturating), the low byte as the GS takes it */
            f32 v = (f32)(s32)c[k] * sc[k];
            s32 iv = v >= 2147483520.0f ? 0x7FFFFFFF : v <= -2147483648.0f ? (s32)0x80000000u : (s32)v;
            rgba |= ((u32)iv & 0xFF) << (k * 8);
        }
        nd_buf[rq][0] = p[0];
        nd_buf[rq][1] = p[1];
        nd_buf[rq][2] = p[2];
        nd_buf[rq][3] = p4 && p[3] & 0xFFFF ? (p[3] & ~0x20u) | 1 : p[3]; /* the strip flag word (natdraw.h) */
        nd_buf[rq + 1][0] = fo((f32)(s32)t[0] * (1.0f / 4096.0f));
        nd_buf[rq + 1][1] = fo((f32)(s32)t[1] * (1.0f / 4096.0f));
        nd_buf[rq + 1][2] = 0x3F800000u;
        nd_buf[rq + 1][3] = rgba;
        rq += 2;
    }
    nd_buf[1][0] = (u32)(s32)fin(i_reg) & 0xFF; /* F: the I register (MULI.w, FTOI4, the GS's F) */
    nd0_built = 1;
    if (!kh1_vu1_draw) return 0;
    nd_buf[0][0] = KH1_NAT_MAGIC | 0;
    nd_buf[0][1] = 1;
    nd_buf[0][2] = 1;
    nd_buf[0][3] = rq - 2;
    nd_buf[1][1] = nd_buf[1][2] = nd_buf[1][3] = 0;
    for (k = 0; k < 4; k++) memcpy(nd_buf[rq + k], m[k], 16);
    kh1_vu1_draw(nd_buf[0], rq + 4);
    if (!p4) mem[48][1] = h[3]; /* P4 leaves the template as it is */
    kh1_vu1_drawn++;
    tpc = (p4 ? 0x45 : 0x4e) & (MICRO_N - 1);
    return 1;
}

/* 2026-10-31: KH1_HOST_NATCHECK=1 (host/null/main.c): P0 runs as the program, and each run's strip is compared with
 * what nd_0's payload would draw: the program's output (the kick's XYZF2, ADC and the 12.4 position) against
 * kh1_nat_tris0's rule on the same positions.  "the program only" must stay 0; "native only" are the triangles
 * the program drops or clips for the guard box (the GPU clips those itself) */
int kh1_vu1_natcheck;
static u32 nc_runs, nc_both, nc_none, nc_vu, nc_nat, nc_zero, nc_p4, nc_p4vu;
static void nd_0_check(void) {
    const u32 *h = mem[top & (DATA_QW - 1)];
    u32 nv = h[0] & 0x7FFF, o = top + 1 + 4 * nv + 1, j; /* the output: its tag at top + 1 + 4n (nat_0 i2) */
    if (!nd0_built) return;
    for (j = 2; j < nv; j++) {
        const u32 *a = mem[(o + 3 * (j - 2) + 2) & (DATA_QW - 1)], *b = mem[(o + 3 * (j - 1) + 2) & (DATA_QW - 1)];
        const u32 *c = mem[(o + 3 * j + 2) & (DATA_QW - 1)];
        u32 fl = nd_buf[3 + 2 * j][3]; /* the payload's (P4's with 0x20 cleared) */
        int vu = !(c[3] & 0x8000), nat = (fl & 0xFFFF) != 0;
        long long cr = (long long)((s32)b[0] - (s32)a[0]) * ((s32)c[1] - (s32)a[1]) -
                       (long long)((s32)b[1] - (s32)a[1]) * ((s32)c[0] - (s32)a[0]);
        if (nat && (fl & 0x20)) {
            nat = fl >> 31 ? cr >= 0 : cr <= 0;
            if (!cr) nc_zero++;
        }
        { /* the colour and ST against the program's RGBAQ / ST (the payload: nd_buf[3 + 2j]) */
            static u32 shown;
            const u32 *rg = mem[(o + 3 * j + 1) & (DATA_QW - 1)], *st = mem[(o + 3 * j) & (DATA_QW - 1)];
            u32 want = (rg[0] & 0xFF) | (rg[1] & 0xFF) << 8 | (rg[2] & 0xFF) << 16 | (rg[3] & 0xFF) << 24;
            if (want != nd_buf[3 + 2 * j + 1][3] && shown++ < 8)
                printf("kh1-vu1: natcheck: colour %08x, payload %08x; RGBAQ q %08x, ST %08x %08x, payload ST %08x %08x\n", want,
                       nd_buf[3 + 2 * j + 1][3], rg[3], st[0], st[1], nd_buf[3 + 2 * j + 1][0], nd_buf[3 + 2 * j + 1][1]);
        }
        {
            static u32 shownf;
            if ((c[3] >> 4 & 0xFF) != nd_buf[1][0] && shownf++ < 4)
                printf("kh1-vu1: natcheck: F %u (XYZF2 w %08x), payload %u, I %08x\n", c[3] >> 4 & 0xFF, c[3], nd_buf[1][0], i_reg);
        }
        if (vu && nat) nc_both++;
        else if (!vu && !nat) nc_none++;
        else if (vu) {
            nc_p4vu += nd0_p4;
            if (nc_vu++ < 12)
                printf("kh1-vu1: natcheck: program only: flag %08x cross %lld, xy %d,%d %d,%d %d,%d (12.4, the offset in)\n", fl, cr,
                       (s32)a[0], (s32)a[1], (s32)b[0], (s32)b[1], (s32)c[0], (s32)c[1]);
        }
        else nc_nat++;
    }
    nc_p4 += nd0_p4;
    if (!(++nc_runs % 20000))
        printf("kh1-vu1: natcheck P0 / P4: %u runs (%u P4); triangles drawn by both %u, by neither %u, the program only %u "
               "(%u P4), native only %u (%u with no area)\n", nc_runs, nc_p4, nc_both, nc_none, nc_vu, nc_p4vu, nc_nat, nc_zero);
}
