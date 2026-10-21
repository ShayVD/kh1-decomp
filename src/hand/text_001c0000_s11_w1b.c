#include "common.h"
/* func_001c3b10 (s11w1, hand strict): from s10 r2_3 (4w nostrict, 2w strict); the x18 loop stores the msg fields straight from w in struct order (m.x = w->x0; m.v[0..2] = w->f14..f1c), which fixes the lwc1 x14/x18 issue order and FP registers. */

typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0xc];
    f32 f14, f18, f1c, f20;
    u8 pad24[0x4c];
    s8 *code;
    u8 pad74[0x17c - 0x74];
    s32 pc;
    u8 pad180[0x2f4 - 0x180];
    f32 x2f4;
    u8 pad2f8[0x328 - 0x2f8];
    union { u64 x; s32 i; struct { u32 b0:1, rest:31; u32 hi; } __attribute__((aligned(8))) b; } fl;
    u8 pad330[0x350 - 0x330];
} __attribute__((aligned(8))) VMa;

typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    u8 pad3038[8];
    s32 x3040;
    s32 x3044;
    s32 x3048;
    s32 x304c;
    s32 x3050;
    s32 x3054;
    s32 x3058;
    s32 x305c;
    s32 x3060;
    s32 x3064;
    s32 x3068;
    s32 x306c;
    union { u64 x; struct { u32 lo; u32 p0:6, b38:1, b39:1, p40:3, b43:1, p44:9, b53:1, p54:10; } __attribute__((aligned(8))) f; } f3070;
    union { u64 x; struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, brest:21; u32 hi; } __attribute__((aligned(8))) b; } f3078;
    u8 pad3080[0x3148 - 0x3080];
    u32 x3148;
    u8 pad314c[0x316c - 0x314c];
    void *x316c;
} BigA;

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct {
    u8 pad0[4];
    u32 x4;
    u32 x8;
    u8 padc[0x34];
    s32 x40[3];
    u8 pad4c[0x14];
    s32 x60[3];
} S5BB0;
typedef struct {
    u8 pad0[0x10];
    VMa *vm;
    s32 n;
    s32 x18;
} Task;

extern BigA D_00389C90;
#include "data/pieces/D_0038D170.h"
extern S5BB0 D_002C5BB0;
extern u32 D_003C39A8;
#include "data/pieces/D_003C21A8.h"
#include "data/pieces/D_00388480.h"
#include "data/pieces/D_00389C80.h"
extern f32 D_002BBDFC;
extern s32 (*D_0037A198[])(VMa *, s32);
Msg *func_001c4730(void);
void func_001c4788(Msg *);
s32 func_001c4640(Msg *);
void func_001cebe8(void);
void func_001cff28(void);
void func_001cfff8(void);
void func_001ca800(void);
void func_001dcea8(VMa *);
void func_001dcfd0(VMa *);
s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);

#define FLUSH() \
    for (i = 0; i < n; i++) { \
        if (!done[i]) func_001c4788(&msgs[i]); \
    }

#define RESTORE() \
    D_00389C90.x3040 = D_00389C90.x3044; \
    D_00389C90.x3048 = D_00389C90.x3050; \
    D_00389C90.x304c = D_00389C90.x3054; \
    D_00389C90.x305c = D_00389C90.x3064; \
    D_00389C90.x3060 = D_00389C90.x3068; \
    (*(u32 *)&D_00389C80) = D_003C39A8; \
    for (i = 0; i < ((u32)D_00389C80); i++) { \
        ((s32 *)&D_00388480)[i] = ((s32 *)&D_003C21A8)[i]; \
    }

s32 func_001c3b10(Task *t) {
    Msg m;
    Msg msgs[256];
    s32 done[256];
    VMa *vm;
    VMa *w;
    Msg *p;
    s32 n = 0;
    s32 i, j, r, k;
    u32 c;
    s32 *pn;
    s32 *d;

    D_00389C90.x316c = t;
    D_002C5BB0.x4 &= D_00389C90.x3148;
    D_002C5BB0.x8 &= D_00389C90.x3148;
    if (~(D_00389C90.x3148 >> 23) & 1) {
        for (i = 0; i < 3; i++) {
            D_002C5BB0.x40[i] = 0;
            D_002C5BB0.x60[i] = 0;
        }
    }
    vm = t->vm;
    pn = &t->n;
    p = func_001c4730();
    while (p) {
        msgs[n++] = *p;
        p = func_001c4730();
    }
    for (i = 255; i >= 0; i--) {
        done[i] = 0;
    }
    if (D_00389C90.f3070.f.b43 == 1) func_001cebe8();
    if (D_00389C90.f3070.f.b38 == 1) func_001cff28();
    if (D_00389C90.f3070.f.b39 == 1) func_001cfff8();
    if (D_00389C90.f3078.b.b10) func_001ca800();
    if (D_00389C90.f3070.f.b53) return 0;
    for (i = 0; i < *pn; i++, vm++) {
        if ((s32)(vm->fl.x >> 3) & 1) {
            if (i != 0) continue;
            if (t->x18) {
                D_00389C90.x3034 = 0;
                w = ((VMa *)&D_0038D170);
                for (j = 1, w++; j < t->n; j++, w++) {
                    if (w->fl.b.b0 == 1) {
                        m.type = 2;
                        m.val = (u32)w->f20;
                        m.x = w->x0; m.v[0] = w->f14; m.v[1] = w->f18; m.v[2] = w->f1c;
                        m.v[3] = 10.0f;
                        func_001c4640(&m);
                    }
                }
                FLUSH();
                return 0;
            }
            RESTORE();
            FLUSH();
            return 4;
        }
        if ((s32)(vm->fl.x >> 8) & 1) continue;
        func_001dcea8(vm);
        func_001dcfd0(vm);
        if ((vm->fl.x & 0x14) == 4) {
            vm->x2f4 -= D_002BBDFC;
            if (vm->x2f4 > 0.0f) continue;
            vm->fl.x &= ~4;
        }
        j = 0;
        if (n > 0) { do {
            p = &msgs[j];
            switch (p->type) {
            case 2:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~1;
                    done[j] = 1;
                    break;
                }
                break;
            case 4:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            case 21:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            case 22:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            }
            j++;
        } while (j < n); }
        while (1) {
            k = func_001c1ce8(vm->code, vm->pc);
            r = D_0037A198[k](vm, func_001c1cf8(vm->code, vm->pc));
            if (r & 2) vm->pc++;
            if (r & 4) break;
            if (r & 8) {
                RESTORE();
                FLUSH();
                return 4;
            }
        }
    }
    FLUSH();
    return 0;
}
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
