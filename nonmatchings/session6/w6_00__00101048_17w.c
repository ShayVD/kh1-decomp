/* 17 words off (mode hand): only the prologue regs: orig uses v1 for lui D_002A3F3C, a0=160, v1=&D_002A3F20 (lui before the div); ours v0/v1/a0. Rest matches. */
#include "common.h"
typedef struct { u64 x[20]; } Blk160;
typedef struct { s32 m[32][16]; s32 v[4]; } Blk810;
typedef struct { u8 kind[16]; u8 pad10[4]; u16 n0; u16 n1; } Setup;
typedef struct { s32 o0; u32 sz4; s32 o8; s32 pc; s32 o10; s32 p14; s32 o18; s32 p1c; s32 o20; u32 sz24; } Hdr;
extern Hdr *D_002A3F3C;
extern s32 D_002A3F20;
extern s32 D_002A3F24;
extern Blk160 D_0029B420[];
void func_00108618(void);
void func_00100b18(Setup *);
void func_00100d18(void *, s32);
void func_00100d90(void *, s32);
void func_00100e08(void *, s32);
void func_00100e80(void *, s32);
void func_00100ef8(void *, s32);
void func_00100f70(Blk810 *);
void func_00101e70(void);
void func_00102978(void);
void func_0011ef10(s32, void (*)(void));
void func_00113768(void);
s32 func_00101048(void) {
    s32 i;
    Hdr *h;
    Blk160 *src;
    Blk810 *mt;
    Setup *s;
    u8 *tex;
    u8 *big;
    i = 0;
    func_00108618();
    h = D_002A3F3C;
    src = (Blk160 *)((u8 *)h + h->o0);
    D_002A3F20 = h->sz4 / sizeof(Blk160);
    for (; i < D_002A3F20; i++) {
        D_0029B420[i] = src[i];
    }
    s = (Setup *)((u8 *)h + h->o8);
    tex = (u8 *)h + h->o10;
    big = (u8 *)h + h->o18;
    func_00100b18(s);
    for (i = 0; i < s->n0; i++) {
        func_00100d18(tex + i * 256, i + 0x3e00);
    }
    for (i = s->n0; i < s->n1; i += 4) {
        func_00100d90(tex + i * 256, i + 0x3e00);
    }
    for (i = 0; i < 16; i++) {
        if (s->kind[i] != 19) {
            if (s->kind[i] == 20) {
                func_00100e08(big + i * 0x10000, i * 256 + 0x2600);
            }
        } else {
            func_00100e80(big + i * 0x10000, i * 256 + 0x2600);
        }
    }
    func_00100ef8(big + 0x100000, 0);
    mt = (Blk810 *)((u8 *)h + h->o20);
    D_002A3F24 = h->sz24 / sizeof(Blk810);
    func_00100f70(mt);
    func_00101e70();
    func_00102978();
    func_0011ef10(0xc350, func_00113768);
    return 4;
}
