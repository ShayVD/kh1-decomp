/* func_001cb440 (hand): 41 words, 744 vs 756 bytes. Whole body matches in shape (VM stack via Sub *s = &vm->u.s, range-test chain, crossjumped tails). Off: D_006298F0 hi in a0 (orig a1), last range test beqzl (orig beqz), and the tail: orig computes base k*176+D once and uses it through 3 copies (move a3,v0; move a2,a3; move v1,a2), loading x44 after storing x30, sp store between. */
#include "common.h"
typedef struct {
    void *obj;
    u8 pad4[0x17c];
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    union {
        Sub s;
        struct { void *obj; u8 pad[0x178]; s32 sp; } h;
    } u;
} VM;
typedef struct { u16 t:4, s:4, b1:8; } Ent;
typedef struct { u8 pad0[0x30]; f32 x30, x34; u8 pad38[8]; f32 x40, x44; u8 pad48[0xb0 - 0x48]; } Spot;
extern Spot D_006298F0[];
extern s32 D_002BBAB0, D_002BBAB8, D_002BBAC8;
extern u8 D_003C5660[], D_003C5680[], D_003C56A0[], D_003C56C0[], D_003C56F0[], D_003C5728[], D_003C5750[], D_003C5780[], D_003C57B0[];
Ent *func_00147778(s32);
s32 func_0010f098(u8 *);
s32 func_001cb440(VM *vm) {
    Sub *s = &vm->u.s;
    s32 y = s->stk[vm->u.h.sp];
    s32 k = s->stk[vm->u.h.sp - 3];
    s32 x = s->stk[vm->u.h.sp - 1];
    Ent *e = func_00147778(s->stk[vm->u.h.sp - 2]);
    s32 n;
    switch (e->t) {
    case 0:
        n = D_002BBAB0 = e->b1;
        D_002BBAC8 = e->s;
        if ((u32)(n - 1) < 16) D_006298F0[k].x40 = func_0010f098(D_003C5660);
        else if ((u32)(n - 142) < 16) D_006298F0[k].x40 = func_0010f098(D_003C5680);
        else if ((u32)(n - 192) < 64) D_006298F0[k].x40 = func_0010f098(D_003C56A0);
        else if ((u32)(n - 81) < 22) D_006298F0[k].x40 = func_0010f098(D_003C5750);
        else if ((u32)(n - 103) < 16) D_006298F0[k].x40 = func_0010f098(D_003C5780);
        else if ((u32)(n - 119) < 16) D_006298F0[k].x40 = func_0010f098(D_003C57B0);
        else if ((u32)(n - 17) < 64) D_006298F0[k].x40 = func_0010f098(D_003C5728);
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].x40 = func_0010f098(D_003C56F0);
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].x40 = func_0010f098(D_003C56C0);
        }
        break;
    }
    vm->u.h.sp -= 4;
    { Spot *p = &D_006298F0[k]; p->x30 = x + p->x40 * 12.0f; p->x34 = y + p->x44 * 12.0f; }

    return 2;
}
