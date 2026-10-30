/* Round 61 (wwm2): score 52 -> 40 (800 vs 800 bytes). Both IPU_CTRL updates go through the spare local m (m = IPU_CTRL | 0x40000000; IPU_CTRL = m + base;), which fixes the closing update's registers and the prologue's v1 sum. Left: the prologue registers (the target has h in a0, bE/b9 in a2 and the IPU_CTRL address in a1) and k = 0 scheduled after the f3DD90 + 16 add. Tried: k = 0 and n = -1 moved, base term orders, a bF temp. */
/* Round 58 (wwm2): score 70 -> 52 (800 vs 800 bytes). The "dead reload" of size after the first IPU wait is func_00f269c0's second argument: it is called with the advanced f3DD90 and size, as in the sibling func_00f25978; the bF terms of base are summed (bF >> 1) << 16 first. Left: the prologue registers (the target has h in a0 and the IPU_CTRL address in a1) and the closing IPU_CTRL update (the target loads into a0 with 0x40000000 in a1; ours ties the load to the or). Tail forms tried without change: base + (...), a temp before or after the or, a u32 cast, the constant first. Earlier header below. */
/* dkmovie.x func_00f25658: near miss (session 141), 800 vs 800 bytes, 46 words differ, score 72 (m2c draft was 236). IPU decode task. Keys: off as n * 768 giv (n starts -1, n++ at loop top), k == 0 ? 0x2C000000 : 0x28000000 (gives bnezl), cont = !(CTRL>>14&1) && !(CTRL>>15&1). Left: the original has a dead reload lw a1,0(sp) of size after the first IPU wait loop (ours has no such insn, so a nop shifts), the 0x10002010 pointer is a1 (ours a2) and the header pointer a0 (ours a1), and the bF bit terms are computed andi-first. Tried: volatile size, base term orders, if/else for the CMD value. Round 21 (wwm1): score 72 -> 70 with the dependency-checked reorderer (w3.py, from wwm2 r35 hill3). */
typedef struct { s32 f0; u8 pad4[5]; u8 b9; u8 padA[4]; u8 bE; u8 bF; } MvHdr;
typedef struct {
    u8 pad[0x3DD08];
    u8 *f3DD08;
    u8 pad3DD0C[0x84];
    MvHdr *f3DD90;
} MovieWork;
extern MovieWork *D_00F28460;
extern u8 *D_00F28464;
void func_00f269c0(MvHdr *, s32);
void func_00f26a20(u8 *, s32);
void func_00f26af0(u8 *, u8 *, s32);
void func_00f26848(s32, s32, s32, s32);

#define IPU_CMD (*(volatile s32 *)0x10002000)
#define IPU_CTRL (*(volatile s32 *)0x10002010)
#define D4_CHCR (*(volatile u32 *)0x1000B400)
#define D3_CHCR (*(volatile u32 *)0x1000B000)
#define D1_CHCR (*(volatile u32 *)0x1000D000)

s32 func_00f25658(void) {
    MvHdr *h;
    u8 f;
    s32 size;
    s32 base;
    u8 b9;
    s32 off, n, k, cont, m;

    h = D_00F28460->f3DD90;
    base = ((h->bF >> 1) << 16) + ((h->bF & 1) << 22);
    size = h->f0;
    b9 = h->b9;
    base = (h->bE << 20) + base;
    IPU_CTRL = base + 0x1200000;
    m = IPU_CTRL | 0x40000000;
    IPU_CTRL = m + base;
    while (IPU_CTRL < 0) {
    }
    n = -1;
    D_00F28460->f3DD90 = (MvHdr *)((u8 *)D_00F28460->f3DD90 + 16);
    k = 0;
    func_00f269c0(D_00F28460->f3DD90, size);
    do {
        IPU_CMD = 0x30000000;
        n++;
        while (IPU_CTRL < 0) {
        }
        func_00f26a20(D_00F28464 + 112, 768);
        IPU_CTRL = base + 0x1200000;
        IPU_CMD = (b9 << 16) | (k == 0 ? 0x2C000000 : 0x28000000);
        k++;
        while (IPU_CTRL < 0) {
        }
        while ((D3_CHCR >> 8) & 1) {
        }
        func_00f26af0(D_00F28460->f3DD08 + n * 768, D_00F28464 + 112, 768);
        while ((D1_CHCR >> 8) & 1) {
        }
        func_00f26848(n, 0, 0, 2);
        while ((D1_CHCR >> 8) & 1) {
        }
        cont = !(((u32)IPU_CTRL >> 14) & 1) && !(((u32)IPU_CTRL >> 15) & 1);
    } while (cont);
    D4_CHCR = 0;
    m = IPU_CTRL | 0x40000000;
    IPU_CTRL = m + base;
    while (IPU_CTRL < 0) {
    }
    while ((D4_CHCR >> 8) & 1) {
    }
    D_00F28460->f3DD90 = (MvHdr *)((u8 *)D_00F28460->f3DD90 + size);
    return 0;
}
