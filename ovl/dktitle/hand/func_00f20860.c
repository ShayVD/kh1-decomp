/* dktitle.x func_00f20860: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 size; u16 off; } Hdr;
extern void func_00f206c8(u8 *, u8 *, s32, s32, s32, s32, s32);
extern u8 D_009A0000[];
static inline Hdr *hdr(u8 *p) { return (Hdr *)(p + 16); }
void func_00f20860(void) { Hdr *h = hdr(D_009A0000); u8 *a = (u8 *)h + h->off; func_00f206c8(a, a + h->size, 11776, 512, 384, 4, 12800); }
