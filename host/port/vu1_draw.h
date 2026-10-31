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

/* 2026-10-31: the time the game thread spends handing payloads over (dmawalk.c's queue put: the copy, and a full
 * ring's wait), all programs' and P13's, kh1_vu1_clock's microseconds; the rest of a native program's time in
 * the Vita's `vu1 programs:` line is its parse */
u32 kh1_vu1_nd_hand_us, kh1_vu1_nd13_hand_us;
static void nd_hand(const u32 *q, u32 nqw) {
    u32 t0 = kh1_vu1_clock ? kh1_vu1_clock() : 0, dt;
    kh1_vu1_draw(q, nqw);
    dt = kh1_vu1_clock ? kh1_vu1_clock() - t0 : 0;
    kh1_vu1_nd_hand_us += dt;
    if ((q[0] & 0xFF) == 13) kh1_vu1_nd13_hand_us += dt;
}

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
    if (nrec) nd_hand(nd_buf[0], rq + nmat * 4);
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
    if (nrec) nd_hand(nd_buf[0], rq + nmat * 4);
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
    nd_hand(nd_buf[0], rq + 4);
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

/* 2026-10-31 (docs/native-renderer.md "P13"): P13 from 006 (vu1_nat.h nat_13), renderer B's skinned, flat-coloured,
 * back-face-culled program: the Dive's big skinned models.  Its stream is P18's with two more kinds of record (op 0
 * with w 1 marks the bone palette's base, vi06; w 2 or more is a palette entry and loads nothing; op 2 is the index
 * stream, vi08 / vi09 the next index), and a vertex is (?, ?, ?, k), k positions each pre-weighted (xyz x weight,
 * w the weight) whose matrices come one by one from the index stream (0 / 1 / 2 a slot, 0x100 + j the palette's
 * entry j, which the program loads into slot 2), then STQ.  The program sums M_i x p_i in ACC, divides and maps as
 * P18 does, and sets the ADC for a back face (P18's rule) or for a vertex off its guard band.
 *
 * Handed over in P18's payload as program 13.  A vertex with one influence carries its position (p.xyz / p.w) and
 * its matrix, as P18's do, for the GPU to transform.  A vertex with more is summed here (c = sum M_i x p_i, the
 * clip-space point the VU would divide) and handed over in its first influence's space: v = M_a^-1 x c (in double;
 * every bone matrix of a model shares one projection, so v.w is the weights' sum, 1), the position v.xyz / v.w with
 * matrix a.  The GPU's transform of that gives c / v.w: the same place on the screen, and the same w.  The guard
 * band is the GPU's clipping (pipes.c draws P13 with z not clamped, as P11).  What the run leaves: the slots (as
 * the stream's loads and the palette's loads into slot 2 leave them), vi06, vi08 / vi09 (the index stream's place),
 * I as the program sets it, the idle PC; not the output area, vf26-31, ACC, Q, the other integer registers (P18's
 * note above).  Anything unexpected (an influence count of 0 or over 8, more than 32 matrices, a matrix that cannot
 * be inverted, v.w not positive, a full buffer) returns 0 and the program runs */
int kh1_vu1_draw_p13 = 1;
u32 kh1_vu1_nd13_multi, kh1_vu1_nd13_verts, kh1_vu1_nd13_fail, kh1_vu1_nd13_fail_us; /* the vertices summed here, and all of P13's handed over */
static int nd13_built;
static double nd13_inv[KH1_NAT_MATS][4][4]; /* M^-1 as rows, for the matrices a summed vertex is put in */
static f32 nd13_f[KH1_NAT_MATS][4][4];     /* the payload's matrices as floats (fin()'d once), for the sums */
static void nd13_add(u32 id, const u32 (*m)[4]) {
    u32 r, c;
    memcpy(nd_mat[id], m, 64);
    for (c = 0; c < 4; c++)
        for (r = 0; r < 4; r++) nd13_f[id][c][r] = fin(m[c][r]);
}
static u32 nd13_have_inv;
/* 2026-10-31 (the Vita measured nd_13 at ~1.4 us a vertex): a summed vertex goes in one reference matrix's space for
 * the whole run, through Q_i = M_ref^-1 x M_i made once per matrix (in double, kept as floats), so a vertex costs
 * k float matrix products and one reciprocal, and no double arithmetic */
static f32 nd13_q[KH1_NAT_MATS][4][4]; /* Q_i, columns as nd13_f */
static u32 nd13_have_q;
static s32 nd13_ref;
static const f32 (*nd13_getq(u32 id))[4] {
    if (!(nd13_have_q >> id & 1)) {
        u32 r, c, k;
        for (c = 0; c < 4; c++)
            for (r = 0; r < 4; r++) {
                double a = 0.0;
                if (id == (u32)nd13_ref) a = r == c;
                else
                    for (k = 0; k < 4; k++) a += nd13_inv[nd13_ref][r][k] * (double)nd13_f[id][c][k];
                nd13_q[id][c][r] = (f32)a;
            }
        nd13_have_q |= 1u << id;
    }
    return (const f32 (*)[4])nd13_q[id];
}
static int nd13_invert(u32 id) {
    double a[4][8];
    u32 r, c, k;
    if (nd13_have_inv >> id & 1) return 1;
    for (r = 0; r < 4; r++) /* M's row r from its columns: c_r = sum_k M[k][r] x_k */
        for (c = 0; c < 4; c++) {
            a[r][c] = nd13_f[id][c][r];
            a[r][4 + c] = r == c;
        }
    for (c = 0; c < 4; c++) { /* Gauss-Jordan with partial pivoting */
        u32 p = c;
        double d;
        for (r = c + 1; r < 4; r++)
            if ((a[r][c] < 0 ? -a[r][c] : a[r][c]) > (a[p][c] < 0 ? -a[p][c] : a[p][c])) p = r;
        if (a[p][c] == 0.0) return 0;
        if (p != c)
            for (k = 0; k < 8; k++) { double t = a[p][k]; a[p][k] = a[c][k]; a[c][k] = t; }
        d = 1.0 / a[c][c];
        for (k = 0; k < 8; k++) a[c][k] *= d;
        for (r = 0; r < 4; r++)
            if (r != c && a[r][c] != 0.0) {
                double f = a[r][c];
                for (k = 0; k < 8; k++) a[r][k] -= f * a[c][k];
            }
    }
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++) nd13_inv[id][r][c] = a[r][4 + c];
    nd13_have_inv |= 1u << id;
    return 1;
}
static int nd_13(u32 pc) {
    u32 i2 = top, rq = 2, nrec = 0, nmat = 0, k, l9;
    u16 i6 = vi[6], i8 = vi[8], i9 = vi[9];
    u32 sl[3][4][4];               /* the slots as the run's loads leave them (written back on success) */
    s32 cur[3] = { -1, -1, -1 };   /* each slot's matrix in this payload, -1 not listed yet */
    u32 at2 = ~0u;                 /* the palette entry slot 2 holds, ~0 when a stream load (or nothing) put it there */
    u32 pal[KH1_NAT_MATS];         /* a palette entry's address for each matrix listed from one, else ~0 */
    static const int base[3] = { 5, 12, 19 };
    nd13_built = 0;
    if (pc != 6) return 0;
    l9 = i9 & (MICRO_N - 1);
    if (l9 != 0x21 && l9 != 0x25 && l9 != 0x29 && l9 != 0x2d) return 0;
    for (k = 0; k < 3; k++) memcpy(sl[k], vf[base[k]], 64);
    nd13_have_inv = 0;
    nd13_have_q = 0;
    nd13_ref = -1;
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        u32 op = h[0] & 0xFFFF, nv, j;
        if (op == 0 || op > 0x8000) { /* 0 (and above 0x8000, as the program's s16 test reads it): w 0 a matrix into
                                        * slot z; w 1 the palette's base; else nothing */
            u32 w = h[3] & 0xFFFF;
            if (w == 0) {
                u32 r = (h[2] & 0xFFFF) == 0 ? 0 : (h[2] & 0xFFFF) == 1 ? 1 : 2;
                for (k = 0; k < 4; k++) memcpy(sl[r][k], mem[(i2 + 1 + k) & (DATA_QW - 1)], 16);
                cur[r] = -1;
                if (r == 2) at2 = ~0u;
            } else if (w == 1)
                i6 = (u16)i2;
            i2 += 8;
            continue;
        }
        if (op == 2) { /* the index stream: z qwords from the next */
            i8 = (u16)(i2 + 1);
            i9 = 0x21;
            i2 = (u16)(i2 + 1 + (h[2] & 0xFFFF));
            continue;
        }
        if (op != 1) break;
        nv = h[2] & 0xFFFF;
        if (!nv) return 0; /* 65536 vertices: none seen */
        if (rq + 1 > ND_QW - KH1_NAT_MATS * 4) return 0;
        nd_buf[rq][0] = mem[(i2 + 1) & (DATA_QW - 1)][0]; /* the GIF tag's low words */
        nd_buf[rq][1] = mem[(i2 + 1) & (DATA_QW - 1)][1];
        nd_buf[rq][2] = nv;
        nd_buf[rq][3] = h[3] & 0xFFFF;
        rq++;
        i2 += 2;
        for (j = 0; j < nv; j++) {
            u32 nb = mem[i2 & (DATA_QW - 1)][3] & 0xFFFF, b, first = 0;
            const u32 *t;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
            float32x4_t acc = vdupq_n_f32(0.0f);
#endif
            f32 c[4] = { 0, 0, 0, 0 };
            if (!nb || nb > 8) return 0;
            if (rq + 2 > ND_QW - KH1_NAT_MATS * 4) return 0;
            i2++;
            for (b = 0; b < nb; b++, i2++) {
                const u32 *p = mem[i2 & (DATA_QW - 1)], *w = mem[i8 & (DATA_QW - 1)];
                u16 ix;
                u32 r, lane = (i9 & (MICRO_N - 1)) >> 2 & 3;
                ix = (u16)w[lane];
                if (lane == 3) { i8 = (u16)(i8 + 1); i9 = 0x21; }
                else i9 = (u16)(0x21 + 4 * (lane + 1));
                if ((s16)(u16)(ix - 0x100) >= 0) { /* the palette's entry: loaded into slot 2 */
                    u32 at = (u16)((u16)(ix - 0x100) + i6) & (DATA_QW - 1), m;
                    if (at != at2) { /* 2026-10-31: the same entry again (most of a model's runs) is already there */
                        for (k = 0; k < 4; k++) memcpy(sl[2][k], mem[(at + 1 + k) & (DATA_QW - 1)], 16);
                        at2 = at;
                        cur[2] = -1;
                        for (m = 0; m < nmat; m++)
                            if (pal[m] == at) { cur[2] = (s32)m; break; }
                    }
                    if (cur[2] < 0) {
                        if (nmat == KH1_NAT_MATS) return 0;
                        nd13_add(nmat, (const u32 (*)[4])sl[2]);
                        pal[nmat] = at;
                        cur[2] = (s32)nmat++;
                    }
                    r = 2;
                } else
                    r = ix == 0 ? 0 : ix == 1 ? 1 : 2;
                if (cur[r] < 0) {
                    if (nmat == KH1_NAT_MATS) return 0;
                    nd13_add(nmat, (const u32 (*)[4])sl[r]);
                    pal[nmat] = ~0u;
                    cur[r] = (s32)nmat++;
                }
                if (!b) {
                    first = (u32)cur[r];
                    if (nb > 1 && nd13_ref < 0) { /* the run's reference matrix: the first summed vertex's first */
                        if (!nd13_invert(first)) return 0;
                        nd13_ref = (s32)first;
                    }
                }
                if (nb == 1 && p[3] == 0x3F800000u) { /* weight 1 (most): the position as it is */
                    nd_buf[rq][0] = p[0];
                    nd_buf[rq][1] = p[1];
                    nd_buf[rq][2] = p[2];
                } else if (nb == 1) {
                    f32 pw = fin(p[3]);
                    if (!(pw > 0.0f)) return 0;
                    nd_buf[rq][0] = fo(fin(p[0]) / pw);
                    nd_buf[rq][1] = fo(fin(p[1]) / pw);
                    nd_buf[rq][2] = fo(fin(p[2]) / pw);
                } else {
                    const f32 (*mm)[4] = nd13_getq((u32)cur[r]);
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
                    /* 2026-10-31: the Vita's VFP is slow at a chain of scalar products; NEON's multiply-accumulate
                     * (not fused: a multiply's rounding, then an add's, as the scalar sum) does a column at once */
                    float32x4_t v = vfin(VU_LD(p));
                    acc = vmlaq_lane_f32(acc, vld1q_f32(mm[0]), vget_low_f32(v), 0);
                    acc = vmlaq_lane_f32(acc, vld1q_f32(mm[1]), vget_low_f32(v), 1);
                    acc = vmlaq_lane_f32(acc, vld1q_f32(mm[2]), vget_high_f32(v), 0);
                    acc = vmlaq_lane_f32(acc, vld1q_f32(mm[3]), vget_high_f32(v), 1);
#else
                    f32 x = fin(p[0]), y = fin(p[1]), z = fin(p[2]), w = fin(p[3]);
                    for (k = 0; k < 4; k++) c[k] += mm[0][k] * x + mm[1][k] * y + mm[2][k] * z + mm[3][k] * w;
#endif
                }
            }
            if (nb > 1) { /* c is already in the reference's space (Q_i): v = c, the position v.xyz / v.w */
                f32 iw;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
                vst1q_f32(c, acc);
#endif
                if (!(c[3] > 1e-6f)) return 0;
                iw = 1.0f / c[3];
                nd_buf[rq][0] = fo(c[0] * iw);
                nd_buf[rq][1] = fo(c[1] * iw);
                nd_buf[rq][2] = fo(c[2] * iw);
                first = (u32)nd13_ref;
                kh1_vu1_nd13_multi++;
            }
            nd_buf[rq][3] = first;
            t = mem[i2 & (DATA_QW - 1)];
            i2++;
            nd_buf[rq + 1][0] = t[0];
            nd_buf[rq + 1][1] = t[1];
            nd_buf[rq + 1][2] = t[2];
            nd_buf[rq + 1][3] = 0;
            rq += 2;
        }
        kh1_vu1_nd13_verts += nv;
        nrec++;
    }
    nd_buf[0][0] = KH1_NAT_MAGIC | 13;
    nd_buf[0][1] = nrec;
    nd_buf[0][2] = nmat;
    nd_buf[0][3] = rq - 2;
    nd_buf[1][0] = (vf[1][0] & 0xFF) | (vf[1][1] & 0xFF) << 8 | (vf[1][2] & 0xFF) << 16 | (vf[1][3] & 0xFF) << 24;
    nd_buf[1][1] = vi[12] >> 4 & 0xFF;
    nd_buf[1][2] = vi[12] >> 15 & 1;
    nd_buf[1][3] = vi[13] >> 15 & 1;
    nd13_built = 1;
    if (!kh1_vu1_draw) return 0;
    memcpy(nd_buf[rq], nd_mat, nmat * 64);
    if (nrec) nd_hand(nd_buf[0], rq + nmat * 4);
    for (k = 0; k < 3; k++) memcpy(vf[base[k]], sl[k], 64);
    vi[6] = i6;
    vi[8] = i8;
    vi[9] = i9;
    if (nrec) i_reg = 0x44ffc000u; /* 2046, the guard band's (the program's LOI) */
    kh1_vu1_drawn++;
    tpc = 6 & (MICRO_N - 1);
    return 1;
}

/* 2026-10-31: KH1_HOST_NATCHECK=1 for P13 too: the program runs, and its output (from top + 0x1E0: per record the GIF
 * tag, then ST, RGBAQ, XYZF2 a vertex) is compared with what nd_13's payload gives: each vertex's screen position
 * (the payload's matrix x its position, divided, in sixteenths: the program's FTOI4) and each triangle's ADC against
 * the cull rule kh1_nat_tris uses, on the program's own 12.4 positions.  "the program only" must stay 0 (but for
 * slivers whose sign the 12.4 rounding decides); "native only" are those the program drops off its guard band (the
 * GPU clips them) */
static u32 n13_runs, n13_verts, n13_far, n13_zfar, n13_both, n13_none, n13_vu, n13_nat, n13_multi_far;
static f32 n13_worst;
static void nd_13_check(void) {
    u32 o = top + 0x1E0, r, j, q = 2, nrec = nd_buf[0][1], cull = nd_buf[1][3];
    if (!nd13_built) return;
    for (r = 0; r < nrec; r++) {
        u32 nv = nd_buf[q][2], par = nd_buf[q][3];
        q++;
        o++; /* the tag */
        for (j = 0; j < nv; j++, q += 2, o += 3) {
            const u32 *x = mem[(o + 2) & (DATA_QW - 1)], *v = nd_buf[q];
            f32 pos[3], ref[3], dx, dy, dz;
            pos[0] = fin(v[0]);
            pos[1] = fin(v[1]);
            pos[2] = fin(v[2]);
            kh1_nat_ref_xyz(nd_mat[v[3]][0], pos, ref);
            dx = ref[0] * 16.0f - (f32)(s32)x[0];
            dy = ref[1] * 16.0f - (f32)(s32)x[1];
            dz = ref[2] * 16.0f - (f32)(s32)x[2];
            if (dx < 0) dx = -dx;
            if (dy < 0) dy = -dy;
            if (dz < 0) dz = -dz;
            n13_verts++;
            if (!(x[3] & 0x8000) && (dx > 2.0f || dy > 2.0f)) { /* a drawn vertex more than 1/8 pixel away */
                static u32 shown;
                n13_far++;
                if (shown++ < 8)
                    printf("kh1-vu1: natcheck P13: vertex %u of record %u: program %d,%d (12.4), payload %.2f,%.2f, matrix %u\n", j,
                           r, (s32)x[0], (s32)x[1], ref[0] * 16.0f, ref[1] * 16.0f, v[3]);
            }
            if (!(x[3] & 0x8000) && dz > 64.0f + (f32)(s32)x[2] * 1e-5f) n13_zfar++;
            if (!(x[3] & 0x8000) && (dx > n13_worst || dy > n13_worst)) n13_worst = dx > dy ? dx : dy;
            if (j >= 2) {
                const u32 *a = mem[(o - 6 + 2) & (DATA_QW - 1)], *b = mem[(o - 3 + 2) & (DATA_QW - 1)];
                int vu = !(x[3] & 0x8000), nat;
                long long cr = (long long)((s32)b[0] - (s32)a[0]) * ((s32)x[1] - (s32)a[1]) -
                               (long long)((s32)b[1] - (s32)a[1]) * ((s32)x[0] - (s32)a[0]);
                nat = !cull || ((par + j) & 1 ? cr >= 0 : cr <= 0);
                if (vu && nat) n13_both++;
                else if (!vu && !nat) n13_none++;
                else if (vu) {
                    if (n13_vu++ < 12)
                        printf("kh1-vu1: natcheck P13: program only: parity %u cross %lld, xy %d,%d %d,%d %d,%d\n", (par + j) & 1,
                               cr, (s32)a[0], (s32)a[1], (s32)b[0], (s32)b[1], (s32)x[0], (s32)x[1]);
                } else n13_nat++;
            }
        }
    }
    if (!(++n13_runs % 2000))
        printf("kh1-vu1: natcheck P13: %u runs, %u vertices (%u summed here), %u drawn ones over 1/8 pixel off (worst %.2f "
               "sixteenths), %u z off; triangles drawn by both %u, by neither %u, the program only %u, native only %u\n",
               n13_runs, n13_verts, kh1_vu1_nd13_multi, n13_far, n13_worst, n13_zfar, n13_both, n13_none, n13_vu, n13_nat);
    (void)n13_multi_far;
}
