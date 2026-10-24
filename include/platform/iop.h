/* Platform wrapper: RPC to the IOP (sifrpc). See docs/portability.md.
 *
 * The game talks to its own IOP sound driver through one RPC client:
 * src/sound/snd_rpc.c binds server 17 and sends every sound command as
 * PlatSifCallRpc(client, command, 0, D_00633640, 0x2000, D_00633640, 0x2000,
 * 0, 0), the arguments and the answer in the same 8 KiB buffer.
 * src/io/discfile.c starts the RPC layer (PlatSifInitRpc(0)) before libcdvd.
 * On the matching PS2 build each wrapper is a macro for the SCE call.  The
 * Vita port does not have an IOP: it implements PlatSifCallRpc for the sound
 * server by decoding the command in place (the sound commands are listed in
 * src/sound/snd_rpc.c), and the others as no-ops. */
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
#else
void PlatSifInitRpc(unsigned int mode);
int PlatSifBindRpc(void *client, unsigned int num, unsigned int mode);
int PlatSifCallRpc(void *client, unsigned int num, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                   void (*end)(void *), void *param);
#endif

#endif /* KH1_PLATFORM_IOP_H */
