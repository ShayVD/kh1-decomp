/* The null pad (session 87, vita-port-plan 5.1aa): platform/pad.h for the host runner, with a
 * scripted controller so a run can press START at the title, open the menu or pull the pad out.
 * src/pad/padread.nostrict.c func_0011f668 is the only reader: once a frame it asks socket 0's
 * state, and when it is 1 (stable) reads the button profile (the first time) and the button
 * buffer: bytes 0-1 the digital buttons, active low, in the order of the game's decoded bits
 * (platform/pad.h PAD_*); bytes 2-5 the sticks, right x / y then left x / y, 0-255 with 128 the
 * centre (func_0011f370 reads them when the profile's byte 2 has its low four bits set).  When the
 * pad is not stable for 31 frames, func_0011f668 raises D_002C5968.b0 and the system-message band
 * shows "no controller" (renderer-spec 4.15, func_0010f918).
 *
 *   KH1_HOST_PAD unset   one pad, connected, nothing pressed, the sticks centred
 *   KH1_HOST_PAD=none    no pad: the state never answers 1 (sessions 63 to 86)
 *   KH1_HOST_PAD=FILE    a script, one line per change, held until the next line:
 *                            FRAME BUTTONS [RX RY LX LY]
 *                        FRAME a frame number (main.c's count, the vblanks so far: the boot's
 *                        first read is at frame 1), lines in frame order; BUTTONS "-" (none),
 *                        "out" (pulled out: the state answers 0), a number (the game's bits,
 *                        0x0008 START) or names joined by "+": SELECT L3 R3 START UP RIGHT DOWN
 *                        LEFT L2 R2 L1 R1 TRIANGLE CIRCLE CROSS SQUARE (circle confirms, cross
 *                        cancels: the Japanese layout); the sticks 0-255, 128 when left out.
 *                        "#" starts a comment.  E.g. press START at frame 300 for two frames:
 *                            300 START
 *                            302 -
 *                        Session 136: FRAME BUTTONS goto X Z [R] steers the left stick to the
 *                        field point (X, Z) instead (the player D_002E26A0[0]'s position, +0x10), and
 *                        centres it within R (16) of it, turning the stick by the camera as the
 *                        game does (steer below).  Nothing 3D is drawn on the null platform,
 *                        so this is how a run walks to a place read from the actors with gdb.
 *                        Session 139: FRAME BUTTONS goto vm K [R] steers to script VM K's entity
 *                        (D_0038D170[K].obj, +0x10) where it is each frame: a place the script
 *                        chooses at run time (the second station's box goes to one of two sides
 *                        by the collision group Sora stands on when the crate breaks).
 *
 * KH1_HOST_TRACE >= 1 prints "kh1-host: pad FRAME BUTTONS" when what the game reads changes.  Not
 * part of the PS2 build. */
#include "common.h"
#include "platform/pad.h"
#include "data/types/vm_rec.h"

#ifdef KH1_VITA
/* session 137v: the Vita build links this file too, as config.txt's pad=FILE (host/vita/pad.c calls these
 * when a script is given; the Vita's frame count is main.c's, as the host's) */
#define PlatDbcInit kh1_script_DbcInit
#define PlatPadInit kh1_script_PadInit
#define PlatPadCreateSocket kh1_script_PadCreateSocket
#define PlatPadGetState kh1_script_PadGetState
#define PlatPadGetButtonProfile kh1_script_PadGetButtonProfile
#define PlatPadRead kh1_script_PadRead
#define PlatVibSetActParam kh1_script_VibSetActParam
const char *kh1_vita_pad_script;
#define fprintf(f, ...) printf(__VA_ARGS__) /* newlib's stderr is a macro; the log is stdout */
#endif

typedef struct _IO_FILE FILE;
FILE *fopen(const char *, const char *);
char *fgets(char *, int, FILE *);
int fclose(FILE *);
int printf(const char *, ...);
int fprintf(FILE *, const char *, ...);
extern FILE *stderr;
char *getenv(const char *);
int strcmp(const char *, const char *);
unsigned long strtoul(const char *, char **, int);
void *realloc(void *, unsigned long);
void exit(int);
extern int kh1_host_trace;
unsigned long kh1_host_frame(void);
double strtod(const char *, char **);
float atan2f(float, float);
float sinf(float);
float cosf(float);
float sqrtf(float);
extern u8 *D_002E26A0[]; /* the player's actor (the actor table D_002C64A0's entry it has) */
extern float D_004F77E0; /* the camera's angle round y */
extern VmRec D_0038D170[]; /* the field's script VMs (src/vm/script_vm.c) */
extern s32 D_0039A570;     /* how many */
void func_00124d58(void *, void *, float, float);

typedef struct {
    unsigned long frame;
    int out;          /* pulled out */
    u32 buttons;      /* the game's decoded bits (active high) */
    u8 stick[4];      /* rx, ry, lx, ly */
    int go;           /* session 136: steer to (gx, gz) */
    float gx, gz, gr;
    int vm;           /* session 139: steer to this VM's entity instead (-1: to gx, gz) */
} NullPadLine;

static NullPadLine *null_pad_lines;
static int null_pad_n = -1;   /* -1: not read yet */
static int null_pad_none;
static int null_pad_last_out = -1;
static u32 null_pad_last_buttons;

static const struct { const char *name; u32 bit; } null_pad_names[] = {
    { "SELECT", PAD_SELECT }, { "L3", PAD_L3 }, { "R3", PAD_R3 }, { "START", PAD_START },
    { "UP", PAD_UP }, { "RIGHT", PAD_RIGHT }, { "DOWN", PAD_DOWN }, { "LEFT", PAD_LEFT },
    { "L2", PAD_L2 }, { "R2", PAD_R2 }, { "L1", PAD_L1 }, { "R1", PAD_R1 },
    { "TRIANGLE", PAD_TRIANGLE }, { "CIRCLE", PAD_CIRCLE }, { "CROSS", PAD_CROSS }, { "SQUARE", PAD_SQUARE },
};

static int space(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

/* one word of s at *i into w (at most n - 1 chars); 0 when the line has no more */
static int word(const char *s, int *i, char *w, int n) {
    int k = 0;
    while (space(s[*i])) (*i)++;
    if (s[*i] == 0 || s[*i] == '#') return 0;
    while (s[*i] && !space(s[*i]) && s[*i] != '#') {
        if (k < n - 1) w[k++] = s[*i];
        (*i)++;
    }
    w[k] = 0;
    return 1;
}

static int bad(const char *path, int ln, const char *what, const char *w) {
    fprintf(stderr, "kh1-host: %s:%d: %s: %s\n", path, ln, what, w);
    return 0;
}

/* BUTTONS into *b (or *out); 0 when it is not one */
static int buttons(const char *w, u32 *b, int *out) {
    char part[16];
    unsigned i;
    int k;
    *b = 0;
    *out = 0;
    if (strcmp(w, "-") == 0) return 1;
    if (strcmp(w, "out") == 0) {
        *out = 1;
        return 1;
    }
    if (w[0] >= '0' && w[0] <= '9') {
        char *end;
        *b = strtoul(w, &end, 0);
        return *end == 0 && *b <= 0xFFFF;
    }
    while (*w) {
        for (k = 0; *w && *w != '+'; w++)
            if (k < 15) part[k++] = *w;
        part[k] = 0;
        if (*w == '+') w++;
        for (i = 0; i < sizeof null_pad_names / sizeof null_pad_names[0]; i++)
            if (strcmp(part, null_pad_names[i].name) == 0) break;
        if (i == sizeof null_pad_names / sizeof null_pad_names[0]) return 0;
        *b |= null_pad_names[i].bit;
    }
    return 1;
}

/* Reads a script; the number of lines, or -1 (printed) when it cannot be read. */
int kh1_null_pad_load(const char *path) {
    FILE *f = fopen(path, "r");
    char s[256], w[64];
    int ln = 0, n = 0, i, k;
    if (!f) {
        fprintf(stderr, "kh1-host: KH1_HOST_PAD=%s: cannot open it\n", path);
        return -1;
    }
    while (fgets(s, sizeof s, f)) {
        NullPadLine L;
        char *end;
        ln++;
        i = 0;
        if (!word(s, &i, w, sizeof w)) continue;
        L.frame = strtoul(w, &end, 0);
        if (*end) return fclose(f), bad(path, ln, "not a frame number", w) - 1;
        if (n && L.frame < null_pad_lines[n - 1].frame)
            return fclose(f), bad(path, ln, "lines out of frame order", w) - 1;
        if (!word(s, &i, w, sizeof w)) return fclose(f), bad(path, ln, "no buttons", s) - 1;
        if (!buttons(w, &L.buttons, &L.out)) return fclose(f), bad(path, ln, "not a button", w) - 1;
        L.go = 0;
        L.vm = -1;
        {
            int j = i;
            if (word(s, &j, w, sizeof w) && strcmp(w, "goto") == 0) {
                char *e2;
                L.go = 1;
                L.gr = 16.0f;
                L.gx = L.gz = 0.0f;
                for (k = 0; k < 4; k++) L.stick[k] = 128;
                if (!word(s, &j, w, sizeof w)) return fclose(f), bad(path, ln, "goto X Z [R]", s) - 1;
                if (strcmp(w, "vm") == 0) {
                    if (!word(s, &j, w, sizeof w)) return fclose(f), bad(path, ln, "goto vm K [R]", s) - 1;
                    L.vm = (int)strtoul(w, &e2, 0);
                    if (*e2 || L.vm >= 32) return fclose(f), bad(path, ln, "goto vm K [R]: K 0-31", w) - 1;
                } else {
                    L.gx = (float)strtod(w, &e2);
                    if (!word(s, &j, w, sizeof w)) return fclose(f), bad(path, ln, "goto X Z [R]", s) - 1;
                    L.gz = (float)strtod(w, &e2);
                }
                if (word(s, &j, w, sizeof w)) L.gr = (float)strtod(w, &e2);
                null_pad_lines = realloc(null_pad_lines, (n + 1) * sizeof *null_pad_lines);
                null_pad_lines[n++] = L;
                continue;
            }
        }
        for (k = 0; k < 4; k++) {
            L.stick[k] = 128;
            if (word(s, &i, w, sizeof w)) {
                unsigned long v = strtoul(w, &end, 0);
                if (*end || v > 255) return fclose(f), bad(path, ln, "not a stick value (0-255)", w) - 1;
                L.stick[k] = v;
            } else if (k) {
                return fclose(f), bad(path, ln, "give all four sticks or none", s) - 1;
            } else {
                for (k = 1; k < 4; k++) L.stick[k] = 128;
                break;
            }
        }
        if (word(s, &i, w, sizeof w)) return fclose(f), bad(path, ln, "more than four sticks", w) - 1;
        null_pad_lines = realloc(null_pad_lines, (n + 1) * sizeof *null_pad_lines);
        null_pad_lines[n++] = L;
    }
    fclose(f);
    null_pad_n = n;
    return n;
}

/* the line that holds at this frame (0: before the first, or no script: connected, nothing) */
static const NullPadLine *now(void) {
    static const NullPadLine idle = { 0, 0, 0, { 128, 128, 128, 128 }, 0, 0, 0, 0 };
    unsigned long fr = kh1_host_frame();
    int lo = 0, hi;
    if (null_pad_n < 0) {
#ifdef KH1_VITA
        const char *s = kh1_vita_pad_script;
#else
        const char *s = getenv("KH1_HOST_PAD");
#endif
        null_pad_n = 0;
        if (s && strcmp(s, "none") == 0)
            null_pad_none = 1;
        else if (s && *s && kh1_null_pad_load(s) < 0)
#ifdef KH1_VITA
            null_pad_n = 0; /* the Vita's own controls (the log says why) */
#else
            exit(2);
#endif
    }
    hi = null_pad_n;
    /* the last line with frame <= fr */
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (null_pad_lines[mid].frame <= fr) lo = mid + 1;
        else hi = mid;
    }
    return lo ? &null_pad_lines[lo - 1] : &idle;
}

static void trace(const NullPadLine *L) {
    unsigned i;
    if (kh1_host_trace < 1 || (L->out == null_pad_last_out && (L->out || L->buttons == null_pad_last_buttons)))
        return;
    null_pad_last_out = L->out;
    null_pad_last_buttons = L->buttons;
    printf("kh1-host: pad %lu ", kh1_host_frame());
    if (L->out) {
        printf("out\n");
        return;
    }
    if (!L->buttons) printf("-");
    for (i = 0; i < sizeof null_pad_names / sizeof null_pad_names[0]; i++)
        if (L->buttons & null_pad_names[i].bit)
            printf("%s%s", (L->buttons & (null_pad_names[i].bit - 1)) ? "+" : "", null_pad_names[i].name);
    printf("\n");
}

int PlatDbcInit(void) { return 0; }
int PlatPadInit(int mode) { return 0; }
int PlatPadCreateSocket(void *param, void *addr) { return 0; }
/* 1 (stable) while a pad is in, 0 with none or pulled out */
int PlatPadGetState(int socket) {
    const NullPadLine *L = now();
    if (null_pad_none) return 0;
    trace(L);
    return L->out ? 0 : 1;
}
/* a DualShock 2's: every digital button and both sticks (byte 2's low bits: func_0011f668 reads
 * the sticks when they are 0xF) */
int PlatPadGetButtonProfile(int socket, void *profile) {
    u8 *p = profile;
    if (null_pad_none || now()->out) return -1;
    p[0] = p[1] = p[2] = p[3] = 0xFF;
    return 4;
}
/* the left stick for a goto line (session 136): of 64 ways round, the one the game's own turn
 * (camera/view.c func_00124d58: the camera's angle D_004F77E0, as plact.c func_00124e08 applies it to
 * the stick of padread.c func_0011f370) sends closest to the point */
static void steer(const NullPadLine *L, u8 *data) {
    static const NullPadLine *last;
    static int moving;
    const float *pos = (const float *)(D_002E26A0[0] + 0x10);
    float gx = L->gx, gz = L->gz, dx, dz, best = -2.0f, d;
    float v[4] __attribute__((aligned(16))), out[4] __attribute__((aligned(16)));
    int k, bk = 0;
    if (L->vm >= 0) {
        const u8 *e = L->vm < D_0039A570 ? (const u8 *)D_0038D170[L->vm].obj : 0;
        if (!e) { /* no such VM or no entity (yet): stand still */
            data[4] = data[5] = 128;
            return;
        }
        gx = ((const float *)(e + 0x10))[0];
        gz = ((const float *)(e + 0x10))[2];
    }
    dx = gx - pos[0];
    dz = gz - pos[2];
    d = sqrtf(dx * dx + dz * dz);
    if (L != last) {
        last = L;
        moving = 0;
        if (kh1_host_trace >= 1)
            printf("kh1-host: pad %lu goto %.1f %.1f from %.1f %.1f %.1f\n", kh1_host_frame(), gx, gz,
                   pos[0], pos[1], pos[2]);
    }
    if (d <= L->gr) {
        if (moving && kh1_host_trace >= 1)
            printf("kh1-host: pad %lu at %.1f %.1f %.1f\n", kh1_host_frame(), pos[0], pos[1], pos[2]);
        moving = 0;
        data[4] = data[5] = 128;
        return;
    }
    moving = 1;
    for (k = 0; k < 64; k++) {
        float c;
        v[0] = sinf(k * 0.0981747704f);
        v[1] = 0.0f;
        v[2] = -cosf(k * 0.0981747704f); /* the stick's y: up is negative */
        v[3] = 0.0f;
        func_00124d58(v, out, D_004F77E0, 0.0f);
        c = (out[0] * dx + out[2] * dz) / d;
        if (c > best) best = c, bk = k;
    }
    data[4] = (u8)(128.0f + 127.0f * sinf(bk * 0.0981747704f));
    data[5] = (u8)(128.0f - 127.0f * cosf(bk * 0.0981747704f));
}

int PlatPadRead(int socket, u8 *data) {
    const NullPadLine *L = now();
    if (null_pad_none || L->out) {
        data[0] = data[1] = 0xFF;
        return -1;
    }
    data[0] = ~L->buttons & 0xFF;
    data[1] = (~L->buttons >> 8) & 0xFF;
    data[2] = L->stick[0];
    data[3] = L->stick[1];
    data[4] = L->stick[2];
    data[5] = L->stick[3];
    if (L->go) steer(L, data);
    return 6;
}
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data) { return 0; }
