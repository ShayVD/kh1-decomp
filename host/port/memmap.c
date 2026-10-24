/* The fixed memory map off the EE (docs/vita-port-plan.md section 4, docs/shiftable-plan.md
 * "Session 26: the memory map past 0x820000"): the D_ names the game C uses for the regions past
 * the image, as offsets into one block so they keep their order and their distances (the block
 * heap ends where the load area starts: src/util/heap.c compares with D_009A0000; objslot.c maps
 * an address back to its 0x40000 slot), plus the save-block offsets and the GS register the game
 * names by address.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"

/* 0x6A0000 - 0x1FE0000 (the stack): 25 MiB, 0x40000-aligned so the slots at D_00FE0000 are too */
#define KH1_MEM_BASE 0x6A0000
#define KH1_MEM_END 0x1FE0000
u8 kh1_memmap[KH1_MEM_END - KH1_MEM_BASE] __attribute__((aligned(0x40000)));

#define KH1_REGION(name, addr) \
    __asm__(".globl " #name "\n\t.set " #name ", kh1_memmap + " #addr " - 0x6A0000")

KH1_REGION(D_006A0000, 0x6A0000);  /* func_0014a090's three pools (0x80000) */
KH1_REGION(D_00720000, 0x720000);  /* func_00133628's seven pools, the party files (to 0x7F2C00) */
KH1_REGION(D_00820000, 0x820000);  /* the block heap (src/util/heap*.c), 0x180000 */
KH1_REGION(D_009A0000, 0x9A0000);  /* the load area (dktitle.x names 0x9A0000 and 0xBA0000) */
KH1_REGION(D_00F20000, 0xF20000);  /* the overlay area: every overlay is linked here */
KH1_REGION(D_00FE0000, 0xFE0000);  /* 12 slots of 0x40000 (src/obj/objslot.c) */
KH1_REGION(D_01CE0000, 0x1CE0000); /* func_00155a50's area, up to the stack */

/* Offsets, not addresses: src/gummi/gumisave.c adds &D_00009B38 ... &D_0000AC20 to the block
 * func_00232cc0(4) returns (the Gummi part of the save data), so each name is its own value. */
#define KH1_OFFSET(name, value) __asm__(".globl " #name "\n\t.set " #name ", " #value)

KH1_OFFSET(D_00009B38, 0x9B38);
KH1_OFFSET(D_00009B3C, 0x9B3C);
KH1_OFFSET(D_00009B40, 0x9B40);
KH1_OFFSET(D_00009B44, 0x9B44);
KH1_OFFSET(D_00009B48, 0x9B48);
KH1_OFFSET(D_00009B4C, 0x9B4C);
KH1_OFFSET(D_00009B50, 0x9B50);
KH1_OFFSET(D_00009B54, 0x9B54);
KH1_OFFSET(D_00009B58, 0x9B58);
KH1_OFFSET(D_00009B5C, 0x9B5C);
KH1_OFFSET(D_00009B60, 0x9B60);
KH1_OFFSET(D_00009C00, 0x9C00);
KH1_OFFSET(D_0000AC20, 0xAC20);

/* GS PMODE (0x12000000): src/screen/fade.c's func_00113ab0 writes 0x22 there.  A plain word
 * off the EE until gs.h takes the write (the renderer's final pass reads PMODE). */
u64 D_12000000;
