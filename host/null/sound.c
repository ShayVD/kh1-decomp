/* The null sound server (session 86, docs/sound-spec.md, vita-port-plan 5.1z): the EE half of the
 * Vita audio layer without the audio.  src/sound/snd_rpc.c binds SIF RPC server 17 and talks to it
 * through PlatSifCallRpc (host/null/plat_null.c passes every call here).  Nothing is played; the
 * status block the IOP writes (RPC 0's word 0, D_0063D640) is kept the way the game reads it:
 *
 *   - +0x1F00 (D_0063F540) counts the bank transfers not yet done.  The EE adds one for each
 *     transfer it queues (commands 3, 4, 0xB and 0x28); the transfers a sent queue holds are done
 *     at the next frame (kh1_null_iop_frame).  Boot (func_0011cd20) waits for the count to be
 *     non-zero after the send; the bank task, objse.c, summon.c, objreq.c and the soft reset wait
 *     for 0.  Unanswered it stayed at 2 from boot on (session 67).
 *   - the 24 SE voices at +0 (SndSe: used +0, sub +4, bank +0xC, id +0x10): command 5 takes a free
 *     one, 6 / 7 free it (7 after its fade), and an SE ends by itself after NULL_SND_SE_FRAMES
 *     (the length is in the wave bank, which needs the IOP module: a fixed time instead), so
 *     func_001ecb08 sees it end as on the console.
 *   - the 4 streams at +0x1800 (SndStream: kind +0 (0 object SE, 1 voice), bank +2, id +3, used
 *     +4, the voice's VAG address +0x10): command 0x12 plays a voice for its VAG length
 *     (size / 16 x 28 samples at pitch x 48000 / 4096 Hz), 0x29 an object SE for
 *     NULL_SND_SE_FRAMES; 0x13 / 0x2B stop them.  func_001ecd08 polls them: objse's slots and
 *     func_0011e248 wait for them to end.
 *   - every other word reads 0: no disc error (+0x1C08), no message (D_0063F640).
 *
 * The direct calls answer in word 0 of the shared buffer: RPC 0x30 (is the track ready, polled by
 * event/sound.c func_001e8b50) answers 1; the others read back their own first argument.
 *
 * KH1_HOST_SND=trace (or KH1_HOST_TRACE=6) prints each command and RPC as
 *   kh1-host: snd FRAME q CMD NAME key=value ...    (a queued record, in queue order)
 *   kh1-host: snd FRAME rpc NUM NAME a0 a1 a2 a3    (a direct call)
 *   kh1-host: snd FRAME end se|voice|objse ...      (a voice the null server ended by time)
 * and tools/host/sndlog.py summarises a run.  Not part of the PS2 build. */
#include "common.h"

int printf(const char *, ...);
char *getenv(const char *);
int strcmp(const char *, const char *);
extern int kh1_host_trace;
unsigned long kh1_host_frame(void);

#define NULL_SND_SE 0x0000
#define NULL_SND_SE_N 24
#define NULL_SND_SE_SIZE 0xB4
#define NULL_SND_STREAM 0x1800
#define NULL_SND_STREAM_N 4
#define NULL_SND_STREAM_SIZE 0x48
#define NULL_SND_PENDING 0x1F00
/* how long an SE (or an object SE stream) "plays" before the server ends it: one second */
#define NULL_SND_SE_FRAMES 60

static u8 *null_snd_status;
static s32 null_snd_landing;
static s32 null_snd_se_left[NULL_SND_SE_N];          /* frames to its end, 0 = held until stopped */
static s32 null_snd_stream_left[NULL_SND_STREAM_N];
static int null_snd_trace = -1;
unsigned kh1_snd_commands; /* main.c's summary */

static int trace(void) {
    if (null_snd_trace < 0) {
        const char *s = getenv("KH1_HOST_SND");
        null_snd_trace = s && strcmp(s, "trace") == 0;
    }
    return null_snd_trace || kh1_host_trace >= 6;
}

static u8 *se(int i) { return null_snd_status + NULL_SND_SE + i * NULL_SND_SE_SIZE; }
static u8 *stream(int i) { return null_snd_status + NULL_SND_STREAM + i * NULL_SND_STREAM_SIZE; }
#define W(p, off) (*(s32 *)((p) + (off)))

/* names and argument names of the queued commands (docs/sound-spec.md 3) */
static const struct { s32 cmd; const char *name; const char *args[7]; } null_snd_cmds[] = {
    { 0x26, "free", { "type", "slot" } },
    { 0x03, "wave", { "slot", "addr", "size" } },
    { 0x04, "setab", { "slot", "addr", "size" } },
    { 0x0B, "seq", { "slot", "addr", "size" } },
    { 0x28, "voicebank", { "addr", "size", "arg" } },
    { 0x0C, "music-start", { "track", "start", "volume", "fade", "flag", "frames2" } },
    { 0x0D, "music-stop", { "track" } },
    { 0x0E, "music-fade", { "track", "volume", "frames" } },
    { 0x05, "se-play", { "bank", "id", "sub", "left", "right" } },
    { 0x08, "se-volume", { "bank", "id", "sub", "left", "right" } },
    { 0x06, "se-stop", { "bank", "id", "sub" } },
    { 0x07, "se-fadeout", { "bank", "id", "sub", "x", "frames" } },
    { 0x02, "se-switch", { "bank", "id", "sub", "value" } },
    { 0x09, "cmd9", { "a", "b", "c", "d" } },
    { 0x12, "voice-play", { "addr", "size", "left", "right", "pitch", "h30", "h31" } },
    { 0x14, "voice-move", { "addr", "left", "right" } },
    { 0x13, "voice-stop", { "addr" } },
    { 0x15, "cmd15", { "a", "b", "c" } },
    { 0x29, "objse-play", { "bank", "id", "x", "y" } },
    { 0x2A, "objse-move", { "bank", "id", "left", "right" } },
    { 0x2B, "objse-stop", { "bank", "id" } },
};

static const char *rpc_name(unsigned num) {
    switch (num) {
    case 0x00: return "bind";
    case 0x0F: return "pause";
    case 0x1E: return "queue";
    case 0x23: return "stereo";
    case 0x24: return "movie-mode";
    case 0x27: return "room-setting";
    case 0x2F: return "music-request";
    case 0x30: return "music-ready";
    default: return "other";
    }
}

static void trace_record(const s32 *q) {
    unsigned i, k;
    for (i = 0; i < sizeof null_snd_cmds / sizeof null_snd_cmds[0]; i++)
        if (null_snd_cmds[i].cmd == q[0]) break;
    if (i == sizeof null_snd_cmds / sizeof null_snd_cmds[0]) {
        printf("kh1-host: snd %lu q 0x%02x unknown %d %d %d %d %d %d %d\n", kh1_host_frame(), q[0], q[1], q[2],
               q[3], q[4], q[5], q[6], q[7]);
        return;
    }
    printf("kh1-host: snd %lu q 0x%02x %s", kh1_host_frame(), q[0], null_snd_cmds[i].name);
    for (k = 0; k < 7 && null_snd_cmds[i].args[k]; k++) {
        if (k == 1 && (q[0] == 3 || q[0] == 4 || q[0] == 0xB)) printf(" %s=0x%x", null_snd_cmds[i].args[k], q[k + 1]);
        else if (k == 0 && (q[0] >= 0x12 && q[0] <= 0x14 || q[0] == 0x28)) printf(" %s=0x%x", null_snd_cmds[i].args[k], q[k + 1]);
        else printf(" %s=%d", null_snd_cmds[i].args[k], q[k + 1]);
    }
    printf("\n");
}

/* an SE voice matches: bank -100 is every bank (the init's stop), a negative id or sub any (inferred
 * from func_001ecb08's wildcards and the init's (-100, -1, -1)) */
static int se_match(int i, s32 bank, s32 id, s32 sub) {
    u8 *p = se(i);
    return (s8)p[0] && (bank == -100 || W(p, 0xC) == bank) && (id < 0 || W(p, 0x10) == id) &&
           (sub < 0 || W(p, 4) == sub);
}

static void se_end(int i) {
    u8 *p = se(i);
    p[0] = 0;
    null_snd_se_left[i] = 0;
}

static void stream_end(int i) {
    stream(i)[4] = 0;
    null_snd_stream_left[i] = 0;
}

static void record(const s32 *q) {
    int i;
    kh1_snd_commands++;
    if (trace()) trace_record(q);
    switch (q[0]) {
    case 3: case 4: case 0xB: case 0x28:
        null_snd_landing++;
        break;
    case 5: /* play an SE: the first free voice; none free, the IOP's choice is not known: dropped */
        for (i = 0; i < NULL_SND_SE_N; i++) {
            u8 *p = se(i);
            if ((s8)p[0]) continue;
            p[0] = 1;
            W(p, 4) = q[3];
            W(p, 0xC) = q[1];
            W(p, 0x10) = q[2];
            null_snd_se_left[i] = NULL_SND_SE_FRAMES;
            break;
        }
        break;
    case 6:
        for (i = 0; i < NULL_SND_SE_N; i++)
            if (se_match(i, q[1], q[2], q[3])) se_end(i);
        break;
    case 7: /* stop after the fade */
        for (i = 0; i < NULL_SND_SE_N; i++)
            if (se_match(i, q[1], q[2], q[3]))
                null_snd_se_left[i] = q[5] > 0 ? q[5] : 1;
        break;
    case 0x12: /* a voice: as long as its VAG data (28 samples a 16-byte block) at its pitch */
        for (i = 0; i < NULL_SND_STREAM_N; i++) {
            u8 *p = stream(i);
            s32 rate = (s32)((long long)q[5] * 48000 / 4096);
            if ((s8)p[4]) continue;
            p[0] = 1;
            p[4] = 1;
            W(p, 0x10) = q[1];
            null_snd_stream_left[i] = rate > 0 ? (s32)((long long)(q[2] / 16) * 28 * 60 / rate) + 1
                                               : NULL_SND_SE_FRAMES;
            break;
        }
        break;
    case 0x13:
        for (i = 0; i < NULL_SND_STREAM_N; i++) {
            u8 *p = stream(i);
            if ((s8)p[4] && (p[0] & 0x7F) == 1 && (q[1] == -1 || W(p, 0x10) == q[1])) stream_end(i);
        }
        break;
    case 0x29: /* an object SE as a stream */
        for (i = 0; i < NULL_SND_STREAM_N; i++) {
            u8 *p = stream(i);
            if ((s8)p[4]) continue;
            p[0] = 0;
            p[2] = (u8)q[1];
            p[3] = (u8)q[2];
            p[4] = 1;
            W(p, 0x10) = 0;
            null_snd_stream_left[i] = NULL_SND_SE_FRAMES;
            break;
        }
        break;
    case 0x2B:
        for (i = 0; i < NULL_SND_STREAM_N; i++) {
            u8 *p = stream(i);
            if ((s8)p[4] && p[0] == 0 && (s8)p[2] == (s8)q[1] && (s8)p[3] == (s8)q[2]) stream_end(i);
        }
        break;
    }
}

/* PlatSifCallRpc for the sound server (17): every call snd_rpc.c makes */
void kh1_null_snd_rpc(unsigned num, void *send, int ssize, void *recv, int rsize) {
    const s32 *w = send;
    int i;
    if (num == 0 && send != 0 && ssize >= 4) {
        /* the bind (func_001ec7d0, which cleared the block): every voice ends */
        null_snd_status = (u8 *)(unsigned long)((u32 *)send)[0];
        null_snd_landing = 0;
        for (i = 0; i < NULL_SND_SE_N; i++) null_snd_se_left[i] = 0;
        for (i = 0; i < NULL_SND_STREAM_N; i++) null_snd_stream_left[i] = 0;
    }
    if (trace() && num != 30)
        printf("kh1-host: snd %lu rpc 0x%02x %s %d %d %d %d\n", kh1_host_frame(), num, rpc_name(num),
               w ? w[0] : 0, w ? w[1] : 0, w ? w[2] : 0, w ? w[3] : 0);
    if (num == 30 && send != 0 && null_snd_status != 0) {
        /* the queue: 8-word records until the first unused (-1) one (func_001ed000, func_001edba0);
         * the send is 0x2000 bytes, the first 256 records of the EE's 1024 */
        for (i = 0; i < ssize / 32 && w[i * 8] != -1; i++) record(&w[i * 8]);
    }
    if (num == 0x30 && recv != 0 && rsize >= 4) *(u32 *)recv = 1;
}

/* a frame (kh1_host_vblank): the transfers sent before it are done, and the voices whose time is up
 * end */
void kh1_null_iop_frame(void) {
    int i;
    if (null_snd_status == 0) return;
    if (null_snd_landing) {
        s32 *pending = (s32 *)(null_snd_status + NULL_SND_PENDING);
        *pending -= null_snd_landing;
        if (*pending < 0) *pending = 0;
        null_snd_landing = 0;
    }
    for (i = 0; i < NULL_SND_SE_N; i++) {
        if (null_snd_se_left[i] == 0 || --null_snd_se_left[i] != 0) continue;
        if (trace())
            printf("kh1-host: snd %lu end se bank=%d id=%d sub=%d\n", kh1_host_frame(), W(se(i), 0xC),
                   W(se(i), 0x10), W(se(i), 4));
        se_end(i);
    }
    for (i = 0; i < NULL_SND_STREAM_N; i++) {
        u8 *p = stream(i);
        if (null_snd_stream_left[i] == 0 || --null_snd_stream_left[i] != 0) continue;
        if (trace()) {
            if (p[0] & 0x7F) printf("kh1-host: snd %lu end voice addr=0x%x\n", kh1_host_frame(), W(p, 0x10));
            else printf("kh1-host: snd %lu end objse bank=%d id=%d\n", kh1_host_frame(), (s8)p[2], (s8)p[3]);
        }
        stream_end(i);
    }
}
