#ifndef FAKE_PSP2_THREADMGR_H
#define FAKE_PSP2_THREADMGR_H
#include "../types.h"
typedef int (*SceKernelThreadEntry)(SceSize args, void *argp);
typedef struct {
    SceSize size;
    void *stack;
    int stackSize;
    int currentPriority;
    int currentCpuAffinityMask;
    int lastExecutedCpuId;
    SceUInt64 runClocks;
    unsigned int intrPreemptCount, threadPreemptCount;
} SceKernelThreadInfo;
#define SCE_KERNEL_CPU_MASK_USER_2 0x40000
SceUID sceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int prio, SceSize stack, unsigned int attr,
                             int cpu_mask, const void *option);
int sceKernelStartThread(SceUID id, SceSize args, void *argp);
int sceKernelDelayThread(unsigned int us);
SceUID sceKernelGetThreadId(void);
int sceKernelGetThreadInfo(SceUID id, SceKernelThreadInfo *info);
#endif
