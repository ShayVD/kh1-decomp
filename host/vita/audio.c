/* The Vita's sound output (docs/sound-spec.md "The IOP on the port", docs/vita-build.md "Sound"):
 * once host/port/snd.c has the user's own sound driver running (the game's bind, RPC 0), a thread of
 * its own runs the driver's ticks and the SPU2 mix (kh1_snd_render) and hands each 256-sample
 * stereo buffer to sceAudioOut's main port at 48 kHz, which blocks until the last one has played: the
 * thread is paced by the audio hardware, not by the game's frames.  The game thread only copies its
 * per-frame command queue into snd.c's FIFO.  The thread sits on the third core with the GPU frame's
 * thread (config.txt's sndcore=), at a higher priority so that a busy frame does not starve it.
 * Not part of the PS2 build. */
#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <string.h>
#include "common.h"

void kh1_vita_log(const char *fmt, ...);
#define vlog kh1_vita_log
void kh1_snd_render(s16 *out, int frames);
void kh1_snd_set_lock(void (*l)(void), void (*u)(void));
extern void (*kh1_snd_started)(void);
extern int kh1_snd_wanted;

#define AUDIO_GRAIN 256

int kh1_vita_snd = 1;      /* config.txt's snd= (0: the null server, no sound) */
int kh1_vita_snd_core = 2; /* config.txt's sndcore= (0, 1 or 2) */
u32 kh1_vita_snd_us;       /* time in kh1_snd_render (the watchdog's sound line) */
u32 kh1_vita_snd_bufs;

static SceKernelLwMutexWork snd_mutex;
static int port = -1;

static void snd_lock(void) { sceKernelLockLwMutex(&snd_mutex, 1, 0); }
static void snd_unlock(void) { sceKernelUnlockLwMutex(&snd_mutex, 1); }

static int audio_thread(SceSize args, void *argp) {
    static s16 buf[2][AUDIO_GRAIN * 2] __attribute__((aligned(64)));
    int k = 0;
    (void)args;
    (void)argp;
    for (;;) {
        u32 t0 = (u32)sceKernelGetProcessTimeWide();
        kh1_snd_render(buf[k], AUDIO_GRAIN);
        kh1_vita_snd_us += (u32)sceKernelGetProcessTimeWide() - t0;
        kh1_vita_snd_bufs++;
        sceAudioOutOutput(port, buf[k]);
        k ^= 1;
    }
    return 0;
}

static void start_output(void) {
    static const SceUInt masks[3] = { SCE_KERNEL_CPU_MASK_USER_0, SCE_KERNEL_CPU_MASK_USER_1, SCE_KERNEL_CPU_MASK_USER_2 };
    SceUID t;
    int vol[2] = { SCE_AUDIO_VOLUME_0DB, SCE_AUDIO_VOLUME_0DB };
    port = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_MAIN, AUDIO_GRAIN, 48000, SCE_AUDIO_OUT_MODE_STEREO);
    if (port < 0) {
        vlog("kh1-vita: sound: no audio port (0x%08x)\n", port);
        return;
    }
    sceAudioOutSetVolume(port, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, vol);
    if (kh1_vita_snd_core < 0 || kh1_vita_snd_core > 2) kh1_vita_snd_core = 2;
    t = sceKernelCreateThread("kh1_snd", audio_thread, 0x10000100 - 16, 0x8000, 0, masks[kh1_vita_snd_core], 0);
    if (t < 0 || sceKernelStartThread(t, 0, 0) < 0) {
        vlog("kh1-vita: sound: no audio thread (0x%08x)\n", t);
        return;
    }
    vlog("kh1-vita: sound: the disc's driver on a thread on core %d, 48 kHz, %d-sample buffers\n", kh1_vita_snd_core,
         AUDIO_GRAIN);
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
