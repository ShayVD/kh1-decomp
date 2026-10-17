#include "common.h"
typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    u8 pad3040[0x30];
    u64 f3070;
    u64 f3078;
} Big;

/* Script VM instance (0x350 bytes). */
typedef struct {
    s32 x0, x4;
    u8 pad8[0x68];
    s8 *code;
    s32 n;
    s32 x78;
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[91];
    s32 x2f0;
    s32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u64 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:54;
    u8 pad330[0x20];
} VM;
extern s32 D_002BBAB0, D_002BBAB8, D_002BBAC8;
extern u8 D_003C5660[], D_003C5680[], D_003C56A0[], D_003C56C0[], D_003C56F0[], D_003C5728[], D_003C5750[], D_003C5780[], D_003C57B0[];
typedef struct { u16 t:4, s:4, b1:8; } Ent;
typedef struct {
    u8 pad0[0x30];
    f32 x30, x34;
    u8 pad38[8];
    f32 x40, x44;
    u8 pad48[0x68];
} Obj;
extern Obj D_006298F0[];
Ent *func_00147778(s32);
s32 func_0010f098(u8 *);

s32 func_001cb440(VM *vm) {
    s32 id, y, i, x;
    Ent *e;
    s32 b;
    Obj *o;

    id = vm->stk[vm->sp - 2];
    i = vm->stk[vm->sp - 3];
    x = vm->stk[vm->sp - 1];
    y = vm->stk[vm->sp];

    e = func_00147778(id);
    switch (e->t) {
    case 0:
        b = e->b1;
        D_002BBAB0 = b;
        D_002BBAC8 = e->s;
        if ((u32)(b - 1) < 16) D_006298F0[i].x40 = func_0010f098(D_003C5660);
        else if ((u32)(b - 142) < 16) D_006298F0[i].x40 = func_0010f098(D_003C5680);
        else if ((u32)(b - 192) < 64) D_006298F0[i].x40 = func_0010f098(D_003C56A0);
        else if ((u32)(b - 81) < 22) D_006298F0[i].x40 = func_0010f098(D_003C5750);
        else if ((u32)(b - 103) < 16) D_006298F0[i].x40 = func_0010f098(D_003C5780);
        else if ((u32)(b - 119) < 16) D_006298F0[i].x40 = func_0010f098(D_003C57B0);
        else if ((u32)(b - 17) < 64) D_006298F0[i].x40 = func_0010f098(D_003C5728);
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[i].x40 = func_0010f098(D_003C56F0);
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[i].x40 = func_0010f098(D_003C56C0);
        }
        break;
    }
    D_006298F0[i].x30 = x + D_006298F0[i].x40 * 12.0f;
    D_006298F0[i].x34 = y + (&D_006298F0[i])->x44 * 12.0f;
    vm->sp -= 4;
    return 2;
}
