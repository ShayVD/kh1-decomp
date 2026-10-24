#include "common.h"

#include "data/types/nostrict_text_00140000_s6_07.h"
Nea98 *D_00551D80 ALIGNED(16);
volatile s32 D_00559DB8 ALIGNED(8);
volatile s32 D_00559DBC ALIGNED(4);

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;
typedef struct DmaTag {
    u16 qwc;
    u8 mark;
    u8 id;
    struct DmaTag *next;
    u32 p[2];
} DmaTag;

static inline void setTag(DmaTag *t, s32 qwc, s32 id, DmaTag *next) {
    t->id = id;
    t->next = next;
    t->qwc = qwc;
}
static inline void setGif(GifTag *g, s32 nloop, s32 nreg) {
    *(u128 *)g = 0;
    g->NLOOP = nloop;
    g->EOP = 1;
    g->NREG = nreg;
}
#include "data/bss_0055_typed.h"
#include "data/data_0035.h"
