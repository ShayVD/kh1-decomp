/* func_00109770: hand (strict). inl_fin as a plain-brace macro (not static inline), stores 6B80, BBDE0, 95160, BBE14, BBE04, BBE18. */
#include "common.h"

void func_00109388(void);
void func_001094f0(void);
void func_0015eda8(void);
void func_0015ee10(void);
void func_00120748(void *, void *, void (*)(void), s32);
void func_00109630(void);
void func_00232da0(void);
void func_001586a8(s32);
s32 func_00111830(void);
void func_00109588(void);
void func_001095b0(void);
void func_0015f018(void);
void func_001ba870(void);
void func_001ba7e0(void);
void func_00111020(s32);
s32 func_00111090(void);
void func_00111060(void);
s32 func_00111110(void);
s32 func_001110f0(void);
void func_001104e0(void);
void func_0010ff60(s32);
s32 func_00111150(void);
void func_00105f28(void);
void func_0010fd40(void);
void func_00114880(void);
s32 func_00109658(void);
void func_001140a0(void);
s32 func_00114280(void);
void func_0010f918(void);
void func_0011eeb0(void);
void func_0011de90(void);
void func_0010f8b8(void);
void func_00106000(s32);
void func_0010a3c0(void);
void func_0011edc8(void);
void func_0010a320(void);

extern char D_0048CCC8[];
extern u8 D_00F20000[];
extern volatile s32 D_002BBE08;
extern volatile u32 D_002BBDE0;
extern volatile s32 D_00495160;
extern volatile s32 D_00495164;
extern s32 D_002B647C, D_002B6474, D_002B6480, D_002B6774, D_002B6770;
extern s32 D_002C1360, D_002C1384;
extern s32 D_002BBE0C, D_002BBE04, D_002BBE14, D_002BBE18;
extern s32 D_002C5AD4, D_002C5AD8;
extern s32 D_002A6B80;
extern s32 D_002BC148[4];
extern s32 D_002BCDC8[4];
extern s32 D_002BCDA8, D_002BC128, D_002BCDD8, D_002BCDDC;

#define inl_fin(k) { \
    D_002A6B80 = 1; \
    D_002BBDE0 = k; \
    D_00495160 = 0; \
    D_002BBE14 = 0; \
    D_002BBE04 = 3; \
    D_002BBE18 = 0; \
    func_001104e0(); \
    func_0010ff60(254); }

/* rodata */
void func_00109770(void) {
    s32 k;
    func_00109388();
    func_001094f0();
    func_0015eda8();
    while (D_002BBE08 != 0) {
        switch (D_002BBDE0) {
        case 0:
            func_00120748(D_0048CCC8, D_00F20000, func_00109630, 0);
            D_002BBDE0 = 1;
            D_00495160 = 0;
            break;
        case 10:
            func_00232da0();
            func_001586a8(15);
            func_00111830();
            D_002B647C = 1;
            D_002B6474 = 1;
            goto c2;
        case 15:
            func_00111830();
            D_002B6480 = 1;
        case 2:
        c2:
            func_00109588();
        case 8:
        case 9:
            func_001095b0();
            break;
        case 4:
            D_002C1360 = 10000;
            D_002C1384 = 10000;
            func_0015f018();
            func_001ba870();
            D_002BBDE0 = 5;
            D_00495160 = 0;
            break;
        case 6:
            D_002C1360 = 10000;
            D_002C1384 = 10000;
            func_001ba7e0();
            D_002BBDE0 = 7;
            D_00495160 = 0;
            break;
        case 11:
            if (D_002B6774 == 0) {
                D_002BBE0C = 1;
                func_00111020(3);
                D_002BBDE0 = 12;
                D_00495160 = 0;
            }
            break;
        case 12:
            if (func_00111090() == 2) {
                func_00111060();
                D_002BBDE0 = 13;
                D_00495160 = 0;
            }
            break;
        case 13:
            if (D_002C5AD4 != 0) {
                inl_fin(14);
                break;
            }
            if (func_00111110() >= func_001110f0() - 1) {
                D_002A6B80 = 1;
            }
            if (func_00111090() == 4) {
                D_002A6B80 = 1;
                func_001104e0();
                func_0010ff60(254);
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        case 16:
            if (D_002B6774 == 0) {
                D_002BBE0C = 1;
                func_00111020(5);
                D_002BBDE0 = 17;
                D_00495160 = 0;
            }
            break;
        case 17:
            if (func_00111090() == 2) {
                func_00111060();
                D_002BBDE0 = 18;
                D_00495160 = 0;
            }
            break;
        case 18:
            if (D_002C5AD8 & 8) {
                inl_fin(19);
                break;
            }
            if (func_00111110() >= func_001110f0() - 1) {
                D_002A6B80 = 1;
            }
            if (func_00111090() == 4) {
                D_002A6B80 = 1;
                func_001104e0();
                func_0010ff60(254);
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        case 14:
        case 19:
            if (func_00111150() == 1) {
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        }
        func_00105f28();
        func_0010fd40();
        func_00114880();
        if (func_00109658()) {
            func_001140a0();
            if (func_00114280()) {
                func_0010f918();
                func_0011eeb0();
                func_0011de90();
                func_0010f8b8();
                func_001104e0();
                func_00106000(D_002BBE04);
                if (D_00495160 != 0) {
                    D_00495160--;
                    func_0010a3c0();
                    if (D_00495160 == 0) {
                        func_0015ee10();
                        func_0011edc8();
                        func_0015eda8();
                        D_002BBDE0 = D_00495164;
                        switch (D_002BBDE0) {
                        case 8:
                            D_002BC128 = D_002BC148[2];
                            D_002BCDA8 = D_002BC148[3];
                            D_002BCDD8 = 1;
                            D_002BCDDC = 0;
                            break;
                        case 9:
                            D_002BC128 = D_002BCDC8[0];
                            D_002BCDA8 = D_002BCDC8[2];
                            D_002BCDD8 = 1;
                            D_002BCDDC = 1;
                            break;
                        }
                        func_001094f0();
                        func_0010a320();
                        D_002B6770 = 0;
                    }
                }
            }
        }
    }
    func_0015ee10();
}

/* func_001fea38: hand (strict). Header stores after func_0011fb38 through union { u64 d; f32 f; } so the f32 o->t load stays after them; strict aliasing keeps the s16 xbe/xc0 loads after o->x/o->y. */

typedef struct {
    u8 pad0[0x48];
    s32 flags;
    u8 pad4c[0x74 - 0x4c];
    f32 sx;
    f32 sy;
    u8 pad7c[0x90 - 0x7c];
    s32 col;
    f32 t;
    u8 pad98[0xb0 - 0x98];
    s32 x;
    s32 y;
    u8 padb8[0xbe - 0xb8];
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    s16 xd4;
    s16 xd6;
    s16 xd8;
    s16 xda;
} WinA;

extern u8 D_003F1A70[];
typedef union { u64 d; f32 f; } QU;
s32 sceGsSyncPath(s32, u16);
f32 sinf(f32);
u64 *func_0011fb38(s32, u64, u64 *);
u64 *func_00122048(u32, u32);
void func_001220b8(void *);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 func_001f4378(WinA *);
s32 func_001f4570(WinA *);
s32 func_001f45e0(WinA *);

void func_001fea38(WinA *o) {
    s32 x[2];
    s32 y[3];
    s32 r[2];
    s32 g[2];
    s32 b[2];
    u64 *p;
    u64 *q;
    void *u;
    s32 col;
    f32 s;
    s32 h;

    if (o->xcc == 0) return;
    func_00266f38(func_00266c08(2), D_003F1A70);
    p = func_00122048(0x400, 0x80);
    q = p + 2;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    q[0] = 0x1000000000008001;
    q[1] = 0xe;
    q = func_0011fb38(0x42, 0x48, q + 2);
    ((QU *)q)[0].d = 0x2026400000008006;
    ((QU *)q)[1].d = 0x41;
    q += 2;
    s = sinf((f32)((s32)o->t % 64) * 0.015625f * 3.1415928f);
    if (func_001f4378(o)) {
        r[0] = (s32)(s * 20.0f) + 32;
        b[0] = g[0] = (s32)(s * 60.0f) + 96;
    } else {
        r[0] = (s32)(s * 20.0f) + 32;
        g[0] = (s32)(s * 60.0f) + 96;
        b[0] = (s32)(s * 30.0f) + 48;
    }
    r[1] = r[0] >> 1;
    g[1] = g[0] >> 1;
    b[1] = b[0] >> 1;
    x[0] = o->x + o->xbe + o->xda * o->xc2;
    x[1] = x[0] + o->xc2 - o->xc6;
    y[0] = o->y + o->xc0 + (o->xd2 * o->xc4 >> 4);
    h = o->xc4 - o->xc8;
    y[1] = y[0] + h / 2;
    y[2] = y[0] + h;
    col = o->col;
    if (o->flags & 1) {
        s32 cx = func_001f4570(o);
        s32 cy = func_001f45e0(o);
        f32 sx = o->sx;
        f32 sy = o->sy;
        f32 fx = cx;
        f32 fy = cy;
        x[0] = fx + (f32)(x[0] - cx) * sx;
        x[1] = fx + (f32)(x[1] - cx) * sx;
        y[0] = fy + (f32)(y[0] - cy) * sy;
        y[1] = fy + (f32)(y[1] - cy) * sy;
        y[2] = fy + (f32)(y[2] - cy) * sy;
    }
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[0]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[0]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[0]; ((s32 *)q)[1] = g[0]; ((s32 *)q)[2] = b[0]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[1]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[0]; ((s32 *)q)[1] = g[0]; ((s32 *)q)[2] = b[0]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[1]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[0]; ((s32 *)q)[1] = y[2]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    ((s32 *)q)[0] = r[1]; ((s32 *)q)[1] = g[1]; ((s32 *)q)[2] = b[1]; ((s32 *)q)[3] = col; q += 2;
    ((s32 *)q)[0] = x[1]; ((s32 *)q)[1] = y[2]; ((s32 *)q)[2] = 0x100000; ((s32 *)q)[3] = 0; q += 2;
    p[0] = ((s32)((u8 *)q - (u8 *)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
