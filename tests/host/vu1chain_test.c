/* natchain (docs/native-plan.md "Records straight from the chain"; host/port/vu1.c nc_*, vu1_draw.h): random VIF1 streams
 * of renderer B packets (P18, P11, P10: STCYCL 1,1; UNPACK V4-32 +TOPS; MSCAL) and renderer A batches (P0, P4: the tag,
 * STCYCL 3,1, V4-32 / V4-8 / V2-16 or V4-16 +TOPS), with the cases the chain reader must give back to VU memory (a
 * stream longer than its unpack, two unpacks, a vertex w not 1, a missing or extra role, STMOD 1, other unpacks, a send
 * ending with unpacks held), fed through the real VIF1 code path with natchain 0, 1, 2 and 3.  The payloads handed over
 * (through the pool's room or kh1_vu1_draw), what each program run reads of its input, the slot registers and tpc must
 * be the same every way; VU memory too, except where natchain 1 dropped an unpack (natchain 2 poisons exactly those
 * words, and 3 must find no payload that differs).  The programs are tests/host/vu1chain/vu1_tr.c's stand-ins.  No game
 * data. */
#include "common.h"
#include "../../host/port/vu1.c"

unsigned long kh1_host_frame(void) { return 0; }
void kh1_nat_ref_xyz(const u32 *m, const f32 *pos, f32 out[3]) { out[0] = out[1] = out[2] = 0; } /* (KH1_HOST_NATCHECK only) */

static u32 rs = 12345;
static u32 rnd(void) {
    rs = rs * 1103515245u + 12345u;
    return rs >> 8;
}
static u32 rnd2(void) { /* 32 random bits (the two calls in order) */
    u32 a = rnd();
    return a | (rnd() & 1) << 31;
}
static u32 rf(void) { /* a float in [-2, 2) */
    Fu f;
    f.f = ((s32)(rnd() & 0xFFFF) - 32768) / 16384.0f;
    return f.u;
}

/* the stream: VIF codes, data runs (pointers into words[], which stay put as a send's words do), send ends, the
 * length a program run reads, and register set-ups */
enum { OP_CODE, OP_DATA, OP_END, OP_LEN, OP_VF };
static struct { u32 op, a, b; } ops[200000];
static u32 nops, words[2000000], nw;
static void op(u32 o, u32 a, u32 b) {
    ops[nops].op = o;
    ops[nops].a = a;
    ops[nops].b = b;
    nops++;
}
static void code(u32 w) { op(OP_CODE, w, 0); }
static u32 *data(u32 n) { /* n words, handed over in one run (or two, sometimes) */
    u32 *p = words + nw;
    if (n > 8 && rnd() % 16 == 0) {
        u32 k = 1 + rnd() % (n - 1);
        op(OP_DATA, nw, k);
        op(OP_DATA, nw + k, n - k);
    } else op(OP_DATA, nw, n);
    nw += n;
    return p;
}
static void mpg(int prog) {
    u32 *p;
    code(0x4A000000u | 1 << 16); /* MPG 1 instruction at 0 */
    p = data(2);
    p[0] = fk_w[prog][0];
    p[1] = fk_w[prog][1];
}
static void unpack_code(u32 cmd, u32 num, u32 addr, int tops_rel, int usn) {
    code((cmd << 24) | (num & 0xFF) << 16 | (tops_rel ? 0x8000 : 0) | (usn ? 0x4000 : 0) | (addr & 0x3FF));
}

/* renderer B: records for P18 / P11 (matrix records 8 qwords) or P10 (5), op 1 groups, the end record */
static u32 b_records(u32 (*q)[4], int p10, u32 maxq) {
    u32 n = 0, g, j, k, groups = 1 + rnd() % 4;
    for (g = 0; g < groups; g++) {
        if (rnd() % 3 == 0 && n + 8 < maxq) { /* a matrix record */
            q[n][0] = 0;
            q[n][1] = rnd() & 0xFF;
            q[n][2] = rnd() % 3;
            q[n][3] = 0;
            for (j = 1; j < (p10 ? 5u : 8u); j++)
                for (k = 0; k < 4; k++) q[n + j][k] = rf();
            n += p10 ? 5 : 8;
        }
        {
            u32 nv = 3 + rnd() % 12, vq = p10 ? 1 : 3;
            if (n + 2 + nv * vq + 1 >= maxq) break;
            q[n][0] = 1;
            q[n][1] = 0;
            q[n][2] = nv;
            q[n][3] = rnd() & 1;
            q[n + 1][0] = 0x8000 | nv;
            q[n + 1][1] = 0x30000000u | (rnd() & 0xFFFF);
            q[n + 1][2] = 0x412;
            q[n + 1][3] = 0;
            n += 2;
            for (j = 0; j < nv; j++) {
                if (p10) {
                    for (k = 0; k < 3; k++) q[n][k] = rf();
                    q[n][3] = rnd() % 3;
                    n++;
                    continue;
                }
                q[n][0] = q[n][1] = q[n][2] = 0;
                q[n][3] = rnd() % 3; /* the slot */
                for (k = 0; k < 3; k++) q[n + 1][k] = rf();
                q[n + 1][3] = rnd() % 200 ? 0x3F800000u : rf(); /* w 1, once in a while not (the program then) */
                for (k = 0; k < 4; k++) q[n + 2][k] = rnd();
                n += 3;
            }
        }
    }
    q[n][0] = 0x8000;
    q[n][1] = q[n][2] = q[n][3] = 0;
    return n + 1;
}
static void b_packet(int prog) {
    static u32 rec[300][4];
    int p10 = prog == 2;
    u32 n = b_records(rec, p10, 250), k = rnd() % 10, cut, *p;
    code(0x01000101u); /* STCYCL 1,1 */
    if (k == 0 && n > 4) { /* the stream's tail unpacked first, at once (STMOD 1 with a ROW): the head held, too short */
        cut = 1 + rnd() % (n - 2);
        u32 *rw, j;
        code(0x30000000u); /* STROW */
        rw = data(4);
        rw[0] = rnd(); rw[1] = rnd(); rw[2] = rnd(); rw[3] = rnd();
        code(0x05000001u); /* STMOD 1 */
        unpack_code(0x6C, n - cut, cut, 1, 0);
        p = data((n - cut) * 4);
        for (j = 0; j < (n - cut) * 4; j++) p[j] = rec[cut + j / 4][j & 3] - rw[j & 3]; /* the records once ROW is added */
        code(0x05000000u);
        unpack_code(0x6C, cut, 0, 1, 0);
        p = data(cut * 4);
        memcpy(p, rec, cut * 16);
    } else if (k == 1 && n > 4) { /* two held unpacks: VU memory */
        cut = 1 + rnd() % (n - 2);
        unpack_code(0x6C, cut, 0, 1, 0);
        p = data(cut * 4);
        memcpy(p, rec, cut * 16);
        unpack_code(0x6C, n - cut, cut, 1, 0);
        p = data((n - cut) * 4);
        memcpy(p, rec[cut], (n - cut) * 16);
    } else { /* the usual packet */
        unpack_code(0x6C, n, 0, 1, 0);
        p = data(n * 4);
        memcpy(p, rec, n * 16);
    }
    op(OP_LEN, n, 0);
    code(0x14000000u | (p10 ? 6 : 7)); /* MSCAL */
}
/* renderer A: one batch of P0 / P4 */
static void a_batch(int p4) {
    u32 nv = 3 + rnd() % 60, j, k, *p, kind = rnd() % 12, fmt3 = rnd() & 1 ? 0x65 : 0x6D, cu = rnd() % 4 != 0,
        tu = rnd() % 4 == 0;
    code(0x01000101u);
    { /* the tag (kind 0: written at once, STMOD 1 with a ROW) */
        u32 rw[4] = { 0, 0, 0, 0 }, *r;
        if (kind == 0) {
            code(0x30000000u);
            r = data(4);
            for (k = 0; k < 4; k++) r[k] = rw[k] = rnd();
            code(0x05000001u);
        }
        unpack_code(0x6C, 1, 0, 1, 0);
        p = data(4);
        p[0] = (0x8000 | nv) - rw[0]; /* the tag once ROW is added */
        p[1] = (0x30000000u | (rnd() & 0xFFFF)) - rw[1];
        p[2] = 0x412 - rw[2];
        p[3] = (0x31000000u | (rnd() & 0xFFFF)) - rw[3];
        if (kind == 0) code(0x05000000u);
    }
    code(0x01000103u); /* STCYCL 3,1 */
    unpack_code(0x6C, nv, 1, 1, 0);
    p = data(nv * 4);
    for (j = 0; j < nv; j++) {
        for (k = 0; k < 3; k++) p[j * 4 + k] = rf();
        p[j * 4 + 3] = rnd() % 3 == 0 ? 0 : rnd() & 1 ? 0x20 : 0x02;
    }
    { /* the colours (kind 1: twice, both held; kind 2: STMOD 1 with a ROW) */
        u32 times = kind == 1 ? 2 : 1;
        if (kind == 2) {
            code(0x30000000u);
            p = data(4);
            p[0] = rnd(); p[1] = rnd(); p[2] = rnd(); p[3] = rnd();
            code(0x05000001u);
        }
        while (times--) {
            unpack_code(0x6E, nv, 2, 1, cu);
            p = data(nv);
            for (j = 0; j < nv; j++) p[j] = rnd2();
        }
        if (kind == 2) code(0x05000000u);
    }
    unpack_code(fmt3, nv, 3, 1, tu);
    p = data(fmt3 == 0x65 ? nv : nv * 2);
    for (j = 0; j < (fmt3 == 0x65 ? nv : nv * 2); j++) p[j] = rnd2();
    if (kind == 3) { /* an extra unpack held */
        unpack_code(0x6C, 1, 200, 1, 0);
        p = data(4);
        p[0] = p[1] = p[2] = p[3] = rnd();
    }
    op(OP_LEN, 1 + nv * 3, 0);
    code(0x14000000u | (kind == 4 ? (p4 ? 0x45 : 0x4e) : 0xc)); /* kind 4: the idle PC */
}
static void make_stream(void) {
    u32 i, n = 3000;
    nops = nw = 0;
    code(0x03000040u); /* BASE 64 */
    code(0x020000F0u); /* OFFSET 240 */
    for (i = 0; i < n; i++) {
        u32 k = rnd() % 16;
        if (k < 7) {
            int prog = rnd() % 3; /* P18, P11, P10 */
            u32 pk, np = 1 + rnd() % 3;
            if (rnd() % 4 == 0) op(OP_VF, 0, 0);
            mpg(prog);
            for (pk = 0; pk < np; pk++) b_packet(prog);
        } else if (k < 14) {
            int p4 = rnd() % 4 == 0;
            if (rnd() % 4 == 0) op(OP_VF, 0, 0);
            mpg(p4 ? 4 : 3);
            a_batch(p4);
        } else if (k == 14) { /* other unpacks: V3-32 at once, V4-32 anywhere (held when +TOPS) */
            u32 *p, j, c = rnd() % 2 ? 0x6C : 0x68, num = 1 + rnd() % 20;
            u32 at = rnd() % 1024, rel = rnd() & 1;
            unpack_code(c, num, at, rel, 0);
            p = data(c == 0x6C ? num * 4 : num * 3);
            for (j = 0; j < (c == 0x6C ? num * 4 : num * 3); j++) p[j] = rnd();
        } else { /* a held unpack left at the send's end */
            u32 *p, j, num = 1 + rnd() % 20;
            code(0x01000101u);
            unpack_code(0x6C, num, rnd() % 512, 1, 0);
            p = data(num * 4);
            for (j = 0; j < num * 4; j++) p[j] = rnd();
        }
        if (rnd() % 3 == 0) op(OP_END, 0, 0);
    }
    op(OP_END, 0, 0);
}

/* what the runs give: an event hash and count, the payloads by kind of hand-off */
static u32 ev_hash, ev_n, ev_pool, ev_copy, ev_runs, run_len, vfseed;
static void ev(const void *b, u32 n) {
    const u8 *c = (const u8 *)b;
    u32 i;
    for (i = 0; i < n; i++) ev_hash = (ev_hash ^ c[i]) * 16777619u;
    ev_n++;
}
static int fk_run(u32 pc) { /* a program: what it reads, its input (as long as the stream said) and the registers */
    u32 k;
    ev(&pc, 4);
    for (k = 0; k < run_len; k++) ev(mem[(top + k) & (DATA_QW - 1)], 16);
    ev(vf, sizeof vf);
    ev_runs++;
    tpc = pc;
    return 1;
}
static void draw(const u32 *q, u32 nqw) {
    ev(q, nqw * 16);
    ev(vf, sizeof vf);
    ev_copy++;
}
static u32 pool_buf[4096 + 16][4];
static int use_room;
static u32 *room(u32 maxqw) { return use_room && maxqw <= 4096 ? pool_buf[rnd() % 16] : 0; }
static u32 *room_at;
static u32 *room_rec(u32 maxqw) { return room_at = room(maxqw); }
static void take(u32 nqw) {
    ev(room_at, nqw * 16);
    ev(vf, sizeof vf);
    ev_pool++;
}

static u32 mem_out[DATA_QW][4];
static u32 run_mode(int mode, int rooms) {
    u32 i, s = vfseed;
    kh1_vif1_reset();
    kh1_vu1_natchain = mode;
    kh1_vu1_nc_runs = kh1_vu1_nc_flushed = kh1_vu1_nc_qw = kh1_vu1_nc_bad = 0;
    ev_hash = 2166136261u;
    ev_n = ev_pool = ev_copy = ev_runs = 0;
    use_room = rooms;
    tr_gen = ~0u;
    for (i = 0; i < nops; i++) {
        switch (ops[i].op) {
        case OP_CODE: kh1_vif1_code(ops[i].a); break;
        case OP_DATA: kh1_vif1_data_n(words + ops[i].a, ops[i].b); break;
        case OP_END: kh1_vif1_end(); break;
        case OP_LEN: run_len = ops[i].a; break;
        case OP_VF: { /* the registers a parse reads (the same in every mode) */
            u32 r, k, keep = rs;
            rs = s;
            for (r = 1; r < 32; r++)
                for (k = 0; k < 4; k++) vf[r][k] = rf();
            vi[12] = (u16)rnd();
            vi[13] = (u16)rnd();
            i_reg = rf();
            s = rs;
            rs = keep;
            break;
        }
        }
    }
    memcpy(mem_out, mem, sizeof mem);
    return ev_hash;
}

int main(void) {
    static u32 m0[DATA_QW][4];
    u32 h0, h, pass, fails = 0, poisoned = 0;
    kh1_vu1_native = 0; /* the stand-in programs run, not vu1_nat.h's */
    kh1_vu1_draw = draw;
    kh1_vu1_draw_room = room_rec;
    kh1_vu1_draw_take = take;
    for (pass = 0; pass < 6; pass++) {
        u32 n0, r0, runs1 = 0, flushed1 = 0, pool1 = 0, a, f;
        rs = 777 + pass * 31;
        make_stream();
        vfseed = rnd();
        h0 = run_mode(0, 0);
        n0 = ev_n;
        r0 = ev_runs;
        memcpy(m0, mem_out, sizeof m0);
        for (a = 1; a <= 3; a++) {
            int rooms = a == 1 ? (int)(pass & 1) : 1;
            u32 seed = rs;
            h = run_mode((int)a, rooms);
            rs = seed;
            if (h != h0 || ev_n != n0 || ev_runs != r0) {
                printf("vu1chain_test: pass %u natchain=%u: events %08x (%u, %u runs) against natchain=0's %08x (%u, %u runs)\n",
                       pass, a, h, ev_n, ev_runs, h0, n0, r0);
                fails++;
            }
            if (a == 1) {
                runs1 = kh1_vu1_nc_runs;
                flushed1 = kh1_vu1_nc_flushed;
                pool1 = ev_pool;
            }
            if (a == 3 && (kh1_vu1_nc_bad || memcmp(mem_out, m0, sizeof m0))) {
                printf("vu1chain_test: pass %u natchain=3: %u payloads differ%s\n", pass, kh1_vu1_nc_bad,
                       memcmp(mem_out, m0, sizeof m0) ? ", VU memory differs" : "");
                fails++;
            }
            if (a == 2) /* every word that differs from natchain=0's is poison */
                for (f = 0; f < DATA_QW * 4; f++) {
                    u32 w = mem_out[f >> 2][f & 3];
                    if (w == m0[f >> 2][f & 3]) continue;
                    if (w != (0xBAD00000u | (f >> 2) << 2 | (f & 3))) {
                        if (!fails++) printf("vu1chain_test: pass %u natchain=2: VU qword %03x word %u is %08x, not poison\n",
                                             pass, f >> 2, f & 3, w);
                    } else poisoned++;
                }
        }
        if (!runs1 || !flushed1 || ((pass & 1) && !pool1)) {
            printf("vu1chain_test: pass %u: the cases did not happen (%u from the chain, %u written late, %u pooled)\n", pass,
                   runs1, flushed1, pool1);
            fails++;
        }
        if (pass == 0)
            printf("vu1chain_test: %u events, %u program runs; natchain=1: %u runs from the chain, %u unpacks written late\n",
                   n0, r0, runs1, flushed1);
    }
    if (fails) {
        printf("vu1chain_test: FAILED (%u)\n", fails);
        return 1;
    }
    printf("vu1chain_test: ok (6 streams, natchain 0-3 the same; %u words poisoned, none read)\n", poisoned);
    return 0;
}
