/* The image transfers between GS memory and main memory on the null platform (session 101,
 * docs/vita-port-plan.md 5.1an "The image transfers from GS memory to main memory"):
 * PlatGsSetDefLoadImage / PlatGsExecLoadImage (main memory -> GS, an upload) and
 * PlatGsSetDefStoreImage / PlatGsExecStoreImage (GS -> main memory, the captures, the lens flare's
 * Z read, the menu backdrop's two pixels).
 *
 * The SetDef calls fill the packet the way libgraph does (sceGsLoadImage 0x60 bytes: the A+D GIF tag,
 * BITBLTBUF, TRXPOS, TRXREG, TRXDIR, the IMAGE tag; sceGsStoreImage 0x70 bytes: 4 VIF codes, the
 * A+D tag, BITBLTBUF, TRXPOS, TRXREG, FINISH, TRXDIR), so a packet the game keeps in data reads the
 * same.  The Exec calls read the registers back from it:
 *
 * - a load is an upload into host/null/gsmem.c's model (TRXDIR 0 and the pixels as IMAGE data, so it
 *   counts and logs like a GIF path one), only while KH1_HOST_TRACE >= 2 feeds the model;
 * - a store copies the rectangle out of the model in the PS2's packed format (CT32 / Z32 4 bytes a
 *   pixel, CT24 / Z24 3, CT16 / Z16 2, T8 1, T4 a nibble, rows w pixels apart, nothing between
 *   them), whatever the view: the null platform keeps the PS2's GS memory, so under KH1_HOST_WIDE
 *   the target is still 512 x 384 and main memory gets 5.1an's shapes (0x90000 bytes, 0x600 a row;
 *   0x24000 for 0x3600).  A port's store resamples its own buffer into the same shape;
 * - session 102: a Z format's pixel whose page the draws wrote (gsmem.c marks draws, it does not
 *   rasterise them) reads 0, the farthest depth: the lens flare (kelnscls.nostrict.c func_00192958
 *   counts the pixels under the light's Z) then sees itself all visible, not a stale upload's bytes.
 *   A Z buffer the model does hold (an upload or a copy into the Z area since, e.g. the stored frame
 *   loaded back, renderer-spec 4.17) still reads its bytes, as the PS2 would.
 *
 * tests/host/gsimage_test.c checks both on made-up pixels. */
#include "common.h"
#include "gsmem.h"
#include "gsqueue.h"

extern int kh1_host_trace;

/* the GIF register numbers */
#define R_BITBLTBUF 0x50
#define R_TRXPOS 0x51
#define R_TRXREG 0x52
#define R_TRXDIR 0x53
#define R_FINISH 0x61

static void reg(u32 *q, u32 lo, u32 hi, u32 addr) { q[0] = lo; q[1] = hi; q[2] = addr; q[3] = 0; }

static void def_image(u32 *q, u32 bitbltbuf_hi, short x, short y, short w, short h, int store) {
    reg(q, 0, (u32)bitbltbuf_hi, R_BITBLTBUF);
    if (store) { q[0] = q[1]; q[1] = 0; } /* the source half: SBP, SBW, SPSM */
    reg(q + 4, store ? ((u32)x & 2047) | ((u32)y & 2047) << 16 : 0,
        store ? 0 : ((u32)x & 2047) | ((u32)y & 2047) << 16, R_TRXPOS);
    reg(q + 8, (u32)w & 0xFFF, (u32)h & 0xFFF, R_TRXREG);
}

static u32 bitblt(short bp, short bw, short psm) {
    return ((u32)bp & 0x3FFF) | ((u32)bw & 63) << 16 | ((u32)psm & 63) << 24;
}

int PlatGsSetDefLoadImage(void *lp, short dbp, short dbw, short psm, short x, short y, short w, short h) {
    u32 *q = (u32 *)lp;
    q[0] = 4 | 1u << 15; q[1] = 1u << 28; q[2] = 0xE; q[3] = 0; /* NLOOP 4 EOP, A+D */
    def_image(q + 4, bitblt(dbp, dbw, psm), x, y, w, h, 0);
    reg(q + 16, 0, 0, R_TRXDIR);                                /* host -> local */
    q[20] = 0; q[21] = 2u << 26; q[22] = 0; q[23] = 0;          /* IMAGE, NLOOP from the size at Exec */
    return 0;
}

int PlatGsSetDefStoreImage(void *sp, short sbp, short sbw, short psm, short x, short y, short w, short h) {
    u32 *q = (u32 *)sp;
    q[0] = q[1] = q[2] = q[3] = 0;                              /* the VIF codes (FLUSHA, DIRECT) */
    q[4] = 5 | 1u << 15; q[5] = 1u << 28; q[6] = 0xE; q[7] = 0;
    def_image(q + 8, bitblt(sbp, sbw, psm), x, y, w, h, 1);
    reg(q + 20, 0, 0, R_FINISH);
    reg(q + 24, 1, 0, R_TRXDIR);                                /* local -> host */
    return 0;
}

/* a pixel's bytes in main memory (0: 4 bits) */
static u32 psm_size(u32 psm) {
    switch (psm) {
    case KH1_PSMCT32: case KH1_PSMZ32: return 4;
    case KH1_PSMCT24: case KH1_PSMZ24: return 3;
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S: return 2;
    case KH1_PSMT8: case KH1_PSMT8H: return 1;
    default: return 0;
    }
}

/* the upload itself: BITBLTBUF's upper word bb, TRXPOS and TRXREG, then the bytes */
static void load_image(u32 bb, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi, const u8 *s, u32 bytes) {
    u32 done = 0, buf[64];
    kh1_gsmem_trxdir(0, 0, bb, pos_lo, pos_hi, reg_lo, reg_hi);
    if (kh1_gsmem_image_same(s, bytes)) return; /* session 137: the title menus' every-frame uploads */
    while (done < bytes) { /* in words, as the IMAGE qwords bring it (src need not be aligned) */
        u32 k = bytes - done < sizeof buf ? bytes - done : sizeof buf, i;
        for (i = 0; i < (k + 3) / 4; i++) buf[i] = 0;
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        __builtin_memcpy(buf, s + done, k); /* session 135: the same words, without a shift a byte */
#else
        for (i = 0; i < k; i++) buf[i >> 2] |= (u32)s[done + i] << (i & 3) * 8;
#endif
        kh1_gsmem_image(buf, (k + 3) / 4);
        done += k;
    }
    kh1_gsmem_image_kept(s, bytes);
}

static void w_load(const u32 *a, const u32 *d, u32 nqw) {
    (void)nqw;
    load_image(a[0], a[1], a[2], a[3], a[4], (const u8 *)d, a[5]);
}

int PlatGsExecLoadImage(void *lp, void *src) {
    const u32 *q = (const u32 *)lp;
    u32 bb = q[5], w = q[12] & 0xFFF, h = q[13] & 0xFFF, n = psm_size(bb >> 24 & 63), a[6];
    if (kh1_host_trace < 2) return 0;
    /* session 141: the bytes copied for the GS side's worker (gsqueue.h), in order with the sends */
    a[0] = bb;
    a[1] = q[8];
    a[2] = q[9];
    a[3] = q[12];
    a[4] = q[13];
    a[5] = n ? w * h * n : (w * h + 1) / 2;
    kh1_gsq_put_bytes(w_load, a, 6, src, a[5]);
    return 0;
}

int PlatGsExecStoreImage(void *sp, void *dst) {
    const u32 *q = (const u32 *)sp;
    u32 bb = q[8], sbp = bb & 0x3FFF, sbw = bb >> 16 & 63, psm = bb >> 24 & 63;
    u32 sx = q[12] & 2047, sy = q[12] >> 16 & 2047, w = q[16] & 0xFFF, h = q[17] & 0xFFF;
    u32 n = psm_size(psm), x, y, i;
    u8 *d = (u8 *)dst;
    kh1_gsq_sync(); /* session 141: every send before it drawn into the model */
    if (kh1_gsmem_addr(psm, 0, 1, 0, 0) == ~0u) return 0; /* a PSM the model does not have */
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            u32 v = kh1_gsmem_read_pixel(psm, sbp, sbw, sx + x, sy + y);
            if ((psm & 0x30) == 0x30 && kh1_gsmem_drawn(psm, sbp, sbw, sx + x, sy + y))
                v = 0; /* depth the draws wrote: the model has none, so the farthest (session 102) */
            if (!n) { /* 4 bits a pixel, the low nibble first */
                u32 k = y * w + x;
                d[k >> 1] = (u8)(k & 1 ? (d[k >> 1] & 15) | (v & 15) << 4 : (d[k >> 1] & 0xF0) | (v & 15));
                continue;
            }
            for (i = 0; i < n; i++) *d++ = (u8)(v >> i * 8);
        }
    return 0;
}
