/* The other readers of a GS store (session 104, docs/vita-port-plan.md 5.1ar), the way flare_test
 * does the lens flare: tests/selftest.sh links the game's own C (src/menu/menubg.c, src/screen/capture.c,
 * src/gfx/sceneeff.c, src/screen/screen.c, with --gc-sections so only the functions below and what
 * they reach need their callees) with the null platform's host/null/gsimage.c / gsmem.c under gcc -m32,
 * and runs each on made-up pixels:
 * - menubg.c func_0020a8f0, the menu backdrop's two colours: a 16 x 1 CT32 store of the frame at
 *   FBP 0, FBW 8, x 256 (the 4:3 centre), y 4 and y 443 (the top and bottom), the first pixel kept
 *   without its alpha byte in D_003F34B0[0] / [1];
 * - capture.c func_0010a3e8, the half-size capture: the 256 x 192 CT24 store of block 0x3600 (FBW 4)
 *   into func_00121e28's 0x24000 bytes, D_002B6778;
 * - sceneeff.c func_00102a48, the menu blur: loads D_002B6778 back (capture.c func_0010a470) and scans
 *   its 0x9000 words; any nonzero word sends the blur D_002A4B60, an all-zero one the empty pass
 *   D_002A4DD0;
 * - screen.c func_001e1480, vm_lib's capture: the 512 x 384 CT24 store of the target 0x1A00 into
 *   D_00F20000, 0x90000 bytes.
 * Each from a frame an upload left (the model holds it), one only the draws wrote (it does not: the
 * null platform reads what was there before, zeros after a reset), one a flat sprite filled for the
 * present (kh1_gsmem_flat(1), KH1_HOST_SHOT), and the wide view (KH1_HOST_WIDE), which none of them
 * sees: the null platform keeps the PS2's GS memory.
 * Session 105: the menu capture's copy itself (a made-up packet with D_002B6760's registers) sent
 * through the GIF path (dmawalk.c -> gsregs.c -> gsmem.c), with and without the present's fill. */
#include "common.h"
#include "platform/gs.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "../../host/null/dmawalk.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

int kh1_host_trace = 2; /* the model takes loads from 2 on */
s32 kh1_view_side16;    /* host/port/view.c's margin, set with kh1_gs_view below */

/* the data and callees the four functions name */
#define GUARD 0x5A
u32 D_003F34B0[2];
u8 D_00F20000[0x90000 + 64] __attribute__((aligned(16)));
u8 D_002BC1B0[0x60] __attribute__((aligned(16))); /* capture.c's load packet */
u64 D_002A49A0[56] __attribute__((aligned(16)));  /* the blur's packet: colours and corners */
u8 D_002A4B60[16], D_002A4DD0[16];
u32 D_002B6760[4] __attribute__((aligned(16))); /* the menu capture's DMA tag: a refe of copy_pkt */
s32 D_002B6778; /* the half capture's buffer (a pointer kept in an s32, as on the PS2) */
void PlatFlushCache(int op) {}
int PlatGsSyncPath(int mode, unsigned short timeout) { return 0; }

static void *sent[8];
static int nsent, walk_copy;
static const char *where(u32 addr, u32 n) { return "test"; }
/* the send: recorded; with walk_copy, the menu capture's chain also goes through the GIF path
 * (host/null/dmawalk.c -> gsregs.c -> gsmem.c), as KH1_HOST_TRACE >= 2 sends it (session 105) */
void func_00106b18(void *pkt) {
    if (nsent < 8) sent[nsent] = pkt;
    nsent++;
    if (walk_copy && pkt == (void *)D_002B6760) kh1_dma_walk(2, 0x104, (u32)(unsigned long)pkt, where);
}

/* A made-up packet with the menu capture's registers (renderer-spec 4.17, session 105 item 4b):
 * one PACKED A+D tag for FRAME_1 (FBP 0x1B0 = block 0x3600, FBW 4, CT32), TEST_1 (ZTE, ZTST
 * ALWAYS), TEX1_1 (MMAG / MMIN bilinear), CLAMP_1 (CLAMP, CLAMP) and TEX0_1 (TBP0 0, TBW 8, CT32,
 * 512 x 512, TCC 1, MODULATE), then a REGLIST tag (EOP) for one SPRITE: PRIM TME FST, RGBAQ 0x80
 * each, UV (0, 0) at XYZ2 (0x7000, 0x7400), UV (512, 448) at XYZ2 (0x8000, 0x8000): the display
 * buffer, 512 x 448, drawn 256 x 192 into the half capture.  XYOFFSET_1 and SCISSOR_1 are what the
 * send finds in force. */
static u32 copy_pkt[40] __attribute__((aligned(16)));
static void copy_setup(void) {
    static const u32 q[40] = {
        0x00000001, 0x50000000, 0x000EEEEE, 0,  0x000401B0, 0, 0x4C, 0,
        0x00030000, 0, 0x47, 0,                0x00000060, 0, 0x14, 0,
        0x00000005, 0, 0x08, 0,                0x64020000, 0x80000006, 0x06, 0,
        0x00008001, 0x64000000, 0x00535310, 0, 0x00000116, 0, 0x80808080, 1,
        0, 0, 0x74007000, 0,                   0x1C002000, 0, 0x80008000, 0,
    };
    u32 i;
    for (i = 0; i < 40; i++) copy_pkt[i] = q[i];
    D_002B6760[0] = 10; /* refe (id 0), 10 qwords */
    D_002B6760[1] = (u32)(unsigned long)copy_pkt;
    D_002B6760[2] = D_002B6760[3] = 0;
}
/* the context the copy finds: XYOFFSET_1 (0x7000, 0x7400), SCISSOR_1 the frame's 512 x 448 */
static void copy_context(void) {
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x40, 511 << 16, 447 << 16);
}
static const KH1FullScreen copy_fs[1] = { { D_002B6760, KH1_FS_XS | KH1_FS_U, "menu capture" } };

/* the whole 4 MB, as 1024 x 1024 CT32 words */
static u32 snap[1024 * 1024];
static void take_snap(void) {
    u32 x, y;
    for (y = 0; y < 1024; y++)
        for (x = 0; x < 1024; x++) snap[y * 1024 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, 0, 16, x, y);
}
/* words changed since take_snap outside the half capture (block 0x3600, FBW 4, 256 x 192), and the
 * blocks they lie in */
static u32 out_b0, out_b1;
static u32 changed_outside(void) {
    static u8 inside[1024 * 1024];
    u32 x, y, n = 0;
    memset(inside, 0, sizeof inside);
    out_b0 = ~0u;
    out_b1 = 0;
    for (y = 0; y < 192; y++)
        for (x = 0; x < 256; x++) inside[kh1_gsmem_addr(KH1_PSMCT32, 0x3600, 4, x, y)] = 1;
    for (y = 0; y < 1024; y++)
        for (x = 0; x < 1024; x++)
            if (!inside[kh1_gsmem_addr(KH1_PSMCT32, 0, 16, x, y)] &&
                kh1_gsmem_read_pixel(KH1_PSMCT32, 0, 16, x, y) != snap[y * 1024 + x]) {
                u32 b = kh1_gsmem_addr(KH1_PSMCT32, 0, 16, x, y) / 64;
                if (b < out_b0) out_b0 = b;
                if (b > out_b1) out_b1 = b;
                n++;
            }
    return n;
}
/* the display buffer (block 0, FBW 8, 512 x 448) uploaded: pixel x of each row c(x) */
static u32 disp_px(u32 x, u32 y) { return 0x80000000u | (x < 256 ? 0x203040 : 0x605040) | (x & 0xFF) << 0; }
static void upload_display(int plain, u32 c) {
    u32 x, y;
    for (y = 0; y < 448; y++)
        for (x = 0; x < 512; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0, 8, x, y, plain ? c : disp_px(x, y));
}

static u8 half[0x24000 + 64] __attribute__((aligned(16)));
static s32 half_n;
void *func_00121e28(s32 n, void **owner) { half_n = n; return half; }

void func_0020a8f0(void);
void func_0010a3e8(void);
void func_00102a48(s32 c, s32 o);
void func_001e1480(void);

static int checks, fails;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("storeread_test: %s\n", name); fails++; } } while (0)

static void view(int wide) {
    kh1_view_side16 = wide ? 1325 : 0;
    kh1_gs_view(wide ? -1325 : 0, wide ? 10842 : 8192); /* 960:544: canvas -82.8 .. 594.8 */
}

/* a w x 1 CT32 row uploaded at (x, y) of the frame (FBP 0, FBW 8), every pixel c */
static void upload_row(u32 x, u32 y, u32 w, u32 c) {
    u32 lp[24], px[64], i;
    for (i = 0; i < w; i++) px[i] = c;
    PlatGsSetDefLoadImage(lp, 0, 8, KH1_PSMCT32, (short)x, (short)y, (short)w, 1);
    PlatGsExecLoadImage(lp, px);
}

/* the 3D pass's draw into a frame at block fbp (FBW fbw), its scissor w x h */
static void draw(u32 fbp, u32 fbw, u32 w, u32 h) {
    kh1_gsmem_draw(fbp / 32 | fbw << 16 | KH1_PSMCT32 << 24, 0, 0x70 | 1 << 24, 0, (w - 1) << 16, (h - 1) << 16, 0);
}

/* an untextured full-frame SPRITE of colour c filled for the present (a clear) */
static void flat_clear(u32 c) {
    KH1GsSprite s;
    memset(&s, 0, sizeof s);
    s.prim = 6;
    s.frame_lo = 0 | 8 << 16 | KH1_PSMCT32 << 24;
    s.xyoffset_lo = 0x7000;
    s.xyoffset_hi = 0x7400;
    s.scissor_lo = 511 << 16;
    s.scissor_hi = 447 << 16;
    s.xy[0] = 0x7000 | 0x7400u << 16;
    s.xy[1] = (0x7000 + 512 * 16) | (0x7400u + 448 * 16) << 16;
    s.rgba = c;
    draw(0, 8, 512, 448); /* the caller still marks the draw */
    kh1_gsmem_flat(1);
    kh1_gsmem_flat_sprite(&s);
    kh1_gsmem_flat(0);
}

/* the half capture's source, block 0x3600 FBW 4: every pixel c */
static void fill_half(u32 c) {
    u32 x, y;
    for (y = 0; y < 192; y++)
        for (x = 0; x < 256; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3600, 4, x, y, c);
}

/* runs the capture and the blur; returns the packet the blur sent */
static void *blur(void) {
    memset(half, GUARD, sizeof half);
    nsent = 0;
    func_0010a3e8();
    nsent = 0;
    func_00102a48(0x40, 0x10);
    return nsent == 1 ? sent[0] : 0;
}

static u32 used(const u8 *b, u32 size) {
    u32 n;
    for (n = size; n && b[n - 1] == GUARD; n--) {}
    return n;
}

int main(void) {
    u32 x, y, ok;
    int wide;

    /* menubg.c func_0020a8f0: the backdrop colours, in the 4:3 view and the wide one */
    for (wide = 0; wide < 2; wide++) {
        kh1_gs_reset();
        view(wide);
        upload_row(256, 4, 16, 0x80112233);
        upload_row(256, 443, 16, 0x80445566);
        upload_row(0, 4, 16, 0x80FFFFFF);   /* the 4:3 edge and the view's edge are not read */
        upload_row(240, 443, 16, 0x80FFFFFF);
        D_003F34B0[0] = D_003F34B0[1] = 0xDEADBEEF;
        func_0020a8f0();
        CHECK(wide ? "backdrop, wide: the top colour at x 256, y 4" : "backdrop: the top colour at x 256, y 4",
              D_003F34B0[0] == 0x112233);
        CHECK(wide ? "backdrop, wide: the bottom colour at y 443" : "backdrop: the bottom colour at y 443",
              D_003F34B0[1] == 0x445566);
    }
    /* a frame the draws wrote after that upload: the model still holds the upload's bytes */
    draw(0, 8, 512, 448);
    func_0020a8f0();
    CHECK("backdrop: a drawn frame reads the bytes from before the draw", D_003F34B0[0] == 0x112233);
    /* drawn only, since a reset: black */
    kh1_gs_reset();
    view(1);
    draw(0, 8, 512, 448);
    func_0020a8f0();
    CHECK("backdrop: a frame only the draws wrote reads black", D_003F34B0[0] == 0 && D_003F34B0[1] == 0);
    /* a clear filled for the present (KH1_HOST_SHOT): its colour */
    flat_clear(0x80203040);
    func_0020a8f0();
    CHECK("backdrop: a flat clear for the present reads its colour", D_003F34B0[0] == 0x203040 && D_003F34B0[1] == 0x203040);

    /* capture.c func_0010a3e8 and sceneeff.c func_00102a48: the half capture and the blur */
    for (wide = 0; wide < 2; wide++) {
        kh1_gs_reset();
        view(wide);
        for (y = 0; y < 192; y++)
            for (x = 0; x < 256; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3600, 4, x, y, 0x80000000u | (x * 0x10203u ^ y * 0x30201u));
        CHECK(wide ? "blur, wide: a captured frame sends the blur" : "blur: a captured frame sends the blur",
              blur() == D_002A4B60);
        CHECK(wide ? "half capture, wide: 0x24000 bytes asked and written" : "half capture: 0x24000 bytes asked and written",
              half_n == 0x24000 && used(half, sizeof half) == 0x24000 && D_002B6778 == (s32)half);
        for (ok = 1, y = 0; y < 192; y += 5)
            for (x = 0; x < 256; x += 3) {
                const u8 *p = half + y * 0x300 + x * 3;
                ok &= (u32)(p[0] | p[1] << 8 | p[2] << 16) == ((x * 0x10203u ^ y * 0x30201u) & 0xFFFFFF);
            }
        CHECK("half capture: 0x300 a row, RGB", ok);
        CHECK("blur: the opaque copy's colour", D_002A49A0[3] == (0x404040ull | 0x80ull << 24 | 0x100000000ull));
        CHECK(wide ? "blur, wide: the corners at the view's edges" : "blur: the corners at the PS2's 0x6fe0 / 0x8fe0",
              wide ? D_002A49A0[5] == ((u64)(0x7000 - 1325 - 0x20) | 0x73e0ull << 16 | 0x100000000ull) &&
                         D_002A49A0[7] == ((u64)(0x9000 + 1325 - 0x20) | 0x8be0ull << 16 | 0x100000000ull)
                   : D_002A49A0[11] == ((u64)(0x6fe0 - 0x10) | (0x73e0ull - 0x10) << 16 | 0x100000000ull));
    }
    /* black with the alpha byte set: the CT24 store drops it, so the capture is empty */
    kh1_gs_reset();
    fill_half(0x80000000u);
    CHECK("blur: a black capture (alpha only) sends the empty pass", blur() == D_002A4DD0);
    /* one pixel, the last one: the 0x9000 words reach the end of the 0x24000 bytes */
    kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3600, 4, 255, 191, 0x80010000u);
    CHECK("blur: the last pixel alone is enough", blur() == D_002A4B60);
    /* a half-size target only the draws wrote (the copy D_002B6760, which the model does not draw):
     * zeros, so on the null platform the menu opens with the empty pass, not the blur */
    kh1_gs_reset();
    view(1);
    draw(0x3600, 4, 256, 192);
    CHECK("blur: a capture only the draws wrote sends the empty pass on the host", blur() == D_002A4DD0);

    /* session 105 (item 4b): the copy itself through the GIF path.  Without kh1_gsmem_flat the model
     * only marks 0x3600 as drawn (the bilinear 512 x 512 texture is past kh1_gsmem_sprite), so a
     * frame the model holds still gives the empty pass; with it (KH1_HOST_SHOT's present) the copy is
     * point-sampled and the blur sees the frame, as the PS2 does */
    copy_setup();
    walk_copy = 1;
    kh1_gs_reset();
    copy_context();
    upload_display(0, 0);
    CHECK("copy, no present fill: the display's frame still gives the empty pass", blur() == D_002A4DD0);
    kh1_gs_reset();
    copy_context();
    upload_display(0, 0);
    kh1_gsmem_flat(1);
    take_snap();
    CHECK("copy, present fill: the blur sees the frame", blur() == D_002A4B60);
    kh1_gsmem_flat(0);
    CHECK("copy, present fill: the 4:3 copy writes only the half capture", changed_outside() == 0);
    for (ok = 1, y = 0; y < 192; y += 7)
        for (x = 0; x < 256; x += 3) { /* pixel (x, y) reads texel (2x, 448 y / 192), CT24 */
            const u8 *p = half + y * 0x300 + x * 3;
            ok &= (u32)(p[0] | p[1] << 8 | p[2] << 16) == (disp_px(2 * x, y * 448 / 192) & 0xFFFFFF);
        }
    CHECK("copy, present fill: the half capture holds the display at half size", ok);
    /* a black frame (the present's clear when nothing else is filled): the CT24 store drops its alpha */
    kh1_gs_reset();
    copy_context();
    upload_display(1, 0x80000000u);
    kh1_gsmem_flat(1);
    CHECK("copy, present fill: a black display still gives the empty pass", blur() == D_002A4DD0);
    kh1_gsmem_flat(0);
    /* the wide view: fullscreen.c's KH1_FS_XS | KH1_FS_U row stretches the copy to the view's half,
     * x 0 .. 338.8 into the PS2's 256-wide buffer */
    kh1_gs_reset();
    view(1);
    kh1_dma_fullscreen(copy_fs, 1, -1325, 10842);
    copy_context();
    upload_display(0, 0);
    kh1_gsmem_flat(1);
    take_snap();
    CHECK("copy, wide, present fill: the blur sees the frame", blur() == D_002A4B60);
    kh1_gsmem_flat(0);
    /* the 83 columns past x 256 wrap into the next page row (the GS's own addressing, FBW 4): rows
     * 0 .. 159's land inside and are drawn over by the later rows, rows 160 .. 191's land in rows
     * 192 .. 223, blocks 0x3900 .. 0x393F (the shared texture slot, renderer-spec 3.1): 83 x 32 words */
    x = changed_outside();
    CHECK("copy, wide, present fill: 83 x 32 words past the capture, in blocks 0x3900 .. 0x393F",
          x == 83 * 32 && out_b0 >= 0x3900 && out_b1 <= 0x393F);
    kh1_dma_fullscreen(0, 0, 0, 0);
    walk_copy = 0;

    /* screen.c func_001e1480: vm_lib's capture of the target into D_00F20000 */
    for (wide = 0; wide < 2; wide++) {
        kh1_gs_reset();
        view(wide);
        for (y = 0; y < 384; y++)
            for (x = 0; x < 512; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1A00, 8, x, y, 0x80000000u | (x * 0x9E37u ^ y * 0x7F4Au));
        memset(D_00F20000, GUARD, sizeof D_00F20000);
        func_001e1480();
        CHECK(wide ? "vm_lib capture, wide: 0x90000 bytes" : "vm_lib capture: 0x90000 bytes",
              used(D_00F20000, sizeof D_00F20000) == 0x90000);
        for (ok = 1, y = 0; y < 384; y += 7)
            for (x = 0; x < 512; x += 5) {
                const u8 *p = D_00F20000 + y * 0x600 + x * 3;
                ok &= (u32)(p[0] | p[1] << 8 | p[2] << 16) == ((x * 0x9E37u ^ y * 0x7F4Au) & 0xFFFFFF);
            }
        CHECK("vm_lib capture: 0x600 a row, RGB", ok);
    }

    if (fails) { printf("storeread_test: %d of %d checks failed\n", fails, checks); return 1; }
    printf("storeread_test: PASS (%d checks)\n", checks);
    return 0;
}
