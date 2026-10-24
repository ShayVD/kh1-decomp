/* The timer and score display (docs/modules.md "Session 46"), nostrict part.
 * func_00248400 is the set up (called from the HUD's func_00236f18): loads
 * the five sprite files, takes the digit, frame and icon sprites, sets the
 * three fonts' TEX0 (D_006692D8 / D_00669308 / D_00669338) and registers the
 * draw hook func_00248380.  func_00247930 draws the record time in red
 * (0xE5, 0x4E, 0x19) at 0.8 alpha, 43 pixels under the time;
 * func_00248238 draws the icon of the caller's kind x0 (a 64x64 image of
 * D_00431F30 uploaded by func_00247cc8) at (12, 15). */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h" /* QW */
#include "data/types/nostrict_text_00240000_h75_p.h"
#include "data/pieces/D_00431D50.h"
#include "data/pieces/D_00467408.h"

typedef struct {
    s32 x0;
    s32 x4;
    s32 on;
    s32 mode;
    s32 a;
    s32 b;
    s32 x18;
    s32 x1c;
    s32 x20;
    s32 x;
    s32 y;
    s32 x2c;
    s32 x30;
    s32 v34, v38, v3C, v40;
    s32 v44, v48, v4C, v50;
} MgHud;
typedef struct { s32 on; MgHud *c; } MgSlot;
typedef struct { s32 v[4]; } C4;
typedef struct { s32 x0, y0, x1, y1, u0, v0, u1, v1; C4 c[4]; u8 pad60[0x40]; u64 unkA0; } Spr2;

u64 D_006692D8 ALIGNED(8);
u64 D_00669308 ALIGNED(8);
u64 D_00669338 ALIGNED(8);
extern Spr2 D_006693F0;
extern u64 D_00491820;
extern u64 D_00669490;
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern QW *D_006691D0; /* src/data/bss_0066.c: Q4 *D_006691D0 */
extern QW *D_006691D4; /* src/data/bss_0066.c: Q4 *D_006691D4 */
extern MgSlot D_00669350; /* src/data/bss_0066.c: u8 D_00669350[0x8] */
extern u8 D_004656A0[];
extern u8 D_00465FD0[];
extern u8 D_00466180[];
extern u8 D_004667B0[];
extern u8 D_00466DE0[];
extern u8 D_00467350[];
extern u8 D_00467388[];
extern u8 D_00467398[];
extern u8 D_004673C0[];
extern u8 D_004673E8[];
extern u8 D_00669358[];
extern u8 D_00669388[]; /* src/data/bss_0066.c: s32 D_00669388[2] */
extern u8 D_00669390[]; /* src/data/bss_0066.c: s32 D_00669390[8] */
extern u8 D_006693B0[]; /* src/data/bss_0066.c: s32 D_006693B0[8] */
extern u8 D_006693D0[];
void func_00237018(void *, s32, s32);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00247cc8(s32);
void func_002474e8(Spr2 *, Fnt *, s32, s32, f32);
void func_0024afc0(void *, void *, void *);
void func_00248380(void);
s32 sprintf(char *, const char *, ...);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_002475d0(s32, s32, s8 *, f32, char *, void *);
#else
void func_002475d0(s32, s32, s8 *, char *, void *, f32);
#define func_002475d0(a1, a2, a3, a4, a5, a6) (func_002475d0)(a1, a2, a3, a5, a6, a4)
#endif

void func_00247930(MgHud *c) {
    s8 col[16];
    char buf[16];
    s32 x, y;
    col[0] = -27;
    x = c->x;
    x = c->x2c ? x + 103 : x + 93;
    col[1] = 78;
    col[2] = 25;
    y = c->y + 43;
    if (c->x2c) {
        sprintf(buf, "%02d", c->v50);
        func_002475d0(x, y, col, 0.7999999523162842f, buf, ((void *)D_00467408));
        x += 22;
        func_002475d0(x, y, col, 0.7999999523162842f, ":", ((void *)D_00467408));
        x += 11;
    }
    sprintf(buf, "%02d", c->v4C);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, ((void *)D_00467408));
    x += 22;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", ((void *)D_00467408));
    x += 11;
    sprintf(buf, "%02d", c->v48);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, ((void *)D_00467408));
    x += 22;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", ((void *)D_00467408));
    x += 5;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", ((void *)D_00467408));
    x += 9;
    sprintf(buf, "%02d", c->v44);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, ((void *)D_00467408));
}

void func_00248238(MgSlot *o) {
    MgHud *w = o->c;
    s32 i;
    if (w->x4 == 0 && w->x18 == 0) return;
    D_006691D4 = D_00351E10;
    D_006691D0 = D_00351E10 + 1;
    func_00247cc8(w->x0);
    D_006693F0.x0 = 12;
    D_006693F0.y0 = 15;
    D_006693F0.x1 = 64;
    D_006693F0.y1 = 64;
    D_006693F0.u0 = 0;
    D_006693F0.v0 = 0;
    D_006693F0.u1 = 63;
    D_006693F0.v1 = 63;
    for (i = 0; i < 4; i++) {
        D_006693F0.c[i].v[0] = 128;
        D_006693F0.c[i].v[1] = 128;
        D_006693F0.c[i].v[2] = 128;
        D_006693F0.c[i].v[3] = 128;
    }
    D_00669490 = D_00491820;
    func_002474e8((Spr2 *)((u8 *)&D_00669490 - 0xA0), &D_00431D50[w->x0], 0, 0, 1.0f);
    func_00237018(D_006691D4, D_006691D0 - D_006691D4, 1);
}

void func_00248400(void) {
    memset(&D_00669350, 0, 8);
    func_0024aac8(D_004656A0);
    func_0024aac8(D_00465FD0);
    func_0024aac8(D_00466180);
    func_0024aac8(D_004667B0);
    func_0024aac8(D_00466DE0);
    func_0024afc0(D_00467350, D_00669358, D_004656A0);
    func_0024afc0(D_00467388, D_00669388, D_00465FD0);
    func_0024afc0(D_00467398, D_00669390, D_00466180);
    func_0024afc0(D_004673C0, D_006693B0, D_004667B0);
    func_0024afc0(D_004673E8, D_006693D0, D_00466DE0);
    D_006692D8 = 0x0007400621413600;
    D_00669308 = 0x0207400621413600;
    D_00669338 = 0x0607400621413600;
    if (func_0011ef38(func_00248380) == 0) func_0011ef10(0x28489, func_00248380);
}
