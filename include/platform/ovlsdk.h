/* Platform wrapper: the SDK calls the overlays' C makes by their SCE names (docs/native-overlays.md).
 *
 * The matched overlay C declares each SCE function itself (sceOpen, FlushCache, sceGsExecLoadImage
 * ...), with the return type that gives the original's registers, so on the PS2 the calls stay as
 * they are.  A port compiles the overlays with this header forced in front (tools/host/ovlnative.py):
 * each name becomes the main ELF's platform wrapper (include/platform/file.h, cd.h, dma.h, gs.h,
 * thread.h) or a port function for the two SDK routines the overlays call by address.  Nothing here
 * applies to the PS2 build. */
#ifndef KH1_PLATFORM_OVLSDK_H
#define KH1_PLATFORM_OVLSDK_H

#ifndef KH1_PS2
#define FlushCache PlatFlushCache
#define sceOpen PlatFsOpen
#define sceClose PlatFsClose
#define sceRead PlatFsRead
#define sceWrite PlatFsWrite
#define sceLseek PlatFsLseek
#define sceIoctl2 PlatFsIoctl2
#define sceSync PlatFsSync
#define sceRemove PlatFsRemove
#define sceMkdir PlatFsMkdir
#define sceFormat PlatFsFormat
#define sceCdSync PlatCdSync
#define sceCdRead PlatCdRead
#define sceCdDiskReady PlatCdDiskReady
#define sceDmaGetChan PlatDmaGetChan
#define sceDmaSend PlatDmaSend
/* wm.x: its packet sends wait on channels 1 / 2; a port's transfer is done when it starts
 * (host/null/plat_null.c) */
#define sceDmaSync PlatOvlDmaSync
#define iFlushCache PlatIFlushCache
#define sceGsSetDefLoadImage PlatGsSetDefLoadImage
#define sceGsExecLoadImage PlatGsExecLoadImage
/* newlib's strncpy (the EE's MMI version in src/sdk/libkernl_asm.s) */
#define func_00265190 strncpy
/* src/asm/text_0024e0a4.s func_0024e640(stack, size, fn, arg): fn(arg) on the given stack
 * (dktitle.x runs its HDD install thread's body this way); host/port/ovl.c */
#define func_0024e640 PlatCallOnStack
#endif

#endif /* KH1_PLATFORM_OVLSDK_H */
