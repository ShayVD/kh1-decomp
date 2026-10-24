/* Declarations of SCE libmc functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository.  Addresses are in functions.tsv (session 44:
 * named by their mcserv RPC numbers, docs/sdk.md). */
#ifndef KH1_SCE_LIBMC_H
#define KH1_SCE_LIBMC_H

int sceMcInit(void);
int sceMcGetSlotMax(int port);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcOpen(int port, int slot, const char *name, int mode);
int sceMcClose(int fd);
int sceMcRead(int fd, void *buf, int size);
int sceMcWrite(int fd, const void *buf, int size);
int sceMcMkdir(int port, int slot, const char *name);
int sceMcChdir(int port, int slot, const char *name, char *cur);
int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table);
int sceMcDelete(int port, int slot, const char *name);
int sceMcFormat(int port, int slot);
int sceMcUnformat(int port, int slot);
int sceMcRename(int port, int slot, const char *name, const char *newname);
int sceMcSync(int mode, int *cmd, int *result);

#endif /* KH1_SCE_LIBMC_H */
