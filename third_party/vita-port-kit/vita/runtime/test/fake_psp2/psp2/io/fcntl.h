/* host tests: the few vitasdk declarations vita/runtime uses, with fakes in test/fake_sdk.c */
#ifndef FAKE_PSP2_IO_FCNTL_H
#define FAKE_PSP2_IO_FCNTL_H
#include "../types.h"
#define SCE_O_RDONLY 0x0001
#define SCE_O_WRONLY 0x0002
#define SCE_O_CREAT 0x0200
#define SCE_O_TRUNC 0x0400
SceUID sceIoOpen(const char *file, int flags, int mode);
int sceIoWrite(SceUID fd, const void *data, unsigned int size);
int sceIoRemove(const char *file);
#endif
