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
#if defined(__i386__) && defined(__GNUC__)
/* IEEE single steps as on the Vita, not x87's wider registers (the host's -m32): the interpreter and the
 * translated programs (vu1_tr.c) then give the same bits however each is compiled */
#pragma GCC target("sse2", "fpmath=sse")
#endif
#include "common.h"
#include "platform/vu1.h"

f32 sqrtf(f32);
f32 sinf(f32);
f32 atanf(f32);
f32 expf(f32);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

void (*kh1_vu1_kick)(const u32 *q, u32 nqw);
u32 (*kh1_vu1_clock)(void);
u32 kh1_vu1_us, kh1_vu1_kick_us;
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
static u32 cur, cur_imm, cur_num, need, got, mpg_changed, micro_gen;
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

/* a result's bits as the VU writes them, without the MAC flag */
static u32 fo(f32 v) {
    Fu x;
    u32 e;
    x.f = v;
    e = x.u & 0x7F800000;
    if (e == 0x7F800000) x.u = (x.u & 0x80000000) | 0x7F7FFFFF;
    else if (!e) x.u &= 0x80000000;
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

static u32 absf(u32 u) {
    Fu y;
    y.f = fin(u);
    return y.u & 0x7FFFFFFF;
}

/* session 143: fin(u) as an integer that orders as the float does: fin's values are finite and never
 * denormal, so sign and magnitude are enough (both zeros 0); no VFP, whose compares the A9 pays a flag
 * transfer each for */
static __inline__ s32 fkey(u32 u) {
    u32 e = u & 0x7F800000, m = u & 0x7FFFFFFF;
    if (e == 0x7F800000) m = 0x7F7FFFFF;
    else if (!e) m = 0;
    return u >> 31 ? -(s32)m : (s32)m;
}

/* the clip flag after CLIPw.xyz of fs against |w| (the float compares of fin()'s values, on fkey) */
static u32 clipw(const u32 *s, u32 wb) {
    s32 w = fkey(wb), v;
    u32 b = 0;
    if (w < 0) w = -w;
    v = fkey(s[0]); if (v > w) b |= 1; if (v < -w) b |= 2;
    v = fkey(s[1]); if (v > w) b |= 4; if (v < -w) b |= 8;
    v = fkey(s[2]); if (v > w) b |= 16; if (v < -w) b |= 32;
    return ((clip_last << 6) | b) & 0xFFFFFF;
}

static u32 rnext(u32 r) {
    u32 b = (r >> 4 & 1) ^ (r >> 22 & 1);
    return (((r << 1) ^ b) & 0x7FFFFF) | 0x3F800000;
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
                if (dest >> (3 - f) & 1) up_res[f] = absf(vf[fs][f]);
            up_to = ft;
            up_dest = dest;
            return 0;
        case 0x1F: /* clipw.xyz fs, ft.w */
            clip_last = clipw(vf[fs], vf[ft][3]);
            *clip = clip_last | 0x80000000;
            return 0;
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

/* DIV / SQRT / RSQRT's Q from fs's and ft's chosen fields */
static u32 qop(u32 x, u32 s, u32 t) {
    f32 a = fin(s), b = fin(t), r;
    Fu y;
    if (x == 0x38 && b == 0) { /* x / 0: +-max, the sign of the quotient */
        y.u = 0x7F7FFFFF | ((s ^ t) & 0x80000000);
        r = y.f;
    } else if (x == 0x38) r = a / b;
    else {
        b = sqrtf(b < 0 ? -b : b);
        if (x == 0x39) r = b;
        else if (b == 0) { y.u = 0x7F7FFFFF | (a < 0 ? 0x80000000 : 0); r = y.f; }
        else r = a / b;
    }
    return fo(r);
}

static int efu_known(u32 x) {
    return (x >= 0x70 && x <= 0x73) || x == 0x76 || (x >= 0x78 && x <= 0x7A) || (x >= 0x7C && x <= 0x7E);
}

/* the EFU's P from vf fs (field fsf for the one-operand forms) */
static u32 pop(u32 x, const u32 *v, u32 fsf) {
    f32 a = fin(v[0]), b = fin(v[1]), c = fin(v[2]), d = fin(v[3]), e = fin(v[fsf]), r;
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
    default: r = expf(-e); break;                                /* eexp */
    }
    return fo(r);
}

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
            case 0x38: case 0x39: case 0x3A: /* div / sqrt / rsqrt */
                if (q_busy) { if (cyc < q_ready) cyc = q_ready; q_at(cyc); }
                q_next = qop(x, vf[is][fsf], vf[it][ftf]);
                q_ready = cyc + (x == 0x3A ? 13 : 7);
                q_busy = 1;
                return 0;
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
                if (x == 0x40) r_reg = rnext(r_reg);
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
                if (!efu_known(x)) { unknown(hi, lo, pc); return 0; }
                if (p_busy) { if (cyc < p_ready) cyc = p_ready; q_at(cyc); }
                p_next = pop(x, vf[is], fsf);
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
    u32 n = 0, a0;
    const u32 *q;
    a &= DATA_QW - 1;
    a0 = a;
    /* the packets' length: tags and data up to the EOP tag, at most the whole of VU memory */
    while (n < DATA_QW) {
        const u32 *tq = mem[a];
        u32 nloop = tq[0] & 0x7FFF, eop = tq[0] >> 15 & 1, flg = tq[1] >> 26 & 3, nreg = tq[1] >> 28 & 15, len;
        if (!nreg) nreg = 16;
        len = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1) / 2 : nloop;
        n++;
        if (len > DATA_QW - n) len = DATA_QW - n;
        n += len;
        a = (a + 1 + len) & (DATA_QW - 1);
        if (eop) break;
    }
    /* session 137v (the Dive's speed on a Vita): handed over in place unless it wraps VU memory's end */
    if (a0 + n <= DATA_QW) q = mem[a0];
    else {
        memcpy(kbuf[0], mem[a0], (DATA_QW - a0) * 16);
        memcpy(kbuf[DATA_QW - a0], mem[0], (n - (DATA_QW - a0)) * 16);
        q = kbuf[0];
    }
    st.kicks++;
    st.kick_qw += n;
    if (kh1_vu1_verbose >= 3 && kh1_vu1_dump_frame && kh1_host_frame() != kh1_vu1_dump_frame) {
        if (kh1_vu1_kick) kh1_vu1_kick(q, n);
        return;
    }
    if (kh1_vu1_verbose >= 3)
        printf("kh1-vu1: kick (frame %lu) %u qwords: tag %08x %08x %08x %08x, %08x %08x %08x %08x\n", kh1_host_frame(), n, q[0], q[1],
               q[2], q[3], q[4], q[5], q[6], q[7]);
    if (kh1_vu1_verbose >= 4) {
        u32 k;
        for (k = 0; k < n; k++) printf("kh1-vu1:   %08x %08x %08x %08x\n", q[k * 4], q[k * 4 + 1], q[k * 4 + 2], q[k * 4 + 3]);
    }
    if (kh1_vu1_kick && kh1_vu1_clock) {
        u32 t0 = kh1_vu1_clock();
        kh1_vu1_kick(q, n);
        kh1_vu1_kick_us += kh1_vu1_clock() - t0;
    } else if (kh1_vu1_kick) kh1_vu1_kick(q, n);
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

/* a run starts with the pipeline drained (the MSCAL / MSCNT comes long after the last run's results land):
 * pending flags, Q and P in place, no VF still on its way, no VI backup.  The translated programs
 * (vu1_tr.c) start from the same */
static void settle(void) {
    flags_at(~0u);
    q_at(~0u);
    memset(vf_ready, 0, sizeof vf_ready);
    vib_left = 0;
    vib_reg = -1;
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
    settle();
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

/* ------------------------------------------------------------------ four lanes at once (vu1_tr.c) */

/* t = k(a, b) on all four fields (vu1_tr.c stores the ones the instruction writes), c the ACC for MADD /
 * MSUB.  The scalar form is the interpreter's fmac() field by field.  On ARM, NEON: its flush of
 * denormals on input and output is fin() / fout()'s, its overflow to infinity is clamped here as fout()
 * does; the one difference is a MADD / MSUB whose product alone is denormal (NEON flushes it before the
 * add, the scalar C keeps it), which only moves a sum of magnitude below 2^-126 */
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
#include <arm_neon.h>
/* session 147: the VU's registers read and written as plain vector memory, not through vld1q / vst1q: gcc sees
 * through these (an ACC stored by one FMAC and read by the next stays in its register; the A9 makes a NEON load
 * of what a NEON store just wrote wait for it) where the intrinsics are opaque to it.  aligned(4): vf / acc / mem
 * are u32 arrays */
typedef uint32x4_t vu_u4 __attribute__((aligned(4), may_alias));
#define VU_LD(p) (*(const vu_u4 *)(p))
#define VU_ST(p, v) (*(vu_u4 *)(p) = (v))
/* session 147: fin()'s clamp in two minimums: a signed one brings a positive word down to 0x7F7FFFFF and
 * leaves a negative one, an unsigned one the reverse with 0xFF7FFFFF (Inf and NaN to the largest finite of
 * their sign; a denormal NEON flushes as it reads it) */
static __inline__ float32x4_t vfin(uint32x4_t u) {
    int32x4_t p = vminq_s32(vreinterpretq_s32_u32(u), vdupq_n_s32(0x7F7FFFFF));
    return vreinterpretq_f32_u32(vminq_u32(vreinterpretq_u32_s32(p), vdupq_n_u32(0xFF7FFFFFu)));
}
/* an arithmetic result: NEON flushed it already.  Its operands are finite (fin()'s, or what the VU wrote), so
 * it is finite or an infinity, never a NaN: the clamp to +-FLT_MAX is fout()'s, -0 kept.  Session 148: done as
 * vfin's two integer minimums (an infinity's pattern to the largest finite of its sign, every finite value
 * as it is), so the two share their constants: the float form's +-FLT_MAX were two more literal-pool loads a
 * result in the translated programs (~10% of P0's instructions were those reloads) */
static __inline__ uint32x4_t vfo(float32x4_t r) {
    return vreinterpretq_u32_f32(vfin(vreinterpretq_u32_f32(r)));
}
static __inline__ uint32x4_t vflush(uint32x4_t u) { /* a value passed through (MAX / MINI): denormal to 0 */
    uint32x4_t z = vceqq_u32(vandq_u32(u, vdupq_n_u32(0x7F800000u)), vdupq_n_u32(0));
    return vbslq_u32(z, vandq_u32(u, vdupq_n_u32(0x80000000u)), u);
}
static __inline__ float32x4_t vin(uint32x4_t u, int fi) { /* fi 0: a value the VU wrote, fin() is itself */
    return fi ? vfin(u) : vreinterpretq_f32_u32(u);
}
static __inline__ __attribute__((always_inline)) void vu_k(u32 *t, int k, float32x4_t a, float32x4_t b, const u32 *c, int fc) {
    float32x4_t r;
    switch (k) {
    case K_ADD: r = vaddq_f32(a, b); break;
    case K_SUB: r = vsubq_f32(a, b); break;
    case K_MUL: r = vmulq_f32(a, b); break;
    case K_MADD: r = vaddq_f32(vin(VU_LD(c), fc), vmulq_f32(a, b)); break;
    case K_MSUB: r = vsubq_f32(vin(VU_LD(c), fc), vmulq_f32(a, b)); break;
    default: { /* MAX / MINI: a > b ? a : b, a < b ? a : b (b on a tie, as the interpreter) */
        uint32x4_t gt = k == K_MAX ? vcgtq_f32(a, b) : vcltq_f32(a, b);
        VU_ST(t, vfo(vreinterpretq_f32_u32(vflush(vbslq_u32(gt, vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b))))));
        return;
    }
    }
    VU_ST(t, vfo(r));
}
/* fa, fb, fc: whether a, b, c need fin() (vu1_translate.py knows when they hold what the VU wrote) */
static __inline__ __attribute__((always_inline)) void vu_op(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, int fa, int fb, int fc) {
    vu_k(t, k, vin(VU_LD(a), fa), vin(VU_LD(b), fb), c, fc);
}
/* b one field, broadcast: a word the core wrote (Q, I) */
static __inline__ __attribute__((always_inline)) void vu_opb(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, int fa, int fb, int fc) {
    vu_k(t, k, vin(VU_LD(a), fa), vin(vdupq_n_u32(*b), fb), c, fc);
}
/* lane l of v in all four (l a constant) */
static __inline__ uint32x4_t vu_lane(uint32x4_t v, int l) {
    switch (l) {
    case 0: return vdupq_lane_u32(vget_low_u32(v), 0);
    case 1: return vdupq_lane_u32(vget_low_u32(v), 1);
    case 2: return vdupq_lane_u32(vget_high_u32(v), 0);
    default: return vdupq_lane_u32(vget_high_u32(v), 1);
    }
}
/* b field l of a VF: taken from the register's vector, so a VF an FMAC just wrote is not read back through a core
 * register (on the A9 a core load of a word NEON stored waits for the store) */
static __inline__ __attribute__((always_inline)) void vu_opbl(u32 *t, int k, const u32 *a, const u32 *b, int l, const u32 *c, int fa, int fb, int fc) {
    vu_k(t, k, vin(VU_LD(a), fa), vreinterpretq_f32_u32(vu_lane(vreinterpretq_u32_f32(vin(VU_LD(b), fb)), l)), c, fc);
}
/* session 141: four lanes for the forms vu1_tr.c ran field by field (an FMAC whose MAC flag a later FMAND /
 * FMEQ / FMOR reads, OPMULA / OPMSUB), exact: the operands always through fin(), the MAC bits (into *macf
 * when macf is not 0) fout()'s for the fields in dest.  Answers 0, touching neither t nor *macf, where
 * NEON's flush to zero could differ from the scalar form in a field of dest: a result of 0 with the MAC
 * flag (a denormal the scalar form flags U), or a MADD / MSUB product of 0 from two non-zero factors (a
 * denormal the scalar add keeps); the caller then runs the scalar form */
static const u32 vu_lanes[16][4] = {
    { 0, 0, 0, 0 }, { 0, 0, 0, ~0u }, { 0, 0, ~0u, 0 }, { 0, 0, ~0u, ~0u },
    { 0, ~0u, 0, 0 }, { 0, ~0u, 0, ~0u }, { 0, ~0u, ~0u, 0 }, { 0, ~0u, ~0u, ~0u },
    { ~0u, 0, 0, 0 }, { ~0u, 0, 0, ~0u }, { ~0u, 0, ~0u, 0 }, { ~0u, 0, ~0u, ~0u },
    { ~0u, ~0u, 0, 0 }, { ~0u, ~0u, 0, ~0u }, { ~0u, ~0u, ~0u, 0 }, { ~0u, ~0u, ~0u, ~0u },
};
static __inline__ __attribute__((always_inline)) int vu_ek(u32 *t, int k, float32x4_t a, float32x4_t b, const u32 *c, u32 dest, u32 *macf) {
    uint32x4_t act = VU_LD(vu_lanes[dest & 15]), z = vdupq_n_u32(0), abs7 = vdupq_n_u32(0x7FFFFFFFu);
    uint32x4_t ru, bad = z, exact, zf = z;
    uint32x2_t any;
    float32x4_t p = vmulq_f32(a, b), r, ci = vdupq_n_f32(0);
    u32 m;
    switch (k) {
    case K_ADD: r = vaddq_f32(a, b); break;
    case K_SUB: r = vsubq_f32(a, b); break;
    case K_MUL: r = p; break;
    case K_MADD: case K_MSUB: {
        uint32x4_t pz = vceqq_u32(vandq_u32(vreinterpretq_u32_f32(p), abs7), z);
        uint32x4_t an = vtstq_u32(vreinterpretq_u32_f32(a), abs7), bn = vtstq_u32(vreinterpretq_u32_f32(b), abs7);
        bad = vandq_u32(pz, vandq_u32(an, bn));
        ci = vfin(VU_LD(c));
        r = k == K_MADD ? vaddq_f32(ci, p) : vsubq_f32(ci, p);
        break;
    }
    default: return 0; /* MAX / MINI: never here */
    }
    ru = vreinterpretq_u32_f32(r);
    if (macf) { /* session 149: a 0 that is exactly 0 gets fout()'s Z here; only a flushed one goes to the scalar form */
        uint32x4_t zr = vceqq_u32(vandq_u32(ru, abs7), z), ex0 = vdupq_n_u32(0x7F800000u);
        switch (k) {
        case K_ADD: exact = vceqq_f32(a, vnegq_f32(b)); break; /* x + -x, 0 + 0 (a denormal read as 0, as fin()) */
        case K_SUB: exact = vceqq_f32(a, b); break;
        case K_MUL: exact = vorrq_u32(vceqq_u32(vandq_u32(vreinterpretq_u32_f32(a), ex0), z),
                                      vceqq_u32(vandq_u32(vreinterpretq_u32_f32(b), ex0), z)); break;
        case K_MADD: exact = vceqq_f32(ci, vnegq_f32(p)); break; /* p not flushed: that is bad already */
        default: exact = vceqq_f32(ci, p); break;
        }
        zf = vandq_u32(zr, exact);
        bad = vorrq_u32(bad, vbicq_u32(zr, exact));
    }
    bad = vandq_u32(bad, act);
    if (!macf) {
        any = vorr_u32(vget_low_u32(bad), vget_high_u32(bad));
        if (vget_lane_u32(vpmax_u32(any, any), 0)) return 0;
        VU_ST(t, vfo(r));
        return 1;
    }
    { /* session 147: the MAC bits summed on NEON with a bad lane as 0x10000, one transfer to the core instead of
       * a store and a core load of each field (fout()'s O for an infinity, S for the sign, Z for an exact 0; U never here) */
        static const u32 wo[4] = { 0x8000, 0x4000, 0x2000, 0x1000 }, ws[4] = { 0x80, 0x40, 0x20, 0x10 }, wz[4] = { 8, 4, 2, 1 };
        uint32x4_t ex = vdupq_n_u32(0x7F800000u);
        uint32x4_t ov = vandq_u32(vceqq_u32(vandq_u32(ru, ex), ex), VU_LD(wo));
        uint32x4_t sg = vandq_u32(vtstq_u32(ru, vdupq_n_u32(0x80000000u)), VU_LD(ws));
        uint32x4_t v = vorrq_u32(vandq_u32(vorrq_u32(vorrq_u32(ov, sg), vandq_u32(zf, VU_LD(wz))), act),
                                 vandq_u32(bad, vdupq_n_u32(0x10000u)));
        any = vadd_u32(vget_low_u32(v), vget_high_u32(v));
        m = vget_lane_u32(vpadd_u32(any, any), 0);
    }
    if (m >> 16) return 0;
    VU_ST(t, vfo(r));
    *macf |= m;
    return 1;
}
static __inline__ __attribute__((always_inline)) int vu_ope(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, u32 dest, u32 *macf) {
    return vu_ek(t, k, vfin(VU_LD(a)), vfin(VU_LD(b)), c, dest, macf);
}
static __inline__ __attribute__((always_inline)) int vu_opbe(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, u32 dest, u32 *macf) {
    return vu_ek(t, k, vfin(VU_LD(a)), vfin(vdupq_n_u32(*b)), c, dest, macf);
}
static __inline__ __attribute__((always_inline)) int vu_opbel(u32 *t, int k, const u32 *a, const u32 *b, int l, const u32 *c, u32 dest, u32 *macf) {
    return vu_ek(t, k, vfin(VU_LD(a)), vreinterpretq_f32_u32(vu_lane(vreinterpretq_u32_f32(vfin(VU_LD(b))), l)), c, dest, macf);
}
/* session 147: an upper result's fields in dest (x the 8 bit) from u into t, on NEON: the A9 reads a word NEON
 * just stored slowly from the core, and u is always one */
/* session 147: clipw() of fs against ft.w on NEON: fkey's magnitude (Inf / NaN the largest, a denormal 0) compared
 * unsigned with w's, the sign then picking the + or - bit; one transfer to the core for the six bits instead of a
 * core load of each field an FMAC just stored */
static __inline__ u32 vu_clipw(const u32 *s, const u32 *t) {
    static const u32 wp[4] = { 1, 4, 16, 0 }, wn[4] = { 2, 8, 32, 0 };
    uint32x4_t u = VU_LD(s), w = VU_LD(t), lim = vdupq_n_u32(0x7F7FFFFFu), ex = vdupq_n_u32(0x7F800000u);
    uint32x4_t m = vandq_u32(vminq_u32(vandq_u32(u, vdupq_n_u32(0x7FFFFFFFu)), lim), vtstq_u32(u, ex));
    uint32x4_t wm = vandq_u32(vminq_u32(vandq_u32(w, vdupq_n_u32(0x7FFFFFFFu)), lim), vtstq_u32(w, ex));
    uint32x4_t gt = vcgtq_u32(m, vu_lane(wm, 3)), neg = vreinterpretq_u32_s32(vshrq_n_s32(vreinterpretq_s32_u32(u), 31));
    uint32x4_t b = vorrq_u32(vandq_u32(vbicq_u32(gt, neg), VU_LD(wp)), vandq_u32(vandq_u32(gt, neg), VU_LD(wn)));
    uint32x2_t h = vadd_u32(vget_low_u32(b), vget_high_u32(b));
    h = vpadd_u32(h, h);
    return ((clip_last << 6) | vget_lane_u32(h, 0)) & 0xFFFFFF;
}
static __inline__ void vu_put(u32 *t, const u32 *u, u32 dest) {
    if ((dest & 15) == 15) VU_ST(t, VU_LD(u));
    else VU_ST(t, vbslq_u32(VU_LD(vu_lanes[dest & 15]), VU_LD(u), VU_LD(t)));
}
static __inline__ void vu_itof(u32 *t, const u32 *a, int sc) {
    static const f32 inv[4] = { 1.0f, 1.0f / 16.0f, 1.0f / 4096.0f, 1.0f / 32768.0f };
    VU_ST(t, vreinterpretq_u32_f32(vmulq_n_f32(vcvtq_f32_s32(vreinterpretq_s32_u32(VU_LD(a))), inv[sc])));
}
static __inline__ void vu_ftoi(u32 *t, const u32 *a, int sc) {
    static const f32 mul[4] = { 1.0f, 16.0f, 4096.0f, 32768.0f };
    VU_ST(t, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(vfin(VU_LD(a)), mul[sc]))));
}
#else
static __inline__ f32 sin1(u32 u, int fi) {
    Fu x;
    if (fi) return fin(u);
    x.u = u;
    return x.f;
}
static __inline__ __attribute__((always_inline)) void vu_op(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, int fa, int fb, int fc) {
    int f;
    for (f = 0; f < 4; f++) {
        f32 x = sin1(a[f], fa), y = sin1(b[f], fb);
        switch (k) {
        case K_ADD: t[f] = fo(x + y); break;
        case K_SUB: t[f] = fo(x - y); break;
        case K_MUL: t[f] = fo(x * y); break;
        case K_MADD: t[f] = fo(sin1(c[f], fc) + x * y); break;
        case K_MSUB: t[f] = fo(sin1(c[f], fc) - x * y); break;
        case K_MAX: t[f] = fo(x > y ? x : y); break;
        default: t[f] = fo(x < y ? x : y); break;
        }
    }
}
static __inline__ __attribute__((always_inline)) void vu_opb(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, int fa, int fb, int fc) {
    u32 bb[4];
    bb[0] = bb[1] = bb[2] = bb[3] = *b;
    vu_op(t, k, a, bb, c, fa, fb, fc);
}
static __inline__ __attribute__((always_inline)) void vu_opbl(u32 *t, int k, const u32 *a, const u32 *b, int l, const u32 *c, int fa, int fb, int fc) {
    vu_opb(t, k, a, b + l, c, fa, fb, fc);
}
static __inline__ u32 vu_clipw(const u32 *s, const u32 *t) { return clipw(s, t[3]); }
static __inline__ void vu_put(u32 *t, const u32 *u, u32 dest) {
    int f;
    for (f = 0; f < 4; f++)
        if (dest >> (3 - f) & 1) t[f] = u[f];
}
/* session 141: the scalar form runs (see the NEON vu_ope) */
static __inline__ __attribute__((always_inline)) int vu_ope(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, u32 dest, u32 *macf) { return 0; }
static __inline__ __attribute__((always_inline)) int vu_opbe(u32 *t, int k, const u32 *a, const u32 *b, const u32 *c, u32 dest, u32 *macf) { return 0; }
static __inline__ __attribute__((always_inline)) int vu_opbel(u32 *t, int k, const u32 *a, const u32 *b, int l, const u32 *c, u32 dest, u32 *macf) { return 0; }
static __inline__ void vu_itof(u32 *t, const u32 *a, int sc) {
    static const f32 d[4] = { 1.0f, 16.0f, 4096.0f, 32768.0f };
    int f;
    for (f = 0; f < 4; f++) t[f] = itof(a[f], d[sc]);
}
static __inline__ void vu_ftoi(u32 *t, const u32 *a, int sc) {
    static const f32 d[4] = { 1.0f, 16.0f, 4096.0f, 32768.0f };
    int f;
    for (f = 0; f < 4; f++) t[f] = ftoi(a[f], d[sc]);
}
#endif

/* ------------------------------------------------------------------ the translated programs */

/* KH1_VU1_TR: out/gen/vu1_tr.c, tools/vu/vu1_translate.py's C of the user's own programs (never
 * committed).  A run whose micro memory holds one of them, from one of its entries, runs that C:
 * the same state and helpers as the interpreter, its timing worked out at build time */
int kh1_vu1_tr = 1;   /* 0: always the interpreter; 2: both, every run, compared (kh1_vu1_tr_check) */
static int tr_lost;   /* a JR went somewhere the translation did not expect */
typedef struct {
    const u32 *w;
    u32 n;
    int (*run)(u32 pc);
    int num; /* the program's number (tools/vu/find_vu1.py's list) */
} TrProg;
#ifdef KH1_VU1_TR
#include "vu1_tr.c"
#else
static const TrProg tr_progs[1] = { { 0, 0, 0, 0 } };
#define TR_PROGS 0
#endif
#include "vu1_nat.h"
#include "vu1_draw.h"
/* the program's C: the hand-written one (vu1_nat.h) where there is one for this entry and case, else the translation */
static int tr_go(int prog, u32 pc) {
    int (*f)(u32) = nat_run(tr_progs[prog].num);
    if (f && f(pc)) return 1;
    return tr_progs[prog].run(pc);
}
static u32 tr_us[KH1_VU1_PROGS], tr_runs[KH1_VU1_PROGS], tr_pairs[KH1_VU1_PROGS];
int kh1_vu1_prog_stats(int i, int *num, u32 *us, u32 *runs, u32 *pairs) {
    if (i < 0 || i >= TR_PROGS || i >= KH1_VU1_PROGS) return 0;
    *num = tr_progs[i].num;
    *us = tr_us[i];
    *runs = tr_runs[i];
    *pairs = tr_pairs[i];
    return 1;
}
static int tr_cur = -1;
static u32 tr_gen = ~0u;

static int tr_find(void) {
    int i, best = -1;
    if (tr_gen == micro_gen) return tr_cur;
    tr_gen = micro_gen;
    for (i = 0; i < TR_PROGS; i++)
        if ((best < 0 || tr_progs[i].n > tr_progs[best].n) && !memcmp(micro, tr_progs[i].w, tr_progs[i].n * 8)) best = i;
    return tr_cur = best;
}

/* kh1_vu1_tr == 2: the translation and the interpreter from the same state, every result compared */
typedef struct {
    u32 mem[DATA_QW][4], vf[32][4], acc[4], r[11];
    u16 vi[16];
} TrSnap;
static TrSnap tr_a, tr_b;
static u32 tr_hash, tr_bad;
static void (*tr_out)(const u32 *q, u32 nqw);
int sprintf(char *, const char *, ...);
void *fopen(const char *, const char *);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int fclose(void *);
static void tr_hash_kick(const u32 *q, u32 nqw) {
    u32 i;
    for (i = 0; i < nqw * 4; i++) tr_hash = (tr_hash ^ q[i]) * 16777619u;
    if (tr_out) tr_out(q, nqw);
}
static void tr_save(TrSnap *t) {
    memcpy(t->mem, mem, sizeof mem);
    memcpy(t->vf, vf, sizeof vf);
    memcpy(t->acc, acc, sizeof acc);
    memcpy(t->vi, vi, sizeof vi);
    t->r[0] = q_reg; t->r[1] = p_reg; t->r[2] = i_reg; t->r[3] = r_reg;
    t->r[4] = mac_now; t->r[5] = clip_now; t->r[6] = clip_last; t->r[7] = tpc;
    t->r[8] = top; t->r[9] = itop; t->r[10] = tr_hash;
}
static void tr_load(const TrSnap *t) {
    memcpy(mem, t->mem, sizeof mem);
    memcpy(vf, t->vf, sizeof vf);
    memcpy(acc, t->acc, sizeof acc);
    memcpy(vi, t->vi, sizeof vi);
    q_reg = t->r[0]; p_reg = t->r[1]; i_reg = t->r[2]; r_reg = t->r[3];
    mac_now = t->r[4]; clip_now = t->r[5]; clip_last = t->r[6]; tpc = t->r[7];
}
static void tr_check(int prog, u32 pc) {
    static const char *names[11] = { "Q", "P", "I", "R", "MAC", "clip", "clip_last", "tpc", "top", "itop", "the kicks" };
    static char buf[32];
    void (*out)(const u32 *, u32) = kh1_vu1_kick;
    KH1Vu1Stats keep = st;
    const char *what = 0;
    u32 i, f;
    int ok;
    tr_save(&tr_a);
    kh1_vu1_kick = tr_hash_kick;
    tr_out = 0;
    tr_hash = 2166136261u;
    tr_lost = 0;
    ok = tr_go(prog, pc);
    tr_save(&tr_b);
    st = keep;
    tr_load(&tr_a);
    tr_out = out;
    tr_hash = 2166136261u;
    run(pc);
    settle();
    kh1_vu1_kick = out;
    if (!ok) return;
    tr_save(&tr_a);
    if (tr_lost) what = "lost (a JR)";
    for (i = 0; !what && i < 11; i++) if (tr_a.r[i] != tr_b.r[i]) what = names[i];
    for (i = 0; !what && i < 16; i++) if (tr_a.vi[i] != tr_b.vi[i]) { sprintf(buf, "vi%02u", i); what = buf; }
    for (i = 0; !what && i < 32; i++)
        for (f = 0; f < 4; f++) if (!what && tr_a.vf[i][f] != tr_b.vf[i][f]) { sprintf(buf, "vf%02u%c", i, "xyzw"[f]); what = buf; }
    for (f = 0; !what && f < 4; f++) if (tr_a.acc[f] != tr_b.acc[f]) what = "ACC";
    for (i = 0; !what && i < DATA_QW; i++)
        for (f = 0; f < 4; f++) if (!what && tr_a.mem[i][f] != tr_b.mem[i][f]) { sprintf(buf, "mem %03x", i); what = buf; }
    st.tr_checked++;
    if (what) {
        st.tr_differ++;
        if (tr_bad++ < 20) printf("kh1-vu1: translated program P%d from %03x differs from the interpreter: %s\n", tr_progs[prog].num, pc, what);
    }
}

/* kh1_vu1_native == 2 (KH1_HOST_VU1NAT=2 / vu1nat=2): a program written by hand runs, then the translation from
 * the same state, every result compared as tr_check() does, the pairs and cycles too (the counts tr_checked /
 * tr_differ); the translation's run is the one kept.  Answers 0 where there is no native form or it gave the run up */
static int nat_check(int prog, u32 pc) {
    static const char *names[11] = { "Q", "P", "I", "R", "MAC", "clip", "clip_last", "tpc", "top", "itop", "the kicks" };
    static char buf[32];
    int (*f)(u32) = nat_run(tr_progs[prog].num);
    void (*out)(const u32 *, u32) = kh1_vu1_kick;
    KH1Vu1Stats keep = st, got;
    const char *what = 0;
    u32 i, k;
    if (!f) return 0;
    tr_hash = 2166136261u;
    tr_save(&tr_a);
    kh1_vu1_kick = tr_hash_kick;
    tr_out = 0;
    if (!f(pc)) {
        kh1_vu1_kick = out;
        st = keep;
        return 0;
    }
    tr_save(&tr_b);
    got = st;
    st = keep;
    tr_load(&tr_a);
    tr_out = out;
    tr_hash = 2166136261u;
    tr_lost = 0;
    tr_progs[prog].run(pc);
    kh1_vu1_kick = out;
    tr_save(&tr_a);
    if (got.insns != st.insns) what = "pairs";
    else if (got.cycles != st.cycles) what = "cycles";
    for (i = 0; !what && i < 11; i++) if (tr_a.r[i] != tr_b.r[i]) what = names[i];
    for (i = 0; !what && i < 16; i++) if (tr_a.vi[i] != tr_b.vi[i]) { sprintf(buf, "vi%02u", i); what = buf; }
    for (i = 0; !what && i < 32; i++)
        for (k = 0; k < 4; k++) if (!what && tr_a.vf[i][k] != tr_b.vf[i][k]) { sprintf(buf, "vf%02u%c", i, "xyzw"[k]); what = buf; }
    for (k = 0; !what && k < 4; k++) if (tr_a.acc[k] != tr_b.acc[k]) what = "ACC";
    for (i = 0; !what && i < DATA_QW; i++)
        for (k = 0; k < 4; k++) if (!what && tr_a.mem[i][k] != tr_b.mem[i][k]) { sprintf(buf, "mem %03x", i); what = buf; }
    st.tr_checked++;
    if (what) {
        st.tr_differ++;
        if (tr_bad++ < 20) printf("kh1-vu1: native P%d from %03x differs from the translation: %s\n", tr_progs[prog].num, pc, what);
    }
    return 1;
}

static void start_run(u32 pc);
static void start(u32 pc) {
    u32 t0;
    if (!kh1_vu1_clock) {
        start_run(pc);
        return;
    }
    t0 = kh1_vu1_clock();
    start_run(pc);
    kh1_vu1_us += kh1_vu1_clock() - t0;
}

/* KH1_HOST_VU1DUMP=DIR:N (host/null/main.c): every Nth run's start (micro memory, then a TrSnap, then the
 * pc), for tools that replay runs offline (the NEON check under qemu-arm).  The files hold the user's own
 * programs and data: scratch only, never committed */
const char *kh1_vu1_dump_dir;
u32 kh1_vu1_dump_every;
static void dump_run(u32 pc) {
    static u32 n, k;
    char path[256];
    void *f;
    if (++n % kh1_vu1_dump_every) return;
    sprintf(path, "%s/vu%05u.bin", kh1_vu1_dump_dir, k++);
    f = fopen(path, "wb");
    if (!f) return;
    tr_save(&tr_a);
    fwrite(micro, sizeof micro, 1, f);
    fwrite(&tr_a, sizeof tr_a, 1, f);
    fwrite(&pc, sizeof pc, 1, f);
    fclose(f);
}

static void start_run(u32 pc) {
    int prog;
    top = tops;
    itop = itops;
    if (dbf) { dbf = 0; tops = base; }
    else { dbf = 1; tops = (base + ofst) & (DATA_QW - 1); }
    settle();
    if (kh1_vu1_dump_dir && kh1_vu1_dump_every) dump_run(pc);
    prog = kh1_vu1_tr && !kh1_vu1_verbose ? tr_find() : -1;
    if (prog >= 0 && kh1_vu1_tr == 2) {
        tr_check(prog, pc);
        return;
    }
    if (prog >= 0) {
        u32 t0 = kh1_vu1_clock ? kh1_vu1_clock() : 0, n0 = st.insns;
        int ran;
        tr_lost = 0;
        /* the native renderer (vu1_draw.h): the run's records handed to the GPU instead */
        ran = kh1_vu1_draw && ((tr_progs[prog].num == 18 && nd_18(pc, 18)) ||
                                (tr_progs[prog].num == 11 && kh1_vu1_draw_p11 && nd_18(pc, 11)) ||
                                (tr_progs[prog].num == 0 && kh1_vu1_draw_p0 && nd_0(pc, 0)) ||
                                (tr_progs[prog].num == 4 && kh1_vu1_draw_p0 && nd_0(pc, 1)));
        if (!ran && kh1_vu1_natcheck && (tr_progs[prog].num == 0 || tr_progs[prog].num == 4)) { /* KH1_HOST_NATCHECK */
            void (*sv)(const u32 *, u32) = kh1_vu1_draw;
            kh1_vu1_draw = 0;
            if (!nd_0(pc, tr_progs[prog].num == 4)) {
                ran = tr_go(prog, pc);
                nd_0_check();
            }
            kh1_vu1_draw = sv;
        }
        if (!ran && kh1_vu1_native == 2) ran = nat_check(prog, pc);
        if (!ran) ran = tr_go(prog, pc);
        if (kh1_vu1_clock && prog < KH1_VU1_PROGS) { /* session 147: each program's own time (the Vita's watchdog) */
            tr_us[prog] += kh1_vu1_clock() - t0;
            tr_runs[prog]++;
            tr_pairs[prog] += st.insns - n0;
        }
        if (ran) {
            st.runs++;
            st_runs_all++;
            st.tr_runs++;
            if (tr_lost && !tr_bad++) printf("kh1-vu1: translated program P%d lost its way (a JR)\n", tr_progs[prog].num);
            return;
        }
    }
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

/* session 143: element e of the data words, 32, 16 or 8 bits (vl 0, 1, 2), sign-extended unless usn */
static __inline__ u32 unpack_el(u32 vl, u32 usn, u32 e) {
    u32 h;
    if (vl == 0) return dbuf[e];
    if (vl == 1) {
        h = dbuf[e >> 1] >> (e & 1) * 16 & 0xFFFF;
        return !usn && h & 0x8000 ? h | 0xFFFF0000u : h;
    }
    h = dbuf[e >> 2] >> (e & 3) * 8 & 0xFF;
    return !usn && h & 0x80 ? h | 0xFFFFFF00u : h;
}

#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
/* session 151: unpack_run on NEON: a vector's elements read as one load (V3: the next element as w; V2: x and y
 * twice; V1: x four times), widened with or without the sign, ROW added or accumulated in a register.  The game
 * thread's unpacks were ~10% of its instructions under qemu-arm in the Dive, an element at a time */
static __inline__ __attribute__((always_inline)) void unpack_run(u32 vn, u32 vl, u32 num, u32 usn, u32 addr) {
    u32 nel = vn + 1, i, cycle = 0, e = 0, x;
    const u8 *b = (const u8 *)dbuf;
    uint32x4_t r = vld1q_u32(row), v;
    for (i = 0; i < num; i++, e += nel) {
        if (vl == 0) {
            if (vn >= 2) v = vld1q_u32(dbuf + e);
            else if (vn == 1) {
                uint32x2_t t = vld1_u32(dbuf + e);
                v = vcombine_u32(t, t);
            } else v = vdupq_n_u32(dbuf[e]);
        } else if (vl == 1) {
            const u16 *h = (const u16 *)b + e;
            uint16x4_t t;
            if (vn >= 2) t = vld1_u16(h);
            else if (vn == 1) t = vreinterpret_u16_u32(vdup_n_u32((u32)h[0] | (u32)h[1] << 16));
            else t = vdup_n_u16(h[0]);
            v = usn ? vmovl_u16(t) : vreinterpretq_u32_s32(vmovl_s16(vreinterpret_s16_u16(t)));
        } else {
            const u8 *c = b + e;
            uint16x4_t t;
            if (vn >= 2) x = (u32)c[0] | (u32)c[1] << 8 | (u32)c[2] << 16 | (u32)c[3] << 24;
            else if (vn == 1) x = ((u32)c[0] | (u32)c[1] << 8) * 0x10001u;
            else x = c[0] * 0x01010101u;
            if (usn) t = vget_low_u16(vmovl_u8(vcreate_u8(x)));
            else t = vreinterpret_u16_s16(vget_low_s16(vmovl_s8(vcreate_s8(x))));
            v = usn ? vmovl_u16(t) : vreinterpretq_u32_s32(vmovl_s16(vreinterpret_s16_u16(t)));
        }
        if (mode == 1) v = vaddq_u32(v, r);
        else if (mode == 2) v = r = vaddq_u32(r, v);
        vst1q_u32(mem[addr & (DATA_QW - 1)], v);
        addr++;
        if (++cycle == wl) { addr += cl - wl; cycle = 0; }
    }
    if (mode == 2) vst1q_u32(row, r);
}
#else
/* session 143: unpack_fast's loop when every element it reads is here, one copy per format (vn, vl constants
 * at each call) so that no test of the format or of the data's end runs an element */
static __inline__ __attribute__((always_inline)) void unpack_run(u32 vn, u32 vl, u32 num, u32 usn, u32 addr) {
    u32 nel = vn + 1, i, cycle = 0, e = 0, v[4], *d;
    for (i = 0; i < num; i++, e += nel) {
        v[0] = unpack_el(vl, usn, e);
        if (vn >= 1) v[1] = unpack_el(vl, usn, e + 1);
        if (vn >= 2) {
            v[2] = unpack_el(vl, usn, e + 2);
            v[3] = unpack_el(vl, usn, e + 3); /* V3: w is the next element in the stream */
        }
        if (vn == 0) v[1] = v[2] = v[3] = v[0];
        else if (vn == 1) { v[2] = v[0]; v[3] = v[1]; }
        d = mem[addr & (DATA_QW - 1)];
        if (mode == 1) { d[0] = v[0] + row[0]; d[1] = v[1] + row[1]; d[2] = v[2] + row[2]; d[3] = v[3] + row[3]; }
        else if (mode == 2) { d[0] = row[0] += v[0]; d[1] = row[1] += v[1]; d[2] = row[2] += v[2]; d[3] = row[3] += v[3]; }
        else { d[0] = v[0]; d[1] = v[1]; d[2] = v[2]; d[3] = v[3]; }
        addr++;
        if (++cycle == wl) { addr += cl - wl; cycle = 0; }
    }
}
#endif

/* Session 137v (the Dive's speed on a Vita): the unmasked V1 / V2 / V3 / V4 of 32, 16 and 8 bits with no
 * filling cycle (WL <= CL), unpack's loop without a call an element; 0 for the rest, which unpack does */
static int unpack_fast(u32 vn, u32 vl, u32 num, u32 usn, u32 addr) {
    u32 nel = vn + 1, i, k, cycle = 0, v[4], e;
    if (vl == 3 || wl > cl) return 0;
    /* V4-32 / V3-32 with all their words here, MODE 0, CL == WL: the words themselves */
    if (vl == 0 && vn >= 2 && mode == 0 && cl == wl && num * nel + (vn == 2) <= got) {
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
        for (i = 0; i < num; i++) vst1q_u32(mem[(addr + i) & (DATA_QW - 1)], vld1q_u32(dbuf + i * nel)); /* no call a qword */
#else
        for (i = 0; i < num; i++) memcpy(mem[(addr + i) & (DATA_QW - 1)], dbuf + i * nel, 16);
#endif
        return 1;
    }
    /* session 143: the last element read, (num - 1) * nel + (V3 ? 3 : nel - 1), is inside the got words */
    if ((num - 1) * nel + (vn == 2 ? 4 : nel) <= got << vl) {
        switch (vl << 2 | vn) {
        case 0x0: unpack_run(0, 0, num, usn, addr); return 1;
        case 0x1: unpack_run(1, 0, num, usn, addr); return 1;
        case 0x2: unpack_run(2, 0, num, usn, addr); return 1;
        case 0x3: unpack_run(3, 0, num, usn, addr); return 1;
        case 0x4: unpack_run(0, 1, num, usn, addr); return 1;
        case 0x5: unpack_run(1, 1, num, usn, addr); return 1;
        case 0x6: unpack_run(2, 1, num, usn, addr); return 1;
        case 0x7: unpack_run(3, 1, num, usn, addr); return 1;
        case 0x8: unpack_run(0, 2, num, usn, addr); return 1;
        case 0x9: unpack_run(1, 2, num, usn, addr); return 1;
        case 0xA: unpack_run(2, 2, num, usn, addr); return 1;
        case 0xB: unpack_run(3, 2, num, usn, addr); return 1;
        }
    }
    for (i = 0; i < num; i++) {
        u32 *d = mem[addr & (DATA_QW - 1)];
        for (k = 0; k < (vn == 2 ? 4u : nel); k++) { /* V3: w is the next element in the stream */
            e = i * nel + k;
            if (vl == 0) v[k] = e < got ? dbuf[e] : 0;
            else if (vl == 1) {
                u32 h = (e >> 1) < got ? dbuf[e >> 1] >> (e & 1) * 16 & 0xFFFF : 0;
                v[k] = !usn && h & 0x8000 ? h | 0xFFFF0000u : h;
            } else {
                u32 b = (e >> 2) < got ? dbuf[e >> 2] >> (e & 3) * 8 & 0xFF : 0;
                v[k] = !usn && b & 0x80 ? b | 0xFFFFFF00u : b;
            }
        }
        if (vn == 0) v[1] = v[2] = v[3] = v[0];
        else if (vn == 1) { v[2] = v[0]; v[3] = v[1]; } /* V2: z and w repeat x and y (PCSX2's unpack) */
        if (mode == 1) for (k = 0; k < 4; k++) d[k] = v[k] + row[k];
        else if (mode == 2) for (k = 0; k < 4; k++) d[k] = row[k] += v[k];
        else for (k = 0; k < 4; k++) d[k] = v[k];
        addr++;
        cycle++;
        if (cycle == wl) { addr += cl - wl; cycle = 0; }
    }
    return 1;
}

static void unpack(void) {
    u32 cmd = cur, vn = cmd >> 2 & 3, vl = cmd & 3, m = cmd & 0x10;
    u32 num = cur_num ? cur_num : 256, usn = cur_imm >> 14 & 1;
    u32 addr = (cur_imm & 0x3FF) + (cur_imm & 0x8000 ? tops : 0);
    u32 ebits = vl == 3 ? 16 : 32 >> vl, nel = vl == 3 ? 1 : vn + 1, cycle = 0, di = 0, i, f;
    st.unpacks++;
    if (!m && unpack_fast(vn, vl, num, usn, addr)) return;
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

/* session 137v: n of the current code's data words at once (the walk's run of them), as n calls of
 * kh1_vif1_data */
void kh1_vif1_data_n(const u32 *w, u32 n) {
    if ((cur == 0x50 || cur == 0x51) && n <= need) { /* session 143: DIRECT's words are the walk's (PATH2) */
        need -= n;
        return;
    }
    if ((cur & 0x60) == 0x60 && n <= need) {
        u32 k = got < sizeof dbuf / 4 ? sizeof dbuf / 4 - got : 0;
        memcpy(dbuf + got, w, (n < k ? n : k) * 4);
        got += n;
        need -= n;
        if (!need) unpack();
        return;
    }
    while (n--) kh1_vif1_data(*w++);
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
        if (!need) unpack();
    }
}
