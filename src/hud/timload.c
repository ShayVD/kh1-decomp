/* TIM2 picture uploads (docs/modules.md "Session 46"), 0x002499f0-0x00249fb0.
 * A Tim is the 0x10-byte file header and one 0x30-byte picture header
 * (TimPic) before the image and its CLUT.  func_00249a48 loads both into
 * the GS (sceGsSetDefLoadImage / sceGsExecLoadImage, the CLUT 16x16 for
 * PSMT8 or 8x2 for PSMT4 from D_00469FB0's PSM per TIM2 type), then sends
 * the texture flush packet that func_002499f0 also sends alone;
 * func_00249dc8 loads the image only.  func_00249c60 loads a list of them
 * (Lst; func_00249d20 appends, func_00249c48 / func_00249d48 empty it).
 * func_00249f08 and func_00249d50 set fields of the picture's TEX0,
 * func_00249da8 tests the "TIM2" magic (D_00491840) and func_00249eb8 takes
 * the 0x40-byte CLUT into a CLUT row (the two halves 0x40 apart). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/types/text_00240000_s6_25_p.h"

typedef struct {
    u64 tbp0 : 14; u64 tbw : 6; u64 psm : 6; u64 f26 : 11;
    u64 cbp : 14; u64 cpsm_csm : 5; u64 csa : 5; u64 cld : 3;
} TexBits;
typedef struct {
    u32 total;
    u32 clutSize;
    u32 imageSize;
    u16 hdrSize;
    u16 clutColors;
    u8 fmt;
    u8 mip;
    u8 clutType;
    u8 imageType;
    s16 w;
    s16 h;
    union { u64 tex0; TexBits tb; } t;
    u64 tex1;
    u32 flags;
    u32 clut;
} TimPic;
typedef struct { u8 pad[0x10]; TimPic pic; u8 data[1]; } Tim;
typedef struct { s32 n; s32 a[1]; } Lst;

extern PsmEnt D_00469FB0[];
extern char D_00491840[];
void func_00237018(void *, s32, s32);
s32 strncmp(const char *, const char *, u32);
void func_00249a48(Tim *, s32);
void func_00249d48(Lst *p);

void func_002499f0(void) {
    u64 pk[6];
    PlatGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
}

void func_00249a48(Tim *t, s32 sync) {
    u8 li[0x60];
    u64 pk[6];
    TimPic *p = &t->pic;
    u8 *img = NULL;
    u8 *clut;
    s16 psm, cpsm; u16 cbp;
    if (p->imageSize) {
        img = t->data;
        PlatGsSetDefLoadImage(li, (u16)(p->t.tex0 & 0x3FFF), (u16)(p->t.tex0 >> 14 & 0x3F), (u16)((p->t.tex0 & 0x3F00000) >> 20), 0, 0, p->w, p->h);
        PlatFlushCache(0);
        PlatGsSyncPath(0, 0);
        PlatGsExecLoadImage(li, img);
    }
    PlatGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (p->clutSize) {
        cbp = p->t.tex0 >> 37 & 0x3FFF;
        cpsm = D_00469FB0[p->clutType].psm;
        clut = img + p->imageSize;
        psm = D_00469FB0[p->imageType].psm;
        if (psm == 19) {
            PlatGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 16, 16);
        } else if (psm == 20) {
            PlatGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 8, 2);
        }
        PlatFlushCache(0);
        PlatGsSyncPath(0, 0);
        PlatGsExecLoadImage(li, clut);
    }
    PlatGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (sync) PlatGsSyncPath(0, 0);
}

void func_00249c48(Lst *p) {
    func_00249d48(p);
}

void func_00249c60(Lst *p) {
    s32 i;
    if (p->n == 0) return;
    for (i = 0; i < p->n - 1; i++) func_00249a48((Tim *)p->a[i], 0);
    func_00249a48((Tim *)p->a[i], 1);
}

s32 func_00249d20(Lst *p, s32 v) {
    p->a[p->n] = v;
    p->n++;
    return v + 16;
}

void func_00249d48(Lst *p) {
    p->n = 0;
}

void func_00249d50(Tim *t, s32 tbp0, s32 cbp) {
    TexBits *b = &t->pic.t.tb;
    b->tbp0 = tbp0;
    b->cbp = cbp;
}

TimPic *func_00249da0(Tim *t) {
    return &t->pic;
}

s32 func_00249da8(char *s) {
    return strncmp(s, D_00491840, 4);
}

void func_00249dc8(Tim *t, s32 sync) {
    u8 li[0x60];
    u64 pk[6];
    TimPic *p = &t->pic;
    u8 *d = NULL;
    if (p->imageSize) {
        d = t->data;
        PlatGsSetDefLoadImage(li, (u16)(p->t.tex0 & 0x3fff), (u16)((p->t.tex0 >> 14) & 0x3f), (u16)((p->t.tex0 & 0x3f00000) >> 20), 0, 0, p->w, p->h);
        PlatFlushCache(0);
        PlatGsSyncPath(0, 0);
        PlatGsExecLoadImage(li, d);
    }
    PlatGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001ULL;
    pk[3] = 0xe;
    pk[5] = 0x3f;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (sync) PlatGsSyncPath(0, 0);
}

void func_00249eb8(u8 *dst, u8 *t) {
    s32 i = 0;
    s32 n = 0x40;
    u8 *s = t + n + *(s32 *)(t + 0x18);
    for (; i < n; i++, s++, dst++) {
        if (i < 0x20) dst[0] = *s;
        else dst[0x20] = *s;
    }
}

TimPic *func_00249f08(Tim *t, s32 tbp0, s32 psm, s32 cbp, s32 csa, s32 cld) {
    TexBits *b = &t->pic.t.tb;
    b->tbp0 = tbp0;
    b->psm = psm;
    b->cbp = cbp;
    b->csa = csa;
    b->cld = cld;
    return &t->pic;
}
