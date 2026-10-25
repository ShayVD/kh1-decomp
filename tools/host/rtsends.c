/* The render-to-texture packets the game builds at run time, built by the game's own C on the host for
 * tools/host/fscheck.py's block check (session 109, docs/vita-port-plan.md 5.1aw): fscheck compiles this
 * with src/gfx/shadow.c, src/gfx/gifpkt.c and src/obj/objdraw.nostrict.c under gcc -m32 (--gc-sections
 * keeps only what the builders below reach) and reads the chains it prints.
 *
 *   rtsends W0 W1 W2 [CW CH ...]
 *
 * - the shadow windows (renderer-spec 3.4 item 1): func_001284a0 into a D_004F7820-sized buffer and
 *   func_00128738 into a D_004F7C10-sized one for each window size Wi (D_002E27E0[i], read from the
 *   user's ELF by fscheck), as func_00128b20 does at start-up;
 * - the texture crossfade (3.4 item 2): func_00135ed0 on a made-up image record CW x CH (the model's
 *   texture size, from the disc at run time), its two PlatDmaSend chains captured.
 *
 * One line per chain: `CHAIN send variant va hex...`, va the buffer's address as a DMA tag holds it
 * (31 bits), the bytes in memory order.  The packets hold registers and coordinates the C computes from
 * constants and the sizes given; nothing here comes from the disc. */
#include "common.h"

int printf(const char *, ...);
int atoi(const char *);
int sprintf(char *, const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

typedef struct { u8 pad[336]; } A6; /* data/types/text_00120000_h31.h */
typedef struct { u8 pad[544]; } B6;
typedef struct { u16 x0; u8 x2, x3; u16 x4, x6, x8; u8 pad0a[2]; s32 xc, x10; } C02Img;
typedef struct { u8 pad00[0x154]; void *x154; } C02Res;
typedef struct { C02Res *res; s32 x4; } C02Src;

/* the data and callees the builders name */
s32 D_002E27E0[4];
static void nop(s32 a) {}
void (*D_00351BC8)(s32) = nop;
s32 func_001623e8(void *r) { return 0; }
void func_001623f8(void *r, s32 i, s32 *t) { t[0] = t[1] = t[2] = t[3] = 0; }
void func_00162428(s32 a, s32 b) {}
int PlatGsSyncPath(int mode, unsigned short timeout) { return 0; }
struct PlatDmaChan { int x; };
static struct PlatDmaChan chan;
struct PlatDmaChan *PlatDmaGetChan(int id) { return &chan; }

void func_001284a0(A6 *buf, s32 idx);
void func_00128738(B6 *buf, s32 idx);
s32 func_00135ed0(C02Img *img, C02Src *src);

static const char *cur_send, *cur_var;

static void dump(const char *send, const char *var, const void *p, int n) {
    const u8 *b = p;
    int i;
    printf("CHAIN %s %s %x ", send, var, (u32)(unsigned long)p & 0x7FFFFFFF);
    for (i = 0; i < n; i++) printf("%02x", b[i]);
    printf("\n");
}

/* func_00135ed0's chains live in its own 128-quadword stack buffer: copied whole when sent */
void PlatDmaSend(struct PlatDmaChan *ch, void *tag) { dump(cur_send, cur_var, tag, 128 * 16); }

static A6 shadow[3] __attribute__((aligned(32)));
static B6 copy[3] __attribute__((aligned(16)));

int main(int argc, char **argv) {
    char var[32];
    int i;
    if (argc < 4) return 2;
    for (i = 0; i < 3; i++) D_002E27E0[i] = atoi(argv[1 + i]);
    for (i = 0; i < 3; i++) {
        func_001284a0(&shadow[i], i);
        func_00128738(&copy[i], i);
        var[0] = '0' + i, var[1] = 0;
        dump("D_004F7820", var, &shadow[i], sizeof(A6));
        dump("D_004F7C10", var, &copy[i], sizeof(B6));
    }
    for (i = 4; i + 1 < argc; i += 2) {
        C02Img img;
        C02Res res;
        C02Src src;
        memset(&img, 0, sizeof img);
        img.x0 = 0x3600, img.x2 = 4, img.x3 = 0x13; /* the slot's PSMT8 upload, as step 2 leaves it */
        img.x4 = atoi(argv[i]), img.x6 = atoi(argv[i + 1]), img.x8 = 0x3700;
        res.x154 = &res;
        src.res = &res, src.x4 = 64;
        cur_send = "func_00135ed0";
        sprintf(var, "%dx%d", img.x4, img.x6); /* the variant: the image size */
        cur_var = var;
        func_00135ed0(&img, &src);
    }
    return 0;
}
