/* xs_simba.x func_00f20618: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x70]; s32 f70; } Act;
typedef struct { f32 lv; u8 pad[0x1C]; } Lvl;
s32 func_00137618(Act *);
s32 func_0013aa60(void);
CONTEXT_ONLY void func_00f202e8(s32 a0) {}
void func_00f20570(Lvl *);
s32 func_00147be0(void *);
s32 func_00157560(Act *);
void func_0014f658(Act *, s32);
extern f32 D_002BBDFC;
extern s32 D_002E27D4;
extern void *D_00304B6C;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern Lvl D_00F21B90[];
extern f32 D_00F21C30;
extern Act *D_00F21C34;
extern Act *D_00F21C38;
extern Lvl *D_00F21C3C;
extern void *D_00F21C44;
extern f32 D_00F21C48;
extern f32 D_00F21C4C;
extern s32 D_00FA6A10;
extern s32 D_00FA6A80;
s32 func_00f20618(void) {
    u8 *pad = D_00304B70;
    Lvl *p;
    s32 i;

    D_00304B7C -= pad[1] * D_002BBDFC;
    switch (D_00FA6A10) {
    case 0:
        D_00F21C48 = 0.0f;
        if (func_00137618(D_00F21C38) && func_0013aa60()) {
            if (D_00F21C38->f70 == 2)
                D_00F21C30 += D_002BBDFC;
            else
                D_00F21C30 = 0.0f;
            if (D_00F21C38->f70 == 0 || 60.0f <= D_00F21C30)
                func_00f202e8(100);
        }
        break;
    case 1:
        D_00F21C48 += pad[3] * D_002BBDFC;
        if (D_00F21C4C < D_00F21C48)
            D_00F21C48 = D_00F21C4C;
        for (i = 4; i >= 0; i--) {
            p = &D_00F21B90[i];
            if (p->lv <= D_00F21C48) {
                if (D_00F21C3C != p)
                    func_00f20570(p);
                break;
            }
        }
        break;
    case 3:
        func_0014f658(D_00F21C34, 0);
        func_00f202e8(0);
        break;
    case 100:
        if (D_00304B6C == 0 && func_00147be0(D_00F21C44) == 0 && func_00157560(D_00F21C38) != 2)
            func_00f202e8(101);
        break;
    case 101:
        D_002E27D4 = 0;
        D_00FA6A80 = 0;
        return 4;
    }
    return 0;
}
