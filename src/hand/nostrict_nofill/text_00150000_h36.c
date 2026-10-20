/* Hand-matched functions near 0x162500 (worker 36): no strict aliasing,
 * delay slots left to the assembler (short-loop nops). */
#include "common.h"

typedef struct { u32 dir:1; u32 b1:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 rest:24; } DmaChcr;
typedef struct { u16 h0; s16 h2; } TaskReg;
typedef struct { u32 w0; u8 pad[396]; } E56A0F0;

extern DmaChcr *D_0055C644;
extern DmaChcr *D_0055C640;
extern E56A0F0 D_0056A0F0[];
extern u32 D_005739F8[]; /* src/data/bss_0057.c: s32 D_005739F8[0x32] */
extern u8 D_0055C698[];

DmaChcr *func_00266c08(s32);
void func_0015f128(void);
void *memset(void *, s32, u32);
TaskReg *func_0011ef10(s32, void *);
s32 func_00160370();

void func_00162500(void) {
    s32 i;
    D_0055C644 = func_00266c08(2);
    D_0055C640 = func_00266c08(1);
    func_0015f128();
    for (i = 0; i < 96; i++) D_0056A0F0[i].w0 = 0;
    for (i = 0; i < 40; i++) D_005739F8[i] = 0;
    memset(D_0055C698, 0, 0xDA58);
    func_0011ef10(0x2E630, func_00160370)->h2 = -1;
}
#include "data/bss_0055_mixed.h"
