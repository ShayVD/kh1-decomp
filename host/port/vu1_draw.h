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
 * the Vita's `vu1 programs:` line is its parse.  2026-11-01 (natchain=1): 1 hand-off in 8 timed (vu1.h KH1_TIME_THIS) */
u32 kh1_vu1_nd_hand_us, kh1_vu1_nd13_hand_us;
static u32 nd_hand_smp;
static void nd_time(u32 t0, u32 num) {
    u32 dt = (kh1_vu1_clock() - t0) * KH1_TIME_EVERY;
    kh1_vu1_nd_hand_us += dt;
    if (num == 13) kh1_vu1_nd13_hand_us += dt;
}
static void nd_hand(const u32 *q, u32 nqw) {
    u32 t0 = 0, timed = kh1_vu1_clock && KH1_TIME_THIS(nd_hand_smp);
    if (timed) t0 = kh1_vu1_clock();
    kh1_vu1_draw(q, nqw);
    if (timed) nd_time(t0, q[0] & 0xFF);
}

#define ND_QW 4096 /* a payload's qwords: VU1's data memory is 1024, a vertex 3 there and 2 here */
static u32 nd_buf[ND_QW][4];
static u32 nd_mat[KH1_NAT_MATS][4][4];

/* 2026-11-01 (natchain=1): the payload written where the GS worker reads it, not built here and copied there: room
 * for ND_QW qwords in natref's pool (host/null/dmawalk.c path1_room; 0 when there is no pool), then the qwords
 * written there handed over (path1_take: the same reference op path1_draw puts).  P13 still builds in nd_buf */
u32 *(*kh1_vu1_draw_room)(u32 maxqw);
void (*kh1_vu1_draw_take)(u32 nqw);
static int nd_pooled;
static u32 (*nd_out(void))[4] {
    u32 *p;
    nd_pooled = 0;
    if (kh1_vu1_natchain && kh1_vu1_natchain != 3 && kh1_vu1_draw && kh1_vu1_draw_room &&
        (p = kh1_vu1_draw_room(ND_QW)) != 0) {
        nd_pooled = 1;
        return (u32 (*)[4])p;
    }
    return nd_buf;
}
static void nd_give(u32 (*ob)[4], u32 nqw) {
    u32 t0 = 0, timed;
    if (!nd_pooled) {
        nd_hand(ob[0], nqw);
        return;
    }
    timed = kh1_vu1_clock && KH1_TIME_THIS(nd_hand_smp);
    if (timed) t0 = kh1_vu1_clock();
    kh1_vu1_draw_take(nqw);
    if (timed) nd_time(t0, ob[0][0] & 0xFF);
}

/* natchain (vu1.c nc_*): the programs whose parse reads held unpacks, and the views they read them by */
static int nc_reader(int num) { return num == 18 || num == 11 || num == 10 || num == 0 || num == 4; }
/* renderer B's packets (renderer-spec 2.3: STCYCL 1,1; UNPACK V4-32 n -> 0 +TOPS; MSCNT): the one held unpack, at
 * top, V4-32 with CL == WL, so VU address top + o is its qword o for o < *lim */
static const u32 (*nc_b(u32 *lim))[4] {
    const NcUp *e = &nc_q[0];
    if (nc_n != 1 || (e->cmd & 0x7F) != 0x6C || e->addr != (top & (DATA_QW - 1)) || e->cl != e->wl) return 0;
    *lim = e->num;
    return (const u32 (*)[4])e->w;
}
/* renderer A's batches (renderer-spec 2.2.2: UNPACK V4-32 1 -> @0, STCYCL 3,1, V4-32 -> @1, V4-8 -> @2, V2-16 or
 * V4-16 -> @3, MSCNT): exactly those four held, each once (so none writes over another) */
static int nc_a(const NcUp **e) {
    u32 i, a = top & (DATA_QW - 1);
    e[0] = e[1] = e[2] = e[3] = 0;
    if (nc_n != 4) return 0;
    for (i = 0; i < 4; i++) {
        const NcUp *x = &nc_q[i];
        u32 c = x->cmd & 0x7F, d = (x->addr - a) & (DATA_QW - 1), k;
        if (d == 0 && c == 0x6C && x->num == 1) k = 0;
        else if (d == 1 && c == 0x6C) k = 1;
        else if (d == 2 && c == 0x6E) k = 2;
        else if (d == 3 && (c == 0x65 || c == 0x6D)) k = 3;
        else return 0;
        if (e[k] || (k && (x->cl != 3 || x->wl != 1))) return 0;
        e[k] = x;
    }
    return 1;
}
/* the held unpacks were read and handed over: never written (natchain=2: their addresses poisoned instead) */
static void nc_drop(void) {
    u32 i, j, f;
    for (i = 0; i < nc_n; i++) {
        const NcUp *e = &nc_q[i];
        kh1_vu1_nc_qw += e->num;
        st.unpacks++;
        if (kh1_vu1_natchain == 2)
            for (j = 0; j < e->num; j++) {
                u32 a = (e->addr + j / e->wl * e->cl + j % e->wl) & (DATA_QW - 1);
                for (f = 0; f < 4; f++) mem[a][f] = 0xBAD00000u | a << 2 | f;
            }
    }
    nc_n = 0;
    kh1_vu1_nc_runs++;
}
static u32 nd_chk[ND_QW][4]; /* natchain=3: the payload parsed from VU memory, for the comparison */
static void nc_compare(const u32 (*a)[4], u32 na, const u32 (*b)[4], u32 nb) {
    if (na != nb || memcmp(a, b, na * 16)) {
        if (!kh1_vu1_nc_bad++) printf("kh1-vu1: natchain: a payload read from the chain differs (P%u, %u / %u qwords)\n",
                                       a[0][0] & 0xFF, na, nb);
    }
    kh1_vu1_nc_runs++;
}

/* P18 from 007 (vu1_nat.h nat_18 is the arithmetic this replaces): 1 when handed over, 0 to run it.  2026-10-31: P11
 * too (num 11): P18's stream and output, with a near-plane cull (w < 1) and the guard band, which the GPU's own
 * clipping replaces (pipes.c draws it with z not clamped).  2026-11-01: nd_18_build reads the stream from VU memory
 * (s 0) or from the held unpack's words (s, lim qwords: anything past them fails, and the caller reads VU memory) */
#define NQ(o) (s ? s[o] : mem[(top + (o)) & (DATA_QW - 1)])
static s16 nb_msrc[KH1_NAT_MATS]; /* 2026-11-02 (natvb): each payload matrix's stream qword, or -1 - its register slot */
static __inline__ __attribute__((always_inline)) u32 nd_18_build(u32 num, u32 (*ob)[4], const u32 (*s)[4], u32 lim,
                                                                 u32 *nrec_o, s32 *last) {
    u32 o = 0, rq = 2, nrec = 0, nmat = 0, k;
    s32 cur[3] = { -1, -1, -1 }; /* each slot's matrix in this payload */
    static const int base[3] = { 5, 12, 19 };
    for (;;) {
        const u32 *h;
        u32 op, nv, j, par;
        if (s && o >= lim) return 0;
        h = NQ(o);
        op = h[0] & 0xFFFF;
        if (!op) { /* a matrix into slot z (0, 1, else 2): the slot's vertices that follow use it */
            u32 sl = (h[2] & 0xFFFF) == 0 ? 0 : (h[2] & 0xFFFF) == 1 ? 1 : 2;
            if (nmat == KH1_NAT_MATS || (s && o + 5 > lim)) return 0;
            for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], NQ(o + 1 + k), 16);
            nb_msrc[nmat] = (s16)(o + 1);
            cur[sl] = last[sl] = (s32)nmat++;
            o += 8;
            continue;
        }
        if (op != 1) break;
        nv = h[2] & 0xFFFF;
        par = h[3] & 0xFFFF;
        if (!nv) nv = 0x10000; /* z counts down to 0 after the first: 0 is 65536, which no stream has */
        if (rq + 1 + nv * 2 + 2 > ND_QW - KH1_NAT_MATS * 4) return 0;
        if (s && o + 2 + nv * 3 > lim) return 0;
        ob[rq][0] = NQ(o + 1)[0]; /* the GIF tag's low words */
        ob[rq][1] = NQ(o + 1)[1];
        ob[rq][2] = nv;
        ob[rq][3] = par;
        rq++;
        o += 2;
        for (j = 0; j < nv; j++, o += 3) {
            const u32 *n = NQ(o), *p = NQ(o + 1), *t = NQ(o + 2);
            u32 sl = (n[3] & 0xFFFF) == 0 ? 0 : (n[3] & 0xFFFF) == 1 ? 1 : 2;
            if (p[3] != 0x3F800000u) return 0; /* w is 1 in every stream seen: else the program's own way */
            if (cur[sl] < 0) { /* the slot's matrix as the registers hold it now */
                if (nmat == KH1_NAT_MATS) return 0;
                for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], vf[base[sl] + k], 16);
                nb_msrc[nmat] = (s16)(-1 - (s32)sl);
                cur[sl] = (s32)nmat++;
            }
            ob[rq][0] = p[0];
            ob[rq][1] = p[1];
            ob[rq][2] = p[2];
            ob[rq][3] = (u32)cur[sl];
            ob[rq + 1][0] = t[0];
            ob[rq + 1][1] = t[1];
            ob[rq + 1][2] = t[2];
            ob[rq + 1][3] = 0;
            rq += 2;
        }
        nrec++;
    }
    ob[0][0] = KH1_NAT_MAGIC | num;
    ob[0][1] = nrec;
    ob[0][2] = nmat;
    ob[0][3] = rq - 2;
    ob[1][0] = (vf[1][0] & 0xFF) | (vf[1][1] & 0xFF) << 8 | (vf[1][2] & 0xFF) << 16 | (vf[1][3] & 0xFF) << 24;
    ob[1][1] = vi[12] >> 4 & 0xFF;
    ob[1][2] = vi[12] >> 15 & 1;
    ob[1][3] = vi[13] >> 15 & 1;
    memcpy(ob[rq], nd_mat, nmat * 64);
    *nrec_o = nrec;
    return rq + nmat * 4;
}
/* 2026-11-02 (natdraw.h natvb, docs/native-plan.md "Vertex buffers cached by the records' address"): a run of P18, P11
 * or P10 whose records are the held unpack s (lim qwords) and whose entry is there with the same words hands over
 * the entry's payload (its matrices from the stream and the slot registers, a stub a strip): 1, with *n its qwords and
 * last the slots' loads.  Check mode (natvb=3) also parses the run and compares */
static u32 nb_bad_shown;
static __inline__ __attribute__((always_inline)) u32 nd_10_build(u32 (*ob)[4], const u32 (*s)[4], u32 lim, u32 *nrec_o,
                                                                 s32 *last);
static __inline__ int nb_hit(u32 num, u32 (*ob)[4], const u32 (*s)[4], u32 lim, u32 rgba, u32 f, u32 flags, s32 *last,
                             u32 *n, KH1NatVb **e_o) {
    static const int base[3] = { 5, 12, 19 };
    const u32 *reg[3];
    u32 nmat;
    KH1NatVb *e;
    *e_o = 0;
    if (!kh1_natvb || kh1_vu1_natchain != 1) return 0;
    e = kh1_natvb_find((const u32 *)s, lim, num, rgba, f, flags);
    *e_o = e;
    if (!e || !kh1_natvb_same(e, (const u32 *)s)) return 0;
    reg[0] = vf[base[0]];
    reg[1] = vf[base[1]];
    reg[2] = vf[base[2]];
    *n = kh1_natvb_payload(e, (const u32 *)s, reg, ob, nd_mat, &nmat, last);
    if (kh1_natvb == 3) { /* the same run parsed: its matrices, slots and triangles */
        u32 r2, n2, rq = ob[0][3];
        s32 l2[3] = { -1, -1, -1 };
        static u32 keep[KH1_NAT_MATS][4][4];
        memcpy(keep, nd_mat, nmat * 64);
        n2 = num == 10 ? nd_10_build(nd_chk, s, lim, &r2, l2) : nd_18_build(num, nd_chk, s, lim, &r2, l2);
        if (!n2 || nd_chk[0][2] != nmat || memcmp(nd_chk[2 + nd_chk[0][3]], ob[2 + rq], nmat * 64) ||
            l2[0] != last[0] || l2[1] != last[1] || l2[2] != last[2] || memcmp(nd_chk[1], ob[1], 16) ||
            !kh1_natvb_check(e, nd_chk[0], num == 11 ? KH1_NAT_LIN : 0)) {
            if (!nb_bad_shown++) printf("kh1-vu1: natvb: a cached run differs from its parse (P%u, %u qwords at %08x)\n", num, lim,
                                        (u32)(unsigned long)s);
            kh1_natvb_bad++;
        }
        memcpy(nd_mat, keep, nmat * 64);
    }
    return 1;
}
static int nd_18(u32 pc, u32 num) {
    u32 (*ob)[4], n = 0, nrec = 0, k, lim;
    s32 last[3] = { -1, -1, -1 }; /* the last matrix each slot loaded */
    static const int base[3] = { 5, 12, 19 };
    const u32 (*s)[4];
    KH1NatVb *e = 0;
    if (pc != 7 || !kh1_vu1_draw) return 0;
    ob = nd_out();
    if (nc_n && (s = nc_b(&lim)) != 0 && kh1_natvb) {
        u32 rgba = (vf[1][0] & 0xFF) | (vf[1][1] & 0xFF) << 8 | (vf[1][2] & 0xFF) << 16 | (vf[1][3] & 0xFF) << 24;
        u32 fl = (vi[12] >> 15 & 1) | (vi[13] >> 15 & 1) << 1;
        if (nb_hit(num, ob, s, lim, rgba, vi[12] >> 4 & 0xFF, fl, last, &n, &e)) {
            nc_drop();
            nd_give(ob, n);
            for (k = 0; k < 3; k++)
                if (last[k] >= 0) memcpy(vf[base[k]], nd_mat[last[k]], 64);
            kh1_vu1_drawn++;
            tpc = 7 & (MICRO_N - 1);
            return 1;
        }
        if ((n = nd_18_build(num, ob, s, lim, &nrec, last)) != 0 && kh1_vu1_natchain == 1 && nrec)
            kh1_natvb_learn((const u32 *)s, lim, num, fl, ob[0], nb_msrc, 7, last, num == 11 ? KH1_NAT_LIN : 0);
        if (n) {
            if (kh1_vu1_natchain == 3) {
                u32 r2;
                s32 l2[3] = { -1, -1, -1 };
                nc_flush();
                nc_compare((const u32 (*)[4])ob, n, (const u32 (*)[4])nd_chk, nd_18_build(num, nd_chk, 0, 0, &r2, l2));
            } else nc_drop();
        }
    } else if (nc_n && (s = nc_b(&lim)) != 0 && (n = nd_18_build(num, ob, s, lim, &nrec, last)) != 0) {
        if (kh1_vu1_natchain == 3) { /* the same from VU memory */
            u32 r2;
            s32 l2[3] = { -1, -1, -1 };
            nc_flush();
            nc_compare((const u32 (*)[4])ob, n, (const u32 (*)[4])nd_chk, nd_18_build(num, nd_chk, 0, 0, &r2, l2));
        } else nc_drop();
    }
    if (!n) {
        if (nc_n) nc_flush();
        last[0] = last[1] = last[2] = -1;
        n = nd_18_build(num, ob, 0, 0, &nrec, last);
        if (!n) return 0;
    }
    if (nrec) nd_give(ob, n);
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
 * no TME).  Fewer than 3 positions (the program's count wraps) is left to the program.  2026-11-01: from VU memory or
 * the held unpack, as nd_18_build */
static u32 nd10_rgba = 0x80808080u;
static void nd_10_setup(void) {
    nd10_rgba = (mem[1][0] & 0xFF) | (mem[1][1] & 0xFF) << 8 | (mem[1][2] & 0xFF) << 16 | (mem[1][3] & 0xFF) << 24;
}
static __inline__ __attribute__((always_inline)) u32 nd_10_build(u32 (*ob)[4], const u32 (*s)[4], u32 lim, u32 *nrec_o,
                                                                 s32 *last) {
    u32 o = 0, rq = 2, nrec = 0, nmat = 0, k;
    s32 cur[3] = { -1, -1, -1 };
    static const int base[3] = { 5, 12, 19 };
    for (;;) {
        const u32 *h;
        u32 op, nv, j;
        if (s && o >= lim) return 0;
        h = NQ(o);
        op = h[0] & 0xFFFF;
        if (!op) {
            u32 sl = (h[2] & 0xFFFF) == 0 ? 0 : (h[2] & 0xFFFF) == 1 ? 1 : 2;
            if (nmat == KH1_NAT_MATS || (s && o + 5 > lim)) return 0;
            for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], NQ(o + 1 + k), 16);
            nb_msrc[nmat] = (s16)(o + 1);
            cur[sl] = last[sl] = (s32)nmat++;
            o += 5;
            continue;
        }
        if (op != 1) break;
        nv = h[2] & 0xFFFF;
        if (nv < 3) return 0;
        if (rq + 1 + nv * 2 + 2 > ND_QW - KH1_NAT_MATS * 4) return 0;
        if (s && o + 2 + nv > lim) return 0;
        ob[rq][0] = NQ(o + 1)[0];
        ob[rq][1] = NQ(o + 1)[1];
        ob[rq][2] = nv;
        ob[rq][3] = 0;
        rq++;
        o += 2;
        for (j = 0; j < nv; j++, o++) {
            const u32 *p = NQ(o);
            u32 sl = (p[3] & 0xFFFF) == 0 ? 0 : (p[3] & 0xFFFF) == 1 ? 1 : 2;
            if (cur[sl] < 0) {
                if (nmat == KH1_NAT_MATS) return 0;
                for (k = 0; k < 4; k++) memcpy(nd_mat[nmat][k], vf[base[sl] + k], 16);
                nb_msrc[nmat] = (s16)(-1 - (s32)sl);
                cur[sl] = (s32)nmat++;
            }
            ob[rq][0] = p[0];
            ob[rq][1] = p[1];
            ob[rq][2] = p[2];
            ob[rq][3] = (u32)cur[sl];
            ob[rq + 1][0] = ob[rq + 1][1] = ob[rq + 1][3] = 0;
            ob[rq + 1][2] = 0x3F800000u;
            rq += 2;
        }
        nrec++;
    }
    ob[0][0] = KH1_NAT_MAGIC | 10;
    ob[0][1] = nrec;
    ob[0][2] = nmat;
    ob[0][3] = rq - 2;
    ob[1][0] = nd10_rgba;
    ob[1][1] = 0;
    ob[1][2] = 0;
    ob[1][3] = 0;
    memcpy(ob[rq], nd_mat, nmat * 64);
    *nrec_o = nrec;
    return rq + nmat * 4;
}
static int nd_10(u32 pc) {
    u32 (*ob)[4], n = 0, nrec = 0, k, lim;
    s32 last[3] = { -1, -1, -1 };
    static const int base[3] = { 5, 12, 19 };
    const u32 (*s)[4];
    KH1NatVb *e = 0;
    if (pc != 6 || !kh1_vu1_draw) return 0;
    ob = nd_out();
    if (nc_n && (s = nc_b(&lim)) != 0 && kh1_natvb) { /* 2026-11-02: natvb, as nd_18 */
        if (nb_hit(10, ob, s, lim, nd10_rgba, 0, 0, last, &n, &e)) {
            nc_drop();
            nd_give(ob, n);
            for (k = 0; k < 3; k++)
                if (last[k] >= 0) memcpy(vf[base[k]], nd_mat[last[k]], 64);
            kh1_vu1_drawn++;
            tpc = 6 & (MICRO_N - 1);
            return 1;
        }
        if ((n = nd_10_build(ob, s, lim, &nrec, last)) != 0 && kh1_vu1_natchain == 1 && nrec)
            kh1_natvb_learn((const u32 *)s, lim, 10, 0, ob[0], nb_msrc, 4, last, 0);
        if (n) {
            if (kh1_vu1_natchain == 3) {
                u32 r2;
                s32 l2[3] = { -1, -1, -1 };
                nc_flush();
                nc_compare((const u32 (*)[4])ob, n, (const u32 (*)[4])nd_chk, nd_10_build(nd_chk, 0, 0, &r2, l2));
            } else nc_drop();
        }
    } else if (nc_n && (s = nc_b(&lim)) != 0 && (n = nd_10_build(ob, s, lim, &nrec, last)) != 0) {
        if (kh1_vu1_natchain == 3) {
            u32 r2;
            s32 l2[3] = { -1, -1, -1 };
            nc_flush();
            nc_compare((const u32 (*)[4])ob, n, (const u32 (*)[4])nd_chk, nd_10_build(nd_chk, 0, 0, &r2, l2));
        } else nc_drop();
    }
    if (!n) {
        if (nc_n) nc_flush();
        last[0] = last[1] = last[2] = -1;
        n = nd_10_build(ob, 0, 0, &nrec, last);
        if (!n) return 0;
    }
    if (nrec) nd_give(ob, n);
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
/* one P0 vertex's colour (ITOF0, x vf31, FTOI0 toward 0 and saturating, the low bytes as the GS takes them) and ST
 * (ITOF12: / 4096), into o[0..1] (s, t bits) and *rgba: the scalar form, and (2026-11-01) four lanes at once on
 * NEON, the same bits (tests/host/vu1neon_test.c: nd0_vert against nd0_vert_c) */
static __inline__ void nd0_vert_c(const u32 *c, const u32 *t, const f32 *sc, u32 *o, u32 *rgba) {
    u32 k, r = 0;
    for (k = 0; k < 4; k++) {
        f32 v = (f32)(s32)c[k] * sc[k];
        s32 iv = v >= 2147483520.0f ? 0x7FFFFFFF : v <= -2147483648.0f ? (s32)0x80000000u : (s32)v;
        r |= ((u32)iv & 0xFF) << (k * 8);
    }
    *rgba = r;
    o[0] = fo((f32)(s32)t[0] * (1.0f / 4096.0f));
    o[1] = fo((f32)(s32)t[1] * (1.0f / 4096.0f));
}
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
/* NEON's float to integer conversion rounds toward 0 and saturates as FTOI0, but at 2^31 - 128 (the largest float
 * below 2^31), which the scalar form takes as saturated: such a vertex (and anything whose ST is not a normal float or 0)
 * goes the scalar way */
static __inline__ void nd0_vert(const u32 *c, const u32 *t, float32x4_t scv, const f32 *sc, u32 *o, u32 *rgba) {
    float32x4_t v = vmulq_f32(vcvtq_f32_s32(vld1q_s32((const s32 *)c)), scv);
    uint32x4_t big = vcgeq_f32(v, vdupq_n_f32(2147483520.0f));
    uint16x4_t n16 = vmovn_u32(vreinterpretq_u32_s32(vcvtq_s32_f32(v)));
    float32x2_t st = vmul_f32(vcvt_f32_s32(vld1_s32((const s32 *)t)), vdup_n_f32(1.0f / 4096.0f));
    uint32x2_t b2 = vorr_u32(vget_low_u32(big), vget_high_u32(big));
    if (vget_lane_u32(b2, 0) | vget_lane_u32(b2, 1)) {
        nd0_vert_c(c, t, sc, o, rgba);
        return;
    }
    *rgba = vget_lane_u32(vreinterpret_u32_u8(vmovn_u16(vcombine_u16(n16, n16))), 0);
    vst1_u32(o, vreinterpret_u32_f32(st)); /* |t| < 2^31 over 4096: a normal float or 0, as fo leaves it */
}
#endif

/* 2026-11-01: nd_0_build reads the batch from VU memory (e 0) or from the four held unpacks (nc_a): the tag, the
 * positions (V4-32), the colours (V4-8) and ST (V2-16 or V4-16), each element as the unpack would have written it;
 * *tw the tag's w (the clipped fans' template) */
static __inline__ __attribute__((always_inline)) u32 nd_0_build(int p4, u32 (*ob)[4], const NcUp *const *e, u32 *tw) {
    const u32 *h = e ? e[0]->w : mem[top & (DATA_QW - 1)];
    u32 nv = h[0] & 0x7FFF, rq = 2, j, k, i2 = top + 1;
    u32 cu = e ? e[2]->imm >> 14 & 1 : 0, tu = e ? e[3]->imm >> 14 & 1 : 0, ts = e && (e[3]->cmd & 0x7F) == 0x6D ? 4 : 2;
    f32 sc[4], m[4][4];
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
    float32x4_t scv;
#endif
    if (!nv || 3 + nv * 2 + 4 > ND_QW || nv * 7u + 8 > DATA_QW) return 0;
    if (e && (nv > e[1]->num || nv > e[2]->num || nv > e[3]->num)) return 0;
    for (k = 0; k < 4; k++) sc[k] = fin(vf[31][k]);
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
    scv = vld1q_f32(sc);
#endif
    for (k = 0; k < 4; k++) { /* column k of P x W: P (vf01-04) applied to W's column k (vf13-16) */
        f32 w0 = fin(vf[13 + k][0]), w1 = fin(vf[13 + k][1]), w2 = fin(vf[13 + k][2]), w3 = fin(vf[13 + k][3]);
        u32 r;
        for (r = 0; r < 4; r++)
            m[k][r] = fin(vf[1][r]) * w0 + fin(vf[2][r]) * w1 + fin(vf[3][r]) * w2 + fin(vf[4][r]) * w3;
    }
    ob[rq][0] = h[0];
    ob[rq][1] = h[1];
    ob[rq][2] = nv;
    ob[rq][3] = 0;
    rq++;
    for (j = 0; j < nv; j++, i2 += 3) {
        const u32 *p, *c, *t;
        u32 rgba, cv[4], tv[2];
        if (e) { /* the unpack's elements: V4-8 and V2-16 / V4-16 sign-extended unless USN */
            const u8 *cb = (const u8 *)e[2]->w + j * 4;
            const u16 *th = (const u16 *)e[3]->w + j * ts;
            p = e[1]->w + j * 4;
            for (k = 0; k < 4; k++) cv[k] = cu ? cb[k] : (u32)(s32)(s8)cb[k];
            tv[0] = tu ? th[0] : (u32)(s32)(s16)th[0];
            tv[1] = tu ? th[1] : (u32)(s32)(s16)th[1];
            c = cv;
            t = tv;
        } else {
            p = mem[i2 & (DATA_QW - 1)];
            c = mem[(i2 + 1) & (DATA_QW - 1)];
            t = mem[(i2 + 2) & (DATA_QW - 1)];
        }
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
        nd0_vert(c, t, scv, sc, ob[rq + 1], &rgba);
#else
        nd0_vert_c(c, t, sc, ob[rq + 1], &rgba);
#endif
        ob[rq][0] = p[0];
        ob[rq][1] = p[1];
        ob[rq][2] = p[2];
        ob[rq][3] = p4 && p[3] & 0xFFFF ? (p[3] & ~0x20u) | 1 : p[3]; /* the strip flag word (natdraw.h) */
        ob[rq + 1][2] = 0x3F800000u;
        ob[rq + 1][3] = rgba;
        rq += 2;
    }
    ob[0][0] = KH1_NAT_MAGIC | 0;
    ob[0][1] = 1;
    ob[0][2] = 1;
    ob[0][3] = rq - 2;
    ob[1][0] = (u32)(s32)fin(i_reg) & 0xFF; /* F: the I register (MULI.w, FTOI4, the GS's F) */
    ob[1][1] = ob[1][2] = ob[1][3] = 0;
    for (k = 0; k < 4; k++) memcpy(ob[rq + k], m[k], 16);
    *tw = h[3];
    return rq + 4;
}
static int nd_0(u32 pc, int p4) {
    const NcUp *e[4];
    u32 (*ob)[4], n = 0, tw = 0;
    nd0_built = 0;
    nd0_p4 = p4;
    if (pc != 0xc && pc != (p4 ? 0x45u : 0x4eu)) return 0;
    ob = kh1_vu1_draw ? nd_out() : nd_buf; /* (KH1_HOST_NATCHECK builds in nd_buf, with nothing held) */
    if (nc_n && nc_a(e) && (n = nd_0_build(p4, ob, e, &tw)) != 0) {
        if (kh1_vu1_natchain == 3) {
            u32 t2 = 0;
            nc_flush();
            nc_compare((const u32 (*)[4])ob, n, (const u32 (*)[4])nd_chk, nd_0_build(p4, nd_chk, 0, &t2));
            if (t2 != tw && !kh1_vu1_nc_bad++) printf("kh1-vu1: natchain: P0's template differs\n");
        } else nc_drop();
    }
    if (!n) {
        if (nc_n) nc_flush();
        n = nd_0_build(p4, ob, 0, &tw);
        if (!n) return 0;
    }
    nd0_built = 1;
    if (!kh1_vu1_draw) return 0;
    nd_give(ob, n);
    if (!p4) mem[48][1] = tw; /* P4 leaves the template as it is */
    kh1_vu1_drawn++;
    tpc = (p4 ? 0x45 : 0x4e) & (MICRO_N - 1);
    return 1;
}
#undef NQ

/* 2026-11-04 (docs/native-renderer.md "The Gummi engine"): C0 / C1 (P100 / P101, renderer-spec 2.5; vu1_nat.h
 * nat_gummi is the arithmetic this replaces) from 02c or their idle PC, as P0 payloads (natdraw.h): one matrix, vf01-04
 * (the local to the VU's clip space the program divides by w), the batch's positions as they are, and per vertex what
 * the program's routines would give it: the lit colour (the normals through vf05-08, MAX 0, the colour matrix
 * vf09-12, done here once a normal) times the multiplier (C0: the vertex's own; C1: the material's, qw 992 + m), MINI
 * 255, FTOI0; ST plus the group's UV scroll (C0).  Each run is a record, its fans as strips (a quad v0..v3 as v1, v2,
 * v0, v3), their triangles flagged for the cull unless the group is double-sided, with the program's facing rule (a
 * fan kept when its first triangle's screen cross product is negative: P0's positive flag).  A group's texture (its
 * GIF tag and TEX0_1) goes to the GS as a kick of its own between payloads.  The program's clipping (the w plane at
 * qw 1020, the guard box) is the GPU's here; a batch wholly outside one plane is drawn by it and clipped.  What the
 * run leaves: the idle PC only (vi08's output buffer, the scratch at qw 1007-1014 and the batch's in-place results
 * are not written; nothing reads them before the next run of the program writes them) */
int kh1_vu1_draw_gum = 1;
u32 kh1_vu1_nd_gum, kh1_vu1_nd_gum_fail; /* runs handed over, runs given back to the program */
static u32 ndg_kq[2][4];
/* 2026-11-04 (docs/native-renderer.md "The Gummi parse, lighter"): a vertex's colour, the lit normal (w the colour
 * matrix's vf12.w) times the multiplier, MINI 255, FTOI0, the low bytes; C1's multiplier is the group's, so its
 * colours are one table a group (a normal each), C0's a vertex's.  The NEON form gives the same bits: VMIN keeps a
 * NaN as the scalar test does and VCVT takes it to 0 as VFP's does, saturating at -2^31 as the scalar form's test */
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
#define NDG_NEON 1
typedef float32x4_t NdgV;
static __inline__ __attribute__((always_inline)) u32 ndg_rgba(float32x4_t col, float32x4_t mul) {
    int32x4_t iv = vcvtq_s32_f32(vminq_f32(vmulq_f32(col, mul), vdupq_n_f32(255.0f)));
    int16x4_t h = vmovn_s32(iv);
    return vget_lane_u32(vreinterpret_u32_s8(vmovn_s16(vcombine_s16(h, h))), 0);
}
static __inline__ __attribute__((always_inline)) uint32x2_t vfin2(uint32x2_t u) { /* vu1.c vfin, two lanes */
    int32x2_t p = vmin_s32(vreinterpret_s32_u32(u), vdup_n_s32(0x7F7FFFFF));
    return vmin_u32(vreinterpret_u32_s32(p), vdup_n_u32(0xFF7FFFFFu));
}
#else
typedef struct { f32 v[4]; } NdgV;
static __inline__ u32 ndg_rgba(NdgV col, NdgV mul) {
    u32 q, rgba = 0;
    for (q = 0; q < 4; q++) {
        f32 v = col.v[q] * mul.v[q];
        s32 iv;
        if (v > 255.0f) v = 255.0f;
        iv = v <= -2147483648.0f ? (s32)0x80000000u : (s32)v;
        rgba |= ((u32)iv & 0xFF) << (q * 8);
    }
    return rgba;
}
#endif
static __inline__ __attribute__((always_inline)) NdgV ndg_fin(const u32 *w) { /* fin() of a qword */
#ifdef NDG_NEON
    return vfin(vld1q_u32(w));
#else
    NdgV r;
    u32 q;
    for (q = 0; q < 4; q++) r.v[q] = fin(w[q]);
    return r;
#endif
}
/* the payload so far (nrec records, rq qwords with the header's two) drawn, with vf01-04 as its matrix */
static void ndg_flush(u32 (*ob)[4], u32 nrec, u32 rq) {
    u32 k;
    ob[0][0] = KH1_NAT_MAGIC | 0;
    ob[0][1] = nrec;
    ob[0][2] = 1;
    ob[0][3] = rq - 2;
    memset(ob[1], 0, 16);
    for (k = 0; k < 4; k++) memcpy(ob[rq + k], vf[1 + k], 16);
    nd_hand(ob[0], rq + 4);
}
static int nd_gum(u32 pc, int c1) {
    const u32 *h;
    u32 (*ob)[4] = nd_buf, rq = 2, nrec = 0, k, base = top & (DATA_QW - 1);
    u32 npos, nnorm, i7, nv0;
    NdgV lit[64]; /* the normals lit, w the colour's (vf12.w) */
    u32 tab[64];  /* C1: a group's colours, a normal each */
    if (pc != 0x2c && pc != (c1 ? 0xc1u : 0xc6u)) return 0;
    h = mem[base];
    npos = h[1] & 0xFFFF;
    nnorm = h[2] & 0xFFFF;
    i7 = (h[3] + base) & 0xFFFF;
    nv0 = (base + 1 + (h[0] & 0xFFFF) + npos) & 0xFFFF; /* the normals' first qword */
    if (!npos || !nnorm || nnorm > 64) goto fail;
    { /* walked first: nothing is handed over unless the whole batch is one done here (routines, fan sizes, room) */
        u32 p7 = i7, need = 2;
        for (;;) {
            const u32 *g = mem[p7 & (DATA_QW - 1)];
            u32 nr = g[0] & 0xFFFF, mm = g[1] & 0xFFFF, vr;
            p7++;
            if (!nr) break;
            vr = mem[(1021 + mm) & (DATA_QW - 1)][0] & 0xFFFF & (MICRO_N - 1);
            if (vr != (c1 ? 0xc3u : 0xc8u) && vr != (c1 ? 0xd7u : 0xdfu)) goto fail;
            p7 += 1 + (mm ? 2 : 0);
            if (mm) need = 2;
            for (; nr; nr--) {
                const u32 *rh = mem[p7 & (DATA_QW - 1)];
                u32 fv = rh[0] & 0xFFFF, ns = rh[1] & 0xFFFF;
                if ((fv != 3 && fv != 4) || !ns || ns > 256) goto fail;
                need += 1 + ns * fv * 2;
                if (need + 4 > ND_QW) goto fail;
                p7 += 2 + ns * fv;
            }
        }
    }
    { /* the normals lit: vf09-12 x max(vf05-08 x (n, 1), 0), in the scalar form's order of sums */
#ifdef NDG_NEON
        float32x4_t m5[4], m9[4], z = vdupq_n_f32(0);
        f32 w12 = fin(vf[12][3]);
        for (k = 0; k < 4; k++) {
            m5[k] = vfin(vld1q_u32(vf[5 + k]));
            m9[k] = vfin(vld1q_u32(vf[9 + k]));
        }
        for (k = 0; k < nnorm; k++) {
            float32x4_t n = vfin(vld1q_u32(mem[(nv0 + k) & (DATA_QW - 1)])), a, l;
            a = vmulq_lane_f32(m5[0], vget_low_f32(n), 0);
            a = vmlaq_lane_f32(a, m5[1], vget_low_f32(n), 1);
            a = vmlaq_lane_f32(a, m5[2], vget_high_f32(n), 0);
            a = vmaxq_f32(vaddq_f32(a, m5[3]), z);
            l = vmulq_lane_f32(m9[0], vget_low_f32(a), 0);
            l = vmlaq_lane_f32(l, m9[1], vget_low_f32(a), 1);
            l = vmlaq_lane_f32(l, m9[2], vget_high_f32(a), 0);
            l = vmlaq_lane_f32(l, m9[3], vget_high_f32(a), 1);
            lit[k] = vsetq_lane_f32(w12, l, 3);
        }
#else
        f32 m9[4][4], m5[4][4];
        for (k = 0; k < 4; k++) {
            u32 r;
            for (r = 0; r < 4; r++) {
                m5[k][r] = fin(vf[5 + k][r]);
                m9[k][r] = fin(vf[9 + k][r]);
            }
        }
        for (k = 0; k < nnorm; k++) {
            const u32 *n = mem[(nv0 + k) & (DATA_QW - 1)];
            f32 x = fin(n[0]), y = fin(n[1]), z = fin(n[2]), a[4];
            u32 r;
            for (r = 0; r < 4; r++) {
                f32 v = m5[0][r] * x + m5[1][r] * y + m5[2][r] * z + m5[3][r];
                a[r] = v > 0 ? v : 0;
            }
            for (r = 0; r < 3; r++) lit[k].v[r] = m9[0][r] * a[0] + m9[1][r] * a[1] + m9[2][r] * a[2] + m9[3][r] * a[3];
            lit[k].v[3] = fin(vf[12][3]);
        }
#endif
    }
    for (;;) { /* the groups */
        const u32 *g = mem[i7 & (DATA_QW - 1)];
        u32 nr = g[0] & 0xFFFF, mm = g[1] & 0xFFFF, dbl = (g[2] & 0xFFFF) != 0, vr, tex, fl;
        u32 sxy[2] = { 0, 0 };
        i7++;
        if (!nr) break;
        vr = mem[(1021 + mm) & (DATA_QW - 1)][0] & 0xFFFF & (MICRO_N - 1);
        tex = vr == (c1 ? 0xd7u : 0xdfu);
        fl = dbl ? 1u : 0x21u; /* a triangle's flag (natdraw.h): the cull unless the group is double-sided */
        if (c1) {
            NdgV mc = ndg_fin(mem[(992 + mm) & (DATA_QW - 1)]);
            for (k = 0; k < nnorm; k++) tab[k] = ndg_rgba(lit[k], mc);
        } else {
            u32 slot = mem[i7 & (DATA_QW - 1)][0] & 0xFFFF;
            if (slot) {
                f32 sx = fin(mem[(991 + slot) & (DATA_QW - 1)][0]), sy = fin(mem[(991 + slot) & (DATA_QW - 1)][1]);
                memcpy(&sxy[0], &sx, 4);
                memcpy(&sxy[1], &sy, 4);
            }
        }
        i7++; /* the UV slot's qword (C1 skips it too) */
        if (mm) { /* a texture: the payload so far drawn, then the GIF tag and TEX0_1 on their own (EOP) */
            if (nrec) {
                ndg_flush(ob, nrec, rq);
                rq = 2;
                nrec = 0;
            }
            memcpy(ndg_kq[0], mem[i7 & (DATA_QW - 1)], 16);
            memcpy(ndg_kq[1], mem[(i7 + 1) & (DATA_QW - 1)], 16);
            ndg_kq[0][0] |= 0x8000u;
            if (kh1_vu1_kick) kh1_vu1_kick(ndg_kq[0], 2);
            i7 += 2;
        }
        for (; nr; nr--) { /* the runs */
            const u32 *rh = mem[i7 & (DATA_QW - 1)], *tag = mem[(i7 + 1) & (DATA_QW - 1)];
            u32 fv = rh[0] & 0xFFFF, ns = rh[1] & 0xFFFF, s, j, rv = rq;
            /* a fan's flag words: its first two vertices end no triangle; a quad v0..v3 is the strip v1, v2, v0,
             * v3, whose second triangle is the reversed one */
            u32 fw[4] = { 0, 0, fl, fv == 4 ? fl | 0x80000000u : fl };
            static const u8 ord4[4] = { 1, 2, 0, 3 }, ord3[3] = { 0, 1, 2 };
            const u8 *ord = fv == 4 ? ord4 : ord3;
            i7 += 2;
            rq++;
            for (s = 0; s < ns; s++, i7 += fv) {
                for (j = 0; j < fv; j++, rq += 2) {
                    const u32 *ix = mem[(i7 + ord[j]) & (DATA_QW - 1)];
                    const u32 *pp = mem[(ix[0] + base) & (DATA_QW - 1)];
                    u32 ni = (ix[1] + base - nv0) & 0xFFFF, rgba;
                    if (ni >= nnorm) ni = 0; /* (the files' colour index is always a normal: renderer-spec 2.5.1) */
                    rgba = c1 ? tab[ni] : ndg_rgba(lit[ni], ndg_fin(mem[(ix[3] + base) & (DATA_QW - 1)]));
#ifdef NDG_NEON
                    {
                        uint32x2_t st = vdup_n_u32(0);
                        if (tex) {
                            float32x2_t f = vreinterpret_f32_u32(vfin2(vld1_u32(mem[(ix[2] + base) & (DATA_QW - 1)])));
                            st = vfin2(vreinterpret_u32_f32(vadd_f32(f, vreinterpret_f32_u32(vld1_u32(sxy)))));
                        }
                        vst1q_u32(ob[rq], vsetq_lane_u32(fw[j], vld1q_u32(pp), 3));
                        vst1q_u32(ob[rq + 1], vcombine_u32(st, vcreate_u32(0x3F800000u | (unsigned long long)rgba << 32)));
                    }
#else
                    ob[rq][0] = pp[0];
                    ob[rq][1] = pp[1];
                    ob[rq][2] = pp[2];
                    ob[rq][3] = fw[j];
                    if (tex) {
                        const u32 *st = mem[(ix[2] + base) & (DATA_QW - 1)];
                        f32 sx, sy;
                        memcpy(&sx, &sxy[0], 4);
                        memcpy(&sy, &sxy[1], 4);
                        ob[rq + 1][0] = fo(fin(st[0]) + sx);
                        ob[rq + 1][1] = fo(fin(st[1]) + sy);
                    } else ob[rq + 1][0] = ob[rq + 1][1] = 0;
                    ob[rq + 1][2] = 0x3F800000u;
                    ob[rq + 1][3] = rgba;
#endif
                }
            }
            ob[rv][0] = tag[0];
            ob[rv][1] = (tag[1] & ~(7u << 15)) | 4u << 15; /* PRE PRIM as a TRISTRIP (natdraw.h's records) */
            ob[rv][2] = ns * fv;
            ob[rv][3] = 0;
            nrec++;
        }
    }
    if (nrec) ndg_flush(ob, nrec, rq);
    kh1_vu1_drawn++;
    kh1_vu1_nd_gum++;
    tpc = (c1 ? 0xc1 : 0xc6) & (MICRO_N - 1);
    return 1;
fail:
    kh1_vu1_nd_gum_fail++;
    return 0;
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
/* 2026-11-01: GPU skinning (natdraw.h KH1_NAT_SKIN; config natskin=1 / KH1_HOST_NATSKIN=1; 0, the default since the
 * first Vita A/B, sums every vertex with more than one bone here, as before): a two-bone vertex goes over as its two pre-weighted positions and matrices, which
 * the vertex shader sums, so only vertices with 3 or more bones are summed here, and a matrix is fin()'d only when one
 * of those (or the reference) uses it */
int kh1_vu1_nat_skin = 0; /* 2026-11-01: off by default after the first Vita A/B (docs/native-renderer.md) */
u32 kh1_vu1_nd13_gpu2; /* the two-bone vertices handed over for the GPU to sum */
static u32 nd13_have_f;
static void nd13_f_of(u32 id) {
    u32 r, c;
    if (nd13_have_f >> id & 1) return;
    for (c = 0; c < 4; c++)
        for (r = 0; r < 4; r++) nd13_f[id][c][r] = fin(nd_mat[id][c][r]);
    nd13_have_f |= 1u << id;
}
static void nd13_add(u32 id, const u32 (*m)[4], int skin) {
    memcpy(nd_mat[id], m, 64);
    nd13_have_f &= ~(1u << id);
    if (!skin) nd13_f_of(id); /* as before natskin: every matrix at once */
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
        nd13_f_of(id);
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
    nd13_f_of(id);
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
    const int skin = kh1_vu1_nat_skin != 0;
    const u32 vq = skin ? 3 : 2, cpu = skin ? 2 : 1; /* a vertex's payload qwords; bones above cpu are summed here */
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
    nd13_have_f = 0;
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
        nd_buf[rq][3] = (h[3] & 0xFFFF) | (skin ? KH1_NAT_SKIN : 0);
        rq++;
        i2 += 2;
        for (j = 0; j < nv; j++) {
            u32 nb = mem[i2 & (DATA_QW - 1)][3] & 0xFFFF, b, first = 0, second = 0, w1 = 0x3F800000u;
            const u32 *t;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
            float32x4_t acc = vdupq_n_f32(0.0f);
#endif
            f32 c[4] = { 0, 0, 0, 0 };
            if (!nb || nb > 8) return 0;
            if (rq + vq > ND_QW - KH1_NAT_MATS * 4) return 0;
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
                        nd13_add(nmat, (const u32 (*)[4])sl[2], skin);
                        pal[nmat] = at;
                        cur[2] = (s32)nmat++;
                    }
                    r = 2;
                } else
                    r = ix == 0 ? 0 : ix == 1 ? 1 : 2;
                if (cur[r] < 0) {
                    if (nmat == KH1_NAT_MATS) return 0;
                    nd13_add(nmat, (const u32 (*)[4])sl[r], skin);
                    pal[nmat] = ~0u;
                    cur[r] = (s32)nmat++;
                }
                if (!b) {
                    first = (u32)cur[r];
                    if (nb > cpu && nd13_ref < 0) { /* the run's reference matrix: the first summed vertex's first */
                        if (!nd13_invert(first)) return 0;
                        nd13_ref = (s32)first;
                    }
                }
                if (skin && nb <= 2) { /* 2026-11-01: the bone's pre-weighted position as it is, for the GPU's sum */
                    u32 *o = b ? nd_buf[rq + 2] : nd_buf[rq];
                    o[0] = p[0];
                    o[1] = p[1];
                    o[2] = p[2];
                    if (b) {
                        o[3] = p[3];
                        second = (u32)cur[r];
                    } else
                        w1 = p[3];
                } else if (nb == 1 && p[3] == 0x3F800000u) { /* weight 1 (most): the position as it is */
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
            if (nb > cpu) { /* c is already in the reference's space (Q_i): v = c, the position v.xyz / v.w */
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
            t = mem[i2 & (DATA_QW - 1)];
            i2++;
            nd_buf[rq + 1][0] = t[0];
            nd_buf[rq + 1][1] = t[1];
            nd_buf[rq + 1][2] = t[2];
            if (skin) { /* natdraw.h KH1_NAT_SKIN: (p1, mi1 | mi2 << 16), (stq, w1), p2 */
                if (nb == 2) kh1_vu1_nd13_gpu2++;
                else { /* one bone, or the sum here in the reference's space: no second */
                    second = first;
                    nd_buf[rq + 2][0] = nd_buf[rq + 2][1] = nd_buf[rq + 2][2] = nd_buf[rq + 2][3] = 0;
                }
                nd_buf[rq][3] = first | second << 16;
                nd_buf[rq + 1][3] = w1;
            } else {
                nd_buf[rq][3] = first;
                nd_buf[rq + 1][3] = 0;
            }
            rq += vq;
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
        u32 nv = nd_buf[q][2], par = nd_buf[q][3] & 0xFFFF, vq = nd_buf[q][3] & KH1_NAT_SKIN ? 3 : 2;
        q++;
        o++; /* the tag */
        for (j = 0; j < nv; j++, q += vq, o += 3) {
            const u32 *x = mem[(o + 2) & (DATA_QW - 1)], *v = nd_buf[q];
            f32 pos[3], ref[3], dx, dy, dz;
            pos[0] = fin(v[0]);
            pos[1] = fin(v[1]);
            pos[2] = fin(v[2]);
            if (vq == 3) { /* 2026-11-01: the skinned vertex: the vertex shader's sum M1 x p1 + M2 x p2, divided */
                const u32 *m1 = nd_mat[v[3] & 0xFFFF][0], *m2 = nd_mat[v[3] >> 16][0], *p2 = nd_buf[q + 2];
                f32 c[4], w1 = fin(nd_buf[q + 1][3]);
                u32 k2;
                for (k2 = 0; k2 < 4; k2++)
                    c[k2] = fin(m1[k2]) * pos[0] + fin(m1[4 + k2]) * pos[1] + fin(m1[8 + k2]) * pos[2] + fin(m1[12 + k2]) * w1 +
                            fin(m2[k2]) * fin(p2[0]) + fin(m2[4 + k2]) * fin(p2[1]) + fin(m2[8 + k2]) * fin(p2[2]) +
                            fin(m2[12 + k2]) * fin(p2[3]);
                ref[0] = c[0] / c[3];
                ref[1] = c[1] / c[3];
                ref[2] = c[2] / c[3];
            } else
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
        printf("kh1-vu1: natcheck P13: %u runs, %u vertices (%u summed here, %u two-bone by the GPU), %u drawn ones over 1/8 pixel off (worst %.2f "
               "sixteenths), %u z off; triangles drawn by both %u, by neither %u, the program only %u, native only %u\n",
               n13_runs, n13_verts, kh1_vu1_nd13_multi, kh1_vu1_nd13_gpu2, n13_far, n13_worst, n13_zfar, n13_both, n13_none, n13_vu, n13_nat);
    (void)n13_multi_far;
}
