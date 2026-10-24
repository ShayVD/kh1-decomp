/* Platform wrapper: RPC to the IOP (sifrpc). See docs/portability.md.
 *
 * The game talks to its own IOP sound driver through one RPC client:
 * src/sound/snd_rpc.c binds server 17 and sends every sound command as
 * PlatSifCallRpc(client, command, 0, D_00633640, 0x2000, D_00633640, 0x2000,
 * 0, 0), the arguments and the answer in the same 8 KiB buffer.
 * src/io/discfile.c starts the RPC layer (PlatSifInitRpc(0)) before libcdvd,
 * reboots the IOP with its own image (PlatSifRebootIop until it is accepted,
 * PlatSifSyncIop until it is up) and loads the IOP modules
 * (PlatSifLoadModule, PlatSifLoadStartModule with arguments); src/game/hdd*.c
 * asks whether "hdd" is loaded (PlatSifSearchModuleByName < 0: no).
 * On the matching PS2 build each wrapper is a macro for the SCE call.  The
 * Vita port does not have an IOP: it implements PlatSifCallRpc for the sound
 * server by decoding the command in place (the sound commands are listed in
 * src/sound/snd_rpc.c), the reboot and module loads as successes (a module
 * id of 1, PlatSifSyncIop 1), PlatSifSearchModuleByName as -1 (no HDD
 * modules), and the others as no-ops. */
#ifndef KH1_PLATFORM_IOP_H
#define KH1_PLATFORM_IOP_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/sifrpc.h"
#define PlatSifInitRpc(mode) sceSifInitRpc(mode)
#define PlatSifBindRpc(client, num, mode) sceSifBindRpc((sceSifClientData *)(client), (num), (mode))
#define PlatSifCallRpc(client, num, mode, send, ssize, recv, rsize, end, param) \
    sceSifCallRpc((sceSifClientData *)(client), (num), (mode), (void *)(send), (ssize), (void *)(recv), (rsize), \
                  (end), (param))
#include "sce/sifdev.h"
#define PlatSifLoadModule(name, arglen, args) sceSifLoadModule((const char *)(name), (arglen), (const char *)(args))
#define PlatSifLoadStartModule(name, arglen, args, result) \
    sceSifLoadStartModule((const char *)(name), (arglen), (const char *)(args), (int *)(result))
#define PlatSifSearchModuleByName(name) sceSifSearchModuleByName((const char *)(name))
#define PlatSifRebootIop(image) sceSifRebootIop((const char *)(image))
#define PlatSifSyncIop() sceSifSyncIop()
#else
void PlatSifInitRpc(unsigned int mode);
int PlatSifBindRpc(void *client, unsigned int num, unsigned int mode);
int PlatSifCallRpc(void *client, unsigned int num, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                   void (*end)(void *), void *param);
int PlatSifLoadModule(const char *name, int arglen, const char *args);
int PlatSifLoadStartModule(const char *name, int arglen, const char *args, int *result);
int PlatSifSearchModuleByName(const char *name);
int PlatSifRebootIop(const char *image);
int PlatSifSyncIop(void);
#endif

#endif /* KH1_PLATFORM_IOP_H */
