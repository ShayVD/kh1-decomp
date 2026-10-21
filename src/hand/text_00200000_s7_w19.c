#include "common.h"
#include "data/bss_0064.h"
/* func_00208ea8: needs s32 func_001f9438 (return type). */
typedef struct {
    u8 pad0[0xbe];
    s16 be;
    s16 c0;
    s16 c2;
    s16 c4;
    s16 c6;
    u8 padc8[0xcc - 0xc8];
    s16 cc;
    s16 ce;
    u8 padd0[0xd8 - 0xd0];
    s16 d8;
} Win;
void func_001f8e18(void *);
void func_001f8f30(void);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00208ea8(Win *o, s32 a1, s32 *strs, s32 k, s32 c0, s32 c1) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 cnt = o->cc;
    s32 rows = o->ce;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            { s32 col = (r == sr && c == sc) ? c1 : c0; func_001f9438(o, 0, x, y, strs[idx], k, col); }
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
void func_00209030(Win *o, s32 a1, s32 *strs, s32 k, s32 c0, s32 c1) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 cnt = o->cc;
    s32 rows = o->ce;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            { s32 col = (r == sr && c == sc) ? c1 : c0; func_001f94f0(o, 0, x, y, strs[idx], k, col); }
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

s32 func_001f9e48(void *, s32, s32, s32, s32, s32, s32);
void func_002091b8(Win *o, s32 a1, s32 *strs, s32 k, s32 c0, s32 c1) {
    s32 x0, dx, dy, sr, sc, idx, y, cnt, rows, cols;
    s32 r, c, x;
    x0 = o->be >> 4;
    dx = o->c2 >> 4;
    dy = o->c4 >> 4;
    sr = func_001fd518(o);
    sc = func_001fd538(o);
    idx = func_001fd618(o);
    y = func_001fd590(o);
    rows = o->ce + 1;
    cnt = o->cc;
    cols = o->d8;
    func_001f8e18(o);
    for (r = 0; r < rows; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            { s32 col = (r == sr && c == sc) ? c1 : c0; func_001f9e48(o, 0, x, y, strs[idx], k, col); }
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

/* func_00232390: func_0020dd38 takes 6 args (6th = id), y = 63 before the func_001fc308 call, callee return types as below. */
typedef struct { u8 pad[8]; s32 x8; } F8;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[];
#include "data/pieces/D_003F47A8.h"
s32 func_001f42b8(void);
void func_001f3708(void *, s32);
void func_0011d768(s32);
s32 func_00219428(void);
void func_00219418(s32);
void func_0020bc48(s32, s32, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fd518(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);

typedef struct { u8 p0[4]; u8 r[0x48e - 4]; u8 sel[0x499 - 0x48e]; u8 cnt[1]; } Base4BE8;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003F7C48.h"
typedef T7C48_3f7c48 T7C48;
#include "data/types/text_00200000_s7_w19_p.h"
#include "data/types/text_00200000_s7_w19.h"
#include "data/pieces/D_003F7A70.h"
extern T7D88 D_003F7D88[];
extern s32 D_0064765C;
void func_00205b30(void *, void *);
void func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020dd38(void *, s32, s32, s32, s32, s32);
s32 func_00207ca0(s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207d60(void *, s32, s32, s32, s32, s32, s32);



void func_00232390(void *a0) {
    u32 i;
    s32 n, j, y, id, max, cnt, c, col;
    T7A70 *e;
    T7C48 *t;
    for (j = 0; (u32)j < 7; j++) func_00205b30(a0, &D_003F7D88[j]);
    y = 63;
    func_001fc308(a0, 11, 13, 0, 0, 61, 0, 0x80009100, 0x8027E4D4);
    func_001f9438(a0, 1, 490, 11, 426, 15, 0x4D508B2E);
    func_001f9438(a0, 0, 44, 42, 427, 15, 0x80C8C8C8);
    func_001f9438(a0, 0, 271, 42, 428, 15, 0x80C8C8C8);
    func_001f9438(a0, 1, 484, 42, 429, 15, 0x80C8C8C8);
    t = &((T7C48_3f7c48 *)&D_003F7C48)[D_0064765C];
    e = &D_003F7A70[t->b2];
    n = t->n;
    for (j = 0; j < n; j++) {
        id = e->id;
        max = e->max;
        e++;
        cnt = ((Base4BE8 *)D_00304BE8)->cnt[id];
        c = cnt < max ? 2 : 0;
        func_0020dd38(a0, c, 247, y, 194, id);
        col = func_00207ca0(0);
        func_001f9438(a0, 0, 400, y + 7, 85, 12, col);
        func_001fb428(a0, 0, 1, 0, 418, y + 7, max, 12, col);
        func_00207d60(a0, c, 445, y, 480, cnt, 12);
        y += 28;
    }
}

/* func_001c8a00: the four stack values read into f32 locals first (x, y, f, z order), then scaled. */
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4a;
typedef struct {
    union {
        u64 flags;
        struct { s32 lo; f32 f4; f32 f8; f32 fc; f32 f10; f32 f14; } s;
    } u;
    f32 t0;
    f32 t1;
    f32 t2;
    u8 pad24[4];
    s32 x28;
    s32 x2c;
    s32 x30;
    u8 pad34[0xc];
    V4a p40;
    V4a p50;
    V4a p60;
    V4a p70;
    V4a p80;
    V4a p90;
    f32 r[3];
    s32 xac;
    f32 fb0;
    s32 xb4;
    u8 padb8[8];
    V4a v0;
    V4a a, b, c, d, e;
    f32 f120, f124, f128, f12c;
} Cam;
extern Cam D_003C5510;
void func_001c6890(void);

#define WRAP(a) while (1) { if (a > 3.1415928f) a -= 6.2831855f; else if (a < -3.1415928f) a += 6.2831855f; else break; }
s32 func_001c8a00(VM *vm) {
    f32 x, y, z, f;
    s32 sp;
    func_001c6890();
    D_003C5510.u.flags |= 2;
    D_003C5510.t1 = 0;
    sp = vm->sp;
    x = vm->stk[sp - 2];
    y = vm->stk[sp - 1];
    f = vm->stk[sp - 3];
    z = vm->stk[sp];
    D_003C5510.p80.x = x / 180.0f * 3.1415928f;
    D_003C5510.p80.y = y / 180.0f * 3.1415928f;
    D_003C5510.p80.z = z / 180.0f * 3.1415928f;
    D_003C5510.u.s.f8 = f * 2.0f;
    WRAP(D_003C5510.p80.x);
    WRAP(D_003C5510.p80.y);
    WRAP(D_003C5510.p80.z);
    D_003C5510.p50.x = D_003C5510.b.x;
    D_003C5510.p50.y = D_003C5510.b.y;
    D_003C5510.p50.z = D_003C5510.b.z;
    vm->sp = sp - 4;
    return 2;
}
#include "data/pieces/D_003F7D88.h"
