/* dktitle.x func_00f20a98: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 pad[8]; s32 size; u16 off; } Hdr;
typedef struct { s32 off; s32 pad; } Ent;
typedef struct { u8 pad[16]; Ent e[14]; } Pak;
extern void func_00f206c8(u8 *, u8 *, s32, s32, s32, s32, s32);
extern void func_00f208f0(u8 *);
extern void func_00f20a78(u8 *, u8 **, u8 **);
extern u8 *D_00F26E1C;
void func_00f20a98(Pak *p) {
    u8 *img, *clut;
    Ent *e = &p->e[1];
    u8 *q;
    q = (u8 *)p + p->e[0].off;
    q += 16;
    img = q + ((Hdr *)q)->off;
    func_00f208f0(img);
    q = (u8 *)p + (e++)->off;
    q += 16;
    D_00F26E1C = q + ((Hdr *)q)->off;
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 12800, 512, 384, 4, 14580);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 13568, 256, 192, 8, 14564);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 13792, 512, 32, 4, 14581);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14180, 512, 32, 8, 14568);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 13920, 512, 32, 4, 14582);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14308, 512, 32, 8, 14572);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14048, 512, 32, 4, 14583);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14436, 512, 32, 8, 14576);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14176, 32, 32, 4, 14584);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14178, 32, 32, 4, 14585);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14586, 512, 32, 4, 14846);
    func_00f20a78((u8 *)p + (e++)->off, &img, &clut);
    func_00f206c8(img, clut, 14714, 512, 32, 8, 14842);
}
