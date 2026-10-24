/* Platform wrapper: controller input and vibration (libpad2, libdbc,
 * libvib). See docs/portability.md.
 *
 * src/pad/padread*.c is the only caller: it opens one libpad2 socket at boot
 * (PlatPadInit = sceDbcInit + scePad2Init, PlatPadCreateSocket), and each
 * frame waits for the state to be 1 (ready), reads the button profile, reads
 * the 128-byte button buffer (the digital buttons in bytes 0-1, active low;
 * analog sticks after) and sends the vibration parameters.  Game code reads
 * the decoded buttons (D_002C5BB0: cur / press / rep), never these calls.
 * On the matching PS2 build each wrapper is a macro for the SCE call, so the
 * generated code is identical to the original.  The Vita port implements the
 * same names with sceCtrlPeekBufferPositive, filling the buffer in the
 * libpad2 layout. */
#ifndef KH1_PLATFORM_PAD_H
#define KH1_PLATFORM_PAD_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libpad2.h"
#define PlatDbcInit() sceDbcInit()
#define PlatPadInit(mode) scePad2Init(mode)
#define PlatPadCreateSocket(param, addr) scePad2CreateSocket((void *)(param), (void *)(addr))
#define PlatPadGetState(socket) scePad2GetState(socket)
#define PlatPadGetButtonProfile(socket, profile) scePad2GetButtonProfile((socket), (void *)(profile))
#define PlatPadRead(socket, data) scePad2Read((socket), (data))
#define PlatVibSetActParam(socket, psize, profile, dsize, data) \
    sceVibSetActParam((socket), (psize), (profile), (dsize), (void *)(data))
#else
int PlatDbcInit(void);
int PlatPadInit(int mode);
int PlatPadCreateSocket(void *param, void *addr);
int PlatPadGetState(int socket);
int PlatPadGetButtonProfile(int socket, void *profile);
int PlatPadRead(int socket, u8 *data);
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data);
#endif

#endif /* KH1_PLATFORM_PAD_H */
