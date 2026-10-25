/* host/null/dmawalk.c on made-up chains (no game data): tests/selftest.sh builds it with
 * gcc -m32 when that works.  Each case is a chain, the channel and the problem bits the walk
 * must answer. */
#include "common.h"
#include "../../host/null/dmawalk.h"

int printf(const char *, ...);

int kh1_host_trace = 2;

static u32 mem[64][4] ALIGNED(16);

static const char *where(u32 a, u32 n) {
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

#define A(i) ((u32)(unsigned long)mem[i])
static void q(int i, u32 a, u32 b, u32 c, u32 d) { mem[i][0] = a; mem[i][1] = b; mem[i][2] = c; mem[i][3] = d; }
/* a GIFtag: NLOOP, EOP, FLG, NREG */
static void gt(int i, u32 nloop, u32 eop, u32 flg, u32 nreg) {
    q(i, nloop | eop << 15, flg << 26 | nreg << 28, 0, 0);
}

static int fails;
static void expect(const char *name, int ch, u32 chcr, int tag, int want) {
    int got = kh1_dma_walk(ch, chcr, A(tag), where);
    if (got != want) { printf("dmawalk_test: %s: got %#x, want %#x\n", name, got, want); fails++; }
}

int main(void) {
    int i;
    /* GIF: cnt with a PACKED packet (1 x 4 regs), end */
    for (i = 0; i < 64; i++) q(i, 0, 0, 0, 0);
    q(0, 0x10000005, 0, 0, 0);
    gt(1, 1, 1, 0, 4);
    q(6, 0x70000000, 0, 0, 0);
    expect("gif packed", 2, 0x104, 0, 0);
    /* the same packet one qword short */
    q(0, 0x10000004, 0, 0, 0);
    q(5, 0x70000000, 0, 0, 0);
    expect("gif short", 2, 0x104, 0, KH1_DMA_GIF_SHORT);
    /* an IMAGE GIFtag in a cnt, its 3 qwords by ref (a block inside the packet), refe 0 */
    q(0, 0x10000001, 0, 0, 0);
    gt(1, 3, 1, 2, 0);
    q(2, 0x30000003, A(10), 0, 0);
    q(3, 0x00000000, 0, 0, 0);
    expect("gif image ref", 2, 0x104, 0, 0);
    /* REGLIST: 3 x 3 regs = 9 64-bit words = 5 qwords */
    q(0, 0x70000006, 0, 0, 0);
    gt(1, 3, 1, 1, 3);
    expect("gif reglist", 2, 0x104, 0, 0);
    q(0, 0x70000005, 0, 0, 0);
    expect("gif reglist short", 2, 0x104, 0, KH1_DMA_GIF_SHORT);
    /* NREG 0 = 16: 1 loop of 16 qwords */
    q(0, 0x70000011, 0, 0, 0);
    gt(1, 1, 1, 0, 0);
    expect("gif nreg 16", 2, 0x104, 0, 0);
    /* data outside, no end */
    q(0, 0x30000001, 0x10, 0, 0);
    expect("ref outside", 2, 0x104, 0, KH1_DMA_DATA_OUTSIDE);
    q(0, 0x20000000, A(0), 0, 0);
    expect("next loop", 2, 0x104, 0, KH1_DMA_NO_END);

    /* VIF1 with TTE: tag upper words NOP, DIRECT 2; then the GIF packet as the DIRECT data */
    for (i = 0; i < 64; i++) q(i, 0, 0, 0, 0);
    q(0, 0x70000002, 0, 0x00000000, 0x50000002);
    expect("vif direct", 1, 0x145, 0, 0);
    q(0, 0x70000001, 0, 0x00000000, 0x50000002);
    expect("vif direct short", 1, 0x145, 0, KH1_DMA_VIF_SHORT);
    /* PATH2: DIRECT 3 holding a GIFtag of 1 x 2 regs (A+D, A+D) and its 2 qwords */
    q(0, 0x70000004, 0, 0x00000000, 0x50000003);
    gt(1, 1, 1, 0, 2);
    mem[1][2] = 0xEE;
    q(2, 0, 0, 0x4C, 0);
    q(3, 0, 0, 0x47, 0);
    q(4, 0, 0, 0, 0);
    expect("vif direct path2", 1, 0x145, 0, 0);
    /* the same DIRECT one qword short of the packet: the VIF stream is whole, PATH2 is not */
    q(0, 0x70000003, 0, 0x00000000, 0x50000002);
    expect("vif direct path2 short", 1, 0x145, 0, KH1_DMA_PATH2_SHORT);
    for (i = 0; i < 64; i++) q(i, 0, 0, 0, 0);
    /* without TTE: STCYCL 1,1; UNPACK V4-32 num 2 (8 words); MSCAL; NOP */
    q(0, 0x70000003, 0, 0, 0);
    q(1, 0x01000101, 0x6C020000, 0, 0);
    q(2, 0, 0, 0, 0);
    q(3, 0, 0, 0x14000000, 0x00000000);
    expect("vif unpack", 1, 0x105, 0, 0);
    /* UNPACK V3-16 num 3: 3 x 48 bits = 5 words; STCYCL 1,2 (WL 2 > CL 1): V4-32 num 4 reads 2
     * vectors, 8 words */
    q(1, 0x01000101, 0x69030000, 0, 0);
    q(2, 0, 0, 0, 0x01000201);
    q(3, 0x6C040000, 0, 0, 0);
    q(4, 0, 0, 0, 0);
    q(5, 0, 0, 0, 0);
    q(0, 0x70000005, 0, 0, 0);
    expect("vif unpack sizes", 1, 0x105, 0, 0);
    /* MPG 1 at word 0: one pad word to 64-bit alignment, then its 2 words */
    q(0, 0x70000001, 0, 0, 0);
    q(1, 0x4A010000, 0, 0, 0);
    expect("vif mpg", 1, 0x105, 0, 0);
    /* 0x6B: vl 3 (5 bits) with vn 2, no code */
    q(1, 0, 0x6B010000, 0, 0);
    expect("vif bad", 1, 0x105, 0, KH1_DMA_VIF_BAD);
    if (fails) { printf("dmawalk_test: %d failed\n", fails); return 1; }
    printf("dmawalk_test: PASS\n");
    return 0;
}
