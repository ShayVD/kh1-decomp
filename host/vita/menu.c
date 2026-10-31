/* The Vita's mod menu (docs/vita-build.md "The mod menu"): a tap in the middle of the front touch screen pauses
 * the game and opens a list of the port's own options, most of them config.txt's keys, changed live where the
 * port can and written back to ux0:data/kh1/config.txt when the menu closes.  The game never reads the front
 * touch screen (the PS2 had none), so the tap takes nothing from it.
 *
 *   Widescreen          wide=: the 16:9 wide view (1), 4:3 stretched (2), 4:3 in black bars (0); live (the view,
 *                       the HUD's anchors and the present are only parameters: host/port/view.c, plat_null.c)
 *   Right stick camera  rcam=: on (1), inverted (-1), off (0, the PS2's right stick); live (pad.c)
 *   FPS counter         fps=: off (0), the pictures a second (1), and the game's frames a second (2); live
 *   Swap circle / cross swapox=1: the Japanese disc's circle-confirms swapped to cross-confirms; live (pad.c)
 *   Rear touch L2/R2/L3/R3 reartouch=0: the rear pad's quarters off (no presses from the hands holding it); live
 *   Volume              volume=0..100: the sound's output level (audio.c); live
 *   Frame catch-up      latewait=: on (0, frames after a late one run without waiting) or off (1); live
 *   Renderer            renderer=native or gs: needs a restart (its shaders and the recorder are set up at start)
 *   Status strip        strip=1; live
 *   Restart / Quit      sceAppMgrLoadExec of the app's own eboot / sceKernelExitProcess (unsaved progress is lost)
 *
 * While it is open the game thread waits here, inside its vblank (main.c), after the GS worker and the GPU
 * frame's thread have finished their queues, so the options can change the GS side's parameters and the menu
 * draws the last picture itself.  The sound's threads go on.  Its buttons are kept from the game until all are
 * released.  Touch: a tap on a row changes it (its left third steps back), a tap outside the panel closes it.
 * Not part of the PS2 build. */
#include <psp2/appmgr.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/sysmodule.h>
#include <psp2/touch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vita2d.h>
#include "common.h"
#include "platform/view.h"
#include "vita.h"

void kh1_null_hud_wide(s32 margin16); /* host/null/plat_null.c */
void kh1_vita_audio_volume(int percent); /* audio.c */
unsigned long kh1_host_frame(void);     /* main.c */

int kh1_vita_fps_osd;         /* config.txt's fps= */
int kh1_vita_swap_ox;         /* config.txt's swapox= (pad.c) */
int kh1_vita_rear_touch = 1;  /* config.txt's reartouch= (pad.c) */
volatile u32 kh1_vita_pictures; /* whole pictures made (main.c's GPU frame, display.c's software present) */

static int *p_wide, *p_late, *p_native, *p_strip; /* main.c's own (kh1_vita_menu_init) */
static int gpu, native_at_start;
static volatile int open_; /* the menu is up (display.c draws it) */
static int sel, dirty, swallow;
static vita2d_pgf *font;

enum { I_WIDE, I_RCAM, I_FPS, I_SWAP, I_REAR, I_VOL, I_PACE, I_REND, I_STRIP, I_RESTART, I_QUIT, I_CLOSE, I_N };
static const char *const names[I_N] = { "Widescreen", "Right stick camera", "FPS counter", "Swap circle / cross",
                                        "Rear touch as L2 / R2 / L3 / R3", "Volume", "Frame catch-up", "Renderer",
                                        "Status strip", "Restart game", "Quit game", "Close" };

/* config.txt's keys the menu writes (the menu's own and main.c's it changes); widescreen= is wide='s other name */
static const char *const keys[] = { "wide", "rcam", "fps", "swapox", "reartouch", "volume", "latewait", "renderer", "strip" };
#define NKEYS (int)(sizeof keys / sizeof keys[0])

void kh1_vita_menu_init(int *wide, int *late_wait, int *native, int *strip, int gpu_on) {
    p_wide = wide;
    p_late = late_wait;
    p_native = native;
    p_strip = strip;
    gpu = gpu_on;
    native_at_start = *native;
    if (kh1_vita_volume != 100) kh1_vita_audio_volume(kh1_vita_volume);
}

/* main.c's config(): the menu's own keys; 1 when the key was one */
int kh1_vita_menu_config(const char *k, const char *v) {
    if (strcmp(k, "fps") == 0) kh1_vita_fps_osd = atoi(v);
    else if (strcmp(k, "swapox") == 0) kh1_vita_swap_ox = atoi(v);
    else if (strcmp(k, "reartouch") == 0) kh1_vita_rear_touch = atoi(v);
    else if (strcmp(k, "volume") == 0) {
        kh1_vita_volume = atoi(v);
        if (kh1_vita_volume < 0) kh1_vita_volume = 0;
        if (kh1_vita_volume > 100) kh1_vita_volume = 100;
    } else return 0;
    return 1;
}

static void value_of(int k, char *b, int n) {
    switch (k) {
    case 0: snprintf(b, n, "%d", *p_wide); break;
    case 1: snprintf(b, n, "%d", kh1_vita_rcam); break;
    case 2: snprintf(b, n, "%d", kh1_vita_fps_osd); break;
    case 3: snprintf(b, n, "%d", kh1_vita_swap_ox); break;
    case 4: snprintf(b, n, "%d", kh1_vita_rear_touch); break;
    case 5: snprintf(b, n, "%d", kh1_vita_volume); break;
    case 6: snprintf(b, n, "%d", *p_late); break;
    case 7: snprintf(b, n, "%s", *p_native ? "native" : "gs"); break;
    default: snprintf(b, n, "%d", *p_strip); break;
    }
}

/* config.txt with the menu's keys set: each key's first line rewritten, its later lines dropped, the keys it did
 * not have added at the end; every other line kept as it was.  Written to a new file, then put in its place */
static void save(void) {
    char path[128], tmp[128], line[256], val[32];
    static char out[16384];
    int len = 0, done[NKEYS], i;
    FILE *f;
    SceUID fd;
    memset(done, 0, sizeof done);
    snprintf(path, sizeof path, "%s/config.txt", kh1_vita_dir);
    snprintf(tmp, sizeof tmp, "%s/config.tmp", kh1_vita_dir);
    if ((f = fopen(path, "r"))) {
        while (fgets(line, sizeof line, f) && len < (int)sizeof out - 512) {
            char key[64];
            const char *eq = strchr(line, '=');
            int k = -1;
            if (line[0] != '#' && eq && eq - line < (int)sizeof key) {
                memcpy(key, line, eq - line);
                key[eq - line] = 0;
                if (strcmp(key, "widescreen") == 0) strcpy(key, "wide");
                for (i = 0; i < NKEYS; i++)
                    if (strcmp(key, keys[i]) == 0) k = i;
            }
            if (k < 0) {
                len += snprintf(out + len, sizeof out - len, "%s%s", line, strchr(line, '\n') ? "" : "\n");
            } else if (!done[k]) {
                value_of(k, val, sizeof val);
                len += snprintf(out + len, sizeof out - len, "%s=%s\n", keys[k], val);
                done[k] = 1;
            }
        }
        fclose(f);
    }
    for (i = 0; i < NKEYS; i++)
        if (!done[i]) {
            value_of(i, val, sizeof val);
            len += snprintf(out + len, sizeof out - len, "%s=%s\n", keys[i], val);
        }
    fd = sceIoOpen(tmp, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0666);
    if (fd < 0) {
        kh1_vita_log("kh1-vita: menu: %s: cannot write (0x%08x)\n", tmp, fd);
        return;
    }
    i = sceIoWrite(fd, out, len);
    sceIoClose(fd);
    if (i != len) {
        kh1_vita_log("kh1-vita: menu: %s: short write\n", tmp);
        return;
    }
    sceIoRemove(path);
    if (sceIoRename(tmp, path) < 0) kh1_vita_log("kh1-vita: menu: could not put %s in place\n", path);
    else kh1_vita_log("kh1-vita: menu: options saved to %s\n", path);
    dirty = 0;
}

/* wide= live: the hor+ view (or the PS2's), the HUD's anchors, the full-screen stretch, the recorder's targets,
 * the present.  Only from the menu: the game thread waits and the GS side's queues are empty */
static void apply_wide(int w) {
    if (w == 1 && !gpu) w = 2;
    *p_wide = w;
    kh1_view_init(w == 1 ? 960.0f / 544.0f : 4.0f / 3.0f);
    kh1_null_hud_wide(kh1_view_side16);
    kh1_vita_display_mode(w, *p_strip);
    kh1_vita_log("kh1-vita: menu: wide=%d\n", w);
}

static void change(int i, int dir) {
    static const int wides[3] = { 1, 2, 0 }, rcams[3] = { 1, -1, 0 };
    int j;
    switch (i) {
    case I_WIDE:
        for (j = 0; j < 3 && wides[j] != *p_wide; j++) {}
        do j = (j + (dir < 0 ? 2 : 1)) % 3;
        while (wides[j] == 1 && !gpu);
        apply_wide(wides[j]);
        break;
    case I_RCAM:
        for (j = 0; j < 3 && rcams[j] != kh1_vita_rcam; j++) {}
        kh1_vita_rcam = rcams[(j + (dir < 0 ? 2 : 1)) % 3];
        break;
    case I_FPS: kh1_vita_fps_osd = (kh1_vita_fps_osd + (dir < 0 ? 2 : 1)) % 3; break;
    case I_SWAP: kh1_vita_swap_ox = !kh1_vita_swap_ox; break;
    case I_REAR: kh1_vita_rear_touch = !kh1_vita_rear_touch; break;
    case I_VOL:
        kh1_vita_volume += dir < 0 ? -10 : 10;
        if (kh1_vita_volume > 100) kh1_vita_volume = dir > 1 ? 0 : 100; /* a tap past the top wraps */
        if (kh1_vita_volume < 0) kh1_vita_volume = 0;
        kh1_vita_audio_volume(kh1_vita_volume);
        break;
    case I_PACE: *p_late = !*p_late; break;
    case I_REND: *p_native = !*p_native; break;
    case I_STRIP:
        *p_strip = !*p_strip;
        kh1_vita_display_mode(*p_wide, *p_strip);
        break;
    case I_RESTART:
        if (dirty) save();
        kh1_vita_log("kh1-vita: menu: restart\n");
        sceAppMgrLoadExec("app0:eboot.bin", NULL, NULL);
        return;
    case I_QUIT:
        if (dirty) save();
        kh1_vita_log("kh1-vita: menu: quit\n");
        sceKernelExitProcess(0);
        return;
    case I_CLOSE: open_ = 0; return;
    }
    dirty = 1;
}

static const char *shown_value(int i, char *b, int n) {
    switch (i) {
    case I_WIDE: return *p_wide == 1 ? "16:9 wide view" : *p_wide == 2 ? "4:3 stretched" : "4:3 black bars";
    case I_RCAM: return kh1_vita_rcam > 0 ? "On" : kh1_vita_rcam < 0 ? "Inverted" : "Off (PS2 layout)";
    case I_FPS: return kh1_vita_fps_osd == 2 ? "FPS + game speed" : kh1_vita_fps_osd ? "On" : "Off";
    case I_SWAP: return kh1_vita_swap_ox ? "Cross confirms" : "Circle confirms";
    case I_REAR: return kh1_vita_rear_touch ? "On" : "Off";
    case I_VOL: snprintf(b, n, "%d%%", kh1_vita_volume); return b;
    case I_PACE: return *p_late ? "Off" : "On";
    case I_REND:
        snprintf(b, n, "%s%s", *p_native ? "Native" : "GS path", *p_native != native_at_start ? " (after restart)" : "");
        return b;
    case I_STRIP: return *p_strip ? "On" : "Off";
    case I_RESTART: return *p_native != native_at_start ? "Applies the renderer" : "Unsaved progress is lost";
    case I_QUIT: return "Unsaved progress is lost";
    default: return "Start / Triangle";
    }
}

/* the panel's layout, screen pixels */
#define PX 150
#define PW 660
#define TOP 40
#define ROW 36
#define RY(i) (TOP + 56 + (i) * ROW)

/* one tap: a touch let go within 0.6 s, moved under 40 px (front touch's 1920 x 1088 halved) */
static int tap(int *tx, int *ty) {
    static int down, x0, y0, moved;
    static SceUInt64 t0;
    static int ready;
    SceTouchData t;
    if (!ready) {
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
        ready = 1;
    }
    if (sceTouchPeek(SCE_TOUCH_PORT_FRONT, &t, 1) <= 0) return 0;
    if (t.reportNum > 0) {
        int x = t.report[0].x / 2, y = t.report[0].y / 2;
        if (!down) {
            down = 1;
            x0 = x;
            y0 = y;
            moved = 0;
            t0 = sceKernelGetProcessTimeWide();
        } else if (abs(x - x0) > 40 || abs(y - y0) > 40)
            moved = 1;
        return 0;
    }
    if (!down) return 0;
    down = 0;
    if (moved || sceKernelGetProcessTimeWide() - t0 > 600000) return 0;
    *tx = x0;
    *ty = y0;
    return 1;
}

/* each vblank (main.c, the game thread): 1 when a tap in the middle of the screen asks for the menu */
int kh1_vita_menu_poll(void) {
    int x, y;
    return tap(&x, &y) && x >= 320 && x < 640 && y >= 136 && y < 408;
}

/* pad.c: 1 while the game should see no buttons (the menu's own, until every one is let go) */
int kh1_vita_menu_swallow(unsigned int held) {
    if (swallow && !held) swallow = 0;
    return swallow;
}

/* the menu, paused in the game's vblank (main.c has emptied the GS side's queues); redraw draws the last picture
 * with the menu over it (display.c) */
void kh1_vita_menu_run(void (*redraw)(void)) {
    SceCtrlData c;
    unsigned int old = ~0u, rep = 0;
    int held_for = 0, x, y;
    kh1_vita_log("kh1-vita: menu: open at frame %lu\n", kh1_host_frame());
    open_ = 1;
    while (open_) {
        unsigned int b, press;
        if (sceCtrlPeekBufferPositive(0, &c, 1) < 0) c.buttons = 0;
        b = c.buttons;
        press = b & ~old;
        /* the d-pad repeats after 0.4 s held, every 0.1 s */
        if ((b & (SCE_CTRL_UP | SCE_CTRL_DOWN | SCE_CTRL_LEFT | SCE_CTRL_RIGHT)) == rep && rep) {
            if (++held_for > 24 && held_for % 6 == 0) press |= rep;
        } else {
            rep = b & (SCE_CTRL_UP | SCE_CTRL_DOWN | SCE_CTRL_LEFT | SCE_CTRL_RIGHT);
            held_for = 0;
        }
        old = b;
        if (press & SCE_CTRL_UP) sel = (sel + I_N - 1) % I_N;
        if (press & SCE_CTRL_DOWN) sel = (sel + 1) % I_N;
        if (press & SCE_CTRL_LEFT && sel < I_RESTART) change(sel, -1);
        if (press & SCE_CTRL_RIGHT && sel < I_RESTART) change(sel, 1);
        if (press & (SCE_CTRL_CIRCLE | SCE_CTRL_CROSS)) change(sel, 1);
        if (press & (SCE_CTRL_START | SCE_CTRL_TRIANGLE)) open_ = 0;
        if (tap(&x, &y)) {
            int i = (y - RY(0) + 8) / ROW;
            if (x < PX || x >= PX + PW || y < TOP || y >= RY(I_N) + 8) open_ = 0;
            else if (y >= RY(0) - 8 && i >= 0 && i < I_N) {
                sel = i;
                change(i, x < PX + PW / 3 && i < I_RESTART ? -1 : 2);
            }
        }
        redraw();
        sceDisplayWaitVblankStart();
    }
    if (dirty) save();
    swallow = 1;
    kh1_vita_log("kh1-vita: menu: closed\n");
}

/* the FPS counter: whole pictures a second (what the eye sees) and the game's own frames a second, measured over
 * each half second */
static void fps_osd(void) {
    static SceUInt64 t0;
    static u32 pics0;
    static unsigned long frames0;
    static float fps, game;
    char b[64];
    SceUInt64 t = sceKernelGetProcessTimeWide();
    if (!t0 || t - t0 > 2000000) {
        t0 = t;
        pics0 = kh1_vita_pictures;
        frames0 = kh1_host_frame();
    } else if (t - t0 >= 500000) {
        fps = (float)(kh1_vita_pictures - pics0) * 1e6f / (float)(t - t0);
        game = (float)(kh1_host_frame() - frames0) * 1e6f / (float)(t - t0);
        t0 = t;
        pics0 = kh1_vita_pictures;
        frames0 = kh1_host_frame();
    }
    if (kh1_vita_fps_osd == 2) snprintf(b, sizeof b, "%.0f fps  game %.0f/60", fps, game);
    else snprintf(b, sizeof b, "%.0f fps", fps);
    {
        int w = vita2d_pgf_text_width(font, 0.9f, b);
        vita2d_draw_rectangle((float)(960 - w - 20), 6.0f, (float)(w + 14), 26.0f, RGBA8(0, 0, 0, 160));
        vita2d_pgf_draw_text(font, 960 - w - 13, 25, fps >= 25.0f ? RGBA8(120, 255, 120, 255) : fps >= 15.0f ? RGBA8(255, 230, 90, 255) : RGBA8(255, 110, 90, 255),
                             0.9f, b);
    }
}

/* display.c's draw, inside vita2d's open scene after the picture: the FPS counter, and the menu while it is up */
void kh1_vita_menu_draw(void) {
    char b[64];
    int i;
    if (!kh1_vita_fps_osd && !open_) return;
    if (!font) { /* the system font (ScePgf) */
        static int tried;
        if (tried) return;
        tried = 1;
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_PGF) != SCE_SYSMODULE_LOADED) sceSysmoduleLoadModule(SCE_SYSMODULE_PGF);
        if (!(font = vita2d_load_default_pgf())) {
            kh1_vita_log("kh1-vita: menu: no system font\n");
            return;
        }
    }
    if (kh1_vita_fps_osd) fps_osd();
    if (!open_) return;
    vita2d_draw_rectangle(0.0f, 0.0f, 960.0f, 544.0f, RGBA8(0, 0, 0, 110));
    vita2d_draw_rectangle((float)PX, (float)TOP, (float)PW, (float)(RY(I_N) - TOP + 8), RGBA8(16, 20, 40, 235));
    vita2d_draw_rectangle((float)PX, (float)TOP, (float)PW, 3.0f, RGBA8(250, 200, 60, 255));
    vita2d_pgf_draw_text(font, PX + 20, TOP + 34, RGBA8(250, 210, 90, 255), 1.1f, "kh1-decomp options");
    vita2d_pgf_draw_text(font, PX + PW - 190, TOP + 32, RGBA8(150, 150, 170, 255), 0.75f, "game paused");
    for (i = 0; i < I_N; i++) {
        const char *v = shown_value(i, b, sizeof b);
        unsigned int col = i >= I_RESTART ? RGBA8(200, 200, 215, 255) : RGBA8(235, 235, 245, 255);
        int w, y = RY(i);
        if (i == sel) vita2d_draw_rectangle((float)PX + 8, (float)(y - 8), (float)PW - 16, (float)ROW - 2, RGBA8(60, 80, 150, 255));
        vita2d_pgf_draw_text(font, PX + 24, y + 18, col, 1.0f, names[i]);
        w = vita2d_pgf_text_width(font, 0.9f, v);
        vita2d_pgf_draw_text(font, PX + PW - 24 - w, y + 18, i == sel ? RGBA8(255, 225, 120, 255) : RGBA8(160, 190, 255, 255), 0.9f, v);
    }
}

/* display.c: whether something is drawn over the picture (each draw must then be a whole one) */
int kh1_vita_menu_overlay(void) { return open_ || kh1_vita_fps_osd; }
