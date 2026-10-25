/* host/null/sound.c, the null sound server, on made-up queues (no game data): tests/selftest.sh builds it
 * with gcc -m32 when that works.  The status block and the records are laid out as src/sound/snd_rpc.c
 * writes and reads them (docs/sound-spec.md). */
#include "common.h"

int printf(const char *, ...);
void kh1_null_snd_rpc(unsigned num, void *send, int ssize, void *recv, int rsize);
void kh1_null_iop_frame(void);

int kh1_host_trace;
unsigned long kh1_host_frame(void) { return 0; }

static u8 status[0x2000] ALIGNED(64);
static u32 buf[2048];
static s32 queue[256][8];
static int n;

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("sound_test: %s\n", name); fails++; } } while (0)

static void q(s32 cmd, s32 a, s32 b, s32 c, s32 d, s32 e) {
    s32 *r = queue[n++];
    r[0] = cmd; r[1] = a; r[2] = b; r[3] = c; r[4] = d; r[5] = e; r[6] = 0; r[7] = 0;
}
static void flush(void) {
    int i, j;
    for (i = n; i < 256; i++)
        for (j = 0; j < 8; j++) queue[i][j] = -1;
    kh1_null_snd_rpc(30, queue, sizeof queue, queue, sizeof queue);
    n = 0;
}
static void frames(int k) { while (k--) kh1_null_iop_frame(); }
#define PENDING (*(s32 *)(status + 0x1F00))
#define SE_USED(i) ((s8)status[(i) * 0xB4])
#define SE_BANK(i) (*(s32 *)(status + (i) * 0xB4 + 0xC))
#define SE_ID(i) (*(s32 *)(status + (i) * 0xB4 + 0x10))
#define ST(i) (status + 0x1800 + (i) * 0x48)

int main(void) {
    int i, used;
    buf[0] = (u32)(unsigned long)status;
    buf[1] = 0;
    kh1_null_snd_rpc(0, buf, sizeof buf, buf, sizeof buf);

    /* transfers: the EE adds one per transfer it queues; the next frame takes them off */
    PENDING = 4;
    q(3, 2, 0x1000, 0x800, 0, 0);
    q(4, 2, 0x2000, 0x100, 0, 0);
    q(0xB, 0, 0x3000, 0x400, 0, 0);
    q(0x28, 0x4000, 0x200, 0, 0, 0);
    flush();
    CHECK("transfers wait for the frame", PENDING == 4);
    frames(1);
    CHECK("four transfers done, 0x28 counted", PENDING == 0);

    /* an SE plays for a second and ends; a stop ends it at once */
    q(5, 2, 12, 0, 0x3FFF, 0x3FFF);
    q(5, -1, 400, 3, 0x3FFF, 0x3FFF);
    flush();
    CHECK("SE 0 playing", SE_USED(0) && SE_BANK(0) == 2 && SE_ID(0) == 12);
    CHECK("SE 1 playing", SE_USED(1) && SE_BANK(1) == -1 && SE_ID(1) == 400);
    q(6, -1, 400, -1, 0, 0);
    flush();
    CHECK("stop by bank and id, any sub", !SE_USED(1) && SE_USED(0));
    frames(59);
    CHECK("SE still playing at frame 59", SE_USED(0));
    frames(1);
    CHECK("SE ended by time", !SE_USED(0));

    /* a fade-out stop ends it after its frames; the init's (-100, -1, -1) stops every bank */
    q(5, -8, 7, 1, 0x1FFF, 0x1FFF);
    flush();
    q(7, -8, 7, 1, -1, 5);
    flush();
    frames(4);
    CHECK("fading SE plays on", SE_USED(0));
    frames(1);
    CHECK("fading SE ends after its frames", !SE_USED(0));
    for (i = 0; i < 30; i++) q(5, 2, i, 0, 0, 0);
    flush();
    for (used = 0, i = 0; i < 24; i++) used += SE_USED(i) != 0;
    CHECK("24 voices at most", used == 24);
    q(6, -100, -1, -1, 0, 0);
    flush();
    for (used = 0, i = 0; i < 24; i++) used += SE_USED(i) != 0;
    CHECK("stop all", used == 0);

    /* a voice: 0x5400 bytes of VAG = 0x540 blocks x 28 samples at 24 kHz (pitch 2048) = 1.568 s = 94 frames */
    q(0x12, 0x8000, 0x5400, 0x3FFF, 0x3FFF, 2048);
    flush();
    CHECK("voice playing", ST(0)[4] && (ST(0)[0] & 0x7F) == 1 && *(s32 *)(ST(0) + 0x10) == 0x8000);
    frames(94);
    CHECK("voice plays its length", ST(0)[4]);
    frames(1);
    CHECK("voice ends after its length", !ST(0)[4]);
    q(0x12, 0x8000, 0x5400, 0x3FFF, 0x3FFF, 2048);
    q(0x29, -3, 5, 0, 0, 0);
    flush();
    CHECK("object SE stream", ST(1)[4] && ST(1)[0] == 0 && (s8)ST(1)[2] == -3 && ST(1)[3] == 5);
    q(0x13, -1, 0, 0, 0, 0);
    q(0x2B, -3, 5, 0, 0, 0);
    flush();
    CHECK("voice and object SE stopped", !ST(0)[4] && !ST(1)[4]);

    /* RPC 0x30 answers ready; another direct call reads back its own argument */
    buf[0] = 1;
    kh1_null_snd_rpc(0x30, buf, sizeof buf, buf, sizeof buf);
    CHECK("0x30 ready", buf[0] == 1);
    buf[0] = 7;
    kh1_null_snd_rpc(0x27, buf, sizeof buf, buf, sizeof buf);
    CHECK("other calls unanswered", buf[0] == 7);

    printf("sound_test: %d checks, %d failed\n", checks, fails);
    return fails != 0;
}
