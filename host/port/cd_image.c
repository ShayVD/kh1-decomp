/* The disc behind platform/cd.h off the EE (phase 5, docs/vita-port-plan.md section 5.1c): the
 * user's own disc image, read by sector, so PlatCdSearchFile and PlatCdRead answer what the
 * drive would.  The game asks for files by ISO9660 path ("\SYSTEM.CNF;1", "\KINGDOM.IDX;1",
 * src/io/discfile.c) and then reads absolute sectors (KINGDOM.IMG is not in the ISO directory:
 * its files are found through KINGDOM.IDX, relative to SYSTEM.CNF's sector), so the image is
 * read as it is, not extracted.  2048-byte sectors (.iso) or raw 2352-byte ones (.bin, mode 1
 * or mode 2 form 1), as tools/shift/extract_kingdom.py reads them.  Plain stdio: the Vita
 * platform can share it.  Nothing is written.  Not part of the PS2 build. */
#include "common.h"

/* the libc calls, declared here like host/port/sdk_host.c does (no system headers) */
typedef unsigned int size_t_;
void *fopen(const char *, const char *);
int fclose(void *);
int fseek(void *, long, int);
size_t_ fread(void *, size_t_, size_t_, void *);
void *memset(void *, int, size_t_);
void *memcpy(void *, const void *, size_t_);

#define SECTOR 2048

static void *img_file;
static int img_ssize;  /* bytes per sector in the file */
static int img_off;    /* where the 2048 data bytes start in one */

/* one sector's 2048 data bytes; 0 if past the end of the image */
static int read_sector(u32 lsn, u8 *buf) {
    if (fseek(img_file, (long)lsn * img_ssize + img_off, 0) != 0) return 0;
    return fread(buf, 1, SECTOR, img_file) == SECTOR;
}

int kh1_cd_image_open(const char *path) {
    static const struct { int ssize, off; } kinds[] = {{2048, 0}, {2352, 24}, {2352, 16}};
    u8 pvd[SECTOR];
    int i;
    img_file = fopen(path, "rb");
    if (!img_file) return 0;
    for (i = 0; i < 3; i++) {
        img_ssize = kinds[i].ssize;
        img_off = kinds[i].off;
        /* the primary volume descriptor at sector 16: type 1, "CD001" */
        if (read_sector(16, pvd) && pvd[0] == 1 && pvd[1] == 'C' && pvd[2] == 'D' && pvd[3] == '0'
            && pvd[4] == '0' && pvd[5] == '1')
            return 1;
    }
    fclose(img_file);
    img_file = 0;
    return 0;
}

int kh1_cd_image_is_open(void) { return img_file != 0; }

/* n sectors from lsn into buf; 0 if any is past the end of the image */
int kh1_cd_image_read(u32 lsn, u32 n, void *buf) {
    u8 *p = (u8 *)buf;
    u32 i;
    for (i = 0; i < n; i++, p += SECTOR)
        if (!read_sector(lsn + i, p)) return 0;
    return 1;
}

static u32 le32(const u8 *p) { return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24; }

static int upper(int c) { return c >= 'a' && c <= 'z' ? c - 32 : c; }

/* an ISO name ("SYSTEM.CNF;1", n bytes) against one component of the path (up to '\' or the end),
 * case-insensitive, either side's ";version" ignored */
static int same_name(const u8 *iso, int n, const char *want, int wn) {
    int i;
    for (i = 0; i < n; i++)
        if (iso[i] == ';') { n = i; break; }
    for (i = 0; i < wn; i++)
        if (want[i] == ';') { wn = i; break; }
    if (n != wn) return 0;
    for (i = 0; i < n; i++)
        if (upper(iso[i]) != upper((u8)want[i])) return 0;
    return 1;
}

/* the directory record named by want[0..wn) in the directory at (lba, size): its extent and size,
 * and whether it is a directory */
static int find_in_dir(u32 lba, u32 size, const char *want, int wn, u32 *out_lba, u32 *out_size,
                       int *is_dir) {
    u8 sec[SECTOR];
    u32 done;
    for (done = 0; done < size; done += SECTOR, lba++) {
        u32 i = 0;
        if (!read_sector(lba, sec)) return 0;
        /* records do not cross sectors; a zero length ends the sector's list */
        while (i < SECTOR && sec[i] != 0) {
            const u8 *r = sec + i;
            int nl = r[32];
            if (i + r[0] > SECTOR) break;
            /* names 0 and 1 are "." and ".." */
            if (!(nl == 1 && r[33] <= 1) && same_name(r + 33, nl, want, wn)) {
                *out_lba = le32(r + 2);
                *out_size = le32(r + 10);
                *is_dir = (r[25] & 2) != 0;
                return 1;
            }
            i += r[0];
        }
    }
    return 0;
}

/* name as libcdvd takes it: "\DIR\FILE.EXT;1" (a leading '\' or '/', either separator) */
int kh1_cd_image_search(const char *name, u32 *lsn, u32 *size) {
    u8 pvd[SECTOR];
    u32 lba, sz;
    int dir = 1;
    if (!img_file || !read_sector(16, pvd)) return 0;
    /* the root directory's record in the primary volume descriptor */
    lba = le32(pvd + 156 + 2);
    sz = le32(pvd + 156 + 10);
    while (*name == '\\' || *name == '/') name++;
    while (*name) {
        int n = 0;
        if (!dir) return 0;
        while (name[n] && name[n] != '\\' && name[n] != '/') n++;
        if (!find_in_dir(lba, sz, name, n, &lba, &sz, &dir)) return 0;
        name += n;
        while (*name == '\\' || *name == '/') name++;
    }
    if (dir) return 0;
    *lsn = lba;
    *size = sz;
    return 1;
}
