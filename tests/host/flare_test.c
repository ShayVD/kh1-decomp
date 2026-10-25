/* The lens flare's visibility count (src/ppp/kelnscls.nostrict.c func_00192958, the game's own C)
 * against the null platform's Z store (host/null/gsimage.c, session 102), on a made-up FlareObj
 * (session 103, docs/vita-port-plan.md 5.1ap): tests/selftest.sh links the matched function with
 * gsimage.c, gsmem.c and the host libvu0 under gcc -m32 when that works, its other callees stubbed.
 *
 * func_00192958 stores the Z24 box around the light (ZBP 0x70, from the packet it builds) and counts
 * the pixels whose depth is under the light's (Z24 grows nearer): f7C, the flare's strength, is
 * multiplied by the visible share and fAC keeps it for the frames that skip the read.
 * - a Z buffer only the draws wrote reads 0 (the farthest): all visible, f7C stays 1;
 * - a Z box uploaded nearer than the light over part of the box dims it by the covered share;
 * - a skipped frame multiplies f7C by the last share again. */
#include "common.h"
#include "platform/gs.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

int kh1_host_trace = 2; /* the model takes loads from 2 on */

/* the callees and data kelnscls.nostrict.c names that func_00192958 does not reach */
u8 D_0061E250[0x100] __attribute__((aligned(16))); /* the flare's GS packet (FlarePkt) */
u8 D_003701F0[16] __attribute__((aligned(16)));
void *D_00615E60, *D_00615E68;
u8 D_00615FC0[64] __attribute__((aligned(16))), D_00616040[64] __attribute__((aligned(16)));
s32 D_0061621C;
void func_00191fc8(void) {}
void func_00192208(void) {}
void func_001924a8(void) {}
void func_00192708(void) {}
void func_00192f78(void) {}
void func_00193408(void) {}
void func_001936c0(void) {}
void func_001a57c0(void) {}
void func_001a5ce8(void) {}
void func_001a60e8(void) {}
void func_001a62c0(void) {}
void func_001a6550(void) {}
void func_001a9098(void) {}
void PlatFlushCache(int op) {}
int PlatGsSyncPath(int mode, unsigned short timeout) { return 0; }

/* func_001aa950 / func_001aa9d0: the scratch stack's 0x3060 bytes (96 of header, then the store) */
#define GUARD 0x5A
static u8 scratch[0x3060 + 64] __attribute__((aligned(16)));
static int allocs, frees;
u8 *func_001aa950(s32 n) { allocs++; return n == 0x3060 ? scratch : 0; }
void func_001aa9d0(s32 n) { if (n == 0x3060) frees++; }

void func_00192958(void *o, s32 a1, s32 frame);

/* FlareObj's fields func_00192958 reads (the offsets in kelnscls.nostrict.c) */
static u8 obj[0xD0] __attribute__((aligned(16)));
static f32 getf(u32 off) { f32 f; memcpy(&f, obj + off, 4); return f; }
static void setf(u32 off, f32 f) { memcpy(obj + off, &f, 4); }

static int checks, fails;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("flare_test: %s\n", name); fails++; } } while (0)

#define LX 256 /* the light on screen (pixels), its Z24 depth */
#define LY 192
#define LZ 0x100000

/* a flare at the light, strength 1, a box of sx x sy pixels (bC0 / bC1: the key's e x 8 by f x 4) */
static void flare(u32 sx, u32 sy) {
    memset(obj, 0, sizeof obj);
    setf(0x7C, 1.0f);
    obj[0x8C] = 0;  /* b8C / b8D: read every frame */
    obj[0x8D] = 0;
    setf(0xB0, (f32)(0x7000 / 16 + LX)); /* the packet's XYOFFSET is 0x7000, 0x7400 (12.4) */
    setf(0xB4, (f32)(0x7400 / 16 + LY));
    setf(0xB8, (f32)LZ);
    setf(0xBC, 1.0f);
    obj[0xC0] = (u8)sx;
    obj[0xC1] = (u8)sy;
}

/* the 3D pass's draw: FRAME CT32 at 0, FBW 8, ZBUF 0x70 Z24, the packet's scissor and TEST (ZTE) */
static void draw_3d(void) {
    kh1_gsmem_draw(0 | 8 << 16 | KH1_PSMCT32 << 24, 0, 0x70 | 1 << 24, 0, 511 << 16, 383 << 16, 0x5000d);
}

/* a Z24 box uploaded at ZBP 0x70 (block 0xE00): w x h at (x, y), depth z */
static u8 zpix[64 * 64 * 3];
static void upload_z(u32 x, u32 y, u32 w, u32 h, u32 z) {
    u32 lp[24], i;
    for (i = 0; i < w * h; i++) {
        zpix[i * 3] = (u8)z;
        zpix[i * 3 + 1] = (u8)(z >> 8);
        zpix[i * 3 + 2] = (u8)(z >> 16);
    }
    PlatGsSetDefLoadImage(lp, 0xE00, 8, KH1_PSMZ24, (short)x, (short)y, (short)w, (short)h);
    PlatGsExecLoadImage(lp, zpix);
}

static int near(f32 a, f32 b) { return a - b < 1e-5f && b - a < 1e-5f; }

int main(void) {
    u32 i, ok;

    kh1_gs_reset();
    kh1_gs_view(-1325, 10842); /* KH1_HOST_WIDE's view: the store still reads the PS2's 512 x 384 */

    /* 1. a Z buffer only the draws wrote: an older upload nearer than the light is gone */
    upload_z(0, 0, 64, 64, 0xFFFFFF);
    upload_z(LX - 32, LY - 32, 64, 64, 0xFFFFFF);
    draw_3d();
    flare(16, 16);
    memset(scratch, GUARD, sizeof scratch);
    func_00192958(obj, 0, 0);
    CHECK("drawn Z: all visible, f7C stays 1", near(getf(0x7C), 1.0f));
    CHECK("drawn Z: fAC is the share, 1", near(getf(0xAC), 1.0f));
    CHECK("the packet: ZBUF 0x70 Z24", *(u32 *)(D_0061E250 + 0x10) == 0x31000070);
    CHECK("the scratch taken and given back", allocs == 1 && frees == 1);
    for (ok = 1, i = 96; i < 96 + 16 * 16 * 3; i++) ok &= scratch[i] == 0;
    CHECK("the store: 16 x 16 Z24 zeros after the header", ok);
    CHECK("the store: nothing past the box", scratch[96 + 16 * 16 * 3] == GUARD);

    /* 2. the left half of the box uploaded nearer than the light (a wall in front of it) */
    kh1_gs_reset();
    draw_3d();
    upload_z(LX - 8, LY - 8, 8, 16, LZ + 0x1000);
    upload_z(LX, LY - 8, 8, 16, LZ - 0x1000);
    flare(16, 16);
    func_00192958(obj, 0, 0);
    CHECK("half covered: f7C 0.5", near(getf(0x7C), 0.5f));
    CHECK("half covered: fAC 0.5", near(getf(0xAC), 0.5f));

    /* 3. b8D 1: odd frames skip the read and multiply by the last share */
    obj[0x8D] = 1;
    func_00192958(obj, 0, 1);
    CHECK("skipped frame: f7C x fAC", near(getf(0x7C), 0.25f));
    CHECK("skipped frame: no store", allocs == 2);

    /* 4. a quarter covered, the largest box (64 x 64 = 4096 pixels: e 8, f 16), at the light's depth
     * itself (not under it, so not visible) */
    kh1_gs_reset();
    draw_3d();
    upload_z(LX - 32, LY - 32, 64, 64, LZ - 1);
    upload_z(LX - 32, LY - 32, 32, 32, LZ);
    flare(64, 64);
    memset(scratch, GUARD, sizeof scratch);
    func_00192958(obj, 0, 0);
    CHECK("quarter covered: f7C 0.75", near(getf(0x7C), 0.75f));
    CHECK("largest box: inside the 0x3060 bytes", scratch[0x3060] == GUARD && scratch[0x3060 - 1] != GUARD);

    /* 5. the box at the screen's left edge is clipped to the scissor: 8 of its 16 columns */
    kh1_gs_reset();
    draw_3d();
    flare(16, 16);
    setf(0xB0, (f32)(0x7000 / 16));
    func_00192958(obj, 0, 0);
    CHECK("clipped box: f7C 0.5 (8 x 16 seen of 16 x 16)", near(getf(0x7C), 0.5f));

    /* 6. off screen: no box, the flare off */
    flare(16, 16);
    setf(0xB0, (f32)(0x7000 / 16 - 100));
    func_00192958(obj, 0, 0);
    CHECK("off screen: f7C and fAC 0", getf(0x7C) == 0.0f && getf(0xAC) == 0.0f);

    if (fails) { printf("flare_test: %d of %d checks failed\n", fails, checks); return 1; }
    printf("flare_test: PASS (%d checks)\n", checks);
    return 0;
}
