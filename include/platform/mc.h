/* Platform wrapper: memory card. See docs/portability.md.
 *
 * Only src/memcard/ calls these (the request queue of
 * include/memcard/mcreq.h); game code queues requests.  On the matching PS2
 * build each wrapper is a macro for the libmc call, so the generated code is
 * identical to the original.  The Vita port implements the same names
 * (a save directory per "BISLPS-25198-NN", synchronous calls whose
 * PlatMcSync answers at once).  The answer codes the steps read are libmc's:
 * >= 0 done (a count or an fd), -1 / -2 a new card (formatted / not),
 * -3 ... -8 the errors src/memcard/mcstep.c maps to its own codes. */
#ifndef KH1_PLATFORM_MC_H
#define KH1_PLATFORM_MC_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libmc.h"
#define PlatMcInit() sceMcInit()
#define PlatMcGetSlotMax(port) sceMcGetSlotMax(port)
#define PlatMcGetInfo(port, slot, type, free, format) sceMcGetInfo((port), (slot), (type), (free), (format))
#define PlatMcOpen(port, slot, name, mode) sceMcOpen((port), (slot), (name), (mode))
#define PlatMcClose(fd) sceMcClose(fd)
#define PlatMcRead(fd, buf, size) sceMcRead((fd), (buf), (size))
#define PlatMcWrite(fd, buf, size) sceMcWrite((fd), (buf), (size))
#define PlatMcMkdir(port, slot, name) sceMcMkdir((port), (slot), (name))
#define PlatMcChdir(port, slot, name, cur) sceMcChdir((port), (slot), (name), (cur))
#define PlatMcGetDir(port, slot, name, mode, maxent, table) sceMcGetDir((port), (slot), (name), (mode), (maxent), (table))
#define PlatMcDelete(port, slot, name) sceMcDelete((port), (slot), (name))
#define PlatMcFormat(port, slot) sceMcFormat((port), (slot))
#define PlatMcUnformat(port, slot) sceMcUnformat((port), (slot))
#define PlatMcRename(port, slot, name, newname) sceMcRename((port), (slot), (name), (newname))
#define PlatMcSync(mode, cmd, result) sceMcSync((mode), (cmd), (result))
#else
int PlatMcInit(void);
int PlatMcGetSlotMax(int port);
int PlatMcGetInfo(int port, int slot, int *type, int *free, int *format);
int PlatMcOpen(int port, int slot, const char *name, int mode);
int PlatMcClose(int fd);
int PlatMcRead(int fd, void *buf, int size);
int PlatMcWrite(int fd, const void *buf, int size);
int PlatMcMkdir(int port, int slot, const char *name);
int PlatMcChdir(int port, int slot, const char *name, char *cur);
int PlatMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table);
int PlatMcDelete(int port, int slot, const char *name);
int PlatMcFormat(int port, int slot);
int PlatMcUnformat(int port, int slot);
int PlatMcRename(int port, int slot, const char *name, const char *newname);
int PlatMcSync(int mode, int *cmd, int *result);
#endif

#endif /* KH1_PLATFORM_MC_H */
