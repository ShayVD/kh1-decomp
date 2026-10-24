/* Primitives sent at once, the nostrict_nofill part (docs/modules.md
 * "Session 45"; prim.c has the list).  func_002386c0(src, n, buf) sends n
 * lines (6 qwords each) in one packet; func_002388b8(src, n, buf) writes n
 * textured quads (as prim.nostrict.c's func_00238768) into buf and returns
 * the end: the HUD's sprites go through it. */
#include "common.h"
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

/* func_00238768 is in prim.nostrict.c. */

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
