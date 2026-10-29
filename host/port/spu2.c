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
 * Not modelled: the noise generator, pitch modulation, the core sound-data input (sceSdBlockTrans:
 * the movie's PCM), the SPU2's IRQ address, the echo / delay modes' delay and feedback.  Not part of
 * the PS2 build. */
#include "common.h"
#include "iop.h"

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

static s32 env_tick(Env *e, s32 level) {
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

static void adsr_tick(Voice *v) {
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

static void vol_tick(Voice *v, int side, u16 reg) {
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
    s32 f0, f1;
    if (shift > 12) shift = 9;
    if (filt > 4) filt = 4;
    f0 = adpcm_f0[filt];
    f1 = adpcm_f1[filt];
    v->flags = b[1];
    if ((v->flags & 4) && !v->lsa_manual) v->lsa = v->nax & ~15u;
    for (i = 0; i < 28; i++) {
        s32 nib = (b[2 + i / 2] >> ((i & 1) * 4)) & 15;
        s32 s = ((s32)(s16)(nib << 12)) >> shift;
        s += (v->hist1 * f0 + v->hist2 * f1 + 32) >> 6;
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        v->hist2 = v->hist1;
        v->hist1 = s;
        v->dec[i] = (s16)s;
    }
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

static s32 cubic(const s16 *s, u32 frac) {
    /* Catmull-Rom between s[1] and s[2], t = frac / 4096 */
    s32 p0 = s[0], p1 = s[1], p2 = s[2], p3 = s[3];
    s32 t = (s32)frac, t2 = (t * t) >> 12, t3 = (t2 * t) >> 12;
    s32 a = (-p0 + 3 * p1 - 3 * p2 + p3), b = (2 * p0 - 5 * p1 + 4 * p2 - p3), cc = (-p0 + p2);
    s64 r = ((s64)a * t3 + (s64)b * t2 + (s64)cc * t) >> 13;
    r += p1;
    if (r > 32767) r = 32767;
    if (r < -32768) r = -32768;
    return (s32)r;
}

/* one 48 kHz sample of one voice, before its volumes: 0 for a voice that is off */
static s32 voice_sample(Voice *v, int c, int n) {
    s32 out;
    u32 step;
    if (v->phase == PH_OFF) return 0;
    out = cubic(v->s, v->counter & 0xFFF);
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
    r->pos = (r->pos + 1) & (RV_SIZE - 1);
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

void kh1_spu2_mix(s16 *out, int frames) {
    int f, c, n;
    for (f = 0; f < frames; f++) {
        s32 lr[2][2] = { { 0, 0 }, { 0, 0 } };
        for (c = 0; c < 2; c++) {
            Core *k = &core[c];
            s32 wet[2] = { 0, 0 };
            for (n = 0; n < 24; n++) {
                Voice *v = &k->v[n];
                s32 s;
                if (v->phase == PH_OFF) continue;
                s = voice_sample(v, c, n);
                vol_tick(v, 0, v->voll);
                vol_tick(v, 1, v->volr);
                if (k->vmixl & (1u << n)) lr[c][0] += (s * v->vol[0]) >> 15;
                if (k->vmixr & (1u << n)) lr[c][1] += (s * v->vol[1]) >> 15;
                if (k->vmixel & (1u << n)) wet[0] += (s * v->vol[0]) >> 15;
                if (k->vmixer & (1u << n)) wet[1] += (s * v->vol[1]) >> 15;
            }
            wet[0] = clamp16(wet[0]);
            wet[1] = clamp16(wet[1]);
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

void kh1_spu2_reset(void) {
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

/* libsd's exports by number (its import table in the driver) */
u32 kh1_sd_call(int fn, const u32 *a) {
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
    case 11: /* sceSdSetCoreAttr(entry, value): SD_C_EFFECT_ENABLE (2) is the one that changes the mix */
        if ((a[0] & ~1u) == 2) core[a[0] & 1].fx_on = (u16)(a[1] != 0);
        return 0;
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
