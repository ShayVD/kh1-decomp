/* Play the game's music or sound effects through the user's own sound driver without the game
 * (docs/sound-spec.md "The IOP on the port"): host/port/iop.c runs LIBSSL.IRX, host/port/spu2.c
 * mixes, and this file sends the commands src/sound/sndctl.c would (sound-spec 3) and writes a WAV.
 * The inputs come from your own disc (tools/shift/extract_kingdom.py); nothing is in the repo.
 *
 *   gcc -m32 -O2 -DKH1_HOST -Iinclude -o out/host/sndplay tools/host/sndplay.c host/port/iop.c host/port/spu2.c
 *   out/host/sndplay LIBSSL.IRX out.wav SECONDS music097.bgm wave0099.wd   # a sequence and its wave bank
 *   out/host/sndplay LIBSSL.IRX out.wav SECONDS music100.dat               # a music .dat (both chunks)
 *   out/host/sndplay LIBSSL.IRX out.wav SECONDS se000.dat ID [ID...]       # system SEs from the boot bank, 1 s apart
 * LIBSD.IRX beside LIBSSL.IRX (any case) gives the reverb its presets (host/port/spu2.c).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int kh1_iop_load(const u8 *irx, u32 size);
int kh1_iop_rpc(u32 sid, u32 fno, const void *send, int ssize, void *recv, int rsize);
void kh1_iop_tick(void);
u32 kh1_iop_timer_hz(void);
extern u32 kh1_iop_insns;
void kh1_spu2_reset(void);
void kh1_spu2_mix(s16 *out, int frames);
int kh1_spu2_voices_on(void);
int kh1_spu2_find_presets(const u8 *irx, u32 size);

static u8 status[0x2200] __attribute__((aligned(16)));
static s32 queue[256][8];
static int nq;
static FILE *wav;
static u32 wav_bytes;

static u8 *load(const char *path, u32 *size) {
    FILE *f = fopen(path, "rb");
    u8 *b;
    long n;
    if (!f) { perror(path); exit(1); }
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    b = malloc((size_t)n + 16);
    if (fread(b, 1, (size_t)n, f) != (size_t)n) { perror(path); exit(1); }
    fclose(f);
    *size = (u32)n;
    return b;
}

static void q(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    s32 *r = queue[nq++];
    r[0] = a; r[1] = b; r[2] = c; r[3] = d; r[4] = e; r[5] = f; r[6] = g; r[7] = h;
}

static void flush(void) {
    if (!nq) return;
    if (nq < 256) memset(queue[nq], 0xFF, (256 - nq) * 32);
    kh1_iop_rpc(17, 30, queue, 0x2000, 0, 0);
    nq = 0;
}

static s32 pending(void) { return *(s32 *)(status + 0x1F00); }

static void put32(u8 *p, u32 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8); p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24); }

static void wav_header(void) {
    u8 h[44];
    memcpy(h, "RIFF", 4);
    put32(h + 4, 36 + wav_bytes);
    memcpy(h + 8, "WAVEfmt ", 8);
    put32(h + 16, 16);
    h[20] = 1; h[21] = 0; h[22] = 2; h[23] = 0;
    put32(h + 24, 48000);
    put32(h + 28, 48000 * 4);
    h[32] = 4; h[33] = 0; h[34] = 16; h[35] = 0;
    memcpy(h + 36, "data", 4);
    put32(h + 40, wav_bytes);
    fseek(wav, 0, SEEK_SET);
    fwrite(h, 1, 44, wav);
    fseek(wav, 0, SEEK_END);
}

/* one tick of the driver and its 200 samples */
static void tick(int record) {
    s16 buf[400];
    kh1_iop_tick();
    kh1_spu2_mix(buf, 200);
    if (record) {
        fwrite(buf, 4, 200, wav);
        wav_bytes += 800;
    }
}

static void wait_transfers(void) {
    int t;
    for (t = 0; t < 2400 && pending() != 0; t++) tick(0);
    printf("sndplay: transfers done after %d ticks (count %d)\n", t, pending());
}

int main(int argc, char **argv) {
    u32 irx_size, size, t, total;
    u8 *irx;
    u32 bind[4];
    double secs;
    const char *base;
    if (argc < 5) {
        fprintf(stderr, "usage: sndplay LIBSSL.IRX out.wav SECONDS FILE [FILE | SE ids...]\n");
        return 2;
    }
    irx = load(argv[1], &irx_size);
    secs = atof(argv[3]);
    kh1_spu2_reset();
    {
        char sd[1024];
        char *slash;
        FILE *f;
        strncpy(sd, argv[1], sizeof sd - 16);
        sd[sizeof sd - 16] = 0;
        slash = strrchr(sd, '/');
        strcpy(slash ? slash + 1 : sd, strstr(argv[1], "LIBSSL") ? "LIBSD.IRX" : "libsd.irx");
        if ((f = fopen(sd, "rb")) != 0) {
            u32 n;
            u8 *b;
            fclose(f);
            b = load(sd, &n);
            printf("sndplay: reverb presets %s\n", kh1_spu2_find_presets(b, n) == 0 ? "found" : "not found");
        }
    }
    if (kh1_iop_load(irx, irx_size) != 0) { fprintf(stderr, "sndplay: the driver did not load\n"); return 1; }
    printf("sndplay: driver loaded, tick %u Hz\n", kh1_iop_timer_hz());
    /* RPC 0: the status block and the message buffer (func_001ec7d0), mode 0 (boot) */
    bind[0] = (u32)(unsigned long)status;
    bind[1] = 0;
    bind[2] = (u32)(unsigned long)(status + 0x2000);
    bind[3] = 0;
    kh1_iop_rpc(17, 0, bind, 16, bind, 16);
    for (t = 0; t < 8; t++) tick(0);
    wav = fopen(argv[2], "wb");
    if (!wav) { perror(argv[2]); return 1; }
    wav_header();
    total = (u32)(secs * 240);
    base = strrchr(argv[4], '/') ? strrchr(argv[4], '/') + 1 : argv[4];
    if (strstr(base, ".bgm") || !strncmp(base, "music", 5)) {
        u8 *seq, *wave;
        u32 seq_size, wave_size;
        if (strstr(argv[4], ".bgm")) {
            if (argc < 6) { fprintf(stderr, "sndplay: a .bgm needs its .wd\n"); return 2; }
            seq = load(argv[4], &seq_size);
            wave = load(argv[5], &wave_size);
        } else {
            u8 *d = load(argv[4], &size);
            seq = d + *(u32 *)(d + 0x10);
            seq_size = *(u32 *)(d + 0x14);
            wave = d + *(u32 *)(d + 0x18);
            wave_size = *(u32 *)(d + 0x1C);
        }
        /* func_0011cbe0: free the slot's wave and sequence, send both (track 0) */
        q(0x26, 0, 0, 0, 0, 0, 0, 0);
        q(0x26, 1, 0, 0, 0, 0, 0, 0);
        *(s32 *)(status + 0x1F00) += 2;
        q(0xB, 0, (s32)(unsigned long)seq, (s32)seq_size, 0, 0, 0, 0);
        q(3, 0, (s32)(unsigned long)wave, (s32)wave_size, 0, 0, 0, 0);
        flush();
        wait_transfers();
        /* func_0011e610: start track 0 at the game's full volume */
        q(0xC, 0, 0x3000, 0x3000, 0, 0, 0, 0);
        flush();
        for (t = 0; t < total; t++) tick(1);
    } else {
        /* the boot bank (func_0011cd20): chunk 0 the SE tables, chunk 1 the waves, slot 2 */
        u8 *d = load(argv[4], &size);
        int i;
        q(0x26, 0, 2, 0, 0, 0, 0, 0);
        q(0x26, 2, 2, 0, 0, 0, 0, 0);
        *(s32 *)(status + 0x1F00) += 2;
        q(4, 2, (s32)(unsigned long)(d + *(u32 *)(d + 0x10)), *(s32 *)(d + 0x14), 0, 0, 0, 0);
        q(3, 2, (s32)(unsigned long)(d + *(u32 *)(d + 0x18)), *(s32 *)(d + 0x1C), 0, 0, 0, 0);
        flush();
        wait_transfers();
        for (i = 5; i < argc; i++) {
            q(5, 2, atoi(argv[i]), 0, 0x3FFF, 0x3FFF, 0, 0); /* func_0011d768: play, centre, full */
            flush();
            for (t = 0; t < 240; t++) tick(1);
        }
        for (t = 0; t < total; t++) tick(1);
    }
    wav_header();
    fclose(wav);
    if (getenv("SNDPLAY_DUMP")) { void kh1_spu2_dump(void); kh1_spu2_dump(); }
    printf("sndplay: %u ms of sound, %u IOP instructions, %d voices on at the end\n", wav_bytes / 192, kh1_iop_insns,
           kh1_spu2_voices_on());
    return 0;
}
