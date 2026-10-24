/* Platform wrapper: the EE kernel (threads, semaphores, the data cache, DMA
 * interrupt handlers). See docs/portability.md.
 *
 * The game runs one worker thread fed by a semaphore (src/util/thread.c),
 * waits on and signals semaphores from the file and sound queues, writes the
 * data cache back before every DMA send (PlatFlushCache(0); PlatIFlushCache
 * from an interrupt handler) and hooks the DMAC interrupt of a channel.
 * PlatPcStart / PlatPcStop run the CPU performance counters (src/pad/padread.c
 * at boot, src/util/heap.c); the Vita build can make them no-ops.  On
 * the matching PS2 build each wrapper is a macro for the kernel call; the
 * casts take the game's own ThreadParam / SemaParam blocks.  The Vita port
 * maps threads and semaphores onto sceKernel* and makes the cache calls
 * no-ops (the renderer reads memory directly). */
#ifndef KH1_PLATFORM_THREAD_H
#define KH1_PLATFORM_THREAD_H

#include "common.h"

#ifdef KH1_PS2
#include "sce/eekernel.h"
#define PlatFlushCache(op) FlushCache(op)
#define PlatIFlushCache(op) iFlushCache(op)
#define PlatCreateThread(param) CreateThread((struct ThreadParam *)(param))
#define PlatStartThread(id, arg) StartThread((id), (void *)(arg))
#define PlatChangeThreadPriority(id, prio) ChangeThreadPriority((id), (prio))
#define PlatGetThreadId() GetThreadId()
#define PlatCreateSema(param) CreateSema((struct SemaParam *)(param))
#define PlatWaitSema(id) WaitSema(id)
#define PlatSignalSema(id) SignalSema(id)
#define PlatISignalSema(id) iSignalSema(id)
#define PlatIReferSemaStatus(id, param) iReferSemaStatus((id), (struct SemaParam *)(param))
#define PlatAddDmacHandler(ch, handler, next) AddDmacHandler((ch), (int (*)(int))(handler), (next))
#define PlatRemoveDmacHandler(ch, id) RemoveDmacHandler((ch), (id))
#define PlatEnableDmac(ch) EnableDmac(ch)
#define PlatDisableDmac(ch) DisableDmac(ch)
#define PlatPcStart(control, c0, c1) scePcStart((control), (c0), (c1))
#define PlatPcStop() scePcStop()
#else
void PlatFlushCache(int op);
void PlatIFlushCache(int op);
int PlatCreateThread(void *param);
int PlatStartThread(int id, void *arg);
int PlatChangeThreadPriority(int id, int prio);
int PlatGetThreadId(void);
int PlatCreateSema(void *param);
int PlatWaitSema(int id);
int PlatSignalSema(int id);
int PlatISignalSema(int id);
int PlatIReferSemaStatus(int id, void *param);
int PlatAddDmacHandler(int ch, int (*handler)(int), int next);
int PlatRemoveDmacHandler(int ch, int id);
int PlatEnableDmac(int ch);
int PlatDisableDmac(int ch);
int PlatPcStart(int control, int c0, int c1);
void PlatPcStop(void);
#endif

#endif /* KH1_PLATFORM_THREAD_H */
