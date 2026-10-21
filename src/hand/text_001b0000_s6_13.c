#include "common.h"
#include "data/bss_0062.h"

typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    s32 x3038;
    u8 pad303c[0x3070 - 0x303c];
    u64 f3070;
    u8 pad3078[0x316c - 0x3078];
    s32 x316c;
    u8 pad3170[0x3384 - 0x3170];
    struct { s32 obj; s32 x4; s32 snd; s32 ret; s32 x10; s32 h; } e[8];
    s32 x3444;
} Big;
extern Big D_00389C90;
#include "data/pieces/D_0037A378.h"
extern s32 D_002C5958;
s32 func_001c4788(void *);

typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
    u8 pad12[4];
    V4 v16;
    V4 v32;
    f32 f48;
    char name[32];
    u8 pad84[12];
} Out;
#include "data/types/text_001b0000_s6_13.h"
typedef struct { u8 pad[4]; u8 type; u8 pad5[2]; u8 b7; u8 pad8[5]; u8 b13; u8 pad14[10]; f32 f24; } ItemInfo;
extern CdEnt *D_006257D0; /* src/data/bss_0062.c: u8 *D_006257D0 */
extern CdEnt D_00621320, D_00622290;
extern Out D_00623E40[];
extern s32 D_00625640, D_00625648[], D_00623E30, D_00623228;
extern Ent D_00623230[];
void func_001bc900(CdEnt *, Out *);
s32 func_001ba3f0(s32);
void func_001ba060(CdEnt *, s32);
CdEnt *func_001ba9d8(s32);
ItemInfo *func_001bb658(s32);
s32 func_001bb740(void);
u8 func_001be5c8(s32);
u8 func_001be5d0(s32);
void func_001bd010(CdEnt *);
/* rodata */
void func_001bd470(void) {
    s32 i, k, n, t;
    ItemInfo *it;
    Ent *e = D_00623230;
    Out *o;
    Out *p = D_00623E40;
    s32 x;
    s32 buf[16];
    D_00625640 = 0;
    func_001bc900(D_006257D0, &p[0]);
    p[0].b8 = 1;
    k = 0;
    for (i = 71; i < 119; i++) {
        if (func_001ba3f0(i) > 0) {
            func_001ba060(&D_00621320, i - 71);
            func_001bc900(&D_00621320, &p[k + 1]);
            D_00625648[k] = i - 71;
            p[k + 1].b8 = 1;
            k++;
        }
    }
    D_00625640 = k;
    for (i = 0; i < 10; i++) {
        func_001bc900(func_001ba9d8(i), &p[k + 1 + i]);
        p[k + 1 + i].b8 = 0;
    }
    if (func_001ba3f0(70) > 0) D_00623E30 = k + 11;
    else if (func_001ba3f0(69) > 0) D_00623E30 = k + 6;
    else D_00623E30 = k + 2;
    it = func_001bb658(0);
    n = 0;
    o = &D_00623E40[1];
    for (i = 0; i < func_001bb740(); i++) {
        if (func_001ba3f0(i) <= 0) continue;
        e->b0 = func_001ba3f0(i);
        x = it[i].b7;
        e->b6 = i;
        { s32 a; a = (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; e->b1 = a; }
        e->b2 = 0;
        e->b3 = 0;
        e->b4 = 0;
        e->b5 = it[i].type;
        e->b7 = func_001be5c8(i);
        e->b8 = func_001be5d0(i);
        if ((u32)(i - 71) < 48) {
            e->b2 = o->b6;
            e->b3 = o->b5;
            e->b4 = o->b11;
            o++;
        } else {
            switch (i) {
            case 58: e->b4 = 1; break;
            case 59: e->b4 = 2; break;
            case 61: e->b4 = 1; break;
            case 62: e->b4 = 2; break;
            case 60: case 63: e->b4 = 3; break;
            }
            if (it[i].type == 1) e->b2 = 4;
            else {
                t = it[i].f24;
                if (t <= 0) e->b2 = 0;
                else if (t < 10) e->b2 = 1;
                else if (t < 20) e->b2 = 2;
                else e->b2 = 3;
            }
            if (it[i].type == 2 || it[i].type == 6) {
                if (it[i].b13 < 100) e->b3 = 1;
                else if (it[i].b13 < 120) e->b3 = 2;
                else e->b3 = 3;
            }
        }
        e++;
        n++;
    }
    D_00623228 = n;
    func_001bd010(&D_00622290);
}

typedef struct { u16 used; u16 h2; u16 h4; u8 pad6[26]; void (*fn)(void); u8 pad36[12]; } Slot;
extern Slot *D_0037A16C;
CONTEXT_ONLY void func_001bfcd8(void) { D_0037A16C = 0; }
CONTEXT_ONLY void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
    }
}
void func_001c0010(void) {
    s32 i;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].used != 0) func_001bffa0(i);
    }
    func_001bfcd8();
}

typedef struct {
    u8 pad[380]; s32 pc; s32 sp; s32 stack[33]; s32 regs[26]; s32 vars[32]; s32 vidx;
    s32 w756; s32 ret[8]; s32 depth; u8 pad796[12]; u64 flags;
} VmA;
u8 *func_00232cc0(s32);
s32 func_001c1330(VmA *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s32 bit = a % 8;
    s32 q = a / 8;
    a = q - 3392;
    v->stack[++v->sp] = (*(s8 *)(p2 + a) >> bit) & 1;
    return 2;
}

void func_001c2d20(s8 *p, s32 *cnt, s8 **tbl) {
    s32 n = *(s32 *)p;
    s32 i;
    p += 4;
    *cnt = n;
    for (i = 0; i < n; i++) {
        tbl[i] = p;
        {
            u8 c;
            for (;;) {
                s8 t = *p;
                c = *p;
                if (t == 4 || t == 0) break;
                if ((u32)(c - 5) < 3) p += 2;
                else if ((s8)c == 11) p += 3;
                else if ((s8)c == 10) { p++; if (*p == 0) p += 2; }
                else if ((s8)c == 13) p += 3;
                else p += (u32)(c - 9) < 23;
                p++;
            }
        }
        p++;
    }
}

s8 *func_001c2df0(s8 *p, s32 k) {
    s32 n = *(s32 *)p;
    s32 i;
    p += 4;
    for (i = 0; i < n; i++) {
        if (i == k) return p;
        {
            u8 c;
            for (;;) {
                s8 t = *p;
                c = *p;
                if (t == 4 || t == 0) break;
                if ((u32)(c - 5) < 3) p += 2;
                else if ((s8)c == 11) p += 3;
                else if ((s8)c == 10) { p++; if (*p == 0) p += 2; }
                else if ((s8)c == 13) p += 3;
                else p += (u32)(c - 9) < 23;
                p++;
            }
        }
        p++;
    }
    return 0;
}

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
    f32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VmC;
typedef struct { u8 type; u8 pad[3]; s32 x4; } MsgC;
#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003A7990.h"
extern s32 D_003B4D90, D_003C21A0;
extern s32 (*D_0037A198[])(VmC *, s32);
extern f32 D_002BBDFC;
s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);
void *func_0011ef10(s32, void *);
s32 func_001c5b88(void);
MsgC *func_001c4730(void);
s32 func_001c3408(void) {
    VmC *e;
    s32 *cnt;
    s32 i, op, arg, r;
    s32 done;
    MsgC *m;
    if ((s32)(D_00389C90.f3070 >> 40) & 1) {
        D_00389C90.f3070 &= ~0x40000000000ULL;
        return 4;
    }
    D_00389C90.x316c = 0;
    if (D_00389C90.x3038 == 0) { e = ((VmC *)&D_003A7990); cnt = &D_003B4D90; }
    else { e = ((VmC *)&D_003B4DA0); cnt = &D_003C21A0; }
    done = 0;
    m = func_001c4730();
    if (((s32)(D_00389C90.f3070 >> 37) & 1) == 1U) func_0011ef10(99999, func_001c5b88);
    for (i = 0; i < *cnt; i++, e++) {
        if (e->b3) {
            if (i != 0) continue;
            if (D_00389C90.x3038 != 0) {
                D_00389C90.x3038 = 0;
                D_00389C90.f3070 &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            } else {
                D_00389C90.f3070 &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            }
        }
        if (e->b8) continue;
        if (e->b2) {
            e->x2f4 -= D_002BBDFC;
            if (e->x2f4 > 0.0f) continue;
            e->b2 = 0;
        }
        if (m) {
            switch (m->type) {
            case 2:
                if (m->x4 == e->x0) { done = 1; e->b0 = 0; }
                break;
            case 4:
                if (m->x4 == e->x0) { done = 1; e->b1 = 0; }
                break;
            case 21:
                if (m->x4 == e->x0) { done = 1; e->b1 = 0; }
                break;
            case 22:
                if (m->x4 == e->x0) { done = 1; e->b1 = 0; }
                break;
            }
        }
        while (1) {
            op = func_001c1ce8(e->code, e->pc);
            arg = func_001c1cf8(e->code, e->pc);
            r = D_0037A198[op](e, arg);
            if (r & 2) e->pc++;
            if (r & 4) break;
            if ((r & 8) || ((s32)(D_00389C90.f3070 >> 40) & 1)) {
                D_00389C90.f3070 &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            }
        }
    }
    if (m && !done) func_001c4788(m);
    return 0;
}

typedef struct { u64 a, b, c, d; } MsgQ; extern s32 D_006297F0, D_006297F4; extern MsgQ D_006277F0[256];
s32 func_001c4788(void *m) {
    if ((D_006297F4 + 1) % 256 == D_006297F0) return -1;
    D_006277F0[D_006297F4] = *(MsgQ *)m;
    D_006297F4 = (D_006297F4 + 1) % 256;
    return 0;
}

typedef struct { s32 x0; s32 id; } Obj;
#include "data/pieces/D_0039A580.h"
typedef VM_39a580 VmE;
#include "data/pieces/D_0038D170.h"
extern s32 D_0039A570, D_003A7980;
extern s32 D_0037A190;
CONTEXT_ONLY s32 func_001c1ce8(s8 *a, s32 b) { return a[b * 4 + 3]; }
s32 func_001c19f8(VmE *, s32);
void func_0012cb78(Obj *, s32);
void func_0012cc38(s32, s32);
void func_0012ccb0(s32);
s32 func_001c4ed0(Obj *o, s32 unused, s32 a2) {
    VmE *vm;
    VmE *t;
    s32 n, i;
        if (!((D_00389C90.f3070 >> 59) & 1)) return 0;
    if (a2 < -1) return 0;
    if ((*(Bits_37a378 *)&D_0037A378).b2 || (D_002C5958 & 0x12000)) return 0;
    if (D_00389C90.x3034 == 0) {
        vm = ((VmE *)&D_0038D170);
        n = D_0039A570;
    } else {
        vm = &D_0039A580;
        n = D_003A7980;
    }
    for (i = 0; i < n; i++) {
        if (vm[i].id == o->id) break;
    }
    if (i >= n) return 0;
    t = &vm[i];
    if (t->x318 != 3 || a2 >= 0) {
        if (D_0037A190 == 0) {
            if (func_001c1ce8(t->code, t->xa0) != 5) {
                vm->stk[++vm->sp] = 3;
                vm->stk[++vm->sp] = i;
                func_001c19f8(vm, 9);
                D_00389C90.x3444 = a2;
            }
        }
        if (a2 != -1) D_0037A190 = 1;
    }
    for (i = 0; i < 8; i++) {
        if (D_00389C90.e[i].obj != (s32)o) continue;
        D_00389C90.e[i].obj = 0;
        if (D_00389C90.e[i].h >= 0) {
            func_0012cb78(o, D_00389C90.e[i].h);
            D_00389C90.e[i].h = -1;
        }
        if (a2 != -1) D_00389C90.e[i].snd = -1;
        if (D_00389C90.e[i].snd >= 0) {
            func_0012cc38(3, D_00389C90.e[i].snd);
            D_00389C90.e[i].snd = -1;
            if (D_00389C90.e[i].x10 == 0) func_0012ccb0(3);
            return D_00389C90.e[i].ret;
        }
    }
    return 0;
}
#include "data/data_0037.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
