/* host/null/gsimage.c, the null platform's image loads and stores (session 101, vita-port-plan 5.1an's
 * contract), on made-up pixels in the GS memory model (no game data): tests/selftest.sh builds it with
 * gcc -m32 when that works.  Under a wide view (kh1_gs_view, KH1_HOST_WIDE's margin) every store must
 * still hand main memory the PS2's shapes: the target 512 x 384 CT24 is 0x90000 bytes, 0x600 a row;
 * the capture at 0x3600 256 x 192 is 0x24000; and a load of the same bytes puts the pixels back. */
#include "common.h"
#include "platform/gs.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

int kh1_host_trace = 2;

#define GUARD 0x5A
static u8 buf[0x90000 + 64];
static u32 pk[28];      /* a sceGsStoreImage's 0x70 bytes */
static u32 lpk[24 + 4]; /* a sceGsLoadImage's 0x60, and a guard */

static int checks, fails;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("gsimage_test: %s\n", name); fails++; } } while (0)

static u32 pat(u32 x, u32 y, u32 salt) { return (x * 0x9E37u ^ y * 0x7F4Au ^ salt) & 0xFFFFFF; }

static void fill(u32 psm, u32 bp, u32 bw, u32 w, u32 h, u32 salt) {
    u32 x, y;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) kh1_gsmem_write_pixel(psm, bp, bw, x, y, pat(x, y, salt));
}

/* stores w x h at block bp into buf; returns the bytes written (the first guard byte left) */
static u32 store(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 w, u32 h) {
    u32 n = 0;
    memset(buf, GUARD, sizeof buf);
    memset(pk, 0xEE, sizeof pk);
    PlatGsSetDefStoreImage(pk, (short)bp, (short)bw, (short)psm, (short)x, (short)y, (short)w, (short)h);
    PlatGsExecStoreImage(pk, buf);
    for (n = sizeof buf; n && buf[n - 1] == GUARD; n--) {}
    return n;
}

int main(void) {
    u32 x, y, n, ok;

    kh1_gs_reset();
    kh1_gs_view(-1325, 10842); /* the Vita's 960:544: canvas -82.8 .. 594.8 (KH1_HOST_WIDE=1) */

    /* the packets' shape: libgraph's, so a packet the game keeps in data reads the same */
    memset(pk, 0xEE, sizeof pk);
    PlatGsSetDefStoreImage(pk, 0x1A00, 8, KH1_PSMCT24, 0, 0, 512, 384);
    CHECK("store packet: A+D tag NLOOP 5", (pk[4] & 0x7FFF) == 5 && pk[6] == 0xE);
    CHECK("store packet: BITBLTBUF source", pk[8] == (0x1A00 | 8 << 16 | KH1_PSMCT24 << 24) && pk[9] == 0 && pk[10] == 0x50);
    CHECK("store packet: TRXREG", pk[16] == 512 && pk[17] == 384 && pk[18] == 0x52);
    CHECK("store packet: TRXDIR 1 last, in 0x70 bytes", pk[24] == 1 && pk[26] == 0x53);
    memset(lpk, 0xEE, sizeof lpk);
    PlatGsSetDefLoadImage(lpk, 0xE00, 8, KH1_PSMCT24, 0, 0, 512, 192);
    CHECK("load packet: BITBLTBUF destination", lpk[4] == 0 && lpk[5] == (0xE00 | 8 << 16 | KH1_PSMCT24 << 24));
    CHECK("load packet: TRXDIR 0, IMAGE tag, 0x60 bytes", lpk[16] == 0 && lpk[18] == 0x53 && lpk[21] >> 26 == 2 &&
                                                         lpk[24] == 0xEEEEEEEE);

    /* capture.c func_00109d98: the target 0x1A00, FBW 8, CT24, 512 x 384 -> D_00F20000 */
    fill(KH1_PSMCT32, 0x1A00, 8, 512, 384, 0xA00000); /* the top byte must not reach main memory */
    for (y = 0; y < 384; y++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1A00, 8, 0, y, pat(0, y, 0xA00000) | 0x80000000u);
    n = store(KH1_PSMCT24, 0x1A00, 8, 0, 0, 512, 384);
    CHECK("target: 0x90000 bytes", n == 0x90000);
    for (ok = 1, y = 0; y < 384; y++)
        for (x = 0; x < 512; x += 7) {
            const u8 *p = buf + y * 0x600 + x * 3;
            ok &= (u32)(p[0] | p[1] << 8 | p[2] << 16) == pat(x, y, 0xA00000);
        }
    CHECK("target: 0x600 a row, 3 bytes a pixel, RGB without the alpha byte", ok);

    /* the stored frame back into the Z area as two 512 x 192 halves (func_00109cd0), read as CT24 */
    PlatGsSetDefLoadImage(lpk, 0xE00, 8, KH1_PSMCT24, 0, 0, 512, 192);
    PlatGsExecLoadImage(lpk, buf);
    PlatGsSetDefLoadImage(lpk, 0x1400, 8, KH1_PSMCT24, 0, 0, 512, 192);
    PlatGsExecLoadImage(lpk, buf + 0x48000);
    for (ok = 1, y = 0; y < 384; y += 3)
        for (x = 0; x < 512; x += 5)
            ok &= kh1_gsmem_read_pixel(KH1_PSMCT24, y < 192 ? 0xE00 : 0x1400, 8, x, y % 192) == pat(x, y, 0xA00000);
    CHECK("the halves loaded back: the same pixels", ok && kh1_gsmem_stats()->extra == 0);

    /* an odd source address (the load copies through words) */
    PlatGsSetDefLoadImage(lpk, 0x3A00, 1, KH1_PSMCT24, 0, 0, 16, 16);
    PlatGsExecLoadImage(lpk, buf + 1);
    ok = kh1_gsmem_read_pixel(KH1_PSMCT24, 0x3A00, 1, 0, 0) == (u32)(buf[1] | buf[2] << 8 | buf[3] << 16) &&
         kh1_gsmem_read_pixel(KH1_PSMCT24, 0x3A00, 1, 15, 15) == (u32)(buf[766] | buf[767] << 8 | buf[768] << 16);
    CHECK("load from an unaligned source", ok);

    /* capture.c func_0010a3e8: the half-size capture 0x3600, FBW 4, 256 x 192 -> 0x24000 bytes */
    fill(KH1_PSMCT24, 0x3600, 4, 256, 192, 0x330000);
    n = store(KH1_PSMCT24, 0x3600, 4, 0, 0, 256, 192);
    CHECK("capture: 0x24000 bytes", n == 0x24000);
    CHECK("capture: 0x300 a row", (u32)(buf[191 * 0x300 + 255 * 3] | buf[191 * 0x300 + 255 * 3 + 1] << 8 |
                                        buf[191 * 0x300 + 255 * 3 + 2] << 16) == pat(255, 191, 0x330000));

    /* kelnscls: the Z buffer, PSMZ24, a box at (100, 60) 24 x 8 -> 3 bytes a pixel, w8 a row */
    fill(KH1_PSMZ24, 0x0E00, 8, 512, 128, 0x123000);
    n = store(KH1_PSMZ24, 0x0E00, 8, 100, 60, 24, 8);
    CHECK("Z24 box: 24 x 8 x 3 bytes", n == 24 * 8 * 3);
    CHECK("Z24 box: the rectangle's own pixels", (u32)(buf[(7 * 24 + 23) * 3] | buf[(7 * 24 + 23) * 3 + 1] << 8 |
                                                       buf[(7 * 24 + 23) * 3 + 2] << 16) == pat(123, 67, 0x123000));

    /* session 102: once a draw has gone through that Z buffer (ZTE on, ZMSK off) the model holds no
     * depth there: the box reads 0, so the flare's count (z < the light's) sees every pixel */
    kh1_gsmem_draw(0xD0 | 8 << 16, 0, 0x70 | 1 << 24, 0, 511 << 16, 383 << 16, 1 << 16);
    CHECK("Z24 drawn: the page is a draw's", kh1_gsmem_drawn(KH1_PSMZ24, 0x0E00, 8, 100, 60));
    n = store(KH1_PSMZ24, 0x0E00, 8, 100, 60, 24, 8);
    for (ok = n == 24 * 8 * 3, x = 0; x < n; x++) ok &= buf[x] == 0;
    CHECK("Z24 drawn: the box reads 0, the farthest", ok);
    kh1_gsmem_write_pixel(KH1_PSMZ24, 0x0E00, 8, 100, 60, 0x654321);
    n = store(KH1_PSMZ24, 0x0E00, 8, 100, 60, 24, 8);
    /* a write gives its page (64 x 32) back to the model: rows 60-63 are the model's, 64-67 still a draw's */
    CHECK("Z24 written after the draw: the model's bytes again, by page", n == 24 * 8 * 3 &&
          (u32)(buf[0] | buf[1] << 8 | buf[2] << 16) == 0x654321 &&
          (u32)(buf[(3 * 24 + 23) * 3] | buf[(3 * 24 + 23) * 3 + 1] << 8 | buf[(3 * 24 + 23) * 3 + 2] << 16) == pat(123, 63, 0x123000) &&
          (u32)(buf[(4 * 24) * 3] | buf[(4 * 24) * 3 + 1] << 8 | buf[(4 * 24) * 3 + 2] << 16) == 0);
    /* a colour target the draws wrote keeps the model's bytes (the flat and textured sprites are drawn) */
    CHECK("CT24 of a drawn page: not zeroed", kh1_gsmem_read_pixel(KH1_PSMCT24, 0x1A00, 8, 5, 5) == pat(5, 5, 0xA00000));

    /* menubg func_0020a8f0: the display, CT32, 16 x 1 at (256, 4) */
    fill(KH1_PSMCT32, 0, 8, 512, 8, 0x456000);
    n = store(KH1_PSMCT32, 0, 8, 256, 4, 16, 1);
    CHECK("display: 16 CT32 pixels", n == 64 && (u32)(buf[0] | buf[1] << 8 | buf[2] << 16) == pat(256, 4, 0x456000));

    /* the same with the 4:3 view: the shapes do not depend on it */
    kh1_gs_view(0, 8192);
    n = store(KH1_PSMCT24, 0x1A00, 8, 0, 0, 512, 384);
    CHECK("target under 4:3: 0x90000 bytes", n == 0x90000);

    /* without KH1_HOST_TRACE >= 2 the model is not fed: a load does nothing */
    kh1_host_trace = 0;
    memset(buf, 0, 768);
    PlatGsSetDefLoadImage(lpk, 0x3A00, 1, KH1_PSMCT24, 0, 0, 16, 16);
    PlatGsExecLoadImage(lpk, buf);
    CHECK("no trace: the model untouched", kh1_gsmem_read_pixel(KH1_PSMCT24, 0x3A00, 1, 0, 0) != 0);

    if (fails) { printf("gsimage_test: %d of %d failed\n", fails, checks); return 1; }
    printf("gsimage_test: PASS (%d checks)\n", checks);
    return 0;
}
