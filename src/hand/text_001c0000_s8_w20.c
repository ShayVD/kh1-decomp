#include "common.h"
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
} VM;
typedef struct {
    s32 x0;
    u16 h4;
    u16 h6;
    u16 h8;
    u8 pada[2];
    u16 hc;
    u16 he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 v30[2];
    u8 pad38[8];
    f32 v40[2];
    u8 pad48[0x38];
    u8 f80[0x10];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} __attribute__((aligned(8))) Obj;
typedef struct { u8 *x0; } P26A0;
extern P26A0 D_002E26A0;
extern Obj D_006298F0[];
s32 func_0017e428(void *, void *);
void func_0017e768(void);

typedef struct {
    void *obj;
    u8 pad4[0x178];
    s32 sp;
    s32 stk[105];
} SubB;
typedef struct {
    s32 x0;
    SubB s;
} VMB;
typedef struct { u16 t:4, s:4, b1:8; } Ent;
extern s32 D_002BBAB0, D_002BBAB8, D_002BBAC8;
extern u8 D_003C5660[], D_003C5680[], D_003C56A0[], D_003C56C0[], D_003C56F0[], D_003C5728[], D_003C5750[], D_003C5780[], D_003C57B0[];
Ent *func_00147778(s32);
s32 func_0010f098(u8 *);
s32 func_001cb440(VMB *vm) {
    SubB *s = &vm->s;
    s32 y = s->stk[vm->s.sp];
    s32 k = s->stk[vm->s.sp - 3];
    s32 x = s->stk[vm->s.sp - 1];
    Ent *e = func_00147778(s->stk[vm->s.sp - 2]);
    s32 n;
    switch (e->t) {
    case 0:
        n = D_002BBAB0 = e->b1;
        D_002BBAC8 = e->s;
        if ((u32)(n - 1) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5660);
        else if ((u32)(n - 142) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5680);
        else if ((u32)(n - 192) < 64) D_006298F0[k].v40[0] = func_0010f098(D_003C56A0);
        else if ((u32)(n - 81) < 22) D_006298F0[k].v40[0] = func_0010f098(D_003C5750);
        else if ((u32)(n - 103) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C5780);
        else if ((u32)(n - 119) < 16) D_006298F0[k].v40[0] = func_0010f098(D_003C57B0);
        else if ((u32)(n - 17) < 64) D_006298F0[k].v40[0] = func_0010f098(D_003C5728);
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].v40[0] = func_0010f098(D_003C56F0);
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_006298F0[k].v40[0] = func_0010f098(D_003C56C0);
        }
        break;
    }
    { f32 a = D_006298F0[k].v40[0];
    vm->s.sp -= 4;
    D_006298F0[k].v30[0] = x + a * 12.0f;
    D_006298F0[k].v30[1] = y + D_006298F0[k].v40[1] * 12.0f; }

    return 2;
}

/* rodata: jtbl 0x4905F0 */
s32 func_001cc640(VM *vm) {
    if (vm->obj == 0) {
        vm->sp -= 2;
        return 2;
    }
    switch (func_0017e428(D_002E26A0.x0 + 16, (u8 *)vm->obj + 16)) {
    case 0: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h8 = 13;
        break;
    }
    case 1: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 225.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[j].h8 = 11;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 45.0f;
        D_006298F0[i].h8 = 1;
        break;
    }
    case 2: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 135.0f;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[j].h8 = 13;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 315.0f;
        D_006298F0[i].h8 = 3;
        break;
    }
    case 3: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 45.0f;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 1;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 225.0f;
        D_006298F0[i].h8 = 11;
        break;
    }
    case 4: {
        s32 i, j;
        j = vm->stk[vm->sp - 1];
        i = vm->stk[vm->sp];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[j].v40[0] = 10.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h8 = 13;
        func_0017e768();
        break;
    }
    }
    vm->sp -= 2;
    return 2;
}
#include "data/data_002B.h"
#include "data/data_003C.h"
