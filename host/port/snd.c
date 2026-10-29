/* The game's sound server (RPC 17) on the port (docs/sound-spec.md "The IOP on the port"): the
 * user's own IOP sound driver, LIBSSL.IRX from the disc image's root, run by host/port/iop.c over
 * host/port/spu2.c.  src/sound/snd_rpc.c stays as it is: platform/iop.h's PlatSifCallRpc hands its
 * calls here (host/null/plat_null.c) when the driver is loaded, and the null server
 * (host/null/sound.c) answers them otherwise (no disc image, or the sound off).
 *
 * Two ways to run it:
 *   - with an audio thread (the Vita, host/vita/audio.c): kh1_snd_render runs the driver's 240 Hz
 *     tick every 200 samples and mixes; the game thread's queue sends (RPC 30, every frame) are
 *     copied into a FIFO and run by the audio thread before its next tick, so the game does not
 *     wait for the driver; the other calls (the game reads their answer) drain the FIFO and run at
 *     once.  One lock (kh1_snd_set_lock) keeps the two threads out of each other.
 *   - without one (the host runner): every call runs at once and kh1_snd_frame (kh1_host_vblank)
 *     runs four ticks a frame, mixing into an optional WAV file (KH1_HOST_SND=wav:FILE).
 *
 * Not part of the PS2 build. */
#include "common.h"
#include "iop.h"

int printf(const char *, ...);
void *memcpy(void *, const void *, unsigned int);
char *getenv(const char *);
int strncmp(const char *, const char *, unsigned int);
int kh1_cd_image_is_open(void);
int kh1_cd_image_search(const char *name, u32 *lsn, u32 *size);
int kh1_cd_image_read(u32 lsn, u32 n, void *buf);
void kh1_spu2_reset(void);
void kh1_spu2_mix(s16 *out, int frames);
int kh1_spu2_find_presets(const u8 *irx, u32 size);

#define SND_SID 17
#define SND_TICK_SAMPLES 200 /* 48000 / 240 */
#define SND_FIFO 16 /* about five frames of sends queue while the Vita's mixer is ahead */
#define SND_MSG 0x2000

static int snd_on;
static int snd_threaded;
static void (*snd_lock_fn)(void);
static void (*snd_unlock_fn)(void);
static int tick_left;

/* the queued RPC 30 sends (threaded mode) */
static u8 fifo_buf[SND_FIFO][SND_MSG];
static int fifo_size[SND_FIFO];
static u32 fifo_num[SND_FIFO];
static volatile int fifo_head, fifo_tail;

u32 kh1_snd_ticks, kh1_snd_rpcs, kh1_snd_fifo_full;

static void lock(void) { if (snd_lock_fn) snd_lock_fn(); }
static void unlock(void) { if (snd_unlock_fn) snd_unlock_fn(); }

void kh1_snd_set_lock(void (*l)(void), void (*u)(void)) {
    snd_lock_fn = l;
    snd_unlock_fn = u;
}

int kh1_snd_active(void) { return snd_on; }

/* the driver from the disc: 0 when it is running */
int kh1_snd_start(void) {
    static u8 irx[0x20000];
    u32 lsn, size;
    if (snd_on) return 0;
    if (!kh1_cd_image_is_open() || !kh1_cd_image_search("\\LIBSSL.IRX;1", &lsn, &size)) {
        printf("kh1-snd: no LIBSSL.IRX on the disc image: no sound\n");
        return -1;
    }
    if (size > sizeof irx || !kh1_cd_image_read(lsn, (size + 2047) / 2048, irx)) {
        printf("kh1-snd: LIBSSL.IRX (%u bytes) could not be read\n", size);
        return -1;
    }
    kh1_spu2_reset();
    {
        /* libsd's reverb presets, from the disc's own LIBSD.IRX (spu2.c) */
        static u8 sd[0x10000];
        u32 sl, ss;
        if (kh1_cd_image_search("\\LIBSD.IRX;1", &sl, &ss) && ss <= sizeof sd &&
            kh1_cd_image_read(sl, (ss + 2047) / 2048, sd) && kh1_spu2_find_presets(sd, ss) == 0)
            printf("kh1-snd: reverb presets from LIBSD.IRX\n");
        else
            printf("kh1-snd: no reverb presets (LIBSD.IRX): reverb off\n");
    }
    if (kh1_iop_load(irx, size) != 0) {
        printf("kh1-snd: the sound driver did not start: no sound\n");
        return -1;
    }
    printf("kh1-snd: sound driver LIBSSL.IRX (%u bytes) running, tick %u Hz\n", size, kh1_iop_timer_hz());
    tick_left = 0;
    snd_on = 1;
    return 0;
}

static void run_rpc(u32 num, const void *send, int ssize, void *recv, int rsize) {
    kh1_snd_rpcs++;
    kh1_iop_rpc(SND_SID, num, send, ssize, recv, rsize);
}

static void drain(void) {
    while (fifo_tail != fifo_head) {
        int t = fifo_tail;
        run_rpc(fifo_num[t], fifo_buf[t], fifo_size[t], 0, 0);
        fifo_tail = (t + 1) % SND_FIFO;
    }
}

/* PlatSifCallRpc for server 17 */
void kh1_snd_rpc(unsigned num, void *send, int ssize, void *recv, int rsize) {
    if (ssize > SND_MSG) ssize = SND_MSG;
    if (snd_threaded && num == 30 && send && ssize > 0) {
        /* the queue: the answer is never read (sound-spec 1), the audio thread runs it */
        int h;
        lock();
        h = fifo_head;
        if ((h + 1) % SND_FIFO == fifo_tail) {
            kh1_snd_fifo_full++;
            drain();
        }
        memcpy(fifo_buf[h], send, (unsigned)ssize);
        fifo_size[h] = ssize;
        fifo_num[h] = num;
        fifo_head = (h + 1) % SND_FIFO;
        unlock();
        return;
    }
    lock();
    drain();
    run_rpc(num, send, ssize, recv, rsize);
    unlock();
}

/* the audio thread: `frames` 48 kHz stereo samples, the driver's ticks between them */
void kh1_snd_render(s16 *out, int frames) {
    snd_threaded = 1;
    while (frames > 0) {
        int n;
        lock();
        if (tick_left == 0) {
            drain();
            kh1_iop_tick();
            kh1_snd_ticks++;
            tick_left = SND_TICK_SAMPLES;
        }
        n = frames < tick_left ? frames : tick_left;
        kh1_spu2_mix(out, n);
        tick_left -= n;
        unlock();
        out += 2 * n;
        frames -= n;
    }
}

/* ---- the host runner: four ticks a frame, an optional WAV file ---- */

typedef struct _FILE FILE;
FILE *fopen(const char *, const char *);
unsigned int fwrite(const void *, unsigned int, unsigned int, FILE *);
int fseek(FILE *, long, int);
int fflush(FILE *);
static FILE *wav;
static u32 wav_bytes;

static void wav_header(void) {
    u8 h[44];
    static const u8 fmt[16] = { 16, 0, 0, 0, 1, 0, 2, 0, 0x80, 0xBB, 0, 0, 0, 0xEE, 2, 0 };
    u32 riff = 36 + wav_bytes;
    memcpy(h, "RIFF", 4);
    h[4] = (u8)riff; h[5] = (u8)(riff >> 8); h[6] = (u8)(riff >> 16); h[7] = (u8)(riff >> 24);
    memcpy(h + 8, "WAVEfmt ", 8);
    memcpy(h + 16, fmt, 16);
    h[32] = 4; h[33] = 0; h[34] = 16; h[35] = 0;
    memcpy(h + 36, "data", 4);
    h[40] = (u8)wav_bytes; h[41] = (u8)(wav_bytes >> 8); h[42] = (u8)(wav_bytes >> 16); h[43] = (u8)(wav_bytes >> 24);
    fseek(wav, 0, 0);
    fwrite(h, 1, 44, wav);
    fseek(wav, 0, 2);
}

/* KH1_HOST_SND=iop runs the driver; =wav:FILE also writes what it plays (from host/null/main.c) */
int kh1_snd_host_init(void) {
    const char *s = getenv("KH1_HOST_SND");
    if (!s || (strncmp(s, "iop", 3) != 0 && strncmp(s, "wav:", 4) != 0)) return 0;
    if (!strncmp(s, "wav:", 4)) {
        wav = fopen(s + 4, "wb");
        if (wav) wav_header();
        else printf("kh1-snd: %s: cannot write\n", s + 4);
    }
    return 1;
}

void kh1_snd_frame(void) {
    static s16 buf[SND_TICK_SAMPLES * 2];
    int i;
    if (!snd_on || snd_threaded) return;
    for (i = 0; i < 4; i++) {
        kh1_iop_tick();
        kh1_snd_ticks++;
        kh1_spu2_mix(buf, SND_TICK_SAMPLES);
        if (wav) {
            fwrite(buf, 4, SND_TICK_SAMPLES, wav);
            wav_bytes += SND_TICK_SAMPLES * 4;
        }
    }
    if (wav && (kh1_snd_ticks & 255) == 0) {
        wav_header();
        fflush(wav);
    }
}

void kh1_snd_host_end(void) {
    if (wav) {
        wav_header();
        fflush(wav);
    }
}
