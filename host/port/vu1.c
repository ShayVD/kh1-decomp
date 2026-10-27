/* VIF1 and VU1 for every port platform (include/platform/vu1.h, docs/vita-build.md "The 3D path").
 *
 * VIF1: the registers that live across sends (CYCLE, MODE, MASK, ROW, COL, BASE, OFST, TOPS, TOP,
 * ITOPS, ITOP, DBF) and the codes the game's chains use: UNPACK in every format (masks, the offset
 * and difference modes, skipping and filling writes, TOPS-relative addresses), MPG, the double
 * buffer's BASE / OFFSET, MSCAL / MSCALF / MSCNT.  DIRECT's data is PATH2, which the walk reads
 * itself, so it is only skipped here.
 *
 * VU1: an interpreter of the microprograms in micro memory, 16 KiB of data memory, 32 VF, 16 VI,
 * ACC, Q, P, I, R and the MAC / clip / status flags.  The game's programs are scheduled by hand
 * (renderer-spec 2.2 / 2.3): they read Q without WAITQ while a DIV is still running, read the MAC
 * and clip flags a fixed distance after the instruction that set them and branch on integer
 * registers one instruction after changing them.  So the model keeps time as the VU does, closely
 * enough for those: one cycle a pair, a stall when a pair reads a VF field an earlier pair writes
 * less than 4 cycles before, FMAC results and flags visible 4 cycles after issue, Q 7 cycles after
 * DIV / SQRT (13 for RSQRT), a branch reading a VI an integer instruction in the pair before it
 * wrote sees the old value (PCSX2's rule; not after a flag instruction, FCAND ... FMOR, whose result
 * every KH1 program tests in the very next pair), and the pair's lower instruction reads the registers from before its
 * upper one writes.  Floats are the VU's: no infinities, NaNs or denormals (a denormal reads and
 * writes as 0, an overflow writes +-max).  XGKICK copies the GIF packets out at once (the GS reading
 * them later is not modelled; the programs double-buffer their output).  Not part of the PS2 build. */
#include "common.h"
#include "platform/vu1.h"

f32 sqrtf(f32);
f32 sinf(f32);
f32 atanf(f32);
f32 expf(f32);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

void (*kh1_vu1_kick)(const u32 *q, u32 nqw);
int kh1_vu1_verbose; /* 1: a line per program run (KH1_HOST_VU1=2) */
u32 kh1_vu1_snap_run; /* with kh1_vu1_verbose: the run (counted from 1) whose start state vu1_snap.bin keeps */
static u32 st_runs_all;
u32 kh1_vu1_snap_kicks; /* and at least this many XGKICKs */
unsigned long kh1_vu1_dump_frame; /* with kh1_vu1_verbose >= 3: only this frame's kicks */
unsigned long kh1_host_frame(void);
int printf(const char *, ...);

#define DATA_QW 0x400    /* 16 KiB */
#define MICRO_N 0x800    /* 16 KiB of 64-bit instructions */
#define MAX_PAIRS 4000000 /* a program that runs longer has lost its way */

typedef union { f32 f; u32 u; s32 s; } Fu;

/* ------------------------------------------------------------------ VU1 state */

static u32 mem[DATA_QW][4];
static u32 micro[MICRO_N][2]; /* [0] lower, [1] upper */
static u32 vf[32][4] = { { 0, 0, 0, 0x3F800000 } }; /* vf00 = (0, 0, 0, 1), never written */
static u32 acc[4];
static u16 vi[16];
static u32 q_reg, q_next, q_ready, q_busy;
static u32 p_reg, p_next, p_ready, p_busy;
static u32 i_reg, r_reg = 0x3F800000;
static u32 mac_now, clip_now, clip_last, stat_now, stat_sticky;
static u32 cyc;
static u32 vf_ready[32][4];
/* flags on their way: visible from cycle t */
#define FLAG_Q 16
static struct { u32 t, mac, clip, has; } fq[FLAG_Q];
static u32 fq_head, fq_n;
static int vib_reg = -1, vib_left; /* the VI the previous pair wrote, and its old value */
static u16 vib_old;
static KH1Vu1Stats st;
static u32 unk_hi, unk_lo, unk_pc;

/* ------------------------------------------------------------------ VIF1 state */

static u32 row[4], col[4], mask, mode, cl = 1, wl = 1;
static u32 base, ofst, tops, top, itops, itop, dbf, tpc;
/* the code whose data is coming */
static u32 cur, cur_imm, cur_num, need, got, mpg_changed;
static u32 dbuf[256 * 4 + 4]; /* an UNPACK's data words (at most 256 vectors of 4 words) */

void kh1_vu1_stats(KH1Vu1Stats *out) {
    *out = st;
    memset(&st, 0, sizeof st);
}

void kh1_vu1_first_unknown(u32 *hi, u32 *lo, u32 *pc) {
    *hi = unk_hi;
    *lo = unk_lo;
    *pc = unk_pc;
}

void kh1_vif1_reset(void) {
    memset(mem, 0, sizeof mem);
    memset(micro, 0, sizeof micro);
    memset(vf, 0, sizeof vf);
    vf[0][3] = 0x3F800000;
    memset(acc, 0, sizeof acc);
    memset(vi, 0, sizeof vi);
    memset(vf_ready, 0, sizeof vf_ready);
    q_reg = q_next = p_reg = p_next = 0;
    q_ready = p_ready = q_busy = p_busy = 0;
    i_reg = 0;
    r_reg = 0x3F800000;
    mac_now = clip_now = clip_last = stat_now = stat_sticky = 0;
    cyc = 0;
    fq_head = fq_n = 0;
    vib_reg = -1;
    vib_left = 0;
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);
    mask = mode = 0;
    cl = wl = 1;
    base = ofst = tops = top = itops = itop = dbf = tpc = 0;
    cur = need = got = 0;
}

/* ------------------------------------------------------------------ floats */

static f32 fin(u32 u) {
    Fu x;
    u32 e = u & 0x7F800000;
    if (e == 0x7F800000) u = (u & 0x80000000) | 0x7F7FFFFF;
    else if (!e) u &= 0x80000000;
    x.u = u;
    return x.f;
}

/* a result's bits as the VU writes them, and its MAC bits for field f (0 = x) */
static u32 fout(f32 v, int f, u32 *macf) {
    Fu x;
    u32 e, b = 3 - f;
    x.f = v;
    e = x.u & 0x7F800000;
    if (e == 0x7F800000) {
        x.u = (x.u & 0x80000000) | 0x7F7FFFFF;
        *macf |= 0x1000u << b;
    } else if (!e) {
        if (x.u & 0x7FFFFF) *macf |= 0x100u << b;
        x.u &= 0x80000000;
    }
    if (!(x.u & 0x7FFFFFFF)) *macf |= 1u << b;
    if (x.u >> 31) *macf |= 0x10u << b;
    return x.u;
}

static u32 ftoi(u32 u, f32 scale) {
    f32 v = fin(u) * scale;
    if (v >= 2147483647.0f) return 0x7FFFFFFF;
    if (v <= -2147483648.0f) return 0x80000000;
    return (u32)(s32)v;
}

static u32 itof(u32 u, f32 scale) {
    Fu x;
    x.f = (f32)(s32)u / scale;
    return x.u;
}

/* ------------------------------------------------------------------ timing */

static void flags_at(u32 t) {
    while (fq_n && fq[fq_head].t <= t) {
        if (fq[fq_head].has & 1) mac_now = fq[fq_head].mac;
        if (fq[fq_head].has & 2) clip_now = fq[fq_head].clip;
        fq_head = (fq_head + 1) % FLAG_Q;
        fq_n--;
    }
}

static void flag_push(u32 t, u32 mac, u32 clip, u32 has) {
    u32 k;
    if (fq_n == FLAG_Q) { /* never with a 4-cycle latency; keep the oldest moving */
        flags_at(fq[fq_head].t);
    }
    k = (fq_head + fq_n) % FLAG_Q;
    fq[k].t = t;
    fq[k].mac = mac;
    fq[k].clip = clip;
    fq[k].has = has;
    fq_n++;
}

static void q_at(u32 t) {
    if (q_busy && t >= q_ready) { q_reg = q_next; q_busy = 0; }
    if (p_busy && t >= p_ready) { p_reg = p_next; p_busy = 0; }
}

/* the cycle a read of fields m (bit 3 = x) of vf r can issue at */
static u32 need_vf(u32 t, int r, u32 m) {
    int f;
    if (!r) return t;
    for (f = 0; f < 4; f++)
        if (m >> (3 - f) & 1 && vf_ready[r][f] > t) t = vf_ready[r][f];
    return t;
}

static void wrote_vf(int r, u32 m, u32 lat) {
    int f;
    for (f = 0; f < 4; f++)
        if (m >> (3 - f) & 1) vf_ready[r][f] = cyc + lat;
}

/* ------------------------------------------------------------------ upper */

/* the pending upper result, written after the lower instruction of the same pair has run */
static int up_to;        /* -1 none, 32 ACC, else a VF */
static u32 up_dest, up_res[4];

enum { K_ADD, K_SUB, K_MADD, K_MSUB, K_MAX, K_MINI, K_MUL };

/* the fields an upper instruction reads of fs and ft, for the stall */
static u32 upper_stall(u32 hi, u32 t) {
    u32 o = hi & 63, dest = hi >> 21 & 15, ft = hi >> 16 & 31, fs = hi >> 11 & 31;
    if (o >= 0x3C) {
        u32 x = (hi >> 6 & 31) << 2 | (o & 3);
        if (x == 0x2F) return t;                           /* nop */
        if (x == 0x1F) return need_vf(need_vf(t, fs, 0xE), ft, 1); /* clip */
        if (x >= 0x10 && x <= 0x17) return need_vf(t, fs, dest); /* itof / ftoi */
        if (x == 0x1D) return need_vf(t, fs, dest);        /* abs */
        if (x < 0x10 || (x >= 0x18 && x <= 0x1B)) return need_vf(need_vf(t, fs, dest), ft, 8 >> (o & 3));
        if (x == 0x2E) return need_vf(need_vf(t, fs, 0xE), ft, 0xE); /* opmula */
        if (x >= 0x28) return need_vf(need_vf(t, fs, dest), ft, dest);
        return need_vf(t, fs, dest);                        /* q / i forms */
    }
    if (o < 0x1C) return need_vf(need_vf(t, fs, dest), ft, 8 >> (o & 3));
    if (o == 0x2E) return need_vf(need_vf(t, fs, 0xE), ft, 0xE);
    if (o >= 0x28) return need_vf(need_vf(t, fs, dest), ft, dest);
    return need_vf(t, fs, dest);
}

static void fmac(int k, u32 dest, const u32 *s, const u32 *t, int to, u32 *macf, int setmac) {
    int f;
    u32 m = 0;
    for (f = 0; f < 4; f++) {
        f32 a, b, r;
        if (!(dest >> (3 - f) & 1)) continue;
        a = fin(s[f]);
        b = fin(t[f]);
        switch (k) {
        case K_ADD: r = a + b; break;
        case K_SUB: r = a - b; break;
        case K_MUL: r = a * b; break;
        case K_MADD: r = fin(acc[f]) + a * b; break;
        case K_MSUB: r = fin(acc[f]) - a * b; break;
        case K_MAX: up_res[f] = a > b ? fout(a, f, &m) : fout(b, f, &m); continue;
        default: up_res[f] = a < b ? fout(a, f, &m) : fout(b, f, &m); continue;
        }
        up_res[f] = fout(r, f, &m);
    }
    up_to = to;
    up_dest = dest;
    if (setmac) *macf = m | 0x10000; /* bit 16: the instruction sets the MAC flag */
}

static void unknown(u32 hi, u32 lo, u32 pc) {
    if (!st.unknown++ && !unk_hi && !unk_lo) {
        unk_hi = hi;
        unk_lo = lo;
        unk_pc = pc;
    }
}

/* runs the upper instruction into up_*; returns the MAC flag it sets (bit 16 set) or 0, and the
 * clip flag in *clip (bit 31 set when it sets it) */
static u32 upper(u32 hi, u32 lo, u32 pc, u32 *clip) {
    u32 o = hi & 63, dest = hi >> 21 & 15, ft = hi >> 16 & 31, fs = hi >> 11 & 31, fd = hi >> 6 & 31;
    u32 t[4], macf = 0;
    int f, k;
    up_to = -1;
    *clip = 0;
    if (o < 0x1C) { /* add / sub / madd / msub / max / mini / mul with ft's broadcast field */
        static const int kinds[7] = { K_ADD, K_SUB, K_MADD, K_MSUB, K_MAX, K_MINI, K_MUL };
        for (f = 0; f < 4; f++) t[f] = vf[ft][o & 3];
        k = kinds[o >> 2];
        fmac(k, dest, vf[fs], t, fd, &macf, k != K_MAX && k != K_MINI);
        return macf;
    }
    if (o < 0x30) {
        static const signed char kq[20] = {
            K_MUL, K_MAX, K_MUL, K_MINI,           /* 1C mulq, 1D maxi, 1E muli, 1F minii */
            K_ADD, K_MADD, K_ADD, K_MADD,          /* 20 addq, maddq, addi, maddi */
            K_SUB, K_MSUB, K_SUB, K_MSUB,          /* 24 subq, msubq, subi, msubi */
            K_ADD, K_MADD, K_MUL, K_MAX,           /* 28 add, madd, mul, max */
            K_SUB, K_MSUB, -1, K_MINI };           /* 2C sub, msub, opmsub, mini */
        k = kq[o - 0x1C];
        if (k < 0) { /* opmsub: fd.xyz = ACC - fs.yzx * ft.zxy */
            u32 s2[4], t2[4];
            s2[0] = vf[fs][1]; s2[1] = vf[fs][2]; s2[2] = vf[fs][0]; s2[3] = 0;
            t2[0] = vf[ft][2]; t2[1] = vf[ft][0]; t2[2] = vf[ft][1]; t2[3] = 0;
            fmac(K_MSUB, dest & 0xE, s2, t2, fd, &macf, 1);
            return macf;
        }
        if (o >= 0x28) {
            fmac(k, dest, vf[fs], vf[ft], fd, &macf, k != K_MAX && k != K_MINI);
            return macf;
        }
        {
            u32 v = (o == 0x1C || o == 0x20 || o == 0x21 || o == 0x24 || o == 0x25) ? q_reg : i_reg;
            for (f = 0; f < 4; f++) t[f] = v;
        }
        fmac(k, dest, vf[fs], t, fd, &macf, k != K_MAX && k != K_MINI);
        return macf;
    }
    if (o < 0x3C) { unknown(hi, lo, pc); return 0; }
    {
        u32 x = fd << 2 | (o & 3);
        switch (x) {
        case 0x00: case 0x01: case 0x02: case 0x03: /* addabc */
        case 0x04: case 0x05: case 0x06: case 0x07: /* subabc */
        case 0x08: case 0x09: case 0x0A: case 0x0B: /* maddabc */
        case 0x0C: case 0x0D: case 0x0E: case 0x0F: /* msubabc */
        case 0x18: case 0x19: case 0x1A: case 0x1B: { /* mulabc */
            static const int kinds[7] = { K_ADD, K_SUB, K_MADD, K_MSUB, 0, 0, K_MUL };
            for (f = 0; f < 4; f++) t[f] = vf[ft][x & 3];
            fmac(kinds[x >> 2], dest, vf[fs], t, 32, &macf, 1);
            return macf;
        }
        case 0x10: case 0x11: case 0x12: case 0x13: { /* itof0 / 4 / 12 / 15 */
            static const f32 sc[4] = { 1.0f, 16.0f, 4096.0f, 32768.0f };
            for (f = 0; f < 4; f++)
                if (dest >> (3 - f) & 1) up_res[f] = itof(vf[fs][f], sc[x & 3]);
            up_to = ft;
            up_dest = dest;
            return 0;
        }
        case 0x14: case 0x15: case 0x16: case 0x17: { /* ftoi0 / 4 / 12 / 15 */
            static const f32 sc[4] = { 1.0f, 16.0f, 4096.0f, 32768.0f };
            for (f = 0; f < 4; f++)
                if (dest >> (3 - f) & 1) up_res[f] = ftoi(vf[fs][f], sc[x & 3]);
            up_to = ft;
            up_dest = dest;
            return 0;
        }
        case 0x1D: /* abs */
            for (f = 0; f < 4; f++)
                if (dest >> (3 - f) & 1) {
                    Fu y;
                    y.f = fin(vf[fs][f]);
                    up_res[f] = y.u & 0x7FFFFFFF;
                }
            up_to = ft;
            up_dest = dest;
            return 0;
        case 0x1F: { /* clipw.xyz fs, ft.w */
            f32 w = fin(vf[ft][3]), v;
            u32 b = 0;
            if (w < 0) w = -w;
            v = fin(vf[fs][0]); if (v > w) b |= 1; if (v < -w) b |= 2;
            v = fin(vf[fs][1]); if (v > w) b |= 4; if (v < -w) b |= 8;
            v = fin(vf[fs][2]); if (v > w) b |= 16; if (v < -w) b |= 32;
            clip_last = ((clip_last << 6) | b) & 0xFFFFFF;
            *clip = clip_last | 0x80000000;
            return 0;
        }
        case 0x1C: case 0x1E: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25: case 0x26: case 0x27: { /* mulaq / mulai / addaq / maddaq / addai / maddai / subaq ... */
            static const signed char kk[12] = { K_MUL, -1, K_MUL, -1, K_ADD, K_MADD, K_ADD, K_MADD, K_SUB, K_MSUB, K_SUB, K_MSUB };
            u32 v = (x == 0x1C || x == 0x20 || x == 0x21 || x == 0x24 || x == 0x25) ? q_reg : i_reg;
            for (f = 0; f < 4; f++) t[f] = v;
            fmac(kk[x - 0x1C], dest, vf[fs], t, 32, &macf, 1);
            return macf;
        }
        case 0x28: case 0x29: case 0x2A: case 0x2C: case 0x2D: { /* adda / madda / mula / suba / msuba */
            static const signed char kk[6] = { K_ADD, K_MADD, K_MUL, -1, K_SUB, K_MSUB };
            fmac(kk[x - 0x28], dest, vf[fs], vf[ft], 32, &macf, 1);
            return macf;
        }
        case 0x2E: { /* opmula: ACC.xyz = fs.yzx * ft.zxy */
            u32 s2[4], t2[4];
            s2[0] = vf[fs][1]; s2[1] = vf[fs][2]; s2[2] = vf[fs][0]; s2[3] = 0;
            t2[0] = vf[ft][2]; t2[1] = vf[ft][0]; t2[2] = vf[ft][1]; t2[3] = 0;
            fmac(K_MUL, dest & 0xE, s2, t2, 32, &macf, 1);
            return macf;
        }
        case 0x2F: return 0; /* nop */
        }
    }
    unknown(hi, lo, pc);
    return 0;
}

/* ------------------------------------------------------------------ lower */

static s32 s11(u32 w) { return (s32)(w << 21) >> 21; }

/* a VI read by a branch: the previous pair's write is not seen yet */
static u16 vib(int r) { return (vib_left && r == vib_reg) ? vib_old : vi[r]; }

static int vi_wrote; /* the VI this pair's lower instruction wrote (-1 none) */
static u16 vi_was;

static void set_vi(int r, u32 v) {
    if (!r) return;
    vi_wrote = r;
    vi_was = vi[r];
    vi[r] = (u16)v;
}

static u32 first_field(u32 dest) {
    int f;
    for (f = 0; f < 4; f++)
        if (dest >> (3 - f) & 1) return f;
    return 0;
}

/* the stall a lower instruction's VF reads need */
static u32 lower_stall(u32 lo, u32 t) {
    u32 o = lo >> 25, dest = lo >> 21 & 15, is = lo >> 11 & 31, it = lo >> 16 & 31;
    if (o == 0x40) {
        u32 f = lo & 63;
        if (f >= 0x3C) {
            u32 x = (lo >> 6 & 31) << 2 | (lo & 3);
            u32 fsf = 8 >> (lo >> 21 & 3), ftf = 8 >> (lo >> 23 & 3);
            switch (x) {
            case 0x30: return need_vf(t, is, dest);                    /* move */
            case 0x31: return need_vf(t, is, 0xF);                     /* mr32 */
            case 0x35: case 0x37: return need_vf(t, is, dest);         /* sqi / sqd */
            case 0x38: case 0x3A: return need_vf(need_vf(t, is, fsf), it, ftf); /* div / rsqrt */
            case 0x39: return need_vf(t, it, ftf);                     /* sqrt */
            case 0x3C: return need_vf(t, is, fsf);                     /* mtir */
            case 0x42: case 0x43: return need_vf(t, is, fsf);          /* rinit / rxor */
            }
            if (x >= 0x70) return need_vf(t, is, 0xF);                 /* EFU */
        }
        return t;
    }
    if (o == 0x01) return need_vf(t, is, dest); /* sq */
    return t;
}

static void kick(u32 a);

/* runs the lower instruction; returns 1 and the target when it branches, 2 at an [E]-less stop */
static int lower(u32 lo, u32 hi, u32 pc, u32 *target) {
    u32 o = lo >> 25, dest = lo >> 21 & 15;
    int it = lo >> 16 & 31, is = lo >> 11 & 31, id = lo >> 6 & 31, f;
    if (o == 0x40) {
        u32 fn = lo & 63;
        it &= 31;
        if (fn < 0x3C) {
            int a = is & 15, b = it & 15, d = id & 15;
            switch (fn) {
            case 0x30: set_vi(d, vi[a] + vi[b]); return 0;
            case 0x31: set_vi(d, vi[a] - vi[b]); return 0;
            case 0x32: set_vi(b, vi[a] + ((s32)(id << 27) >> 27)); return 0; /* iaddi */
            case 0x34: set_vi(d, vi[a] & vi[b]); return 0;
            case 0x35: set_vi(d, vi[a] | vi[b]); return 0;
            }
            unknown(hi, lo, pc);
            return 0;
        }
        {
            u32 x = (u32)id << 2 | (lo & 3);
            u32 fsf = lo >> 21 & 3, ftf = lo >> 23 & 3;
            switch (x) {
            case 0x30: /* move */
                if (lo == 0x8000033C) return 0; /* nop */
                if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = vf[is][f]; wrote_vf(it, dest, 4); }
                return 0;
            case 0x31: /* mr32 */
                if (it) {
                    u32 s[4];
                    s[0] = vf[is][1]; s[1] = vf[is][2]; s[2] = vf[is][3]; s[3] = vf[is][0];
                    for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = s[f];
                    wrote_vf(it, dest, 4);
                }
                return 0;
            case 0x34: case 0x36: { /* lqi / lqd */
                u32 a;
                if (x == 0x36) set_vi(is & 15, vi[is & 15] - 1);
                a = vi[is & 15] & (DATA_QW - 1);
                if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = mem[a][f]; wrote_vf(it, dest, 4); }
                if (x == 0x34) set_vi(is & 15, vi[is & 15] + 1);
                return 0;
            }
            case 0x35: case 0x37: { /* sqi / sqd */
                u32 a;
                if (x == 0x37) set_vi(it & 15, vi[it & 15] - 1);
                a = vi[it & 15] & (DATA_QW - 1);
                for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) mem[a][f] = vf[is][f];
                if (x == 0x35) set_vi(it & 15, vi[it & 15] + 1);
                return 0;
            }
            case 0x38: case 0x39: case 0x3A: { /* div / sqrt / rsqrt */
                f32 a = fin(vf[is][fsf]), b = fin(vf[it][ftf]), r;
                u32 junk = 0;
                Fu y;
                if (q_busy) { if (cyc < q_ready) cyc = q_ready; q_at(cyc); }
                if (x == 0x38 && b == 0) { /* x / 0: +-max, the sign of the quotient */
                    y.u = 0x7F7FFFFF | ((vf[is][fsf] ^ vf[it][ftf]) & 0x80000000);
                    r = y.f;
                } else if (x == 0x38) r = a / b;
                else {
                    b = sqrtf(b < 0 ? -b : b);
                    if (x == 0x39) r = b;
                    else if (b == 0) { y.u = 0x7F7FFFFF | (a < 0 ? 0x80000000 : 0); r = y.f; }
                    else r = a / b;
                }
                q_next = fout(r, 0, &junk);
                q_ready = cyc + (x == 0x3A ? 13 : 7);
                q_busy = 1;
                return 0;
            }
            case 0x3B: /* waitq */
                if (q_busy && cyc < q_ready) cyc = q_ready;
                q_at(cyc);
                return 0;
            case 0x3C: set_vi(it & 15, vf[is][fsf]); return 0;            /* mtir */
            case 0x3D:                                                      /* mfir */
                if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = (u32)(s32)(s16)vi[is & 15]; wrote_vf(it, dest, 4); }
                return 0;
            case 0x3E: /* ilwr */
                set_vi(it & 15, mem[vi[is & 15] & (DATA_QW - 1)][first_field(dest)]);
                return 0;
            case 0x3F: /* iswr */
                for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) mem[vi[is & 15] & (DATA_QW - 1)][f] = vi[it & 15];
                return 0;
            case 0x40: case 0x41: /* rnext / rget */
                if (x == 0x40) {
                    u32 b = (r_reg >> 4 & 1) ^ (r_reg >> 22 & 1);
                    r_reg = (((r_reg << 1) ^ b) & 0x7FFFFF) | 0x3F800000;
                }
                if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = r_reg; wrote_vf(it, dest, 4); }
                return 0;
            case 0x42: r_reg = 0x3F800000 | (vf[is][fsf] & 0x7FFFFF); return 0;        /* rinit */
            case 0x43: r_reg = 0x3F800000 | ((r_reg ^ vf[is][fsf]) & 0x7FFFFF); return 0; /* rxor */
            case 0x64: /* mfp */
                q_at(cyc);
                if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = p_reg; wrote_vf(it, dest, 4); }
                return 0;
            case 0x68: set_vi(it & 15, top); return 0;   /* xtop */
            case 0x69: set_vi(it & 15, itop); return 0;  /* xitop */
            case 0x6C: kick(vi[is & 15]); return 0;      /* xgkick */
            case 0x7B: /* waitp */
                if (p_busy && cyc < p_ready) cyc = p_ready;
                q_at(cyc);
                return 0;
            }
            if (x >= 0x70) { /* the EFU: P */
                f32 a = fin(vf[is][0]), b = fin(vf[is][1]), c = fin(vf[is][2]), d = fin(vf[is][3]);
                f32 e = fin(vf[is][fsf]), r;
                u32 junk = 0;
                switch (x) {
                case 0x70: r = a * a + b * b + c * c; break;                 /* esadd */
                case 0x71: r = 1.0f / (a * a + b * b + c * c); break;        /* ersadd */
                case 0x72: r = sqrtf(a * a + b * b + c * c); break;          /* eleng */
                case 0x73: r = 1.0f / sqrtf(a * a + b * b + c * c); break;   /* erleng */
                case 0x76: r = a + b + c + d; break;                         /* esum */
                case 0x78: r = sqrtf(e < 0 ? -e : e); break;                 /* esqrt */
                case 0x79: r = 1.0f / sqrtf(e < 0 ? -e : e); break;          /* ersqrt */
                case 0x7A: r = 1.0f / e; break;                              /* ercpr */
                case 0x7C: r = sinf(e); break;                               /* esin */
                case 0x7D: r = atanf(e); break;                              /* eatan */
                case 0x7E: r = expf(-e); break;                              /* eexp */
                default: unknown(hi, lo, pc); return 0;
                }
                if (p_busy) { if (cyc < p_ready) cyc = p_ready; q_at(cyc); }
                p_next = fout(r, 0, &junk);
                p_ready = cyc + 18;
                p_busy = 1;
                return 0;
            }
        }
        unknown(hi, lo, pc);
        return 0;
    }
    switch (o) {
    case 0x00: { /* lq */
        u32 a = (vi[is & 15] + s11(lo)) & (DATA_QW - 1);
        if (it) { for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) vf[it][f] = mem[a][f]; wrote_vf(it, dest, 4); }
        return 0;
    }
    case 0x01: { /* sq */
        u32 a = (vi[it & 15] + s11(lo)) & (DATA_QW - 1);
        for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) mem[a][f] = vf[is][f];
        return 0;
    }
    case 0x04: set_vi(it & 15, mem[(vi[is & 15] + s11(lo)) & (DATA_QW - 1)][first_field(dest)]); return 0; /* ilw */
    case 0x05: { /* isw */
        u32 a = (vi[is & 15] + s11(lo)) & (DATA_QW - 1);
        for (f = 0; f < 4; f++) if (dest >> (3 - f) & 1) mem[a][f] = vi[it & 15];
        return 0;
    }
    case 0x08: set_vi(it & 15, vi[is & 15] + ((lo >> 10 & 0x7800) | (lo & 0x7FF))); return 0; /* iaddiu */
    case 0x09: set_vi(it & 15, vi[is & 15] - ((lo >> 10 & 0x7800) | (lo & 0x7FF))); return 0; /* isubiu */
    case 0x10: flags_at(cyc); set_vi(1, clip_now == (lo & 0xFFFFFF)); return 0;                  /* fceq */
    case 0x11: /* fcset */
        flags_at(cyc);
        {
            u32 k;
            for (k = 0; k < fq_n; k++) fq[(fq_head + k) % FLAG_Q].has &= ~2u;
        }
        clip_now = clip_last = lo & 0xFFFFFF;
        return 0;
    case 0x12: flags_at(cyc); set_vi(1, (clip_now & lo & 0xFFFFFF) != 0); return 0;              /* fcand */
    case 0x13: flags_at(cyc); set_vi(1, ((clip_now | lo) & 0xFFFFFF) == 0xFFFFFF); return 0;     /* fcor */
    case 0x14: case 0x16: case 0x17: { /* fseq / fsand / fsor */
        u32 imm = (lo >> 10 & 0x800) | (lo & 0x7FF), s;
        flags_at(cyc);
        s = stat_now | stat_sticky;
        set_vi(it & 15, o == 0x14 ? (s & 0xFFF) == imm : o == 0x16 ? s & imm : (s | imm) & 0xFFF);
        return 0;
    }
    case 0x15: stat_sticky = ((lo >> 10 & 0x800) | (lo & 0x7FF)) & 0xFC0; return 0; /* fsset */
    case 0x18: flags_at(cyc); set_vi(it & 15, (vi[is & 15] & 0xFFFF) == mac_now); return 0;    /* fmeq */
    case 0x1A: flags_at(cyc); set_vi(it & 15, vi[is & 15] & mac_now); return 0;                /* fmand */
    case 0x1B: flags_at(cyc); set_vi(it & 15, vi[is & 15] | mac_now); return 0;                /* fmor */
    case 0x1C: flags_at(cyc); set_vi(it & 15, clip_now & 0xFFF); return 0;                     /* fcget */
    case 0x20: *target = pc + 1 + s11(lo); return 1;                                           /* b */
    case 0x21: *target = pc + 1 + s11(lo); set_vi(it & 15, pc + 2); return 1;                  /* bal */
    case 0x24: *target = vib(is & 15); return 1;                                               /* jr */
    case 0x25: *target = vib(is & 15); set_vi(it & 15, pc + 2); return 1;                      /* jalr */
    case 0x28: if (vib(it & 15) == vib(is & 15)) { *target = pc + 1 + s11(lo); return 1; } return 0;
    case 0x29: if (vib(it & 15) != vib(is & 15)) { *target = pc + 1 + s11(lo); return 1; } return 0;
    case 0x2C: if ((s16)vib(is & 15) < 0) { *target = pc + 1 + s11(lo); return 1; } return 0;
    case 0x2D: if ((s16)vib(is & 15) > 0) { *target = pc + 1 + s11(lo); return 1; } return 0;
    case 0x2E: if ((s16)vib(is & 15) <= 0) { *target = pc + 1 + s11(lo); return 1; } return 0;
    case 0x2F: if ((s16)vib(is & 15) >= 0) { *target = pc + 1 + s11(lo); return 1; } return 0;
    }
    unknown(hi, lo, pc);
    return 0;
}

/* ------------------------------------------------------------------ XGKICK */

static u32 kbuf[DATA_QW][4];

static void kick(u32 a) {
    u32 n = 0;
    a &= DATA_QW - 1;
    while (n < DATA_QW) {
        u32 *tq = mem[a], nloop, flg, nreg, len, eop;
        memcpy(kbuf[n++], tq, 16);
        a = (a + 1) & (DATA_QW - 1);
        nloop = tq[0] & 0x7FFF;
        eop = tq[0] >> 15 & 1;
        flg = tq[1] >> 26 & 3;
        nreg = tq[1] >> 28 & 15;
        if (!nreg) nreg = 16;
        len = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1) / 2 : nloop;
        while (len-- && n < DATA_QW) {
            memcpy(kbuf[n++], mem[a], 16);
            a = (a + 1) & (DATA_QW - 1);
        }
        if (eop) break;
    }
    st.kicks++;
    st.kick_qw += n;
    if (kh1_vu1_verbose >= 3 && kh1_vu1_dump_frame && kh1_host_frame() != kh1_vu1_dump_frame) {
        if (kh1_vu1_kick) kh1_vu1_kick(&kbuf[0][0], n);
        return;
    }
    if (kh1_vu1_verbose >= 3)
        printf("kh1-vu1: kick (frame %lu) %u qwords: tag %08x %08x %08x %08x, %08x %08x %08x %08x\n", kh1_host_frame(), n, kbuf[0][0], kbuf[0][1],
               kbuf[0][2], kbuf[0][3], kbuf[1][0], kbuf[1][1], kbuf[1][2], kbuf[1][3]);
    if (kh1_vu1_verbose >= 4) {
        u32 k;
        for (k = 0; k < n; k++) printf("kh1-vu1:   %08x %08x %08x %08x\n", kbuf[k][0], kbuf[k][1], kbuf[k][2], kbuf[k][3]);
    }
    if (kh1_vu1_kick) kh1_vu1_kick(&kbuf[0][0], n);
}

/* ------------------------------------------------------------------ the run */

/* KH1_HOST_VU1=2: the state at the first runaway program's start, for an offline replay */
static u32 snap_mem[DATA_QW][4], snap_vf[32][4], snap_regs[4];
static u16 snap_vi[16];
static int snapped;
void *fopen(const char *, const char *);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int fclose(void *);
static void snap_take(void) {
    memcpy(snap_mem, mem, sizeof mem);
    memcpy(snap_vf, vf, sizeof vf);
    memcpy(snap_vi, vi, sizeof vi);
    snap_regs[0] = top;
    snap_regs[1] = itop;
    snap_regs[2] = i_reg;
    snap_regs[3] = q_reg;
}
static void snap_write(u32 pc) {
    void *f;
    if (snapped++) return;
    f = fopen("vu1_snap.bin", "wb");
    if (!f) return;
    snap_regs[3] = pc;
    fwrite(micro, sizeof micro, 1, f);
    fwrite(snap_mem, sizeof snap_mem, 1, f);
    fwrite(snap_vf, sizeof snap_vf, 1, f);
    fwrite(snap_vi, sizeof snap_vi, 1, f);
    fwrite(snap_regs, sizeof snap_regs, 1, f);
    fclose(f);
}

/* FNV-1a over the first 64 instructions: which program is in micro memory (the verbose lines) */
static u32 code_id(void) {
    u32 h = 2166136261u, i;
    for (i = 0; i < 128; i++) h = (h ^ micro[i >> 1][i & 1]) * 16777619u;
    return h;
}

#ifndef VU1_TRACE
#define VU1_TRACE(pc)
#endif
static void run(u32 pc) {
    u32 pairs = 0, target = 0, dtarget = 0, c0 = cyc, pc0 = pc, k0 = st.kicks;
    int delay = 0, ending = 0;
    st.runs++;
    st_runs_all++;
    if (kh1_vu1_verbose) snap_take();
    pc &= MICRO_N - 1;
    for (;;) {
        u32 lo = micro[pc][0], hi = micro[pc][1], t, mac, clip, br;
        int b = 0;
        VU1_TRACE(pc);
        /* stalls: the fields this pair reads must be written */
        t = upper_stall(hi, cyc);
        if (!(hi & 0x80000000)) t = lower_stall(lo, t);
        cyc = t;
        q_at(cyc);
        vi_wrote = -1;
        mac = upper(hi, lo, pc, &clip);
        if (hi & 0x80000000) i_reg = lo; /* loi: the upper above read the old I */
        else {
            b = lower(lo, hi, pc, &target);
            /* a flag instruction's VI (FCAND ... FMOR, FCGET) reaches the next pair's branch: every KH1 program
             * tests one that way (P0's FMAND then IBNE vi13 culls backfaces; read with the backup, every
             * triangle went to the culled path) */
            if ((lo >> 25) - 0x10u <= 0x0Cu) vi_wrote = -1;
        }
        /* the upper's result lands after the lower read its registers (and wins a shared target) */
        if (up_to >= 0) {
            int f;
            if (up_to == 32) {
                for (f = 0; f < 4; f++) if (up_dest >> (3 - f) & 1) acc[f] = up_res[f];
            } else if (up_to) {
                for (f = 0; f < 4; f++) if (up_dest >> (3 - f) & 1) vf[up_to][f] = up_res[f];
                wrote_vf(up_to, up_dest, 4);
            }
        }
        if (mac || clip) {
            u32 has = (mac ? 1 : 0) | (clip ? 2 : 0);
            if (mac) {
                u32 m = mac & 0xFFFF, s = 0;
                if (m & 0x000F) s |= 1;
                if (m & 0x00F0) s |= 2;
                if (m & 0x0F00) s |= 4;
                if (m & 0xF000) s |= 8;
                stat_now = s;
                stat_sticky |= s << 6;
            }
            flag_push(cyc + 4, mac & 0xFFFF, clip & 0xFFFFFF, has);
        }
        /* the VI backup: a branch in the next pair reads the value from before this pair */
        vib_left = vi_wrote >= 0;
        vib_reg = vi_wrote;
        vib_old = vi_was;
        st.insns++;
        cyc++;
        if (++pairs > MAX_PAIRS) { st.runaway++; tpc = pc; break; }
        br = pc + 1;
        if (delay) { br = dtarget; delay = 0; }
        if (b == 1) { delay = 1; dtarget = target & (MICRO_N - 1); }
        if (ending) { tpc = br & (MICRO_N - 1); break; }
        if (hi & 0x40000000) ending = 1;
        pc = br & (MICRO_N - 1);
    }
    st.cycles += cyc - c0;
    if (kh1_vu1_verbose && (pairs > MAX_PAIRS || (kh1_vu1_snap_run && st_runs_all >= kh1_vu1_snap_run && st.kicks - k0 >= kh1_vu1_snap_kicks))) snap_write(pc0);
    if (kh1_vu1_verbose)
        printf("kh1-vu1: run %03x -> %03x: %u pairs, %u cycles, top %03x itop %03x, code %08x, %u kicks%s\n", pc0, tpc,
               pairs, cyc - c0, top, itop, code_id(), st.kicks - k0, pairs > MAX_PAIRS ? " RUNAWAY" : "");
}

static void start(u32 pc) {
    top = tops;
    itop = itops;
    if (dbf) { dbf = 0; tops = base; }
    else { dbf = 1; tops = (base + ofst) & (DATA_QW - 1); }
    run(pc);
}

/* ------------------------------------------------------------------ VIF1 codes */

static u32 unpack_data_words(u32 cmd, u32 num) {
    u32 vn = cmd >> 2 & 3, vl = cmd & 3, bits, n = num;
    if (vl == 3 && vn != 3) return ~0u;
    bits = vl == 3 ? 16 : (32 >> vl) * (vn + 1);
    if (wl > cl && wl) {
        u32 r = num % wl;
        n = num / wl * cl + (r < cl ? r : cl);
    }
    return (n * bits + 31) / 32;
}

/* element e (of size bits) of the data words */
static u32 elem(u32 e, u32 bits, int usn, u32 nwords) {
    u32 bit = e * bits, w = bit >> 5, v;
    if (w >= nwords) return 0;
    v = dbuf[w] >> (bit & 31);
    if (bits == 32) return v;
    v &= (1u << bits) - 1;
    if (!usn && v >> (bits - 1) & 1) v |= ~((1u << bits) - 1);
    return v;
}

static void unpack(void) {
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
                u32 h = elem(e0, 16, 1, got);
                v[0] = (h & 31) << 3;
                v[1] = (h >> 5 & 31) << 3;
                v[2] = (h >> 10 & 31) << 3;
                v[3] = (h >> 15 & 1) << 7;
            } else if (vn == 0) {
                v[0] = v[1] = v[2] = v[3] = elem(e0, ebits, usn, got);
            } else if (vn == 1) { /* V2: z and w repeat x and y (PCSX2's unpack) */
                v[0] = v[2] = elem(e0, ebits, usn, got);
                v[1] = v[3] = elem(e0 + 1, ebits, usn, got);
            } else {
                v[0] = elem(e0, ebits, usn, got);
                v[1] = elem(e0 + 1, ebits, usn, got);
                v[2] = elem(e0 + 2, ebits, usn, got);
                v[3] = elem(e0 + 3, ebits, usn, got); /* V3: w is the next element in the stream */
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

void kh1_vif1_code(u32 w) {
    u32 cmd = w >> 24 & 0x7F, imm = w & 0xFFFF, num = w >> 16 & 0xFF;
    if (kh1_vu1_verbose >= 2 && cmd)
        printf("kh1-vif1: %08x  cl %u wl %u base %03x ofst %03x tops %03x dbf %u\n", w, cl, wl, base, ofst, tops, dbf);
    cur = cmd;
    cur_imm = imm;
    cur_num = num;
    need = got = 0;
    switch (cmd) {
    case 0x01: cl = imm & 0xFF; wl = imm >> 8 & 0xFF; return;    /* STCYCL */
    case 0x02: ofst = imm & 0x3FF; dbf = 0; tops = base; return; /* OFFSET */
    case 0x03: base = imm & 0x3FF; return;                       /* BASE */
    case 0x04: itops = imm & 0x3FF; return;                      /* ITOP */
    case 0x05: mode = imm & 3; return;                           /* STMOD */
    case 0x14: case 0x15: start(imm); return;                    /* MSCAL / MSCALF */
    case 0x17: start(tpc); return;                               /* MSCNT */
    case 0x20: need = 1; return;                                 /* STMASK */
    case 0x30: case 0x31: need = 4; return;                      /* STROW / STCOL */
    case 0x4A: need = (num ? num : 256) * 2; return;             /* MPG */
    case 0x50: case 0x51: need = (imm ? imm : 0x10000) * 4; return; /* DIRECT: PATH2, the walk's */
    }
    if ((cmd & 0x60) == 0x60) {
        u32 n = unpack_data_words(cmd, num ? num : 256);
        if (n == ~0u) { cur = 0; return; }
        need = n;
        if (!need) unpack();
        return;
    }
    cur = 0;
}

void kh1_vif1_data(u32 w) {
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
        }
        if (!need && mpg_changed) { st.mpg++; mpg_changed = 0; }
        return;
    }
    case 0x50: case 0x51: return;
    }
    if ((cur & 0x60) == 0x60) {
        if (got < sizeof dbuf / 4) dbuf[got] = w;
        got++;
        if (!need) unpack();
    }
}
