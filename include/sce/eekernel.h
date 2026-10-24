/* Declarations of the EE kernel calls (libkernl syscalls) as linked into the
 * game ELF.  Hand-written from the public function signatures; no SDK
 * headers are copied into this repository.  Addresses are in functions.tsv.
 * The game keeps the parameter blocks in its own structs (src/util/thread.c),
 * so they stay opaque here (include/platform/thread.h casts to them). */
#ifndef KH1_SCE_EEKERNEL_H
#define KH1_SCE_EEKERNEL_H

struct ThreadParam;
struct SemaParam;

void FlushCache(int operation);
void iFlushCache(int operation);

int CreateThread(struct ThreadParam *param);
int StartThread(int thread_id, void *arg);
int ChangeThreadPriority(int thread_id, int priority);
int GetThreadId(void);

int CreateSema(struct SemaParam *param);
int WaitSema(int sema_id);
int SignalSema(int sema_id);
int iSignalSema(int sema_id);
int iReferSemaStatus(int sema_id, struct SemaParam *param);

int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int handler_id);
int EnableDmac(int channel);
int DisableDmac(int channel);

#endif /* KH1_SCE_EEKERNEL_H */
