/* The IOP off the PS2 (docs/sound-spec.md "The IOP on the port"): an R3000A interpreter that runs
 * one IOP module from the user's own disc (the sound driver LIBSSL.IRX) with its kernel, SIF and
 * libsd calls answered in C.  host/port/iop.c is the CPU, the module loader and the kernel;
 * host/port/spu2.c answers libsd (the SPU2's voices, mixed to 48 kHz stereo); host/port/snd.c ties
 * it to the game's sound RPC (server 17).  Not part of the PS2 build. */
#ifndef KH1_HOST_IOP_H
#define KH1_HOST_IOP_H

#include "common.h"

#define KH1_IOP_RAM 0x200000

extern u8 kh1_iop_ram[KH1_IOP_RAM];

/* An IOP address (kseg0 / kseg1 / physical) to the host: RAM only, 0 outside it. */
u8 *kh1_iop_ptr(u32 addr, u32 size);

/* Load a relocatable IRX image (the bytes stay the caller's), run its start routine and the threads
 * it starts until they block.  0 on success. */
int kh1_iop_load(const u8 *irx, u32 size);
int kh1_iop_loaded(void);

/* Call the RPC server `sid`'s function `fno` as sifcmd would: `send` is copied into the server's
 * buffer, the answer (rsize bytes from the address the function returns) into `recv`.  Threads it
 * wakes run before it returns.  -1 when no such server is registered. */
int kh1_iop_rpc(u32 sid, u32 fno, const void *send, int ssize, void *recv, int rsize);

/* One hardware-timer interrupt (the module's handler) and the threads it wakes: the driver's tick.
 * kh1_iop_timer_hz() is the rate its handler asked for (0 before a timer is set). */
void kh1_iop_tick(void);
u32 kh1_iop_timer_hz(void);

/* Instructions run so far (the watchdog's cost line). */
extern u32 kh1_iop_insns;

/* libsd, answered by host/port/spu2.c (the import numbers are libsd's export table's) */
u32 kh1_sd_call(int fn, const u32 *a);
/* a libsd transfer finished: host/port/iop.c runs the module's handler for it at the next chance */
void kh1_iop_raise_trans(int core);
void kh1_iop_set_trans_handler(int core, u32 func, u32 arg);

#endif
