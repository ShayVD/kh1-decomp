/* platform/pad.h on the Vita (docs/vita-port-plan.md section 1): sceCtrl's buttons and sticks
 * written in libpad2's layout, so src/pad/padread*.c decodes them unchanged.  libpad2's digital
 * bits are SceCtrl's (SELECT 0x1 .. SQUARE 0x8000), active low in bytes 0-1; bytes 2-5 the sticks,
 * right x / y then left x / y, 0-255 with 128 the centre.  The Vita has two shoulder buttons: they
 * are L1 / R1 (the game's lock-on and camera); L2 / R2 / L3 / R3 are the rear touch pad's four
 * quarters (upper left L2, upper right R2, lower left L3, lower right R3).  Circle confirms and
 * cross cancels, as on the Japanese PS2.  Vibration is a no-op.  Session 137v: config.txt's pad=FILE plays a
 * host pad script (host/null/pad.c, tests/host/pads/) instead, so a run reaches a place unattended.  The right
 * stick turns the camera: the game (Final Mix included) turns it with L2 / R2 only (fieldcam.c func_00178e10, 2
 * degrees a step while held) and gives the right stick the d-pad's actions (the command menu's cursor;
 * docs/vita-port-plan.md 5.1ab).  config.txt's rcam=1 (the default, 2026-10-31): a free camera, the stick's
 * both axes handed to func_00178e10 through PlatCamStick (left / right turns, up / down pitches; rcaminv=1 flips
 * up / down) and kept from the game; rcam=-1 the same with left / right the other way.  rcam=2, the older way:
 * the x past half way sent as R2 (right) or L2 (left), held, never pulsed (each press also steps the lock-on
 * target), the y left as it was.  rcam=0 sends the stick as it is.  The mod menu (menu.c) adds
 * swapox=1 (circle and cross swapped) and reartouch=0 (the rear pad's quarters off), and keeps its own presses
 * from the game.  Not part of the PS2
 * build. */
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include "common.h"
#include "platform/pad.h"
#include "vita.h"

static unsigned int cur;
int kh1_vita_rcam = 1; /* config.txt's rcam= (main.c): 1 free, -1 free with x the other way, 2 left / right only, 0 off */
int kh1_vita_rcam_inv; /* config.txt's rcaminv=1: the free camera's up / down the other way (menu.c) */
static int free_x, free_y; /* the right stick past its dead zone this frame, -107 .. 107 (PlatCamStick) */

/* rcam=2: the right stick's x as L2 / R2: on past 64 from the centre, off again inside 48 */
static unsigned int rcam(u8 *stick) {
    static int held; /* -1 left, 1 right */
    int dx = (int)stick[0] - 128;
    if (kh1_vita_rcam != 2) return 0;
    if (dx > 64) held = 1;
    else if (dx < -64) held = -1;
    else if (dx > -48 && dx < 48) held = 0;
    stick[0] = 128;
    return held > 0 ? PAD_R2 : held < 0 ? PAD_L2 : 0;
}

/* rcam=1 / -1: the free camera.  The stick is kept from the game (so it no longer moves the command menu's
 * cursor) and handed to fieldcam.c through PlatCamStick, both axes, past a dead zone of 20 */
static int dead(int v) {
    v -= 128;
    return v > 20 ? v - 20 : v < -20 ? v + 20 : 0;
}
static void free_cam(u8 *stick) {
    free_x = free_y = 0;
    if (kh1_vita_rcam != 1 && kh1_vita_rcam != -1) return;
    free_x = dead(stick[0]) * kh1_vita_rcam;
    free_y = dead(stick[1]) * (kh1_vita_rcam_inv ? -1 : 1);
    stick[0] = stick[1] = 128;
}

/* full tilt: 2 degrees a time step across (the game's own L2 / R2 speed), 1.5 up and down */
int PlatCamStick(f32 *yaw, f32 *pitch) {
    *yaw = (f32)free_x / 107.0f * 0.034906585f;
    *pitch = (f32)free_y / 107.0f * 0.026179939f;
    return free_x || free_y;
}

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
    if (kh1_vita_rear_touch && sceTouchPeek(SCE_TOUCH_PORT_BACK, &t, 1) > 0) /* reartouch=0: off (menu.c) */
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
    unsigned int b;
    if (kh1_vita_pad_script) {
        free_x = free_y = 0;
        return kh1_script_PadRead(socket, data);
    }
    sample(stick);
    b = cur | rcam(stick);
    free_cam(stick);
    if (kh1_vita_swap_ox && (b & (PAD_CIRCLE | PAD_CROSS)) && (b & (PAD_CIRCLE | PAD_CROSS)) != (PAD_CIRCLE | PAD_CROSS))
        b ^= PAD_CIRCLE | PAD_CROSS; /* swapox=1 (menu.c): cross confirms */
    if (kh1_vita_menu_swallow(b)) { /* the mod menu's own presses, until let go */
        b = 0;
        stick[0] = stick[1] = stick[2] = stick[3] = 128;
        free_x = free_y = 0;
    }
    data[0] = ~b & 0xFF;
    data[1] = (~b >> 8) & 0xFF;
    data[2] = stick[0];
    data[3] = stick[1];
    data[4] = stick[2];
    data[5] = stick[3];
    return 6;
}
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data) { return 0; }
