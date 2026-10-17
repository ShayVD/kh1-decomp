#include "common.h"

typedef struct { u32 w0; u32 w4; u32 w8; } C01W3;
typedef struct { u32 x0; u32 x4; u32 x8; } C01Pad;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; u8 pad[0x118 - 0x10]; } C01Q;
typedef struct { C01Q *p; u8 pad[28]; } C01Ctx;
typedef struct { u8 pad[0x70]; s32 x70; u8 pad2[0x370 - 0x74]; u64 x370; } C01Obj;

extern u32 D_002E3168;
extern C01W3 D_002E3190;
extern u32 D_00524F48;
extern C01W3 D_002C5958;
extern u32 D_002C5960;
extern u16 *D_002E31A0;
extern u16 *D_002E319C;
extern s32 D_002E31B0;
extern C01Obj *D_002E26A0;
extern s32 D_002E27A8;
extern C01Pad D_002C5BB0;
extern s32 D_00524F50;
extern C01Ctx D_002E3170;
extern C01Q D_002E2FD8[];
extern C01Ctx *D_00524F40;

void *memset(void *, s32, u32);
void func_0012ca38(void);
s32 func_00122ff8(s32);
void func_0012fc58(void);
void func_0012dc70(void);
s32 func_001375d8(C01Obj *);
s32 func_0012e1b0(C01Pad *);
void func_0012e120(void);
u16 *func_001478c8(s32);
void func_0012dea0(C01Q *, s32);
void func_0012f700(C01Pad *);

void func_0012ca38(void) {
    s32 i;
    for (i = 7; i >= 0; i--) ((s32 *)&D_002E3170)[i] = 0;

    D_00524F40 = &D_002E3170;
    D_002E31A0 = 0;
    D_002E3170.p = D_002E2FD8;
    D_002E2FD8[0].xc = 0;
    D_002E319C = 0;

}
s32 func_0012e1b0(C01Pad *p) { return 0; }

s32 func_0012e4b0(void) {
    C01Obj *o;
    u32 mask;
    s32 k;
    C01Pad *pad;

    D_002E3168 = 0;
    memset(&D_002E3190, 0, 12);
    D_002E3190.w0 |= 0x2000000;
    D_002E31A0 = 0;
    D_002E319C = 0;
    D_00524F48 = (D_00524F48 & 0xc) | ((D_002C5958.w0 & 0x104004) != 0);
    if (D_002C5958.w0 & 0x8000004) {
        D_00524F48 |= 8;
    } else {
        if (D_00524F48 & 8) func_0012ca38();
        D_00524F48 &= ~8;
    }
    if (!func_00122ff8(D_002E31B0)) func_0012fc58();
    o = D_002E26A0;
    if (D_002C5960 >> 2 & 1) goto end;
    if (!o) goto end;
    if (D_002E27A8 == 2) goto end;
    if (D_002C5958.w0 >> 27 & 1) goto ret;
    pad = &D_002C5BB0;
    if (D_002C5958.w0 & 0x104004) {
        if (pad->x8 & 4) D_002E3190.w0 |= 0x1000000;
        func_0012ca38();
        return 0;
    }
    D_00524F48 |= 2;
    func_0012dc70();
    if (func_001375d8(o)) D_00524F50 = 0;
    if (D_002E3170.p == &D_002E2FD8[0]) {
        if (D_00524F50 && (pad->x4 & 0x40000)) {
            memset(&D_002E3170, 0, 32);
            D_002E3170.p = &D_002E2FD8[1];
            D_00524F40 = &D_002E3170;
        }
    } else {
        if (!(pad->x4 & 0x40000) || !D_00524F50) {
            memset(&D_002E3170, 0, 32);
            D_002E3170.p = &D_002E2FD8[0];
            D_002E2FD8[0].xc = 0;
            D_00524F40 = &D_002E3170;
        }
    }
    if (func_001375d8(o)) return 0;
    if (!(o->x370 >> 34 & 1)) goto end;
    if (D_00524F40 == &D_002E3170) {
        k = o->x70;
        if ((u32)(k - 24) < 2 || k == 33 || k == 8) {
            if (pad->x4 & 4) D_002E3190.w0 |= 0x8000000;
        } else if (pad->x8 & 4) {
            D_002E3190.w0 |= 0x1000000;
            return 0;
        }
    }
    mask = 0x390000;
    if (D_002E3170.p->x0 != 5) {
        if (pad->x8 & 8) D_002E3168 |= 1;
        k = o->x70;
        if ((u32)(k - 24) < 2 || k == 33 || k == 8) {
            if (pad->x4 & 0x10) D_002E3190.w0 |= 0x10000000;
        } else if (pad->x8 & 0x10) {
            D_002E3190.w0 |= 0x4000000;
            return 0;
        }
        mask = 0x10000;
    }
    if (func_0012e1b0(pad)) {
        if (D_002E319C) {
            if (*D_002E319C & 0x10) {
                if (!(pad->x4 & mask)) goto skip;
            } else {
                if (!(pad->x8 & mask)) goto skip;
            }
            if (!(pad->x8 & mask)) D_002E3190.w0 &= ~0x2000000;
            func_0012e120();
        } else {
            D_002E319C = D_002E31A0 = func_001478c8(67);
            if (pad->x8 & 0x80000) func_0012dea0(D_00524F40->p, 0);
            else if (pad->x8 & 0x100000) func_0012dea0(D_00524F40->p, 1);
            else if (pad->x8 & 0x200000) func_0012dea0(D_00524F40->p, 2);
        }
    }
skip:
    func_0012f700(pad);
end:
    return 0;
ret:
    return 0;
}
