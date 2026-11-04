/* vu1_nat.h's hand-written programs against the translation, on runs dumped from a real run of the game
 * (KH1_HOST_VU1DUMP=DIR:N, host/port/vu1.c dump_run: micro memory, a TrSnap, the pc).  Each dump's run goes
 * through vu1.c's nat_check: the native form, then the translation from the same state, every register, flag,
 * VU memory word, the pair and cycle counts and the kicks' hash compared.  Prints a line per program: runs,
 * native runs (the rest given up to the translation), differences.
 *
 *   arm-linux-gnueabihf-gcc ... -DKH1_HOST -DKH1_VU1_TR -Iout/gen -Iinclude tests/host/vu1nat_replay.c -lm
 *   qemu-arm ./vu1nat_replay [-p NUM] dump/vu*.bin
 *
 * Needs out/gen/vu1_tr.c (the user's own programs as C) and the dumps (their data): both stay out of the
 * repository.  Meaningful on ARM with NEON; elsewhere vu1_nat.h has no programs and every run is given up. */
#include "common.h"
#include "../../host/port/vu1.c"
#include "../../host/port/natdraw.c"
float kh1_depth_f32(u32 z, u32 psm) { return (float)z * (float)psm; }
unsigned long kh1_host_frame(void) { return 0; }
int printf(const char *, ...);
__SIZE_TYPE__ fread(void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int strcmp(const char *, const char *);
int atoi(const char *);

static TrSnap snap;
static u32 runs[200], nat[200], bad[200];
/* -s: the translation alone, and for the Gummi programs (P100 / P101) the path each batch took: culled whole,
 * no position outside the clip box (vf29.z 0x0fa / 0x0ed), or the clipping entry (0x11e / 0x111), and of those
 * how many reached the polygon clipper (bal 0x290 leaves its return in vf25.w) */
static u32 path[200][4], pairs[200][4];
static void stats(int prog, int num, u32 pc) {
    u32 n0 = st.insns, k;
    vf[25][3] = 0xDEAD;
    vf[29][2] = 0xDEAD;
    tr_progs[prog].run(pc);
    if (num >= 200) return;
    k = vf[29][2] == 0xDEAD ? 0 : (vf[29][2] == 0xfa || vf[29][2] == 0xed) ? 1 : vf[25][3] == 0xDEAD ? 2 : 3;
    path[num][k]++;
    pairs[num][k] += st.insns - n0;
}

/* -v: each difference in full (the first field that differs, both values; the pair and cycle counts) */
static int verbose;
static TrSnap ra, rb;
static void detail(int prog, u32 pc, const char *name) {
    int (*f)(u32) = nat_run(tr_progs[prog].num);
    void (*out)(const u32 *, u32) = kh1_vu1_kick;
    KH1Vu1Stats keep = st;
    u32 ni, nc, ti, tc, i, k, n = 0, hn, ht;
    tr_load(&snap);
    top = snap.r[8];
    itop = snap.r[9];
    kh1_vu1_kick = tr_hash_kick;
    tr_out = 0;
    tr_hash = 2166136261u;
    f(pc);
    hn = tr_hash;
    tr_save(&ra);
    ni = st.insns - keep.insns; nc = st.cycles - keep.cycles;
    st = keep;
    tr_load(&snap);
    top = snap.r[8];
    itop = snap.r[9];
    tr_hash = 2166136261u;
#ifdef GST
    memset(gst, 0, sizeof gst);
#endif
    tr_progs[prog].run(pc);
    ht = tr_hash;
#ifdef GST
    for (i = 0; i < 0x800; i++) if (gst[i]) printf("  stall %03x: %u\n", i, gst[i]);
#endif
    tr_save(&rb);
    ti = st.insns - keep.insns; tc = st.cycles - keep.cycles;
    st = keep;
    kh1_vu1_kick = out;
    printf("%s from %03x: pairs %u / %u, cycles %u / %u, kicks %08x / %08x\n", name, pc, ni, ti, nc, tc, hn, ht);
    for (i = 0; i < 10; i++) if (ra.r[i] != rb.r[i] && n++ < 12) printf("  r%u %08x / %08x\n", i, ra.r[i], rb.r[i]);
    for (i = 0; i < 16; i++) if (ra.vi[i] != rb.vi[i] && n++ < 12) printf("  vi%02u %04x / %04x\n", i, ra.vi[i], rb.vi[i]);
    for (i = 0; i < 32; i++)
        for (k = 0; k < 4; k++) if (ra.vf[i][k] != rb.vf[i][k] && n++ < 12) printf("  vf%02u%c %08x / %08x\n", i, "xyzw"[k], ra.vf[i][k], rb.vf[i][k]);
    for (k = 0; k < 4; k++) if (ra.acc[k] != rb.acc[k] && n++ < 12) printf("  acc%c %08x / %08x\n", "xyzw"[k], ra.acc[k], rb.acc[k]);
    for (i = 0; i < DATA_QW; i++)
        for (k = 0; k < 4; k++) if (ra.mem[i][k] != rb.mem[i][k] && n++ < 12) printf("  mem %03x%c %08x / %08x\n", i, "xyzw"[k], ra.mem[i][k], rb.mem[i][k]);
}

/* -t: the time of each form, the state put back before every repeat (qemu-arm's time: a guide only) */
struct timespec { long tv_sec, tv_nsec; };
int clock_gettime(int, struct timespec *);
static double now(void) {
    struct timespec t;
    clock_gettime(1, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}
static int timing;
static double t_nat[200], t_tr[200];
static void timed(int prog, int num, u32 pc) {
    int (*f)(u32) = nat_run(num);
    void (*out)(const u32 *, u32) = kh1_vu1_kick;
    int r, ok = 1;
    double t0;
    kh1_vu1_kick = 0;
    t0 = now();
    for (r = 0; r < 20 && f; r++) {
        tr_load(&snap); top = snap.r[8]; itop = snap.r[9];
        ok = f(pc);
        if (!ok) break;
    }
    if (f && ok) {
        t_nat[num] += now() - t0;
        t0 = now();
        for (r = 0; r < 20; r++) {
            tr_load(&snap); top = snap.r[8]; itop = snap.r[9];
            tr_progs[prog].run(pc);
        }
        t_tr[num] += now() - t0;
        nat[num]++;
    }
    kh1_vu1_kick = out;
}

int main(int argc, char **argv) {
    int i, only = -1, sonly = 0;
    u32 total = 0;
    for (i = 1; i < argc; i++) {
        void *f;
        u32 pc;
        int prog, num;
        u32 b0;
        if (!strcmp(argv[i], "-p") && i + 1 < argc) {
            only = atoi(argv[++i]);
            continue;
        }
        if (!strcmp(argv[i], "-v")) {
            verbose = 1;
            continue;
        }
        if (!strcmp(argv[i], "-t")) {
            timing = 1;
            continue;
        }
        if (!strcmp(argv[i], "-s")) {
            sonly = 1;
            continue;
        }
        f = fopen(argv[i], "rb");
        if (!f) continue;
        if (fread(micro, sizeof micro, 1, f) != 1 || fread(&snap, sizeof snap, 1, f) != 1 || fread(&pc, sizeof pc, 1, f) != 1) {
            fclose(f);
            continue;
        }
        fclose(f);
        micro_gen++;
        prog = tr_find();
        if (prog < 0) continue;
        num = tr_progs[prog].num;
        if (only >= 0 && num != only) continue;
        tr_load(&snap);
        top = snap.r[8];
        itop = snap.r[9];
        tr_bad = 1000;
        b0 = st.tr_differ;
        total++;
        if (num < 200) runs[num]++;
        if (timing) {
            if (num < 200) timed(prog, num, pc);
            continue;
        }
        if (sonly) {
            stats(prog, num, pc);
            continue;
        }
        if (nat_check(prog, pc)) {
            if (num < 200) nat[num]++;
            if (st.tr_differ != b0) {
                if (num < 200) bad[num]++;
                if (verbose && bad[num] <= 8) detail(prog, pc, argv[i]);
            }
        }
    }
    for (i = 0; i < 200; i++)
        if (runs[i]) printf("P%d: %u runs, %u native, %u differ\n", i, runs[i], nat[i], bad[i]);
    for (i = 0; i < 200; i++)
        if (sonly && path[i][0] + path[i][1] + path[i][2] + path[i][3])
            printf("P%d paths (runs / pairs): no batch / culled %u / %u, inside %u / %u, clip entry %u / %u, polygon clipper %u / %u\n", i,
                   path[i][0], pairs[i][0], path[i][1], pairs[i][1], path[i][2], pairs[i][2], path[i][3], pairs[i][3]);
    for (i = 0; i < 200; i++)
        if (timing && t_tr[i] > 0) printf("P%d: %u native runs, native %.3f s, translation %.3f s (%.0f%%)\n", i, nat[i], t_nat[i], t_tr[i], 100 * t_nat[i] / t_tr[i]);
    printf("%u runs replayed\n", total);
    return 0;
}
