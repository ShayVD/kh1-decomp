#include "common.h"
#include "vm/script_vm.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x154];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    s32 x0;
    u8 pad4[8];
    f32 f0c;
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
} Fx;
typedef struct {
    s32 key;
    s32 x4;
    s32 x8;
    s32 xc;
    f32 v[2][4];
} __attribute__((aligned(8))) E48;
typedef struct {
    u8 pad0[0x3070];
    union { u64 x; s32 i[2]; } f3070;
    union { u64 x; s32 i[2]; } f3078;
    u8 pad3080[0x18];
    s32 idx;
    s32 cnt;
    f32 d[3];
    Fx *ptrs[4];
    u8 pad30bc[0x6c];
    s32 cnt2;
    s32 step2;
    s32 cnt3;
    s32 step3[3];
    u8 pad3140[0x18];
    void *f3158;
    u8 pad315c[0x1c];
    s32 n3178;
    s32 pad317c;
    E48 ent3180[1];
} Big;
extern Big D_00389C90;
typedef struct { s32 v[3]; s32 f0c; } Cam;
extern Cam D_002BC080;
s32 func_001d01e8(VM *vm) {
    VmMsg m;
    m.type = 30;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 3] / 100.0f;
    m.v[1] = vm->stk[vm->sp - 2] / 100.0f;
    m.v[2] = vm->stk[vm->sp - 1] / 100.0f;
    func_001c4640(&m);
    vm->sp -= 4;
    return 2;
}
s32 func_001d0070(VM *vm) {
    s32 n = vm->stk[vm->sp];
    D_00389C90.cnt3 = n;
    D_00389C90.step3[0] = (vm->stk[vm->sp - 3] - D_002BC080.v[0]) / n;
    D_00389C90.step3[1] = (vm->stk[vm->sp - 2] - D_002BC080.v[1]) / n;
    D_00389C90.step3[2] = (vm->stk[vm->sp - 1] - D_002BC080.v[2]) / n;
    D_00389C90.f3070.x |= 0x8000000000ULL;
    vm->sp -= 4;
    return 2;
}
s32 func_001d02d0(VM *vm) {
    VmMsg m;
    m.type = 31;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2] * 2.0f;
    m.v[1] = vm->stk[vm->sp - 1] * 2.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}
s8 *func_00232cc0(s32);
s32 func_001d06f0(VM *vm) {
    s32 v = vm->stk[vm->sp];
    s32 q = v / 8;
    s32 sh = 7 - v % 8;
    if (v >= 3072) {
        vm->sp--;
        return 2;
    }
    vm->stk[vm->sp] = (func_00232cc0(1)[q] >> sh) & 1;
    return 2;
}
VM *func_001e98d0(s32, s32);
s32 func_001d14f0(VM *vm) {
    VmMsg m;
    s32 b = vm->stk[vm->sp - 1];
    VM *p = func_001e98d0((s32)(vm->flags.x >> 5) & 1, vm->stk[vm->sp]);
    if (p) {
        m.type = 4;
        m.val = (u32)(b * 2);
        m.x = vm->x0;
        m.v[0] = p->obj->pos[0] - vm->obj->pos[0];
        m.v[1] = p->obj->pos[1] - vm->obj->pos[1];
        m.v[2] = p->obj->pos[2] - vm->obj->pos[2];
        m.v[3] = 1.0f;
        vm->flags.x |= 2;
        func_001c4640(&m);
    }
    vm->sp -= 2;
    return 2;
}
void func_001e58c0(s32);
s32 func_001d34b0(VM *vm) {
    switch (vm->stk[vm->sp]) {
    case 0:
        func_001e58c0(0);
        break;
    case 1:
        func_001e58c0(1);
        break;
    case 2:
        func_001e58c0(2);
        break;
    case 3:
        func_001e58c0(3);
        break;
    }
    vm->sp--;
    return 2;
}
s32 func_001d4b60(VM *vm) {
    VmMsg m;
    m.type = 32;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2];
    m.v[3] = 1.0f;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}
void func_001d3e30(VM *);
s32 func_001d3ff0(VM *vm) {
    vm->flags.x |= 0x200;
    vm->f14 = vm->stk[vm->sp - 2];
    vm->f18 = vm->stk[vm->sp - 1];
    vm->f20 = vm->stk[vm->sp - 3] / 50.0f;
    vm->f1c = vm->stk[vm->sp];
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    func_001d3e30(vm);
    vm->sp -= 4;
    return 2;
}
typedef struct { s32 x0; s32 x4; u8 pad8[8]; f32 pos[3]; u8 pad1c[0x354]; u64 f370; } Obj;
Obj *func_00123220(Obj *);
s32 func_001d4e60(VM *vm) {
    VmMsg m;
    Obj *p;
    for (p = func_00123220(0); p; p = func_00123220(p)) {
        m.type = 7;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
        m.type = 9;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
    }
    return 2;
}
s32 func_001d4f10(VM *vm) {
    VmMsg m;
    Obj *p;
    for (p = func_00123220(0); p; p = func_00123220(p)) {
        m.type = 6;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
        m.type = 8;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
    }
    return 2;
}
Obj *func_001230a0(Obj *);
s32 func_001d59a0(VM *vm) {
    VmMsg m;
    Obj *p;
    m.type = 14;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (((s32)(p->f370 >> 37) & 3) == 2) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}
s32 func_001d5a50(VM *vm) {
    VmMsg m;
    Obj *p;
    m.type = 13;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (((s32)(p->f370 >> 37) & 3) == 2) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}
s32 func_00123618(s32);
s32 func_001d7040(VM *vm) {
    VmMsg m;
    Obj *p;
    m.type = 7;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}
#include "data/pieces/D_00304BE8_s.h"
s32 func_001d6a60(VM *vm) {
    s32 k = vm->stk[vm->sp];
    s32 item = vm->stk[vm->sp - 1];
    s32 r = 0;
    s32 j;
    for (j = 0; j < D_00304BE8->m[k].sub.x21; j++) {
        if (D_00304BE8->m[k].sub.x22[j] == 0) {
            D_00304BE8->m[k].sub.x22[j] = item;
            r = 0;
            break;
        }
    }
    if (j == D_00304BE8->m[k].sub.x21) {
        s32 v = D_00304BE8->items[item] + 1;
        if (v >= 100) {
            D_00304BE8->items[item] = 99;
            r = 1;
        } else {
            D_00304BE8->items[item] = v;
            r = 0;
        }
    }
    vm->sp--;
    vm->stk[vm->sp] = r;
    return 2;
}
s32 func_001d7118(VM *vm) {
    VmMsg m;
    Obj *p;
    m.type = 6;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}
f32 func_001e9e58(f32 *, f32 *);
s32 func_001d7320(VM *vm) {
    Obj *p;
    s32 found = 0;
    f32 best = -1.0f;
    f32 d;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            if (!found) {
                found = 1;
                best = func_001e9e58(vm->obj->pos, p->pos);
            } else {
                d = func_001e9e58(vm->obj->pos, p->pos);
                if (d < best) best = d;
            }
        }
    }
    vm->sp++;
    vm->stk[vm->sp] = best;
    return 2;
}
s32 func_001331d8(s32, s32, void *);
void func_001d75a0(void);
s32 func_001d75d0(VM *vm) {
    if (func_001331d8(vm->stk[vm->sp - 1], vm->stk[vm->sp], func_001d75a0)) {
        D_00389C90.f3070.x &= ~0x2000000000000000ULL;
    } else {
        D_00389C90.f3070.x |= 0x2000000000000000ULL;
    }
    vm->sp -= 2;
    return 2;
}
s32 func_001d6250(VM *vm) {
    s32 n = D_00389C90.n3178;
    D_00389C90.ent3180[n].key = vm->stk[vm->sp - 6];
    D_00389C90.ent3180[n].v[0][0] = vm->stk[vm->sp - 5];
    D_00389C90.ent3180[n].v[0][1] = vm->stk[vm->sp - 4];
    D_00389C90.ent3180[n].v[0][2] = vm->stk[vm->sp - 3];
    D_00389C90.ent3180[n].v[1][0] = vm->stk[vm->sp - 2];
    D_00389C90.ent3180[n].v[1][1] = vm->stk[vm->sp - 1];
    D_00389C90.ent3180[n].v[1][2] = vm->stk[vm->sp];
    D_00389C90.n3178++;
    vm->sp -= 7;
    return 2;
}
