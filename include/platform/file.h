/* Platform wrapper: files through the IOP (sifdev). See docs/portability.md.
 *
 * Three places open files by name instead of reading disc sectors:
 * src/io/discfile.c's func_001202c0 (the other read path: one big file,
 * D_0048D260, read at sector * 2048 when the game runs from the HDD),
 * src/gfx/opfile.c (whole host files for the model tools: open, seek to the
 * end for the size, read, close) and src/game/hdd.c (the HDD install: mount
 * "pfs0:", list a directory, file sizes with PlatFsLseek64, the devctl /
 * ioctl2 queries of the "hdd:" / "pfs:" / "dev9x:" devices).
 * discfile.c's func_00120b10 resets the client (PlatFsReset) before the IOP
 * reboot.  On the matching PS2 build each wrapper is a macro for the sifdev
 * call.  The Vita port maps the names onto its own file system (the game's
 * data directory); the HDD calls answer "no drive" (PlatFsDevctl < 0), so
 * the HDD install is never offered. */
#ifndef KH1_PLATFORM_FILE_H
#define KH1_PLATFORM_FILE_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/sifdev.h"
#define PlatFsReset() sceFsReset()
#define PlatFsOpen(name, flag) sceOpen((const char *)(name), (flag))
#define PlatFsClose(fd) sceClose(fd)
#define PlatFsRead(fd, buf, n) sceRead((fd), (void *)(buf), (n))
#define PlatFsLseek(fd, offset, whence) sceLseek((fd), (offset), (whence))
#define PlatFsLseek64(fd, offset, whence) sceLseek64((fd), (offset), (whence))
#define PlatFsIoctl2(fd, req, arg, arglen, buf, buflen) \
    sceIoctl2((fd), (req), (void *)(arg), (arglen), (void *)(buf), (buflen))
#define PlatFsDopen(name) sceDopen((const char *)(name))
#define PlatFsDclose(fd) sceDclose(fd)
#define PlatFsDread(fd, ent) sceDread((fd), (struct sce_dirent *)(ent))
#define PlatFsMount(fsdev, blockdev, flag, arg, arglen) \
    sceMount((const char *)(fsdev), (const char *)(blockdev), (flag), (void *)(arg), (arglen))
#define PlatFsUmount(fsdev) sceUmount((const char *)(fsdev))
#define PlatFsDevctl(dev, cmd, arg, arglen, buf, buflen) \
    sceDevctl((const char *)(dev), (cmd), (const void *)(arg), (arglen), (void *)(buf), (buflen))
#else
int PlatFsReset(void);
int PlatFsOpen(const char *name, int flag);
int PlatFsClose(int fd);
int PlatFsRead(int fd, void *buf, int n);
int PlatFsLseek(int fd, int offset, int whence);
s64 PlatFsLseek64(int fd, s64 offset, int whence);
int PlatFsIoctl2(int fd, int req, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
int PlatFsDopen(const char *name);
int PlatFsDclose(int fd);
int PlatFsDread(int fd, void *ent);
int PlatFsMount(const char *fsdev, const char *blockdev, int flag, void *arg, int arglen);
int PlatFsUmount(const char *fsdev);
int PlatFsDevctl(const char *dev, int cmd, const void *arg, unsigned int arglen, void *buf, unsigned int buflen);
#endif

#endif /* KH1_PLATFORM_FILE_H */
