/* host/null/pad.c, the null pad and its script (KH1_HOST_PAD), on made-up scripts: tests/selftest.sh
 * builds it with gcc -m32 when that works and passes a scratch directory.  The buffer is checked the
 * way src/pad/padread.nostrict.c func_0011f668 reads it. */
#include "common.h"
#include "platform/pad.h"

typedef struct _IO_FILE FILE;
FILE *fopen(const char *, const char *);
int fputs(const char *, FILE *);
int fclose(FILE *);
int printf(const char *, ...);
int sprintf(char *, const char *, ...);
int kh1_null_pad_load(const char *path);

int kh1_host_trace;
/* the goto lines' game state (session 136): the player at the origin, a camera whose turn only
 * mirrors x (camera/view.c func_00124d58's with the angle 0) */
static f32 player[8] __attribute__((aligned(16)));
u8 *D_002E26A0[3] = { (u8 *)player };
float D_004F77E0;
void func_00124d58(void *v, void *out, float cam, float w) {
    ((f32 *)out)[0] = -((f32 *)v)[0];
    ((f32 *)out)[1] = 0.0f;
    ((f32 *)out)[2] = ((f32 *)v)[2];
}
static unsigned long frame;
unsigned long kh1_host_frame(void) { return frame; }

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("pad_test: %s\n", name); fails++; } } while (0)

static char path[512];
static int load(const char *dir, const char *text) {
    FILE *f;
    sprintf(path, "%s/pad_test.txt", dir);
    f = fopen(path, "w");
    fputs(text, f);
    fclose(f);
    return kh1_null_pad_load(path);
}
/* what func_0011f668 makes of the read: the game's bits, or -1 when the pad is not stable */
static s32 game_bits(u8 *buf) {
    if (PlatPadGetState(0) != 1) return -1;
    if (PlatPadRead(0, buf) < 0) return -2;
    return (buf[0] | (buf[1] << 8)) ^ 0xffff;
}

int main(int argc, char **argv) {
    const char *dir = argc > 1 ? argv[1] : ".";
    u8 buf[256], prof[20];
    CHECK("not a frame", load(dir, "x START\n") < 0);
    CHECK("not a button", load(dir, "10 STRAT\n") < 0);
    CHECK("frame order", load(dir, "10 START\n5 -\n") < 0);
    CHECK("stick range", load(dir, "10 - 1 2 3 256\n") < 0);
    CHECK("stick count", load(dir, "10 - 1 2\n") < 0);
    CHECK("goto needs X Z", load(dir, "10 - goto 5\n") < 0);
    CHECK("goto", load(dir, "10 CROSS goto 0 100 20\n") == 1);
    frame = 10;
    CHECK("goto: the buttons", game_bits(buf) == PAD_CROSS);
    CHECK("goto: the stick toward +z (down here: y is +z after the turn)", buf[4] > 118 && buf[4] < 138 && buf[5] > 240);
    player[6] = 90.0f;
    CHECK("goto: centred within R", game_bits(buf) == PAD_CROSS && buf[4] == 128 && buf[5] == 128);
    player[6] = 100.0f;
    player[4] = 100.0f; /* (100, 100): the target is to -x, which the mirror makes the stick's +x */
    CHECK("goto: the stick toward -x", (game_bits(buf), buf[4] > 240 && buf[5] > 118 && buf[5] < 138));
    CHECK("script", load(dir, "# the title\n\n100 START   # press\n102 -\n150 CIRCLE+UP 128 128 255 0\n"
                              "152 0x4000\n200 out\n260 -\n") == 6);
    frame = 0;
    CHECK("frame 0: connected, nothing", game_bits(buf) == 0 && buf[2] == 128 && buf[5] == 128);
    CHECK("profile: both sticks", PlatPadGetButtonProfile(0, prof) >= 0 && (prof[2] & 0xf) == 0xf);
    frame = 100;
    CHECK("frame 100: START", game_bits(buf) == PAD_START);
    frame = 101;
    CHECK("frame 101: held", game_bits(buf) == PAD_START);
    frame = 102;
    CHECK("frame 102: let go", game_bits(buf) == 0);
    frame = 150;
    CHECK("frame 150: CIRCLE+UP", game_bits(buf) == (PAD_CIRCLE | PAD_UP));
    CHECK("frame 150: sticks rx ry lx ly", buf[2] == 128 && buf[3] == 128 && buf[4] == 255 && buf[5] == 0);
    frame = 152;
    CHECK("frame 152: a number", game_bits(buf) == PAD_CROSS && buf[4] == 128);
    frame = 230;
    CHECK("frame 230: out", game_bits(buf) == -1);
    CHECK("frame 230: no profile", PlatPadGetButtonProfile(0, prof) < 0);
    buf[0] = buf[1] = 0;
    CHECK("frame 230: a read fails, nothing pressed", PlatPadRead(0, buf) < 0 && buf[0] == 0xFF && buf[1] == 0xFF);
    frame = 100000;
    CHECK("after the last line: back in", game_bits(buf) == 0);
    printf("pad_test: %d / %d checks pass\n", checks - fails, checks);
    return fails != 0;
}
