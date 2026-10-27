/* platform/pad.h on the Vita (docs/vita-port-plan.md section 1): sceCtrl's buttons and sticks
 * written in libpad2's layout, so src/pad/padread*.c decodes them unchanged.  libpad2's digital
 * bits are SceCtrl's (SELECT 0x1 .. SQUARE 0x8000), active low in bytes 0-1; bytes 2-5 the sticks,
 * right x / y then left x / y, 0-255 with 128 the centre.  The Vita has two shoulder buttons: they
 * are L1 / R1 (the game's lock-on and camera); L2 / R2 / L3 / R3 are the rear touch pad's four
 * quarters (upper left L2, upper right R2, lower left L3, lower right R3).  Circle confirms and
 * cross cancels, as on the Japanese PS2.  Vibration is a no-op.  Session 137v: config.txt's pad=FILE plays a
 * host pad script (host/null/pad.c, tests/host/pads/) instead, so a run reaches a place unattended.  Not part of
 * the PS2 build. */
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include "common.h"
#include "platform/pad.h"
#include "vita.h"

static unsigned int cur;

static void sample(u8 *stick) {
    SceCtrlData c;
    SceTouchData t;
    unsigned int b, i;
    static int ready;
    if (!ready) {
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
        ready = 1;
    }
    if (sceCtrlPeekBufferPositive(0, &c, 1) < 0) {
        c.buttons = 0;
        c.lx = c.ly = c.rx = c.ry = 128;
    }
    b = c.buttons & (PAD_SELECT | PAD_START | PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT | PAD_TRIANGLE | PAD_CIRCLE |
                     PAD_CROSS | PAD_SQUARE);
    if (c.buttons & SCE_CTRL_LTRIGGER) b |= PAD_L1;
    if (c.buttons & SCE_CTRL_RTRIGGER) b |= PAD_R1;
    /* the rear pad: 1920 x 890 or so, its middle at (960, 500) */
    if (sceTouchPeek(SCE_TOUCH_PORT_BACK, &t, 1) > 0)
        for (i = 0; i < t.reportNum && i < SCE_TOUCH_MAX_REPORT; i++) {
            int left = t.report[i].x < 960, top = t.report[i].y < 500;
            b |= top ? (left ? PAD_L2 : PAD_R2) : (left ? PAD_L3 : PAD_R3);
        }
    cur = b;
    if (stick) {
        stick[0] = c.rx;
        stick[1] = c.ry;
        stick[2] = c.lx;
        stick[3] = c.ly;
    }
}

unsigned int kh1_vita_buttons(void) {
    sample(0);
    return cur;
}

extern const char *kh1_vita_pad_script; /* host/null/pad.c */
int kh1_script_PadGetState(int socket);
int kh1_script_PadGetButtonProfile(int socket, void *profile);
int kh1_script_PadRead(int socket, u8 *data);

int PlatDbcInit(void) { return 0; }
int PlatPadInit(int mode) { return 0; }
int PlatPadCreateSocket(void *param, void *addr) { return 0; }
/* the Vita's own controls are always in: stable */
int PlatPadGetState(int socket) { return kh1_vita_pad_script ? kh1_script_PadGetState(socket) : 1; }
/* a DualShock 2's: every digital button and both sticks */
int PlatPadGetButtonProfile(int socket, void *profile) {
    u8 *p = profile;
    if (kh1_vita_pad_script) return kh1_script_PadGetButtonProfile(socket, profile);
    p[0] = p[1] = p[2] = p[3] = 0xFF;
    return 4;
}
int PlatPadRead(int socket, u8 *data) {
    u8 stick[4];
    if (kh1_vita_pad_script) return kh1_script_PadRead(socket, data);
    sample(stick);
    data[0] = ~cur & 0xFF;
    data[1] = (~cur >> 8) & 0xFF;
    data[2] = stick[0];
    data[3] = stick[1];
    data[4] = stick[2];
    data[5] = stick[3];
    return 6;
}
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data) { return 0; }
