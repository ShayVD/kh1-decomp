#include "common.h"
typedef struct { u16 active; u8 x2, x3; u32 cur; union { u64 d; u32 w; } press; u64 rep; } Pad52;
extern Pad52 D_002C5AD0;
typedef struct { s32 min, max; void (*fn)(s32); } Range52;
typedef struct { s32 a, b; } Pair52;
extern s32 D_004D5AF8;
extern Pair52 *D_004D5AF4;
extern s32 D_002BBBA0;
extern s32 D_002C5BB8;
void func_0011d768(s32);
void func_0010f0d0(s32, s32, s32);
void func_00121ee0(void *);

s32 func_0010f368(Range52 *r, s32 arg) {
    s32 old;
    if (D_002C5AD0.rep & 0x10100010) {
        old = D_004D5AF8;
        D_004D5AF8 = old - 1;
        if (D_004D5AF8 < r->min) {
            if (D_002C5AD0.press.d & 0x10100010) {
                D_004D5AF8 = r->max;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    } else if (D_002C5AD0.rep & 0x40400040) {
        old = D_004D5AF8;
        D_004D5AF8 = old + 1;
        if (r->max < D_004D5AF8) {
            if (D_002C5AD0.press.d & 0x40400040) {
                D_004D5AF8 = r->min;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    }
    if (!D_002BBBA0 && (D_002C5AD0.press.w & 0x4000)) {
        if (D_004D5AF8 != r->max) func_0011d768(3);
        D_004D5AF8 = r->max;
    }
    func_0010f0d0(D_004D5AF4[D_004D5AF8].a, D_004D5AF4[D_004D5AF8].b, arg);
    if (D_002C5BB8 & 1) {
        func_0011d768(2);
        r->fn(D_004D5AF8 + 1);
        func_00121ee0(D_004D5AF4);
        D_004D5AF4 = 0;
        return 1;
    }
    return 0;
}

extern s32 D_002BBDE8;
extern volatile s32 D_002BD114;
extern s32 D_002BCC24;
extern volatile s32 D_002BBDF0;
extern volatile u32 D_002BBDF4;
extern volatile s32 D_002BBDF8;
extern volatile u32 D_004D90F0;
extern volatile s32 D_004D90F4;
s32 func_00111798(void);
void func_001117b8(void);
void func_0010c378(void);

s32 func_00110218(void) {
    if (*(volatile u64 *)0x12001000 & 0x2000) {
        D_002BBDE8 = 1;
    } else {
        D_002BBDE8 = 0;
    }
    if (D_002BD114 == 0 && D_002BCC24 == 0) {
        D_002BBDF0++;
    }
    if (D_002BBDF4 < D_004D90F0) {
        D_002BBDF4 = D_002BBDF4 + 1;
    } else if (func_00111798() < 3) {
        if (D_002BBDF4 < D_004D90F0 + 60) {
            D_002BBDF4 = D_002BBDF4 + 1;
        } else {
            func_001117b8();
            D_002BBDF4 = 0;
        }
    } else {
        D_002BBDF4 = D_004D90F0;
    }
    D_002BBDF8++;
    D_004D90F4++;
    func_0010c378();
    return 0;
}

typedef f32 Mtx52[4][4] __attribute__((aligned(16)));
extern Mtx52 D_002BBE20, D_002BBE60, D_002BBEA0, D_002BBEE0, D_002BBF20, D_002BBF60;
extern Mtx52 D_004D8E40, D_004D9100, D_004D9140, D_004D9180, D_004D91C0, D_004D8E80;
extern f32 D_004D90F8;
void func_00110ce0(void);
void sceVu0CopyMatrix(void *, void *);
void func_00110618(void *, void *, void *, void *, void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_00110a48(f32 x) {
    func_00110ce0();
    sceVu0CopyMatrix(D_004D8E40, D_002BBE20);
    sceVu0CopyMatrix(D_004D9100, D_002BBE60);
    sceVu0CopyMatrix(D_004D9140, D_002BBEA0);
    sceVu0CopyMatrix(D_004D9180, D_002BBEE0);
    sceVu0CopyMatrix(D_004D91C0, D_002BBF20);
    sceVu0CopyMatrix(D_004D8E80, D_002BBF60);
    func_00110618(D_002BBE20, D_002BBE60, D_002BBEA0, D_002BBEE0, D_002BBF20, D_002BBF60, x,
                  0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 1.0f, 16777000.0f, 1.0f,
                  400000000.0f, D_004D90F8);
}
