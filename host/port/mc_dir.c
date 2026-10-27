/* platform/mc.h on the port: a memory card is a directory (docs/vita-port-plan.md "Memory card").
 * kh1_mc_root[port] names it (the host's KH1_HOST_MC, the Vita's ux0:data/kh1/mc0); a port without
 * one, or whose directory does not exist, has no card, as the null platform answered before (every
 * request done at the next PlatMcSync with libmc's "no card detected", -10).  In the directory a save
 * is what the PS2 card holds: BISLPS-25198-NN/ with BISLPS-25198-NN (the 0x16c00-byte image),
 * system.bin, icon.sys and the icons, the bytes the PS2 game wrote (tools/host/ps2mc.py copies them
 * out of an emulator's card image).  The game reads and writes them through src/memcard/'s steps
 * unchanged.
 *
 * Every call does its work at once and keeps the libmc result PlatMcSync then answers (src/memcard
 * polls it with mode 1, mcqueue.c's start with mode 0).  The results are libmc's: >= 0 done (an fd,
 * a count, the entries read), -1 a new formatted card (the first GetInfo of a port), -4 no such
 * entry, -5 denied, -6 not empty, -7 no fd free.  GetDir's table is sceMcTblGetDir's 64 bytes:
 * created and modified times (resv, sec, min, hour, day, month, u16 year, JST as the card keeps
 * them), the size, the attributes and the name at 0x20; the load screen picks the newest save by
 * the modified time.  Names are the game's: absolute ("/BISLPS-25198-01/system.bin") or relative to
 * the directory the last Chdir set; "?" and "*" in the last part of a GetDir pattern.  Not part of
 * the PS2 build. */
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "platform/mc.h"

const char *kh1_mc_root[2];

#define MC_NO_CARD (-10)
#define MC_FREE_CLUSTERS 7000 /* of 8,000 on an 8 MB card: room for a save (132) and more */
#define MC_FDS 8

static int mc_result = MC_NO_CARD;
static int mc_seen[2];
static char mc_cwd[2][256] = {"/", "/"};
static struct {
    FILE *f;
} mc_fd[MC_FDS];

static int mc_card(int port) {
    struct stat st;
    return port >= 0 && port < 2 && kh1_mc_root[port] && stat(kh1_mc_root[port], &st) == 0 && S_ISDIR(st.st_mode);
}

static int done(int r) {
    mc_result = r;
    return 0;
}

/* the card path NAME means (absolute, or under the port's current directory), "." and ".." folded */
static void mc_norm(int port, const char *name, char *out, int n) {
    char tmp[512], *parts[32], *s, *save;
    int np = 0, i, len;
    if (name[0] == '/') snprintf(tmp, sizeof tmp, "%s", name);
    else snprintf(tmp, sizeof tmp, "%s/%s", mc_cwd[port], name);
    for (s = strtok_r(tmp, "/", &save); s; s = strtok_r(0, "/", &save)) {
        if (strcmp(s, ".") == 0) continue;
        if (strcmp(s, "..") == 0) {
            if (np) np--;
            continue;
        }
        if (np < 32) parts[np++] = s;
    }
    len = snprintf(out, n, "/");
    for (i = 0; i < np && len < n; i++) len += snprintf(out + len, n - len, i ? "/%s" : "%s", parts[i]);
}

static void mc_host(int port, const char *card, char *out, int n) {
    snprintf(out, n, "%s%s", kh1_mc_root[port], strcmp(card, "/") == 0 ? "" : card);
}

static void mc_path(int port, const char *name, char *out, int n) {
    char card[512];
    mc_norm(port, name, card, sizeof card);
    mc_host(port, card, out, n);
}

int PlatMcInit(void) { return 0; }
int PlatMcGetSlotMax(int port) { return 1; }

int PlatMcGetInfo(int port, int slot, int *type, int *free, int *format) {
    if (!mc_card(port)) {
        if (type) *type = 0;
        if (free) *free = 0;
        if (format) *format = 0;
        return done(MC_NO_CARD);
    }
    if (type) *type = 2; /* a PS2 card */
    if (free) *free = MC_FREE_CLUSTERS;
    if (format) *format = 1;
    if (!mc_seen[port]) {
        mc_seen[port] = 1;
        strcpy(mc_cwd[port], "/");
        return done(-1);
    }
    return done(0);
}

int PlatMcOpen(int port, int slot, const char *name, int mode) {
    char p[600];
    struct stat st;
    FILE *f;
    int fd;
    if (!mc_card(port)) return done(MC_NO_CARD);
    if (mode & 0x40) return PlatMcMkdir(port, slot, name);
    for (fd = 0; fd < MC_FDS && mc_fd[fd].f; fd++);
    if (fd == MC_FDS) return done(-7);
    mc_path(port, name, p, sizeof p);
    if (stat(p, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return done(-5);
        f = fopen(p, (mode & 3) == 1 ? "rb" : "r+b");
    } else if (mode & 0x200) {
        f = fopen(p, "w+b");
    } else {
        return done(-4);
    }
    if (!f) return done(-4);
    mc_fd[fd].f = f;
    return done(fd);
}

int PlatMcClose(int fd) {
    if (fd < 0 || fd >= MC_FDS || !mc_fd[fd].f) return done(-4);
    fclose(mc_fd[fd].f);
    mc_fd[fd].f = 0;
    return done(0);
}

int PlatMcRead(int fd, void *buf, int size) {
    if (fd < 0 || fd >= MC_FDS || !mc_fd[fd].f) return done(-4);
    return done((int)fread(buf, 1, size, mc_fd[fd].f));
}

int PlatMcWrite(int fd, const void *buf, int size) {
    int n;
    if (fd < 0 || fd >= MC_FDS || !mc_fd[fd].f) return done(-4);
    n = (int)fwrite(buf, 1, size, mc_fd[fd].f);
    fflush(mc_fd[fd].f);
    return done(n == size ? n : -3);
}

int PlatMcMkdir(int port, int slot, const char *name) {
    char p[600];
    struct stat st;
    if (!mc_card(port)) return done(MC_NO_CARD);
    mc_path(port, name, p, sizeof p);
    if (stat(p, &st) == 0) return done(-4); /* sceMcResNoEntry: it exists */
    return done(mkdir(p, 0777) == 0 ? 0 : -4);
}

int PlatMcChdir(int port, int slot, const char *name, char *cur) {
    char card[512], p[600];
    struct stat st;
    if (!mc_card(port)) return done(MC_NO_CARD);
    if (cur) strcpy(cur, mc_cwd[port]);
    mc_norm(port, name, card, sizeof card);
    mc_host(port, card, p, sizeof p);
    if (stat(p, &st) != 0 || !S_ISDIR(st.st_mode)) return done(-4);
    snprintf(mc_cwd[port], sizeof mc_cwd[port], "%s", card);
    return done(0);
}

static int mc_match(const char *pat, const char *s) {
    for (; *pat; pat++, s++) {
        if (*pat == '*') {
            for (;; s++) {
                if (mc_match(pat + 1, s)) return 1;
                if (!*s) return 0;
            }
        }
        if (!*s || (*pat != '?' && *pat != *s)) return 0;
    }
    return !*s;
}

/* sceMcStDateTime from a host time: the card keeps JST */
static void mc_time(unsigned char *t, time_t when) {
    time_t j = when + 9 * 3600;
    struct tm *tm = gmtime(&j);
    memset(t, 0, 8);
    if (!tm) return;
    t[1] = tm->tm_sec;
    t[2] = tm->tm_min;
    t[3] = tm->tm_hour;
    t[4] = tm->tm_mday;
    t[5] = tm->tm_mon + 1;
    t[6] = (tm->tm_year + 1900) & 0xFF;
    t[7] = (tm->tm_year + 1900) >> 8;
}

static void mc_entry(unsigned char *e, const char *name, const struct stat *st) {
    unsigned int size = S_ISDIR(st->st_mode) ? 0 : (unsigned int)st->st_size;
    unsigned short attr = S_ISDIR(st->st_mode) ? 0x8427 : 0x8497;
    memset(e, 0, 64);
    mc_time(e, st->st_mtime);
    mc_time(e + 8, st->st_mtime);
    memcpy(e + 0x10, &size, 4);
    memcpy(e + 0x14, &attr, 2);
    strncpy((char *)e + 0x20, name, 31);
}

int PlatMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table) {
    char card[512], dirp[600], fp[700], *pat;
    unsigned char *out = table;
    struct dirent *de;
    struct stat st;
    DIR *d;
    int n = 0;
    if (!mc_card(port)) return done(MC_NO_CARD);
    if (mode) return done(0); /* the game asks once (mode 0) for up to maxent */
    mc_norm(port, name, card, sizeof card);
    pat = strrchr(card, '/');
    *pat++ = 0;
    mc_host(port, card[0] ? card : "/", dirp, sizeof dirp);
    d = opendir(dirp);
    if (!d) return done(-4);
    /* a directory lists "." and ".." first, as the card's own entries */
    if (card[0] && stat(dirp, &st) == 0) {
        if (n < maxent && mc_match(pat, ".")) mc_entry(out + 64 * n++, ".", &st);
        if (n < maxent && mc_match(pat, "..")) mc_entry(out + 64 * n++, "..", &st);
    }
    while (n < maxent && (de = readdir(d)) != 0) {
        if (de->d_name[0] == '.' || strlen(de->d_name) > 31 || !mc_match(pat, de->d_name)) continue;
        snprintf(fp, sizeof fp, "%s/%s", dirp, de->d_name);
        if (stat(fp, &st) != 0) continue;
        mc_entry(out + 64 * n++, de->d_name, &st);
    }
    closedir(d);
    return done(n);
}

int PlatMcDelete(int port, int slot, const char *name) {
    char p[600];
    struct stat st;
    if (!mc_card(port)) return done(MC_NO_CARD);
    mc_path(port, name, p, sizeof p);
    if (stat(p, &st) != 0) return done(-4);
    if (S_ISDIR(st.st_mode)) return done(rmdir(p) == 0 ? 0 : -6);
    return done(remove(p) == 0 ? 0 : -5);
}

/* a host directory is never formatted or unformatted from the game */
int PlatMcFormat(int port, int slot) { return done(mc_card(port) ? 0 : MC_NO_CARD); }
int PlatMcUnformat(int port, int slot) { return done(mc_card(port) ? -5 : MC_NO_CARD); }

/* sceMcSetFileInfo with only the name valid: NEWNAME is a name in NAME's directory */
int PlatMcRename(int port, int slot, const char *name, const char *newname) {
    char p[600], q[700], *slash;
    if (!mc_card(port)) return done(MC_NO_CARD);
    mc_path(port, name, p, sizeof p);
    snprintf(q, sizeof q, "%s", p);
    slash = strrchr(q, '/');
    snprintf(slash + 1, sizeof q - (slash + 1 - q), "%s", newname);
    return done(rename(p, q) == 0 ? 0 : -4);
}

int PlatMcSync(int mode, int *cmd, int *result) {
    if (cmd) *cmd = 0;
    if (result) *result = mc_result;
    return 1;
}
