/* The model renderer's file loads (docs/modules.md "Session 49"),
 * 0x001aaa70-0x001aae48: func_001aaa70 reads a whole host file into a
 * buffer and func_001aab20 returns a file's size (both exit with "can't open
 * file %s"); func_001aadb0 / func_001aadd0 relocate an OEF2 model (the offset
 * table at +0x3c, after a 16-byte header for func_001aadd0) through
 * opfile.nostrict.c's func_001aab98; func_001aadf0 returns entry i of one of
 * a model's tables.  The file calls func_0025b588 / func_0025b990 /
 * func_0025bbc8 / func_0025b810 look like open / lseek / read / close.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/thread.h"

extern char D_0048FE18[];
s32 func_0025b588(char *, s32);
s32 func_0025b990(s32, s32, s32);
s32 func_0025bbc8(s32, void *, s32);
void func_0025b810(s32);
int printf(const char *, ...);
void exit(s32);

s32 func_001aaa70(char *name, void *buf) {
    char tmp[1024];
    s32 fd, size;
    fd = func_0025b588(name, 1);
    if (fd < 0) {
        printf(D_0048FE18, name);
        exit(1);
    }
    size = func_0025b990(fd, 0, 2);
    func_0025b990(fd, 0, 0);
    if (size != func_0025bbc8(fd, buf, size)) size = 0;
    func_0025b810(fd);
    PlatFlushCache(0);
    return size;
}

/* Returns a file's size (open, seek to end, close); exits if it is missing. */
s32 func_001aab20(char *name) {
    char buf[1024];
    s32 fd, size;
    fd = func_0025b588(name, 1);
    if (fd < 0) {
        printf(D_0048FE18, name);
        exit(1);
    }
    size = func_0025b990(fd, 0, 2);
    func_0025b810(fd);
    return size;
}

void func_001aab98(void *d, void *s);

void func_001aadb0(u8 *d) {
    func_001aab98(d, d + *(s32 *)(d + 0x3C));
}

void func_001aadd0(u8 *d) {
    d += 0x10;
    func_001aab98(d, d + *(s32 *)(d + 0x3C));
}

s32 func_001aadf0(s32 *h, s32 kind, s32 i) {
    s32 o;
    s32 sz = i << 5;
    switch (kind) {
    case 2: o = h[2]; break;
    case 3: o = h[3]; sz = i << 4; break;
    default: goto dflt;
    }
    return o + (s32)h + sz;
dflt:
    sz = i << 2; o = *(s32 *)((s32)h + (kind << 2)); o += (s32)h; return *(s32 *)(sz + o);
}

#include "data/data_0048.h"
