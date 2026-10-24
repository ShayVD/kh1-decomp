/* Platform wrapper: the disc drive (libcdvd). See docs/portability.md.
 *
 * src/io/discfile.c and src/io/cdqueue.c read the disc by sector: they find
 * a file's first sector with PlatCdSearchFile, then loop
 * `PlatCdDiskReady(1) == 2 && PlatCdRead(lsn, sectors, buf, mode)`,
 * `PlatCdSync(1)` until the read ends, and retry while PlatCdGetError()
 * is non-zero.  The boot (discfile.c func_00120b10) runs PlatCdInit(0),
 * PlatCdMmode(2) (DVD media) and PlatCdInitEeCB (the callback thread);
 * src/game/hdd.c installs a power-off handler with PlatCdPOffCallback and
 * src/game/hdd.nofill.c powers off with PlatCdPowerOff.  On the matching PS2
 * build each wrapper is a macro for the libcdvd call.  The Vita port reads
 * the user's own extracted disc image: PlatCdRead copies sectors from it
 * synchronously (so PlatCdSync and PlatCdGetError answer 0 at once),
 * PlatCdDiskReady answers 2 (ready) and the rest are no-ops. */
#ifndef KH1_PLATFORM_CD_H
#define KH1_PLATFORM_CD_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libcdvd.h"
#define PlatCdInit(mode) sceCdInit(mode)
#define PlatCdInitEeCB(prio, stack, size) sceCdInitEeCB((prio), (void *)(stack), (size))
#define PlatCdPOffCallback(func, arg) sceCdPOffCallback((void (*)(void *))(func), (void *)(arg))
#define PlatCdSearchFile(fp, name) sceCdSearchFile((sceCdlFILE *)(fp), (const char *)(name))
#define PlatCdSync(mode) sceCdSync(mode)
#define PlatCdDiskReady(mode) sceCdDiskReady(mode)
#define PlatCdMmode(media) sceCdMmode(media)
#define PlatCdRead(lsn, sectors, buf, mode) sceCdRead((lsn), (sectors), (void *)(buf), (sceCdRMode *)(mode))
#define PlatCdSeek(lsn) sceCdSeek(lsn)
#define PlatCdGetError() sceCdGetError()
#define PlatCdStatus() sceCdStatus()
#define PlatCdBreak() sceCdBreak()
#define PlatCdPowerOff(result) sceCdPowerOff((int *)(result))
#else
int PlatCdInit(int mode);
int PlatCdInitEeCB(int priority, void *stack, int stacksize);
void *PlatCdPOffCallback(void (*func)(void *), void *arg);
int PlatCdSearchFile(void *fp, const char *name);
int PlatCdSync(int mode);
int PlatCdDiskReady(int mode);
int PlatCdMmode(int media);
int PlatCdRead(unsigned int lsn, unsigned int sectors, void *buf, void *mode);
int PlatCdSeek(unsigned int lsn);
int PlatCdGetError(void);
int PlatCdStatus(void);
int PlatCdBreak(void);
int PlatCdPowerOff(int *result);
#endif

#endif /* KH1_PLATFORM_CD_H */
