/* The SPU2 off the PS2 (docs/sound-spec.md "The IOP on the port"): libsd's calls from the user's
 * sound driver (host/port/iop.c) answered against a model of the SPU2's two cores, mixed to 48 kHz
 * stereo by kh1_spu2_mix.
 *
 *   - 2 MiB of sound RAM; sceSdVoiceTrans copies IOP RAM into it (or back) at once and raises the
 *     transfer interrupt the driver set;
 *   - 48 voices (24 a core): SPU ADPCM (16-byte blocks of 28 samples, the five filters, the loop
 *     start / end / repeat flags and ENDX), the pitch counter (0x1000 = 48 kHz), a 4-point cubic
 *     interpolation (the SPU2's own is a Gaussian table, not reproduced), the ADSR envelope (the
 *     PSX / PS2 rate and step rules, ENVX readable), fixed or sweeping volumes, VMIXL / VMIXR;
 *   - each core's voices summed and scaled by its master volume; core 0's output is core 1's
 *     external input (AVOL), as the PS2's DAC hears it;
 *   - reverb: the PSX / PS2 algorithm (same-side and cross reflections, four combs, two all-pass
 *     filters) at half rate, on the voices with VMIXEL / VMIXER, scaled by EVOL, with the preset of
 *     the mode sceSdSetEffectAttr picks.  The presets are libsd's own table, read at run time from
 *     the disc's LIBSD.IRX (kh1_spu2_find_presets); without it the reverb stays off.  The work area
 *     is the model's own buffer, not sound RAM (the driver keeps its waves out of it anyway).
 *
 *   - the noise generator (the PSX / PS2 one, a core's clock from sceSdSetCoreAttr SD_C_NOISE_CLK): a
 *     voice with its NON bit plays the core's noise in place of its wave, under its envelope;
 *
 * Not modelled: pitch modulation, the core sound-data input (sceSdBlockTrans:
 * the movie's PCM), the SPU2's IRQ address, the echo / delay modes' delay and feedback.  Not part of
 * the PS2 build. */
#include "common.h"
#include "iop.h"
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

int printf(const char *, ...);
void *memcpy(void *, const void *, unsigned int);
void *memset(void *, int, unsigned int);

#define SPU_RAM 0x200000

typedef struct {
    s32 counter;
    s32 step;
    u32 inc;
    u8 rate, dec, exp;
} Env;

enum { PH_OFF, PH_ATTACK, PH_DECAY, PH_SUSTAIN, PH_RELEASE };

typedef struct {
    u16 voll, volr, pitch, adsr1, adsr2;
    u32 ssa, lsa, nax; /* byte addresses in sound RAM */
    u8 lsa_written, lsa_manual;
    u8 phase, flags;
    s32 env;
    Env adsr;
    s32 vol[2];       /* the current volumes (fixed, or where a sweep has got to) */
    Env sweep[2];
    u32 counter;      /* pitch counter: 12 bits of fraction */
    s16 dec[28];      /* the block being played */
    int idx;          /* next sample in dec[] (28: decode the next block) */
    s32 hist1, hist2; /* ADPCM history */
    s16 s[4];         /* the last four samples, for the interpolation */
} Voice;

typedef struct {
    Voice v[24];
    u32 vmixl, vmixr, vmixel, vmixer, pmon, non, endx;
    u16 mmix, mvoll, mvolr, evoll, evolr, avoll, avolr, bvoll, bvolr;
    u32 esa, eea, irqa;
    u16 fx_on;
    s32 fx_mode, fx_delay, fx_feedback, fx_depth_l, fx_depth_r;
    u16 noise_clk;  /* SD_C_NOISE_CLK: bits 0-1 the step - 4, bits 2-5 the shift */
    u16 noise_lvl;
    s32 noise_timer;
} Core;

/* the reverb's work area (in samples, a power of two past the largest preset's reach) and its
 * half-rate state */
#define RV_SIZE 0x20000
typedef struct {
    s16 buf[RV_SIZE];
    u32 pos;
    s32 in[2], out[2], prev[2];
    int phase;
} Reverb;
static Reverb rv[2];
static u16 rv_preset[10][32];
static int rv_have;

static u8 spu_ram[SPU_RAM];
static Core core[2];

/* ---- envelopes ---- */

static void env_set(Env *e, int rate, int dec, int exp) {
    e->rate = (u8)rate;
    e->dec = (u8)dec;
    e->exp = (u8)exp;
    e->counter = 0;
    e->step = dec ? -8 + (rate & 3) : 7 - (rate & 3);
    e->inc = 0x8000;
    if (rate < 44) e->step *= 1 << (11 - (rate >> 2));
    else if (rate >= 48) e->inc >>= (rate >> 2) - 11;
}

static __inline__ __attribute__((always_inline)) s32 env_tick(Env *e, s32 level) {
    s32 step = e->step;
    u32 inc = e->inc;
    if (e->exp) {
        if (e->dec) step = (step * level) >> 15;
        else if (level >= 0x6000) {
            if (e->rate < 40) step >>= 2;
            else if (e->rate >= 44) inc >>= 2;
            else { step >>= 1; inc >>= 1; }
        }
    }
    e->counter += (s32)inc;
    if (!(e->counter & 0x8000)) return level;
    e->counter = 0;
    level += step;
    if (level < 0) level = 0;
    if (level > 0x7FFF) level = 0x7FFF;
    return level;
}

static void adsr_phase(Voice *v, int ph) {
    v->phase = (u8)ph;
    switch (ph) {
    case PH_ATTACK: env_set(&v->adsr, (v->adsr1 >> 8) & 0x7F, 0, v->adsr1 >> 15); break;
    case PH_DECAY: env_set(&v->adsr, ((v->adsr1 >> 4) & 0xF) << 2, 1, 1); break;
    case PH_SUSTAIN: env_set(&v->adsr, (v->adsr2 >> 6) & 0x7F, (v->adsr2 >> 14) & 1, v->adsr2 >> 15); break;
    case PH_RELEASE: env_set(&v->adsr, (v->adsr2 & 0x1F) << 2, 1, (v->adsr2 >> 5) & 1); break;
    }
}

static __inline__ __attribute__((always_inline)) void adsr_tick(Voice *v) {
    s32 sl;
    switch (v->phase) {
    case PH_ATTACK:
        v->env = env_tick(&v->adsr, v->env);
        if (v->env >= 0x7FFF) adsr_phase(v, PH_DECAY);
        break;
    case PH_DECAY:
        v->env = env_tick(&v->adsr, v->env);
        sl = ((v->adsr1 & 0xF) + 1) * 0x800;
        if (sl > 0x7FFF) sl = 0x7FFF;
        if (v->env <= sl) adsr_phase(v, PH_SUSTAIN);
        break;
    case PH_SUSTAIN:
        v->env = env_tick(&v->adsr, v->env);
        break;
    case PH_RELEASE:
        v->env = env_tick(&v->adsr, v->env);
        if (v->env == 0) v->phase = PH_OFF;
        break;
    }
}

/* a volume register: bit 15 clear, a fixed 15-bit value; set, a sweep (bit 14 exponential, 13
 * decreasing, 12 negative phase, 6-0 the rate) */
static void vol_set(Voice *v, int side, u16 reg) {
    if (!(reg & 0x8000)) {
        v->vol[side] = (s16)(reg << 1);
        return;
    }
    env_set(&v->sweep[side], reg & 0x7F, (reg >> 13) & 1, (reg >> 14) & 1);
}

static __inline__ __attribute__((always_inline)) void vol_tick(Voice *v, int side, u16 reg) {
    s32 lv;
    if (!(reg & 0x8000)) return;
    lv = v->vol[side] < 0 ? -v->vol[side] : v->vol[side];
    lv = env_tick(&v->sweep[side], lv);
    v->vol[side] = (reg & 0x1000) ? -lv : lv;
}

/* ---- ADPCM ---- */

static const s32 adpcm_f0[5] = { 0, 60, 115, 98, 122 };
static const s32 adpcm_f1[5] = { 0, 0, -52, -55, -60 };

static void decode_block(Voice *v, int c, int n) {
    const u8 *b = spu_ram + (v->nax & (SPU_RAM - 16) & ~15u);
    int shift = b[0] & 15, filt = (b[0] >> 4) & 7, i;
    s32 f0, f1, h1 = v->hist1, h2 = v->hist2;
    s16 *d = v->dec;
    if (shift > 12) shift = 9;
    if (filt > 4) filt = 4;
    f0 = adpcm_f0[filt];
    f1 = adpcm_f1[filt];
    v->flags = b[1];
    if ((v->flags & 4) && !v->lsa_manual) v->lsa = v->nax & ~15u;
    /* the history in locals (the stores into dec[] would make the compiler reload it from the voice) */
    for (i = 0; i < 28; i += 2) {
        u32 by = b[2 + i / 2];
        s32 s = ((s32)(s16)(by << 12)) >> shift;
        s += (h1 * f0 + h2 * f1 + 32) >> 6;
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        h2 = h1;
        h1 = s;
        d[i] = (s16)s;
        s = ((s32)(s16)((by >> 4) << 12)) >> shift;
        s += (h1 * f0 + h2 * f1 + 32) >> 6;
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        h2 = h1;
        h1 = s;
        d[i + 1] = (s16)s;
    }
    v->hist1 = h1;
    v->hist2 = h2;
    (void)c;
    (void)n;
}

/* the block just played has ended: follow its flags */
static void block_end(Voice *v, int c, int n) {
    if (v->flags & 1) {
        core[c].endx |= 1u << n;
        v->nax = v->lsa;
        if (!(v->flags & 2)) {
            v->phase = PH_RELEASE;
            v->env = 0;
            v->phase = PH_OFF;
        }
    } else {
        v->nax = (v->nax + 16) & (SPU_RAM - 1);
    }
}

static s16 next_sample(Voice *v, int c, int n) {
    if (v->idx >= 28) {
        if (v->idx != 99) block_end(v, c, n);
        decode_block(v, c, n);
        v->idx = 0;
    }
    return v->dec[v->idx++];
}

static void key_on(int c, int n) {
    Voice *v = &core[c].v[n];
    v->lsa_manual = v->lsa_written;
    v->lsa_written = 0;
    v->nax = v->ssa & ~15u;
    v->idx = 99; /* decode from SSA without a block end first */
    v->counter = 0;
    v->hist1 = v->hist2 = 0;
    v->s[0] = v->s[1] = v->s[2] = v->s[3] = 0;
    v->env = 0;
    adsr_phase(v, PH_ATTACK);
    core[c].endx &= ~(1u << n);
}

static void key_off(int c, int n) {
    Voice *v = &core[c].v[n];
    if (v->phase != PH_OFF) adsr_phase(v, PH_RELEASE);
}

/* ---- mixing ---- */

/* Catmull-Rom between s[1] and s[2] at 256 steps (the pitch counter's top 8 fraction bits): four
 * 15-bit weights a step, made once (kh1_spu2_reset).  The console's own filter is Gaussian. */
static s32 interp_w[256][4];

static s32 round15(double x) { x *= 32768.0; return x >= 0 ? (s32)(x + 0.5) : -(s32)(0.5 - x); }

static void interp_init(void) {
    int i;
    for (i = 0; i < 256; i++) {
        double t = i / 256.0, t2 = t * t, t3 = t2 * t;
        interp_w[i][0] = round15((-t3 + 2 * t2 - t) * 0.5);
        interp_w[i][1] = round15((3 * t3 - 5 * t2 + 2) * 0.5);
        interp_w[i][2] = round15((-3 * t3 + 4 * t2 + t) * 0.5);
        interp_w[i][3] = round15((t3 - t2) * 0.5);
    }
}

static __inline__ __attribute__((always_inline)) s32 cubic(const s16 *s, u32 frac) {
    const s32 *w = interp_w[frac >> 4];
    s32 r = (s[0] * w[0] + s[1] * w[1] + s[2] * w[2] + s[3] * w[3]) >> 15;
    return r > 32767 ? 32767 : r < -32768 ? -32768 : r;
}

/* one 48 kHz sample of one voice, before its volumes: 0 for a voice that is off.  nz: the core's
 * noise for this sample when the voice's NON bit is set (the wave still plays on underneath, for its
 * loop and end flags) */
static __inline__ __attribute__((always_inline)) s32 voice_sample(Voice *v, int c, int n, const s16 *nz) {
    s32 out;
    u32 step;
    if (v->phase == PH_OFF) return 0;
    out = nz ? *nz : cubic(v->s, v->counter & 0xFFF);
    out = (out * v->env) >> 15;
    step = v->pitch > 0x3FFF ? 0x3FFF : v->pitch;
    v->counter += step;
    while (v->counter >= 0x1000) {
        v->counter -= 0x1000;
        v->s[0] = v->s[1];
        v->s[1] = v->s[2];
        v->s[2] = v->s[3];
        v->s[3] = next_sample(v, c, n);
        if (v->phase == PH_OFF) break;
    }
    adsr_tick(v);
    return out;
}

static s32 clamp16(s32 x) { return x > 32767 ? 32767 : x < -32768 ? -32768 : x; }

/* ---- reverb ---- */

/* libsd's presets (10 modes of 32 halfwords, 0x44 bytes apart, mode 1 "room" first after "off")
 * found in the user's LIBSD.IRX by the room preset's first three registers */
int kh1_spu2_find_presets(const u8 *irx, u32 size) {
    u32 i, m, k;
    for (i = 0x44; i + 9 * 0x44 + 64 <= size; i += 2) {
        if (irx[i] != 0x7D || irx[i + 1] || irx[i + 2] != 0x5B || irx[i + 3] || irx[i + 4] != 0x80 || irx[i + 5] != 0x6D)
            continue;
        for (m = 0; m < 10; m++)
            for (k = 0; k < 32; k++) {
                const u8 *p = irx + i + (m - 1) * 0x44 + 2 * k;
                rv_preset[m][k] = (u16)(p[0] | p[1] << 8);
            }
        rv_have = 1;
        return 0;
    }
    return -1;
}

#define RV(r, off) ((r)->buf[((r)->pos + (u32)(off)) & (RV_SIZE - 1)])
#define VR(i) ((s32)(s16)p[i])
#define MR(i) ((u32)p[i] * 4) /* an address register: 8-byte units, 4 samples */

/* one half-rate step of a core's reverb on its wet input; returns the output pair in r->out */
static void reverb_step(Reverb *r, const u16 *p, s32 evl, s32 evr) {
    /* the buffer and position in locals (RV through r reloads them after every store) */
    s16 *__restrict__ rb = r->buf;
    u32 rpos = r->pos;
#undef RV
#define RV(r, off) (rb[(rpos + (u32)(off)) & (RV_SIZE - 1)])
    s32 lin = (VR(30) * r->in[0]) >> 15, rin = (VR(31) * r->in[1]) >> 15;
    s32 viir = VR(2), vwall = VR(7), vapf1 = VR(8), vapf2 = VR(9), l, rr, t;
    /* same side, then cross reflections */
    t = (lin + ((RV(r, MR(16)) * vwall) >> 15) - RV(r, MR(10) - 1)) * viir >> 15;
    RV(r, MR(10)) = (s16)clamp16(t + RV(r, MR(10) - 1));
    t = (rin + ((RV(r, MR(17)) * vwall) >> 15) - RV(r, MR(11) - 1)) * viir >> 15;
    RV(r, MR(11)) = (s16)clamp16(t + RV(r, MR(11) - 1));
    t = (lin + ((RV(r, MR(25)) * vwall) >> 15) - RV(r, MR(18) - 1)) * viir >> 15;
    RV(r, MR(18)) = (s16)clamp16(t + RV(r, MR(18) - 1));
    t = (rin + ((RV(r, MR(24)) * vwall) >> 15) - RV(r, MR(19) - 1)) * viir >> 15;
    RV(r, MR(19)) = (s16)clamp16(t + RV(r, MR(19) - 1));
    /* the combs */
    l = (VR(3) * RV(r, MR(12)) + VR(4) * RV(r, MR(14)) + VR(5) * RV(r, MR(20)) + VR(6) * RV(r, MR(22))) >> 15;
    rr = (VR(3) * RV(r, MR(13)) + VR(4) * RV(r, MR(15)) + VR(5) * RV(r, MR(21)) + VR(6) * RV(r, MR(23))) >> 15;
    /* the two all-pass filters */
    l = clamp16(l - ((vapf1 * RV(r, MR(26) - MR(0))) >> 15));
    t = RV(r, MR(26) - MR(0));
    RV(r, MR(26)) = (s16)l;
    l = clamp16(((l * vapf1) >> 15) + t);
    rr = clamp16(rr - ((vapf1 * RV(r, MR(27) - MR(0))) >> 15));
    t = RV(r, MR(27) - MR(0));
    RV(r, MR(27)) = (s16)rr;
    rr = clamp16(((rr * vapf1) >> 15) + t);
    l = clamp16(l - ((vapf2 * RV(r, MR(28) - MR(1))) >> 15));
    t = RV(r, MR(28) - MR(1));
    RV(r, MR(28)) = (s16)l;
    l = clamp16(((l * vapf2) >> 15) + t);
    rr = clamp16(rr - ((vapf2 * RV(r, MR(29) - MR(1))) >> 15));
    t = RV(r, MR(29) - MR(1));
    RV(r, MR(29)) = (s16)rr;
    rr = clamp16(((rr * vapf2) >> 15) + t);
    r->prev[0] = r->out[0];
    r->prev[1] = r->out[1];
    r->out[0] = (l * evl) >> 15;
    r->out[1] = (rr * evr) >> 15;
    r->pos = (rpos + 1) & (RV_SIZE - 1);
#undef RV
#define RV(r, off) ((r)->buf[((r)->pos + (u32)(off)) & (RV_SIZE - 1)])
}

/* a core's wet pair at 48 kHz: steps at every other sample on the two inputs' average, the output
 * between the last two steps' */
static void reverb(int c, const s32 *wet, s32 *dry) {
    Core *k = &core[c];
    Reverb *r = &rv[c];
    if (!rv_have || !k->fx_on || k->fx_mode <= 0 || k->fx_mode > 9) return;
    r->in[0] += wet[0];
    r->in[1] += wet[1];
    if (r->phase ^= 1) {
        dry[0] += (r->prev[0] + r->out[0]) >> 1;
        dry[1] += (r->prev[1] + r->out[1]) >> 1;
        return;
    }
    r->in[0] = clamp16(r->in[0] >> 1);
    r->in[1] = clamp16(r->in[1] >> 1);
    reverb_step(r, rv_preset[k->fx_mode], (s16)k->evoll, (s16)k->evolr);
    r->in[0] = r->in[1] = 0;
    dry[0] += r->out[0];
    dry[1] += r->out[1];
}

static s32 mvol(u16 reg) { return reg & 0x8000 ? 0x7FFF : (s16)(reg << 1); }

/* the mix runs voice by voice over a stretch of samples (the driver's ticks fall between calls, so no
 * register changes inside one), into these sums per core and side; then the reverb and the master
 * volumes sample by sample.  The sums are the same as a sample-by-sample loop's. */
#define MIX_MAX 256
static int sd_deferred;
static void publish_env(void);
static s32 mix_dry[2][2][MIX_MAX], mix_wet[2][2][MIX_MAX];
static s16 mix_noise[2][MIX_MAX];

/* the core's noise generator over a stretch (psx-spx "SPU Noise Generator"; it runs whether or not a
 * voice listens, as the hardware's does) */
static void noise_run(Core *k, s16 *out, int frames) {
    s32 step = (k->noise_clk & 3) + 4, reload = 0x20000 >> ((k->noise_clk >> 2) & 15);
    u32 lvl = k->noise_lvl;
    s32 t = k->noise_timer;
    int i;
    for (i = 0; i < frames; i++) {
        t -= step;
        if (t < 0) {
            lvl = ((lvl << 1) | (((lvl >> 15) ^ (lvl >> 12) ^ (lvl >> 11) ^ (lvl >> 10) ^ 1) & 1)) & 0xFFFF;
            t += reload;
            if (t < 0) t += reload;
        }
        out[i] = (s16)lvl;
    }
    k->noise_lvl = (u16)lvl;
    k->noise_timer = t;
}

/* The voice's mix over a stretch in three passes (2026-10-31, docs/sound-spec.md "The mix in passes"),
 * the same numbers as voice_sample()'s sample-by-sample loop (kept below for KH1_SPU2_SLOWMIX):
 *   1. the envelope: env_at[i], the ENVX sample i is scaled by; it changes only when the envelope's
 *      counter overflows, so the samples between are filled in one go.  It stops where the release
 *      reaches 0 (the voice's last sample is the one whose tick turned it off);
 *   2. the wave: the interpolated samples (or the noise) up to there, the pitch counter, the ADPCM
 *      blocks and their end flags, with the voice's state in locals; a block end that stops the voice
 *      stops it here (env 0, off) as block_end() does;
 *   3. the volumes and the sums: with no sweep the volumes are constants, and the four sums are
 *      straight loops (NEON on the Vita). */
static __inline__ __attribute__((always_inline)) u32 env_inc(const Env *e, s32 level) {
    u32 inc = e->inc;
    if (e->exp && !e->dec && level >= 0x6000) {
        if (e->rate < 40) ;
        else if (e->rate >= 44) inc >>= 2;
        else inc >>= 1;
    }
    return inc;
}

/* pass 1: how many samples the voice plays (frames, or fewer if the envelope ends) */
static int env_pass(Voice *__restrict__ v, int frames, s32 *__restrict__ env_at) {
    int i = 0;
    while (i < frames) {
        int ph = v->phase, m;
        u32 inc;
        if (ph == PH_OFF) break;
        env_at[i++] = v->env;
        adsr_tick(v);
        if (v->phase != ph || v->phase == PH_OFF) continue;
        /* the same phase, its condition false at this level: the ticks until the next overflow change
         * nothing but the counter */
        inc = env_inc(&v->adsr, v->env);
        if (!inc) m = frames - i;
        else m = (int)((0x8000u - (u32)v->adsr.counter + inc - 1) / inc) - 1;
        if (m > frames - i) m = frames - i;
        if (m > 0) {
            s32 e = v->env;
            int j;
            v->adsr.counter += (s32)(inc * (u32)m);
            for (j = 0; j < m; j++) env_at[i + j] = e;
            i += m;
        }
    }
    return i;
}

/* pass 2: the wave; returns the samples played (fewer than cnt if a block end stopped the voice) */
static int wave_pass(Voice *__restrict__ v, int c, int n, int cnt, const s16 *__restrict__ nz, s32 *__restrict__ raw) {
    u32 counter = v->counter, step = v->pitch > 0x3FFF ? 0x3FFF : v->pitch;
    s16 s0 = v->s[0], s1 = v->s[1], s2 = v->s[2], s3 = v->s[3];
    int idx = v->idx, i, off = 0;
    for (i = 0; i < cnt; i++) {
        if (nz) raw[i] = nz[i];
        else {
            const s32 *w = interp_w[(counter & 0xFFF) >> 4];
            s32 r = (s0 * w[0] + s1 * w[1] + s2 * w[2] + s3 * w[3]) >> 15;
            raw[i] = r > 32767 ? 32767 : r < -32768 ? -32768 : r;
        }
        counter += step;
        while (counter >= 0x1000) {
            counter -= 0x1000;
            s0 = s1;
            s1 = s2;
            s2 = s3;
            if (idx >= 28) {
                if (idx != 99) {
                    block_end(v, c, n);
                    if (v->phase == PH_OFF) off = 1;
                }
                decode_block(v, c, n);
                idx = 0;
            }
            s3 = v->dec[idx++];
            if (off) break;
        }
        if (off) { i++; break; }
    }
    v->counter = counter;
    v->s[0] = s0;
    v->s[1] = s1;
    v->s[2] = s2;
    v->s[3] = s3;
    v->idx = idx;
    return i;
}

static void voice_render(Voice *__restrict__ v, int c, int n, int frames, s32 (*__restrict__ dry)[MIX_MAX], s32 (*__restrict__ wet)[MIX_MAX]) {
    static s32 env_at[MIX_MAX] __attribute__((aligned(16))), raw[MIX_MAX] __attribute__((aligned(16)));
    const Core *k = &core[c];
    u32 bit = 1u << n;
    int ml = (k->vmixl & bit) != 0, mr = (k->vmixr & bit) != 0, mel = (k->vmixel & bit) != 0, mer = (k->vmixer & bit) != 0;
    int sweep_l = v->voll & 0x8000, sweep_r = v->volr & 0x8000, i, cnt, ph = v->phase;
    const s16 *nz = (k->non & bit) ? mix_noise[c] : 0;
    cnt = env_pass(v, frames, env_at);
    if (!cnt) return;
    /* pass 2 reads the phase only for a block end's stop: give it the phase the voice had */
    {
        int ph_env = v->phase;
        s32 e_env = v->env;
        int got;
        v->phase = (u8)ph;
        got = wave_pass(v, c, n, cnt, nz, raw);
        if (got < cnt || v->phase == PH_OFF) {
            cnt = got;          /* stopped by a block end: env 0, off (block_end) */
            v->env = 0;
            v->phase = PH_OFF;
        } else {
            v->phase = (u8)ph_env;
            v->env = e_env;
        }
    }
    if (sweep_l || sweep_r) {
        for (i = 0; i < cnt; i++) {
            s32 s = (raw[i] * env_at[i]) >> 15, l, r;
            if (sweep_l) vol_tick(v, 0, v->voll);
            if (sweep_r) vol_tick(v, 1, v->volr);
            l = (s * v->vol[0]) >> 15;
            r = (s * v->vol[1]) >> 15;
            if (ml) dry[0][i] += l;
            if (mr) dry[1][i] += r;
            if (mel) wet[0][i] += l;
            if (mer) wet[1][i] += r;
        }
        return;
    }
    {
        /* a sum the voice is not routed to goes to a sink (adding 0 to it would be the same) */
        static s32 sink[MIX_MAX] __attribute__((aligned(16)));
        s32 vl = v->vol[0], vr = v->vol[1];
        s32 *d0 = ml ? dry[0] : sink, *d1 = mr ? dry[1] : sink, *w0 = mel ? wet[0] : sink, *w1 = mer ? wet[1] : sink;
        i = 0;
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        {
            int32x4_t qvl = vdupq_n_s32(vl), qvr = vdupq_n_s32(vr);
            for (; i + 4 <= cnt; i += 4) {
                int32x4_t s = vshrq_n_s32(vmulq_s32(vld1q_s32(raw + i), vld1q_s32(env_at + i)), 15);
                int32x4_t l = vshrq_n_s32(vmulq_s32(s, qvl), 15), r = vshrq_n_s32(vmulq_s32(s, qvr), 15);
                vst1q_s32(d0 + i, vaddq_s32(vld1q_s32(d0 + i), l));
                vst1q_s32(w0 + i, vaddq_s32(vld1q_s32(w0 + i), l));
                vst1q_s32(d1 + i, vaddq_s32(vld1q_s32(d1 + i), r));
                vst1q_s32(w1 + i, vaddq_s32(vld1q_s32(w1 + i), r));
            }
        }
#endif
        for (; i < cnt; i++) {
            s32 s = (raw[i] * env_at[i]) >> 15, l = (s * vl) >> 15, r = (s * vr) >> 15;
            d0[i] += l;
            w0[i] += l;
            d1[i] += r;
            w1[i] += r;
        }
    }
}

#ifdef KH1_SPU2_SLOWMIX
static void voice_render_slow(Voice *__restrict__ v, int c, int n, int frames, s32 (*__restrict__ dry)[MIX_MAX], s32 (*__restrict__ wet)[MIX_MAX]) {
    const Core *k = &core[c];
    u32 bit = 1u << n;
    s32 ml = -(s32)((k->vmixl & bit) != 0), mr = -(s32)((k->vmixr & bit) != 0);
    s32 mel = -(s32)((k->vmixel & bit) != 0), mer = -(s32)((k->vmixer & bit) != 0);
    int sweep_l = v->voll & 0x8000, sweep_r = v->volr & 0x8000, i;
    const s16 *nz = (k->non & bit) ? mix_noise[c] : 0;
    for (i = 0; i < frames && v->phase != PH_OFF; i++) {
        s32 s = voice_sample(v, c, n, nz ? nz + i : 0), l, r;
        if (sweep_l) vol_tick(v, 0, v->voll);
        if (sweep_r) vol_tick(v, 1, v->volr);
        l = (s * v->vol[0]) >> 15;
        r = (s * v->vol[1]) >> 15;
        dry[0][i] += l & ml;
        dry[1][i] += r & mr;
        wet[0][i] += l & mel;
        wet[1][i] += r & mer;
    }
}
#define voice_render voice_render_slow
#endif

static void mix_part(s16 *out, int frames) {
    int f, c, n;
    for (c = 0; c < 2; c++) {
        memset(mix_dry[c], 0, sizeof mix_dry[c]);
        memset(mix_wet[c], 0, sizeof mix_wet[c]);
        noise_run(&core[c], mix_noise[c], frames);
        for (n = 0; n < 24; n++)
            if (core[c].v[n].phase != PH_OFF) voice_render(&core[c].v[n], c, n, frames, mix_dry[c], mix_wet[c]);
    }
    for (f = 0; f < frames; f++) {
        s32 lr[2][2];
        for (c = 0; c < 2; c++) {
            s32 wet[2];
            lr[c][0] = mix_dry[c][0][f];
            lr[c][1] = mix_dry[c][1][f];
            wet[0] = clamp16(mix_wet[c][0][f]);
            wet[1] = clamp16(mix_wet[c][1][f]);
            reverb(c, wet, lr[c]);
        }
        /* core 0's output into core 1 (AVOL), then core 1's master volume */
        {
            s32 l0 = clamp16((clamp16(lr[0][0]) * mvol(core[0].mvoll)) >> 15);
            s32 r0 = clamp16((clamp16(lr[0][1]) * mvol(core[0].mvolr)) >> 15);
            /* AVOL is a plain 16-bit volume (no sweep bit) */
            s32 l = lr[1][0] + ((l0 * (s16)core[1].avoll) >> 15);
            s32 r = lr[1][1] + ((r0 * (s16)core[1].avolr) >> 15);
            out[2 * f] = (s16)clamp16((clamp16(l) * mvol(core[1].mvoll)) >> 15);
            out[2 * f + 1] = (s16)clamp16((clamp16(r) * mvol(core[1].mvolr)) >> 15);
        }
    }
}

void kh1_spu2_mix(s16 *out, int frames) {
    while (frames > 0) {
        int n = frames < MIX_MAX ? frames : MIX_MAX;
        mix_part(out, n);
        out += 2 * n;
        frames -= n;
    }
    if (sd_deferred) publish_env();
}

void kh1_spu2_reset(void) {
    interp_init();
    memset(core, 0, sizeof core);
    memset(rv, 0, sizeof rv);
    memset(spu_ram, 0, sizeof spu_ram);
}

int kh1_spu2_voices_on(void) {
    int c, n, k = 0;
    for (c = 0; c < 2; c++)
        for (n = 0; n < 24; n++) k += core[c].v[n].phase != PH_OFF;
    return k;
}

/* ---- libsd ---- */

static u32 sd_trans_func[2], sd_trans_arg[2];

/* sceSdSetCoreAttr(entry, value): SD_C_EFFECT_ENABLE (2) and SD_C_NOISE_CLK (8), with the core in bit 0,
 * are the ones that change the mix */
static void core_attr(u32 entry, u32 val) {
    switch (entry & ~1u) {
    case 2: core[entry & 1].fx_on = (u16)(val != 0); break;
    case 8: core[entry & 1].noise_clk = (u16)(val & 0x3F); break;
    }
}

static void set_param(u32 p, u32 val) {
    int c = p & 1, n = (p >> 1) & 31, reg = (p >> 8) & 0xFF;
    Core *k = &core[c];
    Voice *v = n < 24 ? &k->v[n] : 0;
    u16 x = (u16)val;
    switch (reg) {
    case 0x00: if (v) { v->voll = x; vol_set(v, 0, x); } break;
    case 0x01: if (v) { v->volr = x; vol_set(v, 1, x); } break;
    case 0x02: if (v) v->pitch = x; break;
    case 0x03: if (v) { v->adsr1 = x; if (v->phase == PH_ATTACK || v->phase == PH_DECAY) adsr_phase(v, v->phase); } break;
    case 0x04: if (v) { v->adsr2 = x; if (v->phase == PH_SUSTAIN || v->phase == PH_RELEASE) adsr_phase(v, v->phase); } break;
    case 0x05: if (v) v->env = x & 0x7FFF; break;
    case 0x06: if (v) v->vol[0] = (s16)x; break;
    case 0x07: if (v) v->vol[1] = (s16)x; break;
    case 0x08: k->mmix = x; break;
    case 0x09: k->mvoll = x; break;
    case 0x0A: k->mvolr = x; break;
    case 0x0B: k->evoll = x; break;
    case 0x0C: k->evolr = x; break;
    case 0x0D: k->avoll = x; break;
    case 0x0E: k->avolr = x; break;
    case 0x0F: k->bvoll = x; break;
    case 0x10: k->bvolr = x; break;
    default: break;
    }
}

static u32 get_param(u32 p) {
    int c = p & 1, n = (p >> 1) & 31, reg = (p >> 8) & 0xFF;
    Core *k = &core[c];
    Voice *v = n < 24 ? &k->v[n] : 0;
    switch (reg) {
    case 0x00: return v ? v->voll : 0;
    case 0x01: return v ? v->volr : 0;
    case 0x02: return v ? v->pitch : 0;
    case 0x03: return v ? v->adsr1 : 0;
    case 0x04: return v ? v->adsr2 : 0;
    case 0x05: return v ? (u32)v->env : 0;
    case 0x06: return v ? (u16)v->vol[0] : 0;
    case 0x07: return v ? (u16)v->vol[1] : 0;
    case 0x08: return k->mmix;
    case 0x09: return k->mvoll;
    case 0x0A: return k->mvolr;
    case 0x0B: return k->evoll;
    case 0x0C: return k->evolr;
    case 0x0D: return k->avoll;
    case 0x0E: return k->avolr;
    default: return 0;
    }
}

static void set_switch(u32 p, u32 val) {
    int c = p & 1, reg = (p >> 8) & 0xFF, n;
    Core *k = &core[c];
    val &= 0xFFFFFF;
    switch (reg) {
    case 0x13: k->pmon = val; break;
    case 0x14: k->non = val; break;
    case 0x15: for (n = 0; n < 24; n++) if (val & (1u << n)) key_on(c, n); break;
    case 0x16: for (n = 0; n < 24; n++) if (val & (1u << n)) key_off(c, n); break;
    case 0x17: k->endx = val; break;
    case 0x18: k->vmixl = val; break;
    case 0x19: k->vmixel = val; break;
    case 0x1A: k->vmixr = val; break;
    case 0x1B: k->vmixer = val; break;
    default: break;
    }
}

static u32 get_switch(u32 p) {
    int c = p & 1, reg = (p >> 8) & 0xFF;
    Core *k = &core[c];
    switch (reg) {
    case 0x13: return k->pmon;
    case 0x14: return k->non;
    case 0x17: return k->endx;
    case 0x18: return k->vmixl;
    case 0x19: return k->vmixel;
    case 0x1A: return k->vmixr;
    case 0x1B: return k->vmixer;
    default: return 0;
    }
}

static void set_addr(u32 p, u32 val) {
    int c = p & 1, n = (p >> 1) & 31, reg = (p >> 8) & 0xFF;
    Core *k = &core[c];
    Voice *v = n < 24 ? &k->v[n] : 0;
    val &= SPU_RAM - 1;
    switch (reg) {
    case 0x1C: k->esa = val; break;
    case 0x1D: k->eea = val; break;
    case 0x1F: k->irqa = val; break;
    case 0x20: if (v) v->ssa = val; break;
    case 0x21: if (v) { v->lsa = val & ~15u; v->lsa_written = 1; if (v->phase != PH_OFF) v->lsa_manual = 1; } break;
    case 0x22: if (v) v->nax = val; break;
    default: break;
    }
}

static u32 get_addr(u32 p) {
    int c = p & 1, n = (p >> 1) & 31, reg = (p >> 8) & 0xFF;
    Core *k = &core[c];
    Voice *v = n < 24 ? &k->v[n] : 0;
    switch (reg) {
    case 0x1C: return k->esa;
    case 0x1D: return k->eea;
    case 0x1F: return k->irqa;
    case 0x20: return v ? v->ssa : 0;
    case 0x21: return v ? v->lsa : 0;
    case 0x22: return v ? v->nax : 0;
    default: return 0;
    }
}

static int sd_log_n;

/* ---- the deferred mode (the Vita's two sound threads, host/vita/audio.c) ----
 * The driver's ticks run on one thread and the mix on another, a few ticks behind.  The writes a tick
 * makes (SetParam, SetSwitch, SetAddr, SetCoreAttr, ClearEffectWorkArea) go into a log with a mark at
 * each tick's end, and the mixer applies one tick's worth before it mixes that tick's 200 samples.
 * The driver's only read of the mix's state, GetParam ENVX (to find voices that have ended), answers
 * the envelope the mixer published after its last tick.  Sound RAM transfers and the reverb's
 * attributes still take effect at once.  The host runs everything on one thread, as before. */
typedef struct {
    u32 fn, a0, a1; /* fn 0: the end of a tick */
} SdCmd;
#define SD_LOG 32768 /* commands, a power of two */
static SdCmd sd_log[SD_LOG];
static volatile u32 sd_log_head, sd_log_tail, sd_marks_in, sd_marks_out;
static volatile s32 env_pub[2][24];

static void sd_apply(u32 fn, u32 a0, u32 a1) {
    switch (fn) {
    case 5: set_param(a0, a1); break;
    case 7: set_switch(a0, a1); break;
    case 9: set_addr(a0, a1); break;
    case 11: core_attr(a0, a1); break;
    case 25: memset(&rv[a0 & 1], 0, sizeof rv[0]); break;
    }
}

static void sd_push(u32 fn, u32 a0, u32 a1) {
    u32 h = sd_log_head; /* never full: the tick thread waits for kh1_spu2_log_room first */
    sd_log[h & (SD_LOG - 1)].fn = fn;
    sd_log[h & (SD_LOG - 1)].a0 = a0;
    sd_log[h & (SD_LOG - 1)].a1 = a1;
    __sync_synchronize();
    sd_log_head = h + 1;
}

void kh1_spu2_set_deferred(int on) {
    int c, n;
    for (c = 0; c < 2; c++)
        for (n = 0; n < 24; n++) env_pub[c][n] = core[c].v[n].env;
    sd_deferred = on;
}

/* the tick thread: room for one more tick's writes, and the mark at a tick's end */
u32 kh1_spu2_log_room(void) { return SD_LOG - (sd_log_head - sd_log_tail); }
void kh1_spu2_tick_mark(void) {
    sd_push(0, 0, 0);
    __sync_synchronize();
    sd_marks_in++;
}

/* the mixer: apply the next tick's writes; 0 when the tick thread has not finished one yet */
int kh1_spu2_apply_tick(void) {
    u32 t;
    if (sd_marks_out == sd_marks_in) return 0;
    __sync_synchronize();
    for (t = sd_log_tail; t != sd_log_head; t++) {
        const SdCmd *e = &sd_log[t & (SD_LOG - 1)];
        if (e->fn == 0) { t++; break; }
        sd_apply(e->fn, e->a0, e->a1);
    }
    __sync_synchronize();
    sd_log_tail = t;
    sd_marks_out++;
    return 1;
}

static void publish_env(void) {
    int c, n;
    for (c = 0; c < 2; c++)
        for (n = 0; n < 24; n++) env_pub[c][n] = core[c].v[n].phase == PH_OFF ? 0 : core[c].v[n].env;
}

/* libsd's exports by number (its import table in the driver) */
u32 kh1_sd_call(int fn, const u32 *a) {
    if (sd_deferred) {
        switch (fn) {
        case 5: case 7: case 9: case 11: case 25:
            sd_push((u32)fn, a[0], a[1]);
            return 0;
        case 6:
            if (((a[0] >> 8) & 0xFF) == 0x05 && ((a[0] >> 1) & 31) < 24) return (u32)env_pub[a[0] & 1][(a[0] >> 1) & 31];
            break;
        }
    }
    switch (fn) {
    case 4: /* sceSdInit(flag) */
        memset(core, 0, sizeof core);
        return 0;
    case 5: set_param(a[0], a[1]); return 0;
    case 6: return get_param(a[0]);
    case 7: set_switch(a[0], a[1]); return 0;
    case 8: return get_switch(a[0]);
    case 9: set_addr(a[0], a[1]); return 0;
    case 10: return get_addr(a[0]);
    case 11: core_attr(a[0], a[1]); return 0; /* sceSdSetCoreAttr */
    case 12: return 0;
    case 17: { /* sceSdVoiceTrans(channel, mode, iop address, spu address, size) */
        u32 size = a[4], spu = a[3] & (SPU_RAM - 1);
        u8 *iop = kh1_iop_ptr(a[2], size);
        if (spu + size > SPU_RAM) size = SPU_RAM - spu;
        if (iop) {
            if (a[1] & 1) memcpy(iop, spu_ram + spu, size);
            else memcpy(spu_ram + spu, iop, size);
        }
        kh1_iop_raise_trans((int)(a[0] & 1));
        return size;
    }
    case 18: return 0;          /* sceSdBlockTrans: the core sound-data input is not modelled */
    case 19: return 1;          /* sceSdVoiceTransStatus: done */
    case 20: return 0;          /* sceSdBlockTransStatus */
    case 23: { /* sceSdSetEffectAttr(core, {core, mode, depth_L, depth_R, delay, feedback}) */
        const u8 *e = kh1_iop_ptr(a[1], 20);
        Core *k = &core[a[0] & 1];
        if (e) {
            k->fx_mode = *(const s32 *)(e + 4);
            k->fx_depth_l = *(const s16 *)(e + 8);
            k->fx_depth_r = *(const s16 *)(e + 10);
            k->fx_delay = *(const s32 *)(e + 12);
            k->fx_feedback = *(const s32 *)(e + 16);
            if ((k->fx_delay || k->fx_feedback) && sd_log_n++ < 16)
                printf("kh1-spu2: reverb delay %d / feedback %d not modelled\n", k->fx_delay, k->fx_feedback);
        }
        return 0;
    }
    case 24: { /* sceSdGetEffectAttr(core, attr) */
        u8 *e = kh1_iop_ptr(a[1], 20);
        Core *k = &core[a[0] & 1];
        if (e) {
            *(s32 *)(e + 0) = (s32)(a[0] & 1);
            *(s32 *)(e + 4) = k->fx_mode;
            *(s16 *)(e + 8) = (s16)k->fx_depth_l;
            *(s16 *)(e + 10) = (s16)k->fx_depth_r;
            *(s32 *)(e + 12) = k->fx_delay;
            *(s32 *)(e + 16) = k->fx_feedback;
        }
        return 0;
    }
    case 25: /* sceSdClearEffectWorkArea(core, channel, mode) */
        memset(&rv[a[0] & 1], 0, sizeof rv[0]);
        return 0;
    case 26:           /* sceSdSetTransIntrHandler(channel, func, arg) */
        sd_trans_func[a[0] & 1] = a[1];
        sd_trans_arg[a[0] & 1] = a[2];
        kh1_iop_set_trans_handler((int)(a[0] & 1), a[1], a[2]);
        return 0;
    case 27: return 0; /* sceSdSetSpu2IntrHandler: no IRQ address is modelled */
    case 30: return 0; /* sceSdStopTrans */
    default:
        if (sd_log_n++ < 16) printf("kh1-spu2: libsd %d not answered\n", fn);
        return 0;
    }
}

/* the voices' state on stdout (tools/host/sndplay.c, SNDPLAY_DUMP=1) */
void kh1_spu2_dump(void) {
    int c, n;
    for (c = 0; c < 2; c++) {
        Core *k = &core[c];
        printf("core %d: mmix %04x mvol %04x/%04x avol %04x/%04x evol %04x/%04x vmix %06x/%06x wet %06x/%06x fx %d\n", c, k->mmix,
               k->mvoll, k->mvolr, k->avoll, k->avolr, k->evoll, k->evolr, k->vmixl, k->vmixr, k->vmixel, k->vmixer,
               k->fx_mode);
        for (n = 0; n < 24; n++) {
            Voice *v = &k->v[n];
            if (v->phase == PH_OFF && !v->pitch) continue;
            printf("  v%02d ph %d env %04x vol %04x/%04x (%d/%d) pitch %04x adsr %04x/%04x ssa %06x lsa %06x nax %06x\n", n,
                   v->phase, v->env, v->voll, v->volr, v->vol[0], v->vol[1], v->pitch, v->adsr1, v->adsr2, v->ssa, v->lsa,
                   v->nax);
        }
    }
}
