/* Platform wrapper: controller input. See docs/portability.md.
 *
 * Game code calls Plat* names only, never sce* directly. On the matching PS2
 * build each wrapper is a macro for the original SCE call, so the generated
 * code is identical to the original. The Vita port provides its own
 * implementation of the same names. */
#ifndef KH1_PLATFORM_PAD_H
#define KH1_PLATFORM_PAD_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/libpad.h"
#define PlatPadRead(port, slot, data) scePadRead((port), (slot), (data))
#else
int PlatPadRead(int port, int slot, u8 *data);
#endif

#endif /* KH1_PLATFORM_PAD_H */
