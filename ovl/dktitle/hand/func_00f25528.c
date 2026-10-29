/* dktitle.x func_00f25528: matched by hand. */
#include "ovl.h"

typedef unsigned int size_t;
void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);
char *func_00265190(char *, const char *, s32);
s32 sceLseek(s32, s32, s32);
s32 sceWrite(s32, const void *, s32);
typedef struct { s32 off; s32 size; } Ent;
typedef struct {
    char magic[9];
    char pad[3];
    s32 x0c;
    Ent e[4];
    u8 rest[464];
} Hdr;
extern s32 D_0046A678;
extern s32 D_00F26E20;
extern void *D_00F26E24;
extern void *D_00F26E28;
extern s32 D_00F26E2C;
extern u8 *D_00F26E44;
extern char D_00F26EC8[], D_00F26EE8[], D_00F27070[], D_00F27090[], D_00F27528[];

#define ALIGN512(x) (((x) + 511) / 512 * 512)
s32 func_00f25528(s32 fd) {
    Hdr h;
    u8 *buf;
    s32 i, r, size, off, n, t;
    s32 o;

    buf = D_00F26E44;

    func_00265190(h.magic, D_00F27528, 9);
    memset(h.pad, 0, 3);
    o = 512;
    h.e[0].off = o;
    h.x0c = 0;
    n = D_00F26E2C;
    h.e[0].size = n;
    o += ALIGN512(n);
    h.e[1].off = o;
    if (D_0046A678) n = strlen(D_00F26EE8); else n = strlen(D_00F27090);
    h.e[1].size = n;
    t = h.e[1].off + ALIGN512(n);
    n = D_00F26E20;
    h.e[2].off = t;
    h.e[2].size = n;
    h.e[3].off = t;
    h.e[3].size = n;
    memset(h.rest, 0, sizeof(h.rest));
    if ((r = sceWrite(fd, &h, 512)) < 0) return r;
    for (i = 0; i < 3; i++) {
        size = h.e[i].size;
        off = h.e[i].off;
        n = ALIGN512(size);
        memset(buf, 0, n);
        switch (i) {
        case 0:
            memcpy(buf, D_00F26E28, size);
            break;
        case 1:
            if (D_0046A678) {
                memcpy(buf, D_00F26EE8, size);
                memcpy(buf + 14, D_00F26EC8, 26);
            } else {
                memcpy(buf, D_00F27090, size);
                memcpy(buf + 14, D_00F27070, 29);
            }
            break;
        case 2:
            memcpy(buf, D_00F26E24, size);
            break;
        }
        if ((r = sceLseek(fd, off, 0)) < 0) return r;
        if ((r = sceWrite(fd, buf, n)) < 0) return r;
    }
    return 0;
}
