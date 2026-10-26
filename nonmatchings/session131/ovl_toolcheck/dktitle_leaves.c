typedef unsigned int u32; typedef int s32; typedef float f32; typedef unsigned short u16; typedef unsigned char u8;
extern s32 D_00F2C6F0, D_00F2C6F4;
void ovl_00f20020(void) { D_00F2C6F0 = 0; D_00F2C6F4 = 0; }
typedef struct { u8 pad[8]; s32 size; u16 off; } Hdr;
void ovl_00f20a78(u8 *p, u8 **a, u8 **b) { Hdr *h = (Hdr *)(p + 16); u8 *s = (u8 *)h + h->off; *a = s; *b = s + h->size; }
typedef struct { f32 v; s32 st; s32 t; } Fade;
void ovl_00f20da0(Fade *f) { f->st = 0; f->v = 0; f->t = 0; }
void ovl_00f20db0(Fade *f) {
    switch (f->st) {
    case 0:
        f->v += 2.1333334f;
        if (128.0f <= f->v) { f->t = 180; f->v = 128.0f; f->st = 1; }
        break;
    case 1:
        if (--f->t == 0) f->st = 2;
        break;
    case 2:
        f->v -= 2.1333334f;
        if (f->v <= 0.0f) f->v = 0.0f;
        break;
    }
}
void ovl_00f26c88(void) {}
s32 ovl_00f26c90(void) { return 3; }
extern s32 D_00F2C8A0;
void ovl_00f26638(s32 a) { D_00F2C8A0 = a; }
extern u32 D_002C5AD8;
u32 ovl_00f24a58(void) { u32 v = D_002C5AD8; return v | ((v >> 24) & 0xf0); }
extern void ovl_00f206c8(u8 *, u8 *, s32, s32, s32, s32, s32);
extern u8 D_009A0000[];
void ovl_00f20860(void) { u8 *a, *b; Hdr *h = (Hdr *)(D_009A0000 + 16); a = (u8 *)h + h->off; b = a + h->size; ovl_00f206c8(a, b, 11776, 512, 384, 4, 12800); }
