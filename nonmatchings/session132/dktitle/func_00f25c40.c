/* dktitle.x func_00f25c40: near-miss draft (session 132), not byte-identical; the port runs it (ovl/dktitle/drafts.tsv). */
#include "ovl.h"

typedef struct { char *(*f0)(void); s32 (*f4)(void); s32 (*f8)(void); s32 (*fc)(void); s32 x10; char *(*f14)(void); } Cfg;
typedef struct { u32 b0 : 1; u32 b1 : 1; u32 b2 : 1; u32 mode : 2; u32 hi : 3; } __attribute__((packed)) Sema;
typedef unsigned int size_t;
s32 sprintf(char *, const char *, ...);
s32 func_00f26180(void);
s32 sceOpen(const char *, s32, ...);
void func_00f25c28(void);
s32 sceClose(s32);
s32 sceCdSync(s32);
s32 sceCdDiskReady(s32);
s32 sceCdRead(u32, u32, void *, void *);
void FlushCache(s32);
s32 sceLseek(s32, s32, s32);
s32 sceWrite(s32, const void *, s32);
s32 sceSync(const char *, s32);
s32 sceRead(s32, void *, s32);
s32 memcmp(const void *, const void *, size_t);
extern volatile Sema D_002C5968;
extern s32 D_0046A614;
extern Cfg D_0046A688;
extern u32 D_00F26E38;
extern s32 D_00F26E3C;
extern s32 D_00F26E40;
extern char *D_00F26E44;
extern char *D_00F26E48;
extern s32 D_00F27214;
extern u8 D_00F27218[];
extern char D_00F27538[];
extern s32 D_00F2C900;
extern s32 D_00F2C904;

s32 func_00f25c40(void) {
    char buf[64];
    Cfg *c;
    s32 fd, r, lba, blk;
    u32 left, chunk, nblk;

    c = &D_0046A688;
    sprintf(buf, D_00F27538, c->f4(), c->f8());
    func_00f26180();
    fd = sceOpen(c->f14(), 0x603, 0x1FF);
    if (fd < 0) for (;;) func_00f25c28();
    D_0046A614 = 390;
    sceClose(fd);
    left = D_00F26E38;
    lba = D_00F26E40;
    D_0046A614 = 400;
    nblk = (left + 0x7FFFF) >> 19;
    D_00F26E3C = 0;
    while (sceCdSync(1) != 0) func_00f25c28();
    blk = 0;
    D_0046A614 = 410;
    if (nblk != 0) {
        do {
            u32 i; // scoped to the loop: 245 -> 7 words (decomp-permuter, session 135)
retry:
            if (D_002C5968.mode) for (;;) func_00f25c28();
            while (D_002C5968.b1 || D_002C5968.b0) func_00f25c28();
            D_00F2C904 = 256;
            D_00F27214 = 1;
            D_00F2C900 = lba;
            while (D_002C5968.b1 || D_002C5968.b0 || sceCdDiskReady(1) != 2
                   || sceCdRead(lba, 256, D_00F26E44, D_00F27218) != 1)
                func_00f25c28();
            while (sceCdSync(1) != 0) {
                func_00f25c28();
                if (D_002C5968.b1) goto retry;
            }
            FlushCache(0);
            fd = sceOpen(D_0046A688.f14(), 0x103, 0x1FF);
            if (fd < 0) for (;;) func_00f25c28();
            chunk = 0x80000; if (left <= 0x7FFFF) chunk = left;
            if (sceLseek(fd, D_00F26E3C, 0) < 0) {
                sceClose(fd);
                goto retry;
            }
            r = sceWrite(fd, D_00F26E44, chunk);
            if (r < 0) for (;;) func_00f25c28();
            if (r != chunk) for (;;) func_00f25c28();
            sceClose(fd);
            sceSync(buf, 0);
verify:
            if (D_002C5968.mode) for (;;) func_00f25c28();
            fd = sceOpen(D_0046A688.f14(), 0x103, 0x1FF);
            if (fd < 0) for (;;) func_00f25c28();
            if (sceLseek(fd, D_00F26E3C, 0) < 0) for (;;) func_00f25c28();
            if (sceRead(fd, D_00F26E48, chunk) != chunk) for (;;) func_00f25c28();
            FlushCache(0);
            if (memcmp(D_00F26E44, D_00F26E48, chunk) != 0) {
                for (i = 0; i < chunk; i++) {
                    if (D_00F26E44[i] != D_00F26E48[i]) {
                        if (sceLseek(fd, D_00F26E3C + i, 0) < 0) for (;;) func_00f25c28();
                        if (sceWrite(fd, D_00F26E44 + i, 1) != 1) for (;;) func_00f25c28();
                    }
                }
                sceClose(fd);
                sceSync(buf, 0);
                goto verify;
            }
            left -= chunk;
            blk++;
            sceClose(fd);
            sceSync(buf, 0);
            lba += chunk >> 11;
            D_00F26E3C += chunk;
        } while (blk < (s32)nblk);
    }
    return 0;
}
