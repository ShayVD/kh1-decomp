/* Object commands: the 32 command nodes D_00525A40 (func_00133868 queues
 * one), the 32 triples D_00526640 (func_001337e0), the per-frame task
 * func_00133a88 that runs them (func_00134718 resets both and installs the
 * tasks), and a node chain an object drags (func_001342c8). Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/types/nostrict_text_00130000_h32.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/fvec.h"
#include "data/pieces/D_002BD250.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002C58D0.h"
#include "vm/script_vm.h"
#include "data/types/nostrict_text_00110000_c01.h"

/* func_00133868 (from hand/nostrict/text_00130000_h32.c). */
typedef struct {
    u8 pad000[0x440];
    W32Node *head;
} W32List;
extern W32Node D_00525A40[32];
W32Node *func_00133868(W32List *l, W32V32 *v) {
    W32Node *n = D_00525A40;
    W32Node *p;
    s32 i;
    for (i = 0; i < 32; i++, n++) {
        if (n->used == 0) {
            if (l->head == 0) {
                l->head = n;
                n->prev = 0;
            } else {
                for (p = l->head; p->next; p = p->next);
                p->next = n;
                n->prev = p;
            }
            n->used = 1;
            n->v = *v;
            n->next = 0;
            n->x4 = 0;
            return n;
        }
    }
    return 0;
}

/* func_00133a88 (from hand/nostrict/text_00110000_c01.c). */
typedef struct {
    u8 pad[0x170];
    u64 lo : 32;
    u64 b32 : 1;
    u64 b33 : 3;
    u64 b36 : 1;
    u64 b37 : 1;
    u64 b38 : 1;
} C01Sub148;
typedef struct { u8 pad[0x18]; u8 n; u8 id[1]; } C01Cnt;
typedef struct { u8 pad[0x10]; f32 x10; u8 pad14[0xc8 - 0x14]; C01Cnt *xc8; } C01Sub6C;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 lo : 4;
    u32 b4 : 1;
} __attribute__((aligned(8))) C01Bits160;
typedef struct Actor_33a88 {
    u32 x0;
    u8 pad4[0x38];
    f32 x3c;
    f32 x40[4];
    u8 pad50[0x1c];
    C01Sub6C *x6c;
    u8 pad70[0x30];
    f32 xa0[4];
    u8 padb0[0x80];
    C01Sub130 *x130;
    u8 pad134[0x14];
    C01Sub148 *x148;
    u8 pad14c[0x14];
    C01Bits160 x160;
    u8 pad168[0x1e8];
    f32 x350[4];
    u8 pad360[0x10];
    u64 x370;
    u8 pad378[0x48];
    f32 x3c0[3];
    f32 x3cc;
    s32 x3d0;
    u8 pad3d4[0x6c];
    u64 x440;
} C01Ply;
typedef struct {
    u32 id : 8;
    u32 v : 24;
    s32 x4;
    u8 pad8[0x10 - 0x8];
    f32 x10[4];
} __attribute__((aligned(8))) C01Cmd;  /* a VmMsg as this file reads it: v (u32:24) */
typedef C01Ply C01Act3;
typedef struct {
    u8 pad[0x30];
    s8 x30[4];
    s8 x34[4];
    u8 pad38[0x40 - 0x38];
    f32 x40[4];
} C01Ev;
typedef struct { u8 pad[4]; f32 x4; } C01Snd;
extern C01CmdInfo D_0030433C[];
C01Act3 *func_00123488(s32);
void func_001336d8(void);
void func_00133708(void);
void func_002675a8(f32 *, f32 *);
void func_00123a88(s32, f32 *);
void func_001339c0(C01Act3 *);
f32 atan2f(f32, f32);
f32 func_00120c88(f32);
void func_00133a38(C01Cmd *, f32, f32);
C01Snd *func_00130340(C01Act3 *, s32, f32);
void func_00135800(C01Act3 *, f32, f32);
void func_00171f58(C01Act3 *);
void func_00153d88(C01Act3 *);
void func_0014cce0(C01Act3 *, f32);
void func_00133978(C01Act3 *, s32);
void func_00133a00(C01Act3 *);
void func_00135df0(C01Act3 *, f32 *);
void func_001358b8(C01Act3 *, s32);
void func_00124060(C01Act3 *, f32 *);
void func_00142388(f32 *, f32 *);
void func_001223b8(void);
void func_0014f658(C01Act3 *, s32);
#define func_00133868 ((C01Ev *(*)(C01Act3 *, C01Cmd *)) func_00133868)
void func_00133a88(void) {
    C01Cmd *c;
    C01Act3 *a;
    C01Ev *e;
    C01Snd *s;
    f32 v[4];
    f32 f;
    s32 i;

    while ((c = (C01Cmd *)func_001c45e8()) != 0) {
        a = func_00123488(c->x4);
        if (D_0030433C[c->id].x0 && !a) {
            func_001c4788(c);
            continue;
        }
        switch (c->id) {
        case 0:
            func_001336d8();
            break;
        case 1:
            func_00133708();
            break;
        case 3:
            func_002675a8(v, c->x10);
            v[3] = a->x3c;
            func_00123a88(c->x4, v);
            break;
        case 4:
            func_001339c0(a);
            func_00133a38(c, func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c), (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 5:
            a->x0 &= ~4;
            func_00130340(a, c->v, 0.0f);
            break;
        case 6:
            a->x0 |= 1;
            func_00135800(a, 1.0f, 0.0f);
            break;
        case 7:
            a->x0 &= ~1;
            break;
        case 8:
            a->x0 |= 2;
            break;
        case 9:
            a->x0 &= ~2;
            break;
        case 10:
            a->x0 &= ~0x20;
            break;
        case 11:
            a->x0 |= 0x20;
            break;
        case 13:
            a->x440 &= ~(1ULL << 32);
            break;
        case 14:
            a->x440 |= 1ULL << 32;
            a->x0 &= ~4;
            if (D_002E26A0[1] == a || D_002E26A0[2] == a) {
                func_00171f58(a);
                func_00153d88(a);
            }
            break;
        case 15:
            a->x440 &= ~(1ULL << 33);
            break;
        case 16:
            a->x440 |= 1ULL << 33;
            break;
        case 12:
            func_0014cce0(a, fabsf(c->x10[1]));
            func_002675a8(a->x3c0, c->x10);
            a->x3c0[1] = a->x3cc = 0.0f;
            if (!((a->x440 >> 33) & 1)) {
                a->x3d0 = 0;
                func_00130340(a, 0x10004, 0.0f);
            }
            a->x0 &= ~0x400;
            break;
        case 2:
            func_00133978(a, 2);
            c->x10[3] = c->x10[3] / 180.0f * 3.1415928f;
            func_00133868(a, c);
            c = 0;
            break;
        case 17:
            a->x0 &= ~4;
            func_00130340(a, c->v, c->x10[0]);
            break;
        case 18:
            func_00133a00(a);
            break;
        case 19:
            a->x0 &= ~4;
            s = func_00130340(a, c->v, c->x10[0]);
            s->x4 = c->x10[1];
            break;
        case 20:
            a->x160.b4 ^= 1;
            break;
        case 21:
            func_001339c0(a);
            f = func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c);
            if (f > 0.0f) f -= 6.2831855f;
            func_00133a38(c, f, (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 22:
            func_001339c0(a);
            f = func_00120c88(atan2f(c->x10[0], c->x10[2]) - a->x3c);
            if (f < 0.0f) f += 6.2831855f;
            func_00133a38(c, f, (u32)c->v);
            func_00133868(a, c);
            c = 0;
            break;
        case 23:
            func_00133978(a, 23);
            func_00133978(a, 44);
            e = func_00133868(a, c);
            func_00135df0(a, v);
            for (i = 0; i < 4; i++) {
                e->x30[i] = v[i];
                e->x34[i] = c->x10[i] * 128.0f;
            }
            a->x370 |= 1ULL << 52;
            c = 0;
            break;
        case 24:
            a->x370 &= ~(1ULL << 52);
            break;
        case 27:
            a->x0 &= ~0x10;
            break;
        case 28:
            a->x0 |= 0x10;
            break;
        case 29:
            func_001358b8(a, (u32)c->v);
            if (c->x10[0] > 0.0f) {
                func_00133868(a, c);
                c = 0;
            }
            break;
        case 30:
            func_00133978(a, 30);
            e = func_00133868(a, c);
            c = 0;
            func_002675a8(e->x40, a->x40);
            break;
        case 31:
            func_00133868(a, c);
            c = 0;
            break;
        case 32:
            func_002675a8(v, c->x10);
            v[3] = a->x3c;
            func_00124060(a, v);
            break;
        case 33:
            a->x0 &= ~0x200;
            break;
        case 34:
            a->x0 |= 0x200;
            break;
        case 35:
            a->x0 &= ~0x1000000;
            break;
        case 36:
            a->x0 |= 0x1000000;
            break;
        case 37:
            a->x0 &= ~0x200000;
            break;
        case 38:
            a->x0 |= 0x200000;
            break;
        case 39:
            func_00142388(c->x10, a->x350);
            break;
        case 40:
            func_001223b8();
            break;
        case 41:
            func_0014f658(a, (u32)c->v);
            break;
        case 42:
            a->x0 &= ~0x40;
            break;
        case 43:
            a->x0 |= 0x40;
            break;
        case 44:
            func_00133978(a, 23);
            func_00133978(a, 44);
            e = func_00133868(a, c);
            for (i = 0; i < 4; i++) {
                e->x30[i] = a->xa0[i] * 128.0f;
                e->x34[i] = c->x10[i] * 128.0f;
            }
            c = 0;
            break;
        }
        if (c) func_001c4788(c);
    }
}
#undef func_00133868

