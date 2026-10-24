/* Declarations of the SCE file calls (libkernl's sifdev: the EE client of
 * the IOP's fileio server) as linked into the game ELF.  Hand-written from
 * the public function signatures; no SDK headers are copied into this
 * repository.  Addresses are in functions.tsv (session 57: named from the
 * fileio RPC numbers, docs/sdk.md). */
#ifndef KH1_SCE_SIFDEV_H
#define KH1_SCE_SIFDEV_H

struct sce_dirent; /* the stat block (0x40 bytes), name[256], a private word */

#define SCE_RDONLY 0x0001
#define SCE_SEEK_SET 0
#define SCE_SEEK_END 2

int sceFsInit(void);
int sceFsReset(void);
int sceOpen(const char *filename, int flag, ...);
int sceClose(int fd);
int sceRead(int fd, void *buf, int nbyte);
int sceWrite(int fd, const void *buf, int nbyte);
int sceLseek(int fd, int offset, int whence);
long sceLseek64(int fd, long offset, int whence); /* long is 64-bit in the EE ABI */
int sceIoctl(int fd, int request, void *arg);
int sceIoctl2(int fd, int request, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
int sceDopen(const char *dirname);
int sceDclose(int fd);
int sceDread(int fd, struct sce_dirent *buf);
int sceMount(const char *fsdev, const char *blockdev, int flag, void *arg, int arglen);
int sceUmount(const char *fsdev);
int sceDevctl(const char *devname, int cmd, const void *arg, unsigned int arglen, void *buf, unsigned int buflen);

/* IOP modules (loadfile) and the IOP reboot (iopreset); SCE's sifdev.h
 * declares them too. */
int sceSifLoadModule(const char *filename, int arglen, const char *args);
int sceSifLoadStartModule(const char *filename, int arglen, const char *args, int *result);
int sceSifSearchModuleByName(const char *name);
int sceSifRebootIop(const char *image);
int sceSifSyncIop(void);

#endif /* KH1_SCE_SIFDEV_H */
