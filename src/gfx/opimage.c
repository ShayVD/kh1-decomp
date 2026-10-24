/* The model renderer's image loads (docs/modules.md "Session 49"),
 * 0x001aa0a8-0x001aa448: func_001aa0a8 is log2 rounded up (a texture
 * size's TW / TH), func_001aa0e0 loads a TIM2 picture's image and CLUT
 * into GS memory (D_003727F0 maps the TIM2 image types to PSMs),
 * func_001aa388 loads one image from a texture header, func_001aa420 hands a
 * header to the hand asm func_001aa1f8 (src/asm/text_001aa1f8.s).  GS calls
 * still by their SDK names (sceGsSetDefLoadImage / sceGsExecLoadImage), not
 * yet behind a platform wrapper.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "platform/gs.h"

s32 FlushCache(s32);
M2C_UNK func_001aa1f8(s32, u8, u16, s32);
extern u8 D_003727F0[];

s32 func_001aa0a8(s32 arg0) {
  s32 var_a1;
  s32 var_v1;
  int new_var;
  var_v1 = 1;
  var_a1 = 0;
  new_var = 1;
  if (arg0 > new_var)
  {
    do
    {
      var_v1 *= 2;
      var_a1 += new_var;
    }
    while (var_v1 < arg0);
  }
  return var_a1;
}

typedef struct {
    u32 totalSize;
    u32 clutSize;
    u32 imageSize;
    u16 headerSize;
    u16 clutColors;
    u8 picFormat;
    u8 mipMaps;
    u8 clutType;
    u8 imageType;
    s16 width;
    s16 height;
    struct { u16 tbp0 : 14; u16 x : 2; u16 y; } t0;
    union { struct { u32 thh : 2; u32 tcc : 1; u32 tfx : 2; u32 cbp : 14; u32 rest : 13; } t1; u32 t1w; };
    u32 tex1[2];
    u8 b28;
    u8 b29;
    u8 b2a;
    u8 b2b;
} PicHdr;
typedef struct {
    u8 hdr[15];
    u8 bF;
    PicHdr ph;
} Tm2;

void func_001aa0e0(Tm2 *t) {
    u8 li[96];
    u8 lc[96];
    PicHdr *ph = &t->ph;
    u8 *img;
    if (ph->imageSize) {
        s32 psm = D_003727F0[ph->imageType];
        s32 tbp = ph->t0.tbp0;
        img = (u8 *)t + 64;
        t->bF = 111;
        PlatGsSetDefLoadImage(li, tbp, ph->b28 >> 2, psm, ph->b2a * 16, ph->b2b * 16, ph->width, ph->height);
        PlatGsSyncPath(0, 0);
        FlushCache(0);
        PlatGsExecLoadImage(li, img);
    }
    if (ph->clutSize) {
        PlatGsSetDefLoadImage(lc, ph->t1.cbp, 1, D_003727F0[ph->clutType], 0, 0, 16, ph->clutSize >> 6);
        PlatGsSyncPath(0, 0);
        FlushCache(0);
        PlatGsExecLoadImage(lc, img + ph->imageSize);
    }
}

/* The argument types decide the extensions: this caller's view of
 * sceGsSetDefLoadImage. */
typedef M2C_UNK (*LoadImg388)(void *, s32, u32, u8, s32, s32, s16, s16);
typedef M2C_UNK (*ExecImg388)(void *, s32);

void func_001aa388(void *arg0, s32 arg1) {
    s32 sp[24];
    ((LoadImg388)sceGsSetDefLoadImage)(sp, M2C_FIELD(arg0, u16 *, 0) & 0x3FFF, (u8) M2C_FIELD(arg0, u8 *, 0xA) >> 2, M2C_FIELD(arg0, u8 *, 0x18), M2C_FIELD(arg0, u8 *, 8) * 0x10, M2C_FIELD(arg0, u8 *, 9) * 0x10, M2C_FIELD(arg0, s16 *, 0xC), M2C_FIELD(arg0, s16 *, 0xE));
    PlatGsSyncPath(0, 0);
    FlushCache(0);
    ((ExecImg388)sceGsExecLoadImage)(sp, M2C_FIELD(arg0, s32 *, 0x14));
    if (arg1 != 0) {
        PlatGsSyncPath(0, 0);
    }
}

void func_001aa420(void *arg0, s32 arg1) {
    func_001aa1f8(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, u8 *, 9), M2C_FIELD(arg0, u16 *, 0), arg1);
}

#include "data/data_0037.h"
