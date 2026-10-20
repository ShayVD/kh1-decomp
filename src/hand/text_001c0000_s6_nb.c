#include "common.h"
#include "data/bss_0066.h"
/* func_001cdcb8: needs func_001c4640 declared non-void (s32) */
typedef struct { u8 pad0[0x10]; f32 pos[3]; } Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
s32 func_001c4640(Msg *m);
s32 func_001cdcb8(VM *vm) {
    Msg m;
    m.type = 16;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

/* func_001ecc68: early `return G;` duplicated before the call (crossjump) */
extern s32 D_003E3C80;
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */
void func_001ed000(s32, u8 *, s32, s32, s32, s32, s32, s32);

s32 func_001ecc68(u8 *p, s32 a, s32 b, s32 c) {
    s32 v, x, y;
    v = p[16] << 24 | p[17] << 16;
    v |= p[18] << 8;
    v |= p[19];
    v = v * 4096 / 48000;
    x = p[30];
    y = p[31];
    if (D_003E3C80 & 4) return D_00633640;
    func_001ed000(18, p, a, b, c, v, x, y);
    return D_00633640;
}


/* func_001f0448: needs CONTEXT_ONLY func_001efba8 above; the q-loop divides by a local `ten` set before the pad test */
extern s32 D_003E8E04;
CONTEXT_ONLY s32 func_001efba8(void) { return D_003E8E04; }

s32 func_001f0448(s32 n, s32 pad, s32 val, s32 w) {
    s32 buf[10];
    s32 neg = 0;
    s32 cnt;
    s32 i;
    s32 ws = w * 16;
    if (val == 0) {
        if (n == 0 || pad == 0) {
            buf[0] = 0;
            cnt = 1;
        } else {
            for (i = n - 1; i >= 0; i--) buf[i] = 0;
            cnt = n;
        }
    } else {
        if (val < 0) { val = -val; neg = 1; }
        if (n == 0) {
            cnt = 0;
            do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < 10);
        } else {
            s32 ten;
            cnt = 0;
            ten = 10;
            if (pad == 0) {
                do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < n);
            } else {
                s32 *q = buf; do { if (val == 0) { *q = 0; q++; cnt++; } else { cnt++; *q = val % ten; val /= ten; q++; } } while (cnt < n);
            }
        }
    }
    return (cnt + neg) * (ws + func_001efba8()) >> 4;
}

/* func_0024d1c8: func_001f31a8 declared s32 (not void) */
extern s32 D_00669A60, D_00669A64, D_00669A7C, D_0046A55C, D_00669A68, D_00669A6C, D_00669A5C;
extern s32 D_00669A70, D_00669A74, D_00669A78, D_00669A58;
extern s16 D_0046A112, D_0046A1F2, D_0046A2D2, D_0046A3B2, D_0046A4DA;
extern s16 D_00669A40[8];
extern s32 D_0046A540, D_0046A544, D_0046A548, D_0046A54C, D_0046A550, D_0046A554, D_0046A558, D_0046A560, D_0046A5BC, D_0046A53C;
extern u8 D_0046A5E0[];
void func_00114820(void);
s32 func_001f31a8(void *, s32);

void func_0024d1c8(s16 *src, s32 a, s32 b, s32 c) {
    s32 i;
    s32 *pp = &c;
    func_00114820();
    D_00669A7C = -1;
    D_0046A55C = 0;
    D_00669A68 = 0;
    D_00669A6C = 0;
    D_00669A60 = a;
    D_00669A64 = b;
    D_00669A5C = c;
    if (c == 0) {
        D_00669A70 = -28;
        D_00669A74 = -16;
        D_00669A78 = -3;
        D_0046A112 = 0;
        D_0046A1F2 = 0;
        D_0046A2D2 = 0;
        D_0046A3B2 = 0;
        D_0046A4DA = 0;
    } else {
        D_00669A70 = 0;
        D_00669A74 = 0;
        D_00669A78 = 0;
        D_0046A112 = -1;
        D_0046A1F2 = -1;
        D_0046A2D2 = -1;
        D_0046A3B2 = -1;
        D_0046A4DA = -1;
    }
    D_00669A58 = 0;
    for (i = 0; i < 8; i++) D_00669A40[i] = -1;
    if (src != NULL) {
        for (i = 0; i < 8; i++) {
            D_00669A40[i] = src[i];
            if (src[i] < 0) break;
            D_00669A58++;
        }
    }
    if (D_00669A58 == 8) D_00669A58 = 7;
    D_0046A540 = 0;
    D_0046A544 = 1;
    D_0046A548 = 0;
    D_0046A54C = 1;
    D_0046A554 = D_0046A550 = 0;
    D_0046A560 = 0;
    D_0046A558 = 0;
    D_0046A5BC = 20;
    D_0046A53C = 0;
    func_001f31a8(D_0046A5E0, 1);
}
#include "data/bss_0066_mixed.h"
#include "data/data_003E.h"
#include "data/data_0046.h"
