/* host/port/vu1.c's VIF1 data path (session 141): the block reader (kh1_vif1_data_n, the decode-then-write
 * UNPACK) against the word-at-a-time reader it replaced (kept below as ref_*, verbatim), on random streams of
 * STCYCL / STMOD / STMASK / STROW / STCOL / BASE / OFFSET / UNPACK (every format, masks, USN, TOPS-relative,
 * filling and skipping writes) / MPG, the data handed over in random runs.  VU1 memory, micro memory, the row
 * and the counts must come out the same.  No game data.  With an argument N, also times N passes of a
 * mesh-like stream both ways (the speed's yardstick; tests/selftest.sh runs without one). */
#include <time.h>
#include "common.h"
#include "../../host/port/vu1.c"

int atoi(const char *);

unsigned long kh1_host_frame(void) { return 0; }

/* ------------------------------------------------------------------ the old reader, verbatim */

/* element e (of size bits) of the data words */
static u32 ref_elem(u32 e, u32 bits, int usn, u32 nwords) {
    u32 bit = e * bits, w = bit >> 5, v;
    if (w >= nwords) return 0;
    v = dbuf[w] >> (bit & 31);
    if (bits == 32) return v;
    v &= (1u << bits) - 1;
    if (!usn && v >> (bits - 1) & 1) v |= ~((1u << bits) - 1);
    return v;
}

static void ref_unpack(void) {
    u32 cmd = cur, vn = cmd >> 2 & 3, vl = cmd & 3, m = cmd & 0x10;
    u32 num = cur_num ? cur_num : 256, usn = cur_imm >> 14 & 1;
    u32 addr = (cur_imm & 0x3FF) + (cur_imm & 0x8000 ? tops : 0);
    u32 ebits = vl == 3 ? 16 : 32 >> vl, nel = vl == 3 ? 1 : vn + 1, cycle = 0, di = 0, i, f;
    st.unpacks++;
    for (i = 0; i < num; i++) {
        u32 v[4], r = cycle < 3 ? cycle : 3;
        int fill = wl > cl && cycle >= cl;
        if (!fill) {
            u32 e0 = di * nel;
            if (vl == 3) { /* V4-5: RGBA 5551 */
                u32 h = ref_elem(e0, 16, 1, got);
                v[0] = (h & 31) << 3;
                v[1] = (h >> 5 & 31) << 3;
                v[2] = (h >> 10 & 31) << 3;
                v[3] = (h >> 15 & 1) << 7;
            } else if (vn == 0) {
                v[0] = v[1] = v[2] = v[3] = ref_elem(e0, ebits, usn, got);
            } else if (vn == 1) { /* V2: z and w repeat x and y (PCSX2's unpack) */
                v[0] = v[2] = ref_elem(e0, ebits, usn, got);
                v[1] = v[3] = ref_elem(e0 + 1, ebits, usn, got);
            } else {
                v[0] = ref_elem(e0, ebits, usn, got);
                v[1] = ref_elem(e0 + 1, ebits, usn, got);
                v[2] = ref_elem(e0 + 2, ebits, usn, got);
                v[3] = ref_elem(e0 + 3, ebits, usn, got); /* V3: w is the next element in the stream */
            }
            di++;
        } else {
            st.fill++;
            v[0] = v[1] = v[2] = v[3] = 0;
        }
        for (f = 0; f < 4; f++) {
            u32 mb = m ? mask >> (r * 8 + f * 2) & 3 : 0, *d = &mem[addr & (DATA_QW - 1)][f];
            if (fill && !mb) mb = 1;
            if (mb == 0) {
                if (mode == 1) *d = v[f] + row[f];
                else if (mode == 2) { row[f] += v[f]; *d = row[f]; }
                else *d = v[f];
            } else if (mb == 1) *d = row[f];
            else if (mb == 2) *d = col[r];
        }
        addr++;
        cycle++;
        if (cl >= wl) {
            if (cycle == wl) { addr += cl - wl; cycle = 0; }
        } else if (cycle == wl) cycle = 0;
    }
}


static void ref_data(u32 w) {
    if (!need) return;
    need--;
    switch (cur) {
    case 0x20: mask = w; return;
    case 0x30: row[got++ & 3] = w; return;
    case 0x31: col[got++ & 3] = w; return;
    case 0x4A: {
        u32 k = got++, a = (cur_imm + k / 2) & (MICRO_N - 1);
        if (micro[a][k & 1] != w) {
            micro[a][k & 1] = w;
            mpg_changed = 1;
            micro_gen++;
        }
        if (!need && mpg_changed) { st.mpg++; mpg_changed = 0; }
        return;
    }
    case 0x50: case 0x51: return;
    }
    if ((cur & 0x60) == 0x60) {
        if (got < sizeof dbuf / 4) dbuf[got] = w;
        got++;
        if (!need) ref_unpack();
    }
}

/* ------------------------------------------------------------------ the streams */

static u32 rs = 12345;
static u32 rnd(void) {
    rs ^= rs << 13;
    rs ^= rs >> 17;
    rs ^= rs << 5;
    return rs;
}

#define STREAM 200000
static u32 sw[STREAM], sdata[STREAM]; /* each word; 1 where it is a code's data */
static u32 sn;

static void put(u32 w, u32 data) {
    if (sn < STREAM) { sw[sn] = w; sdata[sn++] = data; }
}

/* the data words of an UNPACK cmd of num vectors under cl / wl (unpack_data_words's rule, independently) */
static u32 words_for(u32 cmd, u32 num, u32 c, u32 w) {
    u32 vn = cmd >> 2 & 3, vl = cmd & 3, bits = vl == 3 ? 16 : (32 >> vl) * (vn + 1), n = num, i, cyc = 0;
    if (w > c && w) {
        n = 0;
        for (i = 0; i < num; i++) {
            if (cyc < c) n++;
            if (++cyc == w) cyc = 0;
        }
    }
    return (n * bits + 31) / 32;
}

static void make_stream(int mesh) {
    u32 c = 1, w = 1, i, k;
    sn = 0;
    while (sn < STREAM - 1200) {
        u32 pick = mesh ? 6 : rnd() % 12;
        switch (pick) {
        case 0: c = rnd() % 5; w = rnd() % 5; if (rnd() & 1) { c = 1; w = 1; } put(0x01000000 | w << 8 | c, 0); break;
        case 1: put(0x05000000 | (rnd() & 3), 0); break;
        case 2: put(0x20000000, 0); put(rnd(), 1); break;
        case 3: case 4: put((pick == 3 ? 0x30 : 0x31) << 24, 0); for (k = 0; k < 4; k++) put(rnd(), 1); break;
        case 5: put(rnd() & 1 ? 0x03000000 | (rnd() & 0x3FF) : 0x02000000 | (rnd() & 0x3FF), 0); break;
        case 7: { /* MPG: a few instructions, sometimes the same again */
            u32 n = 1 + rnd() % 8, at = rnd() % 64, same = rnd() & 1, x = rnd();
            put(0x4A000000 | n << 16 | at, 0);
            for (k = 0; k < n * 2; k++) put(same ? x + k : rnd(), 1);
            break;
        }
        default: { /* UNPACK */
            u32 fmt, cmd, num, n;
            static const u8 fmts[] = { 0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14, 15 };
            if (mesh) { /* the meshes' kind: V4-32 / V3-32 / V2-16 / V4-8, mostly unmasked */
                static const u8 mf[] = { 12, 8, 5, 14 };
                fmt = mf[rnd() % 4];
                cmd = 0x60 | fmt | ((rnd() % 8) == 0 ? 0x10 : 0);
                num = 20 + rnd() % 60;
            } else {
                fmt = fmts[rnd() % sizeof fmts];
                cmd = 0x60 | fmt | (rnd() & 0x10);
                num = rnd() % 4 == 0 ? 0 : 1 + rnd() % (rnd() & 1 ? 8 : 256);
            }
            put(cmd << 24 | num << 16 | (rnd() & 0xC000) | (rnd() & 0x3FF), 0);
            n = words_for(cmd, num ? num : 256, c, w);
            for (k = 0; k < n; k++) put(rnd(), 1);
            break;
        }
        }
    }
    (void)i;
}

/* ------------------------------------------------------------------ the two runs */

typedef struct {
    u32 mem[DATA_QW][4], micro[MICRO_N][2], row[4], col[4], mask, gen;
    KH1Vu1Stats st;
} Out;
static Out out_ref, out_new;

static void feed_start(void) {
    kh1_vif1_reset();
    micro_gen = 0;
    mpg_changed = 0;
    memset(&st, 0, sizeof st);
}

static void finish(Out *o) {
    memcpy(o->mem, mem, sizeof mem);
    memcpy(o->micro, micro, sizeof micro);
    memcpy(o->row, row, sizeof row);
    memcpy(o->col, col, sizeof col);
    o->mask = mask;
    o->gen = micro_gen;
    o->st = st;
}

static void run_ref(void) {
    u32 i;
    for (i = 0; i < sn; i++)
        if (sdata[i]) ref_data(sw[i]);
        else kh1_vif1_code(sw[i]);
}

/* the new reader the way host/null/dmawalk.c hands it over: a code, then its data in runs that end where
 * a DMA block would (random lengths) */
static void run_new(int chunks) {
    u32 i = 0;
    while (i < sn) {
        if (!sdata[i]) {
            kh1_vif1_code(sw[i++]);
            continue;
        }
        {
            u32 e = i;
            while (e < sn && sdata[e]) e++;
            while (i < e) {
                u32 k = e - i;
                if (chunks && k > 1) k = 1 + rnd() % k;
                kh1_vif1_data_n(sw + i, k);
                i += k;
            }
        }
    }
}

static int compare(const char *what) {
    const Out *a = &out_ref, *b = &out_new;
    if (memcmp(a->mem, b->mem, sizeof a->mem)) { printf("vu1feed_test: %s: VU1 memory differs\n", what); return 1; }
    if (memcmp(a->micro, b->micro, sizeof a->micro)) { printf("vu1feed_test: %s: micro memory differs\n", what); return 1; }
    if (memcmp(a->row, b->row, 16) || memcmp(a->col, b->col, 16) || a->mask != b->mask) {
        printf("vu1feed_test: %s: ROW / COL / MASK differ\n", what);
        return 1;
    }
    if (a->gen != b->gen || a->st.unpacks != b->st.unpacks || a->st.fill != b->st.fill || a->st.mpg != b->st.mpg) {
        printf("vu1feed_test: %s: counts differ (unpacks %u / %u, fill %u / %u, mpg %u / %u, gen %u / %u)\n", what,
               a->st.unpacks, b->st.unpacks, a->st.fill, b->st.fill, a->st.mpg, b->st.mpg, a->gen, b->gen);
        return 1;
    }
    return 0;
}

static double now(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main(int argc, char **argv) {
    int pass, fails = 0;
    u32 unpacks = 0, fills = 0;
    for (pass = 0; pass < 40; pass++) {
        u32 seed;
        make_stream(pass % 4 == 3);
        seed = rs;
        feed_start();
        run_ref();
        finish(&out_ref);
        feed_start();
        run_new(pass & 1);
        finish(&out_new);
        rs = seed;
        if (compare(pass % 4 == 3 ? "mesh stream" : "random stream")) { fails++; break; }
        unpacks += out_ref.st.unpacks;
        fills += out_ref.st.fill;
    }
    if (argc > 1) {
        int n = atoi(argv[1]), k;
        double t0, t1, t2;
        make_stream(1);
        feed_start();
        t0 = now();
        for (k = 0; k < n; k++) run_ref();
        t1 = now();
        feed_start();
        for (k = 0; k < n; k++) run_new(0);
        t2 = now();
        printf("vu1feed_test: mesh stream x %d (%u words): word at a time %.1f ns a word, blocks %.1f ns a word\n", n, sn,
               (t1 - t0) * 1e9 / ((double)n * sn), (t2 - t1) * 1e9 / ((double)n * sn));
    }
    if (fails) return 1;
    printf("vu1feed_test: 40 streams (%u UNPACKs, %u filling writes) the same both ways\n", unpacks, fills);
    return 0;
}
