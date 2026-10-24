/* Declarations of SCE libcdvd functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository.  Addresses are in functions.tsv (session 57:
 * named from the strings and the N / S command numbers, docs/sdk.md). */
#ifndef KH1_SCE_LIBCDVD_H
#define KH1_SCE_LIBCDVD_H

typedef struct sceCdRMode sceCdRMode; /* trycount, spindlctrl, datapattern, pad: 4 bytes */
typedef struct sceCdlFILE sceCdlFILE; /* lsn, size, name[16], date[8]: 36 bytes */

int sceCdInit(int mode);
int sceCdInitEeCB(int priority, void *stack, int stacksize);
void *sceCdPOffCallback(void (*func)(void *), void *addr);
int sceCdSearchFile(sceCdlFILE *fp, const char *name);
int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer);
int sceCdSync(int mode);
int sceCdSyncS(int mode);
int sceCdDiskReady(int mode);
int sceCdMmode(int media);
int sceCdRead(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);
int sceCdSeek(unsigned int lsn);
int sceCdGetError(void);
int sceCdStatus(void);
int sceCdBreak(void);
int sceCdPowerOff(int *result);

#endif /* KH1_SCE_LIBCDVD_H */
