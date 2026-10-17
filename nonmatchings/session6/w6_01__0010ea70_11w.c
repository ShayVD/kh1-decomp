/* func_0010ea70: 11w off (scheduling only), mode hand (strict; reload pattern of v[1] after byte stores needs strict). Needs x24 typed as a non-void pointer (TBox *) so its store does not alias the void* stack slots. Off: order of the zero stores (orig sw x14 right after sb x13, sw x1c right after sw x18) and the float chain store order. Statement-order permutations (~1000) reach 11w at best. */
#include "common.h"
typedef struct {
    s32 x0; s32 x4; s16 x8; s16 xa; s16 xc; s16 xe;
    u8 x10; u8 x11; u8 x12; u8 x13; s32 x14; f32 x18; s32 x1c; s32 x20; struct TBox *x24; s32 x28;
} TObj;
typedef struct TBox {
    u8 pad0[4]; s16 h4; u8 pad6[0x2a]; f32 x30, x34; u8 pad38[0x38]; f32 x70, x74;
} TBox;
extern u8 D_002BBAA0[];
extern void func_00106b18(void *);
extern void func_0010e4f0(TObj *);
extern void *func_00121e28(s32, void *);
extern void func_00121ee0(void *);

void func_0010ea70(s32 x, s32 y, s32 p) {
    void *v[2];
    v[0] = func_00121e28(0xb0, &v[0]);
    v[1] = func_00121e28(0x2c, &v[1]);
#define O ((TObj *)v[1])
#define B ((TBox *)v[0])
    O->x12 = 0;
    O->x0 = 0;
    O->x10 = 1;
    O->x14 = 0;
    O->xa = y;
    O->x4 = p;
    O->x8 = x;
    O->x24 = B;
    O->x13 = 0;
    O->x13 |= 2;
    O->x11 = 0;
    O->x1c = 0;
    B->h4 = 2;
    O->x18 = 0.0f;
    B->x34 = B->x70 = B->x74 = B->x30 = O->x18;
    O->x20 = 0;
    O->xe = 0;
    O->x28 = 0;
    O->xc = 0;
    func_00106b18(D_002BBAA0);
    func_0010e4f0(O);
    func_00121ee0(O);
    func_00121ee0(B);
}
