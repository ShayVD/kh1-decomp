#include "common.h"
#include "data/bss_0065.h"
#include "gfx/gspkt.h"

typedef int u128 __attribute__((mode(TI)));

void func_002386c0(u128 *src, s32 n, u128 *buf) {
    s32 k = 2;
    s32 i;
    u64 t;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 6;
        d[0] = src[i * 6 + 0];
        d[1] = src[i * 6 + 1];
        d[2] = src[i * 6 + 2];
        d[3] = src[i * 6 + 3];
        d[4] = src[i * 6 + 4];
        d[5] = src[i * 6 + 5];
    }
    buf[1] = 0;
    ((u64 *)&buf[1])[1] = 0x43413E;
    t = n | 0x8000;
    t |= (u64)0x60AB4000 << 32;
    ((u64 *)&buf[1])[0] = t;
    func_00237018(buf, k, 1);
}

u128 *func_002388b8(u128 *src, s32 n, u128 *buf) {
    s32 k = 1;
    u64 *e;
    s32 i;
    u64 t;
    buf[0] = 0;
    t = (n * 2) | 0x8000;
    t |= (u64)0xC0ADC000 << 32;
    ((u64 *)buf)[0] = t;
    ((u64 *)buf)[1] = 0x413413413EEE;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 24;
        ((u64 *)d)[0] = 0;
        ((u64 *)d)[1] = 63;
        d[1] = src[i * 14 + 0];
        d[2] = src[i * 14 + 1];
        d[3] = src[i * 14 + 2];
        d[4] = src[i * 14 + 6];
        d[5] = src[i * 14 + 10];
        d[6] = src[i * 14 + 3];
        d[7] = src[i * 14 + 7];
        d[8] = src[i * 14 + 11];
        d[9] = src[i * 14 + 4];
        d[10] = src[i * 14 + 8];
        d[11] = src[i * 14 + 12];
        e = (u64 *)&d[12];
        e[0] = 0;
        e[1] = 63;
        d[13] = src[i * 14 + 0];
        d[14] = src[i * 14 + 1];
        d[15] = src[i * 14 + 4];
        d[16] = src[i * 14 + 8];
        d[17] = src[i * 14 + 12];
        d[18] = src[i * 14 + 3];
        d[19] = src[i * 14 + 7];
        d[20] = src[i * 14 + 11];
        d[21] = src[i * 14 + 5];
        d[22] = src[i * 14 + 9];
        d[23] = src[i * 14 + 13];
    }
    return buf + k;
}

typedef struct { u8 r, g, b, a; } Rgba;
typedef struct { u8 pad[4]; u16 x4; } Res;
extern f32 D_00650DD0;
extern s32 D_006488F0;
Res *func_001478c8(s32);
s32 func_00147808(s32);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);

void func_00239558(s32 id, s32 x, s32 y, s32 c) {
    Rgba col;
    u8 v = c;
    col.r = v;
    col.g = v;
    col.b = v;
    col.a = D_00650DD0 * 128.0f;
    D_006488F0 = func_001f0638(D_006488F0, 1, *(s32 *)&col, ((x * 16 + 0x7100) >> 4) - 0x700,
                               ((y * 16 + 0x7420) >> 4) - 0x740, func_00147808(func_001478c8(id)->x4));
}
#include "data/bss_0064_mixed.h"
