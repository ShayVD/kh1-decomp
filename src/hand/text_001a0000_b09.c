#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) GV4;
typedef struct { u128 a, b; } __attribute__((aligned(16))) GT32;
extern u128 D_00372770[2];
extern s8 D_00372790[];
s8 *func_001aa950(s32);
void func_001aa9d0(s32);
void func_00267530(GV4 *, GV4 *, GV4 *);
void func_002674b0(GV4 *, GV4 *, f32);
void func_00267518(GV4 *, GV4 *, GV4 *);

void func_001a9460(f32 t, u32 c0, u32 c1, u32 *dst) {
    GV4 a;
    GV4 b;
    s8 *tb;
    s32 n;
    s32 i;
    u32 *p;
    f32 f;

    tb = func_001aa950(32);
    n = t;
    ((u128 *)tb)[0] = D_00372770[0];
    ((u128 *)tb)[1] = D_00372770[1];
    if (n < 0) {
        if (n < -256)
            n = -256;
        n += 256;
        p = (u32 *)(((n & 0xe0) + D_00372790[n & 0x1f]) * 4 + (u32)dst);
        for (i = n; i < 256; i++) {
            *p = c0;
            p += tb[i & 0x1f];
        }
        p = dst;
        f = n;
        i = 0;
    } else {
        if (n >= 256)
            n = 255;
        p = dst;
        for (i = 0; i < n; i++) {
            *p = c1;
            p += tb[i & 0x1f];
        }
        f = 256.0f - n;
        n = 256;
    }
    b.x = ((u8 *)&c1)[0];
    b.y = ((u8 *)&c1)[1];
    b.z = ((u8 *)&c1)[2];
    b.w = ((u8 *)&c1)[3];
    a.x = ((u8 *)&c0)[0];
    a.y = ((u8 *)&c0)[1];
    a.z = ((u8 *)&c0)[2];
    a.w = ((u8 *)&c0)[3];
    func_00267530(&a, &a, &b);
    func_002674b0(&a, &a, f);
    for (; i < n; i++) {
        *p = (u32)b.w << 24 | (u32)b.z << 16 | (u32)b.y << 8 | (u32)b.x;
        func_00267518(&b, &b, &a);
        p += tb[i & 0x1f];
    }
    func_001aa9d0(32);
}

#include "data/pieces/D_0037A378.h"

#include "data/data_0037.h"
