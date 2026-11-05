/* The Vita's sound output (docs/sound-spec.md "The IOP on the port", docs/vita-build.md "Sound"):
 * once host/port/snd.c has the user's own sound driver running (the game's bind, RPC 0), three
 * threads play it.
 *   - the tick thread (kh1_snd_iop) runs the driver's 240 Hz ticks a few ticks ahead of the mixer;
 *   - the mixer (kh1_snd_mix) applies each tick's SPU2 writes and mixes its 200 samples into a ring
 *     about 64 ms ahead of the output.
 *     Both run at a lower priority than the game's own threads and on any core (config.txt's
 *     sndcore= pins both to one), so they take the time the game leaves, on two cores at once, and
 *     never hold up a frame;
 *   - the output (kh1_snd_out) hands the ring's samples to sceAudioOut's main port at 48 kHz, 256 at a
 *     time, and blocks until the last ones have played: it is paced by the audio hardware and does
 *     almost no work, so it runs at a high priority.  When the ring runs dry it plays silence for
 *     the gap (counted as short on the watchdog's sound line) rather than wait.
 * The game thread only copies its per-frame command queue into snd.c's FIFO; the sounds it starts
 * play about 100 ms later.  The ring and the output thread are vita-port-kit's (vita/runtime/audioout, vendored:
 * docs/vita-port-kit.md): the plain ring, the mixer paced by its level.
 * Not part of the PS2 build. */
#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/cpu.h>
#include <string.h>
#include "common.h"
#include "../../third_party/vita-port-kit/vita/runtime/audioout/vpk_audio_out.h"
void kh1_vita_thread_note(int uid, const char *name); /* main.c: the watchdog's `threads:` line */

void kh1_vita_log(const char *fmt, ...);
#define vlog kh1_vita_log
int kh1_snd_tick_step(void);
int kh1_snd_mix_step(s16 *out);
void kh1_snd_threads_begin(void);
void kh1_snd_set_lock(void (*l)(void), void (*u)(void));
extern void (*kh1_snd_started)(void);
extern int kh1_snd_wanted;

#define AUDIO_GRAIN 256
#define RING 8192        /* frames (stereo pairs), a power of two */
#define LEAD 3072        /* how far the mixer runs ahead: 64 ms (the tick thread adds up to 33) */

int kh1_vita_snd = 1;       /* config.txt's snd= (0: the null server, no sound) */
int kh1_vita_snd_core = -1; /* config.txt's sndcore= (-1: any core; 0, 1 or 2 pins the mixer) */
/* 2026-10-31: config.txt's sndprio=, the tick thread's and the mixer's priority against the game's threads
 * (0x10000100): negative above them, positive below.  -4, the default since Shay's Vita run of the Dive with
 * renderer=native: at 16 (below, as before) the three cores were busy and about a third of the buffers came out
 * short (garbled sound); at -4 the sound played clean.  The two threads are paced by the output (the mixer stops
 * 64 ms ahead), so above the game they take only what the sound needs */
int kh1_vita_snd_prio = -4;
u32 kh1_vita_snd_us;        /* the mixer's time mixing (the watchdog's sound line) */
u32 kh1_vita_snd_tick_us;   /* the tick thread's time in the driver */
u32 kh1_vita_snd_bufs;      /* buffers played */
u32 kh1_vita_snd_under;     /* buffers the ring could not fill (silence played in their gap) */
u32 kh1_vita_snd_queued;    /* frames in the ring at the last buffer */

static SceKernelLwMutexWork snd_mutex;
static SceUID room;         /* signalled by the output when it has taken a buffer */
static SceUID ticked, mixed; /* a tick done (for the mixer), a tick mixed (for the tick thread) */
static int port = -1;
static VpkAudioRing ring;   /* the plain ring (no rate control): RING frames */
static VpkAudioOut out;     /* the port and the output thread */

static void snd_lock(void) { sceKernelLockLwMutex(&snd_mutex, 1, 0); }
static void snd_unlock(void) { sceKernelUnlockLwMutex(&snd_mutex, 1); }

static int tick_thread(SceSize args, void *argp) {
    (void)args;
    (void)argp;
    for (;;) {
        u32 t0 = (u32)sceKernelGetProcessTimeWide();
        if (kh1_snd_tick_step()) {
            kh1_vita_snd_tick_us += (u32)sceKernelGetProcessTimeWide() - t0;
            sceKernelSignalSema(ticked, 1);
        } else {
            SceUInt timeout = 10000;
            sceKernelWaitSema(mixed, 1, &timeout);
        }
    }
    return 0;
}

static int mix_thread(SceSize args, void *argp) {
    static s16 buf[200 * 2] __attribute__((aligned(64)));
    (void)args;
    (void)argp;
    for (;;) {
        u32 level = vpk_audio_ring_level(&ring), t0, n;
        if (level > RING - 200 || level >= LEAD) {
            SceUInt timeout = 20000;
            sceKernelWaitSema(room, 1, &timeout);
            continue;
        }
        t0 = (u32)sceKernelGetProcessTimeWide();
        n = (u32)kh1_snd_mix_step(buf);
        if (!n) {
            SceUInt timeout = 10000;
            sceKernelWaitSema(ticked, 1, &timeout);
            continue;
        }
        kh1_vita_snd_us += (u32)sceKernelGetProcessTimeWide() - t0;
        sceKernelSignalSema(mixed, 1);
        vpk_audio_ring_push(&ring, buf, (int)n); /* fits: the level was checked above */
    }
    return 0;
}

/* the output thread (the kit's vpk_audio_out) after each grain's pull, before the grain plays: when the ring could
 * not fill it, silence played in the gap */
static void out_pulled(void *user, int got, const VpkAudioRing *r) {
    (void)user;
    if (got < AUDIO_GRAIN) kh1_vita_snd_under++;
    kh1_vita_snd_queued = r->last_level;
    sceKernelSignalSema(room, 1);
    kh1_vita_snd_bufs++;
}

/* the mod menu's volume (menu.c, config.txt's volume=): 0-100, of the output's 0 dB */
int kh1_vita_volume = 100;
void kh1_vita_audio_volume(int percent) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    kh1_vita_volume = percent;
    if (port >= 0) vpk_audio_out_volume(&out, percent);
}

static void start_output(void) {
    static const SceUInt masks[3] = { SCE_KERNEL_CPU_MASK_USER_0, SCE_KERNEL_CPU_MASK_USER_1, SCE_KERNEL_CPU_MASK_USER_2 };
    SceUID t;
    SceUInt mix_mask = kh1_vita_snd_core >= 0 && kh1_vita_snd_core <= 2 ? masks[kh1_vita_snd_core] : SCE_KERNEL_CPU_MASK_USER_ALL;
    static const VpkAudioRingConfig rc = { RING, 0, 0, 0, 0, 0, 0 };
    /* the output above the game's threads (0x10000100): it only copies and waits */
    VpkAudioOutConfig oc = { SCE_AUDIO_OUT_PORT_TYPE_MAIN, AUDIO_GRAIN, 48000, 0, "kh1_snd_out", 0x10000100 - 16,
                             SCE_KERNEL_CPU_MASK_USER_ALL, 0x4000, out_pulled, 0 };
    oc.volume = kh1_vita_volume;
    vpk_audio_ring_init(&ring, &rc);
    port = vpk_audio_out_open(&out, &ring, &oc);
    if (port < 0) {
        vlog("kh1-vita: sound: no audio port (0x%08x)\n", port);
        return;
    }
    room = sceKernelCreateSema("kh1_snd_room", 0, 0, 64, 0);
    ticked = sceKernelCreateSema("kh1_snd_ticked", 0, 0, 64, 0);
    mixed = sceKernelCreateSema("kh1_snd_mixed", 0, 0, 64, 0);
    kh1_snd_threads_begin();
    /* the game's threads run at 0x10000100: the tick thread and the mixer below them, the output above */
    t = sceKernelCreateThread("kh1_snd_iop", tick_thread, 0x10000100 + kh1_vita_snd_prio, 0x8000, 0, mix_mask, 0);
    if (t < 0 || sceKernelStartThread(t, 0, 0) < 0) {
        vlog("kh1-vita: sound: no tick thread (0x%08x)\n", t);
        return;
    }
    kh1_vita_thread_note(t, "sound ticks");
    t = sceKernelCreateThread("kh1_snd_mix", mix_thread, 0x10000100 + kh1_vita_snd_prio, 0x8000, 0, mix_mask, 0);
    if (t < 0 || sceKernelStartThread(t, 0, 0) < 0) {
        vlog("kh1-vita: sound: no mixer thread (0x%08x)\n", t);
        return;
    }
    kh1_vita_thread_note(t, "sound mix");
    t = vpk_audio_out_start(&out);
    if (t < 0) {
        vlog("kh1-vita: sound: no output thread (0x%08x)\n", t);
        return;
    }
    kh1_vita_thread_note(t, "sound out");
    if (kh1_vita_snd_core >= 0 && kh1_vita_snd_core <= 2)
        vlog("kh1-vita: sound: the disc's driver ticking and mixing on core %d, %d ms ahead, 48 kHz\n",
             kh1_vita_snd_core, LEAD * 1000 / 48000);
    else
        vlog("kh1-vita: sound: the disc's driver ticking and mixing on any cores %s the game's threads (sndprio=%d), "
             "%d ms ahead, 48 kHz\n", kh1_vita_snd_prio > 0 ? "below" : kh1_vita_snd_prio < 0 ? "above" : "level with",
             kh1_vita_snd_prio, LEAD * 1000 / 48000);
}

/* from main(), before the game runs: the lock, and the output started when snd.c starts the driver */
void kh1_vita_audio_init(void) {
    if (!kh1_vita_snd) {
        vlog("kh1-vita: sound: off (config.txt snd=0)\n");
        return;
    }
    sceKernelCreateLwMutex(&snd_mutex, "kh1_snd", 0, 0, 0);
    kh1_snd_set_lock(snd_lock, snd_unlock);
    kh1_snd_started = start_output;
    kh1_snd_wanted = 1;
}
