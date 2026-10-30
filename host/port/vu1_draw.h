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

#define ND_QW 4096 /* a payload's qwords: VU1's data memory is 1024, a vertex 3 there and 2 here */
static u32 nd_buf[ND_QW][4];
static u32 nd_mat[KH1_NAT_MATS][4][4];

/* P18 from 007 (vu1_nat.h nat_18 is the arithmetic this replaces): 1 when handed over, 0 to run it */
static int nd_18(u32 pc) {
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
    nd_buf[0][0] = KH1_NAT_MAGIC | 18;
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
