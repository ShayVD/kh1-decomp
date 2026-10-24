/* The HDD install and start-up (docs/modules.md "Session 47"),
 * 0x0024d4a0-0x0024e0a4 except hdd.nofill.c's func_0024d618 and
 * func_0024d7b0.  func_0024d4b0 loads dev9.irx, atad.irx, hdd.irx and
 * pfs.irx (D_0046A60C set once they load) and starts the HDD thread
 * (func_0024d808: 4 KB stack D_00669A80).  func_0024ddf8 checks for an
 * installed copy: it takes the game id from the boot path (func_0011fd30,
 * "SLPS_251.98" gives "25198", D_0046A678 set for this disc), mounts the
 * partition (func_0024d8f0, "hdd0:<name>,<pass>" on pfs0:) and compares
 * kingdom.img's size (func_0024dd98) with the installed file's
 * (func_0024d9f0); D_0046A67C the result (0 none, 1 can install, 2
 * installed, 3 needs reinstall), D_0046A680 the reason, D_0046A614 a
 * progress step.  func_0024db78 checks the free space for a size
 * (func_0024dad0, 0x480A), func_0024dcc8 looks for a name in a directory.
 * The getters func_0024d8a0 ... func_0024d8e0 return the partition and file
 * names.  Read from the strings and the code; the result codes' meanings
 * are a reading, not proved by a boot (and the HDD path needs the
 * Japanese HDD unit). */
#include "common.h"
#include "platform/cd.h"
#include "platform/thread.h"
#include "data/bss_0066.h"
#include "data/data_0046.h"
#include "data/data_0049.h"
#include "data/pieces/D_0046A608.h"
#include "data/pieces/D_0046A628.h"
#include "data/pieces/D_0046A650.h"
#include "data/pieces/D_004919B0.h"

/* The kernel's semaphore and thread parameters (SCE eekernel.h layout). */
typedef struct {
    s32 count, max_count, init_count, wait_threads;
    u32 attr, option;
} SemaParam;

typedef struct {
    s32 status;
    void *func;
    void *stack;
    s32 stack_size;
    void *gp_reg;
    s32 initial_priority;
    s32 current_priority;
    u32 attr, option;
} ThreadParam;

typedef struct { u8 stat[0x40]; char name[256]; u8 pad[0x10]; } Dirent;
/* The partition: its name and password getters and whether it is mounted. */
typedef struct { s32 x0; char *(*name)(void); char *(*pass)(void); s32 xc; s32 mounted; } HddCfg;
/* A kingdom.img entry (func_00120190). */
typedef struct { s32 x0, x4, lsn, size; } FileEnt;

extern HddCfg D_0046A688;
extern char D_004919A8[8]; /* "pfs0:" */
extern char D_00491978[]; /* "hdd", hdd.nofill.c's string */
extern u8 D_00494050[];

s32 abs(s32);
s32 memcmp(const void *, const void *, u32);
s32 sprintf(char *, const char *, ...);
s32 strcmp(const char *, const char *);
char *func_0011fd30(void);
FileEnt *func_00120190(char *);
s32 func_00120a20(const char *, s32, char *, s32 *);
s32 func_0025b588(const char *, s32);
s32 func_0025b810(s32);
s32 func_0025c448(s32, s32, s32, s32, s32, s32);
s32 func_0025cd70(const char *);
s32 func_0025ce38(s32);
s32 func_0025cfa0(s32, Dirent *);
s32 func_0025d880(const char *, const char *, s32, s32, s32);
s32 func_0025daf0(char *);
s64 func_0025db10(s32, s32, s32);
s32 func_0025dd48(const char *, s32, s32, s32, void *, s32);
s32 func_0025e990(const char *);
void func_0024d808(void);
/* hdd.nofill.c */
void func_0024d618(void *);
void func_0024d7b0(void);

u8 D_00669A80[0x1000] ALIGNED(64);

s32 func_0024d4a0(void) {
    return D_0046A60C;
}

s32 func_0024d4b0(void) {
    char hddarg[11] = "-o\0" "1\0" "-n\0" "20";
    char pfsarg[16] = "-m\0" "1\0" "-o\0" "1\0" "-n\0" "28";
    s32 res;
    D_0046A610 = 0;
    D_0046A60C = 0;
    func_00120a20("dev9.irx", 0, 0, &res);
    if (func_00120a20("atad.irx", 0, 0, &res) < 0) return 1;
    if (func_00120a20("hdd.irx", 10, hddarg, &res) < 0) return 1;
    if (func_00120a20("pfs.irx", 18, pfsarg, &res) < 0) return 1;
    D_0046A60C = 1;
    func_0024d808();
    return 0;
}

void func_0024d5d0(s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        s32 *p = &D_0046A618;
        (*p)++;
    }
}

s32 func_0024d608(void) {
    return D_0046A618;
}

/* Starts the thread at func_0024d618 (4 KB stack at D_00669A80, priority
 * 1) with a new semaphore, and registers func_0024d7b0 with it. */
void func_0024d808(void) {
    ThreadParam tp;
    SemaParam sp;
    s32 sema;

    sp.max_count = 1;
    sp.init_count = 0;
    sp.option = 0;
    sema = PlatCreateSema(&sp);
    tp.stack_size = 0x1000;
    tp.gp_reg = D_00494050;
    tp.func = func_0024d618;
    tp.stack = D_00669A80;
    tp.initial_priority = 1;
    PlatStartThread(PlatCreateThread(&tp), (void *) sema);
    PlatCdPOffCallback(func_0024d7b0, sema);
}

char *func_0024d8a0(void) {
    return (char *)&D_0046A620;
}

char *func_0024d8b0(void) {
    return D_0046A628;
}

char *func_0024d8c0(void) {
    return (char *)&D_0046A640;
}

char *func_0024d8d0(void) {
    return D_0046A650;
}

char *func_0024d8e0(void) {
    return (char *)&D_0046A660;
}

s32 func_0024d8f0(void) {
    HddCfg *c = &D_0046A688;
    if (c->mounted == 0) {
        char buf[128];
        char *n = c->name();
        s32 r;
        sprintf(buf, "hdd0:%s,%s", n, c->pass());
        r = func_0025d880("pfs0:", buf, 0, 0, 0);
        if (r < 0) return (r == -5) ? -1 : 1;
        c->mounted = 1;
    }
    return 0;
}

s32 func_0024d9a0(void) {
    s32 r;

    if (D_0046A688.mounted != 0) {
        r = func_0025daf0(D_004919A8);
        if (r == 0) {
            D_0046A688.mounted = 0;
            return r;
        }
    }
    return 1;
}

s32 func_0024d9f0(void) {
    s32 *st = &D_0046A614;
    s32 fd, r;
    s64 sz;
    *st = 90;
    fd = func_0025b588(func_0024d8e0(), 1);
    *st = 100;
    if (fd < 0) {
        r = 1;
    } else {
        sz = func_0025db10(fd, 0, 2);
        *st = 110;
        func_0025b810(fd);
        *st = 120;
        r = 1;
        if (D_0046A608 == sz) r = 0;
    }
    return r;
}

s32 func_0024daa0(void) {
    return func_0025dd48(D_004919B0, 0x4807, 0, 0, 0, 0);
}

s32 func_0024dad0(const char *a0, s32 n) {
    u32 v;
    func_0025dd48(a0, 0x4802, 0, 0, 0, 0);
    D_0046A614 = 60;
    v = 0;
    if (func_0025dd48(a0, 0x480A, 0, 0, &v, 4) != 0) return 0;
    D_0046A614 = 70;
    if ((s32)(v >> 18) < n) return 0;
    return 1;
}

s32 func_0024db68(void) {
    return D_0046A674;
}

s32 func_0024db78(s32 size) {
    HddCfg *c = &D_0046A688;
    s32 used = 0;
    s32 fd;
    s32 flag;
    s32 n;
    char buf[64];
    flag = c->mounted;
    D_0046A674 = 0;
    if (flag) func_0024d9a0();
    D_0046A614 = 40;
    sprintf(buf, "hdd0:%s,,%s", c->name(), D_0046A650);
    fd = func_0025b588(buf, 1);
    if (fd >= 0) {
        used = func_0025c448(fd, 0x6803, 0, 0, 0, 0);
        if (used < 0) used = 0;
        used++;
        func_0025ce38(fd);
    }
    D_0046A614 = 50;
    n = ((((u32)(size + 0xFFFFF) >> 20) + 127) >> 7) + 1;
    if (func_0024dad0(D_004919B0, n - used) == 0) D_0046A674 = -1;
    if (flag) func_0024d8f0();
    D_0046A614 = 80;
    return D_0046A674;
}

s32 func_0024dcc8(const char *path, const char *name) {
    Dirent d;
    s32 fd, n, found = 0;
    fd = func_0025cd70(path);
    if (fd < 0) return 0;
    n = 0;
    while (func_0025cfa0(fd, &d) > 0) n++;
    func_0025ce38(fd);
    if (n == 0) return 0;
    fd = func_0025cd70(path);
    if (fd < 0) return 0;
    while (func_0025cfa0(fd, &d) > 0) {
        if (strcmp(d.name, name) == 0) found = 1;
    }
    func_0025ce38(fd);
    return found;
}

s32 func_0024dd98(s32 *lsn) {
    s32 size;
    FileEnt *e;

    size = 0;
    if (lsn != NULL) {
        *lsn = 0;
    }
    e = func_00120190((char *)&D_004919C8);
    if (e != NULL) {
        size = e->size;
        if (lsn != NULL) {
            *lsn = e->lsn;
        }
    }
    return size;
}

s32 func_0024ddf8(void) {
    s32 i, r, ok;
    char *s, *p, *dst;
    D_0046A614 = 0;
    D_0046A680 = 0;
    D_0046A67C = 0;
    if (!func_0024d4a0()) return D_0046A67C;
    D_0046A614 = 10;
    s = func_0011fd30();
    dst = D_0046A688.name() + 8;
    for (i = 0; memcmp("SLPS", p = s + i, 4) != 0; i++);
    s = p + 5;
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
    dst[3] = s[4];
    dst[4] = s[5];
    if (memcmp(dst, "25198", 5) == 0) D_0046A678 = 1;
    func_0024d9a0();
    if (func_0025e990(D_00491978) < 0) goto fail;
    if (func_0024dcc8(D_004919B0, D_0046A628)) {
        ok = 1;
        D_0046A6AC = 1;
    } else {
        ok = 0;
        D_0046A6AC = 0;
    }
    (*(s32 *)&D_0046A608) = func_0024dd98(0);
    D_0046A614 = 20;
    r = func_0024daa0();
    D_0046A614 = 30;
    switch (abs(r) & 15) {
    case 0:
        func_0024db78(D_0046A608);
        if (func_0024d8f0()) {
            D_0046A67C = 1;
            if (ok) {
                D_0046A67C = 3;
                D_0046A680 = 2;
            }
        } else if (func_0024d9f0()) {
            D_0046A67C = 3;
            func_0024d9a0();
            D_0046A680 = 2;
        } else {
            D_0046A67C = 2;
        }
        break;
    case 1:
        D_0046A680 = 1;
        D_0046A67C = 1;
        break;
    case 2:
        D_0046A67C = 1;
        D_0046A680 = 4;
        break;
    default:
    fail:
        D_0046A67C = 0;
        D_0046A680 = 3;
        break;
    }
    D_0046A614 = 130;
    return D_0046A67C;
}

s32 func_0024e078(void) {
    return D_0046A67C;
}

void func_0024e088(s32 arg0) {
    D_0046A67C = arg0;
}

s32 func_0024e098(void) {
    return D_0046A680;
}
