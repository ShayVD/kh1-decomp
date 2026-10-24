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

/* The game's decoded buttons (src/pad/padread*.c, session 57): libpad2's
 * digital bits made active high (bytes 0-1 xor 0xffff), the right stick's
 * directions in bits 20-23 and the left stick's in bits 28-31 (the d-pad
 * bits shifted up, func_0011f370).  The game confirms with circle and
 * cancels with cross (the Japanese layout). */
#define PAD_SELECT 0x0001u
#define PAD_L3 0x0002u
#define PAD_R3 0x0004u
#define PAD_START 0x0008u
#define PAD_UP 0x0010u
#define PAD_RIGHT 0x0020u
#define PAD_DOWN 0x0040u
#define PAD_LEFT 0x0080u
#define PAD_L2 0x0100u
#define PAD_R2 0x0200u
#define PAD_L1 0x0400u
#define PAD_R1 0x0800u
#define PAD_TRIANGLE 0x1000u
#define PAD_CIRCLE 0x2000u
#define PAD_CROSS 0x4000u
#define PAD_SQUARE 0x8000u
#define PAD_RSTICK(dir) ((dir) << 16)
#define PAD_LSTICK(dir) ((dir) << 24)
/* A direction on the d-pad or the left stick. */
#define PAD_DIR(dir) ((dir) | PAD_LSTICK(dir))

#endif /* KH1_PLATFORM_PAD_H */
